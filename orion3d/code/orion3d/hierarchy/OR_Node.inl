/*------------------------------------------------------------------------------
 *  \file  OR_Node.inl
 *  \brief inlined methods for a hierarchcal node
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
#include "OR_Node.h"

namespace OR {


/*------------------------------------------------------------------------------
 * Name : OR_Node::AddSonFirst
 *
 *  \param  *pNode a new son for the node 
 *  \author Gabriel Peyré 2001-07-08
 *
 * add a son at the end of the list
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Node::AddSonFirst(OR_Node &node)
{
	SonList_.push_front(&node);
	node.SetFather(this);
}


/*------------------------------------------------------------------------------
 * Name : OR_Node::AddSonLast
 *
 *  \param  *pNode a new son for the node 
 *  \author Gabriel Peyré 2001-07-08
 *
 * add a son at the end of the list
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Node::AddSonLast(OR_Node &node)
{
	SonList_.push_back(&node);
	node.SetFather(this);
}



/*------------------------------------------------------------------------------
 * Name : OR_Node::RemoveSon
 *
 *  \param  son the node to remove from the sons list
 *  \author Gabriel Peyré 2001-07-08
 *
 * remove a son from the list
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Node::RemoveSon(OR_Node& son)	
{
	SonList_.remove(&son);
}



/*------------------------------------------------------------------------------
 * Name : OR_Node::GetNbSon
 *
 *  \return the number of sons of the node
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Node::GetNbSon()
{
	return SonList_.size();
}




/*------------------------------------------------------------------------------
 * Name : OR_Node::GetObject
 *
 *  \return the object that this node support (can be NULL)
 *  \author Gabriel Peyré 2001-07-08
 *
 * each node is supporting an OR_Object*, this methods is here to access this object.
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Object* OR_Node::GetObject()
{
	return pObject_;
}



/*------------------------------------------------------------------------------
 * Name : OR_Node::GetObject
 *
 *  \return a const pointer to the object that this node support (can be NULL)
 *  \author Antoine Bouthors 2001-12-02
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
const OR_Object* OR_Node::GetObject() const
{
	return pObject_;
}


/*------------------------------------------------------------------------------
 * Name : OR_Node::SetObject
 *
 *  \param  object set the object this node will support
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_Node::SetObject(OR_Object& Object)
{
	/* check if we need to delete the old object */
	OR_SmartCounter::CheckAndDelete( pObject_ );

	pObject_ = &Object;

	pObject_->UseIt();
}


/*------------------------------------------------------------------------------
 * Name : OR_Node::GetFather
 *
 *  \return get the father node of this node (return NULL if this is the root node).
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Node* OR_Node::GetFather()
{
	return pFather_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Node::SetFather
 *
 *  \param  pNode father of the node
 *  \author Gabriel Peyré 2001-07-11
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Node::SetFather(OR_Node* pNode)
{
	pFather_=pNode;
}


/*------------------------------------------------------------------------------
 * Name : OR_Node::GetSonList
 *
 *  \return the list of the sons of this node
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
OR_INLINE
T_NodeList& OR_Node::GetSonList()
{
	return SonList_;
}


/*------------------------------------------------------------------------------
 * Name : OR_Node::GetSonList
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-12-02
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
const T_NodeList& OR_Node::GetSonList() const
{
	return SonList_;
}



/*------------------------------------------------------------------------------
 * Name : OR_Node::GetPlayerList
 *
 *  \return get the FIFO of animation players.
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
OR_INLINE
T_AnimationPlayerList& OR_Node::GetPlayerList()
{
	return PlayerList_;
}




} // End namespace OR

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

