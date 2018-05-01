/*----------------------------------------------------------------------------*/
/*                             OR_StrVector.h                                 */
/*----------------------------------------------------------------------------*/
/* defines a vector of string*.                                               */
/*----------------------------------------------------------------------------*/

/** \file 
	defines a vector of string*.
	\author Gabriel.
**/


#ifndef _OR_STRVECTOR_H_
#define _OR_STRVECTOR_H_

#include "../configuration/OR_Config.h"
#include "OR_String.h"
#include "OR_Vector_Template.h"

namespace OR
{
	
/*----------------------------------------------------------------------------*/
/*                          class OR_StrVector                                */
/*----------------------------------------------------------------------------*/
/* a vector of OR_String*.                                                    */
/*----------------------------------------------------------------------------*/

/// a vector of OR_String*.
/**
	Defines Compare functions so that we can perform a sort.
	\author
*/
class ORION3D_API OR_StrVector : public OR_Vector_Template<OR_String*>
{
public:
  /** Constructor */
  OR_StrVector (OR_I32 ilimit = 64, OR_I32 ithreshold = 64) :
    OR_Vector_Template<OR_String*>(ilimit, ithreshold) {}

  /** Delete all inserted strings before deleting the object itself */
  virtual ~OR_StrVector ();

  /** FreeItem deletes Item as if it was allocated by 'new char *[]' */
  virtual OR_Bool FreeItem (OR_String* Item);

  /** Compare two array elements in given Mode */
  virtual OR_I32 Compare (OR_String* Item1, OR_String* Item2, OR_I32 Mode) const;

  /** Compare two strings for equality (case-sensitive) */
  virtual OR_I32 CompareKey (OR_String* Item, char* Key, OR_I32 Mode) const;
};



} // namespace OR

#endif /* #ifndef _OR_STRVECTOR_H_ */

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