/*-------------------------------------------------------------------------------------*/
/*                                OR_Archive.h                                         */
/*-------------------------------------------------------------------------------------*/
/* defines a class to work with Zip archive.                                           */
/*-------------------------------------------------------------------------------------*/

/** \file 
	defines a class to work with Zip archive.
	\author Gabriel.
**/

#ifndef _OR_ARCHIVE_H_
#define _OR_ARCHIVE_H_

#include "../configuration/OR_Config.h"
#include "OR_Zip.h"
#include "OR_StrVector.h"
#include "../misc/OR_System.h"

namespace OR
{
	
#ifdef _USE_ZLIB_

/*-------------------------------------------------------------------------------------*/
/*                             class OR_Archive                                        */
/*-------------------------------------------------------------------------------------*/
/* a class to handle a zip archive.                                                    */
/*-------------------------------------------------------------------------------------*/

/// a class to handle a zip archive.
/**
	This class can be used to work with standard ZIP archives.
	Constructor accepts a file name - if such a file is not found, it is
	created. After this you can examine archive directory, read files,
	delete or write files in archive.
	
	Operations which changes archive file will be deferred until Flush()
	method is called. Before calling Flush() you can do any number of
	deletions and writes, but read operations will not be affected by
	these until Flush() will be called.
*/

class ORION3D_API OR_Archive
{
public:
	static char hdr_central[4];
	static char hdr_local[4];
	static char hdr_endcentral[4];
	static char hdr_extlocal[4];
private:
	/** OR_Archive entry class */
	class ArchiveEntry
	{
	public:
	    char *filename;
		ZIP_central_directory_file_header info;
		char *buffer;
		size_t buffer_pos;
		size_t buffer_size;
		char *extrafield, *comment;

		ArchiveEntry (const char *name, ZIP_central_directory_file_header &cdfh);
		virtual ~ArchiveEntry ();
		OR_Bool Append (const void *data, size_t size);
		OR_Bool WriteLFH (FILE *file);
		OR_Bool WriteCDFH (FILE *file);
		OR_Bool ReadExtraField (FILE *file, size_t extra_field_length);
		OR_Bool ReadFileComment (FILE *file, size_t file_comment_length);
		OR_Bool WriteFile (FILE *file);
		void FreeBuffer ();
	};
	
	friend class ArchiveEntry;

	/** A vector of ArchiveEntries */
	class ArchiveEntryVector : public OR_Vector_Template<ArchiveEntry*>
	{
	public:
		ArchiveEntryVector () : OR_Vector_Template<ArchiveEntry*>(256, 256) {}
		virtual ~ArchiveEntryVector () 
		{ 
			DeleteAll (); 
		}
		virtual OR_Bool FreeItem (ArchiveEntry* Item)
		{ 
			OR_DELETE(Item);
			return true; 
		}
		virtual OR_I32 Compare (ArchiveEntry* Item1, ArchiveEntry* Item2, OR_I32 /*Mode*/) const
		{ 
			return strcmp (Item1->filename, Item2->filename); 
		}
		virtual OR_I32 CompareKey (ArchiveEntry* Item, void* Key, OR_I32 /*Mode*/) const
		{ 
			return strcmp (Item->filename, (char *)Key); 
		}
		ArchiveEntry* Get (OR_I32 n) const
		{ 
			return OR_Vector_Template<ArchiveEntry*>::Get(n); 
		}
	};

	/** Archive directory: chain head (sorted) */
	ArchiveEntryVector dir;
	/** The array of files that should be deleted (sorted) */
	OR_StrVector del;
	/** The array of lazy operations (unsorted) */
	ArchiveEntryVector lazy;

	/** Archive file name */
	char *filename;
	/** Archive file pointer. */
	FILE *file;

	/** Archive comment length */
	size_t comment_length;
	/** Archive comment */
	char *comment;

