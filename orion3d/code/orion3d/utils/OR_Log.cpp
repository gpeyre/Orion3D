/*-------------------------------------------------------------------*/
/*                              OR_Log.cpp                           */
/*-------------------------------------------------------------------*/
/* Created : 16 Apr 2001   13h03                                     */
/*-------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Log.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Log.h"
#include "../opengl/OR_GLExtensionsManager.h"

namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                               class OR_Log                        */
/*-------------------------------------------------------------------*/
/* Usefull class to manage a log file.                               */
/*-------------------------------------------------------------------*/


OR_Log::OR_Log(char *LogName)
{
	std::fstream *handler;
	char line[1024];

	this->Indent = 0;

	handler = new std::fstream;

	handler->open(LogName,ios::binary | ios::out | ios::trunc);

	if(handler->fail()) 
	{
		OR_Globals::MessageHandler()->Warning("OR_Log::OR_Log", "Could not create log file.");
		handler->close();
		return;
	}

	char *logname = &Name[0];

	sprintf(logname, "%s", LogName); 
	
	//Clean garbage
	memset(line,0,1024);
	sprintf(line,"Log File: %s \n", LogName);

	handler->write((char *) line,strlen(line));

	handler->close();

}

void OR_Log::AddTimeDate(void)
{
	char dbuffer[9];
	char tbuffer[9];

	_strdate(dbuffer);
	_strtime(tbuffer);

	AddString("Date: %s, Time: %s \n",dbuffer,tbuffer);
}

void OR_Log::AddString(char *error, ...)
{
	va_list argptr;
	char	text[1024];
	char	text2[1024];

	va_start (argptr,error);
	vsprintf (text, error, argptr);
	va_end (argptr);

	sprintf(text2,"%s", text);

	AddLine(text2);
}

void OR_Log::AddvString(char *string, va_list argptr)
{
	char	text[1024];
	vsprintf (text, string, argptr);
	AddLine(text);
}

void OR_Log::AddLine(char *text)
{
	std::fstream *handler;
	char line[1024];

	char tabs[1024]="\n";
	for (OR_I32 i=0 ; i<this->Indent ; ++i) tabs[i+1]='\t';

	handler = new std::fstream;

	handler->open((char *) Name,ios::binary | ios::out | ios::app);

	if(handler->fail()) {
		handler->close();
		return;
	}

	memset(line,0,1024);
	sprintf(line,"%s",text);

	char* pos=line;
	if (this->Indent)
		while(pos=strchr(pos,'\n'))
		{
			memmove(pos+this->Indent, pos, strlen(pos));
			strncpy(pos,tabs,this->Indent+1);
			pos = pos+1;
		}	
	
	handler->write((char *) line,strlen(line));

	handler->close();
}

void OR_Log::AddOSVersion()
{
	OSVERSIONINFO OSinfo;
	OSinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&OSinfo);
	
	BOOL bIsWindows98orLater = (OSinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
								( (OSinfo.dwMajorVersion > 4) ||
								( (OSinfo.dwMajorVersion == 4) && (OSinfo.dwMinorVersion > 0) ) );
	
	AddLine("\n--- OS Version Info ---");
	AddIndent();
	AddString("\nVersion: %u.%u.%u", OSinfo.dwMajorVersion,
			  OSinfo.dwMinorVersion, OSinfo.dwBuildNumber & 0xFFFF);
	if (strlen(&OSinfo.szCSDVersion[0]) > 1)
		AddString("\nAdditional info: %s", OSinfo.szCSDVersion);
	else
		AddLine("\nAdditional info: -none-");
	
	switch(OSinfo.dwPlatformId)
	{
		case VER_PLATFORM_WIN32s:
			AddLine("\nWin32s on Windows 3.1 detected.");
			break;
		case VER_PLATFORM_WIN32_WINDOWS:
			if (bIsWindows98orLater)
				AddLine("\nWindows 98 or later detected.");
			else
				if (LOWORD(OSinfo.dwBuildNumber) > 1080)
					AddLine("\nWindows 95 OSR2 detected.");
				else 
					AddLine("\nWindows 95 detected.");
			break;
		case VER_PLATFORM_WIN32_NT:
			AddLine("\nWindows NT detected.");
		break;
	}

	SubIndent();
	AddLine("\n--- End OS Version Info ---\n");
}

