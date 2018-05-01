/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_IsoSurface.inl
 *  \brief Inlined methods for \c OR_IsoSurface
 *  \author Gabriel Peyré 2002/04/15
 */ 
/*------------------------------------------------------------------------------*/

#include "OR_IsoSurface.h"

namespace OR {


	
/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IsoSurface::Polygonize
 *
 *	Compute the faces of the surface in a given cell of the grid.
 *
 *  \author Gabriel Peyré 2002/04/15
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_I32 OR_IsoSurface::Polygonize(OR_I32 x, OR_I32 y, OR_I32 z)
{
	OR_I32 i;
	OR_Float gridval[8];
	OR_I32 cubeindex = 0;
	OR_I32 ntriang = 0;
	OR_Vector3D gridpos[8];
  
	/* compute the value of gridval */
	/*  gridval[0]=Eval(x, y, z);
		gridval[1]=Eval(x+1, y, z);
		gridval[2]=Eval(x+1, y, z+1);
		gridval[3]=Eval(x, y, z+1);
		gridval[4]=Eval(x, y+1, z);
		gridval[5]=Eval(x+1, y+1, z);
		gridval[6]=Eval(x+1, y+1, z+1);
		gridval[7]=Eval(x, y+1, z+1); */
	/* base adress in the grid*/
	gridval[0] = Grid_.GetData(x,  y,  z  );
	gridval[1] = Grid_.GetData(x+1,y,  z  );
	gridval[2] = Grid_.GetData(x+1,y,  z+1);
	gridval[3] = Grid_.GetData(x,  y,  z+1);
	gridval[4] = Grid_.GetData(x,  y+1,z  );
	gridval[5] = Grid_.GetData(x+1,y+1,z  );
	gridval[6] = Grid_.GetData(x+1,y+1,z+1);
	gridval[7] = Grid_.GetData(x,  y+1,z+1);
	
  
	/* compute the value of gridpos */
	/*	EvalPos(x, y, z, 0)
		EvalPos(x+1, y, z, 1)
		EvalPos(x+1, y, z+1, 2)
		EvalPos(x, y, z+1, 3)
		EvalPos(x, y+1, z, 4)
		EvalPos(x+1, y+1, z, 5)
		EvalPos(x+1, y+1, z+1, 6)
		EvalPos(x, y+1, z+1, 7) */
	OR_Float base_x = ((OR_Float) x*2-Grid_.GetGridSizeX())*Grid_.GetRealSizeX()/((OR_Float) Grid_.GetGridSizeX());
	OR_Float base_y = ((OR_Float) y*2-Grid_.GetGridSizeY())*Grid_.GetRealSizeY()/((OR_Float) Grid_.GetGridSizeY());
	OR_Float base_z = ((OR_Float) z*2-Grid_.GetGridSizeZ())*Grid_.GetRealSizeZ()/((OR_Float) Grid_.GetGridSizeZ());
	OR_Float delta_x = 2.0f*Grid_.GetRealSizeX()/((OR_Float) Grid_.GetGridSizeX());
	OR_Float delta_y = 2.0f*Grid_.GetRealSizeY()/((OR_Float) Grid_.GetGridSizeY());
	OR_Float delta_z = 2.0f*Grid_.GetRealSizeZ()/((OR_Float) Grid_.GetGridSizeZ());
	gridpos[0][X]=base_x;
	gridpos[0][Y]=base_y;
	gridpos[0][Z]=base_z;
	gridpos[1][X]=base_x+delta_x;
	gridpos[1][Y]=base_y;
	gridpos[1][Z]=base_z;
	gridpos[2][X]=base_x+delta_x;
	gridpos[2][Y]=base_y;
	gridpos[2][Z]=base_z+delta_z;
	gridpos[3][X]=base_x;
	gridpos[3][Y]=base_y;
	gridpos[3][Z]=base_z+delta_z;
	gridpos[4][X]=base_x;
	gridpos[4][Y]=base_y+delta_y;
	gridpos[4][Z]=base_z;
	gridpos[5][X]=base_x+delta_x;
	gridpos[5][Y]=base_y+delta_y;
	gridpos[5][Z]=base_z;
	gridpos[6][X]=base_x+delta_x;
	gridpos[6][Y]=base_y+delta_y;
	gridpos[6][Z]=base_z+delta_z;
	gridpos[7][X]=base_x;
	gridpos[7][Y]=base_y+delta_y;
	gridpos[7][Z]=base_z+delta_z;

	/*	Determine the index into the edge table which
		tells us which vertices are inside of the surface   */   
	if(gridval[0] < IsoLevel) cubeindex |= 1;
	if(gridval[1] < IsoLevel) cubeindex |= 2;
	if(gridval[2] < IsoLevel) cubeindex |= 4;
	if(gridval[3] < IsoLevel) cubeindex |= 8;
	if(gridval[4] < IsoLevel) cubeindex |= 16;
	if(gridval[5] < IsoLevel) cubeindex |= 32;
	if(gridval[6] < IsoLevel) cubeindex |= 64;
	if(gridval[7] < IsoLevel) cubeindex |= 128;

	/* Cube is entirely in/out of the surface */   
	if (edgeTable[cubeindex] == 0) return(0);   

	/* Find the vertices where the surface intersects the cube */
	if (edgeTable[cubeindex] & 1)      
		OR_Vector3D::Interpolate(gridpos[0], gridpos[1], gridval[0], gridval[1], IsoLevel, VertList[0]);
	if (edgeTable[cubeindex] & 2)      
		OR_Vector3D::Interpolate(gridpos[1], gridpos[2], gridval[1], gridval[2], IsoLevel, VertList[1]);
	if (edgeTable[cubeindex] & 4)      
		OR_Vector3D::Interpolate(gridpos[2], gridpos[3], gridval[2], gridval[3], IsoLevel, VertList[2]);
	if (edgeTable[cubeindex] & 8)      
		OR_Vector3D::Interpolate(gridpos[3], gridpos[0], gridval[3], gridval[0], IsoLevel, VertList[3]);
	if (edgeTable[cubeindex] & 16)      
	    OR_Vector3D::Interpolate(gridpos[4], gridpos[5], gridval[4], gridval[5], IsoLevel, VertList[4]);
	if (edgeTable[cubeindex] & 32)       
		OR_Vector3D::Interpolate(gridpos[5], gridpos[6], gridval[5], gridval[6], IsoLevel, VertList[5]);
	if (edgeTable[cubeindex] & 64)      
		OR_Vector3D::Interpolate(gridpos[6], gridpos[7], gridval[6], gridval[7], IsoLevel, VertList[6]);
	if (edgeTable[cubeindex] & 128)      
		OR_Vector3D::Interpolate(gridpos[7], gridpos[4], gridval[7], gridval[4], IsoLevel, VertList[7]);
	if (edgeTable[cubeindex] & 256)      
		OR_Vector3D::Interpolate(gridpos[0], gridpos[4], gridval[0], gridval[4], IsoLevel, VertList[8]);
	if (edgeTable[cubeindex] & 512)   
		OR_Vector3D::Interpolate(gridpos[1], gridpos[5], gridval[1], gridval[5], IsoLevel, VertList[9]);
	if (edgeTable[cubeindex] & 1024) 
		OR_Vector3D::Interpolate(gridpos[2], gridpos[6], gridval[2], gridval[6], IsoLevel, VertList[10]);
	if (edgeTable[cubeindex] & 2048) 
		OR_Vector3D::Interpolate(gridpos[3], gridpos[7], gridval[3], gridval[7], IsoLevel, VertList[11]);

	/* Create the triangles */
	for (i=0; triTable[cubeindex][i]!=-1; i+=3) 
	{
		Triangles[ntriang].Vert[0] = &VertList[triTable[cubeindex][i ]];
		Triangles[ntriang].Num[0]  = triTable[cubeindex][i ]; 
		Triangles[ntriang].Vert[1] = &VertList[triTable[cubeindex][i+1]];
		Triangles[ntriang].Num[1]  = triTable[cubeindex][i+1 ]; 
		Triangles[ntriang].Vert[2] = &VertList[triTable[cubeindex][i+2]];
		Triangles[ntriang].Num[2]  = triTable[cubeindex][i+2 ]; 
		ntriang++;   
	}   
	return ntriang;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IsoSurface::RenderCell
 *
 *	Flush to screen the faces of the surface in a given cell of the grid.
 *
 *  \author Gabriel Peyré 2002/04/15
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE 
void OR_IsoSurface::RenderCell(OR_I32 x, OR_I32 y, OR_I32 z)
{
	/* normal to a face */
	const OR_Float *pos;
	OR_I32 nbfces = Polygonize(x, y, z);
	OR_Vector3D Normal;

	for(OR_I32 fce=0; fce<nbfces; fce++)
	{	
		for(OR_I32 i=2; i>=0; i--)
		{
			pos = Triangles[fce].Vert[i]->GetCoord();
			
			/* compute the normal using the gradient */
			switch ( Triangles[fce].Num[i] )
			{
			case 0:
				Grid_.CalcNormalX(x, y, z, IsoLevel, Normal);
				break;
			case 1:
				Grid_.CalcNormalZ(x+1, y, z, IsoLevel, Normal);
				break;
			case 2:
				Grid_.CalcNormalX(x, y, z+1, IsoLevel, Normal);
				break;
			case 3:
				Grid_.CalcNormalZ(x, y, z, IsoLevel, Normal);
				break;
			case 4:
				Grid_.CalcNormalX(x, y+1, z, IsoLevel, Normal);
				break;
			case 5:
				Grid_.CalcNormalZ(x+1, y+1, z, IsoLevel, Normal);
				break;
			case 6:
				Grid_.CalcNormalX(x, y+1, z+1, IsoLevel, Normal);
				break;
			case 7:
				Grid_.CalcNormalZ(x, y+1, z, IsoLevel, Normal);
				break;
			case 8:
				Grid_.CalcNormalY(x, y, z, IsoLevel, Normal);
				break;
			case 9:
				Grid_.CalcNormalY(x+1, y, z, IsoLevel, Normal);
				break;
			case 10:
				Grid_.CalcNormalY(x+1, y, z+1, IsoLevel, Normal);
				break;
			case 11:
				Grid_.CalcNormalY(x, y, z+1, IsoLevel, Normal);
				break;
			}

			Normal = -Normal;
			/* give the vertex to OpenGL */	;
			glNormal3fv( Normal.GetCoord() );
			glVertex3fv( pos );
		}
	}
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaGrid& OR_IsoSurface::SetIsoLevel
 *
 *  \author Gabriel Peyré 2002/04/15
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_IsoSurface::SetIsoLevel(OR_Float val)
{
	IsoLevel=val;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaGrid& OR_IsoSurface::GetIsoLevel
 *
 *  \author Gabriel Peyré 2002/04/15
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_IsoSurface::GetIsoLevel() const
{
	return IsoLevel;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaGrid& OR_IsoSurface::GetGrid()
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	return the grid used to store values.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_MetaGrid& OR_IsoSurface::GetGrid()
{
	return Grid_;
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

