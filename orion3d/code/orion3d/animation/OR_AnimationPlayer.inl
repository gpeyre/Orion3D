/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_AnimationPlayer.inl
 *  \brief Inlined methods for \c OR_AnimationPlayer
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_AnimationPlayer.h"

namespace OR {

/** get the animation */

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::GetAnimation
 *
 *  \return The animation that this 
 *  \author Gabriel Peyré 2001-10-24
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Animation* OR_AnimationPlayer::GetAnimation()
{ 
	return Animation; 
}

/** set the speed */

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::SetSpeed
 *
 *  \param  s the speed of the animation, expressed in % per frame.
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationPlayer::SetSpeed(OR_Float s)
{ 
	Speed=s; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::GetSpeed
 *
 *	the speed of the animation, expressed in % per frame.
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_AnimationPlayer::GetSpeed()
{
	return Speed; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::ModifySpeed
 *
 *  \param  rVal increment/decrment for the speed of the animation, expressed in % per frame.
 *	\return the current speed.
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_AnimationPlayer::ModifySpeed(OR_Float rVal)
{
	Speed += rVal;
	return Speed;
}

/** set the behaviour */

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::SetBehaviour
 *
 *  \param  b automatic behaviour for the player (what it does when animation ends).
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationPlayer::SetBehaviour(OR_ANIMATION_Player_Behavior b)
{ 
	Behaviour=b; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::GetBehaviour
 *
 *  \return automatic behaviour for the player (what it does when animation ends).
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ANIMATION_Player_Behavior OR_AnimationPlayer::GetBehaviour()
{ 
	return Behaviour; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::SetTime
 *
 *  \param  t current time of the animation (in [0,1]).
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationPlayer::SetTime(OR_Float t)
{
	Time=t;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::GetTime
 *
 *  \return current time of the animation (in [0,1]).
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_AnimationPlayer::GetTime()
{ 
	return Time; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer constructor
 *
 *  \return make a pause.
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationPlayer::Pause()
{
	bIsActive_ = false;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::Play
 *
 *  \return when in pause, resume.
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationPlayer::Play()
{
	bIsActive_ = true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer constructor
 *
 *  \return current mode.
 *  \author Gabriel Peyré 2001-10-24
 *
 *	toggle between play/pause mode.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_AnimationPlayer::TogglePlayPause()
{
	return bIsActive_ =! bIsActive_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::Restart
 *
 *  \author Gabriel Peyré 2001-10-24
 *
 *	restart the animation at the begining.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_AnimationPlayer::Restart()
{
	Time=0;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::Step
 *
 *  \param  rVal step value.
 *	\return current time.
 *  \author Gabriel Peyré 2001-10-24
 *
 *	Make a step in the animation.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_AnimationPlayer::Step(OR_Float rVal)
{
	Time += rVal;

	return Time;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::Step
 *
 *  \param  bForward do we step forward or backward ?
 *  \return current time.
 *  \author Gabriel Peyré 2001-10-24
 *
 *	Make a step in the animation of an amount equal to the speed (fwd or bwd).
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_AnimationPlayer::Step(OR_Bool bForward)
{
	if( bForward )
		Time += Speed;
	else
		Time -= Speed;

	return Time;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::StepForward
 *
 *  \return current time.
 *  \author Gabriel Peyré 2001-10-24
 *
 *	Make a step forward in the animation of an amount equal to the speed.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_AnimationPlayer::StepForward()
{
	Time += Speed;
	
	return Time;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::StepBackward
 *
 *  \return current time.
 *  \author Gabriel Peyré 2001-10-24
 *
 *	Make a step backward in the animation of an amount equal to the speed.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_AnimationPlayer::StepBackward()
{
	Time -= Speed;
	
	return Time;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::IsPlaying
 *
 *  \return is the animation in play mode ?
 *  \author Gabriel Peyré 2001-10-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_AnimationPlayer::IsPlaying()
{ 
	return bIsActive_; 
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

