/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_LinearWavelet.h
 *  \brief  Definition of class \c FSW_LinearWavelet
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_LINEARWAVELET_H_
#define _FSW_LINEARWAVELET_H_

#include "FSW_Config.h"
#include "FSW_QuadTreeNode.h"
#include "FSW_WaveletTransform_ABC.h"
#include "FSW_IntegralDataChunk.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_LinearWavelet
 *  \brief  Implement a linear interpolating wavelet.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 *
 *  This use a linear predictor, and an update lifting wich assure 
 *  vanishing of 1 moment.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_LinearWavelet:	public FSW_WaveletTransform_ABC
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
	{ return "FSW_LinearWavelet"; }
    //@}

private:

	void ComputeIntegral( FSW_QuadTreeNode& CurNode );
	void RecurseIntegral( FSW_QuadTreeNode& CurNode, FSW_U32 nLevel );
	void RecopyIntegral( FSW_QuadTreeNode& CurNode, FSW_U32 nLevel );

};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_LinearWavelet.inl"
#endif


#endif // _FSW_LINEARWAVELET_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
