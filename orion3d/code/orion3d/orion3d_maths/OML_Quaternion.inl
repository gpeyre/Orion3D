/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Quaternion.inl
 *  \brief Inlined methods for \c OML_Quaternion
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_Quaternion.h"

namespace OML {

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::GetX
 *
 *  \return the X coord.
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Quaternion::GetX() const
{
	return x;
}
	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::GetY
 *
 *  \return the Y coord.
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Quaternion::GetY() const
{
	return y;
}
	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::GetZ
 *
 *  \return the Z coord.
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Quaternion::GetZ() const
{
	return z;
}	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::GetW
 *
 *  \return the W coord.
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Quaternion::GetW() const
{
	return w;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::SetW
 *
 *  \return the W coord.
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Quaternion::SetW(OML_Float rVal)
{
	w = rVal;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::SetX
 *
 *  \return the X coord.
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Quaternion::SetX(OML_Float rVal)
{
	x = rVal;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::SetY
 *
 *  \return the Y coord.
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Quaternion::SetY(OML_Float rVal)
{
	y = rVal;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::SetZ
 *
 *  \return the Z coord.
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Quaternion::SetZ(OML_Float rVal)
{
	z = rVal;
}
	

} // End namespace OML

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

