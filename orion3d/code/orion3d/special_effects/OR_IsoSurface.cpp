/*------------------------------------------------------------------------*/
/*                         OR_IsoSurface.cpp                              */
/*------------------------------------------------------------------------*/
/*                Implementation of class IsoSurface                      */
/*------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_IsoSurface.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_IsoSurface.h"

#ifndef OR_USE_INLINE
	#include "OR_IsoSurface.inl"
#endif

namespace OR
{
	
#define OR_DEFAULT_ISOSURFACE_SIZE 30

/*------------------------------------------------------------------------*/
/*                            class OR_IsoSurface                         */
/*------------------------------------------------------------------------*/
/* draw an iso-surface given it's grid and its iso level                  */
/*------------------------------------------------------------------------*/

OR_IsoSurface::OR_IsoSurface( OR_Float isolevel )
:	IsoLevel	( isolevel )
{
	/* determine the number of the display list */
	NumList = glGenLists(1);
	Grid_.Reset(OR_DEFAULT_ISOSURFACE_SIZE, OR_DEFAULT_ISOSURFACE_SIZE, OR_DEFAULT_ISOSURFACE_SIZE);
}

void OR_IsoSurface::Render(OR_Bool recompute)
{	
	if (true)//recompute)
	{
	glNewList(NumList, GL_COMPILE_AND_EXECUTE);
		/* draw the balls */
		glBegin(GL_TRIANGLES);
		for(OR_U32 x=1; x<Grid_.GetGridSizeX()-2; x++)
		for(OR_U32 y=1; y<Grid_.GetGridSizeY()-2; y++)
		for(OR_U32 z=1; z<Grid_.GetGridSizeZ()-2; z++)
			RenderCell(x, y, z);
		glEnd();	
	glEndList();
	}
	else
	{
		glCallList(NumList);
	}
}

} // namespace OR

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
