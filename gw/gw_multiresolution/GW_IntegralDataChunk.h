/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_IntegralDataChunk.h
 *  \brief  Definition of class \c GW_IntegralDataChunk
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_INTEGRALDATACHUNK_H_
#define _GW_INTEGRALDATACHUNK_H_

#include "../gw_core/GW_Config.h"
#include "GW_DataChunk_ABC.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_IntegralDataChunk
 *  \brief  Contains the data needed by a vertex base linear wavelet
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 *
 *  A data chunk is put on each vertex V. It contains the value of the integral 
 *	a the scale function that is 1 on this vertex, and decrease linearly to
 *	zero on the neighbor vertex of the level of the node that owned this vertex V.
 */ 
/*------------------------------------------------------------------------------*/

class GW_IntegralDataChunk: public GW_DataChunk_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_IntegralDataChunk();
    virtual ~GW_IntegralDataChunk();
    //@}

	GW_U32 GetType();

	GW_Float GetIntegral(GW_U32 nLevel);
	void SetIntegral(GW_Float rVal, GW_I32 nLevel);
	void AddIntegral(GW_Float rVal, GW_I32 nLevel);

private:

	 T_FloatVector IntegralValues_;

};

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_IntegralDataChunk.inl"
#endif


#endif // _GW_INTEGRALDATACHUNK_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
