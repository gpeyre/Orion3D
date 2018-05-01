//-------------------------------------------------------------------------
/** \name GW file inclusion */
//-------------------------------------------------------------------------
//@{
#include "stdafx.h"
#include <GL/glut.h>
#if 0
#include <CGAL/Cartesian.h>
#include <CGAL/Triangulation_3.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
// #include <CGAL/Homogeneous.h>
// #include <CGAL/point_generators_3.h>
// #include <CGAL/copy_n.h>
// #include <CGAL/Convex_hull_traits_3.h>
// #include <CGAL/convex_hull_3.h>
// #include <CGAL/predicates_on_points_3.h>
// #include <CGAL/IO/Geomview_stream.h>
// #include <CGAL/IO/Polyhedron_geomview_ostream.h>
#endif
#include "../../gw_toolkit/GW_Toolkit.h"
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
	#pragma comment(lib, "CGAL.lib")
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_toolkit.lib")
	#pragma comment(lib, "gw_geodesic.lib")
	#pragma comment(lib, "CGAL.lib")
#endif // GW_DEBUG
//@}


GW_Toolkit Toolkit;
GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
GW_VoronoiMesh& VoronoiMesh = Toolkit.GetVoronoiMesh();
GW_Bool bDisplayMesh = GW_True;
GW_Bool bDisplayVoronoiMesh = GW_False;

/** wire frame/filled mode */
GLfloat nLineWidth = 1;
GW_Bool bWireFrameModeOn = GW_False;
GW_Bool bFilledModeOn = GW_True;
#define WIREFRAME_COLOR 0
#define BACKGROUND_COLOR 1
#define WINDOW_SIZE 600

/** interpolation data */
GW_Float rXInterp = 0.33;
GW_Float rYInterp = 0.33;
GW_Float rXInterpStep = 0.02;
GW_Float rYInterpStep = 0.02;
GW_Vector3D InterpPos;


GW_Float rCurvatureWeight = 0.0;

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
	/* redirect GW messages */
	GW_OutputStream = stdout;

	if( GW_Toolkit::LoadFileList( FILE_LIST, FileList )<0 )
	{
		cerr << "Can't open files listing " << FILE_LIST << "." << endl;
		exit(-1);
	}
	SelectedFile = FileList.begin();

	/* load the current file */
	load_file();
}

void draw_scene()
{
	if( bDisplayMesh )
	{
		/* render path */
		Toolkit.GetGeodesicDisplayer().DisplayPath( Toolkit.GetGeodesicPath(), GW_Vector3D(1,1,1) );
		/* display the list of vertex */
		Toolkit.GetGeodesicDisplayer().DisplayVoronoiPoints( VoronoiMesh, GW_Vector3D(1,1,1) );
		Toolkit.GetGeodesicDisplayer().DisplayGeodesicBoundaries( VoronoiMesh );
		/* render mesh */
		Toolkit.GetGeodesicDisplayer().DisplayMesh( Mesh );
	}
	if( bDisplayVoronoiMesh )
	{
		glDisable( GL_CULL_FACE );
		Toolkit.GetCoarseDisplayer().DisplayMesh( VoronoiMesh );
		glEnable( GL_CULL_FACE );
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_LIGHTING );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
		Toolkit.GetCoarseDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
	}
	if( bFilledModeOn )
		draw_scene();

	/* draw a dot at position of the interpolation */
	glDisable( GL_LIGHTING );
	glLineWidth( 8.0 );
	glColor3f( 1,1,0 );
	glBegin( GL_POINTS );
//	glVertex( InterpPos );
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
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );
		break;
	case '-':
		cout << "Decreasing constrast." << endl;
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kGeodesicDistance) )
			Toolkit.GetGeodesicDisplayer().DecreaseContrast( GW_BasicDisplayer::kGeodesicDistance );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );
		break;
	case 'r':
		Mesh.ResetGeodesicMesh();
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );
		break;
	case '\t':
		if( SelectedFile != FileList.end() )
			SelectedFile++;
		if( SelectedFile == FileList.end() )
			SelectedFile = FileList.begin();
		load_file();
		break;
	case 'f':
		Toolkit.GetGeodesicDisplayer().ToggleDraw(GW_BasicDisplayer::kUseFlatLighting);
		// Toolkit.GetCoarseDisplayer().ToggleDraw(GW_BasicDisplayer::kUseFlatLighting);
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kUseFlatLighting) )
			cout << "Using flat lighting." << endl;
		else
			cout << "Not using flat lighting." << endl;
		break;
	case 's':
		cout << "Saving saved camera settings ... done.";
		GW_InputOutput::SaveCameraSettings();
		break;
	case 'l':
		cout << "Loading saved camera settings ... done.";
		GW_InputOutput::LoadCameraSettings();
		break;
	case '\n':case '\r':
		glutFullScreen();
		break;
	case 'm':
		bDisplayMesh = !bDisplayMesh;
		break;
	case 'M':
		bDisplayVoronoiMesh = !bDisplayVoronoiMesh;
		break;
	default:
		cout << "GW is SO COOL !" << endl;
	}
}

