/*-------------------------------------------------------------------------*/
/*                            OR_Context.cpp                               */
/*-------------------------------------------------------------------------*/
/* a wrapper class for opengl state variables                              */
/*-------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Matrix4x4.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Context.h"
#include "../maths/OR_Maths.h"

#ifndef OR_USE_INLINE
#   include "OR_Context.inl"
#endif

using namespace OR;

/*-------------------------------------------------------------------------*/
/*                      class OR_Context                                   */
/*-------------------------------------------------------------------------*/
/* store rendering state variables                                         */
/*-------------------------------------------------------------------------*/


OR_Context::OR_Context()
{
	/* set up default values */
	ForceDefaultPointSize();
	ForceDefaultLineSize();
	ForceDefaultCullingMode();
	ForceDefaultBlendingMode();
	ForceDefault2DTexturingMode();
	ForceDefaultLightingMode();
	ForceDefaultDepthTestingMode();
	ForceDefaultPerspectiveCorrection();
	ForceDefaultLocalViewer();
	ForceDefaultNormalization();
	ForceDefaultVertexWeighting();
}


void OR_Context::SetColor(OR_Vector4D& color)
{
	Color[R]=color[R];
	Color[V]=color[V];
	Color[B]=color[B];
	Color[A]=color[A];
	glColor4fv(Color);
}

/* draw mode management *****************************************************************/ 
void OR_Context::SimpleDrawMode()
{
	OR_Globals::Context()->DisableLighting();
	OR_Globals::Context()->Disable2DTexturing();
}
 
void OR_Context::NormalDrawMode()
{
	OR_Globals::Context()->SetDefault2DTexturingMode();
	OR_Globals::Context()->SetDefaultLightingMode();
}



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