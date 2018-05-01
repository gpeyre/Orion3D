/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaMesh.cpp
 *  \brief Implementation of class \c OR_MetaMesh
 *  \author Gabriel Peyré 2002/04/15
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MetaMesh.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_MetaMesh.h"
#include "OR_MetaGrid.h"

#ifndef OR_USE_INLINE
	#include "OR_MetaMesh.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaMesh::OR_MetaMesh( OR_Mesh* pMesh )
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	constructor.
 */ 
/*------------------------------------------------------------------------------*/
OR_MetaMesh::OR_MetaMesh( OR_Mesh* pMesh )
:	OR_MetaObject_ABC	(),
	bSystemNeedsUpdate_	( true ),
	rInfluenceRadius_	( 1 )
{
	if( pMesh!=NULL )
		this->SetMesh( *pMesh );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaMesh::~OR_MetaMesh()
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	destructor.
 */ 
/*------------------------------------------------------------------------------*/
OR_MetaMesh::~OR_MetaMesh()
{
	if( pMesh_!=NULL )
	{
		pMesh_->ReleaseIt();
		if( pMesh_->NoLongerUsed() )
			OR_DELETE( pMesh_ );
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaMesh::SetMesh( OR_Mesh& mesh )
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	the mesh
 */ 
/*------------------------------------------------------------------------------*/
void OR_MetaMesh::SetMesh( OR_Mesh& mesh )
{
	pMesh_ = &mesh;
	pMesh_->UseIt();
	/* resize the arrays */
	Coef_.Reset( pMesh_->GetNbVertex() );
	CoefSystem_.Reset( pMesh_->GetNbVertex(), pMesh_->GetNbVertex() );
	Rhs_.Reset( pMesh_->GetNbVertex() );
	/* set the right hand side */
	Rhs_.SetValue( 1 );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaMesh::AddMetaValue(OR_MetaGrid& grid)
 *
 *  \author Gabriel Peyré 2002/04/15
 *
 *	First, we compute the coefficient of each radial function.
 *  Then, we add the corresponding meta-values to the grid.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MetaMesh::AddMetaValue(OR_MetaGrid& grid)
{
	OR_ASSERT( pMesh_!=NULL );
	OR_Vector3D pos_i, pos_j;
	OR_U32 i, j;
	OR_Float* aVertArray = pMesh_->GetVertsArray();
	OR_Matrix4x4& AbsMatrix = pMesh_->GetAbsoluteMatrix();

	/* build the system if needed */
	if( bSystemNeedsUpdate_ )
	{
		for( i=0; i<CoefSystem_.GetNbrRows(); i++ )
		{
			/* compute the position of vertex i */
			pos_i.SetCoord( aVertArray + 3*i );
			pos_i = AbsMatrix*pos_i;
			for( j=0; j<CoefSystem_.GetNbrCols(); j++ )
			{
				/* compute the position of vertex j */
				pos_j.SetCoord( aVertArray + 3*j );
				pos_j = AbsMatrix*pos_j;
				CoefSystem_.SetData(i,j, pMetaFunc_( ~(pos_i - pos_j)/rInfluenceRadius_ ) );
			}
		}

		OR_Float err = 1000;
		OR_U32 nNbrIter = 0;
		while( err>OR_EPSILON && nNbrIter<20 )
		{
			nNbrIter++;
			CoefSystem_.GaussSeidelStep( Coef_, Rhs_ );
			err = (CoefSystem_*Coef_ - Rhs_).NormInf();
			if( err>1000 )
			{
				OR_Globals::MessageHandler()->Warning("OR_MetaMesh::AddMetaValue", "System is ill conditionned.");
				break;
			}
		}
			
		bSystemNeedsUpdate_ = false;
	}

	OR_Vector3D GizmoPos = pMesh_->GetAbsolutePosition();
	OR_Vector3D pos;

	OR_Float rVal = 0;
	/* add each radial function to the grid */
	for( i=0; i<CoefSystem_.GetNbrRows(); ++i )
	{
		pos_i.SetCoord( pMesh_->GetVertsArray() + 3*i );
		pos_i = pMesh_->GetAbsoluteMatrix()*pos_i;

		/* compute a bounding box for the function */

		/* add the values to the grid */
		for( OR_U32 x=0; x<grid.GetGridSizeX(); ++x )
		for( OR_U32 y=0; y<grid.GetGridSizeY(); ++y )
		for( OR_U32 z=0; z<grid.GetGridSizeZ(); ++z )
		{
			grid.ComputePosition(x,y,z, pos);
			OR_Float r = (pos - pos_i).SquareNorm();
			if( r<=rInfluenceRadius_*rInfluenceRadius_ )
			{
				r = OR_Maths::sqrt(r);
				rVal = Coef_.GetData(i)*pMetaFunc_( r/rInfluenceRadius_ );
				grid.AddData(x,y,z, rVal );
			}	
		}
	}
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

