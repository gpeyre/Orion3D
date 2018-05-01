/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Constraint_ABC.inl
 *  \brief PInlined functions of OR_Constraint_ABC.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Constraint_ABC.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Constraint_ABC constructor
 *
 *  \param  pTarget1 first target
 *  \param  pTarget2 second target
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Constraint_ABC::OR_Constraint_ABC(OR_Particule* pTarget1, OR_Particule* pTarget2)
{
	pTarget1=pTarget1_;
	pTarget2=pTarget2_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Constraint_ABC destructor
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Constraint_ABC::~OR_Constraint_ABC()
{
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Constraint_ABC::SetTarget1
 *
 *  \param  pTarget the new first target
 *  \author Gabriel Peyré 2001-07-18
 *
 *	A constraint always involved two constraints.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Constraint_ABC::SetTarget1(OR_Particule* pTarget)
{
	pTarget1_=pTarget;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Constraint_ABC::GetTarget1
 *
 *  \return the first target
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Particule* OR_Constraint_ABC::GetTarget1()
{
	return pTarget1_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Constraint_ABC::SetTarget2
 *
 *  \param  pTarget the new second target
 *  \author Gabriel Peyré 2001-07-18
 *
 *	A constraint always involved two constraints.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Constraint_ABC::SetTarget2(OR_Particule* pTarget)
{
	pTarget2_=pTarget;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Constraint_ABC::GetTarget2
 *
 *  \return the second target
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Particule* OR_Constraint_ABC::GetTarget2()
{
	return pTarget2_;
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

