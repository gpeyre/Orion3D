/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DampingForce.inl
 *  \brief Inlined methods of class OR_DampingForce
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_DampingForce.h"

namespace OR {

	


/*------------------------------------------------------------------------------*/
// Name : OR_DampingForce constructor
/** 
 *  \param  rDamping Damping coefficient.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_DampingForce::OR_DampingForce(OR_Float rDamping)
:	OR_Force_ABC()
{
	rDamping_ = rDamping;
}



/*------------------------------------------------------------------------------*/
// Name : OR_DampingForce destructor
/** 
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_DampingForce::~OR_DampingForce()
{
}



/*------------------------------------------------------------------------------*/
// Name : OR_DampingForce::SetDamping
/** 
 *  \param  rDamping Damping coefficient.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_DampingForce::SetDamping(OR_Float rDamping)
{
	rDamping_=rDamping;
}



/*------------------------------------------------------------------------------*/
// Name : OR_DampingForce::GetDamping
/** 
 *  \return Damping coefficient.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_DampingForce::GetDamping()
{
	return rDamping_;
}


} // End namespace OR

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

