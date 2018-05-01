
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellObject_ABC.h
 *  \brief Definition of class \c OR_ShellObject_ABC
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ShellObject_ABC_h_
#define __OR_ShellObject_ABC_h_

#include "../configuration/OR_Config.h"
#include "OR_ShellCallStack.h"
#include "../Misc/OR_Conversion.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ShellObject_ABC
 *  \brief  Base class for all objects that want to appear on the shell.
 *  \author Gabriel Peyré 2001-11-14
 *  
 *	The basic thing to do is to overload the 3 main commands :
 *		- LsCmd : 'ls'
 *		- CdCmd : 'cd'
 *
 *	A shell object can also register additional specific functions.
 */ 
/*------------------------------------------------------------------------------*/

class OR_ShellObject_ABC;
typedef list<OR_ShellObject_ABC*> T_ShellObjectList;
typedef T_ShellObjectList::iterator IT_ShellObjectList;

class ORION3D_API OR_ShellObject_ABC
{

public:

    OR_ShellObject_ABC();
    virtual ~OR_ShellObject_ABC();

    //-------------------------------------------------------------------------
    /** \name method to overload */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList) = 0;
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList) = 0;
    //@}

	//-------------------------------------------------------------------------
    /** \name function used by the kernel */
    //-------------------------------------------------------------------------
    //@{
	OR_String& GetShellObjectName();

	void ResetName();
	void SetShellName( OR_String& name );
    //@}

    //-------------------------------------------------------------------------
    /** \name static this manipulations */
    //-------------------------------------------------------------------------
    //@{
	static OR_ShellObject_ABC& GetStaticThis();
	void SetStaticThis();
    //@}


protected:

	/** The name of the object. It is set by the parent object, and reset by the shell kernel when it 
		doesn't need it anymore. */
	OR_String ShellObjectName_;

private:

	/** used by static functions to have access to 'this' pointer */
	static OR_ShellObject_ABC* pStaticThis_;

};


/* helpers methods ***************************************************************************/
/** get the number of stack entries needed to put the data in the stack */
inline OR_U32 GetDataLength(const char* DataType)
{
	if( strcmp(DataType, "OR_Vector2D")==0 )
		return 2;
	if( strcmp(DataType, "OR_Vector3D")==0 )
		return 3;
	if( strcmp(DataType, "OR_Vector4D")==0 )
		return 4;
	if( strcmp(DataType, "OR_Matrix3x3")==0 )
		return 9;
	if( strcmp(DataType, "OR_Matrix4x4")==0 )
		return 16;
	if( strcmp(DataType, "OR_Quaternion")==0 )
		return 4;
	return 1;
}


/* Declare and Add general functions to shell *************************************************/
/** the macro used to declare a \b LUA function wrapper that calls the user defined 
	function. */
#define OR_DECL_SHELL_FUNC(func, nbr_ret_val)				\
static int func##_LUA(lua_State* state)						\
{ func(OR_ShellCallStack(*state)); return nbr_ret_val; }	\
static void func(OR_ShellCallStack& stack)

