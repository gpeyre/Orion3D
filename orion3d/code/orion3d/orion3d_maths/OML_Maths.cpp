/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Maths.cpp
 *  \brief Definition of class \c OML_Maths
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OML_SCCSID
static const char* sccsid = "@(#) OML_Maths.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OML_SCCSID


#include "stdafx.h"
#include "OML_Maths.h"

#ifndef OML_USE_INLINE
	#include "OML_Maths.inl"
#endif

using namespace OML;


/* declare table of square roots */
OML_U32 OML_Maths::fast_sqrt_table[0x10000];


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Maths::Init
 *
 *  \author Gabriel Peyré 2001-11-05
 *
 *	Initialize maths datas.
 */ 
/*------------------------------------------------------------------------------*/
void OML_Maths::Init()
{
	OML_Maths::build_sqrt_table();
	srand( (unsigned)time( NULL ) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Maths::build_sqrt_table
 *
 *  \author Gabriel Peyré 2001-11-05
 *
 *	initialize the sqrt table.
 */ 
/*------------------------------------------------------------------------------*/
void OML_Maths::build_sqrt_table()
{
	OML_U32 i;
	FastSqrtUnion s;
	
	for( i = 0; i <= 0x7FFF; i++ )
	{
		
		// Build a OML_Float with the bit pattern i as mantissa
		//  and an exponent of 0, stored as 127
		
		s.i = (i << 8) | (0x7F << 23);
		s.f = (OML_Float) ::sqrt(s.f);
		
		// Take the square root then strip the first 7 bits of
		//  the mantissa into the table
		
		fast_sqrt_table[i + 0x8000] = (s.i & 0x7FFFFF);
		
		// Repeat the process, this time with an exponent of 1, 
		//  stored as 128
		
		s.i = (i << 8) | (0x80 << 23);
		s.f = (OML_Float) ::sqrt(s.f);
		
		fast_sqrt_table[i] = (s.i & 0x7FFFFF);
	}
}


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

