/*-------------------------------------------------------------------*/
/*                       OR_PrintBuildLog.h                          */
/*-------------------------------------------------------------------*/
/* Created : 13 Apr 2001   2h10                                      */
/*-------------------------------------------------------------------*/

/** \file
	Include this file if you want to display a build message for your compiler.
	Really usefull !
	\author Gabriel
*/

#ifndef _OR_PRINTBUILDLOG_H_
#define _OR_PRINTBUILDLOG_H_
	
/* OS message *****************************************************/
#pragma message (" ")
#pragma message ("+--------------------------- Orion3D OS --------------------------------+")
#ifdef _WIN32_
#pragma message ("| Win32 build.                                                          |")
#endif
#ifdef _MAC_OS_
#pragma message ("| MacOS build.                                                          |")
#endif
#ifdef _UNIX_
#pragma message ("| Unix build.                                                           |")
#endif
#if (!defined(_WIN32_) & !defined(_MAC_OS_) & !defined(_UNIX_))
#error You must specify on which OS you are working. Please refer to OR_Config.h.
#endif
/* debug messages ************************************************/
#pragma message ("+-------------------------- Orion3D debug ------------------------------+")
#ifdef OR_DEBUG
#pragma message ("| Debug mode on.                                                        |")
#else
#pragma message ("| Debug mode off.                                                       |")
#endif // OR_DEBUG
/* linkage messages ***********************************************/
#pragma message ("+------------------------ Orion3D import/export ------------------------+")
#ifdef ORION3D_EXPORTS
#pragma message ("| Exporting (building) Orion3D.dll.                                     |")
#endif
#ifdef ORION3D_IMPORTS
#pragma message ("| Importing (using) Orion3D.dll.                                        |")
#endif
#ifdef ORION3D_STATICLINK
#pragma message ("| Using static link.                                                    |")
#endif
#if (!defined(ORION3D_EXPORTS) & !defined(ORION3D_IMPORTS) & !defined(ORION3D_STATICLINK))
#pragma message ("| WARNING : not using Orion3D.dll and not using static link.            |")
#endif
/* image messages ***********************************************/
#pragma message ("+------------------------ Orion3D image library ------------------------+")
#ifdef _USE_OPENIL_
#pragma message ("| Using OpenIL to handle image files.                                   |")
#else
#pragma message ("| *NOT* using OpenIL to handle image files. This is not supported yet.  |")
#error You *MUST* define _USE_OPENIL_ in OR_Config.h.
#endif
/* archive messages ***********************************************/
#pragma message ("+----------------------- Orion3D archives library ----------------------+")
#ifdef _USE_ZLIB_
#pragma message ("| Using ZLIB to handle ZIP file archives.                               |")
#else
#pragma message ("| Not using ZLIB to handle ZIP file archives :  you won't be able to    |")
#pragma message ("| read or write ZIP archive. Define _USE_ZLIB_ to use ZLIB.             |")
#endif
/* output messages ***********************************************/
#ifdef _USE_GLUT_
#pragma message ("+------------------------ Orion3D input/output -------------------------+")
#pragma message ("| Using GLUT for input/output.                                          |")
#endif
#ifdef _USE_GTK_
#pragma message ("+------------------------ Orion3D input/output -------------------------+")
#pragma message ("| Using GTK+ for input/output.                                          |")
#endif
#ifdef _USE_WIN32_
#pragma message ("+------------------------ Orion3D input/output -------------------------+")
#pragma message ("| Using Win32 for input/output.                                         |")
#endif
#ifdef _USE_NONE_
#pragma message ("+------------------------ Orion3D input/output -------------------------+")
#pragma message ("| Not using any library for output/input : you must specify your own    |")
#pragma message ("| functions.                                                            |")
#endif
/* collision detection messages ***************************************/
#pragma message ("+-------------- Orion3D collision detection library --------------------+")
#ifdef _USE_OPCODE_
#pragma message ("| Using OPCODE to handle collision detection.                           |")
#else
#pragma message ("| Not using OPCODE to handle collision detection.                       |")
#pragma message ("| Physics response won't works.                                         |")
#endif

#pragma message ("+-----------------------------------------------------------------------+")
#pragma message (" ")


#endif /* #ifndef _OR_PRINTBUILDLOG_H_ */

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