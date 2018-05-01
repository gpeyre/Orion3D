/*------------------------------------------------------------------------------
 *  \file  OR_Node.h
 *  \brief 	Contains the definition of a node in the Orion3D hierarchy.
 *	A node is used to store an OR_Object and an animation player list used
 *	to play a list of animations on the node.
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/

#ifndef __OR_Node_h_
#define __OR_Node_h_


#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"
#include "../objects/OR_Object.h"
#include "../utils/OR_Serializable.h"
#include "../objects/OR_Skin.h"
#include "../objects/OR_Mesh.h"
#include "../objects/OR_Light.h"
#include "../objects/OR_Gizmo.h"
#include "../objects/OR_Camera.h"
#include "../shell/OR_ShellObject_ABC.h"


namespace OR {


class OR_Node;
/** a list of nodes */
typedef list<OR_Node*> T_NodeList;
/** an iterator on a list of nodes */
typedef T_NodeList::iterator IT_NodeList;
/** an const iterator on a list of nodes */
typedef T_NodeList::const_iterator CIT_NodeList;

/*------------------------------------------------------------------------------
/**  \class  OR_Node
 *  \brief  a node of the hierarchical tree
 *  \author Gabriel Peyré 2001-07-08
 *  The scene graph (ie. the OR_HierarchyTree) is composed of OR_Node.
 *  Each node support an OR_Object.
 *  Each node has :
 *    - a list of sons
 *    - a father node (NULL for the root node)
 *    - a list of animation player (the animations that will be played on the sub-tree).
*/
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_Node: public OR_Serializable, public OR_ShellObject_ABC
{

public:

	OR_Node(OR_Object* object=NULL, class OR_Node* father=NULL);
	OR_Node( const OR_Node& Dup );
	OR_Node& operator=( const OR_Node& Dup );
	virtual ~OR_Node();

    //-------------------------------------------------------------------------
    /** \name sons management */
    //-------------------------------------------------------------------------
    //@{
	void AddSonFirst(OR_Node &pNode);
	void AddSonLast(OR_Node &pNode);
	void RemoveSon(OR_Node& son);
    //@}


    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OR_U32 GetNbSon();
	OR_U32 GetNbElements();
	OR_Object* GetObject();
	const OR_Object* GetObject() const;
	void SetObject(OR_Object& object);
	OR_Node* GetFather();
	void SetFather(OR_Node* pNode);
	T_NodeList& GetSonList();
	const T_NodeList& GetSonList() const;
	T_AnimationPlayerList& GetPlayerList();
    //@}



    //-------------------------------------------------------------------------
    /** \name animations management */
    //-------------------------------------------------------------------------
    //@{
	void AddPlayer(OR_AnimationPlayer& player);
	void RemovePlayer();
	void RemoveAllPlayers();
	void DrawTrajectory();
    //@}

    //-------------------------------------------------------------------------
    /** \name update & draw */
    //-------------------------------------------------------------------------
    //@{
	void Update();
	void Draw();
    //@}

    //-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);

	OR_DECL_SHELL_GET_PRINT_FUNC(NbSon,			OR_Node, U32);
	OR_DECL_SHELL_GET_PRINT_FUNC(NbElements,	OR_Node, U32);

	OR_DECL_IMPL_SHELL_FUNC(RemovePlayer,		OR_Node);
	OR_DECL_IMPL_SHELL_FUNC(RemoveAllPlayers,	OR_Node);
    //@}

    //-------------------------------------------------------------------------
    /** \name serialisation methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildFromFile( OR_File& file );
	virtual void BuildToFile( OR_File& file );
	void ComputeId( OR_U32& id );
	OR_DEFINE_SERIALIZATION(OR_Node);
    //@}

private:

	/* a FIFO of animation player */
	T_AnimationPlayerList PlayerList_;
	
	/** a 3d object (can be a mesh, a light, a nurbs, a cam, etc) */
	OR_Object *pObject_;
	/** the father of the node in the tree [NULL if it's the tree root] */
	OR_Node *pFather_;
	/** list of sons */
	T_NodeList SonList_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_Node.inl"
#endif


#endif // __OR_Node_h_

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
