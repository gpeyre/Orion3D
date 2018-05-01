/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SphericalJoint.inl
 *  \brief Inlined methods for \c OR_SphericalJoint
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_SphericalJoint.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint constructor
 *
 *  \param  RB1 1st rigid body involved.
 *  \param  RB2 2nd rigid body involved.
 *  \param  nID id of the constraint.
 *  \param  Jacobian jacobian matrix of the constraint manager.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SphericalJoint::OR_SphericalJoint(OR_RigidBody& RB1, OR_RigidBody& RB2)
:	OR_Joint_ABC( RB1, RB2)
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint constructor
 *
 *  \author Gabriel Peyré 2001-10-31
 *
 *	Should only be used by automatic serialization process !
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SphericalJoint::OR_SphericalJoint()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint destructor
 *
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SphericalJoint::~OR_SphericalJoint()
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint::SetAnchorPoint
 *
 *  \param  v anchor position in absolute coordonates.
 *  \author Gabriel Peyré 2001-10-31
 *
 *	Compute the position of the anchor in coords relative to each rigid body.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_SphericalJoint::SetAnchorPoint(OR_Vector3D& v)
{
	P1_ = ~( this->GetRigidBody1().GetWorldToBody() ) * v;
	P2_ = ~( this->GetRigidBody2().GetWorldToBody() ) * v;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint::SetAnchorPointRelative1
 *
 *  \param  v the position of the anchor in coords relative to the 1st rigid body.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_SphericalJoint::SetAnchorPointRelative1(OR_Vector3D& v)
{
	P1_ = v;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint::GetAnchorPointRelative1
 *
 *  \return  v the position of the anchor in coords relative to the 1st rigid body.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_SphericalJoint::GetAnchorPointRelative1()
{
	return P1_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint::SetAnchorPointRelative2
 *
 *  \param  v the position of the anchor in coords relative to the 2nd rigid body.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_SphericalJoint::SetAnchorPointRelative2(OR_Vector3D& v)
{
	P2_ = v;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint::GetAnchorPointRelative2
 *
 *  \return  v the position of the anchor in coords relative to the 2nd rigid body.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_SphericalJoint::GetAnchorPointRelative2()
{
	return P2_;
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

