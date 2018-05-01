/*---------------------------------------------------------------------------*/
/*                             OR_SaverSettings.h                            */
/*---------------------------------------------------------------------------*/
/* a class to manage WIN32 screensavers settings                             */
/*---------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SaverSettings.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_SaverSettings.h"

namespace OR
{
	
OR_SaverSettings::OR_SaverSettings()
{
	hwnd=NULL;
	idTimer=0;
	ScrMode=OR_Scr_Undefined;
	/* for the moment, no parameters have been defined */
	ParamRoot=NULL;
}

void OR_SaverSettings::ReadGeneralRegistry()
{
	PasswordDelay = 15;
	MouseThreshold = 50;
	IsDialogActive = false; // default values in case they're not in registry
	LONG res;
	HKEY skey;
	DWORD valtype, valsize, val;
	res = RegOpenKeyEx(HKEY_CURRENT_USER,REGSTR_PATH_PLUSSCR,0,KEY_ALL_ACCESS,&skey);
	if( res!=ERROR_SUCCESS )
		return;
	
	valsize = sizeof(val);
	res = RegQueryValueEx(skey,"Password Delay",0,&valtype,(LPBYTE)&val,&valsize);
	if( res==ERROR_SUCCESS )
		PasswordDelay=val;
	
	valsize = sizeof(val);
	res = RegQueryValueEx(skey,"Mouse Threshold",0,&valtype,(LPBYTE)&val,&valsize);
	if( res==ERROR_SUCCESS )
		MouseThreshold=val;
	
	valsize = sizeof(val);
	res = RegQueryValueEx(skey,"Mute Sound",0,&valtype,(LPBYTE)&val,&valsize);
	if( res==ERROR_SUCCESS )
		MuteSound=val;
	
	RegCloseKey(skey);
}

void OR_SaverSettings::ReadConfigRegistry()
{
	LONG res;
	HKEY skey;
	DWORD valtype, valsize, val;

	/* open the registry key root */
	res = RegOpenKeyEx(HKEY_CURRENT_USER,REGSTR_PATH_CONFIG,0,KEY_ALL_ACCESS,&skey);
	if( res!=ERROR_SUCCESS )
		return;

	/* read each parameter */
	OR_ListElt_Template<OR_SaverParam> *e=ParamRoot;
	while (e!=NULL)
	{
		valsize = sizeof(val);
		res = RegQueryValueEx(skey, e->Element->Name.val(),0,&valtype,(LPBYTE)&val,&valsize);
	
		if( res==ERROR_SUCCESS )
			e->Element->Value=val;
		else 
			e->Element->Value=OR_ERROR;

		e=e->Son;
	}

	/* close the registry key root */
	RegCloseKey(skey);
}  

void OR_SaverSettings::WriteConfigRegistry()
{
	LONG res;
	HKEY skey;
	DWORD val, disp;

	/* open the registry key root */
	res = RegCreateKeyEx(HKEY_CURRENT_USER,REGSTR_PATH_CONFIG,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&skey,&disp);
	if( res!=ERROR_SUCCESS )
		return;

	/* write each parameter */
	OR_ListElt_Template<OR_SaverParam> *e=ParamRoot;
	while (e!=NULL)
	{
		val = e->Element->Value;
		RegSetValueEx(skey, e->Element->Name.val(), 0, REG_DWORD, (CONST BYTE*)&val, sizeof(val));	

		e=e->Son;
	}

	/* close the registry key root */
	RegCloseKey(skey);
}

void OR_SaverSettings::CloseSaverWindow()
{
	ReallyClose = true;
	PostMessage(hwnd,WM_CLOSE,0,0);
}

void OR_SaverSettings::StartDialog()
{
	IsDialogActive = true;
	SendMessage(hwnd,WM_SETCURSOR,0,0);
}

void OR_SaverSettings::EndDialog()
{
	IsDialogActive = false;
	SendMessage(hwnd,WM_SETCURSOR,0,0);
	GetCursorPos(&InitCursorPos);
}

void OR_SaverSettings::ParseCommandLine()
{
	/* parse the command line options */
	char *c = GetCommandLine();
	if(*c == '\"' )
	{
		c++;
		while( *c!=0 && *c!='\"' )
			c++;
	}
	else
	{
		while( *c!=0 && *c!=' ' )
			c++;
	}
	
	if( *c!=0 )
		c++;
	
	while( *c==' ' )
		c++;

	HWND hwnd=NULL;
	if( *c==0 )
	{
		ScrMode = OR_Scr_Config;
		hwnd=NULL;
	}
	else
	{
		if( *c=='-' || *c=='/' )
			c++;
		if( *c=='p' || *c=='P' || *c=='l' || *c=='L' )
		{
			c++;
			while( *c==' ' || *c==':' )
				c++;
			hwnd = (HWND)atoi(c);
			
			ScrMode = OR_Scr_Preview;
		}
		else if( *c=='s' || *c=='S' )
		{
			ScrMode=OR_Scr_Saver;
		}
		else if( *c=='c' || *c=='C' )
		{
			c++;
			while( *c==' ' || *c==':' )
				c++;
			if( *c==0 )
				hwnd = GetForegroundWindow();
			else
				hwnd = (HWND)atoi(c);
			ScrMode = OR_Scr_Config;
		}
		else if( *c=='a' || *c=='A' )
		{
			c++;
			while( *c==' ' || *c==':' )
				c++;
			hwnd = (HWND)atoi(c);
			ScrMode = OR_Scr_Password;
		}
	}	
}

void OR_SaverSettings::AddParam(OR_String n)
{
	ParamRoot=new OR_ListElt_Template<OR_SaverParam>(new OR_SaverParam(n, 0), ParamRoot);
}

OR_RETURN_CODE OR_SaverSettings::SetParam(OR_String n, OR_I32 v)
{
	OR_ListElt_Template<OR_SaverParam> *e=ParamRoot;
	while (e!=NULL)
	{
		if (e->Element->Name==n) 
		{
			e->Element->Value=v;
			return OR_OK;
		}

		e=e->Son;
	}
	return OR_ERROR;
}

OR_I32 OR_SaverSettings::GetParam(OR_String n)
{
	OR_ListElt_Template<OR_SaverParam> *e=ParamRoot;
	while (e!=NULL)
	{
		if (e->Element->Name==n) return e->Element->Value;
		
		e=e->Son;
	}
	return OR_ERROR;
}



} // namespace OR

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