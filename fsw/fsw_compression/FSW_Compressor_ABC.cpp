/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_Compressor_ABC.cpp
 *  \brief  Definition of class \c FSW_Compressor_ABC
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_Compressor_ABC.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_Compressor_ABC.h"
#include "FSW_CompressionHeader.h"

using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_Compressor_ABC constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
FSW_Compressor_ABC::FSW_Compressor_ABC()
:	pCompressionCallback_PerBit_		( NULL ),
	pCompressionCallback_PerBitPlane_	( NULL )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Compressor_ABC destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_Compressor_ABC::~FSW_Compressor_ABC()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
// Name : FSW_Compressor_ABC::SetCompressionCallback_PerBit
/**
 *  \param  pFunc [T_CompressionCallback_Func] The function.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Set the function that is called by the compressor to know if it 
 *  should continue. Called once per bit added.
 */
/*------------------------------------------------------------------------------*/
void FSW_Compressor_ABC::SetCompressionCallback_PerBit(T_CompressionCallback_Func pFunc)
{
	pCompressionCallback_PerBit_ = pFunc;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Compressor_ABC::SetCompressionCallback_PerBitPlane
/**
 *  \param  pFunc [T_CompressionCallback_Func] The function.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Set the function that is called by the compressor to know if it 
 *  should continue. Called once per bitplane.
 */
/*------------------------------------------------------------------------------*/
void FSW_Compressor_ABC::SetCompressionCallback_PerBitPlane(T_CompressionCallback_Func pFunc)
{
	pCompressionCallback_PerBitPlane_ = pFunc;
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
