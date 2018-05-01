//-------------------------------------------------------------------------
/** \name FSW file inclusion */
//-------------------------------------------------------------------------
//@{
#include "trackball.h"
#include "../../fsw_core/FSW_Config.h"
#include "../../fsw_core/FSW_LinearWavelet.h"
#include "../../fsw_core/FSW_ButterflyWavelet.h"
#include "../../fsw_core/FSW_BaseButterfly.h"
#include "../../fsw_core/FSW_BaseSquare.h"
#include "../../fsw_core/FSW_BaseOctahedron.h"
#include "../../fsw_core/FSW_BaseTetrahedron.h"
#include "../../fsw_toolkit/FSW_TopographicFunction.h"
#include "../../fsw_toolkit/FSW_DeltaFunction.h"
#include "../../fsw_compression/FSW_BitStream.h"
#include "../../fsw_compression/FSW_ZeroTreeCompressor.h"
#include <GL/glut.h>
using namespace FSW;
//@}

//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef FSW_DEBUG
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "fsw_core_dbg.lib")
	#pragma comment(lib, "fsw_toolkit_dbg.lib")
	#pragma comment(lib, "fsw_compression_dbg.lib")
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "fsw_core.lib")
	#pragma comment(lib, "fsw_toolkit.lib")
	#pragma comment(lib, "fsw_compression.lib")
#endif // FSW_DEBUG
//@}

//-------------------------------------------------------------------------
/** @name 3D engine */
//-------------------------------------------------------------------------
//@{
/** base object */
FSW_BaseOctahedron	BaseOctahedron;
FSW_BaseTetrahedron	BaseTetrahedron;
FSW_BaseButterfly	BaseButterFly( BaseOctahedron );
FSW_BaseSquare		BaseSquare;
FSW_BaseMesh_ABC* pActiveBaseMesh = &BaseOctahedron;
/** the main quadtree */
FSW_QuadTree QuadTree( *pActiveBaseMesh );
/** the Wavelet transform */
FSW_ButterflyWavelet ButterflyTransform;
FSW_LinearWavelet LinearTransform;
FSW_WaveletTransform_ABC* pActiveTransform = &LinearTransform;
/** the compressor we used for output */
FSW_ZeroTreeCompressor Compressor;
/** Add one each time a forward is done, and remove one when a backward is done */
FSW_I32 nForwardBackward = 0;
/** Functions*/
FSW_TopographicFunction TopographicFunction;
FSW_TopographicFunction EarthFunction;
FSW_TopographicFunction ImageFunction;
FSW_U32 DeltaLevel = 2;
FSW_DeltaFunction DeltaFunc(DeltaLevel,3,0,4.0f);
FSW_TreeFunction_ABC* pActiveFunction = NULL;
//@}

/** for the interface */
FSW_Bool bSpinning = FSW_False, bMoving = FSW_False;
FSW_I32 nBeginX, nBeginY;
FSW_I32 rWidth = 300, rHeight = 300;
GLdouble rAspectRatio;
float curquat[4];
float lastquat[4];
Vector eyePos = { 0.0, 0.0, 3.0 };
FSW_Float rZoom = 2;
FSW_Bool bZooming = FSW_False;
FSW_I32 nMouseY = 0;

GLfloat nLineWidth = 4;
#define BACKGROUND_COLOR 1
#define SPOT_LIGHT_INTENSITY 0.2
#define AMBIENT_LIGHT_INTENSITY 0.5

#define ETOPO_FILE_NAME	"../data/ETOPO15"
#define ETOPO_RESOLUTION 15
#define EARTH_FILE_NAME "../data/earth_nb.jpg"
#define IMAGE_FILE_NAME "../data/lena.gif"
#define COMPRESSED_FILE_NAME "compressed"
#define COMPRESSED_FILE_EXTENSION "fsw"
#ifdef FSW_DEBUG
	#define START_PRECISION 3
#else
	#define START_PRECISION 5
#endif

class FSW_AnalyticFunction: public FSW_TreeFunction_ABC
{
public:
	#define NBR_FUNCTIONS 4
	FSW_AnalyticFunction():FSW_TreeFunction_ABC(), nFuncNum_(0) {}
	FSW_Float GetValue(FSW_Float rU, FSW_Float rV) const
	{ 
		if( nFuncNum_==0 )
			return 0.1f*cos( 5*rU*FSW_TWOPI );
		else if( nFuncNum_==1 )
			return 0;
		else if( nFuncNum_==2 )
			return 0.1f*cos( 5*rV*FSW_TWOPI );
		else
			return 0.1*cos( 5*FSW_TWOPI*sqrt( rU*rU + rV*rV ) );
	}
	const char* GetFunctionExpression()
	{
		if( nFuncNum_==0 )
			return "0.1f*cos( 5*rU*FSW_TWOPI )";
		else if( nFuncNum_==1 )
			return "0";
		else if( nFuncNum_==2 )
			return "0.1f*cos( 5*rV*FSW_TWOPI )";
		else
			return "0.1*cos( sqrt( rU*rU + rV*rV ) )";
	}
	void ToogleFunction()
	{
		nFuncNum_ = (nFuncNum_+1)%NBR_FUNCTIONS;
	}
private:
	FSW_U32 nFuncNum_;
};
FSW_AnalyticFunction AnalyticFunction;

