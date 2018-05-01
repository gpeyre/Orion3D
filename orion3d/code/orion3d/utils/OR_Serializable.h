/*-------------------------------------------------------------------*/
/*                           OR_Serializable.h                       */
/*-------------------------------------------------------------------*/
/* created on 11:5:2001   2:13                                       */
/*-------------------------------------------------------------------*/

/** \file 
	Contains definition of a class for each object that want to be 
	exported/imported to a krd/act file.
	\author Gabriel.
**/

#ifndef _OR_SERIALIZABLE_H_
#define _OR_SERIALIZABLE_H_

#include "../configuration/OR_Config.h"

namespace OR
{

//-------------------------------------------------------------------------
/** \name serialization macros */
//-------------------------------------------------------------------------
//@{
/** defines and implement GetClassName and GetClassName for a normal class */
#define OR_DEFINE_SERIALIZATION(class)									\
	OR_String GetClassName() { return OR_String( #class ); }			\
	static OR_Serializable& CreateInstance() { return *(new class); }	\
	OR_Serializable* Clone() const { return new class( *this ); }
/** defines and implement GetClassName and GetClassName for a template class */
#define OR_DEFINE_SERIALIZATION_TEMPLATE(class, T)						\
	OR_String GetClassName() { return OR_String( #class ); }			\
	static OR_Serializable& CreateInstance() { return *(new class<T>); }\
	OR_Serializable* Clone() const { return (new class<T>( *this ) ); }
//@}

typedef class OR_Serializable& (*T_CreateInstance_Function)(void);
/*------------------------------------------------------------*/
/*                    classe OR_Serializable                  */
/*------------------------------------------------------------*/
/* an interface for serializable objects                      */
/*------------------------------------------------------------*/

/// an interface for serializable objects.
/** 
	A class for each object that want to be 
	exported/imported to a krd/act file.
	\author Gabriel
*/
class ORION3D_API OR_Serializable
{
public:
	/** import the data from an opened file to the object */
	virtual void BuildFromFile(class OR_File& file)=0;
	/** export the data from the object to an opened file */
	virtual void BuildToFile(class OR_File& file)=0;
	/** get the name of the class, usefull for the class factory */
	virtual class OR_String GetClassName()=0;
	/** duplicate the class : it's a virtual copy constructor */
	virtual OR_Serializable* Clone() const = 0;
};


} // namespace OR

#endif /* #ifndef _OR_SERIALIZABLE_H_ */

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
