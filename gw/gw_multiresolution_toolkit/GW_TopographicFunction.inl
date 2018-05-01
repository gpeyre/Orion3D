/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_TopographicFunction.inl
 *  \brief  Inlined methods for \c GW_TopographicFunction
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/
#include "GW_TopographicFunction.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction constructor
/**
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 * 
 *  Constructor
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_TopographicFunction::GW_TopographicFunction()
:	GW_TreeFunction_ABC()
{
	aData_ = 0;
	aSize_[0] = aSize_[1] = 0;
}

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::virtual ~GW_TopographicFunction
/**
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 * 
 *  Destructor
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_TopographicFunction::~GW_TopographicFunction()
{
	if(aData_!=NULL)
		GW_DELETEARRAY(aData_);
}

#define ACCESS_ENTRY(x,y) x + (y)*aSize_[X]
/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::GW_AcessData
/**
 *  \param  uX [GW_U32] Numer of the column.
 *  \param  uY [GW_U32] Number of the row.
 *  \return [GW_Float] Value of the array.
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 * 
 *  Get the value of the array at a given location.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Float GW_TopographicFunction::AccessData( GW_U32 uX, GW_U32 uY ) const
{
	GW_ASSERT(aData_!=NULL);
	GW_ASSERT( uX<aSize_[X] );
	GW_ASSERT( uY<aSize_[Y] );
	return aData_[ ACCESS_ENTRY(uX,uY) ];
}

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::SetData
/**
 *  \param  rVal [GW_Float] value of the entry
 *  \param  uX [GW_U32] X position
 *  \param  uY [GW_U32] Y position
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Set a data in the array.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_TopographicFunction::SetData( GW_Float rVal, GW_U32 uX, GW_U32 uY ) const
{
	GW_ASSERT(aData_!=NULL);
	GW_ASSERT( uX<aSize_[X] );
	GW_ASSERT( uY<aSize_[Y] );
	aData_[ ACCESS_ENTRY(uX,uY) ] = rVal;
}
#undef ACCESS_ENTRY


/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::GetMax
/**
 *  \return [GW_Float] The maximum value
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Get the maximum value of the data set.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Float GW_TopographicFunction::GetMax()
{
	return rMax_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::GetMin
/**
 *  \return [GW_Float] The minimum value
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Get the minimum value of the data set.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Float GW_TopographicFunction::GetMin()
{
	return rMin_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::GetValue
/**
 *  \param  rU [GW_Float] V coord in [0,1].
 *  \param  rV [GW_Float] U coord.
 *  \author Gabriel Peyré
 *  \date   11-29-2002
 * 
 *  Get the value of the function at a given location.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Float GW_TopographicFunction::GetValue( GW_Float rU, GW_Float rV ) const
{
	GW_ASSERT( rU>=0 );
	GW_ASSERT( rV>=0 );
	GW_ASSERT( rU<=1 );
	GW_ASSERT( rV<=1 );
	/* convert to coords in array index */
	GW_Float rIndexX = rU*aSize_[X];
	GW_Float rIndexY = rV*aSize_[Y];
	
	GW_U32 rNearX  = (GW_U32) floor(rIndexX);
	GW_U32 rNearY  = (GW_U32) floor(rIndexY);
	GW_Float s = rIndexX - rNearX;
	GW_Float t = rIndexY  - rNearY;
	/* clamp to [0,aSize-1]*/
	rNearX  = rNearX % aSize_[X];
	rNearY  = rNearY % aSize_[Y];
	GW_U32 rNearX1 = (rNearX+1) % aSize_[X];
	GW_U32 rNearY1 = (rNearY +1) % aSize_[Y];
	/* use bilinear interpolation */
	GW_Float rVal  = (1-s)*this->AccessData(rNearX, rNearY)  + s*AccessData(rNearX1, rNearY);
	GW_Float rVal1 = (1-s)*this->AccessData(rNearX, rNearY1) + s*AccessData(rNearX1, rNearY1);
	return (1-t)*rVal + t*rVal1;
}


/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::GetWidth
/**
 *  \return [GW_U32] The width.
 *  \author Gabriel Peyré
 *  \date   6-6-2003
 * 
 *  GetThe width of the image.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_U32 GW_TopographicFunction::GetWidth()
{
	return aSize_[0];
}

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::GetHeight
/**
 *  \return [GW_U32] The height.
 *  \author Gabriel Peyré
 *  \date   6-6-2003
 * 
 *  Get the heigth of the image.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_U32 GW_TopographicFunction::GetHeight()
{
	return aSize_[1];
}

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::GetData
/**
 *  \return [GW_Float*] the data pointer.
 *  \author Gabriel Peyré
 *  \date   6-6-2003
 * 
 *  Get the raw data. Use it at you own risk !
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Float* GW_TopographicFunction::GetData()
{
	return aData_;
}


GW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2002 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
