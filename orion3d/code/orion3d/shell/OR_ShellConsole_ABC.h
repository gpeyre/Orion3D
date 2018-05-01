/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellConsole_ABC.h
 *  \brief Definition of class \c OR_ShellConsole_ABC
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ShellConsole_ABC_h_
#define __OR_ShellConsole_ABC_h_

#include "../configuration/OR_Config.h"
#include "OR_ShellKernel.h"
#include "OR_ShellConsoleHistory.h"

namespace OR {

class OR_ShellKernel;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ShellConsole_ABC
 *  \brief  base class for all console.
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	A console is linked to a single kernel that perform the shell computations, 
 *	but of course, a kernel can be linked to multiple consoles.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_ShellConsole_ABC
{

public:
	
	#define kShellColor_Foreground_BLUE      0x0001 // text color contains blue.
	#define kShellColor_Foreground_GREEN     0x0002 // text color contains green.
	#define kShellColor_Foreground_RED       0x0004 // text color contains red.
	#define kShellColor_Foreground_INTENSITY 0x0008
	#define kShellColor_Background_BLUE      0x0010 // Background color contains blue.
	#define kShellColor_Background_GREEN     0x0020 // Background color contains green.
	#define kShellColor_Background_RED       0x0040 // Background color contains red.
	#define kShellColor_Background_INTENSITY 0x0080

    OR_ShellConsole_ABC(OR_ShellKernel* ShellKernel = NULL, OR_Bool bPrintFullPrompt = false);
    virtual ~OR_ShellConsole_ABC();

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	void SetShellKernel(OR_ShellKernel& ShellKernel);
	OR_ShellKernel& GetShellKernel();
    //@}

    //-------------------------------------------------------------------------
    /** \name function to overload [direct display, no interpretation] */
    //-------------------------------------------------------------------------
    //@{
	/** used by the kernel to display it's result. */
	virtual void Display(OR_String& text) = 0;
	/** clear the console */
	virtual void Clear() = 0;
	/** erase one of the char printed */
	virtual void EraseOneChar() = 0;

	virtual void WriteString(OR_String& str) = 0;
	virtual void NewLine() = 0;

	/** update the console */
	virtual void Update() = 0;

	virtual OR_U32 SetColor( OR_U32 color ) = 0;
	virtual OR_U32 GetColor() = 0;
    //@}
	
	//-------------------------------------------------------------------------
    /** \name key management [interpretation, then direct display] */
    //-------------------------------------------------------------------------
    //@{
	void KeyPressed(char c);
	void SpecialKeyPressed(OR_U32 virtualKey);

	void DoString(OR_String& str);
    //@}

	
    //-------------------------------------------------------------------------
    /** \name color management, prompt management */
    //-------------------------------------------------------------------------
    //@{
	void SetPrintFullPrompt(OR_Bool bPrintFullPrompt);
	void PrintPrompt();
    //@}

	/** when a user print a new string (this might cause a flush if the used make
		a new line) */
	void Flush();



protected:

	//-------------------------------------------------------------------------
    /** \name internal helpers */
    //-------------------------------------------------------------------------
    //@{
	void EraseCurrentString();
    //@}


	/** the kernel that manage shell computations */
	OR_ShellKernel* pShellKernel_;

	
	/** string to execute */
	OR_String TextBuffer_;
	
	/** a stack of previous entry */
	OR_ShellConsoleHistory HistoryStack_;
	
	/** do we print the full pwd in the path ? */
	OR_Bool bPrintFullPrompt_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ShellConsole_ABC.inl"
#endif


#endif // __OR_ShellConsole_ABC_h_

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

