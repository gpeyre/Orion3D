/*------------------------------------------------------------------------------
 *  \file  OR_Mesh.cpp
 *  \brief implementation of class \c OR_Mesh
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Mesh.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Mesh.h"
#include "../shaders/OR_Shader.h"
#include "../shaders/OR_ShaderManager.h"

#ifndef OR_USE_INLINE
#   include "OR_Mesh.inl"
#endif

namespace OR
{

/*------------------------------------------------------------------------------
 * Name : OR_Mesh initialization constructor
 *
 *  \param  VertsArray The vertices array of the mesh
 *  \param  NormsArray The normals array of the mesh
 *  \param  TCoordsArray The texcoords array of the mesh
 *  \param  FacesArray The indices array of the mesh
 *  \param  NbrVerts The vertices count of the mesh
 *  \param  Nbrfaces The faces count of the mesh
 *  \author Antoine Bouthors 2001-11-01
 *
 * Add a meshdata with the parameters and use it
 *------------------------------------------------------------------------------*/
OR_Mesh::OR_Mesh( const OR_Float* VertsArray, const OR_Float* NormsArray, const OR_Float* TCoordsArray, const OR_U32* FacesArray, OR_U32 NbrVerts, OR_U32 Nbrfaces )
:	OR_Object(),
	OR_Shadable()
{
	m_MeshDataHandle = OR_Globals::MeshDataManager()->AddMesh( VertsArray, NormsArray, TCoordsArray, FacesArray, NbrVerts, Nbrfaces, 0. );
	OR_Globals::MeshDataManager()->UseMesh( m_MeshDataHandle );
}


/*------------------------------------------------------------------------------
 * Name : OR_Mesh default constructor
 *
 *  \author Antoine Bouthors 2001-11-01
 *
 *------------------------------------------------------------------------------*/
OR_Mesh::OR_Mesh()
:	OR_Object(),
	OR_Shadable(),
	m_MeshDataHandle(-1)
{	
}

/*------------------------------------------------------------------------------
 * Name : OR_Mesh constructor
 *
 *  \param  Dup Mesh to copy from
 *  \author Antoine Bouthors 2001-10-08
 *
 * Use the same meshdata than Dup
 *------------------------------------------------------------------------------*/
OR_Mesh::OR_Mesh( const OR_Mesh& Dup ):
	OR_Object( Dup ),
	OR_Shadable( Dup ),
	m_MeshDataHandle( Dup.m_MeshDataHandle )
{	
	OR_Globals::MeshDataManager()->UseMesh( m_MeshDataHandle );
}



/*------------------------------------------------------------------------------
 * Name : OR_Mesh destructor
 *
 *  \author Antoine Bouthors 2001-11-01
 *
 * Release the meshdata handle
 *------------------------------------------------------------------------------*/
OR_Mesh::~OR_Mesh()
{
	if( m_MeshDataHandle != -1 ) OR_Globals::MeshDataManager()->ReleaseMesh( m_MeshDataHandle );
	if( OR_Globals::MeshDataManager()->IsUsed( m_MeshDataHandle ) == false ) OR_Globals::MeshDataManager()->RemoveMesh( m_MeshDataHandle );
}


/*------------------------------------------------------------------------------
 * Name : OR_Mesh::operator
 *
 *  \param  Dup Mesh to copy from
 *  \author Antoine Bouthors 2001-10-08
 *
 * Copy operator. Use the mesh data of Dup
 *------------------------------------------------------------------------------*/
OR_Mesh& OR_Mesh::operator=( const OR_Mesh& Dup )
{
	OR_Object::operator=( Dup );
	OR_Shadable::operator=( Dup );

	if( m_MeshDataHandle != -1 ) OR_Globals::MeshDataManager()->ReleaseMesh( m_MeshDataHandle );
	if( OR_Globals::MeshDataManager()->IsUsed( m_MeshDataHandle ) == false ) OR_Globals::MeshDataManager()->RemoveMesh( m_MeshDataHandle );
	
	m_MeshDataHandle = Dup.m_MeshDataHandle;
	OR_Globals::MeshDataManager()->UseMesh( m_MeshDataHandle );

	return (*this);
}



/*------------------------------------------------------------------------------
 * Name : OR_Mesh::SetAlpha
 *
 *  \param  val new value of the alpha component of the shader.
 *  \author Gabriel Peyré 2001-07-09
 *
 * does nothing if there is no shaders.
 *------------------------------------------------------------------------------*/
void OR_Mesh::SetAlpha(OR_Float val)
{
	if( pShader_!=NULL )
		pShader_->SetAlpha(val);
}


