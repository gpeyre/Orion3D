/*-------------------------------------------------------------------------*/
/*                            OR_Context.h                                 */
/*-------------------------------------------------------------------------*/
/* a wrapper class for opengl state variables                              */
/*-------------------------------------------------------------------------*/

/** \file
	Contains definition of a wrapper class to store and modifiy OpenGL state variables.
	\author Gabriel
*/


#ifndef _OR_CONTEXT_H_
#define _OR_CONTEXT_H_

#include "../configuration/OR_Config.h"
#include "../utils/OR_MessageHandler.h"
#include "../maths/OR_Maths.h"
#include "../orion3d_maths/OML_Vector4D.h"

namespace OR
{
	
typedef ORION3D_API class OML::OML_Vector4D	OR_Vector4D;

/*-------------------------------------------------------------------------*/
/* context default values                                                  */
/*-------------------------------------------------------------------------*/

#define OR_DEFAULT_LINE_SIZE 1
#define OR_DEFAULT_POINT_SIZE 1
#define OR_DEFAULT_COLOR_R 1
#define OR_DEFAULT_COLOR_V 1
#define OR_DEFAULT_COLOR_B 1
#define OR_DEFAULT_COLOR_A 1
#define OR_DEFAULT_BLENDING_MODE OR_Blending_None
#define OR_DEFAULT_CULLING_MODE OR_Culling_Back
#define OR_DEFAULT_TEXTURING2D_MODE true
#define OR_DEFAULT_LIGHTING_MODE true
#define OR_DEFAULT_DEPTHTESTING_MODE true
#define OR_DEFAULT_DRAWING_MODE OR_Drawing_Filled
#define OR_DEFAULT_LOCAL_VIEWER false
#define OR_DEFAULT_PERSPECTIVE_CORRECTION false
#define OR_DEFAULT_NORMALIZATION false
#define OR_DEFAULT_VERTEX_WEIGHTING false

/*-------------------------------------------------------------------------*/
/*                      class OR_Context                                   */
/*-------------------------------------------------------------------------*/
/* store rendering state variables                                         */
/*-------------------------------------------------------------------------*/

/// store rendering state variables.
/** 
	This class is a wrapper class for opengl state variables. It is
	used by Orion3D to avoid using OpenGL functions directly to commute 
	the rendering context.
	Management can be of two kinds, depending on the target :
		- complex mangement : use enum constants and functions like SetxxxMode(), GetxxxMode(), SetDefaultxxxMode().
		- simple management : use boolean values and functions like Enablexxx(), Disablexxx(), IsxxxOn(), SetDefaultxxxMode().
	Where xxx is the name of the target.
	\author Gabriel
*/

class ORION3D_API OR_Context
{
private:
	/** current drawing mode. default=OR_Drawing_Filled*/
	OR_Drawing_Mode DrawingMode;
	/** current culling mode. default=OR_Culling_Back */
	OR_Culling_Mode CullingMode;
	/** current point size */
	OR_Float PointSize;
	/** current line size */
	OR_Float LineSize;
	/** the color in simple draw mode */
	OR_Float Color[4];
	/** the current blending mode */
	OR_Blending_Mode BlendingMode;
	/** is texture 2d enable */
	OR_Bool Texturing2DMode;
	/** is lighting mode enable */
	OR_Bool LightingMode;
	/** is depth texting mode on */
	OR_Bool DepthTestingMode; 
	/** is viewer considered local for lighting calculations*/
	OR_Bool LocalViewer;
	/** is perspective correction enabled */
	OR_Bool PerspectiveCorrection;
	/** is normalization enabled */
	OR_Bool m_Normalization;
	/** is vertex weighting enabled */
	OR_Bool m_VertexWeighting;


public:
	/** constructor */
	OR_Context();

	/* culling management ********************************************************************/
	/** get the current culling mode */
	OR_Culling_Mode GetCullingMode() const;
	/** set the current culling mode 
		\return the previous culling mode */
	OR_Culling_Mode SetCullingMode(OR_Culling_Mode mode);
	/** set the current culling mode 
		\return the previous culling mode */
	OR_Culling_Mode ForceCullingMode(OR_Culling_Mode mode);
	/** reset the default culling mode
		\return the previous culling mode */
	OR_Culling_Mode SetDefaultCullingMode();
	/** reset the default culling mode
		\return the previous culling mode */
	OR_Culling_Mode ForceDefaultCullingMode();

