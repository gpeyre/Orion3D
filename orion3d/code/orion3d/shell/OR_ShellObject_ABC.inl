/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellObject_ABC.inl
 *  \brief Inlined methods for \c OR_ShellObject_ABC
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_ShellObject_ABC.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellObject_ABC::GetShellObjectName
 *
 *  \return the name of the object as a "shell object"
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_String& OR_ShellObject_ABC::GetShellObjectName()
{
	return ShellObjectName_;
}
	
/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellObject_ABC::ResetName
 *
 *  \author Gabriel Peyré 2001-11-14
 *
 *	Free the space used by the object name.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ShellObject_ABC::ResetName()
{
	ShellObjectName_.clear();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellObject_ABC::GetStaticThis
 *
 *  \return the this pointer of the class.
 *  \author Gabriel Peyré 2001-11-17
 *
 *	 used by static member to have access to non static datas.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellObject_ABC& OR_ShellObject_ABC::GetStaticThis()
{
	OR_ASSERT( pStaticThis_!=NULL );
	return *pStaticThis_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellObject_ABC::SetStaticThis
 *
 *  \author Gabriel Peyré 2001-11-17
 *
 *	Used by the kernel to declare wich object is being used, so that 
 *	the static callback functions might access non-static datas.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ShellObject_ABC::SetStaticThis()
{
	pStaticThis_ = this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellObject_ABC::SetShellName
 *
 *  \param  name the shell name of the object.
 *  \author Gabriel Peyré 2001-11-20
 *
 *	The name is set by the father in the hierarchy.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ShellObject_ABC::SetShellName( OR_String& name )
{
	ShellObjectName_ = name;
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

