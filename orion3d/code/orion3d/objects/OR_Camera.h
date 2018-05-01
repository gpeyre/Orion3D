/*----------------------------------------------------------------------*/
/*                                  OR_Camera.h                         */
/*----------------------------------------------------------------------*/
/*                       definition de la classe OR_Camera              */            
/*----------------------------------------------------------------------*/

/** \file 
	Contains the definition of all camera class. The are two basic kind of camera,
	which both inherit from the OR_Camera class :
		- OR_Camera_Free : a a camera given by its position and a vector.
		- OR_Camera_Target : a camera given by its position and a target.

	This file also contains the definition of a camera manager, used to store multiple 
	cameras.
	\author Gabriel.
**/

#ifndef _OR_CAMERA_H_
#define _OR_CAMERA_H_

#include "../configuration/OR_Config.h"
#include "OR_Object.h"
#include "OR_ObjectManager.h"
#include "../maths/OR_Maths.h"

namespace OR
{

/*----------------------------------------------------------------------*/
/*                               class OR_Camera                        */
/*----------------------------------------------------------------------*/
/* super class for all Camera class                                     */           
/*----------------------------------------------------------------------*/
/* inherit from class OR_Object                                         */        
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_Camera in group group_object
 */

/// super class for all Camera class.
/** 
	inherit from class OR_Object.
	\author Gabriel
*/

class ORION3D_API OR_Camera:	public OR_Object
{

	friend class OR_Portal_Renderer;

protected:

	/** the distance to the near clip plane */
	OR_Float Near;
	/** the distance to the far clip plane */
	OR_Float Far;
	/** the lens fov */
	OR_Float Fovy;
	/** aspect=width/height */
	OR_Float Aspect;
	/** orthographic camera */
	OR_Bool IsOrtho;

public:

	/** constructor */
	OR_Camera();

	/** overload virtual function from OR_Object */
	virtual OR_Elements GetType()		
	{ return OR_CAMERA; }

	/** get an axe of the camera */
	OR_Vector3D GetCamAxe(OR_Coord_XYZW axe);

	/** to set the fovy */
	void SetFovy(OR_Float val);
	/** to set the far value */
	void SetFar(OR_Float val);
	/** to set the aspect value */
	void SetAspect(OR_Float aspect);
	/** to set the near clip plane */
	void SetNear(OR_Float val);
	/** to set if it is orthographic */
	void SetOrtho(OR_Bool ortho);
	/** to get the fovy */
	OR_Float GetFovy();
	/** to get the near clip plane */
	OR_Float GetNear();
	/** to get the far clip plane */
	OR_Float GetFar();
	/** to set the aspect value */
	OR_Float GetAspect();
	/** to Get if it is orthographic */
	OR_Bool GetOrtho();
	
	/** initialize the OpenGL projection matrix */
	void SetProjectionMatrix();

	/** initialize the model view matrix before drawing the objects */
	void Put();

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
};

/*----------------------------------------------------------------------*/
/*                   class OR_Camera_Free                               */
/*----------------------------------------------------------------------*/
/* a camera given by its position and a vector                          */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Camera                                         */
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_Camera_Free in group group_object
 */

/// a camera given by its position and a vector.
/** 
	inherit from class OR_Camera.
	\author Gabriel
*/

class ORION3D_API OR_Camera_Free: public OR_Camera
{
public:
	/** constructor */
	OR_Camera_Free();

	/** rotate the camera on one of its own axes */
	void Rotate(OR_Coord_XYZW axe, OR_Float angle);
	void Rotate(OR_Float angle) {}
	/** rotate the camera on one of the world's axes */
	void RotateWorld(OR_Coord_XYZW axe, OR_Float angle);
	/** translate the camera on one of its own axes given a component */
	void Translate(OR_Coord_XYZW axe, OR_Float val);
	/** translate the camera on one of its own axes given a vector */
	void Translate(OR_Vector3D vect);
	/** translate the camera on one of the world axes given a component */
	void TranslateWorld(OR_Coord_XYZW axe, OR_Float val);
	/** translate the camera on one of the world axes given a vector */
	void TranslateWorld(OR_Vector3D vect);

	/** return the type of the camera */
	virtual OR_Elements GetType()	
	{ return OR_CAMERA_Free; }

	/** draw a symbolic camera */
	virtual void Draw();

	//-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	OR_DEFINE_SERIALIZATION(OR_Camera_Free);
    //@}

};

/*----------------------------------------------------------------------*/
/*                   class OR_Camera_Target                             */
/*----------------------------------------------------------------------*/
/* a camera given by its position and a target                          */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Camera                                         */
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_Camera_Target in group group_object
 */

/// a camera given by its position and a vector.
/** 
	inherit from class OR_Camera.
	\author Gabriel
*/

class ORION3D_API OR_Camera_Target: public OR_Camera
{
private:
	/** the roll of the camera */
	OR_Float Roll;
	OR_Float OldRoll;
	/** minimal distance camera->object */
	OR_Float DistanceMin;

	OR_Bool RecomputeBasis;
public:
	/** constructor */
	OR_Camera_Target();

	/** overload because must re-compute the matrix */
	void Posit(OR_Vector3D pos);

