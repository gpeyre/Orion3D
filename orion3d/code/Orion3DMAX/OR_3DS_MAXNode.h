/*------------------------------------------------------------------------------
 *  \file  OR_3DS_MAXNode.h
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-11-05
 *------------------------------------------------------------------------------*/

#ifndef __OR_3DS_MAXNode_h_
#define __OR_3DS_MAXNode_h_

#include "stdafx.h"
#include "OR_3DS_Node.h"
#include "OR_3DS_UserParam.h"
#include "OR_3DS_Utils.h"

using namespace OR;

namespace OR_3DS {

/*------------------------------------------------------------------------------
 *  \class  OR_3DS_MAXNode
 *  \brief  A node of the 3DSMAX scene
 *  \author Antoine Bouthors 2001-11-05
 *  This class is just a wrapper that allows you to get the Orion3D translation
 *	from a INode* node. Simply cast the INode* node to a OR_3DS_MAXNode* one and you can call
 *	the functions returning Orion3D classes
 *------------------------------------------------------------------------------*/

class OR_3DS_MAXNode : public INode
{
private:
	Modifier*	FindSkinModifier();
	Modifier*	FindPhysiqueModifier();
	OR_Skin*	GetOR_SkinFromISkin( TimeValue Time, T_U32Vector &LookupTable, Modifier *SkinMod );
	OR_Skin*	GetOR_SkinFromPhysique( TimeValue Time, T_U32Vector &LookupTable, Modifier *PhysiqueMod );

