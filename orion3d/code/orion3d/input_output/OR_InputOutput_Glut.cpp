/*----------------------------------------------------------------------------*/
/*                         OR_InputOutput_Glut.cpp                            */
/*----------------------------------------------------------------------------*/
/* functions implementation for Glut in/out                                   */
/*----------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_InputOutput_Glut.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_InputOutput.h"

	
#ifdef _USE_GLUT_

namespace OR
{

/*----------------------------------------------------------------------------*/
/*                              class OR_InputOutput                          */
/*----------------------------------------------------------------------------*/
/* gestion des fonction d'input/output via                                    */
/* glut ou windows                                                            */
/*----------------------------------------------------------------------------*/

/* GLUT specific functions ***************************************************/
void OR_InputOutput::PostReDisplay()
{
	glutPostRedisplay();
}

void OR_InputOutput::Swap()
{
	glutSwapBuffers();
}

void OR_InputOutput::Initialisation(OR_I32 *argc, char **argv, char* name,
				  OR_I32 largeur, OR_I32 hteur,
				  OR_I32 posx, OR_I32 posy)
{
	/* create the windows */
	SetupPixelFormat(argc, argv);
	glutInitWindowSize(largeur, hteur);
	glutInitWindowPosition(posx, posy);
	glutCreateWindow(name);
	/* initialize opengl and openil */
	MyOrion->InitGraphics();
}

void OR_InputOutput::SetupPixelFormat(OR_I32 *argc, char **argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH 
		| GLUT_STENCIL | GLUT_MULTISAMPLE);
}

void OR_InputOutput::MainLoop()
{
	/* initialize input/output callback functions */
	#ifdef _USE_WIN32_

	#endif
	#ifdef _USE_GLUT_
		if (Idle!=NULL) glutIdleFunc(Idle);
		if (Display!=NULL) glutDisplayFunc(Display);
		if (Reshape!=NULL) glutReshapeFunc(Reshape);
		if (Mouseclic!=NULL) glutMouseFunc(Mouseclic);
		if (Mouse!=NULL) glutMotionFunc(Mouse);
		if (Passmotion!=NULL) glutPassiveMotionFunc(Passmotion);
		if (KeyPressed!=NULL) glutKeyboardFunc((void (*) (unsigned char, OR_I32, OR_I32)) KeyPressed);
		if (Special!=NULL) glutSpecialFunc(Special);
	#endif

	/* start an inifinite loop */
	OR_CATCH_EXCEPTION(	glutMainLoop(); )
}

} // namespace OR

#endif // _USE_WIN32_


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