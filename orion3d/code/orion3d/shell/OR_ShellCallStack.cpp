/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellCallStack.cpp
 *  \brief Definition of class \c OR_ShellCallStack
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ShellCallStack.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ShellCallStack.h"

#ifndef OR_USE_INLINE
	    #include "OR_ShellCallStack.inl"
#endif

using namespace OR;



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentFloat
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentFloat(OR_Float& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	if( !lua_isnumber(pState_, nPlace) )
		return false;

	val = lua_tonumber(pState_, nPlace);	

	return true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentBool
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentBool(OR_Bool& val, OR_U32 nPlace)
{
	OR_Float fVal;
	OR_Bool bTest = this->AccessArgumentFloat(fVal, nPlace);
	if( !bTest )
		return false;
	if( fVal<0.5f )
		val = false;
	else
		val = true;

	return true;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentUserData
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentUserData(OR_UserData& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	if( !lua_isuserdata(pState_, nPlace) )
		return false;
	
	val = lua_touserdata(pState_, nPlace);
	
	return true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentString
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentString(OR_String& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	if( !lua_isstring(pState_, nPlace) )
		return false;
	
	OR_I32 nStrLength = lua_strlen(pState_, nPlace);
	OR_ASSERT( nStrLength>=0 );
	val.clear();
	val = OR_String(lua_tostring(pState_, nPlace), 0, nStrLength);
	
	return true;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentFunc
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentFunc(T_ShellFunc& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	if( !lua_isfunction(pState_, nPlace) )
		return false;
	
	val = lua_tocfunction(pState_, nPlace);	
	
	return true;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentU32
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentU32(OR_U32& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	if( !lua_isnumber(pState_, nPlace) )
		return false;

	val = (OR_U32) lua_tonumber(pState_, nPlace);	

	return true;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentI32
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentI32(OR_I32& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	if( !lua_isnumber(pState_, nPlace) )
		return false;

	val = (OR_I32) lua_tonumber(pState_, nPlace);	

	return true;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentVector2D
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentVector2D(OR_Vector2D& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	/* get the four values from the stack */
	for( OR_U32 i=0; i<2; ++i )
	{
		if( !lua_isnumber(pState_, nPlace+i) )
			return false;
		else
			val[i] = (OR_Float) lua_tonumber(pState_, nPlace+i);	
	}

	return true;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentVector3D
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentVector3D(OR_Vector3D& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	/* get the four values from the stack */
	for( OR_U32 i=0; i<3; ++i )
	{
		if( !lua_isnumber(pState_, nPlace+i) )
			return false;
		else
			val[i] = (OR_Float) lua_tonumber(pState_, nPlace+i);	
	}

	return true;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentVector4D
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentVector4D(OR_Vector4D& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	/* get the four values from the stack */
	for( OR_U32 i=0; i<4; ++i )
	{
		if( !lua_isnumber(pState_, nPlace+i) )
			return false;
		else
			val[i] = (OR_Float) lua_tonumber(pState_, nPlace+i);	
	}

	return true;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentMatrix4x4
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentMatrix4x4(OR_Matrix4x4& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	/* get the four values from the stack */
	for( OR_U32 i=0; i<4; ++i )
	for( OR_U32 j=0; j<4; ++j )
	{
		if( !lua_isnumber(pState_, nPlace + j+4*(i) ) )
			return false;
		else
			val.SetData( i,j, (OR_Float) lua_tonumber(pState_, nPlace + j+4*(i)) );
	}

	return true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentMatrix3x3
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentMatrix3x3(OR_Matrix3x3& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	/* get the four values from the stack */
	for( OR_U32 i=0; i<3; ++i )
	for( OR_U32 j=0; j<3; ++j )
	{
		if( !lua_isnumber(pState_, nPlace + j+3*(i) ) )
			return false;
		else
			val.SetData( i,j, (OR_Float) lua_tonumber(pState_, nPlace + j+3*(i)) );
	}

	return true;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::AccessArgumentQuaternion
 *
 *  \param  val the returned value.
 *  \param  nPlace the place of the value in the stack.
 *  \return was the value of the correct type ?
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Search in the stack at a given position for a value.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellCallStack::AccessArgumentQuaternion(OR_Quaternion& val, OR_U32 nPlace)
{
	OR_ASSERT( pState_!=NULL );
	/* get the four values from the stack */
	if( !lua_isnumber(pState_, nPlace + 0 ) ||
		!lua_isnumber(pState_, nPlace + 1 ) ||
		!lua_isnumber(pState_, nPlace + 2 ) || 
		!lua_isnumber(pState_, nPlace + 3 ) )
		return false;
	else
	{
		val.SetW( (OR_Float) lua_tonumber(pState_, nPlace + 0) );
		val.SetX( (OR_Float) lua_tonumber(pState_, nPlace + 1) );
		val.SetY( (OR_Float) lua_tonumber(pState_, nPlace + 2) );
		val.SetZ( (OR_Float) lua_tonumber(pState_, nPlace + 3) );
	}
	

	return true;
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueFloat
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueFloat(const OR_Float& val)
{
	OR_ASSERT( pState_!=NULL );
	lua_pushnumber( pState_, val );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueBool
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-22
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueBool(const OR_Bool& val)
{
	if( val )
		this->ReturnValueFloat( 1 );
	else
		this->ReturnValueFloat( 0 );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueUserData
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueUserData(const OR_UserData& val)
{
	OR_ASSERT( pState_!=NULL );
	lua_pushuserdata(pState_, val );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueString
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueString(const OR_String& val)
{
	OR_ASSERT( pState_!=NULL );
	lua_pushlstring( pState_, val.const_val(), val.length() );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueFunc
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueFunc(const T_ShellFunc& val)
{
	OR_ASSERT( pState_!=NULL );
	lua_pushcfunction( pState_, val );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueU32
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueU32(const OR_U32& val)
{
	OR_ASSERT( pState_!=NULL );
	lua_pushnumber( pState_, val );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueI32
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueI32(const OR_I32& val)
{
	OR_ASSERT( pState_!=NULL );
	lua_pushnumber( pState_, val );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueVector2D
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueVector2D(const OR_Vector2D& val)
{
	OR_ASSERT( pState_!=NULL );
	for( OR_U32 i=0; i<2; ++i )
		lua_pushnumber( pState_, val.GetCoord()[i] );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueVector3D
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueVector3D(const OR_Vector3D& val)
{
	OR_ASSERT( pState_!=NULL );
	for( OR_U32 i=0; i<3; ++i )
		lua_pushnumber( pState_, val.GetCoord()[i] );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueVector4D
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueVector4D(const OR_Vector4D& val)
{
	OR_ASSERT( pState_!=NULL );
	for( OR_U32 i=0; i<4; ++i )
		lua_pushnumber( pState_, val.GetCoord()[i] );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueMatrix3x3
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueMatrix3x3(const OR_Matrix3x3& val)
{
	OR_ASSERT( pState_!=NULL );
	for( OR_U32 i=0; i<3; ++i )
	for( OR_U32 j=0; j<3; ++j )
		lua_pushnumber( pState_, val.GetData(i,j) );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueMatrix4x4
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueMatrix4x4(const OR_Matrix4x4& val)
{
	OR_ASSERT( pState_!=NULL );
	for( OR_U32 i=0; i<4; ++i )
	for( OR_U32 j=0; j<4; ++j )
		lua_pushnumber( pState_, val.GetData(i,j) );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::ReturnValueQuaternion
 *
 *  \param  val the value to return.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	push a value in the stack as a return value for the function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellCallStack::ReturnValueQuaternion(const OR_Quaternion& val)
{
	OR_ASSERT( pState_!=NULL );

	lua_pushnumber( pState_, val.GetW() );
	lua_pushnumber( pState_, val.GetX() );
	lua_pushnumber( pState_, val.GetY() );
	lua_pushnumber( pState_, val.GetZ() );
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack::GetNbrArg
 *
 *  \return number of arguments in the stack.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_U32 OR_ShellCallStack::GetNbrArg()
{
	return lua_gettop( pState_ );
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

