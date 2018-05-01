/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_Face.cpp
 *  \brief  Definition of class \c GW_Face
 *  \author Gabriel Peyré
 *  \date   2-15-2003
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_Face.cpp(c) Gabriel Peyré2003";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_Face.h"
#include "GW_Mesh.h"

#ifndef GW_USE_INLINE
    #include "GW_Face.inl"
#endif

using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_Face::operator=
/**
 *  \param  Face [GW_Face&] Face
 *  \return [GW_Face&] *this
 *  \author Gabriel Peyré
 *  \date   1-13-2004
 * 
 *  Copy operator
 */
/*------------------------------------------------------------------------------*/
GW_Face& GW_Face::operator=(const GW_Face& Face)
{
	this->nID_ = Face.nID_;
	return *this;
}


/*------------------------------------------------------------------------------*/
// Name : GW_Face::BuildFromFile
/**
*  \param  file [GW_Ifstream&] The file.
*  \author Gabriel Peyré
*  \date   4-2-2003
* 
*  Serialize the class from a file.
*/
/*------------------------------------------------------------------------------*/
void GW_Face::BuildFromFile( GW_Ifstream& file)
{
	file >> nID_;
	GW_I32 nTempID;
	for( GW_U32 i=0; i<3; ++i )
	{
		file >> nTempID;
		GW_ASSERT( nTempID>=0 );
		GW_Vertex* pVert = GW_Mesh::StaticThis().GetVertex(nTempID);
		GW_ASSERT( pVert!=NULL );
		this->SetVertex(*pVert, i);
	}
	for( GW_U32 i=0; i<3; ++i )
	{
		file >> nTempID;
		if( nTempID<0)
			this->SetFaceNeighbor( NULL, i );
		else
		{
			GW_Face* pFace = GW_Mesh::StaticThis().GetFace( nTempID );
			GW_ASSERT( pFace!=NULL );
			this->SetFaceNeighbor( pFace, i );
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_Face::BuildToFile
/**
*  \param  file [GW_Ofstream&] The file.
*  \author Gabriel Peyré
*  \date   4-2-2003
* 
*  Serialize the class to a file.
*/
/*------------------------------------------------------------------------------*/
void GW_Face::BuildToFile( GW_Ofstream& file )
{
	GW_I32 nNullID = -1;
	file << nID_;
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_ASSERT( this->GetVertex(i)!=NULL );
		GW_I32 nID = this->GetVertex(i)->GetID();
		file << nID;
	}
	for( GW_U32 i=0; i<3; ++i )
	{
		if( this->GetFaceNeighbor(i)==NULL )
			file << nNullID;
		else
		{
			GW_I32 nID = this->GetFaceNeighbor(i)->GetID();
			file << nID;
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_Face::GetArea
/**
 *  \return [GW_Float] The area.
 *  \author Gabriel Peyré
 *  \date   5-30-2003
 * 
 *  Compute the area of the face.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_Face::GetArea()
{
	if( Vertex_[0]==NULL ) return 0;
	if( Vertex_[1]==NULL ) return 0;
	if( Vertex_[2]==NULL ) return 0;
	GW_Vector3D e1 = this->GetVertex(1)->GetPosition() - this->GetVertex(0)->GetPosition();
	GW_Vector3D e2 = this->GetVertex(2)->GetPosition() - this->GetVertex(0)->GetPosition();
	return 0.5*GW_ABS( ~(e1^e2) );
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
