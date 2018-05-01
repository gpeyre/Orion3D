/*------------------------------------------------------------------------------
 *  \file  OR_AnimationNode.cpp
 *  \brief A node in a hierachical animation.
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/


#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_AnimationNode.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_AnimationNode.h"

#ifndef OR_USE_INLINE
#   include "OR_AnimationNode.inl"
#endif

using namespace OR;


OR_AnimationNode::OR_AnimationNode(class OR_AnimationNode* pFather)
{
	pFather_=pFather;
}

OR_AnimationNode::~OR_AnimationNode()
{
	/* delete each track */
	for( IT_AnimationTrackList TrackIt=TrackList_.begin(); TrackIt!=TrackList_.end(); ++TrackIt )
		OR_DELETE(*TrackIt);
	/* delete recursivly each son */
	for( IT_AnimationNodeList NodeIt=SonList_.begin(); NodeIt!=SonList_.end(); ++NodeIt)
		OR_DELETE(*NodeIt);
}

void OR_AnimationNode::Update(OR_Node* hierarchy_node, OR_Float t)
{
	/* compute the animation matrix of the node */
	for( IT_AnimationTrackList TrackIt=TrackList_.begin(); TrackIt!=TrackList_.end(); ++TrackIt )
		(*TrackIt)->Compute(t, hierarchy_node->GetObject());

	/* recurse on the son */
	T_NodeList &SonList = hierarchy_node->GetSonList();
	IT_AnimationNodeList AnimationIt=SonList_.begin();

	for( IT_NodeList HierarchyIt=SonList.begin(); HierarchyIt!=SonList.end(); ++HierarchyIt )
	{
		if ( AnimationIt==SonList_.end() )
		{
			/* the animation node has not enough sons */
			return;
		}
		/* recurse on the child */
		(*AnimationIt)-> Update(*HierarchyIt, t);
		AnimationIt++;
	}
	
	if (AnimationIt!=SonList_.end())
	{
		/* the animation node has too much sons */
		OR_Globals::MessageHandler()->Debug("OR_AnimationNode::Update", 
			"Hierarchy tree and animation tree don't fit.");
		return;
	}
}

void OR_AnimationNode::DrawTrajectory(OR_Node* hierarchy_node)
{
	/* draw the curent node trajectory */
	for( IT_AnimationTrackList TrackIt=TrackList_.begin(); TrackIt!=TrackList_.end(); ++TrackIt )
	{
		if ((*TrackIt)->GetTarget()==OR_ANIMATION_Target_Pos)	
			(*TrackIt)->DrawTrajectory( hierarchy_node->GetObject() );
	}

	/* recurse on the son */
	T_NodeList &SonList = hierarchy_node->GetSonList();
	IT_AnimationNodeList AnimationIt=SonList_.begin();
	
	for( IT_NodeList HierarchyIt=SonList.begin(); HierarchyIt!=SonList.end(); ++HierarchyIt )
	{
		if ( AnimationIt==SonList_.end() )
		{
			/* the animation node has not enough sons */
			return;
		}
		/* recurse on the child */
		(*AnimationIt)-> DrawTrajectory(*HierarchyIt);
		AnimationIt++;
	}
	
	if (AnimationIt!=SonList_.end())
	{
		/* the animation node has too much sons */
		OR_Globals::MessageHandler()->Debug("OR_AnimationNode::DrawTrajectory", 
			"Hierarchy tree and animation tree don't fit.");
		return;
	}
}

#if 0
void OR_AnimationNode::SortTrack()
{
	for( IT_AnimationTrackList TrackIt=TrackList_.begin(); TrackIt!=TrackList_.end(); ++TrackIt )
	{
		OR_AnimationTrack* pTrack = *TrackIt;
		if( pTrack->IsRotationTarget() )
		{
			/* the track is a rotation one, so put it at the begining */
			TrackList_.erase(TrackIt);
			TrackList_.push_front(pTrack);
		}
	}
}
#endif

void OR_AnimationNode::RescaleTime(OR_Float start, OR_Float end)
{
	for( IT_AnimationTrackList TrackIt=TrackList_.begin(); TrackIt!=TrackList_.end(); ++TrackIt )
	{
		T_KeyFrameList& KeyList = (*TrackIt)->GetKeyframeList();
		for( IT_KeyFrameList KeyIt = KeyList.begin(); KeyIt!=KeyList.end(); ++KeyIt )
			(*KeyIt)->SetTime(((*KeyIt)->GetTime()-start)/(end-start));
	}

	/* recurse on each child */
	for( IT_AnimationNodeList NodeIt=SonList_.begin(); NodeIt!=SonList_.end(); ++NodeIt )
		(*NodeIt)->RescaleTime(start, end);
}

