/*--------------------------------------------------------------------------*/
/*                                OR_Functions.h                            */
/*--------------------------------------------------------------------------*/
/* defines misc usefull functions                                           */
/*--------------------------------------------------------------------------*/

/** \file 
	Contains the definition of misc usefull functions.
	\author Gabriel.
**/

#ifndef _OR_FUNCTIONS_H_
#define _OR_FUNCTIONS_H_

#include "../configuration/OR_Config.h"

namespace OR
{

/*-------------------------------------------------------------------------*/
/*              a coolll function to draw local axis                       */
/*-------------------------------------------------------------------------*/

/** a coolll function to draw local axis */
void OR_DrawLocalAxis();

/*-------------------------------------------------------------------------*/
/* get the time since the begining of the program, in mili-second          */
/*-------------------------------------------------------------------------*/
/** get the time since the begining of the program */
OR_I64 ORION3D_API OR_GetTime();

/*-------------------------------------------------------------------------*/
/* primitive pour la manipulation des matrices textures/modelview          */
/*-------------------------------------------------------------------------*/
/** unrotate the texture matrix (usefull for cube mapping) */
void OR_UnRotateTextureMatrix();
/** re-rotate the texture matrix (usefull for cube mapping) */
void ReRotateTextureMatrix();
/** unrotate the model view matrix (usefull for bilboarding) */
void UnRotateModelViewMatrix();

/*-------------------------------------------------------------------------*/
/* orion3d type manipulations                                              */
/*-------------------------------------------------------------------------*/
/** get the global type of the objets. 
	for exemple, OR_Light_TargetSpot --> OR_Light */
enum OR_Elements ORION3D_API GetGlobalType(OR_Elements e);

/*-------------------------------------------------------------------------*/
/*                  string manipulation functions                          */
/*-------------------------------------------------------------------------*/

/** convert a OR_Float to a string : work only under win32 */
char* OR_FloatToString(OR_Float f);
/** print a text file to screen */
void ORION3D_API OR_PrintFromFile(char *adresse, char* title);


/*----------------------------------------------------------------------*/
/* color manipulations                                                  */
/*----------------------------------------------------------------------*/
/** convert HSV to RGB color : TODO !! */
void ORION3D_API OR_HSVtoRGB(OR_Float h, OR_Float s, OR_Float v, OR_Float rgb[3]);



} // namespace OR

#endif    /* #define _OR_FUNCTIONS_H_ */

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////