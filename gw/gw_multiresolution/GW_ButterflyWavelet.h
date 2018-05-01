/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_ButterflyWavelet.h
 *  \brief  Definition of class \c GW_ButterflyWavelet
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_BUTTERFLYWAVELET_H_
#define _GW_BUTTERFLYWAVELET_H_

#include "../gw_core/GW_Config.h"
#include "GW_QuadTreeNode.h"
#include "GW_WaveletTransform_ABC.h"
#include "GW_IntegralDataChunk.h"

GW_BEGIN_NAMESPACE

#define BUTTERFLY_WEIGHT_V 0.5f
#define BUTTERFLY_WEIGHT_F 0.125f
#define BUTTERFLY_WEIGHT_E -0.0625f

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_ButterflyWavelet
 *  \brief  Implement a linear interpolating wavelet.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 *
 *  This use a linear predictor, and an update lifting wich assure 
 *  vanishing of 1 moment.
 */ 
/*------------------------------------------------------------------------------*/

class GW_ButterflyWavelet:	public GW_WaveletTransform_ABC
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
	{ return "GW_ButterflyWavelet"; }
    //@}

	//-------------------------------------------------------------------------
    /** \name Very powerfull helper method. */
    //-------------------------------------------------------------------------
    //@{
	typedef void (*T_FunctionApplyableOnStencil)( GW_QuadTreeVertex& StencilVert, GW_Float rWeight, void* pChunk );
	static void IterateFunctionOnLocalStencil( GW_QuadTreeNode& CurNode, T_FunctionApplyableOnStencil pFunc, GW_U32 nVert, void* pChunk, GW_Float w=0 );
    //@}

private:

	static void Predict_Helper( GW_QuadTreeVertex& StencilVert, GW_Float rWeight, void* pChunk );
	static void Update_Helper( GW_QuadTreeVertex& StencilVert, GW_Float rWeight, void* pChunk );
	static void RecurseIntegral_Helper( GW_QuadTreeVertex& StencilVert, GW_Float rWeight, void* pChunk );

	void ComputeIntegral( GW_QuadTreeNode& CurNode );
	void RecurseIntegral( GW_QuadTreeNode& CurNode, GW_U32 nLevel );
	void RecopyIntegral( GW_QuadTreeNode& CurNode, GW_U32 nLevel );

};


/** An helper data set to recurse update computation on the stencil. */
class T_ButterflyUpdateChunk
{
public:
	T_ButterflyUpdateChunk( GW_Float rCentralIntegral, GW_QuadTreeVertex* pCentralVert, GW_U32 nReverseLevel, GW_Bool bForwardUpdate )
	:	rCentralIntegral_	( rCentralIntegral ),
		pCentralVert_		( pCentralVert ),
		nReverseLevel_		( nReverseLevel ),
		bForwardUpdate_		( bForwardUpdate )
	{ }
	GW_Float rCentralIntegral_;
	GW_QuadTreeVertex* pCentralVert_;
	GW_U32 nReverseLevel_;
	GW_Bool bForwardUpdate_;
};

/** An helper data set to recurse integral computation on the stencil. */
class T_ButterflyRecurseIntegralChunk
{
public:
	T_ButterflyRecurseIntegralChunk( GW_Float rCentralIntegral, GW_U32 nReverseLevel )
	:	rCentralIntegral_	( rCentralIntegral ),
		nReverseLevel_		( nReverseLevel )
	{ }
	GW_Float rCentralIntegral_;
	GW_U32 nReverseLevel_;
};

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_ButterflyWavelet.inl"
#endif


#endif // _GW_BUTTERFLYWAVELET_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
