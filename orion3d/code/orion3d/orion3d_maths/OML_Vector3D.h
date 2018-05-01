
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Vector3D.h
 *  \brief Definition of class \c OML_Vector3D
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_Vector3D_h_
#define __OML_Vector3D_h_

#include "OML_Config.h"
#include "OML_Maths.h"
#include "OML_Matrix3x3.h"

namespace OML {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_Vector3D
 *  \brief  A 3D vector, with usefull operators and methods.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	This class is used every where ...
 *	A constructor makes the conversion OML_Float[3] -> OML_Vector3D
 *	A lot of operator have been defined to make common maths operations, so use them !
 */ 
/*------------------------------------------------------------------------------*/

class OML_Vector3D
{

public:

	/** Substraction
		@return The vector this minus the vector \a V
		@param V Vector to substract
	**/
	OML_Vector3D operator-( const OML_Vector3D& V) const
	{ return OML_Vector3D(Coords[0]-V.Coords[0],Coords[1]-V.Coords[1],Coords[2]-V.Coords[2]); }
	/** Addition
		@return The vector this plus the vector \a V
		@param V Vector to add
	**/
	 OML_Vector3D operator+( const OML_Vector3D& V) const
	{ return OML_Vector3D(Coords[0]+V.Coords[0], Coords[1]+V.Coords[1], Coords[2]+V.Coords[2]); }
	/** Inversion
		@return The vector inverted
	**/
	OML_Vector3D operator-() const
	{ return OML_Vector3D(-Coords[0],-Coords[1],-Coords[2]); }
	/** Dot Product
		@return The dot product between this and \a V
		@param V second vector of the dot product
	*/
	OML_Float operator*( const OML_Vector3D& V) const
	{ return Coords[0]*V.Coords[0] + Coords[1]*V.Coords[1] + Coords[2]*V.Coords[2]; }
	/** Length
		@return The length of the vector
	**/
	OML_Float operator~() const
	{ 
		// return OML_Maths::norm(Coords[0], Coords[1], Coords[2]); 
		return (OML_Float) ::sqrt( Coords[0]*Coords[0] + Coords[1]*Coords[1] + Coords[2]*Coords[2] ); 
	}
	/** Cross Product
		@return The cross product between this and \a V
		@param V second vector of the cross product
	**/
	 OML_Vector3D operator^( const OML_Vector3D& V) const
	{
		return OML_Vector3D(Coords[1]*V.Coords[2] - Coords[2]*V.Coords[1],
			Coords[2]*V.Coords[0] - Coords[0]*V.Coords[2],
			Coords[0]*V.Coords[1] - Coords[1]*V.Coords[0]);
	}
	/** Multiplication
		@return The vector this multplied by \a f
		@param f The OML_Float to multiply the vector by
	**/
	 OML_Vector3D operator*( OML_Float f ) const
	{ return OML_Vector3D(Coords[0]*f,Coords[1]*f,Coords[2]*f); }
	/** Normalisation
		@return The vector normalised (i.e. with a length of 1)
	**/
	 OML_Vector3D operator!() const
	{
		OML_Float n = OML_Maths::norm(Coords[0], Coords[1], Coords[2]);
		OML_Float d;
		if (n!=0) d=1/n;
		else d=0;
		return OML_Vector3D(Coords[0]*d,Coords[1]*d,Coords[2]*d);
	}

	/** Comparison
		@return false if the 2 vectors are the same (with an error of \a EPSILON)
		@param V The vector to compare to
	**/
	 OML_Bool operator!=( const OML_Vector3D& V) const 
	{
		if (fabs(Coords[0]-V.Coords[0])>OML_EPSILON) return true;
		if (fabs(Coords[1]-V.Coords[1])>OML_EPSILON) return true;
		if (fabs(Coords[2]-V.Coords[2])>OML_EPSILON) return true;
		return false;
	}

	/** Comparison
		@return true if the 2 vectors are the same (with an error of \a EPSILON)
		@param V The vector to compare to
	**/
	 OML_Bool operator==( const OML_Vector3D& V) const 
	{
		if (fabs(Coords[0]-V.Coords[0])>OML_EPSILON) return false;
		if (fabs(Coords[1]-V.Coords[1])>OML_EPSILON) return false;
		if (fabs(Coords[2]-V.Coords[2])>OML_EPSILON) return false;
		return true;
	}

