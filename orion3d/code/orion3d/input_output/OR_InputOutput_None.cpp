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

#ifdef _USE_NONE_

namespace OR
{
	
/*----------------------------------------------------------------------------*/
/*                            class OR_InputOutput                            */
/*----------------------------------------------------------------------------*/
/* gestion des fonction d'input/output                                        */
/*----------------------------------------------------------------------------*/

/* NONE specific functions ***************************************************/
void OR_InputOutput::PostReDisplay()
{
	OR_Globals::MessageHandler()->Warning("OR_InputOutput::PostReDisplay", "You should define your own functions.");
}

void OR_InputOutput::Swap()
{
	OR_Globals::MessageHandler()->Warning("OR_InputOutput::Swap", "You should define your own functions.");
}

void OR_InputOutput::Initialisation(OR_I32 *argc, char **argv, char* name,
				  OR_I32 largeur, OR_I32 hteur,
				  OR_I32 posx, OR_I32 posy)
{
	
}

void OR_InputOutput::MainLoop()
{
	OR_Globals::MessageHandler()->FatalError("OR_InputOutput::MainLoop", 
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