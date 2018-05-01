/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Font_ABC.cpp
 *  \brief Definition of class \c OR_Font_ABC
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Font_ABC.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Font_ABC.h"
/* print a log for this project */
#include "../misc/OR_PrintBuildLog.h"

#ifndef OR_USE_INLINE
	#include "OR_Font_ABC.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::Draw
 *
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Gabriel Peyré 2001-11-13
 *
 *	Render the string that have been specified using \c SetText
 */ 
/*------------------------------------------------------------------------------*/
void OR_Font_ABC::Draw()
{
	if( pText_!=NULL )
		this->Draw(pText_);
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

