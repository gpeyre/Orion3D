/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_DeltaFunction.cpp
 *  \brief  Definition of class \c GW_DeltaFunction
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_DeltaFunction.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_DeltaFunction.h"

using namespace GW;


/*------------------------------------------------------------------------------*/
// Name : GW_DeltaFunction constructor
/**
 *  \param  nDepth [GW_U32] the depth of the coefficient set to 1.
 *  \param  nCoefNum [GW_U32] the number of the coefficient set to 1.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
GW_DeltaFunction::GW_DeltaFunction( GW_U32 nDepth, GW_U32 nCoefNum, GW_U32 nVertNum, GW_Float rSPike )
:	GW_TreeFunction_ABC(),
	nDepth_		( nDepth ),
	nCoefNum_	( nCoefNum ),
	nVertNum_	( nVertNum ),
	rSPike_		( rSPike )
{
	GW_ASSERT( nVertNum<3 );
}

/*------------------------------------------------------------------------------*/
// Name : GW_DeltaFunction destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_DeltaFunction::~GW_DeltaFunction()
{
	/* NOTHING  */
}

/*------------------------------------------------------------------------------*/
// Name : GW_DeltaFunction::PostBuildTree
/**
 *  \param  Tree [GW_QuadTree&] The tree.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Set the correct coefficient to 1.
 */
/*------------------------------------------------------------------------------*/
void GW_DeltaFunction::PostBuildTree( GW_QuadTree& Tree )
{
	if( !Tree.NodeMapExist( nDepth_ ) )
		return;
	GW_NodeMap& NodeMap = Tree.GetNodeMap(nDepth_);
	T_QuadTreeNodeMap Map = NodeMap.GetMap();
	GW_U32 nNum = 0;
	for( IT_QuadTreeNodeMap it = Map.begin(); it!=Map.end(); ++it )
	{
		if( nNum==nCoefNum_ )
		{
			GW_QuadTreeNode* pNode = it->second;
			GW_QuadTreeVertex* pVert = pNode->GetOwnedVertex(nVertNum_);
			if( pVert!=NULL );
				pVert->SetValue(rSPike_);
			return;
		}
		nNum++;
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_DeltaFunction::SetDepth
/**
 *  \param  nDepth [GW_U32] Depth
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the depth.
 */
/*------------------------------------------------------------------------------*/
void GW_DeltaFunction::SetDepth( GW_U32 nDepth )
{
	nDepth_ = nDepth;
}

/*------------------------------------------------------------------------------*/
// Name : GW_DeltaFunction::SetCoefNum
/**
 *  \param  nCoefNum [GW_U32] Number.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the number of the coef.
 */
/*------------------------------------------------------------------------------*/
void GW_DeltaFunction::SetCoefNum( GW_U32 nCoefNum )
{
	nCoefNum_ = nCoefNum;
}

/*------------------------------------------------------------------------------*/
// Name : GW_DeltaFunction::SetVertNum
/**
 *  \param  nVertNum [GW_U32] Number.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the vertex number.
 */
/*------------------------------------------------------------------------------*/
void GW_DeltaFunction::SetVertNum( GW_U32 nVertNum )
{
	nVertNum_ = nVertNum;
}

/*------------------------------------------------------------------------------*/
// Name : GW_DeltaFunction::SetSpikeValue
/**
 *  \param  rSPike [GW_Float] Value.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the value of the spike.
 */
/*------------------------------------------------------------------------------*/
void GW_DeltaFunction::SetSpikeValue( GW_Float rSPike )
{
	rSPike_ = rSPike;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
