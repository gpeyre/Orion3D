/*------------------------------------------------------------------------------
 *  \file  OR_3DS_Utils.cpp
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-11-05
 *------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_3DS_Utils.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "stdafx.h"
#include "OR_3DS_Utils.h"

#ifndef OR_USE_INLINE
#   include "OR_3DS_Utils.inl"
#endif

namespace OR_3DS {


OR_3DS_Node*	OR_3DS_Utils::FindNode( OR_3DS_Node* Root, INode* MaxNode )
{
	if (Root->GetMAXNode()==MaxNode) return Root;
	T_NodeList &Sons = Root->GetSonList();
	for( IT_NodeList it = Sons.begin() ; it!=Sons.end() ; ++it )
	{
		OR_3DS_Node* N = FindNode( (OR_3DS_Node*)*it, MaxNode );
		if (N) return N;
	}
	return NULL;
}


/*------------------------------------------------------------------------------
 * Name : OR_3DS_Utils::FindNodeForObject
 *
 *  \param  Root EXPLANATION
 *  \param  MaxObject EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-24
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_3DS_Node* OR_3DS_Utils::FindNodeForObject( OR_3DS_Node* Root, Object* MaxObject )
{
	if( Root->GetMAXNode()->EvalWorldState(0).obj == MaxObject ) return Root;
	T_NodeList &Sons = Root->GetSonList();
	for( IT_NodeList it = Sons.begin() ; it!=Sons.end() ; ++it )
	{
		OR_3DS_Node* N = FindNodeForObject( (OR_3DS_Node*)*it, MaxObject );
		if (N) return N;
	}
	return NULL;

}


OR_Matrix4x4 OR_3DS_Utils::ToOR_Matrix(const Matrix3 & Mat)
{
	return OR_Matrix4x4(
			Mat.GetRow(0).x, Mat.GetRow(1).x, Mat.GetRow(2).x, Mat.GetRow(3).x,
			Mat.GetRow(0).y, Mat.GetRow(1).y, Mat.GetRow(2).y, Mat.GetRow(3).y,
			Mat.GetRow(0).z, Mat.GetRow(1).z, Mat.GetRow(2).z, Mat.GetRow(3).z,
			0,					0,					0,					1);
}



	
/*------------------------------------------------------------------------------
 * Name : OR_3DS_MAXNode::RetrievePositionTrack
 *
 *  \param  start EXPLANATION
 *  \param  end EXPLANATION
 *  \param  PositionController EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-15
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_AnimationTrack* OR_3DS_Utils::GetPositionTrackFromController( Control* PositionController )
{
	OR_AnimationTrack* TheTrack = NULL;

	if( !PositionController ) return NULL;
	IKeyControl *ikeys = GetKeyControlInterface(PositionController);
	if ( !ikeys ) return NULL;
	int NumKeys = ikeys->GetNumKeys();
	if ( NumKeys<= 0 ) return NULL;
		
	//Now get the controller/evaluator type of the track :
	// - Linear :
	if( PositionController->ClassID() == Class_ID(LININTERP_POSITION_CLASS_ID, 0) ) 
	{
		ILinPoint3Key linPosKey;
		TheTrack = new OR_AnimationTrack_Linear_Vector;
		//Retrieve the keys
		for (int i=0 ; i<NumKeys ; i++)
		{						
			ikeys->GetKey(i,&linPosKey);
			if (linPosKey.time < PositionController->GetTimeRange(TIMERANGE_ALL).Start()) continue;
			if (linPosKey.time > PositionController->GetTimeRange(TIMERANGE_ALL).End()) continue;
			//the time is in seconds
			OR_KeyFrame_Linear<OR_Vector3D>* Key = new OR_KeyFrame_Linear<OR_Vector3D>(linPosKey.time / 4800.,OR_Vector3D(linPosKey.val.x , linPosKey.val.y , linPosKey.val.z));
			TheTrack->AddKeyFrame(*Key); 						
		}
	}

	// - Bezier :
	else if (PositionController->ClassID() == Class_ID(HYBRIDINTERP_POSITION_CLASS_ID, 0)) 
	{
		IBezPoint3Key bezPosKey, NextbezPosKey, PrevbezPosKey;
		TheTrack = new OR_AnimationTrack_Bezier_Vector;
		for (int i=0 ; i<NumKeys ; i++)
		{
			ikeys->GetKey(i,&bezPosKey);
			if (bezPosKey.time < PositionController->GetTimeRange(TIMERANGE_ALL).Start()) continue;
			if (bezPosKey.time > PositionController->GetTimeRange(TIMERANGE_ALL).End()) continue;
			//Retrieve also the previous and the next key (if they exist)
			if (i<NumKeys-1) ikeys->GetKey(i+1,&NextbezPosKey);
			if (i>0) ikeys->GetKey(i-1,&PrevbezPosKey);
			OR_KeyFrame_Bezier<OR_Vector3D>* Key = new OR_KeyFrame_Bezier<OR_Vector3D>(bezPosKey.time / 4800.,OR_Vector3D(bezPosKey.val.x , bezPosKey.val.y , bezPosKey.val.z));
			Key->TangentLeft = new OR_Vector2D[3];
			Key->TangentRight = new OR_Vector2D[3];
			Key->Evaluator = new OR_Evaluator_1D_Bezier[3];
			//Store data and time
			if (bezPosKey.outLength == Point3(-1,-1,-1))
				bezPosKey.outLength =  Point3(1/3.,1/3.,1/3.);
			if (bezPosKey.inLength == Point3(-1,-1,-1))
				bezPosKey.inLength =  Point3(1/3.,1/3.,1/3.);
			//Now, store the bezier tangeant :
			// X = time (1 = equal to distance between this key and the newt (or previous)
			// Y = offset from this key (in real units)
			// Z = nothing (hey, these are 2D tangeants you know !)
			if (i>0) 
			{
				Key->TangentLeft[0].SetCoord( -bezPosKey.inLength.x  ,	bezPosKey.intan.x  * bezPosKey.inLength.x * (bezPosKey.time - PrevbezPosKey.time) );
				Key->TangentLeft[1].SetCoord( -bezPosKey.inLength.y  ,	bezPosKey.intan.y  * bezPosKey.inLength.y * (bezPosKey.time - PrevbezPosKey.time) );
				Key->TangentLeft[2].SetCoord( -bezPosKey.inLength.z  ,	bezPosKey.intan.z  * bezPosKey.inLength.z * (bezPosKey.time - PrevbezPosKey.time) );
			}
			else
			{
				//The first key has no left tangeant
				Key->TangentLeft[0].SetCoord( 0 , 0 );
				Key->TangentLeft[1].SetCoord( 0 , 0 );
				Key->TangentLeft[2].SetCoord( 0 , 0);
			}
			if (i<NumKeys-1)
			{
				Key->TangentRight[0].SetCoord( bezPosKey.outLength.x ,	bezPosKey.outtan.x * bezPosKey.outLength.x   * (NextbezPosKey.time - bezPosKey.time) );
				Key->TangentRight[1].SetCoord( bezPosKey.outLength.y ,	bezPosKey.outtan.y * bezPosKey.outLength.y   * (NextbezPosKey.time - bezPosKey.time) );
				Key->TangentRight[2].SetCoord( bezPosKey.outLength.z ,	bezPosKey.outtan.z * bezPosKey.outLength.z   * (NextbezPosKey.time - bezPosKey.time) );
			}
			else
			{
				//And the last key has no right tangeant
				Key->TangentRight[0].SetCoord( 0 , 0 );
				Key->TangentRight[1].SetCoord( 0 , 0 );
				Key->TangentRight[2].SetCoord( 0 , 0 );
			}
			TheTrack->AddKeyFrame(*Key);						
		}
	}/*
	// - TCB (tension, continuity, bias) :
	else if (PositionController->ClassID() == Class_ID(TCBINTERP_POSITION_CLASS_ID, 0)) 
	{
		ITCBPoint3Key tcbPosKey;
		TheTrack = new OR_AnimationTrack_TCB_Vector;
		for (int i=0 ; i<NumKeys ; i++)
		{
			ikeys->GetKey(i,&tcbPosKey);
			if (tcbPosKey.time < PositionController->GetTimeRange(TIMERANGE_ALL).Start()) continue;
			if (tcbPosKey.time > PositionController->GetTimeRange(TIMERANGE_ALL).End()) continue;
			//the time is in seconds
			OR_KeyFrame_TCB<OR_Vector3D>* Key = new OR_KeyFrame_TCB<OR_Vector3D>(tcbPosKey.time / 4800.,OR_Vector3D(tcbPosKey.val.x , tcbPosKey.val.y , tcbPosKey.val.z));
			//Now, store the TCB information :
			Key->Tension	= new float[3];Key->Tension[2]		= Key->Tension[1]		= Key->Tension[0]	= tcbPosKey.tens;
			Key->Continuity = new float[3];Key->Continuity[2]	= Key->Continuity[1]	= Key->Continuity[0]	= tcbPosKey.cont;
			Key->Bias		= new float[3];Key->Bias[2]			= Key->Bias[1]			= Key->Bias[0]		= tcbPosKey.bias;
			Key->Evaluator  = new OR_Evaluator_1D_TCB[3];
			TheTrack->AddKeyFrame(*Key);						
		}
		// initialize the evaluators
		((OR_AnimationTrack_TCB_Vector*)TheTrack)->SetUpAllEvaluators();
	}*/

	if (TheTrack) SetTrackBehavior( TheTrack, PositionController );

	return TheTrack;
}




