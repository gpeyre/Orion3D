/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_MatrixNxP.cpp
 *  \brief Definition of class \c OML_MatrixNxP
 *  \author Gabriel Peyré 2001-09-18
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OML_SCCSID
static const char* sccsid = "@(#) OML_MatrixNxP.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OML_SCCSID


#include "stdafx.h"
#include "OML_MatrixNxP.h"

#ifndef OML_USE_INLINE
	#include "OML_MatrixNxP.inl"
#endif

using namespace OML;

#define ACCESS(i, j) (j)+(i)*nNbrCols_

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::operator *
 *
 *  \param  m right hand side
 *  \return multiplication this*m
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_MatrixNxP OML_MatrixNxP::operator*(const OML_MatrixNxP& m)
{
	OML_ASSERT( this->GetNbrCols() == m.GetNbrRows() );
	OML_MatrixNxP Res( this->GetNbrRows(), m.GetNbrCols() );
	OML_MatrixNxP::Multiply( *this, m, Res );
	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::Multiply
 *
 *  \param  a right side
 *  \param  b left side
 *  \param  r result
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::Multiply(const OML_MatrixNxP& a, const OML_MatrixNxP& b, OML_MatrixNxP& r)
{
	OML_ASSERT( a.GetNbrCols() == b.GetNbrRows() );
	OML_ASSERT( r.GetNbrRows() == a.GetNbrRows() );
	OML_ASSERT( r.GetNbrCols() == b.GetNbrCols() );

	OML_Float rVal;

	for( OML_U32 i=0; i<r.GetNbrRows(); ++i )
	for( OML_U32 j=0; j<r.GetNbrCols(); ++j )
	{
		rVal = 0;
		for( OML_U32 k=0; k<a.GetNbrCols(); ++k )
			rVal += a.GetData(i,k) * b.GetData(k,j);
		r.SetData( i,j, rVal );
	}
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::*=
 *
 *  \param  m right side
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void  OML_MatrixNxP::operator*=(const OML_MatrixNxP & m)
{
	OML_MatrixNxP Tmp( this->GetNbrRows(), this->GetNbrCols() );
	OML_MatrixNxP::Multiply( *this, m, Tmp );
	(*this) = Tmp;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::operator
 *
 *  \param  v right hand statement.
 *  \return the vector multiplied by the matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_VectorND OML_MatrixNxP::operator*(const OML_VectorND& v)
{
	OML_VectorND Res( this->GetNbrRows() );
	OML_MatrixNxP::Multiply( *this, v, Res );
	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::Multiply
 *
 *  \param  a left hand statement.
 *  \param  v Right hand statement.
 *  \param  r Result.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Multiply the vector by the matrix.
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::Multiply(const OML_MatrixNxP& a, const OML_VectorND& v, OML_VectorND& r)
{
	OML_ASSERT( a.GetNbrRows() == r.GetDim() );
	OML_ASSERT( a.GetNbrCols() == v.GetDim() );
	
	OML_Float rVal;

	for( OML_U32 i=0; i<r.GetDim(); ++i )
	{
		rVal = 0;
		for( OML_U32 j=0; j<v.GetDim(); ++j )
			rVal += a.GetData(i,j) * v.GetData(j);
			
		r.SetData( i, rVal );
	}

}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::Transpose
 *
 *  \return Transposed matrix.
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_MatrixNxP OML_MatrixNxP::Transpose()
{
	OML_MatrixNxP Res( this->GetNbrCols(), this->GetNbrRows() );
	OML_MatrixNxP::Transpose( *this, Res );

	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::Transpose
 *
 *  \param  a Right side
 *  \param  r Result
 *  \return Transposed matrix.
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::Transpose(const OML_MatrixNxP& a, OML_MatrixNxP& r)
{
	OML_ASSERT( a.GetNbrCols()==r.GetNbrRows() &&  r.GetNbrCols()==r.GetNbrRows() );
	
	OML_Float* aData = a.GetData();
	OML_Float* rData = r.GetData();
	
	for( OML_U32 i=0; i<a.GetNbrRows(); ++i )
	for( OML_U32 j=0; j<a.GetNbrCols(); ++j )
	{
		r.SetData(i,j, a.GetData(j,i) );
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::operator +
 *
 *  \param  m Right side
 *  \return this+a
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_MatrixNxP  OML_MatrixNxP::operator+(const OML_MatrixNxP & m)
{
	OML_MatrixNxP Res( this->GetNbrRows(), this->GetNbrCols() );
	OML_MatrixNxP::Add( *this, m, Res );
	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::Add
 *
 *  \param  a left hand side
 *  \param  b right hand side
 *  \param  r result = a+b
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::Add(const OML_MatrixNxP& a, const OML_MatrixNxP& b, OML_MatrixNxP& r)
{
	OML_ASSERT( a.GetNbrCols()==b.GetNbrCols() &&  a.GetNbrRows()==b.GetNbrRows() );
	OML_ASSERT( a.GetNbrCols()==r.GetNbrCols() &&  a.GetNbrRows()==r.GetNbrRows() );
	
	OML_Float* aData = a.GetData();
	OML_Float* bData = b.GetData();
	OML_Float* rData = r.GetData();
	
	for( OML_U32 i=0; i<a.GetNbrRows(); ++i )
	for( OML_U32 j=0; j<a.GetNbrCols(); ++j )
		r.SetData(i,j, a.GetData(i,j)+b.GetData(i,j) );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::operator -
 *
 *  \param  m Right side
 *  \return this-a
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_MatrixNxP  OML_MatrixNxP::operator-(const OML_MatrixNxP & m)
{
	OML_MatrixNxP Res( this->GetNbrRows(), this->GetNbrCols() );
	OML_MatrixNxP::Minus( *this, m, Res );
	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::Minus
 *
 *  \param  a left hand side
 *  \param  b right hand side
 *  \param  r result = a-b
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::Minus(const OML_MatrixNxP& a, const OML_MatrixNxP& b, OML_MatrixNxP& r)
{
	OML_ASSERT( a.GetNbrCols()==b.GetNbrCols() &&  a.GetNbrRows()==b.GetNbrRows() );
	OML_ASSERT( a.GetNbrCols()==r.GetNbrCols() &&  a.GetNbrRows()==r.GetNbrRows() );
	
	OML_Float* aData = a.GetData();
	OML_Float* bData = b.GetData();
	OML_Float* rData = r.GetData();
	
	for( OML_U32 i=0; i<a.GetNbrRows(); ++i )
	for( OML_U32 j=0; j<a.GetNbrCols(); ++j )
		r.SetData(i,j, a.GetData(i,j)-b.GetData(i,j) );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::operator -
 *
 *  \return -this
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_MatrixNxP  OML_MatrixNxP::operator-()
{
	OML_MatrixNxP Res( this->GetNbrRows(), this->GetNbrCols() );
	OML_MatrixNxP::UMinus( *this, Res );
	return Res;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::UMinus
 *
 *  \param  a right side
 *  \param  r result
 *  \author Gabriel Peyré 2001-09-19
 *
 *	unary minus.
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::UMinus(const OML_MatrixNxP& a, OML_MatrixNxP& r)
{
	OML_ASSERT( a.GetNbrCols()==r.GetNbrCols() &&  a.GetNbrRows()==r.GetNbrRows() );
	
	OML_Float* aData = a.GetData();
	OML_Float* rData = r.GetData();
	
	for( OML_U32 i=0; i<a.GetNbrRows(); ++i )
	for( OML_U32 j=0; j<a.GetNbrCols(); ++j )
		r.SetData(i,j, -a.GetData(i,j) );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::+=
 *
 *  \param  m right side
 *  \author Gabriel Peyré 2001-09-19
 *
 *	unary minus.
 */ 
/*------------------------------------------------------------------------------*/
void  OML_MatrixNxP::operator+=(const OML_MatrixNxP & m)
{
	OML_MatrixNxP Tmp( this->GetNbrRows(), this->GetNbrCols() );
	OML_MatrixNxP::Add( *this, m, Tmp );
	(*this) = Tmp;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::-=(const 
 *
 *  \param  m right side
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void  OML_MatrixNxP::operator-=(const OML_MatrixNxP & m)
{
	OML_MatrixNxP Tmp( this->GetNbrRows(), this->GetNbrCols() );
	OML_MatrixNxP::Minus( *this, m, Tmp );
	(*this) = Tmp;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::ClearUpperTriangle
 *
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::ClearUpperTriangle()
{
	/** \todo */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::ClearLowerTriangle
 *
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::ClearLowerTriangle()
{
	/** \todo */	
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::SetZero
 *
 *  \return set all component of the matrix to zero.
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::SetZero()
{
	OML_ASSERT( nNbrCols_>0 && nNbrRows_>0 );
	memset( aData_, 0, nNbrRows_*nNbrCols_*sizeof(OML_Float) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::SetValue
 *
 *  \param  rVal value to set.
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::SetValue(OML_Float rVal)
{	
	OML_ASSERT( nNbrCols_>0 && nNbrRows_>0 );	
	for( OML_U32 i=0; i<this->GetNbrRows(); ++i )
	for( OML_U32 j=0; j<this->GetNbrCols(); ++j )
		this->SetData( i, j, rVal );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::Randomize
 *
 *  \param  rMin minimum value
 *  \param  rMax maximum value
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::Randomize(OML_Float rMin, OML_Float rMax)
{
	OML_ASSERT( nNbrCols_>0 && nNbrRows_>0 );	
	for( OML_U32 i=0; i<this->GetNbrRows(); ++i )
	for( OML_U32 j=0; j<this->GetNbrCols(); ++j )
		this->SetData( i, j, rMin + OML_RAND*(rMax-rMin) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::Print
 *
 *  \param  cFormat Format of the real number
 *  \param  f file to print to
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::Print(char *cFormat, FILE *f)
{
	fprintf(f, "--- Matrix --- dim i=%i  j=%i ---\n", this->GetNbrRows(), this->GetNbrCols() );
	for( OML_U32 i=0; i<this->GetNbrRows(); ++i )
	{
		for( OML_U32 j=0; j<this->GetNbrCols(); ++j )
		{
			fprintf(f, " %.3f", this->GetData(i,j) );	
		}
		fprintf(f, "\n");
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OML_MatrixNxP::GaussSeidelStep(OR_VectorND& x, const OR_VectorND& b) const
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	Perform a step in the Gauss-Seidel resolution of M*x = b.
 *
 *	The more diagonal dominant the matrix is, the speeder the algorithm will converge.
 */ 
/*------------------------------------------------------------------------------*/
void OML_MatrixNxP::GaussSeidelStep(OML_VectorND& x, const OML_VectorND& b) const
{
	/* check the sizes */
	OML_U32 n = this->GetNbrCols();
	OML_ASSERT( this->GetNbrRows()==n );
	OML_ASSERT( x.GetDim()==n );
	OML_ASSERT( b.GetDim()==n );
	OML_Float temp;
	OML_U32 i, j;
	for( i=0; i<n; ++i )
	{
		temp = b.GetData(i);
		for( j=0; j<i; ++j )
			temp -= this->GetData(i,j)*x.GetData(j);
		for( j=i+1; j<n; ++j )
			temp -= this->GetData(i,j)*x.GetData(j);
		if( OML_ABS( this->GetData(i,i) ) > OML_EPSILON )
		{
			temp /= this->GetData(i,i);
			x.SetData(i, temp);
		}
	}
}



#undef ACCESS

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