	/** Division
		Divide the vector by \a f
		@param f The OML_Float to divide the vector by
	**/
	 void operator/=(OML_Float f)
	{
		Coords[0]/=f;
		Coords[1]/=f;
		Coords[2]/=f;
	}

	/** Division
		@return The vector divided by \a f
		@param f The OML_Float to divide the vector by
	**/
	 OML_Vector3D	operator/(OML_Float f) const 
	{ return OML_Vector3D(Coords[0]/f, Coords[1]/f, Coords[2]/f); }

	/** Mulitplication
		Mulitply the vector by \a f
		@param f The OML_Float to multiply the vector by
	**/
	void operator*=(OML_Float f)
	{
		Coords[0]*=f;
		Coords[1]*=f;
		Coords[2]*=f;
	}

	/** Addition
		Add the vector \a V to the vector this
		@param V The vector to add
	**/
    void operator+=( const OML_Vector3D& V)
	{
		Coords[0]+=V.Coords[0];
		Coords[1]+=V.Coords[1];
		Coords[2]+=V.Coords[2];
	}

	/** Substraction
		Substract the vector \a V to the vector this
		@param V The vector to substract
	**/
	void operator-=( const OML_Vector3D& V)
	{
		Coords[0]-=V.Coords[0];
		Coords[1]-=V.Coords[1];
		Coords[2]-=V.Coords[2];
	}
	
	/**	\return The specified coordinate of the vector. As it is a reference, you can modify it
		\param i The coordinate to retrieve (0=x, 1=y, 2=z)
	**/
	OML_Float& operator[](OML_U32 i)		//< coordonées
	{ return Coords[i]; }

	/** @return The specified coordinate of the vector. As it is a const reference, you cannot modify it
		@param i The coordinate to retrieve (0=x, 1=y, 2=z)
	**/
	const OML_Float& operator[](OML_U32 i) const		//< coordonées
	{ return Coords[i]; }

	/** Normalizes the vector (lentgh = 1) */
	void Normalize()
	{
		OML_Float n = OML_Maths::norm(Coords[0], Coords[1], Coords[2]);
		if( n<OML_EPSILON )
		{
			Coords[0] = 1;
			Coords[1] = 0;
			Coords[2] = 0;
		}
		else
		{
			n = 1/n;
			Coords[0] *= n;
			Coords[1] *= n;
			Coords[2] *= n;
		}
	}

	/** compute the square of the norm */
	OML_Float SquareNorm() const
	{ 
		return Coords[X]*Coords[X]+Coords[Y]*Coords[Y]+Coords[Z]*Coords[Z]; 
	}
	
	/** return a pointer on the vector datas */
	const OML_Float* GetCoord(void) const
	{ return Coords; }

	static void Interpolate(const OML_Vector3D& p1, const OML_Vector3D& p2, 
					OML_Float valp1,OML_Float valp2, OML_Float IsoLevel,
					OML_Vector3D& newvertex);

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	void SetCoord(OML_Float *c);
	void SetCoord(float x, float y, float z);
	void SetCoord(float xyz);

	OML_Float*	GetData() const;
	OML_Float	GetData(OML_I32 i) const;
	void		SetData(OML_I32 i, OML_Float rVal);
    //@}

	//-------------------------------------------------------------------------
    /** \name Utility */
    //-------------------------------------------------------------------------
    //@{
	void SetZero();
	void SetValue(OML_Float rVal);
	void Randomize(OML_Float rMin=0, OML_Float rMax=1);
	void Print(char *cFormat = "%10.4f ", FILE *f=stdout);
    //@}


	OML_Matrix3x3 CrossProductMatrix();

    //-------------------------------------------------------------------------
    /** \name constructors/destructor  */
    //-------------------------------------------------------------------------
    //@{
	OML_Vector3D();
	OML_Vector3D( const OML_Vector3D& v );
	OML_Vector3D(OML_Float, OML_Float, OML_Float);
	OML_Vector3D(OML_Float);
	OML_Vector3D( const OML_Float*);
	virtual ~OML_Vector3D();
    //@}

protected:
	
	/** Space coords (x,y,z) of the vector  */
	OML_Float		Coords[3];

};

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_Vector3D.inl"
#endif


#endif // __OML_Vector3D_h_

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

