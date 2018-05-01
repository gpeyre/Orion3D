/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MathSurface.inl
 *  \brief Inlined methods for \c OR_MathSurface
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_MathSurface.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetUserParam
 *
 *  \param  pUserParam the new user param.
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetUserParam(void* pUserParam)
{
	pUserParam_ = pUserParam;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::GetUserParam
 *
 *  \return the user param of the callback function.
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void* OR_MathSurface::GetUserParam()
{
	return pUserParam_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetURange
 *
 *  \param  rUMin minimum value on U
 *  \param  rUMax maximum value on U
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetURange(OR_Float rUMin, OR_Float rUMax)
{
	rUMin_ = rUMin;
	rUMax_ = rUMax;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetVRange
 *
 *  \param  rVMin minimum value on V
 *  \param  rVMax maximum value on V
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetVRange(OR_Float rVMin, OR_Float rVMax)
{
	rVMin_ = rVMin;
	rVMax_ = rVMax;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetRange
 *
 *  \param  rUMin minimum value on U
 *  \param  rUMax maximum value on U
 *  \param  rVMin minimum value on V
 *  \param  rVMax maximum value on V
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetRange(OR_Float rUMin, OR_Float rUMax, OR_Float rVMin, OR_Float rVMax)
{
	rUMin_ = rUMin;
	rUMax_ = rUMax;
	rVMin_ = rVMin;
	rVMax_ = rVMax;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetUMin
 *
 *  \param  rUMin minimum value on U
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetUMin(OR_Float rUMin)
{
	rUMin_ = rUMin;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetVMin
 *
 *  \param  rVMin minimum value on V
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetVMin(OR_Float rVMin)
{
	rVMin_ = rVMin;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetUMax
 *
 *  \param  rUMax Maximum value on U
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetUMax(OR_Float rUMax)
{
	rUMax_ = rUMax;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetVMax
 *
 *  \param  rVMax Maximum value on V
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetVMax(OR_Float rVMax)
{
	rVMax_ = rVMax;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::GetUMax
 *
 *  \return maximum value on U
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MathSurface::GetUMax()
{
	return rUMax_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::GetVMax
 *
 *  \return maximum value on V
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MathSurface::GetVMax()
{
	return rVMax_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::GetUMin
 *
 *  \return maximum value on U
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MathSurface::GetUMin()
{
	return rUMin_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::GetVMin
 *
 *  \return maximum value on V
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MathSurface::GetVMin()
{
	return rVMin_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetPrecision
 *
 *  \param  nUPrecision precision on U
 *  \param  nVPrecision precision on V
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetPrecision(OR_U32 nUPrecision, OR_U32 nVPrecision)
{
	nUPrecision_ = nUPrecision;
	nVPrecision_ = nVPrecision;
	this->ResizeTempArrays();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetUPrecision
 *
 *  \param  nUPrecision precision on U
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetUPrecision(OR_U32 nUPrecision)
{
	nUPrecision_ = nUPrecision;
	this->ResizeTempArrays();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetVPrecision
 *
 *  \param  nUPrecision precision on V
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetVPrecision(OR_U32 nVPrecision)
{
	nVPrecision_ = nVPrecision;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::GetUPrecision
 *
 *  \return precision on U
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MathSurface::GetUPrecision()
{
	return nUPrecision_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::GetVPrecision
 *
 *  \return precision on V
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MathSurface::GetVPrecision()
{
	return nVPrecision_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::ComputeNormal
 *
 *  \param  norm the normal to compute.
 *  \param  u U param value.
 *  \param  v V param value.
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::ComputeNormal(OR_Vector3D& norm, OR_Float u, OR_Float v)
{
	OR_ASSERT(pCallbackFunc_!=NULL);

	OR_Vector3D V1, V2;

	pCallbackFunc_(V1, u+OR_EPSILON,v, pUserParam_);
	pCallbackFunc_(V1, u-OR_EPSILON,v, pUserParam_);
	OR_Vector3D du = V1 - V2;
	pCallbackFunc_(V1, u,v+OR_EPSILON, pUserParam_);
	pCallbackFunc_(V1, u,v-OR_EPSILON, pUserParam_);
	OR_Vector3D dv = V1 - V2;
	
	norm = !( du^dv );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::ComputeValue
 *
 *  \param  val the value to compute.
 *  \param  u U param value.
 *  \param  v V param value.
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::ComputeValue(OR_Vector3D& val, OR_Float u, OR_Float v)
{
	pCallbackFunc_(val, u,v, pUserParam_);
}

    

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::ResizeTempArrays
 *
 *  \author Gabriel Peyré 2001-11-12
 *
 *	Resize the temporary arrays according to the size of the grid.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::ResizeTempArrays()
{
	OR_DELETEARRAY(norm1);
	OR_DELETEARRAY(norm2);
	OR_DELETEARRAY(vert1);
	OR_DELETEARRAY(vert2);
	norm1 = new OR_Vector3D[nUPrecision_+1];
	norm2 = new OR_Vector3D[nUPrecision_+1];
	vert1 = new OR_Vector3D[nUPrecision_+1];
	vert2 = new OR_Vector3D[nUPrecision_+1];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::SetCallback
 *
 *  \param  pFunc the function used to compute the value of the surface.
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MathSurface::SetCallback(T_MathSurf_Callback pFunc)
{
	pCallbackFunc_ = pFunc;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::GetCallback
 *
 *  \return the function used to compute the value of the surface.
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
T_MathSurf_Callback OR_MathSurface::GetCallback()
{
	return pCallbackFunc_;
}


} // End namespace OR

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

