/*--------------------------------------------------------------------------*/
/*                                OR_MetaManager.cpp                        */
/*--------------------------------------------------------------------------*/
/*                Implementation of class OR_MetaManager                    */
/*--------------------------------------------------------------------------*/

#include "../stdafx.h"
#include "OR_MetaManager.h"

namespace OR
{
	
/*----------------------------------------------------------------------*/
/*                       class OR_MetaEnv								*/
/*----------------------------------------------------------------------*/
/*            a class to manage different Meta-Object					*/
/*----------------------------------------------------------------------*/
/*	inherit from class OR_ManagerMap_Template & class OR_Object			*/
/*----------------------------------------------------------------------*/

OR_MetaEnv::OR_MetaEnv()
:OR_ManagerMap_Template<class OR_Gizmo>()
{
	this->Enable();
	/* default values */
	Precision[X]=Precision[Y]=Precision[Z]=20;
	NeedsUpdate=true;
	/* initialize the grid */
	Grid=new OR_Float[Precision[X]*Precision[Y]*Precision[Z]];
	/* create an iso-surface to render the meta-balls */
	OR_Float size[3]={1,1,1};
	MySurface=new OR_IsoSurface(Grid, Precision, size, 0.9f);
	/* initializes shader */
	MyShader=NULL;
	SuportGizmo=NULL;
}

OR_MetaEnv::~OR_MetaEnv()
{
	OR_DELETEARRAY(Grid);
}

void OR_MetaEnv::InitGrid()
{
	OR_DELETEARRAY(Grid);
	Grid=new OR_Float[Precision[X]*Precision[Y]*Precision[Z]];
	MySurface->SetGrid(Grid);
}

/* to handle the meta-obj list *****************************************************/
OR_I32 OR_MetaEnv::AddMetaObject(OR_Gizmo* gizmo)
{	
	/* the scene needs to be re-computed */
	NeedsUpdate=true;
	/* add the metaball to the manager */
	return AddElement(gizmo);
}

OR_I32 OR_MetaEnv::DeleteMetaObject(OR_I32 numero)
{
	NeedsUpdate=true;
	return DeleteElement(numero);
}

OR_I32 OR_MetaEnv::DeleteMetaObject()
{
	NeedsUpdate=true;
	return DeleteElement();
}

/* set/get functions ****************************************************************/
void OR_MetaEnv::SetShader(OR_Shader* shader)
{
	MyShader=shader;
}

OR_Shader* OR_MetaEnv::GetShader()
{
	return MyShader;
}

void OR_MetaEnv::SetSupportGizmo(OR_CubeGizmo* support)
{
	SuportGizmo=support;
	/* set the size of the grid */
	MySurface->SetSize(support->GetDim().GetCoord());
}

OR_CubeGizmo* OR_MetaEnv::GetSupportGizmo()
{
	return SuportGizmo;
}
	
/* set up surface parameters *******************************************************/
void OR_MetaEnv::SetIsoLevel(OR_Float level)
{
	MySurface->SetIsoLevel(level);
	NeedsUpdate=true;
}
OR_Float OR_MetaEnv::GetIsoLevel()
{
	return MySurface->GetIsoLevel();
}

void OR_MetaEnv::SetPrecision(OR_I32 precision[3])
{
	Precision[X]=precision[X];
	Precision[Y]=precision[Y];
	Precision[Z]=precision[Z];
	MySurface->SetGridSize(precision);
	InitGrid();
	NeedsUpdate=true;
}

/* draw and update functions *****************************************/
void OR_MetaEnv::UpdateGizmo(OR_Gizmo *gizmo)
{
	/* compute the value to add to the cell */
	OR_Vector3D pos, pos_init;
	OR_Vector3D Size=SuportGizmo->GetDim()*2;
	OR_Vector3D GizmoPos=SuportGizmo->GetAbsolutePosition();
	/* position of the ball in local coords */
	OR_Vector3D MetaPos=~(*SuportGizmo->GetAbsoluteMatrix()) * gizmo->GetAbsolutePosition();

	OR_Float InfluenceRadius=gizmo->GetInfluenceRadius();

	/* compute from where to where update the grid */
	OR_I32 start[3], end[3];
	for (OR_I32 i=0; i<3; i++)
	{
		start[i]=(OR_I32) (  ((OR_Float)Precision[i])/2 + (MetaPos[i]-InfluenceRadius)*((OR_Float)Precision[i])/Size[i]  );
		if (start[i]<0) start[i]=0;
		if (start[i]>Precision[i]) start[i]=Precision[i];
		end[i]=(OR_I32) (  ((OR_Float)Precision[i])/2 + (MetaPos[i]+InfluenceRadius)*((OR_Float)Precision[i])/Size[i]  );
		if (end[i]<0) end[i]=0;
		if (end[i]>Precision[i]) end[i]=Precision[i];
	}

	pos_init[X]=(-1-Precision[X]/2+start[X])*Size[X]/Precision[X];
	pos_init[Y]=(-1-Precision[Y]/2+start[Y])*Size[Y]/Precision[Y];
	pos_init[Z]=(-1-Precision[Z]/2+start[Z])*Size[Z]/Precision[Z];
	/* translate in absolute coords */
	pos_init+=SuportGizmo->GetAbsolutePosition();
	/* for incremental computation of pos */
	OR_Float incx=Size[X]/Precision[X];
	OR_Float incy=Size[Y]/Precision[Y];
	OR_Float incz=Size[Z]/Precision[Z];	

	pos[X]=pos_init[X];
	for(OR_I32 x=start[X]; x<end[X]; x++)
	{
		pos[Y]=pos_init[Y];
		pos[X]+=incx;
		for(OR_I32 y=start[Y]; y<end[Y]; y++)
		{
			pos[Z]=pos_init[Z];
			pos[Y]+=incy;
			for(OR_I32 z=start[Z]; z<end[Z]; z++)
			{
				pos[Z]+=incz;
				/* the magic formula to store the metaball !! */
				Grid[x+Precision[X]*y+Precision[X]*Precision[Y]*z] +=
							gizmo->MetaCellValue(pos);
			}
		}
	}
}

void OR_MetaEnv::Update()
{
	/* TODO : utiliser un memset ? */
	for(OR_I32 x=0; x<Precision[X]; x++)
	for(OR_I32 y=0; y<Precision[Y]; y++)
	for(OR_I32 z=0; z<Precision[Z]; z++)
	{
		/* initialize the value of the cell*/
		Grid[x + y*Precision[X] + z*Precision[X]*Precision[Y]]=0;
	}

	/* iterate on the manger to update the cells */
	for(IT_ManagerMap_Template(OR_Gizmo) it=begin(); it!=end(); ++it)
	{
		UpdateGizmo((*it).second);
	}
}

void OR_MetaEnv::Draw()
{
	if( this->IsActive() ) 
	{
	glPushMatrix();

		#ifdef OR_DEBUG_META_ENV
			/* draw the computed points in the grid */
			DebugDraw();
		#endif /* #ifdef OR_DEBUG_META_ENV */

		OR_Maths::MultiplyCurrentModelView( SuportGizmo->GetAbsoluteMatrix() );

		do
		{
			MyShader->InializeRenderingContext();
			
			/* draw the meta balls */
			MySurface->Render(NeedsUpdate);
			NeedsUpdate=false;
			
			MyShader->ResetRenderingContext();
		}
		while (MyShader->NeedsAnotherPass());
	
		NeedsUpdate=false;
	glPopMatrix();
	}
}

void OR_MetaEnv::DebugDrawGizmo(OR_Gizmo *gizmo)
{
	/* compute the value to add to the cell */
	OR_Vector3D pos, pos_init;
	OR_Vector3D Size=SuportGizmo->GetDim()*2;
	OR_Vector3D GizmoPos=SuportGizmo->GetAbsolutePosition();
	/* position of the ball in local coords */
	OR_Vector3D MetaPos=~(*SuportGizmo->GetAbsoluteMatrix()) * gizmo->GetAbsolutePosition();

	OR_Float InfluenceRadius=gizmo->GetInfluenceRadius();

	/* compute from where to where update the grid */
	OR_I32 start[3], end[3];
	for (OR_I32 i=0; i<3; i++)
	{
		start[i]=(OR_I32) (  ((OR_Float)Precision[i])/2 + (MetaPos[i]-InfluenceRadius)*((OR_Float)Precision[i])/Size[i]  );
		if (start[i]<0) start[i]=0;
		if (start[i]>Precision[i]) start[i]=Precision[i];
		end[i]=(OR_I32) (  ((OR_Float)Precision[i])/2 + (MetaPos[i]+InfluenceRadius)*((OR_Float)Precision[i])/Size[i]  );
		if (end[i]<0) end[i]=0;
		if (end[i]>Precision[i]) end[i]=Precision[i];
	}

	pos_init[X]=(-1-Precision[X]/2+start[X])*Size[X]/Precision[X];
	pos_init[Y]=(-1-Precision[Y]/2+start[Y])*Size[Y]/Precision[Y];
	pos_init[Z]=(-1-Precision[Z]/2+start[Z])*Size[Z]/Precision[Z];
	/* translate in absolute coords */
	pos_init+=SuportGizmo->GetAbsolutePosition();
	/* for incremental computation of pos */
	OR_Float incx=Size[X]/Precision[X];
	OR_Float incy=Size[Y]/Precision[Y];
	OR_Float incz=Size[Z]/Precision[Z];	

	pos[X]=pos_init[X];

	OR_Globals::Context()->SimpleDrawMode();
	OR_Globals::Context()->SetColor(1, 1, 1);
	OR_Globals::Context()->SetPointSize(3);
		
	glPushMatrix();
//	OR_Maths::MultiplyCurrentModelView( gizmo->GetAbsoluteMatrix() );
	glBegin(GL_POINTS);
		for(OR_I32 x=start[X]; x<end[X]; x++)
		{
			pos[Y]=pos_init[Y];
			pos[X]+=incx;
			for(OR_I32 y=start[Y]; y<end[Y]; y++)
			{
				pos[Z]=pos_init[Z];
				pos[Y]+=incy;
				for(OR_I32 z=start[Z]; z<end[Z]; z++)
				{
					pos[Z]+=incz;
					//OR_Vector3D v;
					//MySurface->EvalPos(x, y, z, &v);
					/* display a point */
					glVertex3fv(pos.GetCoord());
				}
			}
		}
	glEnd();
	glPopMatrix();

	OR_Globals::Context()->SetDefaultColor();
	OR_Globals::Context()->SetDefaultPointSize();
	OR_Globals::Context()->NormalDrawMode();

}

void OR_MetaEnv::DebugDraw()
{
	for(IT_ManagerMap_Template(OR_Gizmo) it=MyMap_.begin(); it!=MyMap_.end(); ++it)
	{
		DebugDrawGizmo((*it).second);
	}
}

/*----------------------------------------------------------------------*/
/*                       class OR_MetaManager							*/
/*----------------------------------------------------------------------*/
/*            a class to manage different Meta-Environnemen				*/
/*----------------------------------------------------------------------*/
/*				inherit from class OR_ManagerMap_Template   			*/
/*----------------------------------------------------------------------*/

/* creation methods ****************************************************************/
OR_I32 OR_MetaManager::AddMetaEnv()
{
	OR_MetaEnv* new_metaenv=new OR_MetaEnv();
	return AddElement(new_metaenv);
}

OR_I32 OR_MetaManager::AddMetaObject(OR_Gizmo* gizmo)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->AddMetaObject(gizmo);
}

