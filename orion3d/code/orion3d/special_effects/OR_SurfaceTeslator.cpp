/*------------------------------------------------------------*/
/*                    OR_SurfaceTeslator.cpp                  */
/*------------------------------------------------------------*/
/* definition of class OR_SurfaceTesslator and OR_SurfNode    */
/*------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SurfaceTeslator.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_SurfaceTeslator.h"

namespace OR
{
	
/*------------------------------------------------------------*/
/* class OR_SurfVertex                                        */
/*------------------------------------------------------------*/

OR_SurfVertex::OR_SurfVertex()
{
	Vertex=new OR_Vector3D;
	Normal=new OR_Vector3D;
}


OR_SurfVertex::~OR_SurfVertex()
{
	OR_DELETE(Vertex);
	OR_DELETE(Normal);
}


/*------------------------------------------------------------*/
/*      class OR_SurfNode                                     */
/*------------------------------------------------------------*/

OR_SurfNode::OR_SurfNode()
{

}

OR_SurfNode::~OR_SurfNode()
{
	OR_DELETE(Vert_NO);
	OR_DELETE(Vert_NE);
	OR_DELETE(Vert_SE);
	OR_DELETE(Vert_SO);
	OR_DELETE(Node_NO);
	OR_DELETE(Node_NE);
	OR_DELETE(Node_SE);
	OR_DELETE(Node_SO);
}

void OR_SurfNode::SetAsLeaf()
{
	IsLeafNode=true;
}

void OR_SurfNode::SetAsNonLeaf()
{
	IsLeafNode=false;
}
	
OR_Bool OR_SurfNode::IsLeaf()
{
	return IsLeafNode;
}

/*---------------------------------------------------------------*/
/*              class OR_SurfaceTeslator                         */
/*---------------------------------------------------------------*/

OR_SurfaceTeslator::OR_SurfaceTeslator(OR_SurfaceEquation* myequation)
{
	Root=NULL;
	MyEquation=myequation;
	MaxDepth=OR_START_MAX_DEPHT;
	NeedsRebuild=false;
}

OR_SurfaceTeslator::~OR_SurfaceTeslator()
{
	OR_DELETE(MyEquation);
	OR_DELETE(Root);
}

void OR_SurfaceTeslator::BuildTreeRec(OR_I32 depth, OR_SurfNode* cur_node, 
									  OR_Float UMin, OR_Float UMax, OR_Float VMin, OR_Float VMax)
{
	if (depth>=DepthStop)
	{
		/* we have reach the wanted depth, so stop recurstion */
		cur_node->SetAsLeaf();
	}
	else
	{
		OR_Float UMid=(UMin+UMax)/2;
		OR_Float VMid=(VMin+VMax)/2;
		OR_SurfNode *new_node;
		OR_SurfVertex* vert_n=new OR_SurfVertex;
		OR_SurfVertex* vert_e=new OR_SurfVertex;
		OR_SurfVertex* vert_s=new OR_SurfVertex;
		OR_SurfVertex* vert_o=new OR_SurfVertex;
		OR_SurfVertex* vert_c=new OR_SurfVertex;
		/* compute the different value of the surface */
		if (cur_node->Node_NO==NULL||cur_node->Node_NE==NULL||NeedsRebuild)
			MyEquation->ComputeValue(vert_n, UMid, VMax,
				cur_node->Vert_NO, cur_node->Vert_NE, NULL, NULL);
		if (cur_node->Node_NE==NULL||cur_node->Node_SE==NULL||NeedsRebuild)
			MyEquation->ComputeValue(vert_e, UMax, VMid,
				NULL, NULL, cur_node->Vert_SE, cur_node->Vert_NE);
		if (cur_node->Node_SE==NULL||cur_node->Node_SO==NULL||NeedsRebuild)
			MyEquation->ComputeValue(vert_s, UMid, VMin,
				cur_node->Vert_SO, cur_node->Vert_SE, NULL, NULL);
		if (cur_node->Node_SO==NULL||cur_node->Node_NO==NULL||NeedsRebuild)
			MyEquation->ComputeValue(vert_o, UMin, VMid,
				NULL, NULL, cur_node->Vert_SO, cur_node->Vert_NO);
		if (cur_node->Node_NO==NULL||cur_node->Node_NE==NULL||
			cur_node->Node_SO==NULL||cur_node->Node_SE==NULL||NeedsRebuild)
			MyEquation->ComputeValue(vert_n, UMid, VMid,
				vert_e, vert_o, vert_s, vert_n);
		
		cur_node->SetAsNonLeaf();
		/* create left NO of the node */
		if (cur_node->Node_NO!=NULL || NeedsRebuild)
		{
			/* build the NO node */
			new_node=new OR_SurfNode;
			new_node->Vert_NO=cur_node->Vert_NO;
			new_node->Vert_NE=vert_n;
			new_node->Vert_SE=vert_c;
			new_node->Vert_SO=vert_o;
			/* asign the node as the son of the current node */
			cur_node->Node_NO=new_node;
			/* recurse on the new node */
			BuildTreeRec(depth+1, new_node, UMin, UMid, VMid, VMax);
		}
		/* create left NE of the node */
		if (cur_node->Node_NE!=NULL || NeedsRebuild)
		{
			/* build the NE node */
			new_node=new OR_SurfNode;
			new_node->Vert_NO=vert_n;
			new_node->Vert_NE=cur_node->Vert_NE;
			new_node->Vert_SE=vert_e;
			new_node->Vert_SO=vert_c;
			/* asign the node as the son of the current node */
			cur_node->Node_NE=new_node;
			/* recurse on the new node */
			BuildTreeRec(depth+1, new_node, UMid, UMax, VMid, VMax);
		}
		/* create left SE of the node */
		if (cur_node->Node_SE!=NULL || NeedsRebuild)
		{
			/* build the SE node */
			new_node=new OR_SurfNode;
			new_node->Vert_NO=vert_c;
			new_node->Vert_NE=vert_e;
			new_node->Vert_SE=cur_node->Vert_SE;
			new_node->Vert_SO=vert_s;
			/* asign the node as the son of the current node */
			cur_node->Node_SE=new_node;
			/* recurse on the new node */
			BuildTreeRec(depth+1, new_node, UMid, UMax, VMin, VMid);
		}
		/* create left SO of the node */
		if (cur_node->Node_SO!=NULL || NeedsRebuild)
		{
			/* build the SO node */
			new_node=new OR_SurfNode;
			new_node->Vert_NO=vert_e;
			new_node->Vert_NE=vert_c;
			new_node->Vert_SE=vert_s;
			new_node->Vert_SO=cur_node->Vert_SO;
			/* asign the node as the son of the current node */
			cur_node->Node_SO=new_node;
			/* recurse on the new node */
			BuildTreeRec(depth+1, new_node, UMin, UMid, VMin, VMid);
		}
	}		
}

