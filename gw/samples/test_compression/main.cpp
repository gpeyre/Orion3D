//-------------------------------------------------------------------------
/** \name FSW file inclusion */
//-------------------------------------------------------------------------
//@{
#include "stdafx.h"
#include "../../gw_core/GW_Config.h"
#include "../../gw_multiresolution/GW_LinearWavelet.h"
#include "../../gw_multiresolution/GW_ButterflyWavelet.h"
#include "../../gw_multiresolution/GW_BaseOctahedron.h"
#include "../../gw_multiresolution/GW_BaseButterfly.h"
#include "../../gw_multiresolution_toolkit/GW_TopographicFunction.h"
#include "../../gw_multiresolution_toolkit/GW_DeltaFunction.h"
#include "../../gw_compression/GW_BitStream.h"
#include "../../gw_compression/GW_ZeroTreeCompressor.h"
#include "../../external/wrapper_lua/OR_WrapperLUA.h"
#include "../../external/wrapper_lua/OR_LUA_Float.h"
#include "../../external/wrapper_lua/OR_LUA_String.h"
#include "../../external/wrapper_lua/OR_LUA_Array.h"
#include "../../external/wrapper_lua/OR_LUA_Table.h"
using namespace GW;
using namespace OR;
//@}

//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef GW_DEBUG
	#pragma comment(lib, "gw_core_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit_dbg.lib")
	#pragma comment(lib, "gw_compression_dbg.lib")
	#pragma comment(lib, "orion3d_wrapper_lua_dbg.lib")
#else
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_multiresolution.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit_dbg.lib")
	#pragma comment(lib, "gw_compression.lib")
	#pragma comment(lib, "orion3d_wrapper_lua.lib")
#endif // GW_DEBUG
//@}


class GW_AnalyticFunction: public GW_TreeFunction_ABC
{

public:

	GW_Float GetValue(GW_Float rU, GW_Float rV) const
	{ 
		return 255*GW_ABS(cos( 5*rU*GW_TWOPI ));
	}
};

//-------------------------------------------------------------------------
/** @name Variables */
//-------------------------------------------------------------------------
//@{
/** base object */
GW_BaseOctahedron BaseOctahedron;
GW_BaseButterfly BaseButterFly( BaseOctahedron );
GW_BaseMesh_ABC* pActiveBaseMesh = &BaseOctahedron;
/** the main quadtree */
GW_QuadTree QuadTree( BaseOctahedron );
/** the Wavelet transform */
GW_LinearWavelet		LinearWavelet;
GW_ButterflyWavelet	ButterflyWavelet;
GW_WaveletTransform_ABC* pActiveTransform;
/** the compressor we used for output */
GW_ZeroTreeCompressor Compressor;
/** Different functions */
GW_AnalyticFunction		AnalyticFunction;
GW_TopographicFunction		ImageFunction;
GW_TreeFunction_ABC* pActiveFunction = NULL;
/** scaling type */
GW_Compressor_ABC::T_ScalingType ScalingType = GW_Compressor_ABC::kNormInf;

GW_U32 nNbrSteps = 200;
GW_Float rMaxBPV = 4.0f;
//@}

//#define IMAGE_FILE_NAME "../data/maurice.png"
#define NBR_BIT_PLANES 28
#define SPHERE_PRECISION 6
#define CONFIG_FILE	"config.lua"
#define MAIN_SCRIPT_NAME "draw_all_graph.m"

/*------------------------------------------------------------------------------*/
// Name : CompressionCallback
/**
 *  \param  BitStream [GW_BitStream&] the stream of bit compressed.
 *  \param  QuadTree [GW_QuadTree&] he quadtree being compressed.
 *  \return [GW_Bool] Do we need to continue compression ?
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  This is the callback used during compression.
 */
/*------------------------------------------------------------------------------*/
GW_Bool CompressionCallback_PerBitPlane( const GW_BitStream& BitStream, GW_QuadTree& QuadTree, GW_U8 nBitPlane )
{
	return GW_True;
}

GW_U32 nBitToUncompress = 5000;
/*------------------------------------------------------------------------------*/
// Name : UnCompressionCallback
/**
 *  \param  BitStream [GW_BitStream&] the stream of bit compressed.
 *  \param  QuadTree [GW_QuadTree&] he quadtree being compressed.
 *  \return [GW_Bool] Do we need to continue compression ?
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  This is the callback used during compression.
 */
/*------------------------------------------------------------------------------*/
GW_Bool UnCompressionCallback_PerBit( const GW_BitStream& BitStream, GW_QuadTree& QuadTree, GW_U8 nBitPlane )
{
	if( BitStream.GetNbrBits()>=nBitToUncompress )
		return GW_False;
	else
		return GW_True;
}


