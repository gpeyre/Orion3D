
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Matrix4x4.h
 *  \brief definition of class \c OML_Matrix4x4
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_Matrix4x4_h_
#define __OML_Matrix4x4_h_

#include "OML_Config.h"
#include "OML_Maths.h"
#include "OML_Vector3D.h"

namespace OML {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_Matrix4x4
 *  \brief  a 4x4 matrix 
 *  \author Gabriel Peyré 2001-08-04
 *  
 *	A 4x4 transformation matrix.
 *	\attention The matrix is supposed to be orthogonal for ~ inversion operator.
 *
 *	Note on OpenGL matrix :
 *	\code
 *
 *	(i,j)=Matrix[i][j]
 *
 *	                 +-----+
 *	(0,0) (1,0) (2,0)|(3,0)|
 *	                 |     |
 *	(0,1) (1,1) (2,1)|(3,1)|------> translation value
 *	                 |     |
 *	(0,2) (1,2) (2,2)|(3,2)|
 *	                 +-----+
 *	(0,3) (1,3) (2,3)|(3,3)|------> should be one
 *
 *	\endcode
 *
 *	Important note : Matrix4x4 are COLUMN major like \b opengl one.
 *
 *	It means that they are packed in memory this way :
 *
 *	\code
 *  +--------------------+-------------+-------------+-------------+
 *  |(0,0)(0,1)(0,2)(0,3)|(1,0)...(1,3)|(2,0)...(2,3)|(3,0)...(3,3)|
 *  +--------------------+-------------+-------------+-------------+
 *  | column 0           | column 1    | column 2    | column 3    |
 *  +--------------------+-------------+-------------+-------------+
 *	\endcode
 *
 *	So to acces a data at position (row,col), we use Matrix[row+col*4]
 */ 
/*------------------------------------------------------------------------------*/

class OML_Matrix4x4
{

public:
	
	//-------------------------------------------------------------------------
    /** @name constructor */
    //-------------------------------------------------------------------------
    //@{
	/** Base constructor. Initialize to identity  */
	OML_Matrix4x4();
	/** Initialize the matrix from pointer. */
	OML_Matrix4x4(const OML_Float* c);
	OML_Matrix4x4(const OML_Matrix4x4& matrix);
	OML_Matrix4x4& operator =(const OML_Matrix4x4& matrix);
	/** Initialize the matrix from value. */
	OML_Matrix4x4(
		OML_Float m00, OML_Float m10, OML_Float m20, OML_Float m30, 
		OML_Float m01, OML_Float m11, OML_Float m21, OML_Float m31, 
		OML_Float m02, OML_Float m12, OML_Float m22, OML_Float m32, 
		OML_Float m03, OML_Float m13, OML_Float m23, OML_Float m33);
    //@}

    //-------------------------------------------------------------------------
    /** \name translation operations */
    //-------------------------------------------------------------------------
    //@{
	/** Translate positivly */
	OML_Matrix4x4 operator+( const OML_Vector3D& v ) const;
	/** Translate negativly */
	OML_Matrix4x4 operator-( const OML_Vector3D& v ) const;
	/** Auto-Translate positivly */
	void operator+=( const OML_Vector3D& v );
	/** Auto-Translate negativly */
	void operator-=( const OML_Vector3D& v );
	/** synonymous with += */
	void Translate( const OML_Vector3D& v );
	/** translate on 1 axe */
	void Translate(OML_U32 axe, OML_Float v);
    //@}

    //-------------------------------------------------------------------------
    /** \name scaling operations */
    //-------------------------------------------------------------------------
    //@{
	/** Scale positivly */
	OML_Matrix4x4 operator*(OML_Float v) const;
	/** Scale negativly */
	OML_Matrix4x4 operator/(OML_Float v) const;
	/** Auto-scale positivly */
	void operator*=(OML_Float v);
	/** Auto-scale negativly */
	void operator/=(OML_Float v);
    //@}

    //-------------------------------------------------------------------------
    /** \name inversion operations */
    //-------------------------------------------------------------------------
    //@{
	/** inverse the matrix */
	OML_Matrix4x4 operator~() const;
	/** auto-inverse the matrix */
	void operator!();
	OML_Matrix4x4 Invert() const;
    //@}

	//-------------------------------------------------------------------------
    /** \name transposition methods */
    //-------------------------------------------------------------------------
    //@{
	OML_Matrix4x4  Transpose() const;
	OML_Matrix4x4& AutoTranspose();
    //@}

    //-------------------------------------------------------------------------
    /** \name addition operations */
    //-------------------------------------------------------------------------
    //@{
	/** Add the 2 matrix */
	OML_Matrix4x4 operator+( const OML_Matrix4x4 &v ) const;
	/** Substract the 2 matrix */
	OML_Matrix4x4 operator-( const OML_Matrix4x4 &v ) const;
	/** Auto-add */
	void operator+=( const OML_Matrix4x4 &v );
	/** Auto-substract */
	void operator-=( const OML_Matrix4x4 &v );
    //@}

