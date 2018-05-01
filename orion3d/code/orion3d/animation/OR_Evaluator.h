/*-------------------------------------------------------------------------*/
/*                            OR_Evaluator.h                               */
/*-------------------------------------------------------------------------*/
/* Definition of class to evaluate staticaly curves and surfaces, at a     */
/* given precision                                                         */
/*-------------------------------------------------------------------------*/

/** \file
	Definition of class to evaluate staticaly curves and surfaces, at a  
	given precision.
	\author Gabriel.
**/

#ifndef _OR_EVALUATOR_H_
#define _OR_EVALUATOR_H_

#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"

namespace OR
{
	
/*-------------------------------------------------------------------------*/
/*                        class OR_Evaluator                               */
/*-------------------------------------------------------------------------*/
/* super class for all evaluator                                           */
/*-------------------------------------------------------------------------*/

/*! \ingroup group_animation
 *  \brief class OR_Evaluator in group group_animation
 */

/// super class for all evaluator .
/** 
	An evaluator is used to strore in an array the value of a 1D or 2D curve, 
	and to have an approximate value of the curve at a given X.
	\author Gabriel
*/

class ORION3D_API OR_Evaluator
{

protected:

	/** number of step in the evaluation */
	OR_I32 Precision;
	/** is the list computed */
	OR_Bool IsCompute;

public:

	/** constructor */
	OR_Evaluator(OR_I32 precision=OR_DEFAULT_EVALUATOR_PRECISION)
	{
		Precision=precision;
		IsCompute=false;
	}

};

/*-------------------------------------------------------------------------*/
/*                        class OR_Evaluator_1D                            */
/*-------------------------------------------------------------------------*/
/* super class for all 1D evaluator                                        */
/*-------------------------------------------------------------------------*/

/*! \ingroup group_animation
 *  \brief class OR_Evaluator_1D in group group_animation
 */

/// super class for all 1D evaluator .
/** 
	A 1D evaluator is used to strore in an array the value of a curve 1D, 
	and to have an approximate value of the curve at a given X.
	\author Gabriel
*/

class ORION3D_API OR_Evaluator_1D: public OR_Evaluator
{
protected:
	/** list of X value of the curve */
	OR_Float *ValuesX;
	/** list of Y values of the curve */
	OR_Float *ValuesY;
public:
	/** constructor */
	OR_Evaluator_1D(OR_I32 precision=OR_DEFAULT_EVALUATOR_PRECISION);
	/** destructor */
	virtual ~OR_Evaluator_1D();
	/** compute the value at a given X */
	OR_Float Evaluate(OR_Float x);
};

/*-------------------------------------------------------------------------*/
/*                        class OR_Evaluator_1D_Bezier                     */
/*-------------------------------------------------------------------------*/
/* a 1D cubic bezier evaluator                                             */
/*-------------------------------------------------------------------------*/

/*! \ingroup group_animation
 *  \brief class OR_Evaluator_1D_Bezier in group group_animation
 */

/// a 1D bezier evaluator.
/** 
	A cubic bezier is defined by 4 points :
		- P0 start point.
		- P3 end point.
		- P0->P1 : start tangent.
		- P3->P2 : end tangent.
	\author Gabriel
*/
class ORION3D_API OR_Evaluator_1D_Bezier: public OR_Evaluator_1D
{

public:

	/** force the computation of the whole curve values */
	void Initialize(OR_Float P0, OR_Vector2D P1, OR_Vector2D P2, OR_Float P3);

};

/*-------------------------------------------------------------------------*/
/*                        class OR_Evaluator_1D_TCB                        */
/*-------------------------------------------------------------------------*/
/* a 1D cubic TCB evaluator                                                */
/*-------------------------------------------------------------------------*/

/*! \ingroup group_animation
 *  \brief class OR_Evaluator_1D_Bezier in group group_animation
 */

/// a 1D TCB evaluator.
/** 
	TCB curves are also called Kochanek-Bartels Splines [KBS].
	They introduced three control-values for each keyframe point:
		- Tension: How sharply does the curve bend? 
		- Continuity: How hard is the change of speed and direction? 
		- Bias: How is the direction of the curve as it passes through the keypoint.

	First, here are the equation for hermite curves :
	To calculate a hermite curve you need the following vectors: 
		- P1: the startpoint of the curve 
		- T1: the tangent (e.g. direction and speed) how the curve lefts the startpoint 
		- P2: he endpoint of the curve 
		- T2: the tangent (e.g. direction and speed) how the curves enters the endpoint

	These 4 vectors are simply multiplied with 4 hermite basis functions and summed together.
		- h1(s) =  2s^3 - 3s^2 + 1
		- h2(s) = -2s^3 + 3s^2
		- h3(s) =   s^3 - 2s^2 + s
		- h4(s) =   s^3 -  s^2
*/
/*
	Then, here are the equation to compute TD1 and TS2 :
	The "incomming" Tangent equation:


	          (1-t)*(1-c)*(1+b)                            (1-t)*(1+c)*(1-b)
	TS    =   -----------------  * ( P   -  P    )     +   -----------------  * ( P   -  P    )
	  i              2                i      i-1                  2                i+1    i


	The "outgoing" Tangent equation:

	          (1-t)*(1+c)*(1+b)                            (1-t)*(1-c)*(1-b)
	TD    =   -----------------  * ( P   -  P    )     +   -----------------  * ( P   -  P    )
	  i              2                i      i-1                  2                i+1    i

	
	      
	                

	When you want to interpolate the curve you should use this vector:

	    |  P(i)    |
	C = |  P(i+1)  |
	    |  TD(i)   |
	    |  TS(i+1) |

	\author Gabriel  	
*/
class ORION3D_API OR_Evaluator_1D_TCB: public OR_Evaluator_1D
{
public:
	/** force the computation of the whole curve values */
	void Initialize(OR_Float P0, OR_Float P1, OR_Float P2, OR_Float P3,
					OR_Float T1, OR_Float C1, OR_Float B1,
					OR_Float T2, OR_Float C2, OR_Float B2);
};


} // namespace OR

#endif /* #ifndef _OR_EVALUATOR_H_ */

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_license.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////