# Microsoft Developer Studio Project File - Name="orion3d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=orion3d - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "orion3d.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "orion3d.mak" CFG="orion3d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "orion3d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "orion3d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "orion3d - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "orion3d___Win32_Debug"
# PROP BASE Intermediate_Dir "orion3d___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj\Debug"
# PROP Intermediate_Dir "obj\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /w /W0 /Gm /GX /ZI /Od /D "_DEBUG" /D "_MBCS" /D "_USE_GLUT_" /D "ORION3D_EXPORTS" /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_WIN32_" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /Od /D "_DEBUG" /D "_MBCS" /D "ORION3D_EXPORTS" /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_WIN32_" /FR /Yu"../stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_USE_GLUT_" /d "ORION3D_EXPORTS"
# ADD RSC /l 0x40c /d "_DEBUG" /d "ORION3D_EXPORTS"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../binaries/orion3d_dll/orion3d_glut.dll" /pdbtype:sept /libpath:"../binaries/external_lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"libcmt" /nodefaultlib:"msvcrt" /out:"../binaries/orion3d_dll/orion3d_dbg.dll" /implib:"../binaries/orion3d_lib/orion3d_dbg.lib" /pdbtype:sept /libpath:"../binaries/external_lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy_lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "orion3d - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "orion3d___Win32_Release"
# PROP BASE Intermediate_Dir "orion3d___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj\Release"
# PROP Intermediate_Dir "obj\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_MBCS_USE_GLUT_" /D "ORION3D_EXPORTS" /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_WIN32_" /FR /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_MBCS" /D "ORION3D_EXPORTS" /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_WIN32_" /FR /Yu"../stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_USE_GLUT_" /d "ORION3D_EXPORTS"
# ADD RSC /l 0x40c /d "NDEBUG" /d "ORION3D_EXPORTS"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../binaries/orion3d_dll/orion3d_glut.dll" /libpath:"../binaries/external_lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../binaries/orion3d_dll/orion3d.dll" /implib:"../binaries/orion3d_lib/orion3d.lib" /libpath:"../binaries/external_lib" /libpath:"../binaries/orion3d_lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy_lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "orion3d - Win32 Debug"
# Name "orion3d - Win32 Release"
# Begin Group "animation"

# PROP Default_Filter ""
# Begin Group "Animation  node"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation\OR_AnimationNode.cpp
# End Source File
# Begin Source File

SOURCE=.\animation\OR_AnimationNode.h
# End Source File
# Begin Source File

SOURCE=.\animation\OR_AnimationNode.inl
# End Source File
# End Group
# Begin Group "Player"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation\OR_AnimationPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\animation\OR_AnimationPlayer.h
# End Source File
# Begin Source File

SOURCE=.\animation\OR_AnimationPlayer.inl
# End Source File
# End Group
# Begin Group "Track"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation\OR_AnimationTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\animation\OR_AnimationTrack.h
# End Source File
# Begin Source File

SOURCE=.\animation\OR_AnimationTrack.inl
# End Source File
# End Group
# Begin Group "Evaluator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation\OR_Evaluator.cpp
# End Source File
# Begin Source File

SOURCE=.\animation\OR_Evaluator.h
# End Source File
# End Group
# Begin Group "Keyframe"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation\OR_KeyFrame.h
# End Source File
# End Group
# Begin Group "Animation Manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation\OR_AnimationManager.cpp
# End Source File
# Begin Source File

SOURCE=.\animation\OR_AnimationManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\animation\OR_Animation.cpp
# End Source File
# Begin Source File

SOURCE=.\animation\OR_Animation.h
# End Source File
# End Group
# Begin Group "bsp_portal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bsp_portal\OR_BSP.cpp
# End Source File
# Begin Source File

SOURCE=.\bsp_portal\OR_BSP.h
# End Source File
# Begin Source File

SOURCE=.\bsp_portal\OR_Portals.cpp
# End Source File
# Begin Source File

SOURCE=.\bsp_portal\OR_Portals.h
# End Source File
# Begin Source File

SOURCE=.\bsp_portal\OR_Q3BSP.cpp
# End Source File
# Begin Source File

