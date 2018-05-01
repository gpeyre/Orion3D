/*------------------------------------------------------------------------------
 *  \file  OR_3DS_Node.h
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-11-05
 *------------------------------------------------------------------------------*/

#ifndef __OR_3DS_Node_h_
#define __OR_3DS_Node_h_

#include "stdafx.h"

using namespace OR;

namespace OR_3DS {


///A Node where are stored infos linking MAX and Orion3D nodes
class UNode
{
protected:
	///The 3DSMAX node corresponding to this node
	INode* MAXNode;
	///The 3DSMAX target for this node
	INode* MAXTarget;
public:
	///The LookupTable (only useful for meshes). See CNode::GetOR_Mesh()
	T_U32Vector LookupTable;
	///\return the 3DSMAX node corresponding to this node
	INode* GetMAXNode()					 {return MAXNode;}
	///\return the 3DSMAX target for this node
	INode* GetMAXTarget()				 {return MAXTarget;}
	///Sets the 3DSMAX node corresponding to this node
	///\param _maxnode the 3DSMAX node corresponding to this node
	void SetMAXNode(INode* _maxnode)	 {MAXNode	=_maxnode;}
	///Sets the 3DSMAX target for this node
	///\param _maxnode the 3DSMAX target for this node
	void SetMAXTarget(INode* _maxtarget) {MAXTarget = _maxtarget;}

	///Constructor. Clear LookupTable
	UNode() {LookupTable.clear();}
	///Destructor. Clear LookupTable
	~UNode() {LookupTable.clear();}
};

	
/*------------------------------------------------------------------------------
 *  \class  OR_3DS_Node
 *  \brief  PUT THE COMMENTS ON THE CLASS HERE
 *  \author Antoine Bouthors 2001-11-05
 *  PUT FULL DESCRIPTION HERE 
 *------------------------------------------------------------------------------*/

class OR_3DS_Node: public OR_Node, public UNode
{
};

} // End namespace OR_3DS

#ifdef OR_USE_INLINE
#   include "OR_3DS_Node.inl"
#endif


#endif // __OR_3DS_Node_h_

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

