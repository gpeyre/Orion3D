
/*------------------------------------------------------------------------------*/
/** 
 *  \file  FSW_Vector3D.h
 *  \brief Definition of class \c FSW_Vector3D
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __FSW_Vector3D_h_
#define __FSW_Vector3D_h_

#include "FSW_Config.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_Vector3D
 *  \brief  A 3D vector, with usefull operators and methods.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	This class is used every where ...
 *	A constructor makes the conversion FSW_Float[3] -> FSW_Vector3D
 *	A lot of operator have been defined to make common maths operations, so use them !
 */ 
/*------------------------------------------------------------------------------*/

class FSW_Vector3D
{

public:

    //-------------------------------------------------------------------------
    /** \name constructors/destructor  */
    //-------------------------------------------------------------------------
    //@{
	FSW_Vector3D()
	{ 
		Coords[X] = Coords[Y] = Coords[Z] = 0; 
	}
	FSW_Vector3D( const FSW_Vector3D& v )
	{
		memcpy( Coords, v.Coords, 3*sizeof(FSW_Float) );
	}
	FSW_Vector3D(FSW_Float a, FSW_Float b, FSW_Float c)
	{ 
		Coords[X] = a;
		Coords[Y] = b;
		Coords[Z] = c; 
	}
	virtual ~FSW_Vector3D(){}
    //@}

	/** Substraction
		@return The vector this minus the vector \a V
		@param V Vector to substract
	**/
	FSW_Vector3D operator-( const FSW_Vector3D& V) const
	{ return FSW_Vector3D(Coords[0]-V.Coords[0],Coords[1]-V.Coords[1],Coords[2]-V.Coords[2]); }
	/** Addition
		@return The vector this plus the vector \a V
		@param V Vector to add
	**/
	 FSW_Vector3D operator+( const FSW_Vector3D& V) const
	{ return FSW_Vector3D(Coords[0]+V.Coords[0], Coords[1]+V.Coords[1], Coords[2]+V.Coords[2]); }
	/** Inversion
		@return The vector inverted
	**/
	FSW_Vector3D operator-() const
	{ return FSW_Vector3D(-Coords[0],-Coords[1],-Coords[2]); }
	/** Dot Product
		@return The dot product between this and \a V
		@param V second vector of the dot product
	*/
	FSW_Float operator*( const FSW_Vector3D& V) const
	{ return Coords[0]*V.Coords[0] + Coords[1]*V.Coords[1] + Coords[2]*V.Coords[2]; }
	/** Length
		@return The length of the vector
	**/
	FSW_Float operator~() const
	{ 
		// return FSW_Maths::norm(Coords[0], Coords[1], Coords[2]); 
		return (FSW_Float) ::sqrt( Coords[0]*Coords[0] + Coords[1]*Coords[1] + Coords[2]*Coords[2] ); 
	}
	/** Cross Product
		@return The cross product between this and \a V
		@param V second vector of the cross product
	**/
	 FSW_Vector3D operator^( const FSW_Vector3D& V) const
	{
		return FSW_Vector3D(Coords[1]*V.Coords[2] - Coords[2]*V.Coords[1],
			Coords[2]*V.Coords[0] - Coords[0]*V.Coords[2],
			Coords[0]*V.Coords[1] - Coords[1]*V.Coords[0]);
	}
	/** Multiplication
		@return The vector this multplied by \a f
		@param f The FSW_Float to multiply the vector by
	**/
	 FSW_Vector3D operator*( FSW_Float f ) const
	{ return FSW_Vector3D(Coords[0]*f,Coords[1]*f,Coords[2]*f); }
	/** Normalisation
		@return The vector normalised (i.e. with a length of 1)
	**/
	 FSW_Vector3D operator!() const
	{
		FSW_Float n = this->Norm();
		FSW_Float d;
		if (n!=0) d=1/n;
		else d=0;
		return FSW_Vector3D(Coords[0]*d,Coords[1]*d,Coords[2]*d);
	}

	/** Comparison
		@return false if the 2 vectors are the same (with an error of \a EPSILON)
		@param V The vector to compare to
	**/
	 FSW_Bool operator!=( const FSW_Vector3D& V) const 
	{
		if (fabs(Coords[0]-V.Coords[0])>FSW_EPSILON) return true;
		if (fabs(Coords[1]-V.Coords[1])>FSW_EPSILON) return true;
		if (fabs(Coords[2]-V.Coords[2])>FSW_EPSILON) return true;
		return false;
	}

