/*-------------------------------------------------------------------*/
/*                           OR_AnimationTrack.cpp                   */
/*-------------------------------------------------------------------*/
/* definition of a animations track                                  */
/*-------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_AnimationTrack.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_AnimationTrack.h"

#ifndef OR_USE_INLINE
	#include "OR_AnimationTrack.inl"
#endif

namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                      class OR_AnimationTrack                      */
/*-------------------------------------------------------------------*/
/* super class for all track                                         */
/*-------------------------------------------------------------------*/

void OR_AnimationTrack::FindKeyframe(OR_Float &time, OR_KeyFrame* & key1, OR_KeyFrame* & key2, IT_KeyFrameList& last_it)
{
	OR_Float start_t=KeyframeList_.front()->GetTime();
	OR_Float end_t  =KeyframeList_.back()->GetTime();
	OR_I32 number=0;

	/* set up correct time */
	if( time < start_t)
	{
		switch (BehaviourBefore_)
		{
		case OR_ANIMATION_Behavior_Constant:
			key1=key2=KeyframeList_.front();
			return;
			break;
		case OR_ANIMATION_Behavior_Loop:
			/* compute correct time */
			while (time<start_t)
			{ time+=end_t-start_t; }
			break;
		case OR_ANIMATION_Behavior_PingPong:
			/* compute correct time */
			while (time<start_t)
			{ time+=end_t-start_t; number++; }
			/* if the number of decalage is not pair, symetrize the time */
			if( (number%2) != 0 ) time = start_t + end_t - time;
			break;
		case OR_ANIMATION_Behavior_RelativeLoop:
		default:
			OR_Globals::MessageHandler()->Warning("OR_AnimationTrack::FindKeyframe",
				"The behaviour %i is not supported.", BehaviourBefore_);
			/* to prevent program from crashing */
			key1=key2=KeyframeList_.front();
			return;
			break;
		}
	}
	else if( time >= end_t )
	{
		switch (BehaviourBefore_)
		{
		case OR_ANIMATION_Behavior_Constant:
			key1=key2=KeyframeList_.back();
			return;
			break;
		case OR_ANIMATION_Behavior_Loop:
			/* compute correct time */
			while (time>=end_t)
			{ time-=end_t-start_t; }
			break;
		case OR_ANIMATION_Behavior_PingPong:
			/* compute correct time */
			while (time>end_t)
			{ time-=end_t-start_t; number++; }
			/* if the number of decalage is pair, new_t is ok */
			if ( (number%2) != 0) time = start_t + end_t - time;
			break;
		case OR_ANIMATION_Behavior_RelativeLoop:
		default:
			OR_Globals::MessageHandler()->Warning("OR_AnimationTrack::FindKeyframe",
				"The behaviour %i is not supported.", BehaviourBefore_);
			/* to prevent program from crashing */
			key1=key2=KeyframeList_.front();
			return;
			break;
		}
	}

	/* find the two key */
	for(IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
	{
		OR_KeyFrame* pKey = *it;
		OR_KeyFrame* pNextKey=NULL;
	
		IT_KeyFrameList it_next(it);
		it_next++;

		if( (it_next)!=KeyframeList_.end() )
			pNextKey=*(it_next);
		
		if ( (pKey->GetTime()<=time) && pNextKey!=NULL && (pNextKey->GetTime()>time) )
		{
			/* the key has been found ! */
			key1=pKey;
			key2=pNextKey;
			return;
		}
	}
	
	/* to prevent program from crashing */
	key1=KeyframeList_.front();
	key2=KeyframeList_.front();
	OR_Globals::MessageHandler()->Warning("OR_AnimationTrack::FindKeyframe", "The track is not correct.");
}

/* serialization methods ***************************************/
void OR_AnimationTrack::BuildFromFile( OR_File& file )
{
	file >> Target_
		 >> rLength_
		 >> BehaviourBefore_
		 >> BehaviourAfter_;
	/* import of the key is made by the derived class */
}

void OR_AnimationTrack::BuildToFile( OR_File& file )
{
	file << Target_
		 << rLength_
		 << BehaviourBefore_
		 << BehaviourAfter_;
	/* export the number of keys */
	OR_I32 nb=KeyframeList_.size();
	file << nb;
	/* export recursivly the key */
	for(IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
	{
		file << *it;
	}
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationTrack::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_AnimationTrack::BuildSonList(T_ShellObjectList& ShellSonList)
{
	OR_U32 nCpt = 0;

	for(IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
	{
		OR_KeyFrame* pKey = *it;
		OR_ADD_SHELL_SON(ShellSonList, *pKey, OR_String("keyframe_") + nCpt );
		nCpt++;
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationTrack::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_AnimationTrack::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Length);
}




/* linear track ***************************************************************************************/
/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Linear_Float                 */
/*-------------------------------------------------------------------*/
/* linear tracks                                                     */
/*-------------------------------------------------------------------*/

void OR_AnimationTrack_Linear_Float::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_Linear<OR_Float> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());

	/* value at current time */
	OR_Float data;

	/* compute the data : linear interpolation */
	OR_Float t1=key1->GetTime();
	OR_Float t2=key2->GetTime();
	OR_Float coef=0;
	if(fabs(t2-t1)>OR_EPSILON) coef=(time-t1)/(t2-t1);
	data= key1->Data * ( 1-coef )
	    + key2->Data * coef;

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_PosX:
		object->TranslateAnimation(X, data);
		break;
	case OR_ANIMATION_Target_PosY:
		object->TranslateAnimation(Y, data);
		break;
	case OR_ANIMATION_Target_PosZ:
		object->TranslateAnimation(Z, data);
		break;
	case OR_ANIMATION_Target_ScaleX:
		object->ScaleAnimation(X, data);
		break;
	case OR_ANIMATION_Target_ScaleY:
		object->ScaleAnimation(Y, data);
		break;
	case OR_ANIMATION_Target_ScaleZ:
		object->ScaleAnimation(Z, data);
		break;
	case OR_ANIMATION_Target_AmbientR:
		object->SetAmbient(R, data);
		break;
	case OR_ANIMATION_Target_AmbientV:
		object->SetAmbient(V, data);
		break;
	case OR_ANIMATION_Target_AmbientB:
		object->SetAmbient(B, data);
		break;
	case OR_ANIMATION_Target_DiffuseR:
		object->SetDiffuse(R, data);
		break;
	case OR_ANIMATION_Target_DiffuseV:
		object->SetDiffuse(V, data);
		break;
	case OR_ANIMATION_Target_DiffuseB:
		object->SetDiffuse(B, data);
		break;
	case OR_ANIMATION_Target_SpecularR:
		object->SetSpecular(R, data);
		break;
	case OR_ANIMATION_Target_SpecularV:
		object->SetSpecular(V, data);
		break;
	case OR_ANIMATION_Target_SpecularB:
		object->SetSpecular(B, data);
		break;
	case OR_ANIMATION_Target_Shine:
		object->SetShine(data);
		break;
	case OR_ANIMATION_Target_Display:
		object->SetVisible( data>0 );
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Float::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}


/* serialization methods ***************************************/
void OR_AnimationTrack_Linear_Float::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;
	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Linear<OR_Float> *key=new OR_KeyFrame_Linear<OR_Float>(0,0);
		file >> key;
		KeyframeList_.push_back(key);
	}
}