/*------------------------------------------------------------------------------
 * Name : OR_3DS_AnimUtils::OR_AnimationTrack
 *
 *  \param  &start EXPLANATION
 *  \param  &end EXPLANATION
 *  \param  *RotationController EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-15
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_AnimationTrack*	OR_3DS_Utils::GetRotationTrackFromController( Control *RotationController )
{
	OR_AnimationTrack* TheTrack = NULL;

	if( !RotationController ) return NULL;
	IKeyControl *ikeys = GetKeyControlInterface(RotationController);
	if( !ikeys ) return NULL;
	int NumKeys = ikeys->GetNumKeys();
	if ( NumKeys<= 0 ) return NULL;
	

	if (RotationController->ClassID() == Class_ID(LININTERP_ROTATION_CLASS_ID, 0)) 
	{
		ILinRotKey linRotKey;
		TheTrack = new OR_AnimationTrack_Linear_Quaternion;
		for (int i=0 ; i<NumKeys ; i++)
		{
			ikeys->GetKey( i,&linRotKey );
			if (linRotKey.time < RotationController->GetTimeRange(TIMERANGE_ALL).Start()) continue;
			if (linRotKey.time > RotationController->GetTimeRange(TIMERANGE_ALL).End()) continue;
			OR_KeyFrame_Linear<OR_Quaternion>* Key = new OR_KeyFrame_Linear<OR_Quaternion>(linRotKey.time / 4800.,OR_Quaternion(linRotKey.val.w ,linRotKey.val.x, linRotKey.val.y, linRotKey.val.z));
			TheTrack->AddKeyFrame(*Key);
		}
	}
	else if (RotationController->ClassID() == Class_ID(HYBRIDINTERP_ROTATION_CLASS_ID, 0)) 
	{
		IBezQuatKey bezRotKey;
		TheTrack = new OR_AnimationTrack_Smooth_Quaternion;
		for( int i=0 ; i<NumKeys ; i++ )
		{
			ikeys->GetKey(i,&bezRotKey);
			if (bezRotKey.time < RotationController->GetTimeRange(TIMERANGE_ALL).Start()) continue;
			if (bezRotKey.time > RotationController->GetTimeRange(TIMERANGE_ALL).End()) continue;
			OR_KeyFrame_Smooth<OR_Quaternion>* Key = new OR_KeyFrame_Smooth<OR_Quaternion>(bezRotKey.time / 4800.,OR_Quaternion(bezRotKey.val.w ,bezRotKey.val.x, bezRotKey.val.y, bezRotKey.val.z));
			TheTrack->AddKeyFrame(*Key);
		}
	}/*
	else if (RotationController->ClassID() == Class_ID(TCBINTERP_ROTATION_CLASS_ID, 0)) 
	{
		ITCBRotKey tcbRotKey;
		TheTrack->EvaluatorType = OR_ANIMATION_Evaluator_TCB;				
		TheTrack->Keys = new OR_ExportHeader_Keyframe*[NumKeys];
		TheTrack->KeySize = sizeof(OR_ExportHeader_Keyframe_TCB_Quaternion);
		for (int i=0 ; i<NumKeys ; i++)
		{
			ikeys->GetKey(i,&tcbRotKey);
			OR_ExportHeader_Keyframe_TCB_Quaternion* KeyFrame = new OR_ExportHeader_Keyframe_TCB_Quaternion;
			KeyFrame->Data = OR_Quaternion(Quat(tcbRotKey.val).w , Quat(tcbRotKey.val).x , Quat(tcbRotKey.val).y, Quat(tcbRotKey.val).z);
			//if (i) KeyFrame->Data = ((OR_ExportHeader_Keyframe_TCB_Quaternion*)TheTrack->Keys[i-1])->Data * KeyFrame->Data;
			KeyFrame->Time = tcbRotKey.time / 4800.;
			KeyFrame->Tension	= tcbRotKey.tens;
			KeyFrame->Continuity= tcbRotKey.cont;
			KeyFrame->Bias		= tcbRotKey.bias;
			TheTrack->Keys[i] = KeyFrame;
		}
	}
*/

	if( TheTrack ) SetTrackBehavior( TheTrack, RotationController );

	return TheTrack;
}




