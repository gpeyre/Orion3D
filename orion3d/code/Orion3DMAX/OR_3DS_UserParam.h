/*------------------------------------------------------------------------------
 *  \file  OR_3DS_UserParam.h
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-11-05
 *------------------------------------------------------------------------------*/

#ifndef __OR_3DS_UserParam_h_
#define __OR_3DS_UserParam_h_

#include "stdafx.h"

using namespace OR;

namespace OR_3DS {


const Class_ID MyClassID = Class_ID(0xbb371d7, 0x5f344ff5);
const SClass_ID MySuperClassID = UTILITY_CLASS_ID;


/*------------------------------------------------------------------------------
 *  \class  OR_3DS_UserParam
 *  \brief  PUT THE COMMENTS ON THE CLASS HERE
 *  \author Antoine Bouthors 2001-11-05
 *  PUT FULL DESCRIPTION HERE 
 *------------------------------------------------------------------------------*/

#pragma warning( disable: 4200)

class OR_3DS_UserParam
{
public:
	///Different types of UserParams
	enum UserParamType {UserParam_Undefined,UserParam_U32,UserParam_String};

	///Total size of the param
	int		Size;
	///Name of the param
	char	Name[256];
	///Type (see UserParamType)
	int		Type;
	///Data itself
	char	Data[];
};

#pragma warning( default: 4200)

///Create and initialize a U32 UserParam
///\param Name the name to set to the UserParam
///\param Val the value to set to the UserParam
///\return the UserParam created
OR_3DS_UserParam* new_UserParamU32(char* Name, OR_U32 Val=0);
///Create and initialize a String UserParam
///\param Name the name to set to the UserParam
///\param length the length of the string
///\param Val the string itself
///\return the UserParam created
OR_3DS_UserParam* new_UserParamString(char* Name, unsigned int length=256, char* Val=NULL);

} // End namespace OR_3DS

#ifdef OR_USE_INLINE
#   include "OR_3DS_UserParam.inl"
#endif


#endif // __OR_3DS_UserParam_h_

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