/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Linear_Vector                */
/*-------------------------------------------------------------------*/
/* linear tracks                                                     */
/*-------------------------------------------------------------------*/

void OR_AnimationTrack_Linear_Vector::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_Linear<OR_Vector3D> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());
	/* value at current time */
	OR_Vector3D data;

	/* compute the data : linear interpolation */
	OR_Float t1=key1->GetTime();
	OR_Float t2=key2->GetTime();

	OR_Float coef=0;
	if(fabs(t2-t1)>OR_EPSILON) coef=(time-t1)/(t2-t1);

	data= key1->Data * ( 1-coef )
		+ key2->Data * coef;

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_Pos:
		object->TranslateAnimation(data);
		break;
	case OR_ANIMATION_Target_Scale:
		object->ScaleAnimation(data);
		break;
	case OR_ANIMATION_Target_Ambient:
		object->SetAmbient(data);
		break;
	case OR_ANIMATION_Target_Diffuse:
		object->SetDiffuse(data);
		break;
	case OR_ANIMATION_Target_Specular:
		object->SetSpecular(data);
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Vector::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}

void OR_AnimationTrack_Linear_Vector::DrawTrajectory(OR_Object* object)
{
glPushMatrix();
	OR_Matrix4x4 Mat = ( ~(object->GetOldAnimationMatrix() )*object->GetAbsoluteMatrix() );
	OR_Maths::MultiplyCurrentModelView( Mat );
	OR_Globals::Context()->SimpleDrawMode();
	OR_Globals::Context()->SetPointSize(5);
	
	/** display each key */
	OR_Vector3D pos=((OR_KeyFrame_Linear<OR_Vector3D>*) KeyframeList_.front())->Data;
	/* draw first point */
	OR_Globals::Context()->SetColor(1,1,1);
	glBegin(GL_POINT);
		glVertex3fv(pos.GetCoord());
	glEnd();
		
	for(IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
	{
		OR_KeyFrame_Linear<OR_Vector3D>* pKey = (OR_KeyFrame_Linear<OR_Vector3D>*) *it;
		OR_Globals::Context()->SetColor(1,1,0);
		glBegin(GL_LINES);
			glVertex3fv(pos.GetCoord());
			glVertex3fv(pKey->Data.GetCoord());
		glEnd();
		pos=pKey->Data;
		OR_Globals::Context()->SetColor(1,1,1);
		glBegin(GL_POINTS);
			glVertex3fv(pos.GetCoord());
		glEnd();
	}

	OR_Globals::Context()->SetDefaultPointSize();
	OR_Globals::Context()->NormalDrawMode();
glPopMatrix();
}

/* serialization methods ***************************************/
void OR_AnimationTrack_Linear_Vector::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;
	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Linear<OR_Vector3D> *key=new OR_KeyFrame_Linear<OR_Vector3D>(0,OR_Vector3D());
		file >> key;
		KeyframeList_.push_back(key);
	}
}	


