/*------------------------------------------------------------------------------*/
/**
 *  \file  OR_AnimationNode.inl
 *  \brief A node in a hierachical animation.
 *  \author Gabriel Peyré 2001-07-08
 *-------------------------------------------------------------------------------*/
#include "OR_AnimationNode.h"

namespace OR {
	

/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationNode::AddSon
 *
 *  \param  &node the node to add to the list of sons
 *  \author Gabriel Peyré 2001-07-08
 *
 * add a son at the end of the list of son
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationNode::AddSon(OR_AnimationNode &node)
{
	SonList_.push_back(&node);
}


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationNode::AddSonLast
 *
 *  \param  &node the node to add to the list of sons
 *  \author Gabriel Peyré 2001-07-08
 *
 * add a son at the end of the list of son
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationNode::AddSonLast(OR_AnimationNode &node)
{
	SonList_.push_back(&node);
}


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationNode::AddSonFirst
 *
 *  \param  &pNode the node to add to the list of sons
 *  \author Gabriel Peyré 2001-07-08
 *
 * add a son at the begining of the list of son
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationNode::AddSonFirst(OR_AnimationNode &node)
{
	SonList_.push_front(&node);
}


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationNode::AddTrack
 *
 *  \param  track the track to add to the list 
 *  \author Gabriel Peyré 2001-07-08
 *
 * add a track at the end of the list of track
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationNode::AddTrackLast(OR_AnimationTrack& track)
{
	TrackList_.push_back( &track );
}


/*------------------------------------------------------------------------------
 * Name : OR_AnimationNode::AddTrackFirst
 *
 *  \param  &track EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-12-04
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationNode::AddTrackFirst(OR_AnimationTrack &track)
{
	TrackList_.push_front( &track );
}



/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationNode::GetNbSon
 *
 *  \return the number of sons of the node
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_I32 OR_AnimationNode::GetNbSon()
{
	return SonList_.size();
}


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationNode::GetNbTrack
 *
 *  \return the number of track on the node
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_I32 OR_AnimationNode::GetNbTrack()
{
	return TrackList_.size();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationNode::GetFather
 *
 *  \return the father of the node
 *  \author Gabriel Peyré 2001-07-11
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_AnimationNode* OR_AnimationNode::GetFather()
{
	return this->pFather_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationNode::SetFather
 *
 *  \param  pFather the father of the node
 *  \author Gabriel Peyré 2001-07-11
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationNode::SetFather(OR_AnimationNode* pFather)
{
	this->pFather_ = pFather_;
}


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationNode::GetTrackList
 *
 *  \return list of track of the node
 *  \author Gabriel Peyré 2001-07-08
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
T_AnimationTrackList& OR_AnimationNode::GetTrackList()
{
	return TrackList_;
}


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationNode::GetSonList
 *
 *  \return list of sons of the node
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
OR_INLINE
T_AnimationNodeList& OR_AnimationNode::GetSonList()
{
	return SonList_;
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