void PerformInterpolation()
{
	GW_Face* pFace = VoronoiMesh.GetFace( 0 );
	GW_VoronoiVertex* pV0 = (GW_VoronoiVertex*) pFace->GetVertex(0);
	GW_VoronoiVertex* pV1 = (GW_VoronoiVertex*) pFace->GetVertex(1);
	GW_VoronoiVertex* pV2 = (GW_VoronoiVertex*) pFace->GetVertex(2);
//	VoronoiMesh.InterpolatePositionExhaustiveSearch( Mesh, InterpPos, *pV0, *pV1, *pV2, rXInterp, rYInterp, 1-rXInterp-rYInterp );
	VoronoiMesh.InterpolatePosition( Mesh, InterpPos, *pV0, *pV1, *pV2, rXInterp, rYInterp, 1-rXInterp-rYInterp );
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
	GW_Bool bUseRandomStartPoint = GW_True;
	GW_Bool bAssignColor = GW_False;
	GW_Bool bFillHole = GW_False;
	switch(key)
	{
	case GLUT_KEY_F1:
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add one furthest point  ... " << endl;
		Toolkit.AddFurthestPoint(1, bUseRandomStartPoint, bAssignColor);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F2:
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 10 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(10, bUseRandomStartPoint, bAssignColor);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F11:
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 100 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(100, bUseRandomStartPoint, bAssignColor);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F3:
		Mesh.RegisterWeightCallbackFunction( BasicWeightCallback );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
		cout << "Building coarse mesh ... " << endl;
		VoronoiMesh.BuildMesh( Mesh, bFillHole );
		VoronoiMesh.BuildRawNormal();
		VoronoiMesh.ReOrientMesh( *VoronoiMesh.GetFace(0) );
		VoronoiMesh.ReOrientNormals();
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );
		Toolkit.GetCoarseDisplayer().BuildVertexArray( VoronoiMesh );
		Toolkit.GetCoarseDisplayer().EnableDraw(GW_BasicDisplayer::kUseFlatLighting);
		break;
	case GLUT_KEY_F4:
		Mesh.RegisterWeightCallbackFunction( BasicWeightCallback );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
		cout << "Building geodesic edges ... " << endl;
		VoronoiMesh.BuildGeodesicBoundaries( Mesh );
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().BuildVertexArray( Mesh );
		break;
	case GLUT_KEY_F5:
		Mesh.RegisterWeightCallbackFunction( BasicWeightCallback );
		cout << "Computing parametrization ... " << endl;
		VoronoiMesh.BuildGeodesicParametrization( Mesh );
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kVertexParametrization );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kStoppingVertex );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );
		break;
	case GLUT_KEY_F6:
		{
			GW_VoronoiVertex* pVert = (GW_VoronoiVertex*) VoronoiMesh.GetVertex(nNumLocalFrontSeleted);
			if( pVert!=NULL )
			{
				nNumLocalFrontSeleted = (nNumLocalFrontSeleted+1)%VoronoiMesh.GetNbrVertex();
				Mesh.RegisterForceStopCallbackFunction( 
					GW_VoronoiMesh::FastMarchingCallbackFunction_Parametrization );
				GW_VoronoiMesh::pCurrentVoronoiVertex_ = pVert;

				cout << "Performing local fast marching from vertex " << nNumLocalFrontSeleted << " ... ";
				VoronoiMesh.PerformLocalFastMarching( Mesh, *pVert );
				cout << "done." << endl;
				Toolkit.GetGeodesicDisplayer().SetUpDraw( Mesh );
				Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kStoppingVertex );
//				Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kVertexParametrization );
				Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );
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

/** test for cgal lib */
#if 0
typedef CGAL::Cartesian<GW_Float>					GW_CgalFloat;
typedef CGAL::Point_3<GW_CgalFloat>					GW_Point;
typedef CGAL::Vector_3<GW_CgalFloat>				GW_Vector;
typedef CGAL::Segment_3<GW_CgalFloat>				GW_Segment;
typedef CGAL::Triangle_3<GW_CgalFloat>				GW_Triangle;
typedef CGAL::Triangulation_3<GW_CgalFloat>			GW_Triangulation;
typedef GW_Triangulation::Vertex_iterator			GW_CgalVertexIterator;

// typedef CGAL::Circle_3<GW_CgalFloat>				GW_Circle;
// typedef CGAL::Bbox_3								GW_Bbox;
// typedef CGAL::Aff_transformation_3<GW_CgalFloat>	GW_Transformation;

// typedef CGAL::Polygon_traits_3<GW_CgalFloat>					GW_Polygon_traits;
// typedef std::list< GW_Point >										GW_Polygon_Container;
// typedef CGAL::Polygon_3< Polygon_traits, Polygon_Container >	GW_Polygon;

// typedef CGAL::Triangulation_euclidean_traits_3<GW_CgalFloat>    GW_EucliTraits;
// typedef CGAL::Triangulation_vertex_base_3<GW_EucliTraits>       GW_TrianVbase;
// typedef CGAL::Triangulation_face_base_3<GW_EucliTraits>         GW_TrianFbase;
// typedef CGAL::Triangulation_default_data_structure_3<
// GW_EucliTraits, GW_TrianVbase, GW_TrianFbase>       GW_TrianDs;
// typedef CGAL::Triangulation_3<GW_EucliTraits, GW_TrianDs>			GW_Triangulation;
// typedef CGAL::Delaunay_triangulation_3<GW_EucliTraits, GW_TrianDs>	GW_Delaunay_triangulation;
#endif

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
    // GW_Maths::TestClass();

	/* just a hack to check memory leak under win32 */
#ifdef GW_DEBUG	
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); // Get current flag
	flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	_CrtSetDbgFlag(flag); // Set flag to the new value
#endif

	GW_InputOutput::Init(argc, argv, WINDOW_SIZE, "GW -- Test of mesh parameterization");

	srand( (unsigned)time( NULL ) );

	cout << endl << "    GW -- Test of mesh parameterization" << endl << endl;
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