/*----------------------------------------------------------------------------*/
/*                         OR_InputOutput_None.cpp                            */
/*----------------------------------------------------------------------------*/
/* functions implementation for no in/out                                   */
/*----------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_InputOutput_None.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "../input_output/OR_InputOutput_ABC.h"

#ifdef _USE_NONE_

namespace OR
{
	
//-----------------------------------------------------------------------------
// Name: OR_InputOutput_None constructor
/**
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_InputOutput_None::OR_InputOutput_None(OR_Renderer_ABC& Renderer)
:OR_InputOutput_ABC(Renderer)
{

}


//-----------------------------------------------------------------------------
// Name: OR_InputOutput_None destructor
/**
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_InputOutput_None::~OR_InputOutput_None()
{

}


/* NONE specific functions ***************************************************/
void OR_InputOutput_None::PostReDisplay()
{
	OR_Globals::MessageHandler()->Warning("OR_InputOutput_None::PostReDisplay", "You should define your own functions.");
}

void OR_InputOutput_None::Swap()
{
	OR_Globals::MessageHandler()->Warning("OR_InputOutput_None::Swap", "You should define your own functions.");
}

void OR_InputOutput_None::Initialisation(int *argc, char **argv, char* name,
										 OR_I32 largeur, OR_I32 hteur,
								  	     OR_I32 posx, OR_I32 posy)
{
	
}

void OR_InputOutput_None::MainLoop()
{
	OR_Globals::MessageHandler()->FatalError("OR_InputOutput_None::MainLoop", 
			"You must write your own MainLoop function when defining _USE_NONE_.");
}

} // namespace OR

#endif /* #ifdef _USE_NONE_ */


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