SOURCE=.\bsp_portal\OR_Q3BSP.h
# End Source File
# Begin Source File

SOURCE=.\bsp_portal\OR_Q3Structs.h
# End Source File
# End Group
# Begin Group "configuration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\configuration\OR_Config.h
# End Source File
# Begin Source File

SOURCE=.\configuration\OR_DebugConfig.h
# End Source File
# End Group
# Begin Group "documentation"

# PROP Default_Filter ""
# Begin Group "dxt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\documentation\OR_Doc_Distribution.dxt
# End Source File
# Begin Source File

SOURCE=.\documentation\OR_Doc_InstallCompil.dxt
# End Source File
# Begin Source File

SOURCE=.\documentation\OR_Doc_Licence.dxt
# End Source File
# Begin Source File

SOURCE=.\documentation\OR_Doc_MainPage.dxt
# End Source File
# Begin Source File

SOURCE=.\documentation\OR_Doc_Overview.dxt
# End Source File
# Begin Source File

SOURCE=.\documentation\OR_Doc_PhysicEngine.dxt
# End Source File
# Begin Source File

SOURCE=.\documentation\OR_Doc_ProgrammingNorms.dxt
# End Source File
# Begin Source File

SOURCE=.\documentation\OR_Doc_ScriptShell.dxt
# End Source File
# End Group
# Begin Group "macros"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\documentation\MacroOrion3D.dsm
# End Source File
# End Group
# Begin Source File

SOURCE=.\doxygen.cfg
# End Source File
# End Group
# Begin Group "hierarchy"

# PROP Default_Filter ""
# Begin Group "Node"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hierarchy\OR_Node.cpp
# End Source File
# Begin Source File

SOURCE=.\hierarchy\OR_Node.h
# End Source File
# Begin Source File

SOURCE=.\hierarchy\OR_Node.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\hierarchy\OR_HierarchyTree.cpp
# End Source File
# Begin Source File

SOURCE=.\hierarchy\OR_HierarchyTree.h
# End Source File
# Begin Source File

SOURCE=.\hierarchy\OR_HierarchyTree.inl
# End Source File
# End Group
# Begin Group "misc"

# PROP Default_Filter ""
# Begin Group "Export headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\OR_ExportHeader_ACT.h
# End Source File
# Begin Source File

SOURCE=.\misc\OR_ExportHeader_KRD.h
# End Source File
# End Group
# Begin Group "Constant/Types/Func/Macros"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\OR_Constants.h
# End Source File
# Begin Source File

SOURCE=.\misc\OR_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\OR_Functions.h
# End Source File
# Begin Source File

SOURCE=.\misc\OR_Macros.h
# End Source File
# Begin Source File

SOURCE=.\misc\OR_ReturnCodes.h
# End Source File
# Begin Source File

SOURCE=.\misc\OR_System.h
# End Source File
# Begin Source File

SOURCE=.\misc\OR_Types.h
# End Source File
# End Group
# Begin Group "Endian convention"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\OR_Endian_Conv.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\OR_Endian_Conv.h
# End Source File
# End Group
# Begin Group "Build log"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\OR_PrintBuildLog.h
# End Source File
# End Group
# Begin Group "Global variables"

# PROP Default_Filter ""
# Begin Group "Global Workspace"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\OR_GlobalWorspace.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\OR_GlobalWorspace.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\misc\OR_Globals.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\OR_Globals.h
# End Source File
# Begin Source File

SOURCE=.\misc\OR_Globals.inl
# End Source File
# End Group
# Begin Group "Conversion"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\OR_Conversion.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\OR_Conversion.h
# End Source File
# End Group
# End Group
# Begin Group "objects"

# PROP Default_Filter ""
# Begin Group "Bone"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_Bone.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Bone.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Bone.inl
# End Source File
# End Group
# Begin Group "Cameras"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_Camera.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Camera.h
# End Source File
# End Group
# Begin Group "Gizmos"

