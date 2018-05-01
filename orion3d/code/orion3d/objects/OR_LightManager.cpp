/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_LightManager.cpp
 *  \brief Definition of class \c OR_LightManager
 *  \author Gabriel Peyré 2001-09-25
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_LightManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_LightManager.h"

#ifndef OR_USE_INLINE
	    #include "OR_LightManager.inl"
#endif

using namespace OR;


OR_LightIDManager OR_LightManager::LightIDStack_;

OR_LightManager::OR_LightManager()
:	OR_Manager_Template_Object<OR_Light>()
{
	/* set the global ambient light */
	GlobalAmbient[R]=0;
	GlobalAmbient[V]=0;
	GlobalAmbient[B]=0;
	GlobalAmbient[A]=1;
	AssignGlobalAmbient();
}

OR_LightManager::~OR_LightManager()
{
	/* NOTHING */
}

void OR_LightManager::AssignGlobalAmbient()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalAmbient);
}

/* creation methods ******************************************/
OR_I32 OR_LightManager::AddFreeSpotLight()
{
	/* create a new light */
	OR_Light_FreeSpot* new_light=new OR_Light_FreeSpot();
	
	/* add the light to the manager */
	return this->AddElement(new_light);
}

OR_I32 OR_LightManager::AddTargetSpotLight()
{
	/* create a new light */
	OR_Light_TargetSpot* new_light=new OR_Light_TargetSpot();
	/* add the light to the manager */
	return this->AddElement(new_light);
}

OR_I32 OR_LightManager::AddFreeDirectLight()
{
	/* create a new light */
	OR_Light_FreeDirect* new_light=new OR_Light_FreeDirect();
	/* add the light to the manager */
	return this->AddElement(new_light);
}

OR_I32 OR_LightManager::AddTargetDirectLight()
{
	/* create a new light */
	OR_Light_TargetDirect* new_light=new OR_Light_TargetDirect();
	/* add the light to the manager */
	return this->AddElement(new_light);
}

OR_I32 OR_LightManager::AddLight(OR_Light* NewLight)
{
	/* add the light to the manager */
	return this->AddElement(NewLight);
}

OR_RETURN_CODE OR_LightManager::RemoveElement(OR_Light* element)
{
	//Remove the element
	if (OR_Manager_Template_Object<OR_Light>::RemoveElement(element)!=OR_OK) return OR_ERROR;
	//Switch off the light
	element->Disable();

	return OR_OK;
}

/* color modifications methods *******************************/
OR_I32 OR_LightManager::SetAmbient(OR_Float val[4])
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetAmbient(val);
	return OR_OK;
}

OR_I32 OR_LightManager::SetSpecular(OR_Float val[4])
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetSpecular(val);
	return OR_OK;
}

OR_I32 OR_LightManager::SetDiffuse(OR_Float val[3])
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetDiffuse(val);
	return OR_OK;
}

OR_I32 OR_LightManager::SetAmbient(OR_Coord_RVBA c, OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetAmbient(c, val);
	return OR_OK;
}

OR_I32 OR_LightManager::SetSpecular(OR_Coord_RVBA c, OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetSpecular(c, val);
	return OR_OK;
}

OR_I32 OR_LightManager::SetDiffuse(OR_Coord_RVBA c, OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetDiffuse(c, val);
	return OR_OK;
}

void OR_LightManager::SetGlobalAmbient(OR_Float val[4])
{
	GlobalAmbient[R]=val[R];
	GlobalAmbient[V]=val[V];
	GlobalAmbient[B]=val[B];
	GlobalAmbient[A]=val[A];
	AssignGlobalAmbient();
}

void OR_LightManager::SetGlobalAmbient(OR_Coord_RVBA c, OR_Float val)
{
	GlobalAmbient[c]=val;
	AssignGlobalAmbient();
}

/* change the value of a parameter ***************************/
OR_I32 OR_LightManager::SetCutOff(OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	if ( (GetElementSelected()->GetType()!=OR_LIGHT_Free_Spot) &&
		 (GetElementSelected()->GetType()!=OR_LIGHT_Target_Spot) )
		 return OR_Manager_InvalidSelectedType;
	((OR_Light_Spot*) GetElementSelected())->SetCutOff(val);
	return OR_OK;
}

OR_I32 OR_LightManager::SetExponent(OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	if ( (GetElementSelected()->GetType()!=OR_LIGHT_Free_Spot) &&
		 (GetElementSelected()->GetType()!=OR_LIGHT_Target_Spot) )
		 return OR_Manager_InvalidSelectedType;
	((OR_Light_Spot*) GetElementSelected())->SetExponent(val);
	return OR_OK;
}

OR_I32 OR_LightManager::SetAtenuation(OR_Float val[3])
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	if ( (GetElementSelected()->GetType()!=OR_LIGHT_Free_Spot) &&
		 (GetElementSelected()->GetType()!=OR_LIGHT_Target_Spot) )
		 return OR_Manager_InvalidSelectedType;
	((OR_Light_Spot*) GetElementSelected())->SetAtenuation(val);
	return OR_OK;
}

OR_I32 OR_LightManager::SetTarget(OR_Gizmo* target)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	if ( (GetElementSelected()->GetType()!=OR_LIGHT_Target_Direct) &&
		 (GetElementSelected()->GetType()!=OR_LIGHT_Target_Spot) )
		 return OR_Manager_InvalidSelectedType;
	if (GetElementSelected()->GetType()==OR_LIGHT_Target_Direct)
		((OR_Light_TargetDirect*) GetElementSelected())->SetTarget(target);
	if (GetElementSelected()->GetType()==OR_LIGHT_Target_Spot)
		((OR_Light_TargetSpot*) GetElementSelected())->SetTarget(target);
	return OR_OK;
}

/* set the opengl position of all lights *********************/
void OR_LightManager::PutAllLights()
{
	for(IT_ManagerMap_Template(OR_Light) it=begin(); it!=end(); ++it)
		(*it).second->Put();
}

/* set the opengl properties of all lights *********************/
void OR_LightManager::SetAllProperties()
{
	//Set the opengl properties of the active lights
	for(IT_ManagerMap_Template(OR_Light) it=begin(); it!=end(); ++it)
		(*it).second->SetProperties();

	//disable the other lights (that were not created)
	/** \todo fill this */
}

/* change the position of the light **************************/
OR_I32 OR_LightManager::SetDirection(OR_Vector3D v)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	if ( (GetElementSelected()->GetType()!=OR_LIGHT_Free_Direct) &&
		 (GetElementSelected()->GetType()!=OR_LIGHT_Free_Spot) )
		 return OR_Manager_InvalidSelectedType;
	if (GetElementSelected()->GetType()==OR_LIGHT_Free_Direct)
		((OR_Light_FreeDirect*) GetElementSelected())->SetDirection(v);
	if (GetElementSelected()->GetType()==OR_LIGHT_Free_Spot)
		((OR_Light_FreeSpot*) GetElementSelected())->SetDirection(v);
	return OR_OK;
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

