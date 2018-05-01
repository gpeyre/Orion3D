/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_LinearWavelet.cpp
 *  \brief  Definition of class \c GW_LinearWavelet
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_LinearWavelet.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_LinearWavelet.h"
#include "GW_NodeMap.h"

#ifndef GW_USE_INLINE
    #include "GW_LinearWavelet.inl"
#endif

using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_LinearWavelet::ForwardPredict
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void GW_LinearWavelet::ForwardPredict( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel)
{
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			/* predict stage *************************************/
			GW_U32 s = (i+1) % 3;
			GW_U32 t = (i+2) % 3;
			GW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			GW_QuadTreeVertex* pVert2 = CurNode.GetVertex( t );
			GW_Float rPredicted = 0.5f*( pVert1->GetValue()+pVert2->GetValue() );
			pVert->SetValue( pVert->GetValue()-rPredicted );		
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_LinearWavelet::ForwardUpdate
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void GW_LinearWavelet::ForwardUpdate( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
{
	GW_ASSERT( nReverseLevel>0 );
	/* for each vertex we are responsible for, update the value of it's neighbors */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			
			GW_U32 s = (i+1) % 3;
			GW_U32 t = (i+2) % 3;	

			/* retrieve the integral of the central scaling function */
			GW_IntegralDataChunk* pChunk = (GW_IntegralDataChunk*) pVert->GetDataChunk();
			GW_ASSERT( pChunk!=NULL );
			GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			GW_Float rIntegral_Center = pChunk->GetIntegral( nReverseLevel-1 );
			/* retrieve the first vertex scaling function */
			GW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			pChunk = (GW_IntegralDataChunk*) pVert1->GetDataChunk();
			GW_ASSERT( pChunk!=NULL );
			GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			GW_Float rIntegral = pChunk->GetIntegral( nReverseLevel );
			pVert1->SetValue( pVert1->GetValue()+rIntegral_Center/(2*rIntegral)*pVert->GetValue() );
			/* retrieve the second vertex scaling function */
			pVert1 = CurNode.GetVertex( t );
			pChunk = (GW_IntegralDataChunk*) pVert1->GetDataChunk();
			GW_ASSERT( pChunk!=NULL );
			GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			rIntegral = pChunk->GetIntegral( nReverseLevel );
			pVert1->SetValue( pVert1->GetValue()+rIntegral_Center/(2*rIntegral)*pVert->GetValue() );
		}
	}
}



/*------------------------------------------------------------------------------*/
// Name : GW_LinearWavelet::BackwardPredict
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a Backward step.
 */
