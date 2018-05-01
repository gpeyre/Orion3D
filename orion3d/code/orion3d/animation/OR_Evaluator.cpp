/*-------------------------------------------------------------------------*/
/*                            OR_Evaluator.cpp                             */
/*-------------------------------------------------------------------------*/
/* Definition of class to evaluate staticaly curves and surfaces, at a     */
/* given precision                                                         */
/*-------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Evaluator.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Evaluator.h"

namespace OR
{
	
/*-------------------------------------------------------------------------*/
/*                        class OR_Evaluator_1D                            */
/*-------------------------------------------------------------------------*/
/* super class for all 1D evaluator                                        */
/*-------------------------------------------------------------------------*/

OR_Evaluator_1D::OR_Evaluator_1D(OR_I32 precision)
:OR_Evaluator(precision)
{
	ValuesX=new OR_Float[Precision]; 
	ValuesY=new OR_Float[Precision];
	IsCompute=false;	
}


OR_Evaluator_1D::~OR_Evaluator_1D()
{
	OR_DELETE(ValuesX);
	OR_DELETE(ValuesY);
}

OR_Float OR_Evaluator_1D::Evaluate(OR_Float x)
{
	if( x<OR_EPSILON ) return ValuesY[0];

	if (!IsCompute)
	{
		/* the evaluator has not yet been initiated  */
		OR_Globals::MessageHandler()->Debug("OR_Evaluator_1D::Evaluate", 
						"The evaluator has not yet been initiated.");
						return OR_ERROR;
	}

	if( x<ValuesX[0] ) return ValuesY[0];

	OR_I32 i=1;
	while (i<=Precision-1)
	{
		if (x<ValuesX[i])
		{
			/* we have find the correct interval, so interpolate ! */
			OR_Float t=(x-ValuesX[i-1])/(ValuesX[i]-ValuesX[i-1]);
			return (1-t)*ValuesY[i-1]+t*ValuesY[i];
		}
		i++;
	}

	/* the value is after the last key frame */
	return ValuesY[Precision-1];
}


/*-------------------------------------------------------------------------*/
/*                        class OR_Evaluator_1D_Bezier                     */
/*-------------------------------------------------------------------------*/
/* a 1D cubic bezier evaluator                                             */
/*-------------------------------------------------------------------------*/

void OR_Evaluator_1D_Bezier::Initialize(OR_Float P0, OR_Vector2D P1, OR_Vector2D P2, OR_Float P3)
{
	/* TODO : use central differencing */
	OR_Float t=0;
	OR_Float step=(1.0f)/((OR_Float)Precision-1);
	OR_Float b0, b1, b2, b3;
	
	for (OR_I32 i=0; i<Precision; i++)
	{
		/* compute berstein values */
		b0=(1-t)*(1-t)*(1-t);
		b1=3*t*(1-t)*(1-t);
		b2=3*t*t*(1-t);
		b3=t*t*t;

		ValuesX[i]=        b1*P1[X] + b2*P2[X] + b3;
		ValuesY[i]=b0*P0 + b1*P1[Y] + b2*P2[Y] + b3*P3;

		t+=step;
	}

	IsCompute=true;
}

/*-------------------------------------------------------------------------*/
/*                        class OR_Evaluator_1D_TCB                        */
/*-------------------------------------------------------------------------*/
/* a 1D cubic TCB evaluator                                                */
/*-------------------------------------------------------------------------*/

void OR_Evaluator_1D_TCB::Initialize(OR_Float P0, OR_Float P1, OR_Float P2, OR_Float P3,
									 OR_Float T1, OR_Float C1, OR_Float B1,
									 OR_Float T2, OR_Float C2, OR_Float B2)
{
	OR_Float fact1, fact2;
	/* the "outgoing" first tangent */
	OR_Float TD1[2];
	/* the "incomming" second tangent */
	OR_Float TS2[2];
	/* compute TD1 */
	fact1=0.5f*(1-T1)*(1+C1)*(1+B1);
	fact2=0.5f*(1-T1)*(1+C1)*(1-B1);
	TD1[X] = fact1         + fact2;
	TD1[Y] = fact1*(P1-P0) + fact2*(P2-P1);
	/* compute TS2 */
	fact1=0.5f*(1-T2)*(1+C2)*(1+B2);
	fact2=0.5f*(1-T2)*(1-C2)*(1-B2);
	TS2[X] = fact1         + fact2;
	TS2[Y] = fact1*(P1-P0) + fact2*(P2-P1);
	/* compute the values using hermite interpolation */
	OR_Float t=0;
	OR_Float step=(1.0f)/((OR_Float)Precision-1);
	OR_Float h0, h1, h2, h3;
	
	for (OR_I32 i=0; i<Precision; i++)
	{
		/* compute berstein values */
		h0= 2*t*t*t - 3*t*t + 1;
		h1=-2*t*t*t + 3*t*t;
		h2=   t*t*t - 2*t*t  + t;
		h3=   t*t*t -   t*t;

		ValuesX[i]=        h1*TD1[X] + h2*TS2[X] + h3;
		ValuesY[i]=h0*P0 + h1*TD1[Y] + h2*TS2[Y] + h3*P3;

		t+=step;
	}

	IsCompute=true;
}

} // namespace OR

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