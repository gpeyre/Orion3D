/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ConstraintManager.cpp
 *  \brief Implementation of OR_ConstraintManager.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ConstraintManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ConstraintManager.h"

#ifndef OR_USE_INLINE
	    #include "OR_ConstraintManager.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ConstraintManager::Update
 *
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
void OR_ConstraintManager::Update()
{
	for( OR_I32 nNbrIter=0; nNbrIter<nNbrRelaxation_; ++nNbrIter )
	{
		for( IT_ManagerList_Template(OR_Constraint_ABC) it=begin(); it!=end(); ++it )
		{
			OR_Constraint_ABC* pConstraint = *it;
			if( nNbrIter==0 || pConstraint->IsRelaxable() )
				pConstraint->Update();
		}
	}
}



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

