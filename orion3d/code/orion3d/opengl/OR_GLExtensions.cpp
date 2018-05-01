/*---------------------------------------------------------------*/
/*                       OR_GLExtensions.cpp                     */
/*---------------------------------------------------------------*/
/* implementations for OpenGL extensions                         */
/*---------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_GLExtensions.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "../configuration/OR_Config.h"
#include "OR_GLExtensions.h"

	
/*---------------------------------------------------------------*/
/*                 ARB_multitexture                              */
/*---------------------------------------------------------------*/
PFNGLMULTITEXCOORD1DARBPROC		glMultiTexCoord1dARB = NULL;
PFNGLMULTITEXCOORD1DVARBPROC	glMultiTexCoord1dvARB = NULL;	
PFNGLMULTITEXCOORD1FARBPROC		glMultiTexCoord1fARB = NULL;
PFNGLMULTITEXCOORD1FVARBPROC	glMultiTexCoord1fvARB = NULL;
PFNGLMULTITEXCOORD1IARBPROC		glMultiTexCoord1iARB = NULL;
PFNGLMULTITEXCOORD1IVARBPROC	glMultiTexCoord1ivARB = NULL;	
PFNGLMULTITEXCOORD1SARBPROC		glMultiTexCoord1sARB = NULL;
PFNGLMULTITEXCOORD1SVARBPROC	glMultiTexCoord1svARB = NULL;
PFNGLMULTITEXCOORD2DARBPROC		glMultiTexCoord2dARB = NULL;
PFNGLMULTITEXCOORD2DVARBPROC	glMultiTexCoord2dvARB = NULL;	
PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB = NULL;
PFNGLMULTITEXCOORD2FVARBPROC	glMultiTexCoord2fvARB = NULL;
PFNGLMULTITEXCOORD2IARBPROC		glMultiTexCoord2iARB = NULL;
PFNGLMULTITEXCOORD2IVARBPROC	glMultiTexCoord2ivARB = NULL;
PFNGLMULTITEXCOORD2SARBPROC		glMultiTexCoord2sARB = NULL;
PFNGLMULTITEXCOORD2SVARBPROC	glMultiTexCoord2svARB = NULL;
PFNGLMULTITEXCOORD3DARBPROC		glMultiTexCoord3dARB = NULL;
PFNGLMULTITEXCOORD3DVARBPROC	glMultiTexCoord3dvARB = NULL;
PFNGLMULTITEXCOORD3FARBPROC		glMultiTexCoord3fARB = NULL;
PFNGLMULTITEXCOORD3FVARBPROC	glMultiTexCoord3fvARB = NULL;
PFNGLMULTITEXCOORD3IARBPROC		glMultiTexCoord3iARB = NULL;
PFNGLMULTITEXCOORD3IVARBPROC	glMultiTexCoord3ivARB = NULL;
PFNGLMULTITEXCOORD3SARBPROC		glMultiTexCoord3sARB = NULL;
PFNGLMULTITEXCOORD3SVARBPROC	glMultiTexCoord3svARB = NULL;
PFNGLMULTITEXCOORD4DARBPROC		glMultiTexCoord4dARB = NULL;
PFNGLMULTITEXCOORD4DVARBPROC	glMultiTexCoord4dvARB = NULL;	
PFNGLMULTITEXCOORD4FARBPROC		glMultiTexCoord4fARB = NULL;
PFNGLMULTITEXCOORD4FVARBPROC	glMultiTexCoord4fvARB = NULL;
PFNGLMULTITEXCOORD4IARBPROC		glMultiTexCoord4iARB = NULL;
PFNGLMULTITEXCOORD4IVARBPROC	glMultiTexCoord4ivARB = NULL;
PFNGLMULTITEXCOORD4SARBPROC		glMultiTexCoord4sdARB = NULL;
PFNGLMULTITEXCOORD4SVARBPROC	glMultiTexCoord4svARB = NULL;
PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTextureARB = NULL;	

/*---------------------------------------------------------------*/
/*                 EXT_vertex_weighting                          */
/*---------------------------------------------------------------*/
PFNGLVERTEXWEIGHTFEXTPROC		glVertexWeightfEXT			= NULL;
PFNGLVERTEXWEIGHTFVEXTPROC		glVertexWeightfvEXT			= NULL;
PFNGLVERTEXWEIGHTPOINTEREXTPROC	glVertexWeightPointerEXT	= NULL;


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