# PROP Default_Filter ""
# Begin Group "Sphere gizmo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_SphereGizmo.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_SphereGizmo.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_SphereGizmo.inl
# End Source File
# End Group
# Begin Group "Square gizmo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_SquareGizmo.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_SquareGizmo.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_SquareGizmo.inl
# End Source File
# End Group
# Begin Group "Cylinder gizmo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_CylinderGizmo.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_CylinderGizmo.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_CylinderGizmo.inl
# End Source File
# End Group
# Begin Group "Cube gizmo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_CubeGizmo.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_CubeGizmo.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_CubeGizmo.inl
# End Source File
# End Group
# Begin Group "Point gizmo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_PointGizmo.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_PointGizmo.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_PointGizmo.inl
# End Source File
# End Group
# Begin Group "Vector gizmo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_VectorGizmo.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_VectorGizmo.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_VectorGizmo.inl
# End Source File
# End Group
# Begin Group "Gizmo manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_GizmoManager.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_GizmoManager.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_GizmoManager.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\objects\OR_Gizmo.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Gizmo.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Gizmo.inl
# End Source File
# End Group
# Begin Group "Lights"

# PROP Default_Filter ""
# Begin Group "Light ID manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_LightIDManager.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_LightIDManager.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_LightIDManager.inl
# End Source File
# End Group
# Begin Group "Light manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_LightManager.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_LightManager.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_LightManager.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\objects\OR_Light.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Light.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Light.inl
# End Source File
# End Group
# Begin Group "Mesh"

# PROP Default_Filter ""
# Begin Group "Skin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_Skin.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Skin.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Skin.inl
# End Source File
# End Group
# Begin Group "MeshData"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_MeshDataManager.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_MeshDataManager.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_MeshDataManager.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\objects\OR_Mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Mesh.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Mesh.inl
# End Source File
# End Group
# Begin Group "Object manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_ObjectManager.h
# End Source File
# End Group
# Begin Group "Maths surface"

# PROP Default_Filter ""
# Begin Group "Math surface manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_MathSurfaceManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\objects\OR_MathSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_MathSurface.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_MathSurface.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\objects\OR_Object.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Object.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Object.inl
# End Source File
# End Group
# Begin Group "opengl"

# PROP Default_Filter ""
# Begin Group "Context"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\opengl\OR_Context.cpp
# End Source File
# Begin Source File

SOURCE=.\opengl\OR_Context.h
# End Source File
# Begin Source File

SOURCE=.\opengl\OR_Context.inl
# End Source File
# End Group
# Begin Group "Extensions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\opengl\OR_GLExtensions.cpp
# End Source File
# Begin Source File

SOURCE=.\opengl\OR_GLExtensions.h
# End Source File
# Begin Source File

SOURCE=.\opengl\OR_GLExtensionsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\opengl\OR_GLExtensionsManager.h
# End Source File
# End Group
# End Group
# Begin Group "physic"

# PROP Default_Filter ""
# Begin Group "Forces"

# PROP Default_Filter ""
# Begin Group "Constant force"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_ConstantForce.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_ConstantForce.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_ConstantForce.inl
# End Source File
# End Group
# Begin Group "Force Manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_ForceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_ForceManager.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_ForceManager.inl
# End Source File
# End Group
# Begin Group "Gravity"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_GravityForce.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_GravityForce.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_GravityForce.inl
# End Source File
# End Group
# Begin Group "Damping force"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_DampingForce.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DampingForce.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DampingForce.inl
# End Source File
# End Group
# Begin Group "Magnetic force"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_MagneticForce.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_MagneticForce.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_MagneticForce.inl
# End Source File
# End Group
# Begin Group "Spring force"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_SpringForce.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_SpringForce.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_SpringForce.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_Force_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Force_ABC.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Force_ABC.inl
# End Source File
# End Group
# Begin Group "Collision"

# PROP Default_Filter ""
# Begin Group "Collision manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_CollisionManager.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_CollisionManager.h
# End Source File
# End Group
# Begin Group "Collider"

