//-------------------------------------------------------------------------
/** \name GW file inclusion */
//-------------------------------------------------------------------------
//@{
#include "stdafx.h"
#include "../ressources/trackball.h"
#include "../../gw_toolkit/GW_Toolkit.h"
#include <GL/glut.h>
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
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_toolkit.lib")
#endif // GW_DEBUG
//@}


/** for the interface */
GW_Bool bSpinning = GW_False, bMoving = GW_False;
GW_I32 nBeginX, nBeginY;
GW_I32 rWidth = 300, rHeight = 300;
GLdouble rAspectRatio;
float curquat[4];
float lastquat[4];
TB_Vector eyePos = { 0.0, 0.0, 3.0 };
GW_Float rZoom = 10;
GW_Bool bZooming = GW_False;
GW_I32 nMouseY = 0;
#define ZOOM_MAX 2000
#define ZOOM_FACTOR 0.2f
GW_Bool bWireFrame = GW_False;
GLfloat nLineWidth = 2;
GW_U32 nSelectedFace = 0;
#define  ROT_SPEED 0.3f

GW_Toolkit Toolkit;

/** wire frame/filled mode */
GW_Bool bWireFrameModeOn = GW_False;
GW_Bool bFilledModeOn = GW_True;
#define WIREFRAME_COLOR 0
#define BACKGROUND_COLOR 1
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
*  \author Gabriel Peyr� 2001-10-17
*
*	Init various stuff.
*/ 
/*------------------------------------------------------------------------------*/
void init()
{		
	if( GW_Toolkit::LoadFileList( FILE_LIST, FileList )<0 )
	{
		cerr << "Can't open files listing " << FILE_LIST << "." << endl;
		exit(-1);
	}
	SelectedFile = FileList.begin();
	/* init the fast sqrt table */
	makeInverseSqrtLookupTable();
	/* init the track ball */
	trackball(curquat, -0.5, 0.0, 0.0, 0.0);

	/* load the current file */
	load_file();
}

void init_gl()
{
	/* init opengl */
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	/* load light */
	GLfloat light_color[4] = {0.3,0.3,0.3,1};
	glLightfv( GL_LIGHT0, GL_AMBIENT, light_color );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_color );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light_color );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	glClearColor( BACKGROUND_COLOR,BACKGROUND_COLOR,BACKGROUND_COLOR,BACKGROUND_COLOR );

//	Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kNormal );
//	Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kMinCurv );
	Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kLighting );
	Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
	Toolkit.GetGeodesicDisplayer().SetVectorScaling( 0.3 );
}