/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Linear_Quaternion            */
/*-------------------------------------------------------------------*/
/* linear tracks                                                     */
/*-------------------------------------------------------------------*/


void OR_AnimationTrack_Linear_Quaternion::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_Linear<OR_Quaternion> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());
	/* value at current time */
	OR_Quaternion data;


	/* compute the data : linear interpolation */
	OR_Float t1=key1->GetTime();
	OR_Float t2=key2->GetTime();
	OR_Float coef=0;
	if(fabs(t2-t1)>OR_EPSILON) coef=(time-t1)/(t2-t1);
	/* smooth linear interpolation on the unity sphere */
	data= key1->Data.Lerp( key2->Data, coef );

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_Rot:
		/* convert the quaterninon into a matrix before assignation */
		object->RotateAnimation(data.ToMatrix());
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Quaternion::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}


/* serialization methods ***************************************/
void OR_AnimationTrack_Linear_Quaternion::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;
	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Linear<OR_Quaternion> *key=new OR_KeyFrame_Linear<OR_Quaternion>(0,OR_Quaternion());
		file >> key;
		KeyframeList_.push_back(key);
	}
}	


/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Smooth_Quaternion            */
/*-------------------------------------------------------------------*/
/* smooth track                                                      */
/*-------------------------------------------------------------------*/

void OR_AnimationTrack_Smooth_Quaternion::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_Linear<OR_Quaternion> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());
	/* value at current time */
	OR_Quaternion data;


	/* compute the data : linear interpolation */
	OR_Float t1=key1->GetTime();
	OR_Float t2=key2->GetTime();
	OR_Float coef=0;
	if(fabs(t2-t1)>OR_EPSILON) coef=(time-t1)/(t2-t1);
	/* smooth linear interpolation on the unity sphere */
	data= key1->Data.Slerp( key2->Data, coef );

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_Rot:
		/* convert the quaterninon into a matrix before assignation */
		object->RotateAnimation(data.ToMatrix());
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Quaternion::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}

/* serialization methods ***************************************/
void OR_AnimationTrack_Smooth_Quaternion::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;
	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Smooth<OR_Quaternion> *key=new OR_KeyFrame_Smooth<OR_Quaternion>(0,OR_Quaternion());
		file >> key;
		KeyframeList_.push_back(key);
	}
}	

/* bezier track **************************************************************************************/
/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Bezier_Float                 */
/*-------------------------------------------------------------------*/
/* Bezier tracks                                                     */
/*-------------------------------------------------------------------*/
void OR_AnimationTrack_Bezier_Float::SetUpEvaluator(IT_KeyFrameList it)
{
	OR_Float P1[2], P2[2];

	OR_KeyFrame_Bezier<OR_Float>* key1=(OR_KeyFrame_Bezier<OR_Float>*) *it;
	OR_KeyFrame_Bezier<OR_Float>* key2;

	IT_KeyFrameList it_next(it); it_next++;

	if( it_next != KeyframeList_.end() ) 
		key2=(OR_KeyFrame_Bezier<OR_Float>*) *(it_next);
	else
		key2=(OR_KeyFrame_Bezier<OR_Float>*) KeyframeList_.front();

	/* compute bezier curve control point number 1 and 2  */		
	P1[X]=key1->TangentRight[0][X];
	P1[Y]=key1->Data+key1->TangentRight[0][Y];
	P2[X]=1+key2->TangentLeft[0][X];
	P2[Y]=key2->Data+key2->TangentRight[0][Y];
	/* set up evaluator */
	key1->Evaluator[0].Initialize(key1->Data, P1, P2, key2->Data);
}

