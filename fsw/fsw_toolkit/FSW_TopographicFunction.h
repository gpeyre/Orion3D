
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_TopographicFunction.h
 *  \brief  Definition of class \c FSW_TopographicFunction
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/
#ifndef _FSW_TOPOGRAPHICFUNCTION_H_
#define _FSW_TOPOGRAPHICFUNCTION_H_

#include "../fsw_core/FSW_Config.h"
#include "../fsw_core/FSW_Maths.h"
#include "../fsw_core/FSW_TreeFunction_ABC.h"
#include "../fsw_core/FSW_QuadTreeVertex.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_TopographicFunction
 *  \brief  Load topographic data from a valid ETOPO file.
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 *
 *  This class discribe a function on the sphere via data from an 
 *  ETOPO file. Allow the tree builder to get data from the file 
 *  data using interpolation.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_TopographicFunction: public FSW_TreeFunction_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_TopographicFunction();
    virtual ~FSW_TopographicFunction();
    //@}

	FSW_RETURN_CODE LoadFromFile(	const char* aFileAdress, 
									FSW_U32 uLongPrec, FSW_U32 uLatPrec,
									const char* aMode="rb", const char* aType="U16" );
	FSW_RETURN_CODE LoadFromImage( const char * File );

	//-------------------------------------------------------------------------
    /** \name Overloaded functions */
    //-------------------------------------------------------------------------
    //@{
	virtual FSW_Float GetValue( FSW_Float rU, FSW_Float rV ) const;
    //@}

	
    //-------------------------------------------------------------------------
    /** \name Helpers */
    //-------------------------------------------------------------------------
    //@{
	FSW_Float GetMax();
	FSW_Float GetMin();
    //@}

    //-------------------------------------------------------------------------
    /** \name Helpers */
    //-------------------------------------------------------------------------
    //@{
	void ScaleTo(FSW_Float rMin, FSW_Float rMax);
    //@}


private:

	FSW_Float AccessData( FSW_U32 uX, FSW_U32 uY ) const;
	void SetData( FSW_Float rVal, FSW_U32 uX, FSW_U32 uY ) const;

	/** an array containing the data */
	FSW_Float* aData_;
	FSW_U32 aSize_[2];
	/** helper datas */
	FSW_Float rMax_;
	FSW_Float rMin_;

};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_TopographicFunction.inl"
#endif


#endif // _FSW_TOPOGRAPHICFUNCTION_H_


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
