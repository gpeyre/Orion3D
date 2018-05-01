//*****************************************************************************
/// \author Gabriel Peyré
//*****************************************************************************

#include "OR_Shader.h"

namespace OR {

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::NeedsSorting
 *
 *  \return does this shader needs to be handled by the alpha pipeline ?
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Shader::NeedsSorting()
{
	return bNeedsSorting_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::SetNeedsSorting
 *
 *  \param  bNeedsSorting does this shader needs to be handled by the alpha pipeline ?
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Shader::SetNeedsSorting(OR_Bool bNeedsSorting)
{
	bNeedsSorting_ = bNeedsSorting;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::GetBlendingMode
 *
 *  \return The kind of blending mode used by this shader.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Blending_Mode OR_Shader::GetBlendingMode()
{
	return BlendingMode_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::SetBlendingMode
 *
 *  \param  BlendingMode The kind of blending mode used by this shader.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Shader::SetBlendingMode( OR_Blending_Mode  BlendingMode )
{
	BlendingMode_ = BlendingMode;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::SetCullingMode
 *
 *  \param  mode the culling mode (front/back/both) used by the shader.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Shader::SetCullingMode(OR_Culling_Mode mode)
{ 
	CullingMode=mode; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::GetCullingMode
 *
 *  \return the culling mode (front/back/both) used by the shader.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Culling_Mode OR_Shader::GetCullingMode()
{ 
	return CullingMode; 
}

//-----------------------------------------------------------------------------
// Name: OR_Shader::SetUpColor
/**
*	Set up OpenGL materials proprieties according to the shader colors.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Shader::SetUpColor()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular.GetCoord());
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient.GetCoord());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse.GetCoord());
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Emission.GetCoord());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Shine);
}


} // End namespace OR
