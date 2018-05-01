///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *	OPCODE - Optimized Collision Detection
 *	Copyright (C) 2001 Pierre Terdiman
 *	Homepage: http://www.codercorner.com/Opcode.htm
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains AABB-related code. (axis-aligned bounding box)
 *	\file		OPC_AABB.h
 *	\author		Pierre Terdiman
 *	\date		January, 13, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICEAABB_H__
#define __ICEAABB_H__

#define USE_MINMAX		// if defined, use (Min, Max) AABBs, else use (Center, Extents) ones.

//! Declarations of type-independent methods (implemented in the .cpp)
#define AABB_COMMON_METHODS		\
	AABB&	Add(const AABB& aabb);


#ifdef USE_MINMAX

	class OPCODE_API AABB
	{
		public:
		//! Constructor
		__forceinline				AABB()	{}
		//! Destructor
		__forceinline				~AABB()	{}

		//! Type-independent methods
									AABB_COMMON_METHODS;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to setup an AABB from min & max vectors.
		 *	\param		min			[in] the min point
		 *	\param		max			[in] the max point
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						void		SetMinMax(const Point& min, const Point& max)		{ mMin = min;		mMax = max;									}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to setup an AABB from center & extents vectors.
		 *	\param		c			[in] the center point
		 *	\param		e			[in] the extents vector
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						void		SetCenterExtents(const Point& c, const Point& e)	{ mMin = c - e;		mMax = c + e;								}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to setup an empty AABB.
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						void		SetEmpty()											{ Point p(MIN_FLOAT, MIN_FLOAT, MIN_FLOAT);	mMin = -p; mMax = p;}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to get the size of the AABB. The size is defined as the longest extent.
		 *	\return		the size of the AABB
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						float		GetSize()								const		{ Point e; GetExtents(e);	return e.Max();	}

		// Data access

		//! Get min point of the box
		__forceinline	void		GetMin(Point& min)						const		{ min = mMin;								}
		//! Get max point of the box
		__forceinline	void		GetMax(Point& max)						const		{ max = mMax;								}

		//! Get component of the box's min point along a given axis
		__forceinline	float		GetMin(udword axis)						const		{ return mMin[axis];						}
		//! Get component of the box's max point along a given axis
		__forceinline	float		GetMax(udword axis)						const		{ return mMax[axis];						}

		//! Get box center
		__forceinline	void		GetCenter(Point& center)				const		{ center = (mMax + mMin)*0.5f;				}
		//! Get box extents
		__forceinline	void		GetExtents(Point& extents)				const		{ extents = (mMax - mMin)*0.5f;				}

		//! Get component of the box's center along a given axis
		__forceinline	float		GetCenter(udword axis)					const		{ return (mMax[axis] + mMin[axis])*0.5f;	}
		//! Get component of the box's extents along a given axis
		__forceinline	float		GetExtents(udword axis)					const		{ return (mMax[axis] - mMin[axis])*0.5f;	}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to compute the intersection between two AABBs.
		 *	\param		a		[in] the other AABB
		 *	\return		true on intersection
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__forceinline	bool		Intersect(const AABB& a)				const
						{
							if(mMax.x < a.mMin.x
							|| a.mMax.x < mMin.x
							|| mMax.y < a.mMin.y
							|| a.mMax.y < mMin.y
							|| mMax.z < a.mMin.z
							|| a.mMax.z < mMin.z)	return false;

							return true;
						}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to compute the 1D-intersection between two AABBs, on a given axis.
		 *	\param		a		[in] the other AABB
		 *	\param		axis	[in] the axis (0, 1, 2)
		 *	\return		true on intersection
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__forceinline	bool		Intersect(const AABB& a, udword axis)	const
						{
							if(mMax[axis] < a.mMin[axis] || a.mMax[axis] < mMin[axis])	return false;
							return true;
						}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to recompute the AABB after an arbitrary transform by a 4x4 matrix.
		 *	Original code by Charles Bloom on the GD-Algorithm list. (I slightly modified it)
		 *	\param		mtx			[in] the transform matrix
		 *	\param		aabb		[out] the transformed AABB [can be *this]
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__forceinline	void		Rotate(const Matrix4x4& mtx, AABB& aabb)	const
						{
							// The three edges transformed: you can efficiently transform an X-only vector
							// by just getting the "X" column of the matrix
							Point vx,vy,vz;
							mtx.GetRow(0, vx);	vx *= (mMax.x - mMin.x);
							mtx.GetRow(1, vy);	vy *= (mMax.y - mMin.y);
							mtx.GetRow(2, vz);	vz *= (mMax.z - mMin.z);

							// Transform the min point
							aabb.mMin = aabb.mMax = mMin * mtx;

							// Take the transformed min & axes and find new extents
							// Using CPU code in the right place is faster...
							if(IS_NEGATIVE_FLOAT(vx.x))	aabb.mMin.x += vx.x; else aabb.mMax.x += vx.x;
							if(IS_NEGATIVE_FLOAT(vx.y))	aabb.mMin.y += vx.y; else aabb.mMax.y += vx.y;
							if(IS_NEGATIVE_FLOAT(vx.z))	aabb.mMin.z += vx.z; else aabb.mMax.z += vx.z;
							if(IS_NEGATIVE_FLOAT(vy.x))	aabb.mMin.x += vy.x; else aabb.mMax.x += vy.x;
							if(IS_NEGATIVE_FLOAT(vy.y))	aabb.mMin.y += vy.y; else aabb.mMax.y += vy.y;
							if(IS_NEGATIVE_FLOAT(vy.z))	aabb.mMin.z += vy.z; else aabb.mMax.z += vy.z;
							if(IS_NEGATIVE_FLOAT(vz.x))	aabb.mMin.x += vz.x; else aabb.mMax.x += vz.x;
							if(IS_NEGATIVE_FLOAT(vz.y))	aabb.mMin.y += vz.y; else aabb.mMax.y += vz.y;
							if(IS_NEGATIVE_FLOAT(vz.z))	aabb.mMin.z += vz.z; else aabb.mMax.z += vz.z;
						}
		private:
						Point		mMin;			//!< Min point
						Point		mMax;			//!< Max point
	};

