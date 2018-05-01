/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SmartCounter.cpp
 *  \brief Definition of class \c OR_SmartCounter
 *  \author Gabriel Peyré 2001-09-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SmartCounter.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_SmartCounter.h"

#ifndef OR_USE_INLINE
	    #include "OR_SmartCounter.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SmartCounter::CheckAndDelete
 *
 *  \param  pCounter the counter that we don't use anymore (can be NULL).
 *  \return Do we have delete the pointer ?
 *  \author Gabriel Peyré 2001-10-29
 *
 *	First release the pointer. If it is no longer use, delete it.
 *	Else print a warning message, since only manager should destroy datas.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_SmartCounter::CheckAndDelete(OR_SmartCounter* pCounter)
{
	if( pCounter==NULL )
		return false;

	pCounter->ReleaseIt();
	if( pCounter->NoLongerUsed() )
	{
		/*OR_Globals::MessageHandler()->Warning("OR_SmartCounter::~CheckAndDelete", 
			"Counter no longer used, should not append (deletion is the role of managers).");
		*/
		OR_DELETE(pCounter);
		return true;
	}

	return false;
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

