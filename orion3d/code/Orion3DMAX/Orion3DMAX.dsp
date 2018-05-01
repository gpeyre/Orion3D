# Microsoft Developer Studio Project File - Name="Orion3DMAX" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Orion3DMAX - Win32 Hybrid
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Orion3DMAX.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Orion3DMAX.mak" CFG="Orion3DMAX - Win32 Hybrid"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Orion3DMAX - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Orion3DMAX - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Orion3DMAX - Win32 Hybrid" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Orion3DMAX - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ORION3DMAX_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\orion3d" /I "\3dsmax4\maxsdk\include" /I "\3dsmax4\cstudio\sdk" /D "NDEBUG" /D "_USE_OPENIL_" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ORION3DMAX_EXPORTS" /D "ORION3D_IMPORTS" /U "_USE_SOUND_" /YX /FD /I /3dsmax4/maxsdk/include" /I /3dsmax4/maxsdk/include" /I /3dsmax4/maxsdk/include/" " " " /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmt" /out:"\3dsmax4\plugins\Orion3DMax.dlu" /libpath:"../binaries/external_lib" /libpath:"../binaries/orion3d_lib" /libpath:"/3dsmax4/maxsdk/lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying plug-in into .\bin folder
PostBuild_Cmds=copy \3dsmax4\plugins\Orion3DMax.dlu .\bin\ /Y	copy \3dsmax4\plugins\Orion3DMax.dlu ..\binaries\3dsmax_plugins\ /Y
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Orion3DMAX - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ORION3DMAX_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\orion3d" /I "\3dsmax4\maxsdk\include" /I "\3dsmax4\cstudio\sdk" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ORION3DMAX_EXPORTS" /D "ORION3D_IMPORTS" /U "_USE_SOUND_" /U "_USE_OPCODE_" /FR /YX /FD /I /3dsmax4/maxsdk/include" /I /3dsmax4/maxsdk/include" /I /3dsmax4/maxsdk/include" /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"libcmt" /out:"\3dsmax4\plugins\Orion3DMax.dlu" /pdbtype:sept /libpath:"../binaries/external_lib" /libpath:"../binaries/orion3d_lib" /libpath:"/3dsmax4/maxsdk/lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying plug-in into .\bin folder
PostBuild_Cmds=copy \3dsmax4\plugins\Orion3DMax.dlu .\bin\ /Y	copy \3dsmax4\plugins\Orion3DMax.dlu ..\binaries\3dsmax_plugins\ /Y
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Orion3DMAX - Win32 Hybrid"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Orion3DMAX___Win32_Hybrid"
# PROP BASE Intermediate_Dir "Orion3DMAX___Win32_Hybrid"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Orion3DMAX___Win32_Hybrid"
# PROP Intermediate_Dir "Orion3DMAX___Win32_Hybrid"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\orion3d" /I "\3dsmax4\maxsdk\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ORION3DMAX_EXPORTS" /YX /FD /I /3dsmax4/maxsdk/include" /I /3dsmax4/maxsdk/include" /I /3dsmax4/maxsdk/include" /GZ " " " /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\orion3d" /I "\3dsmax4\maxsdk\include" /I "\3dsmax4\cstudio\sdk" /D "_DEBUG" /D "_USE_OPENIL_" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ORION3DMAX_EXPORTS" /D "ORION3D_IMPORTS" /U "_USE_SOUND_" /YX /FD /I /3dsmax4/maxsdk/include" /I /3dsmax4/maxsdk/include" /I /3dsmax4/maxsdk/include" /GZ " " " /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ../fmod/fmodvc.lib opengl32.lib glu32.lib glut32.lib winmm.lib comctl32.lib geom.lib maxutil.lib core.lib mesh.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"\3dsmax4\plugins\Orion3DMax.dle" /pdbtype:sept /libpath:"\3dsmax4\maxsdk\lib" /libpath:"..\orion3d\debug" /libpath:"/3dsmax4/maxsdk/lib/"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"\3dsmax4\plugins\Orion3DMax.dlu" /pdbtype:sept /libpath:"../binaries/external_lib" /libpath:"../binaries/orion3d_lib" /libpath:"/3dsmax4/maxsdk/lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying plug-in into .\bin folder
PostBuild_Cmds=copy \3dsmax4\plugins\Orion3DMax.dlu .\bin\ /Y	copy \3dsmax4\plugins\Orion3DMax.dlu ..\binaries\3dsmax_plugins\ /Y
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Orion3DMAX - Win32 Release"
# Name "Orion3DMAX - Win32 Debug"
# Name "Orion3DMAX - Win32 Hybrid"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Viewer Sources"

# PROP Default_Filter ".cpp"
# Begin Group "Globals"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\O3DMAXViewer\Globals.cpp
# ADD CPP /Yu"../stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\Globals.h
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\O3DMAXViewer\Interface.cpp
# ADD CPP /Yu"../stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\Interface.h
# End Source File
# End Group
# Begin Group "Interface_Orion3D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\O3DMAXViewer\Interface_Orion3D.cpp
# ADD CPP /Yu"../stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\Interface_Orion3D.h
# End Source File
# End Group
# Begin Group "O3DMAXViewer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\O3DMAXViewer\O3DMAXViewer.cpp
# ADD CPP /Yu"../stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\O3DMAXViewer.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\O3DMAXViewer\resource.h
# End Source File
# End Group
# Begin Group "3DS to Orion3D Wrapper"

# PROP Default_Filter ""
# Begin Group "OR_3DS Files"

# PROP Default_Filter ""
# Begin Group "OR_3DS_MAXMaterial"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_3DS_MAXMaterial.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_MAXMaterial.h
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_MAXMaterial.inl
# End Source File
# End Group
# Begin Group "OR_3DS_MAXNode"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_3DS_MAXNode.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_MAXNode.h
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_MAXNode.inl
# End Source File
# End Group
# Begin Group "OR_3DS_Node"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_3DS_Node.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_Node.h
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_Node.inl
# End Source File
# End Group
# Begin Group "OR_3DS_UserParam"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_3DS_UserParam.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_UserParam.h
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_UserParam.inl
# End Source File
# End Group
# Begin Group "OR_3DS_Utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_3DS_Utils.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_Utils.h
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_Utils.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\OR_3DS.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\OR_3DS_Wrapper.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\OR_3DS_Wrapper.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Orion3DMAX.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Orion3DMAX.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\O3DMAXViewer\binary.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\boite.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\filled.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\fold.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\foldopen.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\logo2.bmp
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\logoblue.bmp
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\O3DMAXViewer.rc
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\point.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\reduce.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\text.ico
# End Source File
# Begin Source File

SOURCE=.\O3DMAXViewer\wire.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\Orion3DMAX.def
# End Source File
# End Target
# End Project
