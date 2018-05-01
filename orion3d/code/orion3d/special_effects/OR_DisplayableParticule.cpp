/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DisplayableParticule.cpp
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_DisplayableParticule.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_DisplayableParticule.h"

#ifndef OR_USE_INLINE
	    #include "OR_DisplayableParticule.inl"
#endif

using namespace OR;



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule::Update
 *
 *  \author Gabriel Peyré 2001-07-29
 *
 *	Update the energy of the particule 
 *	\todo use absolute time.
 */ 
/*------------------------------------------------------------------------------*/
void OR_DisplayableParticule::Update()
{
	rEnergy_ -= rEnergyLost_;
}



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

