/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Macros.h
 *  \brief Defines some usefull macros
 *  \author Gabriel Peyré 2001-07-16
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Macros_h_
#define __OR_Macros_h_


namespace OR {

//-------------------------------------------------------------------------
/** \name numerical macros */
//-------------------------------------------------------------------------
//@{
#undef		MIN
#undef		MAX
#define		MIN(a, b)       ((a) < (b) ? (a) : (b))			//!<	Returns the min value between a and b
#define		MAX(a, b)       ((a) > (b) ? (a) : (b))			//!<	Returns the max value between a and b
#define		MAXMAX(a,b,c)   ((a) > (b) ? MAX (a,c) : MAX (b,c))
#define		OR_MIN(a, b)       MIN(a,b)						//!<	Returns the min value between a and b
#define		OR_MAX(a, b)       MAX(a,b)						//!<	Returns the max value between a and b
#define		OR_MAXMAX(a,b,c)   MAXMAX(a,b,c)

#define		OR_ABS(a)       ((a) > 0 ? (a) : (-a))			//!<	Returns the absolute value a

#define		SQR(x)			((x)*(x))						//!<	Returns x square
#define		CUBE(x)			((x)*(x)*(x))					//!<	Returns x cube
#define		OR_SQR(x)		SQR(x)							//!<	Returns x square
#define		OR_CUBE(x)		CUBE(x)							//!<	Returns x cube
//@}
	
//-------------------------------------------------------------------------
/** \name generic macros */
//-------------------------------------------------------------------------
//@{
/** a random number in [0-1] */
#define OR_RAND ((OR_Float) (rand()%10000))/10000
/** a random number in [a,b] */
#define OR_RAND_RANGE(a,b) (a)+((b)-(a))*((OR_Float) (rand()%10000))/10000
/** delete a single pointer */
#define OR_DELETE(p) {if (p!=NULL) delete p; p=NULL;}
/** delete an array pointer */
#define OR_DELETEARRAY(p) {if (p!=NULL) delete [] p; p=NULL;}
/** check that memory has been allcoated */
#define OR_CHECKALLOC(x)	if(!x) return false;
 //@}


//-------------------------------------------------------------------------
/** \name assertion macros */
//-------------------------------------------------------------------------
//@{
#ifdef OR_DEBUG
	#define OR_ASSERT(expr) _ASSERT(expr)
#else
	#define OR_ASSERT(expr)
#endif // OR_DEBUG
//@}

} // End namespace OR


#endif // __OR_Macros_h_

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

