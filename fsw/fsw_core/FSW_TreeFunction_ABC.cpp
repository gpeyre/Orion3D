/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_TreeFunction_ABC.cpp
 *  \brief  Definition of class \c FSW_TreeFunction_ABC
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_TreeFunction_ABC.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_TreeFunction_ABC.h"

#ifndef FSW_USE_INLINE
    #include "FSW_TreeFunction_ABC.inl"
#endif

#include "FSW_QuadTreeNode.h"
#include "FSW_QuadTreeVertex.h"

using namespace FSW;


/*------------------------------------------------------------------------------*/
// Name : FSW_TreeFunction_ABC::GetValue
/**
 *  \param  CurNode [CurVertex&] The vertex.
 *  \author Gabriel Peyré
 *  \date   11-29-2002
 * 
 *  Get the value at a given position.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_TreeFunction_ABC::GetValue( FSW_Float rU, FSW_Float rV ) const 
{ 
	return 0;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_TreeFunction_ABC::ComputeSphericalNormal
/**
 *  \param  Normal [FSW_Vector3D&] the normal
 *  \param  theta [FSW_Float] the longitude
 *  \param  phi [FSW_Float] the latitude.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Return the normal at a given point on the surface of a sphere of radius 1.
 */
/*------------------------------------------------------------------------------*/
void FSW_TreeFunction_ABC::ComputeSphericalNormal(FSW_Vector3D& Normal, FSW_Float theta, FSW_Float phi) const
{
	FSW_Float rU = theta/FSW_TWOPI;
	FSW_Float rV = phi/FSW_PI + 0.5f;
	/* compute local coords */
	FSW_Vector3D u_theta( (float)-sin(theta), (float)cos(theta), 0 );
	FSW_Vector3D u_phi  ( (float)(-cos(theta)*sin(phi)), (float)(sin(theta)*sin(phi)), (float)cos(phi) );
	FSW_Vector3D u_r    ( (float)(cos(phi)*cos(theta)), (float)(cos(phi)*sin(theta)), (float)sin(phi) );
	/* compute the derivatives */
	FSW_Float rU1 = rU-FSW_EPSILON;
	if( rU1<0 ) rU1=0;
	FSW_Float rU2 = rU+FSW_EPSILON;
	if( rU2>1 ) rU2=1;
	FSW_Float rV1 = rV-FSW_EPSILON;
	if( rV1<0 ) rV1=0;
	FSW_Float rV2 = rV+FSW_EPSILON;
	if( rV2>1 ) rV2=1;
	FSW_Float dtheta = (this->GetValue(rU2, rV) - this->GetValue(rU1, rV))/(rU2-rU1);
	FSW_Float dphi   = (this->GetValue(rU, rV2) - this->GetValue(rU, rV1))/(rV2-rV1); 
	/* deduce the gradient to surface (r-1)=f(theta,phi) */
	Normal = u_r - u_theta*dtheta - u_phi*dphi; 
	Normal.Normalize();
}


/*------------------------------------------------------------------------------*/
// Name : FSW_TreeFunction_ABC::ComputePlanarNormal
/**
 *  \param  Normal [FSW_Vector3D&] the normal
 *  \param  rU [FSW_Float] the \c U coord, in [0,1].
 *  \param  phi [FSW_Float] the \c V coord, in [0,1].
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Return the normal at a given point on the surface of a plane.
 */
/*------------------------------------------------------------------------------*/
void FSW_TreeFunction_ABC::ComputePlanarNormal(FSW_Vector3D& Normal, FSW_Float rU, FSW_Float rV) const
{
	/* compute the derivatives */
	FSW_Float dU = (this->GetValue(rU+FSW_EPSILON, rV) - this->GetValue(rU-FSW_EPSILON, rV))/(2*FSW_EPSILON);
	FSW_Float dV = (this->GetValue(rU, rV+FSW_EPSILON) - this->GetValue(rU, rV-FSW_EPSILON))/(2*FSW_EPSILON); 
	/* deduce the gradient to surface (r-1)=f(theta,phi) */
	Normal = FSW_Vector3D(1, -dU, -dV); 
	Normal.Normalize();
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
