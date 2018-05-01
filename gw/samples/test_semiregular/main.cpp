//-------------------------------------------------------------------------
/** \name GW file inclusion */
//-------------------------------------------------------------------------
//@{
#include "stdafx.h"
#include <GL/glut.h>
#include "../../gw_toolkit/GW_Toolkit.h"
#include "../../gw_multiresolution/GW_BaseMultiresolution.h"
#include "../../gw_multiresolution/GW_LinearWavelet.h"
#include "../../gw_multiresolution/GW_ButterflyWavelet.h"
#include "../../gw_multiresolution_toolkit/GW_TopographicFunction.h"
#include "../../gw_multiresolution_toolkit/GW_DeltaFunction.h"
#include "../../gw_toolkit/GW_InputOutput.h"

#undef exit
using namespace GW;
//@}

//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef GW_DEBUG
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "gw_core_dbg.lib")
	#pragma comment(lib, "gw_toolkit_dbg.lib")
	#pragma comment(lib, "gw_geodesic_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_dbg.lib")
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_toolkit.lib")
	#pragma comment(lib, "gw_geodesic.lib")
	#pragma comment(lib, "gw_multiresolution.lib")
#endif // GW_DEBUG
//@}

/* for the parameterization construction ******************************************/
GW_Toolkit Toolkit;
GW_Bool bDisplayMesh = GW_True;
GW_Bool bDisplayVoronoiMesh = GW_False;
GW_Bool bDisplayMultires = GW_True;

/* for the semi-regular mesh building **********************************************/
GW_BaseMultiresolution BaseMultiresolution( Toolkit.GetGeodesicMesh(), Toolkit.GetVoronoiMesh() );
GW_QuadTree* pQuadTree = NULL;
/** the Wavelet transform */
GW_ButterflyWavelet ButterflyTransform;
GW_LinearWavelet LinearTransform;
GW_WaveletTransform_ABC* pActiveTransform = &LinearTransform;
/** Add one each time a forward is done, and remove one when a backward is done */
GW_I32 nForwardBackward = 0;
/** Functions*/
GW_TopographicFunction ImageFunction;
#define IMAGE_FILE_NAME "../ressources/images/lena.gif"
GW_U32 DeltaLevel = 2;
GW_DeltaFunction DeltaFunc(DeltaLevel,3,0,4.0f);
GW_TreeFunction_ABC* pActiveFunction = &ImageFunction;
#ifdef GW_DEBUG
	#define START_PRECISION 3
#else
	#define START_PRECISION 3
#endif
GW_U32 nSub = START_PRECISION;

/** wire frame/filled mode */
GW_Bool bWireFrameModeOn = GW_False;
GW_Bool bFilledModeOn = GW_True;
#define WIREFRAME_COLOR 0
#define BACKGROUND_COLOR 1
#define WINDOW_SIZE 600
GLfloat nLineWidth = 1;

/** interpolation data */
GW_Float rXInterp = 0.33;
GW_Float rYInterp = 0.33;
GW_Float rXInterpStep = 0.005;
GW_Float rYInterpStep = 0.005;
GW_Vector3D InterpPos;

GW_Float rCurvatureWeight = 0;

#ifdef GW_DEBUG
	#define FILE_LIST "files_debug.txt"
#else
	#define FILE_LIST "files.txt"
#endif
T_StringList FileList;
IT_StringList SelectedFile = FileList.end();

void load_file()
{
	if( SelectedFile!=FileList.end() )
	{
		if( Toolkit.LoadFile( (*SelectedFile).c_str() )<0 )
			exit(-1);
	}
	Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
	Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kStoppingVertex );
}

GW_Float CurvatureWeightCallback(GW_GeodesicVertex& Vert)
{
	GW_Float rTotalCurv = Vert.GetMaxCurv()*Vert.GetMaxCurv() + Vert.GetMinCurv()*Vert.GetMinCurv();
	GW_CLAMP( rTotalCurv, 0, 10 );
	return 0.5+rTotalCurv*rCurvatureWeight;
	return 1;
}

