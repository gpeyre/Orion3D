
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Vector2D.h
 *  \brief Definition of class \c OML_Vector2D
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_Vector2D_h_
#define __OML_Vector2D_h_

#include "OML_Config.h"
#include "OML_Maths.h"


namespace OML {
	
/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_Vector2D
 *  \brief  A 2D vector, with usefull operators and methods.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	This class is used every where ...
 *	A constructor makes the conversion OML_Float[2] -> OML_Vector2D
 *	A lot of operator have been defined to make common maths operations, so use them !
 */ 
/*------------------------------------------------------------------------------*/

class OML_Vector2D
{

public:

    //-------------------------------------------------------------------------
    /** \name constructors/destructor  */
    //-------------------------------------------------------------------------
    //@{
	OML_Vector2D();
	OML_Vector2D(OML_Float, OML_Float);
	OML_Vector2D(OML_Float);
	OML_Vector2D(OML_Float*);
	virtual ~OML_Vector2D();
    //@}


	/** Substraction
		\return The vector this minus the vector \a V
		\param V Vector to substract */
	OML_Vector2D	operator-(OML_Vector2D V)
	{ return OML_Vector2D(Coords[0]-V.Coords[0],Coords[1]-V.Coords[1]); }
	/** Addition
		\return The vector this plus the vector \a V
		\param V Vector to add */
	OML_Vector2D	operator+(OML_Vector2D V)
	{ return OML_Vector2D(Coords[0]+V.Coords[0], Coords[1]+V.Coords[1]); }
	/** Inversion
		\return The vector inverted**/
	OML_Vector2D	operator-()
	{ return OML_Vector2D(-Coords[0],-Coords[1]); }
	/** Dot Product
		\return The dot product between this and \a V
		\param V second vector of the dot product */
	OML_Float operator*(OML_Vector2D V)
	{ return Coords[0]*V.Coords[0] + Coords[1]*V.Coords[1]; }
	/** Length
		\return The length of the vector */
	OML_Float operator~()
	{ return OML_Maths::norm(Coords[0], Coords[1]); }
	/** Multiplication
		\return The vector this multplied by \a f
		\param f The OML_Float to multiply the vector by */
	OML_Vector2D	operator*(OML_Float f)
	{ return OML_Vector2D(Coords[0]*f,Coords[1]*f); }
	/** Normalisation
		\return The vector normalised (i.e. with a length of 1) */
	OML_Vector2D	operator!()
	{
		OML_Float n = OML_Maths::norm(Coords[0], Coords[1]);
		if (n!=0) n=1/n;
		return OML_Vector2D(Coords[0]*n,Coords[1]*n);
	}
	/** Comparison
		\return false if the 2 vectors are the same (with an error of \a EPSILON)
		\param V The vector to compare to */
	OML_Bool	operator!=(OML_Vector2D V)
	{
		if (fabs(Coords[0]-V.Coords[0])>OML_EPSILON) return true;
		if (fabs(Coords[1]-V.Coords[1])>OML_EPSILON) return true;
		return false;
	}
	/** Comparison
		\return true if the 2 vectors are the same (with an error of \a EPSILON)
		\param V The vector to compare to */
	OML_Bool	operator==(OML_Vector2D V)
	{
		if (fabs(Coords[0]-V.Coords[0])>OML_EPSILON) return false;
		if (fabs(Coords[1]-V.Coords[1])>OML_EPSILON) return false;
		return true;
	}
	/** Division
		Divide the vector by \a f
		\param f The OML_Float to divide the vector by */
	void	operator/=(OML_Float f)
	{ Coords[0]/=f; Coords[1]/=f; }
	/** Division
		\return The vector divided by \a f
		\param f The OML_Float to divide the vector by */
	OML_Vector2D	operator/(OML_Float f)
	{ return OML_Vector2D(Coords[0]/f, Coords[1]/f); }
	/** Mulitplication
		Mulitply the vector by \a f
		\param f The OML_Float to multiply the vector by */
	void operator*=(OML_Float f)
	{ Coords[0]*=f; Coords[1]*=f; }
	/** Addition
		Add the vector \a V to the vector this
		\param V The vector to add */
	void operator+=(OML_Vector2D V)
	{ Coords[0]+=V.Coords[0]; Coords[1]+=V.Coords[1]; }
	/** Substraction
		Substract the vector \a V to the vector this
		\param V The vector to substract */
	void operator-=(OML_Vector2D V)
	{ Coords[0]-=V.Coords[0]; Coords[1]-=V.Coords[1]; }
	/** Get a coordinate
		\return The specified coordinate of the vector. As it is a reference, you can modify it
		\param i The coordinate to retrieve (0=x, 1=y) */
	OML_Float& operator[](OML_U32 i)
	{ return Coords[i]; }
	/** Normalizes the vector (lentgh = 1) */
	void Normalize()
	{
		OML_Float n = OML_Maths::norm(Coords[0], Coords[1]);
		if (n!=0) n=1/n;
		Coords[0]*=n;
		Coords[1]*=n;
	}

	/** compute the square of the norm */
	OML_Float SquareNorm()
	{ return Coords[X]*Coords[X] + Coords[Y]*Coords[Y]; }

	/** get a pointer to the 3 coordonates of the vector */
	const OML_Float* GetCoord(void) const
	{ return Coords; }
	OML_Float* GetData(void) const
	{ return (OML_Float*) Coords; }

	/** set the 2 coordonates of the vector */
	void SetCoord(OML_Float *c);
	void SetCoord(float x, float y);
	void SetCoord(float xyz);

protected:

	/** space coordonates of the vector */
	OML_Float Coords[2];

};

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_Vector2D.inl"
#endif


#endif // __OML_Vector2D_h_

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

