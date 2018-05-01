/*----------------------------------------------------------------------------*/
/*                         OR_InputOutput_Glut.cpp                            */
/*----------------------------------------------------------------------------*/
/* functions implementation for Glut in/out                                   */
/*----------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_InputOutput_Glut.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_InputOutput_Glut.h"
/* print a log for this project */
#include "../misc/OR_PrintBuildLog.h"
	

namespace OR
{


GLint OR_InputOutput_Glut::WindowName = 0;

//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Glut constructor
/**
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_InputOutput_Glut::OR_InputOutput_Glut(OR_Renderer_ABC& Renderer)
:OR_InputOutput_ABC(Renderer)
{
	Destroy = Default_Destroy;
	KeyPressed = Default_KeyPressed;
	Mouseclic = Default_Mouseclic;
}


//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Glut destructor
/**
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_InputOutput_Glut::~OR_InputOutput_Glut()
{
	Destroy();
}


/* GLUT specific functions ***************************************************/
void OR_InputOutput_Glut::PostReDisplay()
{
	glutPostRedisplay();
}

void OR_InputOutput_Glut::Swap()
{
	glutSwapBuffers();
}

void OR_InputOutput_Glut::Initialisation(int *argc, char **argv, char* name,
				  OR_I32 largeur, OR_I32 hteur,
				  OR_I32 posx, OR_I32 posy)
{
	/* create the windows */
	SetupPixelFormat(argc, argv);
	glutInitWindowSize(largeur, hteur);
	glutInitWindowPosition(posx, posy);
	WindowName = glutCreateWindow(name);
	/* initialize opengl and openil */
	pRenderer_->InitGraphics();
}

void OR_InputOutput_Glut::SetupPixelFormat(int *argc, char **argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH 
		| GLUT_STENCIL | GLUT_MULTISAMPLE);
}

void OR_InputOutput_Glut::MainLoop()
{
	/* initialize input/output callback functions */
	if (Idle!=NULL) glutIdleFunc(Idle);
	if (Display!=NULL) glutDisplayFunc(Display);
	if (Reshape!=NULL) glutReshapeFunc( (void (*)(int,int)) Reshape);
	if (Mouseclic!=NULL) glutMouseFunc( (void (*)(int,int,int,int)) Mouseclic);
	if (Mouse!=NULL) glutMotionFunc( (void (*)(int,int)) Mouse);
	if (Passmotion!=NULL) glutPassiveMotionFunc( (void (*)(int,int)) Passmotion);
	if (KeyPressed!=NULL) glutKeyboardFunc((void (*)(unsigned char,int,int)) KeyPressed);
	if (Special!=NULL) glutSpecialFunc( (void (*)(int,int,int)) Special);

	/* start an inifinite loop */
	try 
	{ 
		glutMainLoop();
	} 
	catch (OR_Exception_ABC* e) 
	{ 
		OR_Globals::ExceptionHandler()->CatchException(e); 
	}
}



//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Glut::Default_Destroy
/**
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_InputOutput_Glut::Default_Destroy()
{
	glutDestroyWindow( WindowName );
}


//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Glut::Default_KeyPressed
/**
*   @param  button button that has been pressed.
*   @param  x x position the mouse
*   @param  y y position the mouse
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_InputOutput_Glut::Default_KeyPressed(OR_U32 button, OR_I32 x, OR_I32 y)
{
	switch (button)
	{
	case 27:
		exit(0);
		break;
	}
	
}


//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Glut::Default_Mouseclic
/**
*   @param  button button that has been pressed.
*   @param  state state of the button.
*   @param  x x position of the mouse
*   @param  y y position of the mouse.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_InputOutput_Glut::Default_Mouseclic(OR_I32 button, OR_I32 state, OR_I32 x, OR_I32 y)
{
	if (button==GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN) 
			StaticThis_->SetLeftButtonState(true);
		else 
			StaticThis_->SetLeftButtonState(false);
	}
	if (button==GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN) 
			StaticThis_->SetRightButtonState(true); 
		else 
			StaticThis_->SetRightButtonState(false);
	}
}



} // namespace OR


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_license.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////