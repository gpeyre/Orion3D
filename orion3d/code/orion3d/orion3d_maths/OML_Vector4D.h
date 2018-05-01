
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Vector4D.h
 *  \brief Definition of class \c OML_Vector4D
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_Vector4D_h_
#define __OML_Vector4D_h_

#include "OML_Config.h"
#include "OML_Maths.h"

namespace OML {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_Vector4D
 *  \brief  A 4D vector, with usefull operators and methods.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	This class is used every where ...
 *	A constructor makes the conversion OML_Float[4] -> OML_Vector4D
 *	A lot of operator have been defined to make common maths operations, so use them !
 */ 
/*------------------------------------------------------------------------------*/

class OML_Vector4D
{

public:

	//-------------------------------------------------------------------------
    /** \name constructors/destructor  */
    //-------------------------------------------------------------------------
    //@{
	OML_Vector4D();
	OML_Vector4D(OML_Float, OML_Float, OML_Float, OML_Float);
	OML_Vector4D(OML_Float);
	OML_Vector4D(OML_Float*);
	virtual ~OML_Vector4D();
    //@}

	/** Substraction
		\return The vector this minus the vector \a V
		\param V Vector to substract */
	OML_Vector4D	operator-(OML_Vector4D V)
	{ return OML_Vector4D(Coords[R]-V.Coords[R],Coords[1]-V.Coords[1],
						 Coords[B]-V.Coords[B],Coords[A]-V.Coords[A]); }

	/** Addition
		\return The vector this plus the vector \a V
		\param V Vector to add */
	OML_Vector4D	operator+(OML_Vector4D V)
	{ return OML_Vector4D(Coords[R]+V.Coords[R],Coords[1]+V.Coords[1],
						 Coords[B]+V.Coords[B],Coords[A]+V.Coords[A]); }

	/** Inversion
		\return The vector inverted **/
	OML_Vector4D	operator-()
	{ return OML_Vector4D(-Coords[R],-Coords[1],-Coords[B],-Coords[A]); }

	/** Multiplication
		\return The vector this multplied by \a f
		\param f The OML_Float to multiply the vector by */
	OML_Vector4D	operator*(OML_Float f)
	{ return OML_Vector4D(Coords[R]*f,Coords[1]*f,Coords[B]*f,Coords[A]*f); }

	/** Comparison
		\return false if the 2 vectors are the same (with an error of \a EPSILON)
		\param V The vector to compare to */
	OML_Bool operator!=(OML_Vector4D V)
	{
		if (fabs(Coords[R]-V.Coords[R])>OML_EPSILON) return true;
		if (fabs(Coords[1]-V.Coords[1])>OML_EPSILON) return true;
		if (fabs(Coords[B]-V.Coords[B])>OML_EPSILON) return true;
		if (fabs(Coords[A]-V.Coords[A])>OML_EPSILON) return true;
		return false;
	}

	/** Comparison
		\return true if the 2 vectors are the same (with an error of \a EPSILON)
		\param V The vector to compare to */
	OML_Bool operator==(OML_Vector4D V)
	{
		if (fabs(Coords[R]-V.Coords[R])>OML_EPSILON) return false;
		if (fabs(Coords[1]-V.Coords[1])>OML_EPSILON) return false;
		if (fabs(Coords[B]-V.Coords[B])>OML_EPSILON) return false;
		if (fabs(Coords[A]-V.Coords[A])>OML_EPSILON) return false;
		return true;
	}

	/** Division
		Divide the vector by \a f
		\param f The OML_Float to divide the vector by */
	void operator/=(OML_Float f)
	{ Coords[R]/=f; Coords[1]/=f; Coords[B]/=f; Coords[A]/=f; }

	/** Division
		\return The vector divided by \a f
		\param f The OML_Float to divide the vector by */
	OML_Vector4D	operator/(OML_Float f)
	{ return OML_Vector4D(Coords[R]/f, Coords[1]/f, Coords[B]/f, Coords[A]/f); }

	/** Mulitplication
		Mulitply the vector by \a f
		\param f The OML_Float to multiply the vector by */
	void operator*=(OML_Float f)
	{ Coords[R]*=f; Coords[1]*=f; Coords[B]*=f; Coords[A]*=f; }


	/** Addition
		Add the vector \a V to the vector this
		\param V The vector to add */
	void operator+=(OML_Vector4D V)
	{ Coords[R]+=V.Coords[R]; Coords[1]+=V.Coords[1]; 
	  Coords[B]+=V.Coords[B]; Coords[A]+=V.Coords[A];}

	/** Substraction
		Substract the vector \a V to the vector this
		\param V The vector to substract */
	void operator-=(OML_Vector4D V)
	{ Coords[R]-=V.Coords[R]; Coords[1]-=V.Coords[1]; 
	  Coords[B]-=V.Coords[B]; Coords[A]-=V.Coords[A];}

	/** Get a coordinate
		\return The specified coordinate of the vector. As it is a reference, you can modify it
		\param i The coordinate to retrieve (0=x, 1=y) */
	OML_Float& operator[](OML_U32 i)
	{ return Coords[i]; }

	/** get a pointer to the 3 coordonates of the vector */
	OML_Float* GetCoord()
	{ return (OML_Float*) Coords; }
	const OML_Float* GetCoord() const
	{ return (OML_Float*) Coords; }
	OML_Float* GetData(void) const
	{ return (OML_Float*) Coords; }

	/** set the 4 coordonates of the vector */
	void SetCoord(OML_Float *c);
	void SetCoord(float x, float y, float z, float w);
	void SetCoord(float xyzw);

protected:
	
	/** coordonates of the vector (can be R|G|B|A) */
	OML_Float Coords[4];

};

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_Vector4D.inl"
#endif


#endif // __OML_Vector4D_h_

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

