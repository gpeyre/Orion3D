
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShaderManager.h
 *  \brief Definition of class \c OR_ShaderManager
 *  \author Gabriel Peyré 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ShaderManager_h_
#define __OR_ShaderManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Shader.h"
#include "OR_FlatShader.h"
#include "OR_ReflexiveMapShader.h"
#include "OR_SingleTextureMapShader.h"
#include "OR_CartoonShader.h"
#include "OR_BillboardShader.h"
#include "../utils/OR_SmartManagerMap_Template.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ShaderManager
 *  \brief  Manager of shaders.
 *  \author Gabriel Peyré 2001-10-29
 *  
 *	Contains a copy of every shader in the engine.
 *	This alow to have an easy acces to each shader.
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Shader>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_SmartManagerMap_Template<OR_Shader>;
	
class ORION3D_API OR_ShaderManager: public OR_SmartManagerMap_Template<OR_Shader>, public OR_Serializable, public OR_ShellObject_ABC
{

public:
	
	/** add new flat shader */
	OR_I32 AddFlatShader();
	/** add new single texture shader */
	OR_I32 AddSingleTextureMapShader(char* adresse);
	/** add new reflexive shader */
	OR_I32 AddReflexiveMapShader(char* adresse1=NULL, char* adresse2=NULL,
						  char* adresse3=NULL, char* adresse4=NULL,
						  char* adresse5=NULL, char* adresse6=NULL);
	/** add new cartoon shader */
	OR_I32 AddCartoonShader(OR_I32 bordershader, OR_I32 middleshader);
	/** add new bilboard shader */
	OR_I32 AddBillboardShader(OR_I32 myshader);	
	
	/** set the ambient channel */
	OR_I32 SetAmbient(OR_Float ambient[4]);
	/** set the ambient channel for only one component */
	OR_I32 SetAmbient(OR_Coord_RVBA c,OR_Float val);
	/** set the diffuse channel */
	OR_I32 SetDiffuse(OR_Float diffuse[4]);
	/** set the diffuse channel for only one component */
	OR_I32 SetDiffuse(OR_Coord_RVBA c,OR_Float val);
	/** set the specular channel */
	OR_I32 SetSpecular(OR_Float specular[4]);
	/** set the specular channel for only one component */
	OR_I32 SetSpecular(OR_Coord_RVBA c,OR_Float val);
	/** set the emission channel */
	OR_I32 SetEmission(OR_Float emission[4]);
	/** set the emission channel for only one component */
	OR_I32 SetEmission(OR_Coord_RVBA c,OR_Float val);
	/** set the shine channel */
	OR_I32 SetShine(OR_Float shine);
	/** set the alpha componnent for ambient & diffuse */
	OR_I32 SetAlpha(OR_Float val);
	/** return the type of the shader */
	OR_Elements GetType();
	/** re-set the texture */
	OR_I32 LoadTexture( const char * adresse , OR_I32 num );
	/** set the border width : for cartoon shader only */
	OR_I32 SetBorderWidth(OR_I32 val);

	OR_Shader* GetShaderByName(const OR_String& name);


	//-------------------------------------------------------------------------
	/** \name serialization methods */
	//-------------------------------------------------------------------------
	//@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File &file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File &file );
	
	OR_DEFINE_SERIALIZATION(OR_ShaderManager);
	//@}

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	/**
		Usefull function : return a string for each element in the list.
		[used by the shell to automaticaly build a list of name for the sub-directories]
	*/
	OR_String GetUniqueString(IT_ManagerMap_Template(OR_Shader) itIterator)
	{
		for( IT_ManagerMap_Template(OR_Shader) it = this->begin(); it!=this->end(); ++it )
		{
			if( it==itIterator )
			{
				/* the element has been found */
				return (*it).second->GetName();
			}
		}
		/* oups, the object has not been found */
		OR_Globals::MessageHandler()->Warning("OR_Manager_Template_Object::GetUniqueString", "The object doesn't belong to the manager.");

		return OR_String("not_found");
	}
    //@}
};
	

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ShaderManager.inl"
#endif


#endif // __OR_ShaderManager_h_

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

