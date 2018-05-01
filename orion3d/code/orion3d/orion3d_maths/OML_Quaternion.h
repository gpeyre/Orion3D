/*----------------------------------------------------------------------------*/
/*                         OML_Quaternion.h                                    */
/*----------------------------------------------------------------------------*/
/* a quaternion                                                               */
/*----------------------------------------------------------------------------*/


/** \file 
	This file contains the defintion of a quaternion, wich can be used to 
	represent a rotation, and is mainly used for animation purposes.
	\author Gabriel.
**/

#ifndef _OML_QUATERNION_H_
#define _OML_QUATERNION_H_

#include "OML_Maths.h"
#include "OML_Matrix3x3.h"

namespace OML
{
	
class OML_Matrix3x3;

/*--------------------------------------------------------------------*/
/*                       class OML_Quaternion                          */
/*--------------------------------------------------------------------*/
/* a quaternion                                                       */
/*--------------------------------------------------------------------*/

/*! \ingroup group_primitive
 *  \brief class OML_Quaternion in group group primitive
 */

/// A quatenion has 4 components, and represent rotation matrix.
/** 
	The quaternion algebra is known to be the only real algebra (with division)
	of finite dimension after the complex plane. 
	This result is due to Frobenius
	\author Gabriel
*/

class OML_Quaternion
{

public:

    /** defaullt constructor */
    OML_Quaternion();
	/** constructor */
    OML_Quaternion(const OML_Float w, const OML_Float x, 
			      const OML_Float y, const OML_Float z);
	/** constructor roll/axe */
	OML_Quaternion(const OML_Float w, const OML_Float axe[3]);
	/** idem */
	OML_Quaternion(OML_Vector3D& axe);
	
	/** reset the quaternion to identity */
	OML_Quaternion& SetIdentity();


    /** quaternion multiplication */
	OML_Quaternion operator*(const OML_Quaternion& b);
	/** quaternion auto-multiplication */
    OML_Quaternion& operator*=(const OML_Quaternion&);
	/** scale */
	OML_Quaternion operator*(OML_Float m);

	/** retrun the opposite */
	OML_Quaternion operator-();
	/** increment */
    OML_Quaternion& operator+=(OML_Quaternion &rhs);
	/** decrement */
    OML_Quaternion& operator-=(OML_Quaternion &rhs);
	/** addition */
    OML_Quaternion operator+(OML_Quaternion &q);
	/** soustraction */
    OML_Quaternion operator-(OML_Quaternion &q);

    /** return the conjugated quaternion */
    OML_Quaternion GetConjugated();
	/** auto conjugate the quaternion */
    OML_Quaternion& AutoConjugate();

    /** return the inverted quaternion */
    OML_Quaternion operator ~();
	/** auto-invert the quaternion */
    OML_Quaternion& operator !();

    /** auto-normalize the quaternion */
    OML_Quaternion& AutoNormalize();
	/** return a normalize quaternion */
	OML_Quaternion GetNormalized();
	/** get the norm of the quaterion */
	OML_Float GetNorm();
	/** get the suare of the norm of the quaterion */
	OML_Float GetSquareNorm();

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	OML_Float	GetX() const;
	OML_Float	GetY() const;
	OML_Float	GetZ() const;
	OML_Float	GetW() const;
	void		SetW(OML_Float rVal);
	void		SetX(OML_Float rVal);
	void		SetY(OML_Float rVal);
	void		SetZ(OML_Float rVal);
    //@}

    //-------------------------------------------------------------------------
    /** \name conversion operations */
    //-------------------------------------------------------------------------
    //@{
	/** build the quaternion given the axis of the rotation and the angle */
    OML_Quaternion& BuildFromAxis(const OML_Float Angle, OML_Float x, OML_Float y, OML_Float z);
	/** build the quaternion given the 3 euler angles */
    OML_Quaternion& BuildFromEuler(const OML_Float Angle, OML_Float x, OML_Float y, OML_Float z);
	/** build the matrix corresponding to the rotation */
    OML_Matrix3x3 ToMatrix();
	void BuildFromMatrix(OML_Matrix3x3& m);

	void ToAxisAndAngle(OML_Vector3D& axis, OML_Float& angle);
    //@}


	/** interpolate on the unity sphere */
    OML_Quaternion Slerp(OML_Quaternion& to, OML_Float t);
	/** interpolate linearly */
    OML_Quaternion Lerp(OML_Quaternion& to, OML_Float t);

    /** return the exponent of a quaternion */
    OML_Quaternion& Exp();
	/** return the logarithm of the quaternion */
    OML_Quaternion& Log();
	
protected:
		
	/** the fourth component of the quaterion */
	OML_Float w, x, y, z;

};


} // namespace OML

#ifdef OML_USE_INLINE
	#include "OML_Quaternion.inl"
#endif
#endif /* #ifndef _OML_QUATERNION_H_ */

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