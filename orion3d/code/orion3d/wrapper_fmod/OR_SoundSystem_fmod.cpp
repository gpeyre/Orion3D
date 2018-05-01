/*------------------------------------------------------------------------------
/* *  \file  OR_SoundSystem_fmod.cpp
 *  \brief Implementation of class OR_SoundSystem_fmod
 *  \author Backchiche 2001-10-29
 */
/*------------------------------------------------------------------------------*/


#include "../stdafx.h"
#include "OR_SoundSystem_fmod.h"

using namespace OR;

	
/*------------------------------------------------------------------------------
/** Name : OR_SoundSystem_fmod constructor
 *
 *  \author Backchiche 2001-10-29
 */
/*------------------------------------------------------------------------------*/

OR_SoundSystem_fmod::OR_SoundSystem_fmod()
{
	if (FSOUND_GetVersion() < FMOD_VERSION){
		OR_Globals::MessageHandler()->Warning("OR_SoundSystem_fmod Constructor","Bad version of fmod :%.02f\n", FMOD_VERSION);
		return;
	}

	iNb_Soft_Channel=32;
	iNb_Hard_Channel=0;
	listener=NULL;

	DetectBestOutput();
}

OR_SoundSystem_fmod::~OR_SoundSystem_fmod()
{
	for( IT_SoundSampleList Sample=SampleList_.begin(); Sample!=SampleList_.end(); ++Sample )
		OR_DELETE(*Sample);

	FSOUND_Close();
}

OR_I32 OR_SoundSystem_fmod::SetOutput(OR_I32 outputype)
{
	return FSOUND_SetOutput(outputype);
}

OR_I32 OR_SoundSystem_fmod::DetectBestOutput()
{
	OR_A3D=false;
	OR_WINMM=false;
	OR_DSOUND=false;

	// teste WinMM
	SetOutput(FSOUND_OUTPUT_WINMM);

	//teste l'initialisation a 44,1kHz
	if (FSOUND_Init(44100, iNb_Soft_Channel, 0))
	{
		OR_WINMM=true;
		FSOUND_Close();
	}
	
	// teste DirectSound
	SetOutput(FSOUND_OUTPUT_DSOUND);

	//teste l'initialisation a 44,1kHz
	if (FSOUND_Init(44100, iNb_Soft_Channel , 0))
	{
		OR_DSOUND=true;
		FSOUND_Close();
	}
	
	// teste l'A3D
	SetOutput(FSOUND_OUTPUT_A3D);

	//teste l'initialisation a 44,1kHz
	if (FSOUND_Init(44100, iNb_Soft_Channel, 0))
	{
		OR_A3D=true;
		FSOUND_Close();
	}

	// initialise la bonne sortie
	if(OR_DSOUND)
		SetOutput(FSOUND_OUTPUT_DSOUND);
	else if(OR_WINMM)	
		SetOutput(FSOUND_OUTPUT_WINMM);


	// récupère le driver 
	// qui gère le son 3D en hard si possible....

	OR_I32 hard=0;

	for (OR_I32 i=0; i < FSOUND_GetNumDrivers(); i++) 
	{
//		printf("%d - %s\n", i+1, FSOUND_GetDriverName(i));	// print driver names
		{
			OR_U32 caps = 0;

			FSOUND_GetDriverCaps(i, (unsigned int*) &caps);
			
			if (caps & FSOUND_CAPS_HARDWARE)
			{	
				hard=i;
//				printf("  * Driver supports hardware 3D sound!\n");
			}
/*			if (caps & FSOUND_CAPS_EAX)
				printf("  * Driver supports EAX reverb!\n");
			if (caps & FSOUND_CAPS_GEOMETRY_OCCLUSIONS)
				printf("  * Driver supports hardware 3d geometry processing with occlusions!\n");
			if (caps & FSOUND_CAPS_GEOMETRY_REFLECTIONS)
				printf("  * Driver supports hardware 3d geometry processing with reflections!\n");
			if (caps & FSOUND_CAPS_EAX2)
				printf("  * Driver supports EAX 2.0 reverb!\n");
*/		}
	}

//	printf("\n-> Driver selectionne: %d\n",hard);

	FSOUND_SetDriver(hard);	
	

	caps = 0;

	OR_SOUND_HARD=OR_SOUND_EAX=OR_SOUND_GEOM_OCCLUSIONS=OR_SOUND_GEOM_REFLECTION=OR_SOUND_EAX2=false;
	

	FSOUND_GetDriverCaps(FSOUND_GetDriver(), (unsigned int*) &caps);

//	if (!caps)
//		printf("B( Le driver ne supporte que le mode software.\n Dommage pour le son 3D.\n");
	if (caps & FSOUND_CAPS_HARDWARE)
	{
		OR_SOUND_HARD=true;
//		printf(":) Le driver supporte le son 3D en hard\n");
	}
//	else
//		printf(":( Le driver ne supporte pas le son 3D en hard\n");
	if (caps & FSOUND_CAPS_EAX)
	{
		OR_SOUND_EAX=true;
//		printf(":) Le driver supporte la reverb EAX\n");
	}
//	else
//		printf(":( Le driver ne supporte pas la reverb EAX\n");

	if (caps & FSOUND_CAPS_GEOMETRY_OCCLUSIONS)
	{
		OR_SOUND_GEOM_OCCLUSIONS=true;
//		printf(":) Le driver supporte en hard la '3d geometry processing with occlusions'\n");
	}
//	else
//		printf(":( Le driver ne supporte pas en hard la '3d geometry processing with occlusions'\n");
	if (caps & FSOUND_CAPS_GEOMETRY_REFLECTIONS)
	{
		OR_SOUND_GEOM_REFLECTION=true;
//		printf(":) Le driver supporte en hard la '3d geometry processing with reflections'\n");
	}
//	else
//		printf(":( Le driver ne supporte pas en hard la '3d geometry processing with reflections'\n");

	if (caps & FSOUND_CAPS_EAX2)
	{
		OR_SOUND_EAX2=true;
//		printf(":) Le driver supporte la reverb EAX2\n");
	}
//	else
//		printf(":( Le driver ne supporte pas la reverb EAX2\n");


	// ben initialise l'affaire...44,1kHz - max soft channel 32
	FSOUND_Init(44100, iNb_Soft_Channel, 0);

	// Récupère le nombre de canaux...

//	printf("Nombre de canaux en hard : %d\n",FSOUND_GetNumHardwareChannels());

//	printf("Nombre total de canaux : %d\n",FSOUND_GetMaxChannels());

	iNb_Hard_Channel=FSOUND_GetNumHardwareChannels();

	return 1;
}

