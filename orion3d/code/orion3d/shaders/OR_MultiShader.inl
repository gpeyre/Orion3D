/*------------------------------------------------------------------------------
 *  \file  OR_MultiShader.inl
 *  \brief Inlined methods for \c OR_MultiShader
 *  \author Antoine Bouthors 2001-11-21
 *------------------------------------------------------------------------------*/
#include "OR_MultiShader.h"

namespace OR {


/*------------------------------------------------------------------------------
 * Name : OR_MultiShader::AddShader
 *
 *  \param  Shader The shader to add to the Map
 *  \param  Indices The indices of the Shadable affected by the shader
 *  \author Antoine Bouthors 2001-11-21
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_MultiShader::AddShader( OR_Shader* Shader, const OR_U32* Indices, OR_U32 NbrIndices )
{
	OR_ASSERT( Shader != NULL );

	m_SubShaders.push_back( OR_MultishaderToken( 0, Shader, Indices, NbrIndices ) );
}




/*------------------------------------------------------------------------------
 * Name : OR_MultiShader::SetFacesIndicesForShader
 *
 *  \param  Shader The shader you want to set the indices for
 *  \param  Indices An array of vertex indices
 *  \param  NbrIndices The number of VERTEX indices
 *  \author Antoine Bouthors 2001-11-22
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_MultiShader::SetFacesIndicesForShader( OR_Shader* Shader, const OR_U32* Indices, OR_U32 NbrIndices )
{
	OR_ASSERT( Shader != NULL );
	IT_MultishaderTokenList it = m_SubShaders.begin();
	while( it != m_SubShaders.end() && (*it).GetShader() != Shader ) ++it;
	if( it == m_SubShaders.end() ) return;

	(*it).SetIndices( Indices, NbrIndices );
}


/*------------------------------------------------------------------------------
 * Name : OR_MultiShader::GetIndicesForShader
 *
 *  \param  Shader The shader you want to get the indices for
 *  \return A vector containing the faces associated with this shader
 *  \author Antoine Bouthors 2001-11-23
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
T_U32Vector& OR_MultiShader::GetIndicesForShader( const OR_Shader* Shader ) 
{
	OR_ASSERT( Shader != NULL );
	IT_MultishaderTokenList it = m_SubShaders.begin();
	while( it != m_SubShaders.end() && (*it).GetShader() != Shader ) ++it;
	OR_ASSERT( it != m_SubShaders.end() );

	return (*it).GetIndices();
}


/*------------------------------------------------------------------------------
 * Name : OR_MultiShader::GetIndicesForShader
 *
 *  \param  Shader The shader you want to get the indices for
 *  \return A const vector containing the faces associated with this shader
 *  \author Antoine Bouthors 2001-11-23
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
const T_U32Vector& OR_MultiShader::GetIndicesForShader( const OR_Shader* Shader ) const
{
	OR_ASSERT( Shader != NULL );
	CIT_MultishaderTokenList it = m_SubShaders.begin();
	while( it != m_SubShaders.end() && (*it).GetShader() != Shader ) ++it;
	OR_ASSERT( it != m_SubShaders.end() );

	return (*it).GetIndices();
}

/*------------------------------------------------------------------------------
 * Name : OR_MultiShader::GetTokens
 *
 *  \return The list of tokens referencing the subshaders
 *  \author Antoine Bouthors 2001-11-27
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
T_MultishaderTokenList& OR_MultiShader::GetTokens()
{
	return m_SubShaders;
}


/*------------------------------------------------------------------------------
 * Name : OR_MultiShader::GetTokens
 *
 *  \return The list of tokens referencing the subshaders
 *  \author Antoine Bouthors 2001-11-27
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
const T_MultishaderTokenList& OR_MultiShader::GetTokens() const
{
	return m_SubShaders;
}




/*------------------------------------------------------------------------------
 * Name : OR_MultiShader::RemoveShader
 *
 *  \param  The Shader to remove from the Map.
 *  \author Antoine Bouthors 2001-11-21
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
void OR_MultiShader::RemoveShader( OR_Shader* Shader )
{
	OR_ASSERT( Shader != NULL );
	IT_MultishaderTokenList it = m_SubShaders.begin();
	while( it != m_SubShaders.end() && (*it).GetShader() != Shader ) ++it;
	if( it == m_SubShaders.end() ) return;

	m_SubShaders.erase( it );
}



} // End namespace OR

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

