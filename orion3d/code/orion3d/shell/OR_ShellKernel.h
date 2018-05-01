
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellKernel.h
 *  \brief Definition of class \c OR_ShellKernel
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ShellKernel_h_
#define __OR_ShellKernel_h_


#include "../configuration/OR_Config.h"
#include "OR_ShellObject_ABC.h"
#include "../wrapper_lua/OR_WrapperLUA.h"
#include "../utils/OR_StringTokenizer.h"
#include "../utils/OR_Serializable.h"

namespace OR {

/** function to be called when the user types 'quit'. If return!=0, don't exit */
typedef OR_U32 (*OR_Shell_Quit_Func)(void);

class OR_ShellConsole_ABC;
class OR_ShellObject_ABC;


#define OR_SHELL_MAJOR_VERSION 1
#define OR_SHELL_MINOR_VERSION 1

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ShellKernel
 *  \brief  The heart of the shell.
 *  \author Gabriel Peyré 2001-11-14
 *
 *	This class drive the evolution of the user in the shell hierarchy.
 *	\example shell_test/main.cpp
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_ShellKernel:	public OR_Serializable
{

public:

    OR_ShellKernel(OR_ShellObject_ABC& RootObject_, OR_String& RootName = OR_String("root"));
	OR_ShellKernel();
    virtual ~OR_ShellKernel();

    //-------------------------------------------------------------------------
    /** \name force computations */
    //-------------------------------------------------------------------------
    //@{
	void DoString(OR_String& cmd, OR_ShellConsole_ABC& console);
    //@}

    //-------------------------------------------------------------------------
    /** \name basic command */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool    ExecuteCmdCd(const OR_String& name);
	OR_Bool    ExecuteCmdCdSingle(const OR_String& name);
	OR_String  ExecuteCmdHelp(const OR_String& name);
	OR_String& ExecuteCmdLs(const OR_String& name);
	OR_String& ExecuteCmdPwd();
	OR_String  ExecuteCmdAbout();

	OR_Bool TryCompletion(OR_String& orignal, OR_String& completed, OR_String& suggestion);
    //@}

	//-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OR_ShellConsole_ABC* GetCurrentConsole();
	void SetRootObject(OR_ShellObject_ABC& root, OR_String& RootName = OR_String("root"));
	OR_WrapperLUA& GetWrapperLUA();
    //@}	
	
    //-------------------------------------------------------------------------
    /** \name helpers */
    //-------------------------------------------------------------------------
    //@{
	OR_U32 GetPwdLength();
	OR_ShellObject_ABC& GetCurrentObject();
    //@}

	//-------------------------------------------------------------------------
    /** \name exit management */
    //-------------------------------------------------------------------------
    //@{
	static OR_U32 Default_Quit_Func();
	void SetQuitFunc( OR_Shell_Quit_Func QuitFunc );
    //@}

	//-------------------------------------------------------------------------
    /** @name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	/** macro to define class-specific function */
	OR_DEFINE_SERIALIZATION(OR_ShellKernel);
    //@}


private:

    //-------------------------------------------------------------------------
    /** \name secondary methods */
    //-------------------------------------------------------------------------
    //@{
	void ResetShellObjectName(T_ShellObjectList& SonList);
	void ComputePwdString();
	OR_ShellObject_ABC* DirectAccessObject(OR_String name);
	OR_Bool	IsInPwd(OR_ShellObject_ABC& Obj);

	OR_U32		GetNbrSubDir();
	OR_String	GetSubDir(OR_U32 nNumSubDir);
	
	void ResetSonList();
	void ResetFuncDeclList();

	void RegisterFuncDecl();
	void UnRegisterFuncDecl();

	OR_U32 ComputeMaxFuncNameLength();
	OR_ShellFuncDecl* GetFuncByName(const OR_String& name);

	void SetStaticThis();
	static OR_ShellKernel& GetStaticThis();

	/** completion helpers */
	OR_Bool TryCompletionFunction(OR_String& FuncName, OR_String& completed, OR_String& suggestion);
	OR_Bool TryCompletionObject(OR_String& ObjName, OR_String& completed, OR_String& suggestion);
	void ListFuncBeginingWith(T_StringList& FuncList, OR_String& name);
	void ListObjBeginingWith(T_StringList& ObjList, OR_String& name);
	void FindCommonBegining(T_StringList& NameList, OR_String& CommonBegining);
    //@}

    //-------------------------------------------------------------------------
    /** \name special shell functions */
    //-------------------------------------------------------------------------
    //@{	
	void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);

	OR_DECL_SHELL_FUNC(about, 0);
	OR_DECL_SHELL_FUNC(pwd, 0);
	OR_DECL_SHELL_FUNC(cd, 0);
	OR_DECL_SHELL_FUNC(ls, 0);
	OR_DECL_SHELL_FUNC(help, 0);
	OR_DECL_SHELL_FUNC(GetNbrSubDir, 1);
	OR_DECL_SHELL_FUNC(GetSubDir, 1);
    //@}
	

	/** The list of sons, that will be given when an 'ls' is performed.
		The basic tactic to use this list is to fill it each time an 'ls'
		is performed.
		Then, when the shell kernell will have finished using this list, 
		it will free it (to avoid leaving unused datas). */
	T_ShellObjectList SonList_;

	/** The list of the additional functions proposed by the object.
		Each time the kernel enter an object (by a 'cd'), it get the 
		list of functions proposed by the object, and declare them
		to \b LUA so that the used can access them via command line. */
	T_ShellFuncDeclList FuncDeclList_;

	/** The top level lua function, which are declared by the kernel,
		and allow \b LUA script to have access to top level functions
		such as 'ls', 'cd' ... via a standard \b LUA call, ie. ls() ... */
	T_ShellFuncDeclList TopFuncDeclList_;


	/** list of object in the pwd */
	T_ShellObjectList	Pwd_;
	/** string representing the pwd */
	OR_String			PwdString_;
	/** string representing the result of a ls command */
	OR_String		    LsString_;


	/** the \b LUA interpreter */
	OR_WrapperLUA		WrapperLUA_;

	/** the current console (used by callback functions) */
	OR_ShellConsole_ABC* pCurrentConsole_;
	/** static this (used by callback function) */
	static OR_ShellKernel* pStaticThis_;

	OR_Shell_Quit_Func fQuitFunc_;


};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ShellKernel.inl"
#endif


#endif // __OR_ShellKernel_h_

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

