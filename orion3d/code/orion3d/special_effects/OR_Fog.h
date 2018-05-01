/*---------------------------------------------------------------------*/
/*                                   OR_Fog.h                          */
/*---------------------------------------------------------------------*/
/*              definition de la classe OR_Fog                         */            
/*---------------------------------------------------------------------*/
/* Gabriel Peyre - nikopol0@club-internet.fr                           */
/*---------------------------------------------------------------------*/

/** \file 
	NOT UP TO DATE.
	\author Gabriel.
**/

#ifndef _OR_FOG_H_
#define _OR_FOG_H_

#include "../configuration/OR_Config.h"
#include "OR_SpecialEffect.h"

namespace OR
{
	
/*----------------------------------------------------------------------*/
/*                                 classe OR_Fog                        */
/*----------------------------------------------------------------------*/
/*       permet de creer et de gerer un brouillard                      */
/*----------------------------------------------------------------------*/

/// a fog. NOT UP TO DATE.
/** \todo write a brand new fog class, and a volumetric fog one. */
class ORION3D_API OR_Fog: public OR_SpecialEffect
{
private:
        OR_Float Color[3];
        GLenum Type;
        OR_Float Density, Start, End;
public:
	/** constructor */
	OR_Fog()
	:OR_SpecialEffect()
	{}
	// methode de creation :
	void Creat(OR_Float start, OR_Float end, 
				OR_Float density, OR_Float color[3]);		
	// methodes d'activation/d»sactivation :
	void Enable();
	void Disable();
	OR_Bool Toggle();
	void ToggleType();
	// methodes de modification :
	void Mod(OR_Float start, OR_Float end,
	 		OR_Float density, OR_Float color[4]);
	void ModDensity(OR_Float);
	void ModColor(OR_Coord_RVBA component, OR_Float);
	void ModColor(OR_Float vect[3]);

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildFromFile( OR_File& file );
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_Fog);
    //@}
};


} // namespace OR

#endif     /* #ifndef _OR_FOG_H_ */


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