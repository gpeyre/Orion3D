/*-------------------------------------------------------------------*/
/*                           OR_KeyFrame.h                           */
/*-------------------------------------------------------------------*/
/* created on 10:5:2001   1:24                                       */
/*-------------------------------------------------------------------*/

/** \file 
	Contains definitions of animation keyframes.
	\author Gabriel.
**/

#ifndef _OR_KEYFRAME_H_
#define _OR_KEYFRAME_H_

#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"
#include "../objects/OR_Object.h"
#include "OR_Evaluator.h"

namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                      class OR_KeyFrame                            */
/*-------------------------------------------------------------------*/
/* super class for all keyframe                                      */
/*-------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_KeyFrame in group group_animation
 */

/// a keyframe in an animation track. super class for all keyframe .
/** 
	A keyframe is a basic step in an animation track.
	\author Gabriel
*/

class ORION3D_API OR_KeyFrame: public OR_Serializable, public OR_ShellObject_ABC
{

public:

	/** constructor */
	OR_KeyFrame(OR_Float time=0)
	{
		Time=time;
	}

	/** set the keyframe time */
	void SetTime(OR_Float time)
	{
		Time=time;
	}
	/** get the keyframe time */
	OR_Float GetTime()
	{
		return Time;
	}

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file )
	{ file >> Time; }
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file )
	{ file << Time; }

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList)
	{ }
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
	{
		OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Time);
	}
	
	OR_DECL_SHELL_ACCESSOR_FUNC(Time, OR_KeyFrame, Float);
    //@}

protected:
	/** the time when the keyframe occur in the animation, 0<Time<1 */
	OR_Float Time;

};


/** a list of keyframes */
typedef list<OR_KeyFrame*> T_KeyFrameList;
/** iterator on a list of keyframes */
typedef T_KeyFrameList::iterator IT_KeyFrameList;

/* linear keyframes ************************************************************************************/
/*-------------------------------------------------------------------*/
/*                      class OR_KeyFrame_Linear                     */
/*-------------------------------------------------------------------*/
/* template for a linear keyframe                                    */
/*-------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_KeyFrame_Float in group group_animation
 */

/// template for a linear keyframe .
/** 
	A keyframe is a basic step in an animation track.
	\author Gabriel
*/

template <class T>
class ORION3D_API OR_KeyFrame_Linear: public OR_KeyFrame
{
public:
	/** the data of the keyframe */
	T Data;

	/** constructor */
	OR_KeyFrame_Linear<T>(OR_Float time=0, T data = T()): OR_KeyFrame(time)
	{
		Data=data;
	}

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file )
	{ 
		OR_KeyFrame::BuildFromFile(file); 
		file >> Data; 
	}
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file )	
	{ 
		OR_KeyFrame::BuildToFile(file); 
		file << Data; 
	}
	OR_DEFINE_SERIALIZATION_TEMPLATE(OR_KeyFrame_Linear, T);
};

/* smooth keyframe ************************************************************************************/
/*-------------------------------------------------------------------*/
/*                      class OR_KeyFrame_Smooth                     */
/*-------------------------------------------------------------------*/
/* template for a smooth keyframe                                    */
/*-------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_KeyFrame_Smooth in group group_animation
 */

/// template for a smooth keyframe .
/** 
	A keyframe is a basic step in an animation track.
	The smooth keyframe is used only by Quaternion track (using slerp).
	\author Gabriel
*/

template <class T>
class ORION3D_API OR_KeyFrame_Smooth: public OR_KeyFrame
{
public:
	/** the data of the keyframe */
	T Data;

	/** constructor */
	OR_KeyFrame_Smooth<T>( OR_Float time=0, T data = T() ): OR_KeyFrame(time)
	{
		Data=data;
	}

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file )
	{ 
		OR_KeyFrame::BuildFromFile(file); 
		file >> Data; 
	}
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file )	
	{ 
		OR_KeyFrame::BuildToFile(file); 
		file << Data; 
	}
	OR_DEFINE_SERIALIZATION_TEMPLATE(OR_KeyFrame_Smooth, T);
};

/* constant keyframes ************************************************************************************/
/*-------------------------------------------------------------------*/
/*                      class OR_KeyFrame_Constant                   */
/*-------------------------------------------------------------------*/
/* template for a linear keyframe                                    */
/*-------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_KeyFrame_Constant in group group_animation
 */

/// template for a constant keyframe .
/** 
	A keyframe is a basic step in an animation track.
	\author Gabriel
*/

template <class T>
class ORION3D_API OR_KeyFrame_Constant: public OR_KeyFrame
{
public:
	/** the data of the keyframe */
	T Data;

	/** constructor */
	OR_KeyFrame_Constant<T>( OR_Float time=0, T data = T() ): OR_KeyFrame(time)
	{
		Data=data;
	}

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file )
	{ 
		OR_KeyFrame::BuildFromFile(file); 
		file >> Data; 
	}
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file )	
	{ 
		OR_KeyFrame::BuildToFile(file); 
		file << Data; 
	}
	OR_DEFINE_SERIALIZATION_TEMPLATE(OR_KeyFrame_Constant, T);
};

/* bezier keyframes *******************************************************************************/
/*-------------------------------------------------------------------*/
/*                      class OR_KeyFrame_Bezier                     */
/*-------------------------------------------------------------------*/
/* template for a bezier keyframe                                    */
/*-------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_KeyFrame_Quaternion in group group_animation
 */