void OR_SurfaceTeslator::BuildTree(OR_I32 depth)
{
	OR_Float UMin=MyEquation->GetUMin();
	OR_Float UMax=MyEquation->GetUMax();
	OR_Float VMin=MyEquation->GetVMin();
	OR_Float VMax=MyEquation->GetVMax();
	DepthStop=depth;
	if (Root==NULL || NeedsRebuild)
	{
		/* create the root */
		if (Root==NULL) Root=new OR_SurfNode;
		Root->Vert_NO=new OR_SurfVertex;
		Root->Vert_NE=new OR_SurfVertex;
		Root->Vert_SE=new OR_SurfVertex;
		Root->Vert_SO=new OR_SurfVertex;
		MyEquation->ComputeValue(Root->Vert_NO, UMin, VMax, NULL, NULL, NULL, NULL);
		MyEquation->ComputeValue(Root->Vert_NE, UMax, VMax, NULL, NULL, NULL, NULL);
		MyEquation->ComputeValue(Root->Vert_SE, UMax, VMin, NULL, NULL, NULL, NULL);
		MyEquation->ComputeValue(Root->Vert_SO, UMin, VMin, NULL, NULL, NULL, NULL);
	}

	BuildTreeRec(0, Root, UMin, UMax, VMin, VMax);
}

void OR_SurfaceTeslator::BuildTree()
{
	BuildTree(MaxDepth);
}


void OR_SurfaceTeslator::UpdateRec(OR_SurfNode* cur_node)
{
	
}

void OR_SurfaceTeslator::Update()
{
	if (Root!=NULL) UpdateRec(Root);
}

OR_Elements OR_SurfaceTeslator::GetType()
{
	return OR_SURFACE_TESLATOR;
}

void OR_SurfaceTeslator::Rotate(OR_Float val)
{
	Rot+=val;
}

void OR_SurfaceTeslator::SetAngle(OR_Float val)
{
	Rot=val;
}

void OR_SurfaceTeslator::SetAxe(OR_Vector3D axe)
{
	Axe=axe;
}

void OR_SurfaceTeslator::DrawRec(OR_SurfNode* cur_node)
{

}

void OR_SurfaceTeslator::Draw()
{
	
glPushMatrix();
	
	OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );

	if (Root!=NULL) DrawRec(Root);
glPopMatrix();
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