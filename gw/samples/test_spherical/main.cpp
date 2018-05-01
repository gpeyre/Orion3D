//-------------------------------------------------------------------------
/** \name FSW file inclusion */
//-------------------------------------------------------------------------
//@{
#include "stdafx.h"
#include "../../gw_toolkit/GW_InputOutput.h"
#include "../../gw_core/GW_Config.h"
#include "../../gw_multiresolution/GW_LinearWavelet.h"
#include "../../gw_multiresolution/GW_ButterflyWavelet.h"
#include "../../gw_multiresolution/GW_BaseButterfly.h"
#include "../../gw_multiresolution/GW_BaseSquare.h"
#include "../../gw_multiresolution/GW_BaseOctahedron.h"
#include "../../gw_multiresolution/GW_BaseTetrahedron.h"
#include "../../gw_multiresolution_toolkit/GW_TopographicFunction.h"
#include "../../gw_multiresolution_toolkit/GW_DeltaFunction.h"
#include "../../gw_compression/GW_BitStream.h"
#include "../../gw_compression/GW_ZeroTreeCompressor.h"
#include "../../gw_toolkit/GW_OpenGLHelper.h"
#include <GL/glut.h>
using namespace GW;
//@}

//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef GW_DEBUG
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "gw_core_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit_dbg.lib")
	#pragma comment(lib, "gw_compression_dbg.lib")
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_multiresolution.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit_dbg.lib")
	#pragma comment(lib, "gw_compression.lib")
#endif // GW_DEBUG
//@}

//-------------------------------------------------------------------------
/** @name 3D engine */
//-------------------------------------------------------------------------
//@{
/** base object */
GW_BaseOctahedron	BaseOctahedron;
GW_BaseTetrahedron	BaseTetrahedron;
GW_BaseButterfly	BaseButterFly( BaseOctahedron );
GW_BaseSquare		BaseSquare;
GW_BaseMesh_ABC* pActiveBaseMesh = &BaseOctahedron;
/** the main quadtree */
GW_QuadTree QuadTree( *pActiveBaseMesh );
/** the Wavelet transform */
GW_ButterflyWavelet ButterflyTransform;
GW_LinearWavelet LinearTransform;
GW_WaveletTransform_ABC* pActiveTransform = &LinearTransform;
/** the compressor we used for output */
GW_ZeroTreeCompressor Compressor;
/** Add one each time a forward is done, and remove one when a backward is done */
GW_I32 nForwardBackward = 0;
/** Functions*/
GW_TopographicFunction TopographicFunction;
GW_TopographicFunction EarthFunction;
GW_TopographicFunction ImageFunction;
GW_U32 DeltaLevel = 2;
GW_DeltaFunction DeltaFunc(DeltaLevel,3,0,4.0f);
GW_TreeFunction_ABC* pActiveFunction = NULL;
//@}


GLfloat nLineWidth = 4;
#define BACKGROUND_COLOR		1
#define WINDOW_SIZE				600
#define SPOT_LIGHT_INTENSITY	0.2
#define AMBIENT_LIGHT_INTENSITY 0.5

#define ETOPO_FILE_NAME	"../ressources/images/ETOPO15"
#define ETOPO_RESOLUTION 15
#define EARTH_FILE_NAME "../ressources/images/earth_nb.jpg"
#define IMAGE_FILE_NAME "../ressources/images/lena.gif"
#define COMPRESSED_FILE_NAME "compressed"
#define COMPRESSED_FILE_EXTENSION "fsw"
#ifdef GW_DEBUG
	#define START_PRECISION 3
#else
	#define START_PRECISION 5
#endif

