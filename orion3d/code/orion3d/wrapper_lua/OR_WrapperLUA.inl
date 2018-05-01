/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_WrapperLUA.inl
 *  \brief inlined methods for class OR_WrapperLUA
 *  \author Gabriel Peyré 2001-08-30
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_WrapperLUA.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::DoFile
 *
 *  \param  pFileName name of the file to execute.
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Execute the code from a file. Return the \b LUA error code.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_I32 OR_WrapperLUA::DoFile(const char* pFileName)
{
	OR_ASSERT( pFileName!=NULL );
	return lua_dofile(pState_, pFileName);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::DoString
 *
 *  \param  pString the string to execute.
 *  \return the \b LUA error code.
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Execute the code from a string.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_I32 OR_WrapperLUA::DoString(const char* pString)
{
	OR_ASSERT( pString!=NULL );
	return lua_dostring(pState_, pString);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::GetNbrArg
 *
 *  \return the number of arguments in the \b LUA callstack
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_WrapperLUA::GetNbrArg()
{
	return lua_gettop( this->GetState() );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::GetState
 *
 *  \return the \b LUA state.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
lua_State* OR_WrapperLUA::GetState()
{
	return pState_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::SetLineHook
 *
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Set a callback function called each time an end of line is reached.
 *	Simply pass a \c NULL pointer to disable it.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_WrapperLUA::SetLineHook(lua_Hook pFunc)
{
	lua_setlinehook( this->GetState(), pFunc );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::SetCallHook
 *
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Set a callback function called each time a function call is made.
 *	Simply pass a \c NULL pointer to disable it.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_WrapperLUA::SetCallHook(lua_Hook pFunc)
{
	lua_setcallhook( this->GetState(), pFunc );
}

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

