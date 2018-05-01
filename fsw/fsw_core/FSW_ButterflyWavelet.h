/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_ButterflyWavelet.h
 *  \brief  Definition of class \c FSW_ButterflyWavelet
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_BUTTERFLYWAVELET_H_
#define _FSW_BUTTERFLYWAVELET_H_

#include "FSW_Config.h"
#include "FSW_QuadTreeNode.h"
#include "FSW_WaveletTransform_ABC.h"
#include "FSW_IntegralDataChunk.h"

FSW_BEGIN_NAMESPACE

#define BUTTERFLY_WEIGHT_V 0.5f
#define BUTTERFLY_WEIGHT_F 0.125f
#define BUTTERFLY_WEIGHT_E -0.0625f

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_ButterflyWavelet
 *  \brief  Implement a linear interpolating wavelet.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 *
 *  This use a linear predictor, and an update lifting wich assure 
 *  vanishing of 1 moment.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_ButterflyWavelet:	public FSW_WaveletTransform_ABC
{

public:

	/*------------------------------------------------------------------------------*/
    /** \name To overload */
    /*------------------------------------------------------------------------------*/
    //@{
	virtual void UpdateDataChunk( T_NodeMapVector& NodeMapVector );
	virtual void ForwardPredict( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel );
	virtual void ForwardUpdate( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel );
	virtual void BackwardPredict( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel );
	virtual void BackwardUpdate( FSW_QuadTreeNode& CurNode, FSW_U32 nReverseLevel );
    //@}

	
	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the transformed in the compressed files. */
	virtual const char* GetTransformName()
	{ return "FSW_ButterflyWavelet"; }
    //@}

	//-------------------------------------------------------------------------
    /** \name Very powerfull helper method. */
    //-------------------------------------------------------------------------
    //@{
	typedef void (*T_FunctionApplyableOnStencil)( FSW_QuadTreeVertex& StencilVert, FSW_Float rWeight, void* pChunk );
	static void IterateFunctionOnLocalStencil( FSW_QuadTreeNode& CurNode, T_FunctionApplyableOnStencil pFunc, FSW_U32 nVert, void* pChunk, FSW_Float w=0 );
    //@}

private:

	static void Predict_Helper( FSW_QuadTreeVertex& StencilVert, FSW_Float rWeight, void* pChunk );
	static void Update_Helper( FSW_QuadTreeVertex& StencilVert, FSW_Float rWeight, void* pChunk );
	static void RecurseIntegral_Helper( FSW_QuadTreeVertex& StencilVert, FSW_Float rWeight, void* pChunk );

	void ComputeIntegral( FSW_QuadTreeNode& CurNode );
	void RecurseIntegral( FSW_QuadTreeNode& CurNode, FSW_U32 nLevel );
	void RecopyIntegral( FSW_QuadTreeNode& CurNode, FSW_U32 nLevel );

};


/** An helper data set to recurse update computation on the stencil. */
class T_ButterflyUpdateChunk
{
public:
	T_ButterflyUpdateChunk( FSW_Float rCentralIntegral, FSW_QuadTreeVertex* pCentralVert, FSW_U32 nReverseLevel, FSW_Bool bForwardUpdate )
	:	rCentralIntegral_	( rCentralIntegral ),
		pCentralVert_		( pCentralVert ),
		nReverseLevel_		( nReverseLevel ),
		bForwardUpdate_		( bForwardUpdate )
	{ }
	FSW_Float rCentralIntegral_;
	FSW_QuadTreeVertex* pCentralVert_;
	FSW_U32 nReverseLevel_;
	FSW_Bool bForwardUpdate_;
};

/** An helper data set to recurse integral computation on the stencil. */
class T_ButterflyRecurseIntegralChunk
{
public:
	T_ButterflyRecurseIntegralChunk( FSW_Float rCentralIntegral, FSW_U32 nReverseLevel )
	:	rCentralIntegral_	( rCentralIntegral ),
		nReverseLevel_		( nReverseLevel )
	{ }
	FSW_Float rCentralIntegral_;
	FSW_U32 nReverseLevel_;
};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_ButterflyWavelet.inl"
#endif


#endif // _FSW_BUTTERFLYWAVELET_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
