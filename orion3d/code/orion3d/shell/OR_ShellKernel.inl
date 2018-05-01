/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellKernel.inl
 *  \brief Inlined methods for \c OR_ShellKernel
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_ShellKernel.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::GetPwdLength
 *
 *  \return Length of the pwd.
 *  \author Gabriel Peyré 2001-11-15
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_ShellKernel::GetPwdLength()
{
	return Pwd_.size();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::GetCurrentObject
 *
 *  \return the current directory.
 *  \author Gabriel Peyré 2001-11-15
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellObject_ABC& OR_ShellKernel::GetCurrentObject()
{
	OR_ASSERT( !Pwd_.empty() );
	return *(Pwd_.back());
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::DirectAccessObject
 *
 *  \param  name the path to the object we want to access.
 *  \return the object, or NULL if not found.
 *  \author Gabriel Peyré 2001-11-15
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellObject_ABC* OR_ShellKernel::DirectAccessObject(OR_String name)
{
	/* not yet implemented */
	return NULL;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::GetCurrentConsole
 *
 *  \return the console used by the kernel for output. \c NULL if there is no console used.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellConsole_ABC* OR_ShellKernel::GetCurrentConsole()
{
	return pCurrentConsole_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::SetStaticThis
 *
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ShellKernel::SetStaticThis()
{
	pStaticThis_ = this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::GetStaticThis
 *
 *  \return the static this.
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellKernel& OR_ShellKernel::GetStaticThis()
{
	OR_ASSERT( pStaticThis_!=NULL );
	return *pStaticThis_;
}




/*------------------------------------------------------------------------------
 * Name : OR_ShellKernel::SetQuitFunc
 *
 *  \param  QuitFunc The function to call when the user calls 'quit'
 *  \author Antoine Bouthors 2001-12-03
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_ShellKernel::SetQuitFunc( OR_Shell_Quit_Func QuitFunc )
{
	fQuitFunc_ = QuitFunc;
}

/*------------------------------------------------------------------------------
 * Name : OR_ShellConsole_ABC::GetWrapperLUA
 *
 *  \return The \b LUA wrapper.
 *  \author Gabriel Peyré 2001-12-03
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_WrapperLUA& OR_ShellKernel::GetWrapperLUA()
{
	return WrapperLUA_;
}


} // End namespace OR

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

