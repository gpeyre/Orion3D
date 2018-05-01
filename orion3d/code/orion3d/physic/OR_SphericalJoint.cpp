/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SphericalJoint.cpp
 *  \brief Definition of class \c OR_SphericalJoint
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SphericalJoint.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_SphericalJoint.h"

#ifndef OR_USE_INLINE
	#include "OR_SphericalJoint.inl"
#endif

using namespace OR;

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint::GetDimension
 *
 *  \return the numer of degree of freedom that this constraint removes from the system
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_U32 OR_SphericalJoint::GetDimension()
{
	return 3;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphericalJoint::SetUpJacobianMatrix
 *
 *  \param  Jacobian the constraint jacobian matrix.
 *  \param  nOffset the offset of the first raw of constaint in the jacobian matrix.
 *  \author Gabriel Peyré 2001-10-31
 *
 *	compute and place the block in the jacobian matrix.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SphericalJoint::Update(OR_SparseMatrix& Jacobian, OR_VectorND& Constr, OR_VectorND& ConstrDeriv,
							   OR_U32 nOffset)
{
	OR_U32 i,j;
	OR_U32 nRB1Offset = this->GetRigidBody1().GetJointID()*6;
	OR_U32 nRB2Offset = this->GetRigidBody2().GetJointID()*6;

	/* positionate the Jacobian block in the jacobian matrix */
	Block1_.SetOffset( nOffset, nRB1Offset );
	Block2_.SetOffset( nOffset, nRB2Offset );	

	/* compute the constraint value */
	OR_Vector3D DeltaPos = this->GetRigidBody1().ComputePos( P1_ ) - 
						   this->GetRigidBody2().ComputePos( P2_ );
	Constr.SetData( nOffset,   DeltaPos[0] );
	Constr.SetData( nOffset+1, DeltaPos[1] );
	Constr.SetData( nOffset+2, DeltaPos[2] );

	/* compute the constraint derivate value */
	OR_Vector3D DeltaSpeed = this->GetRigidBody1().ComputeSpeed( P1_ ) - 
							 this->GetRigidBody2().ComputeSpeed( P2_ );
	Constr.SetData( nOffset,   DeltaSpeed[0] );
	Constr.SetData( nOffset+1, DeltaSpeed[1] );
	Constr.SetData( nOffset+2, DeltaSpeed[2] );

	/* compute the jacobian matrix for first rigid body */
	Matrix1_.Reset( this->GetDimension(), 6 );
	Matrix1_.SetData(0,0,1);
	Matrix1_.SetData(1,1,1);
	Matrix1_.SetData(2,2,1);

	OR_Matrix3x3 RotConstr = this->GetRigidBody1().GetRotationMatrix()*P1_.CrossProductMatrix();
	for( i=0; i<3; ++i )
	for( j=0; j<3; ++j )
		Matrix1_.SetData(i,j+3,RotConstr.GetData(i,j) );
	
	/* compute the jacobian matrix for second rigid body */
	Matrix2_.Reset( this->GetDimension(), 6 );
	Matrix2_.SetData(0,0,1);
	Matrix2_.SetData(1,1,1);
	Matrix2_.SetData(2,2,1);
	RotConstr = this->GetRigidBody2().GetRotationMatrix()*P2_.CrossProductMatrix();
	for( i=0; i<3; ++i )
	for( j=0; j<3; ++j )
		Matrix2_.SetData(i,j+3,RotConstr.GetData(i,j) );
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