class GW_AnalyticFunction: public GW_TreeFunction_ABC
{
public:
	#define NBR_FUNCTIONS 4
	GW_AnalyticFunction():GW_TreeFunction_ABC(), nFuncNum_(0) {}
	GW_Float GetValue(GW_Float rU, GW_Float rV) const
	{ 
		if( nFuncNum_==0 )
			return 0.1f*cos( 5*rU*GW_TWOPI );
		else if( nFuncNum_==1 )
			return 0;
		else if( nFuncNum_==2 )
			return 0.1f*cos( 5*rV*GW_TWOPI );
		else
			return 0.1*cos( 5*GW_TWOPI*sqrt( rU*rU + rV*rV ) );
	}
	const char* GetFunctionExpression()
	{
		if( nFuncNum_==0 )
			return "0.1f*cos( 5*rU*GW_TWOPI )";
		else if( nFuncNum_==1 )
			return "0";
		else if( nFuncNum_==2 )
			return "0.1f*cos( 5*rV*GW_TWOPI )";
		else
			return "0.1*cos( sqrt( rU*rU + rV*rV ) )";
	}
	void ToogleFunction()
	{
		nFuncNum_ = (nFuncNum_+1)%NBR_FUNCTIONS;
	}
private:
	GW_U32 nFuncNum_;
};
GW_AnalyticFunction AnalyticFunction;

/*------------------------------------------------------------------------------*/
// Name : VertexDisplayer
/**
 *  \param  vert [GW_QuadTreeVertex&] The vertex to display.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Callback function for FSW/Orion3D wrapper.
 *	Display a vertex according to the etopo data range
 */
/*------------------------------------------------------------------------------*/
void VertexDisplayer( GW_QuadTreeVertex& vert )
{
	GLfloat aColor[4] = {0.8,0.8,0.8,1};
	GLfloat aSpecular[4] = {0.3f,0.3f,0.3f,1};

	GW_Vector3D Pos;
	GW_Vector3D Normal;
	/* compute position and normal according to the geometry */
	if( pActiveBaseMesh==&BaseSquare && pActiveFunction!=&DeltaFunc )	// planar
	{
		Pos = vert.GetPosition();
		Pos[2] += vert.GetValue();
		pActiveFunction->ComputePlanarNormal(Normal, 0.5*(Pos[0]+1), 0.5f*(Pos[1]+1));
	}
	else if( pActiveFunction==&DeltaFunc )
	{
		GW_Float rLong, rLat;
		GW_SphericalMaths::ConvertCartesianToSpherical(vert.GetPosition(), rLong, rLat);	
		if( pActiveBaseMesh==&BaseSquare )
		{
			Pos = vert.GetPosition();
			Pos[2] += 0.2*vert.GetValue();
			Normal = GW_Vector3D(0,0,0);
		}
		else
		{
			Pos = vert.GetPosition()*( 1 + 0.1*vert.GetValue() );
			if( nForwardBackward==0 )
				pActiveFunction->ComputeSphericalNormal(Normal, rLong, rLat);
			else
				Normal = GW_Vector3D(0,0,1);
		}
	}
	else								// spherical
	{		
		GW_Float rLong, rLat;
		GW_SphericalMaths::ConvertCartesianToSpherical(vert.GetPosition(), rLong, rLat);	
		Pos = vert.GetPosition()*( 1 + vert.GetValue() );	
		if( nForwardBackward==0 )
			pActiveFunction->ComputeSphericalNormal(Normal, rLong, rLat);
		else
			Normal = Pos;

	}

	if( nForwardBackward==0 && (pActiveFunction==&ImageFunction || pActiveFunction==&EarthFunction) )
	{
		aColor[0] = aColor[1] = aColor[2] = 10.0f*vert.GetValue();
	}
	else if( nForwardBackward==1 && (pActiveFunction==&ImageFunction || pActiveFunction==&EarthFunction) )
	{
		aColor[0] = aColor[1] = aColor[2] = 50.0f*vert.GetValue();
	}
	else if( pActiveFunction==&DeltaFunc )
	{
		if( vert.GetValue()>=0 )
		{
			aColor[0] = 1;
			aColor[1] = aColor[2] = 1-vert.GetValue()/4;
		}
		else
		{
			aColor[0] = aColor[1] = 1+vert.GetValue()/2;
			aColor[2] = 1;
		}
	}
	else
	{
		if( vert.GetValue()>=0 )
		{
			aColor[0] = 1;
			aColor[1] = aColor[2] = 1-4*vert.GetValue();
		}
		else
		{
			aColor[0] = aColor[1] = 1+4*vert.GetValue();
			aColor[2] = 1;
		}
	}

	/* aColor[0] = aColor[1] = aColor[2] = 0;
	aSpecular[0] = aSpecular[1] = aSpecular[2] = 0; */

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat*) aSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat*) aColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat*) aColor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

	glNormal( Normal );
	glVertex( Pos );
}

