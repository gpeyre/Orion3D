//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_Context.h"

namespace OR {


/* culling management ********************************************************************/
OR_INLINE 
OR_Culling_Mode OR_Context::GetCullingMode() const
{
	return CullingMode;
}

OR_INLINE 
OR_Culling_Mode OR_Context::SetCullingMode(OR_Culling_Mode mode)
{
	if (CullingMode!=mode)
	{
		if (CullingMode==OR_Culling_None) glEnable(GL_CULL_FACE);
		/* save the old culling */
		OR_Culling_Mode culling=CullingMode;
		CullingMode=mode;
		if (CullingMode==OR_Culling_Front)
		{
			glCullFace(GL_FRONT);
			return culling;
		}
		else if (CullingMode==OR_Culling_Back)
		{
			glCullFace(GL_BACK);
			return culling;
		}
		else if (CullingMode==OR_Culling_None)
		{
			glDisable(GL_CULL_FACE);
			return culling;
		}
	}
	return CullingMode;
}

OR_INLINE 
OR_Culling_Mode OR_Context::ForceCullingMode(OR_Culling_Mode mode)
{
	/* save the old culling */
	OR_Culling_Mode culling=CullingMode;
	CullingMode=mode;
	if (CullingMode==OR_Culling_Front)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		return culling;
	}
	else if (CullingMode==OR_Culling_Back)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		return culling;
	}
	else if (CullingMode==OR_Culling_None)
	{
		glDisable(GL_CULL_FACE);
		return culling;
	}
	return CullingMode;
}

OR_INLINE 
OR_Culling_Mode OR_Context::SetDefaultCullingMode()
{
	return SetCullingMode( OR_DEFAULT_CULLING_MODE );
}

OR_INLINE 
OR_Culling_Mode OR_Context::ForceDefaultCullingMode()
{
	return ForceCullingMode( OR_DEFAULT_CULLING_MODE );
}


/* line size management ******************************************************************/
OR_INLINE 
OR_Float OR_Context::GetLineSize() const
{
	return LineSize;
}

OR_INLINE 
OR_Float OR_Context::SetLineSize(OR_Float v)
{
	if( v==LineSize ) return LineSize;
	
	OR_Float l=LineSize;
	LineSize=v;
	glLineWidth(LineSize);
	return l;
}

OR_INLINE 
OR_Float OR_Context::ForceLineSize(OR_Float v)
{
	OR_Float l=LineSize;
	LineSize=v;
	glLineWidth(LineSize);
	return l;
}


OR_INLINE 
OR_Float OR_Context::ModifyLineSize(OR_Float v)
{
	LineSize+=v;
	glLineWidth(LineSize);
	return LineSize;
}

OR_INLINE 
OR_Float OR_Context::SetDefaultLineSize()
{
	return SetLineSize( OR_DEFAULT_LINE_SIZE );
}

OR_INLINE 
OR_Float OR_Context::ForceDefaultLineSize()
{
	return ForceLineSize( OR_DEFAULT_LINE_SIZE );
}

/* point size management ****************************************************************/
OR_INLINE 
OR_Float OR_Context::GetPointSize() const
{
	return PointSize;
}

OR_INLINE 
OR_Float OR_Context::SetPointSize(OR_Float v)
{
	if( v == PointSize ) return PointSize;
	
	OR_Float p=PointSize;
	PointSize=v;
	glPointSize(PointSize);
	return p;
}

OR_INLINE 
OR_Float OR_Context::ForcePointSize(OR_Float v)
{
	OR_Float p=PointSize;
	PointSize=v;
	glPointSize(PointSize);
	return p;
}


OR_INLINE 
OR_Float OR_Context::ModifyPointSize(OR_Float v)
{
	PointSize+=v;
	glPointSize(PointSize);
	return PointSize;
}

OR_INLINE 
OR_Float OR_Context::SetDefaultPointSize()
{
	return SetPointSize( OR_DEFAULT_POINT_SIZE );
}

OR_INLINE 
OR_Float OR_Context::ForceDefaultPointSize()
{
	return ForcePointSize( OR_DEFAULT_POINT_SIZE );
}

/* simple color management **************************************************************/
OR_INLINE
void OR_Context::SetColor(OR_Float r, OR_Float v, OR_Float b)
{
	Color[R]=r;
	Color[V]=v;
	Color[B]=b;
	glColor4fv(Color);
}

OR_INLINE 
void OR_Context::SetColor(OR_Float r, OR_Float v, OR_Float b, OR_Float a)
{
	Color[R]=r;
	Color[V]=v;
	Color[B]=b;
	Color[A]=a;
	glColor4fv(Color);
}

OR_INLINE 
void OR_Context::SetColor(OR_Float color[4])
{
	Color[R]=color[R];
	Color[V]=color[V];
	Color[B]=color[B];
	Color[A]=color[A];
	glColor4fv(Color);
}

