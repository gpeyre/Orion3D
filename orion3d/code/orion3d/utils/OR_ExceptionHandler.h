
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ExceptionHandler.h
 *  \brief Definition of class OR_ExceptionHandler
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ExceptionHandler_h_
#define __OR_ExceptionHandler_h_

#include "../configuration/OR_Config.h"
#include "OR_Exception_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ExceptionHandler
 *  \brief  A class that catch excption and respond to them.
 *  \author Gabriel Peyré 2001-08-04	
 *
 *	A code that throw an exception should be handled like that :
 *	\code
 *	OR_CATCH_EXCEPTION(my_function());
 *	\endcode
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_ExceptionHandler
{

public:

    OR_ExceptionHandler();
    virtual ~OR_ExceptionHandler();

	void CatchException(OR_Exception_ABC *e);

private:

};

#define OR_CATCH_EXCEPTION(code)  try { code } catch (OR_Exception_ABC* e) { OR_Globals::ExceptionHandler()->CatchException(e); }

} // End namespace OR

#ifdef OR_USE_INLINE
	#include "OR_ExceptionHandler.inl"
#endif


#endif // __OR_ExceptionHandler_h_

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

