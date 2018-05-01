/*------------------------------------------------------------------------------*/
/**
 *  \file  OR_Config.h
 *  \brief This is the main configuration file.	MUST BE INCLUDED IN EACH ORION3D FILE.
 *  \author Gabriel Peyré 2001-07-10
 */
/*------------------------------------------------------------------------------*/


#ifndef _OR_CONFIG_H_
#define _OR_CONFIG_H_

namespace OR
{

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
		// #defin OR_INLINE __forceinline
	#endif // ORION3D_INLINE
#else
	#ifndef OR_INLINE
		#define OR_INLINE 
	#endif // OR_INLINE	
#endif // OR_USE_INLINE
//@}

//-------------------------------------------------------------------------
/** \name exception directive */
//-------------------------------------------------------------------------
//@{
#ifdef OR_USE_EXCEPTION
	#define OR_THROW(X) throw(X)
#else
	#define OR_THROW(X)
#endif // OR_THROW
//@}

//-------------------------------------------------------------------------
/** \name OS directives */
//-------------------------------------------------------------------------
//@{
/* UNDER VC++, PLEASE, USE PROJECT>SETTING TO SET THE PREPROCESSOR DEFINITION. */
// #define _UNIX_
// #define _MAC_OS_
// #define _WIN32_
#ifdef WIN32
	#ifndef _WIN32_
		#define _WIN32_
	#endif // _WIN32_
#endif // WIN32
//@}

//-------------------------------------------------------------------------
/** \name linkage directives */
//-------------------------------------------------------------------------
//@{
/* UNDER VC++, PLEASE, USE PROJECT>SETTING TO SET THE PREPROCESSOR DEFINITION */
// #define ORION3D_EXPORTS		// Exporting (building) Orion3D.dll.
// #define ORION3D_IMPORTS		// Importing (using) Orion3D.dll.
// #define ORION3D_STATICLIB	// Using static linkage lib file.
// #define ORION3D_STATICLINK	// Not using either the dll or the lib, using direct inclusion of the .cpp.
//@}

//-------------------------------------------------------------------------
/** \name input/output directives */
//-------------------------------------------------------------------------
//@{
/* UNDER VC++, PLEASE, USE PROJECT>SETTING TO SET THE PREPROCESSOR DEFINITION */
// #define _USE_GLUT_	// using GLUT for input/output.
// #define _USE_WIN32_	// using WIN32 for input/output.
// #define _USE_GTK_	// using GTK+ for input/output.
// #define _USE_NONE_	// not using any library for input/output.
//@}



//-------------------------------------------------------------------------
/** \name zip file library directive */
//-------------------------------------------------------------------------
//@{
#ifndef _USE_ZLIB_
	#define _USE_ZLIB_
#endif // _USE_ZLIB_
//@}

//-------------------------------------------------------------------------
/** \name image file library directives */
//-------------------------------------------------------------------------
//@{
#ifndef _USE_OPENIL_
	#define _USE_OPENIL_
#endif // _USE_OPENIL_
//@}

//-------------------------------------------------------------------------
/** \name collision detection library directive */
//-------------------------------------------------------------------------
//@{
#ifndef _USE_OPCODE_
	#define _USE_OPCODE_
#endif // _USE_SWIFT_
//@}

//-------------------------------------------------------------------------
/** \name library linker directives */
//-------------------------------------------------------------------------
//@{
#ifdef _WIN32_
	/* opengl libs ******************************************************/
	#pragma comment(lib, "opengl32.lib")
	#pragma comment(lib, "glu32.lib")

	/* for time get time ************************************************/
	#pragma comment(lib, "winmm.lib")

	/* input/output libs ************************************************/
	#ifdef _USE_GLUT_
		#pragma comment(lib, "glut32.lib")
	#endif // _USE_GLUT_
	#ifdef _USE_GTK_
		#pragma comment(lib, "gdk-1.3.lib")
		#pragma comment(lib, "glib-1.3.lib")
		#pragma comment(lib, "gtk-1.3.lib")
		#pragma comment(lib, "gtkgl.lib")
	#endif // _USE_GTK_

	/* zip libs *********************************************************/
	#ifdef _USE_ZLIB_
		#pragma comment(lib, "zlib.lib")
	#endif // _USE_ZLIB_

	/* images libs ******************************************************/
	#ifdef _USE_OPENIL_
		#ifdef OR_DEBUG
			#pragma comment (lib, "DevIL-d.lib")
			#pragma comment (lib, "ilu-d.lib")
			#pragma comment (lib, "ilut-d.lib")
		#else
			#pragma comment (lib, "DevIL.lib")
			#pragma comment (lib, "ilu.lib")
			#pragma comment (lib, "ilut.lib")
		#endif	// OR_DEBUG
	#endif // _USE_OPENIL_

	/* collision libs ***************************************************/
	#ifdef _USE_OPCODE_
		#ifdef OR_DEBUG
			#pragma comment (lib, "opcode_d.lib")
		#else
			#pragma comment (lib, "opcode.lib")
		#endif	// OR_DEBUG
	#endif // _USE_OPCODE_

	/* font libs ********************************************************/
	#ifdef _USE_FTGL_
		#ifdef OR_DEBUG
			#pragma comment (lib, "orion3d_wrapper_font_dbg.lib")
		#else
			#pragma comment (lib, "orion3d_wrapper_font.lib")
		#endif // OR_DEBUG
	#endif // _USE_FTGL_

	/* LUA support ******************************************************/
	#ifdef OR_DEBUG
		#pragma comment(lib, "orion3d_wrapper_lua_dbg.lib")
	#else
		#pragma comment(lib, "orion3d_wrapper_lua.lib")
	#endif // OR_DEBUG

