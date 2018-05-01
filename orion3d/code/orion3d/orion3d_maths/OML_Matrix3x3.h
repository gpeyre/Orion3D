/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Matrix3x3.h
 *  \brief Definition of class \c OML_Matrix3x3
 *  \author Gabriel Peyré 2001-09-18
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_Matrix3x3_h_
#define __OML_Matrix3x3_h_

#include "OML_Config.h"
#include "OML_VectorND.h"
#include "OML_Maths.h"

namespace OML {

class OML_Quaternion;
class OML_Matrix4x4;
class OML_Vector3D;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_Matrix3x3
 *  \brief  A matrix of variable dimension.
 *  \author Gabriel Peyré 2001-09-18
 *
 *	Note that the matrix is \e row \e major, which is not the case of the 
 *	\c OML_Matrix4x4.
 *	
 *	\code
 *	+-----+-----+.....+-------+
 *  | 0,0 | 0,1 |     | 0,n-1 |
 *	+-----+-----+.....+-------+
 *  | 1,0 | 1,2 |     | 1,n-1 |
 *	+-----+-----+.....+-------+
 *  .     .     . i,j .       . <- i
 *	+-----+-----+.....+-------+
 *  |p-1,0|p-1,1|     |p-1,m-1|
 *	+-----+-----+.....+-------+
 *                 ^
 *                 |
 *                 j
 *  offset = j+i*n
 *	\endcode
 */ 
/*------------------------------------------------------------------------------*/

class OML_Matrix3x3 
{

public:

    //-------------------------------------------------------------------------
    /** \name constructor & destructor */
    //-------------------------------------------------------------------------
    //@{
    OML_Matrix3x3();
	OML_Matrix3x3(
		OML_Float m00, OML_Float m10, OML_Float m20, 
		OML_Float m01, OML_Float m11, OML_Float m21, 
		OML_Float m02, OML_Float m12, OML_Float m22);
	OML_Matrix3x3(const OML_Matrix3x3& m);
	explicit OML_Matrix3x3(const OML_Matrix4x4& m);
	OML_Matrix3x3 &operator = (const OML_Matrix3x3 &m);
	OML_Matrix3x3 &operator = (const OML_Matrix4x4 &m);
    virtual ~OML_Matrix3x3();
    //@}

    //-------------------------------------------------------------------------
    /** \name multiplication methods (both optimised and non-optimised) */
    //-------------------------------------------------------------------------
    //@{
	OML_Matrix3x3 operator*(const OML_Matrix3x3& m) const;
	static void Multiply(const OML_Matrix3x3& a, const OML_Matrix3x3& b, OML_Matrix3x3& r);
	void operator *= (const OML_Matrix3x3 & m);

	OML_Matrix4x4 operator*(const OML_Matrix4x4& m) const;
	static void Multiply(const OML_Matrix3x3& a, const OML_Matrix4x4& b, OML_Matrix4x4& r);
	
	OML_Vector3D operator*(const OML_Vector3D& v) const;
	static void Multiply(const OML_Matrix3x3& a, const OML_Vector3D& v, OML_Vector3D& r);
    //@}

    //-------------------------------------------------------------------------
    /** \name sum */
    //-------------------------------------------------------------------------
    //@{
	OML_Matrix3x3 operator + (const OML_Matrix3x3 & m);
	static void Add(const OML_Matrix3x3& a, const OML_Matrix3x3& b, OML_Matrix3x3& r);
	OML_Matrix3x3 operator - (const OML_Matrix3x3 & m);

	static void Minus(const OML_Matrix3x3& a, const OML_Matrix3x3& b, OML_Matrix3x3& r);
	OML_Matrix3x3 operator - ();

	static void UMinus(const OML_Matrix3x3& a, OML_Matrix3x3& r);
	void operator += (const OML_Matrix3x3 & m);
	void operator -= (const OML_Matrix3x3 & m);
    //@}

	//-------------------------------------------------------------------------
    /** \name scale */
    //-------------------------------------------------------------------------
    //@{
	static void Scale(const OML_Float rScale, const OML_Matrix3x3& a, OML_Matrix3x3& r);
	void AutoScale(OML_Float rFactor);
	OML_Matrix3x3 operator*(OML_Float v) const;
	OML_Matrix3x3 operator/(OML_Float v) const;
	void operator*=(OML_Float v);
	void operator/=(OML_Float v);
    //@}
	
    //-------------------------------------------------------------------------
    /** \name inversion operations */
    //-------------------------------------------------------------------------
    //@{
	/** inverse the matrix */
	OML_Matrix3x3 operator~() const;
	/** auto-inverse the matrix */
	void operator!();
	static void Invert(const OML_Matrix3x3& a, OML_Matrix3x3& r);
	OML_Matrix3x3 Invert() const;
	void AutoInvert();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name rotation operations */
    //-------------------------------------------------------------------------
    //@{
	void RotateX(OML_Float val);
	void RotateY(OML_Float val);
	void RotateZ(OML_Float val);
	
	void Rotate(OML_Coord_XYZW axe, OML_Float val);
	
	void RotateAbsX(OML_Float val);
	void RotateAbsY(OML_Float val);
	void RotateAbsZ(OML_Float val);
	
	void RotateAbs(OML_Coord_XYZW axe, OML_Float val);
    //@}

    //-------------------------------------------------------------------------
    /** \name transposition */
    //-------------------------------------------------------------------------
    //@{
	OML_Matrix3x3 Transpose() const;
	void		 AutoTranspose();
	static void  Transpose(const OML_Matrix3x3& a, OML_Matrix3x3& r);
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OML_Float* GetData() const;
	OML_Float* GetData();
	OML_Float  GetData(OML_I32 i, OML_I32 j) const;
	void      SetData(OML_I32 i, OML_I32 j, OML_Float rVal);
	void	  SetData(OML_Float* aData);
	void	  SetData(
		OML_Float m00, OML_Float m10, OML_Float m20, 
		OML_Float m01, OML_Float m11, OML_Float m21, 
		OML_Float m02, OML_Float m12, OML_Float m22);

	
	OML_Vector3D GetX() const;
	OML_Vector3D GetY() const;
	OML_Vector3D GetZ() const;
	void SetX( const OML_Vector3D& v);
	void SetY( const OML_Vector3D& v);
	void SetZ( const OML_Vector3D& v);
    //@}

    //-------------------------------------------------------------------------
    /** \name conversion */
    //-------------------------------------------------------------------------
    //@{
	void BuildFromQuaternion(OML_Quaternion& q);
    //@}

    //-------------------------------------------------------------------------
    /** \name Utility */
    //-------------------------------------------------------------------------
    //@{
	void SetZero();
	void LoadIdentity();
	void SetValue(OML_Float rVal);
	void Randomize(OML_Float rMin=0, OML_Float rMax=1);
	void Print (char *cFormat = "%10.4f ", FILE *f=stdout);
    //@}

    //-------------------------------------------------------------------------
    /** \name matricial norms */
    //-------------------------------------------------------------------------
    //@{
	OML_Float Norm1();
	OML_Float Norm2();
	OML_Float NormInf();
    //@}

protected:

	/** the matrix datas */
	OML_Float aData_[3][3];

};

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_Matrix3x3.inl"
#endif


#endif // __OML_Matrix3x3_h_

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