OR_INLINE 
void OR_Context::SetColor(OR_Coord_RVBA c, OR_Float color)
{
	Color[c]=color;
	glColor4fv(Color);
}

OR_INLINE 
OR_Float* OR_Context::GetColor() const
{
	return (OR_Float*) Color;
}

OR_INLINE 
void OR_Context::SetDefaultColor()
{
	SetColor(OR_DEFAULT_COLOR_R, OR_DEFAULT_COLOR_V, OR_DEFAULT_COLOR_B, OR_DEFAULT_COLOR_A);
}

/* blending management ****************************************************************/
OR_INLINE 
OR_Blending_Mode OR_Context::SetBlendingMode(OR_Blending_Mode mode)
{
	if (BlendingMode!=mode)
	{
		if (BlendingMode==OR_Blending_None) 
			glEnable(GL_BLEND);
		/* save the old blending */
		OR_Blending_Mode blending=BlendingMode;
		BlendingMode=mode;
		switch(BlendingMode)
		{
		case OR_Blending_SrcA_1MinusSrcA:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case OR_Blending_SrcA_1:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case OR_Blending_SrcA_0: 
			glBlendFunc(GL_SRC_ALPHA, GL_ZERO); 
			break;
		case OR_Blending_1_1:
			glBlendFunc(GL_ONE, GL_ONE);
			break;
		case OR_Blending_None:
			glDisable(GL_BLEND);
			break;
		default:
			BlendingMode=OR_Blending_None;
			glDisable(GL_BLEND);
			break;
		}
		return blending;		
	}
	return BlendingMode;
}


OR_INLINE 
OR_Blending_Mode OR_Context::ForceBlendingMode(OR_Blending_Mode mode)
{
	/* save the old blending */
	OR_Blending_Mode blending=BlendingMode;
	BlendingMode=mode;
	switch(BlendingMode)
	{
	case OR_Blending_SrcA_1MinusSrcA:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case OR_Blending_SrcA_1:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case OR_Blending_SrcA_0: 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ZERO); 
		break;
	case OR_Blending_1_1:
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		break;
	case OR_Blending_None:
		glDisable(GL_BLEND);
		break;
	default:
		BlendingMode=OR_Blending_None;
		glDisable(GL_BLEND);
		break;
	}
	return blending;
}


OR_INLINE 
OR_Blending_Mode OR_Context::SetDefaultBlendingMode()
{
	return SetBlendingMode( OR_DEFAULT_BLENDING_MODE );
}

OR_INLINE 
OR_Blending_Mode OR_Context::ForceDefaultBlendingMode()
{
	return ForceBlendingMode( OR_DEFAULT_BLENDING_MODE );
}

OR_INLINE 
OR_Blending_Mode OR_Context::GetBlendingMode() const
{
	return BlendingMode;
}


/* alpha test management *************************************************************/


/* 2D texture management BOOL ********************************************************/
OR_INLINE 
OR_Bool OR_Context::Enable2DTexturing()
{
	if (!Texturing2DMode)
	{
		Texturing2DMode=true;
		glEnable(GL_TEXTURE_2D);
		return false;
	}
	return true;
}
	
OR_INLINE 
OR_Bool OR_Context::Disable2DTexturing()
{
	if (Texturing2DMode)
	{
		Texturing2DMode=false;
		glDisable(GL_TEXTURE_2D);
		return true;
	}
	return false;
}

OR_INLINE 
OR_Bool OR_Context::Toggle2DTexturing()
{
	if (Texturing2DMode)
	{
		glDisable(GL_TEXTURE_2D);
		return Texturing2DMode=false;
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		return Texturing2DMode=true;
	}
}

OR_INLINE 
OR_Bool OR_Context::SetDefault2DTexturingMode()
{
	if( OR_DEFAULT_TEXTURING2D_MODE )
		return Enable2DTexturing();
	else
		return Disable2DTexturing();
}

OR_INLINE 
OR_Bool OR_Context::ForceDefault2DTexturingMode()
{
	return Force2DTexturingMode( OR_DEFAULT_TEXTURING2D_MODE );
}

OR_INLINE 
OR_Bool OR_Context::Get2DTexturingMode() const
{
	return Texturing2DMode;
}


OR_INLINE
OR_Bool OR_Context::Force2DTexturingMode( OR_Bool Mode )
{
	OR_Bool ReturnValue = Texturing2DMode;
	Texturing2DMode = Mode;
	if( Texturing2DMode ) glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);
	
	return ReturnValue;
}


/* lighting management BOOL **********************************************************/
OR_INLINE 
OR_Bool OR_Context::EnableLighting()
{
	if (!LightingMode)
	{
		LightingMode=true;
		glEnable(GL_LIGHTING);
		return false;
	}
	return true;
}

