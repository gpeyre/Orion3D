/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_LinearWavelet.cpp
 *  \brief  Definition of class \c FSW_LinearWavelet
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_LinearWavelet.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_LinearWavelet.h"
#include "FSW_NodeMap.h"

#ifndef FSW_USE_INLINE
    #include "FSW_LinearWavelet.inl"
#endif

using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_LinearWavelet::ForwardPredict
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_LinearWavelet::ForwardPredict( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel)
{
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			/* predict stage *************************************/
			FSW_U32 s = (i+1) % 3;
			FSW_U32 t = (i+2) % 3;
			FSW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			FSW_QuadTreeVertex* pVert2 = CurNode.GetVertex( t );
			FSW_Float rPredicted = 0.5f*( pVert1->GetValue()+pVert2->GetValue() );
			pVert->SetValue( pVert->GetValue()-rPredicted );		
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_LinearWavelet::ForwardUpdate
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_LinearWavelet::ForwardUpdate( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
{
	FSW_ASSERT( nReverseLevel>0 );
	/* for each vertex we are responsible for, update the value of it's neighbors */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			
			FSW_U32 s = (i+1) % 3;
			FSW_U32 t = (i+2) % 3;	

			/* retrieve the integral of the central scaling function */
			FSW_IntegralDataChunk* pChunk = (FSW_IntegralDataChunk*) pVert->GetDataChunk();
			FSW_ASSERT( pChunk!=NULL );
			FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			FSW_Float rIntegral_Center = pChunk->GetIntegral( nReverseLevel-1 );
			/* retrieve the first vertex scaling function */
			FSW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			pChunk = (FSW_IntegralDataChunk*) pVert1->GetDataChunk();
			FSW_ASSERT( pChunk!=NULL );
			FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			FSW_Float rIntegral = pChunk->GetIntegral( nReverseLevel );
			pVert1->SetValue( pVert1->GetValue()+rIntegral_Center/(2*rIntegral)*pVert->GetValue() );
			/* retrieve the second vertex scaling function */
			pVert1 = CurNode.GetVertex( t );
			pChunk = (FSW_IntegralDataChunk*) pVert1->GetDataChunk();
			FSW_ASSERT( pChunk!=NULL );
			FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			rIntegral = pChunk->GetIntegral( nReverseLevel );
			pVert1->SetValue( pVert1->GetValue()+rIntegral_Center/(2*rIntegral)*pVert->GetValue() );
		}
	}
}



