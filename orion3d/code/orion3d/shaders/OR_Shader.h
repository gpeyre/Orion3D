/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Shader.h
 *  \brief Definition of class \c OR_Shader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _OR_SHADER_H_
#define _OR_SHADER_H_

#include "OR_Texture.h"
#include "../configuration/OR_Config.h"
#include "../objects/OR_Mesh.h"
#include "../opengl/OR_GLExtensionsManager.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_File.h"
#include "../utils/OR_ManagerMap_Template.h"
#include "../maths/OR_Maths.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"

using std::list;

namespace OR
{
	
class OR_Shadable;


/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Shader
 *  \brief  Base class for all shaders.
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_Shader: public OR_Serializable, public OR_SmartCounter, public OR_ShellObject_ABC
{

public:

    //-------------------------------------------------------------------------
    /** \name constructor & destructor */
    //-------------------------------------------------------------------------
    //@{
	/** constructor */
	OR_Shader();
	/** destructor */
	virtual ~OR_Shader() { }
    //@}

    //-------------------------------------------------------------------------
    /** \name Name management */
    //-------------------------------------------------------------------------
    //@{
	/** get the shader name */
	OR_String& GetName()
	{ return Name; }
	const OR_String& GetName() const
	{ return Name; }
	/** set the shader name */
	void SetName( const char* name )
	{ Name = name; }
	void SetName( const OR_String& name )
	{ Name = name; }
    //@}

    //-------------------------------------------------------------------------
    /** \name color management */
    //-------------------------------------------------------------------------
    //@{
	/**
		This macro declare for each XXXX component :
			- virtual void SetXXXX(const OR_Float color[4])
			- virtual OR_Vector4D& GetXXXX()
			- virtual void SetXXXX(const OR_Vector4D& color)
			- virtual void SetXXXX(OR_Coord_RVBA c, OR_Float val)
	*/
	#define DECL_ACCESSOR(name)								\
	virtual void Set##name(const OR_Float color[4])			\
	{	name[X]=color[X];name[Y]=color[Y];					\
		name[Z]=color[Z];name[A]=color[A];	}				\
	virtual OR_Vector4D& Get##name()						\
	{ return name; }										\
	virtual void Set##name(const OR_Vector4D& color)		\
	{ this->Set##name(color.GetCoord()); }					\
	virtual void Set##name(OR_Coord_RVBA c, OR_Float val)	\
	{ name[c]=val; }

	DECL_ACCESSOR(Ambient);
	DECL_ACCESSOR(Diffuse);
	DECL_ACCESSOR(Specular);
	DECL_ACCESSOR(Emission);

	#undef DECL_ACCESSOR

	/** get the shine channel */
	virtual OR_Float GetShine()
	{ return Shine; }
	/** set the shine channel */
	void SetShine(OR_Float shine);
	/** get the alpha value (ambient value) */
	virtual OR_Float GetAlpha()
	{ return Ambient[A]; }
	/** set the alpha componnent for ambient & diffuse */
	void SetAlpha(OR_Float val);

	virtual void SetAmbientDiffuse(OR_Float color[4]);

	void SetUpColor();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name Culling management */
    //-------------------------------------------------------------------------
    //@{
	/** modify the culling */
	void SetCullingMode(OR_Culling_Mode mode);
	/** get the culling mode used by the shader */
	OR_Culling_Mode GetCullingMode();
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	/** return the type of the shader */
	virtual OR_Elements GetType()
	{ return OR_SHADER; }

	/** check if the hardware support bump mapping */
	virtual OR_Bool IsShaderSupported()
	{ return true; }
    //@}

    //-------------------------------------------------------------------------
    /** \name helpers */
    //-------------------------------------------------------------------------
    //@{
	OR_String GetShaderTypeString();
    //@}

    //-------------------------------------------------------------------------
    /** \name alpha channel methods */
    //-------------------------------------------------------------------------
    //@{
	virtual OR_Bool NeedsSorting();
	/** synonymous with \c NeedsSorting() */
	OR_Bool GetNeedsSorting()
	{ return this->NeedsSorting(); }

	void SetNeedsSorting( OR_Bool bNeedsSorting );
	OR_Blending_Mode GetBlendingMode();
	void SetBlendingMode( OR_Blending_Mode  BlendingMode );
    //@}

    //-------------------------------------------------------------------------
    /** \name to process the pixel shader stage */
    //-------------------------------------------------------------------------
    //@{
	/** render the vertex array to screen */
	virtual void ProcessShader(OR_Shadable& object)=0;
    //@}

	//-------------------------------------------------------------------------
    /** \name serialization methods  */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	/** Function called by the shader manager after all shaders of a file have been loaded */
	virtual void PostExportPass();
    //@}

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	
	OR_DECL_SHELL_ACCESSOR_FUNC(Name,			OR_Shader, String);
	OR_DECL_SHELL_ACCESSOR_FUNC(Shine,			OR_Shader, Float);
	OR_DECL_SHELL_ACCESSOR_FUNC(Alpha,			OR_Shader, Float);
	OR_DECL_SHELL_ACCESSOR_FUNC(NeedsSorting,	OR_Shader, Bool);
	OR_DECL_SHELL_GET_PRINT_FUNC(ShaderTypeString,	OR_Shader, String);

	OR_DECL_SHELL_ACCESSOR_FUNC(Diffuse,	OR_Shader, Vector4D);
	OR_DECL_SHELL_ACCESSOR_FUNC(Specular,	OR_Shader, Vector4D);
	OR_DECL_SHELL_ACCESSOR_FUNC(Ambient,	OR_Shader, Vector4D);
	OR_DECL_SHELL_ACCESSOR_FUNC(Emission,	OR_Shader, Vector4D);
	
	OR_DECL_SHELL_FUNC(SetCullingMode, 0);
	OR_DECL_SHELL_FUNC(PrintCullingMode, 0);

	OR_DECL_SHELL_FUNC(SetBlendingMode, 0);
	OR_DECL_SHELL_FUNC(PrintBlendingMode, 0);
    //@}

protected:

	/** name of the shader */
	OR_String Name;
	/** ambient color channel */
	OR_Vector4D Ambient;
	/** diffuse color channel */
	OR_Vector4D Diffuse;
	/** specular color channel */
	OR_Vector4D Specular;
	/** emission color channel */
	OR_Vector4D Emission;
	/** shine color channel */
	OR_Float Shine;
	/** type of culling */
	OR_Culling_Mode CullingMode;

	/** does the shader needs to be handled by the alpha pipeline */
	OR_Bool bNeedsSorting_;
	/** wich kind of blending mode does this shader use */
	OR_Blending_Mode BlendingMode_;

};

} // namespace OR

#ifdef OR_USE_INLINE
#   include "OR_Shader.inl"
#endif

#endif /* #ifndef _OR_SHADER_H_ */


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