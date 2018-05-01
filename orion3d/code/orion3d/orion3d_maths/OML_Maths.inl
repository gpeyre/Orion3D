/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Maths.inl
 *  \brief Inlined methods for \c OML_Maths
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_Maths.h"

namespace OML {

// #define OML_USE_FAST_SQRT


#define FP_BITS(fp) (*(OML_U32 *)&(fp))
#define FP_ABS_BITS(fp) (FP_BITS(fp)&0x7FFFFFFF)
#define FP_SIGN_BIT(fp) (FP_BITS(fp)&0x80000000)
#define FP_ONE_BITS 0x3F800000



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Maths::sqrt
 *
 *  \param  n input value.
 *  \return square root of the value.
 *  \author Gabriel Peyré 2001-11-05
 *
 *	compute a fast sqrt using a table.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Maths::sqrt(OML_Float n)
{ 
#ifdef OML_USE_FAST_SQRT
	OML_ASSERT( n>=0 );

	if (FP_BITS(n) == 0)
		return 0;                 // check for square root of 0
	
	FP_BITS(n) = fast_sqrt_table[(FP_BITS(n) >> 8) & 0xFFFF] | ((((FP_BITS(n) - 0x3F800000) >> 1) + 0x3F800000) & 0x7F800000);
	
	return n;
#else
	return (OML_Float) ::sqrt(n);
#endif // OML_USE_FAST_SQRT
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Maths::norm
 *
 *  \param  x value on X axis.
 *  \param  y value on Y axis.
 *  \return norm of the vector.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Maths::norm(OML_Float x, OML_Float y)
{
	return OML_Maths::sqrt( x*x + y*y );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Maths::norm
 *
 *  \param  x value on X axis.
 *  \param  y value on Y axis.
 *  \param  z value on Z axis.
 *  \return norm of the vector.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Maths::norm(OML_Float x, OML_Float y, OML_Float z)
{
	return OML_Maths::sqrt( x*x + y*y + z*z );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Maths::norm
 *
 *  \param  x value on X axis.
 *  \param  y value on Y axis.
 *  \param  z value on Z axis.
 *  \param  w value on W axis.
 *  \return norm of the vector.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Maths::norm(OML_Float x, OML_Float y, OML_Float z, OML_Float w)
{
	return OML_Maths::sqrt( x*x + y*y + z*z + w*w );
}

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