/*------------------------------------------------------------------------------
 * Name : OR_3DS_Utils::GetScaleTrackFromController
 *
 *  \param  *RotationController EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-06
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_AnimationTrack* OR_3DS_Utils::GetScaleTrackFromController( Control *ScaleController )
{
	OR_AnimationTrack* TheTrack = NULL;

	IKeyControl *ikeys = GetKeyControlInterface(ScaleController);
	if( !ikeys ) return NULL;
	int NumKeys = ikeys->GetNumKeys();
	if ( NumKeys<= 0 ) return NULL;
		
	if (ScaleController->ClassID() == Class_ID(LININTERP_SCALE_CLASS_ID, 0)) 
	{
		ILinScaleKey linScaleKey;
		TheTrack = new OR_AnimationTrack_Linear_Vector;
		for (int i=0 ; i<NumKeys ; i++)
		{
			ikeys->GetKey( i, &linScaleKey );
			if (linScaleKey.time < ScaleController->GetTimeRange(TIMERANGE_ALL).Start()) continue;
			if (linScaleKey.time > ScaleController->GetTimeRange(TIMERANGE_ALL).End()) continue;
			OR_KeyFrame_Linear<OR_Vector3D>* Key = new OR_KeyFrame_Linear<OR_Vector3D>(linScaleKey.time / 4800.,OR_Vector3D(linScaleKey.val.s.x , linScaleKey.val.s.y , linScaleKey.val.s.z));
			TheTrack->AddKeyFrame( *Key );
		}
	}
	else if (ScaleController->ClassID() == Class_ID(HYBRIDINTERP_SCALE_CLASS_ID, 0)) 
	{
		IBezScaleKey bezScaleKey, PrevbezScaleKey, NextbezScaleKey;
		TheTrack = new OR_AnimationTrack_Bezier_Vector;
		for (int i=0 ; i<NumKeys ; i++)
		{
			ikeys->GetKey( i, &bezScaleKey );
			if (bezScaleKey.time < ScaleController->GetTimeRange(TIMERANGE_ALL).Start()) continue;
			if (bezScaleKey.time > ScaleController->GetTimeRange(TIMERANGE_ALL).End()) continue;

			if (i<NumKeys-1) ikeys->GetKey(i+1,&NextbezScaleKey);
			if (i>0) ikeys->GetKey(i-1,&PrevbezScaleKey);
			OR_KeyFrame_Bezier<OR_Vector3D>* Key = new OR_KeyFrame_Bezier<OR_Vector3D>(bezScaleKey.time / 4800.,OR_Vector3D(bezScaleKey.val.s.x , bezScaleKey.val.s.y , bezScaleKey.val.s.z));
			Key->TangentLeft = new OR_Vector2D[3];
			Key->TangentRight = new OR_Vector2D[3];
			Key->Evaluator = new OR_Evaluator_1D_Bezier[3];

			if (bezScaleKey.outLength == Point3(-1,-1,-1))
				bezScaleKey.outLength =  Point3(1/3.,1/3.,1/3.);
			if (bezScaleKey.inLength == Point3(-1,-1,-1))
				bezScaleKey.inLength =  Point3(1/3.,1/3.,1/3.);
			if (i>0) 
			{
				Key->TangentLeft[0].SetCoord( -bezScaleKey.inLength.x  ,	bezScaleKey.intan.x  * bezScaleKey.inLength.x * (bezScaleKey.time - PrevbezScaleKey.time) );
				Key->TangentLeft[1].SetCoord( -bezScaleKey.inLength.y  ,	bezScaleKey.intan.y  * bezScaleKey.inLength.y * (bezScaleKey.time - PrevbezScaleKey.time) );
				Key->TangentLeft[2].SetCoord( -bezScaleKey.inLength.z  ,	bezScaleKey.intan.z  * bezScaleKey.inLength.z * (bezScaleKey.time - PrevbezScaleKey.time) );
			}
			else
			{
				Key->TangentLeft[0].SetCoord( 0 , 0 );
				Key->TangentLeft[1].SetCoord( 0 , 0 );
				Key->TangentLeft[2].SetCoord( 0 , 0 );
			}
			if (i<NumKeys-1)
			{
				Key->TangentRight[0].SetCoord( bezScaleKey.outLength.x ,	bezScaleKey.outtan.x * bezScaleKey.outLength.x   * (NextbezScaleKey.time - bezScaleKey.time) );
				Key->TangentRight[1].SetCoord( bezScaleKey.outLength.y ,	bezScaleKey.outtan.y * bezScaleKey.outLength.y   * (NextbezScaleKey.time - bezScaleKey.time) );
				Key->TangentRight[2].SetCoord( bezScaleKey.outLength.z ,	bezScaleKey.outtan.z * bezScaleKey.outLength.z   * (NextbezScaleKey.time - bezScaleKey.time) );
			}
			else
			{
				Key->TangentRight[0].SetCoord( 0 , 0 );
				Key->TangentRight[1].SetCoord( 0 , 0 );
				Key->TangentRight[2].SetCoord( 0 , 0 );
			}
			TheTrack->AddKeyFrame( *Key );
		}
	}/*
	else if (ScaleController->ClassID() == Class_ID(TCBINTERP_SCALE_CLASS_ID, 0)) 
	{
		ITCBScaleKey tcbScaleKey;
		TheTrack->EvaluatorType = OR_ANIMATION_Evaluator_TCB;				
		TheTrack->Keys = new OR_ExportHeader_Keyframe*[NumKeys];
		TheTrack->KeySize = sizeof(OR_ExportHeader_Keyframe_TCB_Vector);
		for (int i=0 ; i<NumKeys ; i++)
		{
			ikeys->GetKey(i,&tcbScaleKey);
			OR_ExportHeader_Keyframe_TCB_Vector* KeyFrame = new OR_ExportHeader_Keyframe_TCB_Vector;
			KeyFrame->Data		= OR_Vector3D(tcbScaleKey.val.s.x , tcbScaleKey.val.s.y , tcbScaleKey.val.s.z);
			KeyFrame->Time		= tcbScaleKey.time / 4800.;
			KeyFrame->Tension	= tcbScaleKey.tens;
			KeyFrame->Continuity= tcbScaleKey.cont;
			KeyFrame->Bias		= tcbScaleKey.bias;
			TheTrack->Keys[i]	= KeyFrame;
		}
	}
*/
	if( TheTrack ) SetTrackBehavior( TheTrack, ScaleController );

	return TheTrack;

}