void display()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	GLfloat m[4][4];
	GLfloat invm[4][4];
	//	TB_Vector objectSpaceLightPosition;
	TB_Vector objectSpaceEyePosition;

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

	/* Load a persepctive projection normally. */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( /* field of view in degree */ 40.0,
		/* aspect ratio */ rAspectRatio,
		/* Z near */ 1.0, /* Z far */ 500.0f);

	GLdouble eyeLookAt[16];
	/* Compute a "look at" 4x4 matrix with the "eye" at the eye position. */
	buildLookAtMatrix(eyePos.x, eyePos.y, eyePos.z,  0,0,0,  0,1,0,  eyeLookAt);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(eyeLookAt);

	/* posit light */
	glTranslatef(0,0,-rZoom);
	glMultMatrixf(&m[0][0]);
	GLfloat light_position[4] = { 8,8,0,1 };
	glLightfv( GL_LIGHT0 , GL_POSITION, light_position ) ;

	/* draw everything */
	glPushMatrix();

	/* just draw a special face */
	GW_Face* pFace = Toolkit.GetGeodesicMesh().GetFace(nSelectedFace);
	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	Toolkit.GetGeodesicDisplayer().DisplayFace(*pFace);
	glColor3f(0,0,1);
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_Face* pFace1 = pFace->GetFaceNeighbor(i);
		if( pFace1!=NULL )
			Toolkit.GetGeodesicDisplayer().DisplayFace(*pFace1);
	}
	glEnable(GL_LIGHTING);


	/* render stuff */
	if( bWireFrameModeOn )
	{
		Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		glDisable( GL_LIGHTING );
		glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth( nLineWidth );
		Toolkit.GetGeodesicDisplayer().DisplayMesh( Toolkit.GetGeodesicMesh() );
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_LIGHTING );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
	}
	if( bFilledModeOn )
		Toolkit.GetGeodesicDisplayer().DisplayMesh( Toolkit.GetGeodesicMesh() );

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
*  \author Gabriel Peyr�
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
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMinCurv) )
			Toolkit.GetGeodesicDisplayer().IncreaseContrast( GW_BasicDisplayer::kMinCurv );
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMaxCurv) )
			Toolkit.GetGeodesicDisplayer().IncreaseContrast( GW_BasicDisplayer::kMaxCurv );
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMeanCurv) )
			Toolkit.GetGeodesicDisplayer().IncreaseContrast( GW_BasicDisplayer::kMeanCurv );
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kGaussianCurv) )
			Toolkit.GetGeodesicDisplayer().IncreaseContrast( GW_BasicDisplayer::kGaussianCurv );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case '-':
		cout << "Decreasing constrast." << endl;
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMinCurv) )
			Toolkit.GetGeodesicDisplayer().DecreaseContrast( GW_BasicDisplayer::kMinCurv );
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMaxCurv) )
			Toolkit.GetGeodesicDisplayer().DecreaseContrast( GW_BasicDisplayer::kMaxCurv );
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMeanCurv) )
			Toolkit.GetGeodesicDisplayer().DecreaseContrast( GW_BasicDisplayer::kMeanCurv );
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kGaussianCurv) )
			Toolkit.GetGeodesicDisplayer().DecreaseContrast( GW_BasicDisplayer::kGaussianCurv );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case '\t':
		if( SelectedFile != FileList.end() )
			SelectedFile++;
		if( SelectedFile == FileList.end() )
			SelectedFile = FileList.begin();
		load_file();
		break;
	case 'v':
		Toolkit.GetGeodesicDisplayer().SetVectorScaling( Toolkit.GetGeodesicDisplayer().GetVectorScaling()/1.1 );
		cout << "New vector scaling factor : " << Toolkit.GetGeodesicDisplayer().GetVectorScaling() << endl;
		break;
	case 'V':
		Toolkit.GetGeodesicDisplayer().SetVectorScaling( Toolkit.GetGeodesicDisplayer().GetVectorScaling()*1.1 );
		cout << "New vector scaling factor : " << Toolkit.GetGeodesicDisplayer().GetVectorScaling() << endl;
		break;
	case '\n':case '\r':
		glutFullScreen();
		break;
	default:
		cout << "GW is SO COOL !" << endl;
		cout << "---" << endl;
	}
}

/*------------------------------------------------------------------------------*/
// Name : keyboard_spec
/**
*  \param  button [GW::GW_U32] key pressed.
*  \param  x [GW::GW_I32] x position of the mouse.
*  \param  y [GW::GW_I32] y position of the mouse.
*  \author Gabriel Peyr�
*  \date   11-24-2002
* 
*  To handle the keyboard.
*/
/*------------------------------------------------------------------------------*/
void keyboard_spec(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		if( nSelectedFace>0 )
			nSelectedFace--;
		break;
	case GLUT_KEY_RIGHT:
		if( nSelectedFace<Toolkit.GetGeodesicMesh().GetNbrFace()-1 )
			nSelectedFace++;
		break;
	case GLUT_KEY_F1:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kMinCurv );
		cout << "Turning Minimum Curvature display ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMinCurv) )
			 cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F2:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kMaxCurv );
		cout << "Turning Maximum Curvature display ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMaxCurv) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F3:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kGaussianCurv );
		cout << "Turning Gaussian Curvature display ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kGaussianCurv) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F4:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kMeanCurv );
		cout << "Turning Mean Curvature display ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMeanCurv) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F5:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kNormal );
		cout << "Turning Normal Vector display ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kNormal) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		break;
	case GLUT_KEY_F6:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kMinCurvDirection );
		cout << "Turning Minimum Curvature Vector display ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMinCurvDirection) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		break;
	case GLUT_KEY_F7:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kMaxCurvDirection );
		cout << "Turning Maximum Curvature Vector display ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMaxCurvDirection) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		break;
	case GLUT_KEY_F8:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kMaxAbsCurv);
		cout << "Turning Maximum Absolute Curvature display ";
		if( Toolkit	.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kMaxAbsCurv) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F9:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kLighting );
		cout << "Turning Lighting ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kLighting ) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		break;
	default:
		cout << "GW is SO COOL !" << endl;
		cout << "---" << endl;
	}
}

