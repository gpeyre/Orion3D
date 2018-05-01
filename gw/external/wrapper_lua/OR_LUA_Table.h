
/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_LUA_Table.h
 *  \brief  Definition of class \c OR_LUA_Table
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _OR_LUA_TABLE_H_
#define _OR_LUA_TABLE_H_

#include "OR_LUA_Config.h"
#include "OR_LUAVariable_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** \name a map of OR_Variable */
/*------------------------------------------------------------------------------*/
//@{
typedef std::map<std::string, OR_LUAVariable_ABC*> T_LUAVariableMap;
typedef T_LUAVariableMap::iterator IT_LUAVariableMap;
typedef T_LUAVariableMap::reverse_iterator RIT_LUAVariableMap;
typedef T_LUAVariableMap::const_iterator CIT_LUAVariableMap;
typedef T_LUAVariableMap::const_reverse_iterator CRIT_LUAVariableMap;
//@}

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_LUA_Table
 *  \brief  A Table value.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 *
 *  Helper to retrieve a value from LUA.
 */ 
/*------------------------------------------------------------------------------*/
class OR_LUA_Table:		public OR_LUAVariable_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    OR_LUA_Table(const char* aName);
    virtual ~OR_LUA_Table();
    //@}

	//-------------------------------------------------------------------------
    /** \name Overloaded */
    //-------------------------------------------------------------------------
    //@{
	virtual void GetFromLUA(OR_WrapperLUA& LUAWrapper);
	virtual void SetToLUA(OR_WrapperLUA& LUAWrapper);
    //@}
		
	//-------------------------------------------------------------------------
    /** \name Stack manipulation helpers. */
    //-------------------------------------------------------------------------
    //@{
	virtual void GetFromLUAStack(OR_WrapperLUA& LUAWrapper);
	virtual T_LUA_Type GetType();
	virtual void SetToLUAStack(OR_WrapperLUA& LUAWrapper);
    //@}

    //-------------------------------------------------------------------------
    /** \name Direct acess to base type members. */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool GetValue( const string& name, OR_Float& res );
	OR_Bool GetValue( const string& name, string& res );
    //@}

	T_LUAVariableMap& GetTable();

private:

	T_LUAVariableMap Map_;

};

} // End namespace OR


#endif // _OR_LUA_TABLE_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré & Antoine Bouthors
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
