/*---------------------------------------------------------------------*/
/*                          OR_HierarchyTree.h                         */
/*---------------------------------------------------------------------*/
/* definition of hierarchical tree                                     */
/*---------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_HierarchyTree.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_HierarchyTree.h"
#include "../utils/OR_String.h"

#ifndef OR_USE_INLINE
	#include "OR_HierarchyTree.inl"
#endif

namespace OR
{

/*----------------------------------------------------------------------*/
/*                         classe OR_HierarchyTree                      */
/*----------------------------------------------------------------------*/
/* a hierarchical tree used to store all OR_Objects.                    */
/*----------------------------------------------------------------------*/

OR_HierarchyTree::OR_HierarchyTree()
:	OR_ShellObject_ABC()
{	
	/* create an empty tree */
	TreeRoot=new OR_Node;

	NbObjets=0;

	/* assign a default or_object to the tree root */
	TreeRoot->SetObject( *OR_Globals::GetHierarchyRoot() );
	/* add the root in the gizmo manager */
	OR_Globals::GizmoManager()->AddElement( OR_Globals::GetHierarchyRoot() );
}

OR_HierarchyTree::~OR_HierarchyTree()
{
	OR_DELETE( TreeRoot );
}

void OR_HierarchyTree::AddNode(OR_Object* new_object)
{
	/* add a son to the hierarcy root */
	OR_Node* pNode = new OR_Node(new_object, TreeRoot);
	TreeRoot->AddSonLast( *pNode );
}


/*------------------------------------------------------------------------------
 * Name : OR_HierarchyTree::DupTree
 *
 *  \param  Dup EXPLANATION
 *  \param  NULL EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-12-07
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_Node* OR_HierarchyTree::DupTree( const OR_Node* Dup, OR_Node* NewFather )
{
	OR_Node* NewNode = new OR_Node( *Dup );
	CIT_NodeList it;
	const T_NodeList& SonList = Dup->GetSonList();
	for( it=SonList.begin() ; it!=SonList.end() ; ++it )
	{
		OR_Node* NewSonNode = DupTree( (*it), NewNode );
		NewSonNode->SetFather( NewNode );
	}
	if( NewFather )
		NewNode->SetFather( NewFather );

	return NewNode;
}

void OR_HierarchyTree::Draw()
{
	TreeRoot->Draw();
}

void OR_HierarchyTree::Update()
{
	glLoadIdentity();
	TreeRoot->Update();
}

void OR_HierarchyTree::BuildFromFile( OR_File& file )
{
	/* resize list of imported objects */
	OR_U32 nNbr;
	file >> nNbr;
	OR_Globals::ResizeImportedObject(nNbr);

	/* import the root node, wich will export 
	   the whole su-tree */
	OR_Globals::SetCurrentObjectNum( 0 );
	OR_Node* StartNode=new OR_Node(NULL, TreeRoot);
	TreeRoot->AddSonLast(*StartNode);
	file >> StartNode;

	/* compute the target */
	for (OR_U32 i=0; i<nNbr; i++)
	{
		OR_Object* pObj = OR_Globals::GetImportedObject(i);
		OR_ASSERT( pObj!=NULL );
		pObj->PostExportPass();
	}
		

	/* detruit les tables temporaires */
	OR_Globals::ResizeImportedObject(0);
	OR_Globals::ResizeIndexToNumShader(0);

	NbObjets += nNbr;
}

void OR_HierarchyTree::BuildToFile( OR_File& f )
{	
	BuildToFile( f, TreeRoot);
}

void OR_HierarchyTree::BuildToFile( OR_File& file, OR_Node* start )
{
	/* compute the id of each object */
	OR_U32 Id( 0 );
	start->ComputeId( Id );

	/* export the number of objects */
	OR_U32 nb=start->GetNbElements();
	file << nb;
	/* recursivly exports each node */
	file << start;
}

/* search methods **********************************************/
const OR_Node* OR_HierarchyTree::GetNodeByName( const char* name) const
{
	return GetNodeByName_Rec( name, TreeRoot );
}


