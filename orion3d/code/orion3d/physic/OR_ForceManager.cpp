//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ForceManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#ifdef __GNUG__
    #pragma implementation
#endif

#include "../stdafx.h"
#include "OR_ForceManager.h"

#ifndef OR_USE_INLINE
#   include "OR_ForceManager.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
// Name : OR_ForceManager::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ForceManager::BuildFromFile( OR_File& file )
{
	this->SerializeFromFile(file);
}



/*------------------------------------------------------------------------------*/
// Name : OR_ForceManager::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ForceManager::BuildToFile( OR_File& file )
{
	this->SerializeToFile(file);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShaderManager::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 *
 *	Should be overloaded by complex shaders.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ForceManager::BuildSonList(T_ShellObjectList& ShellSonList)
{
	OR_SHELL_BUILD_MANAGER_SON_LIST( ShellSonList, OR_Force_ABC, "force" );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShaderManager::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ForceManager::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	/* NOTHING */
}
