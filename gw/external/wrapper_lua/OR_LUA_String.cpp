/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_LUA_String.cpp
 *  \brief  Definition of class \c OR_LUA_String
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef OR_SCCSID
    static const char* sccsid = "@(#) OR_LUA_String.cpp(c) Gabriel Peyré & Antoine Bouthors2002";
#endif // OR_SCCSID

#include "stdafx.h"
#include "OR_LUA_String.h"

using namespace OR;

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_String constructor
/**
 *  \param  aName [char*] Name.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
OR_LUA_String::OR_LUA_String(const char* aName)
:	OR_LUAVariable_ABC(aName)
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_String::virtual ~OR_LUA_String
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
OR_LUA_String::~OR_LUA_String()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_String::GetFromLUA
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Retrieve the value.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_String::GetFromLUA(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_LUA_CHECK_STACK_START(pState);
	
	OR_ASSERT( pState!=NULL );
	lua_getglobal(pState, Name_.c_str());		// this push the value on the stack.
	this->GetFromLUAStack( LUAWrapper );
	lua_pop(pState, 1);

	OR_LUA_CHECK_STACK_END(pState);
}


/*------------------------------------------------------------------------------*/
// Name : OR_LUA_String::SetToLUA
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Give the new value to LUA.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_String::SetToLUA(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT( pState!=NULL );
	OR_LUA_CHECK_STACK_START(pState);	

	/* check validity of existing variable */
	lua_getglobal(pState, Name_.c_str());
	if( !lua_isstring(pState, -1) )
	{
		bError_ = true;
		lua_pop(pState, 1);
		return;
	}
	lua_pop(pState, 1);
	/* set the value */
	this->SetToLUAStack( LUAWrapper );
	lua_setglobal(pState, Name_.c_str());
	bError_ = false;

	OR_LUA_CHECK_STACK_END(pState);
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_String::SetValue
/**
 *  \param  rVal [OR_String] The new value.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Set the value to this wrapping class. 
 *	IMPORTANT : This doesn't give the value to LUA. You have to call \c SetToLUA.
 *	
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_String::SetValue(const string& rVal)
{
	rVal_ = rVal;
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_String::GetValue
/**
 *  \return [OR_String] The value.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Get the value hold by the class.
 *	IMPORTANT : This doesn't actually get the value from LUA.
 *	You have to call \c GetFromLUA first.
 */
/*------------------------------------------------------------------------------*/
const string& OR_LUA_String::GetValue()
{
	return rVal_;
}


/*------------------------------------------------------------------------------*/
// Name : OR_LUA_String::GetFromLUAStack
/**
 *  \param  LUAWrapper [OR_WrapperLUA&] The LUA wrapper containting the stack.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  GetThe value directly from the stack. Use this function when you have put 
 *	a value on the stack.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_String::GetFromLUAStack(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT( pState!=NULL );
	if( !lua_isstring(pState, -1) )
	{
		bError_ = true;
	}
	else
	{	
		bError_ = false;
		size_t nLength = lua_strlen( pState, -1 );
		rVal_ = string( lua_tostring(pState, -1), nLength );
	}
}


/*------------------------------------------------------------------------------*/
// Name : OR_LUA_String::SetToLUAStack
/**
 *  \param  LUAWrapper [OR_WrapperLUA&] The wrapper containing the stack.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  Simply push the value on the stack.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_String::SetToLUAStack(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();

	OR_ASSERT( pState!=NULL );
	lua_pushlstring( pState, rVal_.c_str(), rVal_.size() );
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_String::GetType
/**
 *  \return [T_LUA_Type] The type.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  Get the type of the variable.
 */
/*------------------------------------------------------------------------------*/
T_LUA_Type OR_LUA_String::GetType()
{
	return OR_LUA_STRING;
}

///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré & Antoine Bouthors
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
