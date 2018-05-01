/*------------------------------------------------------------------------------
 *  \file  OR_MultiShader.h
 *  \brief Definition of class \c OR_MultiShader
 *  \author Antoine Bouthors 2001-11-21
 *------------------------------------------------------------------------------*/

#ifndef __OR_MultiShader_h_
#define __OR_MultiShader_h_

#include "../configuration/OR_Config.h"
#include "OR_Shader.h"
#include "OR_ShaderManager.h"
#include "OR_MultishaderToken.h"
using std::map;

namespace OR {

typedef map<OR_Shader*, T_U32Vector>		T_ShaderMap;
typedef T_ShaderMap::iterator		IT_ShaderMap;
typedef T_ShaderMap::const_iterator	CIT_ShaderMap;

/*------------------------------------------------------------------------------
 *  \class  OR_MultiShader
 *  \brief  This is the equivalent of the multimaterial type in 3DSMAX
 *  \author Antoine Bouthors 2001-11-21
 *  If you want to apply different shaders to different sets of faces for
 *  an object, this is the class to use.
 *  \warning note that the indices for each shader are stored in the multishader
 *  and NOT in the object, unlike 3DSMAX which stores a material ID for each face.
 *  this means that you can't use the same multishader for two objets that are
 *  not similar.
 *------------------------------------------------------------------------------*/

class ORION3D_API OR_MultiShader : public OR_Shader
{

public:

    OR_MultiShader();
    OR_MultiShader( const OR_MultiShader& Dup );
	OR_MultiShader& operator=( const OR_MultiShader& Dup );
    virtual ~OR_MultiShader();

	/** return the type of the shader */
	virtual OR_Elements GetType()
	{ return OR_Shader_Multi; }

	/* to process the pixel shader stage ******************************/
	/** render the vertex array to screen */
	virtual void		ProcessShader( OR_Shadable& object );
	virtual OR_Bool		NeedsSorting();

	void				AddShader( OR_Shader* Shader, const OR_U32* Indices, OR_U32 NbrIndices );
	void				SetFacesIndicesForShader( OR_Shader* Shader, const OR_U32* Indices, OR_U32 NbrIndices );
	void				RemoveShader( OR_Shader* Shader );
	T_U32Vector&		GetIndicesForShader( const OR_Shader* Shader );
	const T_U32Vector&	GetIndicesForShader( const OR_Shader* Shader ) const;

	T_MultishaderTokenList&			GetTokens();
	const T_MultishaderTokenList&	GetTokens() const;

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	/** used to set up the target once the export is done. The object has
		to do a look up in ObjectList using it's id number to set the target.
		If Id==0, that mean there is no target. */
	virtual void PostExportPass();
	OR_DEFINE_SERIALIZATION( OR_MultiShader );
    //@}

private:

	T_MultishaderTokenList	m_SubShaders;
	
};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_MultiShader.inl"
#endif



#endif // __OR_MultiShader_h_

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

