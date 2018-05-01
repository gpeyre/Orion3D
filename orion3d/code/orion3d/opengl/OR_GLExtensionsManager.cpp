/*-------------------------------------------------------------------*/
/*                   OR_GLExtensionsManager.cpp                      */
/*-------------------------------------------------------------------*/
/* Created : 17 Apr 2001   0h57                                      */
/*-------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_GLExtensionsManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_GLExtensionsManager.h"

namespace OR
{
	
/* initialize static datas *******************************************/
OR_Bool OR_GLExtensionsManager::OR_EXT_texture_cube_map=false;
OR_Bool OR_GLExtensionsManager::OR_ARB_multitexture=false;
OR_I32 OR_GLExtensionsManager::OR_MAX_TEXTURE_UNITS_ARB=-1;
OR_Bool OR_GLExtensionsManager::OR_EXT_texture_env_combine=false;
OR_Bool OR_GLExtensionsManager::OR_ARB_vertex_blend=false;
OR_Bool OR_GLExtensionsManager::OR_EXT_vertex_weighting=false;
OR_I32 OR_GLExtensionsManager::OR_ARB_max_vertex_units=-1;

/*-------------------------------------------------------------------*/
/*                   class OR_GLExtensionsManager                    */
/*-------------------------------------------------------------------*/
/* a class to control OpenGL extensions                              */
/*-------------------------------------------------------------------*/

void OR_GLExtensionsManager::SetUpExtensions()
{
	/* set cube map extention ************/
	OR_EXT_texture_cube_map=IsExtensionSupported("GL_EXT_texture_cube_map");

	/* set texture env combine extension */
	OR_EXT_texture_env_combine=IsExtensionSupported("GL_EXT_texture_env_combine");

	/* set multitexturing extention ******/
	OR_ARB_multitexture=IsExtensionSupported("GL_ARB_multitexture");
	glGetIntegerv((unsigned long)GL_MAX_TEXTURE_UNITS_ARB,(GLint *)&OR_MAX_TEXTURE_UNITS_ARB);

	/* vertex weighting ***************************************************/
	OR_EXT_vertex_weighting=IsExtensionSupported("GL_EXT_vertex_weighting");
	
	/* vertex blend *******************************************************/
	OR_ARB_vertex_blend=IsExtensionSupported("GL_ARB_vertex_blend");
	glGetIntegerv((unsigned long)GL_MAX_VERTEX_UNITS_ARB,(GLint *)&OR_ARB_max_vertex_units);


	
	/* set the @ of extension functions */
	GetExtFunctions();	
}

/* the function to get the adress of extension functions */
#ifdef _WIN32_
	#define OR_GET_OPENGL_PROC(x) wglGetProcAddress(x)
#else
	#define OR_GET_OPENGL_PROC(x) glXGetProcAddressARB((byte*) x)
#endif


