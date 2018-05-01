
/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_LUA_String.h
 *  \brief  Definition of class \c OR_LUA_String
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _OR_LUA_STRING_H_
#define _OR_LUA_STRING_H_

#include "OR_LUA_Config.h"
#include "OR_LUAVariable_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_LUA_String
 *  \brief  A String value.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 *
 *  Helper to retrieve a value from LUA.
 */ 
/*------------------------------------------------------------------------------*/

class OR_LUA_String:		public OR_LUAVariable_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    OR_LUA_String(const char* aName);
    virtual ~OR_LUA_String();
    //@}

	//-------------------------------------------------------------------------
    /** \name Overloaded */
    //-------------------------------------------------------------------------
    //@{
	virtual void GetFromLUA(OR_WrapperLUA& LUAWrapper);
	virtual void SetToLUA(OR_WrapperLUA& LUAWrapper);
    //@}

	//-------------------------------------------------------------------------
    /** \name Accessors. */
    //-------------------------------------------------------------------------
    //@{
	void SetValue(const string& rVal);
	const string& GetValue();
    //@}

	//-------------------------------------------------------------------------
    /** \name Stack manipulation helpers. */
    //-------------------------------------------------------------------------
    //@{
	virtual void GetFromLUAStack(OR_WrapperLUA& LUAWrapper);
	virtual T_LUA_Type GetType();
	virtual void SetToLUAStack(OR_WrapperLUA& LUAWrapper);
    //@}

private:

	std::string rVal_;

};

} // End namespace OR


#endif // _OR_LUA_STRING_H_


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
