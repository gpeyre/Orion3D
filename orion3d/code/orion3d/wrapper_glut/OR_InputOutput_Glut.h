//*****************************************************************************
/// \author Gabriel Peyré
//*****************************************************************************

#ifndef __OR_InputOutput_Glut_h_
#define __OR_InputOutput_Glut_h_

#ifdef __GNUG__
    #pragma interface
#endif

#include "../configuration/OR_Config.h"
#include "../input_output/OR_InputOutput_ABC.h"
#include <GL/glut.h>

namespace OR {

//=============================================================================
/**
*   @class  OR_InputOutput_Glut
*   @brief  A wrapper that use GLUT API for input/output.
*
*	GLUT homepage :  <a href="http://reality.sgi.com/opengl/glut3/glut3.html">reality.sgi.com/opengl/glut3/glut3.html</a>
*	GLUT for Win32 : <a href="http://www.xmission.com/~nate/glut.html">www.xmission.com/~nate/glut.html</a>
*	
*/
/// \author Gabriel Peyré
//=============================================================================
class OR_InputOutput_Glut: public OR_InputOutput_ABC
{

public:

    OR_InputOutput_Glut(OR_Renderer_ABC& Renderer);
    virtual ~OR_InputOutput_Glut();

	//-------------------------------------------------------------------------
    /** @name overload of OR_InputOutput_ABC methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void Initialisation(int *argc, char **argv, char* name,
		OR_I32 largeur=640, OR_I32 hteur=480,
		OR_I32 posx=0, OR_I32 posy=0);
	virtual void SetupPixelFormat(int *argc, char **argv);
	virtual void PostReDisplay();
	virtual void Swap();
	virtual void MainLoop();
    //@}

    //-------------------------------------------------------------------------
    /** @name API-specific default callbacks */
    //-------------------------------------------------------------------------
    //@{
	static void Default_Destroy();
	static void Default_KeyPressed(OR_U32 button, OR_I32 x, OR_I32 y);
	static void Default_Mouseclic(OR_I32 button, OR_I32 state, OR_I32 x, OR_I32 y);
    //@}

private:
	static GLint	WindowName;

};

} // End namespace OR

#endif // __OR_InputOutput_Glut_h_