/*------------------------------------------------------------------------------*/
// Name : VertexDisplayer
/**
 *  \param  vert [FSW_QuadTreeVertex&] The vertex to display.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Callback function for FSW/Orion3D wrapper.
 *	Display a vertex according to the etopo data range
 */
/*------------------------------------------------------------------------------*/
__forceinline
void VertexDisplayer( FSW_QuadTreeVertex& vert )
{
	GLfloat aColor[4] = {0.8,0.8,0.8,1};
	GLfloat aSpecular[4] = {0.3f,0.3f,0.3f,1};

	FSW_Vector3D Pos;
	FSW_Vector3D Normal;
	/* compute position and normal according to the geometry */
	if( pActiveBaseMesh==&BaseSquare && pActiveFunction!=&DeltaFunc )	// planar
	{
		Pos = vert.GetPosition();
		Pos[2] += vert.GetValue();
		pActiveFunction->ComputePlanarNormal(Normal, 0.5*(Pos[0]+1), 0.5f*(Pos[1]+1));
	}
	else if( pActiveFunction==&DeltaFunc )
	{
		FSW_Float rLong, rLat;
		FSW_Maths::ConvertCartesianToSpherical(vert.GetPosition(), rLong, rLat);	
		if( pActiveBaseMesh==&BaseSquare )
		{
			Pos = vert.GetPosition();
			Pos[2] += 0.2*vert.GetValue();
			Normal = FSW_Vector3D(0,0,0);
		}
		else
		{
			Pos = vert.GetPosition()*( 1 + 0.1*vert.GetValue() );
			if( nForwardBackward==0 )
				pActiveFunction->ComputeSphericalNormal(Normal, rLong, rLat);
			else
				Normal = FSW_Vector3D(0,0,1);
		}
	}
	else								// spherical
	{		
		FSW_Float rLong, rLat;
		FSW_Maths::ConvertCartesianToSpherical(vert.GetPosition(), rLong, rLat);	
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

	const FSW_Float* aCoord = Normal.GetCoord();
	glNormal3f( aCoord[0], aCoord[1], aCoord[2] );
	aCoord = Pos.GetCoord();
	glVertex3f( aCoord[0], aCoord[1], aCoord[2] );
}

#define MAX_DEPTH 7
FSW_Float rTarget_U = 0.5f;
FSW_Float rTarget_V = 0.5f;


FSW_Bool CompressionCallback( const FSW_BitStream& BitStream, FSW_QuadTree& QuadTree, FSW_U8 nBitPlane )
{
	cout << ((FSW_U32) nBitPlane) << " ";
	return true;
}


FSW_U32 nBitToUncompress = 5000;
/*------------------------------------------------------------------------------*/
// Name : UnCompressionCallback
/**
 *  \param  BitStream [FSW_BitStream&] the stream of bit compressed.
 *  \param  QuadTree [FSW_QuadTree&] he quadtree being compressed.
 *  \return [FSW_Bool] Do we need to continue compression ?
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  This is the callback used during compression.
 */
/*------------------------------------------------------------------------------*/
FSW_Bool UnCompressionCallback_PerBit( const FSW_BitStream& BitStream, FSW_QuadTree& QuadTree, FSW_U8 nBitPlane )
{
	if( BitStream.GetNbrBits()>=nBitToUncompress )
		return FSW_False;
	else
		return FSW_True;
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
	FSW_RETURN_CODE bRes;
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

	/* init the fast sqrt table */
	makeInverseSqrtLookupTable();
	/* init the track ball */
	trackball(curquat, -0.5, 0.0, 0.0, 0.0);
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
void display_rec( FSW_QuadTreeNode& CurNode, FSW_Bool bClockWise )
{
	if( CurNode.GetChildNode(0)!=NULL )
	{
		/* we are not on a leaf, so we should  recurse */
		for( FSW_U32 i=0; i<4; ++i )
		{
			FSW_ASSERT( CurNode.GetChildNode(i)!=NULL );
			if( i!=0 )
				display_rec( *CurNode.GetChildNode(i), !bClockWise );
			else
				display_rec( *CurNode.GetChildNode(i), bClockWise );
		}
	}
	else
	{
		/* we are on a leaf or we were told to stop recursing, so draw */
		FSW_QuadTreeVertex* pVert1 = CurNode.GetVertex( QT_Vert1 );FSW_ASSERT( pVert1!=NULL );
		FSW_QuadTreeVertex* pVert2 = CurNode.GetVertex( QT_Vert2 );FSW_ASSERT( pVert2!=NULL );
		FSW_QuadTreeVertex* pVert3 = CurNode.GetVertex( QT_Vert3 );FSW_ASSERT( pVert3!=NULL );
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
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	GLfloat m[4][4];
	GLfloat invm[4][4];
//	Vector objectSpaceLightPosition;
	Vector objectSpaceEyePosition;

	/* Given the current rotation quaternion, generate the matching rotation
		matrix and combine it with the modelview matrix. */
	build_rotmatrix(m, curquat);

	/* Because we know that "m" is a rotation matrix, we could just
		perform a tranpose here, but for an arbitrary matrix, we 
		need a full matrix inversion. */
	invertMatrixf(&invm[0][0], &m[0][0]);

	/* Transform the light position in world space into object space
		using the inverse of the object space to world space transform. */
	transformPosition(&objectSpaceEyePosition, &eyePos, invm);

	GLdouble eyeLookAt[16];
	/* Compute a "look at" 4x4 matrix with the "eye" at the eye position. */
	buildLookAtMatrix(eyePos.x, eyePos.y, eyePos.z,  0,0,0,  0,1,0,  eyeLookAt);
	glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(eyeLookAt);
		/* Load a persepctive projection normally. */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective( /* field of view in degree */ 40.0,
			/* aspect ratio */ rAspectRatio,
			/* Z near */ 1.0, /* Z far */ 500.0f);
	glMatrixMode(GL_MODELVIEW);

	/* posit light */
	glTranslatef(0,0,-rZoom);
	glMultMatrixf(&m[0][0]);
	GLfloat light_position[4] = { 8,8,0,1 };
	glLightfv( GL_LIGHT0 , GL_POSITION, light_position ) ;

	/* draw sphere */
	glPushMatrix();

	/* render each face of the octogone */
	T_QuadTreeNodeVector BaseNodeVector = QuadTree.GetBaseNodeVector();
	FSW_U32 i = 0;
	for( IT_QuadTreeNodeVector it=BaseNodeVector.begin(); it!=BaseNodeVector.end(); ++it )
	{
		FSW_QuadTreeNode* pNode = *it;
		FSW_ASSERT( pNode!=NULL );
		glBegin( GL_TRIANGLES );
		FSW_Bool bClockWise;
		if( BaseNodeVector.size()==8 || BaseNodeVector.size()==2 )	// special case for octahedron
		{
			if( i<4 )
				bClockWise = (i%2)==0;
			else
				bClockWise = (i%2)==1;
		}
		else
			bClockWise = FSW_True;
		display_rec( *pNode, bClockWise );
		glEnd();
		i++;
	}
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

FSW_U32 nSub = START_PRECISION;
FSW_Bool bCompressionMade = FSW_False;
FSW_U32 nNbrBitTotal;
FSW_Bool bWireFrame = FSW_False;
/*------------------------------------------------------------------------------*/
// Name : keyboard
/**
 *  \param  button [FSW::FSW_U32] key pressed.
 *  \param  x [FSW::FSW_I32] x position of the mouse.
 *  \param  y [FSW::FSW_I32] y position of the mouse.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  To handle the keyboard.
 */
/*------------------------------------------------------------------------------*/
void keyboard(unsigned char button, int x, int y)
{
	FSW_Float rNorm = 0;
	FSW_BitStream BitStream;
	FILE* pFile = NULL;
	char FileName[200];
	FSW_U32 nNbrBitPlane = 28;
	FSW_Float rNbrBitPerVertex;
	FSW_Float rNbrBitPerVertexForPerfect;
	FSW_CompressionHeader CompressionHeader;

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
		rNorm = FSW_Maths::ComputeIntegral( QuadTree );
		cout << "empty tree build ... ";
		DeltaFunc.PostBuildTree( QuadTree );
		rNorm = FSW_Maths::ComputeIntegral( QuadTree );
		cout << "post build done ... ";
		QuadTree.BackwardTransform( *pActiveTransform, DeltaLevel );
		rNorm = FSW_Maths::ComputeIntegral( QuadTree );
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
		cout << " L1=" << FSW_Maths::ComputeL1Distance( QuadTree, *pActiveFunction );
		cout << " L2=" << FSW_Maths::ComputeL2Distance( QuadTree, *pActiveFunction ) << endl;
		cout << "Performing forward transform ... ";
		QuadTree.ForwardTransform( *pActiveTransform, 0 );
		cout << "done." << endl;
		sprintf( FileName, "%s_%d.%s", COMPRESSED_FILE_NAME, nNbrBitPlane, COMPRESSED_FILE_EXTENSION);
		cout << "Begining compression of the data in file " << FileName << " (" << nNbrBitPlane << " bit planes)." << endl;
		pFile = fopen( FileName, "wb" );	
		FSW_ASSERT( pFile!=NULL );
		BitStream.Reset( pFile, FSW_BitStream::kWriteMode );

		Compressor.Compress( BitStream, QuadTree, nNbrBitPlane, FSW_ZeroTreeCompressor::kNormL2 );
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
		cout << " L1=" << FSW_Maths::ComputeL1Distance( QuadTree, *pActiveFunction );
		cout << " L2=" << FSW_Maths::ComputeL2Distance( QuadTree, *pActiveFunction ) << endl;
		cout << "---" << endl;
		bCompressionMade = FSW_True;
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
		cin >> rNbrBitPerVertex;
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
		FSW_ASSERT( pFile!=NULL );
		BitStream.Reset( pFile, FSW_BitStream::kReadMode );
		Compressor.UnCompress( BitStream, QuadTree );
		cout << endl;
		BitStream.Flush();	// The most important : don't forget to flush the rest of the stream before closing the file !
		fclose(pFile);
		cout << "Uncompression finished." << endl;
		cout << "Performing backward transform ... ";
		QuadTree.BackwardTransform( *pActiveTransform, 0 );
		cout << "done." << endl;
		cout << "Error after uncompression :";
		cout << " L1=" << FSW_Maths::ComputeL1Distance( QuadTree, *pActiveFunction );
		cout << " L2=" << FSW_Maths::ComputeL2Distance( QuadTree, *pActiveFunction ) << endl;
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
// Name : idle
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  when nothing occurs
 */
/*------------------------------------------------------------------------------*/
void idle()
{
	if( bSpinning )
	{
		add_quats(lastquat, curquat, curquat);
	}
	glutPostRedisplay();
}

void reshape( int w, int h )
{
	glViewport( 0, 0, w, h  );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(30,w/h,1.5,500);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	rWidth = w;
	rHeight = h;
	rAspectRatio = (GLdouble) rWidth/(GLdouble) rHeight;
}

/*------------------------------------------------------------------------------*/
// Name : mouse
/**
 *  \param  x [FSW::FSW_I32] x position of the pointer.
 *  \param  y [FSW::FSW_I32] y position of the pointer.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  To handle mouse movements.
 */
/*------------------------------------------------------------------------------*/
void mouse_motion(int x, int y)
{
	if( bMoving ) 
	{
		trackball(lastquat,
			(2.0 * nBeginX - rWidth) / rWidth,
			(rHeight - 2.0 * nBeginY) / rHeight,
			(2.0 * x - rWidth) / rWidth,
			(rHeight - 2.0 * y) / rHeight
		);
		nBeginX = x;
		nBeginY = y;
		bSpinning = 1;
		glutIdleFunc(idle);
	}
	else if( bZooming )
	{
		rZoom += 0.001f*( y-nMouseY );
		if( rZoom<=0 )
			rZoom=0;
		if( rZoom>=10 )
			rZoom=10;
	}
}

void mouse_click( int button , int state , int x , int y )
{
	nMouseY = y;
	if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN ) 
	{
		bSpinning = 0;
		trackball(lastquat, 0, 0, 0, 0);
		glutIdleFunc(NULL);
		bMoving = 1;
		nBeginX = x;
		nBeginY = y;
	} 
	else if( button == GLUT_RIGHT_BUTTON && state == GLUT_UP ) 
	{
		bMoving = 0;
	} 
	else if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) 
	{
		bZooming = FSW_True;
	}
	else if( button == GLUT_LEFT_BUTTON && state == GLUT_UP ) 
	{
		bZooming = FSW_False;
	}
}

void mouse_passive( int x , int y )
{
	nMouseY = y;
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
#ifdef FSW_DEBUG
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); // Get current flag
	flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	_CrtSetDbgFlag(flag); // Set flag to the new value
#endif
	glutInit( &argc , argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize( 512, 512 ) ;
	glutInitWindowPosition( 100, 100 ) ;
	glutCreateWindow( ".. FSW ..." );

	FSW_BitStream::TestClass();
	FSW_ZeroTreeCompressor::TestClass();


	cout << endl << "    .. FSW -- demo -- graphical display of transformations and compression .." << endl << endl;
	cout << "By Gabriel Peyre -- gpeyre@altern.org" << endl;
	cout << "FSW homepage : http://nikopol0.alrj.org/fsw/" << endl << endl << endl;

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
	glutMotionFunc( mouse_motion );
	glutMouseFunc( mouse_click );
	glutKeyboardFunc( keyboard );
	glutIdleFunc( idle );
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );

	
	/* run an infinite loop */
	glutMainLoop();
	
	return 0;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////