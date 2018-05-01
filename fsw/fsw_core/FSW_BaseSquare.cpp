/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BaseSquare.cpp
 *  \brief  Definition of class \c FSW_BaseSquare
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_BaseSquare.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_BaseSquare.h"

using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseSquare constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Constructor. 
 */
/*------------------------------------------------------------------------------*/
FSW_BaseSquare::FSW_BaseSquare()
:FSW_BaseMesh_ABC()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseSquare destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_BaseSquare::~FSW_BaseSquare()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseSquare::BuildBaseMesh
/**
 *  \param  BaseNodeVector [T_QuadTreeNodeList&] A vector of node to fill.
 *  \param  BaseVertexVector [T_QuadTreeVertexVector&] A vector of vertex to fill.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  We construct a new list of node, and create associated vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseSquare::BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector )
{
	FSW_ASSERT( BaseNodeVector.empty() );
	FSW_ASSERT( BaseVertexVector.empty() );
	pBaseNodeVector_ = &BaseNodeVector;
	BaseNodeVector.resize( 2 );
	BaseVertexVector.resize( 4 );

	/* create the nodes*/
	for( FSW_U32 i=0; i<2; ++i )
		BaseNodeVector[i] = new FSW_QuadTreeNode;
	/* create the vertex*/
	for( FSW_U32 i=0; i<4; ++i )
		BaseVertexVector[i] = new FSW_QuadTreeVertex;

	/* set up the position of the 6 vertex and assign them to the different childs */
	BaseVertexVector[0]->SetPosition(	FSW_Vector3D(-1,-1,0) );
	BaseVertexVector[1]->SetPosition(	FSW_Vector3D(1,-1,0) );
	BaseVertexVector[2]->SetPosition(	FSW_Vector3D(1,1,0) );
	BaseVertexVector[3]->SetPosition(	FSW_Vector3D(-1,1,0) );

    BaseNodeVector[0]->SetVertex( BaseVertexVector[0], BaseVertexVector[2], BaseVertexVector[3] );
	BaseNodeVector[1]->SetVertex( BaseVertexVector[0], BaseVertexVector[2], BaseVertexVector[1] );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseSquare::GetRelativeSon
/**
 *  \param  nDirection [FSW_U32] The direction.
 *  \return [FSW_QuadTreeNode*] The neighbor.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Get the neighbor of a given node in a given direction (the node 
 *  should be a base node).
 */
/*------------------------------------------------------------------------------*/
FSW_QuadTreeNode* FSW_BaseSquare::GetRelativeSon(FSW_QuadTreeNode& Son, FSW_QuadTreeVertex& Direction)
{
	FSW_ASSERT( pBaseNodeVector_!=NULL );
	FSW_ASSERT( pBaseNodeVector_->size()==2 );
	/* first translate the vertex direction into an index entry */
	FSW_I32 nDirection = -1;
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( Son.GetVertex(i)==(&Direction) )
		{
			nDirection=i;
			break;
		}
	}
	FSW_ASSERT( nDirection>=0 );
	/* first we must figure out wich is the number of pSon */
	for( FSW_U32 i=0; i<2; ++i )
	{
		if( (&Son)==(*pBaseNodeVector_)[i] )
		{
			if( nDirection==2 )	// select the other one.
				return (*pBaseNodeVector_)[1-i];	// 1-i is the other node.
			else				// reflect the same node.
				return (*pBaseNodeVector_)[i];			
		}
	}
	FSW_ASSERT( FSW_False );
	return NULL;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseSquare::Positionate
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The node we want to positionate.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Positionate the owned vertex of the node on a sphere.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseSquare::Positionate( FSW_QuadTreeNode& CurNode )
{
	/* check for each central vertex if we need to create one new
	   or if it can be retrieve either from neighbor or from a pre-existing one */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex(i);
			FSW_ASSERT( pVert!=NULL );
			FSW_Vector3D Pos;
			FSW_U32 s = (i+1) % 3; 
			FSW_U32 t = (i+2) % 3;
			FSW_ASSERT( CurNode.GetVertex(s)!=NULL );
			FSW_ASSERT( CurNode.GetVertex(t)!=NULL );
			Pos = (CurNode.GetVertex(s)->GetPosition() + CurNode.GetVertex(t)->GetPosition())*0.5f;		// compute middle
			pVert->SetPosition(Pos);
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : FSW_BaseSquare::ConvertToLocalFrame
/**
 *  \param  Pos [FSW_Vector3D&] The position.
 *  \param  rU [FSW_Float&] X coord
 *  \param  rV [FSW_Float] Y coord
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Compute local coordinnate from 3D vector position.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseSquare::ConvertToLocalFrame( const FSW_Vector3D& Pos, FSW_Float& rU, FSW_Float& rV )
{
	/* U and V should be in [0,1]  */
	rU = 0.5f*(Pos[0] + 1);
	rV = 0.5f*(Pos[1] + 1);
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseSquare::GetNbrVertex
/**
 *  \param  nDepth [FSW_U32] The depth.
 *  \return [FSW_U32] Number of vertice.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of vertex on the subdivided version of the 
 *  mesh, at given depth.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseSquare::GetNbrVertex( FSW_U32 nDepth )
{
	return (nDepth+2)*(nDepth+2);
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseSquare::GetNbrFace
/**
 *  \param  nDepth [FSW_U32] Depth.
 *  \return [FSW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of face.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseSquare::GetNbrFace( FSW_U32 nDepth )
{
	return 2*( 1<<(2*nDepth) );	// 2*4^(nDepth)
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseSquare::GetNbrEdge
/**
 *  \param  nDepth [FSW_U32] The depth.
 *  \return [FSW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of edges.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseSquare::GetNbrEdge( FSW_U32 nDepth )
{
	return 1<<(2*nDepth);		// 4^(nDepth)
}




///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
