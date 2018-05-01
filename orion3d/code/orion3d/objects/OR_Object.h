/*----------------------------------------------------------*/
/*                          OR_Object                       */
/*----------------------------------------------------------*/
/*	definition of class OR_Object                           */
/*----------------------------------------------------------*/

/** \file 
	Contains the definition of an or_object, which is the base class for ALL
	3D objets stored in Orion3D hierarchy.
	\author Gabriel.
**/

#ifndef _OR_OBJECT_H_
#define _OR_OBJECT_H_

#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"
#include "../physic/OR_Force_ABC.h"
#include "../physic/OR_RigidBody.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_String.h"
#include "../utils/OR_File.h"
#include "../utils/OR_SmartCounter.h"
#include "../maths/OR_Maths.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"

namespace OR
{

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Object
 *  \brief  An object that can be store in the scene graph.
 *  \author Gabriel Peyré 2001-08-04
 *  
 *	All object in Orion3D (mesh, gizmo, camera, lights, ...) inherit from this class.
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_Object: public OR_Serializable, public OR_SmartCounter, public OR_ShellObject_ABC
{

public:

	/** constructor */
	OR_Object();
	/** destructor */
	virtual ~OR_Object();

    //-------------------------------------------------------------------------
    /** @name activity management */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool IsActive() const;
	OR_Bool Disable();
	OR_Bool Enable();
	OR_Bool Toggle();
	OR_Bool SetActivity( OR_Bool Visible );
	/** synonymous with \c IsActive() */
	OR_Bool GetActivity() const
	{ return this->IsActive(); }


	OR_Bool IsVisible() const;
	void SetVisible( OR_Bool Visible );
	/** synonymous with \c IsVisible() */
	OR_Bool GetVisibility() const
	{ return this->IsVisible(); }
	void SetVisibility( OR_Bool bVisible )
	{ this->SetVisible(bVisible); }
    //@}


    //-------------------------------------------------------------------------
    /** @name modify hierarchy parameters  */
    //-------------------------------------------------------------------------
    //@{
	/** set the object name */
	void SetName( const char* name );
	void SetName( const OR_String& name );
	/** get the object name */
	const OR_String& GetName() const;
	OR_String& GetName();
	/** set the object target */
	void SetTarget(OR_Object* target);
	/** set the object as being a skinning bone */
	void SetIsSkinningBone(OR_Bool IsSkinningBone);
	/** \return true if the object used as a skinning bone */
	OR_Bool IsSkinningBone();
	/** synonymous with IsSkinningBone */
	OR_Bool GetIsSkinningBone()
	{ return this->IsSkinningBone(); }

	/** set the object target */
	OR_Object* GetTarget();	
    //@}


    //-------------------------------------------------------------------------
    /** @name Id management  */
    //-------------------------------------------------------------------------
    //@{
	void SetId(OR_U32 id);
	OR_U32 GetId();
    //@}

    //-------------------------------------------------------------------------
    /** @name relative matrix */
    //-------------------------------------------------------------------------
    //@{
	/** get the relative matrix */
	OR_Matrix4x4& GetRelativeMatrix();	
	/** set the relative matrix */
	void          SetRelativeMatrix(OR_Matrix4x4& m);
	/** get the position in relative axes */
	OR_Vector3D GetRelativePosition();
	/** get the position in relative axes via a pointer */
	OR_Float* GetRelativePositionPtr();

	/** translate the object in local axes given a direction */
	virtual void Translate(OR_Coord_XYZW axe, OR_Float val);
	/** translate the object in local axes */
	virtual void Translate(const OR_Vector3D& vect);
	/** rotate the object on a given axis */
	virtual void Rotate(OR_Coord_XYZW axe, OR_Float r);
	/** rotate the object on Z axis */
	virtual void Rotate(OR_Float r);
	/** positionnate the object in local axes */
	virtual void Posit(const OR_Vector3D& pos);

	/** synonymous with posit */
	void		SetPosition(const OR_Vector3D& pos)
	{ this->Posit(pos); }
	/** synonymous with GetRelativePosition */
	OR_Vector3D GetPosition()
	{ return this->GetRelativePosition(); }
    //@}

    //-------------------------------------------------------------------------
    /** @name absolute matrix management */
    //-------------------------------------------------------------------------
    //@{
	OR_Matrix4x4&  GetAbsoluteMatrix();
	void           SetAbsoluteMatrix(const OR_Matrix4x4& m);
	/** get the position in absolute axes via a pointer */
	OR_Float* GetAbsolutePositionPtr();
	/** get the position in absolute axes */
	OR_Vector3D  GetAbsolutePosition();
	OR_Matrix3x3 GetAbsoluteRotation();
	/** translate the absolute matrix */
	void TranslateAbsolute(const OR_Vector3D& pos);
	/** translate the absolute matrix on one axe */
	void TranslateAbsolute(OR_Coord_XYZW axe, OR_Float v);
	/** multiply the absolute matrix by a rotation one */
	void RotateAbsolute(const OR_Matrix4x4& m);
	/** scale the absolute matrix */
	void ScaleAbsolute(const OR_Vector3D& pos);
	/** scale the absolute matrix on one axe */
	void ScaleAbsolute(OR_Coord_XYZW axe, OR_Float v);
    //@}

    //-------------------------------------------------------------------------
    /** @name animation matrix */
    //-------------------------------------------------------------------------
    //@{
	/** get the animation matrix */
	OR_Matrix4x4& GetAnimationMatrix();
	/** get the animation matrix */
	void SetAnimationMatrix(const OR_Matrix4x4& m);
	/** get the previous animation matrix */
	OR_Matrix4x4& GetOldAnimationMatrix();
	/** get the position via a pointer */
	OR_Float* GetAnimationPositionPtr();
	/** get the position axes */
	OR_Vector3D GetAnimationPosition();
	/** translate the animation matrix */
	void TranslateAnimation(const OR_Vector3D& v);
	/** translate the animation matrix on one axe */
	void TranslateAnimation(OR_Coord_XYZW axe, OR_Float v);
	/** multiply the animation matrix by a rotation one */
	void RotateAnimation(const OR_Matrix3x3& m);
	/** scale the animation matrix */
	void ScaleAnimation(const OR_Vector3D& pos);
	/** scale the animation matrix on one axe */
	void ScaleAnimation(OR_Coord_XYZW axe, OR_Float v);
    //@}

    //-------------------------------------------------------------------------
    /** \name Physic management */
    //-------------------------------------------------------------------------
    //@{
	OR_RigidBody*  GetRigidBody();
	void           SetRigidBody(OR_RigidBody& RB);
	OR_RETURN_CODE EnablePhysicCompution();
	OR_RETURN_CODE DisablePhysicCompution();
	OR_Bool		   IsUsingPhysic();
	OR_Bool		   GetUsingPhysic()
	{ return this->IsUsingPhysic(); }
	OR_RETURN_CODE SetUsingPhysic(OR_Bool bUsing);
    //@}

    //-------------------------------------------------------------------------
    /** \name access to shader datas [to ovberload by object having a shader] */
    //-------------------------------------------------------------------------
    //@{
	/** if possible, set the ambient */
	virtual void SetAmbient(OR_Vector3D v) {}
	/** if possible, set the ambient, on one component */
	virtual void SetAmbient(OR_Coord_RVBA comp, OR_Float val) {}
	/** if possible, set the diffuse  */
	virtual void SetDiffuse(OR_Vector3D v) {}
	/** if possible, set the diffuse, on one component */
	virtual void SetDiffuse(OR_Coord_RVBA comp, OR_Float val) {}
	/** if possible, set the specular */
	virtual void SetSpecular(OR_Vector3D v) {}
	/** if possible, set the specular, on one component */
	virtual void SetSpecular(OR_Coord_RVBA comp, OR_Float val) {}
	/** if possible, set the shine */
	virtual void SetShine(OR_Float v) {}
    //@}
	
    //-------------------------------------------------------------------------
    /** @name virtual methods */
    //-------------------------------------------------------------------------
    //@{
	/** virtual method : setup the model view matrix before rendering */
	virtual void Put();
	/** set the world-relative matrix */
	virtual void Update();	
	/** virtual method : render the object */
	virtual void Draw()=0;
	/** virtual method : get the real type of the object */
	virtual OR_Elements GetType()	{ return OR_UNDEFINED; }
    //@}

    //-------------------------------------------------------------------------
    /** @name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	/** used to set up the target once the export is done. The object has
		to do a look up in ObjectList using it's id number to set the target.
		If Id==0, that mean there is no target. */
	virtual void PostExportPass();
    //@}

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	
	OR_DECL_SHELL_ACCESSOR_FUNC(Name,		OR_Object, String);
	OR_DECL_SHELL_ACCESSOR_FUNC(Id,			OR_Object, U32);
	OR_DECL_SHELL_ACCESSOR_FUNC(Visibility,	OR_Object, Bool);
	OR_DECL_SHELL_ACCESSOR_FUNC(Activity,	OR_Object, Bool);
	OR_DECL_SHELL_ACCESSOR_FUNC(IsSkinningBone,	OR_Object, Bool);
	OR_DECL_SHELL_ACCESSOR_FUNC(UsingPhysic,	OR_Object, Bool);

	OR_DECL_SHELL_ACCESSOR_FUNC(RelativeMatrix,		OR_Object, Matrix4x4);
	OR_DECL_SHELL_ACCESSOR_FUNC(AbsoluteMatrix,		OR_Object, Matrix4x4);
	OR_DECL_SHELL_ACCESSOR_FUNC(AnimationMatrix,	OR_Object, Matrix4x4);
	OR_DECL_SHELL_ACCESSOR_FUNC(Position,			OR_Object, Vector3D);

	OR_DECL_SHELL_GET_PRINT_FUNC_ENUM(Type, OR_Object, Elements);
    //@}
	
protected:
	
    //-------------------------------------------------------------------------
    /** @name hierarchy parameters  */
    //-------------------------------------------------------------------------
    //@{
	/** name of the object */
	OR_String Name;
	/** target of the object */
	class OR_Object* Target;
	/** the Id of the target */
	OR_U32 TargetId;
	/** the Id (ie. place in the hierarchy tree) of the object */
	OR_U32 Id;
    //@}
	
	/** is this object used as a bone for skinning */
	OR_Bool bIsSkinningBone_;
	/** is the object active */
	OR_Bool bIsActive_;
	/** is the object visible */
	OR_Bool bIsVisible;
	
    //-------------------------------------------------------------------------
    /** @name transformation & animation matrix */
    //-------------------------------------------------------------------------
    //@{
	/** transformation matrix relative to parents axes */
	OR_Matrix4x4 Matrix;
	/** transformation matrix relative world axes */
	OR_Matrix4x4 AbsoluteMatrix;
	/** the matrix of the current animation */
	OR_Matrix4x4 AnimationMatrix;
	/** \todo : see if we can skip that 
		used only for trajectory display */
	OR_Matrix4x4 OldAnimationMatrix;
    //@}

    //-------------------------------------------------------------------------
    /** @name rigid body datas */
    //-------------------------------------------------------------------------
    //@{
	OR_RigidBody* pRigidBody_;
    //@}

};

/** List of OR_Object* */
typedef list<class OR_Object*> T_ObjectList;
/** iterator for List of OR_Object* */
typedef T_ObjectList::iterator IT_ObjectList;


} // namespace OR

#ifdef OR_USE_INLINE
	#include "OR_Object.inl"
#endif

#endif // _OR_OBJECT_H_

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
//////////////////////////////////////////////////////////////