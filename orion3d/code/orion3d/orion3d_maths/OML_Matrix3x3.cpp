/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Matrix3x3.cpp
 *  \brief Definition of class \c OML_Matrix3x3
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OML_SCCSID
static const char* sccsid = "@(#) OML_Matrix3x3.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OML_SCCSID


#include "stdafx.h"
#include "OML_Matrix3x3.h"
#include "OML_Matrix4x4.h"
#include "OML_Vector3D.h"
#include "OML_Quaternion.h"

#ifndef OML_USE_INLINE
	#include "OML_Matrix3x3.inl"
#endif

using namespace OML;

#define ITERATE(i,j, code )			\
		for(OML_U32 i=0; i<3; ++i)	\
		for(OML_U32 j=0; j<3; ++j)	\
		{ code }


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3 constructor
 *
 *  \param  m original matrix.
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Makes a conversion, keeping only the rotation part of the 4x4 matrix.
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix3x3::OML_Matrix3x3(const OML_Matrix4x4& m)
{
	ITERATE(i,j, this->SetData(i,j, m.GetData(i,j)); );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : copy operator
 *
 *  \param  m original matrix.
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Makes a conversion, keeping only the rotation part of the 4x4 matrix.
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix3x3& OML_Matrix3x3::operator = (const OML_Matrix4x4 &m)
{
	ITERATE(i,j, this->SetData(i,j, m.GetData(i,j)); );
	return *this;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::operator*
 *
 *  \param  m right hand matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix4x4 OML_Matrix3x3::operator*(const OML_Matrix4x4& m) const
{
	OML_Matrix4x4 r;
	OML_Matrix3x3::Multiply( *this, m, r );
	return r;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Multiply
 *
 *  \param  a left hand matrix.
 *  \param  b right hand matrix.
 *  \param  r result.
 *  \author Gabriel Peyré 2001-11-06
 *
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::Multiply(const OML_Matrix3x3& a, const OML_Matrix4x4& b, OML_Matrix4x4& r)
{
	OML_Float rTemp =0;
	r.LoadIdentity();

	for(OML_U32 i=0; i<3; ++i)
	for(OML_U32 j=0; j<4; ++j)
	{
		rTemp =0;
		for(OML_U32 k=0; k<3; ++k)
			rTemp += a.GetData(i,k)*b.GetData(k,j);
		r.SetData(i,j, rTemp);
	}
}

   
/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Multiply
 *
 *  \param  a right hand matrix.
 *  \return vector transformed by the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Vector3D OML_Matrix3x3::operator*(const OML_Vector3D& v) const
{
	OML_Vector3D r;
	OML_Matrix3x3::Multiply( *this, v, r );
	return r;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Multiply
 *
 *  \param  a right hand matrix.
 *  \param  v left hand vector.
 *  \param  r vector transformed by the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::Multiply(const OML_Matrix3x3& a, const OML_Vector3D& v, OML_Vector3D& r)
{
	OML_Float rTemp =0;
	for(OML_U32 i=0; i<3; ++i)
	{
		rTemp =0;
		for(OML_U32 k=0; k<3; ++k)
			rTemp += a.GetData(i,k)*v.GetData(k);
		r.SetData(i, rTemp);
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Invert
 *
 *  \param  a matrix to invert
 *  \param  r result.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
#define ACCESS(i,j) aData[j*3+i]
#define ACCESS_R(i,j) aResData[j*3+i]
#define SUBDET(i0,j0, i1,j1) ( ACCESS(j0,i0)*ACCESS(j1,i1) - ACCESS(j1,i0)*ACCESS(j0,i1) )

void OML_Matrix3x3::Invert(const OML_Matrix3x3& a, OML_Matrix3x3& r)
{
	OML_Float* aData	   = a.GetData();
	OML_Float* aResData = r.GetData();

	/* cofactor */
	OML_Float c00, c01, c02,
			 c10, c11, c12,
			 c20, c21, c22;

	c00 = SUBDET(1,1, 2,2);
	c01 =-SUBDET(1,0, 2,2);
	c02 = SUBDET(1,0, 2,1);

	c10 =-SUBDET(0,1, 2,2);
	c11 = SUBDET(0,0, 2,2);
	c12 =-SUBDET(0,0, 2,1);

	c20 = SUBDET(0,1, 1,2);
	c21 =-SUBDET(0,0, 1,2);
	c22 = SUBDET(0,0, 1,1);

    /* compute 3x3 determinant & its reciprocal */
    OML_Float rDet = ACCESS(0,0)*c00 + ACCESS(1,0)*c01 + ACCESS(2,0)*c02;
    if (rDet == 0.0f)
	{
		/* the aData can't be inverted */
		return;
	}

    rDet = 1.0f/rDet;

	ACCESS_R(0,0) = c00*rDet;
	ACCESS_R(0,1) = c01*rDet;
	ACCESS_R(0,2) = c02*rDet;

	ACCESS_R(1,0) = c10*rDet;
	ACCESS_R(1,1) = c11*rDet;
	ACCESS_R(1,2) = c12*rDet;

	ACCESS_R(2,0) = c20*rDet;
	ACCESS_R(2,1) = c21*rDet;
	ACCESS_R(2,2) = c22*rDet;

}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Invert
 *
 *  \return the inverse of the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix3x3 OML_Matrix3x3::Invert() const
{
	OML_Matrix3x3 r;
	OML_Matrix3x3::Invert(*this, r);

	return r;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::AutoInvert
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Invert the matrix.
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::AutoInvert()
{
	OML_Matrix3x3 r;
	OML_Matrix3x3::Invert(*this, r);
	
	this->SetData( r.GetData() );
}

  
/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::RotateX
 *
 *  \param val rotation angle.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::RotateX(OML_Float val)
{
	OML_Float	Sin = (OML_Float) sin(val),
				Cos = (OML_Float) cos(val);
	OML_Vector3D tmp = this->GetY()*Cos + this->GetZ()*Sin;
	this->SetZ(-this->GetY()*Sin + this->GetZ()*Cos);
	this->SetY(tmp);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::RotateX
 *
 *  \param val rotation angle.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::RotateY(OML_Float val)
{
	OML_Float	Sin = (OML_Float) sin(val),
				Cos = (OML_Float) cos(val);
	OML_Vector3D tmp = this->GetX()*Cos + this->GetZ()*Sin;
	this->SetZ(-this->GetX()*Sin + this->GetZ()*Cos);
	this->SetX(tmp);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::RotateX
 *
 *  \param val rotation angle.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::RotateZ(OML_Float val)
{
	OML_Float	Sin = (OML_Float) sin(val),
				Cos = (OML_Float) cos(val);
	OML_Vector3D tmp = this->GetX()*Cos + this->GetY()*Sin;
	this->SetY(-this->GetX()*Sin + this->GetY()*Cos);
	this->SetX(tmp);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::RotateX
 *
 *  \param val rotation angle.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::Rotate(OML_Coord_XYZW axe, OML_Float val)
{
	switch (axe)
	{
	case X:
		this->RotateX(val);
		break;
	case Y:
		this->RotateY(val);
		break;
	case Z:
		this->RotateZ(val);
		break;
	case W:
		break;
	};
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::RotateX
 *
 *  \param val rotation angle.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::RotateAbsX(OML_Float val)
{
	OML_Float	Sin = (OML_Float) sin(val),
				Cos = (OML_Float) cos(val);
	OML_Float tmp;
	for( OML_I32 i=0; i<=2; ++i )
	{
		tmp = aData_[i][Y]*Cos-aData_[i][Z]*Sin;
		aData_[i][Z] = aData_[i][Y]*Sin+aData_[i][Z]*Cos;
		aData_[i][Y] = tmp;
	}
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::RotateX
 *
 *  \param val rotation angle.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::RotateAbsY(OML_Float val)
{
	OML_Float	Sin = (OML_Float) sin(val),
				Cos = (OML_Float) cos(val);
	OML_Float tmp;
	for( OML_I32 i=0; i<=2; ++i )
	{
		tmp = aData_[i][X]*Cos + aData_[i][Z]*Sin;
		aData_[i][Z] = -aData_[i][X]*Sin + aData_[i][Z]*Cos;
		aData_[i][X] = tmp;
	}
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::RotateX
 *
 *  \param val rotation angle.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::RotateAbsZ(OML_Float val)
{
	OML_Float	Sin = (OML_Float) sin(val),
				Cos = (OML_Float) cos(val);
	OML_Float tmp;
	for( OML_I32 i=0; i<=2; ++i )
	{	
		tmp = aData_[i][X]*Cos - aData_[i][Y]*Sin;
		aData_[i][Y] = aData_[i][X]*Sin + aData_[i][Y]*Cos;
		aData_[i][X] = tmp;
	}
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::RotateX
 *
 *  \param val rotation angle.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::RotateAbs(OML_Coord_XYZW axe, OML_Float val)
{
	switch (axe)
	{
	case X:
		this->RotateAbsX(val);
		break;
	case Y:
		this->RotateAbsY(val);
		break;
	case Z:
		this->RotateAbsZ(val);
		break;
	case W:
		break;
	};
}
 

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Transpose
 *
 *  \param  a original matrix.
 *  \param  r result.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::Transpose(const OML_Matrix3x3& a, OML_Matrix3x3& r)
{
	ITERATE(i,j, r.SetData(i,j, a.GetData(j,i)); )
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::AutoTranspose
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Transpose the matrix.
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::AutoTranspose()
{
	OML_Matrix3x3 r;
	OML_Matrix3x3::Transpose(*this, r);
	(*this) = r;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Transpose
 *
 *  \return transoped matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix3x3 OML_Matrix3x3::Transpose() const
{
	
	OML_Matrix3x3 r;
	OML_Matrix3x3::Transpose(*this, r);
	return r;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::GetData
 *
 *  \return the data of the matrix (OML_Float[9]).
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Float* OML_Matrix3x3::GetData() const
{
	return (OML_Float*) aData_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::GetData
 *
 *  \return the data of the matrix (OML_Float[9]).
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Float* OML_Matrix3x3::GetData()
{
	return (OML_Float*) aData_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::GetData
 *
 *  \param  i row number.
 *  \param  j col number.
 *  \return value of the matrix at place (i,j)
 *  \author Gabriel Peyré 2001-11-06
 *
 * PUT YOUR COMMENTS HERE
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_Matrix3x3::GetData(OML_I32 i, OML_I32 j) const
{
	OML_ASSERT(i<3 && j<3);
	return aData_[j][i];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::SetData
 *
 *  \param  i row number.
 *  \param  j col number.
 *  \param  rVal value of the matrix at place (i,j)
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::SetData(OML_I32 i, OML_I32 j, OML_Float rVal)
{
	OML_ASSERT(i<3 && j<3);
	aData_[j][i] = rVal;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::SetData
 *
 *  \param  aData a pointer on an array of 9 floats
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::SetData(OML_Float* aData)
{
	memcpy(aData_, aData, 9*sizeof(OML_Float));
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::SetData
 *
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::SetData(
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
 * Name : OML_Matrix3x3::SetZero
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Set all data to zero.
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::SetZero()
{
	memset( aData_, 0, 9*sizeof(OML_Float) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::LoadIdentity
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Set the matrix to the identity.
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::LoadIdentity()
{
	aData_[0][1]=aData_[0][2]=
	aData_[1][0]=aData_[1][2]=
	aData_[2][0]=aData_[2][1]=0;
	aData_[0][0]=aData_[1][1]=aData_[2][2]=1;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::SetValue
 *
 *  \param  rVal value to set to the whole matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::SetValue(OML_Float rVal)
{
	ITERATE(i,j, aData_[j][i]=rVal; )
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Randomize
 *
 *  \param  rMin minimum value
 *  \param  rMax maximum value
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::Randomize(OML_Float rMin, OML_Float rMax)
{	
	ITERATE(i,j, this->SetData( i, j, rMin + OML_RAND*(rMax-rMin) ); );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Print
 *
 *  \param  cFormat Format of the real number
 *  \param  f file to print to
 *  \author Gabriel Peyré 2001-09-19
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::Print(char *cFormat, FILE *f)
{
	/** \todo */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::ToQuaternion
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	A quaternion can then be converted into a 4x4 rotation
 *	matrix using the following expression:
 *
 *	\code   
 *		|       2     2                                |
 *		| 1 - 2Y  - 2Z    2XY - 2ZW      2XZ + 2YW     |
 *		|                                              |
 *		|                       2     2                |
 *	M = | 2XY + 2ZW       1 - 2X  - 2Z   2YZ - 2XW     |
 *		|                                              |
 *		|                                      2     2 |
 *		| 2XZ - 2YW       2YZ + 2XW      1 - 2X  - 2Y  |
 *		|                                              |
 *	\endcode
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::BuildFromQuaternion(OML_Quaternion& q)
{
	OML_Float w = q.GetX();
	OML_Float x = q.GetY();
	OML_Float y = q.GetZ();
	OML_Float z = q.GetW();
	this->SetData(1.0f - 2*y*y - 2*z*z, 2*x*y + 2*w*z, 2*x*z - 2*w*y,
				2*x*y - 2*w*z, 1.0f - 2*x*x - 2*z*z, 2*y*z + 2*w*x,
				2*x*z + 2*w*y, 2*y*z - 2*w*x, 1.0f - 2*x*x - 2*y*y);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Norm1
 *
 *  \return pseuo-norm 1 of the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_Matrix3x3::Norm1()
{
	OML_Float rNorm = 0;
	ITERATE(i,j, rNorm+=this->GetData(i,j); )
	return  rNorm;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::Norm2
 *
 *  \return pseuo-norm 2 of the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_Matrix3x3::Norm2()
{
	OML_Float rNorm = 0;
	ITERATE(i,j, rNorm+=this->GetData(i,j)*this->GetData(i,j); )
	return  OML_Maths::sqrt( rNorm );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::NormInf
 *
 *  \return pseudo-infinite norm of the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_Matrix3x3::NormInf()
{
	OML_Float rNorm = 0;
	ITERATE(i,j, 
		if(OML_ABS(this->GetData(i,j))>rNorm) 
			rNorm=this->GetData(i,j); 
	)
	return rNorm;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::GetX
 *
 *  \return X vector of the basis defined by the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Vector3D OML_Matrix3x3::GetX() const
{
	return OML_Vector3D(this->GetData(X,0), this->GetData(Y,0), this->GetData(Z,0));
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::GetY
 *
 *  \return Y vector of the basis defined by the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Vector3D OML_Matrix3x3::GetY() const
{
	return OML_Vector3D(this->GetData(X,1), this->GetData(Y,1), this->GetData(Z,1));
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::GetZ
 *
 *  \return Z vector of the basis defined by the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Vector3D OML_Matrix3x3::GetZ() const
{
	return OML_Vector3D(this->GetData(X,2), this->GetData(Y,2), this->GetData(Z,2));
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::SetX
 *
 *  \param  v X vector of the basis defined by the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::SetX( const OML_Vector3D& v)
{
	this->SetData(X, 0, v[X]);
	this->SetData(Y, 0, v[Y]);
	this->SetData(Z, 0, v[Z]);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::SetX
 *
 *  \param  v Y vector of the basis defined by the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::SetY( const OML_Vector3D& v)
{
	this->SetData(X, 1, v[X]);
	this->SetData(Y, 1, v[Y]);
	this->SetData(Z, 1, v[Z]);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix3x3::SetZ
 *
 *  \param  v Z vector of the basis defined by the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix3x3::SetZ( const OML_Vector3D& v)
{
	this->SetData(X, 2, v[X]);
	this->SetData(Y, 2, v[Y]);
	this->SetData(Z, 2, v[Z]);
}


#undef ITERATE


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