/*------------------------------------------------------------------------------
 * Name : OR_3DS_Utils::GetFloatTrackFromController
 *
 *  \param  *FloatController EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-06
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_AnimationTrack* OR_3DS_Utils::GetFloatTrackFromController( Control *FloatController )
{
	OR_AnimationTrack* TheTrack = NULL;

	if( !FloatController ) return NULL;
	IKeyControl *ikeys = GetKeyControlInterface( FloatController );
	if( !ikeys ) return NULL;
	int NumKeys = ikeys->GetNumKeys();
	if( NumKeys<= 0 ) return NULL;

	if( FloatController->ClassID() == Class_ID( LININTERP_FLOAT_CLASS_ID, 0 ) ) 
	{
		ILinFloatKey linFloatKey;
		TheTrack = new OR_AnimationTrack_Linear_Float;
		for( int i=0 ; i<NumKeys ; i++ )
		{
			ikeys->GetKey( i, &linFloatKey );
			if( linFloatKey.time < FloatController->GetTimeRange(TIMERANGE_ALL).Start() ) continue;
			if( linFloatKey.time > FloatController->GetTimeRange(TIMERANGE_ALL).End() ) continue;
			OR_KeyFrame_Linear<OR_Float>* Key = new OR_KeyFrame_Linear<OR_Float>( linFloatKey.time / 4800., linFloatKey.val );
			TheTrack->AddKeyFrame( *Key );
		}
	}
	else if( FloatController->ClassID() == Class_ID( HYBRIDINTERP_FLOAT_CLASS_ID, 0 ) ) 
	{
		IBezFloatKey bezFloatKey;
		TheTrack = new OR_AnimationTrack_Bezier_Float;
		for( int i=0 ; i<NumKeys ; i++ )
		{
			ikeys->GetKey( i, &bezFloatKey );
			if( bezFloatKey.time < FloatController->GetTimeRange( TIMERANGE_ALL ).Start() ) continue;
			if( bezFloatKey.time > FloatController->GetTimeRange( TIMERANGE_ALL ).End() ) continue;
			OR_KeyFrame_Bezier<OR_Float>* Key = new OR_KeyFrame_Bezier<OR_Float>( bezFloatKey.time / 4800., bezFloatKey.val );
			TheTrack->AddKeyFrame( *Key );
		}
	}

	if( TheTrack ) SetTrackBehavior( TheTrack, FloatController );

	return TheTrack;
}




void OR_3DS_Utils::MakeVector3DTrackRelative( OR_AnimationTrack* Track, OR_Matrix4x4 BaseMatrix )
{
	OR_Matrix4x4	InvertBaseMatrix = BaseMatrix.Invert();
	OR_KeyFrame_Linear<OR_Vector3D>*	LinearKey = NULL;
	OR_KeyFrame_Bezier<OR_Vector3D>*	BezierKey = NULL, *NextBezierKey = NULL;
	OR_KeyFrame_TCB<OR_Vector3D>*		TCBKey = NULL;
	OR_KeyFrame_Constant<OR_Vector3D>*	ConstantKey = NULL;
	IT_KeyFrameList			Iterator, Next_Iterator;
	T_KeyFrameList&			Keyframes = Track->GetKeyframeList();

	switch( Track->GetEvaluatorType() )
	{
	case OR_ANIMATION_Evaluator_Constant:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			ConstantKey = (OR_KeyFrame_Constant<OR_Vector3D>*)(*Iterator);
			ConstantKey->Data = InvertBaseMatrix * ConstantKey->Data;		
		}
		break;
		
	case OR_ANIMATION_Evaluator_TCB:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			TCBKey = (OR_KeyFrame_TCB<OR_Vector3D>*)(*Iterator);
			TCBKey->Data = InvertBaseMatrix * TCBKey->Data;		
		}
		break;
		
	case OR_ANIMATION_Evaluator_Linear:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			LinearKey = (OR_KeyFrame_Linear<OR_Vector3D>*)(*Iterator);
			LinearKey->Data = InvertBaseMatrix * LinearKey->Data;		
		}
		break;
		
	case OR_ANIMATION_Evaluator_Bezier:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			BezierKey = (OR_KeyFrame_Bezier<OR_Vector3D>*)*Iterator;
			BezierKey->Data = InvertBaseMatrix * BezierKey->Data;		
		}
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			Next_Iterator = Iterator; ++Next_Iterator;
			if( Next_Iterator == Keyframes.end() ) Next_Iterator = Keyframes.begin();
			BezierKey = (OR_KeyFrame_Bezier<OR_Vector3D>*)*Iterator;
			NextBezierKey = (OR_KeyFrame_Bezier<OR_Vector3D>*)*Next_Iterator;

			//HERE WE MAKE THE TANGEANTS RELATIVE TO FRAME 0
			OR_Vector3D v, v1, v2;
			// v  = 1st control point, in absolute coords (corresponds to P0)
			v = BaseMatrix * BezierKey->Data;
			// v1 = 2nd control point, in absolute coords (corresponds to P1)
			v1 = OR_Vector3D(v[0]+BezierKey->TangentRight[0][Y],  
							 v[1]+BezierKey->TangentRight[1][Y], 
							 v[2]+BezierKey->TangentRight[2][Y]);
			// now, v1 = 2nd control point relative to frame 0 (correspond to P1) :
			v1= InvertBaseMatrix  * v1;

			// v  = 4th control point, in absolute coords (corresponds to P3)
			v = BaseMatrix * NextBezierKey->Data;
			// now, v2 = 3rd control point, in absolute coords (correspond to P2) :
			v2 = OR_Vector3D(v[0]+NextBezierKey->TangentLeft[0][Y],  
							 v[1]+NextBezierKey->TangentLeft[1][Y], 
							 v[2]+NextBezierKey->TangentLeft[2][Y]);
			// now, v2 = 3rd control point relative to frame 0 (correspond to P2) :
			v2= InvertBaseMatrix  * v2;

			/* compute the relative tangeants (relative to frame 0) 
			   it's just the reverse calculation of v1 & v2 */						
			BezierKey->TangentRight[0][Y]=v1[X] - BezierKey->Data[0];
			BezierKey->TangentRight[1][Y]=v1[Y] - BezierKey->Data[1];
			BezierKey->TangentRight[2][Y]=v1[Z] - BezierKey->Data[2];
			NextBezierKey->TangentLeft[0][Y]=v2[X] - NextBezierKey->Data[0];
			NextBezierKey->TangentLeft[1][Y]=v2[Y] - NextBezierKey->Data[1];
			NextBezierKey->TangentLeft[2][Y]=v2[Z] - NextBezierKey->Data[2];

		}
		((OR_AnimationTrack_Bezier_Vector*)Track)->SetUpAllEvaluators();
		break;
		
		default:
		break;
	}
}

