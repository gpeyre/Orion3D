/*----------------------------------------------------------------------------*/
/*                         OR_Plane.h                                         */
/*----------------------------------------------------------------------------*/
/* a 3d plane                                                                 */
/*----------------------------------------------------------------------------*/


/** \file 
	This file contains the definition of a simple 3D plane, with primitives
	for ray casting.
	\author Gabriel.
*/

#ifndef _OR_PLANE_H_
#define _OR_PLANE_H_

#include "../configuration/OR_Config.h"
#include "OR_Maths.h"

namespace OR
{
	
/*--------------------------------------------------------------*/
/*                   class OR_Plane                             */
/*--------------------------------------------------------------*/
/* A simple 3D plane.                                           */
/*--------------------------------------------------------------*/

/*! \ingroup group_primitive
 *  \brief class OR_Plane in group group primitive
 */

/// A simple 3D plane.
/** 
	A lot of operator have been defined to make common maths operations, 
	so use them !
*/

/****************************************************************************
 * WARNING: Don't Modify this without consulting OR_BSP::Load()!!           *
 * the endian conversion algorithms depend on this!							*
 ****************************************************************************/
class OR_Plane
{
public:

	OR_Vector3D		N;//normale
	OR_Float		d;//distance

	OR_Bool operator==(OR_Plane P);
	OR_Vector3D FindIntersection(OR_Vector3D P1,OR_Vector3D P2);
	OR_Vector3D FindIntersection(OR_Vector3D P1,OR_Vector3D P2,OR_Float Rayon);
};

/*--------------------------------------------------------------*/
/*                   class OR_Face                              */
/*--------------------------------------------------------------*/
/* A simple face.                                               */
/*--------------------------------------------------------------*/

/*! \ingroup group_primitive
 *  \brief class OR_Face in group group primitive
 */

/// A simple face.
/** 
	Functions have been written to make ray-casting.
	\author Antoche
*/

typedef class OR_Face
{
public:
	OR_I32			T;			//ID Texture
	OR_Plane	Plan;		//Plan associ»
	GLint		Indices[3];	//Indices
	OR_Vector3D	Points[3];	//Points
	OR_Vector3D	Normales[3];//Normales
	OR_Vector3D	TexCoord[3];//TexCoords

	OR_Face();
	void	Set(char *Tex, GLuint *Pts);
	void	Draw();
	OR_Position Classify(OR_Plane* P);
	OR_Float	FindInter(OR_Vector3D P1,OR_Vector3D P2);
	OR_Float	FindInter(OR_Vector3D P1,OR_Vector3D P2,OR_Float Rayon);
}OR_Face;

/**
	\class OR_SingleFace
	\todo Add comment
*/
class	OR_SingleFace
{
	OR_U32		V[3];
	OR_U32		TexId;

public:
	OR_SingleFace()				 {}
	OR_SingleFace(OR_U32 *Struct) {Init(Struct);}
	OR_SingleFace(OR_U32 *Points,OR_U32 Tex) {Init(Points,Tex);}
	OR_SingleFace(OR_U32 P1,OR_U32 P2,OR_U32 P3,OR_U32 Tex) {Init(P1,P2,P3,Tex);}


	void	Init(OR_U32* Struct) {memcpy(V,Struct,4*sizeof(OR_U32));}
	void	Init(OR_U32* Points,OR_U32 Tex) {memcpy(V,Points,3*sizeof(OR_U32));TexId=Tex;}
	void	Init(OR_U32 P1,OR_U32 P2,OR_U32 P3,OR_U32 Tex) {V[0]=P1;V[1]=P2;V[2]=P3;TexId=Tex;}
	OR_U32&	operator[](OR_U32 i) {return V[i];}
	OR_U32&	Id() {return TexId;}
};



} // namespace OR

#endif /* #ifndef _OR_PLANE_H_ */

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