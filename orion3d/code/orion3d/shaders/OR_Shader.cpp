/*--------------------------------------------------------------*/
/*                       OR_Shader.cpp                          */
/*--------------------------------------------------------------*/
/* implementation of all different shaders                      */
/*--------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Shader.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Shader.h"
#include "OR_Shadable.h"
#include "../utils/OR_File.h"

#ifndef OR_USE_INLINE
#   include "OR_Shader.inl"
#endif

namespace OR
{

/*--------------------------------------------------------------*/
/*            class OR_Shader                                   */
/*--------------------------------------------------------------*/

OR_Shader::OR_Shader()
:	OR_SmartCounter(),
	OR_ShellObject_ABC(),
	bNeedsSorting_	( false ),
	BlendingMode_	( OR_Blending_None )
{
	Ambient[X]=Ambient[Y]=Ambient[Z]=0;
	Ambient[A]=1;
	Diffuse[X]=Diffuse[Y]=Diffuse[Z]=0;
	Diffuse[A]=1;
	Specular[X]=Specular[Y]=Specular[Z]=0;
	Specular[A]=1;
	Emission[X]=Emission[Y]=Emission[Z]=0;
	Emission[A]=1;
	Shine=100;
	
	CullingMode=OR_Culling_Back;
}


void OR_Shader::SetShine(OR_Float shine)
{
	Shine=shine;
}

void OR_Shader::SetAlpha(OR_Float val)
{
	Ambient[A]=val;
	Diffuse[A]=val;
	Specular[A]=val;
	Emission[A]=val;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::SetAmbientDiffuse
 *
 *  \param  color[4] the ambient and diffuse colors.
 *  \author Gabriel Peyré 2001-10-23
 *
 *	This function set up both ambient and diffuse color.
 *	It is used mainly by the particules system.
 *	For example, bilboard shader should overload it to set up the color of the
 *	base shader.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Shader::SetAmbientDiffuse(OR_Float color[4])
{
	this->SetAmbient( color );
	this->SetDiffuse( color );
}


/* serialization methods ***************************************/
void OR_Shader::BuildFromFile( OR_File& file )
{
	/* load the shader specific datas */
	file >> Name
		 >> Ambient
		 >> Diffuse
		 >> Specular
		 >> Emission
		 >> Shine
		 >> CullingMode;
}

void OR_Shader::BuildToFile( OR_File& file )
{
	/* save the shader specific datas */
	file << Name
		 << Ambient
		 << Diffuse
		 << Specular
		 << Emission
		 << Shine
		 << CullingMode;
}

/*------------------------------------------------------------------------------ 
* Name : OR_Shader::PostExportPass 
* 
*  \author Antoine Bouthors 2002-01-05 
* 
* Function called by the shader manager after all shaders of a file have been loaded
*------------------------------------------------------------------------------*/ 
void OR_Shader::PostExportPass() 
{ 
} 



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::GetShaderTypeString
 *
 *  \return a string representing the type of the shader.
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
OR_String OR_Shader::GetShaderTypeString()
{
	OR_String TypeName;
	
#define BUILD_STRING(type)			\
	case type:  TypeName = #type;	\
	break;
	
	switch( this->GetType() )
	{
		BUILD_STRING(OR_SHADER)
		BUILD_STRING(OR_SHADER_Flat)
		BUILD_STRING(OR_SHADER_SingleTextureMap) 
		BUILD_STRING(OR_SHADER_Reflexive)
		BUILD_STRING(OR_SHADER_Cartoon) 
		BUILD_STRING(OR_SHADER_Billboard)
		BUILD_STRING(OR_SHADER_Bump_Emboss) 
	default:
		TypeName = "undefined";
		break;
	}
	
#undef BUILD_STRING
	
	return TypeName;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 *
 *	Should be overloaded by complex shaders.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Shader::BuildSonList(T_ShellObjectList& ShellSonList)
{
	
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Shader::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{	
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList,	Name);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList,	Shine);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList,	Alpha);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList,	NeedsSorting);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList,	ShaderTypeString);

	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList,	Diffuse);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList,	Specular);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList,	Ambient);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList,	Emission);

	OR_ADD_SHELL_FUNC(FuncDeclList, SetCullingMode, "Set the culling mode (\"OR_Culling_Front\", \"OR_Culling_Back\", \"OR_Culling_None\").");
	OR_ADD_SHELL_FUNC(FuncDeclList, PrintCullingMode, "Print the culling mode.");
	
	OR_ADD_SHELL_FUNC(FuncDeclList, SetBlendingMode, "Set the blending mode (\"OR_Blending_SrcA_1MinusSrcA\", \"OR_Blending_SrcA_1\", \"OR_Blending_SrcA_0\", \"OR_Blending_1_1\", \"OR_Blending_None\").");
	OR_ADD_SHELL_FUNC(FuncDeclList, PrintBlendingMode, "Print the blending mode");
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::SetCullingMode
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Shader::SetCullingMode(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( SetCullingMode, 1 );
	
	/** todo */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::SetBlendingMode
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Shader::SetBlendingMode(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( SetBlendingMode, 1 );
	
	/** todo */
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::PrintCullingMode
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Shader::PrintCullingMode(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( PrintCullingMode, 0 );
	
	/** todo */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader::PrintBlendingMode
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Shader::PrintBlendingMode(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( PrintBlendingMode, 0 );
	
	/** todo */
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