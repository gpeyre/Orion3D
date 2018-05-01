///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *	OPCODE - Optimized Collision Detection
 *	Copyright (C) 2001 Pierre Terdiman
 *	Homepage: http://www.codercorner.com/Opcode.htm
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for 4x4 matrices.
 *	\file		OPC_Matrix4x4.h
 *	\author		Pierre Terdiman
 *	\date		April, 4, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICEMATRIX4X4_H__
#define __ICEMATRIX4X4_H__

	class OPCODE_API Matrix4x4
	{
		public:
		//! Empty constructor.
		__forceinline				Matrix4x4()									{}
		//! Constructor from 16 values
		__forceinline				Matrix4x4(	float m00, float m01, float m02, float m03,
												float m10, float m11, float m12, float m13,
												float m20, float m21, float m22, float m23,
												float m30, float m31, float m32, float m33)
									{
										m[0][0] = m00;	m[0][1] = m01;	m[0][2] = m02;	m[0][3] = m03;
										m[1][0] = m10;	m[1][1] = m11;	m[1][2] = m12;	m[1][3] = m13;
										m[2][0] = m20;	m[2][1] = m21;	m[2][2] = m22;	m[2][3] = m23;
										m[3][0] = m30;	m[3][1] = m31;	m[3][2] = m32;	m[3][3] = m33;
									}
		//! Copy constructor
		__forceinline				Matrix4x4(const Matrix4x4& mat)				{ CopyMemory(m, &mat.m, 16*sizeof(float));	}
		//! Destructor.
		__forceinline				~Matrix4x4()								{}

		//! Gets the translation part of the matrix
		__forceinline	const Matrix4x4&	GetTrans(Point& p)			const	{ p.x = m[3][0];	p.y = m[3][1];	p.z = m[3][2];	return *this;		}
		//! Sets the translation part of the matrix, from a Point.
		__forceinline	Matrix4x4&	SetTrans(const Point& p)					{ m[3][0] = p.x;	m[3][1] = p.y;	m[3][2] = p.z;	return *this;		}
		//! Sets the translation part of the matrix, from floats.
		__forceinline	Matrix4x4&	SetTrans(float tx, float ty, float tz)		{ m[3][0] = tx;		m[3][1] = ty;	m[3][2] = tz;	return *this;		}

		// Row-column access
		//! Returns a row.
		__forceinline	void		GetRow(const udword r, Point& p)	const	{ p.x = m[r][0];	p.y = m[r][1];	p.z = m[r][2];						}
		//! Sets a row.
		__forceinline	void		SetRow(const udword r, const Point& p)		{ m[r][0] = p.x;	m[r][1] = p.y;	m[r][2] = p.z;	m[r][3] = (r!=3) ? 0.0f : 1.0f;		}
		//! Returns a column.
		__forceinline	void		GetCol(const udword c, Point& p)	const	{ p.x = m[0][c];	p.y = m[1][c];	p.z = m[2][c];							}
		//! Sets a column.
		__forceinline	void		SetCol(const udword c, const Point& p)		{ m[0][c] = p.x;	m[1][c] = p.y;	m[2][c] = p.z;	m[3][c] = (c!=3) ? 0.0f : 1.0f;	}

		//! Clear the matrix.
		__forceinline	Matrix4x4&	Zero()										{ ZeroMemory(&m,  sizeof(m));	return *this;							}
		//! Set the identity matrix.
		__forceinline	Matrix4x4&	Identity()									{ Zero(); m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f; return *this;	}

		// Cast operators
		//! Cast a Matrix4x4 to a Matrix3x3.
		__forceinline	operator Matrix3x3()	const
						{
							return Matrix3x3(
							m[0][0],	m[0][1],	m[0][2],
							m[1][0],	m[1][1],	m[1][2],
							m[2][0],	m[2][1],	m[2][2]);
						}

		//! Operator for Matrix4x4 Mul = Matrix4x4 * Matrix4x4;
		__forceinline	Matrix4x4	operator*(const Matrix4x4& mat)	const
						{
							return Matrix4x4(
							m[0][0]*mat.m[0][0] + m[0][1]*mat.m[1][0] + m[0][2]*mat.m[2][0] + m[0][3]*mat.m[3][0],
							m[0][0]*mat.m[0][1] + m[0][1]*mat.m[1][1] + m[0][2]*mat.m[2][1] + m[0][3]*mat.m[3][1],
							m[0][0]*mat.m[0][2] + m[0][1]*mat.m[1][2] + m[0][2]*mat.m[2][2] + m[0][3]*mat.m[3][2],
							m[0][0]*mat.m[0][3] + m[0][1]*mat.m[1][3] + m[0][2]*mat.m[2][3] + m[0][3]*mat.m[3][3],

							m[1][0]*mat.m[0][0] + m[1][1]*mat.m[1][0] + m[1][2]*mat.m[2][0] + m[1][3]*mat.m[3][0],
							m[1][0]*mat.m[0][1] + m[1][1]*mat.m[1][1] + m[1][2]*mat.m[2][1] + m[1][3]*mat.m[3][1],
							m[1][0]*mat.m[0][2] + m[1][1]*mat.m[1][2] + m[1][2]*mat.m[2][2] + m[1][3]*mat.m[3][2],
							m[1][0]*mat.m[0][3] + m[1][1]*mat.m[1][3] + m[1][2]*mat.m[2][3] + m[1][3]*mat.m[3][3],

							m[2][0]*mat.m[0][0] + m[2][1]*mat.m[1][0] + m[2][2]*mat.m[2][0] + m[2][3]*mat.m[3][0],
							m[2][0]*mat.m[0][1] + m[2][1]*mat.m[1][1] + m[2][2]*mat.m[2][1] + m[2][3]*mat.m[3][1],
							m[2][0]*mat.m[0][2] + m[2][1]*mat.m[1][2] + m[2][2]*mat.m[2][2] + m[2][3]*mat.m[3][2],
							m[2][0]*mat.m[0][3] + m[2][1]*mat.m[1][3] + m[2][2]*mat.m[2][3] + m[2][3]*mat.m[3][3],

							m[3][0]*mat.m[0][0] + m[3][1]*mat.m[1][0] + m[3][2]*mat.m[2][0] + m[3][3]*mat.m[3][0],
							m[3][0]*mat.m[0][1] + m[3][1]*mat.m[1][1] + m[3][2]*mat.m[2][1] + m[3][3]*mat.m[3][1],
							m[3][0]*mat.m[0][2] + m[3][1]*mat.m[1][2] + m[3][2]*mat.m[2][2] + m[3][3]*mat.m[3][2],
							m[3][0]*mat.m[0][3] + m[3][1]*mat.m[1][3] + m[3][2]*mat.m[2][3] + m[3][3]*mat.m[3][3]);
						}

		public:

						float		m[4][4];		//!< Array of 16 floats
	};

	OPCODE_API void InvertPRMatrix(Matrix4x4& dest, const Matrix4x4& src);

#endif // __ICEMATRIX4X4_H__

