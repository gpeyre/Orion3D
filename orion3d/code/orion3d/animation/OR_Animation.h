/*------------------------------------------------------------------*/
/*                       OR_Animation.h                             */
/*------------------------------------------------------------------*/
/* definition of animation of a sub-tree                            */
/*------------------------------------------------------------------*/

/** \file 
	Contains definition of animation class [a tree of animation node].
	\author Gabriel.
**/

#ifndef _OR_ANIMATION_H_
#define _OR_ANIMATION_H_

#include "OR_AnimationNode.h"
#include "OR_AnimationTrack.h"
#include "../configuration/OR_Config.h"
#include "../objects/OR_Object.h"
#include "../hierarchy/OR_Node.h"
#include "../misc/OR_Endian_Conv.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_String.h"
#include "../utils/OR_File.h"
#include "../utils/OR_ManagerMap_Template.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"

namespace OR
{

class OR_AnimationNode;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Animation
 *  \brief  An animation tree.
 *  \author Gabriel Peyré 2001-11-14
 *
 *	An animation is based on the father node of a sub-tree.
 *	It is composed of a hierarchy of animation tracks, which descibes 
 *	the hierarchy under	the father node.
 *
 *	\example shell_test/main.cpp
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_Animation: public OR_Serializable, public OR_ShellObject_ABC
{

public:

    //-------------------------------------------------------------------------
    /** \name constructor */
    //-------------------------------------------------------------------------
    //@{
	/** constructor */
	OR_Animation(OR_File file);
	/** base constructor */
	OR_Animation();
	/** destructor */
	virtual ~OR_Animation();
    //@}

	/** update the sub-tree 0<t<1 */
	void Update(class OR_Node* father, OR_Float t);

	/** return the father node of the track sub-tree */
	OR_AnimationNode* GetFatherNode();
	/** set the father node of the track sub-tree */
	void SetFatherNode(OR_AnimationNode* father);

	/** get the name of the animation */
	OR_String& GetName();
	/** set the name of the animation */
	void SetName(const char* name);
	void SetName(const OR_String& name);
	/** get the number of object */
	OR_I32 GetNbObject();
	/** set the number of object */
	void SetNbObject(OR_I32 n);
	/** set the duration of the animation */
	void SetDuration(OR_Float duration);
	/** return the duration of the animation */
	OR_Float GetDuration();

	/** draw the trajectories of all sub-tree */
	void DrawTrajectory(OR_Node* cur_node);

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	/** export the data from the object to an opened file, starting on a given node of the hierarchy
		\param SelectedNode the node of the hierarchy from which we want to begin the export 
		\param OR_Node* HierarchyRoot : the root of the hierarchy, in fact the node that coresponds to the root of the animation.
		
		  for instance, here is how Orion3DMax store the hierarchy :
		\begincode
                    RealRoot
                  /         \
          PluginStuff        PseudoRoot          
		                     /    |    \        
  selected object->      Torso   Cam    Light
                        /  |  \
                          ....
		\endcode
		and an animation can look like this :
		\begincode
                     AnimationRoot
                    /      |      \
                 node1     0       0   [0 means no node since we don't wan't to animate this part of the tree]
                /  |  \    
                  ...
		\endcode
		So the call should be :
		BuildToFile(file, PseudoRoot, Torso);
		This will use the method ComputeStartNode like that
		ComputeStartNode(AnimationRoot, PseudoRoot, Torso)
		which will return the node "node1" which corresponds to "Torso".
	*/
	void BuildToFile(OR_File file, OR_Node* HierarchyRoot, OR_Node* SelectedNode);
	OR_DEFINE_SERIALIZATION(OR_Animation);
    //@}

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	
	OR_DECL_SHELL_ACCESSOR_FUNC(Name,			OR_Animation, String);
	OR_DECL_SHELL_GET_PRINT_FUNC(NbObject,		OR_Animation, U32);
	OR_DECL_SHELL_GET_PRINT_FUNC(Duration,		OR_Animation, Float);
    //@}

	
private:
	/** the father node of the sub-tree of track */
	OR_AnimationNode* FatherNode;
	/** the number of object involved in the animations [for error checking purpose] */
	OR_U32 NbObjects;
	/** name of the object */
	OR_String Name;
	/** duration of the animation, in seconds */
	OR_Float Duration;

	/** given the node that is selected in the hierarchy tree, compute the corresponding */
	OR_AnimationNode* ComputeStartNode(OR_AnimationNode* CurAnimationNode,
									   class OR_Node* CurHierarchyNode,
									   class OR_Node* SelectedNode);

};


} // namespace OR

#endif /* #ifndef _OR_ANIMATION_H_ */

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////