	/** Comparison
		@return true if the 2 vectors are the same (with an error of \a EPSILON)
		@param V The vector to compare to
	**/
	 FSW_Bool operator==( const FSW_Vector3D& V) const 
	{
		if (fabs(Coords[0]-V.Coords[0])>FSW_EPSILON) return false;
		if (fabs(Coords[1]-V.Coords[1])>FSW_EPSILON) return false;
		if (fabs(Coords[2]-V.Coords[2])>FSW_EPSILON) return false;
		return true;
	}

	/** Division
		Divide the vector by \a f
		@param f The FSW_Float to divide the vector by
	**/
	 void operator/=(FSW_Float f)
	{
		Coords[0]/=f;
		Coords[1]/=f;
		Coords[2]/=f;
	}

	/** Division
		@return The vector divided by \a f
		@param f The FSW_Float to divide the vector by
	**/
	 FSW_Vector3D	operator/(FSW_Float f) const 
	{ return FSW_Vector3D(Coords[0]/f, Coords[1]/f, Coords[2]/f); }

	/** Mulitplication
		Mulitply the vector by \a f
		@param f The FSW_Float to multiply the vector by
	**/
	void operator*=(FSW_Float f)
	{
		Coords[0]*=f;
		Coords[1]*=f;
		Coords[2]*=f;
	}

	/** Addition
		Add the vector \a V to the vector this
		@param V The vector to add
	**/
    void operator+=( const FSW_Vector3D& V)
	{
		Coords[0]+=V.Coords[0];
		Coords[1]+=V.Coords[1];
		Coords[2]+=V.Coords[2];
	}

	/** Substraction
		Substract the vector \a V to the vector this
		@param V The vector to substract
	**/
	void operator-=( const FSW_Vector3D& V)
	{
		Coords[0]-=V.Coords[0];
		Coords[1]-=V.Coords[1];
		Coords[2]-=V.Coords[2];
	}
	
	/**	\return The specified coordinate of the vector. As it is a reference, you can modify it
		\param i The coordinate to retrieve (0=x, 1=y, 2=z)
	**/
	FSW_Float& operator[](FSW_U32 i)		//< coordonées
	{ return Coords[i]; }

	/** @return The specified coordinate of the vector. As it is a const reference, you cannot modify it
		@param i The coordinate to retrieve (0=x, 1=y, 2=z)
	**/
	const FSW_Float& operator[](FSW_U32 i) const		//< coordonées
	{ return Coords[i]; }

	/** Normalizes the vector (lentgh = 1) */
	void Normalize()
	{
		FSW_Float n = this->Norm();
		if( n<FSW_EPSILON )
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

	FSW_Float Norm() const
	{
		return sqrt( Coords[0]*Coords[0] + Coords[1]*Coords[1] + Coords[2]*Coords[2] );
	}

	/** compute the square of the norm */
	FSW_Float SquareNorm() const
	{ 
		return Coords[X]*Coords[X]+Coords[Y]*Coords[Y]+Coords[Z]*Coords[Z]; 
	}
	
	/** return a pointer on the vector datas */
	const FSW_Float* GetCoord(void) const
	{ return Coords; }

	static void Interpolate(const FSW_Vector3D& p1, const FSW_Vector3D& p2, 
					FSW_Float valp1,FSW_Float valp2, FSW_Float IsoLevel,
					FSW_Vector3D& newvertex);

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	void SetCoord(FSW_Float *c);
	void SetCoord(FSW_Float x, FSW_Float y, FSW_Float z);
	void SetCoord(FSW_Float xyz);

	FSW_Float*	GetData() const;
	FSW_Float	GetData(FSW_I32 i) const;
	void		SetData(FSW_I32 i, FSW_Float rVal);
    //@}

	//-------------------------------------------------------------------------
    /** \name Utility */
    //-------------------------------------------------------------------------
    //@{
	void SetZero();
	void SetValue(FSW_Float rVal);
	void Randomize(FSW_Float rMin=0, FSW_Float rMax=1);
	void Print(char *cFormat = "%10.4f ", FILE *f=stdout);
    //@}


protected:
	
	/** Space coords (x,y,z) of the vector  */
	FSW_Float		Coords[3];

};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_Vector3D.inl"
#endif


#endif // __FSW_Vector3D_h_

///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