#define MAX_DEPTH 7
GW_Float rTarget_U = 0.5f;
GW_Float rTarget_V = 0.5f;

GW_Bool CompressionCallback( const GW_BitStream& BitStream, GW_QuadTree& QuadTree, GW_U8 nBitPlane )
{
	cout << ((GW_U32) nBitPlane) << " ";
	return true;
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


/*------------------------------------------------------------------------------*/
/** 
 * Name : init
 *
 *  \author Gabriel Peyré 2001-10-17
 *
 *	Load the data on the sphere (image or ETOPO).
 */ 
/*------------------------------------------------------------------------------*/
void init()
{	
	GW_RETURN_CODE bRes;
	/* loading data from a ETOPO file  ********************************/
	cout << "Loading ETOPO file " << ETOPO_FILE_NAME << " ..." << endl;
	bRes = TopographicFunction.LoadFromFile(ETOPO_FILE_NAME, 360*(60/ETOPO_RESOLUTION), 180*(60/ETOPO_RESOLUTION), "rb", "I16");
	if( bRes<0 )
	{
		cout << "Loading failed." << endl;
		::exit(1);
	}
	cout << "Loading successful." << endl;
	TopographicFunction.ScaleTo( 0,0.1f );

	/* loading data from an image **************************************/
	cout << "Loading image file " << IMAGE_FILE_NAME << " ..." << endl;
	bRes = ImageFunction.LoadFromImage(IMAGE_FILE_NAME);
	if( bRes<0 )
	{
		cout << "Loading failed." << endl;
		::exit(1);
	}
	cout << "Loading successful." << endl;
	cout << "----" << endl;
	ImageFunction.ScaleTo( 0,0.1f );

	/* loading data from an image of earth **************************************/
	cout << "Loading Earth image file " << EARTH_FILE_NAME << " ..." << endl;
	bRes = EarthFunction.LoadFromImage(EARTH_FILE_NAME);
	if( bRes<0 )
	{
		cout << "Loading failed." << endl;
		::exit(1);
	}
	cout << "Loading successful." << endl;
	cout << "----" << endl;
	EarthFunction.ScaleTo( 0,0.1f );

	pActiveFunction = &ImageFunction;
	QuadTree.BuildTree(*pActiveFunction, START_PRECISION);	
}

void init_gl()
{
	/* init opengl */
	glEnable(GL_DEPTH_TEST);
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	/* load light */
	GLfloat light_color[4] = {SPOT_LIGHT_INTENSITY,SPOT_LIGHT_INTENSITY,SPOT_LIGHT_INTENSITY,SPOT_LIGHT_INTENSITY};
	GLfloat light_ambient_color[4] = {AMBIENT_LIGHT_INTENSITY,AMBIENT_LIGHT_INTENSITY,AMBIENT_LIGHT_INTENSITY,AMBIENT_LIGHT_INTENSITY};
	glLightfv( GL_LIGHT0, GL_AMBIENT, light_color );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_color );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light_color );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_color);
	/* background color */
	glClearColor( BACKGROUND_COLOR,BACKGROUND_COLOR,BACKGROUND_COLOR,BACKGROUND_COLOR );
}

__forceinline
void display_rec( GW_QuadTreeNode& CurNode, GW_Bool bClockWise )
{
	if( CurNode.GetChildNode(0)!=NULL )
	{
		/* we are not on a leaf, so we should  recurse */
		for( GW_U32 i=0; i<4; ++i )
		{
			GW_ASSERT( CurNode.GetChildNode(i)!=NULL );
			if( i!=0 )
				display_rec( *CurNode.GetChildNode(i), !bClockWise );
			else
				display_rec( *CurNode.GetChildNode(i), bClockWise );
		}
	}
	else
	{
		/* we are on a leaf or we were told to stop recursing, so draw */
		GW_QuadTreeVertex* pVert1 = CurNode.GetVertex( QT_Vert1 );GW_ASSERT( pVert1!=NULL );
		GW_QuadTreeVertex* pVert2 = CurNode.GetVertex( QT_Vert2 );GW_ASSERT( pVert2!=NULL );
		GW_QuadTreeVertex* pVert3 = CurNode.GetVertex( QT_Vert3 );GW_ASSERT( pVert3!=NULL );
		/* use current displayer to draw the vertex to screen */
		if( bClockWise )
		{
			VertexDisplayer( *pVert1 ); VertexDisplayer( *pVert2 ); VertexDisplayer( *pVert3 );
		}
		else
		{
			VertexDisplayer( *pVert3 ); VertexDisplayer( *pVert2 ); VertexDisplayer( *pVert1 );
		}		
	}
}