	/* line size management ******************************************************************/
	/** get the current line size */
	OR_Float GetLineSize() const;
	/** set the line size
		\return the previous line size */
	OR_Float SetLineSize(OR_Float v);
	/** set the line size
		\return the previous line size */
	OR_Float ForceLineSize(OR_Float v);
	/** modifiy the line size +/-
		\return the previous line size */
	OR_Float ModifyLineSize(OR_Float v);
	/** reset the default line size 
		\return the previous line size */
	OR_Float SetDefaultLineSize();
	/** reset the default line size 
		\return the previous line size */
	OR_Float ForceDefaultLineSize();

	/* point size management ****************************************************************/
	/** get the current point size */
	OR_Float GetPointSize() const;
	/** set the point size 
		\return the previous line size */
	OR_Float SetPointSize(OR_Float v);
	/** set the point size 
		\return the previous line size */
	OR_Float ForcePointSize(OR_Float v);
	/** modifiy the point size +/-
		\return the current point size */
	OR_Float ModifyPointSize(OR_Float v);
	/** reset the default point size 
		\return the previous line size */
	OR_Float SetDefaultPointSize();
	/** reset the default point size 
		\return the previous line size */
	OR_Float ForceDefaultPointSize();


	/* draw mode management *****************************************************************/
	/** switch to simple draw mode [without shadows & textures] */
	void SimpleDrawMode();
	/** re-switch to normal draw mode */
	void NormalDrawMode();

	/* simple color management **************************************************************/
	/** set simple draw color in RVB format */
	void SetColor(OR_Float r, OR_Float v, OR_Float b);
	/** set simple draw color in RVBA format */
	void SetColor(OR_Float r, OR_Float v, OR_Float b, OR_Float a);
	/** set simple draw color in OR_Float[4] (RVBA) format */
	void SetColor(OR_Float color[4]);
	/** set simple draw color in OR_Vector4D (RVBA) format */
	void SetColor(OR_Vector4D& color);
	/** set simple draw color on one component (R|V|B|A) */
	void SetColor(OR_Coord_RVBA c, OR_Float color);
	/** get the current simple color color */
	OR_Float* GetColor() const;
	/** re-set the default color */
	void SetDefaultColor();

	/* blending management ****************************************************************/
	/** set blending mode
		\return previous blending mode */
	OR_Blending_Mode SetBlendingMode(OR_Blending_Mode mode);
	/** set blending mode
		\return previous blending mode */
	OR_Blending_Mode ForceBlendingMode(OR_Blending_Mode mode);
	/** set default blending mode 
		\return previous blending mode */
	OR_Blending_Mode SetDefaultBlendingMode();
	/** set default blending mode 
		\return previous blending mode */
	OR_Blending_Mode ForceDefaultBlendingMode();
	/** get current blending mode */
	OR_Blending_Mode GetBlendingMode() const;

	 
	/* alpha test management *************************************************************/


	/* 2D texture management BOOL ********************************************************/
	/** enable 2D texturing mode.
		\return previous value of 2d texturing mode */
	OR_Bool Enable2DTexturing();
	/** disable 2D texturing mode.
		\return previous value of 2d texturing mode */
	OR_Bool Disable2DTexturing();
	/** set the 2D texturing mode 
		\return previous value of 2d texturing mode*/
	OR_Bool Force2DTexturingMode( OR_Bool Mode );	
	/** toggle 2D texturing mode.
		\return previous value of 2d texturing mode */
	OR_Bool Toggle2DTexturing();
	/** set the default 2D texturing mode 
		\return previous value of 2d texturing mode*/
	OR_Bool SetDefault2DTexturingMode();
	/** set the default 2D texturing mode 
		\return previous value of 2d texturing mode*/
	OR_Bool ForceDefault2DTexturingMode();
	/** get 2D texturing mode.
		\return current value of 2d texturing mode */
	OR_Bool Get2DTexturingMode() const;


	/* lighting management BOOL **********************************************************/
	/** enable lighting mode.
		\return previous value of lighting mode */
	OR_Bool EnableLighting();
	/** disable lighting mode.
		\return previous value of lighting mode */
	OR_Bool DisableLighting();
	/** set lighting mode.
		\return previous value of lighting mode */
	OR_Bool ForceLighting( OR_Bool Mode );
	/** toggle lighting mode.
		\return previous value of lighting mode */
	OR_Bool ToggleLighting();
	/** set the default lighting mode 
		\return previous value of lighting mode*/
	OR_Bool SetDefaultLightingMode();
	/** set the default lighting mode 
		\return previous value of lighting mode*/
	OR_Bool ForceDefaultLightingMode();
	/** get lightingmode.
		\return current value of lighting mode */
	OR_Bool GetLightingMode() const;

