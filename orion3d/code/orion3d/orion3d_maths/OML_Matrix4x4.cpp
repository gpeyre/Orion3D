/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Matrix4x4.cpp
 *  \brief implementation of class OML_Matrix4x4
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OML_SCCSID
static const char* sccsid = "@(#) OML_Matrix4x4.cpp (c) Gabriel Peyré & Antoine BouthOMLs 2001";
#endif // OML_SCCSID


#include "stdafx.h"
#include "OML_Matrix4x4.h"

#ifndef OML_USE_INLINE
	#include "OML_Matrix4x4.inl"
#endif

using namespace OML;

#define ITERATE(i,j, code )			\
		for(OML_U32 i=0; i<4; ++i)	\
		for(OML_U32 j=0; j<4; ++j)	\
		{ code }

OML_Matrix4x4 OML_Matrix4x4::operator+( const OML_Vector3D& v ) const
{
	return OML_Matrix4x4(
		Matrix[0][0], Matrix[1][0], Matrix[2][0], Matrix[3][0]+v[0], 
		Matrix[0][1], Matrix[1][1], Matrix[2][1], Matrix[3][1]+v[1], 
		Matrix[0][2], Matrix[1][2], Matrix[2][2], Matrix[3][2]+v[2], 
		Matrix[0][3], Matrix[1][3], Matrix[2][3], Matrix[3][3]);
}

OML_Matrix4x4 OML_Matrix4x4::operator-( const OML_Vector3D& v) const
{
	return OML_Matrix4x4(
		Matrix[0][0], Matrix[1][0], Matrix[2][0], Matrix[3][0]-v[0], 
		Matrix[0][1], Matrix[1][1], Matrix[2][1], Matrix[3][1]-v[1], 
		Matrix[0][2], Matrix[1][2], Matrix[2][2], Matrix[3][2]-v[2], 
		Matrix[0][3], Matrix[1][3], Matrix[2][3], Matrix[3][3]);
}

void OML_Matrix4x4::operator+=( const OML_Vector3D& v)
{
	Matrix[3][0]+=v[0];
	Matrix[3][1]+=v[1];
	Matrix[3][2]+=v[2];
}

void OML_Matrix4x4::operator-=( const OML_Vector3D& v)
{
	Matrix[3][0]-=v[0];
	Matrix[3][1]-=v[1];
	Matrix[3][2]-=v[2];
}
	
OML_Matrix4x4 OML_Matrix4x4::operator*(OML_Float v) const
{
	return OML_Matrix4x4(
		v*Matrix[0][0], v*Matrix[1][0], v*Matrix[2][0], v*Matrix[3][0], 
		v*Matrix[0][1], v*Matrix[1][1], v*Matrix[2][1], v*Matrix[3][1], 
		v*Matrix[0][2], v*Matrix[1][2], v*Matrix[2][2], v*Matrix[3][2], 
		v*Matrix[0][3], v*Matrix[1][3], v*Matrix[2][3], v*Matrix[3][3]);
}

OML_Matrix4x4 OML_Matrix4x4::operator/(OML_Float v) const
{
	return OML_Matrix4x4(
		Matrix[0][0]/v, Matrix[1][0]/v, Matrix[2][0]/v, Matrix[3][0]/v, 
		Matrix[0][1]/v, Matrix[1][1]/v, Matrix[2][1]/v, Matrix[3][1]/v, 
		Matrix[0][2]/v, Matrix[1][2]/v, Matrix[2][2]/v, Matrix[3][2]/v, 
		Matrix[0][3]/v, Matrix[1][3]/v, Matrix[2][3]/v, Matrix[3][3]/v);
}

void OML_Matrix4x4::operator*=(OML_Float v)
{
	Matrix[0][0] *= v; Matrix[1][0] *= v; Matrix[2][0] *= v; Matrix[3][0] *= v;
	Matrix[0][1] *= v; Matrix[1][1] *= v; Matrix[2][1] *= v; Matrix[3][1] *= v;
	Matrix[0][2] *= v; Matrix[1][2] *= v; Matrix[2][2] *= v; Matrix[3][2] *= v;
	Matrix[0][3] *= v; Matrix[1][3] *= v; Matrix[2][3] *= v; Matrix[3][3] *= v;
}