GW_Float BasicWeightCallback(GW_GeodesicVertex& Vert)
{
	return 1;
}

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
__forceinline
void VertexDisplayer( GW_QuadTreeVertex& vert )
{
	GLfloat aColor[4] = {0.8,0.8,0.8,1};
	GLfloat aSpecular[4] = {0.3f,0.3f,0.3f,1};

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat*) aSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat*) aColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat*) aColor);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

	glNormal( vert.GetPosition() );
	glVertex( GW_Vector3D(0,0,1) );		// for the moment normal are not available ...
}

/*------------------------------------------------------------------------------*/
/** 
* Name : init
*
*  \author Gabriel Peyré 2001-10-17
*
*	Init various stuff.
*/ 
/*------------------------------------------------------------------------------*/
void init()
{	
	/* loading data from an image **************************************/
	cout << "Loading image file " << IMAGE_FILE_NAME << " ..." << endl;
	GW_RETURN_CODE bRes = ImageFunction.LoadFromImage(IMAGE_FILE_NAME);
	if( bRes<0 )
	{
		cout << "Loading failed." << endl;
		::exit(1);
	}
	cout << "Loading successful." << endl;
	cout << "----" << endl;
	ImageFunction.ScaleTo( 0,0.1f );

	if( GW_Toolkit::LoadFileList( FILE_LIST, FileList )<0 )
	{
		cerr << "Can't open files listing " << FILE_LIST << "." << endl;
		exit(-1);
	}
	SelectedFile = FileList.begin();
	/* load the current file */
	load_file();

	/* redirect GW messages */
	GW_OutputStream = stdout;
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

void draw_scene()
{
	if( bDisplayMesh )
	{
		/* render path */
		Toolkit.GetGeodesicDisplayer().DisplayPath( Toolkit.GetGeodesicPath(), GW_Vector3D(1,1,1) );
		/* display the list of vertex */
		Toolkit.GetGeodesicDisplayer().DisplayVoronoiPoints( Toolkit.GetVoronoiMesh(), GW_Vector3D(0,0,0)  );
		Toolkit.GetGeodesicDisplayer().DisplayGeodesicBoundaries( Toolkit.GetVoronoiMesh() );
		/* render mesh */
		Toolkit.GetGeodesicDisplayer().DisplayMesh( Toolkit.GetGeodesicMesh() );
	}
	if( bDisplayVoronoiMesh )
	{
		glDisable( GL_CULL_FACE );
		Toolkit.GetCoarseDisplayer().DisplayMesh( Toolkit.GetVoronoiMesh() );
		glEnable( GL_CULL_FACE );
	}
}

void draw_multires()
{
	if( pQuadTree!=NULL && bDisplayMultires )
	{
		glDisable( GL_CULL_FACE );
		glDisable(GL_LIGHTING);
		/* render each face of the octogone */
		T_QuadTreeNodeVector BaseNodeVector = pQuadTree->GetBaseNodeVector();
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
		glEnable( GL_CULL_FACE );
		glEnable(GL_LIGHTING);
	}
}

void display_startpoint( GW_Vertex* pVert, GW_Float r, GW_Float v, GW_Float b )
{
	if( pVert!=NULL )
	{
		glPointSize( 6 );
		glColor3f( r,v,b );
		glDisable( GL_LIGHTING );
		glBegin( GL_POINTS );
			glVertex( *pVert );
		glEnd();
		glEnable( GL_LIGHTING );
	}
}

void display()
{
	GW_InputOutput::PrepareDisplay();

	glPushMatrix();

	if( bWireFrameModeOn )
	{
		Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		Toolkit.GetCoarseDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		glDisable( GL_LIGHTING );
		glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth( nLineWidth );
		draw_scene();
		draw_multires();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_LIGHTING );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
		Toolkit.GetCoarseDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
	}
	if( bFilledModeOn )
	{
		draw_scene();
		glColor3f(0.7,0.7,0.7);
		draw_multires();
	}

	/* draw a dot at position of the interpolation */
	glDisable( GL_LIGHTING );
	glLineWidth( 8.0 );
	glColor3f( 1,1,0 );
	glBegin( GL_POINTS );
	glVertex( InterpPos );
	glEnd();
	glEnable( GL_LIGHTING );

	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

/*------------------------------------------------------------------------------*/
// Name : keyboard
/**
*  \param  button [GW::GW_U32] key pressed.
*  \param  x [GW::GW_I32] x position of the mouse.
*  \param  y [GW::GW_I32] y position of the mouse.
*  \author Gabriel Peyré
*  \date   11-24-2002
* 
*  To handle the keyboard.
*/
/*------------------------------------------------------------------------------*/
void keyboard(unsigned char button, int x, int y)
{

	switch((char) button)
	{
	case 27:
		::exit(0);
		break;
	case 'w':
		bWireFrameModeOn = !bWireFrameModeOn;
		if( bWireFrameModeOn )
			cout << "Wireframe mode ON." << endl;
		else
			cout << "Wireframe mode OFF." << endl;
		break;
	case 'x':
		bFilledModeOn = !bFilledModeOn;
		if( bFilledModeOn )
			cout << "Filled mode ON." << endl;
		else
			cout << "Filled mode OFF." << endl;
		break;
	case '+':
		cout << "Increasing constrast." << endl;
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kGeodesicDistance) )
			Toolkit.GetGeodesicDisplayer().IncreaseContrast( GW_BasicDisplayer::kGeodesicDistance );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case '-':
		cout << "Decreasing constrast." << endl;
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kGeodesicDistance) )
			Toolkit.GetGeodesicDisplayer().DecreaseContrast( GW_BasicDisplayer::kGeodesicDistance );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case 'r':
		Toolkit.GetGeodesicMesh().ResetGeodesicMesh();
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case '\t':
		if( SelectedFile != FileList.end() )
			SelectedFile++;
		if( SelectedFile == FileList.end() )
			SelectedFile = FileList.begin();
		load_file();
		break;
	case '\n':case '\r':
		glutFullScreen();
		break;
	case 'm':
		bDisplayMesh = !bDisplayMesh;
		if( bDisplayMesh )
			cout << "Displaying original mesh" << endl;
		else
			cout << "Not displaying original mesh" << endl;
		break;
	case 'M':
