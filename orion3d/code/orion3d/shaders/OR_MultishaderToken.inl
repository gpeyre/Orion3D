/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MultishaderToken.inl
 *  \brief Inlined methods for \c OR_MultishaderToken
 *  \author Antoine Bouthors 2002-04-04
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_MultishaderToken.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken::GetShader
 *
 *  \return The sub-shader
 *  \author Antoine Bouthors 2002-04-04
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Shader* OR_MultishaderToken::GetShader()
{
	return m_Shader;
}


/*------------------------------------------------------------------------------*/
/** 
* Name : OR_MultishaderToken::GetShader
*
*  \return The const sub-shader
*  \author Antoine Bouthors 2002-04-04
*
*/ 
/*------------------------------------------------------------------------------*/
OR_INLINE
const OR_Shader* OR_MultishaderToken::GetShader() const
{
	return m_Shader;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken::GetId
 *
 *  \return The id of the sub-shader
 *  \author Antoine Bouthors 2002-04-04
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MultishaderToken::GetId()
{
	return m_Id;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken::GetIndices
 *
 *  \return The vertex indices affected by the sub-shader
 *  \author Antoine Bouthors 2002-04-04
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
T_U32Vector& OR_MultishaderToken::GetIndices()
{
	return m_Indices;
}



/*------------------------------------------------------------------------------*/
/** 
* Name : OR_MultishaderToken::GetIndices
*
*  \return The (const) vertex indices affected by the sub-shader
*  \author Antoine Bouthors 2002-04-04
*
*/ 
/*------------------------------------------------------------------------------*/
OR_INLINE
const T_U32Vector& OR_MultishaderToken::GetIndices() const
{
	return m_Indices;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken::SetShader	
 *
 *  \param  The new sub-shader of the token
 *  \author Antoine Bouthors 2002-04-04
 *
 * Set the sub-shader to be used by this token
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MultishaderToken::SetShader( OR_Shader* Shader )
{
	if( m_Shader ) OR_SmartCounter::CheckAndDelete( m_Shader );
	m_Shader = Shader;
	if( m_Shader ) m_Shader->UseIt();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken::void	
 *
 *  \param  Id the new id of the token
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2002-04-04
 *
 * PUT YOUR COMMENTS HERE
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MultishaderToken::SetId( OR_U32 Id )
{
	m_Id = Id;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MultishaderToken::void	
 *
 *  \param  Indices EXPLANATION
 *  \param  NbrIndices EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2002-04-04
 *
 * PUT YOUR COMMENTS HERE
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MultishaderToken::SetIndices( const OR_U32* Indices, OR_U32 NbrIndices )
{
	m_Indices.clear();
	if( Indices && NbrIndices )
	{
		m_Indices.resize( NbrIndices, 0 );
		memcpy( &(m_Indices.front()), Indices, NbrIndices*sizeof(OR_U32) );
	}
	
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