	OR_AnimationTrack* SamplePositionTrack( OR_I32 Step, OR_Float Treshold_Angle, OR_Bool Force, OR_I32 ForceStart, OR_I32 ForceEnd );
	OR_AnimationTrack* SampleRotationTrack( OR_I32 Step, OR_Bool Force, OR_I32 ForceStart, OR_I32 ForceEnd );
	OR_AnimationTrack* SampleScaleTrack( OR_I32 Step, OR_Bool Force, OR_I32 ForceStart, OR_I32 ForceEnd );
public:
	OR_AnimationTrack*	GetVisibilityTrack( float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float ForceStart, OR_Float ForceEnd );
	///\param start the start time (in seconds) of the track
	///\param end the end time (in seconds) of the track
	///\return the position track corresponding to the node, or NULL if there is no position track
	OR_AnimationTrack*	GetPositionTrack( float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float ForceStart, OR_Float ForceEnd );
	///\param start the start time (in seconds) of the track
	///\param end the end time (in seconds) of the track
	///\return the rotation track corresponding to the node, or NULL if there is no rotation track
	OR_AnimationTrack*	GetRotationTrack( float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float ForceStart, OR_Float ForceEnd );
	///\param start the start time (in seconds) of the track
	///\param end the end time (in seconds) of the track
	///\return the scale track corresponding to the node, or NULL if there is no scale track
	OR_AnimationTrack*	GetScaleTrack( float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float ForceStart, OR_Float ForceEnd );
	///\param start the minimum start time (in seconds) of all the tracks of this node
	///\param end the maximum end time (in seconds) of all the tracks of this node
	///\return the animation node taken from this node, or NULL if there is no animation
	OR_AnimationNode*	GetOR_AnimationNode(float &start, float &end,  OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float ForceStart, OR_Float ForceEnd, OR_AnimationNode* Father=NULL );
	///\param start the minimum start time (in seconds) of all the tracks of this tree
	///\param end the maximum end time (in seconds) of all the tracks of this tree
	///\param Father the father of the tree
	///\return the animation tree starting from this node (recursive), or NULL if there is no animation
	OR_AnimationNode*	GetAnimationTree( OR_U32 &nbnodes, float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float ForceStart, OR_Float ForceEnd, OR_AnimationNode* Father=NULL );
	///\return the animation of this node and all its subtree, or NULL if there is no animation
	OR_Animation*		GetOR_Animation( OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float Start, OR_Float End );
	///\param Time the time to retrieve the object
	///\param LookupTable a lookup table for the meshes (see CNode::GetOR_Mesh())
	///\return the OR_Object (ie. a OR_Mesh, OR_Gizmo, OR_Light or OR_Camera) taken from this node, or a PointGizmo if the object couldn't be translated. Use CNode::GetOR_Mesh(), CNode::GetOR_Light(), CNode::GetOR_Gizmo(), CNode::GetOR_Camera()
	OR_Object&			GetOR_Object( TimeValue Time, T_U32Vector &LookupTable, OR_3DS_Node* Root );
	///\param Time the time to retrieve the mesh
	///\param LookupTable a lookup table for the duplicated vertices : if the OR_Mesh's vertices number is N and the INode's is M (N>=M), then the vertex M<=M+i<N was duplicated from the vertex 0<=LookupTable[i]<M
	///\return the OR_Object taken from this node, or NULL if the object couldn't be translated into a Mesh
	OR_Mesh*			GetOR_Mesh( TimeValue Time, T_U32Vector &LookupTable);
	///\param Time the time to retrieve the gizmo
	///\return the OR_Gizmo taken from this node, or NULL if the object couldn't be translated into a Gizmo
	OR_Gizmo*			GetOR_Gizmo( TimeValue Time);
	///\param Time the time to retrieve the light
	///\return the OR_Light taken from this node, or NULL if the object couldn't be translated into a Light
	OR_Light*			GetOR_Light( TimeValue Time);
	///\param Time the time to retrieve the camera
	///\return the OR_Camera taken from this node, or NULL if the object couldn't be translated into a Camera
	OR_Camera*			GetOR_Camera( TimeValue Time);
	///\param Time the time to retrieve the camera
	///\return the OR_Bone taken from this node, or NULL if the object couldn't be translated into a Bone
	OR_Bone*			GetOR_Bone( TimeValue Time);	
	///\param Time the time to retrieve the matrix
	///\return the absolute OR_Matrix4x4 taken from this node
	OR_Matrix4x4		GetOR_Matrix( TimeValue Time);
	///\param Time the time to retrieve the matrix
	///\return the absolute Matrix3 taken from this node
	Matrix3				GetMatrix3( TimeValue Time);
	///\param Time the time to retrieve the matrix
	///\return the offset (Node->Object) Matrix3 taken from this node
	Matrix3				GetOffsetMatrix3( TimeValue Time);
	///\param Time the time to retrieve the matrix
	///\return the offset (Node->Object) OR_Matrix4x4 taken from this node
	OR_Matrix4x4		GetOffsetOR_Matrix( TimeValue Time);
	///\param Time the time to retrieve the matrix
	///\return the OR_Matrix4x4 taken from this node, relative to its father
	OR_Matrix4x4		GetRelativeOR_Matrix( TimeValue Time);
	///\param Time the time to retrieve the matrix
	///\return the absolute Matrix3 taken from this node, relative to its father
	Matrix3				GetRelativeMatrix3( TimeValue Time);
	///\param Time the time to retrieve the node
	///\param Father the father of the tree root
	///\return the tree taken from this node (recursive). Use CNode::GetOR_Object() to fill in the node
	OR_3DS_Node&		GetNode( TimeValue Time , OR_Node* Father=NULL, OR_3DS_Node* Root = NULL );
	///\param Root a Node hierarchy corresponding to the MAX scene. This is necesary to find wich Orion3D object corresponds to each Bone
	///\return the skin taken from this node, or NULL if the object at this node is not a mesh or if it has no Skin modifier
	OR_Skin*			GetOR_Skin(TimeValue Time , T_U32Vector &LookupTable);
	///\param i the index of the UserParam to retrieve
	///\return the ith UserParam of this node, or NULL if i is invalid
	OR_3DS_UserParam*	GetUserParam(int i);
	///\return the number of UserParams at this node
	int					GetNbParam();
	///\param Name the name of the UserParam to retrieve
	///\return the UserParam of this node name Name
	OR_3DS_UserParam*	GetUserParam(char* Name);
	///Add/Replace the UserParam Param at index i for this node
	///\param Param UserParam to add
	///\param index at wich it must be added. It a param already exists at this index, replace it
	void				SetUserParam(OR_3DS_UserParam* Param, int i);
	///Add/Replace the UserParam Param  in this node
	///\param Param UserParam to add.  It a param already exists with the same name, replace it
	void				SetUserParam(OR_3DS_UserParam* Param);
	///Remove a UserParam at this node
	///\param Name name of the UserParam to remove
	///\return true if successful
	bool				RemoveUserParam(char* Name);
	///Remove a UserParam at this node
	///\param i index of the UserParam to remove
	///\return true if successful
	bool				RemoveUserParam(int i);
};



} // End namespace OR_3DS

#ifdef OR_USE_INLINE
#   include "OR_3DS_MAXNode.inl"
#endif


#endif // __OR_3DS_MAXNode_h_

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

