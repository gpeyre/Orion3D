/*------------------------------------------------------------------------------
 *  \file  OR_MultiShader.cpp
 *  \brief Definition of class \c OR_MultiShader 
 *  \author Antoine Bouthors 2001-11-21
 *------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MultiShader.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_MultiShader.h"

#ifndef OR_USE_INLINE
#   include "OR_MultiShader.inl"
#endif

namespace OR {

/*------------------------------------------------------------------------------
/** Name : OR_MultiShader constructor
 *
 *  \author Antoine Bouthors 2001-11-21
 *
*/
/*------------------------------------------------------------------------------*/
OR_MultiShader::OR_MultiShader()
:	OR_Shader()
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------
/** Name : OR_MultiShader copy constructor
 *
 *  \param  Dup The Mutlishader to copy from
 *  \author Antoine Bouthors 2001-11-28
 *
*/
/*------------------------------------------------------------------------------*/
OR_MultiShader::OR_MultiShader( const OR_MultiShader& Dup )
:	OR_Shader( Dup ),
	m_SubShaders( Dup.m_SubShaders )
{
}


/*------------------------------------------------------------------------------
/** Name : OR_MultiShader copy operator
 *
 *  \param  Dup The Mutlishader to copy from
 *  \return this
 *  \author Antoine Bouthors 2001-11-28
 *
*/
/*------------------------------------------------------------------------------*/
OR_MultiShader& OR_MultiShader::operator=( const OR_MultiShader& Dup )
{
	m_SubShaders = Dup.m_SubShaders;

	return (*this);
}

/*------------------------------------------------------------------------------
/** Name : OR_MultiShader destructor
 *
 *  \author Antoine Bouthors 2001-11-21
 *
*/
/*------------------------------------------------------------------------------*/
OR_MultiShader::~OR_MultiShader()
{
	m_SubShaders.clear();
}



/*------------------------------------------------------------------------------
/** Name : OR_MultiShader::ProcessShader
 *
 *  \param  object to object to be processed
 *  \author Antoine Bouthors 2001-11-21
 *
 * For each sub-shader, sets the face list to process and call ProcessShader
*/
/*------------------------------------------------------------------------------*/
void OR_MultiShader::ProcessShader( OR_Shadable& object )
{
	IT_MultishaderTokenList it;

	for( it = m_SubShaders.begin() ; it!=m_SubShaders.end() ; ++it )
	{
		T_U32Vector& Indices = (*it).GetIndices();
		if( Indices.size() > 0 )
		{
			object.SetFaceToProcess( &Indices.front() , Indices.size()/3 );
			(*it).GetShader()->ProcessShader( object );
		}
	}
}


/*------------------------------------------------------------------------------
/** Name : OR_MultiShader::NeedsSorting
 *
 *  \return true if at least one of the su-shader needs sorting
 *  \author Antoine Bouthors 2001-11-28
 *
*/
/*------------------------------------------------------------------------------*/
OR_Bool OR_MultiShader::NeedsSorting()
{
	OR_Bool Result = false;
	for( IT_MultishaderTokenList it=m_SubShaders.begin() ; it!=m_SubShaders.end() ; ++it )
		Result |= (*it).GetShader()->NeedsSorting();

	return Result;
}



/*------------------------------------------------------------------------------
/** Name : OR_MultiShader::BuildToFile
 *
 *  \author Antoine Bouthors 2001-11-21
 *
 * Serialize the multi-shader by writing each of its token
*/
/*------------------------------------------------------------------------------*/
void OR_MultiShader::BuildToFile( OR_File& File )
{
	OR_Shader::BuildToFile( File );

	//Save the number of sub-shaders
	File << (OR_U32)m_SubShaders.size();

	for( IT_MultishaderTokenList it = m_SubShaders.begin() ; it != m_SubShaders.end() ; ++it )
	{
		File << (*it);
	}
}

/*------------------------------------------------------------------------------
/** Name : OR_MultiShader::BuildFromFile
 *
 *  \author Antoine Bouthors 2001-11-21
 *
*/
/*------------------------------------------------------------------------------*/
void OR_MultiShader::BuildFromFile( OR_File& File )
{
	OR_Shader::BuildFromFile( File );
	m_SubShaders.clear();

	//Load the number of sub-shaders
	OR_U32 NbrShaders, i;
	File >> NbrShaders;

	for( i=0 ; i<NbrShaders ; ++i )
	{
		OR_MultishaderToken Token;
		File >> Token;
		m_SubShaders.push_back( Token );
	}
}

/*------------------------------------------------------------------------------
/** Name : OR_MultiShader::PostExportPass
 *
 *  \author Antoine Bouthors 2001-11-21
 *  retrieve the OR_Shader* for each token
 *
*/
/*------------------------------------------------------------------------------*/
void OR_MultiShader::PostExportPass()
{
	OR_Shader::PostExportPass();
	for( IT_MultishaderTokenList it=m_SubShaders.begin() ; it!=m_SubShaders.end() ; ++it )
	{
		(*it).PostExportPass();
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

