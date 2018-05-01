
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SoundSample_fmod.h
 *  \brief Definition of class \c OR_SoundSample_fmod
 *  \author Backchiche 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SoundSample_fmod_h_
#define __OR_SoundSample_fmod_h_

#include "../configuration/OR_Config.h"
#include "../../fmod/fmod.h"
#include "../../fmod/fmod_errors.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SoundSample_fmod.h
 *  \brief  a simple sample.
 *  \author Backchiche 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/

class OR_SoundSample_fmod
{
public:
    //-------------------------------------------------------------------------
    /** \name constructors & destructors */
    //-------------------------------------------------------------------------
    //@{
	OR_SoundSample_fmod(char* Name, OR_SOUND_Types Type, FSOUND_SAMPLE *Sample);
    //@}
	
	char* GetName();
	OR_SOUND_Types GetSoundType();
	FSOUND_SAMPLE* GetSample();

private:
	char name[128];
	OR_SOUND_Types type;
	FSOUND_SAMPLE *sample;
};

typedef list<OR_SoundSample_fmod*> T_SoundSampleList;
typedef T_SoundSampleList::iterator IT_SoundSampleList;

} // End namespace OR



#endif // __OR_SoundSample_fmod_h_

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