OR_INLINE 
OR_Bool OR_Context::DisableLighting()
{
	if (LightingMode)
	{
		LightingMode=false;
		glDisable(GL_LIGHTING);
		return true;
	}
	return false;
}

OR_INLINE 
OR_Bool OR_Context::ToggleLighting()
{
	if (LightingMode)
	{
		glDisable(GL_LIGHTING);
		return LightingMode=false;
	}
	else
	{
		glEnable(GL_LIGHTING);
		return LightingMode=true;
	}
}

OR_INLINE 
OR_Bool OR_Context::ForceLighting( OR_Bool Mode )
{
	OR_Bool ReturnValue = LightingMode;
	LightingMode = Mode;
	if( LightingMode )
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	return ReturnValue;	
}

OR_INLINE 
OR_Bool OR_Context::ForceDefaultLightingMode()
{
	return ForceLighting( OR_DEFAULT_LIGHTING_MODE );
}

OR_INLINE 
OR_Bool OR_Context::SetDefaultLightingMode()
{
	if( OR_DEFAULT_LIGHTING_MODE )
		return EnableLighting();
	else
		return DisableLighting();
}

OR_INLINE 
OR_Bool OR_Context::GetLightingMode() const
{
	return LightingMode;
}
	 
/* stencil buffer management *********************************************************/


/* environement mapping management ***************************************************/


/* depth test management BOOL ********************************************************/
OR_INLINE 
OR_Bool OR_Context::EnableDepthTesting()
{
	if (!DepthTestingMode)
	{
		DepthTestingMode=true;
		glEnable(GL_DEPTH_TEST);
		return false;
	}
	return true;
}

OR_INLINE 
OR_Bool OR_Context::DisableDepthTesting()
{
	if (DepthTestingMode)
	{
		DepthTestingMode=false;
		glDisable(GL_DEPTH_TEST);
		return true;
	}
	return false;
}

OR_INLINE 
OR_Bool OR_Context::ForceDepthTesting( OR_Bool Mode )
{
	OR_Bool ReturnValue = DepthTestingMode;
	DepthTestingMode = Mode;
	if( DepthTestingMode )
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	return ReturnValue;	
}

	
OR_INLINE 
OR_Bool OR_Context::ToggleDepthTesting()
{
	if (DepthTestingMode)
	{
		glDisable(GL_DEPTH_TEST);
		return DepthTestingMode=false;
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		return DepthTestingMode=true;
	}
}


OR_INLINE 
OR_Bool OR_Context::ForceDefaultDepthTestingMode()
{
	return ForceDepthTesting( OR_DEFAULT_DEPTHTESTING_MODE );
}

OR_INLINE 
OR_Bool OR_Context::SetDefaultDepthTestingMode()
{
	if( OR_DEFAULT_DEPTHTESTING_MODE )
		return EnableDepthTesting();
	else
		return DisableDepthTesting();
}

OR_INLINE 
OR_Bool OR_Context::GetDepthTestingMode() const
{
	return DepthTestingMode;
}

/* drawing management ********************************************************************/
OR_INLINE 
OR_Drawing_Mode OR_Context::GetDrawingMode() const
{
	return DrawingMode;
}

OR_INLINE 
OR_Drawing_Mode OR_Context::SetDrawingMode(OR_Drawing_Mode mode)
{
	OR_Drawing_Mode oldmode = DrawingMode;
	if (DrawingMode!=mode)
	{
		switch (mode)
		{
		case OR_Drawing_Filled:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case OR_Drawing_Wireframe:
	        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case OR_Drawing_Point :
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);	
			break;
		}
		DrawingMode = mode;
	}
	return oldmode;
}


OR_INLINE 
OR_Drawing_Mode OR_Context::ForceDrawingMode(OR_Drawing_Mode mode)
{
	OR_Drawing_Mode oldmode = DrawingMode;

	switch (mode)
	{
	case OR_Drawing_Filled:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case OR_Drawing_Wireframe:
	    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case OR_Drawing_Point :
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);	
		break;
	}
	DrawingMode = mode;

	return oldmode;
}


OR_INLINE 
OR_Drawing_Mode OR_Context::SetDefaultDrawingMode()
{
	return SetDrawingMode( OR_DEFAULT_DRAWING_MODE );
}

OR_INLINE 
OR_Drawing_Mode OR_Context::ForceDefaultDrawingMode()
{
	return ForceDrawingMode( OR_DEFAULT_DRAWING_MODE );
}


/* lighting calculations management ***********/
OR_INLINE 
OR_Bool	OR_Context::GetLocalViewer()
{
	return LocalViewer;
}

