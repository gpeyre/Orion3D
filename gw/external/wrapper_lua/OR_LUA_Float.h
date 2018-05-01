
/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_LUA_Float.h
 *  \brief  Definition of class \c OR_LUA_Float
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _OR_LUA_FLOAT_H_
#define _OR_LUA_FLOAT_H_

#include "OR_LUA_Config.h"
#include "OR_LUAVariable_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_LUA_Float
 *  \brief  A Float value.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 *
 *  Helper to retrieve a value from LUA.
 */ 
/*------------------------------------------------------------------------------*/

class OR_LUA_Float:		public OR_LUAVariable_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    OR_LUA_Float(const char* aName);
    virtual ~OR_LUA_Float();
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
	void SetValue(OR_Float rVal);
	OR_Float GetValue();
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

	OR_Float rVal_;

};

} // End namespace OR


#endif // _OR_LUA_FLOAT_H_


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
