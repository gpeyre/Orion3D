				/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_GizmoManager.cpp
 *  \brief Definition of class \c OR_GizmoManager
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_GizmoManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_GizmoManager.h"
#include "OR_CubeGizmo.h"
#include "OR_SphereGizmo.h"
#include "OR_PointGizmo.h"
#include "OR_VectorGizmo.h"
#include "OR_SquareGizmo.h"
#include "OR_CylinderGizmo.h"

#ifndef OR_USE_INLINE
	    #include "OR_GizmoManager.inl"
#endif

using namespace OR;


OR_I32 OR_GizmoManager::AddVectorGizmo(OR_Vector3D vZ, OR_Float dim)
{
	OR_VectorGizmo* new_gizmo=new OR_VectorGizmo(vZ, dim);
	return AddElement(new_gizmo);
}

OR_I32 OR_GizmoManager::AddPointGizmo()
{
	OR_PointGizmo* new_gizmo=new OR_PointGizmo();
	return AddElement(new_gizmo);
}

OR_I32 OR_GizmoManager::AddCubeGizmo(OR_Vector3D vX, OR_Vector3D vY,
									 OR_Vector3D vZ, OR_Vector3D dim)
{
	OR_CubeGizmo* new_gizmo=new OR_CubeGizmo(vX, vY, vZ, dim);
	return AddElement(new_gizmo);
}

OR_I32 OR_GizmoManager::AddSphereGizmo(OR_Vector3D vX, OR_Vector3D vY,
									   OR_Vector3D vZ, OR_Vector3D dim)
{
	OR_SphereGizmo* new_gizmo=new OR_SphereGizmo(vX, vY, vZ, dim);
	return AddElement(new_gizmo);
}

OR_I32 OR_GizmoManager::AddCylinderGizmo(OR_Vector3D vX, OR_Vector3D vY,
										 OR_Vector3D vZ, OR_Vector3D dim)
{
	OR_CylinderGizmo* new_gizmo=new OR_CylinderGizmo(vX, vY, vZ, dim);
	return AddElement(new_gizmo);
}

OR_I32 OR_GizmoManager::AddSquareGizmo(OR_Vector3D vX, OR_Vector3D vY,
									   OR_Vector3D vZ, OR_Vector3D dim)
{
	OR_SquareGizmo* new_gizmo=new OR_SquareGizmo(vX, vY, vZ, dim);
	return AddElement(new_gizmo);
}

OR_I32 OR_GizmoManager::AddGizmo(OR_Gizmo* new_gizmo)
{
	return AddElement(new_gizmo);
}

OR_I32 OR_GizmoManager::SetDim(OR_Vector3D dim)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetDim(dim);
	return OR_OK;
}

OR_I32 OR_GizmoManager::SetMetaIntensity(OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetMetaIntensity(val);
	return OR_OK;
}

OR_I32 OR_GizmoManager::SetInfluenceRadius(OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetInfluenceRadius(val);
	return OR_OK;
}

OR_I32 OR_GizmoManager::SetAxe(OR_Vector3D xaxe, OR_Vector3D yaxe, OR_Vector3D zaxe)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetAxe(xaxe, yaxe, zaxe);
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

