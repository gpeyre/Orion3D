/*----------------------------------------------------------------------------*/
/*                              OR_Constant.h                                 */
/*----------------------------------------------------------------------------*/
/* definition of constants used in Orion3D                                    */
/*----------------------------------------------------------------------------*/

/** \file 
	Contains the definition of the constants used in Orion3D.
	\author Gabriel.
**/

#ifndef _OR_CONSTANTS_H_
#define _OR_CONSTANTS_H_

namespace OR
{

//-------------------------------------------------------------------------
/** \name misc constants */
//-------------------------------------------------------------------------
//@{
/** classical length of sting (mainly used for serialization) */
#define OR_NAME_LENGTH 50
/** to make aproximate computations (derivation, OR_Float comparaisons ...) */
#define OR_EPSILON 0.001f
/** maximum nuber of ligh in the manager */
#define OR_NB_MAX_LIGHT 9
/** maximum nuber of meshdatas in the manager */
#define OR_NB_MAX_MESHDATAS 10000
//@}

//-------------------------------------------------------------------------
/** \name default values */
//-------------------------------------------------------------------------
//@{
/* lens flare *****************************************************************/
/** default dimension */
#define OR_DEFAULT_LensFlare_Size 1
/* log file *******************************************************************/
/** defautl name of the log file */
#define OR_DEFAULT_LOG_NAME "orion3d.log"
/* shader *********************************************************************/
/** default offset value */
#define OR_DEFAULT_BUMPSHADER_OFFSET 0.04f;
//@}

//-------------------------------------------------------------------------
/** \name alpha pipeline configuration */
//-------------------------------------------------------------------------
//@{
/** maximum number of faces that the alpha pipeline can support */
#define OR_MAX_APHA_BUFFER_SIZE 10000
/** the value by witch the imput size is increased each time */
#define OR_ALPHA_BUFFER_INCREASE_SIZE 100
//@}

//-------------------------------------------------------------------------
/** \name numerical  constants */
//-------------------------------------------------------------------------
//@{
/** pi */
#define OR_PI		3.1415926535897932384626433832795028841971693993751f
/** pi/2 */
#define OR_HALFPI	1.57079632679489661923f
/** 2*pi */
#define OR_TWOPI	6.28318530717958647692f
/** 1/pi */
#define OR_INVPI	0.31830988618379067154f
/** 180/pi */
#define OR_RADTODEG	57.2957795130823208768f
/** pi/180 */
#define OR_DEGTORAD	0.01745329251994329577f
/** e */
#define OR_EXP		2.71828182845904523536f
/** 1/log10(2) */
#define OR_ILOG2	3.32192809488736234787f
/** 1/3 */
#define OR_INV3		0.33333333333333333333f
/** 1/6 */
#define OR_INV6		0.16666666666666666666f
/** 1/9 */
#define OR_INV7		0.14285714285714285714f
/** 1/9 */
#define OR_INV9		0.11111111111111111111f
/** 1/255 */
#define OR_INV255	0.00392156862745098039f
/** sqrt(2) */
#define OR_SQRT2    1.41421356237f
//@}

//-------------------------------------------------------------------------
/** \name Type ranges */
//-------------------------------------------------------------------------
//@{
/** max possible sbyte value */
#define	OR_MAX_I8			0x7f	
/** min possible sbyte value */
#define OR_MIN_I8			0x80	
/** max possible ubyte value */
#define	OR_MAX_U8			0xff	
/** min possible ubyte value */
#define	OR_MIN_U8			0x00	
/** max possible sword value */
#define	OR_MAX_I16			0x7fff	
/** min possible sword value */
#define	OR_MIN_I16			0x8000	
/** max possible uword value */
#define	OR_MAX_U16			0xffff	
/** min possible uword value */
#define	OR_MIN_U16			0x0000	
/** max possible sdword value */
#define	OR_MAX_I32			0x7fffffff
/** min possible sdword value */
#define	OR_MIN_I32			0x80000000
/** max possible udword value */
#define	OR_MAX_U32			0xffffffff
/** min possible udword value */
#define	OR_MIN_U32			0x00000000
/** max possible OR_Float value */
#define	OR_MAX_FLOAT		FLT_MAX
/** min possible loat value */
#define	OR_MIN_FLOAT		(-FLT_MAX)
/** integer representation of 1.0 */
#define OR_OR_IEEE_1_0		0x3f800000
/** integer representation of 255.0 */
#define OR_OR_IEEE_255_0	0x437f0000
//@}

//-------------------------------------------------------------------------
/** \name supported file versions */
//-------------------------------------------------------------------------
//@{
/** version of Orion3D */
#define OR_ORION3D_Version					105
/** the minimum version required for import of data from a file */
#define OR_ORION3D_MinSupported_Version		105
//@}


//-------------------------------------------------------------------------
/** \name initial values */
//-------------------------------------------------------------------------
//@{
/** for OR_SurfaceTeslator */
#define OR_START_MAX_DEPHT 6
/** for OR_Evaluator */
#define OR_DEFAULT_EVALUATOR_PRECISION 16
/** default particules size */
#define OR_PARTICULES_DefaultSize 0.1f
//@}


//-------------------------------------------------------------------------
/** \name Physic engine constant */
//-------------------------------------------------------------------------
//@{
/** Runge Kutta 4 coefficients */
#define OR_RK4_COEF1 0.1666666666f
#define OR_RK4_COEF2 0.3333333333f
#define OR_RK4_COEF3 0.3333333333f
#define OR_RK4_COEF4 0.1666666666f
//@}

} // namespace OR

#endif

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