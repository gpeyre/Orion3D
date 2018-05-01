/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ParticuleSystem.inl
 *  \brief Inlined methods of OR_ParticuleSystem
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#include "OR_ParticuleSystem.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem constructor
 *
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ParticuleSystem::OR_ParticuleSystem()
:	OR_SpecialEffect(), 
	OR_ParticuleManager()
{	
	/* initialize source values */
	rEmissionVariance_         = 0.5f;
	rSpeedVariance_            = 0.1f;
	rEnergyStart_              = 1.0f;
	rEnergyLost_               = 0.01f;
	rEnergyLostVariance_	   = 0.1f;
	rEnergyStartVariance_      = 0.1f;
	rEmissionVariance_         = 0.1f;
	rParticuleInvMass_         = 10.0f;
	rParticuleInvMassVariance_ = 0.1f;
	rInitialSpeed_             = 1.0f;
	
	/* default values */
	rDebit_                    = 0.1f;
	rRestToEmit_               = 0;
	nNbrParticules_            = 0;
	nNbrMaxParticules_         = 5000;
	aStartColor_[0]            = 0.3f;
	aStartColor_[1]            = 0.3f;
	aStartColor_[2]            = 0.7f;
	aStartColor_[3]            = 1;
	aEndColor_[0]              = 1;
	aEndColor_[1]              = 0.5f;
	aEndColor_[2]              = 0.0f;
	aEndColor_[3]              = 0.0f;
	/* set default values */
	rMaxRadius_                = 100;
	/* set a default square shape */
	pShape_ = NULL;
	rParticuleBounce_          = 1;
	
	BlendingMode_ = OR_Blending_SrcA_1;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem destructor
 *
 *  \author Gabriel Peyré 2001-07-29
 *
 *	Delete each particule.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ParticuleSystem::~OR_ParticuleSystem()
{
	ClearSystem();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::InitParticule
 *
 *  \param  particule The particule to initialize.
 *  \author Gabriel Peyré 2001-07-29
 *
 *	Set the speed, the energy, etc.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::InitParticule(OR_Particule& particule)
{
	OR_DisplayableParticule* pParticule = (OR_DisplayableParticule*) &particule;

	/* determine the mass of the particule */
	pParticule->SetInvMass(
		rParticuleInvMass_*(1 + rParticuleInvMassVariance_*OR_RAND) );
	/* set the energy and the lost of energy per update */
	pParticule->SetEnergy( 
		rEnergyStart_*(1 + rEnergyStartVariance_*OR_RAND) );
	pParticule->SetEnergyLost( 
		rEnergyLost_*(1 + rEnergyLostVariance_*OR_RAND) );
	/* set the bounce */
	pParticule->SetBounce(rParticuleBounce_);
	/* determine the speed given the variance */
	OR_Float angle_rot=2*OR_PI*OR_RAND;
	OR_Float cosrot=cos(angle_rot);
	OR_Float sinrot=sin(angle_rot);
	OR_Float angle_dif=rEmissionVariance_*OR_RAND;
	OR_Float cosdif=cos(angle_dif);
	OR_Float sindif=sin(angle_dif);
	OR_Float speed_value=rInitialSpeed_*(1 + rSpeedVariance_*OR_RAND );
	/* initialize direction of the speed and the position */
	pEmmitter_->InitParticule(particule, OR_Vector3D(cosrot*sindif, sinrot*sindif, cosdif)*speed_value);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetColor
 *
 *  \param  energy Set the base color to draw a particule given its energy.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetColor(OR_Float rEnergy)
{
	OR_Float aColor[4];
	OR_Float rEnergyMax=rEnergyStart_*(1+rEnergyStartVariance_);
	OR_Float rFactor=rEnergy/rEnergyMax;
	aColor[0]=aStartColor_[0]*rFactor+aEndColor_[0]*(1-rFactor);
	aColor[1]=aStartColor_[1]*rFactor+aEndColor_[1]*(1-rFactor);
	aColor[2]=aStartColor_[2]*rFactor+aEndColor_[2]*(1-rFactor);
	aColor[3]=aStartColor_[3]*rFactor+aEndColor_[3]*(1-rFactor);
	OR_Globals::Context()->SetColor(aColor);

	/* set the color */
	if( pShape_!=NULL ) 
	{
		OR_Shader *pShader=NULL;
		pShader=pShape_->GetShader();
		if( pShader!=NULL )
		{
			pShader->SetAmbientDiffuse( aColor );
		}
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::ClearGarbageCollector
 *
 *  \author Gabriel Peyré 2001-07-29
 *
 *	Delete the particules in the garbage collector.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::ClearGarbageCollector()
{
	for( IT_ParticuleList it=GarbageCollector_.begin(); it!=GarbageCollector_.end(); ++it )
		OR_DELETE(*it);
	GarbageCollector_.clear();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::ClearSystem
 *
 *  \author Gabriel Peyré 2001-07-29
 *
 *	Delete all particule in the system (both alive and in the garbage collector).
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::ClearSystem()
{
	ClearGarbageCollector();
	for( IT_ParticuleList it=begin(); it!=end(); ++it )
		OR_DELETE(*it);
	List_.clear();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetDebit
 *
 *  \param  rDebit The number of particules emmitted each second
 *  \author Gabriel Peyré 2001-07-29
 *
 *	\todo for the moment, the debit does not handle absolute time (it's the number of 
 *	particules emmitted each frame).
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetDebit(OR_Float rDebit)
{
	rDebit_ = rDebit;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetInitialSpeed
 *
 *  \param  rVal The new length of the speed of particules at emission time.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetInitialSpeed(OR_Float rVal)
{
	rInitialSpeed_ = rVal;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetEmissionVariance
 *
 *  \param  rVariance the angular variance of the speed of the particule at emission.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetEmissionVariance(OR_Float rVariance)
{
	rEmissionVariance_ = rVariance;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetSpeedVariance
 *
 *  \param  rVariance the vairance of the length of the speed.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetSpeedVariance(OR_Float rVariance)
{
	rSpeedVariance_ = rVariance;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetEnergyStart
 *
 *  \param  rEnergystart The energy of the particule at emmission.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetEnergyStart(OR_Float rEnergystart)
{
	rEnergyStart_ = rEnergystart;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetEnergyStartVariance
 *
 *  \param  rEnergystartvariance Variance of the energy of the particule at emmission.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetEnergyStartVariance(OR_Float rEnergystartvariance)
{
	rEnergyStartVariance_ = rEnergystartvariance;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetEnergyLost
 *
 *  \param  rEnergylost The energy lost by a particule per second.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetEnergyLost(OR_Float rEnergylost)
{
	rEnergyLost_ = rEnergylost;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetEnergyLostVariance
 *
 *  \param  rEnergylostvariance Variance of the energy lost.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetEnergyLostVariance(OR_Float rEnergylostvariance)
{
	rEnergyLostVariance_ = rEnergylostvariance;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetParticuleInvMass
 *
 *  \param  rVal Inverse of the mass of a particule.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetParticuleInvMass(OR_Float rVal)
{
	rParticuleInvMass_ = rVal;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetParticuleInvMassVariance
 *
 *  \param  val variance of the inverse of the mass of a particule.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetParticuleInvMassVariance(OR_Float rVal)
{
	rParticuleInvMassVariance_ = rVal;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetEmmitter
 *
 *  \return The emitter used to initialize the particules.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Emitter_ABC* OR_ParticuleSystem::GetEmmitter()
{
	return pEmmitter_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetEmmitter
 *
 *  \param  Emitter The emitter used to initialize the particules.
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetEmmitter(OR_Emitter_ABC& Emitter)
{
	pEmmitter_ = &Emitter;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetDebit
 *
 *  \return The number of particule ammited each second.
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetDebit()
{
	return rDebit_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetInitialSpeed
 *
 *  \return length of the speed of particule at emission.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetInitialSpeed()
{
	return rInitialSpeed_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetEmissionVariance
 *
 *  \return angular variance of the speed.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetEmissionVariance()
{
	return rEmissionVariance_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetSpeedVariance
 *
 *  \return variance of the length of the speed.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetSpeedVariance()
{
	return rSpeedVariance_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetEnergyStart
 *
 *  \return energy at emission of the particules.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetEnergyStart()
{
	return rEnergyStart_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetEnergyStartVariance
 *
 *  \return variance of the enrgy at emmisison.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetEnergyStartVariance()
{
	return rEnergyStartVariance_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetEnergyLost
 *
 *  \return The energy lost by a particule each second.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetEnergyLost()
{
	return rEnergyLost_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetEnergyLostVariance
 *
 *  \return variance of the energy lost.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetEnergyLostVariance()
{
	return rEnergyLostVariance_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetParticuleInvMass
 *
 *  \param  rVal inverse of the mass of a particule.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetParticuleInvMass()
{
	return rParticuleInvMass_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetParticuleInvMassVariance
 *
 *  \return variance of the inverse of the mass of a particule.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetParticuleInvMassVariance()
{
	return rParticuleInvMassVariance_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::ModifyDebit
 *
 *  \param  val value added to the debit.
 *  \author Gabriel Peyré 2001-07-29
 *
 *	Can  be used to create, for example, an explosion.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::ModifyDebit(OR_Float rVal)
{
	rDebit_ += rVal;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetMaxRadius
 *
 *  \param  rMaxradius The new maximum radius that can be reached by a particule.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetMaxRadius(OR_Float rMaxradius)
{
	rMaxRadius_ = rMaxradius;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetNbMaxParticules
 *
 *  \param  nVal The new maximum number of particules.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetNbMaxParticules(OR_I32 nVal)
{
	nNbrMaxParticules_ = nVal;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetShape
 *
 *  \param  shape the shape used to draw a particule.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetShape(OR_Mesh& shape)
{
	pShape_ = &shape;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetStartColor
 *
 *  \param  r red component of the color of the paricule at emission
 *  \param  g green component of the color of the paricule at emission
 *  \param  b blue component of the color of the paricule at emission
 *  \param  a alpha component of the color of the paricule at emission
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetStartColor(OR_Float r, OR_Float g, OR_Float b, OR_Float a)
{
	aStartColor_[0] = r;
	aStartColor_[1] = g;
	aStartColor_[2] = b;
	aStartColor_[3] = a;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetEndColor
 *
 *  \param  r red component of the color of the paricule at destruction
 *  \param  g green component of the color of the paricule at destruction
 *  \param  b blue component of the color of the paricule at destruction
 *  \param  a alpha component of the color of the paricule at destruction
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetEndColor(OR_Float r, OR_Float g, OR_Float b, OR_Float a)
{
	aEndColor_[0] = r;
	aEndColor_[1] = g;
	aEndColor_[2] = b;
	aEndColor_[3] = a;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetParticuleBounce
 *
 *  \param  rVal the new bounce of a particule.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetParticuleBounce(OR_Float rVal)
{
	rParticuleBounce_ = rVal;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetShape
 *
 *  \return the shape used to draw the particules.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Mesh* OR_ParticuleSystem::GetShape()
{
	return pShape_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetStartColor
 *
 *  \return the color of the particule at creation.
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float* OR_ParticuleSystem::GetStartColor()
{
	return aStartColor_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetEndColor
 *
 *  \return The color of the particules at destruction.
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float* OR_ParticuleSystem::GetEndColor()
{
	return aEndColor_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetParticuleBounce
 *
 *  \return the bounce of a particule.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_ParticuleSystem::GetParticuleBounce()
{
	return rParticuleBounce_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::EnableBilboarding
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Gabriel Peyré 2001-07-29
 *
 * PUT YOUR COMMENTS HERE
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RETURN_CODE OR_ParticuleSystem::EnableBilboarding()
{
	if( pShape_==NULL ) 
		return OR_ERROR;
	if( pShape_->GetShader()==NULL ) 
		return OR_ERROR;
	if( pShape_->GetShader()->GetType()==OR_SHADER_Billboard ) 
		return OR_OK;

	OR_Shader *pShader = new OR_BillboardShader( pShape_->GetShader() );
	pShape_->SetShader(pShader);
	OR_Globals::ShaderManager()->AddElement(pShader);
	return OR_OK;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::SetBlendingMode
 *
 *  \param  mode the new blending mode used to display the particules.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::SetBlendingMode(OR_Blending_Mode mode)
{
	BlendingMode_ = mode;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::GetBlendingMode
 *
 *  \return the blending mode used to display the particules.
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Blending_Mode OR_ParticuleSystem::GetBlendingMode()
{
	return BlendingMode_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::IsSourceActive
 *
 *  \return Is the source active (ie. is debit > 0 ?)
 *  \author Gabriel Peyré 2001-07-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_ParticuleSystem::IsSourceActive()
{
	return (rDebit_>0);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystem::IsSystemActive
 *
 *  \return Is the system acticve.
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_ParticuleSystem::IsSystemActive()
{
	return ( (rDebit_>0) || nNbrParticules_>0 );
}



/*------------------------------------------------------------------------------*/
// Name : OR_ParticuleSystem::ModifiyDebit
/** 
 *  \param  mod the value to add to the debit.
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleSystem::ModifiyDebit(OR_Float mod)
{
	rDebit_ += mod;
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

