/*---------------------------------------------------------------------------------------*/
/*                                      OR_Bone.h                                        */
/*---------------------------------------------------------------------------------------*/
/* contains the definition of a bone                                                     */
/*---------------------------------------------------------------------------------------*/

/** \file
	Contains the defintion of a bone, which can be used to form a skeleton, and serve as a
	basis to skin a mesh.
	\author Gabriel
*/

#ifndef _OR_BONES_H_
#define _OR_BONES_H_

#include "../configuration/OR_Config.h"
#include "OR_Object.h"
#include "OR_Mesh.h"


/*---------------------------------------------------------------------------------------*/
/*                                 class OR_Bone                                         */
/*---------------------------------------------------------------------------------------*/

/// A bone in a squelleton.
/** 
	A bone is an OR_Object that is used in the hierarchy as a part of a skeleton.
	Generaly, the root node of the squelleton will hold a skinable mesh (ie. a mesh that have
	an OR_Skinable attribute). 
	The root node will set the global position of the skeleton, whereas the position of the other bones
	will have no influence. In fact, a bone (except the root node) use its orientation and it's length 
	to set up the position of it's child bone.
	\author Gabriel
*/

namespace OR
{


class ORION3D_API OR_Bone: public OR_Object
{

public:

	/** constructor */
	OR_Bone(OR_Float rLength=1, OR_Bool bIsEndEffector=false, OR_Mesh* pSkin=NULL);

    //-------------------------------------------------------------------------
    /** @name overload virtual function from OR_Object */
    //-------------------------------------------------------------------------
    //@{
	/** get the type of the object */
	virtual OR_Elements GetType();
	/** draw the mesh */
	virtual void Draw();
	/** set the world-relative matrix */
	virtual void Update();
	virtual void PostExportPass();
    //@}

	//-------------------------------------------------------------------------
    /** @name accessor  */
    //-------------------------------------------------------------------------
    //@{
	/** get the skin */
	OR_Mesh *GetSkin();
	/** set the skin */
	void SetSkin(OR_Mesh* pSkin);
	/** get the length */
	OR_Float GetLength();
	/** set the length */
	void SetLength(OR_Float rLenght);
	//@}

	//-------------------------------------------------------------------------
    /** @name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_Bone);
    //@}
	
private:
	
	/** the skin of the skeleton : can be NULL if there is no skin. */
	OR_Mesh* pSkin_;
	/** the Id of the skin (usefull for BuilTo/FromFile) */
	OR_U32 nSkinId;
	/** the length of the bone */
	OR_Float rLength_;
	/** constraint on rotation */
	OR_Float rRotationConstraint_;
	/** is the bone a end effector ? */
	OR_Bool bIsEndEffector_;
};


} // namespace OR


#ifdef OR_USE_INLINE
	#include "OR_Bone.inl"
#endif // OR_USE_INLINE

#endif // _OR_BONES_H_

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