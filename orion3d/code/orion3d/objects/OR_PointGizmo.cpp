/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PointGizmo.cpp
 *  \brief Definition of class \c OR_PointGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_PointGizmo.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_PointGizmo.h"

#ifndef OR_USE_INLINE
	    #include "OR_PointGizmo.inl"
#endif

using namespace OR;



OR_PointGizmo::OR_PointGizmo()
:	OR_Gizmo()
{
	Dim[X]=Dim[Y]=Dim[Z]=0;
}

void OR_PointGizmo::Draw()
{
#ifdef OR_DRAW_GIZMOS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_GIZMO) ) 
	{
		glPushMatrix();
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(1, 1, 0);
		
		OR_Globals::Data()->WireCube(0.2);
		
		OR_DrawLocalAxis();
		
		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
		glPopMatrix();
	}
#endif
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PointGizmo::InitParticule
 *
 *  \param  particule the particule to initialize
 *  \param  AbsoluteSpeed The speed given in the basis of the object.
 *  \author Gabriel Peyré 2001-07-30
 *
 *	Initialize the position and the speed of the particule.
 */ 
/*------------------------------------------------------------------------------*/
void OR_PointGizmo::InitParticule(OR_Particule& particule, OR_Vector3D& AbsoluteSpeed)
{
	particule.ReSetPosition(GetAbsolutePosition());
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