#else

	class OPCODE_API AABB
	{
		public:
		//! Constructor
		__forceinline				AABB()	{}
		//! Destructor
		__forceinline				~AABB()	{}

		//! Type-independent methods
									AABB_COMMON_METHODS;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to setup an AABB from min & max vectors.
		 *	\param		min			[in] the min point
		 *	\param		max			[in] the max point
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						void		SetMinMax(const Point& min, const Point& max)		{ mCenter = (max + min)*0.5f; mExtents = (max - min)*0.5f;		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to setup an AABB from center & extents vectors.
		 *	\param		c			[in] the center point
		 *	\param		e			[in] the extents vector
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						void		SetCenterExtents(const Point& c, const Point& e)	{ mCenter = c;	 mExtents = e;									}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to setup an empty AABB.
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						void		SetEmpty()											{ mCenter.Zero(); mExtents.Set(MIN_FLOAT, MIN_FLOAT, MIN_FLOAT);}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to get the size of the AABB. The size is defined as the longest extent.
		 *	\return		the size of the AABB
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						float		GetSize()								const		{ return mExtents.Max();					}

		// Data access

		//! Get min point of the box
		__forceinline	void		GetMin(Point& min)						const		{ min = mCenter - mExtents;					}
		//! Get max point of the box
		__forceinline	void		GetMax(Point& max)						const		{ max = mCenter + mExtents;					}

		//! Get component of the box's min point along a given axis
		__forceinline	float		GetMin(udword axis)						const		{ return mCenter[axis] - mExtents[axis];	}
		//! Get component of the box's max point along a given axis
		__forceinline	float		GetMax(udword axis)						const		{ return mCenter[axis] + mExtents[axis];	}

		//! Get box center
		__forceinline	void		GetCenter(Point& center)				const		{ center = mCenter;							}
		//! Get box extents
		__forceinline	void		GetExtents(Point& extents)				const		{ extents = mExtents;						}

		//! Get component of the box's center along a given axis
		__forceinline	float		GetCenter(udword axis)					const		{ return mCenter[axis];						}
		//! Get component of the box's extents along a given axis
		__forceinline	float		GetExtents(udword axis)					const		{ return mExtents[axis];					}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to compute the intersection between two AABBs.
		 *	\param		a		[in] the other AABB
		 *	\return		true on intersection
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__forceinline	bool		Intersect(const AABB& a)				const
						{
							float tx = mCenter.x - a.mCenter.x;	float ex = a.mExtents.x + mExtents.x;	if(AIR(tx) > IR(ex))	return false;
							float ty = mCenter.y - a.mCenter.y;	float ey = a.mExtents.y + mExtents.y;	if(AIR(ty) > IR(ey))	return false;
							float tz = mCenter.z - a.mCenter.z;	float ez = a.mExtents.z + mExtents.z;	if(AIR(tz) > IR(ez))	return false;
							return true;
						}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	The standard intersection method from Gamasutra. Just here to check its speed against the one above.
		 *	\param		a		[in] the other AABB
		 *	\return		true on intersection
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__forceinline	bool		GomezIntersect(const AABB& a)
						{
							Point	T = mCenter - a.mCenter;	// Vector from A to B
							return	((fabsf(T.x) <= (a.mExtents.x + mExtents.x))
									&& (fabsf(T.y) <= (a.mExtents.y + mExtents.y))
									&& (fabsf(T.z) <= (a.mExtents.z + mExtents.z)));
						}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to compute the 1D-intersection between two AABBs, on a given axis.
		 *	\param		a		[in] the other AABB
		 *	\param		axis	[in] the axis (0, 1, 2)
		 *	\return		true on intersection
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__forceinline	bool		Intersect(const AABB& a, udword axis)	const
						{
							float t = mCenter[axis] - a.mCenter[axis];
							float e = a.mExtents[axis] + mExtents[axis];
							if(AIR(t) > IR(e))	return false;
							return true;
						}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	A method to recompute the AABB after an arbitrary transform by a 4x4 matrix.
		 *	\param		mtx			[in] the transform matrix
		 *	\param		aabb		[out] the transformed AABB [can be *this]
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__forceinline	void		Rotate(const Matrix4x4& mtx, AABB& aabb)	const
						{
							// Compute new center
							aabb.mCenter = mCenter * mtx;

							// Compute new extents. FPU code & CPU code have been interleaved for improved performance.
							Point Ex(mtx.m[0][0] * mExtents.x, mtx.m[0][1] * mExtents.x, mtx.m[0][2] * mExtents.x);
							IR(Ex.x)&=0x7fffffff;	IR(Ex.y)&=0x7fffffff;	IR(Ex.z)&=0x7fffffff;

							Point Ey(mtx.m[1][0] * mExtents.y, mtx.m[1][1] * mExtents.y, mtx.m[1][2] * mExtents.y);
							IR(Ey.x)&=0x7fffffff;	IR(Ey.y)&=0x7fffffff;	IR(Ey.z)&=0x7fffffff;

							Point Ez(mtx.m[2][0] * mExtents.z, mtx.m[2][1] * mExtents.z, mtx.m[2][2] * mExtents.z);
							IR(Ez.x)&=0x7fffffff;	IR(Ez.y)&=0x7fffffff;	IR(Ez.z)&=0x7fffffff;

							aabb.mExtents.x = Ex.x + Ey.x + Ez.x;
							aabb.mExtents.y = Ex.y + Ey.y + Ez.y;
							aabb.mExtents.z = Ex.z + Ey.z + Ez.z;
						}
		private:
						Point		mCenter;			//!< AABB Center
						Point		mExtents;			//!< x, y and z extents
	};

#endif

#endif	// __ICEAABB_H__
