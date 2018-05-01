/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_CylinderGizmo.cpp
 *  \brief Definition of class \c OR_CylinderGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_CylinderGizmo.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_CylinderGizmo.h"
#include "../special_effects/OR_MetaGrid.h"

#ifndef OR_USE_INLINE
	#include "OR_CylinderGizmo.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CubeGizmo::AddMetaValue
 *
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
void OR_CylinderGizmo::AddMetaValue(OR_MetaGrid& grid)
{
	OR_Vector3D GizmoPos = this->GetAbsolutePosition();
	OR_Vector3D pos, d;
	
	for( OR_U32 x=0; x<grid.GetGridSizeX(); ++x )
	for( OR_U32 y=0; y<grid.GetGridSizeY(); ++y )
	for( OR_U32 z=0; z<grid.GetGridSizeZ(); ++z )
	{
		grid.ComputePosition(x,y,z, pos );
		d = pos - GizmoPos;

		if(d[X]<0) d[X]=-d[X];
		if(d[Y]<0) d[Y]=-d[Y];
		if(d[Z]<0) d[Z]=-d[Z];
		
		OR_Float r = 0;
		if( OR_ABS(d[Z])<Dim[Z] )
			r = OR_Maths::sqrt( d[X]*d[X] + d[Y]*d[Y] );
		else if( d[Z]>Dim[Z] )
			r = ~(d - OR_Vector3D(0,0,Dim[Z]));
		else 
			r = ~(d - OR_Vector3D(0,0,-Dim[Z]));
		
		if( r<=rInfluenceRadius_ )
			grid.AddData(x,y,z, rMetaIntensity_*pMetaFunc_( r/rInfluenceRadius_ ) );
	}
}


OR_CylinderGizmo::OR_CylinderGizmo(OR_Vector3D vX, OR_Vector3D vY,
			 OR_Vector3D vZ, OR_Vector3D dim)
:	OR_Gizmo(vX, vY, vZ, dim)
{

}

OR_Bool OR_CylinderGizmo::IsInside(OR_Vector3D pos)
{
	return false;
}

OR_Bool OR_CylinderGizmo::FrustrumClip()
{
	return false;
}

/* basic meta-env methods ******************************************/
OR_Float OR_CylinderGizmo::MetaCellValue(OR_Vector3D pos)
{
	return 0;	
}


void OR_CylinderGizmo::Draw()
{
#ifdef OR_DRAW_GIZMOS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_GIZMO) ) 
	{
	glPushMatrix();

		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );

		OR_DrawLocalAxis();

		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(1, 1, 0);

		OR_Data::WireCylinder(Dim[X], Dim[Y], Dim[Z]*2.0f, 12);

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif
}


/*------------------------------------------------------------------------------*/
// Name : OR_CylinderGizmo::DeflectParticule
/** 
 *  \param  particule the particule to deflect.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	Check if a collision has occurs, and then apply an impulse to deviate the particule.
 *	\attention For the moment, works only if Dim[0]==Dim[1]
 */ 
/*------------------------------------------------------------------------------*/
void OR_CylinderGizmo::DeflectParticule(OR_Particule& particule)
{	
	if( pRigidBody_==NULL )
		return;
	
	OR_Matrix4x4 InvMat    = ~(pRigidBody_->GetWorldToBody());
	OR_Matrix4x4 InvMatOld = ~(pRigidBody_->GetWorldToBodyOld());

	/** compute particule position in local coords */
	OR_Vector3D Pos    = InvMat*particule.GetPosition();
	OR_Vector3D PosOld = InvMatOld*particule.GetOldPosition();

	/* project on (X,Y) plane */
	OR_Float rSvgZ    = Pos[Z];
	OR_Float rSvgZOld = PosOld[Z];
	Pos[Z] = PosOld[Z] = 0;

	OR_Float rSquareDist    = Pos.SquareNorm();
	OR_Float rSquareDistOld = PosOld.SquareNorm();	
	OR_Float rSquareRadius  = Dim[X]*Dim[X];

	if( (rSquareDist<rSquareRadius&&rSquareDistOld>rSquareRadius) ||
		(rSquareDist>rSquareRadius&&rSquareDistOld<rSquareRadius) )
	{
		/* the particule has pass the sphere */
		OR_Float rDotP = Pos*PosOld;
		/* search m=b + lambda*(a-b) , solving the equation |m|^2=r^2
		   ie. lambda^2*|a-b|^2 + 2*lambda*(a-b|b) + (|b|^2 - r^2) = 0
		   discriminant : delta' = (a-b|b)^2 - |a-b|^2*(|b|^2-r^2)
		*/
		/* compute (a-b|b) */
		OR_Float rTmp    = rDotP-rSquareDistOld;
		OR_Float rLambda = 0;
		OR_Float rDenom   = rSquareDistOld+rSquareDist-2*rDotP;
		if( rDenom>OR_EPSILON )
		{
			OR_Float rDelta  = rTmp*rTmp - rDenom*(rSquareDistOld-rSquareRadius);
			/* rDenom=0 means a=b, so lambda can be 0 */
			if (rTmp>0)
				rLambda=( -rTmp + OR_Maths::sqrt(rDelta) )/rDenom;
			else
				rLambda=( -rTmp - OR_Maths::sqrt(rDelta) )/rDenom;

		}

		/* intersection of the gizmo & line AB [-OR_EPSILON to unstick the particle] */
		OR_Vector3D m = PosOld+(Pos-PosOld)*(rLambda-OR_EPSILON);

		/* normal at the impact */
		OR_Vector3D normal = !(m);
		/* reflect the speed */
		OR_Vector3D PseudoSpeed = Pos-PosOld;
		/* deflect the velocity */
		PseudoSpeed = PseudoSpeed - normal*( PseudoSpeed*normal )*2;
		/* set the new positions */
		Pos    = m;
		PosOld = Pos - PseudoSpeed;

		/* un-project the particules */
		Pos[Z]    = rSvgZ;
		PosOld[Z] = rSvgZOld;

		/* compute the counce */
		OR_Float rBounce = rBounce_*particule.GetBounce();
		/* scale the speed */
		PosOld = PosOld*rBounce + Pos*(1-rBounce);

		particule.SetPosition(AbsoluteMatrix*Pos);
		particule.SetOldPosition(AbsoluteMatrix*PosOld);
		particule.ComputeSpeed();
	}
}



/*------------------------------------------------------------------------------*/
// Name : OR_CylinderGizmo::DeflectObject
/** 
 *  \param  object the particule to deflect.
 *  \author Gabriel Peyré 2001-08-04
 *
 *  Check if a collision has occurs, and then apply an impulse to deviate the object.
 */ 
/*------------------------------------------------------------------------------*/
void OR_CylinderGizmo::DeflectObject(OR_RigidBody& object)
{
	/** \todo fill this method */
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CylinderGizmo::InitParticule
 *
 *  \param  particule the particule to initialize
 *  \param  AbsoluteSpeed The speed given in the basis of the object.
 *  \author Gabriel Peyré 2001-07-30
 *
 *	Initialize the position and the speed of the particule.
 */ 
/*------------------------------------------------------------------------------*/
void OR_CylinderGizmo::InitParticule(OR_Particule& particule, OR_Vector3D& AbsoluteSpeed)
{
	OR_Float theta = OR_RAND*OR_TWOPI;
	OR_Vector3D Offset(Dim[0]*cos(theta), Dim[1]*sin(theta), OR_RAND_RANGE(-1,1)*Dim[2] );
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

