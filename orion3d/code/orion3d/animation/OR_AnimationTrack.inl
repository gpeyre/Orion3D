/*------------------------------------------------------------------------------*/
/**
 *  \file  OR_AnimationTrack.inl
 *  \brief inlined function of OR_Track 
 *  \author Gabriel Peyré 2001-07-10
 */
/*------------------------------------------------------------------------------*/

#include "OR_AnimationTrack.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/*                      class OR_AnimationTrack                                 */
/*------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationTrack constructor
 *
 *  \param  target the target (position, rotation, ...) of the track
 *  \param  behaviour_before the behaviour (constant, ping pong, ...) after the end of the track
 *  \param  behaviour_after the behaviour (constant, ping pong, ...) before the begining of the track
 *  \author Gabriel Peyré 2001-07-10
 *
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_AnimationTrack::OR_AnimationTrack(OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior behaviour_before, 
														         OR_ANIMATION_Track_Behavior behaviour_after)
{
	Target_=target;
	BehaviourBefore_=behaviour_before;
	BehaviourAfter_=behaviour_after;
	rLength_ = 0;
}

/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationTrack constructor
 *
 *  \author Gabriel Peyré 2001-07-10
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_AnimationTrack::OR_AnimationTrack()
{	
	Target_ = OR_ANIMATION_Target_Undefined;
	rLength_ = 0;
	BehaviourBefore_ = OR_ANIMATION_Behavior_Undefined;
	BehaviourAfter_ = OR_ANIMATION_Behavior_Undefined;
}


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationTrack constructor
 *
 *  \author Gabriel Peyré 2001-07-10
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_AnimationTrack::~OR_AnimationTrack()
{
	/* delete each keyframe */
	for( IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
		OR_DELETE(*it);
}



/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationTrack::GetKeyframeList
 *
 *  \return the list of the keyframe of the track
 *  \author Gabriel Peyré 2001-07-10
 *
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
T_KeyFrameList& OR_AnimationTrack::GetKeyframeList()
{
	return KeyframeList_;
}


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationTrack::AddKeyFrame
 *
 *  \param  &keyframe EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Gabriel Peyré 2001-07-10
 *
 * PUT YOUR COMMENTS HERE
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationTrack::AddKeyFrame(OR_KeyFrame &keyframe)
{
	KeyframeList_.push_back(&keyframe);
}



