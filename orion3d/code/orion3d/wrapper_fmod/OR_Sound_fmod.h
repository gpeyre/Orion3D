/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Sound_fmod.h
 *  \brief Definition of class \c OR_Sound
 *  \author Backchiche 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Sound_fmod_h_
#define __OR_Sound_fmod_h_

#include "../configuration/OR_Config.h"
#include "../Objects/OR_Object.h"

#include "OR_SoundSample_fmod.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Sound_fmod.h
 *  \brief  a simple sound object.
 *  \author Backchiche 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/

class OR_Sound_fmod
{
public:
    //-------------------------------------------------------------------------
    /** \name constructors & destructors */
    //-------------------------------------------------------------------------
    //@{
	OR_Sound_fmod(OR_SoundSample_fmod *Sample);
    //@}


	void Play();

	void SetVolume(OR_I32 vol);
	OR_I32 GetVolume();
	void Stop();
	void Mute(OR_Bool  mute);
	void SetLoop(OR_Bool loop);
	void SetChannel(OR_I32 chan);

	void SetPositionVector(OR_Float *pos,OR_Float *vel);
	void SetObject(OR_Object *objet);
	void Update();

private:
	OR_I32 volume;
	OR_I32 channel;
	OR_SoundSample_fmod *sample;
	OR_U32 loopmode;
	OR_Float *position;
	OR_Float *velocity;
	OR_Object	*objet;
};

typedef list<OR_Sound_fmod*> T_SoundList;
typedef T_SoundList::iterator IT_SoundList;

} // End namespace OR


#endif // __OR_Sound_fmod_h_

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
