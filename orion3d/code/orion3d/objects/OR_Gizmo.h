/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_GizmoManager.h
 *  \brief Definition of class \c OR_GizmoManager
 *  \author Gabriel Peyré 2001-12-12
 *	
 *	Contains the definition of gizmos, wich are invisible objects used for
 *	a lot of things :
 *		- helpers in hierarchy animation.
 *		- to clip sub-tree when a part of the hierarchy is out of the field of view.
 *		- to represent meta-objects.
 *		- to represent meta-environnement [cube gizmo only].
 *		- to deflect points [particules ...] or objects [typicaly other gizmos].
 */ 
/*------------------------------------------------------------------------------*/


#ifndef _OR_GIZMO_H_
#define _OR_GIZMO_H_

#include "../configuration/OR_Config.h"
#include "OR_Object.h"
#include "OR_ObjectManager.h"
#include "../maths/OR_Maths.h"
#include "../special_effects/OR_Emitter_ABC.h"
#include "../special_effects/OR_MetaObject_ABC.h"
#include "../physic/OR_Deflector_ABC.h"
#include "../physic/OR_ParticuleManager.h"

#pragma warning( disable : 4275 ) 

namespace OR
{

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Gizmo
 *  \brief  Super class for all gizmo.
 *  \author Gabriel Peyré 2001-12-12
 *  
 *	A gizmo is an invisible volume use for a lot of thing [clipping ...].
 *	Global definition of Dim[3] : Dim[i] mesure the distance from the center of
 *	the gizmo to the edge of the gizmo on the coord 'i'.
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_Gizmo: public OR_Object, public OR_Emitter_ABC, public OR_Deflector_ABC, public OR_MetaObject_ABC
{

public:

	/** constructor */
	OR_Gizmo(OR_Vector3D vX=OR_Vector3D(1,0,0),
			 OR_Vector3D vY=OR_Vector3D(0,1,0),
			 OR_Vector3D vZ=OR_Vector3D(0,0,1), 
			 OR_Vector3D dim=OR_Vector3D(1,1,1));

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	/** set the dimensions of the gizmo */
	void SetDim(OR_Vector3D dim);
	/** get the dimensions of the gizmo */
	OR_Vector3D& GetDim();
	/** set the axes of the gizmo */
	void SetAxe(OR_Vector3D xaxe, OR_Vector3D yaxe, OR_Vector3D zaxe);
    //@}

    //-------------------------------------------------------------------------
    /** \name frustrum culling function [not yet implemented] */
    //-------------------------------------------------------------------------
    //@{
	/** test if a point is inside the gizmo */
	virtual OR_Bool IsInside(OR_Vector3D pos);
	/** test if the gizmo is inside the frustrum view */
	virtual OR_Bool FrustrumClip();
    //@}

    //-------------------------------------------------------------------------
    /** \name overload of OR_Object methods */
    //-------------------------------------------------------------------------
    //@{
	/** get the type of the object */
	virtual OR_Elements GetType()
	{ return OR_GIZMO; }
	/** overload function from OR_Object */
	virtual void Rotate(OR_Float) {}
	/** overload function from OR_Object */
	virtual void Draw() {}
    //@}

	//-------------------------------------------------------------------------
    /** \name iverload of OR_Deflector_ABC methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void DeflectParticule(OR_Particule& particule) {}
	virtual void DeflectParticuleManager( OR_ParticuleManager& particuleManager );
	virtual void DeflectObject(OR_RigidBody& object) {}
    //@}


						//-------------------------------------------------------------------------
						/** \name overload from \c OR_MetaObject_ABC */
						//-------------------------------------------------------------------------
						//@{
						virtual void AddMetaValue(OR_MetaGrid& grid) {}

						/** set the intensity */
						void SetMetaIntensity(OR_Float intensity);
						void AutoSetMetaIntensity();
						/** get the intensity */
						OR_Float GetMetaIntensity();
						/** set the influence radius */
						void SetInfluenceRadius(OR_Float radius);
						/** get the influence radius */
						OR_Float GetInfluenceRadius();
						//@}
	
    //-------------------------------------------------------------------------
    /** \name helper methods */
    //-------------------------------------------------------------------------
    //@{
	void ResolveImpulse(OR_Particule& particule, OR_Vector3D& Normal, OR_Vector3D& ImpactPos);
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
    //@}

	
protected:

	/** dimensions of the gizmo */
	OR_Vector3D Dim;
	
	/* meta-env variables **************************************************************/
	/** intensity of the meta-object */
	OR_Float rMetaIntensity_;
	/** radius of influence */
	OR_Float rInfluenceRadius_;

};


} // namespace OR

#ifdef OR_USE_INLINE
#   include "OR_Gizmo.inl"
#endif

#endif // _OR_GIZMO_H_


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