void OR_AnimationTrack_Bezier_Float::SetUpAllEvaluators()
{
	/* initialize the evaluators */
	for(IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
		SetUpEvaluator(it);
}

void OR_AnimationTrack_Bezier_Float::Compute(OR_Float time, OR_Object* object)
{
	/* THE ALGO HAS NOT BEEN OPTIMISED YET !!*/
	/* find the good pair of keyframe */
	OR_KeyFrame_Bezier<OR_Float> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());
	/* value at current time */
	OR_Float data;

	/* comute the time, btw the 2 keys */
	OR_Float t1=key1->GetTime();
	OR_Float t2=key2->GetTime();
	OR_Float t=0;
	if(fabs(t2-t1)>OR_EPSILON) t=(time-t1)/(t2-t1);

	/* compute the data using the 3 evaluator of the node */
	data=key1->Evaluator[0].Evaluate(t);

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_PosX:
		object->TranslateAnimation(X, data);
		break;
	case OR_ANIMATION_Target_PosY:
		object->TranslateAnimation(Y, data);
		break;
	case OR_ANIMATION_Target_PosZ:
		object->TranslateAnimation(Z, data);
		break;
	case OR_ANIMATION_Target_ScaleX:
		object->ScaleAnimation(X, data);
		break;
	case OR_ANIMATION_Target_ScaleY:
		object->ScaleAnimation(Y, data);
		break;
	case OR_ANIMATION_Target_ScaleZ:
		object->ScaleAnimation(Z, data);
		break;
	case OR_ANIMATION_Target_AmbientR:
		object->SetAmbient(R, data);
		break;
	case OR_ANIMATION_Target_AmbientV:
		object->SetAmbient(V, data);
		break;
	case OR_ANIMATION_Target_AmbientB:
		object->SetAmbient(B, data);
		break;
	case OR_ANIMATION_Target_DiffuseR:
		object->SetDiffuse(R, data);
		break;
	case OR_ANIMATION_Target_DiffuseV:
		object->SetDiffuse(V, data);
		break;
	case OR_ANIMATION_Target_DiffuseB:
		object->SetDiffuse(B, data);
		break;
	case OR_ANIMATION_Target_SpecularR:
		object->SetSpecular(R, data);
		break;
	case OR_ANIMATION_Target_SpecularV:
		object->SetSpecular(V, data);
		break;
	case OR_ANIMATION_Target_SpecularB:
		object->SetSpecular(B, data);
		break;
	case OR_ANIMATION_Target_Shine:
		object->SetShine(data);
		break;
	case OR_ANIMATION_Target_Display:
		object->SetVisible( data>0 );
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Float::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}

/* serialization methods ***************************************/
void OR_AnimationTrack_Bezier_Float::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;

	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Bezier<OR_Float> *key=new OR_KeyFrame_Bezier<OR_Float>(0,0);
		file >> key;
		KeyframeList_.push_back(key);
	}
	
	/* initialize the evaluators */
	SetUpAllEvaluators();
}	


/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Bezier_Vector                */
/*-------------------------------------------------------------------*/
/* Bezier tracks                                                     */
/*-------------------------------------------------------------------*/
void OR_AnimationTrack_Bezier_Vector::SetUpEvaluator(IT_KeyFrameList it)
{
	OR_Float P1[2], P2[2];

	OR_KeyFrame_Bezier<OR_Vector3D>* key1=(OR_KeyFrame_Bezier<OR_Vector3D>*) *it;
	OR_KeyFrame_Bezier<OR_Vector3D>* key2;

	IT_KeyFrameList it_next(it); ++it_next;
	if( it_next != KeyframeList_.end() )  
		key2=(OR_KeyFrame_Bezier<OR_Vector3D>*) *it_next;
	else
		key2=(OR_KeyFrame_Bezier<OR_Vector3D>*) KeyframeList_.front();

	for (OR_U32 i=0; i<3; i++)
	{
		P1[X]=key1->TangentRight[i][X];
		P1[Y]=key1->Data[i]+key1->TangentRight[i][Y];
		P2[X]=1+key2->TangentLeft[i][X];
		P2[Y]=key2->Data[i]+key2->TangentLeft[i][Y];
		key1->Evaluator[i].Initialize(key1->Data[i], P1, P2, key2->Data[i]);
	}
}

void OR_AnimationTrack_Bezier_Vector::SetUpAllEvaluators()
{
	/* NOTA : the last evaluator will be intialized with the KeyRoot as second key */
	for(IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
		SetUpEvaluator(it);
}

void OR_AnimationTrack_Bezier_Vector::Compute(OR_Float time, OR_Object* object)
{
	/* THE ALGO HAS NOT BEEN OPTIMISED YET !!*/
	/* find the good pair of keyframe */
	OR_KeyFrame_Bezier<OR_Vector3D>* key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());
	/* value at current time */
	OR_Vector3D data;

	/* compute the time, btw the 2 keys */
	OR_Float t1=key1->GetTime();
	OR_Float t2=key2->GetTime();
	OR_Float t=0;
	if(fabs(t2-t1)>OR_EPSILON) t=(time-t1)/(t2-t1);

	/* compute the data using the 3 evaluator of the node */
	data[X]=key1->Evaluator[X].Evaluate(t);
	data[Y]=key1->Evaluator[Y].Evaluate(t);
	data[Z]=key1->Evaluator[Z].Evaluate(t);
	
	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_Pos:
		object->TranslateAnimation(data);
		break;
	case OR_ANIMATION_Target_Scale:
		object->ScaleAnimation(data);
		break;
	case OR_ANIMATION_Target_Ambient:
		object->SetAmbient(data);
		break;
	case OR_ANIMATION_Target_Diffuse:
		object->SetDiffuse(data);
		break;
	case OR_ANIMATION_Target_Specular:
		object->SetSpecular(data);
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Vector::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}

#define OR_DRAW_TANGENT_FACTOR 0.3f

