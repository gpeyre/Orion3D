
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_SparseMatrixBlock.h
 *  \brief Definition of class \c OML_SparseMatrixBlock
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_SparseMatrixBlock_h_
#define __OML_SparseMatrixBlock_h_

#include "OML_Config.h"
#include "OML_MatrixNxP.h"

namespace OML {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_SparseMatrixBlock
 *  \brief  a block in the sparse matrix.
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/

class OML_SparseMatrixBlock
{
public:
	
    //-------------------------------------------------------------------------
    /** \name constructors & destructors */
    //-------------------------------------------------------------------------
    //@{
	OML_SparseMatrixBlock(OML_MatrixNxP& m, OML_U32 nRowOffset, OML_U32 nColOffset);
	OML_SparseMatrixBlock();
	virtual ~OML_SparseMatrixBlock();
	OML_SparseMatrixBlock(const OML_SparseMatrixBlock& m);
	OML_SparseMatrixBlock &operator =(const OML_SparseMatrixBlock &m);
    //@}
	
    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OML_MatrixNxP& GetMatrix() const;
	void          SetMatrix(OML_MatrixNxP& m);
	OML_U32 GetRowOffset() const;
	OML_U32 GetColOffset() const;
	
	void SetRowOffset(OML_U32 nRowOffset);
	void SetColOffset(OML_U32 nColOffset);
	void SetOffset(OML_U32 nRowOffset, OML_U32 nColOffset);
    //@}
	
protected:
	
	/** the matrix that this block supports */
	OML_MatrixNxP* pMatrix_;
	/** the offset on i */
	OML_U32 nRowOffset_; 
	/** the offset on j */
	OML_U32 nColOffset_;
};

typedef list<OML_SparseMatrixBlock*>				T_SparseMatrixBlockList;
typedef T_SparseMatrixBlockList::iterator			IT_SparseMatrixBlockList;
typedef T_SparseMatrixBlockList::const_iterator		ITconst_SparseMatrixBlockList;

typedef vector<OML_SparseMatrixBlock*>				T_SparseMatrixBlockVector;
typedef T_SparseMatrixBlockVector::iterator			IT_SparseMatrixBlockVector;
typedef T_SparseMatrixBlockVector::const_iterator	ITconst_SparseMatrixBlockVector;

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_SparseMatrixBlock.inl"
#endif


#endif // __OML_SparseMatrixBlock_h_

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
