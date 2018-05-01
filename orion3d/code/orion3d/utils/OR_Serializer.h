/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Serializer.h
 *  \brief Definition of class \c OR_Serializer
 *  \author Gabriel Peyré 2002/03/21
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Serializer_h_
#define __OR_Serializer_h_


#include "../configuration/OR_Config.h"
#include "../utils/OR_Serializable.h"
#include "../hierarchy/OR_HierarchyTree.h"
#include "../animation/OR_AnimationManager.h"
#include "../special_effects/OR_SpecialEffectManager.h"
#include "../shaders/OR_ShaderManager.h"


namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Serializer
 *  \brief  This class is used to manage the serialization process.
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	This class tells to \b Orion3D wich part of the engine the users want to exports
 *	to a file. It is then putted at the begining of the file.
 *
 *	When a file is imported to the engine, we first retrieve the \c OR_Serializer 
 *	at the beginning of the file, so we know what we will find inside the file.
 *
 *	The \c OR_Serializer class also contains information about the version of \b Orion3D
 *	being used.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Serializer: public OR_Serializable
{
public:

    //-------------------------------------------------------------------------
    /** \name Constructor and destructor */
    //-------------------------------------------------------------------------
    //@{
	OR_Serializer();
	~OR_Serializer();
	//@}

    //-------------------------------------------------------------------------
    /** @name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildFromFile( OR_File& file );
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_Serializer);
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	#define DECL_ACCESSOR(name)					\
	OR_Bool	GetExport##name()					\
	{ return bExport##name##_; }				\
	void	SetExport##name(OR_Bool bVal)		\
	{ bExport##name##_=bVal; }
	DECL_ACCESSOR(Hierarchy)
	DECL_ACCESSOR(Animation)
	DECL_ACCESSOR(Shader)
	DECL_ACCESSOR(SpecialEffect)
	#undef DECL_ACCESSOR

	OR_Node* GetHierarchyStartNode()
	{ return pHierarchyStartNode_; }
	OR_Node* GetAnimationStartNode()
	{ return pAnimationStartNode_; }
	OR_Node* GetAnimationHierarchyRoot()
	{ return pAnimationHierarchyRoot_; }
	void SetHierarchyStartNode(OR_Node& node)
	{  pHierarchyStartNode_ = &node; }
	void SetAnimationStartNode(OR_Node& node)
	{ pAnimationStartNode_ = &node; }
	void SetAnimationHierarchyRoot(OR_Node& node)
	{ pAnimationHierarchyRoot_ = &node; }

	OR_Bool GetError()
	{ return bError_; }
    //@}
    
private:

	OR_Bool bExportHierarchy_;
	OR_Bool bExportAnimation_;
	OR_Bool bExportShader_;	
	OR_Bool bExportSpecialEffect_;

	/** does an error has occurs during import ? */
	OR_Bool bError_;

	/** were do we start the export of the hierarchy tree ? */
	OR_Node* pHierarchyStartNode_;
	/** wich node of the hierarchy is considered as the root one for animation ? */
	OR_Node* pAnimationHierarchyRoot_;
	/** wich node is the starting node of the export for animation */
	OR_Node* pAnimationStartNode_;

};

} // End namespace OR

#endif // __OR_Serializer_h_

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

