
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_SparseMatrix.h
 *  \brief Definition of class \c OML_SparseMatrix
 *  \author Gabriel Peyré 2001-09-30
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_SparseMatrix_h_
#define __OML_SparseMatrix_h_

#include "OML_Config.h"
#include "OML_VectorND.h"
#include "OML_MatrixNxp.h"
#include "OML_SparseMatrixBlock.h"
#include "OML_Maths.h"

namespace OML {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_SparseMatrix
 *  \brief	a sparse matrix.
 *  \author Gabriel Peyré 2001-09-30
 *  
 *	A sparse matrix is a collection of block matrix.
 *	Don't use it to make ordinary maths ops ! only use it to compute
 *	matrix times vector operation. This is because sparse matrix just makes
 *	reference to \c OML_MatrixNxP, and doesn't perform copy of these matrix, so
 *	no duplication of OML_SparseMatrix should be made.
 */ 
/*------------------------------------------------------------------------------*/

class OML_SparseMatrix
{

public:

    OML_SparseMatrix();
	OML_SparseMatrix(OML_U32 nNbrRows, OML_U32 nNbrCols);
	OML_SparseMatrix(const OML_SparseMatrix& m);
	OML_SparseMatrix &operator = (const OML_SparseMatrix &m);
    virtual ~OML_SparseMatrix();

	//-------------------------------------------------------------------------
    /** \name dimension manipulation */
    //-------------------------------------------------------------------------
    //@{
	OML_U32 GetNbrRows() const;
	OML_U32 GetNbrCols() const;
	void   SetDim(OML_U32 nNbrRows, OML_U32 nNbrCols);
	void   SetNbrRows(OML_U32 nNbrRows);
	void   SetNbrCols(OML_U32 nNbrCols);

	const T_SparseMatrixBlockList& GetBlockList() const;
	T_SparseMatrixBlockList& GetBlockList();
	OML_U32 GetNbrBlock() const;
    //@}

    //-------------------------------------------------------------------------
    /** \name block management */
    //-------------------------------------------------------------------------
    //@{
	void    AddBlock(OML_MatrixNxP& m, OML_U32 nOffsetRow, OML_U32 nOffsetCol);
	OML_Bool RemoveBlock(OML_MatrixNxP& m);
	void    AddBlock(OML_SparseMatrixBlock& m);
	void    RemoveBlock(OML_SparseMatrixBlock& m);
    //@}

    //-------------------------------------------------------------------------
    /** \name multiplication methods (both optimised and non-optimised) */
    //-------------------------------------------------------------------------
    //@{	
	OML_VectorND operator*(const OML_VectorND& v);
	static void Multiply(const OML_SparseMatrix& a, const OML_VectorND& v, OML_VectorND& r);
	static void MultiplyTranspose(const OML_SparseMatrix& a, const OML_VectorND& v, OML_VectorND& r);
    //@}

	//-------------------------------------------------------------------------
    /** \name Utility */
    //-------------------------------------------------------------------------
    //@{
	void SetZero();
	void SetValue(OML_Float rVal);
	void Randomize(OML_Float rMin=0, OML_Float rMax=1);
	void Print (char *cFormat = "%10.4f ", FILE *f=stdout);
    //@}

protected:

	/** list of blocks */
	T_SparseMatrixBlockList BlockList_;	
	
	/** the number of columns */
	OML_U32 nNbrCols_;
	/** the number of rows */
	OML_U32 nNbrRows_;

};

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_SparseMatrix.inl"
#endif


#endif // __OML_SparseMatrix_h_

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