void OR_AnimationTrack_Bezier_Vector::DrawTrajectory(OR_Object* object)
{
	/* change point size */
	OR_Globals::Context()->SetPointSize(3);
	/* swhich to simple draw mode */
glPushMatrix();
	OR_Matrix4x4 Mat = ( ~(object->GetOldAnimationMatrix())*object->GetAbsoluteMatrix() );
	OR_Maths::MultiplyCurrentModelView( Mat );
	OR_Globals::Context()->SimpleDrawMode();

	/** display each key */
	OR_Vector3D pos;
	OR_Vector3D tangent;
	OR_KeyFrame_Bezier<OR_Vector3D> *e;
	OR_Bool first=true;

	for(IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
	{
		e=(OR_KeyFrame_Bezier<OR_Vector3D>*) *it;
		pos=e->Data;
		/* draw key point */
		OR_Globals::Context()->SetColor(1,1,1);
		glBegin(GL_POINTS);
			glVertex3fv(pos.GetCoord());
		glEnd();
		/* draw left tangent */
		if (!first)
		{			
			tangent[X]=-e->TangentLeft[X][1]/e->TangentLeft[X][0];
			tangent[Y]=-e->TangentLeft[Y][1]/e->TangentLeft[Y][0];
			tangent[Z]=-e->TangentLeft[Z][1]/e->TangentLeft[Z][0];
			glBegin(GL_POINTS);
				glVertex3fv((pos+(tangent)*OR_DRAW_TANGENT_FACTOR).GetCoord());
			glEnd();
			OR_Globals::Context()->SetColor(1,0,0);
			glBegin(GL_LINES);
				glVertex3fv(pos.GetCoord());
				glVertex3fv((pos+(tangent)*OR_DRAW_TANGENT_FACTOR).GetCoord());
			glEnd();
		}
		else first=false;
		/* draw right tangent */
		tangent[X]=e->TangentRight[X][1]/e->TangentRight[X][0];
		tangent[Y]=e->TangentRight[Y][1]/e->TangentRight[Y][0];
		tangent[Z]=e->TangentRight[Z][1]/e->TangentRight[Z][0];
		OR_Globals::Context()->SetColor(1,1,1);
		glBegin(GL_POINTS);
			glVertex3fv((pos+(tangent)*OR_DRAW_TANGENT_FACTOR).GetCoord());
		glEnd();
		OR_Globals::Context()->SetColor(1,0,0);
		glBegin(GL_LINES);
			glVertex3fv(pos.GetCoord());
			glVertex3fv((pos+(tangent)*OR_DRAW_TANGENT_FACTOR).GetCoord());
		glEnd();
		/* draw the curve between the 2 points */
		OR_Vector3D data;
		OR_Globals::Context()->SetColor(1,1,0);
		glBegin(GL_LINE_STRIP);
		for (OR_Float t=0; t<=1.05f; t+=0.05f)
		{
			data[X]=e->Evaluator[X].Evaluate(t);
			data[Y]=e->Evaluator[Y].Evaluate(t);
			data[Z]=e->Evaluator[Z].Evaluate(t);
			glVertex3fv(data.GetCoord());
		}
		glEnd();
	}
	/* draw last key point */
	e=(OR_KeyFrame_Bezier<OR_Vector3D>*) KeyframeList_.back();
	pos=e->Data;
	OR_Globals::Context()->SetColor(1,1,1);
	glBegin(GL_POINTS);
		glVertex3fv(pos.GetCoord());
	glEnd();
	/* draw last left tangeant */
	tangent[X]=-e->TangentLeft[X][1]/e->TangentLeft[X][0];
	tangent[Y]=-e->TangentLeft[Y][1]/e->TangentLeft[Y][0];
	tangent[Z]=-e->TangentLeft[Z][1]/e->TangentLeft[Z][0];
	glBegin(GL_POINTS);
		glVertex3fv((pos+(tangent)*OR_DRAW_TANGENT_FACTOR).GetCoord());
	glEnd();
	OR_Globals::Context()->SetColor(1,0,0);
	glBegin(GL_LINES);
		glVertex3fv(pos.GetCoord());
		glVertex3fv((pos+(tangent)*OR_DRAW_TANGENT_FACTOR).GetCoord());
	glEnd();

	OR_Globals::Context()->NormalDrawMode();
glPopMatrix();
}

/* serialization methods ***************************************/
void OR_AnimationTrack_Bezier_Vector::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;

	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Bezier<OR_Vector3D> *key=new OR_KeyFrame_Bezier<OR_Vector3D>(0,OR_Vector3D());
		file >> key;
		KeyframeList_.push_back(key);
	}

	/* initialize the evaluators */
	SetUpAllEvaluators();
}	


