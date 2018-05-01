/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_VectorND.cpp
 *  \brief Definition of class \c OML_VectorND
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OML_SCCSID
static const char* sccsid = "@(#) OML_VectorND.cpp (c) Gabriel Peyré & Antoine BouthOMLs 2001";
#endif // OML_SCCSID


#include "stdafx.h"
#include "OML_VectorND.h"

#ifndef OML_USE_INLINE
	#include "OML_VectorND.inl"
#endif

using namespace OML;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::operator
 *
 *  \param  f Rigth hand statement
 *  \return the vector scaled.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_VectorND OML_VectorND::operator*(const OML_Float& f) const
{
	OML_VectorND Res( this->GetDim() );
	OML_VectorND::Multiply( f, *this, Res );
	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::operator
 *
 *  \param  f Rigth hand statement
 *  \return the vector scaled.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_VectorND OML::operator*(const OML_Float& f, OML_VectorND& v)
{
	OML_VectorND Res( v.GetDim() );
	OML_VectorND::Multiply( f, v, Res );
	return Res;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::Multiply
 *
 *  \param  f left hand statement.
 *  \param  v right hand statement.
 *  \param  r vector v scaled by f.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
void OML_VectorND::Multiply(const OML_Float f, const OML_VectorND& v, OML_VectorND& r)
{
	OML_ASSERT( v.GetDim() == r.GetDim() );
	
	for( OML_U32 i=0; i<r.GetDim(); ++i )
		r.SetData( i, f*v.GetData(i) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::*=
 *
 *  \param  f scale factOML
 *  \author Gabriel Peyré 2001-09-29
 *
 *	Auto-scale the vector.
 */ 
/*------------------------------------------------------------------------------*/
void OML_VectorND::operator*=(const OML_Float & f)
{	
	OML_VectorND::Multiply( f, *this, *this );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::+ 
 *
 *  \param  v right hand statement
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_VectorND OML_VectorND::operator+(const OML_VectorND& v) const
{
	OML_VectorND Res( this->GetDim() );
	OML_VectorND::Add( *this, v, Res );
	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::Add
 *
 *  \param  a left hand statement
 *  \param  b right hand statement
 *  \param  r result
 *  \author Gabriel Peyré 2001-09-29
 *
 *	Add the two vectOMLs.
 */ 
/*------------------------------------------------------------------------------*/
void OML_VectorND::Add(const OML_VectorND& a, const OML_VectorND& b, OML_VectorND& r)
{
	OML_ASSERT( a.GetDim() == r.GetDim() );
	OML_ASSERT( b.GetDim() == r.GetDim() );
	
	for( OML_U32 i=0; i<r.GetDim(); ++i )
		r.SetData( i, a.GetData(i)+b.GetData(i) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::- 
 *
 *  \param  v right hand statement
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_VectorND  OML_VectorND::operator-(const OML_VectorND & v) const
{
	OML_VectorND Res( this->GetDim() );
	OML_VectorND::Minus( *this, v, Res );
	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::Minus
 *
 *  \param  a left hand statement
 *  \param  b right hand statement
 *  \param  r result
 *  \author Gabriel Peyré 2001-09-29
 *
 *	Substract the two vectOMLs.
 */ 
/*------------------------------------------------------------------------------*/
void OML_VectorND::Minus(const OML_VectorND& a, const OML_VectorND& b, OML_VectorND& r)
{
	OML_ASSERT( a.GetDim() == r.GetDim() );
	OML_ASSERT( b.GetDim() == r.GetDim() );
	
	for( OML_U32 i=0; i<r.GetDim(); ++i )
		r.SetData( i, a.GetData(i)-b.GetData(i) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : operator OML_VectorND::-
 *
 *  \return The opposite of the vector.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_VectorND  OML_VectorND::operator-() const
{
	OML_VectorND Res( this->GetDim() );
	OML_VectorND::UMinus( *this, Res );
	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::UMinus
 *
 *  \param  a right hand statement
 *  \param  r result
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
void OML_VectorND::UMinus(const OML_VectorND& a, OML_VectorND& r)
{
	OML_ASSERT( a.GetDim() == r.GetDim() );
	
	for( OML_U32 i=0; i<r.GetDim(); ++i )
		r.SetData( i, -a.GetData(i) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::+= 
 *
 *  \param  v rigth hand statement.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
void  OML_VectorND::operator+=(const OML_VectorND & v)
{	
	OML_VectorND::Add( *this, v, *this );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::-= 
 *
 *  \param  v rigth hand statement.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
void  OML_VectorND::operator-=(const OML_VectorND & v)
{
	OML_VectorND::Minus( *this, v, *this );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::* 
 *
 *  \param  v rigth hand statement.
 *	\return Dot product of the two vectOMLs.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_VectorND::operator*(const OML_VectorND& v)
{
	OML_ASSERT( this->GetDim() == v.GetDim() );
	
	OML_Float rDot=0;
	for( OML_U32 i=0; i<v.GetDim(); ++i )
		rDot += this->GetData(i)*v.GetData(i);

	return rDot;
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::SetZero
 *
 *  \author Gabriel Peyré 2001-09-29
 *
 *	set the vector to zero.
 */
/*------------------------------------------------------------------------------*/
void OML_VectorND::SetZero()
{
	if( this->GetDim()>0 )
		memset( this->GetData(), 0, this->GetDim()*sizeof(OML_Float) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::SetValue
 *
 *  \param  rVal the value to set to the vector.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
void OML_VectorND::SetValue(OML_Float rVal)
{
	if( this->GetDim()>0 )
	{
		for( OML_U32 i=0; i<this->GetDim(); ++i )
			this->SetData(i,rVal);
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::Randomize
 *
 *  \param  rMin=0 minimum value.
 *  \param  rMax=1 maximum value.
 *  \author Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
void OML_VectorND::Randomize(OML_Float rMin, OML_Float rMax)
{
	for( OML_U32 i=0; i<this->GetDim(); ++i )
		this->SetData( i, rMin + OML_RAND*(rMax-rMin) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::Print
 *
 *  \param  cFOMLmat FOMLmat of the real number
 *  \param  f file to print to
 *  \author Gabriel Peyré 2001-09-29
 *
 *	Print the vector to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OML_VectorND::Print(char *cFOMLmat, FILE *f)
{
	fprintf(f, "--- Vector --- dim %i ---\n", this->GetDim() );
	for( OML_U32 i=0; i<this->GetDim(); ++i )
	{
		fprintf(f, " %.3f", this->GetData(i) );	
	}
	fprintf(f, "\n");
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::SolveBiConjugateGradient
 *
 *  \param  b right hand side of the equation.
 *  \param  x solution of the problem. Should be set to an initial guess, for instance \c 0.
 *  \param  atimes user supplyed operation for multiplication of matrix \c A by a vector.
 *	\param  nNbrIterMax number maximum of iterations of the alOMLithm.
 *  \return true if the solution was found, false otherwise.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Solve the equation \c A*x=b, for \c A inversible.
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_VectorND::SolveBiConjugateGradient( const OML_VectorND& b, OML_VectorND& x, 
											   T_MatrixTimeVectOMLFunc atimes, T_MatrixTimeVectOMLFunc atransptimes, 
											   OML_I32 nNbrIterMax, OML_Float rPrecision )
{
	OML_U32 n = b.GetDim();
	OML_ASSERT( n>0 );
	OML_ASSERT( x.GetDim()==n );
	OML_I32 nNbrIter=0;

	if( nNbrIterMax<0 )
		nNbrIterMax = n+4;

	OML_Float rTmp = 0;
	OML_Float ak, bk;
	OML_VectorND aTimesPk(n);
	OML_VectorND aTranspTimesP1k(n);
	/* compute aTimesPk=A*x */
	atimes( x, aTimesPk );

	/* set rk=rk1=b-A*x1 */
	OML_VectorND rk  = b - aTimesPk;
	OML_VectorND r1k = rk;
	OML_VectorND pk  = rk;
	OML_VectorND p1k = rk;

	OML_Float rkTimesr1k = rk*r1k;

	while( rk.NormInf()>rPrecision ||  r1k.NormInf()>rPrecision )
	{
		if( nNbrIter>nNbrIterMax )
			return false;
		nNbrIter++;

		/*
			compute : 
			   	    r_k*r1_k
			a_k = ------------
				   p1_k*A*p_k

			r_(k+1)  = r_k - a_k.(A*p_k)
			r1_(k+1) = r1_k - a_k.(Atransp*p1_k)

		           r_(k+1)*r1_(k+1)
			b_k = ------------------
					  r_k*r1_k

  .
			p_(k+1)  = r_(k+1)  + b_k.p_k
			p1_(k+1) = r1_(k+1) + b_k.p1_k

			x_(k+1) = x_k + a_k.p_k
		*/
		
		/* aTimesPk=A*Pk */
		atimes( pk, aTimesPk );
		atransptimes( p1k, aTranspTimesP1k );

		/* compute ak */
		rTmp = p1k*aTimesPk;
		OML_ASSERT( rTmp!=0 );
		ak = rkTimesr1k/rTmp;

		/* compute next xk */
		x = x + ak*pk;

		/* compute next rk and r1k */
		rk  = rk  - ak*aTimesPk;
		r1k = r1k - ak*aTranspTimesP1k;

		/* compute bk */
		rTmp = rk * r1k;
		OML_ASSERT( rkTimesr1k!=0 );
		bk = rTmp/rkTimesr1k;

		/* compute next rkTimesr1k */
		rkTimesr1k = rTmp;

		/* compute next pk and p1k */
		pk  = rk  + bk*pk;
		p1k = r1k + bk*p1k;
	}

	return true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::SolveBiConjugateGradient
 *
 *  \param  b right hand side of the equation.
 *  \param  x solution of the problem. Should be set to an initial guess, for instance \c 0.
 *  \param  atimes user supplyed operation for multiplication of matrix \c A by a vector.
 *	\param  nNbrIterMax number maximum of iterations of the alOMLithm.
 *  \return true if the solution was found, false otherwise.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Solve the equation \c A*x=b, for \c A symetric positive definite.
 */ 
/*------------------------------------------------------------------------------*/
OML_Bool OML_VectorND::SolveConjugateGradient( const OML_VectorND& b, OML_VectorND& x,
											  T_MatrixTimeVectOMLFunc atimes, 
											  OML_I32 nNbrIterMax, OML_Float rPrecision )
{
	OML_U32 n = b.GetDim();
	OML_ASSERT( n>0 );
	OML_ASSERT( x.GetDim()==n );
	OML_I32 nNbrIter=0;

	if( nNbrIterMax<0 )
		nNbrIterMax = n+4;

	OML_Float rTmp = 0;
	OML_Float ak, bk;
	OML_VectorND aTimesPk(n);
	/* compute aTimesPk=A*x */
	atimes( x, aTimesPk );

	/* set rk=b-A*x1 */
	OML_VectorND rk  = b - aTimesPk;
	OML_VectorND pk  = rk;

	OML_Float rkTimesrk = rk*rk;

	while( rk.NormInf()>rPrecision )
	{
		if( nNbrIter>nNbrIterMax )
			return false;
		nNbrIter++;

		/*
			compute : 
			   	    r_k*r_k
			a_k = ------------
				   p_k*A*p_k

			r_(k+1)  = r_k - a_k.(A*p_k)

		           r_(k+1)*r_(k+1)
			b_k = ------------------
					  r_k*r_k

  .
			p_(k+1)  = r_(k+1)  + b_k.p_k

			x_(k+1) = x_k + a_k.p_k
		*/
		
		/* aTimesPk=A*Pk */
		atimes( pk, aTimesPk );

		/* compute ak */
		rTmp = pk*aTimesPk;
		OML_ASSERT( rTmp!=0 );
		ak = rkTimesrk/rTmp;

		/* compute next xk */
		x = x + ak*pk;

		/* compute next rk and r1k */
		rk  = rk  - ak*aTimesPk;

		/* compute bk */
		rTmp = rk * rk;
		OML_ASSERT( rkTimesrk!=0 );
		bk = rTmp/rkTimesrk;

		/* compute next rkTimesr1k */
		rkTimesrk = rTmp;

		/* compute next pk */
		pk  = rk  + bk*pk;
	}

	/* compute ak */
//	rTmp = pk*aTimesPk;
//	OML_ASSERT( rTmp!=0 );
//	ak = rkTimesrk/rTmp;
	
	/* compute next xk */
	x = x + ak*pk;

	return true;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::NormInf
 *
 *  \return Infinite norm of the vector.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	The infinte norm is the maximum of the absolute value of the coordonates.
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_VectorND::NormInf()
{
	OML_Float rNorm = 0;
	OML_Float rVal = 0;
	for( OML_U32 i=0; i<this->GetDim(); ++i )
	{
		rVal = this->GetData(i);
		if( rVal>rNorm )
			rNorm = rVal;
		if( -rVal>rNorm )
			rNorm = -rVal;
	}
	
	return rNorm;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::Norm2
 *
 *  \return Norm 2 of the vector.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	The eclidian norm of the vector.
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_VectorND::Norm2()
{
	OML_Float rNorm = 0;
	OML_Float rVal = 0;
	for( OML_U32 i=0; i<this->GetDim(); ++i )
	{
		rVal = this->GetData(i);
		rNorm += rVal*rVal;
	}
	
	return OML_Maths::sqrt( rNorm );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::Norm1
 *
 *  \return Norm 1 of the vector.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	The norm 1 is the sum of the absolute value of the coords.
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_VectorND::Norm1()
{
	OML_Float rNorm = 0;
	for( OML_U32 i=0; i<this->GetDim(); ++i )
		rNorm += OML_ABS( this->GetData(i) );
	
	return rNorm;
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The OMLion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the OMLion3D licence.                                  //
//  Refer to OMLion3d_licence.txt for mOMLe details about the OMLion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence OMLion3D.                              //
//  Se repOMLter a OMLion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

