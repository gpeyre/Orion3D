
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SpecialEffectManager.h
 *  \brief definition of a manager of special effects.
 *  \author Gabriel Peyré 2001-07-20
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SpecialEffectManager_h_
#define __OR_SpecialEffectManager_h_

#include "../configuration/OR_Config.h"
#include "OR_SpecialEffect.h"
#include "../utils/OR_SmartManagerMap_Template.h"
#include "../utils/OR_Serializable.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SpecialEffectManager
 *  \brief  A manager of special effects
 *  \author Gabriel Peyré 2001-07-20
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_SmartManagerMap_Template<OR_SpecialEffect>;

class ORION3D_API OR_SpecialEffectManager: public OR_SmartManagerMap_Template<OR_SpecialEffect>, public OR_Serializable
{

public:

	void Update();
	void Draw();
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildFromFile( OR_File& file );
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_SpecialEffectManager);
    //@}

private:

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_SpecialEffectManager.inl"
#endif


#endif // __OR_SpecialEffectManager_h_

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
