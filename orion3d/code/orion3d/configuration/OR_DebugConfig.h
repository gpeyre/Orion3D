/*----------------------------------------------------------------------------*/
/*                              OR_DebugConfig.h                              */
/*----------------------------------------------------------------------------*/
/* definitions to configurate the debug output                                */
/*----------------------------------------------------------------------------*/

/** \file 
	Contains the definition to configurate the debug output.
	\author Gabriel.
**/

#ifndef _OR_DEBUGCONFIG_H_
#define _OR_DEBUGCONFIG_H_

namespace OR
{
	

/** to draw the mesh normals */
// #define OR_DRAW_NORMALS
/** to enable hiden geometrie rendering */
#define OR_DRAW_CAMERAS
/** to enable hiden geometrie rendering */
#define OR_DRAW_GIZMOS
/** to enable hiden geometrie rendering */
#define OR_DRAW_LIGHTS
/** to enable hiden geometrie rendering */
#define OR_DRAW_OBJECT_AXES
/** to enable animation trajectory rendering */
#define OR_DRAW_Trajectories
/** to enable bones rendering */
#define OR_DRAW_BONES
/** draw point computed in the meta-grid */
// #define OR_DEBUG_META_ENV
/** to defines stuff to compute the FPS [for debug sessions] */
#define _COMPUTE_FPS_

/*----------------------------------------------------------------------------*/
/* alpha pipeline debug configuration                                         */
/*----------------------------------------------------------------------------*/

/** diplay a log of sorted faces after a sort */
// #define OR_DEBUG_AlphaPipeline_DiplayLog
/** check the validity of each sort made by the alpha pipeline */
// #define OR_DEBUG_AlphaPipeline_CheckSort

	
} // namespace OR

#endif /* #ifndef _OR_DEBUGCONFIG_H_ */

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