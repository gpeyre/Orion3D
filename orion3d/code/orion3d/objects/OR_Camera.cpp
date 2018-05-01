/*---------------------------------------------------------------------*/
/*                             OR_Camera.cpp                           */
/*---------------------------------------------------------------------*/
/*            implementation de la classe OR_Camera                    */            
/*---------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Camera.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Camera.h"

using namespace OR;
	
/*----------------------------------------------------------------------*/
/*                               class OR_Camera                        */
/*----------------------------------------------------------------------*/
/* super class for all Camera class                                     */           
/*----------------------------------------------------------------------*/
/* inherit from class OR_Object                                         */        
/*----------------------------------------------------------------------*/

OR_Camera::OR_Camera()
:	OR_Object()
{
	IsOrtho = false;
	Near=0.5f;
	Far=20000;
	Fovy=60;
	Aspect=1.5f;
}

OR_Vector3D OR_Camera::GetCamAxe(OR_Coord_XYZW axe)
{
	return OR_Vector3D(AbsoluteMatrix[axe]);
}

void OR_Camera::SetFovy(OR_Float val)
{
	Fovy=val;
}

void OR_Camera::SetFar(OR_Float val)
{
	Far=val;
}

void OR_Camera::SetNear(OR_Float val)
{
	Near=val;
}

void OR_Camera::SetAspect(OR_Float aspect)
{
	Aspect=aspect;
}

void OR_Camera::SetOrtho(OR_Bool ortho)
{
	IsOrtho=ortho;
}

OR_Bool OR_Camera::GetOrtho()
{
	return IsOrtho;
}

OR_Float OR_Camera::GetFovy()
{
	return Fovy;
}


OR_Float OR_Camera::GetNear()
{
	return Near;
}

OR_Float OR_Camera::GetFar()
{
	return Far;
}

OR_Float OR_Camera::GetAspect()
{
	return Aspect;
}

void OR_Camera::SetProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (IsOrtho)
		glOrtho(-Fovy/2.,Fovy/2.,-Fovy/Aspect/2.,Fovy/Aspect/2.,Near,Far);
	else
		gluPerspective(Fovy, Aspect, Near, Far);
	glMatrixMode(GL_MODELVIEW);
}

void OR_Camera::Put()
{
	OR_Maths::SetCurrentModelView( ~AbsoluteMatrix );
}

/* serialization methods ***************************************/
void OR_Camera::BuildFromFile( OR_File& file )
{
	/* load the basic OR_Object datas */
	OR_Object::BuildFromFile(file);
	/* load the mesh specific datas */
	file >> Near
		 >> Far
		 >> Fovy
		 >> Aspect
		 >> IsOrtho;
	
	/* add itself to the manager */
	OR_Globals::CameraManager()->AddElement( this );
}

void OR_Camera::BuildToFile( OR_File& file )
{
	/* save the basic OR_Object datas */
	OR_Object::BuildToFile(file);
	/* save the mesh specific datas */
	file << Near
		 << Far
		 << Fovy
		 << Aspect
		 << IsOrtho; 
}

/*----------------------------------------------------------------------*/
/*                   class OR_Camera_Free                               */
/*----------------------------------------------------------------------*/
/* a camera given by its position and a vector                          */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Camera                                         */
/*----------------------------------------------------------------------*/

OR_Camera_Free::OR_Camera_Free()
:	OR_Camera()
{

}

void OR_Camera_Free::Rotate(OR_Coord_XYZW axe, OR_Float angle)
{
	Matrix.Rotate(axe, angle);
}

void OR_Camera_Free::RotateWorld(OR_Coord_XYZW axe, OR_Float angle)
{
	Matrix.RotateAbs(axe, angle);
}

void OR_Camera_Free::Translate(OR_Coord_XYZW axe, OR_Float val)
{
	Matrix.Translate(Matrix[axe]*val);
}

void OR_Camera_Free::Translate(OR_Vector3D vect)
{
	Matrix.Translate(Matrix[X]*vect[X]+Matrix[Y]*vect[Y]+Matrix[Z]*vect[Z]);
}

void OR_Camera_Free::TranslateWorld(OR_Coord_XYZW axe, OR_Float val)
{
	Matrix.Translate(axe, val);
}