void OML_Matrix4x4::operator/=(OML_Float v)
{
	Matrix[0][0] /= v; Matrix[1][0] /= v; Matrix[2][0] /= v; Matrix[3][0] /= v;
	Matrix[0][1] /= v; Matrix[1][1] /= v; Matrix[2][1] /= v; Matrix[3][1] /= v;
	Matrix[0][2] /= v; Matrix[1][2] /= v; Matrix[2][2] /= v; Matrix[3][2] /= v;
	Matrix[0][3] /= v; Matrix[1][3] /= v; Matrix[2][3] /= v; Matrix[3][3] /= v;
}

void OML_Matrix4x4::operator!()
{
	OML_Float tmp;
	/* compute the reverse translation */
	OML_Float t0=Matrix[0][0]*Matrix[3][0]+Matrix[0][1]*Matrix[3][1]+Matrix[0][2]*Matrix[3][2];
	OML_Float t1=Matrix[1][0]*Matrix[3][0]+Matrix[1][1]*Matrix[3][1]+Matrix[1][2]*Matrix[3][2];
	OML_Float t2=Matrix[2][0]*Matrix[3][0]+Matrix[2][1]*Matrix[3][1]+Matrix[2][2]*Matrix[3][2];
	/* the matrix is supposed to be OMLthogonal !!!!! */
	for( OML_I32 i=0; i<3; i++ )
	for( OML_I32 j=0; j<3; j++ )
	{
		tmp=Matrix[i][j];
		Matrix[i][j]=Matrix[j][i];
		Matrix[j][i]=tmp;
	}
	Matrix[3][0]=-t0;
	Matrix[3][1]=-t1;
	Matrix[3][2]=-t2;
}

OML_Matrix4x4 OML_Matrix4x4::operator/( const OML_Matrix4x4& v) const
{
	return OML_Matrix4x4(&Matrix[0][0])*~(v);
}

void OML_Matrix4x4::operator*=( const OML_Matrix4x4& v)
{
	OML_Float matrix[4][4];
	for( OML_I32 i=0; i<4; i++ )
	for( OML_I32 j=0; j<4; j++ )
		matrix[i][j]=Matrix[i][0]*v[0][j]+Matrix[i][1]*v[1][j]+
					 Matrix[i][2]*v[2][j]+Matrix[i][3]*v[3][j];
	memcpy(Matrix, matrix, 16*sizeof(OML_Float));
	
}

void OML_Matrix4x4::operator/=( const OML_Matrix4x4& v)
{
	/* ok, c bourin ... */
	(*this)*=~(v);
}

void OML_Matrix4x4::RotateX(OML_Float val)
{
	OML_Float Sin=(OML_Float) sin(val),
		  Cos=(OML_Float) cos(val);
	OML_Vector3D tmp=GetY()*Cos+GetZ()*Sin;
	SetZ(-GetY()*Sin+GetZ()*Cos);
	SetY(tmp);
}

void OML_Matrix4x4::RotateY(OML_Float val)
{
	OML_Float Sin=(OML_Float) sin(val),
		  Cos=(OML_Float) cos(val);
	OML_Vector3D tmp=GetX()*Cos+GetZ()*Sin;
	SetZ(-GetX()*Sin+GetZ()*Cos);
	SetX(tmp);
}

void OML_Matrix4x4::RotateZ(OML_Float val)
{
	OML_Float Sin=(OML_Float) sin(val),
		  Cos=(OML_Float) cos(val);
	OML_Vector3D tmp=GetX()*Cos+GetY()*Sin;
	SetY(-GetX()*Sin+GetY()*Cos);
	SetX(tmp);
}

void OML_Matrix4x4::Rotate(OML_U32 axe, OML_Float val)
{
	switch (axe)
	{
	case X:
		RotateX(val);
		break;
	case Y:
		RotateY(val);
		break;
	case Z:
		RotateZ(val);
		break;
	case W:
	        break;
	};
}

void OML_Matrix4x4::RotateAbsX(OML_Float val)
{
	OML_Float Sin=(OML_Float) sin(val),
		  Cos=(OML_Float) cos(val);
	OML_Float tmp;
	for (OML_I32 i=0; i<=2; i++)
	{
		tmp=Matrix[i][Y]*Cos-Matrix[i][Z]*Sin;
		Matrix[i][Z]=Matrix[i][Y]*Sin+Matrix[i][Z]*Cos;
		Matrix[i][Y]=tmp;
	}
}

