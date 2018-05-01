/*-------------------------------------------------------------------*/
/*                         OR_SpecialEffects.h                       */
/*-------------------------------------------------------------------*/
/* Created : 14 Apr 2001   18h14                                     */
/*-------------------------------------------------------------------*/

/** \file
	Defines a base class for all special effects.
	\author Gabriel
*/

#ifndef _OR_SPECIAL_EFFECTS_
#define _OR_SPECIAL_EFFECTS_

#include "../configuration/OR_Config.h"

/*-------------------------------------------------------------------*/
/*                         class OR_SpecialEffect                    */
/*-------------------------------------------------------------------*/
/* base class for all special effects.                               */
/*-------------------------------------------------------------------*/

/// base class for all special effects.
/**
	Basicaly, a special effect is after the hierarchy.
	Most special effects (but not all) shares the same proprieties :
		- they use element of the hierarchy as parameters (such as gizmo emmeters ...).
		- they update themselves each frame.
		- they draw themselves each frame.
	That's the reason of that interface !
	Note that each methodes is not pure virtual, as some class don't want to overload some feature.
	\author Gabriel
*/

class OR_SpecialEffect
{

protected:

	/** is the effect active ? */
	OR_Bool IsActive;

public:

	/** constructor */
	OR_SpecialEffect()
	{ IsActive=true; }
	
	/** get the activity */
	OR_Bool GetActivity()
	{ return IsActive; }
	/** set the activity 
		\return previous activity */
	OR_Bool SetActivity(OR_Bool act)
	{ OR_Bool old=IsActive; IsActive=act; return old; }
	/** set the activity to true
		\return previous activity */
	OR_Bool Enable()
	{ OR_Bool old=IsActive; IsActive=true; return old; }
	/** set the activity to false
		\return previous activity */
	OR_Bool Disable()
	{ OR_Bool old=IsActive; IsActive=false; return old; }

	/** render the special effect to screen */
	virtual void Draw() {}
	/** update the special effect */
	virtual void Update() {}
};


#endif /* _OR_SPECIAL_EFFECTS_ */


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////