OR_INLINE 
OR_Bool OR_Context::SetLocalViewer( OR_Bool Local )
{
	if( Local == LocalViewer ) return LocalViewer;

	LocalViewer = Local;
	if( LocalViewer )
		glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, 1 );
	else
		glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, 0 );

	return !LocalViewer;
}

OR_INLINE 
OR_Bool OR_Context::ForceLocalViewer( OR_Bool Local )
{
	OR_Bool ReturnValue = LocalViewer;
	
	LocalViewer = Local;
	if( LocalViewer )
		glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, 1 );
	else
		glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, 0 );

	return ReturnValue;
}

OR_INLINE 
OR_Bool OR_Context::SetDefaultLocalViewer()
{
	return SetLocalViewer( OR_DEFAULT_LOCAL_VIEWER );
}

OR_INLINE 
OR_Bool OR_Context::ForceDefaultLocalViewer()
{
	return ForceLocalViewer( OR_DEFAULT_LOCAL_VIEWER );
}


/* Perspective correction *********************************************************/
OR_INLINE
OR_Bool OR_Context::GetPerspectiveCorrection()
{
	return PerspectiveCorrection;
}

OR_INLINE
OR_Bool OR_Context::SetPerspectiveCorrection( OR_Bool Correction )
{
	if( Correction == PerspectiveCorrection ) return Correction;

	PerspectiveCorrection = Correction;
	if( Correction )
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	else
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

	return !Correction;
}

OR_INLINE
OR_Bool OR_Context::ForcePerspectiveCorrection( OR_Bool Correction )
{
	OR_Bool ReturnValue = PerspectiveCorrection;

	PerspectiveCorrection = Correction;
	if( Correction )
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	else
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

	return ReturnValue;
}

OR_INLINE
OR_Bool OR_Context::SetDefaultPerspectiveCorrection()
{
	return SetPerspectiveCorrection( OR_DEFAULT_PERSPECTIVE_CORRECTION );
}

OR_INLINE
OR_Bool OR_Context::ForceDefaultPerspectiveCorrection()
{
	return ForcePerspectiveCorrection( OR_DEFAULT_PERSPECTIVE_CORRECTION );
}

/* Normalization *********************************************************/
OR_INLINE
OR_Bool OR_Context::GetNormalization()
{
	return m_Normalization;
}

OR_INLINE
OR_Bool OR_Context::SetNormalization( OR_Bool Normalization )
{
	if( m_Normalization == Normalization ) return Normalization;

	m_Normalization = Normalization;
	if( Normalization )
		glEnable( GL_NORMALIZE );
	else
		glDisable( GL_NORMALIZE );

	return !Normalization;
}

OR_INLINE
OR_Bool OR_Context::ForceNormalization( OR_Bool Normalization )
{
	OR_Bool ReturnValue = m_Normalization;

	m_Normalization = Normalization;
	if( Normalization )
		glEnable( GL_NORMALIZE );
	else
		glDisable( GL_NORMALIZE );

	return ReturnValue;
}

OR_INLINE
OR_Bool OR_Context::SetDefaultNormalization()
{
	return SetNormalization( OR_DEFAULT_NORMALIZATION );
}

OR_INLINE
OR_Bool OR_Context::ForceDefaultNormalization()
{
	return ForceNormalization( OR_DEFAULT_NORMALIZATION );
}

/* Vertex weighting management *********************************************************/
OR_INLINE
OR_Bool OR_Context::GetVertexWeighting()
{
	return m_VertexWeighting;
}

OR_INLINE
OR_Bool OR_Context::SetVertexWeighting( OR_Bool VertexWeighting )
{
	if( m_VertexWeighting == VertexWeighting ) return VertexWeighting;

	m_VertexWeighting = VertexWeighting;
	if( VertexWeighting )
		glEnable( GL_VERTEX_WEIGHTING_EXT );
	else
		glDisable( GL_VERTEX_WEIGHTING_EXT );

	return !VertexWeighting;
}

OR_INLINE
OR_Bool OR_Context::ForceVertexWeighting( OR_Bool VertexWeighting )
{
	OR_Bool ReturnValue = m_VertexWeighting;

	m_VertexWeighting = VertexWeighting;
	if( VertexWeighting )
		glEnable( GL_VERTEX_WEIGHTING_EXT );
	else
		glDisable( GL_VERTEX_WEIGHTING_EXT );

	return ReturnValue;
}

OR_INLINE
OR_Bool OR_Context::SetDefaultVertexWeighting()
{
	return SetVertexWeighting( OR_DEFAULT_VERTEX_WEIGHTING );
}

OR_INLINE
OR_Bool OR_Context::ForceDefaultVertexWeighting()
{
	return ForceVertexWeighting( OR_DEFAULT_VERTEX_WEIGHTING );
}




} // End namespace OR