/* TCB track **************************************************************************************/
/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_TCB_Float                    */
/*-------------------------------------------------------------------*/
/* TCB tracks                                                        */
/*-------------------------------------------------------------------*/
void OR_AnimationTrack_TCB_Float::SetUpEvaluator(IT_KeyFrameList it)
{
	/*	P0 = value before the first key [P0=P1 if this is the first key]
		P1 = value of the first key 
		P2 = value of the second key 
		P3 = value after the second key [P4=P3 if this is the last key] */
	OR_Float P0, P1, P2, P3;

	/* initialize the evaluators */
	OR_KeyFrame_TCB<OR_Float>* key0;
	OR_KeyFrame_TCB<OR_Float>* key1=(OR_KeyFrame_TCB<OR_Float>*) *it;
	OR_KeyFrame_TCB<OR_Float>* key2;
	OR_KeyFrame_TCB<OR_Float>* key3;
	/* initialize key0 */
	if(it!=KeyframeList_.begin())
	{
		IT_KeyFrameList it_before(it); it_before--;
		key0 = (OR_KeyFrame_TCB<OR_Float>*) *it_before;
	}
	else
		key0 = key1;
	/* initialize key2 */
	IT_KeyFrameList it_next(it); it_next++;
	if( it_next != KeyframeList_.end() ) 
		key2=(OR_KeyFrame_TCB<OR_Float>*) *it_next;
	else
		key2=(OR_KeyFrame_TCB<OR_Float>*) KeyframeList_.front();
	/* initialize key3 */
	if( it_next!=KeyframeList_.end() )
	{
		IT_KeyFrameList it_nextnext(it_next); it_nextnext++;
		if( it_nextnext!=KeyframeList_.end() )
			key3 = (OR_KeyFrame_TCB<OR_Float>*) *it_nextnext;
		else
			key3=key2;
	}
	else
		key3 = key2;


	P0=key0->Data;
	P1=key1->Data;
	P2=key2->Data;
	P3=key3->Data;
	/* set up evaluator */
	key1->Evaluator[0].Initialize(P0, P1, P2, P3,
								  key1->Tension[0], key1->Continuity[0], key1->Bias[0],				
								  key2->Tension[0], key2->Continuity[0], key2->Bias[0]);
}

void  OR_AnimationTrack_TCB_Float::SetUpAllEvaluators()
{
	/* NOTA : the last evaluator will be intialized with the KeyRoot as second key */
	for(IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
		SetUpEvaluator(it);
}

void OR_AnimationTrack_TCB_Float::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_TCB<OR_Float>*key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());
	/* value at current time */
	OR_Float data;

	/* comute the time, btw the 2 keys */
	OR_Float t1=key1->GetTime();
	OR_Float t2=key2->GetTime();
	OR_Float t=0;
	if(fabs(t2-t1)>OR_EPSILON) t=(time-t1)/(t2-t1);
	
	/* compute the data using the 3 evaluator of the node */
	data=key1->Evaluator[0].Evaluate(t);

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_PosX:
		object->TranslateAnimation(X, data);
		break;
	case OR_ANIMATION_Target_PosY:
		object->TranslateAnimation(Y, data);
		break;
	case OR_ANIMATION_Target_PosZ:
		object->TranslateAnimation(Z, data);
		break;
	case OR_ANIMATION_Target_ScaleX:
		object->ScaleAnimation(X, data);
		break;
	case OR_ANIMATION_Target_ScaleY:
		object->ScaleAnimation(Y, data);
		break;
	case OR_ANIMATION_Target_ScaleZ:
		object->ScaleAnimation(Z, data);
		break;
	case OR_ANIMATION_Target_AmbientR:
		object->SetAmbient(R, data);
		break;
	case OR_ANIMATION_Target_AmbientV:
		object->SetAmbient(V, data);
		break;
	case OR_ANIMATION_Target_AmbientB:
		object->SetAmbient(B, data);
		break;
	case OR_ANIMATION_Target_DiffuseR:
		object->SetDiffuse(R, data);
		break;
	case OR_ANIMATION_Target_DiffuseV:
		object->SetDiffuse(V, data);
		break;
	case OR_ANIMATION_Target_DiffuseB:
		object->SetDiffuse(B, data);
		break;
	case OR_ANIMATION_Target_SpecularR:
		object->SetSpecular(R, data);
		break;
	case OR_ANIMATION_Target_SpecularV:
		object->SetSpecular(V, data);
		break;
	case OR_ANIMATION_Target_SpecularB:
		object->SetSpecular(B, data);
		break;
	case OR_ANIMATION_Target_Shine:
		object->SetShine(data);
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Float::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}


/* serialization methods ***************************************/
void OR_AnimationTrack_TCB_Float::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;

	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_TCB<OR_Float> *key=new OR_KeyFrame_TCB<OR_Float>(0,0);
		file >> key;
		KeyframeList_.push_back(key);
	}

	/* initialize the evaluators */
	SetUpAllEvaluators();
}	


/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_TCB_Vector                   */
/*-------------------------------------------------------------------*/
/* TCB tracks                                                        */
/*-------------------------------------------------------------------*/