/*------------------------------------------------------------------------------
 * Name : OR_HierarchyTree::GetNodeByName
 *
 *  \param  name EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-12-02
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_Node* OR_HierarchyTree::GetNodeByName( const char* name)
{
	return (OR_Node*)GetNodeByName_Rec( name, TreeRoot );
}

/*------------------------------------------------------------------------------
 * Name : OR_HierarchyTree::DeleteSubTree
 *
 *  \param  node node under which all nodes must be removed
 *  \author Antoine Bouthors 2002-01-04
 *
 * Delete all the hierarchy under the node \c node, but not the node itself
 * (or it would be like the OR_Node destructor)
 *------------------------------------------------------------------------------*/
void OR_HierarchyTree::DeleteSubTree( OR_Node * node )
{
	T_NodeList& SonList = node->GetSonList();
	IT_NodeList it = SonList.begin();
	while( it != SonList.end() )
	{
		delete (*it);
		it = SonList.erase( it );
	}
}



const OR_Node* OR_HierarchyTree::GetNodeByName_Rec( const char* name, const OR_Node* cur_node) const
{
	OR_ASSERT( cur_node->GetObject() != NULL);
	/* check if this node is the good one */
	if ( cur_node->GetObject()->GetName().equals( name ) ) return cur_node;

	/* search recursivly */
	const T_NodeList& SonList = cur_node->GetSonList();
	for( CIT_NodeList it=SonList.begin(); it!=SonList.end(); ++it )
	{
		const OR_Node *n=GetNodeByName_Rec(name, *it);
		if (n!=NULL) return n;
	}

	/* the node has not been found */
	return NULL;
}

OR_Node* OR_HierarchyTree::GetRootNode()
{
	return this->TreeRoot;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_HierarchyTree::GetNode_Rec
 *
 *  \param  pObj the object we want to find the corresponding node.
 *  \return the corresponding node [NULL if not find].
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/
OR_Node* OR_HierarchyTree::GetNode_Rec(OR_Object& obj, OR_Node& cur_node)
{
	if( cur_node.GetObject()==&obj )
		return &cur_node;

	T_NodeList& SonList = cur_node.GetSonList();
	for( IT_NodeList it = SonList.begin(); it != SonList.end(); ++it )
	{
		OR_Node &Node = *(*it);
		OR_Node* pNode = this->GetNode_Rec( obj, Node );
		if( pNode!=NULL )
			return pNode;
	}

	return NULL;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_HierarchyTree::GetNode
 *
 *  \param  pObj the object we want to find the corresponding node.
 *  \return the corresponding node.
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/
OR_Node* OR_HierarchyTree::GetNode(OR_Object& pObj)
{
	OR_ASSERT( TreeRoot!=NULL );
	return this->GetNode_Rec( pObj, *TreeRoot );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_HierarchyTree::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_HierarchyTree::BuildSonList(T_ShellObjectList& ShellSonList)
{
	ShellSonList.clear();

	if( this->GetRootNode()!=NULL )
	{
		OR_String name;
		OR_Object* pObj = this->GetRootNode()->GetObject();
		if( pObj!=NULL )
			name = pObj->GetName();
		else
			name = "root";
		this->GetRootNode()->SetShellName( OR_String("node_")+name );
		ShellSonList.push_back( this->GetRootNode() );
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_HierarchyTree::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_HierarchyTree::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	
	OR_ADD_SHELL_FUNC(FuncDeclList, GetNbrObject, "Return the number of objects in the tree.");
	OR_ADD_SHELL_FUNC(FuncDeclList, PrintNbrObject, "Print the number of objects in the tree.");
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_HierarchyTree::GetNbrObjects
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_HierarchyTree::GetNbrObject(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( GetNbrObject, 0 );

	stack.ReturnValueFloat( OR_ACCESS_THIS(OR_HierarchyTree).GetNbrObject() );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_HierarchyTree::PrintNbrObjects
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_HierarchyTree::PrintNbrObject(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( GetNbrObjects, 0 );

	OR_SHELL_FUNC_PRINT( OR_String("Number of objects : ") + OR_ACCESS_THIS(OR_HierarchyTree).GetNbrObject() );
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
