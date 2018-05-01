/*----------------------------------------------------------------------------*/
/*                              OR_ReturnCode.h                               */
/*----------------------------------------------------------------------------*/
/* definition of return codes used in Orion3D                                 */
/*----------------------------------------------------------------------------*/

/** \file 
	Contains the definition of return codes used in Orion3D.
	\author Gabriel.
**/

#ifndef _OR_RETURNCODE_H_
#define _OR_RETURNCODE_H_

namespace OR
{
	
//-------------------------------------------------------------------------
/** \name Orion3D return codes */
//-------------------------------------------------------------------------
//@{
#define OR_OK							0
#define OR_ERROR						-9
#define OR_Invalid_Argument				-10
#define OR_Unknown_Argument				-11
#define OR_Manager_SelectedEmpty		-12
#define OR_Manager_InvalidSelectedType	-13
#define OR_Error_Opening_File			-14
#define OR_Error_File_Not_Supported		-15
#define OR_Error_Animation_Tree			-16
#define OR_Error_Argument_OutOfRange	-17
#define OR_Error_Buffer_OverFlow		-18
//@}

	
} // namespace OR

#endif /* #ifndef _OR_RETURNCODE_H_ */

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
