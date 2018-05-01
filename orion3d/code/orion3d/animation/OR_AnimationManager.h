/*------------------------------------------------------------------------------
 *  \file  OR_AnimationManager.h
 *  \brief 	Contains the definition of a manager of animation
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/

/** \file 
	Contains definition of animation class [a tree of animation node].
	\author Gabriel.
**/

#ifndef _OR_ANIMATIONMANAGER_H_
#define _OR_ANIMATIONMANAGER_H_

#include "OR_Animation.h"
#include "../utils/OR_ManagerMap_Template.h"
#include "../utils/OR_SmartManagerMap_Template.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"

namespace OR
{

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Animation>;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_AnimationManager
 *  \brief  The manager of animations.
 *  \author Gabriel Peyré 2001-11-14
 *
 *	Contains a copy of every animation in the engine.
 *	This alow to have an easy acces to each animation.
 *
 *	\example shell_test/main.cpp
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_AnimationManager: public OR_ManagerMap_Template<OR_Animation>, public OR_Serializable, public OR_ShellObject_ABC
{

public:
	
	OR_AnimationManager(OR_Bool bIsOwned=false);

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	/** export the data from the object to an opened file
		\param SelectedNode the node of the hierarchy from which we want to begin the export */
	void BuildToFile(OR_File file, OR_Node* HierarchyRoot, OR_Node* SelectedNode);
	OR_DEFINE_SERIALIZATION(OR_AnimationManager);
    //@}	
	
	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
    //@}

	/**
		Usefull function : return a string for each element in the list.
		[used by the shell to automaticaly build a list of name for the sub-directories]
	*/
	OR_String GetUniqueString(IT_ManagerMap_Template(OR_Animation) itIterator)
	{
		for( IT_ManagerMap_Template(OR_Animation) it = this->begin(); it!=this->end(); ++it )
		{
			if( it==itIterator )
			{
				/* the element has been found */
				return (*it).second->GetName();
			}
		}
		/* oups, the object has not been found */
		OR_Globals::MessageHandler()->Warning("OR_AnimationManager::GetUniqueString", "The object doesn't belong to the manager.");

		return OR_String("not_found");
	}

};

#pragma warning( default : 4275 )  


} // namespace OR

#endif /* #ifndef _OR_ANIMATIONMANAGER_H_ */

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////
