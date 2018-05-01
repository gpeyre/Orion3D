
/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_LUAVariable_ABC.h
 *  \brief  Definition of class \c OR_LUAVariable_ABC
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _OR_LUAVARIABLE_ABC_H_
#define _OR_LUAVARIABLE_ABC_H_

#include "OR_LUA_Config.h"
#include "OR_WrapperLUA.h"

namespace OR {

class OR_WrapperLUA;

enum T_LUA_Type
{
	OR_LUA_FLOAT,
	OR_LUA_STRING,
	OR_LUA_ARRAY,
	OR_LUA_TABLE,
	OR_LUA_UNDEFINED
};

#ifdef OR_DEBUG 
	#define OR_LUA_CHECK_STACK_START(pState)	OR_U32 nLUA_Stack_Top = lua_gettop(pState)
	#define OR_LUA_CHECK_STACK_END(pState)	OR_ASSERT( nLUA_Stack_Top == lua_gettop(pState) );	
#else
	#define OR_LUA_CHECK_STACK_START(pState)
	#define OR_LUA_CHECK_STACK_END
#endif	// OR_DEBUG 




/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_LUAVariable_ABC
 *  \brief  Base class for all LUA wrapping variables.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 *
 *  Manage a link between the C++ variable and LUA.
 */ 
/*------------------------------------------------------------------------------*/

class OR_LUAVariable_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    OR_LUAVariable_ABC(const char* aName);
    virtual ~OR_LUAVariable_ABC();
    //@}

    //-------------------------------------------------------------------------
    /** \name To overload. */
    //-------------------------------------------------------------------------
    //@{
	virtual void GetFromLUA(OR_WrapperLUA& LUAWrapper) = 0;
	virtual void SetToLUA(OR_WrapperLUA& LUAWrapper) = 0;
    //@}

	OR_Bool GetError();

    //-------------------------------------------------------------------------
    /** \name Helpers methods. */
    //-------------------------------------------------------------------------
    //@{
	static T_LUA_Type GetTopStackType(OR_WrapperLUA& LUAWrapper);
    //@}


    //-------------------------------------------------------------------------
    /** \name Stack manipulation helpers. */
    //-------------------------------------------------------------------------
    //@{
	virtual void GetFromLUAStack(OR_WrapperLUA& LUAWrapper) = 0;
	virtual void SetToLUAStack(OR_WrapperLUA& LUAWrapper) = 0;
	virtual T_LUA_Type GetType() = 0;
    //@}

protected:

	/** the LUA name of the variable. */
	string Name_;
	/** set to \c true if an error occrued while proccessing the variable to/from LUA */
	OR_Bool bError_;

};


} // End namespace OR

#endif // _OR_LUAVARIABLE_ABC_H_


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