void OR_SoundSystem_fmod::AddSample(char *name, char *path, OR_SOUND_Types type)
{
	OR_I32 bExist=0;

	for(IT_SoundSampleList it = SampleList_.begin() ; it!=SampleList_.end() && !bExist ; ++it )
	{
		OR_SoundSample_fmod *pSample = *it;
		if (!strcmp(pSample->GetName(),name))
			bExist=1;
	}

	if (bExist)
		OR_Globals::MessageHandler()->Warning("OR_SoundSystem_fmod::AddSample","The name %s already exist",name);
	else
	{
		FSOUND_SAMPLE *pfsample;
		
		if(type==OR_SOUND_2D)
			pfsample=FSOUND_Sample_Load(FSOUND_UNMANAGED, path, FSOUND_2D, 0);
		else
			pfsample=FSOUND_Sample_Load(FSOUND_UNMANAGED, path,FSOUND_HW3D, 0);

		if(pfsample)
		{
			OR_SoundSample_fmod *pSample = new OR_SoundSample_fmod(name,type,pfsample);
			AddSample(*pSample);

		}else
			OR_Globals::MessageHandler()->Warning("OR_SoundSystem_fmod::AddSample","L'ajout du sample a echoue\nnom:%s\npath:%s\n",name,path);
	}
		
}

OR_I32 OR_SoundSystem_fmod::PlaySample(char *name)
{
	OR_I32 bExist=0;
	OR_SoundSample_fmod *pSample;

	for(IT_SoundSampleList it = SampleList_.begin() ; it!=SampleList_.end() && !bExist ; ++it )
	{
		pSample = *it;
		if (!strcmp(pSample->GetName(),name))
			bExist=1;
	}

	if (bExist)
		return FSOUND_PlaySound3DAttrib(FSOUND_FREE, pSample->GetSample(), -1, 255, FSOUND_STEREOPAN, NULL, NULL);


	OR_Globals::MessageHandler()->Warning("OR_SoundSystem_fmod::PlaySample","The sample %s doesn't exist",name);

	return 0;
}

OR_I32 OR_SoundSystem_fmod::GetNbSample()
{
	return SampleList_.size();
}


void OR_SoundSystem_fmod::AddSample(OR_SoundSample_fmod& sample)
{
	SampleList_.push_back(&sample);
}

OR_Sound_fmod* OR_SoundSystem_fmod::NewSound(char *sample)
{
	OR_I32 bExist=0;
	OR_SoundSample_fmod *pSample;
	OR_Sound_fmod *pSound;

	for(IT_SoundSampleList it = SampleList_.begin() ; it!=SampleList_.end() && !bExist ; ++it )
	{
		pSample = *it;
		if (!strcmp(pSample->GetName(),sample))
			bExist=1;
	}

	if (bExist)
	{
		pSound = new OR_Sound_fmod(pSample);
		SoundList_.push_back(pSound);
		return pSound;
	}

	OR_Globals::MessageHandler()->Warning("OR_SoundSystem_fmod::NewSound","The sample %s doesn't exist",sample);

	return 0;

}

void OR_SoundSystem_fmod::SystemUpdate()
{
	// Update de ts les sons....

	for(IT_SoundList it = SoundList_.begin() ; it!=SoundList_.end() ; ++it )
	{
		OR_Sound_fmod *pSound= *it;
		pSound->Update();
	}

	if (listener)
	{
		OR_Float *pos;
		OR_Float vel[3]={0,0,0};



		OR_Float *FORWARD = (OR_Float*)(-listener->GetAbsoluteMatrix().GetZ()).GetCoord();
		OR_Float *TOP = (OR_Float*)(-listener->GetAbsoluteMatrix().GetY()).GetCoord();

		pos=listener->GetAbsolutePositionPtr();

		FSOUND_3D_Listener_SetAttributes(pos,&vel[0],FORWARD[0],FORWARD[1],FORWARD[2],TOP[0],TOP[1],TOP[2]);
	}

	FSOUND_3D_Update();
}


void OR_SoundSystem_fmod::SetListener(OR_Object *objet)
{
	listener=objet;
}