void OML_Matrix4x4::RotateAbsY(OML_Float val)
{
	OML_Float Sin=(OML_Float) sin(val),
		  Cos=(OML_Float) cos(val);
	OML_Float tmp;
	for (OML_I32 i=0; i<=2; i++)
	{
		tmp=Matrix[i][X]*Cos+Matrix[i][Z]*Sin;
		Matrix[i][Z]=-Matrix[i][X]*Sin+Matrix[i][Z]*Cos;
		Matrix[i][X]=tmp;
	}
}

void OML_Matrix4x4::RotateAbsZ(OML_Float val)
{
	OML_Float Sin=(OML_Float) sin(val),
		  Cos=(OML_Float) cos(val);
	OML_Float tmp;
	for (OML_I32 i=0; i<=2; i++)
	{	
		tmp=Matrix[i][X]*Cos-Matrix[i][Y]*Sin;
		Matrix[i][Y]=Matrix[i][X]*Sin+Matrix[i][Y]*Cos;
		Matrix[i][X]=tmp;
	}
}

void OML_Matrix4x4::RotateAbs(OML_U32 axe, OML_Float val)
{
	switch (axe)
	{
	case X:
		RotateAbsX(val);
		break;
	case Y:
		RotateAbsY(val);
		break;
	case Z:
		RotateAbsZ(val);
		break;
	case W:
		break;
	};
}

OML_Vector3D OML_Matrix4x4::operator[](OML_U32 i) const
{
	return OML_Vector3D((OML_Float*) &Matrix[i]);
}

void OML_Matrix4x4::AutoScaleTranslation(OML_Float v)
{
	Matrix[3][0]*=v;	
	Matrix[3][1]*=v;
	Matrix[3][2]*=v;
}

void OML_Matrix4x4::UnScale()
{
	OML_Float l = OML_Maths::sqrt(Matrix[0][0]*Matrix[0][0] + Matrix[0][1]*Matrix[0][1] + Matrix[0][2]*Matrix[0][2] );
	Matrix[0][0] /= l;
	Matrix[0][1] /= l;
	Matrix[0][2] /= l;
	l = OML_Maths::sqrt(Matrix[1][0]*Matrix[1][0] + Matrix[1][1]*Matrix[1][1] + Matrix[1][2]*Matrix[1][2] );
	Matrix[1][0] /= l;
	Matrix[1][1] /= l;
	Matrix[1][2] /= l;
	l = OML_Maths::sqrt(Matrix[2][0]*Matrix[2][0] + Matrix[2][1]*Matrix[2][1] + Matrix[2][2]*Matrix[2][2] );
	Matrix[2][0] /= l;
	Matrix[2][1] /= l;
	Matrix[2][2] /= l;
}

/* scale operations **************************************************/
void OML_Matrix4x4::AutoScale( const OML_Vector3D& v)
{	
	for(OML_U32 i=0; i<3; ++i)
	for(OML_U32 j=0; j<4; ++j)
		Matrix[i][j] *= v[i];
}

