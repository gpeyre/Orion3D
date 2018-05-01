/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_Config.h
 *  \brief  Main configuration file.
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_CONFIG_H_
#define _FSW_CONFIG_H_

#include "stdafx.h"

namespace FSW {

#define FSW_VERSION 100

//-------------------------------------------------------------------------
/** \name debug & inline directive */
//-------------------------------------------------------------------------
//@{
#ifdef _DEBUG
	#ifndef FSW_DEBUG
		#define FSW_DEBUG
	#endif // FSW_DEBUG
#endif // _DEBUG
	
#ifndef FSW_DEBUG
	#ifndef FSW_USE_INLINE
		#define FSW_USE_INLINE
	#endif // FSW_USE_INLINE
#endif // FSW_DEBUG
	
#ifdef FSW_USE_INLINE
	#ifndef FSW_INLINE
		#define FSW_INLINE inline
	#endif // FSWION3D_INLINE
#else
	#ifndef FSW_INLINE
		#define FSW_INLINE 
	#endif // FSW_INLINE	
#endif // FSW_USE_INLINE
//@}

//-------------------------------------------------------------------------
/** \name Name space management */
//-------------------------------------------------------------------------
//@{
#define FSW_BEGIN_NAMESPACE		namespace FSW {
#define FSW_END_NAMESPACE		}
//@}
	
//-------------------------------------------------------------------------
/** \name Basic types */
//-------------------------------------------------------------------------
//@{
#ifdef __UNIX__
	typedef char					FSW_I8;
	typedef unsigned char           FSW_U8;
	typedef short					FSW_I16;
	typedef unsigned short			FSW_U16;
	typedef long                    FSW_I32;
	typedef unsigned long           FSW_U32;
	typedef long long int           FSW_I64;
	typedef unsigned long long int  FSW_U64;
	typedef float                   FSW_Real32;
	typedef double                  FSW_Real64;
	typedef bool                    FSW_Bool;
	typedef FSW_Real64              FSW_Float;
#elif defined (WIN32)
	typedef char                FSW_I8;
	typedef unsigned char       FSW_U8;
	typedef short				FSW_I16;
	typedef unsigned short		FSW_U16;
	typedef long                FSW_I32;
	typedef unsigned long       FSW_U32;
	typedef __int64             FSW_I64;
	typedef unsigned __int64    FSW_U64;
	typedef float               FSW_Real32;
	typedef double              FSW_Real64;
	typedef bool                FSW_Bool;
	typedef FSW_Real64          FSW_Float;
#elif defined (_PS2_)
	typedef char                FSW_I8;
	typedef unsigned char       FSW_U8;
	typedef short				FSW_I16;
	typedef unsigned short		FSW_U16;
	typedef int                 FSW_I32;
	typedef unsigned int        FSW_U32;
	typedef long long           FSW_I64;
	typedef unsigned long long  FSW_U64;
	typedef float               FSW_Real32;
	typedef double              FSW_Real64;
	typedef FSW_I8              FSW_Bool;
	typedef FSW_Real64          FSW_Float;
#else
	#error "Unknown architecture !"
#endif
	
	typedef void*				FSW_UserData;
	
