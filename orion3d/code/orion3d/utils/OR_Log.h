/*-------------------------------------------------------------------*/
/*                              OR_Log.h                             */
/*-------------------------------------------------------------------*/
/* Created : 16 Apr 2001   13h03                                     */
/*-------------------------------------------------------------------*/

/** \file
	Contains defintion to write into a log file.
	\author Gabriel
*/

#ifndef _OR_LOG_H_
#define _OR_LOG_H_

#include "../configuration/OR_Config.h"
#include "../utils/OR_ManagerMap_Template.h"
#include "../utils/OR_Serializable.h"

namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                               class OR_Log                        */
/*-------------------------------------------------------------------*/
/* Usefull class to manage a log file.                               */
/*-------------------------------------------------------------------*/

/// Usefull class to manage a log file.
/**	Contains some cool function to write into a log file.
	\author Gabriel
*/

class ORION3D_API OR_Log:	public OR_Serializable
{
private:

	/** name of the fog file */
	char Name[20];
	/** indent index */
	OR_I32 Indent;

public:

	/** constructor */
	OR_Log(char* LogName=OR_DEFAULT_LOG_NAME);

	/** add a string into the log file, using printf() usage */
	void AddString(char *string, ...);
	/** add a string into the log file, using vprintf() usage */
	void AddvString(char *string, va_list argptr);
	/** add a line of text into the log file */
	void AddLine(char *text);
	/** add date time into the log file */
	void AddTimeDate();
	/** add the OS version into the log file */
	void AddOSVersion();
	/** add the memory status into the log file */
	void AddMemorySatus();
	/** add the Orion3D configuration into the log file */
	void AddOrion3DConfiguration();
	/** add the drivers configuration into the log file */
	void AddDriversConfiguration();

	/** Increment the indent */
	void AddIndent();
	/** Decrement the indent */
	void SubIndent();
	/** Set the indent */
	void SetIndent(OR_I32 indent);
	/** \return the current indent index */
	OR_I32 GetIndent();

	//-------------------------------------------------------------------------
    /** @name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	/** macro to define class-specific function */
	OR_DEFINE_SERIALIZATION(OR_Log);
    //@}

};

/*-------------------------------------------------------------------*/
/*                         class OR_LogManager                       */
/*-------------------------------------------------------------------*/
/* a manager of log.                                                 */
/*-------------------------------------------------------------------*/

///
/**
	A manager of Log file.
	\author Gabriel
*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Log>;

class ORION3D_API OR_LogManager: public OR_ManagerMap_Template<OR_Log>
{
public:
	/** create a new log */
	OR_I32 AddLog(char* LogName=OR_DEFAULT_LOG_NAME);

	/** add a string into the log file, using printf() usage */
	OR_RETURN_CODE AddString(char *string, ...);
	/** add a string into the log file, using vprintf() usage */
	OR_RETURN_CODE AddvString(char *string, va_list argptr);
	/** add a line of text into the log file */
	OR_RETURN_CODE AddLine(char *text);
	/** add date time into the log file */
	OR_RETURN_CODE AddTimeDate();
	/** add the OS version into the log file */
	OR_RETURN_CODE AddOSVersion();
	/** add the memory status into the log file */
	OR_RETURN_CODE AddMemorySatus();
	/** add the Orion3D configuration into the log file */
	OR_RETURN_CODE AddOrion3DConfiguration();
	/** add the drivers configuration into the log file */
	OR_RETURN_CODE AddDriversConfiguration();

	/** Increment the indent */
	OR_RETURN_CODE AddIndent();
	/** Decrement the indent */
	OR_RETURN_CODE SubIndent();
	/** Set the indent */
	OR_RETURN_CODE SetIndent(OR_I32 indent);
	/** \return the current indent index */
	OR_I32 GetIndent();
};



} // namespace OR

#endif /* #ifndef _OR_LOG_H_ */


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_license.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////