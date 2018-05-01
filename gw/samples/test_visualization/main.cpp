//-------------------------------------------------------------------------
/** \name GW file inclusion */
//-------------------------------------------------------------------------
//@{
#include "stdafx.h"
#include "../ressources/trackball.h"
#include "../../gw_core/GW_Config.h"
#include "../../gw_core/GW_Face.h"
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
#else
	#pragma comment(lib, "glut32.lib")
#endif // OR_DEBUG
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
#define ZOOM_MAX 100
#define ZOOM_FACTOR 0.1f
GW_Bool bWireFrame = GW_False;
GLfloat nLineWidth = 2;



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
	GLfloat light_color[4] = {0.8,0.8,0.8,1};
	glLightfv( GL_LIGHT0, GL_AMBIENT, light_color ) ;
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_color ) ;
	glLightfv( GL_LIGHT0, GL_SPECULAR, light_color ) ;
	glEnable( GL_LIGHTING ) ;
	glEnable( GL_LIGHT0 ) ;
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

	glutSolidSphere(1, 10, 10);

	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

/*------------------------------------------------------------------------------*/
// Name : keyboard
/**
 *  \param  button [GW::OR_U32] key pressed.
 *  \param  x [GW::OR_I32] x position of the mouse.
 *  \param  y [GW::OR_I32] y position of the mouse.
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
	default:
		cout << "GW is SO COOL !" << endl;
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
 *  \param  x [GW::OR_I32] x position of the pointer.
 *  \param  y [GW::OR_I32] y position of the pointer.
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
	glutInit( &argc , argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize( 512, 512 ) ;
	glutInitWindowPosition( 100, 100 ) ;
	glutCreateWindow( ".. GW ..." );



	cout << endl << "    .. GW -- demo -- graphical display of transformations and compression .." << endl << endl;
	cout << "---" << endl;
	cout << "Use 'Left Click + Mouse' to spin the sphere." << endl;
	cout << "Use 'Right Click' to pop-up menu." << endl;
	cout << "Use 'Right+Left Click + mouse up/down' to zoom in/out." << endl;
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