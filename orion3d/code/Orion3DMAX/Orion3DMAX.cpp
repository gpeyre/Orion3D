/** \file 
	Contains the code of the main Dll classes
	\author Antoche
**/

#include "stdafx.h"
#include "Orion3DMAX.h"

/****************************************************************
Code du DLL :
 - DllMain (init custom controls & common controls)
 - LibNumberClasses, LibClassesDexc, LibDescription,  LibVersion
*****************************************************************/


/////////////////////////////////////////////////////////////////
// DllMain : point d'entrée de la dll.
/////////////////////////////////////////////////////////////////
/** Who could imagine that it is the entry point of the dll ?? Look at the MSDN for more information
	@return something syaing if all went done
	@param hinstDLL the instance of the dll
	@param fdwReason flag indicating why the DLL entry-point function is being called
	@param lpvReserved Specifies further aspects of DLL initialization and cleanup
**/
BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved) 
	{	
	// Hang on to this DLL's instance handle.
	hInstance = hinstDLL;
	if (! controlsInit) {
		controlsInit = TRUE;
		
		// Initialize MAX's custom controls
		InitCustomControls(hInstance);
		
		InitCommonControls();
	}
	return(TRUE);
}

/////////////////////////////////////////////////////////////////
// LibNumberClasses() : renvoie le nombre de plug-ins dans la DLL
/////////////////////////////////////////////////////////////////
int LibNumberClasses() 
{
	return 1; 
}


/////////////////////////////////////////////////////////////////
// LibClassesDesc(i) : renvoie les descripteurs de classe pour
// le i-ème plug-in
/////////////////////////////////////////////////////////////////
ClassDesc *LibClassDesc(int i) 
{
	switch (i)
	{
	case 0:		return &ViewerCD;
//	case 1:		return &ACTCD;
	default:	return NULL;
	}
}

/////////////////////////////////////////////////////////////////
// LibDescription : renvoie une description du plug-in
/////////////////////////////////////////////////////////////////
const TCHAR *LibDescription() 
{
	return _T("Orion3DMAX plug-in");
}


/////////////////////////////////////////////////////////////////
// LibVersion : renvoie la version de 3DSMAX sur laquelle le
// plug-in doit tourner
/////////////////////////////////////////////////////////////////
ULONG LibVersion()
{
	return VERSION_3DSMAX;
}
