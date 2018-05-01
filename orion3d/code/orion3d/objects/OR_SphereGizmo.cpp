/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SphereGizmo.cpp
 *  \brief Definition of class \c OR_SphereGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SphereGizmo.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_SphereGizmo.h"
#include "../special_effects/OR_MetaGrid.h"

#ifndef OR_USE_INLINE
	    #include "OR_SphereGizmo.inl"
#endif

using namespace OR;


#if 0
void OR_MetaEnv::UpdateGizmo(OR_Gizmo *gizmo)
{
	/* compute the value to add to the cell */
	OR_Vector3D pos, pos_init;
	OR_Vector3D Size=SuportGizmo->GetDim()*2;
	OR_Vector3D GizmoPos=SuportGizmo->GetAbsolutePosition();
	/* position of the ball in local coords */
	OR_Vector3D MetaPos=~( SuportGizmo->GetAbsoluteMatrix() ) * gizmo->GetAbsolutePosition();

	OR_Float InfluenceRadius = gizmo->GetInfluenceRadius();

	/* compute from where to where update the grid */
	OR_I32 start[3], end[3];
	for (OR_I32 i=0; i<3; i++)
	{
		start[i]=(OR_I32) (  ((OR_Float)Precision[i])/2 + (MetaPos[i]-InfluenceRadius)*((OR_Float)Precision[i])/Size[i]  );
		if (start[i]<0) start[i]=0;
		if (start[i]>Precision[i]) start[i]=Precision[i];
		end[i]=(OR_I32) (  ((OR_Float)Precision[i])/2 + (MetaPos[i]+InfluenceRadius)*((OR_Float)Precision[i])/Size[i]  );
		if (end[i]<0) end[i]=0;
		if (end[i]>Precision[i]) end[i]=Precision[i];
	}

	pos_init[X]=(-1-Precision[X]/2+start[X])*Size[X]/Precision[X];
	pos_init[Y]=(-1-Precision[Y]/2+start[Y])*Size[Y]/Precision[Y];
	pos_init[Z]=(-1-Precision[Z]/2+start[Z])*Size[Z]/Precision[Z];
	/* translate in absolute coords */
	pos_init+=SuportGizmo->GetAbsolutePosition();
	/* for incremental computation of pos */
	OR_Float incx=Size[X]/Precision[X];
	OR_Float incy=Size[Y]/Precision[Y];
	OR_Float incz=Size[Z]/Precision[Z];	

	pos[X]=pos_init[X];
	for(OR_I32 x=start[X]; x<end[X]; x++)
	{
		pos[Y]=pos_init[Y];
		pos[X]+=incx;
		for(OR_I32 y=start[Y]; y<end[Y]; y++)
		{
			pos[Z]=pos_init[Z];
			pos[Y]+=incy;
			for(OR_I32 z=start[Z]; z<end[Z]; z++)
			{
				pos[Z]+=incz;
				/* the magic formula to store the metaball !! */
				Grid[x+Precision[X]*y+Precision[X]*Precision[Y]*z] +=
							gizmo->MetaCellValue(pos);
			}
		}
	}
}
#endif

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphereGizmo::AddMetaValue
 *
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
void OR_SphereGizmo::AddMetaValue(OR_MetaGrid& grid)
{
		OR_Vector3D GizmoPos = this->GetAbsolutePosition();
		OR_Vector3D pos;
		
		for( OR_U32 x=0; x<grid.GetGridSizeX(); ++x )
		for( OR_U32 y=0; y<grid.GetGridSizeY(); ++y )
		for( OR_U32 z=0; z<grid.GetGridSizeZ(); ++z )
		{
			grid.ComputePosition(x,y,z, pos );
			OR_Float rr = (pos-GizmoPos).SquareNorm();
			if( rr<=rInfluenceRadius_*rInfluenceRadius_ )
			{
				OR_Float r = OR_Maths::sqrt(rr);
				grid.AddData(x,y,z, rMetaIntensity_*pMetaFunc_( r/rInfluenceRadius_ ) );
			}
		}
}



OR_SphereGizmo::OR_SphereGizmo(OR_Vector3D vX,
			 OR_Vector3D vY,
			 OR_Vector3D vZ, 
			 OR_Vector3D dim)
:	OR_Gizmo(vX, vY, vZ, dim)
{

}

OR_Bool OR_SphereGizmo::IsInside(OR_Vector3D pos)
{
	return false;
}

OR_Bool OR_SphereGizmo::FrustrumClip()
{
	return false;
}


void OR_SphereGizmo::Draw()
{
#ifdef OR_DRAW_GIZMOS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_GIZMO) ) 
	{
	glPushMatrix();
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();
		
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(1, 1, 0);

		glPushMatrix();
			glScalef(Dim[X], Dim[Y], Dim[Z]);
			OR_Globals::Data()->WireSphere(1, 8, 6);
		glPopMatrix();

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif
}

/*------------------------------------------------------------------------------*/
// Name : OR_SphereGizmo::DeflectParticule
/** 
 *  \param  particule the particule to deflect.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	Check if a collision has occurs, and then apply an impulse to deviate the particule.
 *	\attention For the moment, works only with sphere, not with elipsoides.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SphereGizmo::DeflectParticule(OR_Particule& particule)
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
	
	if( OML::OML_RayCaster::RayCastSphere_Segment(Dim[0], PosOld, Pos, Normal, Intersection) )
	{
		/* a collision has occured */
		OR_Vector3D ImpactPos = pRigidBody_->GetWorldToBody()*Intersection;
		OR_Vector3D Normal    = !( ImpactPos-this->GetAbsolutePosition() );
		
		particule.SetPosition( pRigidBody_->GetWorldToBody()*Intersection );
		/* compute the impulse created by the choc, in local coords */
		this->ResolveImpulse(particule, AbsoluteMatrix.GetZ(), ImpactPos);
	}
}



/*------------------------------------------------------------------------------*/
// Name : OR_SphereGizmo::DeflectObject
/** 
 *  \param  object the particule to deflect.
 *  \author Gabriel Peyré 2001-08-04
 *
 *  Check if a collision has occurs, and then apply an impulse to deviate the object.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SphereGizmo::DeflectObject(OR_RigidBody& object)
{
	/** \todo fill this method */
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SphereGizmo::InitParticule
 *
 *  \param  particule the particule to initialize
 *  \param  AbsoluteSpeed The speed given in the basis of the object.
 *  \author Gabriel Peyré 2001-07-30
 *
 *	Initialize the position and the speed of the particule.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SphereGizmo::InitParticule(OR_Particule& particule, OR_Vector3D& AbsoluteSpeed)
{
	OR_Float theta = OR_RAND*OR_TWOPI;
	OR_Float phi   = OR_RAND*OR_TWOPI;

	OR_Vector3D Offset;
	Offset[0] = OR_RAND*Dim[X]*cos(theta);
	OR_Float rRadius = OR_RAND*Dim[Y]*sin(theta);
	Offset[1] = rRadius*cos(phi);
	Offset[2] = rRadius*sin(phi);

	particule.ReSetPosition(GetAbsolutePosition()+Offset);
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

