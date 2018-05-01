	/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_MatrixNxP.h
 *  \brief Definition of class \c OML_MatrixNxP
 *  \author Gabriel Peyré 2001-09-18
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_MatrixNxP_h_
#define __OML_MatrixNxP_h_

#include "OML_Config.h"
#include "OML_VectorND.h"
#include "OML_Maths.h"

namespace OML {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_MatrixNxP
 *  \brief  A matrix of variable dimension.
 *  \author Gabriel Peyré 2001-09-18
 *
 *	Note that the matrix is \e row \e major, which is not the case of the 
 *	\c OML_Matrix4x4.
 *	
 *	\code
 *	+-----+-----+.....+-------+
 *  | 0,0 | 0,1 |     | 0,n-1 |
 *	+-----+-----+.....+-------+
 *  | 1,0 | 1,2 |     | 1,n-1 |
 *	+-----+-----+.....+-------+
 *  .     .     . i,j .       . <- i
 *	+-----+-----+.....+-------+
 *  |p-1,0|p-1,1|     |p-1,m-1|
 *	+-----+-----+.....+-------+
 *                 ^
 *                 |
 *                 j
 *  offset = j+i*n
 *	\endcode
 */ 
/*------------------------------------------------------------------------------*/

class OML_MatrixNxP
{

public:

    OML_MatrixNxP();
	OML_MatrixNxP(OML_U32 nNbrRows, OML_U32 nNbrCols);
	OML_MatrixNxP(const OML_MatrixNxP& m);
	OML_MatrixNxP &operator = (const OML_MatrixNxP &m);
    virtual ~OML_MatrixNxP();

    //-------------------------------------------------------------------------
    /** \name dimension manipulation */
    //-------------------------------------------------------------------------
    //@{
	OML_U32 GetNbrRows() const;
	OML_U32 GetNbrCols() const;
	void Reset(OML_U32 nNbrRows, OML_U32 nNbrCols);
    //@}

    //-------------------------------------------------------------------------
    /** \name multiplication methods (both optimised and non-optimised) */
    //-------------------------------------------------------------------------
    //@{
	OML_MatrixNxP operator*(const OML_MatrixNxP& m);
	static void Multiply(const OML_MatrixNxP& a, const OML_MatrixNxP& b, OML_MatrixNxP& r);
	void operator *= (const OML_MatrixNxP & m);
	
	OML_VectorND operator*(const OML_VectorND& v);
	static void Multiply(const OML_MatrixNxP& a, const OML_VectorND& v, OML_VectorND& r);
    //@}
	
	OML_MatrixNxP Transpose();
	static void  Transpose(const OML_MatrixNxP& a, OML_MatrixNxP& r);

    //-------------------------------------------------------------------------
    /** \name sum */
    //-------------------------------------------------------------------------
    //@{
	OML_MatrixNxP operator + (const OML_MatrixNxP & m);
	static void Add(const OML_MatrixNxP& a, const OML_MatrixNxP& b, OML_MatrixNxP& r);
	OML_MatrixNxP operator - (const OML_MatrixNxP & m);
	static void Minus(const OML_MatrixNxP& a, const OML_MatrixNxP& b, OML_MatrixNxP& r);
	OML_MatrixNxP operator - ();
	static void UMinus(const OML_MatrixNxP& a, OML_MatrixNxP& r);
	void operator += (const OML_MatrixNxP & m);
	void operator -= (const OML_MatrixNxP & m);
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OML_Float*	GetData() const;
	OML_Float	GetData(OML_U32 i, OML_U32 j) const;
	void		SetData(OML_U32 i, OML_U32 j, OML_Float rVal);
    //@}

	
    //-------------------------------------------------------------------------
    /** \name Utility */
    //-------------------------------------------------------------------------
    //@{
	void ClearUpperTriangle();
	void ClearLowerTriangle();
	void SetZero();
	void SetValue(OML_Float rVal);
	void Randomize(OML_Float rMin=0, OML_Float rMax=1);
	void Print (char *cFormat = "%10.4f ", FILE *f=stdout);
    //@}

	//-------------------------------------------------------------------------
	/** \name  system resolution*/
	//-------------------------------------------------------------------------
	//@{
	void GaussSeidelStep(OML_VectorND& x, const OML_VectorND& b) const;
	//@}


protected:

	/** the number of columns */
	OML_U32 nNbrCols_;
	/** the number of rows */
	OML_U32 nNbrRows_;
	/** the matrix datas */
	OML_Float* aData_;

};

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_MatrixNxP.inl"
#endif


#endif // __OML_MatrixNxP_h_

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