void OR_3DS_Utils::MakeVector3DTrackRelative( OR_AnimationTrack* Track, OR_Vector3D BaseVector )
{
	OR_KeyFrame_Linear<OR_Vector3D>*	LinearKey = NULL;
	OR_KeyFrame_Bezier<OR_Vector3D>*	BezierKey = NULL, *NextBezierKey = NULL;
	OR_KeyFrame_TCB<OR_Vector3D>*		TCBKey = NULL;
	OR_KeyFrame_Constant<OR_Vector3D>*	ConstantKey = NULL;
	IT_KeyFrameList			Iterator, Next_Iterator;
	T_KeyFrameList&			Keyframes = Track->GetKeyframeList();

	switch( Track->GetEvaluatorType() )
	{
	case OR_ANIMATION_Evaluator_Constant:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			ConstantKey = (OR_KeyFrame_Constant<OR_Vector3D>*)(*Iterator);
			ConstantKey->Data = ConstantKey->Data - BaseVector;		
		}
		break;
		
	case OR_ANIMATION_Evaluator_TCB:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			TCBKey = (OR_KeyFrame_TCB<OR_Vector3D>*)(*Iterator);
			TCBKey->Data = TCBKey->Data - BaseVector;
		}
		break;
		
	case OR_ANIMATION_Evaluator_Linear:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			LinearKey = (OR_KeyFrame_Linear<OR_Vector3D>*)(*Iterator);
			LinearKey->Data = LinearKey->Data - BaseVector;
		}
		break;
		
	case OR_ANIMATION_Evaluator_Bezier:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			BezierKey = (OR_KeyFrame_Bezier<OR_Vector3D>*)*Iterator;
			BezierKey->Data = BezierKey->Data - BaseVector;
		}
		((OR_AnimationTrack_Bezier_Vector*)Track)->SetUpAllEvaluators();
		break;
		
		default:
		break;
	}
}


