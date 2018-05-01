/*------------------------------------------------------------------------------
 *  \file  OR_Conversion.h
 *  \brief 	Contains the definition of a node in the Orion3D hierarchy.
 *	A node is used to store an OR_Object and an animation player list used
 *	to play a list of animations on the node.
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/

#ifndef __OR_Conversion_h_
#define __OR_Conversion_h_


#include "../configuration/OR_Config.h"

namespace OR {

/*------------------------------------------------------------------------------
 *  \class  OR_Conversion
 *  \brief  a class to perform various conversion.
 *  \author Gabriel Peyré 2001-07-08
 *
 *	This class is mainly used by the shell to perform conversion between 
 *	\c enum and \c OR_String (to display to screen / get from input).
 *------------------------------------------------------------------------------*/

class ORION3D_API OR_Conversion
{

public:

    //-------------------------------------------------------------------------
    /** \name conversion from enum to string 
		Declare the functions : 
			- XXXX OR_Conversion::StringTo_XXXX(OR_String& str) : convert from a string to enum XXXX.
			- OR_String OR_Conversion::XXXX_ToString(XXXX val) : convert from enum XXXX to a string.
	*/
    //-------------------------------------------------------------------------
    //@{
	#define DECL_CONV(type)	\
	static type OR_Conversion::StringTo_##type(OR_String& str);		\
	static OR_String OR_Conversion::type##_ToString(type val)		\

	DECL_CONV(OR_VIEWPORT_Type);
	DECL_CONV(OR_LENSFLARE_Type);
	DECL_CONV(OR_Culling_Mode);
	DECL_CONV(OR_Drawing_Mode);
	DECL_CONV(OR_Blending_Mode);
	DECL_CONV(OR_ANIMATION_Evaluator_Type);
	DECL_CONV(OR_ANIMATION_Track_Type);
	DECL_CONV(OR_ANIMATION_Track_Behavior);
	DECL_CONV(OR_ANIMATION_Player_Behavior);
	DECL_CONV(OR_ANIMATION_Target);
	DECL_CONV(OR_Types);
	DECL_CONV(OR_Elements);
	DECL_CONV(OR_ForceType); 
	DECL_CONV(OR_META_Type); 
	DECL_CONV(OR_MetaBehaviour);
	DECL_CONV(OR_MetaNormalType);
	DECL_CONV(OR_ScrMode); 
	DECL_CONV(OR_Position); 
	DECL_CONV(OR_BUTTON);
	DECL_CONV(OR_BUTTON_STATE);
	DECL_CONV(OR_SOUND_Types);

	#undef DECL_CONV


	static void AddSonFirst(OR_Conversion &pConversion);
    //@}

};

} // End namespace OR


#endif // __OR_Conversion_h_

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