# PROP Default_Filter ""
# Begin Group "Rigid body collider"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_RigidBodyCollider.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_RigidBodyCollider.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_RigidBodyCollider.inl
# End Source File
# End Group
# Begin Group "Deflector collider"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_DeflectorCollider.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DeflectorCollider.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DeflectorCollider.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_Collider_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Collider_ABC.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Collider_ABC.inl
# End Source File
# End Group
# Begin Group "Physic model"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_PhysicModel.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_PhysicModel.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_PhysicModel.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_Collision.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Collision.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Collision.inl
# End Source File
# End Group
# Begin Group "Particule"

# PROP Default_Filter ""
# Begin Group "Particules manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_ParticuleManager.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_ParticuleManager.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_ParticuleManager.inl
# End Source File
# End Group
# Begin Group "Constraint"

# PROP Default_Filter ""
# Begin Group "Constraints manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_ConstraintManager.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_ConstraintManager.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_ConstraintManager.inl
# End Source File
# End Group
# Begin Group "Relaxable"

# PROP Default_Filter ""
# Begin Group "Distance"

# PROP Default_Filter ""
# Begin Group "Minimum"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_MinimumDistanceConstraint.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_MinimumDistanceConstraint.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_MinimumDistanceConstraint.inl
# End Source File
# End Group
# Begin Group "Maximum"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_MaximumDistanceConstraint.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_MaximumDistanceConstraint.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_MaximumDistanceConstraint.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_DistanceConstraint_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DistanceConstraint_ABC.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DistanceConstraint_ABC.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_RelaxableConstraint_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_RelaxableConstraint_ABC.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_RelaxableConstraint_ABC.inl
# End Source File
# End Group
# Begin Group "Non relaxable"

# PROP Default_Filter ""
# Begin Group "Spring"

# PROP Default_Filter ""
# Begin Group "Damped spring"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_DampedSpringConstraint.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DampedSpringConstraint.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DampedSpringConstraint.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_PushSpringConstraint.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_PushSpringConstraint.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_PushSpringConstraint.inl
# End Source File
# Begin Source File

SOURCE=.\physic\OR_SpringConstraint.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_SpringConstraint.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_SpringConstraint.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_NonRelaxableConstraint_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_NonRelaxableConstraint_ABC.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_NonRelaxableConstraint_ABC.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_Constraint_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Constraint_ABC.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Constraint_ABC.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_Particule.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Particule.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Particule.inl
# End Source File
# End Group
# Begin Group "Deflector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_Deflector_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Deflector_ABC.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Deflector_ABC.inl
# End Source File
# End Group
# Begin Group "Rigid body"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_RigidBody.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_RigidBody.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_RigidBody.inl
# End Source File
# End Group
# Begin Group "Physic entity"

# PROP Default_Filter ""
# Begin Group "Physic entity manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_PhysicEntityManager.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_PhysicEntityManager.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_PhysicEntityManager.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_PhysicEntity.h
# End Source File
# End Group
# Begin Group "Joint"

# PROP Default_Filter ""
# Begin Group "Joint manager"

# PROP Default_Filter ""
# Begin Group "Joint manager token"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_JointManagerToken.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_JointManagerToken.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_JointManagerToken.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_JointManager.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_JointManager.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_JointManager.inl
# End Source File
# End Group
# Begin Group "Spherical Joint"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_SphericalJoint.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_SphericalJoint.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_SphericalJoint.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\physic\OR_Joint_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Joint_ABC.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Joint_ABC.inl
# End Source File
# End Group
# End Group
# Begin Group "shaders"

# PROP Default_Filter ""
# Begin Group "Alpha pipeline"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_AlphaPipeline.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_AlphaPipeline.h
# End Source File
# End Group
# Begin Group "Shadable"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_Shadable.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_Shadable.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_Shadable.inl
# End Source File
# End Group
# Begin Group "Texture"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_Texture.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_Texture.h
# End Source File
# End Group
# Begin Group "Shader Manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_ShaderManager.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_ShaderManager.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_ShaderManager.inl
# End Source File
# End Group
# Begin Group "Shaders class"

