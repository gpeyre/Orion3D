/*----------------------------------------------------------------------*/
/*                                OR_Light.cpp                          */
/*----------------------------------------------------------------------*/
/* implementations of light class                                       */
/*----------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Light.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Light.h"
#include "OR_LightManager.h"

#ifndef OR_USE_INLINE
#   include "OR_Light.inl"
#endif

namespace OR
{
	
/*----------------------------------------------------------------------*/
/*                                classe OR_Light                       */
/*----------------------------------------------------------------------*/
/* super class for all Light class                                      */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Object                                         */
/*----------------------------------------------------------------------*/

OR_Light::OR_Light()
:	OR_Object	( ),
	nLightID_	( 0 )
{
	Ambient[R]=Ambient[V]=Ambient[B]=0.7f;
	Diffuse[R]=Diffuse[V]=Diffuse[B]=0.7f;
	Specular[R]=Specular[V]=Specular[B]=0.7f;
	Ambient[A]=Diffuse[A]=Specular[A]=1;
	
	this->AssignLightID();
}


/*------------------------------------------------------------------------------
 * Name : OR_Light constructor
 *
 *  \param  Dup EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-24
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_Light::OR_Light( const OR_Light& Dup )
:	OR_Object	( Dup ),
	nLightID_	( 0 ),
	Ambient		( Dup.Ambient ),
	Diffuse		( Dup.Diffuse ),
	Specular	( Dup.Specular )
{
	this->AssignLightID();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Light destructor
 *
 *  \author Gabriel Peyré 2001-09-24
 *
 *	Remove its Id from the stack.
 */ 
/*------------------------------------------------------------------------------*/
OR_Light::~OR_Light()
{
	Disable();
	OR_LightManager::GetLightIDStack().ReleaseID( this->GetLightID() );
}


void OR_Light::SetAmbient(OR_Float val[4])
{
	Ambient[R]=val[R];
	Ambient[V]=val[V];
	Ambient[B]=val[B];
	Ambient[A]=val[A];
	SetColors();
}

void OR_Light::SetSpecular(OR_Float val[4])
{
	Specular[R]=val[R];
	Specular[V]=val[V];
	Specular[B]=val[B];
	Specular[A]=val[A];
	SetColors();
}

void OR_Light::SetDiffuse(OR_Float val[4])
{
	Diffuse[R]=val[R];
	Diffuse[V]=val[V];
	Diffuse[B]=val[B];
	Diffuse[A]=val[A];
	SetColors();
}

void OR_Light::SetAmbient(OR_Coord_RVBA c, OR_Float val)
{
	Ambient[c]=val;
	SetColors();
}

void OR_Light::SetSpecular(OR_Coord_RVBA c, OR_Float val)
{
	Specular[c]=val;
	SetColors();
}

void OR_Light::SetDiffuse(OR_Coord_RVBA c, OR_Float val)
{
	Diffuse[c]=val;
	SetColors();
}

OR_Bool OR_Light::Enable()
{
	glEnable(nLightID_);
	return OR_Object::Enable();
}

OR_Bool OR_Light::Disable()
{
	glDisable(nLightID_);
	return OR_Object::Disable();
}

OR_Bool OR_Light::Toggle()
{
	OR_Bool bTmp = OR_Object::Toggle();

	if( this->IsActive() ) 
		glEnable(nLightID_);
	else 
		glDisable(nLightID_);

	return bTmp;
}

void OR_Light::SetProperties( )
{
	SetColors( );
}


void OR_Light::SetColors()
{
	glLightfv(nLightID_, GL_AMBIENT, Ambient.GetCoord());
	glLightfv(nLightID_, GL_DIFFUSE, Diffuse.GetCoord());
	glLightfv(nLightID_, GL_SPECULAR, Specular.GetCoord());
	if( this->IsActive() ) 
		glEnable(nLightID_);
	else 
		glDisable(nLightID_);
}


/* serialization methods ***************************************/
void OR_Light::BuildFromFile( OR_File& file )
{
	/* load the basic OR_Object datas */
	OR_Object::BuildFromFile(file);
	/* load the light specific datas */
	file >> Ambient
		 >> Diffuse
		 >> Specular;
	SetColors();

	/* add itself to the manager */
	OR_Globals::LightManager()->AddElement( this );
}

void OR_Light::BuildToFile( OR_File& file )
{
	/* save the basic OR_Object datas */
	OR_Object::BuildToFile(file);
	/* save the mesh specific datas */
	file << Ambient
		 << Diffuse
		 << Specular; 
}


/*----------------------------------------------------------------------*/
/*                    classe OR_Light_Spot                              */
/*----------------------------------------------------------------------*/
/* super class for all spot class [ie. a cone of light]                 */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light                                          */
/*----------------------------------------------------------------------*/

OR_Light_Spot::OR_Light_Spot()
:	OR_Light()
{
	CutOff=180;
	/* constant */
	Atenuation[0]=1;
	/* linear */
	Atenuation[1]=0;
	/* quadratic */
	Atenuation[2]=0;
	/* exponent */
	Exponent=0;
}

