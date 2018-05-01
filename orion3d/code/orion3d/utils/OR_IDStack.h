
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_IDStack.h
 *  \brief Definition of class \c OR_IDStack
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_IDStack_h_
#define __OR_IDStack_h_

#include "../configuration/OR_Config.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_IDStack
 *  \brief  A stack of ID.
 *  \author Gabriel Peyré 2001-10-3
 */ 
/*------------------------------------------------------------------------------*/

class OR_IDStack
{

public:

    OR_IDStack();
    virtual ~OR_IDStack();

	void Init(OR_U32 nStart, OR_U32 nEnd);
	
	
	OR_U32 GetNewID();
	void   ReleaseID(OR_U32 nID);
	
	OR_Bool IsEmpty();
	OR_Bool IsAvailable( OR_U32 nID );
	
private:
	
	T_U32List IDStack_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_IDStack.inl"
#endif


#endif // __OR_IDStack_h_

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

