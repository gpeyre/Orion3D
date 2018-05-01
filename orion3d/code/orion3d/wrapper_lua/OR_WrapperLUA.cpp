/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_WrapperLUA.cpp
 *  \brief implementation for class OR_WrapperLUA
 *  \author Gabriel Peyré 2001-08-30
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_WrapperLUA.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_WrapperLUA.h"
/* print a log for this project */
#include "../misc/OR_PrintBuildLog.h"

#ifndef OR_USE_INLINE
	#include "OR_WrapperLUA.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA constructor
 *
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Initialize \b LUA.
 */ 
/*------------------------------------------------------------------------------*/
OR_WrapperLUA::OR_WrapperLUA()
{
	/* create the state */	
	pState_ = lua_open(0);
	OR_ASSERT( pState_!=NULL );
	/* load the optional libs */
	lua_baselibopen(pState_);
	lua_iolibopen(pState_);
	lua_strlibopen(pState_);
	lua_mathlibopen(pState_);
	lua_dblibopen(pState_);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA destructor
 *
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Close the \b LUA state.
 */ 
/*------------------------------------------------------------------------------*/
OR_WrapperLUA::~OR_WrapperLUA()
{
	/* close the LUA state */
	lua_close(pState_);
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::RegisterFunc	
 *
 *  \param  pFunc the function to register.
 *  \param  name the name of the function.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
void OR_WrapperLUA::RegisterFunc(lua_CFunction pFunc, const char* name)
{
	OR_ASSERT( name!=NULL );
	OR_ASSERT( pFunc!=NULL );
	lua_register(this->GetState(), name, pFunc);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::UnRegisterFunc
 *
 *  \param  name name of the function to unregister.
 *  \return was the unregistrement a success ?
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
void OR_WrapperLUA::UnRegisterFunc(const char* name)
{	
	OR_ASSERT(name!=NULL);
	lua_register(this->GetState(), name, NULL);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::RegisterFloat
 *
 *  \param  val	 value of the new variable.
 *  \param  name name of the variable to create.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
void OR_WrapperLUA::RegisterFloat(OR_Float val, const char* name)
{
	OR_ASSERT(name!=NULL);
	lua_pushnumber( this->GetState(), val);
	lua_setglobal( this->GetState(), name );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::RegisterUserData
 *
 *  \param  val	 value of the new variable.
 *  \param  name name of the variable to create.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
void OR_WrapperLUA::RegisterUserData(OR_UserData val, const char* name)
{
	OR_ASSERT(name!=NULL);
	lua_pushuserdata( this->GetState(), val);
	lua_setglobal( this->GetState(), name );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::RegisterString
 *
 *  \param  val	 value of the new variable.
 *  \param  name name of the variable to create.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
void OR_WrapperLUA::RegisterString(const char* val, const char* name)
{
	OR_ASSERT(name!=NULL);
	OR_ASSERT(val!=NULL);
	lua_pushstring( this->GetState(), val);
	lua_setglobal( this->GetState(), name );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::UnRegisterVariable
 *
 *  \param  name name of the function to unregister.
 *  \return was the unregistrement a success ?
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
void OR_WrapperLUA::UnRegisterVariable(const char* name)
{	
	OR_ASSERT(name!=NULL);
	lua_register(this->GetState(), name, NULL);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::IsFloat
 *
 *  \param  name name of the function to unregister.
 *  \return Is the variable of given name of the right type ?
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_WrapperLUA::IsFloat(const char* name)
{
	lua_getglobal( this->GetState(), name );
	OR_I32 bTest = lua_isnumber( this->GetState(), 1 );
	lua_pop(this->GetState(),1);

	return bTest;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::IsUserData
 *
 *  \param  name name of the function to unregister.
 *  \return Is the variable of given name of the right type ?
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_WrapperLUA::IsUserData(const char* name)
{
	lua_getglobal( this->GetState(), name );
	OR_I32 bTest = lua_isuserdata( this->GetState(), 1 );
	lua_pop(this->GetState(),1);

	return bTest;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::IsFunction
 *
 *  \param  name name of the function to unregister.
 *  \return Is the variable of given name of the right type ?
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_WrapperLUA::IsFunction(const char* name)
{
	lua_getglobal( this->GetState(), name );
	OR_I32 bTest = lua_isfunction( this->GetState(), 1 );
	lua_pop(this->GetState(),1);

	return bTest;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::IsString
 *
 *  \param  name name of the function to unregister.
 *  \return Is the variable of given name of the right type ?
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_WrapperLUA::IsString(const char* name)
{
	lua_getglobal( this->GetState(), name );
	OR_I32 bTest = lua_isstring( this->GetState(), 1 );
	lua_pop(this->GetState(),1);

	return bTest;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_WrapperLUA::GetDebugInfo
 *
 *  \param  pDebg the debugging structure.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Fill in the \b LUA debug structure.
 */ 
/*------------------------------------------------------------------------------*/
void OR_WrapperLUA::GetDebugInfo(lua_Debug* pDebg)
{
	OR_ASSERT( pDebg!=NULL );
	lua_getinfo( this->GetState(), "l", pDebg);
	lua_getinfo( this->GetState(), "n", pDebg);
	lua_getinfo( this->GetState(), "u", pDebg);
//	lua_getinfo( this->GetState(), "S", pDebg);
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

