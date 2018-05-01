/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Collision.inl
 *  \brief inlined methods for OR_Collision class.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Collision.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision constructor
 *
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Collision::OR_Collision()
:	bIsvertexFace_( false )
{
	pBodyB_ = NULL;
	pBodyA_ = NULL;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision destructor
 *
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Collision::~OR_Collision()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::GetBodyA
 *
 *  \return First body involved.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RigidBody* OR_Collision::GetBodyA()
{
	return pBodyA_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::GetBodyB
 *
 *  \return Second body involved.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RigidBody* OR_Collision::GetBodyB()
{
	return pBodyB_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::SetBodyA
 *
 *  \param  BodyA First body involved.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Collision::SetBodyA(OR_RigidBody& BodyA)
{
	pBodyA_ = &BodyA;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::SetBodyB
 *
 *  \param  BodyB Second body involved.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Collision::SetBodyB(OR_RigidBody& BodyB)	
{
	pBodyB_ = &BodyB;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::GetPosition
 *
 *  \return Position of the contact point, in world frame.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_Collision::GetPosition()
{
	return Position_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::SetPosition
 *
 *  \param  Postion Position of the contact point, in world frame.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Collision::SetPosition(OR_Vector3D& Position)
{
	Position_ = Position;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::GetNormal
 *
 *  \return Normal at contact point, in world frame.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	The normal points from B to A.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_Collision::GetNormal()
{
	return Normal_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::SetNormal
 *
 *  \param  Normal ENormal at contact point, in world frame.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	The normal points from B to A.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Collision::SetNormal(OR_Vector3D& Normal)
{
	Normal_ = Normal;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::GetEdgeA
 *
 *  \return The colliding edge in body A.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	This attribute has sense only for edge/edge collision.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_Collision::GetEdgeA()
{
	return EdgeA_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::GetEdgeB
 *
 *  \param EdgeA The colliding edge in body A.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	This attribute has sense only for edge/edge collision.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Collision::SetEdgeA(OR_Vector3D& EdgeA)
{
	EdgeA_ = EdgeA;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::GetEdgeA
 *
 *  \return The colliding edge in body B.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	This attribute has sense only for edge/edge collision.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_Collision::GetEdgeB()
{
	return EdgeB_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::GetEdgeB
 *
 *  \param EdgeB The colliding edge in body B.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	This attribute has sense only for edge/edge collision.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Collision::SetEdgeB(OR_Vector3D& EdgeB)
{
	EdgeB_ = EdgeB;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::IsVertexFace
 *
 *  \return Is the contact a vertex/face one ?
 *  \author Gabriel Peyré 2001-08-28
 *
 *	If it is not, then, it is an edge/edge one.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Collision::IsVertexFace()
{
	return bIsvertexFace_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collision::SetIsVertexFace
 *
 *  \param  bIsvertexFace Is the contact a vertex/face one ?
 *  \author Gabriel Peyré 2001-08-28
 *
 *	If it is not, then, it is an edge/edge one.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Collision::SetIsVertexFace(OR_Bool bIsvertexFace)
{
	bIsvertexFace_ = bIsvertexFace;
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






