/* serialization methods ***************************************/
void OR_AnimationNode::BuildFromFile( OR_File& file )
{
	OR_U32 nb_sons, nb_tracks;
	OR_U32 i;
	OR_ANIMATION_Evaluator_Type evaluator=OR_ANIMATION_Evaluator_Undefined;
	OR_ANIMATION_Track_Type track_type=OR_ANIMATION_Track_Undefined;
	/* read node datas */
	file >> nb_sons
		 >> nb_tracks;

	/* import the tracks */
	for (i=0; i<nb_tracks; i++)
	{
		/* import the type of the track */
		file >> track_type;
		/* export the type of the evaluator */
		file >> evaluator;
		/* create the track */
		OR_AnimationTrack *track;
		switch (evaluator)
		{
			case OR_ANIMATION_Evaluator_Linear:
				switch (track_type)
				{
					case OR_ANIMATION_Track_Float:
						track=new OR_AnimationTrack_Linear_Float;
						break;
					case OR_ANIMATION_Track_Quaternion:
						track=new OR_AnimationTrack_Linear_Quaternion;
						break;
					case OR_ANIMATION_Track_Vector:
						track=new OR_AnimationTrack_Linear_Vector;
						break;
					default:
						/* the track type is not supported */
						OR_Globals::MessageHandler()->Debug("OR_Animation::LoadFromFile_Rec", 
							"The track type '%i' is not supported.", track_type);
						return;
						break;
				}
				break;
			case OR_ANIMATION_Evaluator_Bezier:
				switch (track_type)
				{
					case OR_ANIMATION_Track_Float:
						track=new OR_AnimationTrack_Bezier_Float;
						break;
					case OR_ANIMATION_Track_Vector:
						track=new OR_AnimationTrack_Bezier_Vector;
						break;
					default:
						/* the track type is not supported */
						OR_Globals::MessageHandler()->Debug("OR_Animation::LoadFromFile_Rec", 
							"The track type '%i' is not supported.", track_type);
						return;
						break;
				}
				break;
			case OR_ANIMATION_Evaluator_Constant:
				switch (track_type)
				{
					case OR_ANIMATION_Track_Float:
						track=new OR_AnimationTrack_Constant_Float;
						break;
					case OR_ANIMATION_Track_Quaternion:
						track=new OR_AnimationTrack_Constant_Quaternion;
						break;
					case OR_ANIMATION_Track_Bool:
						track=new OR_AnimationTrack_Constant_Vector;
						break;
					case OR_ANIMATION_Track_Vector:
						track=new OR_AnimationTrack_Constant_Bool;
						break;
					default:
						/* the track type is not supported */
						OR_Globals::MessageHandler()->Debug("OR_Animation::LoadFromFile_Rec", 
							"The track type '%i' is not supported.", track_type);
						return;
						break;
				}
				break;
			case OR_ANIMATION_Evaluator_TCB:
				switch (track_type)
				{
					case OR_ANIMATION_Track_Float:
						track=new OR_AnimationTrack_TCB_Float;
						break;
					case OR_ANIMATION_Track_Vector:
						track=new OR_AnimationTrack_TCB_Vector;
						break;
					default:
						/* the track type is not supported */
						OR_Globals::MessageHandler()->Debug("OR_Animation::LoadFromFile_Rec", 
							"The track type '%i' is not supported.", track_type);
						return;
						break;
				}
				break;
			default:
				/* the evaluator type is not supported */
				OR_Globals::MessageHandler()->Debug("OR_Animation::LoadFromFile_Rec", 
					"The evaluator type '%i' is not supported.", evaluator);
				return;
				break;			
		}
		/* add the corresponding track to the node */
		AddTrackLast( *track );
		/* import the track */
		file >> track;
	}
	
	/* sort the list of track to put the rotate track at the begining */
	//SortTrack();

	/* export recursivly the sons */
	for (i=0; i<nb_sons; i++)
	{
		OR_AnimationNode* new_node=new OR_AnimationNode(this);
		/* add the node to the list of son */
		AddSonLast(*new_node);
		/* recurse on the new node */
		file >> new_node;
	}
}

void OR_AnimationNode::BuildToFile( OR_File& file )
{
	/* write node datas */
	OR_I32 nb=GetNbSon();
	file << nb;
	nb=GetNbTrack();
	file << nb;

	/* export the different tracks */
	for( IT_AnimationTrackList TrackIt=TrackList_.begin(); TrackIt!=TrackList_.end(); ++TrackIt )
	{
		OR_AnimationTrack* pTrack = *TrackIt;
		/* export the type of the track */
		OR_ANIMATION_Track_Type tr_type=pTrack->GetTrackType();
		file << tr_type;
		/* export the type of the evaluator */
		OR_ANIMATION_Evaluator_Type ev_type=pTrack->GetEvaluatorType();
		file << ev_type;
		/* export the track */
		file << pTrack;
	}

	/* recursivly export the different sons */
	for( IT_AnimationNodeList NodeIt=SonList_.begin(); NodeIt!=SonList_.end(); ++NodeIt)
	{
		file << (*NodeIt);
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationNode::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_AnimationNode::BuildSonList(T_ShellObjectList& ShellSonList)
{
	OR_U32 nCpt = 0;

	for( IT_AnimationTrackList TrackIt=TrackList_.begin(); TrackIt!=TrackList_.end(); ++TrackIt )
	{
		OR_AnimationTrack* pTrack = *TrackIt;
		OR_ADD_SHELL_SON(ShellSonList, *pTrack, OR_String("track_") + nCpt );
		nCpt++;
	}

	nCpt = 0;

	for( IT_AnimationNodeList NodeIt=SonList_.begin(); NodeIt!=SonList_.end(); ++NodeIt)
	{
		OR_AnimationNode* pNode = *NodeIt;
		OR_ADD_SHELL_SON(ShellSonList, *pNode, OR_String("animation_node_") + nCpt );
		nCpt++;
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationNode::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_AnimationNode::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, NbSon);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, NbTrack);
}


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

