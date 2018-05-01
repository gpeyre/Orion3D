
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_LightManager.h
 *  \brief Definition of class \c OR_LightManager
 *  \author Gabriel Peyré 2001-09-25
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_LightManager_h_
#define __OR_LightManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Light.h"
#include "OR_LightIDManager.h"
#include "OR_ObjectManager.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_LightManager
 *  \brief  a manager of lights
 *  \author Gabriel Peyré 2001-09-25
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_Manager_Template_Object<OR_Light>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_SmartManagerMap_Template<OR_Light>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Light>;

class ORION3D_API OR_LightManager: public OR_Manager_Template_Object<OR_Light>
{
	
public:
	
    //-------------------------------------------------------------------------
    /** \name constructor/destructor */
    //-------------------------------------------------------------------------
    //@{
	/** constructor : initialize a pile of free light */
	OR_LightManager();
	/** destructor : delete the pile */
	~OR_LightManager();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name creation methods */
    //-------------------------------------------------------------------------
    //@{
	/** create a new free spot light */
	OR_I32 AddFreeSpotLight();
	/** create a new target spot light */
	OR_I32 AddTargetSpotLight();
	/** create a new free direct light */
	OR_I32 AddFreeDirectLight();
	/** create a new target direct light */
	OR_I32 AddTargetDirectLight();
	/** add a light (must be used instead of AddElement()) */
	OR_I32 AddLight(OR_Light* NewLight);
	/** Remove an element (not delete) */
	virtual OR_RETURN_CODE RemoveElement(OR_Light* element);
    //@}
	
	//-------------------------------------------------------------------------
    /** \name Ligt ID manipulations */
    //-------------------------------------------------------------------------
    //@{
	static OR_U32 GetNewID();
	static void   ReleaseID(OR_U32 nID);
	static OR_LightIDManager& GetLightIDStack();
    //@}

    //-------------------------------------------------------------------------
    /** \name color modification methods */
    //-------------------------------------------------------------------------
    //@{
	/** set the ambient component of the light */
	OR_I32 SetAmbient(OR_Float val[4]);
	/** set the specular component of the light */
	OR_I32 SetSpecular(OR_Float val[4]);
	/** set the diffuse component of the light */
	OR_I32 SetDiffuse(OR_Float val[3]);
	/** set the ambient component of the light */
	OR_I32 SetAmbient(OR_Coord_RVBA c, OR_Float val);
	/** set the specular component of the light */
	OR_I32 SetSpecular(OR_Coord_RVBA c, OR_Float val);
	/** set the diffuse component of the light */
	OR_I32 SetDiffuse(OR_Coord_RVBA c, OR_Float val);
	/** set global ambient light color */
	void SetGlobalAmbient(OR_Float val[4]);
	/** set global ambient light color */
	void SetGlobalAmbient(OR_Coord_RVBA c, OR_Float val);
    //@}
	
    //-------------------------------------------------------------------------
    /** \name modifiers */
    //-------------------------------------------------------------------------
    //@{
	/** set the cutoff value : for spot light only */
	OR_I32 SetCutOff(OR_Float val);
	/** set the exponent value : for spot light only */
	OR_I32 SetExponent(OR_Float val);
	/** set the atenuation value : for spot light only */
	OR_I32 SetAtenuation(OR_Float val[3]);
	/** set the target : for target light only */
	OR_I32 SetTarget(OR_Gizmo* target);	
	/** set the direction of the light, ie. Z axis */
	OR_I32 SetDirection(OR_Vector3D v);
    //@}

    //-------------------------------------------------------------------------
    /** \name opengl states modifications */
    //-------------------------------------------------------------------------
    //@{
	/** posit all light in the scene */
	void PutAllLights();
	/** set the light properties of the light to opengl */
	void SetAllProperties();
    //@}
	
private:
	
	/** global ambient light color */
	OR_Float GlobalAmbient[4];
	/** a stack of free light numbers */
	static OR_LightIDManager LightIDStack_;
	
	/** assign global ambient light to OpenGL */
	void AssignGlobalAmbient();

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_LightManager.inl"
#endif


#endif // __OR_LightManager_h_

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

