# Microsoft Developer Studio Project File - Name="wrapper_lua" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=wrapper_lua - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wrapper_lua.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wrapper_lua.mak" CFG="wrapper_lua - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wrapper_lua - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "wrapper_lua - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wrapper_lua - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/Release"
# PROP Intermediate_Dir "obj/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../lua" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../binaries/orion3d_lib/orion3d_wrapper_lua.lib"

!ELSEIF  "$(CFG)" == "wrapper_lua - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/Debug"
# PROP Intermediate_Dir "obj/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../lua" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../binaries/orion3d_lib/orion3d_wrapper_lua_dbg.lib"

!ENDIF 

# Begin Target

# Name "wrapper_lua - Win32 Release"
# Name "wrapper_lua - Win32 Debug"
# Begin Group "Variables"

# PROP Default_Filter ""
# Begin Group "Float"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_LUA_Float.cpp
# End Source File
# Begin Source File

SOURCE=.\OR_LUA_Float.h
# End Source File
# End Group
# Begin Group "String"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_LUA_String.cpp
# End Source File
# Begin Source File

SOURCE=.\OR_LUA_String.h
# End Source File
# End Group
# Begin Group "Array"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_LUA_Array.cpp
# End Source File
# Begin Source File

SOURCE=.\OR_LUA_Array.h
# End Source File
# End Group
# Begin Group "Table"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_LUA_Table.cpp
# End Source File
# Begin Source File

SOURCE=.\OR_LUA_Table.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\OR_LUAVariable_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\OR_LUAVariable_ABC.h
# End Source File
# End Group
# Begin Group "Main Class"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OR_WrapperLUA.cpp
# End Source File
# Begin Source File

SOURCE=.\OR_WrapperLUA.h
# End Source File
# Begin Source File

SOURCE=.\OR_WrapperLUA.inl
# End Source File
# End Group
# Begin Group "Doc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\doc\dxt\OR_LUA_MainPage.dxt
# End Source File
# End Group
# Begin Source File

SOURCE=.\OR_LUA_Config.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Target
# End Project
