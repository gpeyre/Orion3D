/*------------------------------------------------------------------------------
 *  \file  OR_MeshDataManager.h
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *	\todo Document these classes/files
 *  \author Antoine Bouthors 2001-10-15
 *------------------------------------------------------------------------------*/

#ifndef __OR_MeshDataManager_h_
#define __OR_MeshDataManager_h_

#include "../configuration/OR_Config.h"

namespace OR {

class OR_MeshData
{
public:
	OR_U32		m_FacesOffset;
	OR_U32		m_VertsOffset;
	OR_U32		m_NbrVerts;
	OR_U32		m_NbrFaces;
	OR_Float	m_Priority;
	OR_U32		m_Handle;
	OR_I32		m_ReferenceCounter;

	OR_MeshData( OR_U32 FacesOffset, OR_U32 VertsOffset, OR_U32 NbrVerts, OR_U32 NbrFaces, OR_Float Priority, OR_U32 Handle ,OR_I32 ReferenceCounter ) :
		m_FacesOffset( FacesOffset ),
		m_VertsOffset( VertsOffset ),
		m_NbrVerts( NbrVerts ),
		m_NbrFaces( NbrFaces ),
		m_Priority( Priority ),
		m_Handle( Handle ),
		m_ReferenceCounter( ReferenceCounter )
	{}

};

/*------------------------------------------------------------------------------
 *  \class  OR_MeshDataManager
 *  \brief  PUT THE COMMENTS ON THE CLASS HERE
 *  \author Antoine Bouthors 2001-10-15
 *  PUT FULL DESCRIPTION HERE 
 *------------------------------------------------------------------------------*/

class ORION3D_API OR_MeshDataManager
{
public:

    OR_MeshDataManager();
    virtual ~OR_MeshDataManager();

	OR_U32		AddMesh( const OR_Float* Points, const OR_Float* Normals, const OR_Float* TexCoords, const OR_U32* Faces, OR_U32 NbrVerts, OR_U32 NbrFaces, OR_Float Priority );
	void		RemoveMesh( OR_U32 Handle );
	OR_Bool		Resize( OR_U32 NewVertsNumber, OR_U32 NewFacesNumber );
	OR_U32		GetVertsCapacity() const;
	OR_U32		GetFacesCapacity() const;
	OR_U32		GetTotalNbrVerts() const;
	OR_U32		GetTotalNbrFaces() const;

	void		UseMesh( OR_U32 Handle );
	void		ReleaseMesh( OR_U32 Handle );
	OR_Bool		IsUsed( OR_U32 Handle );
	OR_U32		RemoveUnusedObjects();

	void		SetPriority( OR_U32 Handle, OR_Float Priority );
	OR_Float	GetPriority( OR_U32 Handle ) const;
	OR_U32		GetNbrVerts( OR_U32 Handle ) const;
	OR_U32		GetNbrFaces( OR_U32 Handle ) const;
	OR_Float*	GetVertexArray( OR_U32 Handle );
	OR_Float*	GetNormalsArray( OR_U32 Handle );
	OR_Float*	GetTexCoordsArray( OR_U32 Handle );
	OR_U32*		GetFacesArray( OR_U32 Handle );
	
	void		AccessArrays( OR_U32 Handle, OR_Float*& Points, OR_Float*& Normals, OR_Float*& TexCoords, OR_U32*& Faces, OR_U32& NbrVerts, OR_U32& NbrFaces );
	void		PrepareData( OR_U32 Handle );
	void		DrawAllFaces( OR_U32 Handle ) const;
	void		DrawOneFace( OR_U32 Handle, OR_U32 Face ) const;
	void		Update();
	
private:

	OR_Bool			m_DataPrepared;

	OR_U32*			m_Data;
	OR_U32*			m_Points;
	OR_U32*			m_Normals;
	OR_U32*			m_TexCoords;
	OR_U32*			m_Faces;
	OR_U32			m_NbrFaces;
	OR_U32			m_NbrVerts;
	OR_U32			m_VertsCapacity;
	OR_U32			m_FacesCapacity;

	OR_U32			m_NbrTotalHandles;
	T_U32List		m_AvailableHandles;
	OR_MeshData**	m_Handles;
	
};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_MeshDataManager.inl"
#endif


#endif // __OR_MeshDataManager_h_

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
