
/*------------------------------------------------------------------------------*/
/** 
 *  \file   OR_LUA_Array.h
 *  \brief  Definition of class \c OR_LUA_Array
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _OR_LUA_ARRAY_H_
#define _OR_LUA_ARRAY_H_

#include "OR_LUA_Config.h"
#include "OR_LUA_String.h"
#include "OR_LUAVariable_ABC.h"
#include "OR_LUA_Float.h"
#include "OR_LUA_Table.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** \name a vector of OR_LUAVariable_ABC */
/*------------------------------------------------------------------------------*/
//@{
typedef std::vector<class OR_LUAVariable_ABC*> T_LUAVariableVector;
typedef T_LUAVariableVector::iterator IT_LUAVariableVector;
typedef T_LUAVariableVector::reverse_iterator RIT_LUAVariableVector;
typedef T_LUAVariableVector::const_iterator CIT_LUAVariableVector;
typedef T_LUAVariableVector::const_reverse_iterator CRIT_LUAVariableVector;
//@}

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_LUA_Array
 *  \brief  A Array value.
 *  \author Gabriel Peyré
 *  \date   11-17-2002
 *
 *  Helper to retrieve a value from LUA.
 */ 
/*------------------------------------------------------------------------------*/

class OR_LUA_Array:		public OR_LUAVariable_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    OR_LUA_Array(const char* aName);
    virtual ~OR_LUA_Array();
    //@}

	//-------------------------------------------------------------------------
    /** \name Overloaded */
    //-------------------------------------------------------------------------
    //@{
	virtual void GetFromLUA(OR_WrapperLUA& LUAWrapper);
	virtual void SetToLUA(OR_WrapperLUA& LUAWrapper);
    //@}

	T_LUAVariableVector& GetArray();

	//-------------------------------------------------------------------------
    /** \name Stack manipulation helpers. */
    //-------------------------------------------------------------------------
    //@{
	virtual void GetFromLUAStack(OR_WrapperLUA& LUAWrapper);
	virtual T_LUA_Type GetType();
	virtual void SetToLUAStack(OR_WrapperLUA& LUAWrapper);
    //@}

private:

	T_LUAVariableVector VariableVector_;
	OR_U32 nSize_;

};

} // End namespace OR


#endif // _OR_LUA_ARRAY_H_


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
