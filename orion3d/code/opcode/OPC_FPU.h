///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *	OPCODE - Optimized Collision Detection
 *	Copyright (C) 2001 Pierre Terdiman
 *	Homepage: http://www.codercorner.com/Opcode.htm
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains FPU related code.
 *	\file		OPC_FPU.h
 *	\author		Pierre Terdiman
 *	\date		April, 4, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef __ICEFPU_H__
#define __ICEFPU_H__

	#define	SIGN_BITMASK			0x80000000

	//! Integer representation of a floating-point value.
	#define IR(x)					((udword&)(x))

	//! Absolute integer representation of a floating-point value
	#define AIR(x)					(IR(x)&0x7fffffff)

	//! Floating-point representation of an integer value.
	#define FR(x)					((float&)(x))

	//! Integer-based comparison of a floating point value.
	//! Don't use it blindly, it can be faster or slower than the FPU comparison, depends on the context.
	#define IS_NEGATIVE_FLOAT(x)	(IR(x)&0x80000000)

	#define FCOMI_ST0	_asm	_emit	0xdb	_asm	_emit	0xf0
	#define FCOMIP_ST0	_asm	_emit	0xdf	_asm	_emit	0xf0
	#define FCMOVB_ST0	_asm	_emit	0xda	_asm	_emit	0xc0
	#define FCMOVNB_ST0	_asm	_emit	0xdb	_asm	_emit	0xc0

	#define FCOMI_ST1	_asm	_emit	0xdb	_asm	_emit	0xf1
	#define FCOMIP_ST1	_asm	_emit	0xdf	_asm	_emit	0xf1
	#define FCMOVB_ST1	_asm	_emit	0xda	_asm	_emit	0xc1
	#define FCMOVNB_ST1	_asm	_emit	0xdb	_asm	_emit	0xc1

	#define FCOMI_ST2	_asm	_emit	0xdb	_asm	_emit	0xf2
	#define FCOMIP_ST2	_asm	_emit	0xdf	_asm	_emit	0xf2
	#define FCMOVB_ST2	_asm	_emit	0xda	_asm	_emit	0xc2
	#define FCMOVNB_ST2	_asm	_emit	0xdb	_asm	_emit	0xc2

	//! A global function to find MAX(a,b,c) using FCOMI/FCMOV
	__forceinline float FCMax3(float a, float b, float c)
	{
		float Res;
		_asm	fld		[a]
		_asm	fld		[b]
		_asm	fld		[c]
		FCOMI_ST1
		FCMOVB_ST1
		FCOMI_ST2
		FCMOVB_ST2
		_asm	fstp	[Res]
		_asm	fcompp
		return Res;
	}

	//! A global function to find MIN(a,b,c) using FCOMI/FCMOV
	__forceinline float FCMin3(float a, float b, float c)
	{
		float Res;
		_asm	fld		[a]
		_asm	fld		[b]
		_asm	fld		[c]
		FCOMI_ST1
		FCMOVNB_ST1
		FCOMI_ST2
		FCMOVNB_ST2
		_asm	fstp	[Res]
		_asm	fcompp
		return Res;
	}

#endif // __ICEFPU_H__
