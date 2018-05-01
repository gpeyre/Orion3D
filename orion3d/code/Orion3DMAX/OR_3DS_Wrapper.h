#ifndef _OR_3DS_WRAPPER_H_
#define _OR_3DS_WRAPPER_H_

#include "stdafx.h"
#include "./OR_3DS.h"

using namespace OR_3DS;

#define	OR_Update_Matrices	 0x01
#define	OR_Update_Targets	 0x02
#define	OR_Apply_Shaders	 0x04
#define	OR_Update_Hierarchy	 0x08
#define	OR_Update_Materials	 0x10
#define	OR_Update_Animations 0x20
#define	OR_Update_Everything 0xFF
const OR_U32 OR_Update_Objects = OR_Update_Hierarchy | OR_Update_Targets;
const OR_U32 OR_Update_Shaders = OR_Update_Materials | OR_Apply_Shaders;


class OR_3DSWrapper
{
private:

	OR_Toolkit*	Engine;
	IUtil*		IUtility;
	Interface*	MAXInterface;
	TimeValue	Time;
	T_MaxToOrionMtlMap MaxToOrionMtlMap;
	OR_I32		SamplingRate;
	OR_Float	SamplingTreshold;
	OR_Bool		SamplingForce;
	OR_I32		SamplingStart;
	OR_I32		SamplingEnd;

	///Retrieve the Orion3D tree from the 3DSMAX tree starting from RootNode
	OR_3DS_Node*	RetrieveNode_Rec( INode* RootNode, OR_Node* Father = NULL, OR_3DS_Node* Root = NULL );
	///Update the matrices of the Orion3D tree starting from curnode with data from 3DSMAX
	void	UpdateMatrices_Rec(OR_3DS_Node* curnode);
	///Erase all the shaders and retrieve new Orion3D shaders from 3DSMAX materials
	void	RetrieveSceneMaterials();
	OR_Shader*	RetrieveMaterial( MtlBase* MaxMtl );
	///Resolve all targets from curnode (recursive)
	void	UpdateTargets(OR_3DS_Node* curnode, OR_3DS_Node* Root);
	///Set the Orion3D shaders to the meshes starting from curnode (recursive)
	void	ApplyShader(OR_3DS_Node* curnode);
	void	ApplyShaders_Rec( OR_3DS_Node* Root );

public:
	OR_3DSWrapper(IUtil* iu=NULL , Interface* ip=NULL , OR_Toolkit* Engine=NULL);
	~OR_3DSWrapper();
	OR_3DS_Node*	Update(int Flags, OR_3DS_Node* Root=NULL);
	void			CopyTextures( const OR_String BaseRep );
	void	SetIUtil(IUtil* iu);
	void	SetInterface(Interface* ip);
	void	SetTime(TimeValue Time);
	void	SetEngine(OR_Toolkit* Engine);

	void	SetSamplingRate( const OR_I32& Rate )			{ SamplingRate = Rate; }
	void	SetSamplingTreshold( const OR_Float& Treshold )	{ SamplingTreshold = Treshold; }
	void	SetSamplingStart( const OR_I32& Start )		{ SamplingStart = Start; }
	void	SetSamplingEnd( const OR_I32& End )			{ SamplingEnd = End; }
	void	SetSamplingForce( const OR_Bool& Force )		{ SamplingForce = Force; }

	const OR_Bool& GetSamplingForce() const		{ return SamplingForce; }
	const OR_I32& GetSamplingRate() const		{ return SamplingRate; }
	const OR_Float& GetSamplingTreshold() const	{ return SamplingTreshold; }
	const OR_I32& GetSamplingStart() const		{ return SamplingStart; }
	const OR_I32& GetSamplingEnd() const		{ return SamplingEnd; }

};






#endif //_OR_3DS_WRAPPER_H_