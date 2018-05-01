/*------------------------------------------------------------------------------
 *  \file  OR_AnimationManager.cpp
 *  \brief 	Contains the definition of a manager of animation
 *  \author Gabriel Peyré 2001-07-08
 *------------------------------------------------------------------------------*/


#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Animation.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_AnimationManager.h"

namespace OR
{

/*------------------------------------------------------------------------------*/
// Name : OR_Animation::OR_AnimationManager
/** 
 *  \param  bIsOwned Does the manager destroy it's elements when the destructor is called ?
 *  \author Gabriel Peyré 2001-08-15
 */ 
/*------------------------------------------------------------------------------*/
OR_AnimationManager::OR_AnimationManager(OR_Bool bIsOwned)
:	OR_ManagerMap_Template<OR_Animation>(bIsOwned)
{
	/* NOTHING */
}


void OR_AnimationManager::BuildFromFile( OR_File& file )
{
	/* read the number of animation */
	OR_U32 nb_anims;
	file >> nb_anims;

	/* export the differents animations */
	for (OR_U32 i=0; i<nb_anims; i++)
	{
		OR_Animation* anim=new OR_Animation();
		file >> anim;
		
		/* add the animation to the manager */
		this->AddElement(anim);
	}	
}

void OR_AnimationManager::BuildToFile( OR_File& file )
{
	/* write the number of animatios */
	OR_U32 nb=GetNbElements();
	file << nb;

	/* iterate on each animation */
	for( IT_ManagerMap_Template(OR_Animation) it=begin(); it!=end(); ++it )
		file << (*it).second;
}

void OR_AnimationManager::BuildToFile(OR_File file, OR_Node* HierarchyRoot, OR_Node* SelectedNode)
{
	/* write the number of animatios */
	OR_U32 nb=GetNbElements();
	file << nb;

	/* export each animation */
	for(IT_ManagerMap_Template(OR_Animation) it=begin(); it!=end(); ++it)
	{
		(*it).second->BuildToFile(file, HierarchyRoot, SelectedNode);
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationManager::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 *
 *	Should be overloaded by complex shaders.
 */ 
/*------------------------------------------------------------------------------*/
void OR_AnimationManager::BuildSonList(T_ShellObjectList& ShellSonList)
{
	OR_SHELL_BUILD_MANAGER_SON_LIST( ShellSonList, OR_Animation, "animation" );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_AnimationManager::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_AnimationManager::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	/* NOTHING */
}

} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                           END OF FILE                                     //
///////////////////////////////////////////////////////////////////////////////