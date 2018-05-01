/*------------------------------------------------------------------------------
/**  \file  OR_Sound_fmod.cpp
 *  \brief Implementation of class OR_Sound
 *  \author Backchiche 2001-10-29
 */
/*------------------------------------------------------------------------------*/


#include "../stdafx.h"
#include "OR_Sound_fmod.h"

using namespace OR;

	
/*------------------------------------------------------------------------------
/** Name : OR_Sound_fmod constructor
 *
 *  \param  Sample the sample that this Sound play
 *  \param  system the sound system
 *  \author Backchiche 2001-10-29
 */
/*------------------------------------------------------------------------------*/

OR_Sound_fmod::	OR_Sound_fmod(OR_SoundSample_fmod *Sample)
{
	sample=Sample;
	volume=255;
	channel=-1;
	loopmode=FSOUND_LOOP_OFF;

	position=NULL;
	velocity=NULL;
}

void OR_Sound_fmod::Play()
{
	if (sample==NULL)
		printf("OR_Sound->play : Aucun sample n'a ete charge pour ce son...\n");

	if (sample->GetSoundType()==OR_SOUND_2D)
	{
		channel=FSOUND_PlaySound3DAttrib(channel, sample->GetSample(), -1,volume, FSOUND_STEREOPAN, NULL, NULL);
		if (channel!=-1)
			FSOUND_SetLoopMode(channel,loopmode);
	}
	else
	{	
		FSOUND_Sample_SetLoopMode(sample->GetSample(),loopmode);
		channel=FSOUND_PlaySound3DAttrib(channel, sample->GetSample(), -1,volume, -1, position, velocity);
		FSOUND_Reverb_SetMix(channel, FSOUND_REVERBMIX_USEDISTANCE);
	}
				
}


void OR_Sound_fmod::SetVolume(OR_I32 vol)
{
	if ((vol>-1)&&(vol<256))
		volume=vol;

	if ((channel!=-1)&&FSOUND_IsPlaying(channel))
		FSOUND_SetVolume(channel,volume);
}

OR_I32 OR_Sound_fmod::GetVolume()
{
	return volume;
}



void OR_Sound_fmod::Stop()
{
	if (FSOUND_IsPlaying(channel))
		FSOUND_StopSound(channel);
}


void OR_Sound_fmod::Mute(OR_Bool  mute)
{
	if (channel!=-1)
		FSOUND_SetMute(channel,mute);
}

void OR_Sound_fmod::SetLoop(OR_Bool loop)
{
	if (loop)
		loopmode=FSOUND_LOOP_NORMAL;
	else
		loopmode=FSOUND_LOOP_OFF;
	
	if (sample->GetSoundType() == OR_SOUND_2D)
		if (channel!=-1)
			FSOUND_SetLoopMode(channel,loopmode);
	else
		FSOUND_Sample_SetLoopMode(sample->GetSample(),loopmode);
}


void OR_Sound_fmod::SetPositionVector(OR_Float *pos,OR_Float *vel)
{
	position=pos;
	velocity=vel;
}

void OR_Sound_fmod::SetObject(OR_Object *objet)
{
	position=objet->GetAbsolutePositionPtr();
}

void OR_Sound_fmod::Update()
{
	if (channel!=-1)
		FSOUND_3D_SetAttributes(channel,position,velocity);

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

