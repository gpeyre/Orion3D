/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_CubeGizmo.cpp
 *  \brief Definition of class \c OR_CubeGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_CubeGizmo.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_CubeGizmo.h"
#include "../special_effects/OR_MetaGrid.h"

#ifndef OR_USE_INLINE
	#include "OR_CubeGizmo.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CubeGizmo::AddMetaValue
 *
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
void OR_CubeGizmo::AddMetaValue(OR_MetaGrid& grid)
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
		
		OR_Float r;
		if ((d[X]>d[Y])  && (d[X]>d[Z]))
			r = d[X];
		else if((d[Y]>d[X]) && (d[Y]>d[Z]))
			r = d[Y];
		else 
			r = d[Z];
		
		if( r<=rInfluenceRadius_ )
			grid.AddData(x,y,z, rMetaIntensity_*pMetaFunc_( r/rInfluenceRadius_ ) );
	}
}

OR_CubeGizmo::OR_CubeGizmo(OR_Vector3D vX, OR_Vector3D vY,
			 OR_Vector3D vZ, OR_Vector3D dim)
:	OR_Gizmo(vX, vY, vZ, dim)
{

}

OR_Bool OR_CubeGizmo::IsInside(OR_Vector3D pos)
{
	return false;
}

OR_Bool OR_CubeGizmo::FrustrumClip()
{
	return false;
}

void OR_CubeGizmo::Draw()
{
#ifdef OR_DRAW_GIZMOS
	
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_GIZMO) ) 
	{
	glPushMatrix();
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();

		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(1, 0, 0);

		glScalef(2*Dim[X], 2*Dim[Y], 2*Dim[Z]);
		glBegin(GL_LINE_LOOP);
			OR_Globals::Data()->WireCube(1);
		glEnd();

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
	
#endif
}


/*------------------------------------------------------------------------------*/
// Name : OR_CubeGizmo::DeflectParticule_OnPlane
/**
 *	An helper function used by DeflectParticule
 */ 
