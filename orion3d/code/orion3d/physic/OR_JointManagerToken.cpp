/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_JointManagerToken.cpp
 *  \brief Definition of class \c OR_JointManagerToken
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_JointManagerToken.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_JointManagerToken.h"

#ifndef OR_USE_INLINE
	    #include "OR_JointManagerToken.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManagerToken::SetUpMassMatrix
 *
 *  \author Gabriel Peyré 2001-10-31
 *
 *	Compute the mass matrix of the object, and then positionnate the block
 *	in the jacobian matrix according to the rigid body ID.
 */ 
/*------------------------------------------------------------------------------*/
void OR_JointManagerToken::SetUpMassMatrix()
{
	OR_ASSERT( pBody_!=NULL );

	/* copute the mass matrix */
	OR_Float rInvMass = pBody_->GetInvMass();
	OR_Matrix3x3 InvI = pBody_->GetIWorldInv();
	InvMassMatrix_.SetZero();
	InvMassMatrix_.SetData(0,0, rInvMass);
	InvMassMatrix_.SetData(1,1, rInvMass);
	InvMassMatrix_.SetData(2,2, rInvMass);
	for( OR_U32 i=0; i<3;  ++i )
	for( OR_U32 j=0; j<3;  ++j )
		InvMassMatrix_.SetData( 3+i,3+j, InvI.GetData(i,j) );

	/* set block position */
	OR_U32 nID = pBody_->GetJointID();
	InvMassBlock_.SetColOffset( 6*nID );
	InvMassBlock_.SetRowOffset( 6*nID );
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

