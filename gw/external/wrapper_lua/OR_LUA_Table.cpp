/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_LUA_Table.cpp
 *  \brief  Definition of class \c OR_LUA_Table
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef OR_SCCSID
    static const char* sccsid = "@(#) OR_LUA_Table.cpp(c) Gabriel Peyré & Antoine Bouthors2002";
#endif // OR_SCCSID

#include "stdafx.h"
#include "OR_LUA_Table.h"
#include "OR_LUA_Array.h"

using namespace OR;

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Table constructor
/**
 *  \param  aName [char*] Name.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
OR_LUA_Table::OR_LUA_Table(const char* aName)
:	OR_LUAVariable_ABC(aName)
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Table::virtual ~OR_LUA_Table
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
OR_LUA_Table::~OR_LUA_Table()
{
	/* delete variables */
	for( IT_LUAVariableMap it=Map_.begin(); it!=Map_.end(); ++it )
		OR_DELETE(it->second);
	Map_.clear();
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Table::GetFromLUA
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Retrieve the value.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_Table::GetFromLUA(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT( pState!=NULL );

	/* delete previous variables */
	for( IT_LUAVariableMap it=Map_.begin(); it!=Map_.end(); ++it )
		OR_DELETE(it->second);
	Map_.clear();

	lua_getglobal(pState, Name_.c_str());
	this->GetFromLUAStack( LUAWrapper );
	lua_pop(pState, 1);
}


/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Table::SetToLUA
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Give the new value to LUA.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_Table::SetToLUA(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT( pState!=NULL );
	OR_LUA_CHECK_STACK_START(pState);	

	/* check if the variable already exists */
	lua_getglobal(pState, Name_.c_str());
	if( !lua_istable(pState, -1) )
	{
		bError_ = true;
		lua_pop(pState, 1);

		OR_LUA_CHECK_STACK_END(pState);	
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
// Name : OR_LUA_Table::GetTable
/**
 *  \return [T_LUAVariableMap&] The map.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  Get the map containing the variables.
 */
/*------------------------------------------------------------------------------*/
T_LUAVariableMap& OR_LUA_Table::GetTable()
{
	return Map_;
}


/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Table::GetFromLUAStack
/**
 *  \param  LUAWrapper [OR_WrapperLUA&] The LUA wrapper containting the stack.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  GetThe value directly from the stack. Use this function when you have put 
 *	a value on the stack.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_Table::GetFromLUAStack(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT( pState!=NULL );
	OR_LUA_CHECK_STACK_START(pState);	

	if( !lua_istable(pState, -1) )
	{
		bError_ = true;
	}
	else
	{
		char* new_name;
		new_name = new char[ Name_.size() + 10 ];

		lua_pushnil( pState );
		OR_U32 i=1;
		std::string key;
		while( lua_next(pState, -2)!=0 ) 
		{
			/* 'key' is at index -2 and value is at index -1 */
			if( lua_isstring(pState, -2) )
			{
				size_t nKeyLength = lua_strlen( pState, -2 );
				key = string( lua_tostring(pState, -2), nKeyLength );
			}
			else
			{
				/* problem : the key is not a string ... */
                sprintf(new_name, "%s_%lu", Name_.c_str(), i);
				key = string( new_name );
			}
			/* now, retrieve the value */
			OR_LUAVariable_ABC* pVar = NULL;
			switch( OR_LUAVariable_ABC::GetTopStackType(LUAWrapper) ) 
			{
			case OR_LUA_FLOAT:
				pVar = new OR_LUA_Float( key.c_str() );
				pVar->GetFromLUAStack( LUAWrapper );
				break;
			case OR_LUA_STRING:
				pVar = new OR_LUA_String( key.c_str() );
				pVar->GetFromLUAStack( LUAWrapper );
				break;
			case OR_LUA_ARRAY:
				pVar = new OR_LUA_Array( key.c_str() );
				pVar->GetFromLUAStack( LUAWrapper );
				break;
			case OR_LUA_TABLE:
				pVar = new OR_LUA_Table( key.c_str() );
				pVar->GetFromLUAStack( LUAWrapper );
				break;
			default:
				bError_ = true;
				lua_pop(pState, 3);

				OR_LUA_CHECK_STACK_END(pState);	
				return;
				break;
			}
			i++;
			/* chek if the key doesn't exist ... */
			IT_LUAVariableMap it = Map_.find( key );
			if( it!=Map_.end() )
			{
				bError_ = true;
				lua_pop(pState, 2);

				OR_LUA_CHECK_STACK_END(pState);	
				return;
				break;
			}
			Map_[key] = pVar;
			/* pop only the value */
			lua_pop(pState, 1);
		}
		
		OR_DELETEARRAY(new_name);
		bError_ = false;
	}

	OR_LUA_CHECK_STACK_END(pState);	
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Table::SetToLUAStack
/**
 *  \param  LUAWrapper [OR_WrapperLUA&] The wrapper containing the stack.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  Simply push the value on the stack.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_Table::SetToLUAStack(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT( pState!=NULL );

	for( IT_LUAVariableMap it=Map_.begin(); it!=Map_.end(); ++it )
	{
		std::string key = it->first;
		OR_LUAVariable_ABC* pVar = it->second;
		OR_ASSERT( pVar!=NULL );
		/* push first the 'key', then the 'value' */
		lua_pushlstring( pState, key.c_str(), key.size() );
		pVar->SetToLUAStack( LUAWrapper );
		/* set the element of the table with 'key' at -2 and 'value' at -1 */
		lua_settable( pState, -3 );
	}
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Table::GetType
/**
 *  \return [T_LUA_Type] The type.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  Get the type of the variable.
 */
/*------------------------------------------------------------------------------*/
T_LUA_Type OR_LUA_Table::GetType()
{
	return OR_LUA_TABLE;
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Table::GetValue
/**
 *  \param  name [string&] The name of the subfield.
 *  \param  res [OR_Float&] Th return value. 0 if the sub field doesn't exist or is of wrond type.
 *  \return [OR_Bool] Was the acess successful ?
 *  \author Gabriel Peyré
 *  \date   11-19-2002
 * 
 *  Allow a direct access to a sub field of type \c float.
 */
/*------------------------------------------------------------------------------*/
OR_Bool OR_LUA_Table::GetValue( const string& name, OR_Float& res )
{
	IT_LUAVariableMap it = Map_.find( name );
	if( it!=Map_.end() )
	{
		OR_LUAVariable_ABC* pVar = it->second;
		if( pVar->GetType()==OR_LUA_FLOAT )
		{
			res = ((OR_LUA_Float*) pVar)->GetValue();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Table::GetValue
/**
 *  \param  name [string&] The name of the subfield.
 *  \param  res [OR_Float&] Th return value. 0 if the sub field doesn't exist or is of wrond type.
 *  \return [OR_Bool] Was the acess successful ?
 *  \author Gabriel Peyré
 *  \date   11-19-2002
 * 
 *  Allow a direct access to a sub field of type \c string.
 */
/*------------------------------------------------------------------------------*/
OR_Bool OR_LUA_Table::GetValue( const string& name, string& res )
{
	IT_LUAVariableMap it = Map_.find( name );
	if( it!=Map_.end() )
	{
		OR_LUAVariable_ABC* pVar = it->second;
		if( pVar->GetType()==OR_LUA_STRING )
		{
			res = ((OR_LUA_String*) pVar)->GetValue();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
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
