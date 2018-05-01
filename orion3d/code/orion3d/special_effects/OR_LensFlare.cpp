/*-------------------------------------------------------------------*/
/*                           OR_LensFlare.cpp                        */
/*-------------------------------------------------------------------*/
/* Created : 14 Apr 2001   18h09                                     */
/*-------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_LensFlare.cpp (c) Backchiche 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_LensFlare.h"


namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                   class OR_LensFlare                              */
/*-------------------------------------------------------------------*/
/* super class for all lens flare.                                   */
/*-------------------------------------------------------------------*/


OR_LensFlare::OR_LensFlare()
:	OR_SpecialEffect(),
	OR_Shadable()
{
	MyShader=NULL;
	Size[X]=OR_DEFAULT_LensFlare_Size;
	Size[Y]=OR_DEFAULT_LensFlare_Size;
	Distance=0;
}

void OR_LensFlare::Display(OR_Vector3D v, OR_Float d)
{
	OR_ASSERT(MyShader!=NULL);

	if( this->IsActive() )
	{

		OR_Camera* cam = OR_Globals::CameraManager()->GetActiveCamera();

		/* compute the factor : warning : camera_look=Z<0 */
		OR_Float factor=-v*cam->GetAbsoluteMatrix().GetZ();

		if (factor>OR_EPSILON)
		{
			OR_Float lambda=d/factor;
//			Pos=cam->GetAbsolutePosition()+( (cam->GetAbsoluteMatrix()->GetRotation())*v )*lambda;
			Pos=cam->GetAbsolutePosition() + ((cam->GetAbsoluteMatrix().GetRotation()))*v*lambda;

			OR_Matrix4x4 TempMatrix;
			OR_Maths::GetCurrentModelView( TempMatrix );
			/* give the face to the alpha pipeline  */
			OR_Globals::AlphaPipeline()->AddFace( this, 0, 1, 2, 3*TempMatrix.TransformOnZ(Pos[X], Pos[Y], Pos[Z]) );
		}
	
	}
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Mesh::ProcessAllFaces
 *
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Just flush all face to screen.
 */ 
/*------------------------------------------------------------------------------*/
void OR_LensFlare::ProcessAllFaces()
{
	glPushMatrix();
	glTranslatef(Pos[X], Pos[Y], Pos[Z]);

	OR_Globals::Context()->DisableLighting();
	OR_Globals::Context()->SetColor(MyShader->GetAmbient());
	OR_Globals::Context()->SetBlendingMode(OR_Blending_1_1);
	/* draw the square */
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-Size[X],  -Size[Y], 0);
	glTexCoord2f(1,0);
	glVertex3f(Size[X],  -Size[Y], 0);
	glTexCoord2f(1,1);
	glVertex3f(Size[X],  Size[Y], 0);
	glTexCoord2f(0,1);
	glVertex3f(-Size[X],  Size[Y], 0);
	glEnd();
	OR_Globals::Context()->SetDefaultLightingMode();

	glPopMatrix();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_LensFlare::ProcessOneFace
 *
 *  \param  nNumFace The face to render
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Lensflare doesn't support this feature.
 */ 
/*------------------------------------------------------------------------------*/
void OR_LensFlare::ProcessOneFace(OR_U32 nNumFace)
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_LensFlare::AccessArrays
 *
 *  \param  aVertArray Array of vertex to process. Size 3*nNbrVert.
 *  \param  aNormArray Array of normal to process. Size 3*nNbrVert.
 *  \param  aFaceArray Array of face to process. Size 3*nNbrFace. Index on the 2 previous arrays.
 *  \param  nNbrVert Number of vertex to process.
 *  \param  nNbrFace Number of faces to process.
 *  \author Gabriel Peyré 2001-08-30
 *
 *	Lensflare doesn't support this feature.
 */ 
/*------------------------------------------------------------------------------*/
void OR_LensFlare::AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCoordArray, OR_U32* &aFaceArray,
						    OR_U32& nNbrVert, OR_U32& nNbrFace )
{
	aVertArray     = NULL;
	aNormArray     = NULL;
	aTexCoordArray = NULL;
	aFaceArray     = NULL;
	nNbrVert   = 0;
	nNbrFace   = 0;
}

OR_RETURN_CODE OR_LensFlare::EnableBilboarding()
{
	if (MyShader==NULL) return OR_ERROR;
	if (MyShader->GetType()==OR_SHADER_Billboard) return OR_OK;
	MyShader=new OR_BillboardShader( MyShader );
	return OR_OK;
}

/*------------------------------------------------------------------------------*/
// Name : OR_LensFlare::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_LensFlare::BuildFromFile( OR_File& file )
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------*/
// Name : OR_LensFlare::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_LensFlare::BuildToFile( OR_File& file )
{
}

/*-------------------------------------------------------------------*/
/*                   class OR_LensFlare_Infinite                     */
/*-------------------------------------------------------------------*/
/* an infinite lens flare.                                           */
/*-------------------------------------------------------------------*/

OR_LensFlare_Infinite::OR_LensFlare_Infinite()
:OR_LensFlare()
{
	Direction=OR_Vector3D(0,0,1);
}

void OR_LensFlare_Infinite::Update()
{

}

void OR_LensFlare_Infinite::Draw()
{
	Display(Direction, Distance);
}

/*------------------------------------------------------------------------------*/
// Name : OR_LensFlare_Infinite::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_LensFlare_Infinite::BuildFromFile( OR_File& file )
{
}



/*------------------------------------------------------------------------------*/
// Name : OR_LensFlare_Infinite::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_LensFlare_Infinite::BuildToFile( OR_File& file )
{
}

/*-------------------------------------------------------------------*/
/*                   class OR_LensFlare_Local                        */
/*-------------------------------------------------------------------*/
/* a local lens flare.                                               */
/*-------------------------------------------------------------------*/

OR_LensFlare_Local::OR_LensFlare_Local()
:OR_LensFlare()
{
	Target=NULL;
}

void OR_LensFlare_Local::Update()
{
	OR_ASSERT(Target!=NULL);
}

void OR_LensFlare_Local::Draw()
{
	OR_ASSERT(Target!=NULL);
	OR_Vector3D v = Target->GetAbsolutePosition() - OR_Globals::CameraManager()->GetElementSelected()->GetAbsolutePosition();
	Display(v, Distance*(~v));
}


/*------------------------------------------------------------------------------*/
// Name : OR_LensFlare_Local::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_LensFlare_Local::BuildFromFile( OR_File& file )
{
}



/*------------------------------------------------------------------------------*/
// Name : OR_LensFlare_Local::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_LensFlare_Local::BuildToFile( OR_File& file )
{
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