
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Config.h
 *  \brief main config file.
 *  \authOML Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_Config_h_
#define __OML_Config_h_

#include <crtdbg.h>
#include "stdafx.h"

namespace OML {

//-------------------------------------------------------------------------
/** \name debug & inline directive */
//-------------------------------------------------------------------------
//@{
#ifdef _DEBUG
	#ifndef OML_DEBUG
		#define OML_DEBUG
	#endif // OML_DEBUG
#endif // _DEBUG
	
#ifndef OML_DEBUG
	#ifndef OML_USE_INLINE
		#define OML_USE_INLINE
	#endif // OML_USE_INLINE
#endif // OML_DEBUG
	
#ifdef OML_USE_INLINE
	#ifndef OML_INLINE
		#define OML_INLINE inline
	#endif // OMLION3D_INLINE
#else
	#ifndef OML_INLINE
		#define OML_INLINE 
	#endif // OML_INLINE	
#endif // OML_USE_INLINE
//@}

	
//-------------------------------------------------------------------------
/** \name Basic types */
//-------------------------------------------------------------------------
//@{
#ifdef __UNIX__
	typedef char					OML_I8;
	typedef unsigned char           OML_U8;
	typedef short					OML_I16;
	typedef unsigned short			OML_U16;
	typedef long                    OML_I32;
	typedef unsigned long           OML_U32;
	typedef long long int           OML_I64;
	typedef unsigned long long int  OML_U64;
	typedef float                   OML_Real32;
	typedef double                  OML_Real64;
	typedef bool                    OML_Bool;
	typedef OML_Real32              OML_Float;
#elif defined (WIN32)
	typedef char                OML_I8;
	typedef unsigned char       OML_U8;
	typedef short				OML_I16;
	typedef unsigned short		OML_U16;
	typedef long                OML_I32;
	typedef unsigned long       OML_U32;
	typedef __int64             OML_I64;
	typedef unsigned __int64    OML_U64;
	typedef float               OML_Real32;
	typedef double              OML_Real64;
	typedef bool                OML_Bool;
	typedef OML_Real32          OML_Float;
#elif defined (_PS2_)
	typedef char                OML_I8;
	typedef unsigned char       OML_U8;
	typedef short				OML_I16;
	typedef unsigned short		OML_U16;
	typedef int                 OML_I32;
	typedef unsigned int        OML_U32;
	typedef long long           OML_I64;
	typedef unsigned long long  OML_U64;
	typedef float               OML_Real32;
	typedef double              OML_Real64;
	typedef OML_I8              OML_Bool;
	typedef OML_Real32          OML_Float;
#else
	#error "Unknown architecture !"
#endif
	
	typedef void*				OML_UserData;
	
	/** value returned by function to indicates errOML OML OML_OK */
	typedef OML_I32 OML_RETURN_CODE;

//@}

//-------------------------------------------------------------------------
/** \name numerical macros */
//-------------------------------------------------------------------------
//@{
#undef		MIN
#undef		MAX
#define		MIN(a, b)       ((a) < (b) ? (a) : (b))			//!<	Returns the min value between a and b
#define		MAX(a, b)       ((a) > (b) ? (a) : (b))			//!<	Returns the max value between a and b
#define		MAXMAX(a,b,c)   ((a) > (b) ? MAX (a,c) : MAX (b,c))
#define		OML_MIN(a, b)       MIN(a,b)						//!<	Returns the min value between a and b
#define		OML_MAX(a, b)       MAX(a,b)						//!<	Returns the max value between a and b
#define		OML_MAXMAX(a,b,c)   MAXMAX(a,b,c)
	
#define		OML_ABS(a)       ((a) > 0 ? (a) : (-a))			//!<	Returns the absolute value a
	
#define		SQR(x)			((x)*(x))						//!<	Returns x square
#define		CUBE(x)			((x)*(x)*(x))					//!<	Returns x cube
#define		OML_SQR(x)		SQR(x)							//!<	Returns x square
#define		OML_CUBE(x)		CUBE(x)							//!<	Returns x cube
//@}

//-------------------------------------------------------------------------
/** \name generic macros */
//-------------------------------------------------------------------------
//@{
/** a random number in [0-1] */
#define OML_RAND ((OML_Float) (rand()%10000))/10000
/** a random number in [a,b] */
#define OML_RAND_RANGE(a,b) (a)+((b)-(a))*((OML_Float) (rand()%10000))/10000
/** delete a single pointer */
#define OML_DELETE(p) {if (p!=NULL) delete p; p=NULL;}
/** delete an array pointer */
#define OML_DELETEARRAY(p) {if (p!=NULL) delete [] p; p=NULL;}
//@}

	//-------------------------------------------------------------------------
/** \name some constants */
//-------------------------------------------------------------------------
//@{
/** to make aproximate computations (derivation, OML_Float comparaisons ...) */
#define OML_EPSILON 0.001f
/** space coords */
enum OML_Coord_XYZW { X, Y, Z, W };
/** color coords */
enum OML_Coord_RVBA { R, V, B, A };
//@}

//-------------------------------------------------------------------------
/** \name numerical  constants */
//-------------------------------------------------------------------------
//@{
/** pi */
#define OML_PI		3.1415926535897932384626433832795028841971693993751f
/** pi/2 */
#define OML_HALFPI	1.57079632679489661923f
/** 2*pi */
#define OML_TWOPI	6.28318530717958647692f
/** 1/pi */
#define OML_INVPI	0.31830988618379067154f
/** 180/pi */
#define OML_RADTODEG	57.2957795130823208768f
/** pi/180 */
#define OML_DEGTOMLAD	0.01745329251994329577f
/** e */
#define OML_EXP		2.71828182845904523536f
/** 1/log10(2) */
#define OML_ILOG2	3.32192809488736234787f
/** 1/3 */
#define OML_INV3		0.33333333333333333333f
/** 1/6 */
#define OML_INV6		0.16666666666666666666f
/** 1/9 */
#define OML_INV7		0.14285714285714285714f
/** 1/9 */
#define OML_INV9		0.11111111111111111111f
/** 1/255 */
#define OML_INV255	0.00392156862745098039f
/** sqrt(2) */
#define OML_SQRT2    1.41421356237f
//@}

//-------------------------------------------------------------------------
/** \name assertion macros */
//-------------------------------------------------------------------------
//@{
#ifdef OML_DEBUG
	#define OML_ASSERT(expr) _ASSERT(expr)
#else
	#define OML_ASSERT(expr)
#endif // OML_DEBUG
//@}


} // End namespace OML


#endif // __OML_Config_h_

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The OMLion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the OMLion3D licence.                                  //
//  Refer to OMLion3d_licence.txt fOML mOMLe details about the OMLion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence OMLion3D.                              //
//  Se repOMLter a OMLion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

