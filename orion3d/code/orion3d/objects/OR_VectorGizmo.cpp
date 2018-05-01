/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_VectorGizmo.cpp
 *  \brief Definition of class \c OR_VectorGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_VectorGizmo.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_VectorGizmo.h"

#ifndef OR_USE_INLINE
	    #include "OR_VectorGizmo.inl"
#endif

using namespace OR;


OR_VectorGizmo::OR_VectorGizmo(OR_Vector3D vZ, OR_Float dim)
:	OR_Gizmo()
{
	Dim[Z]=dim;
	Dim[X]=Dim[Y]=0;
	Matrix.ReComputeBasis_GivenZ(vZ);
}

void OR_VectorGizmo::Draw()
{
#ifdef OR_DRAW_GIZMOS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_GIZMO) ) 
	{
	glPushMatrix();
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();

		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(1, 1, 0);

		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, Dim[Z]);
		glEnd();

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_VectorGizmo::InitParticule
 *
 *  \param  particule the particule to initialize
 *  \param  AbsoluteSpeed The speed given in the basis of the object.
 *  \author Gabriel Peyré 2001-07-30
 *
 *	Initialize the position and the speed of the particule.
 */ 
/*------------------------------------------------------------------------------*/
void OR_VectorGizmo::InitParticule(OR_Particule& particule, OR_Vector3D& AbsoluteSpeed)
{
	particule.ReSetPosition( this->GetAbsolutePosition());
	OR_Vector3D speed = AbsoluteMatrix.GetRotation()*AbsoluteSpeed;
	particule.SetSpeed( speed );
}



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

