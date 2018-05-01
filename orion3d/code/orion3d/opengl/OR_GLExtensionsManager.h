/*-------------------------------------------------------------------*/
/*                   OR_GLExtensionsManager.h                        */
/*-------------------------------------------------------------------*/
/* Created : 17 Apr 2001   0h57                                      */
/*-------------------------------------------------------------------*/

/** \file
	Defines stuff to control OpenGL extensions.
	\author Gabriel
*/


#ifndef _OR_GLEXTENSIONSMANAGER_H_
#define _OR_GLEXTENSIONSMANAGER_H_

#include "../configuration/OR_Config.h"
#include "OR_GLExtensions.h"

namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                   class OR_GLExtensionsManager                    */
/*-------------------------------------------------------------------*/
/* a class to control OpenGL extensions                              */
/*-------------------------------------------------------------------*/

/// a class to control OpenGL extensions.
/**	This class initialize OpenGL extension at creation (ie. check for
	available extensions, and ask for proc adress if possible).
	\author Gabriel
*/

class ORION3D_API OR_GLExtensionsManager
{

public:

	/** check for used extentions and ask proc adress */
	static void SetUpExtensions();

	/** check if a given extension is available */
	static OR_Bool IsExtensionSupported(const char *extension);

	/* cube mapping extension **********************************************/
	/** is cube map supported on client hardware ? */
	static OR_Bool IsCubeMapSupported()
	{ return OR_EXT_texture_cube_map; }

	/* multitexture extension **********************************************/
	/** is multitexturing supported on client hardware ? */
	static OR_Bool IsMultitextureSupported()
	{ return OR_ARB_multitexture; }
	/** get the number of texture units */
	static OR_U32 GetNbTextureUnits()
	{ return OR_MAX_TEXTURE_UNITS_ARB; }

	/** texture env combine extension **************************************/
	/** is texture env combine supported on client hardware ? */
	static OR_Bool IsTextureEnvCombineSupported()
	{ return OR_EXT_texture_env_combine; }

	/** vertex weighting *******************************************************/
	/** is vertex weighting supported on client hardware ? */
	static OR_Bool IsVertexWeightingSupported()
	{ return OR_EXT_vertex_weighting; }

	/** vertex blend *******************************************************/
	/** is vertex blend supported on client hardware ? */
	static OR_Bool IsVertexBlendSupported()
	{ return OR_ARB_vertex_blend; }
	/** get the number of vertex units */
	static OR_U32 GetNbVertexUnits()
	{ return OR_ARB_max_vertex_units; }
	
private:
	
	/* cube mapping extension **********************************************/
	/** is cube map supported */
	static OR_Bool OR_EXT_texture_cube_map;
	
	/* multitexture extension **********************************************/
	/** is multitexturing supported */
	static OR_Bool OR_ARB_multitexture;
	/** the number of texture units */
	static OR_I32 OR_MAX_TEXTURE_UNITS_ARB;
	
	/* texture env combine extension **************************************/
	/** is texture env combine supported */
	static OR_Bool OR_EXT_texture_env_combine;
	
	/* vertex weighting ***************************************************/
	/** is vertex blend supported */
	static OR_Bool OR_ARB_vertex_blend;
	/** maximum vertex units */
	static OR_I32 OR_ARB_max_vertex_units;
	
	/* vertex blend *******************************************************/
	/** is vertex weighting supported */
	static OR_Bool OR_EXT_vertex_weighting;
	
	/* private functions ***************************************************/
	/** initialize OpenGL extensions functions adress */
	static void GetExtFunctions();

};


} // namespace OR

#endif /* #ifndef _OR_GLEXTENSIONSMANAGER_H_ */


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