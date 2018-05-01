/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_LinearWavelet.h
 *  \brief  Definition of class \c GW_LinearWavelet
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_LINEARWAVELET_H_
#define _GW_LINEARWAVELET_H_

#include "../gw_core/GW_Config.h"
#include "GW_QuadTreeNode.h"
#include "GW_WaveletTransform_ABC.h"
#include "GW_IntegralDataChunk.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_LinearWavelet
 *  \brief  Implement a linear interpolating wavelet.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 *
 *  This use a linear predictor, and an update lifting wich assure 
 *  vanishing of 1 moment.
 */ 
/*------------------------------------------------------------------------------*/

class GW_LinearWavelet:	public GW_WaveletTransform_ABC
{

public:

	/*------------------------------------------------------------------------------*/
    /** \name To overload */
    /*------------------------------------------------------------------------------*/
    //@{
	virtual void UpdateDataChunk( T_NodeMapVector& NodeMapVector );
	virtual void ForwardPredict( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel );
	virtual void ForwardUpdate( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel );
	virtual void BackwardPredict( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel );
	virtual void BackwardUpdate( GW_QuadTreeNode& CurNode, GW_U32 nReverseLevel );
    //@}

	
	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the transformed in the compressed files. */
	virtual const char* GetTransformName()
	{ return "GW_LinearWavelet"; }
    //@}

private:

	void ComputeIntegral( GW_QuadTreeNode& CurNode );
	void RecurseIntegral( GW_QuadTreeNode& CurNode, GW_U32 nLevel );
	void RecopyIntegral( GW_QuadTreeNode& CurNode, GW_U32 nLevel );

};

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_LinearWavelet.inl"
#endif


#endif // _GW_LINEARWAVELET_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