    //-------------------------------------------------------------------------
    /** \name multiplications operations */
    //-------------------------------------------------------------------------
    //@{
	/** Multiply the 2 matrix */
	OML_Matrix4x4 operator*( const OML_Matrix4x4& v ) const;
	/** Divide the 2 matrix */
	OML_Matrix4x4 operator/( const OML_Matrix4x4& v) const;
	/** Auto-multiply */
	void operator*=( const OML_Matrix4x4& v );
	/** Auto-divide */
	void operator/=( const OML_Matrix4x4& v );
	/** transform a vector */
	OML_Vector3D operator*( const OML_Vector3D& v );

	/** get the Z component of a tranformed vector */
	OML_Float TransformOnZ(OML_Float x, OML_Float y, OML_Float z);
	OML_Float TransformOnZ(OML_Vector3D& v);
    //@}

    //-------------------------------------------------------------------------
    /** \name rotation operations */
    //-------------------------------------------------------------------------
    //@{
	/** rotate on its own X axis */
	void RotateX(OML_Float val);
	/** rotate on its own Y axis */
	void RotateY(OML_Float val);
	/** rotate on its own Z axis */
	void RotateZ(OML_Float val);
	/** Rotate on a own given axis */
	void Rotate(OML_U32 axe, OML_Float val);
	/** rotate on world X axis */
	void RotateAbsX(OML_Float val);
	/** rotate on world Y axis */
	void RotateAbsY(OML_Float val);
	/** rotate on world Z axis */
	void RotateAbsZ(OML_Float val);
	/** Rotate on a world given axis */
	void RotateAbs(OML_U32 axe, OML_Float val);
    //@}

    //-------------------------------------------------------------------------
    /** \name scale operations */
    //-------------------------------------------------------------------------
    //@{
	void AutoScaleTranslation(OML_Float v);
	/** normalize the transfo matrix 
		\todo Toche rename it AutoUnscale */
	void UnScale();
	/** scale tge matrix */
	void AutoScale( const OML_Vector3D& v);
	/** scale on one axe */
	void AutoScale(OML_U32 axe, OML_Float v);
	void AutoScale(OML_Float rVal);

	OML_Matrix4x4 Scale(OML_Float rVal);
    //@}
	
    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	/** return the rotation matrix */
	OML_Matrix3x3 GetRotation();
	
	/** get X image axis */
	OML_Vector3D GetX() const;
	/** get Y image axis */
	OML_Vector3D GetY() const;
	/** get Z image axis */
	OML_Vector3D GetZ() const;
	/** set X image axis */
	void SetX( const OML_Vector3D& v);
	/** set Y image axis */
	void SetY( const OML_Vector3D& v);
	/** set Z image axis */
	void SetZ( const OML_Vector3D& v);

	/** return a pointer on the coordinates */
	OML_Float* GetData() const;
	/** same */
	OML_Float* GetCoords() const;

	OML_Float GetData(OML_U32 i, OML_U32 j) const;
	void     SetData(OML_U32 i, OML_U32 j, OML_Float v);

	/** set the translation value */
	void SetTranslation( const OML_Vector3D& v);
	/** set the translation value, on one axe */
	void SetTranslation(OML_Coord_XYZW axe, OML_Float v);
	/** set the scale value */
	void SetScale( const OML_Vector3D& v);
	/** set the scale value, on one axe */
	void SetScale(OML_Coord_XYZW axe, OML_Float v);
	void SetScale(OML_Float rScale);
	/** set the rotation part of the matrix */
	void SetRotation( const OML_Matrix3x3& m);
	/** get the translation vector */
	OML_Vector3D GetTranslation();
	/** get the translation vector */
	OML_Float* GetTranslationPtr();
	/** get a colum */
	OML_Vector3D operator[](OML_U32 i) const;
	//@}

    //-------------------------------------------------------------------------
    /** \name re-orthogonalisation methods */
    //-------------------------------------------------------------------------
    //@{
	/** to recompute an orthogonal matrix given a new vector X */
	void ReComputeBasis_GivenX( OML_Vector3D v);
	/** to recompute an orthogonal matrix given a new vector X */
	void ReComputeBasis_GivenY( OML_Vector3D v);
	/** to recompute an orthogonal matrix given a new vector X */
	void ReComputeBasis_GivenZ( OML_Vector3D v);
    //@}

	//-------------------------------------------------------------------------
    /** \name initialisation */
    //-------------------------------------------------------------------------
    //@{
	/** initialize the matrix to identity */
	void SetZero();
	void LoadIdentity();
	void SetCoords(
		OML_Float m00, OML_Float m10, OML_Float m20, OML_Float m30, 
		OML_Float m01, OML_Float m11, OML_Float m21, OML_Float m31, 
		OML_Float m02, OML_Float m12, OML_Float m22, OML_Float m32, 
		OML_Float m03, OML_Float m13, OML_Float m23, OML_Float m33);
	void SetCoords( const OML_Float* m );
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

	/** the data of the matrix */
	OML_Float Matrix[4][4];

};

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_Matrix4x4.inl"
#endif


#endif // __OML_Matrix4x4_h_

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
