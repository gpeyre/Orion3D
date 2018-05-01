/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaEnv.h
 *  \brief Contains the implementation of a meta-env
 *  \author Gabriel Peyré 2001-07-15
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MetaEnv.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_MetaEnv.h"


#ifndef OR_USE_INLINE
	#include "OR_MetaEnv.inl"
#endif

namespace OR
{
	
/*----------------------------------------------------------------------*/
/*                       class OR_MetaEnv								*/
/*----------------------------------------------------------------------*/
/*            a class to manage different Meta-Object					*/
/*----------------------------------------------------------------------*/

OR_MetaEnv::OR_MetaEnv()
:	OR_ManagerMap_Template<OR_MetaObject_ABC>(),
	OR_SpecialEffect(),
	OR_Shadable(),
	bNeedUpdate_	( true ),
	bNeedRedraw_	( true ),
	pShader_		( NULL )
{
	/* NOTHING */
}

OR_MetaEnv::~OR_MetaEnv()
{
	/* NOTHING */
}


/* set/get functions ****************************************************************/
void OR_MetaEnv::SetShader(OR_Shader& shader)
{
	pShader_ = &shader;
}

OR_Shader* OR_MetaEnv::GetShader()
{
	return pShader_;
}

void OR_MetaEnv::SetSupportGizmo(OR_CubeGizmo& support)
{
	IsoSurface_.GetGrid().SetSupportGizmo(support);
}


/* draw and update functions *****************************************/
void OR_MetaEnv::Update()
{
	if( bNeedUpdate_ )
	{
		/* initialize the value of the cell*/
		IsoSurface_.GetGrid().SetZero();

		/* iterate on the manger to update the cells */
		for(IT_ManagerMap_Template(OR_MetaObject_ABC) it=begin(); it!=end(); ++it)
		{
			OR_MetaObject_ABC* pObj = (*it).second;
				pObj->AddMetaValue( IsoSurface_.GetGrid() );
		}

		bNeedUpdate_ = false;
	}
}

void OR_MetaEnv::Draw()
{
	OR_ASSERT( pShader_!=NULL );
	/** \todo Turn it into an OR_Shadable */
	if( this->IsActive() ) 
	{
	glPushMatrix();

		OR_Maths::MultiplyCurrentModelView( IsoSurface_.GetGrid().GetSupportGizmo()->GetAbsoluteMatrix() );
		pShader_->ProcessShader(*this);		

		bNeedRedraw_ = false;

	glPopMatrix();
	}
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaEnv::ProcessAllFaces
 *
 *  \author Gabriel Peyré 2001-08-30
 *
 *	\important OR_MetaEnv does not support partial flush of vertex.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MetaEnv::ProcessAllFaces()
{
	OR_ASSERT( this->GetShadableMode()==OR_Shadable::kProcessAll  );
	/* draw the meta balls */
	IsoSurface_.Render( bNeedRedraw_ );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaEnv::ProcessOneFace
 *
 *  \param  nNumFace The face to render
 *  \author Gabriel Peyré 2001-08-30
 *
 *	\important OR_MetaEnv does not support per-vertex rendering.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MetaEnv::ProcessOneFace(OR_U32 nNumFace)
{
	OR_ASSERT( false );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shadable::AccessArrays
 *
 *  \param  aVertArray Array of vertex to process. Size 3*nNbrVert.
 *  \param  aNormArray Array of normal to process. Size 3*nNbrVert.
 *  \param  aFaceArray Array of face to process. Size 3*nNbrFace. Index on the 2 previous arrays.
 *  \param  nNbrVert Number of vertex to process.
 *  \param  nNbrFace Number of faces to process.
 *  \author Gabriel Peyré 2001-08-30
 *
 *	\important OR_MetaEnv does not support direct access to vertex.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MetaEnv::AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCoordArray, OR_U32* &aFaceArray,
						   	   OR_U32& nNbrVert, OR_U32& nNbrFace )
{
	OR_ASSERT( false );
	aVertArray     = NULL;
	aNormArray     = NULL;
	aFaceArray     = NULL;
	aTexCoordArray = NULL;
	nNbrVert   = -1;
	nNbrFace   = -1;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IsoSurface& OR_MetaEnv::GetIsoSurface()
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	The surface used to render to screen the meta-env.
 */ 
/*------------------------------------------------------------------------------*/
OR_IsoSurface& OR_MetaEnv::GetIsoSurface()
{
	return IsoSurface_;
}


/*------------------------------------------------------------------------------*/
// Name : OR_MetaEnv::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MetaEnv::BuildFromFile( OR_File& file )
{
	/** \todo implement this */
}



/*------------------------------------------------------------------------------*/
// Name : OR_MetaEnv::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MetaEnv::BuildToFile( OR_File& file )
{
	/** \todo implement this */
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