# PROP Default_Filter ""
# Begin Group "Shader flat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_FlatShader.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_FlatShader.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_FlatShader.inl
# End Source File
# End Group
# Begin Group "Shader bump"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_BumpShader_Emboss.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_BumpShader_Emboss.h
# End Source File
# End Group
# Begin Group "Shader single texture"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_SingleTextureMapShader.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_SingleTextureMapShader.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_SingleTextureMapShader.inl
# End Source File
# End Group
# Begin Group "Shader reflexive"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_ReflexiveMapShader.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_ReflexiveMapShader.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_ReflexiveMapShader.inl
# End Source File
# End Group
# Begin Group "Shader cartoon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_CartoonShader.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_CartoonShader.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_CartoonShader.inl
# End Source File
# End Group
# Begin Group "Bilboard shaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_BillboardShader.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_BillboardShader.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_BillboardShader.inl
# End Source File
# End Group
# Begin Group "MultiShader"

# PROP Default_Filter ""
# Begin Group "MultishaderToken"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shaders\OR_MultishaderToken.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_MultishaderToken.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_MultishaderToken.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\shaders\OR_MultiShader.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_MultiShader.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_MultiShader.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\shaders\OR_Shader.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_Shader.h
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_Shader.inl
# End Source File
# End Group
# End Group
# Begin Group "special_effects"

# PROP Default_Filter ""
# Begin Group "Fog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\special_effects\OR_Fog.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_Fog.h
# End Source File
# End Group
# Begin Group "Lens flare"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\special_effects\OR_LensFlare.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_LensFlare.h
# End Source File
# End Group
# Begin Group "Surfaces"

# PROP Default_Filter ""
# Begin Group "Surface tesslator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\special_effects\OR_SurfaceTeslator.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_SurfaceTeslator.h
# End Source File
# End Group
# End Group
# Begin Group "Particules system"

# PROP Default_Filter ""
# Begin Group "Emmitter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\special_effects\OR_Emitter_ABC.h
# End Source File
# End Group
# Begin Group "Displayable particules"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\special_effects\OR_DisplayableParticule.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_DisplayableParticule.h
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_DisplayableParticule.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\special_effects\OR_ParticuleSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_ParticuleSystem.h
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_ParticuleSystem.inl
# End Source File
# End Group
# Begin Group "Cloth"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\special_effects\OR_Cloth.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_Cloth.h
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_Cloth.inl
# End Source File
# End Group
# Begin Group "Special effect manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\special_effects\OR_SpecialEffectManager.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_SpecialEffectManager.h
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_SpecialEffectManager.inl
# End Source File
# End Group
# Begin Group "Meta-env"

# PROP Default_Filter ""
# Begin Group "Iso surface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\special_effects\OR_IsoSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_IsoSurface.h
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_IsoSurfaceTab.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_IsoSurfaceTab.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\special_effects\OR_MetaEnv.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_MetaEnv.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\special_effects\OR_SpecialEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_SpecialEffect.h
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_SpecialEffect.inl
# End Source File
# End Group
# Begin Group "utils"

# PROP Default_Filter ""
# Begin Group "Archive zip"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_Archive.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_Archive.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_Zip.h
# End Source File
# End Group
# Begin Group "Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_Data.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_Data.h
# End Source File
# End Group
# Begin Group "File"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_File.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_File.h
# End Source File
# End Group
# Begin Group "Log"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_Log.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_Log.h
# End Source File
# End Group
# Begin Group "Message"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_MessageHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_MessageHandler.h
# End Source File
# End Group
# Begin Group "Performances"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_PerformancesManager.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_PerformancesManager.h
# End Source File
# End Group
# Begin Group "Serialization"

# PROP Default_Filter ""
# Begin Group "Serializable"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_Serializable.h
# End Source File
# End Group
# Begin Group "Serializer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_Serializer.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_Serializer.h
# End Source File
# End Group
# End Group
# Begin Group "Templates"

# PROP Default_Filter ""
# Begin Group "Manager"

# PROP Default_Filter ""
# Begin Group "Smart counter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_SmartCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_SmartCounter.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_SmartCounter.inl
# End Source File
# End Group
# Begin Group "Smart manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_SmartManagerMap_Template.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\utils\OR_ManagerList_Template.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_ManagerMap_Template.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_PriorityManager_Template.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\utils\OR_List_Template.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_Vector_Template.h
# End Source File
# End Group
# Begin Group "String"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_String.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_String.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_String.inl
# End Source File
# Begin Source File

