/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MultishaderToken.cpp
 *  \brief Definition of class \c OR_MultishaderToken
 *  \author Antoine Bouthors 2002-04-04
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MultishaderToken.cpp (c) Gabriel Peyré & Antoine Bouthors 2002";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_MultishaderToken.h"

#ifndef OR_USE_INLINE
	    #include "OR_MultishaderToken.inl"
#endif

using namespace OR;



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken constructor
 *
 *  \param  Id=0 Id of the sub-shader
 *  \param  Shader=NULL the sub-shader
 *  \param  Indices=NULL the vertex indices the sub-shader will affect
 *  \param  NbrIndices=0 the number of indices
 *  \author Antoine Bouthors 2002-04-04
 *
 * OR_MultishaderToken constructor
 */ 
/*------------------------------------------------------------------------------*/
OR_MultishaderToken::OR_MultishaderToken( OR_U32 Id, OR_Shader* Shader, const OR_U32* Indices, OR_U32 NbrIndices )
:	OR_Serializable(),
	m_Id( Id ),
	m_Shader( Shader )
{
	if( Indices && NbrIndices )
	{
		m_Indices.resize( NbrIndices, 0 );
		memcpy( &(m_Indices.front()), Indices, NbrIndices*sizeof(OR_U32) );
	}

	if( m_Shader ) m_Shader->UseIt();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken copy constructor
 *
 *  \param  Dup the token to copy from
 *  \author Antoine Bouthors 2002-04-04
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_MultishaderToken::OR_MultishaderToken( const OR_MultishaderToken& Dup )
:	OR_Serializable( Dup ),
	m_Id( Dup.m_Id ),
	m_Shader( Dup.m_Shader ),
	m_Indices( Dup.m_Indices ),
	m_Name( Dup.m_Name )
{
	if( m_Shader ) m_Shader->UseIt();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken copy operator
 *
 *  \param  Dup the token to copy from
 *  \return this
 *  \author Antoine Bouthors 2002-04-04
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_MultishaderToken& OR_MultishaderToken::operator=( const OR_MultishaderToken& Dup )
{
	m_Id = Dup.m_Id;
	m_Shader = Dup.m_Shader;
	m_Indices = Dup.m_Indices;
	m_Name = Dup.m_Name;
	if( m_Shader ) m_Shader->UseIt();

	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken destructor
 *
 *  \author Antoine Bouthors 2002-04-04
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_MultishaderToken::~OR_MultishaderToken()
{
	if( m_Shader ) OR_SmartCounter::CheckAndDelete( m_Shader );
    m_Indices.clear();
	m_Id = 0;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MultishaderToken::BuildFromFile
 *
 *  \author Antoine Bouthors 2002-04-04
 *
 * Retrieve the id, the name and the indices
 */ 
/*------------------------------------------------------------------------------*/
void OR_MultishaderToken::BuildFromFile( OR_File& File )
{
	OR_U32 i, NbrIndices, CurrentIndice;

	File	>> m_Id
			>> m_Name
			>> NbrIndices;
	
	m_Indices.resize( NbrIndices, 0 );
	for( i=0 ; i<NbrIndices ; ++i )
	{
		File >> CurrentIndice;
		m_Indices[i] = CurrentIndice;
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MultishaderToken::BuildToFile
 *
 *  \author Antoine Bouthors 2002-04-04
 *
 * Write the id, the name and the indices
 */ 
/*------------------------------------------------------------------------------*/
void OR_MultishaderToken::BuildToFile( OR_File& File )
{
	OR_U32 i, NbrIndices;

	NbrIndices = (OR_U32)m_Indices.size();

	File	<< m_Id
			<< m_Shader->GetName()
			<< NbrIndices;

	for( i=0 ; i<NbrIndices ; ++i )
	{
		File << m_Indices[i];
	}
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MultishaderToken::
 *
 *  \author Antoine Bouthors 2002-04-04
 *
 * Retrieve the OR_Shader* from its name
 */ 
/*------------------------------------------------------------------------------*/
void OR_MultishaderToken::PostExportPass()
{
	OR_Shader* Shader = OR_Globals::ShaderManager()->GetShaderByName( m_Name );
	OR_ASSERT( Shader != NULL );
	m_Shader = Shader;

	m_Shader->UseIt();

#ifndef OR_DEBUG
	m_Name.clear();	 //I prefer keeping it for debug purposes
#endif
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