	/* lighting calculations management ***********/
	/** \return true if the viewer is considered local */
	OR_Bool	GetLocalViewer();
	/** set the local viewer mode
		\return previous value of local viewer mode */
	OR_Bool SetLocalViewer( OR_Bool Local );
	/** force the local viewer mode
		\return previous value of local viewer mode */
	OR_Bool ForceLocalViewer( OR_Bool Local );
	/** set the default local viewer mode
		\return previous value of local viewer mode */
	OR_Bool SetDefaultLocalViewer();
	/** force the default local viewer mode
		\return previous value of local viewer mode */
	OR_Bool ForceDefaultLocalViewer();

	/* Perspective correction *********************************************************/
	/** \return true if the perspective correction is enabled */
	OR_Bool GetPerspectiveCorrection();
	/** set the perspective correction
		\return previous value of perspective correction */
	OR_Bool SetPerspectiveCorrection( OR_Bool Correction );
	/** force the perspective correction
		\return previous value of perspective correction */
	OR_Bool ForcePerspectiveCorrection( OR_Bool Correction );
	/** set the default perspective correction
		\return previous value of perspective correction */
	OR_Bool SetDefaultPerspectiveCorrection();
	/** force the default perspective correction
		\return previous value of perspective correction */
	OR_Bool ForceDefaultPerspectiveCorrection();
	 
	/* Normalization *********************************************************/
	/** \return true if the normalization is enabled */
	OR_Bool GetNormalization();
	/** set the normalization
		\return previous value of normalization */
	OR_Bool SetNormalization( OR_Bool Normalization );
	/** force the normalization
		\return previous value of normalization */
	OR_Bool ForceNormalization( OR_Bool Normalization );
	/** set the default normalization
		\return previous value of normalization */
	OR_Bool SetDefaultNormalization();
	/** force the default normalization
		\return previous value of normalization */
	OR_Bool ForceDefaultNormalization();

	/* Vertex weighting management *********************************************************/
	/** \return true if the Vertex Weighting is enabled */
	OR_Bool GetVertexWeighting();
	/** set the Vertex Weighting
		\return previous value of Vertex Weighting */
	OR_Bool SetVertexWeighting( OR_Bool VertexWeighting );
	/** force the Vertex Weighting
		\return previous value of Vertex Weighting */
	OR_Bool ForceVertexWeighting( OR_Bool VertexWeighting );
	/** set the default Vertex Weighting
		\return previous value of Vertex Weighting */
	OR_Bool SetDefaultVertexWeighting();
	/** force the default Vertex Weighting
		\return previous value of Vertex Weighting */
	OR_Bool ForceDefaultVertexWeighting();

	
	/* stencil buffer management *********************************************************/


	/* environement mapping management ***************************************************/


	/* depth test management BOOL ********************************************************/
		/** enable DepthTesting mode.
		\return previous value of DepthTesting mode */
	OR_Bool EnableDepthTesting();
	/** disable DepthTesting mode.
		\return previous value of DepthTesting mode */
	OR_Bool DisableDepthTesting();
	/** force DepthTesting mode.
		\return previous value of DepthTesting mode */
	OR_Bool ForceDepthTesting( OR_Bool Mode );
	/** toggle DepthTesting mode.
		\return previous value of DepthTesting mode */
	OR_Bool ToggleDepthTesting();
	/** set the default DepthTesting mode 
		\return previous value of DepthTesting mode*/
	OR_Bool SetDefaultDepthTestingMode();
	/** set the default DepthTesting mode 
		\return previous value of DepthTesting mode*/
	OR_Bool ForceDefaultDepthTestingMode();
	/** get DepthTestingmode.
		\return current value of DepthTesting mode */
	OR_Bool GetDepthTestingMode() const;

	/* Drawing management */
	/** get the current culling mode */
	OR_Drawing_Mode GetDrawingMode() const;
	/** set the current culling mode 
		\return the previous culling mode */
	OR_Drawing_Mode SetDrawingMode(OR_Drawing_Mode mode);
	/** set the current culling mode 
		\return the previous culling mode */
	OR_Drawing_Mode ForceDrawingMode(OR_Drawing_Mode mode);
	/** reset the default culling mode
		\return the previous culling mode */
	OR_Drawing_Mode SetDefaultDrawingMode();
	/** reset the default culling mode
		\return the previous culling mode */
	OR_Drawing_Mode ForceDefaultDrawingMode();

};

} // namespace OR

#ifdef OR_USE_INLINE
#   include "OR_Context.inl"
#endif

#endif /* #ifndef _OR_CONTEXT_H_ */


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

