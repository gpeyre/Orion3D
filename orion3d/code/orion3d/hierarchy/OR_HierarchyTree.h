/*---------------------------------------------------------------------*/
/*                          OR_HierarchyTree.h                         */
/*---------------------------------------------------------------------*/
/* implementation of hierarchical tree                                 */           
/*---------------------------------------------------------------------*/

#ifndef _OR_HIERARCHYTREE_H_
#define _OR_HIERARCHYTREE_H_

#include "../configuration/OR_Config.h"
#include "OR_Node.h"
#include "../objects/OR_Object.h"
#include "../objects/OR_Mesh.h"
#include "../objects/OR_Light.h"
#include "../objects/OR_Gizmo.h"
#include "../objects/OR_GizmoManager.h"
#include "../special_effects/OR_ParticuleSystem.h"
#include "../objects/OR_MathSurface.h"
#include "../special_effects/OR_MetaEnv.h"
#include "../shaders/OR_Shader.h"
#include "../utils/OR_Serializable.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"
#include "../shell/OR_ShellFuncDecl.h"
#include "../wrapper_lua/OR_WrapperLUA.h"

namespace OR
{

/*----------------------------------------------------------------------*/
/*                         classe OR_HierarchyTree                      */
/*----------------------------------------------------------------------*/
/* a hierarchical tree used to store all OR_Objects.                    */
/*----------------------------------------------------------------------*/

/// a hierarchical tree used to store all OR_Objects.
/** 
	contains a copy of each manager of object that can be store in the tree,
	so that, when a new object is created by the tree, it can be accessible
	by other class easily.
	\author Gabriel
*/
class ORION3D_API OR_HierarchyTree: public OR_Serializable, public OR_ShellObject_ABC
{

public:

	/* constructor & destructor ************************************/
	/** constructor */
	OR_HierarchyTree();
	/** destructor */
	~OR_HierarchyTree();


	/* creation methods ********************************************/
	/** add a node under the root */
	void AddNode( OR_Object* new_object );
	OR_Node* DupTree( const OR_Node* Dup, OR_Node* NewFather = NULL );

	/* rendering methods *******************************************/
	/** draw the whole tree */
	void Draw();
	/** update each object in the hierarchy */
	void Update();

	/* node managing ***********************************************/
	/** delete a sub-tree (remove each object from the correct manager). */
	void DeleteSubTree(OR_Node* node);

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	/* search methods **********************************************/
	/** search for a node given the name of the object */
	const OR_Node* GetNodeByName( const char* name) const;
	OR_Node* GetNodeByName( const char* name);
	/** Return the root node */
	OR_Node* GetRootNode();
	OR_Node* GetNode(OR_Object& pObj);

	OR_U32 GetNbrObject();
    //@}


	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	/** write in an opened KRD file from the datas that are in the sub-tree 
	    starting on node start */
	void BuildToFile( OR_File& f, OR_Node* start);
	OR_DEFINE_SERIALIZATION(OR_HierarchyTree);

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	
	OR_DECL_SHELL_FUNC(GetNbrObject, 1);
	OR_DECL_SHELL_FUNC(PrintNbrObject, 0);
    //@}

	
private:
	
	/** number of objects in the tree */
	OR_I32 NbObjets;
	
	/** the root of the tree */
	OR_Node* TreeRoot;
	
	/* recursive methods *******************************************/
	/** used recursivly by GetNodeByName */
	const OR_Node* GetNodeByName_Rec( const char* name, const OR_Node* cur_node ) const;
	OR_Node* GetNode_Rec(OR_Object& pObj, OR_Node& cur_node);
	/** used recursivly by DeleteSubTree */
	void DeleteSubTree_Rec(OR_Node* cur_node);
	
};


} // namespace OR



#ifdef OR_USE_INLINE
	#include "OR_HierarchyTree.inl"
#endif

#endif     /* #ifndef _OR_HIERARCHYTREE_H_ */


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