/*-------------------------------------------------------------------*/
/*                           OR_WinAmp.h                             */
/*-------------------------------------------------------------------*/
/* created on 20:5:2001   2:01                                       */
/*-------------------------------------------------------------------*/

/** \file 
	Contains definition of a wrapper class to build WinAmp plugins.
	\author Gabriel.
**/

#ifndef _OR_WINAMP_H_
#define _OR_WINAMP_H_

#include "../configuration/OR_Config.h"

namespace OR
{
	
/*------------------------------------------------------------*/
/* WinAmp definitions                                         */
/*------------------------------------------------------------*/

/** a structure to register the plugin */
typedef struct winampVisModule {
	char *description; // description of module
	HWND hwndParent;   // parent window (filled in by calling app)
	HINSTANCE hDllInstance; // instance handle to this DLL (filled in by calling app)
	OR_I32 sRate;		 // sample rate (filled in by calling app)
	OR_I32 nCh;			 // number of channels (filled in...)
	OR_I32 latencyMs;     // latency from call of RenderFrame to actual drawing
	// (calling app looks at this value when getting data)
	OR_I32 delayMs;       // delay between calls in ms
	
	// the data is filled in according to the respective Nch entry
	OR_I32 spectrumNch;
	OR_I32 waveformNch;
	unsigned char spectrumData[2][576];
	unsigned char waveformData[2][576];
	
	void (*Config)(struct winampVisModule *this_mod);  // configuration dialog
	OR_I32 (*Init)(struct winampVisModule *this_mod);     // 0 on success, creates window, etc
	OR_I32 (*Render)(struct winampVisModule *this_mod);   // returns 0 if successful, 1 if vis should end
	void (*Quit)(struct winampVisModule *this_mod);    // call when done
	
	void *userData; // user data, optional
} winampVisModule;

/** the header of the plugin */
typedef struct {
	OR_I32 version;       // VID_HDRVER
	char *description; // description of library
	winampVisModule* (*getModule)(OR_I32);
} winampVisHeader;

/** exported symbols */
typedef winampVisHeader* (*winampVisGetHeaderType)();

/** version of current module (0x101 == 1.01) */
#define VIS_HDRVER 0x101

/** configuration dialog */
typedef void (*winamp_config_func)(struct winampVisModule *this_mod); 
/** initialization for module */
typedef OR_I32 (*winamp_init_func)(struct winampVisModule *this_mod);
/** rendering for module */
typedef OR_I32 (*winamp_render_func)(struct winampVisModule *this_mod);
/** deinitialization for module */
typedef void (*winamp_quit_func)(struct winampVisModule *this_mod);

/** exported symbols : the only one */
typedef winampVisHeader* (*winampVisGetHeaderType)();

/*------------------------------------------------------------*/
/*                    class OR_WinAmp                         */
/*------------------------------------------------------------*/
/* a wrapper class to build WinAmp plugins                    */
/*------------------------------------------------------------*/

/// a wrapper class to build WinAmp plugins.
/** 
	Define basic datas for a WinAmp plugins.
	What you should do is write the winampVisGetHeader which should be like this :

	#ifdef __cplusplus
	extern "C" {
	#endif
	__declspec( dllexport ) winampVisHeader *winampVisGetHeader()
	{
		return MyWinAmp->GetHeader();
	}
	#ifdef __cplusplus
	}
	#endif

	\author Gabriel
*/
class OR_WinAmp
{
private:
	/** plugin's header */
	winampVisHeader hdr;
	/** plugin's module description */
	static winampVisModule mod;
public:
	/** constructor */
	OR_WinAmp();
	
	/** get the header */
	winampVisHeader* GetHeader()
	{ return &hdr; }

	/** set the config function */
	void SetConfig(winamp_config_func f)
	{ mod.Config=f; }
	/** set the init function */
	void SetInit(winamp_init_func f)
	{ mod.Init=f; }
	/** set the render function */
	void SetRender(winamp_render_func f)
	{ mod.Render=f; }
	/** set the quit function */
	void SetQuit(winamp_quit_func f)
	{ mod.Quit=f; }
	
	/** get the WinAmp module given it's number */
	static winampVisModule *GetModule (OR_I32 which)
	{	
		// return the module only if which is 0
		if (which == 0) return &mod;
		// default
		return NULL;
	}	

	/* configuration managing **********************************************/
	/** reads the configuration */
	static void ReadConfig(struct winampVisModule *this_mod);
	/** writes the configuration */
	static void WriteConfig(struct winampVisModule *this_mod);
	/** makes the .ini file filename */
	static void WriteIniFile(struct winampVisModule *this_mod, char *ini_file);
};



} // namespace OR

#endif /* #ifndef _OR_WINAMP_H_ */

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////

