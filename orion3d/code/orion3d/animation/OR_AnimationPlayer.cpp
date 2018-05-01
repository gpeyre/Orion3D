/*------------------------------------------------------------------*/
/*                       OR_AnimationPlayer.h                             */
/*------------------------------------------------------------------*/
/* defintion of a player of animations                              */
/*------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_AnimationPlayer.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_AnimationPlayer.h"

#ifndef OR_USE_INLINE
	#include "OR_AnimationPlayer.inl"
#endif

namespace OR
{
	
/*----------------------------------------------------------*/
/*               class OR_AnimationPlayer                   */
/*----------------------------------------------------------*/
/* an animation player is a wrapper used by a node in the   */
/* hierarchy to store a pointer to an animation, and its    */
/* parameters                                               */
/*----------------------------------------------------------*/

OR_AnimationPlayer::OR_AnimationPlayer(OR_Animation* anim, OR_I32 timestoplay, OR_Float speed)
:	TimesPlayed( 0 ),
	Speed      ( speed ),
	Time       ( 0 ),
	bIsActive_ ( 0 ),
	Behaviour  ( OR_ANIMATION_Player_Pause ),
	LastUpdate ( -1 ),
	TimesToPlay( timestoplay ),
	Animation  ( anim )
{
	/* NOTHING */
}

OR_Bool OR_AnimationPlayer::IsFinished()
{
	/* the player should be destry only on OR_ANIMATION_Player_Stop mode */
	if (Behaviour==OR_ANIMATION_Player_Stop)
	{
		if (TimesToPlay<0) return false;
		if (Time>=1)
		{
			return (TimesPlayed+1>=TimesToPlay);
		}
		else return false;
	}
	else return false;
}

void OR_AnimationPlayer::Update(OR_Node* father)
{
	/* check if the animation needs to be restarted */
	if (Time>1)
	{
		/* reset the time regarding Behaviour */
		switch (Behaviour)
		{
		case OR_ANIMATION_Player_Pause:
			this->Pause();
			Time=1;
			break;
		case OR_ANIMATION_Player_Stop:		
			Time=0;
			TimesPlayed++;
			break;
		case OR_ANIMATION_Player_Loop:
			Time=0;
			TimesPlayed++;
			break;
		case OR_ANIMATION_Player_PingPong:
			Speed=-Speed;
			TimesPlayed++;
			break;
		default:
			OR_Globals::MessageHandler()->Warning("OR_AnimationPlayer::Update", "Behaviour %i not supported.", Behaviour);
			break;
		}
	}
	if (Time<0)
	{
		/* reset the time regarding Behaviour */
		switch (Behaviour)
		{
		case OR_ANIMATION_Player_Pause:
			this->Pause();
			break;
		case OR_ANIMATION_Player_Stop:		
			Time=1;
			TimesPlayed++;
			break;
		case OR_ANIMATION_Player_Loop:
			Time=1;
			TimesPlayed++;
			break;
		case OR_ANIMATION_Player_PingPong:
			Speed=-Speed;
			TimesPlayed++;
			break;
		default:
			OR_Globals::MessageHandler()->Warning("OR_AnimationPlayer::Update", "Behaviour %i not supported.", Behaviour);
			break;
		}
	}

	
	/* launch the animation update */
	Animation->Update(father, Time);
	if (LastUpdate>0)
	{
		OR_I64 t=LastUpdate;
		LastUpdate=OR_GetTime();
		/* compute the new time */
		if( this->IsPlaying() ) 
			Time+=Speed  * ((OR_Float)(LastUpdate-t))/(1000*Animation->GetDuration());
		//	Time+=0.001f; /* for debug only !! */
	}
	else
	{
		/* the animation has not yet been updated */
		LastUpdate=OR_GetTime();
	}
}



void OR_AnimationPlayer::DrawTrajectory(OR_Node* cur_node)
{
	Animation->DrawTrajectory(cur_node);
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_AnimationPlayer::BuildSonList(T_ShellObjectList& ShellSonList)
{
	if( this->GetAnimation()!=NULL )
		OR_ADD_SHELL_SON(ShellSonList, *this->GetAnimation(), OR_String("animation") );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationPlayer::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_AnimationPlayer::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Time);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Speed);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, IsFinished);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, IsPlaying);

	OR_ADD_SHELL_FUNC(FuncDeclList, Play,				"Play the animation.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Pause,				"Pause the animation.");
	OR_ADD_SHELL_FUNC(FuncDeclList, TogglePlayPause,	"Toggle play/pause.");
	OR_ADD_SHELL_FUNC(FuncDeclList, StepForward,		"Make one step forward.");
	OR_ADD_SHELL_FUNC(FuncDeclList, StepBackward,		"Make one step backward.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Restart,			"Restart the animation.");
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