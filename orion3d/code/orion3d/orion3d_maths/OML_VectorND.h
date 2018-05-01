
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_VectorND.h
 *  \brief Definition of class \c OML_VectorND
 *  \authOML Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_VectorND_h_
#define __OML_VectorND_h_

#include "OML_Config.h"
#include "OML_Maths.h"

namespace OML {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_VectorND
 *  \brief  A vector of any dimension.
 *  \authOML Gabriel Peyré 2001-09-29
 */ 
/*------------------------------------------------------------------------------*/

class OML_VectorND;
typedef void (*T_MatrixTimeVectOMLFunc)( OML_VectorND& v, OML_VectorND& r );

class OML_VectorND
{

public:

	OML_VectorND();
	OML_VectorND(OML_U32 nDim);
	OML_VectorND(const OML_VectorND& m);
	OML_VectorND &operator = (const OML_VectorND &m);
    virtual ~OML_VectorND();
	
    //-------------------------------------------------------------------------
    /** \name dimension manipulation */
    //-------------------------------------------------------------------------
    //@{
	OML_U32 GetDim() const;
	void Reset(OML_U32 nDim);
    //@}

	//-------------------------------------------------------------------------
    /** \name multiplication methods  */
    //-------------------------------------------------------------------------
    //@{
	OML_VectorND operator*(const OML_Float& f) const;
	static void Multiply(const OML_Float f, const OML_VectorND& v, OML_VectorND& r);
	void operator *= (const OML_Float & f);
    //@}

    //-------------------------------------------------------------------------
    /** \name sum */
    //-------------------------------------------------------------------------
    //@{
	OML_VectorND operator + (const OML_VectorND& v) const;
	static void Add(const OML_VectorND& a, const OML_VectorND& b, OML_VectorND& r);
	OML_VectorND operator - (const OML_VectorND & m) const;
	static void Minus(const OML_VectorND& a, const OML_VectorND& b, OML_VectorND& r);
	OML_VectorND operator - () const;
	static void UMinus(const OML_VectorND& a, OML_VectorND& r);
	void operator += (const OML_VectorND & v);
	void operator -= (const OML_VectorND & v);
    //@}

    //-------------------------------------------------------------------------
    /** \name misc math ops */
    //-------------------------------------------------------------------------
    //@{	
	OML_Float operator*(const OML_VectorND& f);

	OML_Float NormInf();
	OML_Float Norm1();
	OML_Float Norm2();
    //@}


    //-------------------------------------------------------------------------
    /** \name accessOMLs */
    //-------------------------------------------------------------------------
    //@{
	OML_Float* GetData() const;
	OML_Float  GetData(OML_U32 i) const;
	void       SetData(OML_U32 i, OML_Float rVal);
    //@}

    //-------------------------------------------------------------------------
    /** \name Utility */
    //-------------------------------------------------------------------------
    //@{
	void SetZero();
	void SetValue(OML_Float rVal);
	void Randomize(OML_Float rMin=0, OML_Float rMax=1);
	void Print (char *cFOMLmat = "%10.4f ", FILE *f=stdout);
    //@}

    //-------------------------------------------------------------------------
    /** \name linear system resolution */
    //-------------------------------------------------------------------------
    //@{
	static OML_Bool SolveBiConjugateGradient( const OML_VectorND& b, OML_VectorND& x, 
											  T_MatrixTimeVectOMLFunc atimes, T_MatrixTimeVectOMLFunc atransptimes, 
											  OML_I32 nNbrIterMax=-1, OML_Float rPrecision = OML_EPSILON );
	static OML_Bool SolveConjugateGradient  ( const OML_VectorND& b, OML_VectorND& x, 
											T_MatrixTimeVectOMLFunc atimes, 
											OML_I32 nNbrIterMax=-1, OML_Float rPrecision = OML_EPSILON );
    //@}

protected:
	
	/** dimension of the vector */
	OML_U32 nDim_;
	/** the vector datas */
	OML_Float* aData_;

};


OML_VectorND operator*(const OML_Float& f, OML_VectorND& v);

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_VectorND.inl"
#endif


#endif // __OML_VectorND_h_

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The OMLion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the OMLion3D licence.                                  //
//  Refer to OMLion3d_licence.txt fOML mOMLe details about the OMLion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence OMLion3D.                              //
//  Se repOMLter a OMLion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

