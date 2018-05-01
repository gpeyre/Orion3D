/*---------------------------------------------------------------------*/
/*                                  stdafx.h                           */
/*---------------------------------------------------------------------*/
/* to build precompiled headers                                        */            
/*---------------------------------------------------------------------*/

/** \file 
	This file indicate to the compiler which header must be included as precompiled headers.
	\author Gabriel.
**/

#ifndef _OR_STDAFX_H_
#define _OR_STDAFX_H_


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
//#include <ios>
#include <stdarg.h>
#include <conio.h>
#include <direct.h>
//@}



/*----------------------------------------------------------------------*/
/* win32 #include                                                       */
/*----------------------------------------------------------------------*/

#ifdef WIN32
	/** main win32 header */
	#include <windows.h>
#endif // _USE_WIN32_


//-------------------------------------------------------------------------
/** \name OpenGL inclusions */
//-------------------------------------------------------------------------
//@{
/** main opengl header */
#include <GL/gl.h>
/** main glu header */
#include <GL/glu.h>
//@}


#endif // _OR__STDAFX_H_



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