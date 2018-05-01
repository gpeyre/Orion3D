/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_DeltaFunction.cpp
 *  \brief  Definition of class \c FSW_DeltaFunction
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_DeltaFunction.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_DeltaFunction.h"

using namespace FSW;


/*------------------------------------------------------------------------------*/
// Name : FSW_DeltaFunction constructor
/**
 *  \param  nDepth [FSW_U32] the depth of the coefficient set to 1.
 *  \param  nCoefNum [FSW_U32] the number of the coefficient set to 1.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
FSW_DeltaFunction::FSW_DeltaFunction( FSW_U32 nDepth, FSW_U32 nCoefNum, FSW_U32 nVertNum, FSW_Float rSPike )
:	FSW_TreeFunction_ABC(),
	nDepth_		( nDepth ),
	nCoefNum_	( nCoefNum ),
	nVertNum_	( nVertNum ),
	rSPike_		( rSPike )
{
	FSW_ASSERT( nVertNum<3 );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_DeltaFunction destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_DeltaFunction::~FSW_DeltaFunction()
{
	/* NOTHING  */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_DeltaFunction::PostBuildTree
/**
 *  \param  Tree [FSW_QuadTree&] The tree.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Set the correct coefficient to 1.
 */
/*------------------------------------------------------------------------------*/
void FSW_DeltaFunction::PostBuildTree( FSW_QuadTree& Tree )
{
	if( !Tree.NodeMapExist( nDepth_ ) )
		return;
	FSW_NodeMap& NodeMap = Tree.GetNodeMap(nDepth_);
	T_QuadTreeNodeMap Map = NodeMap.GetMap();
	FSW_U32 nNum = 0;
	for( IT_QuadTreeNodeMap it = Map.begin(); it!=Map.end(); ++it )
	{
		if( nNum==nCoefNum_ )
		{
			FSW_QuadTreeNode* pNode = it->second;
			FSW_QuadTreeVertex* pVert = pNode->GetOwnedVertex(nVertNum_);
			if( pVert!=NULL );
				pVert->SetValue(rSPike_);
			return;
		}
		nNum++;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_DeltaFunction::SetDepth
/**
 *  \param  nDepth [FSW_U32] Depth
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the depth.
 */
/*------------------------------------------------------------------------------*/
void FSW_DeltaFunction::SetDepth( FSW_U32 nDepth )
{
	nDepth_ = nDepth;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_DeltaFunction::SetCoefNum
/**
 *  \param  nCoefNum [FSW_U32] Number.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the number of the coef.
 */
/*------------------------------------------------------------------------------*/
void FSW_DeltaFunction::SetCoefNum( FSW_U32 nCoefNum )
{
	nCoefNum_ = nCoefNum;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_DeltaFunction::SetVertNum
/**
 *  \param  nVertNum [FSW_U32] Number.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the vertex number.
 */
/*------------------------------------------------------------------------------*/
void FSW_DeltaFunction::SetVertNum( FSW_U32 nVertNum )
{
	nVertNum_ = nVertNum;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_DeltaFunction::SetSpikeValue
/**
 *  \param  rSPike [FSW_Float] Value.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the value of the spike.
 */
/*------------------------------------------------------------------------------*/
void FSW_DeltaFunction::SetSpikeValue( FSW_Float rSPike )
{
	rSPike_ = rSPike;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
