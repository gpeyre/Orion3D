
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DisplayableParticule.h
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_DisplayableParticule_h_
#define __OR_DisplayableParticule_h_

#include "../configuration/OR_Config.h"
#include "../physic/OR_Particule.h"
#include "../objects/OR_Mesh.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_DisplayableParticule
 *  \brief  A particule that can ba displayed to screen
 *  \author Gabriel Peyré 2001-07-29
 *	This kind of particule is used in a particule system.
 */ 
/*------------------------------------------------------------------------------*/

class OR_DisplayableParticule: public OR_Particule
{

public:

    OR_DisplayableParticule();
    virtual ~OR_DisplayableParticule();
	
    //-------------------------------------------------------------------------
    /** \name particules system specific */
    //-------------------------------------------------------------------------
    //@{
	void Draw(OR_Mesh* pMesh);
	void Posit();
	OR_Bool IsDead();
    //@}

	//-------------------------------------------------------------------------
    /** \name overload of OR_Particule methods */
    //-------------------------------------------------------------------------
    //@{
	void Update();
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OR_Float GetEnergy();
	void  SetEnergy(const OR_Float rEnergy);
	OR_Float GetEnergyLost();
	void  SetEnergyLost(const OR_Float rEnergyLost);
    //@}

private:

	/** used to compute its color and fade into the background. If energy==0, the particule is dead ... */
	OR_Float rEnergy_;
	/** the energy the particule lost each frame. */
	OR_Float rEnergyLost_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_DisplayableParticule.inl"
#endif


#endif // __OR_DisplayableParticule_h_

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

