
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellConsoleText.h
 *  \brief Definition of class \c OR_ShellConsoleText
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ShellConsoleText_h_
#define __OR_ShellConsoleText_h_

#include "../configuration/OR_Config.h"
#include "OR_ShellConsole_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ShellConsoleText
 *  \brief  a basic console.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_ShellConsoleText:	public OR_ShellConsole_ABC
{

public:

    OR_ShellConsoleText(OR_ShellKernel* ShellKernel = NULL, OR_Bool bOpen = false, OR_Bool bPrintFullPrompt = false);
    virtual ~OR_ShellConsoleText();
	
    //-------------------------------------------------------------------------
    /** \name functions overloaded */
    //-------------------------------------------------------------------------
    //@{
	/** used by the kernel to display it's result. */
	virtual void Display(OR_String& text);
	virtual void Clear();
	/** update the console */
	virtual void Update();

	virtual void EraseOneChar();

	virtual void WriteString(OR_String& str);
	virtual void NewLine();
	
	virtual OR_U32 SetColor( OR_U32 color );
	virtual OR_U32 GetColor();
    //@}


	//-------------------------------------------------------------------------
    /** \name Win32 callbacks */
    //-------------------------------------------------------------------------
    //@{
	void KeyEventProc(KEY_EVENT_RECORD record);
	static BOOL CtrlHandler(DWORD fdwCtrlType);
    //@}

	

    //-------------------------------------------------------------------------
    /** \name creation/destruction */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool OpenConsole();
	OR_Bool IsOpen();
	void    CloseConsole();
    //@}


private:
	
    //-------------------------------------------------------------------------
    /** \name iternals helpers */
    //-------------------------------------------------------------------------
    //@{
	void ScrollScreenBuffer(HANDLE, INT);
    //@}

	/** in stream */
	HANDLE hStdout_;
	/** out stream */
	HANDLE hStdin_; 

	OR_Bool bIsOpen_;

	/** to read data from in stream */
	char aReadBuffer_[256];
	/** events buffers */
	INPUT_RECORD irInBuf_[128]; 


};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ShellConsoleText.inl"
#endif


#endif // __OR_ShellConsoleText_h_

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

