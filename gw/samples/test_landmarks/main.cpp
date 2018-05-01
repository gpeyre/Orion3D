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
	#pragma comment(lib, "DevIL-d.lib")
	#pragma comment(lib, "ilu-d.lib")
	#pragma comment(lib, "ilut-d.lib")
	#pragma comment(lib, "gw_core_dbg.lib")
	#pragma comment(lib, "gw_toolkit_dbg.lib")
	#pragma comment(lib, "gw_geodesic_dbg.lib")
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "DevIL.lib")
	#pragma comment(lib, "ilu.lib")
	#pragma comment(lib, "ilut.lib")
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_toolkit.lib")
	#pragma comment(lib, "gw_geodesic.lib")
#endif // GW_DEBUG
//@}


GW_Toolkit Toolkit;
GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
GW_VoronoiMesh& VoronoiMesh = Toolkit.GetVoronoiMesh();
GW_GeodesicDisplayer& Displayer = Toolkit.GetGeodesicDisplayer();
T_GeodesicVertexList& VertList = VoronoiMesh.GetBaseVertexList();
GW_Bool bDisplayMesh = GW_True;
GW_Bool bDisplayVoronoiMesh = GW_False;

/** start point and end point */
GW_GeodesicVertex*	pStartVertex = NULL;
GW_GeodesicVertex*	pEndVertex = NULL;
GW_GeodesicMesh CoarseMesh;
GW_U32 nDisplayBasePointType = 0;

/** wire frame/filled mode */
GLfloat nLineWidth = 1;
GW_Bool bWireFrameModeOn = GW_False;
GW_Bool bFilledModeOn = GW_True;
#define WIREFRAME_COLOR 0
#define BACKGROUND_COLOR 1
#define WINDOW_SIZE 600


#ifdef GW_DEBUG
	#define FILE_LIST "files_debug.txt"
#else
	#define FILE_LIST "files.txt"
#endif

T_StringList FileList;
IT_StringList SelectedFile = FileList.end();
GW_Float rCurvatureWeight = 0; // 0.08;

void load_file()
{
	if( SelectedFile!=FileList.end() )
	{
		if( Toolkit.LoadFile( (*SelectedFile).c_str() )<0 )
			exit(-1);
	}
	Displayer.DisableDraw( GW_BasicDisplayer::kVertexParametrization );
	Displayer.DisableDraw( GW_BasicDisplayer::kStoppingVertex );
	Mesh.ReOrientMesh( *Mesh.GetFace(0) );
	Mesh.ReOrientNormals();
	Displayer.BuildColorArray( Mesh );
    Displayer.SetColorStreamFixedRadius( Mesh.GetBoundingRadius()*3 );
}

GW_Float BasicWeightCallback(GW_GeodesicVertex& Vert)
{
	return 1;
}
GW_GeodesicMesh::T_WeightCallbackFunction WeightCallback = BasicWeightCallback; // HalfHalfWeightCallback;


/*------------------------------------------------------------------------------*/
/** 
* Name : init
*
*  \author Gabriel Peyré 2001-10-17
*
*	Init various stuff.
*/ 
/*------------------------------------------------------------------------------*/
GW_Float* pHeuristic = NULL;  
GW_Float rHeuristicWeight = 1;
void PerformHeuristicPropagation();
void update_heuristic();
void init()
{	
    if( ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
        iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION ||
        ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION ) 
    {
        cout << "DevIL version is different...exiting!";
        exit(1);
    } 
    ilInit();

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

	/* start and end vertices at random */
	GW_Bool bUseRandomPoint = GW_False;
	if( bUseRandomPoint )
	{
		pStartVertex	= (GW_GeodesicVertex*) Mesh.GetRandomVertex();
		pEndVertex		= (GW_GeodesicVertex*) Mesh.GetRandomVertex();
	}
	else
	{
		// bunny 2500 / 6000
        // dave 50k 1500/6000
        // sphere 1000/6000
		pStartVertex	= (GW_GeodesicVertex*) Mesh.GetVertex(20152);
		pEndVertex		= (GW_GeodesicVertex*) Mesh.GetVertex(13883);
    }
    Toolkit.SetEndVertex( *pEndVertex );
    Mesh.RegisterWeightCallbackFunction( WeightCallback );

    /* 
    bool bUseRandomStartPoint = 0;
    bool bAssignColor = 0;
    int nNbrLandmarks = 10;
    Mesh.ResetGeodesicMesh();
    Mesh.RegisterWeightCallbackFunction( WeightCallback );
    Toolkit.AddFurthestPoint(nNbrLandmarks, bUseRandomStartPoint, bAssignColor);
    */

    /* compute heuristic function */
    if( pHeuristic==NULL )
        pHeuristic = new GW_Float[Mesh.GetNbrVertex()];
    memset(pHeuristic, 0, Mesh.GetNbrVertex() * sizeof(GW_Float));

    update_heuristic();
}