GW_U32 nNbrBitTotal;

void PerformCompression( const char* file_name )
{	
	GW_Float rNorm = 0;
	GW_BitStream BitStream;
	FILE* pFile = NULL;

	Compressor.SetCompressionCallback_PerBitPlane( CompressionCallback_PerBitPlane );
	Compressor.SetCompressionCallback_PerBit( NULL );
	/* first rebuild the tree. */
	cout << "Building quadtree from function ... ";
	QuadTree.BuildTree(*pActiveFunction, SPHERE_PRECISION);
	cout << "done." << endl;
	GW_Float rDist1 = GW_SphericalMaths::ComputeL1Distance( QuadTree, *pActiveFunction );
	GW_Float rDist2 = GW_SphericalMaths::ComputeL2Distance( QuadTree, *pActiveFunction );
	cout << "L1 distance before quantification : ";
	cout << " L1=" << rDist1 << " L2=" << rDist2 << endl;
	cout << "Performing forward transform ... ";
	QuadTree.ForwardTransform( *pActiveTransform, 0 );
	cout << "done." << endl;
	cout << "Begining compression of the data in file " << file_name << " (" << NBR_BIT_PLANES << " bit planes)." << endl;
	pFile = fopen( file_name, "wb" );	
	GW_ASSERT( pFile!=NULL );
	BitStream.Reset( pFile, GW_BitStream::kWriteMode );
	Compressor.Compress( BitStream, QuadTree, NBR_BIT_PLANES, ScalingType );
	cout << "done." << endl;
	cout << "Number of bit used " << BitStream.GetNbrBits() << endl;
	BitStream.Flush();	// The most important : don't forget to flush the rest of the stream before closing the file !
	fclose(pFile);
	QuadTree.BackwardTransform( LinearWavelet, 0 );
	rDist1 = GW_SphericalMaths::ComputeL1Distance( QuadTree, *pActiveFunction );
	rDist2 = GW_SphericalMaths::ComputeL2Distance( QuadTree, *pActiveFunction );
	cout << "Distance after quantification : ";
	cout << " L1=" << rDist1 << " L2=" << rDist2 << endl;
	cout << "---" << endl;

	nNbrBitTotal = BitStream.GetNbrBits();
}