void OR_AnimationTrack_TCB_Vector::SetUpEvaluator(IT_KeyFrameList it)
{
	/*	P0 = value before the first key [P0=P1 if this is the first key]
		P1 = value of the first key 
		P2 = value of the second key 
		P3 = value after the second key [P4=P3 if this is the last key] */
	OR_Float P0, P1, P2, P3;


	/* initialize the evaluators */
	OR_KeyFrame_TCB<OR_Vector3D>* key0;
	OR_KeyFrame_TCB<OR_Vector3D>* key1=(OR_KeyFrame_TCB<OR_Vector3D>*) *it;
	OR_KeyFrame_TCB<OR_Vector3D>* key2;
	OR_KeyFrame_TCB<OR_Vector3D>* key3;
	/* initialize key0 */
	if(it!=KeyframeList_.begin())
	{
		IT_KeyFrameList it_before(it); it_before--;
		key0 = (OR_KeyFrame_TCB<OR_Vector3D>*) *it_before;
	}
	else
		key0 = key1;
	/* initialize key2 */
	IT_KeyFrameList it_next(it); it_next++;
	if( it_next != KeyframeList_.end() ) 
		key2=(OR_KeyFrame_TCB<OR_Vector3D>*) *it_next;
	else
		key2=(OR_KeyFrame_TCB<OR_Vector3D>*) KeyframeList_.front();
	/* initialize key3 */
	if( it_next!=KeyframeList_.end() )
	{
		IT_KeyFrameList it_nextnext(it_next); it_nextnext++;
		if( it_nextnext!=KeyframeList_.end() )
			key3 =(OR_KeyFrame_TCB<OR_Vector3D>*) *it_nextnext;
		else
			key3=key2;
	}
	else
		key3 = key2;
	
	


	for (OR_I32 i=0; i<3; i++)
	{
		P0=key0->Data[i];
		P1=key1->Data[i];
		P2=key2->Data[i];
		P3=key3->Data[i];
		/* set up evaluator */
		key1->Evaluator[i].Initialize(P0, P1, P2, P3,
									  key1->Tension[i], key1->Continuity[i], key1->Bias[i],				
									  key2->Tension[i], key2->Continuity[i], key2->Bias[i]);
	}
}

void  OR_AnimationTrack_TCB_Vector::SetUpAllEvaluators()
{
	/* NOTA : the last evaluator will be intialized with the KeyRoot as second key */
	for(IT_KeyFrameList it=KeyframeList_.begin(); it!=KeyframeList_.end(); ++it)
		SetUpEvaluator(it);
}

void OR_AnimationTrack_TCB_Vector::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_TCB<OR_Vector3D> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());
	/* value at current time */
	OR_Vector3D data;

	/* comute the time, btw the 2 keys */
	OR_Float t1=key1->GetTime();
	OR_Float t2=key2->GetTime();
	OR_Float t=0;
	if(fabs(t2-t1)>OR_EPSILON) t=(time-t1)/(t2-t1);
		
	/* compute the data using the 3 evaluator of the node */
	data[X]=key1->Evaluator[X].Evaluate(t);
	data[Y]=key1->Evaluator[Y].Evaluate(t);
	data[Z]=key1->Evaluator[Z].Evaluate(t);


	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_Pos:
		object->TranslateAnimation(data);
		break;
	case OR_ANIMATION_Target_Scale:
		object->ScaleAnimation(data);
		break;
	case OR_ANIMATION_Target_Ambient:
		object->SetAmbient(data);
		break;
	case OR_ANIMATION_Target_Diffuse:
		object->SetDiffuse(data);
		break;
		break;
	case OR_ANIMATION_Target_Specular:
		object->SetSpecular(data);
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Vector::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}

/* serialization methods ***************************************/
void OR_AnimationTrack_TCB_Vector::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;

	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_TCB<OR_Vector3D> *key=new OR_KeyFrame_TCB<OR_Vector3D>( 0, OR_Vector3D(0,0,0) );
		file >> key;
		KeyframeList_.push_back(key);
	}

	/* initialize each evaluator */
	SetUpAllEvaluators();
}	



/* Constant track **************************************************************************************/
/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Constant_Float               */
/*-------------------------------------------------------------------*/
/* Constant tracks                                                   */
/*-------------------------------------------------------------------*/

