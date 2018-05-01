/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Cloth.cpp
 *  \brief Implementation of class OR_Cloth
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Cloth.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Cloth.h"

#ifndef OR_USE_INLINE
	#include "OR_Cloth.inl"
#endif

using namespace OR;

//-----------------------------------------------------------------------------
// Name: OR_Cloth constructor
/**
*   @param  nNbrParticulesX the number of particules on X axis
*   @param  nNbrParticulesY the number of particules on Y axis
*   @param  pGizmo The gizmo that gives the position and dimension of the cloth.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_Cloth::OR_Cloth(OR_I32 nNbrParticulesX, OR_I32 nNbrParticulesY, OR_CubeGizmo* pGizmo)
:OR_SpecialEffect(),
 OR_ParticuleManager(&ConstraintManager)
{
	pGizmo_ = pGizmo;
	aNbrParticules_[0]=nNbrParticulesX;
	aNbrParticules_[1]=nNbrParticulesY;
	bNeedsRebuild_=true;
	rSideStiffness_         = 0;
	rDiagonalStiffness_     = 0;
	rStructuralStiffness_   = 0;
	rSideDampling_          = 0;
	rDiagonalDampling_      = 0;
	rStructuralDampling_    = 0;
	rMaxRelativeElongation_ = 1.5f;

	rParticuleInvMass_      = 10.0f;

	pParticuleArray_        = NULL;
	pSideSpringArray_       = NULL;
	pDiagonalSpringArray_   = NULL;
	pStructuralSpringArray_ = NULL;
	pConstraintArray_       = NULL;

	bUseRelaxableConstraints_ = true;
}

//-----------------------------------------------------------------------------
// Name: OR_Cloth destructor
/**
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_Cloth::~OR_Cloth()
{
	Reset();
}

//-----------------------------------------------------------------------------
// Name: OR_Cloth::Build
/**
*
*	Create all arrays (particules & constraints).
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_Cloth::Build()
{
	/* delete all arrays */
	Reset();
	/* create all arrays */
	pParticuleArray_        = new OR_Particule[aNbrParticules_[0]*aNbrParticules_[1]];
	pSideSpringArray_       = new OR_DampedSpringConstraint[aNbrParticules_[0]*aNbrParticules_[1]*2];
	pDiagonalSpringArray_   = new OR_DampedSpringConstraint[aNbrParticules_[0]*aNbrParticules_[1]*2];
	pStructuralSpringArray_ = new OR_DampedSpringConstraint[aNbrParticules_[0]*aNbrParticules_[1]*2];
	pConstraintArray_       = new OR_MaximumDistanceConstraint[aNbrParticules_[0]*aNbrParticules_[1]*2];

	/* reset constraints and particules */
	PositionateParticules();
	SetUpConstraints();
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::Reset
/**
*	delete all arrays
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_Cloth::Reset()
{
	/* clear the Lists of constraints and particules */
	ConstraintManager.clear();
	List_.clear();
	/* delete the arrays */
	OR_DELETEARRAY(pParticuleArray_);
	OR_DELETEARRAY(pSideSpringArray_);
	OR_DELETEARRAY(pDiagonalSpringArray_);
	OR_DELETEARRAY(pStructuralSpringArray_);
	OR_DELETEARRAY(pConstraintArray_);
	bNeedsRebuild_=true;
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::PositionateParticules
/**
*	Set the position of each particule, using the gizmo proprieties.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_Cloth::PositionateParticules()
{
	if( pGizmo_!=NULL )
	{
		OR_Float rRestLength = pGizmo_->GetDim()[X]/aNbrParticules_[0];
		OR_Vector3D& pos = pGizmo_->GetAbsolutePosition();
		OR_I32 nMidNumberX = (OR_I32) aNbrParticules_[0]/2;
		OR_I32 nMidNumberY = (OR_I32) aNbrParticules_[1]/2;
		OR_Matrix4x4& TranfoMatrix = pGizmo_->GetAbsoluteMatrix();

		for(OR_I32 nX=0; nX<aNbrParticules_[0]; ++nX)
		for(OR_I32 nY=0; nY<aNbrParticules_[1]; ++nY)
		{
			OR_Particule* pParticule = &pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX, nY)];			/*
			OR_Vector3D particule_pos = pos + pMatrix->GetX()*(nX-nMidNumberX)*rRestLength
											+ pMatrix->GetY()*(nY-nMidNumberY)*rRestLength; */
			OR_Vector3D particule_pos = OR_Vector3D( ((OR_Float) nX-nMidNumberX)*rRestLength, 
												   ((OR_Float)nY-nMidNumberY)*rRestLength, 0 );
			pParticule->SetPosition(particule_pos);
			pParticule->SetOldPosition(particule_pos);
			pParticule->SetInvMass(rParticuleInvMass_);
			List_.push_back(pParticule);
		}
	}
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::SetUpConstraints
/**
*	Set the stiffness & restlength of each constraint.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_Cloth::SetUpConstraints()
{
	if(pGizmo_!=NULL)
	{
		OR_Float rRestLength = pGizmo_->GetDim()[X]/aNbrParticules_[0];

		for(OR_I32 nX=0; nX<aNbrParticules_[0]; ++nX)
		for(OR_I32 nY=0; nY<aNbrParticules_[1]; ++nY)
		{
			OR_I32 offset=ACCESS_PARTICULE_ARRAY(nX, nY)*2;
			/* set the particule involved in the constraint */
			OR_Particule* pPart1 = &pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX, nY)];
			OR_Particule* pPart2 = NULL;
			OR_Particule* pPart3 = NULL;
			OR_Particule* pPart4 = NULL;
			OR_Particule* pPart5 = NULL;
			OR_Particule* pPart6 = NULL;
			if(nX < aNbrParticules_[0]-1)
				pPart2 = &pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX+1, nY)];
			if(nY < aNbrParticules_[1]-1)
				pPart3 = &pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX, nY+1)];
			if(nX < aNbrParticules_[0]-2)
				pPart4 = &pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX+2, nY)];
			if( (nX < aNbrParticules_[0]-1) && (nY < aNbrParticules_[1]-1) )
				pPart5 = &pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX+1, nY+1)];
			if(nY < aNbrParticules_[1]-2)
				pPart6 = &pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX, nY+2)];

			if( pPart2!=NULL )
			{
				pSideSpringArray_[offset+0].SetTarget1(pPart1);
				pSideSpringArray_[offset+0].SetTarget2(pPart2);
				ConstraintManager.AddLast(pSideSpringArray_[offset+0]);
				if( bUseRelaxableConstraints_ )
				{
					/* relaxable constraint */
					pConstraintArray_[offset+0].SetTarget1(pPart1);
					pConstraintArray_[offset+0].SetTarget2(pPart2);
					OR_Float rDist = ~(pPart1->GetPosition() - pPart2->GetPosition())*rMaxRelativeElongation_;
					pConstraintArray_[offset+0].SetDistance(rDist);
					ConstraintManager.AddLast(pConstraintArray_[offset+0]);
				}
			}
			if( pPart3!=NULL )
			{
				pSideSpringArray_[offset+1].SetTarget1(pPart1);
				pSideSpringArray_[offset+1].SetTarget2(pPart3);
				ConstraintManager.AddLast(pSideSpringArray_[offset+1]);
				if( bUseRelaxableConstraints_ )
				{
					pConstraintArray_[offset+1].SetTarget1(pPart1);
					pConstraintArray_[offset+1].SetTarget2(pPart3);
					OR_Float rDist = ~(pPart1->GetPosition() - pPart3->GetPosition())*rMaxRelativeElongation_;
					pConstraintArray_[offset+1].SetDistance(rDist);
					ConstraintManager.AddLast(pConstraintArray_[offset+1]);
				}
			}

			if( pPart5!=NULL )
			{
				pDiagonalSpringArray_[offset+0].SetTarget1(pPart1);
				pDiagonalSpringArray_[offset+0].SetTarget2(pPart5);
				ConstraintManager.AddLast(pDiagonalSpringArray_[offset+0]);
			}
			if( pPart3!=NULL && pPart2!=NULL)
			{
				pDiagonalSpringArray_[offset+1].SetTarget1(pPart2);
				pDiagonalSpringArray_[offset+1].SetTarget2(pPart3);
				ConstraintManager.AddLast(pDiagonalSpringArray_[offset+1]);
			}

			if( pPart4!=NULL )
			{
				pStructuralSpringArray_[offset+0].SetTarget1(pPart1);
				pStructuralSpringArray_[offset+0].SetTarget2(pPart4);
				ConstraintManager.AddLast(pStructuralSpringArray_[offset+0]);
			}
			if( pPart6!=NULL )
			{
				pStructuralSpringArray_[offset+1].SetTarget1(pPart1);
				pStructuralSpringArray_[offset+1].SetTarget2(pPart6);
				ConstraintManager.AddLast(pStructuralSpringArray_[offset+1]);
			}

			/* set the stiffness */
			for(OR_I32 i=0; i<2; ++i)
			{
				pSideSpringArray_[offset+i].SetStiffness(rSideStiffness_);
				pSideSpringArray_[offset+i].SetDampling(rSideDampling_);
				pSideSpringArray_[offset+i].SetRestLength(rRestLength);

				pDiagonalSpringArray_[offset+i].SetStiffness(rDiagonalStiffness_);
				pDiagonalSpringArray_[offset+i].SetDampling(rDiagonalDampling_);
				pDiagonalSpringArray_[offset+i].SetRestLength(rRestLength*OR_SQRT2);

				pStructuralSpringArray_[offset+i].SetStiffness(rStructuralStiffness_);
				pStructuralSpringArray_[offset+i].SetDampling(rStructuralDampling_);
				pStructuralSpringArray_[offset+i].SetRestLength(rRestLength*2);
			}
		}
	}
}