	/** set the minimum distance to the target  */
	void SetDistanceMin(OR_Float val);

	/** set the roll */
	void SetRool(OR_Float r)
	{ Roll=r; Matrix.RotateZ(Roll);}
	/** get the roll */
	OR_Float GetRoll()
	{ return Roll; }

	/** rotate the camera on the axis camera->target, ie. Z axis */
	void Rotate(OR_Coord_XYZW axe, OR_Float angle);
	void Rotate(OR_Float angle) { }
	/** translate the camera on one of its own axes given a component */
	void Translate(OR_Coord_XYZW axe, OR_Float val);
	/** translate the camera on one of its own axes given a vector */
	void Translate(OR_Vector3D vect);
	/** translate the camera on one of the world axes given a component */
	void TranslateWorld(OR_Coord_XYZW axe, OR_Float val);
	/** translate the camera on one of the world axes given a vector */
	void TranslateWorld(OR_Vector3D vect);

	/** return the type of the camera */
	virtual OR_Elements GetType()	
	{ return OR_CAMERA_Target; }

	/** overload bc must use the target to compute the matrix */
	virtual void Update();
	/** draw a symbolic camera */
	virtual void Draw();

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	//-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	OR_DEFINE_SERIALIZATION(OR_Camera_Target);
    //@}
};


/*----------------------------------------------------------------------*/
/*                      classe OR_CameraManager	                        */
/*----------------------------------------------------------------------*/
/* to store the differents cameras                                      */            
/*----------------------------------------------------------------------*/
/*	inherit from class OR_ManagerMap_Template_Object                    */
/*----------------------------------------------------------------------*/

/*! \ingroup group_manager 
 *  \brief class OR_CameraManager in group group_manager
 */

/// The manager of cameras.
/** 
	Contains a copy of every camera in the hirarchy.
	This alow to have an easy acces to each camera.
	@author Gabriel
*/
/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
#pragma warning( disable : 4660 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_Manager_Template_Object<OR_Camera>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_SmartManagerMap_Template<OR_Camera>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Camera>;

class ORION3D_API OR_CameraManager: public OR_Manager_Template_Object<OR_Camera>
{
	
public:

	/** constructor */ 
	OR_CameraManager() 
	:OR_Manager_Template_Object<OR_Camera>() 
	{ ActiveCamera=NULL; } 
	
	/** add a new free camera */
	OR_I32 AddFreeCamera();
	/** add a new target camera */
	OR_I32 AddTargetCamera();
	
	/** set the position */
	OR_I32 Posit(OR_Vector3D pos);
	/** rotate the camera on one of its own axes : for free and satellite, and target (if axe=Z) */
	OR_I32 Rotate(OR_Coord_XYZW axe, OR_Float angle);
	/** rotate the camera on one of the world's axes  : for free */
	OR_I32 RotateWorld(OR_Coord_XYZW axe, OR_Float angle);
	/** translate the camera on one of its own axes given a component  : for free and satellite */
	OR_I32 Translate(OR_Coord_XYZW axe, OR_Float val);
	/** translate the camera on one of its own axes given a vector  : for free and satellite */
	OR_I32 Translate(OR_Vector3D vect);
	/** translate the camera on one of the world axes given a component  : for free and satellite */
	OR_I32 TranslateWorld(OR_Coord_XYZW axe, OR_Float val);
	/** translate the camera on one of the world axes given a vector  : for free and satellite */
	OR_I32 TranslateWorld(OR_Vector3D vect);

	/** set the active camera */ 
	void SetActiveCamera(OR_Camera* cam) 
	{ ActiveCamera=cam; } 
	/** get the active camera */ 
	OR_Camera* GetActiveCamera() 
	{ return ActiveCamera; } 


	/** set the target : for target and satellite */
	OR_I32 SetTarget(OR_Object* target);
	/** set the minimum distance to the target : for satellite  */
	OR_I32 SetDistanceMin(OR_Float val);

	/** get an axe of the camera */
	OR_Vector3D GetPosition();
	/** overload virtual function from OR_Object */
	OR_Vector3D GetCamAxe(OR_Coord_XYZW axe);

	/** to set the fovy */
	OR_I32 SetFovy(OR_Float val);
	/** to set the far clip plane */
	OR_I32 SetFar(OR_Float val);
	/** to set the near clip plane */
	OR_I32 SetNear(OR_Float val);
	/** to get the fovy */
	OR_Float GetFovy();
	/** to get the near clip plane */
	OR_Float GetNear();
	/** to get the far clip plane */
	OR_Float GetFar();
	/** to get the aspect value */
	OR_Float GetAspect();

	/* enable/disable methods ************************************/
	/** OR_Object method */
    virtual OR_I32 Enable();
	/** OR_Object method */
    virtual OR_I32 Disable();
	/** OR_Object method */
    virtual OR_Bool Toggle();

	/** initialize the model view matrix before drawing the objects */
	OR_I32 PutSelectedCamera();

private:
	/** the camera that is used by the current rendering process */ 
	OR_Camera* ActiveCamera;

};

#pragma warning( default : 4275 )  


} // namespace OR
	
#endif /* _OR_CAMERA_H_ */



///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////