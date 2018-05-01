
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BitStream.h
 *  \brief  Definition of class \c FSW_BitStream
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_BITSTREAM_H_
#define _FSW_BITSTREAM_H_

#include "../fsw_core/FSW_Config.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_BitStream
 *  \brief  Implement a stream of bit.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 *
 *  Allow to put/get single bit into a file or any other stream.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_BitStream
{

public:

	enum T_StreamMode
	{
		kWriteMode	=	ios::out,
		kReadMode	=	ios::in
	};

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_BitStream(FILE* StreamToUse = NULL, T_StreamMode mode = kWriteMode);
    virtual ~FSW_BitStream();
    //@}

    //-------------------------------------------------------------------------
    /** \name Method for serialization. */
    //-------------------------------------------------------------------------
    //@{
	void Put( FSW_Bool bVal );
	void Put( FSW_U32 nVal );
	void Get( FSW_Bool& bVal );
	void Get( FSW_U32& nVal );

	void DebugPut( FSW_Bool bVal, FSW_U8 nDebugToken );
	void DebugGet( FSW_Bool& bVal, FSW_U8& nDebugToken );
    //@}


    //-------------------------------------------------------------------------
    /** \name Operators for serialization. */
    //-------------------------------------------------------------------------
    //@{
	FSW_BitStream& operator << ( FSW_Bool bVal );
	FSW_BitStream& operator << ( FSW_U32 nVal );
	FSW_BitStream& operator >> ( FSW_Bool& bVal );
	FSW_BitStream& operator >> ( FSW_U32& bVal );
    //@}

	FSW_Bool GetError();
	FILE* GetStream();
	FSW_U32 GetNbrBits() const;

	void Reset( FILE* StreamToUse, T_StreamMode mode );
	void Flush();

	static void TestClass( FSW_Bool bVerbose=FSW_False );

private:

	/** the stream */
	FILE* pStream_;
	/** Count the number of bit. Usfull for stats reporting. */
	FSW_U32 nNbrBits_;
    /** Current \c char (serialized to stream when full). */
	FSW_U8 nCurChar_;
	/** Current mask, indicate the position of the next bit in the char. */
	FSW_U8 nMask_;
	/** set to true if there was an error during last read/write */
	FSW_Bool bError_;
	/** the way we use the stream */
	T_StreamMode Mode_;

};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_BitStream.inl"
#endif


#endif // _FSW_BITSTREAM_H_


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
