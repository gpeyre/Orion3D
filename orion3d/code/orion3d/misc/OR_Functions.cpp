/*--------------------------------------------------------------------------*/
/*                                OR_Functions.cpp                          */
/*--------------------------------------------------------------------------*/
/* defines misc usefull functions                                           */
/*--------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Functions.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Functions.h"

namespace OR
{
	
/*--------------------------------------------------------------------------*/
/*              a coolll function to draw local axis                        */
/*--------------------------------------------------------------------------*/

void OR_DrawLocalAxis()
{
#ifdef OR_DRAW_OBJECT_AXES
	if( OR_Globals::GetDrawObject(OR_LOCAL_AXES) )
	{
		OR_Globals::Context()->SetCullingMode(OR_Culling_None);
		OR_Globals::Context()->SimpleDrawMode();
		/* draw the axes of the object */
		glBegin(GL_LINES);
			OR_Globals::Context()->SetColor(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			OR_Globals::Context()->SetColor(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);
			OR_Globals::Context()->SetColor(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);
		glEnd();
		glPushMatrix();
			glTranslatef(0.8f, 0, 0);
			glRotatef(90, 0, 1, 0);
			OR_Globals::Context()->SetColor(1, 0, 0);
			OR_Globals::Data()->SolidCone(0.1f, 0.2f, 12, 1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 0.8f, 0);
			glRotatef(-90, 1, 0, 0);
			OR_Globals::Context()->SetColor(0, 1, 0);
			OR_Globals::Data()->SolidCone(0.1f, 0.2f, 12, 1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 0, 0.8f);
			OR_Globals::Context()->SetColor(0, 0, 1);
			OR_Globals::Data()->SolidCone(0.1f, 0.2f, 12, 1);
		glPopMatrix();

		OR_Globals::Context()->SetDefaultColor();
		OR_Globals::Context()->NormalDrawMode();
		OR_Globals::Context()->SetDefaultCullingMode();
	}
#endif /* OR_DRAW_OBJECT_AXES */
}

/*-------------------------------------------------------------------------*/
/* get the time since the begining of the program, in mili-second          */
/*-------------------------------------------------------------------------*/

OR_I64 ORION3D_API OR_GetTime()
{
#ifdef _UNIX_
	long long tsc;
	
	gettsc(&tsc);
	return (OR_I64) gettsctime(tsc);
#else 
    /* 
     * windows or mac -- note that i have defined a macro for the mac to
     * take care of this, and it's conveniently named timeGetTime ;-)
     */
	return (OR_I64) timeGetTime();
#endif	/* #ifdef _UNIX_ */
}

/*--------------------------------------------------------------------*/
/* primitive pour la manipulation des matrices textures/modelview     */
/*--------------------------------------------------------------------*/

void OR_UnRotateTextureMatrix()
{
	OR_Float matrix[4][4], inv_matrix[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0][0]);
	/* invert the matrix */
		
	inv_matrix[0][0]=matrix[0][0];
	inv_matrix[0][1]=matrix[1][0];
	inv_matrix[0][2]=matrix[2][0];
	inv_matrix[0][3]=0;
	inv_matrix[1][0]=matrix[0][1];
	inv_matrix[1][1]=matrix[1][1];
	inv_matrix[1][2]=matrix[2][1];
	inv_matrix[1][3]=0;
	inv_matrix[2][0]=matrix[0][2];
	inv_matrix[2][1]=matrix[1][2];
	inv_matrix[2][2]=matrix[2][2];
	inv_matrix[2][3]=0;
	inv_matrix[3][0]=0;
	inv_matrix[3][1]=0;
	inv_matrix[3][2]=0;
	inv_matrix[3][3]=0;		
			
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	/* invert the rotations */
	glLoadMatrixf(&inv_matrix[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void ReRotateTextureMatrix()
{
	/* reset the texture matrix */
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void UnRotateModelViewMatrix()
{
	OR_Float matrix[4][4];
	/* unrotate the matrix */
	glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0][0]);
	matrix[0][0]=matrix[1][1]=matrix[2][2]=1;
	matrix[0][1]=matrix[0][2]=0;
	matrix[1][0]=matrix[1][2]=0;
	matrix[2][0]=matrix[2][1]=0;
	glLoadMatrixf(&matrix[0][0]);
}

/*-------------------------------------------------------------------------*/
/* orion3d type manipulations                                              */
/*-------------------------------------------------------------------------*/
/** get the global type of the objets. 
	for exemple, OR_Light_TargetSpot --> OR_Light */
OR_Elements GetGlobalType(OR_Elements e)
{
	switch (e)
	{
	case OR_LIGHT:
	case OR_LIGHT_Target_Spot: 
	case OR_LIGHT_Free_Spot:
	case OR_LIGHT_Target_Direct: 
	case OR_LIGHT_Free_Direct:
		return OR_LIGHT;
		break;
	case OR_CAMERA: 
	case OR_CAMERA_Free: 
	case OR_CAMERA_Target:
		return OR_CAMERA;
		break;
	case OR_SHADER:
	case OR_SHADER_Flat:
	case OR_SHADER_SingleTextureMap: 
	case OR_SHADER_Reflexive:
	case OR_SHADER_Cartoon: 
	case OR_SHADER_Billboard:
	case OR_SHADER_Bump_Emboss: 
		return OR_SHADER;
		break;
	case OR_GIZMO: 
	case OR_GIZMO_Sphere: 
	case OR_GIZMO_Cube: 
	case OR_GIZMO_Cylinder:
	case OR_GIZMO_Square: 
	case OR_GIZMO_Vector: 
	case OR_GIZMO_Point:
		return OR_GIZMO;
		break;	
	default:
		return e;
		break;
	}
}

/*-------------------------------------------------------------------------*/
/*                  string manipulation functions                          */
/*-------------------------------------------------------------------------*/

char* OR_FloatToString(OR_Float f)
{
#ifdef _WIN32_
	OR_I32 dec, sign;
	char *c=_ecvt(f, 6, (int*) &dec, (int*) &sign );

	char* d=_strdup(c);
	d[dec]='.';
	d[dec+1]=NULL;
	strcat(d, &c[dec]);
	return d;
#else
	char c[100]="Not yet implemented under unix/mac";
	return c;
#endif
}

void ORION3D_API OR_PrintFromFile(char *adresse, char* title)
{
#ifdef _WIN32_
	FILE* file;
	if ((file=fopen(adresse, "rt"))!=NULL)
	{
		char c[5000];
		char message[10000]="";
		while (!feof(file))
		{
			fgets(c, 200, file);
			if (c[0]!='#') strcat(message, c);
		}
		MessageBox(0, message, title, MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		OR_Globals::MessageHandler()->Debug("PrintHelp", 
						"Could not find text file '%s'.", adresse);
	}
#else
	FILE* file;
	if ((file=fopen("adresse", "rt"))!=NULL)
	{
		char c[1000];
		while (!feof(file))
		{
			fgets(c, 200, file);
			if (c[0]!='#') fprintf(stderr, "%s", c);
		}
	}
	else
	{
		OR_Globals::MessageHandler()->Debug("PrintHelp", 
						"Could not find text file");
	}
#endif
}



} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////