//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

namespace OR {

/* get hierarchy parameters **************************************/
OR_INLINE
const OR_String& OR_Object::GetName() const
{
	return Name;
}


/*------------------------------------------------------------------------------
 * Name : OR_Object::GetName
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-12-02
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_String& OR_Object::GetName()
{
	return Name;
}



/* modify hierarchy parameters **************************************/
OR_INLINE
void OR_Object::SetName( const char* name)
{
	Name = OR_String(name);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::SetName
 *
 *  \param  name new name of the object.
 *  \author Gabriel Peyré 2001-11-22
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Object::SetName( const OR_String& name )
{
	Name = name;
}



/*------------------------------------------------------------------------------
 * Name : OR_Object::IsVisible
 *
 *  \return true if the object is visible, false if it is hidden
 *  \author Antoine Bouthors 2001-10-30
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Object::IsVisible() const
{
	return bIsVisible;
}


/*------------------------------------------------------------------------------
 * Name : OR_Object::SetVisible
 *
 *  \param  Visible The new state of the visible flag of the object
 *  \author Antoine Bouthors 2001-10-30
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Object::SetVisible( OR_Bool Visible )
{
	bIsVisible = Visible;
}


//-----------------------------------------------------------------------------
// Name: OR_Object::GetActivity
/**
*   @return is the object active or not ?
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Object::IsActive() const
{ 
	return bIsActive_; 
}

//-----------------------------------------------------------------------------
// Name: OR_Object::Disable
/**
*   @return previous activity 
*
*	Disable the object for rendering
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Object::Disable()
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = false; 
	return old;
}



//-----------------------------------------------------------------------------
// Name: OR_Object::Enable
/**
*   @return previous activity 
*
*	Enable the object for rendering
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Object::Enable()
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = true; 
	return old;
}

//-----------------------------------------------------------------------------
// Name: OR_Object::Toggle
/**
*   @return Current activity.
*
*	Toggel on/off the object for rendering.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Object::Toggle()
{
	bIsActive_=!bIsActive_; 
	return bIsActive_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::SetActivity
 *
 *  \param  Visible new visibility attribute.
 *  \return previous value.
 *  \author Gabriel Peyré 2001-11-22
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Object::SetActivity( OR_Bool bActive )
{
	OR_Bool bPrev = this->IsActive();
	bIsActive_ = bActive;

	return bPrev;
}


//-----------------------------------------------------------------------------
// Name: OR_Object::SetId
/**
*   @param  id The id of the object, ie. it's number in the scene graph.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Object::SetId(OR_U32 id)
{ 
	Id=id; 
}

//-----------------------------------------------------------------------------
// Name: OR_Object::GetId
/**
*   @return The id of the object, ie. it's number in the scene graph.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_U32 OR_Object::GetId()
{ 
	return Id; 
}


//-----------------------------------------------------------------------------
// Name: OR_Object::GetAbsoluteMatrix
/**
*   @return absolute transofmration matrix.
*
*	The absolute matrix is computed during the update of the scene graph or via physic computations.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Matrix4x4& OR_Object::GetAbsoluteMatrix()
{ 
	return AbsoluteMatrix; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object constructor
 *
 *  \return The relative matrix.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	The relative matrix transforms from father (in scene graph) frame to object frame.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix4x4& OR_Object::GetRelativeMatrix()
{
	return Matrix;
}

//-----------------------------------------------------------------------------
// Name: OR_Object::GetAbsolutePosition
/**
*   @return absolute position of the object.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Vector3D OR_Object::GetAbsolutePosition()		
{
	return AbsoluteMatrix.GetTranslation(); 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::GetAbsoluteRotation
 *
 *  \return the rotation matrix in world frame.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix3x3 OR_Object::GetAbsoluteRotation()
{
	return AbsoluteMatrix.GetRotation();
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::GetAnimationMatrix
 *
 *  \return The animation matrix.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	The animation matrix is pre-multiplied to the trasnformation matrix before rendering.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix4x4& OR_Object::GetAnimationMatrix()
{
	return AnimationMatrix;
}
/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::SetAnimationMatrix
 *
 *  \return The animation matrix.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	The animation matrix is pre-multiplied to the trasnformation matrix before rendering.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Object::SetAnimationMatrix(const OR_Matrix4x4& m)
{
	AnimationMatrix = m;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::GetOldAnimationMatrix
 *
 *  \return The previous animation matrix.
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix4x4& OR_Object::GetOldAnimationMatrix()
{
	return OldAnimationMatrix;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::GetRigidBody
 *
 *  \return The rigid body used to make physic computations.
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RigidBody* OR_Object::GetRigidBody()
{
	return pRigidBody_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::SetRigidBody
 *
 *  \param  RB The rigid body used to make physic computations.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	When physics computations are enable, the object use rigid body to compute its
 *	movements. Else, it use the scene graph and animations to compute its movement.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Object::SetRigidBody(OR_RigidBody& RB)
{
	pRigidBody_ = &RB;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::EnablePhysicCompution
 *
 *  \return OR_OK if there is a rigid body, OR_ERROR otherwise.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Enable the physic computation by the rigid body.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RETURN_CODE OR_Object::EnablePhysicCompution()
{
	if( pRigidBody_==NULL )
		return OR_ERROR;
	pRigidBody_->EnablePhysicComputations();
	return OR_OK;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::DisablePhysicCompution
 *
 *  \return OR_OK if there is a rigid body, OR_ERROR otherwise.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Disable the physic computation by the rigid body.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RETURN_CODE OR_Object::DisablePhysicCompution()
{
	if( pRigidBody_==NULL )
		return OR_ERROR;
	pRigidBody_->DisablePhysicComputations();
	return OR_OK;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::IsUsingPhysic
 *
 *  \return true if the object as a rigid body computing physics.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Note that computation of hysic by the rigid body can be turned off.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Object::IsUsingPhysic()
{
	if( pRigidBody_==NULL )
		return false;
	return pRigidBody_->IsUsingPhysic();
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::SetUsingPhysic
 *
 *  \return OR_OK if there is a rigid body, OR_ERROR otherwise.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Disable the physic computation by the rigid body.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RETURN_CODE OR_Object::SetUsingPhysic(OR_Bool bUsing)
{
	if( bUsing )
		return this->EnablePhysicCompution();
	else
		return this->DisablePhysicCompution();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::SetRelativeMatrix
 *
 *  \param  m the new relative matrix
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Object::SetRelativeMatrix(OR_Matrix4x4& m)
{
	Matrix = m;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::SetAbsoluteMatrix
 *
 *  \param  m absolute matrix
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Object::SetAbsoluteMatrix(const OR_Matrix4x4& m)
{
	AbsoluteMatrix = m;
}

} // End namespace OR
