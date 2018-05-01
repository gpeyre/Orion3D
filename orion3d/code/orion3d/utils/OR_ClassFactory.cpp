/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ClassFactory.cpp
 *  \brief Implementation of class OR_ClassFactory
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ClassFactory.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ClassFactory.h"


#include "../animation/OR_Animation.h"
#include "../animation/OR_AnimationManager.h"
#include "../animation/OR_AnimationNode.h"
#include "../animation/OR_AnimationTrack.h"
#include "../animation/OR_KeyFrame.h"
#include "../shaders/OR_Shader.h"
#include "../shaders/OR_BumpShader_Emboss.h"
#include "../shaders/OR_Texture.h"
#include "../shaders/OR_ShaderManager.h"
#include "../shaders/OR_MultiShader.h"
#include "../utils/OR_String.h"
#include "../objects/OR_Bone.h"
#include "../objects/OR_Camera.h"
#include "../objects/OR_Gizmo.h"
#include "../objects/OR_CubeGizmo.h"
#include "../objects/OR_SphereGizmo.h"
#include "../objects/OR_PointGizmo.h"
#include "../objects/OR_VectorGizmo.h"
#include "../objects/OR_SquareGizmo.h"
#include "../objects/OR_CylinderGizmo.h"
#include "../objects/OR_Light.h"
#include "../objects/OR_Mesh.h"
#include "../objects/OR_Skin.h"
#include "../objects/OR_MathSurface.h"
#include "../hierarchy/OR_Node.h"
#include "../hierarchy/OR_HierarchyTree.h"
#include "../physic/OR_ConstantForce.h"
#include "../physic/OR_ConstraintManager.h"
#include "../physic/OR_DampedSpringConstraint.h"
#include "../physic/OR_DampingForce.h"
#include "../physic/OR_ForceManager.h"
#include "../physic/OR_GravityForce.h"
#include "../physic/OR_MagneticForce.h"
#include "../physic/OR_MaximumDistanceConstraint.h"
#include "../physic/OR_MinimumDistanceConstraint.h"
#include "../physic/OR_PushSpringConstraint.h"
#include "../physic/OR_SpringConstraint.h"
#include "../special_effects/OR_Cloth.h"
#include "../special_effects/OR_Fog.h"
#include "../special_effects/OR_LensFlare.h"
#include "../special_effects/OR_MetaEnv.h"
#include "../special_effects/OR_ParticuleSystem.h"
#include "../special_effects/OR_SpecialEffectManager.h"



using namespace OR;

T_ClassFactoryMap OR_ClassFactory::Map_;

/*------------------------------------------------------------------------------*/
// Name : OR_ClassFactory::CreateInstance
/** 
 *  \param  ClassName Name of the class we want to create an instance.
 *  \return An instance of class whose name is ClassName.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Throws an exception if the class could not been created.
 */ 
/*------------------------------------------------------------------------------*/
OR_Serializable& OR_ClassFactory::CreateInstance(OR_String& ClassName)
{
	IT_ClassFactoryMap it = Map_.find(ClassName);
	if( it==Map_.end() )
		throw(new OR_MsgException(OR_String("Class named ") + ClassName + OR_String(" does not exist."), 
								  OR_String("OR_ClassFactory::CreateInstance")) );
	return (*it).second();
}



/*------------------------------------------------------------------------------*/
// Name : OR_ClassFactory::BuildFromFile
/** 
 *  \param  file The file from which build the object.
 *  \return The object that have been created.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Create an object serialized into a file. Doesn't need to know the type of the object.
 */ 
/*------------------------------------------------------------------------------*/
OR_Serializable& OR_ClassFactory::BuildFromFile(OR_File& file)
{
	/* get the name of the class */
	OR_String ClassName;
	file >> ClassName;
	/* create an instance of the class */
	OR_Serializable& obj = OR_ClassFactory::CreateInstance( ClassName );
	/* build the object from the file */
	file >> obj;
	return obj;
}



/*------------------------------------------------------------------------------*/
// Name : OR_ClassFactory::BuildToFile
/** 
 *  \param  file The file to which build the object.
 *  \param  obj The object we want to export.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export an object to a file, so that it can be retrived without knowing it's type.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ClassFactory::BuildToFile(OR_File& file, OR_Serializable& obj)
{
	/* export the name of the class */
	OR_String& ClassName = obj.GetClassName();
	file << ClassName;
	/* export the object */
	file << obj;
}




/*------------------------------------------------------------------------------*/
// Name : OR_ClassFactory::RegisterClass
/** 
 *  \param  ClassName Name of the class to register
 *  \param  CreateInstanceFunc The class duplication method.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Create an entry in the map for the class, so that it can be instanciate using CreateInstance
 */ 
/*------------------------------------------------------------------------------*/
void OR_ClassFactory::RegisterClass(OR_String ClassName, T_CreateInstance_Function CreateInstanceFunc)
{
	Map_[ClassName] = CreateInstanceFunc;
}


