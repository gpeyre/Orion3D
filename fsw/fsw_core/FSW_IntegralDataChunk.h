
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_IntegralDataChunk.h
 *  \brief  Definition of class \c FSW_IntegralDataChunk
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_INTEGRALDATACHUNK_H_
#define _FSW_INTEGRALDATACHUNK_H_

#include "FSW_Config.h"
#include "FSW_DataChunk_ABC.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_IntegralDataChunk
 *  \brief  Contains the data needed by a vertex base linear wavelet
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 *
 *  A data chunk is put on each vertex V. It contains the value of the integral 
 *	a the scale function that is 1 on this vertex, and decrease linearly to
 *	zero on the neighbor vertex of the level of the node that owned this vertex V.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_IntegralDataChunk: public FSW_DataChunk_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_IntegralDataChunk();
    virtual ~FSW_IntegralDataChunk();
    //@}

	FSW_U32 GetType();

	FSW_Float GetIntegral(FSW_U32 nLevel);
	void SetIntegral(FSW_Float rVal, FSW_I32 nLevel);
	void AddIntegral(FSW_Float rVal, FSW_I32 nLevel);

private:

	 T_FloatVector IntegralValues_;

};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_IntegralDataChunk.inl"
#endif


#endif // _FSW_INTEGRALDATACHUNK_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
