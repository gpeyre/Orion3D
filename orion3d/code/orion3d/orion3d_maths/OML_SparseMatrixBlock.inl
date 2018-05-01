/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_SparseMatrixBlock.inl
 *  \brief Inlined methods for \c OML_SparseMatrixBlock
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/
#include "OML_SparseMatrixBlock.h"

namespace OML {

OML_INLINE
OML_SparseMatrixBlock::OML_SparseMatrixBlock(OML_MatrixNxP& m, OML_U32 nRowOffset, OML_U32 nColOffset)
:	pMatrix_	( &m ),
	nRowOffset_	( nRowOffset ),
	nColOffset_	( nColOffset )
{
	/* NOTHING */
}

OML_INLINE
OML_SparseMatrixBlock::OML_SparseMatrixBlock()
:	pMatrix_	( NULL ),
	nRowOffset_	( 0 ),
	nColOffset_	( 0 )
{
	/* NOTHING */
}

OML_INLINE
OML_SparseMatrixBlock::~OML_SparseMatrixBlock()
{
	/* NOTHING */
}

OML_INLINE
OML_SparseMatrixBlock::OML_SparseMatrixBlock(const OML_SparseMatrixBlock& m)
{
	nRowOffset_ = m.GetRowOffset();
	nColOffset_ = m.GetRowOffset();
	pMatrix_    = & m.GetMatrix();
}

OML_INLINE
OML_SparseMatrixBlock& OML_SparseMatrixBlock::operator =(const OML_SparseMatrixBlock &m)
{
	nRowOffset_ = m.GetRowOffset();
	nColOffset_ = m.GetRowOffset();
	pMatrix_    = & m.GetMatrix();
	
	return *this;
}

OML_INLINE
OML_MatrixNxP& OML_SparseMatrixBlock::GetMatrix() const
{
	OML_ASSERT( pMatrix_!=NULL );
	return *pMatrix_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrixBlock::SetMatrix
 *
 *  \param  m The matrix that this block supports.
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_SparseMatrixBlock::SetMatrix(OML_MatrixNxP& m)
{
	pMatrix_ = &m;
}


OML_INLINE
OML_U32 OML_SparseMatrixBlock::GetRowOffset() const
{
	return nRowOffset_;
}

OML_INLINE
OML_U32 OML_SparseMatrixBlock::GetColOffset() const
{
	return nColOffset_;
}

OML_INLINE
void OML_SparseMatrixBlock::SetRowOffset(OML_U32 nRowOffset)
{
	nRowOffset_ = nRowOffset_;
}

OML_INLINE
void OML_SparseMatrixBlock::SetColOffset(OML_U32 nColOffset)
{
	nColOffset_ = nRowOffset_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_SparseMatrixBlock::SetOffset
 *
 *  \param  nRowOffset position of the block in the rows
 *  \param  nColOffset position of the block in the colls
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OML_INLINE
void OML_SparseMatrixBlock::SetOffset(OML_U32 nRowOffset, OML_U32 nColOffset)
{
	this->SetRowOffset( nRowOffset );
	this->SetColOffset( nColOffset );
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