int nbr_landmark_upadted = 0;
void update_heuristic()
{
    cout << "Computing heuristic ";
    Mesh.RegisterForceStopCallbackFunction(NULL);
    int i=0;
    for( IT_GeodesicVertexList it=VertList.begin(); it!=VertList.end(); ++it )
    {
        i++;
        if(i>nbr_landmark_upadted)
        {
            GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) *it;
            // start propagation
            Mesh.ResetGeodesicMesh();
            Mesh.PerformFastMarching( pVert );
            // distance of end point
            GW_Float d = pEndVertex->GetDistance();
            for( unsigned int k=0; k<Mesh.GetNbrVertex(); ++k )
            {
                GW_GeodesicVertex* pVert = (GW_GeodesicVertex*)  Mesh.GetVertex(k);
                GW_Float dd = GW_ABS(pVert->GetDistance()-d);
                pHeuristic[k] = GW_MAX( pHeuristic[k], dd );
            }
            cout << "*";
        }
    }
    cout << endl;
    nbr_landmark_upadted = (int) VertList.size();

    PerformHeuristicPropagation();
}

GW_Float HeuristicCallback(GW_GeodesicVertex& v)
{
    unsigned int i = v.GetID();
    return rHeuristicWeight* pHeuristic[i];
}

GW_Bool ForceStopCallback(GW_GeodesicVertex& v)
{
    return &v == pEndVertex;
}

void PerformHeuristicPropagation()
{
    Mesh.RegisterHeuristicToGoalCallbackFunction( HeuristicCallback );
    /* update distance function */
    Mesh.ResetGeodesicMesh();
    Mesh.RegisterForceStopCallbackFunction(ForceStopCallback);
    Mesh.PerformFastMarching( pStartVertex );
    /* set up display */
    Displayer.DisableDraw( GW_BasicDisplayer::kMarchingState );
    Displayer.SetUpDraw( Mesh );
    Displayer.BuildColorArray( Mesh );
    /* extract path */
    Toolkit.GetGeodesicPath().ResetPath();
    Toolkit.ComputePath( GW_False );
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

bool bDisplayPath = true;
void draw_scene()
{
	if( bDisplayMesh )
	{
		/* render path */
        if( bDisplayPath )
    		Displayer.DisplayPath( Toolkit.GetGeodesicPath(), GW_Vector3D(0,0,1) );
		Displayer.DisplayVoronoiPoints( VoronoiMesh, GW_Vector3D(1,0,0) );
        /* display the list of vertex */
        display_startpoint( pStartVertex, 0,0,1 );
        display_startpoint( pEndVertex, 0,1,0 );
		/* render mesh */
		if( bWireFrameModeOn )
			glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		Displayer.DisplayMesh( Mesh );
	}
	if( bDisplayVoronoiMesh )
	{
		glDisable( GL_CULL_FACE );
		Toolkit.GetCoarseDisplayer().DisplayMesh( VoronoiMesh );
		glEnable( GL_CULL_FACE );
	}
}

void display()
{
	GW_InputOutput::PrepareDisplay();

	glPushMatrix();

	if( bWireFrameModeOn )
	{
		draw_scene();
		Displayer.EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		Toolkit.GetCoarseDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		glDisable( GL_LIGHTING );
		glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth( nLineWidth );
		draw_scene();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_LIGHTING );
		Displayer.DisableDraw( GW_BasicDisplayer::kForceMonoColor );
		Toolkit.GetCoarseDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
	}
	else if( bFilledModeOn )
		draw_scene();

	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}


