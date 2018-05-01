#ifndef _OR_ENDIAN_CONV_H_
#define _OR_ENDIAN_CONV_H_

#include "../configuration/OR_Config.h"

	
/*
 * The following define the slashes used in pathnames of the PC/MAC/UNIX platforms
 *
 * *SLASH are the filename delimitors
 * *BACK  are the characters used to ascend one level
 * *ABS   are the chars we put at the beginning of the filename to indicate an absolute path
 * *REL   are the chars we put at the beginning of the filename to indicate a relative path
 *
 * Additional rule for mac path validation: path can contain no colons.  and that would mean
 * it's a simple filename or dir name (and not an abs path)
 * Every other time, the path needn't have a trailing colon, except if it's an abs. path.
 *
 * Simplified version: always prepend and end with a colon for relative paths, and always
 * end with a colong for abs paths.
 */
#define PCSLASH   "\\"
#define PCBACK    ".."
#define PCABS	  PCSLASH
#define PCREL	  ""

#define MACSLASH  ":"
#define MACBACK   MACSLASH
#define MACABS	  ""
#define MACREL	  MACSLASH

#define UNIXSLASH "/"
#define UNIXBACK  ".."
#define UNIXABS	  UNIXSLASH
#define UNIXREL   ""

#ifdef _MAC_OS_
	#define OR_SLASH MACSLASH
	#define OR_BACK  MACBACK
	#define OR_REL   MACREL
#elif defined(_UNIX_)
	#define OR_SLASH UNIXSLASH
	#define OR_BACK  UNIXBACK
	#define OR_REL   UNIXREL
#else /*windows*/
	#define OR_SLASH PCSLASH
	#define OR_BACK  PCBACK
	#define OR_REL   PCREL
#endif	

#if defined(_MAC_OS_) | defined(_UNIX_)
	/* macro that inverses the bytes in a 16bit number */
	#define INVS(n) ((n << 8) & 0xFF00) + ((n >> 8) & 0x00FF)
	/* macro that inverses the bytes in a 32bit number */
	#define INVI(n) (INVS(((n & 0xFFFF0000)  >> 16)) + /* lsb */ \
					(INVS(( n & 0x0000FFFF)) << 16))   /* msb */
#else 
	/* do nothing */
	#define INVS(n) (n)
	#define INVI(n) (n)
#endif
	/* inverses the bytes in a 32bit OR_Float */
	float   invf(float n);
	/* inverses the bytes in an array of floats of length len */
	void invf(float n[], int len);
	/* same for dwords */
	void invi(DWORD n[], DWORD len);
	void invs(char *s, int len);
	/* a generalized fread function that decides if to invert or not */
	size_t xfread(void *dest, size_t size, size_t nmemb, FILE *stream);
	void   convpath(char *path, char *base);
	void ImportType(void *Type, FILE *file);
#endif /* ifndef _OR_ENDIAN_CONV_H */

	

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