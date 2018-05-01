/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_MatrixNxP.inl
 *  \brief Inlined methods for \c OML_MatrixNxP
 *  \author Gabriel Peyré 2001-09-18
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_MatrixNxP.h"

namespace OML {

#define ACCESS(i, j) (j)+(i)*nNbrCols_

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP constructor
 *
 *  \author Gabriel Peyré 2001-09-19
 *
 *	Base constructor, create a zero dimension matrix.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_MatrixNxP::OML_MatrixNxP()
:	nNbrRows_	( 0 ),
	nNbrCols_	( 0 ),
	aData_		( NULL )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP constructor
 *
 *  \param  nNbrRows number of rows of the matrix.
 *  \param  nNbrCols number of columns of the matrix.
 *  \author Gabriel Peyré 2001-09-19
 *
 *	Create a matrix with given size.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_MatrixNxP::OML_MatrixNxP(OML_U32 nNbrRows, OML_U32 nNbrCols)
:	nNbrRows_	( 0 ),
	nNbrCols_	( 0 ),
	aData_		( NULL )
{
	this->Reset( nNbrRows, nNbrCols );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP constructor
 *
 *  \param  m the original matrix.
 *  \author Gabriel Peyré 2001-09-19
 *
 *	Copy constructor.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_MatrixNxP::OML_MatrixNxP(const OML_MatrixNxP& m)
:	nNbrRows_	( 0 ),
	nNbrCols_	( 0 ),
	aData_		( NULL )
{
	if( m.GetData()==NULL )
	{
		OML_DELETEARRAY( aData_ );
		nNbrRows_ = nNbrCols_ = 0;
	}
	else
	{
		nNbrRows_ = m.GetNbrRows();
		nNbrCols_ = m.GetNbrCols();
		OML_ASSERT( nNbrCols_>0 && nNbrRows_>0 );
		OML_DELETEARRAY( aData_ );
		aData_ = new OML_Float[nNbrRows_*nNbrCols_];
		memcpy( aData_,  m.GetData(), nNbrRows_*nNbrCols_*sizeof(OML_Float) );
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::copy contuctor
 *
 *  \param  m the original matrix.
 *  \author Gabriel Peyré 2001-09-19
 *
 *	Copy operator.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_MatrixNxP& OML_MatrixNxP::operator=(const OML_MatrixNxP &m)
{
	if( m.GetData()==NULL )
	{
		OML_DELETEARRAY( aData_ );
		nNbrRows_ = nNbrCols_ = 0;
	}
	else
	{
		nNbrRows_ = m.GetNbrRows();
		nNbrCols_ = m.GetNbrCols();
		OML_ASSERT( nNbrCols_>0 && nNbrRows_>0 );
		OML_DELETEARRAY( aData_ );
		aData_ = new OML_Float[nNbrRows_*nNbrCols_];
		memcpy( aData_,  m.GetData(), nNbrRows_*nNbrCols_*sizeof(OML_Float) );
	}

	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP destructor
 *
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_MatrixNxP::~OML_MatrixNxP()
{
	OML_DELETEARRAY( aData_ );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::GetNbrRows
 *
 *  \return The number of rows of the matrix.
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_U32 OML_MatrixNxP::GetNbrRows() const
{
	return nNbrRows_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::GetNbrCols
 *
 *  \return The number of columns of the matrix.
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_U32 OML_MatrixNxP::GetNbrCols() const
{
	return nNbrCols_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::Reset
 *
 *  \param  nNbrRows The number of rows of the matrix.
 *  \param  nNbrCols The number of columns of the matrix.
 *  \author Gabriel Peyré 2001-09-19
 *
 *	Allocate space for the matrix.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_MatrixNxP::Reset(OML_U32 nNbrRows, OML_U32 nNbrCols)
{	
	OML_ASSERT( nNbrCols>0 && nNbrRows>0 );

	if( nNbrRows*nNbrCols != nNbrRows_*nNbrCols_ )
	{
		OML_DELETEARRAY( aData_ );
		aData_ = new OML_Float[nNbrRows*nNbrCols];
		nNbrRows_ = nNbrRows;
		nNbrCols_ = nNbrCols;
	}
	
	this->SetZero();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::GetData
 *
 *  \return Pointer on the datas of the matrix (can be \c NULL).
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float* OML_MatrixNxP::GetData() const
{
	return aData_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::GetData
 *
 *  \param  i row number
 *  \param  j col number
 *  \return value of the (i,j) data.
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_MatrixNxP::GetData(OML_U32 i, OML_U32 j) const
{
	OML_ASSERT( i<this->GetNbrRows() && j<this->GetNbrCols() );
	return aData_[ACCESS(i,j)];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_MatrixNxP::SetData
 *
 *  \param  i row number
 *  \param  j col number
 *  \param  rVal value
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_MatrixNxP::SetData(OML_U32 i, OML_U32 j, OML_Float rVal)
{
	OML_ASSERT( i<this->GetNbrRows() && j<this->GetNbrCols() );
	aData_[ACCESS(i,j)] = rVal;
}

#undef ACCESS

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

