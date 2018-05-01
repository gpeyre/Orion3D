/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_SparseMatrix.inl
 *  \brief Inlined methods for \c OML_SparseMatrix
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_SparseMatrix.h"

namespace OML {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix constructor
 *
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Create a zero sized matrix.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_SparseMatrix::OML_SparseMatrix()
:	nNbrCols_( 0 ),
	nNbrRows_( 0 )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix constructor
 *
 *  \param  nNbrRows number of rows of the matrix.
 *  \param  nNbrCols number of columns of the matrix.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	create a matrix of given size.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_SparseMatrix::OML_SparseMatrix(OML_U32 nNbrRows, OML_U32 nNbrCols)
:	nNbrCols_( nNbrCols ),
	nNbrRows_( nNbrRows )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix constructor
 *
 *  \param  m the original matrix.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	copy constructor.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_SparseMatrix::OML_SparseMatrix(const OML_SparseMatrix& m)
{
	nNbrCols_ = m.GetNbrCols();
	nNbrRows_ = m.GetNbrRows();
	const T_SparseMatrixBlockList& BlockList = m.GetBlockList();

	for( ITconst_SparseMatrixBlockList it=BlockList.begin(); it!=BlockList.end(); ++it )
		BlockList_.push_back( new OML_SparseMatrixBlock( *(*it) ) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix constructor
 *
 *  \param  m the original matrix.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	copy operator.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_SparseMatrix& OML_SparseMatrix::operator=(const OML_SparseMatrix &m)
{
	nNbrCols_ = m.GetNbrCols();
	nNbrRows_ = m.GetNbrRows();
	const T_SparseMatrixBlockList& BlockList = m.GetBlockList();
	for( ITconst_SparseMatrixBlockList it=BlockList.begin(); it!=BlockList.end(); ++it )
		BlockList_.push_back( new OML_SparseMatrixBlock( *(*it) ) );

	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix destructor
 *
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_SparseMatrix::~OML_SparseMatrix()
{
	for( IT_SparseMatrixBlockList it=BlockList_.begin(); it!=BlockList_.end(); ++it )
		OML_DELETE( *it );
	BlockList_.clear();
}

	


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::GetNbrRows
 *
 *  \return The number of row of the matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_U32 OML_SparseMatrix::GetNbrRows() const
{
	return nNbrRows_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::GetNbrCols
 *
 *  \return the number of columns of the matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_U32 OML_SparseMatrix::GetNbrCols() const
{
	return nNbrCols_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::SetDim
 *
 *  \param  nNbrRows The number of row of the matrix.
 *  \param  nNbrCols the number of columns of the matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_SparseMatrix::SetDim(OML_U32 nNbrRows, OML_U32 nNbrCols)
{
	nNbrCols_ = nNbrCols;
	nNbrRows_ = nNbrRows;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::SetNbrRows
 *
 *  \param  nNbrRows The number of rows of the matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_SparseMatrix::SetNbrRows(OML_U32 nNbrRows)
{
	nNbrRows_ = nNbrRows;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::SetNbrCols
 *
 *  \param  nNbrCols the number of columns of the matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_SparseMatrix::SetNbrCols(OML_U32 nNbrCols)
{
	nNbrCols_ = nNbrCols;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::GetBlockList
 *
 *  \return list of the block that compose the matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
const T_SparseMatrixBlockList& OML_SparseMatrix::GetBlockList() const
{
	return BlockList_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::GetBlockList
 *
 *  \return list of the block that compose the matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
T_SparseMatrixBlockList& OML_SparseMatrix::GetBlockList()
{
	return BlockList_;
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::void	
 *
 *  \param  m the matrix that the block will support.
 *	\param nOffsetRow the offset of the block on i
 *	\param nOffsetCol the offset of the block on j
 *  \author Gabriel Peyré 2001-09-30
 *
 * PUT YOUR COMMENTS HERE
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_SparseMatrix::AddBlock(OML_MatrixNxP& m, OML_U32 nOffsetRow, OML_U32 nOffsetCol)
{
	BlockList_.push_back( new OML_SparseMatrixBlock(m, nOffsetRow, nOffsetRow) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::RemoveBlock
 *
 *  \param  m the matrix we want to remove from the sparse matrix.
 *  \author Gabriel Peyré 2001-09-30
 *
 *	Waring : use this mathod if you don't own the matrix.
 *	else directly use the remove method with matrix block.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_Bool OML_SparseMatrix::RemoveBlock(OML_MatrixNxP& m)
{
	for( IT_SparseMatrixBlockList it=BlockList_.begin(); it!=BlockList_.end(); ++it )
	{
		OML_SparseMatrixBlock* pBlock = *it;
		if( &pBlock->GetMatrix()==&m )
		{
			BlockList_.erase( it );
			OML_DELETE( pBlock );
			return true;
		}
	}

	return false;	
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::AddBlock
 *
 *  \param  m the block to add to the matrix.
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Use this method if you are responsible for the block.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_SparseMatrix::AddBlock(OML_SparseMatrixBlock& m)
{
	BlockList_.push_back( &m );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::RemoveBlock
 *
 *  \param  m the block to remove to the matrix.
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Use this method if you are responsible for the block.
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_SparseMatrix::RemoveBlock(OML_SparseMatrixBlock& m)
{
	BlockList_.remove( &m );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrix::GetNbrBlock
 *
 *  \return the number of blocks in the matrix.
 *  \author Gabriel Peyré 2001-11-28
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
OML_U32 OML_SparseMatrix::GetNbrBlock() const
{
	return BlockList_.size();
}


} // End namespace OML

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