void PerformUnCompression( const char* file_name, const char* test_name, const char* test_caption )
{
	GW_Float rNorm = 0;
	GW_BitStream BitStream;
	FILE* pFile = NULL;
	GW_Float rNbrBitPerVertexForPerfect = nNbrBitTotal/QuadTree.GetBaseMesh().GetNbrVertex( QuadTree.GetDepth() );
	GW_CompressionHeader CompressionHeader;

	Compressor.SetCompressionCallback_PerBitPlane( CompressionCallback_PerBitPlane );
	Compressor.SetCompressionCallback_PerBit( UnCompressionCallback_PerBit );
	
	cout << "Decompression of the data from file '" << file_name << "'." << endl;

	/* print some informations found in file */
	CompressionHeader.ReadFromFile( file_name );
	cout << "These informations where found in the compressed file :" << endl;
	cout << "    - Base mesh name  : " << CompressionHeader.GetBaseMeshName() << endl;
	cout << "    - Transform name  : " << CompressionHeader.GetTransformName() << endl;
	cout << "    - Compressor name : " << CompressionHeader.GetCompressorName() << endl;
	cout << "    - Comments        : " << CompressionHeader.GetComments() << endl;
	cout << "    - Nbr bit planes  : " << CompressionHeader.GetNbrBitPlane() << endl;
	cout << "    - Scaling type    : " << CompressionHeader.GetScalingTypeString() << endl;
	cout << "    - Tree depth      : " << CompressionHeader.GetTreeDepth() << endl;
	cout << "    - Max coef value  : " << CompressionHeader.GetMaxCoefValue() << endl;

	/* print the header of the matlab file */
	std::ofstream ResultFileMatlab;
	ResultFileMatlab.precision( 30 );
	ResultFileMatlab.open( (string(test_name) + ".m").c_str(), std::ios::out );


	ResultFileMatlab << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	ResultFileMatlab << "% Distortion result for decomression of file " << file_name << endl;
	ResultFileMatlab << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl << endl;

	GW_Float rStep = rMaxBPV/((float)nNbrSteps);
	GW_Float *aL2Error = new GW_Float[nNbrSteps];
	GW_Float *aL1Error = new GW_Float[nNbrSteps];
	GW_Float *aBPP = new GW_Float[nNbrSteps];	
	GW_Float rNbrBitPerVertex = 0;
	for( GW_U32 i = 1; i<=nNbrSteps; ++i )
	{
		rNbrBitPerVertex+=rStep;
		nBitToUncompress = (GW_U32) rNbrBitPerVertex*QuadTree.GetBaseMesh().GetNbrVertex( QuadTree.GetDepth());
		/* first rebuild the tree. */		
		pFile = fopen( file_name, "rb" );	
		GW_ASSERT( pFile!=NULL );
		BitStream.Reset( pFile, GW_BitStream::kReadMode );
		Compressor.UnCompress( BitStream, QuadTree );
		BitStream.Flush();	// The most important : don't forget to flush the rest of the stream before closing the file !
		fclose(pFile);
		QuadTree.BackwardTransform( *pActiveTransform, 0 );
		GW_Float rDist1 = GW_SphericalMaths::ComputeL1Distance( QuadTree, *pActiveFunction );
		GW_Float rDist2 = GW_SphericalMaths::ComputeL2Distance( QuadTree, *pActiveFunction );
		cout << i << "/" << nNbrSteps << " : " << nBitToUncompress << " bits. Erreurs : " << " L1=" << rDist1 << " L2=" << rDist2 << endl;
		GW_ASSERT( i<nNbrSteps );
		aL1Error[i-1] = rDist1;
		aL2Error[i-1] = rDist2;
		aBPP[i-1] = rNbrBitPerVertex;
	}
	cout << "---" << endl;
	/* process the Matlab file */
	ResultFileMatlab << "file_name = '" << file_name << "';" << endl;
	ResultFileMatlab << "test_name = '" << test_name << "';" << endl;
	ResultFileMatlab << "test_caption = '" << test_caption << "';" << endl;
	ResultFileMatlab << "max_bpv = " << rMaxBPV << ";" << endl;
	ResultFileMatlab << "bit_planes = " << NBR_BIT_PLANES << ";" << endl;
	ResultFileMatlab << "nbr_vertex = " << QuadTree.GetBaseMesh().GetNbrVertex( QuadTree.GetDepth() ) << ";" << endl;
	ResultFileMatlab << "test_name = '" << test_name << "';" << endl;
	ResultFileMatlab << "l1_error = [";
	for( GW_U32 u=0; u<nNbrSteps; ++u )
	{
		ResultFileMatlab << aL1Error[u];
		if( u!=nNbrSteps-1 )
			ResultFileMatlab << ", ";
	}
	ResultFileMatlab << "];" << endl;
	ResultFileMatlab << "l2_error = [";
	for( GW_U32 u=0; u<nNbrSteps; ++u )
	{
		ResultFileMatlab << aL2Error[u];
		if( u!=nNbrSteps-1 )
			ResultFileMatlab << ", ";
	}
	ResultFileMatlab << "];" << endl;
	ResultFileMatlab << "bpv = [";
	for( GW_U32 u=0; u<nNbrSteps; ++u )
	{
		ResultFileMatlab << aBPP[u];
		if( u!=nNbrSteps-1 )
			ResultFileMatlab << ", ";
	}
	ResultFileMatlab << "];" << endl;
	ResultFileMatlab.close();

	GW_DELETEARRAY(aL2Error);
	GW_DELETEARRAY(aL1Error);
	GW_DELETEARRAY(aBPP);
}

/*------------------------------------------------------------------------------*/
// Name : SetUpTest
/**
 *  \param  transform [char*] ...
 *  \param  scaling [char*] ...
 *  \param  basemesh [char*] ...
 *  \param  func_type [char*] ...
 *  \param  image_file [char*] ...
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  An helper that set up datas for test.
 */
