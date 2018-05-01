/*-------------------------------------------------------------------*/
/*                           OR_AnimationTrack.h                     */
/*-------------------------------------------------------------------*/
/* definition of a animations track                                  */
/*-------------------------------------------------------------------*/

/** \file 
	Contains definition of animation track class [used to store a list of key frame].
	There is different kind of key type, depending on wich evaluator is used [linear, 
	bezier, TCB, constant] and wich data is stored [OR_Float, vector, quaternion]
	\author Gabriel.
**/


#ifndef _OR_ANIMATION_TRACK_H_
#define _OR_ANIMATION_TRACK_H_

#include "../configuration/OR_Config.h"
#include "OR_Evaluator.h"
#include "OR_KeyFrame.h"
#include "../maths/OR_Maths.h"
#include "../objects/OR_Object.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_File.h"
#include "../utils/OR_String.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"

namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                      class OR_AnimationTrack                      */
/*-------------------------------------------------------------------*/
/* super class for all track                                         */
/*-------------------------------------------------------------------*/

/*! \ingroup group_animation
 *  \brief class OR_AnimationTrack in group group_animation.
 */

/// a list of keyframes. super class for all track.
/** 
	List all key frame composing the animation of a single node.
	\author Gabriel
*/

class ORION3D_API OR_AnimationTrack: public OR_Serializable, public OR_ShellObject_ABC
{

public:

    //-------------------------------------------------------------------------
    /** \name constructor and destructor */
    //-------------------------------------------------------------------------
    //@{
	/** constructor */
	OR_AnimationTrack(OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior behaviour_before, OR_ANIMATION_Track_Behavior behaviour_after);
	/** constructor */
	OR_AnimationTrack();
	/** destructor */
	virtual ~OR_AnimationTrack();
    //@}

    //-------------------------------------------------------------------------
    /** \name keyframes management */
    //-------------------------------------------------------------------------
    //@{
	T_KeyFrameList& GetKeyframeList();
	void AddKeyFrame(OR_KeyFrame &keyframe);
	void AddKeyFrameFirst(OR_KeyFrame &keyframe);
	void AddKeyFrameLast(OR_KeyFrame &keyframe);
	void RemoveKeyFrame(OR_KeyFrame &keyframe);
    //@}

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	/** set the duration */
	void SetLength(OR_Float length);
	/** get the duration */
	OR_Float GetLength();
	/** set the behaviourS */
	void SetBehaviour(OR_ANIMATION_Track_Behavior b_before, OR_ANIMATION_Track_Behavior b_after);
	/** set the behaviour before */
	void SetBehaviourBefore(OR_ANIMATION_Track_Behavior b_before);
	/** set the behaviour after */
	void SetBehaviourAfter(OR_ANIMATION_Track_Behavior b_after);
	/** get the behaviour before the beginning */
	OR_ANIMATION_Track_Behavior GetBehaviourBefore();
	/** get the behaviour after the end */
	OR_ANIMATION_Track_Behavior GetBehaviourAfter();
	/** get the target */
	OR_ANIMATION_Target GetTarget();
	/** set the target */
	void SetTarget(OR_ANIMATION_Target target);
	/** is the target a rotation one */
	OR_Bool IsRotationTarget();
	/** is the target a translation one */
	OR_Bool IsTranslationTarget();
	/** is the target a scale one */
	OR_Bool IsScaleTarget();

	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType();
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType();
    //@}

    //-------------------------------------------------------------------------
    /** \name virtual functions */
    //-------------------------------------------------------------------------
    //@{
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object)=0;
	/** draw the trajectory of the object */
	virtual void DrawTrajectory(OR_Object *object)
	{ }
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
    //@}

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	
	OR_DECL_SHELL_ACCESSOR_FUNC(Length, OR_AnimationTrack, Float);
    //@}

protected:

	/** the list of keyframes */
	T_KeyFrameList KeyframeList_;
	/** target caracteristic */
	OR_ANIMATION_Target Target_;
	/** duration of the track animation, in seconds */
	OR_Float rLength_;
	/** the behaviour of the track before the begining (loop, ping-pong, ...) */
	OR_ANIMATION_Track_Behavior BehaviourBefore_;
	/** the behaviour of the track after the end (loop, ping-pong, ...) */
	OR_ANIMATION_Track_Behavior BehaviourAfter_;

	/** Find the good keyframes using the behaviour. If the time is not in the range of the animation, it computes a "recomputed time"
		using the animation behaviour.
		\param time current time of the animation 
		\param key1 the key before the recomputed time
		\param key2 the key after the recomputed time
	*/
	void FindKeyframe(OR_Float &time, OR_KeyFrame* & key1, OR_KeyFrame* & key2, IT_KeyFrameList &last_it);

};


