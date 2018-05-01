/*------------------------------------------------------------------------------*/
/** 
 *  \file  FSW_Vector3D.inl
 *  \brief Inlined methods for \c FSW_Vector3D
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
#include "FSW_Vector3D.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector::SetCoord
 *
 *  \param  c array of 3 floats [the 3 corrdonates]
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_Vector3D::SetCoord(FSW_Float *c)
{
	memcpy(Coords,c,sizeof(FSW_Float)*3);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector::SetCoord
 *
 *  \param  x value of the x coordonate.
 *  \param  y value of the y coordonate.
 *  \param  z value of the z coordonate.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Assign a value to each coordonate.
 */ 
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_Vector3D::SetCoord(FSW_Float x, FSW_Float y, FSW_Float z)
{
	Coords[X] = x;
	Coords[Y] = y;
	Coords[Z] = z;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector::SetCoord
 *
 *  \param  xyz value of the 3 coordonates.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Assign the same value to each coordonate.
 */ 
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_Vector3D::SetCoord(FSW_Float xyz)
{
	Coords[X] = Coords[Y] = Coords[Z] = xyz;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector3D::SetZero
 *
 *  \author Gabriel Peyré 2001-09-29
 *
 *	set the vector to zero.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_Vector3D::SetZero()
{
	memset( this->GetData(), 0, 3*sizeof(FSW_Float) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector3D::SetValue
 *
 *  \param  rVal the value to set to the vector.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_Vector3D::SetValue(FSW_Float rVal)
{
	this->SetCoord(rVal);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector3D::Randomize
 *
 *  \param  rMin=0 minimum value.
 *  \param  rMax=1 maximum value.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_Vector3D::Randomize(FSW_Float rMin, FSW_Float rMax)
{
	for( FSW_U32 i=0; i<3; ++i )
		this->SetData( i, rMin + FSW_RAND*(rMax-rMin) );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector3D::GetData
 *
 *  \return The array of FSW_Float of the vector.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Float* FSW_Vector3D::GetData() const
{
	return (FSW_Float*) Coords;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector3D::GetData
 *
 *  \param  i offset in the vector.
 *  \return the value of the given coord.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Float FSW_Vector3D::GetData(FSW_I32 i) const
{
	FSW_ASSERT( i<3 );
	return Coords[i];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector3D::SetData
 *
 *  \param  i offset in the vector.
 *  \param  rVal value to set to this coord.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_Vector3D::SetData(FSW_I32 i, FSW_Float rVal)
{
	FSW_ASSERT( i<3 );
	Coords[i] = rVal;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : FSW_Vector3D::SetData
 *
 *  interpolate between two vectors.
 */ 
/*------------------------------------------------------------------------------*/
FSW_INLINE 
void FSW_Vector3D::Interpolate(const FSW_Vector3D& p1, const FSW_Vector3D& p2, 
								FSW_Float valp1, FSW_Float valp2, FSW_Float IsoLevel,
								FSW_Vector3D& newvertex)
{
	FSW_Float mu; 
	if( FSW_ABS(IsoLevel-valp1) < FSW_EPSILON )
	{
		newvertex = p1;
		return;
	}
	if( FSW_ABS(IsoLevel-valp2) < FSW_EPSILON )
	{
		newvertex = p2;
		return;
	}
	if( FSW_ABS(valp1-valp2) < FSW_EPSILON )
	{
		newvertex = p1;
		return;
	}
	mu = (IsoLevel - valp1) / (valp2 - valp1); 
	newvertex = p1 + (p2 - p1)*mu;
}

FSW_END_NAMESPACE

///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

