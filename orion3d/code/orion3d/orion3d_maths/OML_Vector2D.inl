/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Vector2D.inl
 *  \brief Inlined methods for \c OML_Vector2D
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_Vector2D.h"

namespace OML {



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector2D constructor
 *
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Base constructor. Do nothing.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector2D::OML_Vector2D()
{ 
	Coords[X] = Coords[Y] = 0; 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector2D constructor
 *
 *  \param  a X value of the vector.
 *  \param  b Y value of the vector.
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Initializes the vector with the values given
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector2D::OML_Vector2D(OML_Float a, OML_Float b)
{ 
	Coords[X] = a;
	Coords[Y] = b;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector2D constructor
 *
 *  \param  v value to set to each coords.
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Initializes the vector with the value given.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector2D::OML_Vector2D(OML_Float v)
{
	Coords[X] = Coords[Y] = v; 
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector2D constructor
 *
 *  \param  c A OML_Float pointer pointing at the 3 values (x,y,z)
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Initializes the vector with the values given.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector2D::OML_Vector2D(OML_Float* c)
{ 
	OML_ASSERT( c!=NULL );
	memcpy(Coords,c,2*sizeof(OML_Float)); 
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector2D destructor
 *
 *  \author Gabriel Peyré 2001-10-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Vector2D::~OML_Vector2D()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector::SetCoord
 *
 *  \param  c array of 2 floats [the 2 corrdonates]
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector2D::SetCoord(OML_Float *c)
{
	memcpy(Coords, c, sizeof(OML_Float)*2);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector::SetCoord
 *
 *  \param  x value of the x coordonate.
 *  \param  y value of the y coordonate.

 *  \author Gabriel Peyré 2001-09-10
 *
 *	Assign a value to each coordonate.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Vector2D::SetCoord(float x, float y)
{
	Coords[X] = x;
	Coords[Y] = y;
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
void OML_Vector2D::SetCoord(float xyz)
{
	Coords[X] = Coords[Y] = xyz;
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

