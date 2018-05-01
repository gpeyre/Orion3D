
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BitStream.h
 *  \brief  Definition of class \c GW_BitStream
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_BITSTREAM_H_
#define _GW_BITSTREAM_H_

#include "../gw_core/GW_Config.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_BitStream
 *  \brief  Implement a stream of bit.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 *
 *  Allow to put/get single bit into a file or any other stream.
 */ 
/*------------------------------------------------------------------------------*/

class GW_BitStream
{

public:

	enum T_StreamMode
	{
		kWriteMode	=	std::ios::out,
		kReadMode	=	std::ios::in
	};

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_BitStream(FILE* StreamToUse = NULL, T_StreamMode mode = kWriteMode);
    virtual ~GW_BitStream();
    //@}

    //-------------------------------------------------------------------------
    /** \name Method for serialization. */
    //-------------------------------------------------------------------------
    //@{
	void Put( GW_Bool bVal );
	void Put( GW_U32 nVal );
	void Get( GW_Bool& bVal );
	void Get( GW_U32& nVal );

	void DebugPut( GW_Bool bVal, GW_U8 nDebugToken );
	void DebugGet( GW_Bool& bVal, GW_U8& nDebugToken );
    //@}


    //-------------------------------------------------------------------------
    /** \name Operators for serialization. */
    //-------------------------------------------------------------------------
    //@{
	GW_BitStream& operator << ( GW_Bool bVal );
	GW_BitStream& operator << ( GW_U32 nVal );
	GW_BitStream& operator >> ( GW_Bool& bVal );
	GW_BitStream& operator >> ( GW_U32& bVal );
    //@}

	GW_Bool GetError();
	FILE* GetStream();
	GW_U32 GetNbrBits() const;

	void Reset( FILE* StreamToUse, T_StreamMode mode );
	void Flush();

	static void TestClass( GW_Bool bVerbose=GW_False );

private:

	/** the stream */
	FILE* pStream_;
	/** Count the number of bit. Usfull for stats reporting. */
	GW_U32 nNbrBits_;
    /** Current \c char (serialized to stream when full). */
	GW_U8 nCurChar_;
	/** Current mask, indicate the position of the next bit in the char. */
	GW_U8 nMask_;
	/** set to true if there was an error during last read/write */
	GW_Bool bError_;
	/** the way we use the stream */
	T_StreamMode Mode_;

};

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_BitStream.inl"
#endif


#endif // _GW_BITSTREAM_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré & Antoine Bouthors
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
