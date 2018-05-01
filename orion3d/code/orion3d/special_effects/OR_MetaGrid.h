/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaGrid.h
 *  \brief Definition of class \c OR_MetaGrid
 *  \author Gabriel Peyré 2002/04/14
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_MetaGrid_h_
#define __OR_MetaGrid_h_

#include "../configuration/OR_Config.h"
#include "../objects/OR_CubeGizmo.h"
				  
namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MetaGrid
 *  \brief  AddCommentHere
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	Just a grid of value.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_MetaGrid
{
public:

    //-------------------------------------------------------------------------
    /** \name Constructor and destructor */
    //-------------------------------------------------------------------------
    //@{
	OR_MetaGrid( OR_CubeGizmo* pSuportGizmo = NULL );
	~OR_MetaGrid();
	//@}

	void Reset( OR_U32 size_x, OR_U32 size_y, OR_U32 size_z );
	void SetZero();										
	void ComputePosition(OR_U32 x, OR_U32 y, OR_U32 z, OR_Vector3D& pos) const;

	//-------------------------------------------------------------------------
	/** \name  accessors */
	//-------------------------------------------------------------------------
	//@{
	void			SetSupportGizmo( OR_CubeGizmo& SupportGizmo );
	OR_CubeGizmo*	GetSupportGizmo();
	OR_U32			GetGridSizeX() const;
	OR_U32			GetGridSizeY() const;
	OR_U32			GetGridSizeZ() const;
	OR_Float		GetRealSizeX() const;
	OR_Float		GetRealSizeY() const;
	OR_Float		GetRealSizeZ() const;

	void		SetData(OR_U32 x, OR_U32 y, OR_U32 z, OR_Float val);
	void		AddData(OR_U32 x, OR_U32 y, OR_U32 z, OR_Float val);
	OR_Float	GetData(OR_U32 x, OR_U32 y, OR_U32 z) const;
	//@}

	//-------------------------------------------------------------------------
	/** \name compute a normal for a vertex on a given axis */
	//-------------------------------------------------------------------------
	//@{
	void CalcNormalX(OR_I32 x, OR_I32 y, OR_I32 z, OR_Float IsoLevel, OR_Vector3D& Normal) const;
	void CalcNormalY(OR_I32 x, OR_I32 y, OR_I32 z, OR_Float IsoLevel, OR_Vector3D& Normal) const;
	void CalcNormalZ(OR_I32 x, OR_I32 y, OR_I32 z, OR_Float IsoLevel, OR_Vector3D& Normal) const;

	static OR_Float InterpVal(OR_Float val1, OR_Float val2, OR_Float val_cible1, OR_Float val_cible2, OR_Float IsoLevel);
	//@}	

private:

	/** the support of the meta-env */
	OR_CubeGizmo* pSuportGizmo_;
	/** size of the grid in number of cells */
	OR_U32 uGridSize_[3];
	/** the array of values */
	OR_Float* aArray_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_MetaGrid.inl"
#endif

#endif // __OR_MetaGrid_h_

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

