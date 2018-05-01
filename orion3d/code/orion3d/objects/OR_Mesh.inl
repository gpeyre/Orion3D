/*------------------------------------------------------------------------------
 *  \file  OR_Mesh.inl
 *  \brief Inline function of a mesh
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
#include "OR_Mesh.h"

namespace OR {

/*------------------------------------------------------------------------------
 * Name : OR_Mesh::GetVertsArray
 *
 *  \return the array of vertex
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Float* OR_Mesh::GetVertsArray()
{
	return OR_Globals::MeshDataManager()->GetVertexArray( m_MeshDataHandle );
}


/*------------------------------------------------------------------------------
 * Name : OR_Mesh::GetNormsArray
 *
 *  \return the array of normals
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Float* OR_Mesh::GetNormsArray()
{
	return OR_Globals::MeshDataManager()->GetNormalsArray( m_MeshDataHandle );
}


/*------------------------------------------------------------------------------
 * Name : OR_Mesh::GetTCoordsArray
 *
 *  \return the array of texture coordonates
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Float* OR_Mesh::GetTCoordsArray()
{
	return OR_Globals::MeshDataManager()->GetTexCoordsArray( m_MeshDataHandle );
}

/*------------------------------------------------------------------------------
 * Name : OR_Mesh::GetFaceList
 *
 *  \return the list of faces
 *  \author Gabriel Peyré 2001-07-09
 *
 * The list of faces is in fact an array of index. Each 3 index is treated as a 
 * face.
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32* OR_Mesh::GetFaceList()
{
	return OR_Globals::MeshDataManager()->GetFacesArray( m_MeshDataHandle );
}


/*------------------------------------------------------------------------------
 * Name : OR_Mesh::GetNbVertex
 *
 *  \return the number of vertex [size of the vertex list].
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Mesh::GetNbVertex()
{
	return OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle );
}


/*------------------------------------------------------------------------------
 * Name : OR_Mesh::GetNbFaces
 *
 *  \return the number of faces [size of the face list / 3].
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Mesh::GetNbFaces()
{
	return OR_Globals::MeshDataManager()->GetNbrFaces( m_MeshDataHandle );
}


/*------------------------------------------------------------------------------
 * Name : OR_Mesh::GetType
 *
 *  \return the Orion3D type of this class.
 *  \author Gabriel Peyré 2001-07-09
 *
 * For dynamic type access.
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Elements OR_Mesh::GetType()
{
	return OR_MESH;
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

