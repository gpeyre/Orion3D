/*------------------------------------------------------------------------------
 *  \file  OR_MeshDataManager.cpp
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-10-15
 *------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MeshDataManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_MeshDataManager.h"

#ifndef OR_USE_INLINE
#   include "OR_MeshDataManager.inl"
#endif

namespace OR
{



/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager constructor
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_MeshDataManager::OR_MeshDataManager()
{
	m_DataPrepared = false;
	m_VertsCapacity = 0;
	m_FacesCapacity = 0;
	m_NbrVerts = 0;
	m_NbrFaces = 0;
	m_Points = NULL;
	m_Normals = NULL;
	m_TexCoords = NULL;
	m_Faces = NULL;
	m_Data = NULL;

	m_NbrTotalHandles = OR_NB_MAX_MESHDATAS;
	m_Handles = new OR_MeshData*[ m_NbrTotalHandles ];
	memset( m_Handles, 0, m_NbrTotalHandles*sizeof(OR_MeshData*) );
	for( OR_U32 i=0 ; i<m_NbrTotalHandles ; ++i )
		m_AvailableHandles.push_back( i );
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager destructor
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_MeshDataManager::~OR_MeshDataManager()
{
	for( OR_U32 i = 0 ; i<m_NbrTotalHandles ; ++i )
		if( m_Handles[i] ) RemoveMesh( i );

	OR_DELETEARRAY( m_Data );
	OR_DELETEARRAY( m_Handles );
}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::Update
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
void OR_MeshDataManager::Update()
{

}


/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::AddMesh		
 *
 *  \param  Points EXPLANATION
 *  \param  Normals EXPLANATION
 *  \param  TexCoords EXPLANATION
 *  \param  Faces EXPLANATION
 *  \param  NbrVerts EXPLANATION
 *  \param  NbrFaces EXPLANATION
 *  \param  Priority EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_U32 OR_MeshDataManager::AddMesh( const OR_Float* Points, const OR_Float* Normals, const OR_Float* TexCoords, const OR_U32* Faces, OR_U32 NbrVerts, OR_U32 NbrFaces, OR_Float Priority )
{
	OR_U32 NewVertsNumber = m_NbrVerts + NbrVerts;
	OR_U32 NewFacesNumber = m_NbrFaces + NbrFaces;

	if( NewVertsNumber > m_VertsCapacity || NewFacesNumber > m_FacesCapacity )
	{
		if( Resize( NewVertsNumber, NewFacesNumber ) == false ) return -1;
	}

	OR_U32*	DestPoints		= m_Points		+ m_NbrVerts*3;
	OR_U32*	DestNormals		= m_Normals		+ m_NbrVerts*3;
	OR_U32*	DestTexCoords	= m_TexCoords	+ m_NbrVerts*2;
	OR_U32*	DestFaces		= m_Faces		+ m_NbrFaces*3;
	
	memcpy( DestPoints,		Points,		NbrVerts*3*sizeof(OR_U32) );
	memcpy( DestNormals,	Normals,	NbrVerts*3*sizeof(OR_U32) );
	memcpy( DestTexCoords,	TexCoords,	NbrVerts*2*sizeof(OR_U32) );
	memcpy( DestFaces,		Faces,		NbrFaces*3*sizeof(OR_U32) );
	// Shift the indices :
	//for( OR_U32* p=DestFaces ; p<DestFaces+NbrFaces*3 ; (*(p++))+=m_NbrVerts );
	
	OR_U32 NewHandle = m_AvailableHandles.front();
	m_AvailableHandles.pop_front();
	
	OR_MeshData* NewData = new OR_MeshData
	(
		m_NbrFaces,
		m_NbrVerts, 
		NbrVerts,
		NbrFaces,
		Priority,
		NewHandle,
		0
	);

	m_Handles[NewHandle] = NewData;

	m_NbrVerts += NbrVerts;
	m_NbrFaces += NbrFaces;

	m_DataPrepared = false;

	return NewHandle;
}






/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::RemoveMesh
 *
 *  \param  Handle EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
void OR_MeshDataManager::RemoveMesh( OR_U32 Handle )
{
	OR_ASSERT( Handle < m_NbrTotalHandles );
	OR_MeshData*& MeshData = m_Handles[ Handle ];
	OR_ASSERT( MeshData != NULL );
	OR_ASSERT( MeshData->m_ReferenceCounter == 0 );

	OR_U32*	DestPoints		= m_Points		+ MeshData->m_VertsOffset*3;
	OR_U32*	DestNormals		= m_Normals		+ MeshData->m_VertsOffset*3;
	OR_U32*	DestTexCoords	= m_TexCoords	+ MeshData->m_VertsOffset*2;
	OR_U32*	DestFaces		= m_Faces		+ MeshData->m_FacesOffset*3;

	OR_U32*	OrgPoints		= DestPoints	+ MeshData->m_NbrVerts*3;
	OR_U32*	OrgTexCoords	= DestTexCoords	+ MeshData->m_NbrVerts*3;
	OR_U32*	OrgNormals		= DestNormals	+ MeshData->m_NbrVerts*2;
	OR_U32*	OrgFaces		= DestFaces		+ MeshData->m_NbrFaces*3;

	OR_U32 NbrVertsToMove = m_NbrVerts - MeshData->m_VertsOffset - MeshData->m_NbrVerts;
	OR_U32 NbrFacesToMove = m_NbrFaces - MeshData->m_FacesOffset - MeshData->m_NbrFaces;
	
	memmove( DestPoints,	OrgPoints,		NbrVertsToMove*3*sizeof(OR_U32) );
	memmove( DestNormals,	OrgNormals,		NbrVertsToMove*3*sizeof(OR_U32) );
	memmove( DestTexCoords,	OrgTexCoords,	NbrVertsToMove*2*sizeof(OR_U32) );
	memmove( DestFaces,		OrgFaces,		NbrFacesToMove*3*sizeof(OR_U32) );

	m_NbrVerts -= MeshData->m_NbrVerts;
	m_NbrFaces -= MeshData->m_NbrFaces;

	// Shift the indices :
	//for( OR_U32* p=DestFaces ; p<DestFaces+NbrFacesToMove*3 ; (*(p++))-=NbrVertsToMove );

	for( OR_U32 i=0 ; i<m_NbrTotalHandles ; ++i )
	{
		OR_MeshData* CurMeshData = m_Handles[ i ];
		if( CurMeshData )
		{
			if( CurMeshData->m_FacesOffset > MeshData->m_FacesOffset ) CurMeshData->m_FacesOffset -= MeshData->m_NbrFaces;
			if( CurMeshData->m_VertsOffset > MeshData->m_VertsOffset ) CurMeshData->m_VertsOffset -= MeshData->m_NbrVerts;
		}
	}

	m_AvailableHandles.push_front( MeshData->m_Handle );
	OR_DELETE( MeshData );

	m_DataPrepared = false;
}



/*------------------------------------------------------------------------------
 * Name : OR_MeshDataManager::Resize		
 *
 *  \param  NewVertsNumber EXPLANATION
 *  \param  NewFacesNumber EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-17
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_Bool	OR_MeshDataManager::Resize( OR_U32 NewVertsNumber, OR_U32 NewFacesNumber )
{
	if( NewVertsNumber < m_NbrVerts || NewFacesNumber < m_NbrFaces ) return false;
	
	OR_U32 DataSize = NewVertsNumber*8 + NewFacesNumber*3;
	OR_U32* NewData = new OR_U32[DataSize];
	
	if( !NewData ) return false;

	OR_U32*	NewPoints		= NewData;
	OR_U32*	NewNormals		= NewPoints + NewVertsNumber*3;
	OR_U32*	NewTexCoords	= NewNormals + NewVertsNumber*3;
	OR_U32*	NewFaces		= NewTexCoords + NewVertsNumber*2;

	if( m_Points )		memcpy( NewPoints,		m_Points,		m_NbrVerts*3*sizeof(OR_U32) );
	if( m_Normals )		memcpy( NewNormals,		m_Normals,		m_NbrVerts*3*sizeof(OR_U32) );
	if( m_TexCoords )	memcpy( NewTexCoords,	m_TexCoords,	m_NbrVerts*2*sizeof(OR_U32) );
	if( m_Faces )		memcpy( NewFaces,		m_Faces,		m_NbrFaces*3*sizeof(OR_U32) );

	OR_DELETEARRAY( m_Data );
	m_Data = NewData;

	m_Points	= NewPoints;
	m_Normals	= NewNormals;
	m_TexCoords = NewTexCoords;
	m_Faces		= NewFaces;

	m_VertsCapacity = NewVertsNumber;
	m_FacesCapacity = NewFacesNumber;
	
	m_DataPrepared = false;

	return true;
}


} // namespace OR

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

