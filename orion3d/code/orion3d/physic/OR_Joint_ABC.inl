/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Joint_ABC.inl
 *  \brief Inlined methods for \c OR_Joint_ABC
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Joint_ABC.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC::SetRigidBody1
 *
 *  \param  RB first rigid body.involved.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Joint_ABC::SetRigidBody1(OR_RigidBody& RB)
{
	pBody1_ = &RB;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC::SetRigidBody2
 *
 *  \param  RB second rigid body.involved.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Joint_ABC::SetRigidBody2(OR_RigidBody& RB)
{
	pBody2_ = &RB;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC::GetRigidBody1
 *
 *  \return first rigid body.involved.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RigidBody& OR_Joint_ABC::GetRigidBody1()
{
	OR_ASSERT( pBody1_!=NULL );
	return *pBody1_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC::GetRigidBody2
 *
 *  \return second rigid body.involved.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RigidBody& OR_Joint_ABC::GetRigidBody2()
{
	OR_ASSERT( pBody2_!=NULL );
	return *pBody2_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC::GetBlock1
 *
 *  \return block of the first body in the jacobian.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SparseMatrixBlock& OR_Joint_ABC::GetBlock1()
{
	return Block1_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC::GetBlock2
 *
 *  \return block of the second body in the jacobian.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SparseMatrixBlock& OR_Joint_ABC::GetBlock2()
{
	return Block2_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC::SetJacobianMatrix
 *
 *  \param  Jacobian the jacobian of the constraints.
 *  \author Gabriel Peyré 2001-10-31
 *
 *	Used to keep track of the matrix, because we need to remove our blocks
 *	at deletion.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Joint_ABC::SetJacobianMatrix(OR_SparseMatrix& Jacobian)
{
	if( pJacobian_!=NULL )
	{
		pJacobian_->RemoveBlock( Block1_ );
		pJacobian_->RemoveBlock( Block2_ );
	}

	pJacobian_ = &Jacobian;
	pJacobian_->AddBlock( Block1_ );
	pJacobian_->AddBlock( Block2_ );
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

