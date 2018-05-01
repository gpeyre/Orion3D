
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MultishaderToken.h
 *  \brief Definition of class \c OR_MultishaderToken
 *  \author Antoine Bouthors 2002-04-04
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_MultishaderToken_h_
#define __OR_MultishaderToken_h_

#include "../configuration/OR_Config.h"
#include "OR_Shader.h"
#include "OR_ShaderManager.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MultishaderToken
 *  \brief  Defines a sub-shader for the multishader shader
 *  \author Antoine Bouthors 2002-04-04
 *  Each sub-shader is described by an id, the shader which is applied, and a
 *  list of faces on which it is applied. 
 */ 
/*------------------------------------------------------------------------------*/

class OR_MultishaderToken: public OR_Serializable
{

public:

    OR_MultishaderToken( OR_U32 Id=0, OR_Shader* Shader=NULL, const OR_U32* Indices=NULL, OR_U32 NbrIndices=0 );
	OR_MultishaderToken( const OR_MultishaderToken& Dup );
	OR_MultishaderToken& operator=( const OR_MultishaderToken& Dup );
    virtual ~OR_MultishaderToken();

    //-------------------------------------------------------------------------
    /** \name Get methods */
    //-------------------------------------------------------------------------
    //@{
	OR_Shader*			GetShader();
	const OR_Shader*	GetShader() const;
	OR_U32				GetId();
	T_U32Vector&		GetIndices();
	const T_U32Vector&	GetIndices() const;
    //@}

    //-------------------------------------------------------------------------
    /** \name Set methods */
    //-------------------------------------------------------------------------
    //@{
	void	SetShader( OR_Shader* Shader );
	void	SetId( OR_U32 Id );
	void	SetIndices( const OR_U32* Indices, OR_U32 NbrIndices );
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

	OR_DEFINE_SERIALIZATION(OR_MultishaderToken);
	//@}

private:

	OR_U32		m_Id;
	OR_String	m_Name;
	OR_Shader*	m_Shader;
	T_U32Vector	m_Indices;

};

///a list of OR_MultishaderToken
typedef list<OR_MultishaderToken> T_MultishaderTokenList;
///iterator for T_MultishaderTokenList
typedef T_MultishaderTokenList::iterator IT_MultishaderTokenList;
///const iterator for T_MultishaderTokenList
typedef T_MultishaderTokenList::const_iterator CIT_MultishaderTokenList;




} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_MultishaderToken.inl"
#endif


#endif // __OR_MultishaderToken_h_

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

