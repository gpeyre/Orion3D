/*-----------------------------------------------------------------------------*/
/** 
 *  \file   FSW_ButterflyWavelet.cpp
 *  \brief  Definition of class \c FSW_ButterflyWavelet
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_ButterflyWavelet.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_ButterflyWavelet.h"
#include "FSW_NodeMap.h"

#ifndef FSW_USE_INLINE
    #include "FSW_ButterflyWavelet.inl"
#endif

using namespace FSW;


/*------------------------------------------------------------------------------*/
// Name : FSW_ButterflyWavelet::Predict_Helper
/**
 *  \param  StencilVert [FSW_QuadTreeVertex&] A vertex in the stencil.
 *  \param  rWeight [FSW_Float] It's weight.
 *  \param  pChunk [void*] Should be the center vertex.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This function is called on each vertex of the stencil of a given 
 *  vertex to compute predicted value. So simple using \c FSW_ButterflyWavelet::IterateFunctionOnLocalStencil !
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::Predict_Helper( FSW_QuadTreeVertex& StencilVert, FSW_Float rWeight, void* pChunk )
{
	FSW_Float* pVal = (FSW_Float*) pChunk;
	FSW_ASSERT( pVal!=NULL );
	*pVal += StencilVert.GetValue()*rWeight;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ButterflyWavelet::Update_Helper
/**
 *  \param  StencilVert [FSW_QuadTreeVertex&] A vertex in the stencil.
 *  \param  rWeight [FSW_Float] It's weight.
 *  \param  pChunk [void*] Should be the center vertex.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This function is called on each vertex of the stencil of a given 
 *  vertex to update their value. So simple using \c FSW_ButterflyWavelet::IterateFunctionOnLocalStencil !
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::Update_Helper( FSW_QuadTreeVertex& StencilVert, FSW_Float rWeight, void* pChunk )
{
	T_ButterflyUpdateChunk* pUpdateCunk = (T_ButterflyUpdateChunk*) pChunk;
	FSW_ASSERT( pUpdateCunk!=NULL );
	/* get the integral of the stencil vertex */
	FSW_IntegralDataChunk* pIntegralDataChunk = (FSW_IntegralDataChunk*) StencilVert.GetDataChunk();
	FSW_ASSERT( pIntegralDataChunk!=NULL );
	FSW_ASSERT( pIntegralDataChunk->GetType()==T_IntegralDataChunk );
	FSW_Float rIntegral = pIntegralDataChunk->GetIntegral( pUpdateCunk->nReverseLevel_ );
	/* lift the value */
	FSW_Float rUpdateVal = rWeight*pUpdateCunk->rCentralIntegral_/rIntegral * pUpdateCunk->pCentralVert_->GetValue();
	if( !pUpdateCunk->bForwardUpdate_ )
		rUpdateVal = -rUpdateVal;
	StencilVert.SetValue( StencilVert.GetValue() + rUpdateVal );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ButterflyWavelet::ForwardPredict
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::ForwardPredict( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel)
{
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			/* compute the prediced value using iteration on the stencil */
			FSW_Float rPredictedValue = 0;
			FSW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Predict_Helper, i, &rPredictedValue );
			pVert->SetValue( pVert->GetValue()-rPredictedValue );	
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : FSW_ButterflyWavelet::ForwardUpdate
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::ForwardUpdate( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
{
	FSW_ASSERT( nReverseLevel>0 );
	/* for each vertex we are responsible for, update the value of it's neighbors */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			
			/* retrieve the integral of the central scaling function */
			FSW_IntegralDataChunk* pChunk = (FSW_IntegralDataChunk*) pVert->GetDataChunk();
			FSW_ASSERT( pChunk!=NULL );
			FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			FSW_Float rIntegral_Center = pChunk->GetIntegral( nReverseLevel-1 );

			/* lift the values on the stencil using iteration on the stencil */
			T_ButterflyUpdateChunk UpdateChunk( rIntegral_Center, pVert, nReverseLevel, FSW_True );
			FSW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Update_Helper, i, &UpdateChunk );
		}
	}
}



