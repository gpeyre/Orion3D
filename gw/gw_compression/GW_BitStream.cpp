/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BitStream.cpp
 *  \brief  Definition of class \c GW_BitStream
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_BitStream.cpp(c) Gabriel Peyré & Antoine Bouthors2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_BitStream.h"

#ifndef GW_USE_INLINE
    #include "GW_BitStream.inl"
#endif

using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream constructor
/**
 *  \param  StreamToUse [iostream&] The STL stream we want to use. It's up to the used to open/close it.
 *	\param	mode [T_StreamMode] Can be \c kWriteMode to put value in the stream, and \c kReadMode to get value from the tream.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
GW_BitStream::GW_BitStream(FILE* StreamToUse, T_StreamMode mode)
:	pStream_	( StreamToUse ),
	nNbrBits_	( 0 ),
	nCurChar_	( 0 ),
	bError_		( GW_False ),
	Mode_		( mode )
{
	if( mode==kWriteMode )
		nMask_	= 0x80;		// write
	else
		nMask_	= 0;		// read
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_BitStream::~GW_BitStream()
{
	/* flush the char if it's not finished. */
	if( Mode_ == kWriteMode )
		this->Flush();
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::TestClass
/**
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Launch a bunch of test on the class.
 */
/*------------------------------------------------------------------------------*/
void GW_BitStream::TestClass( GW_Bool bVerbose )
{
#ifdef GW_DEBUG
	/* Test classic Get/Set *****************************************************/
	if( bVerbose )
		cout << "GW_BitStream -- starting test ... ";
	FILE* pFile = fopen( GW_TEST_FILE, "wb" );	
	GW_ASSERT( pFile!=NULL );
	GW_BitStream bs( pFile, GW_BitStream::kWriteMode );
	GW_Bool bVal[10] = { GW_True, GW_False, GW_True, GW_True, GW_True, 
						 GW_False, GW_False, GW_True, GW_True, GW_False };
	GW_U32 bUVal[10] = {0,1,2,3,4,5,6,7,8,9};
	for( GW_U32 i=0; i<10; ++i )
		bs << bVal[i];
	for( GW_U32 i=0; i<10; ++i )
		bs << bUVal[i];
	for( GW_U32 i=0; i<10; ++i )
		bs << bVal[i];

	bs.Flush();
	fclose(pFile);
	pFile = fopen( "test.bin", "rb" );
	bs.Reset( pFile, GW_BitStream::kReadMode );

	GW_Bool bTest;
	GW_U32 bUTest;
	for( GW_U32 i=0; i<10; ++i )
	{
		bs >> bTest;
		GW_ASSERT( bTest==bVal[i] );
	}
	for( GW_U32 i=0; i<10; ++i )
	{
		bs >> bUTest;
		GW_ASSERT( bUTest==bUVal[i] );
	}
	for( GW_U32 i=0; i<10; ++i )
	{
		bs >> bTest;
		GW_ASSERT( bTest==bVal[i] );
	}

	/* Test Get/Set in debug version **************************************************/
	enum T_SomeDebugToken
	{ kPass1 = 32, kPass2 = 64 };
	pFile = fopen( GW_TEST_FILE, "wb" );	
	GW_ASSERT( pFile!=NULL );
	bs.Reset( pFile, GW_BitStream::kWriteMode );
	for( GW_U32 i=0; i<10; ++i )
		bs.DebugPut( bVal[i], kPass1+i );
	for( GW_U32 i=0; i<10; ++i )
		bs.Put( bUVal[i] ) ;
	for( GW_U32 i=0; i<10; ++i )
		bs.DebugPut( bVal[i], kPass2+i );

	bs.Flush();
	fclose(pFile);
	pFile = fopen( "test.bin", "rb" );
	bs.Reset( pFile, GW_BitStream::kReadMode );

	bTest;
	bUTest;
	GW_U8 nDebugToken; 
	for( GW_U32 i=0; i<10; ++i )
	{
		bs.DebugGet( bTest, nDebugToken );
		GW_ASSERT( bTest==bVal[i] );
		GW_ASSERT( nDebugToken==kPass1+i );
	}
	for( GW_U32 i=0; i<10; ++i )
	{
		bs >> bUTest;
		GW_ASSERT( bUTest==bUVal[i] );
	}
	for( GW_U32 i=0; i<10; ++i )
	{
		bs.DebugGet( bTest, nDebugToken );
		GW_ASSERT( bTest==bVal[i] );
		GW_ASSERT( nDebugToken==kPass2+i );
	}

	if( bVerbose )
		cout << "test completed with success." << endl;
#endif // #ifdef
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::Reset
/**
 *  \param  StreamToUse [iostream*] The new STL stream. Let the stream NULL to keep previous one.
 *	\param	mode [T_StreamMode] Can be \c ios::out to put value in the stream, and \c ios::in to get value from the tream.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Reset the whole stream.
 */
/*------------------------------------------------------------------------------*/
void GW_BitStream::Reset( FILE* StreamToUse, T_StreamMode mode )
{
	/* flush the char if it's not finished. */
	if( Mode_==kWriteMode )
		this->Flush();
	/* reset the params */
	pStream_	= StreamToUse;
	nNbrBits_	= 0;
	nCurChar_	= 0;
	bError_		= GW_False;
	Mode_ = mode;
	if( mode==kWriteMode )
		nMask_	= 0x80;		// write
	else
		nMask_	= 0;		// read
}


/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::Flush
/**
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Write to the stream the current char.
 */
/*------------------------------------------------------------------------------*/
void GW_BitStream::Flush()
{
	if( Mode_==kWriteMode )
	{
		if( nMask_!=0x80 )
		{
			size_t nCount = fwrite(&nCurChar_, sizeof(GW_U8), 1, pStream_ );
			GW_ASSERT( nCount==1 );
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
// Name : GW_BitStream::DebugPut
/**
 *  \param  bVal [GW_Bool] Value to serialize.
 *  \param  nDebugToken [GW_U8] A debug information.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  A debug version of \c Put that allow to serialize both the bool 
 *  and a debug information.
 */
/*------------------------------------------------------------------------------*/
void GW_BitStream::DebugPut( GW_Bool bVal, GW_U8 nDebugToken )
{
	/* do some check */
	GW_ASSERT( pStream_!=NULL );
	GW_ASSERT( Mode_ == kWriteMode );

	/* flush current char */
	this->Flush();

	/* insert the bool value as the MSB */
	if( bVal )
		nDebugToken |= 128;
	else
		nDebugToken &= 127;

	size_t nCount = fwrite(&nDebugToken, sizeof(GW_U8), 1, pStream_ );
	GW_ASSERT( nCount==1 );

	nNbrBits_++;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::DebugGet
/**
 *  \param  bVal [GW_Bool] Value to serialize.
 *  \param  nDebugToken [GW_U8] A debug information.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  A debug version of \c Get that allow to serialize both the bool 
 *  and a debug information.
 */
/*------------------------------------------------------------------------------*/
void GW_BitStream::DebugGet( GW_Bool& bVal, GW_U8& nDebugToken )
{
	/* do some check */
	GW_ASSERT( pStream_!=NULL );
	GW_ASSERT( Mode_ == kReadMode );

	if( feof(pStream_) )
	{
		bError_ = GW_True;
		return;
	}

	size_t nCount = fread(&nDebugToken, sizeof(GW_U8), 1, pStream_ );
	GW_ASSERT( nCount==1 );

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
