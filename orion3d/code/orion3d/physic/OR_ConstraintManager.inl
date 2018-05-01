/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ConstraintManager.inl
 *  \brief Inlined functions of OR_ConstraintManager.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_ConstraintManager.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ConstraintManager constructor
 *
 *  \author Gabriel Peyré 2001-07-18
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ConstraintManager::OR_ConstraintManager()
:OR_ManagerList_Template<OR_Constraint_ABC>()
{
	nNbrRelaxation_=3;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ConstraintManager::GetNbrIteration
 *
 *  \return The number of relaxations used to solve the relaxation scheme.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ConstraintManager::GetNbrIteration()
{
	return nNbrRelaxation_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ConstraintManager::GetNbrIteration
 *
 *  \param  nNbrRelaxation The new number of relaxations used to solve the relaxation scheme.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ConstraintManager::SetNbrIteration(OR_Float nNbrRelaxation)
{
	nNbrRelaxation_=nNbrRelaxation;
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