/*------------------------------------------------------------------------------*/
// Name : FSW_ButterflyWavelet::BackwardPredict
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a Backward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::BackwardPredict( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
{
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			/* compute the prediced value using iteration on the stencil */
			FSW_Float rPredictedValue = 0;
			FSW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Predict_Helper, i, &rPredictedValue );
			pVert->SetValue( pVert->GetValue()+rPredictedValue );
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ButterflyWavelet::ForwardUpdate
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::BackwardUpdate( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
{
	FSW_ASSERT( nReverseLevel>0 );
	/* compute the detail coefficient for the central vertex we are responsible for */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			
			/* retrieve the integral of the central scaling function */
			FSW_IntegralDataChunk* pChunk = (FSW_IntegralDataChunk*) pVert->GetDataChunk();
			FSW_ASSERT( pChunk!=NULL );
			FSW_ASSERT( pChunk->GetType()==T_IntegralDataChunk );
			FSW_Float rIntegral_Center = pChunk->GetIntegral( nReverseLevel-1 );

			/* lift the values on the stencil using iteration on the stencil */
			T_ButterflyUpdateChunk UpdateChunk( rIntegral_Center, pVert, nReverseLevel, FSW_False );
			FSW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Update_Helper, i, &UpdateChunk );
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ButterflyWavelet::UpdateDataChunk
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral of the vertex we are responsible for.
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::UpdateDataChunk( T_NodeMapVector& NodeMapVector )
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
// Name : FSW_ButterflyWavelet::ComputeIntegral
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Curent node.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral of a node at the finest level using 
 *  quadrature formula.
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::ComputeIntegral( FSW_QuadTreeNode& CurNode )
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
// Name : FSW_ButterflyWavelet::RecopyIntegral
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \param  nLevel [FSW_U32] The current level.
 *  \author Gabriel Peyré
 *  \date   11-13-2002
 * 
 *  Just recopy the integral from the level just before.
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::RecopyIntegral( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
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
// Name : FSW_ButterflyWavelet::RecurseIntegral_Helper
/**
 *  \param  StencilVert [FSW_QuadTreeVertex&] A vertex in the stencil.
 *  \param  rWeight [FSW_Float] It's weight.
 *  \param  pChunk [void*] Should be the center vertex.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This function is called on each vertex of the stencil of a given 
 *  vertex to compute the integral at a given depth. So simple using \c FSW_ButterflyWavelet::IterateFunctionOnLocalStencil !
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::RecurseIntegral_Helper( FSW_QuadTreeVertex& StencilVert, FSW_Float rWeight, void* pChunk )
{
	T_ButterflyRecurseIntegralChunk* pRecurseIntegralChunk = (T_ButterflyRecurseIntegralChunk*) pChunk;
	FSW_IntegralDataChunk* pChunk1 = (FSW_IntegralDataChunk*) StencilVert.GetDataChunk();
	FSW_ASSERT( pChunk1!=NULL );
	FSW_ASSERT( pChunk1->GetType()==T_IntegralDataChunk );
	pChunk1->AddIntegral( rWeight*pRecurseIntegralChunk->rCentralIntegral_, pRecurseIntegralChunk->nReverseLevel_ );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ButterflyWavelet::RecurseIntegral
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Current node.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Compute the integral at a node using recursion.
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::RecurseIntegral( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel )
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

			/* lift the values on the stencil using iteration on the stencil */
			T_ButterflyRecurseIntegralChunk RecurseIntegralChunk( pChunk->GetIntegral(nReverseLevel-1), nReverseLevel );
			FSW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, RecurseIntegral_Helper, i, &RecurseIntegralChunk );	
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ButterflyWavelet::IterateFunctionOnLocalStencil
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Base node of the stencil.
 *  \param  pChunk [void*] A chunk passed to the function.
 *  \return nVert [FSW_U32] The number of the vertex we are dealing with.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This is a usefull helper method. This calls a function on each vertex member of the stencil
 *	arround the vertex number \c nVert of node \c CurNode. This pass the weight of the vertex and the vertex to the function.
 */
/*------------------------------------------------------------------------------*/
void FSW_ButterflyWavelet::IterateFunctionOnLocalStencil( FSW_QuadTreeNode& CurNode, T_FunctionApplyableOnStencil pFunc, FSW_U32 nVert, void* pChunk, FSW_Float w )
{
	/* for v1 & v2 : weight 1/2 */
	FSW_U32 s = (nVert+1) % 3; 
	FSW_U32 t = (nVert+2) % 3;
	FSW_QuadTreeVertex* v1 = CurNode.GetVertex(s);
	FSW_QuadTreeVertex* v2 = CurNode.GetVertex(t);
	FSW_ASSERT( v1!=NULL );
	FSW_ASSERT( v2!=NULL );
	pFunc( *v1, BUTTERFLY_WEIGHT_V, pChunk );		// v1
	pFunc( *v2, BUTTERFLY_WEIGHT_V, pChunk );		// v2
	/* for f1 & f2 : weight 1/8 */
	FSW_QuadTreeVertex* f1 = CurNode.GetVertex(nVert);
	FSW_ASSERT( f1!=NULL );
	pFunc( *f1, BUTTERFLY_WEIGHT_F+2*w, pChunk );	// f1
	FSW_QuadTreeNode* pNodeDown = CurNode.GetNeighbor( *f1 );
	FSW_ASSERT( pNodeDown!=NULL );
	FSW_QuadTreeVertex* f2 = pNodeDown->GetVertex( *v1,*v2 );
	FSW_ASSERT( f2!=NULL );
	pFunc( *f2, BUTTERFLY_WEIGHT_F+2*w, pChunk );					// f2
	/*  for e3 weight -1/16 */
	FSW_QuadTreeNode* pNode1 = pNodeDown->GetNeighbor( *v2 );
	FSW_ASSERT( pNode1!=NULL );
	FSW_QuadTreeVertex* pVert1 = pNode1->GetVertex( *v1,*f2 );
	FSW_ASSERT( pVert1!=NULL );
	pFunc( *pVert1, BUTTERFLY_WEIGHT_E-w, pChunk );					// e3
	/* e4 weight -1/16 */
	pNode1 = pNodeDown->GetNeighbor( *v1 );
	FSW_ASSERT( pNode1!=NULL );
	pVert1 = pNode1->GetVertex( *v2,*f2 );
	FSW_ASSERT( pVert1!=NULL );
	pFunc( *pVert1, BUTTERFLY_WEIGHT_E-w, pChunk );					// e4
	/* e1 weight -1/16 */
	pNode1 = CurNode.GetNeighbor( *v2 );
	FSW_ASSERT( pNode1!=NULL );
	pVert1 = pNode1->GetVertex( *v1,*f1 );
	FSW_ASSERT( pVert1!=NULL );
	pFunc( *pVert1, BUTTERFLY_WEIGHT_E-w, pChunk );				// e1
	/* e2 weight -1/16 */
	pNode1 = CurNode.GetNeighbor( *v1 );
	FSW_ASSERT( pNode1!=NULL );
	pVert1 = pNode1->GetVertex( *v2,*f1 );
	FSW_ASSERT( pVert1!=NULL );
	pFunc( *pVert1, BUTTERFLY_WEIGHT_E-w, pChunk );				// e1
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