//		bDisplayVoronoiMesh = !bDisplayVoronoiMesh;
		bDisplayMultires = !bDisplayMultires;
		if( bDisplayMultires )
			cout << "Displaying semiregular mesh" << endl;
		else
			cout << "Not displaying semiregular mesh" << endl;
		break;
	case 'l':	
		if( pQuadTree!=NULL )
		{
			nForwardBackward++;
			cout << "Performing forward transform ... ";
			pQuadTree->ForwardTransform( *pActiveTransform, 0 );
			cout << "done." << endl;
			cout << "---" << endl;
		}
		break;
	case 'L':
		if( pQuadTree!=NULL )
		{
			nForwardBackward--;
			cout << "Performing backward transform ... ";
			pQuadTree->BackwardTransform( *pActiveTransform, 0 );
			cout << "done." << endl;
			cout << "---" << endl;
		}
		break;
	case 'P':
		if( pQuadTree!=NULL )
		{
			nForwardBackward = 0;
			nSub++;
			cout << "Building tree, level " << nSub << " ... ";
			pQuadTree->BuildTree(*pActiveFunction, nSub);
			cout << "done." << endl;
			cout << "---" << endl;
			if( pActiveFunction==&DeltaFunc )
			{
				DeltaFunc.PostBuildTree( *pQuadTree );
				pQuadTree->BackwardTransform( *pActiveTransform, DeltaLevel );
			}
		}
		break;
	case 'p':
		if( pQuadTree!=NULL )
		{
			nForwardBackward = 0;
			if( nSub!=0 )
				nSub--;
			cout << "Building tree, level " << nSub << " ... ";
			pQuadTree->BuildTree(*pActiveFunction, nSub);
			cout << "done." << endl;
			cout << "---" << endl;
			if( pActiveFunction==&DeltaFunc )
			{
				DeltaFunc.PostBuildTree( *pQuadTree );
				pQuadTree->BackwardTransform( *pActiveTransform, DeltaLevel );
			}
		}
		break;
	case 'a':
		if( pQuadTree!=NULL )
		{
			nForwardBackward = 0;
			pActiveFunction = &DeltaFunc;
			cout << "Building Wavelet, level " << nSub << " ... ";
			pQuadTree->BuildTree(DeltaFunc , nSub );
			GW_Float rNorm = GW_SphericalMaths::ComputeIntegral( *pQuadTree );
			cout << "empty tree build ... ";
			DeltaFunc.PostBuildTree( *pQuadTree );
			rNorm = GW_SphericalMaths::ComputeIntegral( *pQuadTree );
			cout << "post build done ... ";
			pQuadTree->BackwardTransform( *pActiveTransform, DeltaLevel );
			rNorm = GW_SphericalMaths::ComputeIntegral( *pQuadTree );
			cout << "backward transform done." << endl;
			cout << "---" << endl;
		}
		break;


	default:
		cout << "GW is SO COOL !" << endl;
	}
}

