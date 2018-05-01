/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_VectorND.inl
 *  \brief Inlined methods fOML \c OML_VectorND
 *  \authOML Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_VectorND.h"

namespace OML {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND constructOML
 *
 *  \authOML Gabriel Peyré 2001-09-29
 *
 *	Create a zero dimensional vector.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_VectorND::OML_VectorND()
:	nDim_		( 0 ),
	aData_		( NULL )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND constructOML
 *
 *  \param  nDim dimension of the vector
 *  \authOML Gabriel Peyré 2001-09-29
 *
 *	Create a vector of given size.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_VectorND::OML_VectorND(OML_U32 nDim)
:	nDim_		( 0 ),
	aData_		( NULL )
{
	this->Reset( nDim );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND constructOML
 *
 *  \param  v source vector
 *  \authOML Gabriel Peyré 2001-09-29
 *
 *	Copy constructOML.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_VectorND::OML_VectorND(const OML_VectorND& v)
:	nDim_		( 0 ),
	aData_		( NULL )
{
	if( v.GetData()==NULL )
	{
		OML_DELETEARRAY( aData_ );
		nDim_ = 0;
	}
	else
	{
		nDim_ = v.GetDim();
		OML_ASSERT( nDim_>0 );
		OML_DELETEARRAY( aData_ );
		aData_ = new OML_Float[nDim_];
		memcpy( aData_,  v.GetData(), nDim_*sizeof(OML_Float) );
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::=(const 
 *
 *  \param  v source vector.
 *  \authOML Gabriel Peyré 2001-09-29
 *
 *	copy operator.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_VectorND& OML_VectorND::operator =(const OML_VectorND &v)
{
	if( v.GetData()==NULL )
	{
		OML_DELETEARRAY( aData_ );
		nDim_ = 0;
	}
	else
	{
		nDim_ = v.GetDim();
		OML_ASSERT( nDim_>0 );
		OML_DELETEARRAY( aData_ );
		aData_ = new OML_Float[nDim_];
		memcpy( aData_,  v.GetData(), nDim_*sizeof(OML_Float) );
	}

	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::~OML_MatrixNxP
 *
 *  \authOML Gabriel Peyré 2001-09-29
 *
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_VectorND::~OML_VectorND()
{
	OML_DELETEARRAY( aData_ );
}

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::GetDim
 *
 *  \return The dimension of the vector.
 *  \authOML Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_U32 OML_VectorND::GetDim() const
{
	return nDim_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::Reset
 *
 *  \param  nDim Dimension of the vector.
 *  \authOML Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_VectorND::Reset(OML_U32 nDim)
{
	OML_ASSERT( nDim>0 );
	
	if( nDim!=nDim_ )
	{
		OML_DELETEARRAY( aData_ );
		aData_ = new OML_Float[nDim];
		nDim_ = nDim;
	}

	this->SetZero();
}


	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::GetData
 *
 *  \return The array of float of the vector.
 *  \authOML Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float* OML_VectorND::GetData() const
{
	return aData_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::GetData
 *
 *  \param  i offset in the vector.
 *  \return the value of the given coord.
 *  \authOML Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Float OML_VectorND::GetData(OML_U32 i) const
{
	OML_ASSERT( i<this->GetDim() );
	return aData_[i];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_VectorND::SetData
 *
 *  \param  i offset in the vector.
 *  \param  rVal value to set to this coord.
 *  \authOML Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_VectorND::SetData(OML_U32 i, OML_Float rVal)
{
	OML_ASSERT( i<this->GetDim() );
	aData_[i] = rVal;
}





} // End namespace OML

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The OMLion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the OMLion3D licence.                                  //
//  Refer to OMLion3d_licence.txt fOML mOMLe details about the OMLion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence OMLion3D.                              //
//  Se repOMLter a OMLion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

