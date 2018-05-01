/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ParticuleSystem.cpp
 *  \brief Implementation of OR_ParticuleSystem
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ParticuleSystem.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ParticuleSystem.h"

#ifndef OR_USE_INLINE
	    #include "OR_ParticuleSystem.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::Update
 *
 *  \author Gabriel Peyré 2001-07-18
 *
 *	Create new particule, put dead one to the garbage collector.
 *
 *	This does \b not update physics computations, since this is done by the 
 *	physic engine, ie. by class \c OR_PhysicEntityManager.	
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleSystem::Update()
{	
	if( !this->IsActive() )
		return;

	/* the number of particules to emmit */
	OR_I32 NbParticulesToEmit;
	/* compute the number of particules to emit */
	NbParticulesToEmit=(OR_I32)( rDebit_+rRestToEmit_ );

	/* check for dead particules*/
	for( IT_ParticuleList it=begin(); it!=end(); ++it )
	{
		OR_DisplayableParticule* pParticule = (OR_DisplayableParticule*) (*it);

		/* update energy of the particule */
		pParticule->Update();

		if( pParticule->IsDead() )
		{
			GarbageCollector_.push_back(*it);
			nNbrParticules_--;
			/* the particule is dead, so push it in the garbage collector */
			it = List_.erase(it);
			it--;
		}
	}

	/* create new particules */
	for( OR_I32 i=0; i<NbParticulesToEmit; i++ )
	{
		if ( nNbrParticules_<nNbrMaxParticules_)
		{
			nNbrParticules_++;
			OR_Particule* pParticule;
			/* if the stack is not empty, use it, else, create a new particule */
			if( !GarbageCollector_.empty() )
			{
				pParticule=GarbageCollector_.front();
				GarbageCollector_.pop_front();
				pParticule->ReSet();
			}
			else
				pParticule=new OR_DisplayableParticule();
			AddFirst(*pParticule);
			OR_ASSERT(pEmmitter_!=NULL);

			InitParticule(*pParticule);
		}
	
	}
	
	rRestToEmit_= rDebit_+ rRestToEmit_ - NbParticulesToEmit;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::Draw
 *
 *  \return Draw each particule to screen
 *  \author Gabriel Peyré 2001-07-20
 *
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleSystem::Draw()
{
	if( !this->IsActive() )
		return;

glPushMatrix();

	/* set the blending on */
	OR_Globals::Context()->SetBlendingMode(BlendingMode_);
	/* don't write in the depth buffer */
	glDepthMask(GL_FALSE);

	/* disable lighting */
	OR_Globals::Context()->DisableLighting();

	/* put the correct culling, save the old one (usefull for planar reflexion) */
	OR_Culling_Mode culling=OR_Globals::Context()->SetDefaultCullingMode();

	/* draw existing particules */
	for( IT_ParticuleList it=begin(); it!=end(); ++it )
	{
		OR_DisplayableParticule* pParticule = (OR_DisplayableParticule*) (*it);
		/* set the color and the alpha coresponding to the energy */
		
		this->SetColor(pParticule->GetEnergy());
		
		/* translate the particule */
		pParticule->Posit();

		pParticule->Draw(pShape_);
	}

	/* enable lighting */
	OR_Globals::Context()->SetDefaultLightingMode();

	/* re-set the blending off */
	OR_Globals::Context()->SetDefaultBlendingMode();

	glDepthMask(GL_TRUE);

	/* re-set the original culling */
	OR_Globals::Context()->SetCullingMode(culling);

glPopMatrix();
}

/*------------------------------------------------------------------------------*/
// Name : OR_ParticuleSystem::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleSystem::BuildFromFile( OR_File& file )
{
	/* \todo fill this */
}



/*------------------------------------------------------------------------------*/
// Name : OR_ParticuleSystem::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleSystem::BuildToFile( OR_File& file )
{
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