/*------------------------------------------------------------------------------*/
void OR_CubeGizmo::DeflectParticule_OnPlane(OR_Vector3D& Pos, OR_Vector3D& PosOld, OR_Matrix4x4& matrix, 
											OR_Float rBounce, OR_Float rDimX, OR_Float rDimY)
{
	OR_Matrix4x4 InvMat = ~(matrix);

	/** compute particule position in local coords */
	OR_Vector3D mPos    = InvMat*Pos;
	OR_Vector3D mPosOld = InvMat*PosOld;

	/* check if position before/after are on both sides of the gizmo */
	OR_Float dotb = mPosOld[Z]; // before
	OR_Float dota = mPos[Z];	// after
	if ((dotb<0&&dota>0)||(dotb>0&&dota<0))
	{
		/* the particule has cross the gizmo */
		OR_Float lambda=dotb/(dotb-dota);
		/* intersection of the gizmo & line AB */
		OR_Vector3D m=mPosOld*(1-lambda)+mPos*lambda;
		/* position of the point in local coords */
		OR_Float dotx=m[X];
		if ( (dotx<rDimX) && (dotx>-rDimX) )
		{
			OR_Float doty=m[Y];
			if ( (doty<rDimY) && (doty>-rDimY) )
			{
				/* a collision has occurs */
				/* reflect speed */
				mPosOld[Z] += dota - 2*dotb;
				mPos[Z]    -= dota;
				/* scale speed accrording to bounce */
				mPosOld = mPosOld*rBounce + mPos*(1-rBounce);
				
				/* "unstick" the particule from  the plane */
				if (dotb>0) 
				{
					mPos[Z]    += OR_EPSILON;
					mPosOld[Z] += OR_EPSILON;
				}
				else 
				{
					mPos[Z]    -= OR_EPSILON;
					mPosOld[Z] -= OR_EPSILON;
				}
				Pos    = matrix*mPos;
				PosOld = matrix*mPosOld;
			}
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : OR_CubeGizmo::DeflectParticule
/** 
 *  \param  particule the particule to deflect.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	Check if a collision has occurs, and then apply an impulse to deviate the particule.
 */ 
/*------------------------------------------------------------------------------*/
void OR_CubeGizmo::DeflectParticule(OR_Particule& particule)
{	
	if( pRigidBody_==NULL )
		return;

	OR_Matrix4x4 InvMat    = ~(pRigidBody_->GetWorldToBody());
	OR_Matrix4x4 InvMatOld = ~(pRigidBody_->GetWorldToBodyOld());

	/* compute the bounce */	
	OR_Float rBounce = rBounce_*particule.GetBounce();

	/** compute particule position in local coords */
	OR_Vector3D Pos    = InvMat*particule.GetPosition();
	OR_Vector3D PosOld = InvMatOld*particule.GetOldPosition();

	/* face transformation matrix */
	OR_Matrix4x4 matrix(1, 0, 0, 0,
					 0, 1, 0, 0,
					 0, 0, 1, -Dim[Z],
					 0, 0, 0, 1);
	DeflectParticule_OnPlane(Pos, PosOld, matrix, rBounce, Dim[X], Dim[Y]);
	matrix.SetCoords(1, 0, 0, 0,
					 0,-1, 0, 0,
					 0, 0,-1, Dim[Z],
					 0, 0, 0, 1);
	DeflectParticule_OnPlane(Pos, PosOld, matrix, rBounce, Dim[X], Dim[Y]);
	matrix.SetCoords(1, 0, 0, 0,
					 0, 0, 1, -Dim[Y],
					 0,-1, 0, 0,
					 0, 0, 0, 1);
	DeflectParticule_OnPlane(Pos, PosOld, matrix, rBounce, Dim[X], Dim[Z]);
	matrix.SetCoords(1, 0, 0, 0,
				 	 0, 0,-1, Dim[Y],
			  		 0, 1, 0, 0,
					 0, 0, 0, 1);
	DeflectParticule_OnPlane(Pos, PosOld, matrix, rBounce, Dim[X], Dim[Z]);	
	matrix.SetCoords(0, 0, 1,-Dim[X],
					 0, 1, 0, 0,
					-1, 0, 0, 0,
					 0, 0, 0, 1);
	DeflectParticule_OnPlane(Pos, PosOld, matrix, rBounce, Dim[Z], Dim[Y]);
	matrix.SetCoords(0, 0,-1, Dim[X],
				  	 0, 1, 0, 0,
					 1,	0, 0, 0,
					 0, 0, 0, 1);
	DeflectParticule_OnPlane(Pos, PosOld, matrix, rBounce, Dim[Z], Dim[Y]);
}



/*------------------------------------------------------------------------------*/
// Name : OR_CubeGizmo::DeflectObject
/** 
 *  \param  object the particule to deflect.
 *  \author Gabriel Peyré 2001-08-04
 *
 *  Check if a collision has occurs, and then apply an impulse to deviate the object.
 */ 
/*------------------------------------------------------------------------------*/
void OR_CubeGizmo::DeflectObject(OR_RigidBody& object)
{
	/** \todo fill this method */
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CubeGizmo::InitParticule
 *
 *  \param  particule the particule to initialize
 *  \param  AbsoluteSpeed The speed given in the basis of the object.
 *  \author Gabriel Peyré 2001-07-30
 *
 *	Initialize the position and the speed of the particule.
 */ 
/*------------------------------------------------------------------------------*/
void OR_CubeGizmo::InitParticule(OR_Particule& particule, OR_Vector3D& AbsoluteSpeed)
{
	OR_Vector3D Offset(OR_RAND_RANGE(-1,1)*Dim[X], OR_RAND_RANGE(-1,1)*Dim[Y], OR_RAND_RANGE(-1,1)*Dim[Z]);
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

