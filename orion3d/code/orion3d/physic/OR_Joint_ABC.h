
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Joint_ABC.h
 *  \brief Definition of class \c OR_Joint_ABC
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Joint_ABC_h_
#define __OR_Joint_ABC_h_

#include "../configuration/OR_Config.h"
#include "OR_RigidBody.h"
#include "../utils/OR_SmartCounter.h"
#include "../maths/OR_Maths.h"
#include "../utils/OR_Serializable.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Joint_ABC
 *  \brief  Base class for a joint.
 *  \author Gabriel Peyré 2001-10-30
 * 
 *	A joint links two rigid bodies, and create a constraint between them.
 *	This contraint is expressed by two matrix block, wich will be put in 
 *	the jacobian matrix \b J that is taken care at by the joint manager.
 *	
 *	To put these blocks in the correct place, it uses :
 *		- the ID's of the two rigid bodies.
 *		- it's own ID wich is attribuated by the constraints manager.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Joint_ABC: public OR_SmartCounter, public OR_Serializable
{

public:

	OR_Joint_ABC();
	OR_Joint_ABC(OR_RigidBody& RB1, OR_RigidBody& RB2);
    virtual ~OR_Joint_ABC();

    //-------------------------------------------------------------------------
    /** \name methods to overload */
    //-------------------------------------------------------------------------
    //@{
	/** compute and place the block in the jacobian matrix */
	virtual void Update(OR_SparseMatrix& Jacobian, OR_VectorND& Constr, OR_VectorND& ConstrDeriv,
						OR_U32 nOffset) = 0;
	/** the numer of degree of freedom that this constraint removes from the system */
	virtual OR_U32 GetDimension() = 0;
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	void SetRigidBody1(OR_RigidBody& RB);
	void SetRigidBody2(OR_RigidBody& RB);
	OR_RigidBody& GetRigidBody1();
	OR_RigidBody& GetRigidBody2();
	OR_SparseMatrixBlock& GetBlock1();
	OR_SparseMatrixBlock& GetBlock2();
	void SetJacobianMatrix(OR_SparseMatrix& Jacobian);
    //@}

	
	//-------------------------------------------------------------------------
    /** @name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file )	
	{ /* \todo fill this */ }
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file )
	{ /* \todo fill this */ }
    //@}

protected:


	/** first rigid body */
	OR_RigidBody* pBody1_;
	/** second rigid body */
	OR_RigidBody* pBody2_;

	/** the block matrix of body 1 in the global jacobian matrix */
	OR_SparseMatrixBlock Block1_;
	/** the block matrix of body 2 in the global jacobian matrix */
	OR_SparseMatrixBlock Block2_;
	/** the NxP matrix of body 1 in the global jacobian matrix */
	OR_MatrixNxP Matrix1_;
	/** the NxP matrix of body 2 in the global jacobian matrix */
	OR_MatrixNxP Matrix2_;
	/** the jacobian matrix */
	OR_SparseMatrix* pJacobian_;

};

typedef list<OR_Joint_ABC*> T_JointList;
typedef T_JointList::iterator IT_JointList;

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_Joint_ABC.inl"
#endif


#endif // __OR_Joint_ABC_h_

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

