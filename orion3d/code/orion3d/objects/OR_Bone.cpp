/*---------------------------------------------------------------------------------------*/
/*                                      OR_Bone.cpp                                      */
/*---------------------------------------------------------------------------------------*/
/* contains the definition of a bone                                                     */
/*---------------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Bone.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Bone.h"

#ifndef OR_USE_INLINE
	#include "OR_Bone.inl"
#endif // OR_USE_INLINE


namespace OR
{
	
/*---------------------------------------------------------------------------------------*/
/*                                 class OR_Bone                                         */
/*---------------------------------------------------------------------------------------*/

#define OR_BONES_WIDTH 0.5f

void OR_Bone::Draw()
{

	if(pSkin_!=NULL)
	{
		/* skin the skin */
	}

#ifdef OR_DRAW_BONES
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_BONE) ) 
	{
		glPushMatrix();
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();
		
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(1, 1, 0);
		
		if(!bIsEndEffector_)
		{
			glBegin(GL_LINES);

			glVertex3f(-OR_BONES_WIDTH, 0, 0);
			glVertex3f(0, -OR_BONES_WIDTH, -OR_BONES_WIDTH);
			glVertex3f(-OR_BONES_WIDTH, 0, 0);
			glVertex3f(0, OR_BONES_WIDTH, -OR_BONES_WIDTH);
			glVertex3f(-OR_BONES_WIDTH, 0, 0);
			glVertex3f(0, -OR_BONES_WIDTH, OR_BONES_WIDTH);
			glVertex3f(-OR_BONES_WIDTH, 0, 0);
			glVertex3f(0, OR_BONES_WIDTH, OR_BONES_WIDTH);

			glVertex3f(rLength_, 0, 0);
			glVertex3f(0, -OR_BONES_WIDTH, -OR_BONES_WIDTH);
			glVertex3f(rLength_, 0, 0);
			glVertex3f(0, OR_BONES_WIDTH, -OR_BONES_WIDTH);
			glVertex3f(rLength_, 0, 0);
			glVertex3f(0, -OR_BONES_WIDTH, OR_BONES_WIDTH);
			glVertex3f(rLength_, 0, 0);
			glVertex3f(0, OR_BONES_WIDTH, OR_BONES_WIDTH);

			glVertex3f(0, -OR_BONES_WIDTH, -OR_BONES_WIDTH);
			glVertex3f(0, OR_BONES_WIDTH, -OR_BONES_WIDTH);
			glVertex3f(0, OR_BONES_WIDTH, -OR_BONES_WIDTH);
			glVertex3f(0, OR_BONES_WIDTH, OR_BONES_WIDTH);
			glVertex3f(0, OR_BONES_WIDTH, OR_BONES_WIDTH);
			glVertex3f(0, -OR_BONES_WIDTH, OR_BONES_WIDTH);
			glVertex3f(0, -OR_BONES_WIDTH, OR_BONES_WIDTH);
			glVertex3f(0, -OR_BONES_WIDTH, -OR_BONES_WIDTH);

			glEnd();
		}
		else
		{
			OR_Globals::Data()->WireSphere(OR_BONES_WIDTH, 12, 8);
		}
		
		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
		glPopMatrix();
	}
#endif

}


void OR_Bone::Update()
{
	/* compute the animation matrix */
	OR_Maths::MultiplyCurrentModelView( Matrix );
	OR_Maths::MultiplyCurrentModelView( AnimationMatrix );
	OR_Maths::GetCurrentModelView( AbsoluteMatrix );

	/* translate in X direction to set up the child matrix */
	glTranslatef(rLength_, 0,0);

	/* reset the animation matrix */
#ifdef OR_DRAW_Trajectories
	/* todo : see if we can skip that */
	OldAnimationMatrix=AnimationMatrix;
#endif
	
	AnimationMatrix.LoadIdentity();
}

void OR_Bone::BuildFromFile( OR_File& file )
{
	/* load the basic OR_Object datas */
	OR_Object::BuildFromFile(file);
	/* load the bone specific datas */
	file >> rLength_
		 >> nSkinId;
}

void OR_Bone::BuildToFile( OR_File& file )
{
	/* save the basic OR_Object datas */
	OR_Object::BuildToFile(file);
	/* save the bone specific datas */
	if(pSkin_!=NULL)
		nSkinId=pSkin_->GetId();
	else
		nSkinId=-1;
	file << rLength_
		 << nSkinId;

	/* add itself to the manager */
	/** \todo use a bone manager */
//	OR_Globals::BoneManager()->AddElement( this );
}

void OR_Bone::PostExportPass()
{
	if( (TargetId>=0) && (TargetId<OR_Globals::GetNbrObjectImported()) )
		this->SetTarget( OR_Globals::GetImportedObject(TargetId) );
	else 
		this->SetTarget(NULL);

	if ((nSkinId>=0) && (nSkinId<OR_Globals::GetNbrObjectImported()))
	{
		OR_Object* pObj = OR_Globals::GetImportedObject(TargetId);
		if( (pObj!=NULL) && (pObj->GetType() == OR_MESH) )
		{
			this->SetSkin((OR_Mesh*) pObj);
		}
		else
		{
			OR_Globals::MessageHandler()->Warning("OR_Bone::PostExportPass", "The skin object is not an OR_Mesh.");
			this->SetSkin(NULL);
		}
	}
	else 
		this->SetSkin(NULL);
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
