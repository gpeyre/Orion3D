
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Collider_ABC.h
 *  \brief Definition of class \c OR_Collider_ABC
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Collider_ABC_h_
#define __OR_Collider_ABC_h_

#include "../configuration/OR_Config.h"
#include "OR_PhysicModel.h"
#include "OR_RigidBody.h"

namespace OR {

class OR_CollisionManager;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Collider_ABC
 *  \brief  Base class for all collider.
 *  \author Gabriel Peyré 2001-09-13
 *  
 *	A collider track collision between a pair of object.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Collider_ABC
{

public:

    OR_Collider_ABC();
    virtual ~OR_Collider_ABC();

	
    //-------------------------------------------------------------------------
    /** \name collision detection method */
    //-------------------------------------------------------------------------
    //@{
	virtual void PerformCollisionDetection( OR_CollisionManager& CollisionManager )=0;
	virtual OR_PhysicEntity& GetCollidee0()=0;
	virtual OR_PhysicEntity& GetCollidee1()=0;
    //@}

	//-------------------------------------------------------------------------
    /** \name activity management */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool IsActive();
	void Enable();
	void Disable();
    //@}

private:

	
	/** do we need to check collision for this pair */
	OR_Bool bIsActive_;

};


typedef list<OR_Collider_ABC*>		T_ColliderList;
typedef T_ColliderList::iterator	IT_ColliderList;

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_Collider_ABC.inl"
#endif


#endif // __OR_Collider_ABC_h_

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

