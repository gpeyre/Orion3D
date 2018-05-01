/*------------------------------------------------------------------------------
 *  \file  OR_3DS_MAXMaterial.h
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-11-05
 *------------------------------------------------------------------------------*/

#ifndef __OR_3DS_MAXMaterial_h_
#define __OR_3DS_MAXMaterial_h_

#include "stdafx.h"

using namespace OR;

namespace OR_3DS {

/*------------------------------------------------------------------------------
 *  \class  OR_3DS_MAXMaterial
 *  \brief  A material of 3DSMAX
 *  \author Antoine Bouthors 2001-11-05
 *  This class is just a wrapper that allows you to get the Orion3D translation
 *	from a MtlBase*. Simply cast the MtlBase* node to a OR_3DS_MAXMaterial* one and you can call
 *	the functions returning Orion3D classes 
 *------------------------------------------------------------------------------*/

class OR_3DS_MAXMaterial: public MtlBase
{
public:
	///\param Time the time to retrieve the shader	
	///\return the OR_Shader corresponding to this Material
	OR_Shader* GetOR_Shader(TimeValue Time);
};

} // End namespace OR_3DS

#ifdef OR_USE_INLINE
#   include "OR_3DS_MAXMaterial.inl"
#endif


#endif // __OR_3DS_MAXMaterial_h_

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

