/*-----------------------------------------------------------------------------*/
/** 
 *  \file   GW_ButterflyWavelet.cpp
 *  \brief  Definition of class \c GW_ButterflyWavelet
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_ButterflyWavelet.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_ButterflyWavelet.h"
#include "GW_NodeMap.h"

#ifndef GW_USE_INLINE
    #include "GW_ButterflyWavelet.inl"
#endif

using namespace GW;


/*------------------------------------------------------------------------------*/
// Name : GW_ButterflyWavelet::Predict_Helper
/**
 *  \param  StencilVert [GW_QuadTreeVertex&] A vertex in the stencil.
 *  \param  rWeight [GW_Float] It's weight.
 *  \param  pChunk [void*] Should be the center vertex.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This function is called on each vertex of the stencil of a given 
 *  vertex to compute predicted value. So simple using \c GW_ButterflyWavelet::IterateFunctionOnLocalStencil !
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::Predict_Helper( GW_QuadTreeVertex& StencilVert, GW_Float rWeight, void* pChunk )
{
	GW_Float* pVal = (GW_Float*) pChunk;
	GW_ASSERT( pVal!=NULL );
	*pVal += StencilVert.GetValue()*rWeight;
}

/*------------------------------------------------------------------------------*/
// Name : GW_ButterflyWavelet::Update_Helper
/**
 *  \param  StencilVert [GW_QuadTreeVertex&] A vertex in the stencil.
 *  \param  rWeight [GW_Float] It's weight.
 *  \param  pChunk [void*] Should be the center vertex.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This function is called on each vertex of the stencil of a given 
 *  vertex to update their value. So simple using \c GW_ButterflyWavelet::IterateFunctionOnLocalStencil !
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::Update_Helper( GW_QuadTreeVertex& StencilVert, GW_Float rWeight, void* pChunk )
{
	T_ButterflyUpdateChunk* pUpdateCunk = (T_ButterflyUpdateChunk*) pChunk;
	GW_ASSERT( pUpdateCunk!=NULL );
	/* get the integral of the stencil vertex */
	GW_IntegralDataChunk* pIntegralDataChunk = (GW_IntegralDataChunk*) StencilVert.GetDataChunk();
	GW_ASSERT( pIntegralDataChunk!=NULL );
	GW_ASSERT( pIntegralDataChunk->GetType()==T_IntegralDataChunk );
	GW_Float rIntegral = pIntegralDataChunk->GetIntegral( pUpdateCunk->nReverseLevel_ );
	/* lift the value */
	GW_Float rUpdateVal = rWeight*pUpdateCunk->rCentralIntegral_/rIntegral * pUpdateCunk->pCentralVert_->GetValue();
	if( !pUpdateCunk->bForwardUpdate_ )
		rUpdateVal = -rUpdateVal;
	StencilVert.SetValue( StencilVert.GetValue() + rUpdateVal );
}

/*------------------------------------------------------------------------------*/
// Name : GW_ButterflyWavelet::ForwardPredict
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::ForwardPredict( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel)
{
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			/* compute the prediced value using iteration on the stencil */
			GW_Float rPredictedValue = 0;
			GW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Predict_Helper, i, &rPredictedValue );
			pVert->SetValue( pVert->GetValue()-rPredictedValue );	
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : GW_ButterflyWavelet::ForwardUpdate
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::ForwardUpdate( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
{
	GW_ASSERT( nReverseLevel>0 );
	/* for each vertex we are responsible for, update the value of it's neighbors */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			
			/* retrieve the integral of the central scaling function */
			GW_IntegralDataChunk* pChunk = (GW_IntegralDataChunk*) pVert->GetDataChunk();
			GW_ASSERT( pChunk!=NULL );
			GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			GW_Float rIntegral_Center = pChunk->GetIntegral( nReverseLevel-1 );

			/* lift the values on the stencil using iteration on the stencil */
			T_ButterflyUpdateChunk UpdateChunk( rIntegral_Center, pVert, nReverseLevel, GW_True );
			GW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Update_Helper, i, &UpdateChunk );
		}
	}
}