void OR_Light_Spot::SetProperties( ) 
{ 
	SetColors( ); 

	glLightf( nLightID_ , GL_SPOT_CUTOFF , CutOff ); 
	glLightf( nLightID_ , GL_SPOT_EXPONENT , Exponent ); 
	glLightf( nLightID_ , GL_CONSTANT_ATTENUATION , Atenuation[0] ); 
	glLightf( nLightID_ , GL_LINEAR_ATTENUATION , Atenuation[1] ); 
	glLightf( nLightID_ , GL_QUADRATIC_ATTENUATION , Atenuation[2] ); 
} 

void OR_Light_Spot::SetCutOff(OR_Float val)
{
	CutOff=val;
	SetProperties();
}

void OR_Light_Spot::SetExponent(OR_Float val)
{
	Exponent=val;
	SetProperties();
}

void OR_Light_Spot::SetAtenuation(OR_Float val[3])
{
	Atenuation[0]=val[0];
	Atenuation[1]=val[1];
	Atenuation[2]=val[2];
	SetProperties();
}

/* serialization methods ***************************************/
void OR_Light_Spot::BuildFromFile( OR_File& file )
{
	/* load the basic OR_Light datas */
	OR_Light::BuildFromFile(file);
	/* load the light spot specific datas */
	file >> CutOff
		 >> Exponent
		 >> Atenuation;
	 SetProperties( );
}

void OR_Light_Spot::BuildToFile( OR_File& file )
{
	/* save the basic OR_Light datas */
	OR_Light::BuildToFile(file);
	/* load the light spot specific datas */
	file << CutOff
		 << Exponent
		 << Atenuation;
}


/*----------------------------------------------------------------------*/
/*                    classe OR_Light_FreeSpot                          */
/*----------------------------------------------------------------------*/
/* a spot [ie. a cone of light] given by its position and a vector      */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light_Spot                                     */
/*----------------------------------------------------------------------*/

OR_Light_FreeSpot::OR_Light_FreeSpot()
:	OR_Light_Spot()
{
	SetProperties();
}



OR_Light_FreeSpot::~OR_Light_FreeSpot()
{
	printf("kk");
}


void OR_Light_FreeSpot::Put()
{
	/* non directionnal light */
	OR_Float pos[4]={0, 0, 0, 1};
	/* pure world Z axis */
	OR_Float zaxe[4]={0, 0, -1, 0};
	
	if( this->IsActive() )
	{
	glPushMatrix();
		/* posit the light */
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		glLightfv(nLightID_, GL_POSITION, pos);
		/* set the direction of the cone */
		glLightfv(nLightID_, GL_SPOT_DIRECTION, zaxe);
	glPopMatrix();
	}
}

void OR_Light_FreeSpot::SetDirection(OR_Vector3D v)
{
	/* re-set the orthogonal matrix */
	Matrix.ReComputeBasis_GivenZ(-v);
}