void OR_3DS_Utils::MakeQuaternionTrackRelative( OR_AnimationTrack* Track, OR_Quaternion BaseQuat )
{
	OR_KeyFrame_Linear<OR_Quaternion>*		LinearKey = NULL;
	OR_KeyFrame_Smooth<OR_Quaternion>*		SmoothKey = NULL;
	OR_KeyFrame_Constant<OR_Quaternion>*	ConstantKey = NULL;
	IT_KeyFrameList			Iterator;
	T_KeyFrameList&			Keyframes = Track->GetKeyframeList();
	OR_Quaternion			InvertBaseQuat = ~BaseQuat;

	switch( Track->GetEvaluatorType() )
	{
	case OR_ANIMATION_Evaluator_Constant:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			ConstantKey = (OR_KeyFrame_Constant<OR_Quaternion>*)(*Iterator);
			ConstantKey->Data = ConstantKey->Data * InvertBaseQuat;		
		}
		break;
		
	case OR_ANIMATION_Evaluator_Linear:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			LinearKey = (OR_KeyFrame_Linear<OR_Quaternion>*)(*Iterator);
			LinearKey->Data = LinearKey->Data * InvertBaseQuat;
		}
		break;
		
	case OR_ANIMATION_Evaluator_Smooth:
		for( Iterator = Keyframes.begin() ; Iterator != Keyframes.end() ; ++Iterator )
		{
			SmoothKey = (OR_KeyFrame_Smooth<OR_Quaternion>*)*Iterator;
			SmoothKey->Data = SmoothKey->Data * InvertBaseQuat;
		}
		break;
		
		default:
		break;
	}

}


