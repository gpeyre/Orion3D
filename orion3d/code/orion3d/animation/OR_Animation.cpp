/*------------------------------------------------------------------*/
/*                       OR_Animation.cpp                           */
/*------------------------------------------------------------------*/
/* definition of animation of a sub-tree                            */
/*------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Animation.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Animation.h"

namespace OR
{
	
/*------------------------------------------------------------------*/
/*                      class OR_Animation                          */
/*------------------------------------------------------------------*/
/* the animation of a sub-tree                                      */
/*------------------------------------------------------------------*/


OR_Animation::OR_Animation(OR_File file)
{
	FatherNode=NULL;
	Name=OR_String("");
	NbObjects=0;
	Duration=1;
	BuildFromFile(file);

}

OR_Animation::OR_Animation()
{
	FatherNode=NULL;
	Name=OR_String("");
	NbObjects=0;
	Duration=1;
}

OR_Animation::~OR_Animation()
{
	OR_DELETE(FatherNode);
}

void OR_Animation::Update(OR_Node* father, OR_Float t)
{
	FatherNode->Update(father, t);
}

OR_AnimationNode* OR_Animation::GetFatherNode()
{
	return FatherNode;
}

void OR_Animation::SetFatherNode(OR_AnimationNode* father)
{
	FatherNode=father;
}

OR_String& OR_Animation::GetName()
{
	return Name;
}

void OR_Animation::SetName(const char* name)
{	
	Name = OR_String(name);
}

void OR_Animation::SetName(const OR_String& name)
{	
	Name = name;
}

OR_I32 OR_Animation::GetNbObject()
{
	return NbObjects;
}

void OR_Animation::SetNbObject(OR_I32 n)
{
	NbObjects=n;
}

void OR_Animation::SetDuration(OR_Float duration)
{
	Duration=duration;
}

OR_Float OR_Animation::GetDuration()
{
	return Duration;
}

void OR_Animation::DrawTrajectory(OR_Node* cur_node)
{
	FatherNode->DrawTrajectory(cur_node);
}

/* serialization methods ***************************************/
void OR_Animation::BuildToFile( OR_File& file )
{
	/* export the animation data */
	file << NbObjects
		 << Name
		 << Duration;

	/* export the sub tree of animation node */
	file << FatherNode;
}

void OR_Animation::BuildToFile(OR_File file, OR_Node* HierarchyRoot, OR_Node* SelectedNode)
{
	/* set the name of the animation */
	Name=SelectedNode->GetObject()->GetName();

	/* export the animation data */
	file << NbObjects
		 << Name
		 << Duration;

	/* compute the animation node corresponding to the hierarchy selected node */
	OR_AnimationNode* pStartNode=ComputeStartNode(FatherNode, HierarchyRoot, SelectedNode);

	if(pStartNode==NULL)
	{
		OR_Globals::MessageHandler()->Warning("OR_Animation::BuildToFile", 
			"Can't retrieve the root node of the animation, ACT file will be corrupted.");
	}
	else
	{
		/* export the sub tree of animation node */
		file << pStartNode;
	}
}


void OR_Animation::BuildFromFile( OR_File& file )
{
	/* import the animation data */
	file >> NbObjects
		 >> Name
		 >> Duration;

	/* create the father node */
	FatherNode=new OR_AnimationNode(NULL);
	/* export recursivly the hierarchy */
	file >> FatherNode;
}


OR_AnimationNode* OR_Animation::ComputeStartNode(OR_AnimationNode* CurAnimationNode, class OR_Node* CurHierarchyNode,
												 class OR_Node* SelectedNode)
{
	if(CurHierarchyNode==SelectedNode) return CurAnimationNode;
	
	/* recurse on the son */
	T_NodeList &HierarchySonList = CurHierarchyNode->GetSonList();
	T_AnimationNodeList &AnimationSonList = CurAnimationNode->GetSonList();
	IT_AnimationNodeList AnimationIt = AnimationSonList.begin();

	for( IT_NodeList HierarchyIt=HierarchySonList.begin(); HierarchyIt!=HierarchySonList.end(); ++HierarchyIt )
	{
		if( AnimationIt==AnimationSonList.end() )
		{
			/* the animation node has not enough sons */
			OR_Globals::MessageHandler()->Debug("OR_Animation::Update_Rec", 
				"Hierarchy tree and animation tree don't fit.");
			return NULL;
		}
		/* recurse on the child */
		OR_AnimationNode* result=ComputeStartNode(*AnimationIt, *HierarchyIt , SelectedNode);
		if(result!=NULL) return result;
		
		AnimationIt++;
	}

	if ( AnimationIt!=AnimationSonList.end() )
	{
		/* the animation node has too much sons */
		OR_Globals::MessageHandler()->Debug("OR_Animation::Update_Rec", 
			"Hierarchy tree and animation tree don't fit.");
		return NULL;
	}
	return NULL;

}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Animation::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Animation::BuildSonList(T_ShellObjectList& ShellSonList)
{
	if( this->GetFatherNode()!=NULL )
		OR_ADD_SHELL_SON(ShellSonList, *this->GetFatherNode(), OR_String("father_node") );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Animation::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Animation::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Name);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, NbObject);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, Duration);
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
//                           END OF FILE                                     //
///////////////////////////////////////////////////////////////////////////////