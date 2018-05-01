/*-------------------------------------------------------------------------*/
/*                             IsoSurface.h                                */
/*-------------------------------------------------------------------------*/
/*                         Definition of class IsoSurface                  */
/*-------------------------------------------------------------------------*/

/** \file 
	Contains the definition of an iso-surface, wich is used to compute an iso-value
	surface given a 3D grid of OR_Float, which can be seen as a potential field.

	It uses the marching cube algo to compute the surface.
	\author Gabriel.
**/

#ifndef _ISOSURFACE_H_
#define _ISOSURFACE_H_

#include "../configuration/OR_Config.h"
#include "OR_MetaGrid.h"
#include "../maths/OR_Maths.h"
#include "../shaders/OR_Texture.h"
#include "../maths/OR_Maths.h"

namespace OR
{	

/** a face used by the marching cube algo */
class OR_ISO_Face
{

public:

	OR_Vector3D *Vert[3];
	OR_I32 Num[3];
};

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MetaGrid
 *  \brief  an iso-surface computed using the marching cube algo
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	the iso-surface is defined via a potential field, stored in a 3D grid.
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_IsoSurface
{
public:

	/**	constructor */
	OR_IsoSurface( OR_Float isolevel = 1 );

	//-------------------------------------------------------------------------
	/** \name accessors */
	//-------------------------------------------------------------------------
	//@{
	OR_MetaGrid& GetGrid();
	/** set the isolevel */
	void SetIsoLevel(OR_Float);
	/** get the isolevel */
	OR_Float GetIsoLevel() const;
	//@}
	

	/** calculate and the render whole surface */
	void Render(OR_Bool recompute);

private:

	/** the grid used to compute the values */
	OR_MetaGrid Grid_;
	/** value of the iso-level */
	OR_Float IsoLevel;
	/** the number of the display list */
	unsigned long NumList;
	/** draw the normal or not */
	OR_Bool DrawNormal;
	/** a list of vertex */
	OR_Vector3D VertList[12];
	/** a list af face to draw (the Vert should point on a vertex of VertList) */
	OR_ISO_Face Triangles[12];
	
	/** put the triangles to be render into Triangles and return the number of triangles */
	OR_I32 Polygonize(OR_I32 x, OR_I32 y, OR_I32 z);
	
	/** render a cell */
	void RenderCell(OR_I32 x, OR_I32 y, OR_I32 z);

	/** datas used by the marching cube algo */
	static OR_I32 edgeTable[256];
	static OR_I32 triTable[256][16];

};


} // namespace OR

#ifdef OR_USE_INLINE
	#include "OR_IsoSurface.inl"
#endif

#endif				/* #ifndef _ISOSURFACE_H_ */


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////