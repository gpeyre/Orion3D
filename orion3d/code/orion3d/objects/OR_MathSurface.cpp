/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MathSurface.cpp
 *  \brief Definition of class \c OR_MathSurface
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MathSurface.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_MathSurface.h"

#ifndef OR_USE_INLINE
	    #include "OR_MathSurface.inl"
#endif

using namespace OR;





/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface constructor
 *
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_MathSurface::OR_MathSurface()
:	OR_Object(),
	OR_Shadable(),
	pCallbackFunc_	( NULL ),
	pUserParam_		( NULL ),
	nUPrecision_	( 20 ),
	nVPrecision_	( 20 ),
	rUMin_			( 0 ),
	rVMin_			( 0 ),
	rUMax_			( 1 ),
	rVMax_			( 1 ),
	bNeedsUpdate_	( true ),
	norm1			( NULL ),
	norm2			( NULL ),
	vert1			( NULL ),
	vert2			( NULL )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface destructor
 *
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_MathSurface::~OR_MathSurface()
{
	OR_DELETEARRAY(norm1);
	OR_DELETEARRAY(norm2);
	OR_DELETEARRAY(vert1);
	OR_DELETEARRAY(vert2);
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::GetType
 *
 *  \return the type of \c OR_Object
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
OR_Elements OR_MathSurface::GetType()
{
	return OR_MATH_SURFACE;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::Draw
 *
 *  \return draw the object.
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/
void OR_MathSurface::Draw()
{
	OR_ASSERT( pShader_!=NULL );

	if( !this->IsActive() || !OR_Globals::GetDrawObject(OR_MESH) )
		return;
	
	if ( !pShader_->NeedsSorting() )
	{
		glPushMatrix();
		
		/* positionate the object in world frame */
		OR_Maths::MultiplyCurrentModelView( AbsoluteMatrix );
		
#ifdef OR_DRAW_OBJECT_AXES
		OR_DrawLocalAxis();
#endif /* #ifdef OR_DRAW_OBJECT_AXES */
		
		/* set up the shadable datas : process all faces */
		this->SetFaceToProcess_All();
		/* render the shadable datas */
		pShader_->ProcessShader(*this);
		
		glPopMatrix();
	}
	else
	{
		/** \todo add support of alpha pipeline for Mathsurface */
	}	
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::ProcessAllFaces
 *
 *  \author Gabriel Peyré 2001-11-12
 *
 *	Draw the whole surface.
 *	This is the only rendering mode supported by mathsurfaces.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MathSurface::ProcessAllFaces()
{
	/* we only support "process all mode" */
	OR_ASSERT( this->GetShadableMode()==OR_Shadable::kProcessAll );
	
	/* check if we need to construct new temp arrays */
	if( norm1==NULL )
		this->ResizeTempArrays();

	/* render the surface to screen */
	OR_U32 i, j;
	
	OR_Float u_step=(rUMax_-rUMin_)/nUPrecision_;
	OR_Float v_step=(rVMax_-rVMin_)/nVPrecision_;
	OR_Float u_tex_step=1.0f/nUPrecision_;
	OR_Float v_tex_step=1.0f/nVPrecision_;

	OR_Float u=rUMin_;
	OR_Float v=rVMin_;

	/* compute the first row of values */
	for( i=0; i<nUPrecision_+1; i++ )
	{
		this->ComputeNormal(norm1[i], u,v);
		this->ComputeValue(vert1[i], u,v);
		
		u += u_step;
	}
	
	v+=v_step;
	
	
	for (j=1; j<nVPrecision_+1; j++)
	{
		u=rUMin_;
		
		/* comute the first value of the row */
		this->ComputeNormal(norm2[0], u,v);
		this->ComputeValue(vert2[0], u,v);
		
		glBegin(GL_TRIANGLE_STRIP);
		
		/* give the normal & vertex to OpenGL */
		glTexCoord2f(0, (j-1)*v_tex_step);
		glNormal3fv( norm1[0].GetCoord() );
		glVertex3fv( vert1[0].GetCoord() );

		glTexCoord2f(0, j*v_tex_step);
		glNormal3fv( norm2[0].GetCoord() );
		glVertex3fv( vert2[0].GetCoord() );
		
		u+=u_step;
		
		for (OR_U32 i=1; i<nUPrecision_+1; i++)
		{				
			
			this->ComputeNormal(norm2[i], u,v);
			this->ComputeValue(vert2[i], u,v);
			
			/* give the normal & vertex to OpenGL */
			glTexCoord2f(i*u_tex_step, (j-1)*v_tex_step);
			glNormal3fv( norm1[i].GetCoord() );
			glVertex3fv( vert1[i].GetCoord() );

			glTexCoord2f(i*u_tex_step, j*v_tex_step);
			glNormal3fv( norm2[i].GetCoord() );
			glVertex3fv( vert2[i].GetCoord() );
			
			u+=u_step;
		}
		
		glEnd();
		
		/* swap norm1/norm2 & vert1/vert2 */
		OR_Vector3D *svg = norm1;
		norm1 = norm2;
		norm2 = svg;
		svg = vert1;
		vert1 = vert2;
		vert2 = svg;
		
		v+=v_step;
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::ProcessOneFace
 *
 *  \param  nNumFace The face to render
 *  \author Gabriel Peyré 2001-08-30
 *
 *	NOT SUPPORTED BY MATHSURFACE YET
 */ 
/*------------------------------------------------------------------------------*/
void OR_MathSurface::ProcessOneFace(OR_U32 nNumFace)
{
	OR_ASSERT( false );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::AccessArrays
 *
 *  \param  aVertArray Array of vertex to process. Size 3*nNbrVert.
 *  \param  aNormArray Array of normal to process. Size 3*nNbrVert.
 *  \param  aFaceArray Array of face to process. Size 3*nNbrFace. Index on the 2 previous arrays.
 *  \param  nNbrVert Number of vertex to process.
 *  \param  nNbrFace Number of faces to process.
 *  \author Gabriel Peyré 2001-08-30
 *
 *	NOT SUPPORTED BY MATHSURFACE YET
 */ 
/*------------------------------------------------------------------------------*/
void OR_MathSurface::AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCoordArray, OR_U32* &aFaceArray,
						    OR_U32& nNbrVert, OR_U32& nNbrFace )
{
	OR_ASSERT( false );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::BuildFromFile
 *
 *  \param  file the target file.
 *  \author Gabriel Peyré 2001-11-12
 *
 *	Note that the callback function is not exprted, so you'll need to reset it by your
 *	own !
 */ 
/*------------------------------------------------------------------------------*/
void OR_MathSurface::BuildFromFile(OR_File& file)
{
	/* load the basic OR_Object datas */
	OR_Object::BuildFromFile(file);

	/** get the shader */
	OR_String shader_name;
	file >> shader_name;
	OR_Shader* pRetrievedShader = OR_Globals::ShaderManager()->GetShaderByName( shader_name ); 
	if( pRetrievedShader==NULL )
	{
		/* the shader couldn't be retrieved, use default one */
		pRetrievedShader = OR_Globals::GetDefaultShader();
	}
	this->SetShader(pRetrievedShader);
	
	/* load the surface specific informations */
	file	>> nUPrecision_
			>> nVPrecision_
			>> rUMin_
			>> rVMin_
			>> rUMax_
			>> rVMax_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MathSurface::BuildToFile
 *
 *  \param  file the target file.
 *  \author Gabriel Peyré 2001-11-12
 *
 *	Note that the callback function is not exprted, so you'll need to reset it by your
 *	own !
 */ 
/*------------------------------------------------------------------------------*/
void OR_MathSurface::BuildToFile(OR_File& file)
{
	/* save the basic OR_Object datas */
	OR_Object::BuildToFile(file);

	/** if there is a shader, save it's name */
	if( this->GetShader()!=NULL )
	{
		file << this->GetShader()->GetName();
	}
	else
	{
		OR_Globals::MessageHandler()->Warning( "OR_MathSurface::BuildToFile", "Surface has no shader. Using default one." );
		file << OR_Globals::GetDefaultShader()->GetName();
	}

	/* save the surface specific informations */
	file	<< nUPrecision_
			<< nVPrecision_
			<< rUMin_
			<< rVMin_
			<< rUMax_
			<< rVMax_;
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

