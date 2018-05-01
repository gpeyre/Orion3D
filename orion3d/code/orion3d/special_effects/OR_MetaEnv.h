/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaEnv.h
 *  \brief Contains the definition of a meta-env
 *  \author Gabriel Peyré 2001-07-15
 *
 *	A meta-env is composed of :
 *		- a cube gizmo, representing the area in wich the meta-object will be rendered.
 *		- a manager of gizmo, representing the meta-objects that are to be rendered
 * 
 *	 The meta-env used an Iso-Surface to render the grid with a marching-cube algo.	
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_MetaEnv_H_
#define __OR_MetaEnv_H_

#include "../configuration/OR_Config.h"
#include "OR_IsoSurface.h"
#include "OR_SpecialEffect.h"
#include "OR_MetaObject_ABC.h"
#include "../maths/OR_Maths.h"
#include "../utils/OR_ManagerMap_Template.h"
#include "../objects/OR_Object.h"
#include "../objects/OR_Gizmo.h"
#include "../objects/OR_CubeGizmo.h"
#include "../shaders/OR_Shader.h"
#include "../shaders/OR_Shadable.h"

namespace OR
{
	
/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MetaEnv
 *  \brief  A single meta-environnement.
 *  \author Gabriel Peyré 2001-07-15
 *  
 *	The meta-environnement is composed of :
 *		- a list of meta-stuff [meta-ball, bloby-ball...], which is used to compute a 3d grid.
 *		- an iso-surface, which is used to render the 3d grid to screen.
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_MetaObject_ABC>;

class ORION3D_API OR_MetaEnv: public OR_ManagerMap_Template<OR_MetaObject_ABC>, public OR_SpecialEffect, public OR_Shadable
{

public:

    //-------------------------------------------------------------------------
    /** \name constructor & destructor */
    //-------------------------------------------------------------------------
    //@{
	/** constructor */
	OR_MetaEnv();
	/** destructor : delete the grid */
	~OR_MetaEnv();
    //@}

    //-------------------------------------------------------------------------
    /** \name set/get functions */
    //-------------------------------------------------------------------------
    //@{
	/** set the shader for the surface */
	void SetShader(OR_Shader& shader);
	/** get the shader used to render the meta-env */
	OR_Shader* GetShader();

	/** set the support of the meta-env */
	void SetSupportGizmo(OR_CubeGizmo& support);
    //@}

    //-------------------------------------------------------------------------
    /** \name set up surface parameters */
    //-------------------------------------------------------------------------
    //@{
	OR_IsoSurface& GetIsoSurface();
	/** set the iso-level used to render the surface */
	void SetIsoLevel(OR_Float level);
	/** get the iso-level used to render the surface */
	OR_Float GetIsoLevel();
    //@}

    //-------------------------------------------------------------------------
    /** \name draw and update functions */
    //-------------------------------------------------------------------------
    //@{
	/** update the rotations for animation */
	virtual void Update();
	/** draw the meta-env */
	virtual void Draw();
    //@}
	
    //-------------------------------------------------------------------------
    /** @name overloaded functions from OR_Shadable */
    //-------------------------------------------------------------------------
    //@{
	virtual void ProcessAllFaces();
	virtual void ProcessOneFace(OR_U32 nNumFace);
	virtual void AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCorrdArray, OR_U32* &aFaceArray, 
							   OR_U32& nNbrVert, OR_U32& nNbrFace );
    //@}  

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	/** compute the id of each shader */
	void ComputeId();
	OR_DEFINE_SERIALIZATION(OR_MetaEnv);
    //@}
	
private:
	
	/** an iso-surface to draw the meta-balls */
	OR_IsoSurface IsoSurface_;
	/** the shader used to render the surface */
	OR_Shader* pShader_;

	/** do we need to recompute the grid */
	OR_Bool bNeedUpdate_;
	OR_Bool bNeedRedraw_;
};

} // namespace OR


#ifdef OR_USE_INLINE
	#include "OR_MetaEnv.inl"
#endif

#endif // __OR_MetaEnv_H_


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