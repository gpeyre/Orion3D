/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaObject_ABC.inl
 *  \brief Inlined methods for \c OR_MetaObject_ABC
 *  \author Gabriel Peyré 2002/04/15
 */ 
/*------------------------------------------------------------------------------*/

#include "OR_MetaObject_ABC.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaObject_ABC::OR_MetaObject_ABC()
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	constructor
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_MetaObject_ABC::OR_MetaObject_ABC()
{	
	pMetaFunc_ = Default_MetaFunction;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaObject_ABC::SetMetaFunction( T_MetaFunction pMetaFunc )
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	AddCommentHere
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MetaObject_ABC::SetMetaFunction( T_MetaFunction pMetaFunc )
{
	pMetaFunc_ = pMetaFunc;
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

