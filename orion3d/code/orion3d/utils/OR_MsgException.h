
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MsgException.h
 *  \brief Definition of class OR_MsgException
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_MsgException_h_
#define __OR_MsgException_h_

#include "../configuration/OR_Config.h"
#include "OR_Exception_ABC.h"
#include "OR_String.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MsgException
 *  \brief  an exception with a message.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_MsgException: public OR_Exception_ABC
{

public:

    OR_MsgException(OR_String Message, OR_String Function);
    virtual ~OR_MsgException();

	void Print();

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	void    SetMessage(OR_String Message);
	OR_String& GetMessage();
	void    SetFunction(OR_String Function);
	OR_String& GetFunction();
    //@}


private:

	/** the function where the excption was thrown */
	OR_String Function_;
	/** the message */
	OR_String Message_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
	#include "OR_MsgException.inl"
#endif


#endif // __OR_MsgException_h_

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

