//*****************************************************************************
// Created: Gabriel Peyré 2001-06-29
//*****************************************************************************

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Shadable.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Shadable.h"
#include "OR_Shader.h"

#ifndef OR_USE_INLINE
#   include "OR_Shadable.inl"
#endif

namespace OR {

	
//-----------------------------------------------------------------------------
// Name: OR_Shadable constructor
/**
	\author Gabriel Peyré 2001-06-29
*/
//-----------------------------------------------------------------------------
OR_Shadable::OR_Shadable()
:	pFaceArray_		( NULL ),
	nNbrFace_		( NULL ),
	pShader_		( NULL ),
	ShadableMode_	( OR_Shadable::kProcessAll )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------
 * Name : OR_Shadable destructor
 *
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/
OR_Shadable::~OR_Shadable()
{
	/* we don't use the shader any more */
	OR_SmartCounter::CheckAndDelete( pShader_ );
}



/*------------------------------------------------------------------------------
 * Name : OR_Shadable constructor
 *
 *  \author Antoine Bouthors 2001-10-31
 *------------------------------------------------------------------------------*/
OR_Shadable::OR_Shadable( const OR_Shadable& Dup ):
	pFaceArray_		( Dup.pFaceArray_ ),
	nNbrFace_		( Dup.nNbrFace_ ),
	pShader_		( Dup.pShader_ ),
	ShadableMode_	( Dup.ShadableMode_ )
{
	if( pShader_) pShader_->UseIt();	
}


/*------------------------------------------------------------------------------
 * Name : OR_Shadable::operator
 *
 *  \author Antoine Bouthors 2001-10-31
 *------------------------------------------------------------------------------*/
OR_Shadable& OR_Shadable::operator=( const OR_Shadable& Dup )
{
	pFaceArray_		= Dup.pFaceArray_;
	nNbrFace_		= Dup.nNbrFace_;
	pShader_		= Dup.pShader_;
	ShadableMode_	= Dup.ShadableMode_;
	pShader_->UseIt();

	return (*this);
}


/*------------------------------------------------------------------------------*/
/**
 * Name : OR_Shadable::SetShader
 *
 *  \param  pShader the shader that the object will used to be rendered 
 *  \author Gabriel Peyré 2001-07-09
 */
/*------------------------------------------------------------------------------*/
void OR_Shadable::SetShader(OR_Shader* pShader)
{
	/* we don't use the old shader, check is we need to delete it */
	/** Bug fixed 2001-11-1 by Antoche (the plugin crash here) */
	if( pShader_ ) 
		OR_SmartCounter::CheckAndDelete( pShader_ );

	pShader_=pShader;

	/* declare that we use the shader */
	if( pShader_!=NULL )
		pShader_->UseIt();
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shadable::AccessArrays
 *
 *  \param  aVertArray Array of vertex to process. Size 3*nNbrVert.
 *  \param  aNormArray Array of normal to process. Size 3*nNbrVert.
 *  \param  aFaceArray Array of face to process. Size 3*nNbrFace. Index on the 2 previous arrays.
 *  \param  nNbrVert Number of vertex to process.
 *  \param  nNbrFace Number of faces to process.
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Access the array of the object. If ths shadable doesn't allow this functionnality, it
 *	returns NULL. 
 *
 *	\important This is a \e default implementation, assuming that the shadable doesn't 
 *	provide this functionality. For example, \c OR_Mesh should overloads this method.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Shadable::AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCoordArray, OR_U32* &aFaceArray,
							   	OR_U32& nNbrVert, OR_U32& nNbrFace )
{
	aVertArray     = NULL;
	aNormArray     = NULL;
	aFaceArray     = NULL;
	aTexCoordArray = NULL;
	nNbrVert   = -1;
	nNbrFace   = -1;
}

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

