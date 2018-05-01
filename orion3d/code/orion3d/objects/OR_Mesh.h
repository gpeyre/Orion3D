/*------------------------------------------------------------------------------
 *  \file  OR_Mesh.h
 *  \brief Contains the definition of a mesh, wich is the basic 3D object
 *  \author Gabriel Peyré 2001-07-09
 *------------------------------------------------------------------------------*/

#ifndef __OR_Mesh_h_
#define __OR_Mesh_h_

#include "../configuration/OR_Config.h"
#include "OR_Object.h"
#include "OR_ObjectManager.h"
#include "../shaders/OR_Shader.h"
#include "../shaders/OR_AlphaPipeline.h"
#include "../shaders/OR_Shadable.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_File.h"
#include "../shaders/OR_Shadable.h"
#include "../objects/OR_MeshDataManager.h"

namespace OR {


/**------------------------------------------------------------------------------
 *  \class  OR_Mesh
 *  \brief  This is the basic 3D object, compound of faces (3 vertex).
 *  \author Gabriel Peyré 2001-07-09
 *  
 *  The vertex of the mesh are stored in OpenGL vertex arrays 
 *  (Vertex, Normals, TexCoords, and vertex weight if this is a skin).
 *  The mesh inherit from :
 *		- OR_Object : as every object in the scene graph
 *		- OR_Shadable : because the mesh is drawn using a shader.
 *------------------------------------------------------------------------------*/
class ORION3D_API OR_Mesh: public OR_Object, public OR_Shadable
{

protected:

	/** The MeshData handle */
	OR_U32 m_MeshDataHandle;

public:
	
    //-------------------------------------------------------------------------
    /** \name constructors and destructor */
    //-------------------------------------------------------------------------
    //@{
	/** constructor : init from memory */
	OR_Mesh( const OR_Float* VertsArray, const OR_Float* NormsArray, const OR_Float* TCoordsArray, const OR_U32* FacesArray, OR_U32 NbrVerts, OR_U32 Nbrfaces );
	/** copy constructor */
	OR_Mesh( const OR_Mesh& Dup );
	/** base constructor : do nothing (usefull for imporation) */
	OR_Mesh();
	/** destructor */
	virtual ~OR_Mesh();
	/** copy operator */
	OR_Mesh& operator=( const OR_Mesh& Dup );

	OR_U32 GetMeshDataHandle()
	{ return m_MeshDataHandle; }
    //@}
	

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	/** \return the vertex list */ 
	OR_Float* GetVertsArray();
	/** \return the normals list */ 
	OR_Float* GetNormsArray();
	/** \return the texcoords list */ 
	OR_Float* GetTCoordsArray();
	/** get the face list */ 
	OR_U32* GetFaceList();
	/** get the number of vertex */ 
	OR_U32 GetNbVertex();
	/** get the number of faces */ 
	OR_U32 GetNbFaces();
	/** set the alpha value */
	void SetAlpha(OR_Float val);
    //@}

    //-------------------------------------------------------------------------
    /** \name overloaded methods from OR_Object */
    //-------------------------------------------------------------------------
    //@{
	/** the type of the object */
	virtual OR_Elements GetType();
	/** draw the mesh */
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

	virtual void SetUpModelView();
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

	OR_DEFINE_SERIALIZATION(OR_Mesh);
    //@}

};


/**-----------------------------------------------------------------------------
 *  \class  OR_MeshManager
 *  \brief  The manager of mesh.
 *  \author Gabriel Peyré 2001-07-09
 *  
 *  Contains a copy of every mesh in the hirarchy.
 *	This alow to have an easy acces to each mesh.
 *------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
#pragma warning( disable : 4660 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_Manager_Template_Object<OR_Mesh>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_SmartManagerMap_Template<OR_Mesh>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Mesh>;

class ORION3D_API OR_MeshManager: public OR_Manager_Template_Object<OR_Mesh>
{
public:
	/** create a mesh from an open krd file file */
	OR_I32 AddMesh(FILE *fichier, OR_I32 nbvertex, OR_I32 listsize);
	
	/** set the shader used to render the object */
	OR_I32 SetShader(OR_Shader& shader);
};


} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_Mesh.inl"
#endif


#endif // __OR_Mesh_h_

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
