/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_HierarchyTree.inl
 *  \brief Inlined methods for \c OR_HierarchyTree
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_HierarchyTree.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_HierarchyTree::GetNbrObject
 *
 *  \return the number of object in the scene.
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_HierarchyTree::GetNbrObject()
{
	return NbObjets;
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