/** a list of animation tracks */
typedef list<OR_AnimationTrack*> T_AnimationTrackList;
/** iterator for a list of animation tracks */
typedef T_AnimationTrackList::iterator IT_AnimationTrackList;

/* linear track ***************************************************************************************/
/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Linear_Float                 */
/*-------------------------------------------------------------------*/
/* linear tracks                                                     */
/*-------------------------------------------------------------------*/
/// a linear OR_Float track.
class ORION3D_API OR_AnimationTrack_Linear_Float: public OR_AnimationTrack
{
public:
	/** constructor TO REMOVE ! */
	OR_AnimationTrack_Linear_Float(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
								  OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** base constructor */
	OR_AnimationTrack_Linear_Float():OR_AnimationTrack()
	{}
	
	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Float; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Linear; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Linear_Float);
};

/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Linear_Vector                */
/*-------------------------------------------------------------------*/
/* linear tracks                                                     */
/*-------------------------------------------------------------------*/

/// a linear vector track.
class ORION3D_API OR_AnimationTrack_Linear_Vector: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_Linear_Vector(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** constructor */
	OR_AnimationTrack_Linear_Vector():OR_AnimationTrack()	{}

	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);
	/** draw the trajectory of the object */
	virtual void DrawTrajectory(OR_Object *object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Vector; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Linear; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Linear_Vector);
};

/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Linear_Quaternion            */
/*-------------------------------------------------------------------*/
/* linear tracks                                                     */
/*-------------------------------------------------------------------*/

/// a linear quaternion track.
class ORION3D_API OR_AnimationTrack_Linear_Quaternion: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_Linear_Quaternion(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** constructor */
	OR_AnimationTrack_Linear_Quaternion():OR_AnimationTrack()	{}
	
	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Quaternion; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Linear; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Linear_Quaternion);
};


/* smooth track **************************************************************************************/
/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Smooth_Quaternion            */
/*-------------------------------------------------------------------*/
/* Slerp track                                                       */
/*-------------------------------------------------------------------*/

/// a smooth quaternion track.
class ORION3D_API OR_AnimationTrack_Smooth_Quaternion: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_Smooth_Quaternion(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
		OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** base constructor */
	OR_AnimationTrack_Smooth_Quaternion():OR_AnimationTrack() {}
	
	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Quaternion; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Smooth; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Smooth_Quaternion);
};

/* bezier track **************************************************************************************/
/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Bezier_Float                 */
/*-------------------------------------------------------------------*/
/* Bezier tracks                                                     */
/*-------------------------------------------------------------------*/

/// a bezier OR_Float track.
class ORION3D_API OR_AnimationTrack_Bezier_Float: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_Bezier_Float(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** base constructor */
	OR_AnimationTrack_Bezier_Float():OR_AnimationTrack() {}

	/** set up all evaluator of the track */
	void  SetUpAllEvaluators();
	/** set up the evaluator of a keyframe */
	void SetUpEvaluator(IT_KeyFrameList it);

	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Float; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Bezier; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Bezier_Float);
};

/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Bezier_Vector                */
/*-------------------------------------------------------------------*/
/* Bezier tracks                                                     */
/*-------------------------------------------------------------------*/

/// a bezier vector track.
class ORION3D_API OR_AnimationTrack_Bezier_Vector: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_Bezier_Vector(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	
	/** base constructor */
	OR_AnimationTrack_Bezier_Vector():OR_AnimationTrack() {}

	/** set up all evaluator of the track */
	void  SetUpAllEvaluators();
	/** set up the evaluator of a keyframe */
	void SetUpEvaluator(IT_KeyFrameList it);

	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/** draw the trajectory of the object */
	virtual void DrawTrajectory(OR_Object *object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Vector; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Bezier; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Bezier_Vector);
};

