/*------------------------------------------------------------------------------
 *  \file  OR_Skin.cpp
 *  \brief implementation of class OR_Skin
 *  \author Antoine Bouthors 2001-10-05
 *------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) Skin.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Skin.h"

#ifndef OR_USE_INLINE
#   include "OR_Skin.inl"
#endif

namespace OR
{


/*------------------------------------------------------------------------------
 * Name : OR_Skin::PrepareDrawing
 *
 *  \author Antoine Bouthors 2001-10-11
 *
 * Prepare the data to be drawn ( fill in m_SkinMatrices )
 *------------------------------------------------------------------------------*/
void OR_Skin::PrepareDrawing()
{
	OR_Float		*VertsArray, *NormsArray, *TCoordsArray;
	OR_U32			*FaceList, NbFaces, NbVertex;
	OR_Globals::MeshDataManager()->AccessArrays( m_MeshDataHandle, VertsArray, NormsArray, TCoordsArray, FaceList, NbVertex, NbFaces );

	OR_Float		Zeros[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	OR_Matrix4x4	TheMatrix;
	OR_Matrix4x4	TheRotationMatrix;
	OR_Vector3D		Position;
	OR_Vector3D		Normal;
	OR_U32			j;
	
	for ( OR_U32 b=0 ; b<m_NbrBones ; ++b )
	{
		m_SkinMatrices[b] = m_PrecomputedRefMatrices[b]*( m_Bones[b]->GetAbsoluteMatrix() )*m_PrecomputedMeshRefMatrice;
	}

	OR_ASSERT( m_VertexArray );
	OR_ASSERT( m_NormalArray );
	if( m_SkinningEnabled )
	{
		for( OR_U32 Indice = 0 ; Indice < NbVertex ; ++Indice )
		{
			TheMatrix.SetCoords( Zeros );

			//Compute the matrices (using matrix blending)
			for ( j=0 ; j<m_NbrBones ; ++j )
			{
				OR_Float Factor = m_WeightArrays[ j ][ Indice ];
				if( Factor > 0 ) TheMatrix += m_SkinMatrices[ j ] * Factor;
			}
			TheRotationMatrix = TheMatrix;
			TheRotationMatrix.SetTranslation( OR_Vector3D(0,0,0) );		

			//Compute the result
			Position = TheMatrix * OR_Vector3D( m_VertexArray + 3*Indice );
			Normal	= TheRotationMatrix * OR_Vector3D( m_NormalArray + 3*Indice );

			//Store
			memcpy( VertsArray+3*Indice, Position.GetCoord(), 3*sizeof(float) );			
			memcpy( NormsArray+3*Indice, Normal.GetCoord(), 3*sizeof(float) );
		}
	}
	else
	{
		memcpy( VertsArray, m_VertexArray, NbVertex*3*sizeof(float) );			
		memcpy( NormsArray, m_NormalArray, NbVertex*3*sizeof(float) );
	}
}

  
/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Skin::ProcessAllFaces
 *
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Just flush all face to screen.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Skin::ProcessAllFaces()
{
	/* set the vertex array pointers */
	OR_Globals::MeshDataManager()->PrepareData( m_MeshDataHandle );
	OR_Globals::Context()->SetNormalization( true );	

	if( this->GetShadableMode()==OR_Shadable::kProcessAll )
	{
		/* flush everything */
		OR_Globals::MeshDataManager()->DrawAllFaces( m_MeshDataHandle );
	}
	else
	{
		OR_ASSERT( this->GetFaceArrayToProcess()!=NULL &&
				 this->GetNbrFaceToProcess()>=0 );
		/* flush only the specified faces */
		glDrawElements( GL_TRIANGLES, this->GetNbrFaceToProcess()*3, GL_UNSIGNED_INT, this->GetFaceArrayToProcess() );	
	}

}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Skin::ProcessOneFace
 *
 *  \param  nNumFace The face to render
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Just flush one given face to screen.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Skin::ProcessOneFace(OR_U32 nNumFace)
{
	/* set the vertex array pointers */
	OR_Globals::MeshDataManager()->PrepareData( m_MeshDataHandle );
	OR_Globals::Context()->SetNormalization( true );
	
	/* flush only one face */
	OR_Globals::MeshDataManager()->DrawOneFace( m_MeshDataHandle, nNumFace );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Skin::AccessArrays
 *
 *  \param  aVertArray Array of vertex to process. Size 3*nNbrVert.
 *  \param  aNormArray Array of normal to process. Size 3*nNbrVert.
 *  \param  aFaceArray Array of face to process. Size 3*nNbrFace. Index on the 2 previous arrays.
 *  \param  nNbrVert Number of vertex to process.
 *  \param  nNbrFace Number of faces to process.
 *  \author Antoine Bouthors 2001-10-13
 */ 
/*------------------------------------------------------------------------------*/
void OR_Skin::AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCoordArray, OR_U32* &aFaceArray,
						    OR_U32& nNbrVert, OR_U32& nNbrFace )
{
	if( !m_SkinningEnabled )
	{
		aVertArray = m_VertexArray;
		aNormArray = m_NormalArray;
		aTexCoordArray = OR_Globals::MeshDataManager()->GetTexCoordsArray( m_MeshDataHandle );
		aFaceArray = OR_Globals::MeshDataManager()->GetFacesArray( m_MeshDataHandle );
		nNbrVert = OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle );
		nNbrFace = OR_Globals::MeshDataManager()->GetNbrFaces( m_MeshDataHandle );
	}
	else
	{
		OR_Globals::MeshDataManager()->AccessArrays( m_MeshDataHandle, aVertArray, aNormArray, aTexCoordArray, aFaceArray, nNbrVert, nNbrFace );
	}
}



