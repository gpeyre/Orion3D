//*****************************************************************************
/// \author Gabriel Peyré
//*****************************************************************************

#ifndef __OR_InputOutput_None_h_
#define __OR_InputOutput_None_h_

#ifdef __GNUG__
    #pragma interface
#endif


#include "../configuration/OR_Config.h"
#include "OR_InputOutput_ABC.h"

#ifdef _USE_NONE_

namespace OR {

//=============================================================================
/**
*   @class  OR_InputOutput_None
*   @brief  Wrapper for input/output using no external API.
*/
/// \author Gabriel Peyré
//=============================================================================
class OR_InputOutput_None: public OR_InputOutput_ABC
{

public:

    OR_InputOutput_None(OR_Renderer_ABC& Renderer);
    virtual ~OR_InputOutput_None();

	
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

private:

};

} // End namespace OR

#endif // _USE_NONE_


#endif // __OR_InputOutput_None_h_
