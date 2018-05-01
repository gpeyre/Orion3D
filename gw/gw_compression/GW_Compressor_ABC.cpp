/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_Compressor_ABC.cpp
 *  \brief  Definition of class \c GW_Compressor_ABC
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_Compressor_ABC.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_Compressor_ABC.h"
#include "GW_CompressionHeader.h"

using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_Compressor_ABC constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
GW_Compressor_ABC::GW_Compressor_ABC()
:	pCompressionCallback_PerBit_		( NULL ),
	pCompressionCallback_PerBitPlane_	( NULL )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_Compressor_ABC destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_Compressor_ABC::~GW_Compressor_ABC()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
// Name : GW_Compressor_ABC::SetCompressionCallback_PerBit
/**
 *  \param  pFunc [T_CompressionCallback_Func] The function.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Set the function that is called by the compressor to know if it 
 *  should continue. Called once per bit added.
 */
/*------------------------------------------------------------------------------*/
void GW_Compressor_ABC::SetCompressionCallback_PerBit(T_CompressionCallback_Func pFunc)
{
	pCompressionCallback_PerBit_ = pFunc;
}

/*------------------------------------------------------------------------------*/
// Name : GW_Compressor_ABC::SetCompressionCallback_PerBitPlane
/**
 *  \param  pFunc [T_CompressionCallback_Func] The function.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Set the function that is called by the compressor to know if it 
 *  should continue. Called once per bitplane.
 */
/*------------------------------------------------------------------------------*/
void GW_Compressor_ABC::SetCompressionCallback_PerBitPlane(T_CompressionCallback_Func pFunc)
{
	pCompressionCallback_PerBitPlane_ = pFunc;
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