void OR_Log::AddMemorySatus()
{
	MEMORYSTATUS memstat;
	memstat.dwLength = sizeof(MEMORYSTATUS);

	GlobalMemoryStatus(&memstat);

	AddLine("\n--- Memory Stat ---");
	AddIndent();	
	AddString("\nTotal Physical Memory: %.02f MB.", memstat.dwTotalPhys/1048576.f);
	AddString("\nAvailable Physical Memory:  %.02f MB.", memstat.dwAvailPhys/1048576.f);
	AddString("\nTotal Virtual Memory: %u MB.", memstat.dwTotalVirtual/1048576);
	AddString("\nAvailable Virtual Memory:  %u MB.", memstat.dwAvailVirtual/1048576);
	SubIndent();
	AddLine("\n--- End Memory Stat ---\n");
}

void OR_Log::AddOrion3DConfiguration()
{
	AddLine("\n--- Orion3D configuration ---");
	AddIndent();	
	AddString("\n- Orion3D version : %.2f", 0.01*OR_ORION3D_Version);
	AddLine ("\n- Orion3D image library : ");
#ifdef _USE_OPENIL_
	AddLine ("Using OpenIL to handle image files.");
#else
	AddLine ("NOT* using OpenIL to handle image files. This is not supported yet.");
#endif
	/* archive messages ***********************************************/
	AddLine ("\n- Orion3D archives library : ");
#ifdef _USE_ZLIB_
	AddLine ("Using ZLIB to handle ZIP file archives.");
#else
	AddLine ("Not using ZLIB to handle ZIP file archives :  you won't be able to");
	AddLine ("          read or write ZIP archive. Define _USE_ZLIB_ to use ZLIB.");
#endif
	/* sound messages ***********************************************/
	AddLine ("\n- Orion3D sound library : ");
#ifdef _USE_ZLIB_
	AddLine ("Using FMOD to handle sound.");
#else
	AddLine ("Not using FMOD to handle sound :  you won't be able to play any sound.");
#endif
	/* output messages ***********************************************/
	AddLine ("\n- Orion3D input/output : ");
#ifdef _USE_GLUT_
	AddLine ("Using GLUT for input/output.");
#endif
#ifdef _USE_GTK_
	AddLine ("Using GTK+ for input/output.");
#endif
#ifdef _USE_WIN32_
	AddLine ("Using Win32 for input/output.");
#endif
#ifdef _USE_NONE_
	AddLine ("Not using any library for output/input : you must specify your own functions.");
#endif
	SubIndent();
	AddLine("\n--- End Orion3D configuration ---\n");	
}

