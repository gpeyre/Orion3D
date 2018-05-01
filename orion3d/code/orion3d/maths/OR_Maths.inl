/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Maths.inl
 *  \brief Inlined methods for \c OR_Maths
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Maths.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Maths GetCurrentModelView
 *
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Set this matrix to the current modelview matrix.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Maths::GetCurrentModelView(OR_Matrix4x4& mat)
{
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.GetData());
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Maths SetCurrentModelView
 *
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Set the current modelview matrix to this matrix
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Maths::SetCurrentModelView(OR_Matrix4x4& mat)
{
	glLoadMatrixf( mat.GetData() );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Maths MultiplyCurrentModelView
 *
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Multiply the current modelview matrix by this matrix, ie. M <- this*M
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Maths::MultiplyCurrentModelView(OR_Matrix4x4& mat)
{
	glMultMatrixf( mat.GetData() );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Maths GetCurrentProjection
 *
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Set this matrix to the current projection matrix.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Maths::GetCurrentProjection(OR_Matrix4x4& mat)
{
	glGetFloatv(GL_PROJECTION_MATRIX, mat.GetData());
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Maths SetCurrentProjection
 *
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Set the current projection matrix to this matrix
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Maths::SetCurrentProjection(OR_Matrix4x4& mat)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( mat.GetData() );
	glMatrixMode(GL_MODELVIEW);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Maths MultiplyCurrentProjection
 *
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Multiply the current projection matrix by this matrix, ie. M <- this*M
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Maths::MultiplyCurrentProjection(OR_Matrix4x4& mat)
{
	glMatrixMode(GL_PROJECTION);
	glMultMatrixf( mat.GetData() );
	glMatrixMode(GL_MODELVIEW);
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

