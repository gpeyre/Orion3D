/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_JointManagerToken.inl
 *  \brief Inlined methods for \c OR_JointManagerToken
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_JointManagerToken.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManagerToken constructor
 *
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_JointManagerToken::OR_JointManagerToken()
:	pBody_( NULL )
{
	InvMassMatrix_.Reset( 6,6 );
	InvMassBlock_.SetMatrix( InvMassMatrix_ );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManagerToken destructor
 *
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_JointManagerToken::~OR_JointManagerToken()
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManagerToken::GetInvMassMatrixBlock
 *
 *  \return inverse mass matrix.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SparseMatrixBlock& OR_JointManagerToken::GetInvMassMatrixBlock()
{
	return InvMassBlock_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManagerToken::SetRigidBody
 *
 *  \param  RB the rigid body.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_JointManagerToken::SetRigidBody( OR_RigidBody& RB )
{
	pBody_ = &RB;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManagerToken::ReleaseRigidBody
 *
 *  \author Gabriel Peyré 2001-10-31
 *
 *	We don't need this rigid body anymore, so set the pointer to NULL.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_JointManagerToken::ReleaseRigidBody()
{
	pBody_ = NULL;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManagerToken::GetRigidBody
 *
 *  \return the rigid body.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RigidBody* OR_JointManagerToken::GetRigidBody()
{
	return pBody_;
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