void OR_Camera_Free::TranslateWorld(OR_Vector3D vect)
{
	Matrix+=vect;
}

void OR_Camera_Free::Draw()
{
#ifdef OR_DRAW_CAMERAS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_CAMERA) && !IsOrtho ) 
	{
	glPushMatrix();
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();	

		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(0.8f, 0.8f, 1);
		
		OR_Float h=(OR_Float)(Far*tan(Fovy*OR_PI/360));
		OR_Float w=h*Aspect;
	
		/* draw the field of view */
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(w, h, -Far);
			glVertex3f(0,0,0);
			glVertex3f(w, -h, -Far);
			glVertex3f(0,0,0);
			glVertex3f(-w, -h, -Far);
			glVertex3f(0,0,0);
			glVertex3f(-w, h, -Far);
			glVertex3f(0,0,0);
			glVertex3f(0, 0, -Far);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex3f(w, h, -Far);
			glVertex3f(w, -h, -Far);
			glVertex3f(-w, -h, -Far);
			glVertex3f(-w, h, -Far);
			glVertex3f(w, h, -Far);
		glEnd();
		OR_Float fact=Near/Far;
		glBegin(GL_LINE_STRIP);
			glVertex3f(w*fact, h*fact, -Near);
			glVertex3f(w*fact, -h*fact, -Near);
			glVertex3f(-w*fact, -h*fact, -Near);
			glVertex3f(-w*fact, h*fact, -Near);
			glVertex3f(w*fact, h*fact, -Near);
		glEnd();

		glTranslatef(0,0,-Far);
		OR_Globals::Data()->SolidSphere(0.2f, 12, 8);

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif /* #ifdef OR_DRAW_CAMERA */
}

/*----------------------------------------------------------------------*/
/*                   class OR_Camera_Target                             */
/*----------------------------------------------------------------------*/
/* a camera given by its position and a target                          */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Camera                                         */
/*----------------------------------------------------------------------*/

OR_Camera_Target::OR_Camera_Target()
:	OR_Camera()
{
	Target=(OR_Object*) OR_Globals::GetHierarchyRoot();
	Roll=0;
	OldRoll=Roll;
	DistanceMin=0;

	RecomputeBasis=true;
}

void OR_Camera_Target::Posit(OR_Vector3D pos)
{
	Matrix.SetTranslation(pos);

	RecomputeBasis=true;
}

void OR_Camera_Target::SetDistanceMin(OR_Float val)
{
	DistanceMin=val;
}

void OR_Camera_Target::Rotate(OR_Coord_XYZW axe, OR_Float a)
{
	OR_Float d;
	OR_Vector3D t;
	switch (axe)
	{
	case Y:
		d=~(GetAbsolutePosition()-Target->GetAbsolutePosition());
		t=( Matrix.GetZ()*(cos(a)-1) + Matrix.GetX()*sin(a) )*d;
		Matrix.Translate( t );		
		Matrix.Rotate(axe, -a);
		break;		
	case X:
		d=~(GetAbsolutePosition()-Target->GetAbsolutePosition());
		t=( Matrix.GetZ()*(cos(a)-1) - Matrix.GetY()*sin(a) )*d;
		Matrix.Translate( t );
		Matrix.Rotate(axe, a);
		break;
	case Z:
		Roll+=a;
		Matrix.RotateZ(a);
		break;		
	default:
		break;
	};
}

void OR_Camera_Target::Translate(OR_Coord_XYZW axe, OR_Float val)
{
	Matrix.Translate(Matrix[axe]*val);
}

void OR_Camera_Target::Translate(OR_Vector3D vect)
{
	Matrix.Translate(Matrix[X]*vect[X]+Matrix[Y]*vect[Y]+Matrix[Z]*vect[Z]);	
}

void OR_Camera_Target::TranslateWorld(OR_Coord_XYZW axe, OR_Float val)
{
	Matrix.Translate(axe, val);
}

void OR_Camera_Target::TranslateWorld(OR_Vector3D vect)
{
	Matrix.Translate(vect);
}

void OR_Camera_Target::Update()
{
	OR_ASSERT(Target!=NULL);
	/* compute the relative matrix. position is, ok, compute axis */
	OR_Vector3D axe=Matrix.GetTranslation() - Target->GetAbsolutePosition();
	axe.Normalize();
	Matrix.SetZ( axe );
	Matrix.SetX( !(Matrix.GetY()^axe) );
	Matrix.SetY( axe^Matrix.GetX() );
	/* compute absolute matrix */
	OR_Maths::MultiplyCurrentModelView( Matrix );
	OR_Maths::MultiplyCurrentModelView( AnimationMatrix );
	OR_Maths::GetCurrentModelView( AbsoluteMatrix );
	
#ifdef OR_DRAW_Trajectories
	/* todo : see if we can skip that */
	OldAnimationMatrix=AnimationMatrix;
#endif

	AnimationMatrix.LoadIdentity();
}

void OR_Camera_Target::Draw()
{
#ifdef OR_DRAW_CAMERAS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_CAMERA) ) 
	{
	glPushMatrix();
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(0.8f, 0.8f, 1);

		OR_Float h=(OR_Float)(Far*tan(Fovy*OR_PI/360));
		OR_Float w=h*Aspect;

		/* draw the line between camera and target */
		glBegin(GL_LINES);
			glVertex3fv(GetAbsolutePosition().GetCoord());
			glVertex3fv(Target->GetAbsolutePosition().GetCoord());
		glEnd();


		
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();	

		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(0.8f, 0.8f, 1);

		/* draw the field of view */
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(w, h, -Far);
			glVertex3f(0,0,0);
			glVertex3f(w, -h, -Far);
			glVertex3f(0,0,0);
			glVertex3f(-w, -h, -Far);
			glVertex3f(0,0,0);
			glVertex3f(-w, h, -Far);
		glEnd();
		glBegin(GL_LINE_STRIP);
			glVertex3f(w, h, -Far);
			glVertex3f(w, -h, -Far);
			glVertex3f(-w, -h, -Far);
			glVertex3f(-w, h, -Far);
			glVertex3f(w, h, -Far);
		glEnd();
		OR_Float fact=Near/Far;
		glBegin(GL_LINE_STRIP);
			glVertex3f(w*fact, h*fact, -Near);
			glVertex3f(w*fact, -h*fact, -Near);
			glVertex3f(-w*fact, -h*fact, -Near);
			glVertex3f(-w*fact, h*fact, -Near);
			glVertex3f(w*fact, h*fact, -Near);
		glEnd();

		glTranslatef(0,0,-Far);
		OR_Globals::Data()->SolidSphere(0.2f, 12, 8);

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif /* #ifdef OR_DRAW_CAMERA */
}

/* serialization methods ***************************************/
void OR_Camera_Target::BuildFromFile( OR_File& file )
{
	/* load the basic OR_Camera datas */
	OR_Camera::BuildFromFile(file);
	/* load the OR_Camera_Target specific datas */
	file >> Roll
		 >> DistanceMin;
}

void OR_Camera_Target::BuildToFile( OR_File& file )
{
	/* save the basic OR_Camera datas */
	OR_Camera::BuildToFile(file);
	/* save the OR_Camera_Target specific datas */
	file << Roll
		 << DistanceMin;
}


/*----------------------------------------------------------------------*/
/*                      classe OR_CameraManager	                        */
/*----------------------------------------------------------------------*/
/* to store the differents cameras                                      */            
/*----------------------------------------------------------------------*/
/*	inherit from class OR_ManagerMap_Template                           */
/*----------------------------------------------------------------------*/

OR_I32 OR_CameraManager::AddFreeCamera()
{
	OR_Camera_Free* new_cam=new OR_Camera_Free();
	return AddElement(new_cam);
}

OR_I32 OR_CameraManager::AddTargetCamera()
{
	OR_Camera_Target* new_cam=new OR_Camera_Target();
	return AddElement(new_cam);
}

OR_I32 OR_CameraManager::Posit(OR_Vector3D pos)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->Posit(pos);
	return OR_OK;
}

OR_I32 OR_CameraManager::Rotate(OR_Coord_XYZW axe, OR_Float angle)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetType())
	{
	case OR_CAMERA_Free:
		((OR_Camera_Free*) GetElementSelected())->Rotate(axe, angle);
		break;
	case OR_CAMERA_Target:
		((OR_Camera_Target*) GetElementSelected())->Rotate(axe, angle);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	};
	return OR_OK;
}

