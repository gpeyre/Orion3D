/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_TreeFunction_ABC.cpp
 *  \brief  Definition of class \c GW_TreeFunction_ABC
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_TreeFunction_ABC.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_TreeFunction_ABC.h"

#ifndef GW_USE_INLINE
    #include "GW_TreeFunction_ABC.inl"
#endif

#include "GW_QuadTreeNode.h"
#include "GW_QuadTreeVertex.h"

using namespace GW;


/*------------------------------------------------------------------------------*/
// Name : GW_TreeFunction_ABC::GetValue
/**
 *  \param  CurNode [CurVertex&] The vertex.
 *  \author Gabriel Peyré
 *  \date   11-29-2002
 * 
 *  Get the value at a given position.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_TreeFunction_ABC::GetValue( GW_Float rU, GW_Float rV ) const 
{ 
	return 0;
}

/*------------------------------------------------------------------------------*/
// Name : GW_TreeFunction_ABC::ComputeSphericalNormal
/**
 *  \param  Normal [GW_Vector3D&] the normal
 *  \param  theta [GW_Float] the longitude
 *  \param  phi [GW_Float] the latitude.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Return the normal at a given point on the surface of a sphere of radius 1.
 */
/*------------------------------------------------------------------------------*/
void GW_TreeFunction_ABC::ComputeSphericalNormal(GW_Vector3D& Normal, GW_Float theta, GW_Float phi) const
{
	GW_Float rU = theta/GW_TWOPI;
	GW_Float rV = phi/GW_PI + 0.5f;
	/* compute local coords */
	GW_Vector3D u_theta( (float)-sin(theta), (float)cos(theta), 0 );
	GW_Vector3D u_phi  ( (float)(-cos(theta)*sin(phi)), (float)(sin(theta)*sin(phi)), (float)cos(phi) );
	GW_Vector3D u_r    ( (float)(cos(phi)*cos(theta)), (float)(cos(phi)*sin(theta)), (float)sin(phi) );
	/* compute the derivatives */
	GW_Float rU1 = rU-GW_EPSILON;
	if( rU1<0 ) rU1=0;
	GW_Float rU2 = rU+GW_EPSILON;
	if( rU2>1 ) rU2=1;
	GW_Float rV1 = rV-GW_EPSILON;
	if( rV1<0 ) rV1=0;
	GW_Float rV2 = rV+GW_EPSILON;
	if( rV2>1 ) rV2=1;
	GW_Float dtheta = (this->GetValue(rU2, rV) - this->GetValue(rU1, rV))/(rU2-rU1);
	GW_Float dphi   = (this->GetValue(rU, rV2) - this->GetValue(rU, rV1))/(rV2-rV1); 
	/* deduce the gradient to surface (r-1)=f(theta,phi) */
	Normal = u_r - u_theta*dtheta - u_phi*dphi; 
	Normal.Normalize();
}


/*------------------------------------------------------------------------------*/
// Name : GW_TreeFunction_ABC::ComputePlanarNormal
/**
 *  \param  Normal [GW_Vector3D&] the normal
 *  \param  rU [GW_Float] the \c U coord, in [0,1].
 *  \param  phi [GW_Float] the \c V coord, in [0,1].
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Return the normal at a given point on the surface of a plane.
 */
/*------------------------------------------------------------------------------*/
void GW_TreeFunction_ABC::ComputePlanarNormal(GW_Vector3D& Normal, GW_Float rU, GW_Float rV) const
{
	/* compute the derivatives */
	GW_Float dU = (this->GetValue(rU+GW_EPSILON, rV) - this->GetValue(rU-GW_EPSILON, rV))/(2*GW_EPSILON);
	GW_Float dV = (this->GetValue(rU, rV+GW_EPSILON) - this->GetValue(rU, rV-GW_EPSILON))/(2*GW_EPSILON); 
	/* deduce the gradient to surface (r-1)=f(theta,phi) */
	Normal = GW_Vector3D(1, -dU, -dV); 
	Normal.Normalize();
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
