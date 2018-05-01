/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_TopographicFunction.inl
 *  \brief  Inlined methods for \c FSW_TopographicFunction
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/
#include "FSW_TopographicFunction.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction constructor
/**
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 * 
 *  Constructor
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_TopographicFunction::FSW_TopographicFunction()
:	FSW_TreeFunction_ABC()
{
	aData_ = 0;
	aSize_[0] = aSize_[1] = 0;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction::virtual ~FSW_TopographicFunction
/**
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 * 
 *  Destructor
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_TopographicFunction::~FSW_TopographicFunction()
{
	if(aData_!=NULL)
		FSW_DELETEARRAY(aData_);
}

#define ACCESS_ENTRY(x,y) x + (y)*aSize_[X]
/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction::FSW_AcessData
/**
 *  \param  uX [FSW_U32] Numer of the column.
 *  \param  uY [FSW_U32] Number of the row.
 *  \return [FSW_Float] Value of the array.
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 * 
 *  Get the value of the array at a given location.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Float FSW_TopographicFunction::AccessData( FSW_U32 uX, FSW_U32 uY ) const
{
	FSW_ASSERT(aData_!=NULL);
	FSW_ASSERT( uX<aSize_[X] );
	FSW_ASSERT( uY<aSize_[Y] );
	return aData_[ ACCESS_ENTRY(uX,uY) ];
}

/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction::SetData
/**
 *  \param  rVal [FSW_Float] value of the entry
 *  \param  uX [FSW_U32] X position
 *  \param  uY [FSW_U32] Y position
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Set a data in the array.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_TopographicFunction::SetData( FSW_Float rVal, FSW_U32 uX, FSW_U32 uY ) const
{
	FSW_ASSERT(aData_!=NULL);
	FSW_ASSERT( uX<aSize_[X] );
	FSW_ASSERT( uY<aSize_[Y] );
	aData_[ ACCESS_ENTRY(uX,uY) ] = rVal;
}
#undef ACCESS_ENTRY


/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction::GetMax
/**
 *  \return [FSW_Float] The maximum value
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Get the maximum value of the data set.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Float FSW_TopographicFunction::GetMax()
{
	return rMax_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction::GetMin
/**
 *  \return [FSW_Float] The minimum value
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Get the minimum value of the data set.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Float FSW_TopographicFunction::GetMin()
{
	return rMin_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction::GetValue
/**
 *  \param  rU [FSW_Float] V coord in [0,1].
 *  \param  rV [FSW_Float] U coord.
 *  \author Gabriel Peyré
 *  \date   11-29-2002
 * 
 *  Get the value of the function at a given location.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Float FSW_TopographicFunction::GetValue( FSW_Float rU, FSW_Float rV ) const
{
	FSW_ASSERT( rU>=0 );
	FSW_ASSERT( rV>=0 );
	FSW_ASSERT( rU<=1 );
	FSW_ASSERT( rV<=1 );
	/* convert to coords in array index */
	FSW_Float rIndexX = rU*aSize_[X];
	FSW_Float rIndexY = rV*aSize_[Y];
	
	FSW_U32 rNearX  = (FSW_U32) floor(rIndexX);
	FSW_U32 rNearY  = (FSW_U32) floor(rIndexY);
	FSW_Float s = rIndexX - rNearX;
	FSW_Float t = rIndexY  - rNearY;
	/* clamp to [0,aSize-1]*/
	rNearX  = rNearX % aSize_[X];
	rNearY  = rNearY % aSize_[Y];
	FSW_U32 rNearX1 = (rNearX+1) % aSize_[X];
	FSW_U32 rNearY1 = (rNearY +1) % aSize_[Y];
	/* use bilinear interpolation */
	FSW_Float rVal  = (1-s)*this->AccessData(rNearX, rNearY)  + s*AccessData(rNearX1, rNearY);
	FSW_Float rVal1 = (1-s)*this->AccessData(rNearX, rNearY1) + s*AccessData(rNearX1, rNearY1);
	return (1-t)*rVal + t*rVal1;
}


FSW_END_NAMESPACE


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
