/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaGrid.inl
 *  \brief Inlined methods for \c OR_MetaGrid
 *  \author Gabriel Peyré 2002/04/14
 */ 
/*------------------------------------------------------------------------------*/

#include "OR_MetaGrid.h"

namespace OR {

#define ACCESS(i, j, k) (k)+(j)*uGridSize_[Z]+(i)*uGridSize_[Z]*uGridSize_[Y]

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaGrid::SetSupportGizmo( OR_CubeGizmo& SupportGizmo )
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	AddCommentHere
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MetaGrid::SetSupportGizmo( OR_CubeGizmo& SupportGizmo )
{
	pSuportGizmo_  =&SupportGizmo;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CubeGizmo* OR_MetaGrid::GetSupportGizmo()
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	AddCommentHere
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_CubeGizmo* OR_MetaGrid::GetSupportGizmo()
{
	return pSuportGizmo_;	
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_U32 OR_MetaGrid::GetGridSizeX() const
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	AddCommentHere
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MetaGrid::GetGridSizeX() const
{
	return uGridSize_[X];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_U32 OR_MetaGrid::GetGridSizeY() const
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	AddCommentHere
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MetaGrid::GetGridSizeY() const
{
	return uGridSize_[Y];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_U32 OR_MetaGrid::GetGridSizeZ() const
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	AddCommentHere
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_MetaGrid::GetGridSizeZ() const
{
	return uGridSize_[Z];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaGrid::SetData(OR_U32 x, OR_U32 y, OR_U32 z, OR_Float val)
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	access the array.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MetaGrid::SetData(OR_U32 x, OR_U32 y, OR_U32 z, OR_Float val)
{
	OR_ASSERT( x<uGridSize_[X] );
	OR_ASSERT( y<uGridSize_[Y] );
	OR_ASSERT( z<uGridSize_[Z] );
	aArray_[ACCESS(x,y,z)] = val;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaGrid::AddData(OR_U32 x, OR_U32 y, OR_U32 z, OR_Float val)
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	access the array.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MetaGrid::AddData(OR_U32 x, OR_U32 y, OR_U32 z, OR_Float val)
{
	OR_ASSERT( x<uGridSize_[X] );
	OR_ASSERT( y<uGridSize_[Y] );
	OR_ASSERT( z<uGridSize_[Z] );
	aArray_[ACCESS(x,y,z)] += val;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Float OR_MetaGrid::GetData(OR_U32 x, OR_U32 y, OR_U32 z) const
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	access the array.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MetaGrid::GetData(OR_U32 x, OR_U32 y, OR_U32 z) const
{
	OR_ASSERT( x<uGridSize_[X] );
	OR_ASSERT( y<uGridSize_[Y] );
	OR_ASSERT( z<uGridSize_[Z] );
	return aArray_[ACCESS(x,y,z)];
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaGrid::CalcNormalX(OR_I32 x, OR_I32 y, OR_I32 z, OR_Vector3D& Normal)
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	compute a normal at a point of the grid, using interpolation on a given direction.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE 
void OR_MetaGrid::CalcNormalX(OR_I32 x, OR_I32 y, OR_I32 z, OR_Float IsoLevel, OR_Vector3D& Normal) const
{
	/* Normal[X]=2*( aArray_[ACCESS(x+1, y, z)]-aArray_[ACCESS(x, y, z)] ); */
	Normal[X] = InterpVal( aArray_[ACCESS(x+1, y, z)], aArray_[ACCESS(x, y, z)], 
				aArray_[ACCESS(x+2, y, z)]-aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x+1, y, z)]-aArray_[ACCESS(x-1, y, z)] , IsoLevel );
	Normal[Y] = InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x+1, y, z)], aArray_[ACCESS(x, y+1, z)], aArray_[ACCESS(x+1, y+1, z)] , IsoLevel ) -
				InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x+1, y, z)], aArray_[ACCESS(x, y-1, z)], aArray_[ACCESS(x+1, y-1, z)] , IsoLevel);
	Normal[Z] = InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x+1, y, z)], aArray_[ACCESS(x, y, z+1)], aArray_[ACCESS(x+1, y, z+1)] , IsoLevel ) -
				InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x+1, y, z)], aArray_[ACCESS(x, y, z-1)], aArray_[ACCESS(x+1, y, z-1)] , IsoLevel);
	/* re-normalize */
	Normal.Normalize();
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaaArray_::CalcNormalY(OR_I32 x, OR_I32 y, OR_I32 z, OR_Vector3D& Normal)
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	compute a normal at a point of the grid, using interpolation on a given direction.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE  
void OR_MetaGrid::CalcNormalY(OR_I32 x, OR_I32 y, OR_I32 z, OR_Float IsoLevel, OR_Vector3D& Normal) const
{
	/* Normal[Y]=2*( aArray_[ACCESS(x, y+1, z)]-aArray_[ACCESS(x, y, z)] ); */
	Normal[Y] = InterpVal( aArray_[ACCESS(x, y+1, z)], aArray_[ACCESS(x, y, z)], 
				aArray_[ACCESS(x, y+2, z)]-aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y+1, z)]-aArray_[ACCESS(x, y-1, z)] , IsoLevel );
	Normal[X] = InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y+1, z)], aArray_[ACCESS(x+1, y, z)], aArray_[ACCESS(x+1, y+1, z)]  , IsoLevel) -
				InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y+1, z)], aArray_[ACCESS(x-1, y, z)], aArray_[ACCESS(x-1, y+1, z)]  , IsoLevel);
	Normal[Z] = InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y+1, z)], aArray_[ACCESS(x, y, z+1)], aArray_[ACCESS(x, y+1, z+1)]  , IsoLevel) -
				InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y+1, z)], aArray_[ACCESS(x, y, z-1)], aArray_[ACCESS(x, y+1, z-1)]  , IsoLevel);
	/* re-normalize */
	Normal.Normalize();
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaaArray_::CalcNormalZ(OR_I32 x, OR_I32 y, OR_I32 z, OR_Vector3D& Normal)
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	compute a normal at a point of the grid, using interpolation on a given direction.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE  
void OR_MetaGrid::CalcNormalZ(OR_I32 x, OR_I32 y, OR_I32 z, OR_Float IsoLevel, OR_Vector3D& Normal) const
{
	/* Normal[Z]=2*( aArray_[ACCESS(x, y, z+1)]-aArray_[ACCESS(x, y, z)] ); */
	Normal[Z]=InterpVal( aArray_[ACCESS(x, y, z+1)], aArray_[ACCESS(x, y, z)], 
			  aArray_[ACCESS(x, y, z+2)]-aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y, z+1)]-aArray_[ACCESS(x, y, z-1)], IsoLevel );
	Normal[Y]=InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y, z+1)], aArray_[ACCESS(x, y+1, z)], aArray_[ACCESS(x, y+1, z+1)] , IsoLevel) -
			  InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y, z+1)], aArray_[ACCESS(x, y-1, z)], aArray_[ACCESS(x, y-1, z+1)] , IsoLevel);
	Normal[X]=InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y, z+1)], aArray_[ACCESS(x+1, y, z)], aArray_[ACCESS(x+1, y, z+1)] , IsoLevel) -
			  InterpVal( aArray_[ACCESS(x, y, z)], aArray_[ACCESS(x, y, z+1)], aArray_[ACCESS(x-1, y, z)], aArray_[ACCESS(x-1, y, z+1)] , IsoLevel);
	/* re-normalize */
	Normal.Normalize();
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaGrid::InterpVal
 *
 *  \interpolate between two values.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/ 
