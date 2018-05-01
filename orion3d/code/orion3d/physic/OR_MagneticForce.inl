/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MagneticForce.inl
 *  \brief Inlined methods of class OR_MagneticForce
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_MagneticForce.h"

namespace OR {



/*------------------------------------------------------------------------------*/
// Name : OR_MagneticForce constructor
/** 
 *  \param  MagneticField The magnetic field.
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_MagneticForce::OR_MagneticForce(OR_Vector3D& MagneticField)
:	OR_Force_ABC()
{
	MagneticField_ = MagneticField;
}



/*------------------------------------------------------------------------------*/
// Name : OR_MagneticForce destructor
/** 
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_MagneticForce::~OR_MagneticForce()
{
}



/*------------------------------------------------------------------------------*/
// Name : OR_MagneticForce::SetMagneticField
/** 
 *  \param  MagneticField The magnetic field.
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MagneticForce::SetMagneticField(OR_Vector3D& MagneticField)
{
	MagneticField_ = MagneticField;
}



/*------------------------------------------------------------------------------*/
// Name : OR_MagneticForce::GetMagneticField
/** 
 *  \return The magnetic field.
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_MagneticForce::GetMagneticField()
{
	return MagneticField_;
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

