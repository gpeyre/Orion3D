/*----------------------------------------------------------------------------*/
/*                             OR_StrVector.h                                 */
/*----------------------------------------------------------------------------*/
/* defines a vector of string*.                                               */
/*----------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_StrVector.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_StrVector.h"

namespace OR
{
	
/*----------------------------------------------------------------------------*/
/*                          class OR_StrVector                                */
/*----------------------------------------------------------------------------*/
/* a vector of OR_String*.                                                    */
/*----------------------------------------------------------------------------*/

OR_Bool OR_StrVector::FreeItem (OR_String* Item)
{
  OR_DELETE(Item);
  return true;
}

OR_StrVector::~OR_StrVector ()
{
  DeleteAll ();
}

OR_I32 OR_StrVector::Compare (OR_String* Item1, OR_String* Item2, OR_I32 Mode) const
{
    return strcmp(Item1->val(), Item2->val());
}

OR_I32 OR_StrVector::CompareKey (OR_String* Item, char* Key, OR_I32 Mode) const
{
    return strcmp(Item->val(), Key);
}


} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                           END OF FILE                                     //
///////////////////////////////////////////////////////////////////////////////