
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_RigidBody.h
 *  \brief Definition of class OR_RigidBody
 *  \author Gabriel Peyré 2001-08-19
 */ 
/*------------------------------------------------------------------------------*/

#pragma once
#ifndef __OR_RigidBody_h_
#define __OR_RigidBody_h_

#include "../configuration/OR_Config.h"
#include "OR_PhysicEntity.h"
#include "../maths/OR_Maths.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"


namespace OR {

class OR_ForceManager;
class OR_PhysicModel;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_RigidBody
 *  \brief  Contains all datas to handle a rigid body.
 *  \author Gabriel Peyré 2001-08-19
 *  
 *	Contains datas and basic functions to compute the movement of a rigid body.
 *  We make computations (ie. integration of physics equations) on the 4 states 
 *	variables, but we keep track of auxiliary quantities that are often used.
 *
 *	Derivations for physics computations :
 *	\code
 *	d Pos_(t)
 *	--------- = Speed_(t)
 *	    dt
 *
 *	d Rot_(t)   1
 *	--------- = - * (#Omega_(t))*Rot_(t)
 *      dt      2
 *
 *	d P_(t)
 *	------- = ForceAccumulator_(t)
 *	  dt
 *	
 *	d L_(t)
 *	------- = TorqueAccumulator_(t)
 *	  dt
 *
 *	where the operator '#' turn a vector v into a quaternion q=[0,v]
 *	\endcode
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_RigidBody: public OR_PhysicEntity, public OR_ShellObject_ABC
{

public:

    OR_RigidBody(OR_Object& object, OR_Bool bAssignRigidBodyToObject = true );
    virtual ~OR_RigidBody();

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OR_Float     GetMass();
	OR_Float     GetInvMass();
	void         SetMass(const OR_Float rMass);
	OR_Matrix3x3&   GetIBody();
	void         SetIBody(const OR_Matrix3x3& IBody);
	OR_Matrix3x3&   GetIBodyInv();
	OR_Vector3D& GetGravityCenter();
	void		 SetGravityCenter(OR_Vector3D& GravityCenter);
	OR_Float   GetBounce();
	void       SetBounce(OR_Float rBounce);
	OR_Float   GetFriction();
	void       SetFriction(OR_Float rFriction);

	OR_Vector3D&   GetPosition();
	void           SetPosition(const OR_Vector3D Pos);
	OR_Quaternion& GetRotation(); 
	void           SetRotation(const OR_Quaternion& Rot);
	OR_Vector3D&   GetP();
	void           SetP(const OR_Vector3D& P);
	OR_Vector3D&   GetL();
	void           SetL(const OR_Vector3D& L);

	OR_Matrix3x3&     GetIWorldInv();
	OR_Matrix3x3&     GetIWorld();
	OR_Vector3D&   GetSpeed();
	void           SetSpeed(const OR_Vector3D& speed);
	OR_Vector3D&   GetOmega();
	void           SetOmega(const OR_Vector3D& Omega);

	OR_Matrix4x4& GetWorldToBody();
	OR_Matrix4x4& GetWorldToBodyOld();

	OR_Matrix3x3& GetRotationMatrix();

	OR_ForceManager* GetForceManager();
	void		     SetForceManager(OR_ForceManager& ForceManager);

	OR_Vector3D& GetForceAccumulator();
	OR_Vector3D& GetTorqueAccumulator();
	OR_Vector3D& GetForceImpulseAccumulator();
	OR_Vector3D& GetTorqueImpulseAccumulator();
    //@}


    //-------------------------------------------------------------------------
    /** \name accumulators access */
    //-------------------------------------------------------------------------
    //@{
	void AddForce(const OR_Vector3D& force);
	void AddTorque(const OR_Vector3D& torque);
	void AddForceImpulse(const OR_Vector3D& forceImpulse);
	void AddTorqueImpulse(const OR_Vector3D& torqueImpulse);
    //@}

    //-------------------------------------------------------------------------
    /** @name state management */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool EnablePhysicComputations();
	OR_Bool DisablePhysicComputations();
	OR_Bool TogglePhysicComputations();
	OR_Bool IsUsingPhysic();
    //@}

    //-------------------------------------------------------------------------
    /** \name mass management helper */
    //-------------------------------------------------------------------------
    //@{
	void SetUpMassSphere(OR_Float rDensity, OR_Float rRadius);
	void SetUpMassBox(OR_Float rDensity, OR_Vector3D Dim);
	void SetUpMassBox(OR_Float rDensity, OR_Float rDimX, OR_Float rDimY, OR_Float rDimZ);
	void SetUpMassCylinder(OR_Float rDensity, OR_Float rHeight, OR_Float rRadius);
	void AdjustMass(OR_Float rNewMass);
	void TranslateMass(OR_Vector3D Dir);
	void RotateMass(OR_Matrix3x3 Rot);
    //@}

    //-------------------------------------------------------------------------
    /** \name helpers methods */
    //-------------------------------------------------------------------------
    //@{
	void ComputeWorldToBody();
	OR_Vector3D ComputeSpeed( OR_Vector3D Radius );
	OR_Vector3D ComputePos( OR_Vector3D Radius );
	void ComputeAuxiliaryVariables();
	void SynchronizeWithObject();
    //@}

    //-------------------------------------------------------------------------
    /** \name collision detection methods */
    //-------------------------------------------------------------------------
    //@{
	void			SetPhysicModel(OR_PhysicModel& PhysicModel);
	OR_PhysicModel* GetPhysicModel();
    //@}

    //-------------------------------------------------------------------------
    /** \name constaint resolution management */
    //-------------------------------------------------------------------------
    //@{
	OR_U32 GetJointID();
	void   SetJointID(OR_U32 nJointID);
    //@}


    //-------------------------------------------------------------------------
    /** \name overload of \c OR_PhysicEntity methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void UpdatePhysics_RK4( OR_U32 nStepRK4 );
	virtual void UpdatePhysics_Verlet();	
	virtual void UpdatePhysics_Euler();
	virtual T_PhysicEntity_Type GetPhysicType();
	virtual void ProcessForce( OR_ForceManager& ForceManager );
	virtual void ResetAccumulators();
    //@}

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	
	OR_DECL_SHELL_ACCESSOR_FUNC(Mass,			OR_RigidBody, Float);
	OR_DECL_SHELL_ACCESSOR_FUNC(IBody,			OR_RigidBody, Matrix3x3);
	OR_DECL_SHELL_ACCESSOR_FUNC(GravityCenter,	OR_RigidBody, Vector3D);
	OR_DECL_SHELL_ACCESSOR_FUNC(Bounce,			OR_RigidBody, Float);
	OR_DECL_SHELL_ACCESSOR_FUNC(Friction,		OR_RigidBody, Float);
	OR_DECL_SHELL_ACCESSOR_FUNC(Position,		OR_RigidBody, Vector3D);
	OR_DECL_SHELL_ACCESSOR_FUNC(Rotation,		OR_RigidBody, Quaternion);
	OR_DECL_SHELL_ACCESSOR_FUNC(P,				OR_RigidBody, Vector3D);
	OR_DECL_SHELL_ACCESSOR_FUNC(L,				OR_RigidBody, Vector3D);
	OR_DECL_SHELL_GET_PRINT_FUNC(IWorld,		OR_RigidBody, Matrix3x3);
	OR_DECL_SHELL_ACCESSOR_FUNC(Speed,			OR_RigidBody, Vector3D);
	OR_DECL_SHELL_ACCESSOR_FUNC(Omega,			OR_RigidBody, Vector3D);
	OR_DECL_SHELL_GET_PRINT_FUNC(WorldToBody,	OR_RigidBody, Matrix4x4);
	OR_DECL_SHELL_GET_PRINT_FUNC(WorldToBodyOld,OR_RigidBody, Matrix4x4);

	OR_DECL_SHELL_GET_PRINT_FUNC(RotationMatrix,		OR_RigidBody, Matrix3x3);

	OR_DECL_SHELL_GET_PRINT_FUNC(ForceAccumulator,			OR_RigidBody, Vector3D);
	OR_DECL_SHELL_GET_PRINT_FUNC(TorqueAccumulator,			OR_RigidBody, Vector3D);
	OR_DECL_SHELL_GET_PRINT_FUNC(ForceImpulseAccumulator,	OR_RigidBody, Vector3D);
	OR_DECL_SHELL_GET_PRINT_FUNC(TorqueImpulseAccumulator,	OR_RigidBody, Vector3D);
    //@}

private:

	/** the object that is the support of this rigid body */
	OR_Object* pObject_;

    //-------------------------------------------------------------------------
    /** \name constant quantities */
    //-------------------------------------------------------------------------
    //@{
	/** the mass of the object */
	OR_Float rMass_;
	/** the inertia matrix in body space */
	OR_Matrix3x3 IBody_;
	/** inverse of the inertia matrix in body space */
	OR_Matrix3x3 IBodyInv_;
	/** the center of gravity, in body frame */
	OR_Vector3D GravityCenter_;
	/** bouncing coef */
	OR_Float rBounce_;
	/** friction coef */
	OR_Float rFriction_;
    //@}

    //-------------------------------------------------------------------------
    /** \name state variables */
    //-------------------------------------------------------------------------
    //@{
	/** position of the object, in world coordinates */
	OR_Vector3D Pos_;
	/** rotation of the object in world coordinates, with no translations */
	OR_Quaternion Rot_;
	/** quantity of move of the object (ie. p=m*v), in world coordinates */
	OR_Vector3D P_;
	/** linear momentum (ie. omega=I*L) */
	OR_Vector3D L_;
    //@}

    //-------------------------------------------------------------------------
    /** \name auxiliary variables */
    //-------------------------------------------------------------------------
    //@{
	/** the matrix of rotation of the object (ie. matrix version of the quaternion ) */
	OR_Matrix3x3 RotMatrix_;
	/** the inertia matrix in \b world space : Iworld = Rotation*Ibody*transp(Rotation) */
	OR_Matrix3x3 IWorld_;
	/** inverse of the inertia matrix in \b world space : Iworld = Rotation*Ibody*transp(Rotation) */
	OR_Matrix3x3 IWorldInv_;
	/** speed of the center of mass of the object : speed = p/m */
	OR_Vector3D Speed_;
	/** instantatnate rotation : omega=I*L */
	OR_Vector3D Omega_;

	/** transformation matrix (duplicate the information of the OR_Object matrix) */
	OR_Matrix4x4 WorldToBody_;
	/** previous transformation matrix (used for example for deflexion) */
	OR_Matrix4x4 WorldToBodyOld_;
    //@}

    //-------------------------------------------------------------------------
    /** \name accumulators */
    //-------------------------------------------------------------------------
    //@{
	/** forces acting on the object */
	OR_Vector3D ForceAccumulator_;
	/** torques acting on the object */
	OR_Vector3D TorqueAccumulator_;
	/** translation impulse acting on the object */
	OR_Vector3D ForceImpulseAccumulator_;
	/** rotztion impulse acting on the object */
	OR_Vector3D TorqueImpulseAccumulator_;
    //@}

    //-------------------------------------------------------------------------
    /** @name annex variables */
    //-------------------------------------------------------------------------
    //@{
	/** does the objet use physics computation at update */
	OR_Bool bUsePhysic_;
	/** an additional force manager, used to store forces specific to this object */
	OR_ForceManager* pForceManager_;
	/** the model that can will used for collision detection */
	OR_PhysicModel* pPhysicModel_;

	/** the ID used by the joint manager to store this rigid body */
	OR_U32 nJointID_;
    //@}

	//-------------------------------------------------------------------------
    /** @name RK4 specific datas */
    //-------------------------------------------------------------------------
    //@{
	/** RK4 accumulator for position integration */
	OR_Vector3D   RK4_Pos_Accumulator_;
	/** RK4 accumulator for rotation integration */
	OR_Quaternion RK4_Rot_Accumulator_;
	/** RK4 accumulator for quantity of movement integration */
	OR_Vector3D   RK4_P_Accumulator_;
	/** RK4 accumulator for linear momentum integration */
	OR_Vector3D   RK4_L_Accumulator_;

	/** position at current time */
	OR_Vector3D   Cur_Pos_;
	/** rotation at current time */
	OR_Quaternion Cur_Rot_;
	/** quantity of movement at current time */
	OR_Vector3D   Cur_P_;
	/** linear momentum at current time */
	OR_Vector3D   Cur_L_;
    //@}

};

typedef list<OR_RigidBody*>			T_RigidBodyList;
typedef T_RigidBodyList::iterator	IT_RigidBodyList;

typedef vector<OR_RigidBody*>		T_RigidBodyVector;
typedef T_RigidBodyVector::iterator	IT_RigidBodyVector;

} // End namespace OR

#ifdef OR_USE_INLINE
	#include "OR_RigidBody.inl"
#endif


#endif // __OR_RigidBody_h_

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























