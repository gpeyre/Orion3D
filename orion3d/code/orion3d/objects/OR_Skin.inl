/*------------------------------------------------------------------------------
 *  \file  OR_Skin.inl
 *  \brief Inline functions for OR_Skin
 *  \author Antoine Bouthors 2001-10-05
 *------------------------------------------------------------------------------*/
#include "OR_Skin.h"

namespace OR
{

	
/*------------------------------------------------------------------------------
 * Name : OR_Skin constructor
 *
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Skin::OR_Skin() : 
	OR_Mesh(),
	m_SkinningEnabled( false ),
	m_NbrBones( 0 ),
	m_RefMatrices( NULL ),
	m_WeightArrays( NULL ),
	m_Bones( NULL ),
	m_VertexArray( NULL ),
	m_NormalArray( NULL ),
	m_PrecomputedRefMatrices( NULL ),
	m_SkinMatrices( NULL )
{	
}



/*------------------------------------------------------------------------------
 * Name : OR_Skin copy constructor
 *
 *  \param  Dup skin to duplicate
 *  \author Antoine Bouthors 2001-10-08
 *
 * Duplicate the skin, including internal private data (no need to initalize)
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Skin::OR_Skin( const OR_Skin& Dup ):
	OR_Mesh( Dup ),
	m_SkinningEnabled( Dup.m_SkinningEnabled ),
	m_NbrBones( 0 ),
	m_RefMatrices( NULL ),
	m_WeightArrays( NULL ),
	m_VertexArray( NULL ),
	m_NormalArray( NULL ),
	m_Bones( NULL ),
	m_PrecomputedRefMatrices( NULL ),
	m_SkinMatrices( NULL )
{
	this->SetNbrBones( Dup.m_NbrBones );
	for( OR_U32 i=0 ; i<m_NbrBones ; ++i )
	{
		m_WeightArrays[i] = Dup.m_WeightArrays[i];
		m_RefMatrices[i] = Dup.m_RefMatrices[i];
		m_PrecomputedRefMatrices[i] = Dup.m_PrecomputedRefMatrices[i];
		m_Bones[i] = Dup.m_Bones[i];
	}
	m_MeshRefMatrix = Dup.m_MeshRefMatrix;
	m_SkinElts = Dup.m_SkinElts;

	OR_U32		NbVertex = OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle );
	m_VertexArray = new OR_Float[ NbVertex*3 ];
	m_NormalArray = new OR_Float[ NbVertex*3 ];
	memcpy( m_VertexArray, Dup.m_VertexArray, NbVertex*3*sizeof(float) );			
	memcpy( m_VertexArray, Dup.m_NormalArray, NbVertex*3*sizeof(float) );
}



/*------------------------------------------------------------------------------
 * Name : OR_Skin copy constructor
 *
 *  \param  Dup mesh to duplicate
 *  \author Antoine Bouthors 2001-10-08
 *
 * Duplicate the mesh without creating any skinning info
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Skin::OR_Skin( const OR_Mesh& Dup ):
	OR_Mesh( Dup ),
	m_SkinningEnabled( false ),
	m_NbrBones( 0 ),
	m_RefMatrices( NULL ),
	m_VertexArray( NULL ),
	m_NormalArray( NULL ),
	m_WeightArrays( NULL ),
	m_Bones( NULL ),
	m_PrecomputedRefMatrices( NULL ),
	m_SkinMatrices( NULL )
{
}



/*------------------------------------------------------------------------------
 * Name : OR_Skin constructor
 *
 *  \param  &verts Vertex array
 *  \param  &norms Normal array
 *  \param  &tcoords Texture coords array
 *  \param  faces Faces Array
 *  \param  nbface Number of faces
 *  \author Antoine Bouthors 2001-10-07
 *
 * Create a mesh without creating any skinning info
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Skin::OR_Skin( const OR_Float* VertsArray, const OR_Float* NormsArray, const OR_Float* TCoordsArray, const OR_U32* FacesArray, OR_U32 NbrVerts, OR_U32 Nbrfaces ) : 
	OR_Mesh( VertsArray, NormsArray, TCoordsArray, FacesArray, NbrVerts, Nbrfaces ),
	m_SkinningEnabled( false ),
	m_NbrBones( 0 ),
	m_RefMatrices( NULL ),
	m_WeightArrays( NULL ),
	m_VertexArray( NULL ),
	m_NormalArray( NULL ),
	m_Bones( NULL ),
	m_PrecomputedRefMatrices( NULL ),
	m_SkinMatrices( NULL )
{	
}



/*------------------------------------------------------------------------------
 * Name : OR_Skin destructor
 *
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Skin::~OR_Skin()
{
	OR_DELETEARRAY( m_WeightArrays );
	OR_DELETEARRAY( m_RefMatrices );
	OR_DELETEARRAY( m_PrecomputedRefMatrices );
	OR_DELETEARRAY( m_SkinMatrices );
	OR_DELETEARRAY( m_Bones );
	OR_DELETEARRAY( m_VertexArray );
	OR_DELETEARRAY( m_NormalArray );
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::operator
 *
 *  \param  Dup EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-31
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Skin& OR_Skin::operator=( const OR_Skin& Dup )
{
	OR_Mesh::operator=( Dup );
	
	m_SkinningEnabled = Dup.m_SkinningEnabled;
	OR_DELETEARRAY( m_RefMatrices );
	OR_DELETEARRAY( m_WeightArrays);
	OR_DELETEARRAY( m_VertexArray );
	OR_DELETEARRAY( m_NormalArray );
	OR_DELETEARRAY( m_Bones );
	OR_DELETEARRAY( m_PrecomputedRefMatrices );
	OR_DELETEARRAY( m_SkinMatrices );
	this->SetNbrBones( Dup.m_NbrBones );
	for( OR_U32 i=0 ; i<m_NbrBones ; ++i )
	{
		m_WeightArrays[i] = Dup.m_WeightArrays[i];
		m_RefMatrices[i] = Dup.m_RefMatrices[i];
		m_PrecomputedRefMatrices[i] = Dup.m_PrecomputedRefMatrices[i];
		m_Bones[i] = Dup.m_Bones[i];
	}
	m_MeshRefMatrix = Dup.m_MeshRefMatrix;
	m_SkinElts = Dup.m_SkinElts;

	OR_U32		NbVertex = OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle );
	if( Dup.m_VertexArray && Dup.m_NormalArray )
	{
		m_VertexArray = new OR_Float[ NbVertex*3 ];
		m_NormalArray = new OR_Float[ NbVertex*3 ];
		memcpy( m_VertexArray, Dup.m_VertexArray, NbVertex*3*sizeof(float) );			
		memcpy( m_VertexArray, Dup.m_NormalArray, NbVertex*3*sizeof(float) );
	}

	return (*this);
}




/*------------------------------------------------------------------------------
 * Name : OR_Skin::GetNbrBones
 *
 *  \return The number of unique bones in the Skin
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
const OR_U32& OR_Skin::GetNbrBones() const
{
	return m_NbrBones; 
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::SetNbrBones
 *
 *  \param  NbrBones Total number of bones in the skin
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Skin::SetNbrBones( const OR_U32& NbrBones )
{
	m_NbrBones = NbrBones;
	OR_DELETEARRAY( m_WeightArrays );
	OR_DELETEARRAY( m_RefMatrices );
	OR_DELETEARRAY( m_PrecomputedRefMatrices );
	OR_DELETEARRAY( m_SkinMatrices );
	OR_DELETEARRAY( m_Bones );
	m_WeightArrays = new T_FloatVector[ m_NbrBones+1 ];
	m_RefMatrices = new OR_Matrix4x4[ m_NbrBones ];
	m_PrecomputedRefMatrices = new OR_Matrix4x4[ m_NbrBones ];
	m_SkinMatrices = new OR_Matrix4x4[ m_NbrBones+1 ];
	m_Bones = new OR_Object*[ m_NbrBones ];

	OR_U32 NbVertex = OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle );
	for( OR_U32 i=0 ; i<m_NbrBones ; ++i )
		m_WeightArrays[i].resize( NbVertex, 0 );
	m_WeightArrays[m_NbrBones].resize( NbVertex, 1 );
	memset( m_Bones, 0, m_NbrBones*sizeof(OR_Object*) );
	m_SkinningEnabled = true;
}



/*------------------------------------------------------------------------------
 * Name : OR_Skin::SetBone
 *
 *  \param  i Index of the bone to set
 *  \param  Bone The bone used to skin the mesh
 *  \author Antoine Bouthors 2001-10-08
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Skin::SetBone( OR_U32 i, OR_Object* Bone )
{
	OR_ASSERT( m_Bones!= NULL );
	OR_ASSERT( i < m_NbrBones );

	m_Bones[i] = Bone;
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::GetBone
 *
 *  \param  i Index of the bone to get
 *  \return The i-th bone
 *  \author Antoine Bouthors 2001-10-08
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
const OR_Object* OR_Skin::GetBone( OR_U32 i ) const
{
	OR_ASSERT( m_Bones!= NULL );
	OR_ASSERT( i < m_NbrBones );

	return m_Bones[i];
}



/*------------------------------------------------------------------------------ 
* Name : OR_Skin::GetBone 
* 
*  \param  i Index of the bone to get 
*  \return The i-th bone 
*  \author Antoine Bouthors 2002-01-05 
* 
*------------------------------------------------------------------------------*/ 
OR_INLINE 
OR_Object * OR_Skin::GetBone( OR_U32 i ) 
{ 
	OR_ASSERT( m_Bones != NULL ); 
	OR_ASSERT( i < m_NbrBones ); 

	return m_Bones[i]; 
} 

/*------------------------------------------------------------------------------
 * Name : OR_Skin::SetMeshRefMatrix
 *
 *  \param  MeshRefMatrix The reference matric of the Skin
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Skin::SetMeshRefMatrix( const OR_Matrix4x4& MeshRefMatrix )	
{
	m_MeshRefMatrix = MeshRefMatrix; 
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::GetMeshRefMatrix
 *
 *  \return The reference matric of the Skin
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
const OR_Matrix4x4& OR_Skin::GetMeshRefMatrix() const
{
	return m_MeshRefMatrix; 
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::SetRefMatrix
 *
 *  \param  i Index of the bone for which to set the reference matrix
 *  \param  RefMatrix The reference matrix of the i-th bone skinning the mesh
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Skin::SetRefMatrix( OR_U32 i, const OR_Matrix4x4& RefMatrix )
{
	if( i>=m_NbrBones )
	{
		OR_MsgException MyException( OR_String( "Bone index exceeds total bones number" ), OR_String( "OR_Skin::SetRefMatrix" ) );
		throw( &MyException );
	}
	else
		m_RefMatrices[i] = RefMatrix;
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::GetRefMatrix
 *
 *  \param  i Index of the bone from which to get the reference matrix
 *  \return  The reference matrix of the i-th bone skinning the mesh
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
const OR_Matrix4x4& OR_Skin::GetRefMatrix( OR_U32 i ) const
{
	if( i>=m_NbrBones )
	{
		OR_MsgException MyException( OR_String( "Bone index exceeds total bones number" ), OR_String( "OR_Skin::GetRefMatrix" ) );
		throw( &MyException );
	}
	else
	{
		return m_RefMatrices[i];
	}
}



/*------------------------------------------------------------------------------
 * Name : OR_Skin::SetWeight
 *
 *  \param  nBone Index of the bone
 *  \param  nVert Index of the vert
 *  \param  Weight Weight to set to the nVert-th vertex and the nBone-th bone 
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Skin::SetWeight( OR_U32 nBone, OR_U32 nVert, OR_Float Weight )
{
	OR_ASSERT( m_WeightArrays!= NULL );
	OR_ASSERT( nBone < m_NbrBones );
	OR_ASSERT( nVert < OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle ) );

	m_WeightArrays[nBone][nVert] = Weight;
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::GetWeight
 *
 *  \param  nBone Index of the bone
 *  \param  nVert Index of the vert
 *  \return Weight to set to the nVert-th vertex and the nBone-th bone 
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_Skin::GetWeight( OR_U32 nBone, OR_U32 nVert ) const
{
	OR_ASSERT( m_WeightArrays!= NULL );
	OR_ASSERT( nBone < m_NbrBones );
	OR_ASSERT( nVert < OR_Globals::MeshDataManager()->GetNbrVerts( m_MeshDataHandle ) );

	return m_WeightArrays[nBone][nVert];
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::PrecomputeRefMatrices
 *
 *  \author Antoine Bouthors 2001-10-06
 *
 * Fill in m_PrecomputedRefMatrices
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Skin::PrecomputeRefMatrices()
{
	OR_ASSERT( m_PrecomputedRefMatrices!=NULL );
	OR_ASSERT( m_RefMatrices!=NULL );
	
	for( OR_U32 i=0 ; i<m_NbrBones ; ++i )
		m_PrecomputedRefMatrices[i] =  m_MeshRefMatrix*m_RefMatrices[i].Invert();

	m_PrecomputedMeshRefMatrice = m_MeshRefMatrix.Invert();
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::GetSkinElts
 *
 *  \return The skin elements used in the skinning
 *  \author Antoine Bouthors 2001-10-08
 *
 * Use at your own risks
 *------------------------------------------------------------------------------*/
OR_INLINE
const OR_Skin::T_SkinEltList& OR_Skin::GetSkinElts() const
{
	return m_SkinElts; 
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::EnableSkinning
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-20
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Skin::EnableSkinning()
{
	m_SkinningEnabled = true;
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::DisableSkinning
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-20
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Skin::DisableSkinning()
{
	m_SkinningEnabled = false;
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::IsSkinningEnabled
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-20
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Skin::IsSkinningEnabled()
{
	return m_SkinningEnabled;
}


/*------------------------------------------------------------------------------
 * Name : OR_Skin::GetType
 *
 *  \return the Orion3D type of this class.
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Elements OR_Skin::GetType()
{
	return OR_SKIN;
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