/*------------------------------------------------------------------------------*/
// Name : OR_ClassFactory::RegisterAllClass
/** 
 *  \author Gabriel Peyré 2001-08-05
 *
 *  This is where OR_Serializable class are registred for serialization.
 *	So newly coded serialiable class should be registred here.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ClassFactory::RegisterAllClass()
{
	OR_REGISTER_CLASS(OR_Animation);
	OR_REGISTER_CLASS(OR_AnimationManager);
	OR_REGISTER_CLASS(OR_AnimationNode);
	OR_REGISTER_CLASS(OR_AnimationTrack_Linear_Float);
	OR_REGISTER_CLASS(OR_AnimationTrack_Linear_Vector);
	OR_REGISTER_CLASS(OR_AnimationTrack_Smooth_Quaternion);
	OR_REGISTER_CLASS(OR_AnimationTrack_Smooth_Quaternion);
	OR_REGISTER_CLASS(OR_AnimationTrack_Bezier_Float);
	OR_REGISTER_CLASS(OR_AnimationTrack_Bezier_Vector);
	OR_REGISTER_CLASS(OR_AnimationTrack_TCB_Float);
	OR_REGISTER_CLASS(OR_AnimationTrack_TCB_Vector);
	OR_REGISTER_CLASS(OR_AnimationTrack_Constant_Float);
	OR_REGISTER_CLASS(OR_AnimationTrack_Constant_Vector);
	OR_REGISTER_CLASS(OR_AnimationTrack_Constant_Quaternion);
	OR_REGISTER_CLASS(OR_AnimationTrack_Constant_Bool);
	OR_REGISTER_CLASS(OR_HierarchyTree);
	OR_REGISTER_CLASS(OR_Node);
	OR_REGISTER_CLASS(OR_ShaderManager);
	OR_REGISTER_CLASS(OR_Texture);
	OR_REGISTER_CLASS(OR_String);
	OR_REGISTER_CLASS(OR_Bone);
	OR_REGISTER_CLASS(OR_Camera_Free);
	OR_REGISTER_CLASS(OR_Camera_Target);
	OR_REGISTER_CLASS(OR_VectorGizmo);
	OR_REGISTER_CLASS(OR_PointGizmo);
	OR_REGISTER_CLASS(OR_CubeGizmo);
	OR_REGISTER_CLASS(OR_SphereGizmo);
	OR_REGISTER_CLASS(OR_CylinderGizmo);
	OR_REGISTER_CLASS(OR_SquareGizmo);
	OR_REGISTER_CLASS(OR_Light_FreeSpot);
	OR_REGISTER_CLASS(OR_Light_TargetSpot);
	OR_REGISTER_CLASS(OR_Light_FreeDirect);
	OR_REGISTER_CLASS(OR_Light_TargetDirect);
	OR_REGISTER_CLASS(OR_Mesh);
	OR_REGISTER_CLASS(OR_Skin);
	OR_REGISTER_CLASS(OR_BumpShader_Emboss);
	OR_REGISTER_CLASS(OR_FlatShader);
	OR_REGISTER_CLASS(OR_SingleTextureMapShader);
	OR_REGISTER_CLASS(OR_ReflexiveMapShader);
	OR_REGISTER_CLASS(OR_CartoonShader);
	OR_REGISTER_CLASS(OR_BillboardShader);
	OR_REGISTER_CLASS(OR_LensFlare_Infinite);
	OR_REGISTER_CLASS(OR_LensFlare_Local);
	OR_REGISTER_CLASS(OR_HierarchyTree);
	OR_REGISTER_CLASS(OR_ConstantForce);
	OR_REGISTER_CLASS(OR_DampingForce);
	OR_REGISTER_CLASS(OR_ForceManager);
	OR_REGISTER_CLASS(OR_GravityForce);
	OR_REGISTER_CLASS(OR_MagneticForce);
	OR_REGISTER_CLASS(OR_Cloth);
	OR_REGISTER_CLASS(OR_Fog);
	OR_REGISTER_CLASS(OR_MetaEnv);
	OR_REGISTER_CLASS(OR_ParticuleSystem);
	OR_REGISTER_CLASS(OR_SpecialEffectManager);
	OR_REGISTER_CLASS(OR_LensFlare_Infinite);
	OR_REGISTER_CLASS(OR_LensFlare_Local);
	OR_REGISTER_CLASS(OR_MathSurface);
	OR_REGISTER_CLASS(OR_MultiShader);
	OR_REGISTER_CLASS(OR_Particule);
	OR_REGISTER_CLASS(OR_SpringConstraint);
	OR_REGISTER_CLASS(OR_MinimumDistanceConstraint);
	OR_REGISTER_CLASS(OR_MaximumDistanceConstraint);
	OR_REGISTER_CLASS(OR_MultishaderToken);

}




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

