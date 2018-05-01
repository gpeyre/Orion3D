/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Matrix3x3.inl
 *  \brief Inlined methods for \c OML_Matrix3x3
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_Matrix3x3.h"

namespace OML {

#define ITERATE(i,j, code )			\
		for(OML_U32 i=0; i<3; ++i)	\
		for(OML_U32 j=0; j<3; ++j)	\
		{ code }

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3 constructor
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Base constructor, load identity.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3::OML_Matrix3x3()
{
	this->LoadIdentity();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3 constructor
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Initialize the matrix with given coordinates.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3::OML_Matrix3x3(
						   OML_Float m00, OML_Float m10, OML_Float m20, 
						   OML_Float m01, OML_Float m11, OML_Float m21, 
						   OML_Float m02, OML_Float m12, OML_Float m22)
{
	aData_[0][0]=m00; aData_[0][1]=m01; aData_[0][2]=m02;
	aData_[1][0]=m10; aData_[1][1]=m11; aData_[1][2]=m12;
	aData_[2][0]=m20; aData_[2][1]=m21;	aData_[2][2]=m22;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3 constructor
 *
 *  \param  m original matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3::OML_Matrix3x3(const OML_Matrix3x3& m)
{
	memcpy(aData_, m.GetData(), 9*sizeof(OML_Float));
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : copy operator
 *
 *  \param  m original matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3& OML_Matrix3x3::operator = (const OML_Matrix3x3 &m)
{
	memcpy(aData_, m.GetData(), 9*sizeof(OML_Float));
	return *this;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3 destructor
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3::~OML_Matrix3x3()
{
	/* NOTHING */
}

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Multiply
 *
 *  \param  a left hand matrix.
 *  \param  b right hand matrix.
 *  \param  r result.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::Multiply(const OML_Matrix3x3& a, const OML_Matrix3x3& b, OML_Matrix3x3& r)
{
	OML_Float rTemp =0;
	ITERATE(i,j,
		rTemp =0;
		for(OML_U32 k=0; k<3; ++k)
			rTemp += a.GetData(i,k)*b.GetData(k,j);
		r.SetData(i,j, rTemp);
	)
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Multiply
 *
 *  \param  a left hand matrix.
 *  \param  b right hand matrix.
 *  \param  r result.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3 OML_Matrix3x3::operator*(const OML_Matrix3x3& m) const
{
	OML_Matrix3x3 r;
	OML_Matrix3x3::Multiply( *this, m, r );
	return r;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::operator *=
 *
 *  \param  m right hand matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::operator *=(const OML_Matrix3x3 & m)
{
	OML_Matrix3x3 r;
	OML_Matrix3x3::Multiply( *this, m, r );
	(*this) = r;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Add
 *
 *  \param  a left hand matrix.
 *  \param  b right hand matrix.
 *  \param  r result.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::Add(const OML_Matrix3x3& a, const OML_Matrix3x3& b, OML_Matrix3x3& r)
{
	ITERATE(i,j, r.SetData(i,j, a.GetData(i,j)+b.GetData(i,j)); );
}


	
/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Add
 *
 *  \param  a left hand matrix.
 *  \param  b right hand matrix.
 *  \param  r result.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3 OML_Matrix3x3::operator + (const OML_Matrix3x3 & m)
{
	OML_Matrix3x3 r;
	OML_Matrix3x3::Add( *this, m, r );
	return r;
}	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Minus
 *
 *  \param  a left hand matrix.
 *  \param  b right hand matrix.
 *  \param  r result.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::Minus(const OML_Matrix3x3& a, const OML_Matrix3x3& b, OML_Matrix3x3& r)
{
	ITERATE(i,j, r.SetData(i,j, a.GetData(i,j)-b.GetData(i,j)); );
}

	
/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Add
 *
 *  \param  a left hand matrix.
 *  \param  b right hand matrix.
 *  \param  r result.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3 OML_Matrix3x3::operator - (const OML_Matrix3x3 & m)
{	
	OML_Matrix3x3 r;
	OML_Matrix3x3::Minus( *this, m, r );
	return r;
}
	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::UMinus
 *
 *  \param  a left hand matrix.
 *  \param  r result.
 *  \return opposed of the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::UMinus(const OML_Matrix3x3& a, OML_Matrix3x3& r)
{
	ITERATE(i,j, r.SetData(i,j, -a.GetData(i,j)); );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::UMinus
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::operator += (const OML_Matrix3x3 & m)
{
	OML_Matrix3x3 r;
	OML_Matrix3x3::Add( *this, m, r );
	(*this) = r;	
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::UMinus
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::operator -= (const OML_Matrix3x3 & m)
{
	OML_Matrix3x3 r;
	OML_Matrix3x3::Minus( *this, m, r );
	(*this) = r;
}
	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Scale
 *
 *  \param  rScale factor
 *  \param  a left hand matrix
 *  \param  r right hand matrix
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::Scale(const OML_Float rScale, const OML_Matrix3x3& a, OML_Matrix3x3& r)
{
	ITERATE(i,j, r.SetData(i,j, a.GetData(i,j)*rScale); );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::AutoScale
 *
 *  \param  rFactor scaling factor.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::AutoScale(OML_Float rFactor)
{
	OML_Matrix3x3::Scale( rFactor, *this, *this );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::operator*
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3 OML_Matrix3x3::operator*(OML_Float v) const
{
	OML_Matrix3x3 r;
	OML_Matrix3x3::Scale( v, *this, r );
	return r;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Scale
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3 OML_Matrix3x3::operator/(OML_Float v) const
{
	OML_ASSERT( v!=0 );
	OML_Matrix3x3 r;
	OML_Matrix3x3::Scale( 1/v, *this, r );
	return r;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Scale
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::operator*=(OML_Float v)
{
	OML_Matrix3x3::Scale( v, *this, *this );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Scale
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::operator/=(OML_Float v)
{
	OML_ASSERT( v!=0 );
	OML_Matrix3x3::Scale( 1/v, *this, *this );
}
	
/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Scale
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Matrix3x3 OML_Matrix3x3::operator~() const
{
	return OML_Matrix3x3::Transpose();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Scale
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_Matrix3x3::operator!()
{
	this->AutoTranspose();
}


#undef ITERATE

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