/*------------------------------------------------------------------------------*/
/**
 * Name : OR_AnimationTrack::AddKeyFrameFirst
 *
 *  \param  &keyframe EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Gabriel Peyré 2001-07-10
 *
 * PUT YOUR COMMENTS HERE
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationTrack::AddKeyFrameFirst(OR_KeyFrame &keyframe)
{
	KeyframeList_.push_front(&keyframe);
}


/*------------------------------------------------------------------------------
/**
 * Name : OR_AnimationTrack::AddKeyFrameLast
 *
 *  \param  &keyframe EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Gabriel Peyré 2001-07-10
 *
 * PUT YOUR COMMENTS HERE
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationTrack::AddKeyFrameLast(OR_KeyFrame &keyframe)
{
	KeyframeList_.push_back(&keyframe);
}



/*------------------------------------------------------------------------------*/
/** 
 *  Name : OR_AnimationTrack::RemoveKeyFrame
 *
 *  \param  &keyframe EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Gabriel Peyré 2001-07-10
 *
 * PUT YOUR COMMENTS HERE
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationTrack::RemoveKeyFrame(OR_KeyFrame &keyframe)
{
	KeyframeList_.remove(&keyframe);
}

/*------------------------------------------------------------------------------
/** 
 *  Name : OR_AnimationTrack::SetLength
 *
 *  \param  length the duration of the animation 
 *  \author Gabriel Peyré 2001-07-10
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationTrack::SetLength(OR_Float length)
{
	rLength_=length;
}

/*------------------------------------------------------------------------------
/** Name : OR_AnimationTrack::GetLength
 *
 *  \return the duration of the animation
 *  \author Gabriel Peyré 2001-07-10
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_AnimationTrack::GetLength()
{
	return rLength_;
}


/*------------------------------------------------------------------------------
/** Name : OR_AnimationTrack::SetBehaviour
 *
 *  \param  BehaviourBefore the behaviour of the animation before the begining
 *  \param  BehaviourAfter the behaviour of the animation after the end
 *  \author Gabriel Peyré 2001-07-10
 *
 * The behaviour describe the way animation will be played outside the range.
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationTrack::SetBehaviour(OR_ANIMATION_Track_Behavior BehaviourBefore, OR_ANIMATION_Track_Behavior BehaviourAfter)
{
	BehaviourBefore_=BehaviourBefore;
	BehaviourAfter_=BehaviourAfter;
}


/*------------------------------------------------------------------------------
/** Name : OR_AnimationTrack::SetBehaviourBefore
 *
 *  \param  BehaviourBefore the behaviour of the animation before the begining
 *  \author Gabriel Peyré 2001-07-10
 *
 * The behaviour describe the way animation will be played outside the range.
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationTrack::SetBehaviourBefore(OR_ANIMATION_Track_Behavior BehaviourBefore)
{
	BehaviourBefore_=BehaviourBefore;
}


/*------------------------------------------------------------------------------
/** Name : OR_AnimationTrack::SetBehaviourAfter
 *
 *  \param  BehaviourAfter the behaviour of the animation after the end
 *  \author Gabriel Peyré 2001-07-10
 *
 * The behaviour describe the way animation will be played outside the range.
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationTrack::SetBehaviourAfter(OR_ANIMATION_Track_Behavior BehaviourAfter)
{
	BehaviourAfter_=BehaviourAfter;
}


/*------------------------------------------------------------------------------
/** Name : OR_AnimationTrack::GetBehaviourBefore
 *
 *  \return the behaviour of the animation after the end
 *  \author Gabriel Peyré 2001-07-10
 *
 * The behaviour describe the way animation will be played outside the range.
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ANIMATION_Track_Behavior OR_AnimationTrack::GetBehaviourBefore()
{
	return BehaviourBefore_;
}


/*------------------------------------------------------------------------------
/** Name : OR_AnimationTrack::GetBehaviourAfter
 *
 *  \return the behaviour of the animation after the end
 *  \author Gabriel Peyré 2001-07-10
 *
 * The behaviour describe the way animation will be played outside the range.
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ANIMATION_Track_Behavior OR_AnimationTrack::GetBehaviourAfter()
{
	return BehaviourAfter_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationTrack::GetTarget
 *
 *  \return the target of the animation
 *  \author Gabriel Peyré 2001-07-10
 *
 * the target of the animation is the part of the object that is animated (position, rotation ...).
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ANIMATION_Target OR_AnimationTrack::GetTarget()
{
	return Target_;
}

/** set the target */

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationTrack::SetTarget
 *
 *  \param  target the new target of the animation
 *  \author Gabriel Peyré 2001-07-10
 *
 * the target of the animation is the part of the object that is animated (position, rotation ...).
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationTrack::SetTarget(OR_ANIMATION_Target target)
{
	Target_=target;
}

/** is the target a rotation one */

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationTrack::IsRotationTarget
 *
 *  \return true if the target of the track is rotation. 
 *  \author Gabriel Peyré 2001-07-10
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_AnimationTrack::IsRotationTarget()
{
	return (Target_==OR_ANIMATION_Target_Rot);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationTrack::IsTranslationTarget
 *
 *  \return true if the target of the track is translation [on 1 or 3 axis]
 *  \author Gabriel Peyré 2001-07-10
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_AnimationTrack::IsTranslationTarget()
{
	return (Target_==OR_ANIMATION_Target_Pos  ||
			Target_==OR_ANIMATION_Target_PosX ||
			Target_==OR_ANIMATION_Target_PosY ||
			Target_==OR_ANIMATION_Target_PosZ);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationTrack::IsScaleTarget
 *
 *  \return true if the target is scale [on 1 or 3 axis]
 *  \author Gabriel Peyré 2001-07-10
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_AnimationTrack::IsScaleTarget()
{
	return (Target_==OR_ANIMATION_Target_Scale  ||
			Target_==OR_ANIMATION_Target_ScaleX ||	
			Target_==OR_ANIMATION_Target_ScaleY ||
			Target_==OR_ANIMATION_Target_ScaleZ);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationTrack::GetTrackType
 *
 *  \return the type of the track (OR_Float, quats, etc ...) 
 *  \author Gabriel Peyré 2001-07-10
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ANIMATION_Track_Type OR_AnimationTrack::GetTrackType()
{
	return OR_ANIMATION_Track_Undefined;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationTrack::GetEvaluatorType
 *
 *  \return the evaluator of the track (bezier, tcb, etc ...)
 *  \author Gabriel Peyré 2001-07-10
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ANIMATION_Evaluator_Type OR_AnimationTrack::GetEvaluatorType()
{
	return OR_ANIMATION_Evaluator_Undefined; 
}

} // namespace OR 

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