void OR_Log::AddDriversConfiguration()
{
	AddLine("\n--- Extensions used by Orion3D ---");
	AddIndent();	
	/* cube mapping */
	if( OR_Globals::GLExtensionsManager()->IsCubeMapSupported() )
		AddLine("\n- Cube mapping is supported");
	else 
		AddLine("\n- Cube mapping is NOT supported");
	/* multitexturing */
	if( OR_Globals::GLExtensionsManager()->IsMultitextureSupported() )
		AddString( "\n- Multitexturing is supported with %i texture units.", 
				   OR_Globals::GLExtensionsManager()->GetNbTextureUnits() );
	else 
		AddLine("\n- Multitexturing is NOT supported");
	/* texture env combine */
	if( OR_Globals::GLExtensionsManager()->IsTextureEnvCombineSupported() ) 
		AddLine("\n- Texture env combine is supported");
	else 
		AddLine("\n- Texture env combine is NOT supported");
	SubIndent();
	AddLine("\n--- End extensions used by Orion3D ---\n");	

	/* opengl general information */
	char *str;
	unsigned short l1;	
	char car;
	AddLine("\n---OpenGL driver information ---");
	AddIndent();	
	/* vendor */
	str = (char *) glGetString(GL_VENDOR);
	if (str) AddString("\nVendor : %s",str);
	/* renderer */
	else AddString("\nVendor : unknown.");
	str = (char *) glGetString(GL_RENDERER);
	if (str) AddString("\nRenderer : %s ",str);
	else AddString("\nRenderer : unknown.");
	/* version */
	str = (char *) glGetString(GL_VERSION);
	if (str) AddString("\nVersion : %s ",str);
	else AddString("\nVersion : unknown.");
	/* extensions */
	AddString("\nSupported Extensions :");
	AddIndent();	
	str = (char *) glGetString(GL_EXTENSIONS);
	if(str) 
	{
		AddString("\n");
		for(l1=0;l1<strlen(str);l1++) 
		{
			car = *(str + l1);
			if(car == '\n') break;
			//if (l1 == 0) AddString("        ");
			if(car == ' ' /*&& *(str + l1 + 1) != 0*/) AddString("\n");
			else AddString("%c",car);
		}
	} 
	else 
	{
		AddString("\n-none-");
	}

	SubIndent();
	SubIndent();
	AddLine("\n--- End OpenGL Driver informations ---\n");
}

void OR_Log::AddIndent()
{
	++this->Indent;
}

void OR_Log::SubIndent()
{
	if (this->Indent>0)  --this->Indent;
}

void OR_Log::SetIndent(OR_I32 indent)
{
	if (indent>=0) this->Indent = indent;
}

OR_I32 OR_Log::GetIndent()
{
	return this->Indent;
}



void OR_Log::BuildFromFile( OR_File& file )
{
	/** \todo fille the export functions */
}

void OR_Log::BuildToFile( OR_File& file )
{
	/** \todo fille the export functions */
}

/*-------------------------------------------------------------------*/
/*                         class OR_LogManager                       */
/*-------------------------------------------------------------------*/
/* a manager of log.                                                 */
/*-------------------------------------------------------------------*/

OR_I32 OR_LogManager::AddLog(char* LogName)
{
	OR_Log* new_elt=new OR_Log(LogName);
	return AddElement(new_elt);
}

OR_RETURN_CODE OR_LogManager::AddString(char *error, ...)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	va_list argptr;

	va_start (argptr,error);
	GetElementSelected()->AddvString(error, argptr);
	va_end (argptr);
	return OR_OK;
}

OR_RETURN_CODE OR_LogManager::AddvString(char *string, va_list argptr)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;

	GetElementSelected()->AddvString(string, argptr);
	return OR_OK;

}

OR_RETURN_CODE OR_LogManager::AddLine(char *text)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->AddLine(text);
	return OR_OK;
}

OR_RETURN_CODE OR_LogManager::AddTimeDate()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->AddTimeDate();
	return OR_OK;
}

OR_RETURN_CODE OR_LogManager::AddOSVersion()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->AddOSVersion();
	return OR_OK;
}

OR_RETURN_CODE OR_LogManager::AddMemorySatus()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->AddMemorySatus();
	return OR_OK;
}

OR_RETURN_CODE OR_LogManager::AddOrion3DConfiguration()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->AddOrion3DConfiguration();
	return OR_OK;
}

OR_RETURN_CODE OR_LogManager::AddDriversConfiguration()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->AddDriversConfiguration();
	return OR_OK;
}

OR_RETURN_CODE OR_LogManager::AddIndent()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->AddIndent();
	return OR_OK;
}

OR_RETURN_CODE OR_LogManager::SubIndent()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SubIndent();
	return OR_OK;
}

OR_RETURN_CODE OR_LogManager::SetIndent(OR_I32 indent)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetIndent(indent);
	return OR_OK;
}

OR_I32 OR_LogManager::GetIndent()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;	
	return GetElementSelected()->GetIndent();
}


} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_license.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////