/*----------------------------------------------------------*/
/*                      OR_Object.cpp                       */
/*----------------------------------------------------------*/
/*	implementation of class OR_Object                       */
/*----------------------------------------------------------*/

#include "../stdafx.h"
#include "../configuration/OR_Config.h"
#include "OR_Object.h"
#include "OR_Gizmo.h"

#ifndef OR_USE_INLINE
	#include "OR_Object.inl"
#endif

namespace OR
{
	
/*----------------------------------------------------------*/
/*						class OR_Object						*/
/*----------------------------------------------------------*/
/*			basic class for each 3D object					*/
/*----------------------------------------------------------*/

OR_Object::OR_Object()
:	OR_SmartCounter		(),
	OR_ShellObject_ABC(),
	bIsActive_			( true ),
	bIsSkinningBone_	( false ),
	Id					( -1 ),
	Name				( "undefined" )
{
	/* for the moment, we dosen't use physics computations */
	pRigidBody_ = NULL;
	/* default hierarchy parameters */
	Target = NULL;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object destructor
 *
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Check that no object is still referencing the object.
 */ 
/*------------------------------------------------------------------------------*/
OR_Object::~OR_Object()
{
	/* NOTHING */
}

void OR_Object::Translate(OR_Coord_XYZW axe, OR_Float val)
{
	Matrix.Translate(axe, val);
}

void OR_Object::Translate(const OR_Vector3D& vect)
{
	Matrix+=vect;
}


void OR_Object::Rotate(OR_Coord_XYZW axe, OR_Float r)
{
	Matrix.Rotate(axe, r);
}

void OR_Object::Rotate(OR_Float r)
{
	Matrix.RotateZ(r);
}

void OR_Object::Posit(const OR_Vector3D& pos)
{
	Matrix.SetTranslation(pos);
}

OR_Vector3D OR_Object::GetRelativePosition()
{	
	return Matrix.GetTranslation();
}

OR_Float* OR_Object::GetRelativePositionPtr()
{	
	return Matrix.GetTranslationPtr();
}

OR_Float* OR_Object::GetAbsolutePositionPtr()
{
	return AbsoluteMatrix.GetTranslationPtr();
}

/* absolute matrix modifications : for animation use ***************/
void OR_Object::TranslateAbsolute(const OR_Vector3D& v)
{
	AbsoluteMatrix.Translate(v);
	if(pRigidBody_!=NULL)
		pRigidBody_->GetPosition() += v;
}

void OR_Object::TranslateAbsolute(OR_Coord_XYZW axe, OR_Float v)
{
	AbsoluteMatrix.Translate(axe, v);
	if(pRigidBody_!=NULL)
		pRigidBody_->GetPosition()[axe] += v;
}

void OR_Object::RotateAbsolute(const OR_Matrix4x4& m)
{
	AbsoluteMatrix=m*AbsoluteMatrix;
}

void OR_Object::ScaleAbsolute(const OR_Vector3D& v)
{
	AbsoluteMatrix.AutoScale(v);
}

void OR_Object::ScaleAbsolute(OR_Coord_XYZW axe, OR_Float v)
{
	AbsoluteMatrix.AutoScale(axe, v);
}

/* animation matrix ***************************************************/
OR_Float* OR_Object::GetAnimationPositionPtr()
{
	return AnimationMatrix.GetTranslationPtr();
}

OR_Vector3D OR_Object::GetAnimationPosition()
{
	return AnimationMatrix.GetTranslation();
}

void OR_Object::TranslateAnimation(const OR_Vector3D& v)
{
	AnimationMatrix.Translate(v);
}

void OR_Object::TranslateAnimation(OR_Coord_XYZW axe, OR_Float v)
{
	AnimationMatrix.Translate(axe, v);
}

void OR_Object::RotateAnimation(const OR_Matrix3x3& m)
{
	AnimationMatrix = m*AnimationMatrix;
}

void OR_Object::ScaleAnimation(const OR_Vector3D& v)
{
	AnimationMatrix.AutoScale(v);
}

void OR_Object::ScaleAnimation(OR_Coord_XYZW axe, OR_Float v)
{
	AnimationMatrix.AutoScale(axe, v);
}


/* virtual methods **************************************************/
void OR_Object::Put()
{
	OR_Maths::MultiplyCurrentModelView( Matrix );
}

void OR_Object::Update()
{
	/* compute the animation matrix */
	OR_Maths::MultiplyCurrentModelView( Matrix );
	OR_Maths::MultiplyCurrentModelView( AnimationMatrix );

	/* compute the absolute matrix */
	if( pRigidBody_==NULL )
		OR_Maths::GetCurrentModelView( AbsoluteMatrix );
	else
		AbsoluteMatrix = pRigidBody_->GetWorldToBody();

	/* reset the animation matrix */
#ifdef OR_DRAW_Trajectories
	/* todo : see if we can skip that */
	OldAnimationMatrix=AnimationMatrix;
#endif

	AnimationMatrix.LoadIdentity();

}

OR_Object* OR_Object::GetTarget()
{
	return Target;

}

/*------------------------	------------------------------------------------------
 * Name : OR_Object::SetIsSkinningBone
 *
 *  \param  IsSkinningBone_ Is the object used as a bone for skining ?
 *  \author Antoine Bouthors 2001-07-02
 *------------------------------------------------------------------------------*/
void OR_Object::SetIsSkinningBone(OR_Bool IsSkinningBone)
{
	this->bIsSkinningBone_ = IsSkinningBone;
}


/*------------------------------------------------------------------------------
 * Name : OR_Object::GetIsSkinningBone
 *
 *  \return Is the object used as a bone for skining ?
 *  \author Antoine Bouthors 2001-07-02
 *------------------------------------------------------------------------------*/
OR_Bool OR_Object::IsSkinningBone()
{
	return this->bIsSkinningBone_;
}


void OR_Object::SetTarget(OR_Object* target)
{
	Target= target;
}

/* serialization methods ***************************************/
void OR_Object::BuildFromFile( OR_File& file )
{
	file >> Matrix
		 >> Name
		 >> TargetId
		 >> bIsVisible;
}

void OR_Object::BuildToFile( OR_File& file )
{
	file << Matrix
		 << Name;

	OR_U32 id = -1;
	if( Target!=NULL ) 
		id=Target->GetId();
	file << id;
	file << bIsVisible;
}

//-----------------------------------------------------------------------------
// Name: OR_Object::PostExportPass
/**
*	Used to set up the target once the export is done. The object has
*	to do a look up in ObjectList using it's id number to set the target.
*	If Id==0, that mean there is no target
*/
///	\author Gabriel Peyré 2001-08-30
//-----------------------------------------------------------------------------
void OR_Object::PostExportPass()
{
	if( (TargetId>=0) && (TargetId<OR_Globals::GetNbrObjectImported()) )
		SetTarget( OR_Globals::GetImportedObject(TargetId) );
	else 
		SetTarget( NULL );
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Object::BuildSonList(T_ShellObjectList& ShellSonList)
{
	if( this->GetTarget()!=NULL )
		OR_ADD_SHELL_SON(ShellSonList, *this->GetTarget(), OR_String("target_") + this->GetTarget()->GetName() );
	if( this->GetRigidBody()!=NULL )
		OR_ADD_SHELL_SON(ShellSonList, *this->GetRigidBody(), OR_String("rigid_body") );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Object::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Name);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Id);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Visibility);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Activity);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, IsSkinningBone);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, UsingPhysic);

	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, RelativeMatrix);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, AbsoluteMatrix);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, AnimationMatrix);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Position);

	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, Type);
}

} // namespace OR

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
///////////////////////////////////////////////////////////////////////////////
