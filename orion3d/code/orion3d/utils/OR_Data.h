/*------------------------------------------------------------------------*/
/*                        OR_Data.h                                       */
/*------------------------------------------------------------------------*/
/* misc data used in Orion3D                                              */
/*------------------------------------------------------------------------*/


/** \file 
	Contains definition of miscanlious datas used in orion3d engine [tiny 3d objects 
	used for debug, defaut datas ...].
	\author Gabriel.
**/


#ifndef _OR_DATA_H_
#define _OR_DATA_H_


#include "../configuration/OR_Config.h"

namespace OR
{

class OR_Mesh;
class OR_Gizmo;
class OR_Shader;
class OR_Object;

/*----------------------------------------------------------------------------*/
/*                            class OR_Data                                   */
/*----------------------------------------------------------------------------*/
/* defines misc datas for Orion3D                                             */
/*----------------------------------------------------------------------------*/

/// defines misc datas for Orion3D .
/** 
	These data are used for initialisation or for debuging.
	\author Gabriel
*/

class ORION3D_API OR_Data
{
private:
	/** a square default shape used to render particules systems */
	OR_Mesh* DefaultParticuleShape;
	/** a default root object for the hierarchy */
	OR_Gizmo* DefaultHierarchyRoot;
	/** defaut shader */
	OR_Shader* DefaultShader;
public:
	/** constructor : initialize the default datas */
	OR_Data();
	/** destructor : free memory */
	~OR_Data();

	/** get the default root node */
	OR_Object* GetDefaultHierarchyRoot();
	/** get the default particule shape */
	OR_Object* GetDefaultParticuleShape();
	/** get the default shader */
	OR_Shader* GetDefaultShader();


	static void WireSphere(OR_Float radius, OR_I32 slices, OR_I32 stacks);
	static void SolidSphere(OR_Float radius, OR_I32 slices, OR_I32 stacks);
	static void WireCone(OR_Float base, OR_Float height, OR_I32 slices, OR_I32 stacks);
	static void SolidCone(OR_Float base, OR_Float height, OR_I32 slices, OR_I32 stacks);
	static void WireCube(OR_Float size);
	static void SolidCube(OR_Float size);
	static void WireTorus(OR_Float innerRadius, OR_Float outerRadius, OR_I32 sides, OR_I32 rings);
	static void SolidTorus(OR_Float innerRadius, OR_Float outerRadius, OR_I32 sides, OR_I32 rings);
	static void WireDodecahedron(void);
	static void SolidDodecahedron(void);
	static void WireTeapot(OR_Float size);
	static void SolidTeapot(OR_Float size);
	static void WireOctahedron(void);
	static void SolidOctahedron(void);
	static void WireTetrahedron(void);
	static void SolidTetrahedron(void);
	static void WireIcosahedron(void);
	static void SolidIcosahedron(void);


	static void WireCylinder(OR_Float rRadiusX, OR_Float rRadiusY, OR_Float rHeight, OR_I32 nSlice);
};


} // namespace OR


#endif

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                           END  OF FILE	                                 //
///////////////////////////////////////////////////////////////////////////////
