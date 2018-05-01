/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ExceptionHandler.cpp
 *  \brief Implementation of class OR_ExceptionHandler
 *  \author Gabriel Peyr� 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ExceptionHandler.cpp (c) Gabriel Peyr� & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ExceptionHandler.h"
#include <iostream>

#ifndef OR_USE_INLINE
	#include "OR_ExceptionHandler.inl"
#endif

using namespace OR;



/*------------------------------------------------------------------------------*/
// Name : OR_ExceptionHandler::CatchException
/** 
 *  \param  e Pointer on the exception that has been caught.
 *  \author Gabriel Peyr� 2001-08-04
 *
 *	Responds to an excption (output an error message, and quit).
 */ 
/*------------------------------------------------------------------------------*/
void OR_ExceptionHandler::CatchException(OR_Exception_ABC *e)
{
	e->Print();
	exit(1);
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