	/** value returned by function to indicates errFSW FSW FSW_OK */
	typedef FSW_I32 FSW_RETURN_CODE;

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
#define		FSW_MIN(a, b)       MIN(a,b)						//!<	Returns the min value between a and b
#define		FSW_MAX(a, b)       MAX(a,b)						//!<	Returns the max value between a and b
#define		FSW_MAXMAX(a,b,c)   MAXMAX(a,b,c)
	
#define		FSW_ABS(a)       ((a) > 0 ? (a) : -(a))			//!<	Returns the absolute value a
	
#define		SQR(x)			((x)*(x))						//!<	Returns x square
#define		CUBE(x)			((x)*(x)*(x))					//!<	Returns x cube
#define		FSW_SQR(x)		SQR(x)							//!<	Returns x square
#define		FSW_CUBE(x)		CUBE(x)							//!<	Returns x cube
//@}

//-------------------------------------------------------------------------
/** \name generic macros */
//-------------------------------------------------------------------------
//@{
/** a random number in [0-1] */
#define FSW_RAND ((FSW_Float) (rand()%10000))/10000
/** a random number in [a,b] */
#define FSW_RAND_RANGE(a,b) (a)+((b)-(a))*((FSW_Float) (rand()%10000))/10000
/** delete a single pointer */
#define FSW_DELETE(p) {if (p!=NULL) delete p; p=NULL;}
/** delete an array pointer */
#define FSW_DELETEARRAY(p) {if (p!=NULL) delete [] p; p=NULL;}
//@}

//-------------------------------------------------------------------------
/** \name some constants */
//-------------------------------------------------------------------------
//@{
#define FSW_True  true
#define FSW_False false
/** to make aproximate computations (derivation, FSW_Float comparaisons ...) */
#define FSW_EPSILON 0.001f
/** space coords */
enum FSW_Coord_XYZW { X, Y, Z, W };
/** color coords */
enum FSW_Coord_RVBA { R, V, B, A };
/** The temporary file we use to launch debug test involving stream i/o */
#define FSW_TEST_FILE "test.bin"
//@}

//-------------------------------------------------------------------------
/** \name numerical  constants */
//-------------------------------------------------------------------------
//@{
/** pi */
#define FSW_PI		3.1415926535897932384626433832795028841971693993751f
/** pi/2 */
#define FSW_HALFPI	1.57079632679489661923f
/** 2*pi */
#define FSW_TWOPI	6.28318530717958647692f
/** 1/pi */
#define FSW_INVPI	0.31830988618379067154f
/** 180/pi */
#define FSW_RADTODEG(x)	(x)*57.2957795130823208768f
/** pi/180 */
#define FSW_DEGTORAD(x)	(x)*0.01745329251994329577f
/** e */
#define FSW_EXP		2.71828182845904523536f
/** 1/log10(2) */
#define FSW_ILOG2	3.32192809488736234787f
/** 1/3 */
#define FSW_INV3		0.33333333333333333333f
/** 1/6 */
#define FSW_INV6		0.16666666666666666666f
/** 1/9 */
#define FSW_INV7		0.14285714285714285714f
/** 1/9 */
#define FSW_INV9		0.11111111111111111111f
/** 1/255 */
#define FSW_INV255	0.00392156862745098039f
/** sqrt(2) */
#define FSW_SQRT2    1.41421356237f
//@}

//-------------------------------------------------------------------------
/** \name assertion macros */
//-------------------------------------------------------------------------
//@{
#ifdef FSW_DEBUG
	#define FSW_ASSERT(expr) _ASSERT(expr)
	#define FSW_DEBUG_ONLY(expr) expr
#else
	#define FSW_ASSERT(expr)
	#define FSW_DEBUG_ONLY(expr)
#endif // FSW_DEBUG
//@}

//-------------------------------------------------------------------------
/** \name FSW return codes */
//-------------------------------------------------------------------------
//@{
#define FSW_OK							0
#define FSW_ERROR						-9
#define FSW_Invalid_Argument			-10
#define FSW_Unknown_Argument			-11
#define FSW_Error_Opening_File			-14
#define FSW_Error_File_Not_Supported	-15
#define FSW_Error_Animation_Tree		-16
#define FSW_Error_Argument_OutOfRange	-17
#define FSW_Error_Buffer_OverFlow		-18
//@}

//-------------------------------------------------------------------------
/** \name The different kind of transform we suppport for the moment. */
//-------------------------------------------------------------------------
//@{
enum T_WaveletTransformType
{
	T_IntegralDataChunk
};
//@}

/*------------------------------------------------------------------------------*/
/** \name a vector of FSW_NodeMap */
/*------------------------------------------------------------------------------*/
//@{
typedef vector<class FSW_NodeMap*> T_NodeMapVector;
typedef T_NodeMapVector::iterator IT_NodeMapVector;
typedef T_NodeMapVector::reverse_iterator RIT_NodeMapVector;
typedef T_NodeMapVector::const_iterator CIT_NodeMapVector;
typedef T_NodeMapVector::const_reverse_iterator CRIT_NodeMapVector;
//@}

/*------------------------------------------------------------------------------*/
/** \name a vector of FSW_Float */
/*------------------------------------------------------------------------------*/
//@{
typedef vector<FSW_Float> T_FloatVector;
typedef T_FloatVector::iterator IT_FloatVector;
typedef T_FloatVector::reverse_iterator RIT_FloatVector;
typedef T_FloatVector::const_iterator CIT_FloatVector;
typedef T_FloatVector::const_reverse_iterator CRIT_FloatVector;
//@}

} // End namespace FSW

#ifdef FSW_DEBUG
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

#endif // _FSW_CONFIG_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2002 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