/*------------------------------------------------------------------------------*/
// Name : GW_ButterflyWavelet::BackwardPredict
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a Backward step.
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::BackwardPredict( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
{
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			/* compute the prediced value using iteration on the stencil */
			GW_Float rPredictedValue = 0;
			GW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Predict_Helper, i, &rPredictedValue );
			pVert->SetValue( pVert->GetValue()+rPredictedValue );
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_ButterflyWavelet::ForwardUpdate
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::BackwardUpdate( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
{
	GW_ASSERT( nReverseLevel>0 );
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			
			/* retrieve the integral of the central scaling function */
			GW_IntegralDataChunk* pChunk = (GW_IntegralDataChunk*) pVert->GetDataChunk();
			GW_ASSERT( pChunk!=NULL );
			GW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			GW_Float rIntegral_Center = pChunk->GetIntegral( nReverseLevel-1 );

			/* lift the values on the stencil using iteration on the stencil */
			T_ButterflyUpdateChunk UpdateChunk( rIntegral_Center, pVert, nReverseLevel, GW_False );
			GW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Update_Helper, i, &UpdateChunk );
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_ButterflyWavelet::UpdateDataChunk
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral of the vertex we are responsible for.
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::UpdateDataChunk( T_NodeMapVector& NodeMapVector )
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
// Name : GW_ButterflyWavelet::ComputeIntegral
/**
 *  \param  CurNode [GW_QuadTreeNode&] Curent node.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral of a node at the finest level using 
 *  quadrature formula.
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::ComputeIntegral( GW_QuadTreeNode& CurNode )
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
// Name : GW_ButterflyWavelet::RecopyIntegral
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \param  nLevel [GW_U32] The current level.
 *  \author Gabriel Peyré
 *  \date   11-13-2002
 * 
 *  Just recopy the integral from the level just before.
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::RecopyIntegral( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
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
// Name : GW_ButterflyWavelet::RecurseIntegral_Helper
/**
 *  \param  StencilVert [GW_QuadTreeVertex&] A vertex in the stencil.
 *  \param  rWeight [GW_Float] It's weight.
 *  \param  pChunk [void*] Should be the center vertex.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This function is called on each vertex of the stencil of a given 
 *  vertex to compute the integral at a given depth. So simple using \c GW_ButterflyWavelet::IterateFunctionOnLocalStencil !
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::RecurseIntegral_Helper( GW_QuadTreeVertex& StencilVert, GW_Float rWeight, void* pChunk )
{
	T_ButterflyRecurseIntegralChunk* pRecurseIntegralChunk = (T_ButterflyRecurseIntegralChunk*) pChunk;
	GW_IntegralDataChunk* pChunk1 = (GW_IntegralDataChunk*) StencilVert.GetDataChunk();
	GW_ASSERT( pChunk1!=NULL );
	GW_ASSERT( pChunk1->GetType()==T_IntegralDataChunk );
	pChunk1->AddIntegral( rWeight*pRecurseIntegralChunk->rCentralIntegral_, pRecurseIntegralChunk->nReverseLevel_ );
}

/*------------------------------------------------------------------------------*/
// Name : GW_ButterflyWavelet::RecurseIntegral
/**
 *  \param  CurNode [GW_QuadTreeNode&] Current node.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral at a node using recursion.
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::RecurseIntegral( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel )
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

			/* lift the values on the stencil using iteration on the stencil */
			T_ButterflyRecurseIntegralChunk RecurseIntegralChunk( pChunk->GetIntegral(nReverseLevel-1), nReverseLevel );
			GW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, RecurseIntegral_Helper, i, &RecurseIntegralChunk );	
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_ButterflyWavelet::IterateFunctionOnLocalStencil
/**
 *  \param  CurNode [GW_QuadTreeNode&] Base node of the stencil.
 *  \param  pChunk [void*] A chunk passed to the function.
 *  \return nVert [GW_U32] The number of the vertex we are dealing with.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This is a usefull helper method. This calls a function on each vertex member of the stencil
 *	arround the vertex number \c nVert of node \c CurNode. This pass the weight of the vertex and the vertex to the function.
 */
/*------------------------------------------------------------------------------*/
void GW_ButterflyWavelet::IterateFunctionOnLocalStencil( GW_QuadTreeNode& CurNode, T_FunctionApplyableOnStencil pFunc, GW_U32 nVert, void* pChunk, GW_Float w )
{
	/* for v1 & v2 : weight 1/2 */
	GW_U32 s = (nVert+1) % 3; 
	GW_U32 t = (nVert+2) % 3;
	GW_QuadTreeVertex* v1 = CurNode.GetVertex(s);
	GW_QuadTreeVertex* v2 = CurNode.GetVertex(t);
	GW_ASSERT( v1!=NULL );
	GW_ASSERT( v2!=NULL );
	pFunc( *v1, BUTTERFLY_WEIGHT_V, pChunk );		// v1
	pFunc( *v2, BUTTERFLY_WEIGHT_V, pChunk );		// v2
	/* for f1 & f2 : weight 1/8 */
	GW_QuadTreeVertex* f1 = CurNode.GetVertex(nVert);
	GW_ASSERT( f1!=NULL );
	pFunc( *f1, BUTTERFLY_WEIGHT_F+2*w, pChunk );	// f1
	GW_QuadTreeNode* pNodeDown = CurNode.GetNeighbor( *f1 );
	GW_ASSERT( pNodeDown!=NULL );
	GW_QuadTreeVertex* f2 = pNodeDown->GetVertex( *v1,*v2 );
	GW_ASSERT( f2!=NULL );
	pFunc( *f2, BUTTERFLY_WEIGHT_F+2*w, pChunk );					// f2
	/*  for e3 weight -1/16 */
	GW_QuadTreeNode* pNode1 = pNodeDown->GetNeighbor( *v2 );
	GW_ASSERT( pNode1!=NULL );
	GW_QuadTreeVertex* pVert1 = pNode1->GetVertex( *v1,*f2 );
	GW_ASSERT( pVert1!=NULL );
	pFunc( *pVert1, BUTTERFLY_WEIGHT_E-w, pChunk );					// e3
	/* e4 weight -1/16 */
	pNode1 = pNodeDown->GetNeighbor( *v1 );
	GW_ASSERT( pNode1!=NULL );
	pVert1 = pNode1->GetVertex( *v2,*f2 );
	GW_ASSERT( pVert1!=NULL );
	pFunc( *pVert1, BUTTERFLY_WEIGHT_E-w, pChunk );					// e4
	/* e1 weight -1/16 */
	pNode1 = CurNode.GetNeighbor( *v2 );
	GW_ASSERT( pNode1!=NULL );
	pVert1 = pNode1->GetVertex( *v1,*f1 );
	GW_ASSERT( pVert1!=NULL );
	pFunc( *pVert1, BUTTERFLY_WEIGHT_E-w, pChunk );				// e1
	/* e2 weight -1/16 */
	pNode1 = CurNode.GetNeighbor( *v1 );
	GW_ASSERT( pNode1!=NULL );
	pVert1 = pNode1->GetVertex( *v2,*f1 );
	GW_ASSERT( pVert1!=NULL );
	pFunc( *pVert1, BUTTERFLY_WEIGHT_E-w, pChunk );				// e1
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