/*------------------------------------------------------------------------------
 * Name : OR_Mesh::Draw
 *
 *  \author Gabriel Peyré 2001-07-10
 *
 * Draw the mesh according to its caractristics :
 *		- If it has a skin, use it to draw the mesh.
 *		- If it has an alpha component, add its faces to the alpha pipeline.
 *		- If it's a normal mesh, then set-up the OR_Shadable state machine, 
 *		  and ask the shader to do it's job, that's to say to render the vertex
 *		  of the mesh, using the informations of the OR_Shadable part of the mesh.
 *------------------------------------------------------------------------------*/
void OR_Mesh::Draw()
{
	if( !bIsVisible ) return;
	OR_ASSERT(pShader_!=NULL);
	
	if( !this->IsActive() || !OR_Globals::GetDrawObject(OR_MESH) )
		return;
	if( this->IsSkinningBone() && !OR_Globals::GetDrawObject(OR_SKINNING_BONE) ) 
		return;
	
	if ( !pShader_->NeedsSorting() )
	{
		glPushMatrix();
		
		/* positionate the object in world frame */
		this->SetUpModelView();
		/* set up the shadable datas : process all faces */
		this->SetFaceToProcess_All();

#ifdef OR_DRAW_OBJECT_AXES
		OR_DrawLocalAxis();
#endif /* #ifdef OR_DRAW_OBJECT_AXES */

		/* render the shadable datas */
		pShader_->ProcessShader(*this);
		
		glPopMatrix();
	}
	else
	{
		OR_Float*	VertsArray = OR_Globals::MeshDataManager()->GetVertexArray( m_MeshDataHandle );
		OR_U32*		FaceList = OR_Globals::MeshDataManager()->GetFacesArray( m_MeshDataHandle );
		OR_U32		NbFaces = OR_Globals::MeshDataManager()->GetNbrFaces( m_MeshDataHandle );

		OR_Matrix4x4 TempMatrix;

		/* here we just draw the local axis [geometry is drawn by the alpha pipeline] */
#ifdef OR_DRAW_OBJECT_AXES
		glPushMatrix();
			OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
			OR_Maths::GetCurrentModelView( TempMatrix );
			OR_DrawLocalAxis();
		glPopMatrix();
#endif /* #ifdef OR_DRAW_OBJECT_AXES */
		
		OR_Float zMid;
		/* the mesh faces needs to be stored in the alpha pîpeline */
		for (OR_U32 i=0; i<NbFaces; i++)
		{
			zMid = TempMatrix.TransformOnZ(VertsArray[3*FaceList[3*i  ]], VertsArray[3*FaceList[3*i  ]+1], VertsArray[3*FaceList[3*i  ]+2] )
				+	TempMatrix.TransformOnZ(VertsArray[3*FaceList[3*i+1]], VertsArray[3*FaceList[3*i+1]+1], VertsArray[3*FaceList[3*i+1]+2] )
				+	TempMatrix.TransformOnZ(VertsArray[3*FaceList[3*i+2]], VertsArray[3*FaceList[3*i+2]+1], VertsArray[3*FaceList[3*i+2]+2] );
			OR_Globals::AlphaPipeline()->AddFace(this, &FaceList[3*i], zMid );
		}
	}	

}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Mesh::ProcessAllFaces
 *
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Just flush all face to screen.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Mesh::ProcessAllFaces()
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
 * Name : OR_Mesh::ProcessOneFace
 *
 *  \param  nNumFace The face to render
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Just flush one given face to screen.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Mesh::ProcessOneFace(OR_U32 nNumFace)
{
	/* set the vertex array pointers */
	OR_Globals::MeshDataManager()->PrepareData( m_MeshDataHandle );
	OR_Globals::Context()->SetNormalization( false );
	
	/* flush only one face */
	OR_Globals::MeshDataManager()->DrawOneFace( m_MeshDataHandle, nNumFace );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Mesh::ProcessOneFace
 *
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Set up the modeview matrix before rendering.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Mesh::SetUpModelView()
{
	OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Mesh::AccessArrays
 *
 *  \param  aVertArray Array of vertex to process. Size 3*nNbrVert.
 *  \param  aNormArray Array of normal to process. Size 3*nNbrVert.
 *  \param  aFaceArray Array of face to process. Size 3*nNbrFace. Index on the 2 previous arrays.
 *  \param  nNbrVert Number of vertex to process.
 *  \param  nNbrFace Number of faces to process.
 *  \author Gabriel Peyré 2001-08-30
 */ 
/*------------------------------------------------------------------------------*/
void OR_Mesh::AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCoordArray, OR_U32* &aFaceArray,
						    OR_U32& nNbrVert, OR_U32& nNbrFace )
{
	OR_Globals::MeshDataManager()->AccessArrays( m_MeshDataHandle, aVertArray, aNormArray, aTexCoordArray, aFaceArray, nNbrVert, nNbrFace );	
}

/*------------------------------------------------------------------------------
 * Name : OR_Mesh::BuildFromFile
 *
 *  \param  file the file we want to import the mesh from
 *  \author Gabriel Peyré 2001-07-09
 *
 * Import the mesh from a file
 *------------------------------------------------------------------------------*/
void OR_Mesh::BuildFromFile( OR_File& file )
{
	OR_Float		*VertsArray, *NormsArray, *TCoordsArray;
	OR_U32			*FaceList, NbFaces, NbVertex;

	/* load the basic OR_Object datas */
	OR_Object::BuildFromFile(file);
	/* load the mesh specific datas */
	file >> NbVertex
		>> NbFaces;

	/** get the shader */
	OR_String shader_name;
	file >> shader_name;
	pShader_ = OR_Globals::ShaderManager()->GetShaderByName( shader_name ); 
	if( pShader_==NULL )
	{
		/* the shader couldn't be retrieved, use default one */
		pShader_ = OR_Globals::GetDefaultShader();
	}
	pShader_->UseIt();

	/* read the vertex list from the file */
	VertsArray=new OR_Float[3*NbVertex];
	NormsArray=new OR_Float[3*NbVertex];
	TCoordsArray=new OR_Float[2*NbVertex];
	FaceList=new OR_U32[3*NbFaces];
	file.Read(VertsArray, sizeof(OR_Float), (unsigned long)3*NbVertex);
	file.Read(NormsArray, sizeof(OR_Float), (unsigned long)3*NbVertex);
	file.Read(TCoordsArray, sizeof(OR_Float), (unsigned long)2*NbVertex);
	file.Read(FaceList, sizeof(OR_U32), (unsigned long)3*NbFaces);

	m_MeshDataHandle = OR_Globals::MeshDataManager()->AddMesh( VertsArray, NormsArray, TCoordsArray, FaceList, NbVertex, NbFaces, 0 );
	OR_Globals::MeshDataManager()->UseMesh( m_MeshDataHandle );

	OR_DELETEARRAY(VertsArray);
	OR_DELETEARRAY(NormsArray);
	OR_DELETEARRAY(TCoordsArray);
	OR_DELETEARRAY(FaceList);

	/* add itself to the manager */
	OR_Globals::MeshManager()->AddElement( this );
}


/*------------------------------------------------------------------------------
 * Name : OR_Mesh::BuildToFile
 *
 *  \param  file The file we want to import the mesh from.
 *  \author Gabriel Peyré 2001-07-09
 *
 * Export the mesh from a file
 *------------------------------------------------------------------------------*/
void OR_Mesh::BuildToFile( OR_File& file )
{
	OR_Float		*VertsArray, *NormsArray, *TCoordsArray;
	OR_U32			*FaceList, NbFaces, NbVertex;
	OR_Globals::MeshDataManager()->AccessArrays( m_MeshDataHandle, VertsArray, NormsArray, TCoordsArray, FaceList, NbVertex, NbFaces );

	/* save the basic OR_Object datas */
	OR_Object::BuildToFile(file);
	/* save the mesh specific datas */
	file << NbVertex
		 << NbFaces;

	/** if there is a shader, save it's name */
	if( this->GetShader()!=NULL )
	{
		file << this->GetShader()->GetName();
	}
	else
	{
		OR_Globals::MessageHandler()->Warning( "OR_Mesh::BuildToFile", "Mesh has no shader. Using default one." );
		file << OR_Globals::GetDefaultShader()->GetName();
	}

	/* write the vertex list to the file */
	file.Write( VertsArray, sizeof(OR_Float), (unsigned long)3*NbVertex);
	file.Write( NormsArray, sizeof(OR_Float), (unsigned long)3*NbVertex);
	file.Write( TCoordsArray, sizeof(OR_Float), (unsigned long)2*NbVertex);
	file.Write( FaceList, sizeof(OR_U32), (unsigned long)3*NbFaces);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Mesh::PostExportPass
 *
 *  \author Gabriel Peyré 2001-07-18
 *
 *	used to set up the bones once the export is done. The skin has
 *  to do a look up in ObjectList using bones id number to set the bones objects.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Mesh::PostExportPass()
{
	/* auto set the target */
	OR_Object::PostExportPass();
}

/*----------------------------------------------------------------------*/
/*                        classe OR_MeshManager							*/
/*----------------------------------------------------------------------*/
/*		permet de gerer plusieurs meshs via une liste chainee			*/
/*----------------------------------------------------------------------*/
/* herite de la classe OR_ManagerMap_Template   						*/
/*----------------------------------------------------------------------*/

OR_I32 OR_MeshManager::SetShader(OR_Shader& shader)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetShader(&shader);

	return OR_OK;
}

} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////