//-----------------------------------------------------------------------------
// Name: OR_Cloth::Draw
/**
*	Draw the cloth
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_Cloth::Draw()
{
	if( this->IsActive() )
	{
		glPushMatrix();
		OR_Globals::Context()->SetLineSize(2);
		OR_Globals::Context()->SetPointSize(6);
		OR_Globals::Context()->SimpleDrawMode();
		for(OR_I32 nX=0; nX<aNbrParticules_[0]; ++nX)
		for(OR_I32 nY=0; nY<aNbrParticules_[1]; ++nY)
		{
			const OR_Float* pPos = pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX, nY)].GetPosition().GetCoord();
			OR_Globals::Context()->SetColor(1,1,0);
			glBegin(GL_POINTS);
				glVertex3fv(pPos);
			glEnd();
			
			OR_Globals::Context()->SetColor(0,1,0);
			if(nX!=aNbrParticules_[0]-1)
			{
				const OR_Float* pPos2 = pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX+1, nY)].GetPosition().GetCoord();
				glBegin(GL_LINES);
					glVertex3fv(pPos);
					glVertex3fv(pPos2);
				glEnd();
			}
			if(nY!=aNbrParticules_[1]-1)
			{
				const OR_Float* pPos2 = pParticuleArray_[ACCESS_PARTICULE_ARRAY(nX, nY+1)].GetPosition().GetCoord();
				glBegin(GL_LINES);
					glVertex3fv(pPos);
					glVertex3fv(pPos2);
				glEnd();
			}
		}
		glPopMatrix();
	}
}


//-----------------------------------------------------------------------------
// Name: OR_Cloth::Update
/**
*	Nothing to do : this is taken care by the physic engine (ie. class \c OR_PhysicEntityManager).
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_Cloth::Update()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : OR_Cloth::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Cloth::BuildFromFile( OR_File& file )
{
}



/*------------------------------------------------------------------------------*/
// Name : OR_Cloth::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Cloth::BuildToFile( OR_File& file )
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


