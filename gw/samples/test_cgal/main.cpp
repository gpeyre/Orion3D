//-------------------------------------------------------------------------
/** \name GW file inclusion */
//-------------------------------------------------------------------------
//@{
#include "stdafx.h"
#include <GL/glut.h>
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
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_toolkit.lib")
	#pragma comment(lib, "gw_geodesic.lib")
#endif // GW_DEBUG
//@}


/** for the interface */
GW_U32 nNbrStartVertex = 1;
GLfloat nLineWidth = 1;

GW_Toolkit Toolkit;
GW_Bool bDisplayMesh = GW_True;
GW_Bool bDisplayVoronoiMesh = GW_False;
GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
GW_VoronoiMesh& VoronoiMesh = Toolkit.GetVoronoiMesh();
T_GeodesicVertexList& VertList = Toolkit.GetVoronoiMesh().GetBaseVertexList();

/** wire frame/filled mode */
GW_Bool bWireFrameModeOn = GW_False;
GW_Bool bFilledModeOn = GW_True;
#define WIREFRAME_COLOR 0
#define WINDOW_SIZE 600

#define FILE_LIST "files.txt"
T_StringList FileList;
IT_StringList SelectedFile = FileList.end();

void load_file()
{
	if( SelectedFile!=FileList.end() )
	{
		if( Toolkit.LoadFile( (*SelectedFile).c_str() )<0 )
			exit(-1);
	}
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
		/* render mesh */
		Toolkit.GetGeodesicDisplayer().DisplayMesh( Toolkit.GetGeodesicMesh() );
		/* render path */
		Toolkit.GetGeodesicDisplayer().DisplayPath( Toolkit.GetGeodesicPath(), GW_Vector3D(1,1,1) );
		/* display the list of vertex */
		Toolkit.GetGeodesicDisplayer().DisplayVoronoiPoints( Toolkit.GetVoronoiMesh() );
		Toolkit.GetGeodesicDisplayer().DisplayGeodesicBoundaries( Toolkit.GetVoronoiMesh() );
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

	/* draw scene */
	glPushMatrix();

	if( bWireFrameModeOn )
	{
		Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		glDisable( GL_LIGHTING );
		glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth( nLineWidth );
		draw_scene();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_LIGHTING );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
	}
	if( bFilledModeOn )
		draw_scene();

	if( bDisplayVoronoiMesh )
	{
		Toolkit.GetCoarseDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		glDisable( GL_LIGHTING );
		glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth( nLineWidth );

		glDisable( GL_CULL_FACE );
		Toolkit.GetCoarseDisplayer().DisplayMesh( Toolkit.GetVoronoiMesh() );
		glEnable( GL_CULL_FACE );

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_LIGHTING );
		Toolkit.GetCoarseDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
	}

	/* draw start and end points */
    display_startpoint( Toolkit.GetEndVertex(), 1,0,0 );
	T_GeodesicVertexList &StartVertList = Toolkit.GetStartVertex();
	for( IT_GeodesicVertexList it=StartVertList.begin(); it!=StartVertList.end(); ++it )
		display_startpoint( *it, 0,0,1 );


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
			cout << "Filled mode OFF." << endl;
		break;
	case 'x':
		bFilledModeOn = !bFilledModeOn;
		if( bFilledModeOn )
			cout << "Filled mode ON." << endl;
		else
			cout << "Filled mode OFF." << endl;
		break;
	case 'F':
		cout << "Number of front " << Toolkit.AddStartVertex() << "." << endl;
		Toolkit.SetUpMarching();
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case 'f':
		cout << "Number of front " << Toolkit.RemoveStartVertex() << "." << endl;
		Toolkit.SetUpMarching();
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
	case 'e':		
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kBoundaries );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		cout << "Turning Boundaries display ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kBoundaries) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		break;
	case 'c':
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kGeodesicDistanceStreamColor );
		cout << "Turning colorization of distance using color stream ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kGeodesicDistanceStreamColor) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		break;
	case 'm':
		bDisplayMesh = !bDisplayMesh;
		break;
	case 'M':
		bDisplayVoronoiMesh = !bDisplayVoronoiMesh;
		break;
	case 's':
		cout << "Saving saved camera settings ... done.";
		GW_InputOutput::SaveCameraSettings();
		break;
	case 'l':
		cout << "Loading saved camera settings ... done.";
		GW_InputOutput::LoadCameraSettings();
		break;
	case 'i':
		switch( GW_GeodesicFace::GetTriangularInterpolationType() ) {
		case GW_TriangularInterpolation_ABC::kLinearTriangulationInterpolation:
			GW_GeodesicFace::SetTriangularInterpolationType( GW_TriangularInterpolation_ABC::kQuadraticTriangulationInterpolation );
			cout << "Using quadratic triangular interpolation." << endl;
			break;
		case GW_TriangularInterpolation_ABC::kQuadraticTriangulationInterpolation:
			GW_GeodesicFace::SetTriangularInterpolationType( GW_TriangularInterpolation_ABC::kLinearTriangulationInterpolation );
			cout << "Using linear triangular interpolation." << endl;
			break;
		case GW_TriangularInterpolation_ABC::kCubicTriangulationInterpolation:
			GW_GeodesicFace::SetTriangularInterpolationType( GW_TriangularInterpolation_ABC::kQuadraticTriangulationInterpolation );
			cout << "Using quadratic triangular interpolation." << endl;
			break;
		}
		Toolkit.ComputePath( GW_False );
		/* now recompute the last path */
		break;
	default:
		cout << "GW is SO COOL !" << endl;
	}
}

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
		if( Toolkit.GetGeodesicMesh().IsFastMarchingFinished() )
		{
			Toolkit.SetUpMarching();
			GW_Vertex* pStart = Toolkit.GetStartVertex().front();
			Toolkit.GetGeodesicDisplayer().AddFrontColor( *pStart, GW_Vector3D(0,0,1) );
		}
		cout << "Perform one step in fast marching ... ";
		Toolkit.GetGeodesicMesh().PerformFastMarchingOneStep();
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F11:
		if( Toolkit.GetGeodesicMesh().IsFastMarchingFinished() )
		{
			Toolkit.SetUpMarching();
			GW_Vertex* pStart = Toolkit.GetStartVertex().front();
			Toolkit.GetGeodesicDisplayer().AddFrontColor( *pStart, GW_Vector3D(0,0,1) );
		}
		cout << "Perform 200 step in fast marching ... ";
		{
			for( GW_U32 i=0; i<200; ++i )
				Toolkit.GetGeodesicMesh().PerformFastMarchingOneStep();
		}
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F2:
		cout << "Perform Fast Marching ... ";
		Toolkit.GetGeodesicMesh().PerformFastMarchingFlush();
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().SetUpDraw( Toolkit.GetGeodesicMesh() );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kMarchingState );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F3:
		Toolkit.ComputePath();
		break;
	case GLUT_KEY_F4:
		cout << "Building coarse mesh ... ";
		Toolkit.GetVoronoiMesh().BuildMesh( Toolkit.GetGeodesicMesh() );
		Toolkit.GetVoronoiMesh().BuildRawNormal();
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		Toolkit.GetCoarseDisplayer().BuildVertexArray( Toolkit.GetVoronoiMesh() );
		break;
	case GLUT_KEY_F5:
		cout << "Building geodesic edges ... ";
		Toolkit.GetVoronoiMesh().BuildGeodesicBoundaries( Toolkit.GetGeodesicMesh() );
		cout << "done." << endl;
		cout << "Computing parametrization ... ";
		Toolkit.GetVoronoiMesh().BuildGeodesicParametrization( Toolkit.GetGeodesicMesh() );
		cout << "done." << endl;
		Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kVertexParametrization );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F7:
		Toolkit.SetUpMarching();
		{
			GW_Vertex* pStart = Toolkit.GetStartVertex().front();
			Toolkit.GetGeodesicDisplayer().AddFrontColor( *pStart, GW_Vector3D(0,0,1) );
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
	// GW_Maths::TestClass();

	/* just a hack to check memory leak under win32 */
#ifdef GW_DEBUG	
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); // Get current flag
	flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	_CrtSetDbgFlag(flag); // Set flag to the new value
#endif
	
	GW_InputOutput::Init(argc, argv, WINDOW_SIZE, "GW -- Test of geodesic computations");

	cout << endl << "    GW -- Test of geodesic computations." << endl << endl;
	cout << "---" << endl;
	cout << "Use 'Left Click + Mouse' to spin the sphere." << endl;
	cout << "Use 'Right Click' to pop-up menu." << endl;
	cout << "Use 'Right+Left Click + mouse up/down' to zoom in/out." << endl;
	cout << "---" << endl;
	cout << "F1:  Perform one step in fast marching." << endl;
	cout << "F2:  Flush all fast marching computations." << endl;
	cout << "F3:  Compute a geodesic path." << endl;
	cout << "F4:  Build coarse mesh." << endl;
	cout << "F8:  Turn Lighting ON/OFF." << endl;
	cout << "---" << endl;
	cout << "w: Toggle wireframe ON/OFF." << endl;
	cout << "s/S: Add/Remove one front for marching." << endl;
	cout << "e : Toogle boudnaries display ON/OFF" << endl;
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