SOURCE=.\utils\OR_StringTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_StringTokenizer.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_StringTokenizer.inl
# End Source File
# Begin Source File

SOURCE=.\utils\OR_StrVector.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_StrVector.h
# End Source File
# End Group
# Begin Group "Exception"

# PROP Default_Filter ""
# Begin Group "Message exception"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_MsgException.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_MsgException.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_MsgException.inl
# End Source File
# End Group
# Begin Group "Exception handler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_ExceptionHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_ExceptionHandler.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_ExceptionHandler.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\utils\OR_Exception_ABC.h
# End Source File
# End Group
# Begin Group "Class factory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_ClassFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_ClassFactory.h
# End Source File
# End Group
# Begin Group "ID management"

# PROP Default_Filter ""
# Begin Group "ID stack"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_IDStack.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_IDStack.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_IDStack.inl
# End Source File
# End Group
# End Group
# Begin Group "Sorting"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_RadixSort.cpp
# End Source File
# Begin Source File

SOURCE=.\utils\OR_RadixSort.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_RadixSort.inl
# End Source File
# End Group
# End Group
# Begin Group "input_output"

# PROP Default_Filter ""
# Begin Group "Screen saver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\input_output\OR_SaverSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\input_output\OR_SaverSettings.h
# End Source File
# End Group
# Begin Group "Viewport"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\input_output\OR_Viewport.cpp
# End Source File
# Begin Source File

SOURCE=.\input_output\OR_Viewport.h
# End Source File
# End Group
# Begin Group "Winamp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\input_output\OR_WinAmp.cpp
# End Source File
# Begin Source File

SOURCE=.\input_output\OR_WinAmp.h
# End Source File
# End Group
# Begin Group "Renderer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\input_output\OR_Renderer_ABC.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\input_output\OR_InputOutput_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\input_output\OR_InputOutput_ABC.h
# End Source File
# Begin Source File

SOURCE=.\input_output\OR_InputOutput_ABC.inl
# End Source File
# End Group
# Begin Group "shell"

# PROP Default_Filter ""
# Begin Group "Shell concole"

# PROP Default_Filter ""
# Begin Group "Text console"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shell\OR_ShellConsoleText.cpp
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellConsoleText.h
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellConsoleText.inl
# End Source File
# End Group
# Begin Group "Shell console history"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shell\OR_ShellConsoleHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellConsoleHistory.h
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellConsoleHistory.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\shell\OR_ShellConsole_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellConsole_ABC.h
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellConsole_ABC.inl
# End Source File
# End Group
# Begin Group "Shell stack"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shell\OR_ShellCallStack.cpp
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellCallStack.h
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellCallStack.inl
# End Source File
# End Group
# Begin Group "Shell functions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shell\OR_ShellFuncDecl.cpp
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellFuncDecl.h
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellFuncDecl.inl
# End Source File
# End Group
# Begin Group "Shell kernel"

# PROP Default_Filter ""
# Begin Group "Shell kernel manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shell\OR_ShellKernelManager.cpp
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellKernelManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\shell\OR_ShellKernel.cpp
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellKernel.h
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellKernel.inl
# End Source File
# End Group
# Begin Group "Shell object"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shell\OR_ShellObject_ABC.cpp
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellObject_ABC.h
# End Source File
# Begin Source File

SOURCE=.\shell\OR_ShellObject_ABC.inl
# End Source File
# End Group
# End Group
# Begin Group "maths"

# PROP Default_Filter ""
# Begin Group "Plane"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\maths\OR_Plane.cpp
# End Source File
# Begin Source File

SOURCE=.\maths\OR_Plane.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\maths\OR_Maths.cpp
# End Source File
# Begin Source File

SOURCE=.\maths\OR_Maths.h
# End Source File
# Begin Source File

SOURCE=.\maths\OR_Maths.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\OR_Dll.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Target
# End Project
