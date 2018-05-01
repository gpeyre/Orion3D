/** \file 
	Contains classes used to retrieve animation information from 3DSMAX classes
	\author Antoche
**/

#ifndef _OR_3DS_ANIMUTILS_H_
#define _OR_3DS_ANIMUTILS_H_

#include "stdafx.h"
#include "OR_3DS_Node.h"

using namespace OR;

using std::vector;
using std::map;

namespace OR_3DS {

typedef map<INode*,OR_U32> T_INodeMap;
typedef T_INodeMap::iterator IT_INodeMap;

typedef map<MtlBase*,OR_Shader*> T_MaxToOrionMtlMap;
typedef T_MaxToOrionMtlMap::iterator IT_MaxToOrionMtlMap;
typedef T_MaxToOrionMtlMap::const_iterator CIT_MaxToOrionMtlMap;

///A table of SingleFace
typedef vector<OR_SingleFace ,	allocator<OR_SingleFace> >	OR_SingleFace_vector;

/*
///A class that call a function when 3DSMAX time change
class CTimeCallback:public TimeChangeCallback 
{
public:
	///If Call is true, func will be called when time change
	bool Call;
	///The function to call at exit
	void (*func)(TimeValue t);
	///Function callled by 3DSMAX when it exits
	virtual void TimeChanged(TimeValue t) 
	{
		if(Call && func) 
			func(t);
	}
	///Constructor. Initialize func and Plugin to NULL
	CTimeCallback() {Call=false;func=NULL;}
};*/


class OR_3DS_Utils
{
public:
	///\param Root the point to start search
	///\param MaxNode the node to search
	///\return the Orion3D Node corresponding to MaxNode (recursive)
	static OR_3DS_Node*	FindNode(OR_3DS_Node* Root, INode* MaxNode);
	static OR_3DS_Node*	FindNodeForObject(OR_3DS_Node* Root, Object* MaxObject);
	static OR_Matrix4x4 ToOR_Matrix(const Matrix3 & Mat);

	static OR_AnimationTrack*	GetPositionTrackFromController( Control* PositionController );
	static OR_AnimationTrack*	GetRotationTrackFromController( Control *RotationController );
	static OR_AnimationTrack*	GetScaleTrackFromController( Control *ScaleController );
	static OR_AnimationTrack*	GetFloatTrackFromController( Control *FloatController );

	static void MakeVector3DTrackRelative( OR_AnimationTrack* Track, OR_Matrix4x4 BaseMatrix );
	static void MakeVector3DTrackRelative( OR_AnimationTrack* Track, OR_Vector3D BaseVector );
	static void MakeQuaternionTrackRelative( OR_AnimationTrack* Track, OR_Quaternion BaseQuat );
	static void SetTrackBehavior( OR_AnimationTrack* TheTrack, Control *Controller );

	static void InitMultiShaderFromMesh( OR_MultiShader* MultiShader, MultiMtl* MaxMtl, Mesh* TheMesh, const T_MaxToOrionMtlMap& Map );
};


} // End namespace OR_3DS


#endif //_OR_3DS_ANIMUTILS_H_