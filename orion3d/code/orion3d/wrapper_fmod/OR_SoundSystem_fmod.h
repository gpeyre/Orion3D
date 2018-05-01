
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SoundSystem.h
 *  \brief Definition of class \c OR_SoundSystem
 *  \author Backchiche 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SoundSystem_fmod_h_
#define __OR_SoundSystem_fmod_h_


#include "../configuration/OR_Config.h"

#include "../../fmod/fmod.h"
#include "../../fmod/fmod_errors.h"
#include "../Objects/OR_Object.h"

#include "OR_SoundSample_fmod.h"
#include "OR_Sound_fmod.h"

#pragma comment (lib, "fmodvc.lib")

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SoundSystem_fmod
 *  \author Backchiche 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/
class OR_SoundSystem_fmod
{
public:
	OR_SoundSystem_fmod();
	~OR_SoundSystem_fmod();

	OR_I32 SetOutput(OR_I32 outputype);
	OR_I32 DetectBestOutput();
	
	void AddSample(char *name, char *path, OR_SOUND_Types type);
	OR_I32 PlaySample(char *name);
	OR_I32 GetNbSample();

	OR_Sound_fmod* NewSound(char *sample); 

	void SystemUpdate();
	void SetListener(OR_Object *objet);

private:
	void AddSample(OR_SoundSample_fmod& sample);

	OR_Bool OR_A3D,OR_DSOUND,OR_WINMM,OR_SOUND_HARD,OR_SOUND_EAX,OR_SOUND_GEOM_OCCLUSIONS
		,OR_SOUND_GEOM_REFLECTION,OR_SOUND_EAX2;

	OR_U32		caps;
	OR_I32		iNb_Hard_Channel,iNb_Soft_Channel;

	OR_Object* listener;

	T_SoundSampleList	SampleList_;
	T_SoundList			SoundList_;
};

} // End namespace OR

#endif // __OR_SoundSystem_fmod_h_

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
