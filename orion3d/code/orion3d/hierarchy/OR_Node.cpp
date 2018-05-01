/*------------------------------------------------------------------------------
 *  \file  OR_Node.cpp
 *  \brief Implementation of class OR_Node
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Node.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Node.h"
#include "../animation/OR_AnimationPlayer.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"

#ifndef OR_USE_INLINE
	#include "OR_Node.inl"
#endif

using namespace OR;

	
/*------------------------------------------------------------------------------
 * Name : OR_Node constructor
 *
 *  \param  object the object that this node supports
 *  \param  father the father of the node (NULL if this is the root node)
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
OR_Node::OR_Node(OR_Object* pObj, OR_Node* pFather)
:	OR_ShellObject_ABC()
{
	pObject_ = pObj;
	pFather_ = pFather;
	if( pObj!=NULL )
		pObj->UseIt();
}


/*------------------------------------------------------------------------------
 * Name : OR_Node constructor
 *
 *  \param  Dup EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-12-07
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_Node::OR_Node( const OR_Node& Dup )
:	pFather_( NULL )
{
	pObject_ = (OR_Object*)Dup.pObject_->Clone();
	if( pObject_!=NULL )
		pObject_->UseIt();
}




/*------------------------------------------------------------------------------
 * Name : OR_Node::operator
 *
 *  \param  Dup EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-12-07
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_Node& OR_Node::operator=( const OR_Node& Dup )
{
	pObject_ = (OR_Object*)Dup.pObject_->Clone();
	pFather_ = NULL;
	if( pObject_!=NULL )
		pObject_->UseIt();
	return (*this);
}


/*------------------------------------------------------------------------------
 * Name : OR_Node destructor
 *
 *  \author Gabriel Peyré 2001-07-08
 *
 *	Delete recursivly the sub-tree.
 *
 *	Delete the object only if it is no longer used. Normaly, this should not arrive, since 
 *	this is the job of the manager.
 *------------------------------------------------------------------------------*/
OR_Node::~OR_Node()
{
	/* delete this object only if it is no more used */
	OR_SmartCounter::CheckAndDelete( pObject_ );
	
	/* delete each node in the sons list */
	for( IT_NodeList it=SonList_.begin(); it!=SonList_.end(); ++it )
		OR_DELETE(*it);
}



/*------------------------------------------------------------------------------
 * Name : OR_Node constructor
 *
 *  \return the number of element of the sub-tree
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
OR_U32 OR_Node::GetNbElements()
{
	OR_U32 nb=1;
	for( IT_NodeList it=SonList_.begin(); it!=SonList_.end(); ++it )
		nb+=(*it)->GetNbElements();

	return nb;
}

/* animation managing methods ***********************************/	

/*------------------------------------------------------------------------------
 * Name : OR_Node constructor
 *
 *  \param  player the player to add at the end of the list.
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
void OR_Node::AddPlayer(OR_AnimationPlayer& player)
{
	PlayerList_.push_back(&player);
}


/*------------------------------------------------------------------------------
 * Name : OR_Node constructor
 *
 *  \author Gabriel Peyré 2001-07-08
 *
 * remove the first player from the list
 *------------------------------------------------------------------------------*/
