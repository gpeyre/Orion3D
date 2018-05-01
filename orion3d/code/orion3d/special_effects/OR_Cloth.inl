//*****************************************************************************
/// \author Gabriel Peyré
//*****************************************************************************


#include "OR_Cloth.h"

namespace OR {

//-----------------------------------------------------------------------------
// Name: OR_Cloth::SetNbrParticules
/**
*   @param  nNbrParticulesX the number of particules on X axis
*   @param  nNbrParticulesY the number of particules on Y axis
*
*	Set the number of particules and then rebuild the cloth.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Cloth::SetNbrParticules(OR_I32 nNbrParticulesX, OR_I32 nNbrParticulesY)
{
	aNbrParticules_[0]=nNbrParticulesX;
	aNbrParticules_[1]=nNbrParticulesY;
	bNeedsRebuild_=true;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::GetNbrParticules
/**
*   @return the number of particules on each axis
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
OR_I32* OR_Cloth::GetNbrParticules()
{
	return aNbrParticules_;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::SetGizmo
/**
*   @param  pGizmo The gizmo that gives the position and dimension of the cloth.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Cloth::SetGizmo(OR_CubeGizmo& gizmo)
{
	pGizmo_ = &gizmo;
	PositionateParticules();
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::GetGizmo
/**
*   @return The gizmo that gives the position and dimension of the cloth.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
OR_CubeGizmo* OR_Cloth::GetGizmo()
{
	return pGizmo_;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::GetParticule
/**
*   @param  nX position of the particule on Y axis
*   @param  nY position of the particule on Y axis
*
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
OR_Particule* OR_Cloth::GetParticule(OR_I32 nX, OR_I32 nY)
{
	OR_ASSERT( CHECK_INSIDE_CLOTH(nX, nY) );
	return &pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX, nY)];
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::GetSideStiffness
/**
*   @return The stiffness of the side springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_Cloth::GetSideStiffness()
{
	return rSideStiffness_;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::GetDiagonalStiffness
/**
*   @return The stiffness of the diagonal springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_Cloth::GetDiagonalStiffness()
{
	return rDiagonalStiffness_;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::GetStructuralStiffness
/**
*   @return The stiffness of the structural springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_Cloth::GetStructuralStiffness()
{
	return rStructuralStiffness_;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::SetSideStiffness
/**
*   @param  rSideStiffness The stiffness of the side springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Cloth::SetSideStiffness(OR_Float rSideStiffness)
{
	rSideStiffness_=rSideStiffness;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::SetDiagonalStiffness
/**
*   @param  rDiagonalStiffness The stiffness of the diagonal springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Cloth::SetDiagonalStiffness(OR_Float rDiagonalStiffness)
{
	rDiagonalStiffness_=rDiagonalStiffness;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::SetStructuralStiffness
/**
*   @param  rStructuralStiffness The stiffness of the structural springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Cloth::SetStructuralStiffness(OR_Float rStructuralStiffness)
{
	rStructuralStiffness_=rStructuralStiffness;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Cloth::GetMaxRelativeElongation
 *
 *  \return The maximum relative elongation distance.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	The maximum elongation is used to store maximum distance constraints between 
 *	particules.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_Cloth::GetMaxRelativeElongation()
{
	return rMaxRelativeElongation_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Cloth::SetMaxRelativeElongation
 *
 *  \param  rMaxRelativeElongation The maximum relative elongation distance.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	The maximum elongation is used to store maximum distance constraints between 
 *	particules.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Cloth::SetMaxRelativeElongation(OR_Float rMaxRelativeElongation)
{
	rMaxRelativeElongation_ = rMaxRelativeElongation;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Cloth::UseRelaxableConstraints
 *
 *  \param  bUse Do we use maximum distance constraints for simulation.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Cloth::UseRelaxableConstraints(OR_Bool bUse)
{
	bUseRelaxableConstraints_ = bUse;
}



//-----------------------------------------------------------------------------
// Name: OR_Cloth::GetSideDampling
/**
*   @return The stiffness of the side springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_Cloth::GetSideDampling()
{
	return rSideDampling_;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::GetDiagonalDampling
/**
*   @return The stiffness of the diagonal springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_Cloth::GetDiagonalDampling()
{
	return rDiagonalDampling_;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::GetStructuralDampling
/**
*   @return The stiffness of the structural springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_Cloth::GetStructuralDampling()
{
	return rStructuralDampling_;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::SetSideDampling
/**
*   @param  rSideDampling The stiffness of the side springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Cloth::SetSideDampling(OR_Float rSideDampling)
{
	rSideDampling_=rSideDampling;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::SetDiagonalDampling
/**
*   @param  rDiagonalDampling The stiffness of the diagonal springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Cloth::SetDiagonalDampling(OR_Float rDiagonalDampling)
{
	rDiagonalDampling_=rDiagonalDampling;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::SetStructuralDampling
/**
*   @param  rStructuralDampling The stiffness of the structural springs.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Cloth::SetStructuralDampling(OR_Float rStructuralDampling)
{
	rStructuralDampling_=rStructuralDampling;
}



/*------------------------------------------------------------------------------*/
// Name : OR_Cloth::AutoSetDampling
/** 
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Gabriel Peyré 2001-08-04
 *
 *  Compute the ideal dampling for all spring using the equation :
 *		Dampling = sqrt(4*Stifness*Mass);
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Cloth::AutoSetDampling()
{
	if( rParticuleInvMass_>0 )
	{
		rSideDampling_       = sqrt(4*rSideStiffness_/rParticuleInvMass_);
		rDiagonalDampling_   = sqrt(4*rDiagonalStiffness_/rParticuleInvMass_);
		rStructuralDampling_ = sqrt(4*rStructuralStiffness_/rParticuleInvMass_);
	}
}



/*------------------------------------------------------------------------------*/
// Name : OR_Cloth::GetParticuleInvMass
/** 
 *  \return Inverse of the mass of a particule.
 *  \author Gabriel Peyré 2001-08-04
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_Cloth::GetParticuleInvMass()
{
	return rParticuleInvMass_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_Cloth::SetParticuleInvMass
/** 
 *  \param  rInvMass inverse of the mass of a particule.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Cloth::SetParticuleInvMass(OR_Float rInvMass)
{
	OR_ParticuleManager::SetParticuleInvMass(rInvMass);
	rParticuleInvMass_ = rInvMass;
}

} // namespace OR