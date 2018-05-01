/*------------------------------------------------------------------*/
/*                       OR_Animation.h                             */
/*------------------------------------------------------------------*/
/* defintion of a player of animations                              */
/*------------------------------------------------------------------*/

/** \file 
	An animtion player is present on each node of a hierarchy.
	You can push an animation on it, and it will be played on the 
	sub-tree of the node.
	The player also allow to control the way the animation is played
	\author Gabriel.
**/


#ifndef _OR_ANIMATIONPLAYER_H_
#define _OR_ANIMATIONPLAYER_H_

#include "../configuration/OR_Config.h"
#include "OR_Animation.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"

namespace OR
{

class OR_Animation;

/*----------------------------------------------------------*/
/*               class OR_AnimationPlayer                   */
/*----------------------------------------------------------*/
/* an animation player is a wrapper used by a node in the   */
/* hierarchy to store a pointer to an animation, and its    */
/* parameters                                               */
/*----------------------------------------------------------*/


/*! \ingroup group_animation
 *  \brief class OR_AnimationPlayer in group group_animation
 */

/// the animation of a sub-tree.
/** 
	an animation player is a wrapper used by a node in the
	hierarchy to store a pointer to an animation, and its parameters.
	\author Gabriel
*/

class ORION3D_API OR_AnimationPlayer: public OR_ShellObject_ABC
{

public:

	/** constructor */
	OR_AnimationPlayer(OR_Animation *anim=NULL, OR_I32 timestoplay=1, OR_Float speed=1);

	/** get the animation */
	OR_Animation *GetAnimation();

    //-------------------------------------------------------------------------
    /** \name methods used by the hyerarchy */
    //-------------------------------------------------------------------------
    //@{
	/** is the animation finished (should the player be removed) */
	OR_Bool IsFinished();
	OR_Bool GetIsFinished()
	{ return this->IsFinished(); }
	/** update the sub-tree 0<t<1 */
	void Update(OR_Node* father);
    //@}


    //-------------------------------------------------------------------------
    /** \name set up animation parameters */
    //-------------------------------------------------------------------------
    //@{
	/** set the speed */
	void SetSpeed(OR_Float s);
	/** get the speed */
	OR_Float GetSpeed();
	OR_Float ModifySpeed(OR_Float rVal);
	/** set the behaviour */
	void SetBehaviour(OR_ANIMATION_Player_Behavior b);
	/** get the behaviour */
	OR_ANIMATION_Player_Behavior GetBehaviour();
	/** set the playing time */
	void SetTime(OR_Float t);
	/** get the playing time */
	OR_Float GetTime();
    //@}


    //-------------------------------------------------------------------------
    /** \name handle the player */
    //-------------------------------------------------------------------------
    //@{
	/** pause the animation */
	void Pause();
	/** play the animation */
	void Play();
	/** toggel play/pause */
	OR_Bool TogglePlayPause();
	/** restart the animation */
	void Restart();
	OR_Float Step(OR_Float rVal);
	OR_Float Step(OR_Bool bForward = true);
	OR_Float StepForward();
	OR_Float StepBackward();
	/** \return true if the animation player is playing */
	OR_Bool IsPlaying();
	OR_Bool GetIsPlaying()
	{ return this->IsPlaying(); }
    //@}


    //-------------------------------------------------------------------------
    /** \name helpers */
    //-------------------------------------------------------------------------
    //@{
	/** draw the trajectories of all sub-tree */
	void DrawTrajectory(OR_Node* cur_node);
    //@}
	
	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	
	OR_DECL_SHELL_ACCESSOR_FUNC(Time,			OR_AnimationPlayer, Float);
	OR_DECL_SHELL_ACCESSOR_FUNC(Speed,			OR_AnimationPlayer, Float);
	OR_DECL_SHELL_GET_PRINT_FUNC(IsFinished,	OR_AnimationPlayer, Bool);
	OR_DECL_SHELL_GET_PRINT_FUNC(IsPlaying,		OR_AnimationPlayer, Bool);

	OR_DECL_IMPL_SHELL_FUNC(Play,				OR_AnimationPlayer);
	OR_DECL_IMPL_SHELL_FUNC(Pause,				OR_AnimationPlayer);
	OR_DECL_IMPL_SHELL_FUNC(TogglePlayPause,	OR_AnimationPlayer);
	OR_DECL_IMPL_SHELL_FUNC(StepForward,		OR_AnimationPlayer);
	OR_DECL_IMPL_SHELL_FUNC(StepBackward,		OR_AnimationPlayer);
	OR_DECL_IMPL_SHELL_FUNC(Restart,			OR_AnimationPlayer);
    //@}

	
private:
	
	/** the animation that is played */
	OR_Animation *Animation;
	/** the speed of the animation [a multiplyer factor] */
	OR_Float Speed;
	/** the current time in the animation, start from 0 to 1 */
	OR_Float Time;
	/** the number of times the animation has been played */
	OR_I32 TimesPlayed;
	/** the number of time the animation must be played, infinite loop if <0 */
	OR_I32 TimesToPlay;
	/** time of the last update */
	OR_I64 LastUpdate;
	/** use to pause/continue the animation */
	OR_Bool bIsActive_;
	/** what is done when the animation end */
	OR_ANIMATION_Player_Behavior Behaviour;

};

} // namespace OR

#ifdef OR_USE_INLINE
	#include "OR_AnimationPlayer.inl"
#endif

#endif // _OR_ANIMATIONPLAYER_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////