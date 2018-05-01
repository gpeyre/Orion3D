# Microsoft Developer Studio Project File - Name="orion3d_static" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=orion3d_static - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "orion3d_static.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "orion3d_static.mak" CFG="orion3d_static - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "orion3d_static - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "orion3d_static - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "orion3d_static - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj\Release"
# PROP Intermediate_Dir "obj\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"../stdafx.h" /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../binaries/orion3d_lib/orion3d_static.lib"

!ELSEIF  "$(CFG)" == "orion3d_static - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj\Debug_static"
# PROP Intermediate_Dir "obj\Debug_static"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"../stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../binaries/orion3d_lib/orion3d_static_dbg.lib"

!ENDIF 

# Begin Target

# Name "orion3d_static - Win32 Release"
# Name "orion3d_static - Win32 Debug"
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
# Begin Group "Serializable"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_Serializable.h
# End Source File
# End Group
# Begin Group "Templates"

# PROP Default_Filter ""
# Begin Group "Manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\utils\OR_ManagerList_Template.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_ManagerList_Template.inl
# End Source File
# Begin Source File

SOURCE=.\utils\OR_ManagerMap_Template.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_ManagerMap_Template.inl
# End Source File
# Begin Source File

SOURCE=.\utils\OR_PriorityManager_Template.h
# End Source File
# Begin Source File

SOURCE=.\utils\OR_PriorityManager_Template.inl
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
# Begin Group "Maths surface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\special_effects\OR_MathsSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_MathsSurface.h
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_MathsSurface_Def.cpp
# End Source File
# Begin Source File

SOURCE=.\special_effects\OR_MathsSurface_Def.h
# End Source File
# End Group
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

SOURCE=.\special_effects\OR_SpecialEffect.h
# End Source File
# End Group
# Begin Group "sound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sound\OR_SoundSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\OR_SoundSystem.h
# End Source File
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
# Begin Source File

SOURCE=.\shaders\OR_BumpShader_Emboss.cpp
# End Source File
# Begin Source File

SOURCE=.\shaders\OR_BumpShader_Emboss.h
# End Source File
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
# Begin Group "physic"

# PROP Default_Filter ""
# Begin Group "Physic handler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_PhysicHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_PhysicHandler.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_PhysicHandler.inl
# End Source File
# End Group
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
# Begin Source File

SOURCE=.\physic\OR_Force_ABC.h
# End Source File
# End Group
# Begin Group "Collision"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_Collision.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_Collision.h
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
# Begin Group "Deflector manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\physic\OR_DeflectorManager.cpp
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DeflectorManager.h
# End Source File
# Begin Source File

SOURCE=.\physic\OR_DeflectorManager.inl
# End Source File
# End Group
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
# Begin Source File

SOURCE=.\objects\OR_Light.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Light.h
# End Source File
# End Group
# Begin Group "Mesh"

# PROP Default_Filter ""
# Begin Group "Skinnable"

# PROP Default_Filter ""
# Begin Group "Skinlink"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_SkinLink.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_SkinLink.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_SkinLink.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\objects\OR_Skinnable.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Skinnable.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Skinnable.inl
# End Source File
# End Group
# Begin Group "MeshData"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\objects\OR_MeshData.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_MeshData.h
# End Source File
# Begin Source File

SOURCE=.\objects\OR_MeshData.inl
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
# Begin Source File

SOURCE=.\objects\OR_Object.cpp
# End Source File
# Begin Source File

SOURCE=.\objects\OR_Object.h
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
# Begin Group "Constant/Types/Global/Func/Macros"

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

SOURCE=.\misc\OR_GlobalVariables.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\OR_GlobalVariables.h
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
# Begin Group "Static link"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\OR_StaticLink.h
# End Source File
# End Group
# End Group
# Begin Group "maths"

# PROP Default_Filter ""
# Begin Group "Quaternion"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\maths\OR_Quaternion.cpp
# End Source File
# Begin Source File

SOURCE=.\maths\OR_Quaternion.h
# End Source File
# End Group
# Begin Group "Matrix"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\maths\OR_Matrix4x4.cpp
# End Source File
# Begin Source File

SOURCE=.\maths\OR_Matrix4x4.h
# End Source File
# Begin Source File

SOURCE=.\maths\OR_Matrix4x4.inl
# End Source File
# End Group
# Begin Group "Plane"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\maths\OR_Plane.cpp
# End Source File
# Begin Source File

SOURCE=.\maths\OR_Plane.h
# End Source File
# End Group
# Begin Group "Vector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\maths\OR_Vector.cpp
# End Source File
# Begin Source File

SOURCE=.\maths\OR_Vector.h
# End Source File
# End Group
# Begin Group "Functions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\maths\OR_MathFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\maths\OR_MathFunctions.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\maths\OR_Maths.cpp
# End Source File
# Begin Source File

SOURCE=.\maths\OR_Maths.h
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
# End Group
# Begin Group "documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\doxygen.cfg
# End Source File
# Begin Source File

SOURCE=.\documentation\MacroOrion3D.dsm
# End Source File
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

SOURCE=.\documentation\OR_Doc_ProgrammingNorms.dxt
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
# Begin Source File

SOURCE=.\animation\OR_Animation.cpp
# End Source File
# Begin Source File

SOURCE=.\animation\OR_Animation.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\orion3d.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\orion3d.h
# End Source File
# Begin Source File

SOURCE=.\Orion3D.inl
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
