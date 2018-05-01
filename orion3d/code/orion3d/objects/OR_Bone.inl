/*---------------------------------------------------------------------------------------*/
/*                                      OR_Bone.inl                                      */
/*---------------------------------------------------------------------------------------*/
/* contains the definition of a bone                                                     */
/*---------------------------------------------------------------------------------------*/

#include "OR_Bone.h"


namespace OR
{

/*---------------------------------------------------------------------------------------*/
/*                                 class OR_Bone                                         */
/*---------------------------------------------------------------------------------------*/

OR_INLINE
OR_Bone::OR_Bone(OR_Float rLength, OR_Bool bIsEndEffector, OR_Mesh* pSkin)
:	OR_Object()
{
	rLength_=rLength;
	pSkin_=pSkin;
	bIsEndEffector_=bIsEndEffector;
	rRotationConstraint_=OR_PI;
}

OR_INLINE
OR_Elements OR_Bone::GetType()
{
	return OR_BONE;
}

OR_INLINE
OR_Mesh *OR_Bone::GetSkin()
{
	return pSkin_;
}

OR_INLINE
void OR_Bone::SetSkin(OR_Mesh* pSkin)
{
	pSkin_=pSkin;	
}

OR_INLINE
OR_Float OR_Bone::GetLength()
{
	return rLength_;
}

OR_INLINE
void OR_Bone::SetLength(OR_Float rLength)
{
	rLength_=rLength;
}

}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////