/*------------------------------------------------------------------------------
 * Name : OR_3DS_AnimUtils::SetTrackBehavior		
 *
 *  \param  TheTrack EXPLANATION
 *  \param  *Controller EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-15
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
void	OR_3DS_Utils::SetTrackBehavior( OR_AnimationTrack* TheTrack, Control *Controller )
{
	if( !TheTrack ) return;
	if( !Controller )
	{
		TheTrack->SetBehaviour( OR_ANIMATION_Behavior_Constant, OR_ANIMATION_Behavior_Constant );
		return;
	}

	//ORT = Out of Range Type
	switch( Controller->GetORT(ORT_AFTER) )
	{
	case ORT_CONSTANT:
		TheTrack->SetBehaviourAfter(OR_ANIMATION_Behavior_Constant);
		break;
	case ORT_OSCILLATE:
		TheTrack->SetBehaviourAfter(OR_ANIMATION_Behavior_PingPong);
		break;
	case ORT_CYCLE:
	case ORT_LOOP:
		TheTrack->SetBehaviourAfter(OR_ANIMATION_Behavior_Loop);
		break;
	case ORT_RELATIVE_REPEAT:
		TheTrack->SetBehaviourAfter(OR_ANIMATION_Behavior_RelativeLoop);
		break;
	default:
		TheTrack->SetBehaviourAfter(OR_ANIMATION_Behavior_Undefined);
		break;
	}
	switch(Controller->GetORT(ORT_BEFORE))
	{
	case ORT_CONSTANT:
		TheTrack->SetBehaviourBefore(OR_ANIMATION_Behavior_Constant);
		break;
	case ORT_OSCILLATE:
		TheTrack->SetBehaviourBefore(OR_ANIMATION_Behavior_PingPong);
		break;
	case ORT_CYCLE:
	case ORT_LOOP:
		TheTrack->SetBehaviourBefore(OR_ANIMATION_Behavior_Loop);
		break;
	case ORT_RELATIVE_REPEAT:
		TheTrack->SetBehaviourBefore(OR_ANIMATION_Behavior_RelativeLoop);
		break;
	default:
		TheTrack->SetBehaviourBefore(OR_ANIMATION_Behavior_Undefined);
		break;
	}

}



/*------------------------------------------------------------------------------
 * Name : OR_3DS_Utils::InitMultiShaderFromMesh
 *
 *  \param  MultiShader EXPLANATION
 *  \param  Mesh EXPLANATION
 *  \param  Map EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-27
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
void OR_3DS_Utils::InitMultiShaderFromMesh( OR_MultiShader* MultiShader, MultiMtl* MaxMtl, Mesh* TheMesh, const T_MaxToOrionMtlMap& Map )
{
	OR_ASSERT( MultiShader != NULL );
	OR_ASSERT( TheMesh != NULL );

	OR_U32 i;
	OR_U32 NbrMaxSubMtl = MaxMtl->NumSubMtls();
	OR_U32 NbrFaces = TheMesh->getNumFaces();

	for( i=0 ; i<NbrMaxSubMtl ; ++i )
	{
		CIT_MaxToOrionMtlMap itOrionSubMtl = Map.find( MaxMtl->GetSubMtl( i ) );
		OR_ASSERT( itOrionSubMtl != Map.end() );
		OR_Shader* OrionSubMtl = (*itOrionSubMtl).second;

		T_U32Vector& Indices = MultiShader->GetIndicesForShader( OrionSubMtl );

		for( OR_U32 j=0 ; j<NbrFaces ; ++j )
		{
			if( TheMesh->getFaceMtlIndex( j ) == i )
			{
				Indices.push_back( TheMesh->faces[j].v[0] );
				Indices.push_back( TheMesh->faces[j].v[1] );
				Indices.push_back( TheMesh->faces[j].v[2] );
			}
		}	
		if( Indices.size() == 0 ) 
		{
			MultiShader->RemoveShader( OrionSubMtl );
		}
	}
}



} // End namespace OR_3DS




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

