
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_WaveletTransform_ABC.h
 *  \brief  Definition of class \c GW_WaveletTransform_ABC
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_WAVELETTRANSFORM_ABC_H_
#define _GW_WAVELETTRANSFORM_ABC_H_

#include "../gw_core/GW_Config.h"
#include "GW_QuadTreeNode.h"

GW_BEGIN_NAMESPACE

class GW_NodeMap;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_WaveletTransform_ABC
 *  \brief  Base class for all wavelet transform on the sphere.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 *
 *  Each class must implement 2 transforms (forward and backward).
 */ 
/*------------------------------------------------------------------------------*/

class GW_WaveletTransform_ABC
{

public:

	GW_WaveletTransform_ABC();

    /*------------------------------------------------------------------------------*/
    /** \name Launch the global transforms and pre-computation. Shouln't be overloaded. */
    /*------------------------------------------------------------------------------*/
    //@{
	virtual void UpdateDataChunk( T_NodeMapVector& NodeMapVector ) = 0;
    virtual void ForwardTransform( GW_NodeMap& NodeMap, GW_U32 nReverseLevel );
	virtual void BackwardTransform( GW_NodeMap& NodeMap, GW_U32 nReverseLevel );
    //@}

    //-------------------------------------------------------------------------
    /** \name Predict and update stages : to overload. */
    //-------------------------------------------------------------------------
    //@{
	virtual void ForwardPredict( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel ) = 0;
	virtual void ForwardUpdate( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel ) = 0;
	virtual void BackwardPredict( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel ) = 0;
	virtual void BackwardUpdate( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel ) = 0;
    //@}

	void SetUseUpdate( GW_Bool bUseUpdate );
	GW_Bool GetUseUpdate();

	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the transformed in the compressed files. */
	virtual const char* GetTransformName() = 0;
    //@}

private:

	GW_Bool bUseUpdate_;

};

GW_END_NAMESPACE


#ifdef GW_USE_INLINE
    #include "GW_WaveletTransform_ABC.inl"
#endif

#endif // _GW_WAVELETTRANSFORM_ABC_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