void display()
{
	GW_InputOutput::PrepareDisplay();

	glPushMatrix();

	/* render each face of the octogone */
	T_QuadTreeNodeVector BaseNodeVector = QuadTree.GetBaseNodeVector();
	GW_U32 i = 0;
	for( IT_QuadTreeNodeVector it=BaseNodeVector.begin(); it!=BaseNodeVector.end(); ++it )
	{
		GW_QuadTreeNode* pNode = *it;
		GW_ASSERT( pNode!=NULL );
		glBegin( GL_TRIANGLES );
		GW_Bool bClockWise;
		if( BaseNodeVector.size()==8 || BaseNodeVector.size()==2 )	// special case for octahedron
		{
			if( i<4 )
				bClockWise = (i%2)==0;
			else
				bClockWise = (i%2)==1;
		}
		else
			bClockWise = GW_True;
		display_rec( *pNode, bClockWise );
		glEnd();
		i++;
	}
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

GW_U32 nSub = START_PRECISION;
GW_Bool bCompressionMade = GW_False;
GW_U32 nNbrBitTotal;
GW_Bool bWireFrame = GW_False;
/*------------------------------------------------------------------------------*/
// Name : keyboard
/**
 *  \param  button [FSW::GW_U32] key pressed.
 *  \param  x [FSW::GW_I32] x position of the mouse.
 *  \param  y [FSW::GW_I32] y position of the mouse.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  To handle the keyboard.
 */
/*------------------------------------------------------------------------------*/
void keyboard(unsigned char button, int x, int y)
{
	GW_Float rNorm = 0;
	GW_BitStream BitStream;
	FILE* pFile = NULL;
	char FileName[200];
	GW_U32 nNbrBitPlane = 28;
	GW_Float rNbrBitPerVertex;
	GW_Float rNbrBitPerVertexForPerfect;
	GW_CompressionHeader CompressionHeader;

	switch((char) button)
	{
	case 27:
		::exit(0);
		break;
	case 'l':	
		nForwardBackward++;
		cout << "Performing forward transform ... ";
		QuadTree.ForwardTransform( *pActiveTransform, 0 );
		cout << "done." << endl;
		cout << "---" << endl;
		break;
	case 'L':
		nForwardBackward--;
		cout << "Performing backward transform ... ";
		QuadTree.BackwardTransform( *pActiveTransform, 0 );
		cout << "done." << endl;
		cout << "---" << endl;
		break;
	case '+':
		nForwardBackward = 0;
		nSub++;
		cout << "Building tree, level " << nSub << " ... ";
		QuadTree.BuildTree(*pActiveFunction, nSub);
		cout << "done." << endl;
		cout << "---" << endl;
		if( pActiveFunction==&DeltaFunc )
		{
			DeltaFunc.PostBuildTree( QuadTree );
			QuadTree.BackwardTransform( *pActiveTransform, DeltaLevel );
		}
		break;
	case '-':
		nForwardBackward = 0;
		if( nSub!=0 )
			nSub--;
		cout << "Building tree, level " << nSub << " ... ";
		QuadTree.BuildTree(*pActiveFunction, nSub);
		cout << "done." << endl;
		cout << "---" << endl;
		if( pActiveFunction==&DeltaFunc )
		{
			DeltaFunc.PostBuildTree( QuadTree );
			QuadTree.BackwardTransform( *pActiveTransform, DeltaLevel );
		}
		break;
	case 'a':
		nForwardBackward = 0;
		pActiveFunction = &DeltaFunc;
		cout << "Building Wavelet, level " << nSub << " ... ";
		QuadTree.BuildTree(DeltaFunc , nSub );
		rNorm = GW_SphericalMaths::ComputeIntegral( QuadTree );
		cout << "empty tree build ... ";
		DeltaFunc.PostBuildTree( QuadTree );
		rNorm = GW_SphericalMaths::ComputeIntegral( QuadTree );
		cout << "post build done ... ";
		QuadTree.BackwardTransform( *pActiveTransform, DeltaLevel );
		rNorm = GW_SphericalMaths::ComputeIntegral( QuadTree );
		cout << "backward transform done." << endl;
		cout << "---" << endl;
		break;
	case 'c':
		nForwardBackward = 0;
		Compressor.SetCompressionCallback_PerBitPlane( CompressionCallback );
		Compressor.SetCompressionCallback_PerBit( NULL );
		/* first rebuild the tree. */
		cout << "Rebuilding the tree (to have up-to-date data) ... ";
		QuadTree.BuildTree(*pActiveFunction, nSub);
		cout << "done." << endl;
		cout << "Error before compression (should be 0) :";
		cout << " L1=" << GW_SphericalMaths::ComputeL1Distance( QuadTree, *pActiveFunction );
		cout << " L2=" << GW_SphericalMaths::ComputeL2Distance( QuadTree, *pActiveFunction ) << endl;
		cout << "Performing forward transform ... ";
		QuadTree.ForwardTransform( *pActiveTransform, 0 );
		cout << "done." << endl;
		sprintf( FileName, "%s_%d.%s", COMPRESSED_FILE_NAME, nNbrBitPlane, COMPRESSED_FILE_EXTENSION);
		cout << "Begining compression of the data in file " << FileName << " (" << nNbrBitPlane << " bit planes)." << endl;
		pFile = fopen( FileName, "wb" );	
		GW_ASSERT( pFile!=NULL );
		BitStream.Reset( pFile, GW_BitStream::kWriteMode );

		Compressor.Compress( BitStream, QuadTree, nNbrBitPlane, GW_ZeroTreeCompressor::kNormL2 );
		cout << endl;
		BitStream.Flush();	// The most important : don't forget to flush the rest of the stream before closing the file !
		fclose(pFile);
		nNbrBitTotal = BitStream.GetNbrBits();
		cout << "Compression finished" << endl;
		cout << "Performing backward transform ... ";
		QuadTree.BackwardTransform( *pActiveTransform, 0 );
		cout << "done." << endl;
		cout << "Number of bit used " << nNbrBitTotal << endl;
		cout << "[What you see is a quantified version of the data.]" << endl;
		cout << "Error after compression (quantification) :";
		cout << " L1=" << GW_SphericalMaths::ComputeL1Distance( QuadTree, *pActiveFunction );
		cout << " L2=" << GW_SphericalMaths::ComputeL2Distance( QuadTree, *pActiveFunction ) << endl;
		cout << "---" << endl;
		bCompressionMade = GW_True;
		break;
	case 'C':
		nForwardBackward = 0;
		if( !bCompressionMade )
		{
			cout << "You must perform a compression first. Press 'c'." << endl;
			cout << "---" << endl;
			break;
		}
		rNbrBitPerVertexForPerfect = nNbrBitTotal/QuadTree.GetBaseMesh().GetNbrVertex( QuadTree.GetDepth() );
		cout << "Enter the Number of bit per vertex (" << rNbrBitPerVertexForPerfect << " bits for a perfect reconstruction) : ";
		std::cin >> rNbrBitPerVertex;
		nBitToUncompress = rNbrBitPerVertex*QuadTree.GetBaseMesh().GetNbrVertex( QuadTree.GetDepth());
		Compressor.SetCompressionCallback_PerBitPlane( CompressionCallback );
		Compressor.SetCompressionCallback_PerBit( UnCompressionCallback_PerBit );
		/* first print some usefull information */
		sprintf( FileName, "%s_%d.%s", COMPRESSED_FILE_NAME, nNbrBitPlane, COMPRESSED_FILE_EXTENSION);
		CompressionHeader.ReadFromFile( FileName );
		cout << "These informations where found in the compressed file :" << endl;
		cout << "    - Base mesh name  : " << CompressionHeader.GetBaseMeshName() << endl;
		cout << "    - Transform name  : " << CompressionHeader.GetTransformName() << endl;
		cout << "    - Compressor name : " << CompressionHeader.GetCompressorName() << endl;
		cout << "    - Comments        : " << CompressionHeader.GetComments() << endl;
		cout << "    - Nbr bit planes  : " << CompressionHeader.GetNbrBitPlane() << endl;
		cout << "    - Scaling type    : " << CompressionHeader.GetScalingTypeString() << endl;
		cout << "    - Tree depth      : " << CompressionHeader.GetTreeDepth() << endl;
		cout << "    - Max coef value  : " << CompressionHeader.GetMaxCoefValue() << endl;
		/* then launch decompression */
		cout << "Begining uncompression of the data from file " << FileName << "." << endl;
		pFile = fopen( FileName, "rb" );
		GW_ASSERT( pFile!=NULL );
		BitStream.Reset( pFile, GW_BitStream::kReadMode );
		Compressor.UnCompress( BitStream, QuadTree );
		cout << endl;
		BitStream.Flush();	// The most important : don't forget to flush the rest of the stream before closing the file !
		fclose(pFile);
		cout << "Uncompression finished." << endl;
		cout << "Performing backward transform ... ";
		QuadTree.BackwardTransform( *pActiveTransform, 0 );
		cout << "done." << endl;
		cout << "Error after uncompression :";
		cout << " L1=" << GW_SphericalMaths::ComputeL1Distance( QuadTree, *pActiveFunction );
		cout << " L2=" << GW_SphericalMaths::ComputeL2Distance( QuadTree, *pActiveFunction ) << endl;
		cout << "---" << endl;
		break;
	case '\t':
		nForwardBackward = 0;
		/* swap between functions */
		if(pActiveFunction==&AnalyticFunction)
		{
			cout << "Now displaying image function." << endl;
			pActiveFunction = &ImageFunction;
		}
		else if(pActiveFunction==&ImageFunction)
		{
			cout << "Now displaying earth function." << endl;
			pActiveFunction = &EarthFunction;
		}
		else if( pActiveFunction==&EarthFunction)
		{
			cout << "Now displaying topographic function." << endl;
			pActiveFunction = &TopographicFunction;
		}
		else if( pActiveFunction==&TopographicFunction )
		{
			cout << "Now displaying analytic function." << endl;
			pActiveFunction = &AnalyticFunction;
		}
		cout << "Re-building tree, level " << nSub << " ... ";
		QuadTree.BuildTree(*pActiveFunction, nSub);
		cout << "done." << endl;
		cout << "---" << endl;
		break;
	case ' ':
		nForwardBackward = 0;
		/* swap between base mesh */
		if( pActiveBaseMesh==&BaseOctahedron )
		{
			cout << "Now using butterfly subdivided mesh as base mesh." << endl;
			pActiveBaseMesh = &BaseButterFly;
		}
		else if( pActiveBaseMesh==&BaseButterFly )
		{
			cout << "Now using square subdivided patch as base mesh." << endl;
			pActiveBaseMesh = &BaseSquare;
		}
		else if( pActiveBaseMesh==&BaseSquare )
		{
			cout << "Now using subdivided tetrahedron as base mesh." << endl;
			pActiveBaseMesh = &BaseTetrahedron;
		}
		else if( pActiveBaseMesh==&BaseTetrahedron )
		{
			cout << "Now using subdivided octahedron as base mesh." << endl;
			pActiveBaseMesh = &BaseOctahedron;
		}
		QuadTree.SetBaseMesh( *pActiveBaseMesh );
		/* rebuild the tree */
		cout << "Re-building tree, level " << nSub << " ... ";
		QuadTree.BuildTree(*pActiveFunction, nSub);
		cout << "done." << endl;
		cout << "---" << endl;
		break;
	case 't':
		nForwardBackward = 0;
		/* swap between base mesh */
		if( pActiveTransform==&LinearTransform )
		{
			cout << "Now using butterfly wavelet transform." << endl;
			pActiveTransform = &ButterflyTransform;
		}
		else if( pActiveTransform==&ButterflyTransform )
		{
			cout << "Now using linear wavelet transform." << endl;
			pActiveTransform = &LinearTransform;
		}
		/* rebuild the tree */
		cout << "Re-building tree, level " << nSub << " ... ";
		QuadTree.BuildTree(*pActiveFunction, nSub);
		cout << "done." << endl;
		cout << "---" << endl;
		break;
	case 'p':
		cout << "Changing analytic function." << endl;
		AnalyticFunction.ToogleFunction();
		pActiveFunction = &AnalyticFunction;
		cout << "Now using function : f(rU,rV)=" << AnalyticFunction.GetFunctionExpression() << " (rU,rV) in [0,1]x[0,1]" << endl;
		cout << "Re-building tree, level " << nSub << " ... ";
		QuadTree.BuildTree(*pActiveFunction, nSub);
		cout << "done." << endl;
		cout << "---" << endl;
		break;
	case 'w':
		if( !bWireFrame )
		{
			cout << "Wireframe mode on." << endl;
			cout << "---" << endl;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth( nLineWidth );
		}
		else
		{
			cout << "Filled mode on." << endl;
			cout << "---" << endl;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		bWireFrame = !bWireFrame;
		break;
	case 'b':
		BaseButterFly.SetTension( BaseButterFly.GetTension()-0.01f );
		cout << "New tension for the butterfly scheme : " << BaseButterFly.GetTension() << endl;
		pActiveBaseMesh = &BaseButterFly;
		QuadTree.SetBaseMesh( *pActiveBaseMesh );
		cout << "Re-building tree, level " << nSub << " ... ";
		QuadTree.BuildTree(*pActiveFunction, nSub);
		cout << "done." << endl;
		cout << "---" << endl;
		break;
	case 'B':
		BaseButterFly.SetTension( BaseButterFly.GetTension()+0.01f );
		cout << "New tension for the butterfly scheme : " << BaseButterFly.GetTension() << endl;
		pActiveBaseMesh = &BaseButterFly;
		QuadTree.SetBaseMesh( *pActiveBaseMesh );
		cout << "Re-building tree, level " << nSub << " ... ";
		QuadTree.BuildTree(*pActiveFunction, nSub);
		cout << "done." << endl;
		cout << "---" << endl;
		break;
	default:
		cout << "FSW is SO COOL !" << endl;
		cout << "---" << endl;
	}
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
int main( int argc, char *argv[] )
{	

	/* just a hack to check memory leak under win32 */
#ifdef GW_DEBUG	
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); // Get current flag
	flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	_CrtSetDbgFlag(flag); // Set flag to the new value
#endif

	GW_InputOutput::Init(argc, argv, WINDOW_SIZE, "GW -- Test of Spherical Wavelets");

//	GW_BitStream::TestClass();
//	GW_ZeroTreeCompressor::TestClass();


	cout << endl << "    .. FSW -- demo -- graphical display of transformations and compression .." << endl << endl;
	cout << "By Gabriel Peyre -- peyre@cmapx.polytechnique.fr" << endl;

	cout << "---" << endl;
	cout << "Use 'Left Click + Mouse' to spin the sphere." << endl;
	cout << "Use 'Right Click' to pop-up menu." << endl;
	cout << "Use 'Right+Left Click + mouse up/down' to zoom in/out." << endl;
	cout << "Here is a list of the key you can use : " << endl;
	cout << "    '+/-' : increase/decrease precision of the sphere." << endl;
	cout << "    'l/L' : forward/backward spherical-wavelet transform." << endl;
	cout << "    'a' : display of a spherical wavelet." << endl;
	cout << "    'c' : compress the data in a file." << endl;
	cout << "    'C' : decompress the data from a file." << endl;
	cout << "    'TAB' : toggle between functions." << endl;
	cout << "    'SPACE' : toggle between base mesh." << endl;
	cout << "    't' : toggle between wavelet transforms." << endl;
	cout << "    'p' : toggle between analytic functions." << endl;
	cout << "    'w' : toggle wireframe/filled mode." << endl;
	cout << "    'b/B' : decrease/increase tension for the butterfly base mesh." << endl;
	cout << "---" << endl;
	fflush(stdout);

	/* load a bunch of stuff */
	init();
	init_gl();

	/* set up callback functions */
	glutKeyboardFunc( keyboard );
	glutDisplayFunc( display );
	
	/* run an infinite loop */
	glutMainLoop();
	
	return 0;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////