void PerformInterpolation()
{
	GW_Face* pFace = Toolkit.GetVoronoiMesh().GetFace( 0 );
	GW_VoronoiVertex* pV0 = (GW_VoronoiVertex*) pFace->GetVertex(0);
	GW_VoronoiVertex* pV1 = (GW_VoronoiVertex*) pFace->GetVertex(1);
	GW_VoronoiVertex* pV2 = (GW_VoronoiVertex*) pFace->GetVertex(2);
//	Toolkit.GetVoronoiMesh().InterpolatePositionExhaustiveSearch( Toolkit.GetGeodesicMesh(), InterpPos, *pV0, *pV1, *pV2, rXInterp, rYInterp, 1-rXInterp-rYInterp );
	Toolkit.GetVoronoiMesh().InterpolatePosition( Toolkit.GetGeodesicMesh(), InterpPos, *pV0, *pV1, *pV2, rXInterp, rYInterp, 1-rXInterp-rYInterp );
}

GW_U32 nNumLocalFrontSeleted = 0;
/*------------------------------------------------------------------------------*/
// Name : keyboard_spec
/**
*  \param  button [GW::GW_U32] key pressed.
*  \param  x [GW::GW_I32] x position of the mouse.
*  \param  y [GW::GW_I32] y position of the mouse.
*  \author Gabriel Peyré
*  \date   11-24-2002
* 
*  To handle the keyboard.
*/
/*------------------------------------------------------------------------------*/
void keyboard_spec(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_F1:
		Toolkit.GetGeodesicMesh().RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add one furthest point  ... " << endl;
		Toolkit.AddFurthestPoint(1);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F2:
		Toolkit.GetGeodesicMesh().RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 10 furthest point  ... " << endl;
		Toolkit.AddFurthestPoint(10);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F11:
		Toolkit.GetGeodesicMesh().RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 100 furthest point  ... " << endl;
		Toolkit.AddFurthestPoint(100);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F3:
		Toolkit.GetGeodesicMesh().RegisterWeightCallbackFunction( BasicWeightCallback );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
		cout << "Building coarse mesh ... " << endl;
		Toolkit.GetVoronoiMesh().BuildMesh( Toolkit.GetGeodesicMesh() );
		Toolkit.GetVoronoiMesh().BuildRawNormal();
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		Toolkit.GetCoarseDisplayer().BuildVertexArray( Toolkit.GetVoronoiMesh() );
		break;
	case GLUT_KEY_F4:
		Toolkit.GetGeodesicMesh().RegisterWeightCallbackFunction( BasicWeightCallback );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
		cout << "Building geodesic edges ... " << endl;
		Toolkit.GetVoronoiMesh().BuildGeodesicBoundaries( Toolkit.GetGeodesicMesh() );
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().BuildVertexArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F5:
		Toolkit.GetGeodesicMesh().RegisterWeightCallbackFunction( BasicWeightCallback );
		cout << "Computing parametrization ... " << endl;
		Toolkit.GetVoronoiMesh().BuildGeodesicParametrization( Toolkit.GetGeodesicMesh() );
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kVertexParametrization );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kStoppingVertex );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F6:
		{
			GW_VoronoiVertex* pVert = (GW_VoronoiVertex*) Toolkit.GetVoronoiMesh().GetVertex(nNumLocalFrontSeleted);
			if( pVert!=NULL )
			{
				nNumLocalFrontSeleted = (nNumLocalFrontSeleted+1)%Toolkit.GetVoronoiMesh().GetNbrVertex();
				Toolkit.GetGeodesicMesh().RegisterForceStopCallbackFunction( 
					GW_VoronoiMesh::FastMarchingCallbackFunction_Parametrization );
				GW_VoronoiMesh::pCurrentVoronoiVertex_ = pVert;

				cout << "Performing local fast marching from vertex " << nNumLocalFrontSeleted << " ... ";
				Toolkit.GetVoronoiMesh().PerformLocalFastMarching( Toolkit.GetGeodesicMesh(), *pVert );
				cout << "done." << endl;
				Toolkit.GetGeodesicDisplayer().SetUpDraw( Toolkit.GetGeodesicMesh() );
				Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kStoppingVertex );
//				Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kVertexParametrization );
				Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
			}
		}
		break;
	case GLUT_KEY_F8:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kLighting );
		cout << "Turning Lighting ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kLighting ) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		break;
	case GLUT_KEY_F10:
		pQuadTree = new GW_QuadTree( BaseMultiresolution );
		cout << "Building the tree ... " << endl;
		pActiveFunction = &ImageFunction;
		pQuadTree->BuildTree(*pActiveFunction, START_PRECISION);	
		cout << "done." << endl;
		break;
	case GLUT_KEY_LEFT:
		rXInterp -= rXInterpStep;
		if( rXInterp<0 )
			rXInterp = 0;
		PerformInterpolation();
		break;
	case GLUT_KEY_DOWN:
		rYInterp -= rYInterpStep;
		if( rYInterp<0 )
			rYInterp = 0;
		PerformInterpolation();
		break;
	case GLUT_KEY_RIGHT:
		rXInterp += rXInterpStep;
		if( rXInterp+rYInterp>1 )
		{
			rXInterp /= rXInterp+rYInterp;
			rYInterp /= rXInterp+rYInterp;
		}
		PerformInterpolation();
		break;
	case GLUT_KEY_UP:
		rYInterp += rXInterpStep;
		if( rXInterp+rYInterp>1 )
		{
			rXInterp /= rXInterp+rYInterp;
			rYInterp /= rXInterp+rYInterp;
		}
		PerformInterpolation();
		break;
	default:
		cout << "GW is SO COOL !" << endl;
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

	GW_InputOutput::Init(argc, argv, WINDOW_SIZE, "GW -- Test of semiregular mesh");

	srand( (unsigned)time( NULL ) );

	cout << endl << "    .. GW -- Test of semiregular mesh .." << endl << endl;
	cout << "---" << endl;
	cout << "Use 'Left Click + Mouse' to spin the sphere." << endl;
	cout << "Use 'Right Click' to pop-up menu." << endl;
	cout << "Use 'Right+Left Click + mouse up/down' to zoom in/out." << endl;
	cout << "---" << endl;
	cout << "F1:  Add 1 furthest point to coarse mesh." << endl;
	cout << "F2:  Add 10 furthest points to coarse mesh." << endl;
	cout << "F3:  Build coarse mesh." << endl;
	cout << "F4:  Build geodesic boundaries." << endl;
	cout << "F5:  Compute parametrization." << endl;
	cout << "F6:  Perform a local fast marching." << endl;
	cout << "F8:  Turn Lighting ON/OFF." << endl;
	cout << "---" << endl;
	cout << "w: Toggle wireframe ON/OFF." << endl;
	cout << "s/S: Add/Remove one front for marching." << endl;
	cout << "b/B: Add a level of base points for future coarse mesh." << endl;
	cout << "+/- : increase/decrease contrast of current proprieties." << endl;
	cout << "---" << endl;
	fflush(stdout);

	/* load a bunch of stuff */
	init();

	/* set up callback functions */
	glutKeyboardFunc( keyboard );
	glutSpecialFunc(keyboard_spec);
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