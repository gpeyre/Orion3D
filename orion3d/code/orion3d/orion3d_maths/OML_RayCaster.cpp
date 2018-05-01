/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_RayCaster.cpp
 *  \brief Definition of class \c OML_RayCaster
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OML_SCCSID
static const char* sccsid = "@(#) OML_RayCaster.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OML_SCCSID


#include "../stdafx.h"
#include "OML_RayCaster.h"

#ifndef OML_USE_INLINE
	    #include "OML_RayCaster.inl"
#endif

using namespace OML;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_RayCaster::RayCastSphere
 *
 *  \param  radius the radius of the sphere.
 *  \param  v1 first point, origine of the ray
 *  \param  v2 second point, gives the direction of the ray
 *  \param  normal returned value : the normal at intersection, if exists.
 *  \param  intersection returned value : the intersection point, if exists.
 *  \return does the ray intersect the sphere ?
 *  \author Gabriel Peyré 2001-12-12
 *
 *	Make an intersection test between a sphere centred at the origin and a ray 
 *  starting from \c v1, passing through \c v2.
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_RayCaster::RayCastSphere(OML_Float rRadius, const OML_Vector3D& v1, const OML_Vector3D& v2,  
									OML_Vector3D& normal, OML_Vector3D& intersection)
{
	OML_Float rSquareDist2    = v2.SquareNorm();
	OML_Float rSquareDist1    = v1.SquareNorm();	
	OML_Float rSquareRadius  = rRadius*rRadius;

	if( (rSquareDist2<rSquareRadius && rSquareDist1>rSquareRadius) ||
		(rSquareDist2>rSquareRadius && rSquareDist1<rSquareRadius) )
	{
		/* the particule has pass the sphere */
		OML_Float rDotP = v2*v1;
		/* search m=b + lambda*(a-b) , solving the equation |m|^2=r^2
		   ie. lambda^2*|a-b|^2 + 2*lambda*(a-b|b) + (|b|^2 - r^2) = 0
		   discriminant : delta' = (a-b|b)^2 - |a-b|^2*(|b|^2-r^2)
		*/
		/* compute (a-b|b) */
		OML_Float rTmp    = rDotP-rSquareDist1;
		OML_Float rLambda = 0;
		OML_Float rDenom   = rSquareDist1+rSquareDist2-2*rDotP;
		if( rDenom>OML_EPSILON )
		{
			OML_Float rDelta  = rTmp*rTmp - rDenom*(rSquareDist1-rSquareRadius);
			if( rDelta<0 )
				return false;
			/* rDenom=0 means a=b, so lambda can be 0 */
			if (rTmp>0)
				rLambda=( -rTmp + OML_Maths::sqrt(rDelta) )/rDenom;
			else
				rLambda=( -rTmp - OML_Maths::sqrt(rDelta) )/rDenom;

		}

		/* intersection of the gizmo & line AB [-OML_EPSILON to unstick the particle] */
		intersection = v1+(v2-v1)*(rLambda*0.95f ); //OML_EPSILON);

		/* normal at the impact */
		normal = !( intersection );

		return true;
	}

	return false;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_RayCaster::RayCastSphere_Segment
 *
 *  \param  radius the radius of the sphere.
 *  \param  v1 first point, origine of the ray
 *  \param  v2 second point, gives the direction of the ray
 *  \param  normal returned value : the normal at intersection, if exists.
 *  \param  intersection returned value : the intersection point, if exists.
 *  \return does the ray intersect the sphere ?
 *  \author Gabriel Peyré 2001-12-12
 *
 *	Make an intersection test between a sphere centred at the origin and the [v1,v2] segment.
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_RayCaster::RayCastSphere_Segment(OML_Float rRadius, const OML_Vector3D& v1, const OML_Vector3D& v2, 
											  OML_Vector3D& normal, OML_Vector3D& intersection)
{
	OML_Float rSquareDist2    = v2.SquareNorm();
	OML_Float rSquareDist1    = v1.SquareNorm();	
	OML_Float rSquareRadius  = rRadius*rRadius;

	if( (rSquareDist2<rSquareRadius && rSquareDist1>rSquareRadius) ||
		(rSquareDist2>rSquareRadius && rSquareDist1<rSquareRadius) )
	{
		/* the particule has pass the sphere */
		OML_Float rDotP = v2*v1;
		/* search m=b + lambda*(a-b) , solving the equation |m|^2=r^2
		   ie. lambda^2*|a-b|^2 + 2*lambda*(a-b|b) + (|b|^2 - r^2) = 0
		   discriminant : delta' = (a-b|b)^2 - |a-b|^2*(|b|^2-r^2)
		*/
		/* compute (a-b|b) */
		OML_Float rTmp    = rDotP-rSquareDist1;
		OML_Float rLambda = 0;
		OML_Float rDenom   = rSquareDist1+rSquareDist2-2*rDotP;
		if( rDenom>OML_EPSILON )
		{
			OML_Float rDelta  = rTmp*rTmp - rDenom*(rSquareDist1-rSquareRadius);

			if( rDelta<0 )
				return false;

			/* rDenom=0 means a=b, so lambda can be 0 */
			if (rTmp>0)
				rLambda=( -rTmp + OML_Maths::sqrt(rDelta) )/rDenom;
			else
				rLambda=( -rTmp - OML_Maths::sqrt(rDelta) )/rDenom;
		}
		else
		{
			return false;
		}

		/* intersection of the gizmo & line AB [-OML_EPSILON to unstick the particle] */
		intersection = v1+(v2-v1)*(rLambda*0.95f ); //OML_EPSILON);

		/* normal at the impact */
		normal = !( intersection );

		return true;
	}

	return false;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_RayCaster::RayCastSphere
 *
 *  \param  center the center of the sphere.
 *  \param  radius the radius of the sphere.
 *  \param  v1 first point, origine of the ray
 *  \param  v2 second point, gives the direction of the ray
 *  \param  normal returned value : the normal at intersection, if exists.
 *  \param  intersection returned value : the intersection point, if exists.
 *  \return does the ray intersect the sphere ?
 *  \author Gabriel Peyré 2001-12-12
 *
 *	Make an intersection test between a sphere centred at the origin and a ray 
 *  starting from \c v1, passing through \c v2.
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_RayCaster::RayCastSphere(OML_Float rRadius, const OML_Vector3D& center, const OML_Vector3D& v1, const OML_Vector3D& v2, OML_Vector3D& normal, OML_Vector3D& intersection)
{
	OML_Bool bSuccess = OML_RayCaster::RayCastSphere(rRadius, v1 - center, v2 - center, normal, intersection);	
	intersection += center;
	return bSuccess;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_RayCaster::RayCastSphere_Segment
 *
 *  \param  center the center of the sphere. 
 *  \param  radius the radius of the sphere.
 *  \param  v1 first point, origine of the ray
 *  \param  v2 second point, gives the direction of the ray
 *  \param  normal returned value : the normal at intersection, if exists.
 *  \param  intersection returned value : the intersection point, if exists.
 *  \return does the ray intersect the sphere ?
 *  \author Gabriel Peyré 2001-12-12
 *
 *	Make an intersection test between a sphere centred at the origin and and the [v1,v2] segment.
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_RayCaster::RayCastSphere_Segment(OML_Float rRadius, const OML_Vector3D& center, const OML_Vector3D& v1, const OML_Vector3D& v2, OML_Vector3D& normal, OML_Vector3D& intersection)
{
	OML_Bool bSuccess = OML_RayCaster::RayCastSphere_Segment(rRadius, v1 - center, v2 - center, normal, intersection);	
	intersection += center;
	return bSuccess;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_RayCaster::RayCastSquare
 *
 *  \param  rDimX dimension on X axis of the square.
 *  \param  rDimY dimension on Y axis of the square.
 *  \param  v1 first point, origine of the ray
 *  \param  v2 second point, gives the direction of the ray
 *  \param  normal returned value : the normal at intersection, if exists.
 *  \param  intersection returned value : the intersection point, if exists.
 *  \return does the ray intersect the square ?
 *  \author Gabriel Peyré 2001-12-12
 *
 *	Make an intersection test between a square patch centred at the origin, vith axis aligned on X and Y world axis, 
 *	and a ray from \c v1 diriged toward \c v2.
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_RayCaster::RayCastSquare(OML_Float rDimX, OML_Float rDimY, 
									  const OML_Vector3D& v1, const OML_Vector3D& v2, 
									  OML_Vector3D& normal, OML_Vector3D& intersection)
{
	/* check if position before/after are on both sides of the gizmo */
	OML_Float dotb = v1[Z]; // before
	OML_Float dota = v2[Z];	// after
	if( (dotb>0&&dota>dotb)||(dotb<0&&dota<dotb) )
	{
		/* the ray doesn't cross the plane */
		return false;
	}
	
	/* the particule has cross the gizmo */
	OML_Float rLambda = dotb/(dotb-dota);
	
	/* intersection of the gizmo & line AB */
	intersection = v1+(v2-v1)*(rLambda*0.95f );
	
	/* position of the point in local coords */
	OML_Float dotx = intersection[X];
	
	if ( (dotx<rDimX) && (dotx>-rDimX) )
	{
		OML_Float doty = intersection[Y];
		if ( (doty<rDimY) && (doty>-rDimY) )
		{				
			normal = OML_Vector3D(0,0,1);
			return true;
		}
	}
	
	return false;
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_RayCaster::RayCastSquare_Segment
 *
 *  \param  rDimX dimension on X axis of the square.
 *  \param  rDimY dimension on Y axis of the square.
 *  \param  v1 first point, origine of the ray
 *  \param  v2 second point, gives the direction of the ray
 *  \param  normal returned value : the normal at intersection, if exists.
 *  \param  intersection returned value : the intersection point, if exists.
 *  \return does the ray intersect the square ?
 *  \author Gabriel Peyré 2001-12-12
 *
 *	Make an intersection test between a square patch centred at the origin, vith axis aligned on X and Y world axis, 
 *	and a segment [v1,v2].
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_RayCaster::RayCastSquare_Segment(OML_Float rDimX, OML_Float rDimY, 
											  const OML_Vector3D& v1, const OML_Vector3D& v2, 
											  OML_Vector3D& normal, OML_Vector3D& intersection)
{
	/* check if position before/after are on both sides of the gizmo */
	OML_Float dotb = v1[Z]; // before
	OML_Float dota = v2[Z];	// after
	if( (dotb<0&&dota>0)||(dotb>0&&dota<0) )
	{
		/* the particule has cross the gizmo */
		OML_Float rLambda = dotb/(dotb-dota);
		
		/* intersection of the gizmo & line AB */
		intersection = v1+(v2-v1)*(rLambda*0.95f );
		
		/* position of the point in local coords */
		OML_Float dotx = intersection[X];
		
		if ( (dotx<rDimX) && (dotx>-rDimX) )
		{
			OML_Float doty = intersection[Y];
			if ( (doty<rDimY) && (doty>-rDimY) )
			{				
				normal = OML_Vector3D(0,0,1);
				return true;
			}
		}
	}
	
	return false;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_RayCaster::RayCastSquare
 *
 *  \param  center the center of the square.
 *  \param  AxeX the X axis of the suare.
 *  \param  AxeY the Y axis of the suare.
 *  \param  v1 first point, origine of the ray
 *  \param  v2 second point, gives the direction of the ray
 *  \param  normal returned value : the normal at intersection, if exists.
 *  \param  intersection returned value : the intersection point, if exists.
 *  \return does the ray intersect the square ?
 *  \author Gabriel Peyré 2001-12-12
 *
 *	Make an intersection test between a square patch centred at the origin, vith axis aligned on X and Y world axis, 
 *	and a ray from \c v1 diriged toward \c v2.
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_RayCaster::RayCastSquare(const OML_Vector3D center, const OML_Vector3D& AxeX, const OML_Vector3D& AxeY, 
									  const OML_Vector3D& v1, const OML_Vector3D& v2, 
									  OML_Vector3D& normal, OML_Vector3D& intersection)
{
	OML_Matrix4x4 m;
	OML_Float rDimX  = ~AxeX;
	OML_Float rDimY  = ~AxeY;
	OML_ASSERT( rDimX>0 && rDimY>0 );
	m.SetX( AxeX/rDimX );
	m.SetY( AxeY/rDimY );
	m.SetZ( m.GetX()^m.GetY() );
	m.SetTranslation( center );
	OML_Matrix4x4 InvMat = ~m;

	OML_Bool bSuccess = OML_RayCaster::RayCastSquare(rDimX, rDimY, InvMat*v1, InvMat*v2, normal, intersection);
	intersection = m * intersection;
	normal = m*normal;

	return bSuccess;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_RayCaster::RayCastSquare_Segment
 *
 *  \param  center the center of the square.
 *  \param  AxeX the X axis of the suare.
 *  \param  AxeY the Y axis of the suare.
 *  \param  v1 first point, origine of the ray
 *  \param  v2 second point, gives the direction of the ray
 *  \param  normal returned value : the normal at intersection, if exists.
 *  \param  intersection returned value : the intersection point, if exists.
 *  \return does the ray intersect the square ?
 *  \author Gabriel Peyré 2001-12-12
 *
 *	Make an intersection test between a square patch centred at the origin, vith axis aligned on X and Y world axis, 
 *	and a segment [v1,v2].
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_RayCaster::RayCastSquare_Segment(const OML_Vector3D center, const OML_Vector3D& AxeX, const OML_Vector3D& AxeY, 
											  const OML_Vector3D& v1, const OML_Vector3D& v2, 
											  OML_Vector3D& normal, OML_Vector3D& intersection)
{
	OML_Matrix4x4 m;
	OML_Float rDimX  = ~AxeX;
	OML_Float rDimY  = ~AxeY;
	OML_ASSERT( rDimX>0 && rDimY>0 );
	m.SetX( AxeX/rDimX );
	m.SetY( AxeY/rDimY );
	m.SetZ( m.GetX()^m.GetY() );
	m.SetTranslation( center );
	OML_Matrix4x4 InvMat = ~m;
	
	OML_Bool bSuccess = OML_RayCaster::RayCastSquare_Segment(rDimX, rDimY, InvMat*v1, InvMat*v2, normal, intersection);
	intersection = m * intersection;
	normal = m*normal;

	return bSuccess;
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

