/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BitStream.cpp
 *  \brief  Definition of class \c FSW_BitStream
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_BitStream.cpp(c) Gabriel Peyré & Antoine Bouthors2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_BitStream.h"

#ifndef FSW_USE_INLINE
    #include "FSW_BitStream.inl"
#endif

using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream constructor
/**
 *  \param  StreamToUse [iostream&] The STL stream we want to use. It's up to the used to open/close it.
 *	\param	mode [T_StreamMode] Can be \c kWriteMode to put value in the stream, and \c kReadMode to get value from the tream.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
FSW_BitStream::FSW_BitStream(FILE* StreamToUse, T_StreamMode mode)
:	pStream_	( StreamToUse ),
	nNbrBits_	( 0 ),
	nCurChar_	( 0 ),
	bError_		( FSW_False ),
	Mode_		( mode )
{
	if( mode==kWriteMode )
		nMask_	= 0x80;		// write
	else
		nMask_	= 0;		// read
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_BitStream::~FSW_BitStream()
{
	/* flush the char if it's not finished. */
	if( Mode_ == kWriteMode )
		this->Flush();
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::TestClass
/**
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Launch a bunch of test on the class.
 */
/*------------------------------------------------------------------------------*/
void FSW_BitStream::TestClass( FSW_Bool bVerbose )
{
#ifdef FSW_DEBUG
	/* Test classic Get/Set *****************************************************/
	if( bVerbose )
		cout << "FSW_BitStream -- starting test ... ";
	FILE* pFile = fopen( FSW_TEST_FILE, "wb" );	
	FSW_ASSERT( pFile!=NULL );
	FSW_BitStream bs( pFile, FSW_BitStream::kWriteMode );
	FSW_Bool bVal[10] = { FSW_True, FSW_False, FSW_True, FSW_True, FSW_True, 
						 FSW_False, FSW_False, FSW_True, FSW_True, FSW_False };
	FSW_U32 bUVal[10] = {0,1,2,3,4,5,6,7,8,9};
	for( FSW_U32 i=0; i<10; ++i )
		bs << bVal[i];
	for( FSW_U32 i=0; i<10; ++i )
		bs << bUVal[i];
	for( FSW_U32 i=0; i<10; ++i )
		bs << bVal[i];

	bs.Flush();
	fclose(pFile);
	pFile = fopen( "test.bin", "rb" );
	bs.Reset( pFile, FSW_BitStream::kReadMode );

	FSW_Bool bTest;
	FSW_U32 bUTest;
	for( FSW_U32 i=0; i<10; ++i )
	{
		bs >> bTest;
		FSW_ASSERT( bTest==bVal[i] );
	}
	for( FSW_U32 i=0; i<10; ++i )
	{
		bs >> bUTest;
		FSW_ASSERT( bUTest==bUVal[i] );
	}
	for( FSW_U32 i=0; i<10; ++i )
	{
		bs >> bTest;
		FSW_ASSERT( bTest==bVal[i] );
	}

	/* Test Get/Set in debug version **************************************************/
	enum T_SomeDebugToken
	{ kPass1 = 32, kPass2 = 64 };
	pFile = fopen( FSW_TEST_FILE, "wb" );	
	FSW_ASSERT( pFile!=NULL );
	bs.Reset( pFile, FSW_BitStream::kWriteMode );
	for( FSW_U32 i=0; i<10; ++i )
		bs.DebugPut( bVal[i], kPass1+i );
	for( FSW_U32 i=0; i<10; ++i )
		bs.Put( bUVal[i] ) ;
	for( FSW_U32 i=0; i<10; ++i )
		bs.DebugPut( bVal[i], kPass2+i );

	bs.Flush();
	fclose(pFile);
	pFile = fopen( "test.bin", "rb" );
	bs.Reset( pFile, FSW_BitStream::kReadMode );

	bTest;
	bUTest;
	FSW_U8 nDebugToken; 
	for( FSW_U32 i=0; i<10; ++i )
	{
		bs.DebugGet( bTest, nDebugToken );
		FSW_ASSERT( bTest==bVal[i] );
		FSW_ASSERT( nDebugToken==kPass1+i );
	}
	for( FSW_U32 i=0; i<10; ++i )
	{
		bs >> bUTest;
		FSW_ASSERT( bUTest==bUVal[i] );
	}
	for( FSW_U32 i=0; i<10; ++i )
	{
		bs.DebugGet( bTest, nDebugToken );
		FSW_ASSERT( bTest==bVal[i] );
		FSW_ASSERT( nDebugToken==kPass2+i );
	}

	if( bVerbose )
		cout << "test completed with success." << endl;
#endif // #ifdef
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::Reset
/**
 *  \param  StreamToUse [iostream*] The new STL stream. Let the stream NULL to keep previous one.
 *	\param	mode [T_StreamMode] Can be \c ios::out to put value in the stream, and \c ios::in to get value from the tream.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Reset the whole stream.
 */
/*------------------------------------------------------------------------------*/
void FSW_BitStream::Reset( FILE* StreamToUse, T_StreamMode mode )
{
	/* flush the char if it's not finished. */
	if( Mode_==kWriteMode )
		this->Flush();
	/* reset the params */
	pStream_	= StreamToUse;
	nNbrBits_	= 0;
	nCurChar_	= 0;
	bError_		= FSW_False;
	Mode_ = mode;
	if( mode==kWriteMode )
		nMask_	= 0x80;		// write
	else
		nMask_	= 0;		// read
}


/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::Flush
/**
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Write to the stream the current char.
 */
/*------------------------------------------------------------------------------*/
void FSW_BitStream::Flush()
{
	if( Mode_==kWriteMode )
	{
		if( nMask_!=0x80 )
		{
			size_t nCount = fwrite(&nCurChar_, sizeof(FSW_U8), 1, pStream_ );
			FSW_ASSERT( nCount==1 );
			/* reset char and mask */
			nCurChar_ = 0;
			nMask_ = 0x80;
		}
	}
	else
	{
		/* restart the char */
		nMask_ = 0;
		nCurChar_ = 0;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::DebugPut
/**
 *  \param  bVal [FSW_Bool] Value to serialize.
 *  \param  nDebugToken [FSW_U8] A debug information.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  A debug version of \c Put that allow to serialize both the bool 
 *  and a debug information.
 */
/*------------------------------------------------------------------------------*/
void FSW_BitStream::DebugPut( FSW_Bool bVal, FSW_U8 nDebugToken )
{
	/* do some check */
	FSW_ASSERT( pStream_!=NULL );
	FSW_ASSERT( Mode_ == kWriteMode );

	/* flush current char */
	this->Flush();

	/* insert the bool value as the MSB */
	if( bVal )
		nDebugToken |= 128;
	else
		nDebugToken &= 127;

	size_t nCount = fwrite(&nDebugToken, sizeof(FSW_U8), 1, pStream_ );
	FSW_ASSERT( nCount==1 );

	nNbrBits_++;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::DebugGet
/**
 *  \param  bVal [FSW_Bool] Value to serialize.
 *  \param  nDebugToken [FSW_U8] A debug information.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  A debug version of \c Get that allow to serialize both the bool 
 *  and a debug information.
 */
/*------------------------------------------------------------------------------*/
void FSW_BitStream::DebugGet( FSW_Bool& bVal, FSW_U8& nDebugToken )
{
	/* do some check */
	FSW_ASSERT( pStream_!=NULL );
	FSW_ASSERT( Mode_ == kReadMode );

	if( feof(pStream_) )
	{
		bError_ = FSW_True;
		return;
	}

	size_t nCount = fread(&nDebugToken, sizeof(FSW_U8), 1, pStream_ );
	FSW_ASSERT( nCount==1 );

	/* get back MSB */
	bVal = (nDebugToken&128)==128;
	/* clear the MSB */
	nDebugToken &= 127;

	nNbrBits_++;
}

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