void TakeScreenShot( const char* base_name = "image", const char* extension = "jpg")
{
	// perform a screenshot
	ILuint ImageName;
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	ilutGLScreen();	

	string num_str, file_name;
	for( GW_U32 num=0; num<999; num++ ) 
	{
		num_str = "";
		if( num<10 )
			num_str = num_str + "0";
		if( num<100 )
			num_str = num_str + "0";
		char tmp[256];
		sprintf(tmp, "%u", num );
		num_str = num_str + tmp;

		file_name = string(base_name) + num_str + string(".") + extension;
		FILE* pF = fopen(file_name.c_str(), "rb");
		if( !pF )
			break;
		fclose(pF);
	}
	ilEnable(IL_FILE_OVERWRITE);
	ilSaveImage( (char*) file_name.c_str() );
}

bool bIsHeuristicDisplayed = false;
void switch_distance_display()
{
    bIsHeuristicDisplayed  = !bIsHeuristicDisplayed;
    if( bIsHeuristicDisplayed  )
    {
        for( int i=0; i<Mesh.GetNbrVertex(); ++i )
        {
            GW_GeodesicVertex* pv = (GW_GeodesicVertex*) Mesh.GetVertex(i);
            pv->SetDistance( pHeuristic[i] );
        }
    }
    else
    {
        PerformHeuristicPropagation();
    }
    Displayer.BuildColorArray( Mesh );
}