	/* Orion3D maths lib ************************************************/
	#ifdef OR_DEBUG
		#pragma comment(lib, "orion3d_maths_dbg.lib")
	#else
		#pragma comment(lib, "orion3d_maths.lib")
	#endif // OR_DEBUG
	
	/* Orion3D main library *********************************************/
	#if (defined ORION3D_IMPORTS) && !(defined ORION3D_EXPORTS)
		#ifdef OR_DEBUG
			#pragma comment(lib, "orion3d_dbg.lib")
		#else
			#pragma comment(lib, "orion3d.lib")
		#endif // OR_DEBUG
	#endif // ORION3D_IMPORTS
#else
	/* Rakan : add your linker specifs here */
	#error Linking specifications must be included here.
#endif
//@}

//-------------------------------------------------------------------------
/** \name compiler specific options */
//-------------------------------------------------------------------------
//@{
/** When you define the STRICT symbol, you enable features that require more care in declaring and using types.
	This helps you write more portable code.  */
#ifndef STRICT
	#define STRICT
#endif // STRICT
//@}

//-------------------------------------------------------------------------
/** \name disable stupid warnings */
//-------------------------------------------------------------------------
//@{
/** f$%!&# warning 4244 */
#pragma warning( disable : 4244 )
/** conversion OR_Float -> double */
#pragma warning( disable : 4305 )
/** non dll-interface class 'OR_ManagerMap_Template<class xxx>' used as base for dll-interface class */
#pragma warning( disable : 4275 )
/** class 'xxx' needs to have dll-interface to be used by clients of class 'yyy' */
#pragma warning( disable : 4251 )
/** forcing value to bool 'true' or 'false' (performance warning) */
#pragma warning( disable : 4800 )
/** forcing value to bool 'true' or 'false' (performance warning) */
#pragma warning( disable : 4800 )
/* 'identifier' : identifier was truncated to 'number' characters in the debug information */
#pragma warning( disable : 4786 )
//@}


} // namespace OR

namespace OR
{

//-------------------------------------------------------------------------
/** \name dll import/export definitions */
//-------------------------------------------------------------------------
//@{
#if (defined(_UNIX_) | defined(_MAC_OS_))
	#define ORION3D_API
#else /* windows */
	/* exporting dll *****************************************************/
	#ifdef ORION3D_EXPORTS
		#define ORION3D_API __declspec(dllexport)
		#define ORION3D_API_TEMPLATE
	#endif
	/* importing dll *****************************************************/
	#ifdef ORION3D_IMPORTS
		#define ORION3D_API __declspec(dllimport)
		#define ORION3D_API_TEMPLATE extern
	#endif /* #ifdef ORION3D_IMPORTS */
	/* not using dll *****************************************************/
	#ifdef ORION3D_STATICLINK
		#define ORION3D_API
		#define ORION3D_API_TEMPLATE
	#endif /* #ifdef ORION3D_STATICLINK */
	/* hum, the user has not define anything ! ***************************/
	#if ( !(defined(ORION3D_IMPORTS)) & !(defined(ORION3D_EXPORTS)) & !(defined(ORION3D_STATICLINK)) )
		#pragma message("Warning, no dll export/import directive have been specified")
		#define ORION3D_API
		#define ORION3D_API_TEMPLATE
	#endif
#endif /* #ifdef _UNIX_ */
//@}


} // namespace OR

//-------------------------------------------------------------------------
/** \name unix / windows definitions */
//-------------------------------------------------------------------------
//@{
#if (defined(_UNIX_) | defined(_MAC_OS_))
	/* to handle time  */
	#ifdef _UNIX_
    	#include "gettsctime.h"
	#else
		#include <LowMem.h>
		#define timeGetTime() (LMGetTicks())
	#endif	
	/* clear memory */
    #include <string>
	#define ZeroMemory(a,b) (memcpy(NULL,a,b))
    /* DWORD doesn't exist here */
    #define DWORD OR_U32
    /* assertion */
    #include <assert.h>
    #define _ASSERTE(a) (assert(a)) 
	#define _ASSERT(a) (assert(a)) 
#else /* windows */
	/** debugging, assertion */
    #include <crtdbg.h>
#endif	/* #ifdef _UNIX_ */
//@}

//-------------------------------------------------------------------------
/** @name gtk/gtkgl #include */
//-------------------------------------------------------------------------
//@{
#ifdef _USE_GTK_
	/** main gtk header */
	#include <gtk/gtk.h>
	/** main gtkgl header */
	#include <gtkgl/gtkglarea.h>
	/** keyboard constant */
	#include <gdk/gdkkeysyms.h>
#endif/* #ifdef _USE_GTK_ */
//@}




//-------------------------------------------------------------------------
/** @name glut #include */
//-------------------------------------------------------------------------
//@{
#ifdef _USE_GLUT_
	#include <GL/glut.h>
#endif /* #ifdef _USE_GLUT_ */
//@}



//-------------------------------------------------------------------------
/** \name Orion3D basic inclusions */
//-------------------------------------------------------------------------
//@{
#include "OR_DebugConfig.h"
#include "../misc/OR_Constants.h"
#include "../misc/OR_Types.h"
#include "../misc/OR_Functions.h"
#include "../misc/OR_ReturnCodes.h"
#include "../misc/OR_Macros.h"
#include "../misc/OR_Globals.h"
#include "../utils/OR_MessageHandler.h"
#include "../opengl/OR_GLExtensions.h"
#include "../opengl/OR_Context.h"
#include "../utils/OR_Data.h"
#include "../utils/OR_String.h"
//@}


#endif // _OR_CONFIG_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////
