/*------------------------------------------------------------------------------*/
/** 
 *  \file   Stdafx.h
 *  \brief  Include for precompiled header.
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/
#ifndef _STDAFX_H_
#define _STDAFX_H_

#pragma once

/* 'identifier' : identifier was truncated to 'number' characters in the debug information */
#pragma warning( disable : 4786 )

//-------------------------------------------------------------------------
/** \name C++ STL */
//-------------------------------------------------------------------------
//@{
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include <string>
using namespace std;
//@}

//-------------------------------------------------------------------------
/** \name classical ANSI c libraries */
//-------------------------------------------------------------------------
//@{
#include <stdio.h>			
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
//#include <ios>
#include <stdarg.h>
#include <conio.h>
#include <crtdbg.h>
//@}

//-------------------------------------------------------------------------
/** \name DevIl */
//-------------------------------------------------------------------------
//@{
#include <il/il.h>
#include <il/ilu.h>
#include <il/ilut.h>
//@}

/*----------------------------------------------------------------------*/
/* win32 #include                                                       */
/*----------------------------------------------------------------------*/

#ifdef WIN32
	/** main win32 header */
	#include <windows.h>
#endif // _USE_WIN32_


#endif // _STDAFX_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
