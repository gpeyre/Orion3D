# Microsoft Developer Studio Project File - Name="orion3d_maths" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=orion3d_maths - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "orion3d_maths.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "orion3d_maths.mak" CFG="orion3d_maths - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "orion3d_maths - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "orion3d_maths - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../binaries/orion3d_lib/orion3d_maths_dbg.lib"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../binaries/orion3d_lib/orion3d_maths_dbg.lib"

!ENDIF 

# Begin Target

# Name "orion3d_maths - Win32 Release"
# Name "orion3d_maths - Win32 Debug"
# Begin Group "maths"

# PROP Default_Filter ""
# Begin Group "Quaternion"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_Quaternion.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_Quaternion.h
# End Source File
# Begin Source File

SOURCE=.\OML_Quaternion.inl
# End Source File
# End Group
# Begin Group "Matrix"

# PROP Default_Filter ""
# Begin Group "Matrix 4x4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_Matrix4x4.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_Matrix4x4.h
# End Source File
# Begin Source File

SOURCE=.\OML_Matrix4x4.inl
# End Source File
# End Group
# Begin Group "Matrix NxP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_MatrixNxP.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_MatrixNxP.h
# End Source File
# Begin Source File

SOURCE=.\OML_MatrixNxP.inl
# End Source File
# End Group
# Begin Group "Sparse matrix"

# PROP Default_Filter ""
# Begin Group "Sparse matrix block"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_SparseMatrixBlock.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_SparseMatrixBlock.h
# End Source File
# Begin Source File

SOURCE=.\OML_SparseMatrixBlock.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\OML_SparseMatrix.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_SparseMatrix.h
# End Source File
# Begin Source File

SOURCE=.\OML_SparseMatrix.inl
# End Source File
# End Group
# Begin Group "Matrix 3x3"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_Matrix3x3.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_Matrix3x3.h
# End Source File
# Begin Source File

SOURCE=.\OML_Matrix3x3.inl
# End Source File
# End Group
# End Group
# Begin Group "Vector"

# PROP Default_Filter ""
# Begin Group "Vector 2D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_Vector2D.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_Vector2D.h
# End Source File
# Begin Source File

SOURCE=.\OML_Vector2D.inl
# End Source File
# End Group
# Begin Group "Vector 3D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_Vector3D.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_Vector3D.h
# End Source File
# Begin Source File

SOURCE=.\OML_Vector3D.inl
# End Source File
# End Group
# Begin Group "Vector 4D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_Vector4D.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_Vector4D.h
# End Source File
# Begin Source File

SOURCE=.\OML_Vector4D.inl
# End Source File
# End Group
# Begin Group "Vector ND"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_VectorND.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_VectorND.h
# End Source File
# Begin Source File

SOURCE=.\OML_VectorND.inl
# End Source File
# End Group
# End Group
# Begin Group "Ray cast"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OML_RayCaster.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_RayCaster.h
# End Source File
# Begin Source File

SOURCE=.\OML_RayCaster.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\OML_Maths.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OML_Maths.h
# End Source File
# Begin Source File

SOURCE=.\OML_Maths.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\OML_Config.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "orion3d_maths - Win32 Release"

!ELSEIF  "$(CFG)" == "orion3d_maths - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Target
# End Project