/* TCB track **************************************************************************************/
/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_TCB_Float                    */
/*-------------------------------------------------------------------*/
/* TCB tracks                                                        */
/*-------------------------------------------------------------------*/

/// a TCB OR_Float track.
class ORION3D_API OR_AnimationTrack_TCB_Float: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_TCB_Float(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** base constructor */
	OR_AnimationTrack_TCB_Float():OR_AnimationTrack() {}

	/** set up all evaluator of the track */
	void  SetUpAllEvaluators();
	/** set up the evaluator of a keyframe 
		\param KeyBefore the key before e */
	void SetUpEvaluator(IT_KeyFrameList it);
	
	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Float; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_TCB; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_TCB_Float);
};

/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_TCB_Vector                   */
/*-------------------------------------------------------------------*/
/* TCB tracks                                                        */
/*-------------------------------------------------------------------*/

/// a TCB vector track.
class ORION3D_API OR_AnimationTrack_TCB_Vector: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_TCB_Vector(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** base constructor */
	OR_AnimationTrack_TCB_Vector():OR_AnimationTrack() {}
	

	/** set up all evaluator of the track */
	void  SetUpAllEvaluators();
	/** set up the evaluator of a keyframe 
		\param KeyBefore the key before e */
	void SetUpEvaluator(IT_KeyFrameList it);

	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Vector; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_TCB; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_TCB_Vector);
};

/* Constant track **************************************************************************************/
/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Constant_Float               */
/*-------------------------------------------------------------------*/
/* Constant tracks                                                   */
/*-------------------------------------------------------------------*/

/// a constant OR_Float track.
class ORION3D_API OR_AnimationTrack_Constant_Float: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_Constant_Float(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** base constructor */
	OR_AnimationTrack_Constant_Float():OR_AnimationTrack() {}
	
	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Float; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Constant; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Constant_Float);
};

/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Constant_Vector              */
/*-------------------------------------------------------------------*/
/* Constant tracks                                                   */
/*-------------------------------------------------------------------*/

/// a constant vector track.
class ORION3D_API OR_AnimationTrack_Constant_Vector: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_Constant_Vector(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** base constructor */
	OR_AnimationTrack_Constant_Vector():OR_AnimationTrack() {}
	
	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Vector; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Constant; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Constant_Vector);
};

/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Constant_Quaternion          */
/*-------------------------------------------------------------------*/
/* Constant tracks                                                   */
/*-------------------------------------------------------------------*/

/// a constant quaternion track.
class ORION3D_API OR_AnimationTrack_Constant_Quaternion: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_Constant_Quaternion(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** base constructor */
	OR_AnimationTrack_Constant_Quaternion():OR_AnimationTrack() {}
	
	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Quaternion; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Constant; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Constant_Quaternion);
};

/*-------------------------------------------------------------------*/
/*              class OR_AnimationTrack_Constant_Bool                */
/*-------------------------------------------------------------------*/
/* Constant tracks                                                   */
/*-------------------------------------------------------------------*/

/// a constant OR_Bool track.
class ORION3D_API OR_AnimationTrack_Constant_Bool: public OR_AnimationTrack
{
public:
	/** constructor */
	OR_AnimationTrack_Constant_Bool(FILE* file, OR_ANIMATION_Target target, OR_ANIMATION_Track_Behavior b_before, 
									OR_ANIMATION_Track_Behavior b_after, OR_U32 NbKey);
	/** base constructor */
	OR_AnimationTrack_Constant_Bool():OR_AnimationTrack() {}
	
	/* virtual function **************************************************/
	/** update an object in the hierarchy, return the current keyframe */
	virtual void Compute(OR_Float time, OR_Object* object);

	/* query functions ***************************************************/
	/** get the type of the track (OR_Float, quats, etc ...) */
	virtual OR_ANIMATION_Track_Type GetTrackType()
	{ return OR_ANIMATION_Track_Bool; }
	/** get the evaluator of the track (bezier, tcb, etc ...) */
	virtual OR_ANIMATION_Evaluator_Type GetEvaluatorType()
	{ return OR_ANIMATION_Evaluator_Constant; }

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_AnimationTrack_Constant_Bool);
};


} // namespace OR

#ifdef OR_USE_INLINE
	#include "OR_AnimationTrack.inl"
#endif

#endif /* #ifdef _OR_ANIMATION_TRACK_H_ */


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