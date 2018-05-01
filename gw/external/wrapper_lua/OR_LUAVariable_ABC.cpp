/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_LUAVariable_ABC.cpp
 *  \brief  Definition of class \c OR_LUAVariable_ABC
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef OR_SCCSID
    static const char* sccsid = "@(#) OR_LUAVariable_ABC.cpp(c) Gabriel Peyré & Antoine Bouthors2002";
#endif // OR_SCCSID

#include "stdafx.h"
#include "OR_LUAVariable_ABC.h"

using namespace OR;

/*------------------------------------------------------------------------------*/
// Name : OR_LUAVariable_ABC constructor
/**
 *  \param  aName [char*] The name of the variable
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
OR_LUAVariable_ABC::OR_LUAVariable_ABC(const char* aName)
:	Name_	( aName ),
	bError_	( false )
{
	/* NOTHING  */
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUAVariable_ABC destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
OR_LUAVariable_ABC::~OR_LUAVariable_ABC()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUAVariable_ABC::GetError
/**
 *  \return [OR_Bool] Error or not ?
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 * 
 *  Set to true if an error occured during last update of the 
 *  variable.
 */
/*------------------------------------------------------------------------------*/
OR_Bool OR_LUAVariable_ABC::GetError()
{
	return bError_;
}

/*------------------------------------------------------------------------------*/
// Name : OR_LUAVariable_ABC::GetTopStackType
/**
 *  \param  LUAWrapper [OR_WrapperLUA&] The current wrapper
 *  \return [T_LUA_Type] The type.
 *  \author Gabriel Peyré
 *  \date   11-18-2002
 * 
 *  Get the type of the element placed on the top of the stack.
 */
/*------------------------------------------------------------------------------*/
T_LUA_Type OR_LUAVariable_ABC::GetTopStackType(OR_WrapperLUA& LUAWrapper)
{
	lua_State* pState = LUAWrapper.GetState();
	OR_ASSERT(pState!=NULL);
	if( lua_isnumber(pState, -1) )
		return OR_LUA_FLOAT;
	if( lua_isstring(pState, -1) )
		return OR_LUA_STRING;
	if( lua_istable(pState, -1) )
	{
		/* this is the complex case, because we have 2 OR_LUA type possible 
		   We have to check if the 1st 'key' is a string or not. */
		lua_pushnil( pState );
		if( lua_next(pState, -2)!=0 )
		{
			/* check the first 'key' */
			if( lua_isstring(pState, -2) )
			{
				lua_pop(pState, 2);
				return OR_LUA_TABLE;
			}
			else
			{
				lua_pop(pState, 2);	// pop 'key' and 'value'
				return OR_LUA_ARRAY;
			}
		}
		else
		{
			/* the array seems to be empty */
			return OR_LUA_ARRAY;
		}
	}
	return OR_LUA_UNDEFINED;
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
