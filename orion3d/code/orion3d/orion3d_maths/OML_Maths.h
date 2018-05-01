
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Maths.h
 *  \brief Definition of class \c OML_Maths
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_Maths_h_
#define __OML_Maths_h_

#include "OML_Config.h"

namespace OML {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_Maths
 *  \brief  Basic maths functions that fits nowhere else.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/

/** used for fast square root computations */
typedef union FastSqrtUnion
{
	OML_Float f;
	OML_U32 i;
} FastSqrtUnion;

class OML_Maths
{

public:

	static void Init();

	static OML_Float sqrt(OML_Float v);
	static OML_Float norm(OML_Float x, OML_Float y);
	static OML_Float norm(OML_Float x, OML_Float y, OML_Float z);
	static OML_Float norm(OML_Float x, OML_Float y, OML_Float z, OML_Float w);

private:
	
	static void build_sqrt_table();

	/** a table of suqare roots */
	static OML_U32 fast_sqrt_table[0x10000];

};

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_Maths.inl"
#endif


#endif // __OML_Maths_h_

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

