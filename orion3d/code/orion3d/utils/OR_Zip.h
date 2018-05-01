/*--------------------------------------------------------------------------*/
/*                              OR_Zip.h                                    */
/*--------------------------------------------------------------------------*/
/* type definitions to handle zip files.                                    */
/*--------------------------------------------------------------------------*/


/** \file 
	type definitions to handle zip files.
	\author Gabriel.
**/

#ifndef _OR_ZIP_H_
#define _OR_ZIP_H_

#include "../configuration/OR_Config.h"

namespace OR
{
	
#ifdef _USE_ZLIB_

extern "C"
{
#define Byte z_Byte	/* Kludge to avoid conflicting typedef in zconf.h */
	#include "../../zlib/zlib.h"
#undef Byte
}



#define CENTRAL_HDR_SIG	'\001','\002'	/* the infamous "PK" signature bytes, */
#define LOCAL_HDR_SIG	'\003','\004'	/*  sans "PK" (so unzip executable not */
#define END_CENTRAL_SIG	'\005','\006'	/*  mistaken for zipfile itself) */
#define EXTD_LOCAL_SIG	'\007','\010'	/* [ASCII "\113" == EBCDIC "\080" ??] */

#define DEF_WBITS	15		/* Default LZ77 window size */
#define ZIP_STORE	0		/* 'STORED' method id */
#define ZIP_DEFLATE	8		/* 'DEFLATE' method id */

typedef unsigned char  uch;
typedef unsigned short ush;
typedef unsigned long  ulg;

#define CRCVAL_INITIAL  0L

typedef struct
{
  uch version_needed_to_extract[2];
  ush general_purpose_bit_flag;
  ush compression_method;
  ush last_mod_file_time;
  ush last_mod_file_date;
  ulg crc32;
  ulg csize;
  ulg ucsize;
  ush filename_length;
  ush extra_field_length;
} ZIP_local_file_header;

typedef struct
{
  uch version_made_by[2];
  uch version_needed_to_extract[2];
  ush general_purpose_bit_flag;
  ush compression_method;
  ush last_mod_file_time;
  ush last_mod_file_date;
  ulg crc32;
  ulg csize;
  ulg ucsize;
  ush filename_length;
  ush extra_field_length;
  ush file_comment_length;
  ush disk_number_start;
  ush internal_file_attributes;
  ulg external_file_attributes;
  ulg relative_offset_local_header;
} ZIP_central_directory_file_header;

typedef struct
{
  ush number_this_disk;
  ush num_disk_start_cdir;
  ush num_entries_centrl_dir_ths_disk;
  ush total_entries_central_dir;
  ulg size_central_directory;
  ulg offset_start_central_directory;
  ush zipfile_comment_length;
} ZIP_end_central_dir_record;

//--- ZIP_local_file_header layout ---------------------------------------------
#define ZIP_LOCAL_FILE_HEADER_SIZE              26
#      define L_VERSION_NEEDED_TO_EXTRACT_0     0
#      define L_VERSION_NEEDED_TO_EXTRACT_1     1
#      define L_GENERAL_PURPOSE_BIT_FLAG        2
#      define L_COMPRESSION_METHOD              4
#      define L_LAST_MOD_FILE_TIME              6
#      define L_LAST_MOD_FILE_DATE              8
#      define L_CRC32                           10
#      define L_COMPRESSED_SIZE                 14
#      define L_UNCOMPRESSED_SIZE               18
#      define L_FILENAME_LENGTH                 22
#      define L_EXTRA_FIELD_LENGTH              24

//--- ZIP_central_directory_file_header layout ---------------------------------
#define ZIP_CENTRAL_DIRECTORY_FILE_HEADER_SIZE  42
#      define C_VERSION_MADE_BY_0               0
#      define C_VERSION_MADE_BY_1               1
#      define C_VERSION_NEEDED_TO_EXTRACT_0     2
#      define C_VERSION_NEEDED_TO_EXTRACT_1     3
#      define C_GENERAL_PURPOSE_BIT_FLAG        4
#      define C_COMPRESSION_METHOD              6
#      define C_LAST_MOD_FILE_TIME              8
#      define C_LAST_MOD_FILE_DATE              10
#      define C_CRC32                           12
#      define C_COMPRESSED_SIZE                 16
#      define C_UNCOMPRESSED_SIZE               20
#      define C_FILENAME_LENGTH                 24
#      define C_EXTRA_FIELD_LENGTH              26
#      define C_FILE_COMMENT_LENGTH             28
#      define C_DISK_NUMBER_START               30
#      define C_INTERNAL_FILE_ATTRIBUTES        32
#      define C_EXTERNAL_FILE_ATTRIBUTES        34
#      define C_RELATIVE_OFFSET_LOCAL_HEADER    38

//--- ZIP_end_central_dir_record layout ----------------------------------------
#define ZIP_END_CENTRAL_DIR_RECORD_SIZE         18
#      define E_NUMBER_THIS_DISK                0
#      define E_NUM_DISK_WITH_START_CENTRAL_DIR 2
#      define E_NUM_ENTRIES_CENTRL_DIR_THS_DISK 4
#      define E_TOTAL_ENTRIES_CENTRAL_DIR       6
#      define E_SIZE_CENTRAL_DIRECTORY          8
#      define E_OFFSET_START_CENTRAL_DIRECTORY  12
#      define E_ZIPFILE_COMMENT_LENGTH          16


#endif /* #ifdef _USE_ZLIB_ */


} // namespace OR

#endif /* #ifndef _OR_ZIP_H_ */


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