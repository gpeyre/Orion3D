
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ClassFactory.h
 *  \brief Definition of class OR_ClassFactory
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ClassFactory_h_
#define __OR_ClassFactory_h_

#include "../configuration/OR_Config.h"
#include "OR_Serializable.h"
#include "OR_MsgException.h"


namespace OR {

typedef map<OR_String, T_CreateInstance_Function> T_ClassFactoryMap;
typedef T_ClassFactoryMap::iterator IT_ClassFactoryMap;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ClassFactory
 *  \brief  A class factory.
 *  \author Gabriel Peyré 2001-08-05
 *  A class factory can create object of classderivating from class OR_Serializable
 *	given the name of the class. This is very usefull for serialization process.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_ClassFactory
{

public:

	//-------------------------------------------------------------------------
    /** \name creation methods */
    //-------------------------------------------------------------------------
    //@{
	static OR_Serializable& CreateInstance(OR_String& ClassName) OR_THROW(OR_MsgException);
    //@}

    //-------------------------------------------------------------------------
    /** \name file serialization methods */
    //-------------------------------------------------------------------------
    //@{
	static OR_Serializable& BuildFromFile(OR_File& file);
	static void             BuildToFile(OR_File& file, OR_Serializable& obj);
    //@}

	//-------------------------------------------------------------------------
    /** \name registration methods */
    //-------------------------------------------------------------------------
    //@{
	static void RegisterClass(OR_String ClassName, T_CreateInstance_Function CreateInstanceFunc) OR_THROW(OR_MsgException);
	static void RegisterAllClass();
    //@}



private:

	static T_ClassFactoryMap Map_;

};

#define OR_REGISTER_CLASS(class)  OR_ClassFactory::RegisterClass(OR_String(#class), class::CreateInstance)

} // End namespace OR


#endif // __OR_ClassFactory_h_

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