/*------------------------------------------------------------------------------*/
// Name : idle
/**
*  \author Gabriel Peyr�
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
	if( h!=0 )
	{
		glViewport( 0, 0, w, h  );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective(30,w/h,1.5,50000);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		rWidth = w;
		rHeight = h;
		rAspectRatio = (GLdouble) rWidth/(GLdouble) rHeight;
	}
}

/*------------------------------------------------------------------------------*/
// Name : mouse
/**
*  \param  x [GW::GW_I32] x position of the pointer.
*  \param  y [GW::GW_I32] y position of the pointer.
*  \author Gabriel Peyr�
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
			ROT_SPEED*(2.0 * nBeginX - rWidth) / rWidth,
			ROT_SPEED*(rHeight - 2.0 * nBeginY) / rHeight,
			ROT_SPEED*(2.0 * x - rWidth) / rWidth,
			ROT_SPEED*(rHeight - 2.0 * y) / rHeight
			);
		nBeginX = x;
		nBeginY = y;
		bSpinning = 1;
		glutIdleFunc(idle);
	}
	else if( bZooming )
	{
		rZoom += ZOOM_FACTOR*( y-nMouseY );
		if( rZoom<=0 )
			rZoom=0;
		if( rZoom>=ZOOM_MAX )
			rZoom=ZOOM_MAX;
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
		bZooming = GW_True;
	}
	else if( button == GLUT_LEFT_BUTTON && state == GLUT_UP ) 
	{
		bZooming = GW_False;
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
*  \author Gabriel Peyr� 11-24-2002
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
	glutInit( &argc , argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize( WINDOW_SIZE, WINDOW_SIZE ) ;
	glutInitWindowPosition( 100, 100 ) ;
	glutCreateWindow( ".. GW ..." );

	cout << endl << "    .. GW -- demo -- graphical display of transformations and compression .." << endl << endl;
	cout << "---" << endl;
	cout << "Use 'Left Click + Mouse' to spin the sphere." << endl;
	cout << "Use 'Right Click' to pop-up menu." << endl;
	cout << "Use 'Right+Left Click + mouse up/down' to zoom in/out." << endl;
	cout << "---" << endl;
	cout << "F1: Turn Minimum Curvature display ON/OFF." << endl;
	cout << "F2: Turn Maximum Curvature display ON/OFF." << endl;
	cout << "F3: Turn Gaussian Curvature display ON/OFF." << endl;
	cout << "F4: Turn Mean Curvature display ON/OFF." << endl;
	cout << "F5: Turn Normal Vector display ON/OFF." << endl;
	cout << "F6: Turn Minimum Cuvature Direction display ON/OFF." << endl;
	cout << "F7: Turn Maximum Cuvature Direction display ON/OFF." << endl;
	cout << "F8: Turn Maximum Absolute Cuvature display ON/OFF." << endl;
	cout << "F9: Turn Lighting ON/OFF." << endl;
	cout << "---" << endl;
	cout << "w : Toggle wireframe ON/OFF." << endl;
	cout << "Left/Right arrows : select prev/next triangle." << endl;
	cout << "+/- : increase/decrease contrast of current proprieties." << endl;
	cout << "---" << endl;
	fflush(stdout);

	/* load a bunch of stuff */
	init();
	init_gl();

	/* set up callback functions */
	glutMotionFunc( mouse_motion );
	glutMouseFunc( mouse_click );
	glutKeyboardFunc( keyboard );
	glutSpecialFunc(keyboard_spec);
	glutIdleFunc( idle );
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );

	/* run an infinite loop */
	glutMainLoop();

	return 0;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyr�
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////