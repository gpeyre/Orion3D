/*----------------------------------------------------------------------------*/
/*                         OML_Quaternion.cpp                                  */
/*----------------------------------------------------------------------------*/
/* a quaternion                                                               */
/*----------------------------------------------------------------------------*/

#ifdef OML_SCCSID
static const char* sccsid = "@(#) OML_Quaternion.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OML_SCCSID

#include "stdafx.h"
#include "OML_Maths.h"
#include "OML_Vector2D.h"
#include "OML_Vector3D.h"
#include "OML_Vector4D.h"
#include "OML_Matrix4x4.h"
#include "OML_Quaternion.h"


#ifndef OML_USE_INLINE
	#include "OML_Quaternion.inl"
#endif


using namespace OML;
	
/*--------------------------------------------------------------------*/
/*                       class OML_Quaternion                          */
/*--------------------------------------------------------------------*/
/* a quaternion                                                       */
/*--------------------------------------------------------------------*/

OML_Quaternion::OML_Quaternion()
{
	x=y=z=0;
	w=1;
}

OML_Quaternion::OML_Quaternion(const OML_Float _w, const OML_Float _x, 
							 const OML_Float _y, const OML_Float _z)
{
	x=_x;
	y=_y;
	z=_z;
	w=_w;
}

OML_Quaternion::OML_Quaternion(const OML_Float _w, const OML_Float axe[3])
{
	x=axe[X];
	y=axe[Y];
	z=axe[Z];
	w=_w;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion constructor
 *
 *  \param  axe the axe of the quaternion
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OML_Quaternion::OML_Quaternion(OML_Vector3D& axe)
{
	x = axe[X];
	y = axe[Y];
	z = axe[Z];
	w = 0;
}


OML_Quaternion OML_Quaternion::operator*(const OML_Quaternion& b)
{
	return OML_Quaternion(w*b.w - (x*b.x + y*b.y + z*b.z),
					w*b.x + b.w*x + y*b.z - z*b.y,
					w*b.y + b.w*y + z*b.x - x*b.z,
					w*b.z + b.w*z + x*b.y - y*b.x);
}

OML_Quaternion& OML_Quaternion::operator*=(const OML_Quaternion& q)
{
	OML_Float _w = w*q.w - (x*q.x + y*q.y + z*q.z);
	OML_Float _x = w*q.x + q.w*x + y*q.z - z*q.y;
	OML_Float _y = w*q.y + q.w*y + z*q.x - x*q.z;
	z = w*q.z + q.w*z + x*q.y - y*q.x;
	w = _w;
	x = _x;
	y = _y;
	return *this;
}

OML_Quaternion OML_Quaternion::operator*(OML_Float m)
{
    return OML_Quaternion(m*w, m*x, m*y, m*z);
}

OML_Quaternion& OML_Quaternion::operator+=(OML_Quaternion &q)
{
    w+=q.w;
    x+=q.x;
	y+=q.y;
	z+=q.z;
    return *this;
}

OML_Quaternion& OML_Quaternion::operator-=(OML_Quaternion &q)
{
    w-=q.w;
    x-=q.x;
	y-=q.y;
	z-=q.z;
    return *this;
}

OML_Quaternion OML_Quaternion::operator+(OML_Quaternion &q)
{
	return OML_Quaternion(w+q.w, x+q.x, y+q.y, z+q.z);
}

OML_Quaternion OML_Quaternion::operator-(OML_Quaternion &q)
{
	return OML_Quaternion(w-q.w, x-q.x, y-q.y, z-q.z);
}

OML_Quaternion OML_Quaternion::operator-()
{
	return OML_Quaternion(-w, -x, -y, -z);
}

OML_Quaternion OML_Quaternion::GetConjugated()
{
	return OML_Quaternion(w, -x, -y, -z);
}

OML_Quaternion& OML_Quaternion::AutoConjugate()
{
	x=-x;
	y=-y;
	z=-z;
	return *this;
}

OML_Quaternion OML_Quaternion::operator ~()
{
	OML_Float norme2 = w*w + x*x + y*y + z*z;
	if (norme2==0.0) norme2=1;

	OML_Float recip=1/norme2;

	return OML_Quaternion(w*recip, -x*recip, -y*recip, -z*recip);
}

OML_Quaternion& OML_Quaternion::operator !()
{
	OML_Float norme2=w*w + x*x + y*y + z*z;
	if (norme2==0.0) norme2=1;

	OML_Float recip=1/norme2;

	w= w*recip;
	x=-x*recip;
	y=-y*recip;
	z=-z*recip;

	return *this;
}

OML_Quaternion& OML_Quaternion::AutoNormalize()
{
	OML_Float norme = OML_Maths::norm( x,y,z,w );
	if (norme == 0.0)
    {
		w = 1.0; 
		x = y = z = 0.0;
	}
	else
    {
		OML_Float recip = 1/norme;

		w *= recip;
		x *= recip;
		y *= recip;
		z *= recip;
	}
	return *this;
}

OML_Quaternion OML_Quaternion::GetNormalized()
{
	OML_Float norme = OML_Maths::norm( x,y,z,w );
	if (norme == 0.0)
    {
		return OML_Quaternion();
	}
	else
    {
		OML_Float recip = 1/norme;
		return OML_Quaternion(w*recip, x*recip, y*recip, z*recip); 
	}
}

OML_Float OML_Quaternion::GetNorm()
{
	return OML_Maths::norm( x,y,z,w );
}

OML_Float OML_Quaternion::GetSquareNorm()
{
	return w*w + x*x + y*y + z*z;
}

OML_Quaternion& OML_Quaternion::BuildFromAxis(const OML_Float angle, OML_Float _x, OML_Float _y, OML_Float _z)
{
	OML_Float omega, s, c;
    
	s = OML_Maths::norm( _x, _y, _z );
  
	if (fabs(s) > OML_EPSILON)
    {
		c=1/s;
	  
		_x*=c;
		_y*=c;
		_z*=c;

		omega=-0.5f*angle;
		s=(OML_Float)sin(omega);

		x=s*_x;
		y=s*_y;
		z=s*_z;
		w=(OML_Float)cos(omega);
	}
	else
	{
		x=y=0.0f;
		z=0.0f;
		w=1.0f;
	}
	AutoNormalize();
	return *this;
}

OML_Quaternion& OML_Quaternion::BuildFromEuler(const OML_Float Angle, OML_Float x, OML_Float y, OML_Float z)
{
	return *this;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::ToAxisAndAngle
 *
 *  \param  axis output the axis of the rotation.
 *  \param  angle output the angle of the rotation (\b IN \b RADIAN).
 *  \author Gabriel Peyré 2001-11-06
 *
 *	A quaternion can be converted back to a rotation axis and angle
 *	using the following algorithm :
 *
 *	\code
 *	If the axis of rotation is         (ax, ay, az)
 *	and the angle is                   theta (radians)
 *	then the                           angle= 2 * acos(w)
 *
 *	ax= x / scale
 *	ay= y / scale
 *  az= z / scale
 *  
 *	where scale = x^2 + y^2 + z^2
 *	\endcode
 */ 
/*------------------------------------------------------------------------------*/
void OML_Quaternion::ToAxisAndAngle(OML_Vector3D& axis, OML_Float& angle)
{
	OML_Float rAngle = 2*((OML_Float) acos( w ));
	OML_Float rScale = x*x + y*y + z*z;

	if( OML_ABS(rScale)<OML_EPSILON )
		return;

	rScale = 1/rScale;

	axis.SetData(0, x*rScale );
	axis.SetData(1, y*rScale );
	axis.SetData(2, z*rScale );
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion constructor
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Create a matrix representing the same rotation.
 *
 *	Then the quaternion can then be converted into a 4x4 rotation
 *	matrix using the following expression:
 *
 *	\code   
 *		|       2     2                                |
 *		| 1 - 2Y  - 2Z    2XY - 2ZW      2XZ + 2YW     |
 *		|                                              |
 *		|                       2     2                |
 *	M = | 2XY + 2ZW       1 - 2X  - 2Z   2YZ - 2XW     |
 *		|                                              |
 *		|                                      2     2 |
 *		| 2XZ - 2YW       2YZ + 2XW      1 - 2X  - 2Y  |
 *		|                                              |
 *	\endcode	 
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix3x3 OML_Quaternion::ToMatrix()
{
	return OML_Matrix3x3(1.0f - 2*y*y - 2*z*z, 2*x*y + 2*w*z, 2*x*z - 2*w*y, 
					 2*x*y - 2*w*z, 1.0f - 2*x*x - 2*z*z, 2*y*z + 2*w*x,
					 2*x*z + 2*w*y, 2*y*z - 2*w*x, 1.0f - 2*x*x - 2*y*y);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Quaternion::BuildFromMatrix
 *
 *  \param  m rotation matrix.
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Build the quaternion to reflect the rotation matrix.
 */ 
/*------------------------------------------------------------------------------*/
void OML_Quaternion::BuildFromMatrix(OML_Matrix3x3& m)
{
	/** \todo find this f&%$* formula */
}


OML_Quaternion OML_Quaternion::Slerp(OML_Quaternion& b, OML_Float t)
{
	OML_Float omega, cosom, sinom, sclp, sclq;

	cosom = x*b.x + y*b.y + z*b.z + w*b.w;

	if ((1.0f+cosom) > OML_EPSILON)
	{
		if ((1.0f-cosom) > OML_EPSILON)
		{
			omega = (OML_Float) acos(cosom);
			sinom = (OML_Float) sin(omega);
			sclp = (OML_Float) sin((1.0f-t)*omega) / sinom;
			sclq = (OML_Float) sin(t*omega) / sinom;
		}
		else
		{
			sclp = 1.0f - t;
			sclq = t;
		}

		x = sclp*x + sclq*b.x;
		y = sclp*y + sclq*b.y;
		z = sclp*z + sclq*b.z;
		w = sclp*w + sclq*b.w;
	}
	else
	{
		x =-y;
		y = x;
		z =-w;
		w = z;

		sclp = (OML_Float) sin((1.0f-t) * OML_PI * 0.5);
		sclq = (OML_Float) sin(t * OML_PI * 0.5);

		x = sclp*x + sclq*b.x;
		y = sclp*y + sclq*b.y;
		z = sclp*z + sclq*b.z;
	}
	return *this;
}

OML_Quaternion OML_Quaternion::Lerp(OML_Quaternion& to, OML_Float t)
{
	return OML_Quaternion(w*(1-t) + to.w*t,x*(1-t) + to.x*t, y*(1-t) + to.y*t, 
						z*(1-t) + to.z*t).GetNormalized();
}

OML_Quaternion& OML_Quaternion::Exp()
{
	OML_Float mul;
	OML_Float length = OML_Maths::norm( x, y, z );

	if (length > OML_EPSILON)  
		mul = (OML_Float) sin(length)/length;
	else 
		mul = 1.0;

	w = (OML_Float) cos(length);

	x *= mul;
	y *= mul;
	z *= mul; 

	return *this;
}

OML_Quaternion& OML_Quaternion::Log()
{
	OML_Float length;

	length = OML_Maths::norm( x,y,z );
	length = (OML_Float) atan(length/w);

	w = 0.0;

	x *= length;
	y *= length;
	z *= length;

	return *this;
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////