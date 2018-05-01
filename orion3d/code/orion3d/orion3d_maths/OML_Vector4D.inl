/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Vector4D.inl
 *  \brief Inlined methods for \c OML_Vector4D
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_Vector4D.h"

namespace OML {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector4D constructor
 *
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Base constructor. Do nothing.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector4D::OML_Vector4D()
{ 
	Coords[0] = Coords[1] = Coords[2] = Coords[3] = 0; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector4D constructor
 *
 *  \param  a X value of the vector.
 *  \param  b Y value of the vector.
 *  \param  c Z value of the vector.
 *  \param  c W value of the vector.
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Initializes the vector with the values given
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector4D::OML_Vector4D(OML_Float a, OML_Float b, OML_Float c, OML_Float d)
{ 
	Coords[X] = a;
	Coords[Y] = b;
	Coords[Z] = c;
	Coords[3] = d;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector4D constructor
 *
 *  \param  v value to set to each coords.
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Initializes the vector with the value given.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector4D::OML_Vector4D(OML_Float v)
{
	Coords[X] = Coords[Y] = Coords[Z] = Coords[3] = v; 
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector4D constructor
 *
 *  \param  c A OML_Float pointer pointing at the 3 values (x,y,z)
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Initializes the vector with the values given.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector4D::OML_Vector4D(OML_Float* c)
{ 
	OML_ASSERT( c!=NULL );
	memcpy(Coords,c,4*sizeof(OML_Float) ); 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector4D destructor
 *
 *  \author Gabriel Peyré 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector4D::~OML_Vector4D()
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
void OML_Vector4D::SetCoord(OML_Float *c)
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
 *  \param  w value of the w coordonate.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Assign a value to each coordonate.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector4D::SetCoord(float x, float y, float z, float w)
{
	Coords[X] = x;
	Coords[Y] = y;
	Coords[Z] = z;	
	Coords[W] = w;
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
void OML_Vector4D::SetCoord(float xyzw)
{
	Coords[X] = Coords[Y] = Coords[Z] = Coords[W] = xyzw;
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

