/*---------------------------------------------------------------------------*/
/*                             OR_SaverSettings.h                            */
/*---------------------------------------------------------------------------*/
/* a class to manage WIN32 screensavers settings                             */
/*---------------------------------------------------------------------------*/

#ifndef OR_SAVERSETTINGS_H
#define OR_SAVERSETTINGS_H

#include "../configuration/OR_Config.h"
#include "../utils/OR_Vector_Template.h"
#include "../utils/OR_List_Template.h"
#include "../utils/OR_String.h"
#include <regstr.h>

namespace OR
{
	
#define REGSTR_PATH_PLUSSCR (REGSTR_PATH_SETUP "\\Screen Savers")
#define REGSTR_PATH_CONFIG  ("Software\\Orion3D\\Screen Savers")

/*---------------------------------------------------------------------------*/
/*                     class OR_SaverParameter                               */
/*---------------------------------------------------------------------------*/

/// a parameter of the screen saver
/**
	a parameter is simply a value and a name.
	\author Gabriel
*/

class OR_SaverParam
{
public:
	/** name of the parameter */
	OR_String Name;
	/** value of the parameter */
	OR_I32 Value;
	/** constructor */
	OR_SaverParam(OR_String n, OR_I32 v)
	{ Name=n; Value=v; }
};


/*---------------------------------------------------------------------------*/
/*                      class OR_SaverSettings                               */
/*---------------------------------------------------------------------------*/
/* a class to manage screensavers settings                                   */
/*---------------------------------------------------------------------------*/

/// a class to manage screensavers settings.
/**
	It simply store the current settings of the screensaver, using WIN32 registry.
	IMPORTANT : initialize ParamName & ParamValue first !
	\author Gabriel
*/

class ORION3D_API OR_SaverSettings
{
public:
	HWND hwnd;
	OR_U32 PasswordDelay;   // in seconds
	OR_U32 MouseThreshold;  // in pixels
	BOOL  MuteSound;
	POINT InitCursorPos;
	OR_U32 InitTime;        // in ms
	UINT  idTimer;         // a timer id, because this particular saver uses a timer
	BOOL  IsDialogActive;
	BOOL  ReallyClose;     // for NT, so we know if a WM_CLOSE came from us or it.

	/** list of all parameters */
	OR_ListElt_Template<OR_SaverParam> *ParamRoot;

	/** current screen mode */
	OR_ScrMode ScrMode;

	/** constructor */
	OR_SaverSettings();

	/** read genral datas about the user from registry */
	void ReadGeneralRegistry();
	/** read saver configuration datas from the registry */
	void ReadConfigRegistry();
	/** write saver configuration in the registry */
	void WriteConfigRegistry();
	/** called to terminate the screen saver */
	void CloseSaverWindow();
	/** some stuff to configure the screen saver when launching the dialog box */
	void StartDialog();
	/** some stuff to configure the screen saver when killing the dialog box */
	void EndDialog();

	/** parse the command line to tell in which mode the screensaver is running */
	void ParseCommandLine();

	/** get the list of parameters names */
	void AddParam(OR_String n);
	/** set the value of a parameter */
	OR_RETURN_CODE SetParam(OR_String n, OR_I32 v);
	/** get the value of a parameter */
	OR_I32 GetParam(OR_String n);
};



} // namespace OR

#endif /* #ifndef OR_SAVERSETTINGS_H */



///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                           END  OF FILE	                                 //
///////////////////////////////////////////////////////////////////////////////