/*------------------------------------------------------------------------------
 * Name : OR_Skin::Draw
 *
 *  \author Antoine Bouthors 2001-10-06
 *
 * Draw the mesh
 *------------------------------------------------------------------------------*/
void OR_Skin::Draw()
{
	if( !bIsVisible ) return;
	if( this->IsSkinningBone() && !OR_Globals::GetDrawObject(OR_SKINNING_BONE) ) 
		return;

	PrepareDrawing();
	OR_Mesh::Draw();
}



/*------------------------------------------------------------------------------
 * Name : OR_Skin::Initialize
 *
 *  \author Antoine Bouthors 2001-10-06
 *
 * Initialize internal private data. Call it after creation
 *------------------------------------------------------------------------------*/
void OR_Skin::Initialize()
{
	OR_Float*	VertsArray = OR_Globals::MeshDataManager()->GetVertexArray( m_MeshDataHandle );
	OR_Float*	NormsArray = OR_Globals::MeshDataManager()->GetNormalsArray( m_MeshDataHandle );
	OR_U32		NbVertex = OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle );

	PrecomputeRefMatrices();

	OR_DELETEARRAY( m_VertexArray );
	OR_DELETEARRAY( m_NormalArray );
	m_VertexArray = new OR_Float[ NbVertex*3 ];
	m_NormalArray = new OR_Float[ NbVertex*3 ];
	memcpy( m_VertexArray, VertsArray, NbVertex*3*sizeof(OR_Float) );
	memcpy( m_NormalArray, NormsArray, NbVertex*3*sizeof(OR_Float) );

}




/*------------------------------------------------------------------------------
 * Name : OR_Skin::BuildFromFile
 *
 *  \param  file EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-20
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
void OR_Skin::BuildFromFile( OR_File& file )
{
	OR_Mesh::BuildFromFile( file );
	OR_U32 NbrVerts = OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle );
	OR_U32 NbrBones;
	OR_U32 CurBoneId;
	OR_U32 i,j;

	file >>	NbrBones;
	SetNbrBones( NbrBones );
	file >> m_SkinningEnabled;
	for( i=0 ; i<m_NbrBones ; ++i )
	{
		for( j=0 ; j<NbrVerts ; ++j ) file >> m_WeightArrays[i][j];
		file >> CurBoneId;	m_Bones[i] = (OR_Object*)CurBoneId;
		file >>	m_RefMatrices[i];
	}
	file >> m_MeshRefMatrix;
	for( j=0 ; j<NbrVerts ; ++j ) file >> m_WeightArrays[m_NbrBones][j];

	/* add itself to the manager */
	OR_Globals::SkinManager( )->AddElement( this ); 
	OR_Globals::MeshManager( )->RemoveElement( this ); 
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::BuildToFile
 *
 *  \param  file EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-20
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
void OR_Skin::BuildToFile( OR_File& file )
{
	OR_U32 NbrVerts = OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle );
	OR_U32 i,j;

	OR_Float *    VertsArray = OR_Globals::MeshDataManager( ) -> GetVertexArray( m_MeshDataHandle ); 
	OR_Float *    NormsArray = OR_Globals::MeshDataManager( ) -> GetNormalsArray( m_MeshDataHandle ); 

	memcpy( VertsArray , m_VertexArray , NbrVerts * 3 * sizeof( OR_Float ) ); 
	memcpy( NormsArray , m_NormalArray , NbrVerts * 3 * sizeof( OR_Float ) ); 
	OR_Mesh::BuildToFile( file ); 

	file <<	m_NbrBones;
	file << m_SkinningEnabled;
	for( i=0 ; i<m_NbrBones ; ++i )
	{
		for( j=0 ; j<NbrVerts ; ++j ) file << m_WeightArrays[i][j];
		file << ( m_Bones[i]->GetId() );
		file <<	m_RefMatrices[i];
	}
	file << m_MeshRefMatrix;
	for( j=0 ; j<NbrVerts ; ++j ) file << m_WeightArrays[m_NbrBones][j];
}



/*------------------------------------------------------------------------------
 * Name : OR_Skin::PostExportPass
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-20
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
void OR_Skin::PostExportPass()
{
	OR_Mesh::PostExportPass();
	
	for( OR_U32 i=0 ; i<m_NbrBones ; ++i )
	{
		m_Bones[i] = OR_Globals::GetImportedObject( (OR_U32)m_Bones[i] );
		OR_ASSERT( m_Bones[i] != NULL );
	}

	Initialize();
}


} // Namespace OR






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

