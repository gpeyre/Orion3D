/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_Config.h
 *  \brief  Main configuration file.
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _OR_LUA_CONFIG_H_
#define _OR_LUA_CONFIG_H_

namespace OR {

#define OR_VERSION 100

//-------------------------------------------------------------------------
/** \name debug & inline directive */
//-------------------------------------------------------------------------
//@{
#ifdef _DEBUG
	#ifndef OR_DEBUG
		#define OR_DEBUG
	#endif // OR_DEBUG
#endif // _DEBUG
	
#ifndef OR_DEBUG
	#ifndef OR_USE_INLINE
		#define OR_USE_INLINE
	#endif // OR_USE_INLINE
#endif // OR_DEBUG
	
#ifdef OR_USE_INLINE
	#ifndef OR_INLINE
		#define OR_INLINE inline
	#endif // ORION3D_INLINE
#else
	#ifndef OR_INLINE
		#define OR_INLINE 
	#endif // OR_INLINE	
#endif // OR_USE_INLINE
//@}

//-------------------------------------------------------------------------
/** \name library linkage specification */
//-------------------------------------------------------------------------
//@{
#pragma comment (lib, "LibLua.lib" )
#pragma comment (lib, "LibLuaLib.lib" )
//@}
	
//-------------------------------------------------------------------------
/** \name Basic types */
//-------------------------------------------------------------------------
//@{
#ifdef __UNIX__
	typedef char					OR_I8;
	typedef unsigned char           OR_U8;
	typedef short					OR_I16;
	typedef unsigned short			OR_U16;
	typedef long                    OR_I32;
	typedef unsigned long           OR_U32;
	typedef long long int           OR_I64;
	typedef unsigned long long int  OR_U64;
	typedef float                   OR_Real32;
	typedef double                  OR_Real64;
	typedef bool                    OR_Bool;
	typedef OR_Real32              OR_Float;
#elif defined (WIN32)
	typedef char                OR_I8;
	typedef unsigned char       OR_U8;
	typedef short				OR_I16;
	typedef unsigned short		OR_U16;
	typedef long                OR_I32;
	typedef unsigned long       OR_U32;
	typedef __int64             OR_I64;
	typedef unsigned __int64    OR_U64;
	typedef float               OR_Real32;
	typedef double              OR_Real64;
	typedef bool                OR_Bool;
	typedef OR_Real32          OR_Float;
#elif defined (_PS2_)
	typedef char                OR_I8;
	typedef unsigned char       OR_U8;
	typedef short				OR_I16;
	typedef unsigned short		OR_U16;
	typedef int                 OR_I32;
	typedef unsigned int        OR_U32;
	typedef long long           OR_I64;
	typedef unsigned long long  OR_U64;
	typedef float               OR_Real32;
	typedef double              OR_Real64;
	typedef OR_I8              OR_Bool;
	typedef OR_Real32          OR_Float;
#else
	#error "Unknown architecture !"
#endif
	
	typedef void*				OR_UserData;
	
	/** value returned by function to indicates errOR OR OR_OK */
	typedef OR_I32 OR_RETURN_CODE;

//@}

//-------------------------------------------------------------------------
/** \name generic macros */
//-------------------------------------------------------------------------
//@{
/** delete a single pointer */
#define OR_DELETE(p) {if (p!=NULL) delete p; p=NULL;}
/** delete an array pointer */
#define OR_DELETEARRAY(p) {if (p!=NULL) delete [] p; p=NULL;}
//@}

//-------------------------------------------------------------------------
/** \name some constants */
//-------------------------------------------------------------------------
//@{
#define OR_True  true
#define OR_False false
//@}

//-------------------------------------------------------------------------
/** \name assertion macros */
//-------------------------------------------------------------------------
//@{
#ifdef OR_DEBUG
	#define OR_ASSERT(expr) _ASSERT(expr)
	#define OR_DEBUG_ONLY(expr) expr
#else
	#define OR_ASSERT(expr)
	#define OR_DEBUG_ONLY(expr)
#endif // OR_DEBUG
//@}


} // End namespace OR

#endif // _OR_LUA_CONFIG_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2002 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
