/*-------------------------------------------------------------------*/
/*                    OR_BumpShader_Emboss.cpp                       */
/*-------------------------------------------------------------------*/
/* Created : 17 Apr 2001   2h12                                      */
/*-------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_BumpShader_Emboss.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_BumpShader_Emboss.h"

namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                   class OR_BumpShader_Emboss                      */
/*-------------------------------------------------------------------*/
/* an emboss bump map shader.                                        */
/*-------------------------------------------------------------------*/

OR_BumpShader_Emboss::OR_BumpShader_Emboss(char* adresse, OR_Bool ismipmap)
:OR_Shader()
{
	MyTexture=new OR_Texture(false, 0, ismipmap);
	MyLight=NULL;
	if (adresse!=NULL) MyTexture->LoadImage(adresse);
	Offset=OR_DEFAULT_BUMPSHADER_OFFSET;
	if (!IsShaderSupported())
	{
		OR_Globals::MessageHandler()->Warning("OR_BumpShader_Emboss::OR_BumpShader_Emboss", 
								 "Client hardware doesn't support emboss bump mapping.");
	}
}

void OR_BumpShader_Emboss::LoadTexture(char* adresse)
{
	if (adresse!=NULL) MyTexture->LoadImage(adresse);
	/* check if the image have 3 component */
	if (MyTexture->GetComponents() != 4)
	{
		OR_Globals::MessageHandler()->Warning("OR_BumpShader_Emboss::LoadTexture", 
				"The texture %s doesn't have an alpha channel.", adresse);
	}
}

/* to process the pixel shader stage ******************************/
void OR_BumpShader_Emboss::ProcessBump_1Pass(OR_Mesh* object)
{
	OR_Float *VertList=object->GetVertsArray();
	OR_Float *NormList=object->GetNormsArray();
	OR_Float *TCoordList=object->GetTCoordsArray();
	OR_U32 *FaceList=object->GetFaceList();
	OR_U32 NbFaces=object->GetNbFaces();
		
	OR_ASSERT(MyTexture->IsImageLoaded());
	OR_ASSERT(MyLight!=NULL);
	
	/*-------------------------------------------------------
	For this method we will use a texture that has the base
	texture as color RGB channel and the heighmap as an alpha 
	channel.
	Some color degradation is visible. Maybe I'm not doing it
	right. Maybe as color operations are done with imprecise 
	integer color values, so many operations end in loss off
	presicion.
	Also, highlights have less intensity.
	It's a tradeoff for a noticeable increase in speed.
	-------------------------------------------------------*/

	OR_Vector3D texcoord;

	/* set Blend mode */
	OR_Globals::Context()->SetBlendingMode(OR_Blending_SrcA_0);
	
	/* Texture unit 0 ************************************************/
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	MyTexture->Bind();
	
	/* enable conbine mode */
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
	
	/*  set up combine Color Operation: modulate2X */
	glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);
	glTexEnvf (GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 2.0);
	/* Defaults SOURCE<n> and OPERAND<n> are ok for color */

	/*  set up combine Alpha operation : replace */
	glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_REPLACE);
	/* Defaults SOURCE<n> and OPERAND<n> are ok for alpha */

	/* Texture unit 1 ************************************************/
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	MyTexture->Bind();
	
	/* enable conbine mode */
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
	
	/*  set up combine Color Operation: replace1X */
	glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);
	glTexEnvf (GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 1.0);

	/* Use result of previous texture environment as input source */
	glTexEnvf (GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PREVIOUS_EXT);
	
	/* Alpha operation: Add Signed 2X (that's Arg0 + Arg1 - 0.5) */
	glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_ADD_SIGNED_EXT);

	/* Use texture as SOURCE0 */
	glTexEnvf (GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_TEXTURE);
	/* Use (1-alpha) as OPERAND0 */
	glTexEnvf (GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT, GL_ONE_MINUS_SRC_ALPHA);
	/* Use result of previous texture environment as SOURCE1 */
	glTexEnvf (GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, GL_PREVIOUS_EXT);

	/*******************************************************************
	Render the diplay list using : 
		- Normal texcoords for Texture Unit 0.
		- Offsetted for Texture Unit 1.
	********************************************************************/
	/* the number of the current vertex */
	OR_U32 vert;
	/* U and V values of the 3 vertex */
	OR_Float U[3], V[3];
	/* the coords of the deplaeced point on (U,V) */
	OR_Float offset_u=0, offset_v=0;
	/* the coords of the deplaced point in local texcoords */
	OR_Float fx, fy;
	/* the tangent on X and Y */
	OR_Vector3D tangent_x, tangent_y;


	glBegin(GL_TRIANGLES);
	for (OR_U32 i = 0; i < NbFaces; i++)	
	{
		OR_I32 v;
		/* compute the (U,V) of each vertex */
		for (v=0; v<3; v++)
		{
			vert=FaceList[3*i+v];
			U[v]=TCoordList[2*vert];
			V[v]=TCoordList[2*vert+1];
		}
		/* compute the tex coords tangents */
		tangent_x=OR_Vector3D(&VertList[3*FaceList[3*i+2]]) 
					- OR_Vector3D(&VertList[3*FaceList[3*i+1]]);	// v2-v1
		tangent_x.Normalize();	
		tangent_y=OR_Vector3D(&VertList[3*FaceList[3*i]]) 
					- OR_Vector3D(&VertList[3*FaceList[3*i+1]]);	// v0-v1
		tangent_y.Normalize();	

		for (v=0; v<3; v++)
		{
			vert=FaceList[3*i+v];
			/* compute the deplacement vector in world coords */
			texcoord = ~( object->GetAbsoluteMatrix() )*MyLight->GetAbsolutePosition() 
				     - OR_Vector3D(&VertList[8*vert+5]);
			texcoord.Normalize();
			texcoord *= Offset;
			/* compute the deplaced point in texcoords */
			fx=texcoord*tangent_x;
			fy=texcoord*tangent_y;
			/* compute the (U,V) values of the deplaced point */
			offset_u=fx*(U[2] - U[1]) + fy*(U[0] - U[1]);
			offset_u=fx*(V[2] - V[1]) + fy*(V[0] - V[1]);

			glNormal3fv(NormList+3*vert);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, U[v], V[v]);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, U[v] + offset_u, V[v] + offset_v);
			glVertex3fv(VertList+3*vert);
		}
	}
	glEnd();

	/* restore previous states */	
	OR_Globals::Context()->SetDefaultBlendingMode();
	/* disable texture unit 1 */
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB);
}

