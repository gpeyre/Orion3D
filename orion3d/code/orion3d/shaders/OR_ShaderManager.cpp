/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShaderManager.cpp
 *  \brief Definition of class \c OR_ShaderManager
 *  \author Gabriel Peyré 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ShaderManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ShaderManager.h"

#ifndef OR_USE_INLINE
	#include "OR_ShaderManager.inl"
#endif

using namespace OR;

/*----------------------------------------------------------------------*/
/*                        classe OR_ShaderManager						*/
/*----------------------------------------------------------------------*/
/*		permet de gerer plusieurs shaders via une liste chainee	     	*/
/*----------------------------------------------------------------------*/
/* herite de la classe OR_ShaderManager		     						*/
/*----------------------------------------------------------------------*/

OR_I32 OR_ShaderManager::AddFlatShader()
{
	OR_FlatShader* new_shader=new OR_FlatShader();
	return AddElement(new_shader);
}

OR_I32 OR_ShaderManager::AddSingleTextureMapShader(char* adresse)
{
	OR_SingleTextureMapShader* new_shader=new OR_SingleTextureMapShader(adresse);
	return AddElement(new_shader);
}

OR_I32 OR_ShaderManager::AddReflexiveMapShader(char* adresse1, char* adresse2,
						      char* adresse3, char* adresse4,
						      char* adresse5, char* adresse6)
{
	OR_ReflexiveMapShader* new_shader=new OR_ReflexiveMapShader(adresse1, adresse2,
		adresse3, adresse4, adresse5, adresse6);
	return AddElement(new_shader);
}

OR_I32 OR_ShaderManager::AddCartoonShader(OR_I32 bordershader, OR_I32 middleshader)
{
	OR_CartoonShader* new_shader=new  
		OR_CartoonShader(SearchElement(bordershader), SearchElement(middleshader));
	return AddElement(new_shader);
}

OR_I32 OR_ShaderManager::AddBillboardShader(OR_I32 myshader)
{
	OR_BillboardShader* new_shader=new OR_BillboardShader(SearchElement(myshader));
	return AddElement(new_shader);
}

OR_I32 OR_ShaderManager::LoadTexture( const char* adresse, OR_I32 num )
{
	switch (GetElementSelected()->GetType())
	{
	case OR_SHADER_SingleTextureMap:
		((OR_SingleTextureMapShader*) GetElementSelected())->LoadTexture(adresse);
		return 0;
		break;
	case OR_SHADER_Reflexive:
		((OR_ReflexiveMapShader*) GetElementSelected())->LoadTexture(adresse, num);
		return 0;
		break;
	default:
		return 1;
		break;
	};
}

OR_I32 OR_ShaderManager::SetBorderWidth(OR_I32 val)
{
	if (IsSelectedEmpty()) return 1;
	if (GetElementSelected()->GetType()!=OR_SHADER_Cartoon)
		return 1; 
	((OR_CartoonShader*) GetElementSelected())->SetBorderWidth(val);
	return 0;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader* OR_ShaderManager::GetShaderByName()
 *
 *  \author Gabriel Peyré 2002/03/21
 *	\return \c NULL if the search fails.
 *
 *	Retrieve a shader given it's name. Mainly use by the serialization process.
 */ 
/*------------------------------------------------------------------------------*/
OR_Shader* OR_ShaderManager::GetShaderByName(const OR_String& name)
{
	for( IT_ManagerMap_Template(OR_Shader) it = begin( ); it != end( ); ++ it ) 
	{
		OR_Shader* pShader = (*it).second;
		if( pShader->GetName()==name )
			return pShader;
	}
	/* search failed */
	return NULL;
}


/* saving methods **********************************************/
void OR_ShaderManager::BuildFromFile( OR_File& file) 
{
	IT_ManagerMap_Template( OR_Shader ) it;

	/* read the number of shader */
	OR_U32 nNbrShader;
	file >> nNbrShader;

	/* re-size IndexToNumShader */
	OR_Globals::ResizeIndexToNumShader(nNbrShader);

	for (OR_U32 i=0; i<nNbrShader; i++)
	{
		OR_Shader* pShader = (OR_Shader*) &OR_ClassFactory::BuildFromFile(file);
	
		/* todo : enlever des que Toche mettra autre chose que 0 ! */
		pShader->SetAlpha(1);
		/* TODO : enlever le *100 des que antoche a corriger le chbince */
		pShader->SetShine(100);

		/* save the ID of the shader and the shader */
		OR_Globals::SetIndexToNumShader( i, OR_Globals::ShaderManager()->AddElement(pShader) );
	}

	for( it = begin( ); it != end( ); ++ it ) 
	{ 
		OR_Shader * pShader = ( * it ).second; 

		/* apply the post-export pass */
		pShader->PostExportPass();
	}
}


void OR_ShaderManager::BuildToFile( OR_File& file )
{
	/* export the number of shader */
	OR_U32 nb=GetNbElements();
	file << nb;

	/* iterate on each shader */ 
	for( IT_ManagerMap_Template( OR_Shader ) it = begin( ); it != end( ); ++ it ) 
	{ 
		OR_Shader * pShader = ( * it ).second; 
		/* export the shader to a file */
		OR_ClassFactory::BuildToFile(  file, *pShader  );
	}
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShaderManager::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 *
 *	Should be overloaded by complex shaders.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShaderManager::BuildSonList(T_ShellObjectList& ShellSonList)
{
	OR_SHELL_BUILD_MANAGER_SON_LIST( ShellSonList, OR_Shader, "shader" );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShaderManager::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShaderManager::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	/* NOTHING */
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

