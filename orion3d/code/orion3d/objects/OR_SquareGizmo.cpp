				/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SquareGizmo.cpp
 *  \brief Definition of class \c OR_SquareGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SquareGizmo.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_SquareGizmo.h"

#ifndef OR_USE_INLINE
	    #include "OR_SquareGizmo.inl"
#endif

using namespace OR;


OR_SquareGizmo::OR_SquareGizmo(OR_Vector3D vX, OR_Vector3D vY,
			 OR_Vector3D vZ, OR_Vector3D dim)
:OR_Gizmo(vX, vY, vZ, dim)
{

}

/* basic clipping functions ****************************************/
OR_Bool OR_SquareGizmo::IsInside(OR_Vector3D pos)
{
	return false;
}

OR_Bool OR_SquareGizmo::FrustrumClip()
{
	return false;
}

void OR_SquareGizmo::Draw()
{
#ifdef OR_DRAW_GIZMOS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_GIZMO) ) 
	{
	glPushMatrix();

		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );

		OR_DrawLocalAxis();
		
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(1, 1, 0);

		glBegin(GL_LINE_LOOP);
		glVertex3f(-Dim[X], -Dim[Y], 0);
		glVertex3f(-Dim[X],  Dim[Y], 0);
		glVertex3f( Dim[X],  Dim[Y], 0);
		glVertex3f( Dim[X], -Dim[Y], 0);
		glEnd();

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif
}

/*------------------------------------------------------------------------------*/
// Name : OR_SquareGizmo::DeflectParticule
/** 
 *  \param  particule the particule to deflect.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	Check if a collision has occurs, and then apply an impulse to deviate the particule.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SquareGizmo::DeflectParticule(OR_Particule& particule)
{
	if( pRigidBody_==NULL )
		return;

	OR_Matrix4x4 InvMat    = ~(pRigidBody_->GetWorldToBody());
	OR_Matrix4x4 InvMatOld = ~(pRigidBody_->GetWorldToBodyOld());

	/** compute particule position in local coords */
	OR_Vector3D Pos    = InvMat*particule.GetPosition();
	OR_Vector3D PosOld = InvMatOld*particule.GetOldPosition();

	OR_Vector3D Intersection;
	OR_Vector3D Normal;

	if( OML::OML_RayCaster::RayCastSquare_Segment(Dim[0], Dim[1], PosOld, Pos, Normal, Intersection) )
	{
		/* a collision has occured */
		OR_Vector3D ImpactPos = pRigidBody_->GetWorldToBody()*Intersection;
		
		particule.SetPosition( pRigidBody_->GetWorldToBody()*Intersection );
		/* compute the impulse created by the choc, in local coords */
		this->ResolveImpulse(particule, AbsoluteMatrix.GetZ(), ImpactPos);
	}
}


/*------------------------------------------------------------------------------*/
// Name : OR_SquareGizmo::DeflectObject
/** 
 *  \param  object the particule to deflect.
 *  \author Gabriel Peyré 2001-08-04
 *
 *  Check if a collision has occurs, and then apply an impulse to deviate the object.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SquareGizmo::DeflectObject(OR_RigidBody& object)
{
	/** \todo fill this method */
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SquareGizmo::InitParticule
 *
 *  \param  particule the particule to initialize
 *  \param  AbsoluteSpeed The speed given in the basis of the object.
 *  \author Gabriel Peyré 2001-07-30
 *
 *	Initialize the position and the speed of the particule.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SquareGizmo::InitParticule(OR_Particule& particule, OR_Vector3D& AbsoluteSpeed)
{
	OR_Vector3D Offset(Dim[0]*OR_RAND_RANGE(-1,1), Dim[1]*OR_RAND_RANGE(-1,1), 0);

	particule.ReSetPosition( GetAbsolutePosition()+Offset );
	OR_Vector3D speed = AbsoluteMatrix.GetRotation()*AbsoluteSpeed;
	particule.SetSpeed( speed );
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