void OR_Light_FreeSpot::Draw()
{
#ifdef OR_DRAW_LIGHTS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_LIGHT) ) 
	{
	glPushMatrix();
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();	
		
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(Diffuse);

		if (CutOff<180.)
		{
			glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f(0,0,-2);
			glEnd();
			
			glTranslatef(0, 0, -2);
				OR_Globals::Data()->SolidSphere(0.1f, 12, 8);
				OR_Globals::Data()->WireCone(2*tan(CutOff*OR_PI/180), 2, 8, 1);
			glTranslatef(0, 0, 2);
		}
		else
			OR_Globals::Data()->WireSphere(.3f, 12, 8);

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif
}

/*----------------------------------------------------------------------*/
/*                    classe OR_Light_TargetSpot                        */
/*----------------------------------------------------------------------*/
/* a spot [ie. a cone of light] given by its position and a target      */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light_Spot                                     */
/*----------------------------------------------------------------------*/

OR_Light_TargetSpot::OR_Light_TargetSpot()
:	OR_Light_Spot()
{
	SetProperties();
}

void OR_Light_TargetSpot::Put()
{
	/* non directionnal light */
	OR_Float pos[4]={0, 0, 0, 1};
	/* compute the position of the gizmo in local coords */
	/* ????????????? must be re-normalized ?????????? */
	OR_Vector3D axe=!(Target->GetAbsolutePosition() - this->GetAbsolutePosition());
	/* pure vector axe */
	OR_Float zaxe[4];
	zaxe[X]=axe[X];
	zaxe[Y]=axe[Y];
	zaxe[Z]=axe[Z];
	zaxe[W]=0;

	if( this->IsActive() ) 
	{
	glPushMatrix();
		/* set the direction of the cone */
		glLightfv(nLightID_, GL_SPOT_DIRECTION, zaxe);

		/* posit the light */
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		glLightfv(nLightID_, GL_POSITION, pos);
	glPopMatrix();
	}
}

void OR_Light_TargetSpot::Draw()
{
#ifdef OR_DRAW_LIGHTS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_LIGHT) ) 
	{
	glPushMatrix();
		/* draw the line between light and target */
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(Diffuse);

		glBegin(GL_LINES);
			glVertex3fv(GetAbsolutePosition().GetCoord());
			glVertex3fv(Target->GetAbsolutePosition().GetCoord());
		glEnd();

		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();
	
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(Diffuse);

		OR_Float len = fabs(~(Target->GetAbsolutePosition()-GetAbsolutePosition()));
		glTranslatef(0, 0, -len);
			OR_Globals::Data()->WireCone(len*tan(CutOff*OR_PI/180), len, 8, 1);
		glTranslatef(0, 0, len);
		

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif
}

/*----------------------------------------------------------------------*/
/*                    classe OR_Light_Direct                            */
/*----------------------------------------------------------------------*/
/* super class for all direct class [ie. an infinite light]             */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light                                          */
/*----------------------------------------------------------------------*/

OR_Light_Direct::OR_Light_Direct()
:	OR_Light()
{

}


/*----------------------------------------------------------------------*/
/*                    classe OR_Light_FreeDirect                        */
/*----------------------------------------------------------------------*/
/* a direct [ie. an infinite light] given by its position and a vector  */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light_Direct                                   */
/*----------------------------------------------------------------------*/

OR_Light_FreeDirect::OR_Light_FreeDirect()
:	OR_Light_Direct()
{
	SetProperties();
}


void OR_Light_FreeDirect::SetDirection(OR_Vector3D v)
{
	/* re-set the orthogonal matrix */
	Matrix.ReComputeBasis_GivenZ(-v);
}

void OR_Light_FreeDirect::Put()
{
	/* directionnal light */
	OR_Float pos[4]={0, 0, 1, 0};
	if( this->IsActive() ) 
	{
	glPushMatrix();
		/* posit the light */
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		
		glLightfv(nLightID_, GL_POSITION, pos);
	glPopMatrix();
	}
}

void OR_Light_FreeDirect::Draw()
{
#ifdef OR_DRAW_LIGHTS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_LIGHT) ) 
	{
	glPushMatrix();
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();

		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(Diffuse);
	
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,0,-2);
		glEnd();
		
		glTranslatef(0, 0, -2);
			OR_Globals::Data()->SolidSphere(0.1f, 12, 8);
		glTranslatef(0, 0, 1);
			glScalef(1, 1, 2);
			OR_Globals::Data()->WireCube(1);
			glScalef(1, 1, 0.5f);
		glTranslatef(0, 0, 1);

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif
}

/*----------------------------------------------------------------------*/
/*                    classe OR_Light_TargetDirect                      */
/*----------------------------------------------------------------------*/
/* a direct [ie. an infinite light] given by its position and a target  */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light_Direct                                   */
/*----------------------------------------------------------------------*/

OR_Light_TargetDirect::OR_Light_TargetDirect()
:	OR_Light_Direct()
{
	SetProperties();
}

void OR_Light_TargetDirect::Put()
{
	/* directionnal light */
	OR_Vector3D pos=Target->GetAbsolutePosition()-GetAbsolutePosition();
	/* pure vector axe */
	OR_Float zaxe[4];
	zaxe[X]=pos[X];
	zaxe[Y]=pos[Y];
	zaxe[Z]=pos[Z];
	zaxe[X]=0;

	if( this->IsActive() ) 
	{
	glPushMatrix();
		/* posit the light */
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		glLightfv(nLightID_, GL_POSITION, zaxe);
	glPopMatrix();
	}
}


void OR_Light_TargetDirect::Draw()
{
#ifdef OR_DRAW_LIGHTS
	if( this->IsActive() && OR_Globals::GetDrawObject(OR_LIGHT) ) 
	{
	glPushMatrix();
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		OR_DrawLocalAxis();
		
		OR_Globals::Context()->SimpleDrawMode();
		OR_Globals::Context()->SetColor(Diffuse);

		glBegin(GL_LINE);
			glVertex3f(0,0,0);
			glPushMatrix();
				glLoadIdentity();
				glVertex3fv(Target->GetAbsolutePosition().GetCoord());
			glPopMatrix();
		glEnd();

		/* TODO : rotater le cube */
		OR_Float len = fabs(~(Target->GetAbsolutePosition()-GetAbsolutePosition()));
		glTranslatef(0, 0, -len/2.);
		glScalef(1, 1, len);
		OR_Globals::Data()->WireCube(1);
		glScalef(1 , 1 , 1./len);
		glTranslatef(0, 0, len/2.);

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
	glPopMatrix();
	}
#endif
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Light::AssignLightID
 *
 *  \author Gabriel Peyré 2001-09-25
 *
 *	assign a free light Id for the light.
 */ 
/*------------------------------------------------------------------------------*/
OR_U32 OR_Light::AssignLightID()
{
	OR_ASSERT( nLightID_==0 || OR_LightManager::GetLightIDStack().IsAvailable(nLightID_) );
	nLightID_ = OR_LightManager::GetLightIDStack().GetNewID();

	this->SetProperties();

	return nLightID_;
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