string base_name = "hand_sampling_halfhalf/image/image";
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
        rHeuristicWeight += 0.025;
        cout << "New heuristic weight = " << rHeuristicWeight << endl;
        PerformHeuristicPropagation();
        break;
    case '-':
        rHeuristicWeight -= 0.025;
        rHeuristicWeight = GW_MAX(0,rHeuristicWeight);
        cout << "New heuristic weight = " << rHeuristicWeight << endl;
        PerformHeuristicPropagation();
        break;

    case 'i':
        init();
        break;
	case 'r':
		Mesh.ResetGeodesicMesh();
		Displayer.BuildColorArray( Mesh );
		break;
	case '\t':
		if( SelectedFile != FileList.end() )
			SelectedFile++;
		if( SelectedFile == FileList.end() )
			SelectedFile = FileList.begin();
		load_file();
		break;
	case 'f':
		Displayer.ToggleDraw(GW_BasicDisplayer::kUseFlatLighting);
		// Toolkit.GetCoarseDisplayer().ToggleDraw(GW_BasicDisplayer::kUseFlatLighting);
		if( Displayer.GetPropriety(GW_BasicDisplayer::kUseFlatLighting) )
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
	case 'u':
		{
			cout << "Updating distance info ... ";
			VoronoiMesh.PerformFastMarching( Mesh, VertList );
			Displayer.BuildColorArray( Mesh );
			cout << "done." << endl;
		}
		break;
	case 'a':
		TakeScreenShot(base_name.c_str());
        break;
    case 'q':
        Displayer.SetColorStreamFixedRadius( Displayer.GetColorStreamFixedRadius()*1.1 );
        Displayer.BuildColorArray( Mesh );
        break;
    case 'Q':
        Displayer.SetColorStreamFixedRadius( Displayer.GetColorStreamFixedRadius()/1.1 );
        Displayer.BuildColorArray( Mesh );
        break;
	case '&':
		{
			float a[3] = {0,1,0};
			GW_InputOutput::RotateView(-0.01, a);
		}
		break;
	case 'é':
		{
			float a[3] = {0,1,0};
			GW_InputOutput::RotateView(0.01, a);
		}
		break;
	case 'y':
		nDisplayBasePointType = (nDisplayBasePointType+1)%3;
		cout << "Display base point type " << nDisplayBasePointType << "." << endl;
        break;
    case 'c':
        Displayer.ToggleDraw( GW_BasicDisplayer::kGeodesicDistanceStreamColor );
        cout << "Turning colorization of distance using color stream ";
        if( Displayer.GetPropriety(GW_BasicDisplayer::kGeodesicDistanceStreamColor) )
            cout << "ON." << endl;
        else 
            cout << "OFF." << endl;
        Displayer.BuildColorArray( Mesh );
        break;
    case 'h':
        switch_distance_display();
        break;
    case 'p':
        bDisplayPath = !bDisplayPath;
        break;
    case 'z':
        pStartVertex	= (GW_GeodesicVertex*) Mesh.GetRandomVertex();
        pEndVertex		= (GW_GeodesicVertex*) Mesh.GetRandomVertex();
        cout << "start " << pStartVertex->GetID() << " end " << pEndVertex->GetID() << endl;
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
#define TRANS_CAM 0.05
	GW_Bool bUseRandomStartPoint = GW_False;
	GW_Bool bAssignColor = GW_False;
	GW_Bool bFillHole = GW_False;
	switch(key)
	{
	case GLUT_KEY_F1:
        VoronoiMesh.PerformFastMarching( Mesh, VertList );
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add one furthest point  ... " << endl;
		Toolkit.AddFurthestPoint(1, bUseRandomStartPoint, bAssignColor);
		cout << "done." << endl;
        update_heuristic();
		break;
    case GLUT_KEY_F2:
        VoronoiMesh.PerformFastMarching( Mesh, VertList );
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add 10 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(10, bUseRandomStartPoint, bAssignColor);
		cout << "done." << endl;
        update_heuristic();
		break;
    case GLUT_KEY_F3:
        VoronoiMesh.PerformFastMarching( Mesh, VertList );
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add 100 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(100, bUseRandomStartPoint, bAssignColor, 10);
		cout << "done." << endl;
        update_heuristic();
		break;
	case GLUT_KEY_F6:
		{
			cout << "Building coarse mesh ... " << endl;
			Mesh.RegisterWeightCallbackFunction( BasicWeightCallback );
			VoronoiMesh.BuildMesh( Mesh, bFillHole );
			GW_OutputComment("Building normals.");
			VoronoiMesh.BuildRawNormal();
			GW_OutputComment("Reorienting the mesh.");
			VoronoiMesh.ReOrientMesh( *VoronoiMesh.GetFace(0) );
			VoronoiMesh.ReOrientNormals();
			cout << "done." << endl;
			Displayer.BuildColorArray( Mesh );
			Toolkit.GetCoarseDisplayer().BuildVertexArray( VoronoiMesh );
			Toolkit.GetCoarseDisplayer().EnableDraw(GW_BasicDisplayer::kUseFlatLighting);
	
			/* copy the coarse mesh */
			((GW_Mesh&) CoarseMesh) = ((GW_Mesh&) VoronoiMesh);
			CoarseMesh.BuildConnectivity();	

			break;
		}

	case GLUT_KEY_F8:
		Displayer.ToggleDraw( GW_BasicDisplayer::kLighting );
		cout << "Turning Lighting ";
		if( Displayer.GetPropriety(GW_BasicDisplayer::kLighting ) )
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

	GW_InputOutput::Init(argc, argv, WINDOW_SIZE, "GW -- Test of geodesic remeshing");

	srand( (unsigned)time( NULL ) );

	cout << endl << "    GW -- Test of mesh parameterization" << endl << endl;
	cout << "---" << endl;
	cout << "Use 'Left Click + Mouse' to spin the sphere." << endl;
	cout << "Use 'Right Click' to pop-up menu." << endl;
	cout << "Use 'Right+Left Click + mouse up/down' to zoom in/out." << endl;
	cout << "---" << endl;
	cout << "F1:  Add 1 furthest point to coarse mesh." << endl;
	cout << "F2:  Add 10 furthest points to coarse mesh." << endl;
	cout << "---" << endl;
	cout << "w: Toggle wireframe ON/OFF." << endl;
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