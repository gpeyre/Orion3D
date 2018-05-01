//*****************************************************************************
// Created: Gabriel Peyré 2001-06-29
//*****************************************************************************

#include "OR_Shadable.h"

namespace OR {


/*------------------------------------------------------------------------------
 * Name : OR_Shadable::GetShader
 *
 *  \return the shader that the object will used to be rendered 
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Shader* OR_Shadable::GetShader()
{
	return pShader_;
}


/*------------------------------------------------------------------------------
 * Name : OR_Shadable::GetShadableMode
 *
 *  \return the way we want to process the shader
 *		    (using an array of vertex, or processing all). 
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Shadable::T_ShadableMode OR_Shadable::GetShadableMode()
{
	return ShadableMode_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shadable::SetFaceToProcess
 *
 *  \param  aFace The array of face to process. Size 3*nNbr
 *  \param  nNbr The number of face to process.
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Set the shadable in a state so that it process only the array of vertex specifyed
 *	by this method.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Shadable::SetFaceToProcess(OR_U32* aFace, OR_U32 nNbr)
{
	pFaceArray_   = aFace;
	nNbrFace_     = nNbr;
	ShadableMode_ = OR_Shadable::kProcessArray;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shadable::SetFaceToProcess_All
 *
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Set the shadable in a state so that it process all face of the object.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Shadable::SetFaceToProcess_All()
{
	pFaceArray_   = NULL;
	nNbrFace_     = -1;
	ShadableMode_ = OR_Shadable::kProcessAll;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shadable::GetFaceArrayToProcess
 *
 *  \return Pointer on the faces to process.
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Can be NULL if we are in "process all" mode.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32* OR_Shadable::GetFaceArrayToProcess()
{
	return pFaceArray_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shadable::GetNbrFaceToProcess
 *
 *  \return The number of face to process.
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Can be -1 if we are in "process all" mode. Then, pFaceArray_==NULL.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Shadable::GetNbrFaceToProcess()
{
	return nNbrFace_;
}



} // End namespace OR
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

