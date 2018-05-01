
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_GizmoManager.h
 *  \brief Definition of class \c OR_GizmoManager
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_GizmoManager_h_
#define __OR_GizmoManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Gizmo.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_GizmoManager
 *  \brief  a manager of gizmo
 *  \author Gabriel Peyré 2001-12-12
 *  
 *	Contains a copy of every gizmos in the hirarchy.
 *	This alow to have an easy acces to each gizmos.
 */ 
/*------------------------------------------------------------------------------*/
	
#pragma warning( disable : 4275 ) 

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_Manager_Template_Object<OR_Gizmo>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_SmartManagerMap_Template<OR_Gizmo>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Gizmo>;

class ORION3D_API OR_GizmoManager: public OR_Manager_Template_Object<OR_Gizmo>
{

public:

	/* create a gizmo given its attributes **********/
	/** create a vector gizmo  */
	OR_I32 AddVectorGizmo(OR_Vector3D vZ=OR_Vector3D(0,0,1), OR_Float dim=1);
	/** create a point gizmo */
	OR_I32 AddPointGizmo();
	/** create a cubic gizmo from a file */
	OR_I32 AddCubeGizmo(OR_Vector3D vX=OR_Vector3D(1,0,0),
		OR_Vector3D vY=OR_Vector3D(0,1,0),
		OR_Vector3D vZ=OR_Vector3D(0,0,1), 
		OR_Vector3D dim=OR_Vector3D(1,1,1));
	/** create a spheric gizmo from a file */
	OR_I32 AddSphereGizmo(OR_Vector3D vX=OR_Vector3D(1,0,0),
		OR_Vector3D vY=OR_Vector3D(0,1,0),
		OR_Vector3D vZ=OR_Vector3D(0,0,1), 
		OR_Vector3D dim=OR_Vector3D(1,1,1));
	/** create a cylindric gizmo from a file */
	OR_I32 AddCylinderGizmo(OR_Vector3D vX=OR_Vector3D(1,0,0),
		OR_Vector3D vY=OR_Vector3D(0,1,0),
		OR_Vector3D vZ=OR_Vector3D(0,0,1), 
		OR_Vector3D dim=OR_Vector3D(1,1,1));
	/** create a square gizmo from a file */
	OR_I32 AddSquareGizmo(OR_Vector3D vX=OR_Vector3D(1,0,0),
		OR_Vector3D vY=OR_Vector3D(0,1,0),
		OR_Vector3D vZ=OR_Vector3D(0,0,1), 
		OR_Vector3D dim=OR_Vector3D(1,1,1));
	/* duplicate gizmo **********************************/
	/** create a cubic gizmo from a file */
	OR_I32 AddGizmo(OR_Gizmo* gizmo);
	
	/** set the dimensions of the gizmo */
	OR_I32 SetDim(OR_Vector3D dim);
	/** set the axes of the gizmo */
	OR_I32 SetAxe(OR_Vector3D xaxe, OR_Vector3D yaxe, OR_Vector3D zaxe);
	
	/** set the intensity of the selected gizmo */
	OR_I32 SetMetaIntensity(OR_Float val);
	/** set the influence radius of the selected gizmo */
	OR_I32 SetInfluenceRadius(OR_Float val);
};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_GizmoManager.inl"
#endif


#endif // __OR_GizmoManager_h_

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