/*------------------------------------------------------------------------------*/
void GW_LinearWavelet::BackwardPredict( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
{
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			/* predict stage *************************************/
			GW_U32 s = (i+1) % 3;
			GW_U32 t = (i+2) % 3;
			GW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			GW_QuadTreeVertex* pVert2 = CurNode.GetVertex( t );
			GW_Float rPredicted = 0.5f*( pVert1->GetValue()+pVert2->GetValue() );
			pVert->SetValue( pVert->GetValue() + rPredicted );		
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_LinearWavelet::ForwardUpdate
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void GW_LinearWavelet::BackwardUpdate( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
{
	GW_ASSERT( nReverseLevel>0 );
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			
			GW_U32 s = (i+1) % 3;
			GW_U32 t = (i+2) % 3;	

			/* retrieve the integral of the central scaling function */
			GW_IntegralDataChunk* pChunk = (GW_IntegralDataChunk*) pVert->GetDataChunk();
			GW_ASSERT( pChunk!=NULL );
			GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			GW_Float rIntegral_Center = pChunk->GetIntegral( nReverseLevel-1 );
			/* retrieve the first vertex scaling function */
			GW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			pChunk = (GW_IntegralDataChunk*) pVert1->GetDataChunk();
			GW_ASSERT( pChunk!=NULL );
			GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			GW_Float rIntegral = pChunk->GetIntegral( nReverseLevel );
			pVert1->SetValue( pVert1->GetValue()-rIntegral_Center/(2*rIntegral)*pVert->GetValue() );
			/* retrieve the second vertex scaling function */
			pVert1 = CurNode.GetVertex( t );
			pChunk = (GW_IntegralDataChunk*) pVert1->GetDataChunk();
			GW_ASSERT( pChunk!=NULL );
			GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			rIntegral = pChunk->GetIntegral( nReverseLevel );
			pVert1->SetValue( pVert1->GetValue()-rIntegral_Center/(2*rIntegral)*pVert->GetValue() );
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_LinearWavelet::UpdateDataChunk
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral of the vertex we are responsible for.
 */
/*------------------------------------------------------------------------------*/
void GW_LinearWavelet::UpdateDataChunk( T_NodeMapVector& NodeMapVector )
{
	/* first pass to compute the integral at the highest level ********************/
	RIT_NodeMapVector it = NodeMapVector.rbegin();
	GW_NodeMap* pMap = *it;
	GW_ASSERT( pMap!=NULL );

	T_QuadTreeNodeMap* pQuadTreeNodeMap = &pMap->GetMap();

	for( IT_QuadTreeNodeMap NodeTreeMapIT=pQuadTreeNodeMap->begin(); NodeTreeMapIT!=pQuadTreeNodeMap->end(); ++NodeTreeMapIT )
	{
		/* get the node */
		GW_QuadTreeNode* pNode = NodeTreeMapIT->second;
		GW_ASSERT( pNode!=NULL );
		this->ComputeIntegral( *pNode );
	}

	/* from the node just before leaf to root *************************************/
	it++;
	GW_U32 nLevel = 1;
	while( it != NodeMapVector.rend() )
	{
		pMap = *it;
		GW_ASSERT( pMap!=NULL );
		pQuadTreeNodeMap = &pMap->GetMap();

		/* first, recopy integral from uper level */
		for( IT_QuadTreeNodeMap NodeTreeMapIT=pQuadTreeNodeMap->begin(); NodeTreeMapIT!=pQuadTreeNodeMap->end(); ++NodeTreeMapIT )
		{
			/* get the node */
			GW_QuadTreeNode* pNode = NodeTreeMapIT->second;
			GW_ASSERT( pNode!=NULL );
			this->RecopyIntegral( *pNode, nLevel );
		}

		/* then use a recursion formula */
		for( IT_QuadTreeNodeMap NodeTreeMapIT=pQuadTreeNodeMap->begin(); NodeTreeMapIT!=pQuadTreeNodeMap->end(); ++NodeTreeMapIT )
		{
			/* get the node */
			GW_QuadTreeNode* pNode = NodeTreeMapIT->second;
			GW_ASSERT( pNode!=NULL );
			this->RecurseIntegral( *pNode, nLevel );
		}

		it++;
		nLevel++;
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_LinearWavelet::ComputeIntegral
/**
 *  \param  CurNode [GW_QuadTreeNode&] Curent node.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral of a node at the finest level using 
 *  quadrature formula.
 */
/*------------------------------------------------------------------------------*/
void GW_LinearWavelet::ComputeIntegral( GW_QuadTreeNode& CurNode )
{
	/* compute the integral for the 3 vertex (if needed) */
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_QuadTreeVertex* pVert = CurNode.GetVertex( i );
		GW_ASSERT( pVert!=NULL );
		/* if needed, create a new chunk */
		GW_IntegralDataChunk* pChunk = (GW_IntegralDataChunk*) pVert->GetDataChunk();
		if( pChunk==NULL )
		{
			pChunk = new GW_IntegralDataChunk;
			pVert->SetDataChunk(*pChunk);
			/* we need to compute this integral, au boulot ! */
			GW_QuadTreeVertex* pCurDirection	= CurNode.GetVertex( (i+1)%3 );
			GW_QuadTreeVertex* pNextDirection	= CurNode.GetVertex( (i+2)%3 );
			GW_QuadTreeNode* pNeighbor = CurNode.GetNeighbor(*pCurDirection);
			GW_Float rIntegral = GW_SphericalMaths::FlatTriangleArea(CurNode);
			GW_DEBUG_ONLY( GW_U32 nCheck = 0; )
			while( pNeighbor!=&CurNode )
			{
				GW_DEBUG_ONLY( nCheck++; )
				GW_Float rArea = GW_SphericalMaths::FlatTriangleArea(*pNeighbor);
				GW_ASSERT( rArea>=0 );
				rIntegral += rArea;
				/* check for new direction */
				pCurDirection	= pNextDirection;
				pNextDirection	= pNeighbor->GetCompletionVertex( *pVert, *pCurDirection );
				GW_ASSERT( pCurDirection!=NULL );
				pNeighbor = pNeighbor->GetNeighbor(*pCurDirection);
			}
		//	GW_ASSERT( nCheck==5 || nCheck==3);
			pChunk->SetIntegral( rIntegral/3, 0 );	// we are at level 0 starting from leaf
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : GW_LinearWavelet::RecopyIntegral
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \param  nLevel [GW_U32] The current level.
 *  \author Gabriel Peyré
 *  \date   11-13-2002
 * 
 *  Just recopy the integral from the level just before.
 */
/*------------------------------------------------------------------------------*/
void GW_LinearWavelet::RecopyIntegral( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
{
	GW_ASSERT( nReverseLevel>0 );
	/* copy the integral for the 3 vertex */
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_QuadTreeVertex* pVert = CurNode.GetVertex( i );
		GW_ASSERT( pVert!=NULL );
		/* the chunk should already exist */
		GW_IntegralDataChunk* pChunk = (GW_IntegralDataChunk*) pVert->GetDataChunk();
		GW_ASSERT( pChunk!=NULL );
		GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );

		/* simply recopy integral */
		pChunk->SetIntegral( pChunk->GetIntegral(nReverseLevel-1), nReverseLevel );
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_LinearWavelet::RecurseIntegral
/**
 *  \param  CurNode [GW_QuadTreeNode&] Current node.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral at a node using recursion.
 */
/*------------------------------------------------------------------------------*/
void GW_LinearWavelet::RecurseIntegral( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
{
	/* redistribuate contribution from the 3 owned vertex (the ones that disapear
	   between current low level and precedent level). */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			/* the chunk should already exist */
			GW_IntegralDataChunk* pChunk = (GW_IntegralDataChunk*) pVert->GetDataChunk();
			GW_ASSERT( pChunk!=NULL );
			GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );

			/* the numbers of the two vertex we should contribute to */
			GW_U32 s = (i+1)%3;
			GW_U32 t = (i+2)%3;

			GW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			GW_ASSERT( pVert1!=NULL );
			GW_IntegralDataChunk* pChunk1 = (GW_IntegralDataChunk*) pVert1->GetDataChunk();
			GW_ASSERT( pChunk1!=NULL );
			GW_ASSERT( pChunk1->GetType()==T_IntegralDataChunk );
			pChunk1->AddIntegral( 0.5f*pChunk->GetIntegral(nReverseLevel-1), nReverseLevel );

			
			pVert1 = CurNode.GetVertex( t );
			GW_ASSERT( pVert1!=NULL );
			pChunk1 = (GW_IntegralDataChunk*) pVert1->GetDataChunk();
			GW_ASSERT( pChunk1!=NULL );
			GW_ASSERT( pChunk1->GetType()==T_IntegralDataChunk );
			pChunk1->AddIntegral( 0.5f*pChunk->GetIntegral(nReverseLevel-1), nReverseLevel );		
		}
	}
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
