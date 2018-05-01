
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellFuncDecl.h
 *  \brief Definition of class \c OR_ShellFuncDecl
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ShellFuncDecl_h_
#define __OR_ShellFuncDecl_h_

#include "../configuration/OR_Config.h"
#include "../wrapper_lua/OR_WrapperLUA.h"

namespace OR {

/** a LUA callback function */
typedef lua_CFunction T_ShellFunc;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ShellFuncDecl
 *  \brief  a function declaration for the shell.
 *  \author Gabriel Peyré 2001-11-17
 *
 *	This object is used by a shell object to give to the shell kernel
 *	explation about a function the object is able to perform.
 *
 *	Each time the user make a 'cd' to an object, the kernel get all 
 *	function declarations, and use them to declare these function to 
 *	\b LUA, so that the user can use them from command line.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_ShellFuncDecl
{

public:

    OR_ShellFuncDecl(T_ShellFunc ShellFunc, OR_String& FuncName, OR_String& FuncDesc);
    virtual ~OR_ShellFuncDecl();

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	T_ShellFunc&	GetFunc();
	OR_String&		GetFuncName();
	OR_String&		GetFuncDesc();
    //@}


private:


	/* the function that will be called by LUA **/
	T_ShellFunc ShellFunc_;
	/** the name of the function */
	OR_String FuncName_;
	/** the description of the function */
	OR_String FuncDesc_;


};

/** a list of function declarations */
typedef list<OR_ShellFuncDecl*> T_ShellFuncDeclList;
typedef T_ShellFuncDeclList::iterator IT_ShellFuncDeclList;

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ShellFuncDecl.inl"
#endif


#endif // __OR_ShellFuncDecl_h_

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