/** the macro to use to add a function to the functions list */
#define OR_ADD_SHELL_FUNC(FuncDeclList, func, desc)			\
FuncDeclList.push_back( new OR_ShellFuncDecl(func##_LUA,	\
					   OR_String(#func),					\
					   OR_String(desc)) )

/* declare and implement 0 argument shell function *********************************************/
/** this macro declare and implement a function that takes no argument
	In fact, it simply wrap the call to the standard non-shell functio */
#define OR_DECL_IMPL_SHELL_FUNC(func, classname)			\
static int func##_LUA(lua_State* state)						\
{ func(OR_ShellCallStack(*state)); return 0; }				\
static void func(OR_ShellCallStack& stack)					\
{ OR_INIT_SHELL_FUNC( classname, 0 );						\
  OR_ACCESS_THIS(classname).func(); }

/** this macro declare and implement a function that takes 1 argument
	In fact, it simply wrap the call to the standard non-shell functio */
#define OR_DECL_IMPL_SHELL_FUNC_1ARG(func, type, classname)	\
static int func##_LUA(lua_State* state)						\
{ func(OR_ShellCallStack(*state)); return 0; }				\
static void func(OR_ShellCallStack& stack)					\
{ OR_INIT_SHELL_FUNC( classname, 1 );						\
  OR_SHELL_ACCESS_AND_USE( func, 1, type, var,				\
  OR_ACCESS_THIS(classname).func( var.val() ); ) }




/* Declare and Add printing functions to shell *************************************************/
/** define a PrintXXX function and implement it using 
	a GetXXX function that must be provided by the user */
#define OR_DECL_SHELL_PRINT_FUNC(var, classname, type)				\
static int Print##var##_LUA(lua_State* state)						\
{ Print##var(OR_ShellCallStack(*state)); return 0; }				\
static void Print##var(OR_ShellCallStack& stack)					\
{ OR_INIT_SHELL_FUNC( Print##var, 0 );								\
OR_SHELL_FUNC_PRINT( OR_String( OR_ACCESS_THIS(classname).Get##var() ) ); }

/** idem but for enumerated types */
#define OR_DECL_SHELL_PRINT_FUNC_ENUM(var, classname, type)			\
static int Print##var##_LUA(lua_State* state)						\
{ Print##var(OR_ShellCallStack(*state)); return 0; }				\
static void Print##var(OR_ShellCallStack& stack)					\
{ OR_INIT_SHELL_FUNC( Print##var, 0 );								\
  OR_SHELL_FUNC_PRINT( OR_Conversion::OR_##type##_ToString( OR_ACCESS_THIS(classname).Get##var() ) ); }

/** add a printing function to the function list */
#define OR_ADD_SHELL_PRINT_FUNC(FuncDeclList, var)					\
FuncDeclList.push_back( new OR_ShellFuncDecl(Print##var##_LUA,		\
					   OR_String("Print" #var),						\
					   OR_String("Print the value of " #var ".")) )

/* Declare and Add accessing functions to shell *************************************************/
/** define a GetXXX function and implement it using 
	a GetXXX function that must be provided by the user */
#define OR_DECL_SHELL_GET_FUNC(var, classname, type)				\
static int Get##var##_LUA(lua_State* state)							\
{ Get##var(OR_ShellCallStack(*state));								\
  return GetDataLength("OR_" #type); }								\
static void Get##var(OR_ShellCallStack& stack)						\
{ OR_INIT_SHELL_FUNC( Get##var, 0 );								\
stack.ReturnValue##type( OR_ACCESS_THIS(classname).Get##var() ); }

/** idem but for enumerated types */
#define OR_DECL_SHELL_GET_FUNC_ENUM(var, classname, type)			\
static int Get##var##_LUA(lua_State* state)							\
{ Get##var(OR_ShellCallStack(*state));								\
  return 1; }														\
static void Get##var(OR_ShellCallStack& stack)						\
{ OR_INIT_SHELL_FUNC( Get##var, 0 );								\
	stack.ReturnValueString( OR_Conversion::OR_##type##_ToString( OR_ACCESS_THIS(classname).Get##var() ) ); }

/** add a printing function to the function list */
#define OR_ADD_SHELL_GET_FUNC(FuncDeclList, var)					\
FuncDeclList.push_back( new OR_ShellFuncDecl(Get##var##_LUA,		\
					   OR_String("Get" #var),						\
					   OR_String("Get the value of " #var ".")) )

/* Declare and Add setting functions to shell *************************************************/
/** define a GetXXX function and implement it using 
	a GetXXX function that must be provided by the user */
#define OR_DECL_SHELL_SET_FUNC(var, classname, type)				\
static int Set##var##_LUA(lua_State* state)							\
{ Set##var(OR_ShellCallStack(*state)); return 0; }					\
static void Set##var(OR_ShellCallStack& stack)						\
{ OR_INIT_SHELL_FUNC( Set##var, GetDataLength("OR_" #type) );		\
  OR_SHELL_ACCESS_AND_USE( Set##var, 1, type, NewVal, OR_ACCESS_THIS(classname).Set##var( NewVal ); ) }

/** idem but for enumerated types */
#define OR_DECL_SHELL_SET_FUNC_ENUM(var, classname, type)			\
static int Set##var##_LUA(lua_State* state)							\
{ Set##var(OR_ShellCallStack(*state)); return 0; }					\
static void Set##var(OR_ShellCallStack& stack)						\
{ OR_INIT_SHELL_FUNC( Set##var, 1 );								\
  OR_SHELL_ACCESS_AND_USE( Set##var, 1, String, NewVal, OR_ACCESS_THIS(classname).Set##var(		\
		OR_Conversion::StringTo_OR_##type(NewVal)  ); ) }

/** add a printing function to the function list */
#define OR_ADD_SHELL_SET_FUNC(FuncDeclList, var)					\
FuncDeclList.push_back( new OR_ShellFuncDecl(Set##var##_LUA,		\
					   OR_String("Set" #var),						\
					   OR_String("Set the value of " #var ".")) )
		


/* Declare and Add all accessor funct to the shell *************************************************/
#define OR_DECL_SHELL_ACCESSOR_FUNC(var, classname, type)	\
OR_DECL_SHELL_PRINT_FUNC(var, classname, type);				\
OR_DECL_SHELL_GET_FUNC(var, classname, type);				\
OR_DECL_SHELL_SET_FUNC(var, classname, type)

#define OR_DECL_SHELL_ACCESSOR_FUNC_ENUM(var, classname, type)	\
OR_DECL_SHELL_PRINT_FUNC_ENUM(var, classname, type);			\
OR_DECL_SHELL_GET_FUNC_ENUM(var, classname, type);				\
OR_DECL_SHELL_SET_FUNC_ENUM(var, classname, type)

#define OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, var)		\
OR_ADD_SHELL_PRINT_FUNC(FuncDeclList, var);					\
OR_ADD_SHELL_GET_FUNC(FuncDeclList, var);					\
OR_ADD_SHELL_SET_FUNC(FuncDeclList, var)

/* Declare and Add only get/print funct to the shell *************************************************/
#define OR_DECL_SHELL_GET_PRINT_FUNC(var, classname, type)	\
OR_DECL_SHELL_PRINT_FUNC(var, classname, type);				\
OR_DECL_SHELL_GET_FUNC(var, classname, type)

#define OR_DECL_SHELL_GET_PRINT_FUNC_ENUM(var, classname, type)	\
OR_DECL_SHELL_PRINT_FUNC_ENUM(var, classname, type);			\
OR_DECL_SHELL_GET_FUNC_ENUM(var, classname, type)

#define OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, var)		\
OR_ADD_SHELL_PRINT_FUNC(FuncDeclList, var);					\
OR_ADD_SHELL_GET_FUNC(FuncDeclList, var)






/* son list creation *******************************************************************************/
/** add a son to the list */
inline void OR_ADD_SHELL_SON(T_ShellObjectList& ShellSonList, OR_ShellObject_ABC& ShellObj, OR_String& SonName)
{	
	ShellObj.SetShellName( SonName );
	ShellSonList.push_back( &ShellObj );
}

/** build a shell son list for a manager */
#define OR_SHELL_BUILD_MANAGER_SON_LIST( sonlist, classname, prefix )								\
for(IT_ManagerMap_Template(classname) it=begin(); it!=end(); ++it)									\
{ OR_ADD_SHELL_SON(sonlist, *(*it).second, OR_String(prefix "_") + this->GetUniqueString(it) ); }




/* helpers ******************************************************************************************/
/** get back the console, and then check the number of arguments */
#define OR_INIT_SHELL_FUNC(name, nb_args)												\
OR_ShellConsole_ABC* pConsole = OR_Globals::ShellKernelManager()->GetCurrentConsole();	\
OR_ASSERT( pConsole!=NULL );															\
if( stack.GetNbrArg()!=nb_args )														\
pConsole->Display( OR_String(#name " : invalid number of arguments.") );

/** print a string to the console */
#define OR_SHELL_FUNC_PRINT( str )	pConsole->Display( str )

/** access an argument checking it's type */
#define OR_SHELL_ACCESS_AND_USE( FuncName, Pos, Type, Data, code)				\
OR_##Type Data;																	\
OR_Bool bCheck = stack.AccessArgument##Type(Data, Pos);							\
if( bCheck ) { code }															\
else { OR_SHELL_FUNC_PRINT( OR_String( #FuncName " : invalid argument" ) ); }

/** access the static this with the rigth type */
#define OR_ACCESS_THIS(Type) ((Type&) GetStaticThis())


} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ShellObject_ABC.inl"
#endif


#endif // __OR_ShellObject_ABC_h_

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