void OR_Node::RemovePlayer()
{
	if( !PlayerList_.empty() )
	{
		OR_AnimationPlayer* pPlayer = PlayerList_.front();
		OR_DELETE(pPlayer);
		PlayerList_.pop_front();
	}
	else
	{
		OR_Globals::MessageHandler()->Warning("OR_Node::AddPlayer", 
			"The player list is empty");
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Node::RemoveAllPlayers
 *
 *  \return remove all the animation player that are on the object.
 *  \author Gabriel Peyré 2001-07-11
 */ 
/*------------------------------------------------------------------------------*/
void OR_Node::RemoveAllPlayers()
{
	for(IT_AnimationPlayerList it=PlayerList_.begin(); !PlayerList_.empty(); PlayerList_.pop_front() )
	{
		OR_AnimationPlayer* pPlayer = *it;
		OR_DELETE(pPlayer);
	}
}



/*------------------------------------------------------------------------------
 * Name : OR_Node Update
 *
 *  \author Gabriel Peyré 2001-07-08
 *
 * If there is a player on the node, update the animation.
 * Then, update the object that the node supports.
 *------------------------------------------------------------------------------*/
void OR_Node::Update()
{
	OR_ASSERT( pObject_!=NULL );

	/* compute the animation if necessary */
	if( !PlayerList_.empty() )
	{
		OR_AnimationPlayer* pPlayer = PlayerList_.front();
		/* test if the animation is finished */
		if( pPlayer->IsFinished() )
		{
			/* the player is finished, so destroy it ! */
			RemovePlayer();
		}
		else
		{
			/* there is an animation player alive, so play the animation ! */
			pPlayer->Update(this);
		}
	}

	/* compute the absolute matrix using relative & animation matrix */
	pObject_->Update();

	/* update recursivly each son */
	for( IT_NodeList it=SonList_.begin(); it!=SonList_.end(); ++it )
	{
		glPushMatrix();
			(*it)->Update();
		glPopMatrix();
	}
}



/*------------------------------------------------------------------------------
 * Name : OR_Node::Draw
 *
 *  \author Gabriel Peyré 2001-07-08
 *
 * Draw the object this node supports, and then recurse on each son.
 *------------------------------------------------------------------------------*/
void OR_Node::Draw()
{
	OR_ASSERT(pObject_ != NULL);
	/* draw the node */
	pObject_->Draw();
#ifdef OR_DRAW_Trajectories
	/* draw the trajectory */
	if( OR_Globals::GetDrawObject(OR_TRAJECTORIES) ) 
		DrawTrajectory();
#endif /* #ifdef OR_DRAW_Trajectories */
	
	/* draw recursivly each son */
	for( IT_NodeList it=SonList_.begin(); it!=SonList_.end(); ++it )
		(*it)->Draw();
}


/*------------------------------------------------------------------------------
 * Name : OR_Node DrawTrajectory
 *
 *  \author Gabriel Peyré 2001-07-08
 *
 * If there is a player in the list, draw the trajectory of the animation.
 *------------------------------------------------------------------------------*/
void OR_Node::DrawTrajectory()
{
	if( !PlayerList_.empty() )
		PlayerList_.front()->DrawTrajectory(this);
}


/*------------------------------------------------------------------------------
 * Name : OR_Node ComputeId
 *
 *  \param  id the id of the node.
 *  \author Gabriel Peyré 2001-07-08
 *
 * Set the ID of this node, and then recurse on each child, with a new ID.
 *------------------------------------------------------------------------------*/
void OR_Node::ComputeId( OR_U32& id )
{
	pObject_->SetId(id);
	/* recursivly set up the different sons */
	for( IT_NodeList it=SonList_.begin(); it!=SonList_.end(); ++it )
	{
		id++;
		(*it)->ComputeId(id);
	}
}


/*------------------------------------------------------------------------------
 * Name : OR_Node BuildFromFile
 *
 *  \param  file the file from which we import the node
 *  \author Gabriel Peyré 2001-07-08
 *
 * import the node from a file.
 *------------------------------------------------------------------------------*/
void OR_Node::BuildFromFile( OR_File& file )
{	
	/* import the object from the file */
	this->SetObject( (OR_Object&) OR_ClassFactory::BuildFromFile(file) );
	/* keeps track of the object for resolution of targets */
	OR_Globals::SetImportedObject( OR_Globals::GetCurrentObjectNum(), pObject_ );

	/* read the number of sons */
	OR_U32 nb_sons=0;
	file >> nb_sons;

	/* imports the sons */
	for (OR_U32 i=0; i<nb_sons; i++)
	{
		/* create a new node */
		OR_Node* pNode = new OR_Node(NULL, this);
		/* add the node to the sons list */
		this->AddSonLast(*pNode);

		/* recurse on son node */
		OR_Globals::SetCurrentObjectNum( OR_Globals::GetCurrentObjectNum()+1 );
		file >> pNode;
	}
}


/*------------------------------------------------------------------------------
 * Name : OR_Node BuildToFile
 *
 *  \param  file the file we export the node from
 *  \author Gabriel Peyré 2001-07-08
 *
 * Export the node to a file.
 *------------------------------------------------------------------------------*/
void OR_Node::BuildToFile( OR_File& file )
{
	/* export the object to a file */
	OR_ClassFactory::BuildToFile(  file, *pObject_  );

	/* write the number of sons */
	OR_I32 nb = this->GetNbSon();
	file << nb;

	/* recursivly export the different sons */
	for( IT_NodeList it=SonList_.begin(); it!=SonList_.end(); ++it )
		file << (*it);
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Node::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Node::BuildSonList(T_ShellObjectList& ShellSonList)
{
	ShellSonList.clear();

	for( IT_NodeList it=SonList_.begin(); it!=SonList_.end(); ++it )
	{
		OR_Node* pNode = *it;
		OR_ASSERT( pNode!=NULL );
		OR_Object* pObj = pNode->GetObject();
		OR_ASSERT( pObj!=NULL );
		/* set the name of the son */
		OR_ADD_SHELL_SON(ShellSonList, *pNode, OR_String("node_") + pObj->GetName() );

		ShellSonList.push_back( pNode );
	}

	if( this->GetObject()!=NULL )
		OR_ADD_SHELL_SON(ShellSonList, *this->GetObject(), OR_String("obj_")	+ this->GetObject()->GetName() );

	OR_U32 nCpt = 0;
	for(IT_AnimationPlayerList itPlayer=PlayerList_.begin(); itPlayer!=PlayerList_.end(); ++itPlayer )
	{
		OR_AnimationPlayer* pPlayer = *itPlayer;
		OR_ADD_SHELL_SON(ShellSonList, *pPlayer, OR_String("player_") + nCpt );
		nCpt++;
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Node::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Node::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, NbSon);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, NbElements);

	OR_ADD_SHELL_FUNC(FuncDeclList, RemovePlayer,		"Remove the first player.");
	OR_ADD_SHELL_FUNC(FuncDeclList, RemoveAllPlayers,	"Remove all players.");
}



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

