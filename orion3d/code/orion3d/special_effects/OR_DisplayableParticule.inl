/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DisplayableParticule.inl
 *  \brief inlined function of class OR_DisplayableParticule.
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_DisplayableParticule.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule constructor
 *
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_DisplayableParticule::OR_DisplayableParticule()
:OR_Particule()
{
	rEnergyLost_=0.01f;
	rEnergy_=1.0f;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule destructor
 *
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_DisplayableParticule::~OR_DisplayableParticule()
{
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule::Draw
 *
 *  \param  pMesh The mesh used for the shape
 *  \author Gabriel Peyré 2001-07-29
 *
 *	Draw the particule.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_DisplayableParticule::Draw(OR_Mesh* pMesh)
{
	if( pMesh==NULL )
	{
		UnRotateModelViewMatrix();
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetCullingMode(OR_Culling_None);
		OR_Globals::Context()->SetColor(1,1,1);
		/* the shape is not defined */
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(-OR_PARTICULES_DefaultSize,  OR_PARTICULES_DefaultSize, 0);
			glVertex3f(-OR_PARTICULES_DefaultSize, -OR_PARTICULES_DefaultSize, 0);
			glVertex3f( OR_PARTICULES_DefaultSize,  OR_PARTICULES_DefaultSize, 0);
			glVertex3f( OR_PARTICULES_DefaultSize, -OR_PARTICULES_DefaultSize, 0);		
		glEnd();
		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->SetDefaultCullingMode();
		OR_Globals::Context()->NormalDrawMode();
	}
	else
	{
		pMesh->Draw();		
	}
	glPopMatrix();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule::Posit
 *
 *  \author Gabriel Peyré 2001-07-29
 *
 *	Push the modelview matrix and positionnate the particule.
 *	The decomposition Posit/Draw is used mainly for handling bilboading shaders.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_DisplayableParticule::Posit()
{
	glPushMatrix(); 
	glTranslatef(Pos_[X], Pos_[Y], Pos_[Z]);
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule::IsDead
 *
 *  \return true if the particule is dead (ie. energy<0).
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_DisplayableParticule::IsDead()
{
	return rEnergy_<0;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule::GetEnergy
 *
 *  \return the energy of the particule
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_DisplayableParticule::GetEnergy()
{
	return rEnergy_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule::SetEnergy
 *
 *  \param  rEnergy The new energy of the particule.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_DisplayableParticule::SetEnergy(const OR_Float rEnergy)
{
	rEnergy_ = rEnergy;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule::GetEnergyLost
 *
 *  \return The energy lost by the particule at each update.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_DisplayableParticule::GetEnergyLost()
{
	return rEnergyLost_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DisplayableParticule::SetEnergyLost
 *
 *  \param  rEnergyLost The new energy lost by the particule at each update.
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_DisplayableParticule::SetEnergyLost(const OR_Float rEnergyLost)
{
	rEnergyLost_ = rEnergyLost;
}



} // End namespace OR

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