OR_I32 OR_MetaManager::GetNbMetaObject()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->GetNbElements();
}

/* to set up the selected meta-env **************************************************/
OR_I32 OR_MetaManager::SetPrecision(OR_I32 precision[3])
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetPrecision(precision);
	return OR_OK;
}

OR_I32 OR_MetaManager::DeleteMetaObject(OR_I32 numero)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->DeleteElement(numero);
}

OR_I32 OR_MetaManager::DeleteMetaObject()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->DeleteElement();
}

OR_I32 OR_MetaManager::SelectMetaBall(OR_I32 num)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->Select(num);
}

OR_I32 OR_MetaManager::GetNumMetaBallSelected()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->GetNumElementSelected();
}

OR_I32 OR_MetaManager::SetShader(OR_Shader* shader)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetShader(shader);
	return OR_OK;
}

OR_I32 OR_MetaManager::SetIsoLevel(OR_Float val)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetIsoLevel(val);
	return OR_OK;
}

OR_I32 OR_MetaManager::SetSupportGizmo(OR_CubeGizmo* support)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetSupportGizmo(support);
	return OR_OK;
}


/* update & draw functions *****************************************************************/
void OR_MetaManager::Update()
{
	for( T_ManagerIterator )
	Iterator(Update_Iterator);
}

void OR_MetaManager::Draw()
{
	Iterator(Draw_Iterator);
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