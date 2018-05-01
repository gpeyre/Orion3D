///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *	OPCODE - Optimized Collision Detection
 *	Copyright (C) 2001 Pierre Terdiman
 *	Homepage: http://www.codercorner.com/Opcode.htm
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for 3D vectors.
 *	\file		OPC_Point.h
 *	\author		Pierre Terdiman
 *	\date		April, 4, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICEPOINT_H__
#define __ICEPOINT_H__

	class Plane;
	class Matrix3x3;
	class Matrix4x4;

	class OPCODE_API Point
	{
		public:

		//! Empty constructor
		__forceinline				Point()														{}
		//! Constructor from floats
		__forceinline				Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z)	{}
		//! Constructor from array
		__forceinline				Point(float f[3]) : x(f[0]), y(f[1]), z(f[2])				{}
		//! Copy constructor
		__forceinline				Point(const Point& p) : x(p.x), y(p.y), z(p.z)				{}
		//! Destructor
		__forceinline				~Point()													{}

		//! Returns MIN(x, y, z);
		__forceinline	float		Min()								const		{ return MIN(x, MIN(y, z));												}
		//! Returns MAX(x, y, z);
		__forceinline	float		Max()								const		{ return MAX(x, MAX(y, z));												}
		//! TO BE DOCUMENTED
		__forceinline	Point&		Min(const Point& p)								{ x = MIN(x, p.x); y = MIN(y, p.y); z = MIN(z, p.z);	return *this;	}
		//! TO BE DOCUMENTED
		__forceinline	Point&		Max(const Point& p)								{ x = MAX(x, p.x); y = MAX(y, p.y); z = MAX(z, p.z);	return *this;	}

		//! Computes square magnitude
		__forceinline	float		SquareMagnitude()					const		{ return x*x + y*y + z*z;												}
		//! Computes magnitude
		__forceinline	float		Magnitude()							const		{ return sqrtf(x*x + y*y + z*z);										}

		//! Return largest axis
		__forceinline	udword		LargestAxis()						const
						{
							const float* Vals = &x;
							udword m = 0;
							if(Vals[1] > Vals[m]) m = 1;
							if(Vals[2] > Vals[m]) m = 2;
							return m;
						}

		// Arithmetic operators
		//! Operator for Point Negate = - Point
		__forceinline	Point		operator-()							const		{ return Point(-x, -y, -z);							}

		//! Operator for Point Plus = Point + Point.
		__forceinline	Point		operator+(const Point& p)			const		{ return Point(x + p.x, y + p.y, z + p.z);			}
		//! Operator for Point Minus = Point - Point.
		__forceinline	Point		operator-(const Point& p)			const		{ return Point(x - p.x, y - p.y, z - p.z);			}
		//! Operator for Point Scale = Point * float.
		__forceinline	Point		operator*(float s)					const		{ return Point(x * s,   y * s,   z * s );			}
		//! Operator for Point Scale = float * Point.
		friend			Point		operator*(float s, const Point& p)				{ return Point(s * p.x, s * p.y, s * p.z);			}
		//! Operator for Point Scale = Point / float.
		__forceinline	Point		operator/(float s)					const		{ s = 1.0f / s; return Point(x * s, y * s, z * s);	}

		//! Operator for float DotProd = Point | Point.
		__forceinline	float		operator|(const Point& p)			const		{ return x*p.x + y*p.y + z*p.z;						}
		//! Operator for Point VecProd = Point ^ Point.
		__forceinline	Point		operator^(const Point& p)			const
						{
							return Point(
							y * p.z - z * p.y,
							z * p.x - x * p.z,
							x * p.y - y * p.x );
						}

		//! Operator for Point += Point.
		__forceinline	Point&		operator+=(const Point& p)						{ x += p.x; y += p.y; z += p.z;	return *this;		}
		//! Operator for Point += float.
		__forceinline	Point&		operator+=(float s)								{ x += s;   y += s;   z += s;	return *this;		}

		//! Operator for Point -= Point.
		__forceinline	Point&		operator-=(const Point& p)						{ x -= p.x; y -= p.y; z -= p.z;	return *this;		}
		//! Operator for Point -= float.
		__forceinline	Point&		operator-=(float s)								{ x -= s;   y -= s;   z -= s;	return *this;		}
		//! Operator for Point *= float.
		__forceinline	Point&		operator*=(float s)								{ x *= s; y *= s; z *= s;		return *this;		}
		//! Operator for Point /= float.
		__forceinline	Point&		operator/=(float s)								{ s = 1.0f/s; x *= s; y *= s; z *= s; return *this; }

		// Arithmetic operators
		//! Operator for Point Mul = Point * Matrix3x3.
						Point		operator*(const Matrix3x3& mat)		const;
		//! Operator for Point Mul = Point * Matrix4x4.
						Point		operator*(const Matrix4x4& mat)		const;
		//! Operator for Point *= Matrix3x3.
						Point&		operator*=(const Matrix3x3& mat);
		//! Operator for Point *= Matrix4x4.
						Point&		operator*=(const Matrix4x4& mat);

		//! Access as array
		__forceinline				operator	const	float*() const	{ return &x; }
		//! Access as array
		__forceinline				operator			float*()		{ return &x; }

		public:
						float		x;		//!< x coordinate
						float		y;		//!< y coordinate
						float		z;		//!< z coordinate
	};

#endif //__ICEPOINT_H__
