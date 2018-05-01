
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellCallStack.h
 *  \brief Definition of class \c OR_ShellCallStack
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ShellCallStack_h_
#define __OR_ShellCallStack_h_

#include "../configuration/OR_Config.h"
#include "../wrapper_lua/OR_WrapperLUA.h"
#include "OR_ShellFuncDecl.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ShellCallStack
 *  \brief  Just a wrapper for the LUA call stack.
 *  \author Gabriel Peyré 2001-11-17
 *  
 *	This is the basic type that is passed to every function that a shell object
 *	can implements. It contains both :  
 *		- the argument(s) of the function.
 *		- the return value(s). 
 *
 *	This class provide useful method for access some functions arguments 
 *	that have been put in the stack.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_ShellCallStack
{

public:

    OR_ShellCallStack(lua_State& pState);
    virtual ~OR_ShellCallStack();

    //-------------------------------------------------------------------------
    /** \name helper methods */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool AccessArgumentFloat(OR_Float& val, OR_U32 nPlace);
	OR_Bool AccessArgumentBool(OR_Bool& val, OR_U32 nPlace);
	OR_Bool AccessArgumentUserData(OR_UserData& val, OR_U32 nPlace);
	OR_Bool AccessArgumentString(OR_String& val, OR_U32 nPlace);
	OR_Bool AccessArgumentFunc(T_ShellFunc& val, OR_U32 nPlace);
	OR_Bool AccessArgumentU32(OR_U32& val, OR_U32 nPlace);
	OR_Bool AccessArgumentI32(OR_I32& val, OR_U32 nPlace);
	OR_Bool AccessArgumentVector2D(OR_Vector2D& val, OR_U32 nPlace);
	OR_Bool AccessArgumentVector3D(OR_Vector3D& val, OR_U32 nPlace);
	OR_Bool AccessArgumentVector4D(OR_Vector4D& val, OR_U32 nPlace);
	OR_Bool AccessArgumentMatrix3x3(OR_Matrix3x3& val, OR_U32 nPlace);
	OR_Bool AccessArgumentMatrix4x4(OR_Matrix4x4& val, OR_U32 nPlace);
	OR_Bool AccessArgumentQuaternion(OR_Quaternion& val, OR_U32 nPlace);

	void ReturnValueFloat(const OR_Float& val);
	void ReturnValueBool(const OR_Bool& val);
	void ReturnValueUserData(const OR_UserData& val);
	void ReturnValueString(const OR_String& val);
	void ReturnValueFunc(const T_ShellFunc& val);
	void ReturnValueU32(const OR_U32& val);
	void ReturnValueI32(const OR_I32& val);
	void ReturnValueVector2D(const OR_Vector2D& val);
	void ReturnValueVector3D(const OR_Vector3D& val);
	void ReturnValueVector4D(const OR_Vector4D& val);
	void ReturnValueMatrix3x3(const OR_Matrix3x3& val);
	void ReturnValueMatrix4x4(const OR_Matrix4x4& val);
	void ReturnValueQuaternion(const OR_Quaternion& val);

	OR_U32 GetNbrArg();
	lua_State* GetState();
    //@}


private:

	lua_State* pState_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ShellCallStack.inl"
#endif


#endif // __OR_ShellCallStack_h_

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

