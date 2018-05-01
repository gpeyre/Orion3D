/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_IDStack.cpp
 *  \brief Definition of class \c OR_IDStack
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_IDStack.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_IDStack.h"

#ifndef OR_USE_INLINE
	    #include "OR_IDStack.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IDStack::Init
 *
 *  \param  nStart first ID that will be available
 *  \param  nEnd last ID that will be available.
 *  \author Gabriel Peyré 2001-10-31
 *
 *	Initialize the stack with ID in the given range.
 */ 
/*------------------------------------------------------------------------------*/
void OR_IDStack::Init(OR_U32 nStart, OR_U32 nEnd)
{
	OR_I32 nDir = 1;
	if( nEnd<nStart )
		nDir = -1;
	for( OR_U32 i=nStart; i<=nEnd; i+=nDir )
		IDStack_.push_back( i );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IDStack::IsAvailable
 *
 *  \param  nID the ID to test
 *  \return true if the ID can be used.
 *  \author Gabriel Peyré 2001-09-25
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_IDStack::IsAvailable( OR_U32 nID )
{
	for( IT_U32List it = IDStack_.begin(); it!=IDStack_.end(); ++it )
		if( (*it)==nID )
			return true;

	return false;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IDStack::GetNewID
 *
 *  \return a new ID.
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
OR_U32 OR_IDStack::GetNewID()
{
	OR_ASSERT( !IDStack_.empty() );
	
	OR_U32 nID = IDStack_.front();
	IDStack_.pop_front();
	
	return nID;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IDStack::ReleaseID
 *
 *  \param  nID the ID to release.
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
void OR_IDStack::ReleaseID(OR_U32 nID)
{
	IDStack_.push_front(nID);
	IDStack_.sort();
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

