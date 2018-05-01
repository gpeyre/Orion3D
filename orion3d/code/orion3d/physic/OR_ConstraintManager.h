/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ConstraintManager.h
 *  \brief Definition of OR_ConstraintManager.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ConstraintManager_h_
#define __OR_ConstraintManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Constraint_ABC.h"
#include "../utils/OR_ManagerList_Template.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ConstraintManager
 *  \brief  Manager of constraint.
 *  \author Gabriel Peyré 2001-07-18
 *
 *	A constraint manager is able to solve it's constraints, recursing only on 
 *	relaxable ones.
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerList_Template<OR_Constraint_ABC>;

class ORION3D_API OR_ConstraintManager: public OR_ManagerList_Template<OR_Constraint_ABC>
{

public:
	
	OR_ConstraintManager();

    //-------------------------------------------------------------------------
    /** \name update */
    //-------------------------------------------------------------------------
    //@{
	void Update();
    //@}

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	OR_Float GetNbrIteration();
	void  SetNbrIteration(OR_Float nNbrRelaxation);
    //@}

private:


	/** the number of relaxations used to solve relaxable constraints */
	OR_I32 nNbrRelaxation_;
};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ConstraintManager.inl"
#endif


#endif // __OR_ConstraintManager_h_

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
