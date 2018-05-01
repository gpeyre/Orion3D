/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MsgException.inl
 *  \brief Inlined methods of class OR_MsgException
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_MsgException.h"

namespace OR {

/*------------------------------------------------------------------------------*/
// Name : OR_MsgException constructor
/** 
 *  \param  Message The message to explain the explain the exception.
 *  \param  Function The function where the excption was thrown.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_MsgException::OR_MsgException(OR_String Message, OR_String Function)
{
	Message_  = Message;
	Function_ = Function;
}

/*------------------------------------------------------------------------------*/
// Name : OR_MsgException destructor
/** 
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_MsgException::~OR_MsgException()
{
}

/*------------------------------------------------------------------------------*/
// Name : OR_MsgException::Print
/** 
 *  \param  buffer an output stream.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MsgException::Print()
{
	OR_String msg = OR_String("Exception in method ") + Function_ + OR_String(" : ") + Message_;
	MessageBox(0,msg.val(),"Orion3D internal exception",MB_OK | MB_ICONERROR);
}

/*------------------------------------------------------------------------------*/
// Name : OR_MsgException::SetMessage
/** 
 *  \param  Message The message to explain the explain the exception.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MsgException::SetMessage(OR_String Message)
{
	Message_ = Message;
}

/*------------------------------------------------------------------------------*/
// Name : OR_MsgException::GetMessage
/** 
 *  \return The message to explain the explain the exception.
 *  \author Gabriel Peyré 2001-08-01
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_String& OR_MsgException::GetMessage()
{
	return Message_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_MsgException::SetFunction
/** 
 *  \param  Function The function where the excption was thrown.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MsgException::SetFunction(OR_String Function)
{
	Function_ = Function;
}



/*------------------------------------------------------------------------------*/
// Name : OR_MsgException::GetFunction
/** 
 *  \return The function where the excption was thrown.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_String& OR_MsgException::GetFunction()
{
	return Function_;
}


} // End namespace OR

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

