/*------------------------------------------------------------------------------
 *  \file  OR_Skin.h
 *  \brief Contains the definition of a OR_Skin, which is a bone-based deformable OR_Mesh
 *  \author Antoine Bouthors 2001-10-05
 *------------------------------------------------------------------------------*/

#ifndef __OR_Skin_h_
#define __OR_Skin_h_

#include "../configuration/OR_Config.h"
#include "OR_Mesh.h"
#include "OR_ObjectManager.h"


namespace OR {


/*------------------------------------------------------------------------------
/**  \class  OR_Skin
 *  \brief  A kind mesh that can be deformed by a set of bones
 *  \author Antoine Bouthors 2001-10-05
 *
 *	\example skin_test/main.cpp
 */
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_Skin : public OR_Mesh
{
public:

	/*------------------------------------------------------------------------------
	/**  \class  OR_SkinElt
	 *  \brief  A structure regrouping faces sharing the same bones. 
	 *  \author Antoine Bouthors 2001-10-05
	 */
	/*------------------------------------------------------------------------------*/
	struct OR_SkinElt
	{
		T_U32Vector	m_Bones;	//!< The bones that are used to skin all the faces described				
		OR_U32		m_Start;	//!< The first face ( in the indices array ) that is skinned by these bones
		OR_U32		m_NbrFaces;	//!< Number of faces (including the first) that are skinned by these bones

		bool operator<( const OR_SkinElt& j ) const { return( m_Bones.size() < j.m_Bones.size() ); }
	};

	/** list of SkinElt */
	typedef list<OR_SkinElt> T_SkinEltList;
	/** iterator for list of SkinElt */
	typedef T_SkinEltList::iterator IT_SkinEltList;
	/** const iterator for list of SkinElt */
	typedef T_SkinEltList::const_iterator CIT_SkinEltList;



	
	OR_Skin();
    OR_Skin( const OR_Skin& Dup );
    OR_Skin( const OR_Mesh& Dup );
    OR_Skin( const OR_Float* VertsArray, const OR_Float* NormsArray, const OR_Float* TCoordsArray, const OR_U32* FacesArray, OR_U32 NbrVerts, OR_U32 Nbrfaces );
    virtual ~OR_Skin();
    OR_Skin& operator=( const OR_Skin& Dup );

    //-------------------------------------------------------------------------
    /** \name Skinning parameters methods */
    //-------------------------------------------------------------------------
    //@{
	const OR_U32&			GetNbrBones() const;
	void					SetNbrBones( const OR_U32& NbrBones );
	void					SetBone( OR_U32 i, OR_Object* Bone );
	const OR_Object*		GetBone( OR_U32 i ) const;
	OR_Object *				GetBone( OR_U32 i );

	void					SetMeshRefMatrix( const OR_Matrix4x4& MeshRefMatrix );
	const OR_Matrix4x4&		GetMeshRefMatrix() const;
	void					SetRefMatrix( OR_U32 i, const OR_Matrix4x4& RefMatrix );
	const OR_Matrix4x4&		GetRefMatrix( OR_U32 i ) const;

	void					SetWeight( OR_U32 nBone, OR_U32 nVert, OR_Float Weight );
	OR_Float				GetWeight( OR_U32 nBone, OR_U32 nVert ) const;

	const T_SkinEltList&	GetSkinElts() const;

	void					Initialize();

	void					EnableSkinning();
	void					DisableSkinning();
	OR_Bool					IsSkinningEnabled();
    //@}

    //-------------------------------------------------------------------------
    /** \name overloaded methods from OR_Object */
    //-------------------------------------------------------------------------
    //@{
	/** the type of the object */
	virtual OR_Elements GetType();
	/** draw the skin */
	virtual void		Draw();
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
	virtual void BuildFromFile(OR_File& file);
	/** export the data from the object to an opened file */
	virtual void BuildToFile(OR_File& file);
	/** used to set up the bones once the export is done. The skin has
		to do a look up in ObjectList using bones id number to set the bones objects. */
	virtual void PostExportPass();

	OR_DEFINE_SERIALIZATION(OR_Skin);
    //@}
	
private:

	/** Prepare the data to be drawn ( fill in m_SkinMatrices ) */
	void PrepareDrawing();


    //-------------------------------------------------------------------------
    /** \name skin data */
    //-------------------------------------------------------------------------
    //@{
	/** Is skinning enalbed */
	OR_Bool			m_SkinningEnabled;
	/** Number of weightarrays */
	OR_U32			m_NbrBones;
	/** Weight arrays for all vertices */
	T_FloatVector*	m_WeightArrays;
	/** Bones used to skin the mesh */
	OR_Object**		m_Bones;
	/** Reference matrices of each bone */
	OR_Matrix4x4*	m_RefMatrices;
	/** Reference matrix of the mesh */
	OR_Matrix4x4	m_MeshRefMatrix;
	/** Original vertices array */
	OR_Float*		m_VertexArray;
	/** Original normals array */
	OR_Float*		m_NormalArray;
    //@}

    //-------------------------------------------------------------------------
    /** \name optimization data & functions. For internal use only */
    //-------------------------------------------------------------------------
    //@{
 	/** Matrices used in the computations. m_PrecomputedRefMatrices[i] = m_MeshRefMatrix*~m_RefMatrices[i] */
	OR_Matrix4x4*	m_PrecomputedRefMatrices;
  	/** Matrice used in the computations. m_PrecomputedMeshRefMatrice = ~m_MeshRefMatrix */
	OR_Matrix4x4	m_PrecomputedMeshRefMatrice;
	/** List of skin elements. A skin element regroups vertices skinned by the same bones */
	T_SkinEltList	m_SkinElts;
 	/** Matrices used in skinning. This is a cache for matrices to blend. They are updated every frame */
	OR_Matrix4x4*	m_SkinMatrices;
	/** Fill in m_PrecomputedRefMatrices */
	void			PrecomputeRefMatrices();
    //@}

};


/*------------------------------------------------------------------------------
 *  \class  OR_SkinManager
 *  \brief  The manager of Skin.
 *  \author Antoine Bouthors 2001-10-05
 *  
 *  Contains a copy of every skin in the hirarchy.
 *	This alow to have an easy acces to each skin.
 *------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
#pragma warning( disable : 4660 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_Manager_Template_Object<OR_Skin>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_SmartManagerMap_Template<OR_Skin>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Skin>;

class ORION3D_API OR_SkinManager: public OR_Manager_Template_Object<OR_Skin>
{
};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_Skin.inl"
#endif



#endif // __OR_Skin_h_

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

