/*-------------------------------------------------------------------*/
/*                         OR_SpecialEffect.h                       */
/*-------------------------------------------------------------------*/
/* Created : 14 Apr 2001   18h14                                     */
/*-------------------------------------------------------------------*/

/** \file
	Defines a base class for all special effects.
	\author Gabriel
*/

#ifndef _OR_SPECIAL_EFFECTS_H_
#define _OR_SPECIAL_EFFECTS_H_

#include "../configuration/OR_Config.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_SmartCounter.h"

namespace OR
{
	
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

class ORION3D_API OR_SpecialEffect: public OR_Serializable, public OR_SmartCounter
{

protected:

	/** is the effect active ? */
	OR_Bool bIsActive_;

public:
	
	OR_SpecialEffect();
	virtual ~OR_SpecialEffect();

    //-------------------------------------------------------------------------
    /** \name activity management */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool IsActive();
	OR_Bool SetActivity(OR_Bool a);
	OR_Bool Enable();
	OR_Bool Disable();
	OR_Bool Toggle();
    //@}

    //-------------------------------------------------------------------------
    /** \name virtual methods */
    //-------------------------------------------------------------------------
    //@{
	/** render the special effect to screen */
	virtual void Draw() {}
	/** update the special effect */
	virtual void Update() {}
    //@}

};

} // namespace OR

#ifdef OR_USE_INLINE
	#include "OR_SpecialEffect.inl"
#endif

#endif // _OR_SPECIAL_EFFECTS_H_


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