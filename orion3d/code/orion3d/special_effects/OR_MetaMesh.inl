/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaMesh.inl
 *  \brief Inlined methods for \c OR_MetaMesh
 *  \author Gabriel Peyré 2002/04/15
 */ 
/*------------------------------------------------------------------------------*/

#include "OR_MetaMesh.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaMesh::SetInfluenceRadius(OR_Float radius)
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	the radius of influence of each radius function.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MetaMesh::SetInfluenceRadius(OR_Float radius)
{
	rInfluenceRadius_ = radius;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Float OR_MetaMesh::GetInfluenceRadius()
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	\return the radius of influence of each radius function.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MetaMesh::GetInfluenceRadius()
{
	return rInfluenceRadius_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Mesh* OR_MetaMesh::GetMesh()
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	\return the mesh
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Mesh* OR_MetaMesh::GetMesh()
{
	return pMesh_;
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

