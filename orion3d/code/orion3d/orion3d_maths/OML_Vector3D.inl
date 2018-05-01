/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Vector3D.inl
 *  \brief Inlined methods for \c OML_Vector3D
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_Vector3D.h"

namespace OML {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D constructor
 *
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Base constructor. Do nothing.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector3D::OML_Vector3D()
{ 
	Coords[X] = Coords[Y] = Coords[Z] = 0; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D constructor
 *
 *  \param  v the original
 *  \author Gabriel Peyré 2001-12-12
 *
 *	Copy constructor.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector3D::OML_Vector3D( const OML_Vector3D& v)
{
	memcpy( Coords, v.Coords, 3*sizeof(OML_Float) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D constructor
 *
 *  \param  a X value of the vector.
 *  \param  b Y value of the vector.
 *  \param  c Z value of the vector.
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Initializes the vector with the values given
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector3D::OML_Vector3D(OML_Float a, OML_Float b, OML_Float c)
{ 
	Coords[X] = a;
	Coords[Y] = b;
	Coords[Z] = c; 
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D constructor
 *
 *  \param  v value to set to each coords.
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Initializes the vector with the value given.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector3D::OML_Vector3D(OML_Float v)
{
	Coords[X] = Coords[Y] = Coords[Z] = v; 
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D constructor
 *
 *  \param  c A OML_Float pointer pointing at the 3 values (x,y,z)
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Initializes the vector with the values given.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector3D::OML_Vector3D( const OML_Float* c)
{ 
	OML_ASSERT( c!=NULL );
	memcpy(Coords,c,12); 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D destructor
 *
 *  \author Gabriel Peyré 2001-10-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector3D::~OML_Vector3D()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector::SetCoord
 *
 *  \param  c array of 3 floats [the 3 corrdonates]
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector3D::SetCoord(OML_Float *c)
{
	memcpy(Coords,c,sizeof(OML_Float)*3);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector::SetCoord
 *
 *  \param  x value of the x coordonate.
 *  \param  y value of the y coordonate.
 *  \param  z value of the z coordonate.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Assign a value to each coordonate.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector3D::SetCoord(float x, float y, float z)
{
	Coords[X] = x;
	Coords[Y] = y;
	Coords[Z] = z;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector::SetCoord
 *
 *  \param  xyz value of the 3 coordonates.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Assign the same value to each coordonate.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector3D::SetCoord(float xyz)
{
	Coords[X] = Coords[Y] = Coords[Z] = xyz;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D::SetZero
 *
 *  \author Gabriel Peyré 2001-09-29
 *
 *	set the vector to zero.
 */
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector3D::SetZero()
{
	memset( this->GetData(), 0, 3*sizeof(OML_Float) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D::SetValue
 *
 *  \param  rVal the value to set to the vector.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector3D::SetValue(OML_Float rVal)
{
	this->SetCoord(rVal);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D::Randomize
 *
 *  \param  rMin=0 minimum value.
 *  \param  rMax=1 maximum value.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector3D::Randomize(OML_Float rMin, OML_Float rMax)
{
	for( OML_U32 i=0; i<3; ++i )
		this->SetData( i, rMin + OML_RAND*(rMax-rMin) );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D::GetData
 *
 *  \return The array of float of the vector.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float* OML_Vector3D::GetData() const
{
	return (OML_Float*) Coords;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D::GetData
 *
 *  \param  i offset in the vector.
 *  \return the value of the given coord.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_Vector3D::GetData(OML_I32 i) const
{
	OML_ASSERT( i<3 );
	return Coords[i];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D::SetData
 *
 *  \param  i offset in the vector.
 *  \param  rVal value to set to this coord.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector3D::SetData(OML_I32 i, OML_Float rVal)
{
	OML_ASSERT( i<3 );
	Coords[i] = rVal;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D::SetData
 *
 *  interpolate between two vectors.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE 
void OML_Vector3D::Interpolate(const OML_Vector3D& p1, const OML_Vector3D& p2, 
								OML_Float valp1, OML_Float valp2, OML_Float IsoLevel,
								OML_Vector3D& newvertex)
{
	OML_Float mu; 
	if( fabsf(IsoLevel-valp1) < OML_EPSILON )
	{
		newvertex = p1;
		return;
	}
	if( fabsf(IsoLevel-valp2) < OML_EPSILON )
	{
		newvertex = p2;
		return;
	}
	if( fabsf(valp1-valp2) < OML_EPSILON )
	{
		newvertex = p1;
		return;
	}
	mu = (IsoLevel - valp1) / (valp2 - valp1); 
	newvertex = p1 + (p2 - p1)*mu;
}

} // End namespace OML

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