	void ReadDirectory ();
	OR_Bool IsDeleted (const char *name) const;
	void UnpackTime (unsigned short zdate, ush ztime, OR_FileTime &rtime) const;
	void PackTime (const OR_FileTime &ztime, unsigned short &rdate, unsigned short &rtime) const;
	OR_Bool ReadArchiveComment (FILE *file, size_t zipfile_comment_length);
	void LoadECDR (ZIP_end_central_dir_record &ecdr, char *buff);
	OR_Bool ReadCDFH (ZIP_central_directory_file_header &cdfh, FILE *file);
	OR_Bool ReadLFH (ZIP_local_file_header &lfh, FILE *file);
	OR_Bool WriteECDR (ZIP_end_central_dir_record &ecdr, FILE *file);
	OR_Bool WriteZipArchive ();
	OR_Bool WriteCentralDirectory (FILE *temp);
	void UpdateDirectory ();
	void ReadZipDirectory (FILE *infile);
	ArchiveEntry *InsertEntry (const char *name, ZIP_central_directory_file_header &cdfh);
	void ReadZipEntries (FILE *infile);
	char *ReadEntry (FILE *infile, ArchiveEntry *f);

public:
	/** Open the archive. */
	OR_Archive (const char *filename);
	/** Close the archive. */
	virtual ~OR_Archive ();
	
	/** Type a directory listing of the archive to the console. */
	void Dir () const;

	/**
		Create a new file in the archive. If the file already exists
		it will be overwritten. Calling NewFile twice with same filename
		without calling Flush() inbetween will cause unpredictable results.
		
		Returns NULL if not succesful. Otherwise it returns a pointer
		that can be passed to 'Write' routine. You won't see any changes
		to archive until 'Flush' will be called.
		
		'size' is the _advisory_ file size. There is no problem if you will
		write more or less bytes, its just a matter of performance - if you
		set the right size, archive manager will have to allocate memory
		only once; however if you set size to zero and then write all the
		data in one call, it will have same performance.
	*/
	void *NewFile (const char *name, size_t size = 0, OR_Bool pack = true);

	/**
		Delete a file from the archive. You won't see any changes
		to archive until 'Flush' will be called.
	*/
	OR_Bool DeleteFile (const char *name);

	/**
		Return true if a file exists. Also return the
		size of the file if needed.
	*/
	OR_Bool FileExists (const char *name, size_t *size = NULL) const;

	/**
		Read a file completely. After finishing with the returned
		data you need to 'delete[]' it. If the file does not exists
		this function returns NULL. If "size" is not null, it is set
		to unpacked size of the file.
	*/
	char *Read (const char *name, size_t *size = NULL);

	/**
		Write data to a file. Note that 'size' need not be
		the overall file size if this was given in 'NewFile',
		but this function will fail if the total size of written
		data exceeds the maximum size given to 'NewFile'.
	*/
	OR_Bool Write (void *entry, const char *data, size_t size);

	/**
		Execute all pending operations involving writes to archive
		Neither DeleteFile or NewFile will have effect until this
		function will be called. Returns false if operation failed.
		If operation failed, postponed operations remains in the
		same state as before calling Flush(), i.e. for example
		user can be prompted to free some space on drive then retry
		Flush().
	*/
	OR_Bool Flush ();

	/** Get Nth file in archive or NULL */
	void *GetFile (OR_I32 no)
	{ 
		return (no >= 0) && (no < dir.GetLength()) ? dir.Get (no) : NULL; 
	}

	/** Find a file in archive; returns a handle or NULL */
	void *FindName (const char *name) const;
	/** Query name from handle */
	char *GetFileName (void *entry) const
	{ 
		return ((ArchiveEntry*)entry)->filename; 
	}
	/** Query file size from handle */
	size_t GetFileSize (void *entry) const
	{ 
		return ((ArchiveEntry*)entry)->info.ucsize; 
	}
	/** Query filetime from handle */
	void GetFileTime (void *entry, OR_FileTime &ztime) const;
	/** Set filetime for handle*/
	void SetFileTime (void *entry, const OR_FileTime &ztime);

	/** Query archive filename */
	char *GetName () const
	{ 
		return filename; 
	}
	/** Query archive comment */
	char *GetComment () const
	{ 
		return comment; 
	}
};

inline 
void OR_Archive::GetFileTime (void* entry, OR_FileTime &ztime) const
{
  if (entry)
  {
    UnpackTime (((ArchiveEntry*)entry)->info.last_mod_file_date,
                ((ArchiveEntry*)entry)->info.last_mod_file_time,
                ztime);
  }
}

inline
void OR_Archive::SetFileTime (void* entry, const OR_FileTime &ztime)
{
  if (entry)
  {
    PackTime (ztime,
              ((ArchiveEntry*)entry)->info.last_mod_file_date,
              ((ArchiveEntry*)entry)->info.last_mod_file_time);
  }
}


#endif /* #ifdef _USE_ZLIB_ */

} // namespace OR

#endif /* #ifndef _OR_ARCHIVE_H_ */


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