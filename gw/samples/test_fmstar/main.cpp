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

/** different kind of callbacks */
GW_Float CurvatureWeightCallback(GW_GeodesicVertex& Vert)
{
	GW_Float rTotalCurv = Vert.GetMaxCurv()*Vert.GetMaxCurv() + Vert.GetMinCurv()*Vert.GetMinCurv();
	GW_CLAMP( rTotalCurv, 0, 10 );
	return 0.5+rTotalCurv*rCurvatureWeight;
	return 1;
}
GW_Float HalfHalfWeightCallback(GW_GeodesicVertex& Vert)
{
	GW_Vector3D& pos = Vert.GetPosition();
	if( pos[0]>0 )
		return 0.5;
	else
		return 1;
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
GW_Float rHeuristicWeight = 0.9;
void PerformHeuristicPropagation();
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
		pStartVertex	= (GW_GeodesicVertex*) Mesh.GetVertex(1500);
		pEndVertex		= (GW_GeodesicVertex*) Mesh.GetVertex(6000);
    }
    Toolkit.SetEndVertex( *pEndVertex );
    Mesh.RegisterWeightCallbackFunction( WeightCallback );
    /* compute heuristic function */
    if( pHeuristic==NULL )
        pHeuristic = new GW_Float[Mesh.GetNbrVertex()];
    Mesh.ResetGeodesicMesh();
    Mesh.RegisterForceStopCallbackFunction(NULL);
    Mesh.PerformFastMarching( pEndVertex );
    for( unsigned int i=0; i<Mesh.GetNbrVertex(); ++i )
    {
        GW_GeodesicVertex* pVert = (GW_GeodesicVertex*)  Mesh.GetVertex(i);
        pHeuristic[i] = pVert->GetDistance();
    }
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

