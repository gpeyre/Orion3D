/*----------------------------------------------------------------------*/
/*                          OR_System.h                                 */
/*----------------------------------------------------------------------*/
/* definitions relative to the system level.                            */
/*----------------------------------------------------------------------*/

#ifndef _OR_SYSTEM_H_
#define _OR_SYSTEM_H_

namespace OR
{
	
/*
NOTA : for the moment, all these definition are only useful for Zip file managing.
*/

/*---------------------------------------------------------------------*/
/*                         VFS definitions                             */
/*---------------------------------------------------------------------*/

/**	File time structure - used to query and set
	the last-modification time of a file. */
struct OR_FileTime
{
	OR_I32 sec;		// 0..59
	OR_I32 min;		// 0..59
	OR_I32 hour;		// 0..23
	OR_I32 day;		// 1..31
	OR_I32 mon;		// 0..11
	OR_I32 year;		// 1900, 2001, ...
};

/** This macro can be used to assign a "struct tm" to a OR_FileTime */
#define ASSIGN_FILETIME(ft,tm)	\
		(ft).sec = (tm).tm_sec;	\
		(ft).min = (tm).tm_min;	\
		(ft).hour = (tm).tm_hour;	\
		(ft).day = (tm).tm_mday;	\
		(ft).mon = (tm).tm_mon;	\
		(ft).year = (tm).tm_year + 1900;
  

/** Composite path divider */
#define VFS_PATH_DIVIDER        ','
/** The "virtual" path separator */
#define VFS_PATH_SEPARATOR      '/'
/** The maximal "virtual" path+filename length */
#define VFS_MAX_PATH_LEN        256
/** The maximal  path+filename length */
#ifndef MAXPATHLEN
#define MAXPATHLEN				256
#endif

/** Maximal path length */
#ifndef MAXPATHLEN
	#ifdef _MAX_FNAME
		#define MAXPATHLEN _MAX_FNAME
	#else
		#define MAXPATHLEN 260 /* not 256 */
	#endif
#endif

/** Path separator character */
#ifndef PATH_SEPARATOR
	#if defined(_MAC_OS_) || defined(__CYGWIN32__)
		#define PATH_SEPARATOR '/'
	#elif defined(_WIN32_)
		#define PATH_SEPARATOR '\\'
	#else
		#define PATH_SEPARATOR '/'
	#endif
#endif

/** append a slash char to a string */
#define APPEND_SLASH(str,len)			\
     if ((len)					\
      && (str[len - 1] != '/')			\
      && (str[len - 1] != PATH_SEPARATOR))	\
     {						\
       str[len++] = PATH_SEPARATOR;		\
       str[len] = 0;				\
     } /* endif */
	 

/* temporaty file & directory ***************************************/
#ifdef _WIN32_
	#include <process.h>
	#define TEMP_FILE "~orion.tmp", GETPID()
	#define TEMP_DIR win32_tempdir()
	/** function called by TEMP_DIR macro */
	static inline char *win32_tempdir()
	{
		char *tmp;
		if ((tmp = getenv ("TMP")) != NULL)
			return tmp;
		if ((tmp = getenv ("TEMP")) != NULL)
			return tmp;
		return "";
	}
#endif
#ifndef _WIN32_
	#error Must define TEMP_DIR, TEMP_FILE, etc ...
#endif

/** get the process identifier */
#ifdef _WIN32_
	#define GETPID() _getpid()
#endif
#ifndef _WIN32_
	#error Must define GETPID ...
#endif



	
} // namespace OR

#endif /* #ifndef _OR_SYSTEM_H_ */


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////