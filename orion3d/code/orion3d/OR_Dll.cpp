/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Dll.cpp
 *  \brief Definction of the entry point for the dll
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Dll.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "stdafx.h"
#include "configuration/OR_Config.h"
/* print a log of the configuration */
#include "misc/OR_PrintBuildLog.h"

/** Defines the entry point for the DLL application. */
#ifdef ORION3D_EXPORTS
#ifdef _MAC_OS_
OR_I32 main(void) {
	return 0;
}
#elif defined(_UNIX_)
/* do nothing */
#else
/* WINDOWS SPECIFIC --> */
BOOL APIENTRY DllMain(HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
/* <-- END WINDOWS SPECIFIC */
#endif /* #ifdef _UNIX_ */
#endif /* ORION3D_EXPORTS */



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

