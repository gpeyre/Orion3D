/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Matrix4x4.inl
 *  \brief Inline methods for OML_Matrix4x4
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_Matrix4x4.h"

namespace OML {
	
/** 
	i=column number
    j=row number 
	So we access Matrix[i][j]
*/
#define ACCESS_MATRIX(i,j) j+4*(i)

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::~
 *
 *  \return The inverse of the matrix.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	Compute the inverse the matrix, assuming that it's an orthogonal matrix.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix4x4 OML_Matrix4x4::operator~() const
{
	/* the inverse translation : -A^(-1)*t
		+--------+ +--+
		|00 01 02| |30|	
	   -|10 11 12|*|31|
		|20 21 22| |32|
		+--------+ +--+
	*/
	OML_Float t0=Matrix[0][0]*Matrix[3][0]+Matrix[0][1]*Matrix[3][1]+Matrix[0][2]*Matrix[3][2];
	OML_Float t1=Matrix[1][0]*Matrix[3][0]+Matrix[1][1]*Matrix[3][1]+Matrix[1][2]*Matrix[3][2];
	OML_Float t2=Matrix[2][0]*Matrix[3][0]+Matrix[2][1]*Matrix[3][1]+Matrix[2][2]*Matrix[3][2];
	/* the matrix is supposed to be orthogonal !!!!! */
	return OML_Matrix4x4(
		Matrix[0][0], Matrix[0][1], Matrix[0][2], -t0, 
		Matrix[1][0], Matrix[1][1], Matrix[1][2], -t1, 
		Matrix[2][0], Matrix[2][1], Matrix[2][2], -t2, 
		Matrix[0][3], Matrix[1][3], Matrix[2][3],  Matrix[3][3]);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::*
 *
 *  \return The product of the 2 matrix.
 *	\param  v The right side operand.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	Compute the product of the two matrix.
 *	\todo launch an exception if the matrix is singular.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix4x4 OML_Matrix4x4::operator*( const OML_Matrix4x4& v) const
{
	/*
	matrix[i][j]=Matrix[i][0]*v[0][j]+Matrix[i][1]*v[1][j]+
	Matrix[i][2]*v[2][j]+Matrix[i][3]*v[3][j];
	*/
	OML_Float matrix[4][4];
	OML_Float* mat2 = v.GetCoords();
	for (OML_I32 i=0; i<4; i++)
	for (OML_I32 j=0; j<4; j++)
		matrix[i][j]=Matrix[i][0]*mat2[ACCESS_MATRIX(0,j)]+Matrix[i][1]*mat2[ACCESS_MATRIX(1,j)]+
					 Matrix[i][2]*mat2[ACCESS_MATRIX(2,j)]+Matrix[i][3]*mat2[ACCESS_MATRIX(3,j)];
	return OML_Matrix4x4(&matrix[0][0]);
}


/*------------------------------------------------------------------------------
 * Name : OML_Matrix4x4::operator
 *
 *  \param  v right hand statement.
 *  \return sum of the two matrix.
 *  \author Antoine Bouthors 2001-10-06
 *------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix4x4 OML_Matrix4x4::operator+( const OML_Matrix4x4 &v) const
{
	return OML_Matrix4x4(	Matrix[0][0] + v.Matrix[0][0], Matrix[1][0] + v.Matrix[1][0], Matrix[2][0] + v.Matrix[2][0], Matrix[3][0] + v.Matrix[3][0],
							Matrix[0][1] + v.Matrix[0][1], Matrix[1][1] + v.Matrix[1][1], Matrix[2][1] + v.Matrix[2][1], Matrix[3][1] + v.Matrix[3][1],
							Matrix[0][2] + v.Matrix[0][2], Matrix[1][2] + v.Matrix[1][2], Matrix[2][2] + v.Matrix[2][2], Matrix[3][2] + v.Matrix[3][2],
							Matrix[0][3] + v.Matrix[0][3], Matrix[1][3] + v.Matrix[1][3], Matrix[2][3] + v.Matrix[2][3], Matrix[3][3] + v.Matrix[3][3] );
}



/*------------------------------------------------------------------------------
 * Name : OML_Matrix4x4::operator
 *
 *  \param  v right hand statement.
 *  \return dif of the two matrix.
 *  \author Antoine Bouthors 2001-10-06
 *------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix4x4 OML_Matrix4x4::operator-( const OML_Matrix4x4 &v ) const
{
	return OML_Matrix4x4(	Matrix[0][0] - v.Matrix[0][0], Matrix[1][0] - v.Matrix[1][0], Matrix[2][0] - v.Matrix[2][0], Matrix[3][0] - v.Matrix[3][0],
							Matrix[0][1] - v.Matrix[0][1], Matrix[1][1] - v.Matrix[1][1], Matrix[2][1] - v.Matrix[2][1], Matrix[3][1] - v.Matrix[3][1],
							Matrix[0][2] - v.Matrix[0][2], Matrix[1][2] - v.Matrix[1][2], Matrix[2][2] - v.Matrix[2][2], Matrix[3][2] - v.Matrix[3][2],
							Matrix[0][3] - v.Matrix[0][3], Matrix[1][3] - v.Matrix[1][3], Matrix[2][3] - v.Matrix[2][3], Matrix[3][3] - v.Matrix[3][3] );

}



/*------------------------------------------------------------------------------
 * Name : OML_Matrix4x4::operator
 *
 *  \param  v right hand statement.
 *  \author Antoine Bouthors 2001-10-06
 *
 *------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix4x4::operator+=( const OML_Matrix4x4 &v )
{
	Matrix[0][0] += v.Matrix[0][0]; Matrix[1][0] += v.Matrix[1][0]; Matrix[2][0] += v.Matrix[2][0]; Matrix[3][0] += v.Matrix[3][0];
	Matrix[0][1] += v.Matrix[0][1]; Matrix[1][1] += v.Matrix[1][1]; Matrix[2][1] += v.Matrix[2][1]; Matrix[3][1] += v.Matrix[3][1];
	Matrix[0][2] += v.Matrix[0][2]; Matrix[1][2] += v.Matrix[1][2]; Matrix[2][2] += v.Matrix[2][2]; Matrix[3][2] += v.Matrix[3][2];
	Matrix[0][3] += v.Matrix[0][3]; Matrix[1][3] += v.Matrix[1][3]; Matrix[2][3] += v.Matrix[2][3]; Matrix[3][3] += v.Matrix[3][3];
}


/*------------------------------------------------------------------------------
 * Name : OML_Matrix4x4::operator
 *
 *  \param  v right hand statement.
 *  \author Antoine Bouthors 2001-10-06
 *------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix4x4::operator-=( const OML_Matrix4x4 &v )
{
	Matrix[0][0] -= v.Matrix[0][0]; Matrix[1][0] -= v.Matrix[1][0]; Matrix[2][0] -= v.Matrix[2][0]; Matrix[3][0] -= v.Matrix[3][0];
	Matrix[0][1] -= v.Matrix[0][1]; Matrix[1][1] -= v.Matrix[1][1]; Matrix[2][1] -= v.Matrix[2][1]; Matrix[3][1] -= v.Matrix[3][1];
	Matrix[0][2] -= v.Matrix[0][2]; Matrix[1][2] -= v.Matrix[1][2]; Matrix[2][2] -= v.Matrix[2][2]; Matrix[3][2] -= v.Matrix[3][2];
	Matrix[0][3] -= v.Matrix[0][3]; Matrix[1][3] -= v.Matrix[1][3]; Matrix[2][3] -= v.Matrix[2][3]; Matrix[3][3] -= v.Matrix[3][3];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::*
 *
 *  \return The rotation part of the matrix.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	Compute a matrix without the translation (last column).
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3 OML_Matrix4x4::GetRotation()
{
	return OML_Matrix3x3(*this);
}


//-----------------------------------------------------------------------------
// Name: OML_Matrix4x4::GetCoords
/**
*   @return a pointer on the datas of the matrix
*/
///	\author Gabriel Peyré 2001-08-30
//-----------------------------------------------------------------------------
OML_INLINE
OML_Float* OML_Matrix4x4::GetCoords() const
{
	return (OML_Float*) Matrix;
}


//-----------------------------------------------------------------------------
// Name: OML_Matrix4x4::SetCoords
/**
*	Set the different elements of the matrix.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OML_INLINE
void OML_Matrix4x4::SetCoords(
			   OML_Float m00, OML_Float m10, OML_Float m20, OML_Float m30, 
			   OML_Float m01, OML_Float m11, OML_Float m21, OML_Float m31, 
			   OML_Float m02, OML_Float m12, OML_Float m22, OML_Float m32, 
			   OML_Float m03, OML_Float m13, OML_Float m23, OML_Float m33)
{
	Matrix[0][0]=m00; Matrix[0][1]=m01; Matrix[0][2]=m02; Matrix[0][3]=m03;
	Matrix[1][0]=m10; Matrix[1][1]=m11; Matrix[1][2]=m12; Matrix[1][3]=m13;
	Matrix[2][0]=m20; Matrix[2][1]=m21;	Matrix[2][2]=m22; Matrix[2][3]=m23;
	Matrix[3][0]=m30; Matrix[3][1]=m31; Matrix[3][2]=m32; Matrix[3][3]=m33;
}


/*------------------------------------------------------------------------------
 * Name : OML_Matrix4x4::SetCoords
 *
 *  \param  m Coords array in the order m00,m01,m02,m03,m10... 
	\note : order different from the other SetCoords() function
 *  \author Antoine Bouthors 2001-10-09
 *
 *------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix4x4::SetCoords( const OML_Float* m )
{
	memcpy( Matrix, m, 16*sizeof( OML_Float ) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::SetScale
 *
 *  \param  rScale the new scale value.
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix4x4::SetScale(OML_Float rScale)
{
	OML_ASSERT( rScale>OML_EPSILON );
	Matrix[3][3] = rScale;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::TransformOnZ
 *
 *  \param  x X component of the orginal vector.
 *  \param  y Y component of the orginal vector.
 *  \param  z Z component of the orginal vector.
 *  \return The X coordinate of the oringal vector tranformed by the matrix.
 *  \author Gabriel Peyré 2001-10-30
 *
 *	This speed up computation when you only needs depth information (used by 
 *	the alpha pipeline).
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Matrix4x4::TransformOnZ(OML_Float x, OML_Float y, OML_Float z)
{ 
	return Matrix[0][2]*x + Matrix[1][2]*y + Matrix[2][2]*z + Matrix[3][2]; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::TransformOnZ
 *
 *  \param  v the orginal vector.
 *  \return The X coordinate of the oringal vector tranformed by the matrix.
 *  \author Gabriel Peyré 2001-10-30
 *
 *	This speed up computation when you only needs depth information (used by 
 *	the alpha pipeline).
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Matrix4x4::TransformOnZ(OML_Vector3D& v)
{
	return Matrix[0][2]*v[X] + Matrix[1][2]*v[Y] + Matrix[2][2]*v[Z] + Matrix[3][2]; 
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::GetData
 *
 *  \param  i line number.
 *  \param  j column number.
 *  \return data at position (i,j) in the matrix.
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Watch out that data are placed in memory in REVERSE oreder (COLUMN major).
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Matrix4x4::GetData(OML_U32 i, OML_U32 j) const
{
	OML_ASSERT( i<4 && j<4 );
	return Matrix[j][i];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::SetData
 *
 *  \param  i line number.
 *  \param  j column number.
 *  \param  v data to put at position (i,j) in the matrix.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix4x4::SetData(OML_U32 i, OML_U32 j, OML_Float v)
{
	OML_ASSERT( i<4 && j<4 );
	Matrix[j][i] = v;
}

#undef ACCESS_MATRIX


} // End namespace OML

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

