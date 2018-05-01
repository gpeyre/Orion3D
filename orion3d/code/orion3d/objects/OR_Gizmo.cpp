/*-------------------------------------------------------------*/
/*                      OR_Gizmo.cpp                          */
/*-------------------------------------------------------------*/
/* implementation of invisible objects (gizmos, deflector ...) */
/*-------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Gizmo.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Gizmo.h"
#include "OR_GizmoManager.h"

#ifndef OR_USE_INLINE
#   include "OR_Gizmo.inl"
#endif

using namespace OR;
	
/*---------------------------------------------------------*/
/*                         class OR_Gizmo                  */
/*---------------------------------------------------------*/
/* super class for all gizmo                               */
/*---------------------------------------------------------*/

OR_Gizmo::OR_Gizmo(OR_Vector3D vX,
			 OR_Vector3D vY,
			 OR_Vector3D vZ, 
			 OR_Vector3D dim)
:	OR_Object(), 
	OR_MetaObject_ABC()
{
	Matrix.SetX(!(vX));
	Matrix.SetY(!(vY));
	Matrix.SetZ(!(vZ));

	Dim=dim;

	/* set default parameters */
	rInfluenceRadius_=2*dim[X];
	this->AutoSetMetaIntensity();
}

void OR_Gizmo::SetDim(OR_Vector3D dim)
{
	Dim=dim;
}

OR_Vector3D& OR_Gizmo::GetDim()
{
	return Dim;
}

void OR_Gizmo::SetAxe(OR_Vector3D vX, OR_Vector3D vY, OR_Vector3D vZ)
{
	Matrix.SetX(!(vX));
	Matrix.SetY(!(vY));
	Matrix.SetZ(!(vZ));
}

OR_Bool OR_Gizmo::IsInside(OR_Vector3D pos)
{
	return false;
}

OR_Bool OR_Gizmo::FrustrumClip()
{
	return false;
}

void OR_Gizmo::SetMetaIntensity(OR_Float intensity)
{
	rMetaIntensity_ = intensity;
}

void OR_Gizmo::AutoSetMetaIntensity()
{
	if( rInfluenceRadius_-Dim[X] <OR_EPSILON )
	{
		/* ensure that the influence radius is suffisant */
		rInfluenceRadius_ = 2*Dim[X];
	}

	rMetaIntensity_ = 1/pMetaFunc_( Dim[X]/rInfluenceRadius_ );
}

OR_Float OR_Gizmo::GetMetaIntensity()
{
	return rMetaIntensity_;
}

void OR_Gizmo::SetInfluenceRadius(OR_Float radius)
{
	rInfluenceRadius_=radius;
}

OR_Float OR_Gizmo::GetInfluenceRadius()
{
	return rInfluenceRadius_;
}


/* serialization methods ***************************************/
void OR_Gizmo::BuildFromFile( OR_File& file )
{
	/* load the basic OR_Object datas */
	OR_Object::BuildFromFile(file);
	/* load the gizmo specific datas */
	file >> Dim
		 >> rMetaIntensity_
		 >> rInfluenceRadius_;

	/* add itself to the manager */
	OR_Globals::GizmoManager()->AddElement( this );
}

void OR_Gizmo::BuildToFile( OR_File& file )
{
	/* save the basic OR_Object datas */
	OR_Object::BuildToFile(file);
	/* save the gizmo specific datas */
	file << Dim
		 << rMetaIntensity_
		 << rInfluenceRadius_; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Gizmo::DeflectParticuleManager
 *
 *  \param  particuleManager the manager to deflect.
 *  \author Gabriel Peyré 2001-09-04
 *
 *	Deflect each particule of a particule manager.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Gizmo::DeflectParticuleManager( OR_ParticuleManager& particuleManager )
{
	T_ParticuleList& ParticuleList = particuleManager.GetParticuleList();
	for( IT_ParticuleList it=ParticuleList.begin(); it!=ParticuleList.end(); ++it )
		this->DeflectParticule( *(*it) );
}

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////
