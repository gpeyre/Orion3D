/*-------------------------------------------------------------------*/
/*                           OR_WinAmp.cpp                           */
/*-------------------------------------------------------------------*/
/* created on 20:5:2001   2:21                                       */
/*-------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_WinAmp.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_WinAmp.h"

namespace OR
{
	
/* initialisation of static datas */
winampVisModule OR_WinAmp::mod;

/*------------------------------------------------------------*/
/*                    class OR_WinAmp                         */
/*------------------------------------------------------------*/
/* a wrapper class to build WinAmp plugins                    */
/*------------------------------------------------------------*/

OR_WinAmp::OR_WinAmp()
{
	mod.description = strdup("OrionAmp");
	mod.hwndParent=NULL;
	mod.hDllInstance=NULL;
	mod.sRate=0;
	mod.nCh=0;
	mod.latencyMs=25;
	mod.delayMs=25;
	mod.spectrumNch=1;
	mod.waveformNch=1;
	mod.Config=NULL;
	mod.Init=NULL;
	mod.Render=NULL;
	mod.Quit=NULL;

	hdr.getModule=GetModule;
	hdr.description = strdup("OrionAmp");
	hdr.version=VIS_HDRVER;
}

/* configuration managing **********************************************/
void OR_WinAmp::ReadConfig(struct winampVisModule *this_mod)
{

}

void OR_WinAmp::WriteConfig(struct winampVisModule *this_mod)
{

}

void OR_WinAmp::WriteIniFile(struct winampVisModule *this_mod, char *ini_file)
{

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
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////
