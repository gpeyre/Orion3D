/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_LUA_Array.cpp
 *  \brief  Definition of class \c OR_LUA_Array
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef OR_SCCSID
    static const char* sccsid = "@(#) OR_LUA_Array.cpp(c) Gabriel Peyré & Antoine Bouthors2002";
#endif // OR_SCCSID

#include "stdafx.h"
#include "OR_LUA_Array.h"

using namespace OR;

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Array constructor
/**
 *  \param  aName [char*] Name.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
OR_LUA_Array::OR_LUA_Array(const char* aName)
:	OR_LUAVariable_ABC	(aName),
	nSize_				( 0 )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Array::virtual ~OR_LUA_Array
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
OR_LUA_Array::~OR_LUA_Array()
{
	/* delete the variables */
	for( IT_LUAVariableVector it=VariableVector_.begin(); it!=VariableVector_.end(); ++it )
		OR_DELETE(*it);
	VariableVector_.clear();

}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Array::GetFromLUA
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Retrieve the value.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_Array::GetFromLUA(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT( pState!=NULL );

	/* clean the previous vector */
	for( IT_LUAVariableVector it=VariableVector_.begin(); it!=VariableVector_.end(); ++it )
		OR_DELETE(*it);
	VariableVector_.clear();

	lua_getglobal(pState, Name_.c_str());
	this->GetFromLUAStack( LUAWrapper );
	lua_pop(pState, 1);
}


/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Array::SetToLUA
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Give the new value to LUA.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_Array::SetToLUA(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT( pState!=NULL );
	/* check if the variable already exists */
	lua_getglobal(pState, Name_.c_str());
	if( !lua_istable(pState, -1) )
	{
		bError_ = true;
		lua_pop(pState, 1);
		return;
	}
	/* set the value */
	this->SetToLUAStack( LUAWrapper );
	lua_setglobal(pState, Name_.c_str());
	bError_ = false;
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Array::GetArray
/**
 *  \return [T_LUAVariableVector*] The array.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  Get an array containing the list of the varialbes.
 */
/*------------------------------------------------------------------------------*/
T_LUAVariableVector& OR_LUA_Array::GetArray()
{
	return VariableVector_;
}


/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Array::GetFromLUAStack
/**
 *  \param  LUAWrapper [OR_WrapperLUA&] The LUA wrapper containting the stack.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  GetThe value directly from the stack. Use this function when you have put 
 *	a value on the stack.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_Array::GetFromLUAStack(OR_WrapperLUA& LUAWrapper)
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
		nSize_ = lua_getn(pState, -1);
		if( nSize_<=0 )
		{
			bError_ = true;
			lua_pop(pState, 1);

			OR_LUA_CHECK_STACK_END(pState);
			return;
		}
		char* new_name;
		new_name = new char[ Name_.size() + 10 ];
		for( OR_U32 i=1; i<=nSize_; ++i )
		{
			/* create a new name */
			sprintf(new_name, "%s_%lu", Name_.c_str(), i);
			/* push the i_th element of the array on the stack */
			lua_rawgeti( pState, -1, i );
			OR_LUAVariable_ABC* pVar = NULL;
			switch( OR_LUAVariable_ABC::GetTopStackType(LUAWrapper) ) 
			{
			case OR_LUA_FLOAT:
				pVar = new OR_LUA_Float( new_name );
				pVar->GetFromLUAStack( LUAWrapper );
				break;
			case OR_LUA_STRING:
				pVar = new OR_LUA_String( new_name );
				pVar->GetFromLUAStack( LUAWrapper );
				break;
			case OR_LUA_ARRAY:
				pVar = new OR_LUA_Array( new_name );
				pVar->GetFromLUAStack( LUAWrapper );
				break;
			case OR_LUA_TABLE:
				pVar = new OR_LUA_Table( new_name );
				pVar->GetFromLUAStack( LUAWrapper );
				break;
			default:
				bError_ = true;
				lua_pop(pState, 1);

				OR_LUA_CHECK_STACK_END(pState);	
				return;
				break;
			}
			lua_pop(pState, 1);	// pop the value that was pushed by lua_rawgeti
			VariableVector_.push_back( pVar );
		}
		OR_DELETEARRAY(new_name);
		bError_ = false;
	}
	OR_LUA_CHECK_STACK_END(pState);	
}


/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Array::SetToLUAStack
/**
 *  \param  LUAWrapper [OR_WrapperLUA&] The wrapper containing the stack.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  Simply push the value on the stack.
 */
/*------------------------------------------------------------------------------*/
void OR_LUA_Array::SetToLUAStack(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT( pState!=NULL );
	OR_LUA_CHECK_STACK_START(pState);	

	nSize_ = lua_getn(pState, -1);
	if( nSize_<=0 )
	{
		bError_ = true;
		lua_pop(pState, 1);

		OR_LUA_CHECK_STACK_END(pState);	
		return;
	}

	OR_U32 i=1;		// in LUA, table starts at 1.
	for( IT_LUAVariableVector it=VariableVector_.begin(); it!=VariableVector_.end(); ++it )
	{
		OR_LUAVariable_ABC* pVar = *it;
		OR_ASSERT( pVar!=NULL );
		pVar->SetToLUAStack( LUAWrapper );
		/* set the ith element of the table with value on top of the stack */
		lua_rawseti( pState, -2, i );
		i++;
	}

	OR_LUA_CHECK_STACK_END(pState);	
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUA_Array::GetType
/**
 *  \return [T_LUA_Type] The type.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  Get the type of the variable.
 */
/*------------------------------------------------------------------------------*/
T_LUA_Type OR_LUA_Array::GetType()
{
	return OR_LUA_ARRAY;
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
