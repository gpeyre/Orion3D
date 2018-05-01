/*------------------------------------------------------------------------------
/**  \file  OR_SoundSample_fmod.cpp
 *  \brief Implementation of class OR_SoundSample
 *  \author Backchiche 2001-10-29
 */
/*------------------------------------------------------------------------------*/


#include "../stdafx.h"
#include "OR_SoundSample_fmod.h"

using namespace OR;

	
/*------------------------------------------------------------------------------
/**
 * Name : OR_SoundSample_fmod constructor
 *	\param Name name of the sample
 *	\param file file to load
 *  \author Backchiche 2001-10-29
*/
/*------------------------------------------------------------------------------*/

OR_SoundSample_fmod::OR_SoundSample_fmod(char* Name, OR_SOUND_Types Type, FSOUND_SAMPLE *Sample)
{
	strcpy(name,Name);
	type=Type;
	sample=Sample;
}

char* OR_SoundSample_fmod::GetName()
{
	return name;
}

OR_SOUND_Types OR_SoundSample_fmod::GetSoundType()
{
	return type;
}

FSOUND_SAMPLE* OR_SoundSample_fmod::GetSample()
{
	return sample;
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

