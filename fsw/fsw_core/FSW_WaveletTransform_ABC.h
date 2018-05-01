
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_WaveletTransform_ABC.h
 *  \brief  Definition of class \c FSW_WaveletTransform_ABC
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_WAVELETTRANSFORM_ABC_H_
#define _FSW_WAVELETTRANSFORM_ABC_H_

#include "FSW_Config.h"
#include "FSW_QuadTreeNode.h"

FSW_BEGIN_NAMESPACE

class FSW_NodeMap;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_WaveletTransform_ABC
 *  \brief  Base class for all wavelet transform on the sphere.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 *
 *  Each class must implement 2 transforms (forward and backward).
 */ 
/*------------------------------------------------------------------------------*/

class FSW_WaveletTransform_ABC
{

public:

	FSW_WaveletTransform_ABC();

    /*------------------------------------------------------------------------------*/
    /** \name Launch the global transforms and pre-computation. Shouln't be overloaded. */
    /*------------------------------------------------------------------------------*/
    //@{
	virtual void UpdateDataChunk( T_NodeMapVector& NodeMapVector ) = 0;
    virtual void ForwardTransform( FSW_NodeMap& NodeMap, FSW_U32 nReverseLevel );
	virtual void BackwardTransform( FSW_NodeMap& NodeMap, FSW_U32 nReverseLevel );
    //@}

    //-------------------------------------------------------------------------
    /** \name Predict and update stages : to overload. */
    //-------------------------------------------------------------------------
    //@{
	virtual void ForwardPredict( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel ) = 0;
	virtual void ForwardUpdate( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel ) = 0;
	virtual void BackwardPredict( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel ) = 0;
	virtual void BackwardUpdate( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel ) = 0;
    //@}

	void SetUseUpdate( FSW_Bool bUseUpdate );
	FSW_Bool GetUseUpdate();

	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the transformed in the compressed files. */
	virtual const char* GetTransformName() = 0;
    //@}

private:

	FSW_Bool bUseUpdate_;

};

FSW_END_NAMESPACE


#ifdef FSW_USE_INLINE
    #include "FSW_WaveletTransform_ABC.inl"
#endif

#endif // _FSW_WAVELETTRANSFORM_ABC_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
