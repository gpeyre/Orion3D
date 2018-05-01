
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_WrapperLUA.h
 *  \brief definOR_I32ion for class OR_WrapperLUA
 *  \author Gabriel Peyré 2001-08-30
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_WrapperLUA_h_
#define __OR_WrapperLUA_h_

#include "OR_LUA_Config.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "luadebug.h"
}

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_WrapperLUA
 *  \brief  A basic wrapper for \b LUA scripting langage.
 *  \author Gabriel Peyré 2001-08-30
 *  
 *	More information on <a href="http://www.tecgraf.puc-rio.br/lua/">\b LUA hompage</a>.
 *
 *	\example lua_test/main.cpp
 */ 
/*------------------------------------------------------------------------------*/

class OR_WrapperLUA
{

public:

    OR_WrapperLUA();
    virtual ~OR_WrapperLUA();

	//-------------------------------------------------------------------------
    /** \name accessors  */
    //-------------------------------------------------------------------------
    //@{
	lua_State* GetState();
    //@}

    //-------------------------------------------------------------------------
    /** \name code execution */
    //-------------------------------------------------------------------------
    //@{
	OR_I32 DoFile(const char* pFileName);
	OR_I32 DoString(const char* pString);
    //@}

	//-------------------------------------------------------------------------
	/** \name creation of variables */
	//-------------------------------------------------------------------------
	//@{
	void RegisterFloat(OR_Float val, const char* name);
	void RegisterUserData(OR_UserData val, const char* name);
	void RegisterFunction(lua_CFunction val, const char* name);
	void RegisterString(const char* val, const char* name);
	void RegisterFunc(lua_CFunction pFunc, const char* name);

	void UnRegisterVariable(const char* name);
	void UnRegisterFunc(const char* name);
	//@}

	//-------------------------------------------------------------------------
	/** \name Test of \b LUA variable type */
	//-------------------------------------------------------------------------
	//@{
	OR_Bool IsFloat(const char* name);
	OR_Bool IsUserData(const char* name);
	OR_Bool IsFunction(const char* name);
	OR_Bool IsString(const char* name);
	//@}	

    //-------------------------------------------------------------------------
    /** \name C functions management */
    //-------------------------------------------------------------------------
    //@{
	OR_U32 GetNbrArg();
    //@}

	//-------------------------------------------------------------------------
    /** \name Hook management and debugging */
    //-------------------------------------------------------------------------
    //@{
	void SetLineHook(lua_Hook pFunc);
	void SetCallHook(lua_Hook pFunc);
	void GetDebugInfo(lua_Debug* pDebg);
    //@}

	//-------------------------------------------------------------------------
    /** \name Error Management. */
    //-------------------------------------------------------------------------
    //@{
	bool GetError();
	const char* GetErrorString();
    //@}

private:

	/** store all LUA global variable for this wrapper */
	lua_State *pState_;
	/** eventual errors during last parsing */
	int nError_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_WrapperLUA.inl"
#endif


#endif // __OR_WrapperLUA_h_

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

