
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_JointManagerToken.h
 *  \brief Definition of class \c OR_JointManagerToken
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_JointManagerToken_h_
#define __OR_JointManagerToken_h_

#include "../configuration/OR_Config.h"
#include "OR_RigidBody.h"
#include "../utils/OR_SmartCounter.h"
#include "../maths/OR_Maths.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_JointManagerToken
 *  \brief  Used by the joint manager to store rigid bodies with mass matrix.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/

class OR_JointManagerToken
{

public:

    OR_JointManagerToken();
    virtual ~OR_JointManagerToken();

	void SetUpMassMatrix();
	OR_SparseMatrixBlock& GetInvMassMatrixBlock();

	void		  SetRigidBody( OR_RigidBody& RB );
	void		  ReleaseRigidBody();
	OR_RigidBody* GetRigidBody();

private:

	OR_RigidBody* pBody_;
	OR_MatrixNxP InvMassMatrix_;
	OR_SparseMatrixBlock InvMassBlock_;

};

typedef vector<OR_JointManagerToken*> T_JointTokenVector;
typedef T_JointTokenVector::iterator IT_JointTokenVector;

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_JointManagerToken.inl"
#endif


#endif // __OR_JointManagerToken_h_

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

