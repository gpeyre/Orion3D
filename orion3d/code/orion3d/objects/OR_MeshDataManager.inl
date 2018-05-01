/*------------------------------------------------------------------------------
 *  \file  OR_MeshDataManager.inl
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-10-15
 *------------------------------------------------------------------------------*/
#include "OR_MeshDataManager.h"

namespace OR {




/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::PrepareData
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_MeshDataManager::PrepareData( OR_U32 Handle )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	glVertexPointer(3, GL_FLOAT, 0, m_Points + MeshData->m_VertsOffset*3 );
	glNormalPointer(GL_FLOAT, 0, m_Normals + MeshData->m_VertsOffset*3 );
	glTexCoordPointer(2, GL_FLOAT, 0, m_TexCoords + MeshData->m_VertsOffset*2 );
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::DrawFaces
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_MeshDataManager::DrawAllFaces( OR_U32 Handle ) const
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	glDrawElements( GL_TRIANGLES, MeshData->m_NbrFaces*3, GL_UNSIGNED_INT, m_Faces + MeshData->m_FacesOffset*3 );
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::DrawOneFace
 *
 *  \param  Handle EXPLANATION
 *  \param  Face EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_MeshDataManager::DrawOneFace( OR_U32 Handle, OR_U32 Face ) const
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, m_Faces + ( Face + MeshData->m_FacesOffset )*3 );
}



/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::UseMesh		
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void	OR_MeshDataManager::UseMesh( OR_U32 Handle )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	++( MeshData->m_ReferenceCounter );
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::ReleaseMesh
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_MeshDataManager::ReleaseMesh( OR_U32 Handle )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	--( MeshData->m_ReferenceCounter );
	OR_ASSERT( MeshData->m_ReferenceCounter >= 0 );
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::IsUsed
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_MeshDataManager::IsUsed( OR_U32 Handle )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	return( MeshData->m_ReferenceCounter > 0 );
}



/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::SetPriority
 *
 *  \param  Handle EXPLANATION
 *  \param  Priority EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_MeshDataManager::SetPriority( OR_U32 Handle, OR_Float Priority )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	MeshData->m_Priority = Priority;
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetPriority
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MeshDataManager::GetPriority( OR_U32 Handle ) const
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	return MeshData->m_Priority;
}



/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::AccessArrays
 *
 *  \param  Handle EXPLANATION
 *  \param  Points EXPLANATION
 *  \param  Normals EXPLANATION
 *  \param  TexCoords EXPLANATION
 *  \param  Faces EXPLANATION
 *  \param  NbrVerts EXPLANATION
 *  \param  NbrFaces EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_MeshDataManager::AccessArrays( OR_U32 Handle, OR_Float*& Points, OR_Float*& Normals, OR_Float*& TexCoords, OR_U32*& Faces, OR_U32& NbrVerts, OR_U32& NbrFaces )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	Points = (OR_Float*)m_Points + MeshData->m_VertsOffset*3;
	Normals = (OR_Float*)m_Normals + MeshData->m_VertsOffset*3;
	TexCoords = (OR_Float*)m_TexCoords + MeshData->m_VertsOffset*2;
	Faces = m_Faces + MeshData->m_FacesOffset*3;
	NbrVerts = MeshData->m_NbrVerts;
	NbrFaces = MeshData->m_NbrFaces;
}




/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::RemoveUnusedObjects
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MeshDataManager::RemoveUnusedObjects()
{
	OR_U32 Count(0);
	
	for( OR_U32 i = 0 ; i<m_NbrTotalHandles ; ++i )
	{
		if( m_Handles[i] && m_Handles[i]->m_ReferenceCounter == 0 )
		{
			++Count;
			RemoveMesh( i );
		}
	}

	return Count;
}




/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetVertsCapacity
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MeshDataManager::GetVertsCapacity() const
{
	return m_VertsCapacity;
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetFacesCapacity
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MeshDataManager::GetFacesCapacity() const
{
	return m_FacesCapacity;
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetNbrVerts
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MeshDataManager::GetTotalNbrVerts() const
{
	return m_NbrVerts;
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetNbrFaces
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MeshDataManager::GetTotalNbrFaces() const
{
	return m_NbrFaces;
}



/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetNbrVerts
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MeshDataManager::GetNbrVerts( OR_U32 Handle ) const
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	return MeshData->m_NbrVerts;
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetNbrFaces
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MeshDataManager::GetNbrFaces( OR_U32 Handle ) const
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	return MeshData->m_NbrFaces;
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetVertexArray
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Float* OR_MeshDataManager::GetVertexArray( OR_U32 Handle )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	return( (OR_Float*)m_Points + MeshData->m_VertsOffset*3 );
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetNormalsArray
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Float* OR_MeshDataManager::GetNormalsArray( OR_U32 Handle )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	return( (OR_Float*)m_Normals + MeshData->m_VertsOffset*3 );
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetTexCoordsArray
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Float* OR_MeshDataManager::GetTexCoordsArray( OR_U32 Handle )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	return( (OR_Float*)m_TexCoords + MeshData->m_VertsOffset*2 );
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::GetFacesArray
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-19
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32* OR_MeshDataManager::GetFacesArray( OR_U32 Handle )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData* MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );

	return( m_Faces + MeshData->m_FacesOffset*3 );
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
