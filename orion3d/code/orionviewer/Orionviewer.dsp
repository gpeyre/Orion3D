# Microsoft Developer Studio Project File - Name="Orionviewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Orionviewer - Win32 Debug Glut
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Orionviewer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Orionviewer.mak" CFG="Orionviewer - Win32 Debug Glut"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Orionviewer - Win32 Debug Glut" (based on "Win32 (x86) Console Application")
!MESSAGE "Orionviewer - Win32 Release Glut" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Orionviewer - Win32 Debug Glut"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Orionviewer___Win32_Debug_Glut"
# PROP BASE Intermediate_Dir "Orionviewer___Win32_Debug_Glut"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/Debug_Glut"
# PROP Intermediate_Dir "obj/Debug_Glut"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /w /W0 /Gm /GX /ZI /Od /D "_DEBUG" /D "_USE_GLUT_" /D "ORION3D_IMPORTS" /D "_CONSOLE" /D "WIN32" /D "_MBCS" /D "_WIN32_" /Fr /YX /FD /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../lua" /D "_DEBUG" /D "_USE_GLUT_" /D "_CONSOLE" /D "WIN32" /D "_MBCS" /D "_WIN32_" /D "ORION3D_IMPORTS" /Fr /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /debug /machine:I386 /out:"orionviewer_glut.exe" /libpath:"../binaries/external_lib" /libpath:"../binaries/orion3d_lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /debug /machine:I386 /out:"orionviewer_glut.exe" /libpath:"../binaries/external_lib" /libpath:"../binaries/orion3d_lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=copy_dll
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Orionviewer - Win32 Release Glut"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Orionviewer___Win32_Release_Glut"
# PROP BASE Intermediate_Dir "Orionviewer___Win32_Release_Glut"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/Release Glut"
# PROP Intermediate_Dir "obj/Release Glut"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "_USE_GLUT_" /D "_CONSOLE" /D "WIN32" /D "_MBCS" /D "_WIN32_" /D "ORION3D_STATICLINK" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../lua" /D "NDEBUG" /D "_USE_GLUT_" /D "_CONSOLE" /D "WIN32" /D "_MBCS" /D "_WIN32_" /D "ORION3D_IMPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG _USE_GLUT_"
# ADD RSC /l 0x40c /d "NDEBUG _USE_GLUT_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 glut32.lib zlib.lib openil.lib fmodvc.lib opengl32.lib glu32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"orionviewer_glut.exe" /libpath:"../binaries/external_lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"orionviewer_glut.exe" /libpath:"../binaries/external_lib" /libpath:"../binaries/orion3d_lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=copy_dll
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Orionviewer - Win32 Debug Glut"
# Name "Orionviewer - Win32 Release Glut"
# Begin Group "ReadMe, licence & doc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\orion3d_license.txt
# End Source File
# Begin Source File

SOURCE=.\OrionViewer.dxt
# End Source File
# Begin Source File

SOURCE=.\orionviewer_help.txt
# End Source File
# Begin Source File

SOURCE=.\OrionViewer_Readme.txt
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\Orionviewer.rc
# End Source File
# End Group
# Begin Group "pch"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "GTK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OrionViewer_GTK.cpp
# End Source File
# Begin Source File

SOURCE=.\OrionViewer_GTK.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\OrionViewer.cpp
# End Source File
# End Target
# End Project
