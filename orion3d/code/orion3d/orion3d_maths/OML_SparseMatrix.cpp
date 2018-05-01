/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_SparseMatrix.cpp
 *  \brief Definition of class \c OML_SparseMatrix
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OML_SCCSID
static const char* sccsid = "@(#) OML_SparseMatrix.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OML_SCCSID


#include "stdafx.h"
#include "OML_SparseMatrix.h"

#ifndef OML_USE_INLINE
	#include "OML_SparseMatrix.inl"
#endif

using namespace OML;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::operator
 *
 *  \param  v the vector to multiply with the matrix.
 *  \return the multiplication of the vector by the matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_VectorND OML_SparseMatrix::operator*(const OML_VectorND& v)
{
	OML_VectorND Res( v.GetDim() );
	OML_SparseMatrix::Multiply( *this, v, Res );
	return Res;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::Multiply
 *
 *  \param  a left hand statement
 *  \param  v right hand statement
 *  \param  r result
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Multiply the matrix by the vector.
 */ 
/*------------------------------------------------------------------------------*/
void OML_SparseMatrix::Multiply(const OML_SparseMatrix& a, const OML_VectorND& v, OML_VectorND& r)
{
	OML_ASSERT( a.GetNbrRows()==r.GetDim() );
	OML_ASSERT( a.GetNbrCols()==v.GetDim() );

	/* clear the result */
	r.SetZero();

	OML_Float rVal = 0;

	for( ITconst_SparseMatrixBlockList it=a.GetBlockList().begin(); it!=a.GetBlockList().end(); ++it )
	{
		OML_SparseMatrixBlock* pBlock = *it;
		OML_MatrixNxP& Matrix = pBlock->GetMatrix();
		OML_U32 iOffset = pBlock->GetRowOffset();
		OML_U32 jOffset = pBlock->GetColOffset();
		for( OML_U32 i=0; i<Matrix.GetNbrRows(); ++i )
		{
			rVal = 0;
			for( OML_U32 j=0; j<Matrix.GetNbrCols(); ++j )
				rVal += Matrix.GetData( i, j ) * v.GetData( j+jOffset ); 

			r.SetData( i+iOffset, rVal );
		}
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::MultiplyTranspose
 *
 *  \param  a left hand statement
 *  \param  v right hand statement
 *  \param  r result
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Multiply the \b transpose of the matrix by the vector.
 */ 
/*------------------------------------------------------------------------------*/
void OML_SparseMatrix::MultiplyTranspose(const OML_SparseMatrix& a, const OML_VectorND& v, OML_VectorND& r)
{
	OML_ASSERT( a.GetNbrRows()==v.GetDim() );
	OML_ASSERT( a.GetNbrCols()==r.GetDim() );
	
	/* clear the result */
	r.SetZero();
	
	OML_Float rVal = 0;
	
	for( ITconst_SparseMatrixBlockList it=a.GetBlockList().begin(); it!=a.GetBlockList().end(); ++it )
	{
		OML_SparseMatrixBlock* pBlock = *it;
		OML_MatrixNxP& Matrix = pBlock->GetMatrix();
		OML_U32 iOffset = pBlock->GetRowOffset();
		OML_U32 jOffset = pBlock->GetColOffset();
		for( OML_U32 j=0; j<Matrix.GetNbrCols(); ++j )
		{
			rVal = 0;
			for( OML_U32 i=0; i<Matrix.GetNbrRows(); ++i )
				rVal += Matrix.GetData( i, j ) * v.GetData( i+iOffset ); 
			
			r.SetData( j+jOffset, rVal );
		}
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::SetZero
 *
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Set each block to zero.
 */ 
/*------------------------------------------------------------------------------*/
void OML_SparseMatrix::SetZero()
{
	for( IT_SparseMatrixBlockList it=BlockList_.begin(); it!=BlockList_.end(); ++it )
		(*it)->GetMatrix().SetZero();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::SetValue
 *
 *  \param  rVal the value to assign to the matrix.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Set each block to a given value.
 */ 
/*------------------------------------------------------------------------------*/
void OML_SparseMatrix::SetValue(OML_Float rVal)
{
	for( IT_SparseMatrixBlockList it=BlockList_.begin(); it!=BlockList_.end(); ++it )
		(*it)->GetMatrix().SetValue( rVal );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::Randomize
 *
 *  \param  rMin minimum value
 *  \param  rMax maximum value
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Randomize each block.
 */ 
/*------------------------------------------------------------------------------*/
void OML_SparseMatrix::Randomize(OML_Float rMin, OML_Float rMax)
{
	for( IT_SparseMatrixBlockList it=BlockList_.begin(); it!=BlockList_.end(); ++it )
		(*it)->GetMatrix().Randomize( rMin, rMax );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::Print
 *
 *  \param  cFormat Format of the real number
 *  \param  f file to print to
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Print each block to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OML_SparseMatrix::Print(char *cFormat, FILE *f)
{
	OML_U32 nCpt = 0;
	for( IT_SparseMatrixBlockList it=BlockList_.begin(); it!=BlockList_.end(); ++it )
	{
		fprintf(f, "--- Block %i --- offset i=%i  j=%i ---\n", nCpt, (*it)->GetRowOffset(), (*it)->GetColOffset() );
		(*it)->GetMatrix().Print( cFormat, f );
		nCpt++;
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