void OR_GLExtensionsManager::GetExtFunctions()
{
	/* multitexture extension **********************************************/
	glMultiTexCoord1dARB	= (PFNGLMULTITEXCOORD1DARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord1dEXT");
	glMultiTexCoord1dvARB	= (PFNGLMULTITEXCOORD1DVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord1dvARB");	
	glMultiTexCoord1fARB	= (PFNGLMULTITEXCOORD1FARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord1fARB");
	glMultiTexCoord1fvARB	= (PFNGLMULTITEXCOORD1FVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord1fvARB");
	glMultiTexCoord1iARB	= (PFNGLMULTITEXCOORD1IARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord1iARB");
	glMultiTexCoord1ivARB	= (PFNGLMULTITEXCOORD1IVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord1ivARB");
	glMultiTexCoord1sARB	= (PFNGLMULTITEXCOORD1SARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord1sARB");
	glMultiTexCoord1svARB	= (PFNGLMULTITEXCOORD1SVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord1svARB");
	glMultiTexCoord2dARB	= (PFNGLMULTITEXCOORD2DARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord2dARB");
	glMultiTexCoord2dvARB	= (PFNGLMULTITEXCOORD2DVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord2dvARB");	
	glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord2fARB");
	glMultiTexCoord2fvARB	= (PFNGLMULTITEXCOORD2FVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord2fvARB");
	glMultiTexCoord2iARB	= (PFNGLMULTITEXCOORD2IARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord2iARB");
	glMultiTexCoord2ivARB	= (PFNGLMULTITEXCOORD2IVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord2ivARB");
	glMultiTexCoord2sARB	= (PFNGLMULTITEXCOORD2SARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord2sARB");
	glMultiTexCoord2svARB	= (PFNGLMULTITEXCOORD2SVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord2svARB");
	glMultiTexCoord3dARB	= (PFNGLMULTITEXCOORD3DARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord3dARB");
	glMultiTexCoord3dvARB	= (PFNGLMULTITEXCOORD3DVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord3dvARB");
	glMultiTexCoord3fARB	= (PFNGLMULTITEXCOORD3FARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord3fARB");
	glMultiTexCoord3fvARB	= (PFNGLMULTITEXCOORD3FVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord3fvARB");
	glMultiTexCoord3iARB	= (PFNGLMULTITEXCOORD3IARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord3iARB");
	glMultiTexCoord3ivARB	= (PFNGLMULTITEXCOORD3IVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord3ivARB");
	glMultiTexCoord3sARB	= (PFNGLMULTITEXCOORD3SARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord3sARB");
	glMultiTexCoord3svARB	= (PFNGLMULTITEXCOORD3SVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord3svARB");
	glMultiTexCoord4dARB	= (PFNGLMULTITEXCOORD4DARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord4dARB");
	glMultiTexCoord4dvARB	= (PFNGLMULTITEXCOORD4DVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord4dvARB");	
	glMultiTexCoord4fARB	= (PFNGLMULTITEXCOORD4FARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord4fARB");
	glMultiTexCoord4fvARB	= (PFNGLMULTITEXCOORD4FVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord4fvARB");
	glMultiTexCoord4iARB	= (PFNGLMULTITEXCOORD4IARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord4iARB");
	glMultiTexCoord4ivARB	= (PFNGLMULTITEXCOORD4IVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord4ivARB");
	glMultiTexCoord4sdARB	= (PFNGLMULTITEXCOORD4SARBPROC)		OR_GET_OPENGL_PROC("glMultiTexCoord4sdARB");
	glMultiTexCoord4svARB	= (PFNGLMULTITEXCOORD4SVARBPROC)	OR_GET_OPENGL_PROC("glMultiTexCoord4svARB");
	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		OR_GET_OPENGL_PROC("glActiveTextureARB");
	glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC)	OR_GET_OPENGL_PROC("glClientActiveTextureARB");

	/* vertex weighting ***************************************************/
	glVertexWeightfEXT			= (PFNGLVERTEXWEIGHTFEXTPROC)		OR_GET_OPENGL_PROC("glVertexWeightfEXT");
	glVertexWeightfvEXT			= (PFNGLVERTEXWEIGHTFVEXTPROC)		OR_GET_OPENGL_PROC("glVertexWeightfvEXT");
	glVertexWeightPointerEXT	= (PFNGLVERTEXWEIGHTPOINTEREXTPROC)	OR_GET_OPENGL_PROC("glVertexWeightPointerEXT");
}

OR_Bool OR_GLExtensionsManager::IsExtensionSupported(const char *extension)
{
	const GLubyte* extensions=NULL;
	const GLubyte* start;
	GLubyte *where, *terminator;
	/* il ne faut pas qu'il y ait d'espace ds le nom */
	where = (GLubyte *)strchr(extension, ' ');
	if (where || *extension=='\0') return false;

	/* the extension that the graphic card support */
	extensions=glGetString(GL_EXTENSIONS);

	if (extensions==NULL)
	{
		OR_Globals::MessageHandler()->FatalError("OR_IsExtensionSupported", "Could not find OpenGL extensions.");
	}

	start=extensions;
	for(;;)
	{
		where=(GLubyte *) strstr((const char*) start, extension);
		if (!where)
			break;
		terminator=where+strlen(extension);
		if (where==start || *(where-1)==' ')
			if (*terminator==' ' || *terminator=='\0' )
				return true;
		start=terminator;
	}
	return false;
}

} // namespace OR

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