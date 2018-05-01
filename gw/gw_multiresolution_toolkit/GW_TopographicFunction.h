
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_TopographicFunction.h
 *  \brief  Definition of class \c GW_TopographicFunction
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/
#ifndef _GW_TOPOGRAPHICFUNCTION_H_
#define _GW_TOPOGRAPHICFUNCTION_H_

#include "../gw_core/GW_Config.h"
#include "../gw_multiresolution/GW_SphericalMaths.h"
#include "../gw_multiresolution/GW_TreeFunction_ABC.h"
#include "../gw_multiresolution/GW_QuadTreeVertex.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_TopographicFunction
 *  \brief  Load topographic data from a valid ETOPO file.
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 *
 *  This class discribe a function on the sphere via data from an 
 *  ETOPO file. Allow the tree builder to get data from the file 
 *  data using interpolation.
 */ 
/*------------------------------------------------------------------------------*/

class GW_TopographicFunction: public GW_TreeFunction_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_TopographicFunction();
    virtual ~GW_TopographicFunction();
    //@}

	GW_RETURN_CODE LoadFromFile(	const char* aFileAdress, 
									GW_U32 uLongPrec, GW_U32 uLatPrec,
									const char* aMode="rb", const char* aType="U16" );
	GW_RETURN_CODE LoadFromImage( const char * File );

	//-------------------------------------------------------------------------
    /** \name Overloaded functions */
    //-------------------------------------------------------------------------
    //@{
	virtual GW_Float GetValue( GW_Float rU, GW_Float rV ) const;
    //@}

	
    //-------------------------------------------------------------------------
    /** \name Helpers */
    //-------------------------------------------------------------------------
    //@{
	GW_Float GetMax();
	GW_Float GetMin();
	void GetGradient( GW_Float rU, GW_Float rV, GW_Float& gU, GW_Float& gV ) const;
    //@}

    //-------------------------------------------------------------------------
    /** \name Helpers */
    //-------------------------------------------------------------------------
    //@{
	void ScaleTo(GW_Float rMin, GW_Float rMax);
    //@}

    //-------------------------------------------------------------------------
    /** \name Direct data access. */
    //-------------------------------------------------------------------------
    //@{
	GW_U32 GetWidth();
	GW_U32 GetHeight();
	GW_Float* GetData();
    //@}


private:

	GW_Float AccessData( GW_U32 uX, GW_U32 uY ) const;
	void SetData( GW_Float rVal, GW_U32 uX, GW_U32 uY ) const;

	/** an array containing the data */
	GW_Float* aData_;
	GW_U32 aSize_[2];
	/** helper datas */
	GW_Float rMax_;
	GW_Float rMin_;

};

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_TopographicFunction.inl"
#endif


#endif // _GW_TOPOGRAPHICFUNCTION_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2002 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