void OR_BumpShader_Emboss::ProcessBump_Flat(OR_Mesh* object)
{
#if 0
	do
	{
		MyTexture->Bind();
		/* activate mesh's vertex array */
		//glInterleavedArrays(GL_T2F_N3F_V3F, 0, object->GetVertList());
		glVertexPointer(3, GL_FLOAT, 0, object->GetVertsArray());
		glNormalPointer(GL_FLOAT, 0, object->GetNormsArray());
		glTexCoordPointer(2, GL_FLOAT, 0, object->GetTCoordsArray());
		/* dereference the vertices */
		glDrawElements(GL_TRIANGLES, object->GetNbFaces()*3, GL_UNSIGNED_INT, object->GetFaceList());
	}
	while (NeedsAnotherPass());
#endif
}

void OR_BumpShader_Emboss::ProcessShader(OR_Shadable& object)
{
	/** \todo : use the OR_Shadable to render the object */
#if 0
	/* choose the algo according to client hardware */
	if (IsShaderSupported())
	{
		ProcessBump_1Pass(object);
	}
	else
	{
		ProcessBump_Flat(object);
	}
#endif
}

/* serialization methods ***************************************/
void OR_BumpShader_Emboss::BuildFromFile( OR_File& file )
{
	/* load the basic shader datas */
	OR_Shader::BuildFromFile(file);
	/* load the specific datas */
	file >> MyTexture;
	/* \todo : get the light id */
}

void OR_BumpShader_Emboss::BuildToFile( OR_File& file )
{
	/* save the basic shader datas */
	OR_Shader::BuildToFile(file);
	/* save the specific datas */
	if (MyTexture==NULL)
	{
		MyTexture=new OR_Texture;
		OR_Globals::TextureManager()->AddElement(MyTexture);
	}
	file >> MyTexture;
	/* \todo : store the light id */
}


} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_license.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////