OR_INLINE
OR_Float OR_MetaGrid::InterpVal(OR_Float val1, OR_Float val2, OR_Float val_cible1, OR_Float val_cible2, OR_Float IsoLevel)
{
	OR_Float mu; 
	if( fabsf(IsoLevel-val1) < OR_EPSILON ) 
		return val_cible1;
	if( fabsf(IsoLevel-val2) < OR_EPSILON ) 
		return val_cible2;
	if( fabsf(val1-val2) < OR_EPSILON )
		return val_cible1;
	mu = (IsoLevel - val1) / (val2 - val1); 
	return val_cible1 + mu * (val_cible2 - val_cible1);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaGrid::SetZero()
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	initialize the grid.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MetaGrid::SetZero()
{
	memset(aArray_, 0, uGridSize_[X]*uGridSize_[Y]*uGridSize_[Z]*sizeof(OR_Float) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaGrid::ComputePosition(OR_U32 x, OR_U32 y, OR_U32 z, OR_Vector3D& pos) const
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	compute the position of a point in the grid.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MetaGrid::ComputePosition(OR_U32 x, OR_U32 y, OR_U32 z, OR_Vector3D& pos) const
{
	OR_ASSERT( x<uGridSize_[X] );
	OR_ASSERT( y<uGridSize_[Y] );
	OR_ASSERT( z<uGridSize_[Z] );
	OR_ASSERT( pSuportGizmo_!=NULL );
	pos = pSuportGizmo_->GetAbsolutePosition();
	pos[X] += (2.0*x - uGridSize_[X])*pSuportGizmo_->GetDim()[X]/uGridSize_[X];
	pos[Y] += (2.0*y - uGridSize_[Y])*pSuportGizmo_->GetDim()[Y]/uGridSize_[Y];
	pos[Z] += (2.0*z - uGridSize_[Z])*pSuportGizmo_->GetDim()[Z]/uGridSize_[Z];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Float OR_MetaGrid::GetRealSizeX() const
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	get the half size of the grid in world dimension.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MetaGrid::GetRealSizeX() const
{
	OR_ASSERT( pSuportGizmo_!=NULL );
	return pSuportGizmo_->GetDim()[X];
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Float OR_MetaGrid::GetRealSizeY() const
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	get the half size of the grid in world dimension.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MetaGrid::GetRealSizeY() const
{
	OR_ASSERT( pSuportGizmo_!=NULL );
	return pSuportGizmo_->GetDim()[Y];
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Float OR_MetaGrid::GetRealSizeZ() const
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	get the half size of the grid in world dimension.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MetaGrid::GetRealSizeZ() const
{
	OR_ASSERT( pSuportGizmo_!=NULL );
	return pSuportGizmo_->GetDim()[Z];
}


#undef ACCESS

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