/// template for a bezier keyframe.
/** 
	A keyframe is a basic step in an animation track.
	\author Gabriel
*/
template <class T>
class ORION3D_API OR_KeyFrame_Bezier: public OR_KeyFrame
{
public:
	/** the data of the keyframe */
	T Data;

	/** constructor */
	OR_KeyFrame_Bezier<T>(OR_Float time = 0, T data = T() ): OR_KeyFrame(time)
	{
		Data=data;
		TangentLeft=NULL;
		TangentRight=NULL;
	}
	/** destructor */
	~OR_KeyFrame_Bezier<T>()
	{
		OR_DELETEARRAY(TangentLeft);
		OR_DELETEARRAY(TangentRight);
	}

	/** bezier info : can be 1 or 3 tangent(s) */
	OR_Vector2D* TangentLeft;
	/** bezier info : can be 1 or 3 tangent(s) */
	OR_Vector2D* TangentRight;

	/** a list of evaluator */
	OR_Evaluator_1D_Bezier* Evaluator;
	
	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file )
	{ 
		OR_KeyFrame::BuildFromFile(file); 
		file >> Data; 
		/* import the tangent */
		if (sizeof(T)==sizeof(OR_Vector3D))
		{
			Evaluator = new OR_Evaluator_1D_Bezier[3];
			TangentLeft = new OR_Vector2D[3];
			TangentRight = new OR_Vector2D[3];
			file >> TangentLeft[X] 
				 >> TangentLeft[Y] 
				 >> TangentLeft[Z]
				 >> TangentRight[X] 
				 >> TangentRight[Y] 
				 >> TangentRight[Z]; 
		}
		else if (sizeof(T)==sizeof(OR_Float))
		{
			Evaluator = new OR_Evaluator_1D_Bezier;
			TangentLeft = new OR_Vector2D;
			TangentRight = new OR_Vector2D;
			file >> TangentLeft[X] 
				 >> TangentRight[X];
		}
	}
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file )	
	{ 
		OR_KeyFrame::BuildToFile(file); 
		file << Data;
		/* export the tangent */
		if (sizeof(T)==sizeof(OR_Vector3D))
		{
			file << TangentLeft[X] 
	 			 << TangentLeft[Y] 
			  	 << TangentLeft[Z]
				 << TangentRight[X] 
				 << TangentRight[Y] 
			 	 << TangentRight[Z];
		}
		else if (sizeof(T)==sizeof(OR_Float))
		{
			file << TangentLeft[X]
				 << TangentRight[X];
		}
	}
	OR_DEFINE_SERIALIZATION_TEMPLATE(OR_KeyFrame_Bezier, T);
};

/* TCB keyframes *******************************************************************************/
/*-------------------------------------------------------------------*/
/*                      class OR_KeyFrame_TCB                        */
/*-------------------------------------------------------------------*/
/* template for a TCB keyframe                                       */
/*-------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_KeyFrame_Quaternion in group group_animation
 */

/// template for a TCB keyframe.
/** 
	A keyframe is a basic step in an animation track.
	\author Gabriel
*/

template <class T>
class ORION3D_API OR_KeyFrame_TCB: public OR_KeyFrame
{
public:
	/** the data of the keyframe */
	T Data;

	/** constructor */
	OR_KeyFrame_TCB<T>( OR_Float time = 0, T data = T() ): OR_KeyFrame(time)
	{
		Data=data;
		Tension=NULL;
		Continuity=NULL;
		Bias=NULL;
	}
	/** destructor */
	~OR_KeyFrame_TCB<T>()
	{
		OR_DELETEARRAY(Tension);
		OR_DELETEARRAY(Continuity);
		OR_DELETEARRAY(Bias);
	}

	/** TCB info : can be 1 or 3 value(s) */
	OR_Float* Tension;
	/** TCB info : can be 1 or 3 value(s) */
	OR_Float* Continuity;
	/** TCB info : can be 1 or 3 value(s) */
	OR_Float* Bias;

	/** a list of evaluator */
	OR_Evaluator_1D_TCB* Evaluator;

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file )
	{ 
		OR_KeyFrame::BuildFromFile(file); 
		/* import the TCB */
		if (sizeof(T)==sizeof(OR_Float))
		{
			Tension = new OR_Float[3];
			Continuity = new OR_Float[3];
			Bias = new OR_Float[3];
			file >> Tension[X] 
				>> Tension[Y] 
				>> Tension[Z]
				>> Continuity[X] 
				>> Continuity[Y] 
				>> Continuity[Z]
				>> Bias[X] 
				>> Bias[Y] 
				>> Bias[Z]; 
		}
		else if (sizeof(T)==sizeof(OR_Float))
		{
			Tension = new OR_Float;
			Continuity = new OR_Float;
			Bias = new OR_Float;
			file >> Tension[X] 
				 >> Continuity[X] 
				 >> Bias[X];
		}
	}
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file )	
	{ 
		OR_KeyFrame::BuildToFile(file); 
		file << Data; 
		/* export the TCB */
		if (sizeof(T)==sizeof(OR_Float))
		{
			file << Tension[X] 
				<< Tension[Y] 
				<< Tension[Z]
				<< Continuity[X] 
				<< Continuity[Y] 
				<< Continuity[Z]
				<< Bias[X] 
				<< Bias[Y] 
				<< Bias[Z]; 
		}
		else if (sizeof(T)==sizeof(OR_Float))
		{
			file << Tension[X] 
				<< Continuity[X] 
				<< Bias[X];
		}
	}
	OR_DEFINE_SERIALIZATION_TEMPLATE(OR_KeyFrame_TCB, T);
};

} // namespace OR

#endif /* #ifndef _OR_KEYFRAME_H_ */


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