void OR_AnimationTrack_Constant_Float::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_Constant<OR_Float> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());
	/* value at current time */
	OR_Float data;

	/* compute the data : linear interpolation */
	data=key1->Data;

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_PosX:
		object->TranslateAnimation(X, data);
		break;
	case OR_ANIMATION_Target_PosY:
		object->TranslateAnimation(Y, data);
		break;
	case OR_ANIMATION_Target_PosZ:
		object->TranslateAnimation(Z, data);
		break;
	case OR_ANIMATION_Target_ScaleX:
		object->ScaleAnimation(X, data);
		break;
	case OR_ANIMATION_Target_ScaleY:
		object->ScaleAnimation(Y, data);
		break;
	case OR_ANIMATION_Target_ScaleZ:
		object->ScaleAnimation(Z, data);
		break;
	case OR_ANIMATION_Target_AmbientR:
		object->SetAmbient(R, data);
		break;
	case OR_ANIMATION_Target_AmbientV:
		object->SetAmbient(V, data);
		break;
	case OR_ANIMATION_Target_AmbientB:
		object->SetAmbient(B, data);
		break;
	case OR_ANIMATION_Target_DiffuseR:
		object->SetDiffuse(R, data);
		break;
	case OR_ANIMATION_Target_DiffuseV:
		object->SetDiffuse(V, data);
		break;
	case OR_ANIMATION_Target_DiffuseB:
		object->SetDiffuse(B, data);
		break;
	case OR_ANIMATION_Target_SpecularR:
		object->SetSpecular(R, data);
		break;
	case OR_ANIMATION_Target_SpecularV:
		object->SetSpecular(V, data);
		break;
	case OR_ANIMATION_Target_SpecularB:
		object->SetSpecular(B, data);
		break;
	case OR_ANIMATION_Target_Shine:
		object->SetShine(data);
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Float::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}

/* serialization methods ***************************************/
void OR_AnimationTrack_Constant_Float::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;

	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Constant<OR_Float> *key=new OR_KeyFrame_Constant<OR_Float>(0,0);
		file >> key;
		KeyframeList_.push_back(key);
	}
}	



/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Constant_Vector              */
/*-------------------------------------------------------------------*/
/* Constant tracks                                                   */
/*-------------------------------------------------------------------*/

void OR_AnimationTrack_Constant_Vector::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_Constant<OR_Vector3D> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());
	/* value at current time */
	OR_Vector3D data;

	/* compute the data : linear interpolation */
	data=key1->Data;

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_Pos:
		object->TranslateAnimation(data);
		break;
	case OR_ANIMATION_Target_Scale:
		object->ScaleAnimation(data);
		break;
	case OR_ANIMATION_Target_Ambient:
		object->SetAmbient(data);
		break;
	case OR_ANIMATION_Target_Diffuse:
		object->SetDiffuse(data);
		break;
	case OR_ANIMATION_Target_Specular:
		object->SetSpecular(data);
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Vector::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}


/* serialization methods ***************************************/
void OR_AnimationTrack_Constant_Vector::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;

	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Constant<OR_Vector3D> *key=new OR_KeyFrame_Constant<OR_Vector3D>( 0, OR_Vector3D(0,0,0) );
		file >> key;
		KeyframeList_.push_back(key);
	}
}	



/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Constant_Quaternion          */
/*-------------------------------------------------------------------*/
/* Constant tracks                                                   */
/*-------------------------------------------------------------------*/

void OR_AnimationTrack_Constant_Quaternion::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_Constant<OR_Quaternion> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());

	/* compute the data : no interpolation */
	OR_Quaternion data=key1->Data;

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_Rot:
		/* convert the quaterninon into a matrix before assignation */
		object->RotateAnimation(data.ToMatrix());
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Quaternion::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}


/* serialization methods ***************************************/
void OR_AnimationTrack_Constant_Quaternion::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;

	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Constant<OR_Quaternion> *key=new OR_KeyFrame_Constant<OR_Quaternion>(0, OR_Quaternion());
		file >> key;
		KeyframeList_.push_back(key);
	}
}	


/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Constant_Bool                */
/*-------------------------------------------------------------------*/
/* Constant tracks                                                   */
/*-------------------------------------------------------------------*/

void OR_AnimationTrack_Constant_Bool::Compute(OR_Float time, OR_Object* object)
{
	/* find the good pair of keyframe */
	OR_KeyFrame_Constant<OR_Bool> *key1, *key2;
	FindKeyframe(time, (OR_KeyFrame* &) key1, (OR_KeyFrame* &) key2, KeyframeList_.end());

	/* compute the data : no interpolation */
	OR_Bool data=key1->Data;

	/* assign the data */
	switch (Target_)
	{
	case OR_ANIMATION_Target_Display:
		/* convert the quaterninon into a matrix before assignation */
		if (data) object->Enable();
		else object->Disable();
		break;
	default:
		/* the track type is not supported */
		OR_Globals::MessageHandler()->Debug("OR_AnimationTrack_Linear_Quaternion::Compute", 
						"The track Target_ '%i' is not supported.", Target_);
		break;
	}
}

/* serialization methods ***************************************/
void OR_AnimationTrack_Constant_Bool::BuildFromFile( OR_File& file )
{
	/* import basic track features */
	OR_AnimationTrack::BuildFromFile(file);
	/* export the number of keys */
	OR_U32 nb_keys;
	file >> nb_keys;

	/* import the keys */
	for (OR_U32 i=0; i<nb_keys; i++)
	{
		OR_KeyFrame_Constant<OR_Bool> *key=new OR_KeyFrame_Constant<OR_Bool>(0,0);
		file >> key;

		KeyframeList_.push_back(key);
	}
}	



} // namespace OR

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