/*------------------------------------------------------------------------------*/
// Name : FSW_LinearWavelet::BackwardPredict
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a Backward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_LinearWavelet::BackwardPredict( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
{
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			/* predict stage *************************************/
			FSW_U32 s = (i+1) % 3;
			FSW_U32 t = (i+2) % 3;
			FSW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			FSW_QuadTreeVertex* pVert2 = CurNode.GetVertex( t );
			FSW_Float rPredicted = 0.5f*( pVert1->GetValue()+pVert2->GetValue() );
			pVert->SetValue( pVert->GetValue() + rPredicted );		
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_LinearWavelet::ForwardUpdate
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_LinearWavelet::BackwardUpdate( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
{
	FSW_ASSERT( nReverseLevel>0 );
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			
			FSW_U32 s = (i+1) % 3;
			FSW_U32 t = (i+2) % 3;	

			/* retrieve the integral of the central scaling function */
			FSW_IntegralDataChunk* pChunk = (FSW_IntegralDataChunk*) pVert->GetDataChunk();
			FSW_ASSERT( pChunk!=NULL );
			FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			FSW_Float rIntegral_Center = pChunk->GetIntegral( nReverseLevel-1 );
			/* retrieve the first vertex scaling function */
			FSW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			pChunk = (FSW_IntegralDataChunk*) pVert1->GetDataChunk();
			FSW_ASSERT( pChunk!=NULL );
			FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			FSW_Float rIntegral = pChunk->GetIntegral( nReverseLevel );
			pVert1->SetValue( pVert1->GetValue()-rIntegral_Center/(2*rIntegral)*pVert->GetValue() );
			/* retrieve the second vertex scaling function */
			pVert1 = CurNode.GetVertex( t );
			pChunk = (FSW_IntegralDataChunk*) pVert1->GetDataChunk();
			FSW_ASSERT( pChunk!=NULL );
			FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			rIntegral = pChunk->GetIntegral( nReverseLevel );
			pVert1->SetValue( pVert1->GetValue()-rIntegral_Center/(2*rIntegral)*pVert->GetValue() );
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_LinearWavelet::UpdateDataChunk
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral of the vertex we are responsible for.
 */
/*------------------------------------------------------------------------------*/
void FSW_LinearWavelet::UpdateDataChunk( T_NodeMapVector& NodeMapVector )
{
	/* first pass to compute the integral at the highest level ********************/
	RIT_NodeMapVector it = NodeMapVector.rbegin();
	FSW_NodeMap* pMap = *it;
	FSW_ASSERT( pMap!=NULL );

	T_QuadTreeNodeMap* pQuadTreeNodeMap = &pMap->GetMap();

	for( IT_QuadTreeNodeMap NodeTreeMapIT=pQuadTreeNodeMap->begin(); NodeTreeMapIT!=pQuadTreeNodeMap->end(); ++NodeTreeMapIT )
	{
		/* get the node */
		FSW_QuadTreeNode* pNode = NodeTreeMapIT->second;
		FSW_ASSERT( pNode!=NULL );
		this->ComputeIntegral( *pNode );
	}

	/* from the node just before leaf to root *************************************/
	it++;
	FSW_U32 nLevel = 1;
	while( it != NodeMapVector.rend() )
	{
		pMap = *it;
		FSW_ASSERT( pMap!=NULL );
		pQuadTreeNodeMap = &pMap->GetMap();

		/* first, recopy integral from uper level */
		for( IT_QuadTreeNodeMap NodeTreeMapIT=pQuadTreeNodeMap->begin(); NodeTreeMapIT!=pQuadTreeNodeMap->end(); ++NodeTreeMapIT )
		{
			/* get the node */
			FSW_QuadTreeNode* pNode = NodeTreeMapIT->second;
			FSW_ASSERT( pNode!=NULL );
			this->RecopyIntegral( *pNode, nLevel );
		}

		/* then use a recursion formula */
		for( IT_QuadTreeNodeMap NodeTreeMapIT=pQuadTreeNodeMap->begin(); NodeTreeMapIT!=pQuadTreeNodeMap->end(); ++NodeTreeMapIT )
		{
			/* get the node */
			FSW_QuadTreeNode* pNode = NodeTreeMapIT->second;
			FSW_ASSERT( pNode!=NULL );
			this->RecurseIntegral( *pNode, nLevel );
		}

		it++;
		nLevel++;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_LinearWavelet::ComputeIntegral
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Curent node.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral of a node at the finest level using 
 *  quadrature formula.
 */
/*------------------------------------------------------------------------------*/
void FSW_LinearWavelet::ComputeIntegral( FSW_QuadTreeNode& CurNode )
{
	/* compute the integral for the 3 vertex (if needed) */
	for( FSW_U32 i=0; i<3; ++i )
	{
		FSW_QuadTreeVertex* pVert = CurNode.GetVertex( i );
		FSW_ASSERT( pVert!=NULL );
		/* if needed, create a new chunk */
		FSW_IntegralDataChunk* pChunk = (FSW_IntegralDataChunk*) pVert->GetDataChunk();
		if( pChunk==NULL )
		{
			pChunk = new FSW_IntegralDataChunk;
			pVert->SetDataChunk(*pChunk);
			/* we need to compute this integral, au boulot ! */
			FSW_QuadTreeVertex* pCurDirection	= CurNode.GetVertex( (i+1)%3 );
			FSW_QuadTreeVertex* pNextDirection	= CurNode.GetVertex( (i+2)%3 );
			FSW_QuadTreeNode* pNeighbor = CurNode.GetNeighbor(*pCurDirection);
			FSW_Float rIntegral = FSW_Maths::FlatTriangleArea(CurNode);
			FSW_DEBUG_ONLY( FSW_U32 nCheck = 0; )
			while( pNeighbor!=&CurNode )
			{
				FSW_DEBUG_ONLY( nCheck++; )
				FSW_Float rArea = FSW_Maths::FlatTriangleArea(*pNeighbor);
				FSW_ASSERT( rArea>=0 );
				rIntegral += rArea;
				/* check for new direction */
				pCurDirection	= pNextDirection;
				pNextDirection	= pNeighbor->GetCompletionVertex( *pVert, *pCurDirection );
				FSW_ASSERT( pCurDirection!=NULL );
				pNeighbor = pNeighbor->GetNeighbor(*pCurDirection);
			}
		//	FSW_ASSERT( nCheck==5 || nCheck==3);
			pChunk->SetIntegral( rIntegral/3, 0 );	// we are at level 0 starting from leaf
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : FSW_LinearWavelet::RecopyIntegral
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \param  nLevel [FSW_U32] The current level.
 *  \author Gabriel Peyré
 *  \date   11-13-2002
 * 
 *  Just recopy the integral from the level just before.
 */
/*------------------------------------------------------------------------------*/
void FSW_LinearWavelet::RecopyIntegral( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
{
	FSW_ASSERT( nReverseLevel>0 );
	/* copy the integral for the 3 vertex */
	for( FSW_U32 i=0; i<3; ++i )
	{
		FSW_QuadTreeVertex* pVert = CurNode.GetVertex( i );
		FSW_ASSERT( pVert!=NULL );
		/* the chunk should already exist */
		FSW_IntegralDataChunk* pChunk = (FSW_IntegralDataChunk*) pVert->GetDataChunk();
		FSW_ASSERT( pChunk!=NULL );
		FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );

		/* simply recopy integral */
		pChunk->SetIntegral( pChunk->GetIntegral(nReverseLevel-1), nReverseLevel );
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_LinearWavelet::RecurseIntegral
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Current node.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral at a node using recursion.
 */
/*------------------------------------------------------------------------------*/
void FSW_LinearWavelet::RecurseIntegral( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
{
	/* redistribuate contribution from the 3 owned vertex (the ones that disapear
	   between current low level and precedent level). */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			/* the chunk should already exist */
			FSW_IntegralDataChunk* pChunk = (FSW_IntegralDataChunk*) pVert->GetDataChunk();
			FSW_ASSERT( pChunk!=NULL );
			FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );

			/* the numbers of the two vertex we should contribute to */
			FSW_U32 s = (i+1)%3;
			FSW_U32 t = (i+2)%3;

			FSW_QuadTreeVertex* pVert1 = CurNode.GetVertex( s );
			FSW_ASSERT( pVert1!=NULL );
			FSW_IntegralDataChunk* pChunk1 = (FSW_IntegralDataChunk*) pVert1->GetDataChunk();
			FSW_ASSERT( pChunk1!=NULL );
			FSW_ASSERT( pChunk1->GetType()==T_IntegralDataChunk );
			pChunk1->AddIntegral( 0.5f*pChunk->GetIntegral(nReverseLevel-1), nReverseLevel );

			
			pVert1 = CurNode.GetVertex( t );
			FSW_ASSERT( pVert1!=NULL );
			pChunk1 = (FSW_IntegralDataChunk*) pVert1->GetDataChunk();
			FSW_ASSERT( pChunk1!=NULL );
			FSW_ASSERT( pChunk1->GetType()==T_IntegralDataChunk );
			pChunk1->AddIntegral( 0.5f*pChunk->GetIntegral(nReverseLevel-1), nReverseLevel );		
		}
	}
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
