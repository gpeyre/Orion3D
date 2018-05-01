/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_JointManager.inl
 *  \brief Inlined methods for \c OR_JointManager
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_JointManager.h"

namespace OR {
	


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::LhsTimeVector
 *
 *  \param  v vector to multiply.
 *  \param  r result.
 *  \return J*W*J^T*v
 *  \author Gabriel Peyré 2001-11-05
 *
 *	This is the callback method used by the conjugate gradient algorithm
 *	to compute the solution.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_JointManager::LhsTimeVector( OR_VectorND& v, OR_VectorND& r )
{
	OR_ASSERT( pStaticThis_!=NULL );

	OR_VectorND Temp(  pStaticThis_->GetRigidBodyDimension() );
	OR_VectorND Temp2( pStaticThis_->GetRigidBodyDimension() );

	OR_SparseMatrix::MultiplyTranspose( pStaticThis_->GetJacobian(), v, Temp );
	OR_SparseMatrix::Multiply( pStaticThis_->GetInvMassMatrix(), Temp, Temp2 );
	OR_SparseMatrix::Multiply( pStaticThis_->GetJacobian(), Temp2, r );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::GetInvMassMatrix
 *
 *  \return global inverse mass matrix.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SparseMatrix& OR_JointManager::GetInvMassMatrix()
{
	return InvMassMatrix_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::GetJacobian
 *
 *  \return global jacobian matrix.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SparseMatrix& OR_JointManager::GetJacobian()
{
	return Jacobian_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::GetRigidBodyDimension
 *
 *  \return dimension of rigid-body related datas.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_JointManager::GetRigidBodyDimension()
{
	return 6*JointTokenVector_.size();
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