void draw_scene()
{
	if( bDisplayMesh )
	{
		/* render path */
		Displayer.DisplayPath( Toolkit.GetGeodesicPath(), GW_Vector3D(0,0,1) );
        /* display the list of vertex */
        display_startpoint( pStartVertex, 0,0,1 );
        display_startpoint( pEndVertex, 1,0,0 );
		/* render mesh */
		if( bWireFrameModeOn )
			glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		Displayer.DisplayMesh( Mesh );
        Displayer.DisplayPath( Toolkit.GetGeodesicPath(), GW_Vector3D(1,1,1) );
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
#if 0
	case '+':
		rKernelMaxDist *= 1.03f;
		cout << "New kernel support " << rKernelMaxDist << "." << endl;
		cout << "Peform interpolation ... ";
		InterpolateCoarseDistanceFunction();
		cout << "done." << endl;
		break;
	case '-':
		rKernelMaxDist /= 1.03f;
		cout << "New kernel support " << rKernelMaxDist << "." << endl;
		cout << "Peform interpolation ... ";
		InterpolateCoarseDistanceFunction();
		cout << "done." << endl;
		break;
	case 'i':
		nInterpOrder = (nInterpOrder+1)%nNbrInterpOrder;
		cout << "Interpolation using " << InterpOrderDescr[nInterpOrder] << "." << endl;
		InterpolateCoarseDistanceFunction();
        break;
    case 'c':
        rMaxInterpolatedDistance /= 1.05;
        Displayer.DisableDraw( GW_BasicDisplayer::kGeodesicDistance );
        Displayer.BuildColorArray( Mesh );
        break;
    case 'C':
        rMaxInterpolatedDistance *= 1.05;
        Displayer.DisableDraw( GW_BasicDisplayer::kGeodesicDistance );
        Displayer.BuildColorArray( Mesh );
        break;
    case 't':
        bUseStreamColor = !bUseStreamColor;
        if( bUseStreamColor )
            cout << "Using stream colors." << endl;
        else
            cout << "Not using stream colors." << endl;
        Displayer.BuildColorArray( Mesh );
        break;
#endif
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
#if 0
	case GLUT_KEY_F1:
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add one furthest point  ... " << endl;
		Toolkit.AddFurthestPoint(1, bUseRandomStartPoint, bAssignColor);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F2:
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add 10 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(10, bUseRandomStartPoint, bAssignColor);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F3:
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add 100 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(100, bUseRandomStartPoint, bAssignColor, 10);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F4:
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add 1000 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(1000, bUseRandomStartPoint, bAssignColor,100);
		cout << "done." << endl;
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
	case GLUT_KEY_F7:
		{
			cout << "Perform interpolation of coarse distance map ... " << endl;
			InterpolateCoarseDistanceFunction();
			cout << "done." << endl;
		}

		break;
#endif
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














GW_Float rKernelMaxDist = -1;
GW_U32 nInterpOrder = 2;
GW_U32 nNbrInterpOrder = 5;
string InterpOrderDescr[5] = {
    string("Gaussian rho(r)=exp(-r^2)"),
        string("Quadratic rho(r)=sqrt(1-r^2)"),
        string("Cubic rho(r)=2(r+1/2)(r-1)^2"),
        string("Linear rho(r)=1-r"), 
        string("Thin plate spline rho(r)=r^2*ln(r)")  };

GW_Float InterpolationKernel( GW_Float r )
{
    r /= rKernelMaxDist;

    if( nInterpOrder==0 )
    {
        //	if( r<0 || r>1 )
        //		return 0;
        //	else
        return exp(-r*r);
    }
    else if( nInterpOrder==1 )
    {
        if( r<0 || r>1 )
            return 0;
        else
            return sqrt(1-r*r);
    }
    else if( nInterpOrder==2 )
    {
        if( r<0 || r>1 )
            return 0;
        else
            return 2.0*(r+0.5)*(r-1.0)*(r-1.0);
    }
    else if( nInterpOrder==3 )
    {
        if( r<0 || r>1 )
            return 0;
        else
            return 1-r;
    }
    else
    {
        if( r<=0 || r>1 )
            return 0;
        else
            return r*r*log(r);
    }
}

/** distance between base points and other points */
GW_MatrixNxP DistMatrix;
/** vertex number of each base vertex */
T_U32Vector Base2Geo_Num;
T_U32Map Geo2Base_Num;
GW_Bool bInterpolationDataBuilt = GW_False;
GW_Float rMaxDist = 0;

GW_Bool InsertVertCallback( GW_GeodesicVertex& Vert, GW_Float rNewDist )
{
    return rNewDist < 1.02*rKernelMaxDist;
}
/** compute the distance info */
void BuildInterpolationData()
{
    GW_U32 n = Mesh.GetNbrVertex();
    GW_U32 p = VoronoiMesh.GetNbrVertex();
    cout << "Building Interpolation Data ... " << endl;
    bInterpolationDataBuilt = GW_True;

    //	Mesh.RegisterVertexInsersionCallbackFunction( InsertVertCallback );

    DistMatrix.Reset( p,n );
    /* Gather distance information between base vertex and the rest **********************************************/
    GW_U32 i = 0;
    cout << "  * Computing distance information ";
    GW_ProgressBar pb;
    pb.Begin();
    for( IT_GeodesicVertexList it = VertList.begin(); it!=VertList.end(); ++it )
    {
        GW_GeodesicVertex* pVert = *it; GW_ASSERT( pVert!=NULL );
        Mesh.ResetGeodesicMesh();
        Mesh.PerformFastMarching( pVert );
        for( GW_U32 j=0; j<n; ++j )
        {
            GW_GeodesicVertex* pVert2 = (GW_GeodesicVertex*) Mesh.GetVertex(j); GW_ASSERT( pVert2!=NULL );
            DistMatrix.SetData(i,j, pVert2->GetDistance()*pVert2->GetDistance() );
        }
        i++;
        pb.Update(((GW_Float)i)/((GW_Float)p));
    }
    pb.End();
    cout << endl;


    /* get max distance, to set up the kernel size */ 
    if( rKernelMaxDist<0 )
    {
        rMaxDist = -GW_INFINITE;
        for( GW_U32 i=0; i<p; ++i )
            for( GW_U32 j=0; j<p; ++j )
            {
                GW_U32 jj = Base2Geo_Num[j];
                rMaxDist = GW_MAX( rMaxDist, DistMatrix.GetData(i,jj) );
            }
            rKernelMaxDist = rMaxDist/2.0;
    }

    Mesh.RegisterVertexInsersionCallbackFunction( NULL );
    cout << "done." << endl;
}

/** perform interpolation of a given function using RBF */
void PerfomInterpolation_RBF( T_FloatVector& Original, T_FloatVector& Interpolated )
{
    if( !bInterpolationDataBuilt )
        BuildInterpolationData();
    GW_U32 n = Mesh.GetNbrVertex();
    GW_U32 p = VoronoiMesh.GetNbrVertex();
    GW_ASSERT( Original.size()==p );
    GW_VectorND w(p,0.0);
    GW_VectorND b(p,0.0);		// the weight for the RBF
    GW_MatrixNxP M(p,p,0.0);		// matrix {rho(d(i,j))}

    /* set up matrix */
    for( GW_U32 i=0; i<p; ++i )
        for( GW_U32 j=0; j<p; ++j )
        {
            GW_U32 ii = Base2Geo_Num[i];
            GW_U32 jj = Base2Geo_Num[j];
            GW_Float d1 = DistMatrix.GetData( j,ii );
            GW_Float d2 = DistMatrix.GetData( i,jj );
            GW_Float v = InterpolationKernel(d1);
            M.SetData( i,j, v );
        }
        /* set up rhs */
        for( GW_U32 i=0; i<p; ++i )
        {
            GW_Float v = Original[i];
            b.SetData(i,v);
        }
        /* solve the system M*w = b */
        M.LUSolve( w, b );
        GW_Float err = (M*w-b).Norm1();
        GW_ASSERT( err<1e-7 );
        /* perform interpolation */
        Interpolated.resize( n );
        for( GW_U32 x=0; x<n; ++x )
        {
            GW_Float v = 0;
            for( GW_U32 i=0; i<p; ++i )
            {
                GW_Float d = DistMatrix.GetData( i,x );	// distance between x and i
                v += InterpolationKernel(d)*w[i];
            }
            Interpolated[x] = v;
        }

        /** todo remove */
        for( GW_U32 i=0; i<p; ++i )
        {
            GW_U32 ii = Base2Geo_Num[i];
            GW_Float v1 = Original[i];
            GW_Float v2 = Interpolated[ii];
            GW_ASSERT( GW_ABS(v1-v2)<1e-5 );
        }
}

/** perform interpolation of a given function using Nearest Neighbor */
void PerfomInterpolation_NN( T_FloatVector& Original, T_FloatVector& Interpolated )
{
    if( !bInterpolationDataBuilt )
        BuildInterpolationData();
    GW_U32 n = Mesh.GetNbrVertex();
    GW_U32 p = VoronoiMesh.GetNbrVertex();
    GW_ASSERT( Original.size()==p );

    /* perform interpolation */
    Interpolated.resize( n );
    for( GW_U32 x=0; x<n; ++x )
    {
        /* find nearest neighbor */
        GW_Float d = GW_INFINITE;	// smallest distance
        GW_Float v = 0;	// function value
        for( GW_U32 i=0; i<p; ++i )
        {
            if( DistMatrix.GetData( i,x )<d )
            {
                d = DistMatrix.GetData( i,x );
                v = Original[i];
            }
        }
        Interpolated[x] = v;
    }
}


/** perform interpolation of a given function using Barycentric Coordinates */
void PerfomInterpolation_Barycentric( T_FloatVector& Original, T_FloatVector& Interpolated )
{ 
    if( !bInterpolationDataBuilt )
        BuildInterpolationData();
    GW_U32 n = Mesh.GetNbrVertex();
    GW_U32 p = VoronoiMesh.GetNbrVertex();
    GW_ASSERT( Original.size()==p );

    /* perform interpolation */
    Interpolated.resize( n );
    for( GW_U32 x=0; x<n; ++x )
    {
        /* find nearest neighbor */
        GW_Float d[3] = {GW_INFINITE,GW_INFINITE,GW_INFINITE};	// smallest distance
        GW_U32 id[3] = {0,0,0};	// function value
        for( GW_U32 i=0; i<p; ++i )
        {
            GW_Float dd = DistMatrix.GetData( i,x );
            GW_Float vv = Original[i];
            if( dd<d[0] )
            {
                d[2] = d[1]; d[1] = d[0]; d[0] = dd;
                id[2] = id[1]; id[1] = id[0]; id[0] = i;
            }
            else if( dd<d[1] )
            {
                d[2] = d[1]; d[1] = dd;
                id[2] = id[1]; id[1] = i;
            }
            else if( dd<d[2] )
            {
                d[2] = dd;
                id[2] = i;
            }
        }
        GW_Float v[3] = { Original[id[0]], Original[id[1]], Original[id[2]] };	// function value
        GW_Float dd[3];		// d[0] is distance bewteen 1 and 2
        for( GW_U32 i=0; i<3; ++i )
        {
            GW_U32 i1 = id[ (i+1)%3 ];
            GW_U32 i2 = id[ (i+2)%3 ];
            GW_U32 ii1 = Base2Geo_Num[i1];
            GW_U32 ii2 = Base2Geo_Num[i2];
            dd[i] = 0.5*( DistMatrix.GetData(i1,ii2)+DistMatrix.GetData(i2,ii1) );
        }
        GW_Float Area[3];
        for( GW_U32 i=0; i<3; ++i )
        {
            GW_U32 i1 = (i+1)%3;
            GW_U32 i2 = (i+2)%3;
            // we have a triangle with length dd[i],d[i1],d[i2] ... use heron formula
            GW_Float p = 0.5*( dd[i]+d[i1]+d[i2] );	// semi perimeter
            Area[i] = p*(p-dd[i])*(p-d[i1])*(p-d[i2]);
            if( Area[i]<0 ) 
                Area[i]=0;
            Area[i] = sqrt( Area[i] );
        }
        GW_Float AreaTot = Area[0]+Area[1]+Area[2];
        if( AreaTot>0 )
        {
            Area[0] /= AreaTot;
            Area[1] /= AreaTot;
            Area[2] /= AreaTot;
        }
        else
            Area[0] = 1;
        Interpolated[x] = Area[0]*v[0]+Area[1]*v[1]+Area[2]*v[2];
    }
}


/** perform interpolation of a given function using Barycentric Coordinates */
void PerfomInterpolation_Weighted( T_FloatVector& Original, T_FloatVector& Interpolated )
{
    rKernelMaxDist = 3.0;	// relax a bit
    Mesh.RegisterVertexInsersionCallbackFunction( InsertVertCallback );
    if( !bInterpolationDataBuilt )
        BuildInterpolationData();
    Mesh.RegisterVertexInsersionCallbackFunction( NULL );
    rKernelMaxDist = 3.0;	// relax a bit

    GW_U32 n = Mesh.GetNbrVertex();
    GW_U32 p = VoronoiMesh.GetNbrVertex();
    GW_ASSERT( Original.size()==p );

    /* perform interpolation */
    Interpolated.resize( n );
    for( GW_U32 x=0; x<n; ++x )
    {
        GW_Float w = 0;
        GW_Float v = 0;
        for( GW_U32 i=0; i<p; ++i )
        {
            GW_Float d = DistMatrix.GetData(i,x);
            d = InterpolationKernel(d);
            w += d;
            v += Original[i]*d;
        }
        Interpolated[x] = v/w; 
    }
}

T_FloatVector InterpolatedDistance;
T_FloatVector CoarseDistance;
GW_Float rMinInterpolatedDistance = 0;
GW_Float rMaxInterpolatedDistance = 1;
GW_Bool bUseStreamColor = GW_True;
void AssignInterpolatedColor( GW_Vertex& vert, float* color )
{
    GW_U32 nID = vert.GetID();
    GW_Float d = InterpolatedDistance[nID];
    GW_Float v = GW_SCALE_01( d, rMinInterpolatedDistance, rMaxInterpolatedDistance );
    if( bUseStreamColor )
    {
        GW_Vector3D c = Displayer.GetStreamColor( v, 1 );
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
    }
    else
    {
        color[0] = 1-v;
        color[1] = 0;
        color[2] = v;
    }
}

void InterpolateCoarseDistanceFunction()
{
    /* first set up coarse vertex correspondance */
    GW_U32 n = Mesh.GetNbrVertex();
    GW_U32 p = VoronoiMesh.GetNbrVertex();
    Base2Geo_Num.resize( p );
    Geo2Base_Num.clear();
    GW_U32 k = 0;
    for( IT_GeodesicVertexList it = VertList.begin(); it!=VertList.end(); ++it )
    {
        GW_GeodesicVertex* pVert = *it; GW_ASSERT( pVert!=NULL );
        Base2Geo_Num[k] = pVert->GetID();
        Geo2Base_Num[pVert->GetID()] = k;
        k++;
    }

    /* retrive start/end points */
    GW_U32 n_start = pStartVertex->GetID();
    GW_U32 n_end   = pEndVertex->GetID();
    GW_ASSERT( Geo2Base_Num.find(n_start)!=Geo2Base_Num.end() );
    GW_ASSERT( Geo2Base_Num.find(n_end)!=Geo2Base_Num.end() );
    GW_U32 n_start_coarse = Geo2Base_Num[n_start];
    GW_U32 n_end_coarse = Geo2Base_Num[n_end];

    /* first perform fast marching on the coarse mesh from the end point */
    GW_GeodesicVertex* pStart	= (GW_GeodesicVertex*) CoarseMesh.GetVertex( n_start_coarse );
    GW_GeodesicVertex* pEnd		= (GW_GeodesicVertex*) CoarseMesh.GetVertex( n_end_coarse );
    CoarseMesh.ResetGeodesicMesh();
    CoarseMesh.PerformFastMarching( pEnd );
    /* register coarse distance map */
    CoarseDistance.resize(p);
    for( GW_U32 i=0; i<p; ++i )
    {
        GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) CoarseMesh.GetVertex(i);
        CoarseDistance[i] = pVert->GetDistance();
        //	CoarseDistance[i] = pVert->GetPosition()[0];
    }

    //	PerfomInterpolation_RBF(CoarseDistance, InterpolatedDistance);
    PerfomInterpolation_Weighted(CoarseDistance, InterpolatedDistance);
    rMaxInterpolatedDistance = -GW_INFINITE;
    rMinInterpolatedDistance = GW_INFINITE;
    for( IT_FloatVector it=InterpolatedDistance.begin(); it!=InterpolatedDistance.end(); ++it )
    {
        rMaxInterpolatedDistance = GW_MAX(rMaxInterpolatedDistance, *it);
        rMinInterpolatedDistance = GW_MIN(rMinInterpolatedDistance, *it);
    }
    /* build the color array of the fine mesh */
    Displayer.DisableDraw( GW_BasicDisplayer::kGeodesicDistance );
    Displayer.RegisterComputeColorCallback( AssignInterpolatedColor );
    Displayer.BuildColorArray( Mesh );
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////