/*------------------------------------------------------------------------------*/
void SetUpTest( const char* test_name, const char* transform, const char* scaling, const char* basemesh, const char* func_type, const char* image_file )
{
	cout << "Setup for test '" << test_name << "'." << endl;
	/* scaling *************************************************/
	if( strcmp(scaling,"L1")==0 )
	{
		cout << "Scaling type : L1 norm." << endl;
		ScalingType = GW_Compressor_ABC::kNormL1;
	}
	else if( strcmp(scaling,"L2")==0 )
	{
		cout << "Scaling type : L2 norm." << endl;
		ScalingType = GW_Compressor_ABC::kNormL2;
	}
	else if( strcmp(scaling,"Inf")==0 )
	{
		cout << "Scaling type : infinite norm." << endl;
		ScalingType = GW_Compressor_ABC::kNormInf;
	}
	else
		cout << "Scaling type not supported." << endl;
	/* transform ************************************************/
	if( strcmp(transform,"Linear")==0 )
	{
		cout << "Wavelet transform : linear." << endl;
		pActiveTransform = &LinearWavelet;
	}
	else if( strcmp(transform,"Butterfly")==0 )
	{
		cout << "Wavelet transform : butterfly." << endl;
		pActiveTransform = &ButterflyWavelet;
	}
	else
		cout << "Transform type not supported." << endl;
	/* basemesh ************************************************/
	if( strcmp(basemesh,"Octahedron")==0 )
	{
		cout << "Base mesh : octahedron." << endl;
		pActiveBaseMesh = &BaseOctahedron;
		QuadTree.SetBaseMesh( *pActiveBaseMesh );
	}
	else if( strcmp(basemesh,"Butterfly")==0 )
	{
		cout << "Base mesh : butterfly." << endl;
		pActiveBaseMesh = &BaseButterFly;
		QuadTree.SetBaseMesh( *pActiveBaseMesh );
	}
	else
		cout << "Base mesh type not supported." << endl;
	/* func_type ************************************************/
	if( strcmp(func_type,"Image")==0 )
	{
		cout << "Function type : image" << endl;
		/* loading data from an image **************************************/
		cout << "Loading Image file '" << image_file << "' ...";
		GW_RETURN_CODE bRes = ImageFunction.LoadFromImage(image_file);
		if( bRes<0 )
		{
			cout << "Loading failed." << endl;
			::exit(1);
		}
		cout << "Loading successful." << endl;
		pActiveFunction = &ImageFunction;
	}
	else if( strcmp(func_type,"Analytic")==0 )
	{
		cout << "Function type : analytic." << endl;
		pActiveFunction = &AnalyticFunction;
	}
	else
		cout << "Function type not supported." << endl;
	cout << "---" << endl;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : main 
 *
 *  \param  argc ...
 *  \param  argv ...
 *  \author Gabriel Peyré 11-24-2002
 *
 *	Entry point for the application.
 */ 
/*------------------------------------------------------------------------------*/
int main(int argc, char** argv)
{	
	/* parsing configuration file ***********************************************/
	OR_WrapperLUA LuaWrapper;
	/* process LUA code */
	GW_I32 nErr = LuaWrapper.DoFile(CONFIG_FILE);
	if( nErr!=0 )
	{
		cout << "Error processing configuration file" << CONFIG_FILE " : " << strerror(nErr) << endl;
		::exit(1);
	}
	/* Retrieve variable from config file. */
	OR_LUA_String start_whith("start_whith");
	OR_LUA_Array test_list("test_list");
	OR_LUA_Float nbr_steps("nbr_steps");
	OR_LUA_Float max_bpv("max_bpv");
	start_whith.GetFromLUA( LuaWrapper );
	test_list.GetFromLUA( LuaWrapper );
	nbr_steps.GetFromLUA( LuaWrapper );
	max_bpv.GetFromLUA( LuaWrapper );
	/* do some error check */
	if( test_list.GetError() )
	{
		cout << "Error processing configuration file" << CONFIG_FILE << endl;
		::exit(1);
	}
	/* cool caption */
	cout << endl << endl << start_whith.GetValue() << endl;
	/* set the nbr of tests */
	nNbrSteps = (GW_U32) nbr_steps.GetValue();
	rMaxBPV   = max_bpv.GetValue();

	/* print the header of the matlab file */
	std::ofstream Script;
	Script.open( MAIN_SCRIPT_NAME, std::ios::out );
	Script << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	Script << "% Draw all distorition curves - Automaticaly generated by test_compression " << endl;
	Script << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl << endl;

	/* launch the various tests **************************************/
	T_LUAVariableVector& testVect = test_list.GetArray();
	GW_U32 i = 0;
	cout << "---" << endl;
	for( IT_LUAVariableVector it=testVect.begin(); it!=testVect.end(); ++it )
	{
		GW_ASSERT( (*it)->GetType()==OR_LUA_TABLE );	// check before casting ...
		OR_LUA_Table* pVar = (OR_LUA_Table*) *it;
		string test_name, temp_file, scaling, transform, basemesh, func_type, image_file, test_caption;
		pVar->GetValue("test_name", test_name);
		pVar->GetValue("temp_file", temp_file);
		pVar->GetValue("scaling", scaling);
		pVar->GetValue("transform", transform);
		pVar->GetValue("basemesh", basemesh);
		pVar->GetValue("func_type", func_type);
		pVar->GetValue("image_file", image_file);
		pVar->GetValue("test_caption", test_caption);

		SetUpTest( test_name.c_str(), transform.c_str(), scaling.c_str(), basemesh.c_str(), func_type.c_str(), image_file.c_str()  );
		PerformCompression( temp_file.c_str() ); 
		PerformUnCompression( temp_file.c_str(), test_name.c_str(), test_caption.c_str() );

		Script << test_name << ";" << endl;
		Script << "draw_graph;" << endl;
	}

	Script.close();
	
	return 0;
}