OR_I32 OR_CameraManager::RotateWorld(OR_Coord_XYZW axe, OR_Float angle)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetType())
	{
	case OR_CAMERA_Free:
		((OR_Camera_Free*) GetElementSelected())->RotateWorld(axe, angle);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	};
	return OR_OK;
}

OR_I32 OR_CameraManager::Translate(OR_Coord_XYZW axe, OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetType())
	{
	case OR_CAMERA_Free:
		((OR_Camera_Free*) GetElementSelected())->Translate(axe, val);
		break;
	case OR_CAMERA_Target:
		((OR_Camera_Target*) GetElementSelected())->Translate(axe, val);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	};
	return OR_OK;
}

OR_I32 OR_CameraManager::Translate(OR_Vector3D vect)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetType())
	{
	case OR_CAMERA_Free:
		((OR_Camera_Free*) GetElementSelected())->Translate(vect);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	};
	return OR_OK;
}

OR_I32 OR_CameraManager::TranslateWorld(OR_Coord_XYZW axe, OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetType())
	{
	case OR_CAMERA_Free:
		((OR_Camera_Free*) GetElementSelected())->TranslateWorld(axe, val);
		break;
	case OR_CAMERA_Target:
		((OR_Camera_Target*) GetElementSelected())->TranslateWorld(axe, val);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	};
	return OR_OK;
}

