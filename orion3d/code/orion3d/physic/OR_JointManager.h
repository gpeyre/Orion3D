
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_JointManager.h
 *  \brief Definition of class \c OR_JointManager
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_JointManager_h_
#define __OR_JointManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Joint_ABC.h"
#include "../utils/OR_SmartManagerMap_Template.h"
#include "../utils/OR_IDStack.h"
#include "OR_JointManagerToken.h"

namespace OR {

#define OR_NBR_MAX_JOINT 100

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_JointManager
 *  \brief  a manager of joint.
 *  \author Gabriel Peyré 2001-10-30
 *  
 *	This is the class that drives the constraint resolution.
 *	What it does is :
 *		- loop over the joint and ask them to fill the jacobian matrix.
 *		- loop over the rigid body and ask them to fill the mass matrix.
 *		- resolve the constraint system.
 *		- add the corresponding forces to each rigid body.
 *
 *	Note that :
 *		- it has its own list of rigid bodies (independantly to the physic entity manager).
 *		- that a rigid body can belong to only one \c OR_JointManager.
 *		- all that is because it gives a unique ID to each rigid body.
 *
 *	Here is the stucture of the jacobian matrix :
 *	\code
 *			  rbj_0         rbj_1
 *	+--...---+-----+--...--+-----+--...--+				^
 *	|        |     |       |     |       |				|
 *	.        .     .       .     .       .				|
 *	+--...---+-----+--...--+-----+--...--+				|
 *	|        |     |       |     |       |	<- Ci_0		|
 *	+--...---+-----+--...--+-----+--...--+
 *	.        .     .       .     .       .				size
 *	+--...---+-----+--...--+-----+--...--+				 =
 *	|        |     |       |     |       |	<- Ci_1		Sum(Constrain->GetDim())
 *	+--...---+-----+--...--+-----+--...--+				
 *	.        .     .       .     .       .				|
 *	|        |     |       |     |       |				|
 *	+--...---+-----+--...--+-----+--...--+				v
 *	
 *	<--- size = 6*NbrRigidBody        --->
 *	\endcode
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Joint_ABC>;

class ORION3D_API OR_JointManager: public OR_SmartManagerMap_Template<OR_Joint_ABC>
{

public:

    OR_JointManager();
    virtual ~OR_JointManager();

	void Update();

    //-------------------------------------------------------------------------
    /** \name joint management */
    //-------------------------------------------------------------------------
    //@{
	OR_I32 AddJoint(OR_Joint_ABC& Joint);
	void   RemoveJoint(OR_Joint_ABC& Joint);
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	T_JointList& GetJointList();
	OR_SparseMatrix& GetInvMassMatrix();
	OR_SparseMatrix& GetJacobian();
	OR_U32 GetRigidBodyDimension();
    //@}

private:

	/** a static this used by callback methods */
	static OR_JointManager* pStaticThis_;

	static void LhsTimeVector( OR_VectorND& v, OR_VectorND& r );

	//-------------------------------------------------------------------------
    /** \name helper methods */
    //-------------------------------------------------------------------------
    //@{
	void AddRigidBody(OR_RigidBody& RB);
	void RemoveRigidBody(OR_RigidBody& RB);

	void ComputeRhs();
	void ComputeForceAndTorque();
    //@}

	/** stack of available IDs */
	OR_IDStack IDStack_;

    //-------------------------------------------------------------------------
    /** \name jacobian system datas */
    //-------------------------------------------------------------------------
    //@{
	/** jacobian matrix of the system */
	OR_SparseMatrix Jacobian_;
	/** right hand side of the equation */
	OR_VectorND Rhs_;
	/** constraint value */
	OR_VectorND Constr_;
	/** derivate of the constraint value */
	OR_VectorND ConstrDeriv_;
	/** lagrange multipliers */
	OR_VectorND Lambda_;
	/** external forces acting on the system */
	OR_VectorND ForceExt_;
	/** dimension of the constraints */
	OR_U32 nConstrDim_;
    //@}


	//-------------------------------------------------------------------------
    /** \name rigid body related datas */
    //-------------------------------------------------------------------------
    //@{
	/** list of rigid body involved */
	T_JointTokenVector JointTokenVector_;

	/** global inverse mass matrix */
	OR_SparseMatrix InvMassMatrix_;
    //@}

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_JointManager.inl"
#endif


#endif // __OR_JointManager_h_

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

