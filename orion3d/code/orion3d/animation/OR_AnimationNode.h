/*------------------------------------------------------------------------------
 *  \file  OR_AnimationNode.h
 *  \brief A node in a hierachical animation.
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/

#ifndef __OR_AnimationNode_h_
#define __OR_AnimationNode_h_

#include "../configuration/OR_Config.h"
#include "OR_AnimationTrack.h"
#include "../objects/OR_Object.h"
#include "../hierarchy/OR_Node.h"
#include "../misc/OR_Endian_Conv.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_String.h"
#include "../utils/OR_File.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"


namespace OR {
	
class OR_AnimationNode;	
/** a list of nodes */
typedef list<OR_AnimationNode*> T_AnimationNodeList;
/** an iterator on a list of nodes */
typedef T_AnimationNodeList::iterator IT_AnimationNodeList;

/*------------------------------------------------------------------------------
/**  \class  OR_AnimationNode
 *  \brief  A node in a hierachical animation.
 *  \author Gabriel Peyré 2001-07-08
 *  An animation is composed of a tree of AnimationNode.
 *  Each node has a list of track, which contains the animation informations for
 *  the object.
*/
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_AnimationNode: public OR_Serializable, public OR_ShellObject_ABC
{

public:

	//-------------------------------------------------------------------------
    /** \name constructor & destructor */
    //-------------------------------------------------------------------------
    //@{
	/** constructor */
	OR_AnimationNode(class OR_AnimationNode* father=NULL);
	/** destructor */
	virtual ~OR_AnimationNode();
    //@}

    //-------------------------------------------------------------------------
    /** \name update & draw  */
    //-------------------------------------------------------------------------
    //@{
	/** update an object 0<t<1 */
	void Update(OR_Node* hierarchy_node, OR_Float t);
	/** draw the trajectory of the object */
	void DrawTrajectory(OR_Node* hierarchy_node);
    //@}

    //-------------------------------------------------------------------------
    /** \name sons management */
    //-------------------------------------------------------------------------
    //@{
	/** add an object to the son list */
	void AddSon(OR_AnimationNode &pNode);
	/** add a son as the last son on the list */
	void AddSonFirst(OR_AnimationNode &pNode);
	void AddSonLast(OR_AnimationNode &pNode);
	T_AnimationNodeList& GetSonList();
	OR_AnimationNode* GetFather();
	void SetFather(OR_AnimationNode* pFather);
    //@}

	//-------------------------------------------------------------------------
    /** \name track management */
    //-------------------------------------------------------------------------
    //@{
	/** add a track at the end of the track list */
	void AddTrackLast(OR_AnimationTrack &track);
	/** add a track at the start of the track list */
	void AddTrackFirst(OR_AnimationTrack &track);
	/** get the number of son */
	OR_I32 GetNbSon();
	/** get the number of track */
	OR_I32 GetNbTrack();
	/** sort the list of track to put the rotate track at the begining (to avoid) */
	//void SortTrack();
	T_AnimationTrackList& GetTrackList();
    //@}

    //-------------------------------------------------------------------------
    /** \name helpers methods */
    //-------------------------------------------------------------------------
    //@{
	void RescaleTime(OR_Float start, OR_Float end);
	/** Make all keys relative to their own nodes, that is, to the first key */
	void RelativiseKeys();
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationNode);
    //@}


	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	
	OR_DECL_SHELL_GET_PRINT_FUNC(NbSon,		OR_AnimationNode, U32);
	OR_DECL_SHELL_GET_PRINT_FUNC(NbTrack,	OR_AnimationNode, U32);
    //@}

private :

	/** a list of track */
	T_AnimationTrackList TrackList_;
	/** the father node */
	OR_AnimationNode *pFather_;
	/** the root of the sons' list*/
	T_AnimationNodeList SonList_;

};


} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_AnimationNode.inl"
#endif


#endif // __OR_AnimationNode_h_

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