OR_I32 OR_CameraManager::TranslateWorld(OR_Vector3D vect)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetType())
	{
	case OR_CAMERA_Free:
		((OR_Camera_Free*) GetElementSelected())->TranslateWorld(vect);
		break;
	case OR_CAMERA_Target:
		((OR_Camera_Target*) GetElementSelected())->TranslateWorld(vect);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	};
	return OR_OK;
}

/* enable/disable methods ************************************/
OR_I32 OR_CameraManager::Enable()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->Enable();
	return OR_OK;
}

OR_I32 OR_CameraManager::Disable()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->Disable();
	return OR_OK;
}

OR_Bool OR_CameraManager::Toggle()
{
	if (IsSelectedEmpty()) return false;
	return GetElementSelected()->Toggle();
}

OR_I32 OR_CameraManager::SetTarget(OR_Object* target)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetType())
	{
	case OR_CAMERA_Target:
		((OR_Camera_Target*) GetElementSelected())->SetTarget(target);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	};
	return OR_OK;
}

OR_I32 OR_CameraManager::SetDistanceMin(OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetType())
	{
	case OR_CAMERA_Target:
		((OR_Camera_Target*) GetElementSelected())->SetDistanceMin(val);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	};
	return OR_OK;
}

OR_Vector3D OR_CameraManager::GetPosition()
{
	if( IsSelectedEmpty() ) 
		return OR_Vector3D();
	return GetElementSelected()->GetAbsolutePosition();
}

OR_Vector3D OR_CameraManager::GetCamAxe(OR_Coord_XYZW axe)
{
	if( IsSelectedEmpty() ) 
		return OR_Vector3D();
	return GetElementSelected()->GetCamAxe(axe);
}

OR_I32 OR_CameraManager::SetFovy(OR_Float val)
{
	if( IsSelectedEmpty() ) 
		return OR_Manager_SelectedEmpty;
	this->GetElementSelected()->SetFovy(val);
	return OR_OK;
}

OR_I32 OR_CameraManager::SetFar(OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetFar(val);
	return OR_OK;
}

OR_I32 OR_CameraManager::SetNear(OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetNear(val);
	return OR_OK;
}

OR_Float OR_CameraManager::GetFovy()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->GetFovy();
}

OR_Float OR_CameraManager::GetNear()
{	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->GetNear();

}

OR_Float OR_CameraManager::GetFar()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->GetFar();
}

OR_Float OR_CameraManager::GetAspect()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->GetAspect();
}

OR_I32 OR_CameraManager::PutSelectedCamera()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->Put();
	return OR_OK;
}




///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////