void OML_Matrix4x4::AutoScale(OML_U32 axe, OML_Float v)
{	
	for(OML_U32 i=0; i<4; ++i)
		Matrix[axe][i] *= v;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::AutoScale
 *
 *  \param  rVal factOML
 *  \author Gabriel Peyré 2001-11-05
 *
 *	Scale each component of the matrix by the scale factOML.
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix4x4::AutoScale(OML_Float rVal)
{
	for(OML_U32 i=0; i<4; ++i)
	for(OML_U32 j=0; j<4; ++j)
		Matrix[j][i] *= rVal;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::Scale
 *
 *  \param  rVal factOML
 *	\return scaled matrix
 *  \author Gabriel Peyré 2001-11-05
 *
 *	Return a scaled matrix by the scale factOML.
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix4x4 OML_Matrix4x4::Scale(OML_Float rVal)
{
	OML_Matrix4x4 m(*this);
	m.AutoScale(rVal);

	return m;
}


void OML_Matrix4x4::Translate( const OML_Vector3D& v)
{
	(*this)+=v;
}

/* get value operations **********************************************/
void OML_Matrix4x4::Translate(OML_U32 axe, OML_Float v)
{
	Matrix[3][axe]+=v;
}

OML_Vector3D OML_Matrix4x4::GetX() const
{
	return Matrix[X];
}

OML_Vector3D OML_Matrix4x4::GetY() const
{
	return Matrix[Y];
}

OML_Vector3D OML_Matrix4x4::GetZ() const
{
	return Matrix[Z];
}

void OML_Matrix4x4::SetX( const OML_Vector3D& v)
{
	Matrix[0][0]=v[0];
	Matrix[0][1]=v[1];
	Matrix[0][2]=v[2];
}

void OML_Matrix4x4::SetY( const OML_Vector3D& v)
{
	Matrix[1][0]=v[0];
	Matrix[1][1]=v[1];
	Matrix[1][2]=v[2];
}

void OML_Matrix4x4::SetZ( const OML_Vector3D& v)
{
	Matrix[2][0]=v[0];
	Matrix[2][1]=v[1];
	Matrix[2][2]=v[2];
}

void OML_Matrix4x4::SetTranslation( const OML_Vector3D& v)
{
	Matrix[3][X]=v[X];
	Matrix[3][Y]=v[Y];
	Matrix[3][Z]=v[Z];
}

void OML_Matrix4x4::SetTranslation(OML_Coord_XYZW axe, OML_Float v)
{
	Matrix[3][axe]=v;
}

void OML_Matrix4x4::SetScale( const OML_Vector3D& v)
{
	Matrix[X][0]=v[X];
	Matrix[Y][0]=v[Y];
	Matrix[Z][0]=v[Z];
}

void OML_Matrix4x4::SetScale(OML_Coord_XYZW axe, OML_Float v)
{
	Matrix[axe][0]=v;
}

void OML_Matrix4x4::SetRotation( const OML_Matrix3x3& m)
{
	for( OML_U32 i=0; i<3; ++i )
	for( OML_U32 j=0; j<3; ++j )
		this->SetData(i,j, m.GetData(i,j)  );
}

OML_Float* OML_Matrix4x4::GetData() const
{
	return (OML_Float*) &Matrix[0][0];
}

OML_Vector3D OML_Matrix4x4::GetTranslation()
{
	return OML_Vector3D(Matrix[3][0], Matrix[3][1], Matrix[3][2]);
}

OML_Float* OML_Matrix4x4::GetTranslationPtr()
{
	return Matrix[3];
}

void OML_Matrix4x4::ReComputeBasis_GivenX( OML_Vector3D v)
{
	/* re-nOMLm v */
	v.Normalize();
	SetX(v);
	/* re-compute a basis */
	OML_Vector3D axe_z=v^GetY();
	OML_Float n=~(axe_z);
	if (n<OML_EPSILON)
	{
		/* old X is colinear to new Z, so use Y to compute the new basis */
		OML_Vector3D axe_y=GetZ()^v;
		axe_y.Normalize();
		SetY(axe_y);
		SetZ(v^axe_y);
	}
	else
	{
		/* re-nOMLm the new Y */
		axe_z.Normalize();
		SetZ(axe_z);
		SetY(axe_z^v);
	}
}

void OML_Matrix4x4::ReComputeBasis_GivenY( OML_Vector3D v)
{
	/* re-nOMLm v */
	v.Normalize();
	SetY(v);
	/* re-compute a basis */
	OML_Vector3D axe_x=v^GetZ();
	OML_Float n=~(axe_x);
	if (n<OML_EPSILON)
	{
		/* old X is colinear to new Z, so use Y to compute the new basis */
		OML_Vector3D axe_z=GetX()^v;
		axe_z.Normalize();
		SetZ(axe_z);
		SetX(v^axe_z);
	}
	else
	{
		/* re-nOMLm the new X */
		axe_x.Normalize();
		SetX(axe_x);
		SetY(axe_x^v);
	}
}

void OML_Matrix4x4::ReComputeBasis_GivenZ( OML_Vector3D v)
{
	/* re-nOMLm v */
	v.Normalize();
	SetZ(v);
	/* re-compute a basis */
	OML_Vector3D axe_x=GetY()^v;
	OML_Float n=~(axe_x);
	if (n<OML_EPSILON)
	{
		/* old X is colinear to new Z, so use Y to compute the new basis */
		OML_Vector3D axe_y=v^GetX();
		axe_y.Normalize();
		SetY(axe_y);
		SetX(axe_y^v);
	}
	else
	{
		/* re-nOMLm the new X */
		axe_x.Normalize();
		SetX(axe_x);
		SetY(v^axe_x);
	}
}

void OML_Matrix4x4::LoadIdentity()
{
	Matrix[0][1]=Matrix[0][2]=Matrix[0][3]=
	Matrix[1][0]=Matrix[1][2]=Matrix[1][3]=
	Matrix[2][0]=Matrix[2][1]=Matrix[2][3]=
	Matrix[3][0]=Matrix[3][1]=Matrix[3][2]=0;
	Matrix[0][0]=Matrix[1][1]=Matrix[2][2]=Matrix[3][3]=1;
}

OML_Matrix4x4::OML_Matrix4x4() 
{ 
	for (OML_I32 i=0; i<4; i++)
	for (OML_I32 j=0; j<4; j++)
		Matrix[i][j]=0;
	Matrix[0][0]=Matrix[1][1]=Matrix[2][2]=Matrix[3][3]=1;
}

OML_Matrix4x4::OML_Matrix4x4(const OML_Float* c)
{ 
	memcpy(Matrix, c, 16*sizeof(OML_Float)); 
}

OML_Matrix4x4::OML_Matrix4x4(
		OML_Float m00, OML_Float m10, OML_Float m20, OML_Float m30, 
		OML_Float m01, OML_Float m11, OML_Float m21, OML_Float m31, 
		OML_Float m02, OML_Float m12, OML_Float m22, OML_Float m32, 
		OML_Float m03, OML_Float m13, OML_Float m23, OML_Float m33)
{
	Matrix[0][0]=m00; Matrix[0][1]=m01; Matrix[0][2]=m02; Matrix[0][3]=m03;
	Matrix[1][0]=m10; Matrix[1][1]=m11; Matrix[1][2]=m12; Matrix[1][3]=m13;
	Matrix[2][0]=m20; Matrix[2][1]=m21;	Matrix[2][2]=m22; Matrix[2][3]=m23;
	Matrix[3][0]=m30; Matrix[3][1]=m31; Matrix[3][2]=m32; Matrix[3][3]=m33;
}


//-----------------------------------------------------------------------------
// Name: OML_Matrix4x4 constructOML
/**
*   @param  matrix the element to copy
*   @return *this
*
*	copy constructOML 
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OML_Matrix4x4::OML_Matrix4x4(const OML_Matrix4x4& matrix)
{
	memcpy(Matrix, matrix.GetCoords(), 16*sizeof(OML_Float)); 	
}


//-----------------------------------------------------------------------------
// Name: OML_Matrix4x4::=(const 
/**
*   @param  matrix matrix the element to copy
*   @return *this
*
*	copy operator
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OML_Matrix4x4& OML_Matrix4x4::operator=(const OML_Matrix4x4& matrix)
{	
	memcpy(Matrix, matrix.GetCoords(), 16*sizeof(OML_Float)); 
	return *this;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::Invert
 *
 *  \return The inverse of the matrix.
 *  \author Gabriel Peyré 2001-08-04
 *
 *	Compute the inverse the matrix, not assuming that it's
 *	an orthogonal matrix.
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix4x4 OML_Matrix4x4::Invert() const
{
	/* to stOMLe the invert matrix tempOMLary */
	OML_Float Invert[4][4];

    double x00, x01, x02;
    double x10, x11, x12;
    double x20, x21, x22;
    double x30, x31, x32;
    double rcp;
    double y01, y02, y03, y12, y13, y23;
    double z02, z03, z12, z13, z22, z23, z32, z33;

#define x03 x01
#define x13 x11
#define x23 x21
#define x33 x31
#define z00 x02
#define z10 x12
#define z20 x22
#define z30 x32
#define z01 x03
#define z11 x13
#define z21 x23
#define z31 x33

    /* read 1st two columns of matrix into registers */
    x00 = Matrix[0][0]; // src.xx; 1st column
    x01 = Matrix[1][0]; // src.xy; 2nd column
    x10 = Matrix[0][1]; // src.yx; 1st column
    x11 = Matrix[1][1]; // src.yy; 2nd column
    x20 = Matrix[0][2]; // src.zx; 1st column
    x21 = Matrix[1][2]; // src.zy; 2nd column
    x30 = Matrix[0][3]; // src.wx; 1st column
    x31 = Matrix[1][3]; // src.wy; 2nd column

    /* compute all six 2x2 determinants of 1st two columns */
    y01 = x00*x11 - x10*x01;
    y02 = x00*x21 - x20*x01;
    y03 = x00*x31 - x30*x01;
    y12 = x10*x21 - x20*x11;
    y13 = x10*x31 - x30*x11;
    y23 = x20*x31 - x30*x21;

    /* read 2nd two columns of matrix into registers */
    x02 = Matrix[2][0]; // src.xz; 3rd column
    x03 = Matrix[3][0]; // src.xw; 4th column
    x12 = Matrix[2][1]; // src.yz; 3rd column
    x13 = Matrix[3][1]; // src.yw; 4th column
    x22 = Matrix[2][2]; // src.zz; 3rd column
    x23 = Matrix[3][2]; // src.zw; 4th column
    x32 = Matrix[2][3]; // src.wz; 3rd column
    x33 = Matrix[3][3]; // src.ww; 4th column

    /* compute all 3x3 cofactOMLs for 2nd two columns */
    z33 = x02*y12 - x12*y02 + x22*y01;
    z23 = x12*y03 - x32*y01 - x02*y13;
    z13 = x02*y23 - x22*y03 + x32*y02;
    z03 = x22*y13 - x32*y12 - x12*y23;
    z32 = x13*y02 - x23*y01 - x03*y12;
    z22 = x03*y13 - x13*y03 + x33*y01;
    z12 = x23*y03 - x33*y02 - x03*y23;
    z02 = x13*y23 - x23*y13 + x33*y12;

    /* compute all six 2x2 determinants of 2nd two columns */
    y01 = x02*x13 - x12*x03;
    y02 = x02*x23 - x22*x03;
    y03 = x02*x33 - x32*x03;
    y12 = x12*x23 - x22*x13;
    y13 = x12*x33 - x32*x13;
    y23 = x22*x33 - x32*x23;

    /* read 1st two columns of matrix into registers */
	x00 = Matrix[0][0]; // src.xx; 1st column
    x01 = Matrix[1][0]; // src.xy; 2nd column
    x10 = Matrix[0][1]; // src.yx; 1st column
    x11 = Matrix[1][1]; // src.yy; 2nd column
    x20 = Matrix[0][2]; // src.zx; 1st column
    x21 = Matrix[1][2]; // src.zy; 2nd column
    x30 = Matrix[0][3]; // src.wx; 1st column
    x31 = Matrix[1][3]; // src.wy; 2nd column

    /* compute all 3x3 cofactOMLs for 1st column */
    z30 = x11*y02 - x21*y01 - x01*y12;
    z20 = x01*y13 - x11*y03 + x31*y01;
    z10 = x21*y03 - x31*y02 - x01*y23;
    z00 = x11*y23 - x21*y13 + x31*y12;

    /* compute 4x4 determinant & its reciprocal */
    rcp = x30*z30 + x20*z20 + x10*z10 + x00*z00;
    if (rcp == 0.0f)
	{
		/* the matrix can't be inverted */
		return OML_Matrix4x4();
	}

    rcp = 1.0f/rcp;

    /* compute all 3x3 cofactOMLs for 2nd column */
    z31 = x00*y12 - x10*y02 + x20*y01;
    z21 = x10*y03 - x30*y01 - x00*y13;
    z11 = x00*y23 - x20*y03 + x30*y02;
    z01 = x20*y13 - x30*y12 - x10*y23;

    /* multiply all 3x3 cofactOMLs by reciprocal */
    /* inverse.xx */ Invert[0][0] = (OML_Float)(z00*rcp);
    /* inverse.yx */ Invert[0][1] = (OML_Float)(z01*rcp);
    /* inverse.xy */ Invert[1][0] = (OML_Float)(z10*rcp);
    /* inverse.zx */ Invert[0][2] = (OML_Float)(z02*rcp);
    /* inverse.xz */ Invert[2][0] = (OML_Float)(z20*rcp);
    /* inverse.wx */ Invert[0][3] = (OML_Float)(z03*rcp);
    /* inverse.xw */ Invert[3][0] = (OML_Float)(z30*rcp);
    /* inverse.yy */ Invert[1][1] = (OML_Float)(z11*rcp);
    /* inverse.zy */ Invert[1][2] = (OML_Float)(z12*rcp);
    /* inverse.yz */ Invert[2][1] = (OML_Float)(z21*rcp);
    /* inverse.wy */ Invert[1][3] = (OML_Float)(z13*rcp);
    /* inverse.yw */ Invert[3][1] = (OML_Float)(z31*rcp);
    /* inverse.zz */ Invert[2][2] = (OML_Float)(z22*rcp);
    /* inverse.wz */ Invert[2][3] = (OML_Float)(z23*rcp);
    /* inverse.zw */ Invert[3][2] = (OML_Float)(z32*rcp);
    /* inverse.ww */ Invert[3][3] = (OML_Float)(z33*rcp);

    return OML_Matrix4x4((OML_Float*) Invert);;

#undef x03
#undef x13
#undef x23
#undef x33
#undef z00
#undef z10
#undef z20
#undef z30
#undef z01
#undef z11
#undef z21
#undef z31

}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::Transpose
 *
 *  \return The matrix transposed.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Compute the transposed matrix.
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix4x4 OML_Matrix4x4::Transpose() const
{
	return OML_Matrix4x4(
		Matrix[0][0], Matrix[0][1], Matrix[0][2], Matrix[0][3], 
		Matrix[1][0], Matrix[1][1], Matrix[1][2], Matrix[1][3], 
		Matrix[2][0], Matrix[2][1], Matrix[2][2], Matrix[2][3], 
		Matrix[3][0], Matrix[3][1], Matrix[3][2], Matrix[3][3] );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::AutoTranspose
 *
 *  \return *this
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Transpose the matrix.
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix4x4& OML_Matrix4x4::AutoTranspose()
{
	OML_Float tmp;
	#define SWAP(i,j) tmp=Matrix[i][j]; Matrix[i][j]=Matrix[j][i]; Matrix[j][i]=tmp;
	SWAP(0,1);
	SWAP(0,2);
	SWAP(0,3);
	SWAP(1,2);
	SWAP(1,3);
	SWAP(2,3);
	#undef SWAP

	return *this;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::*
 *
 *  \return The product of the matrix by a vectOML.
 *	\param  v The result of the product.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OML_Vector3D OML_Matrix4x4::operator*( const OML_Vector3D& v)
{
	return OML_Vector3D(
		Matrix[0][0]*v[0]+Matrix[1][0]*v[1]+Matrix[2][0]*v[2]+Matrix[3][0],
		Matrix[0][1]*v[0]+Matrix[1][1]*v[1]+Matrix[2][1]*v[2]+Matrix[3][1],
		Matrix[0][2]*v[0]+Matrix[1][2]*v[1]+Matrix[2][2]*v[2]+Matrix[3][2]);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::SetZero
 *
 *  \return set all component of the matrix to zero.
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix4x4::SetZero()
{
	memset( Matrix, 0, 16*sizeof(OML_Float) );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::Randomize
 *
 *  \param  rMin minimum value
 *  \param  rMax maximum value
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix4x4::Randomize(OML_Float rMin, OML_Float rMax)
{	
	ITERATE(i,j, this->SetData( i, j, rMin + OML_RAND*(rMax-rMin) ); );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::Print
 *
 *  \param  cFOMLmat FOMLmat of the real number
 *  \param  f file to print to
 *  \author Gabriel Peyré 2001-09-19
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
void OML_Matrix4x4::Print(char *cFOMLmat, FILE *f)
{
	/** \todo */
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::Norm1
 *
 *  \return pseuo-nOMLm 1 of the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_Matrix4x4::Norm1()
{
	OML_Float rNOMLm = 0;
	ITERATE(i,j, rNOMLm+=this->GetData(i,j); )
	return  rNOMLm;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::Norm2
 *
 *  \return pseuo-nOMLm 2 of the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_Matrix4x4::Norm2()
{
	OML_Float rNOMLm = 0;
	ITERATE(i,j, rNOMLm+=this->GetData(i,j)*this->GetData(i,j); )
	return  OML_Maths::sqrt( rNOMLm );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Matrix4x4::NormInf
 *
 *  \return pseudo-infinite nOMLm of the matrix.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OML_Float OML_Matrix4x4::NormInf()
{
	OML_Float rNOMLm = 0;
	ITERATE(i,j, 
		if(OML_ABS(this->GetData(i,j))>rNOMLm) 
			rNOMLm=this->GetData(i,j); 
	)
	return rNOMLm;
}

#undef ITERATE

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

