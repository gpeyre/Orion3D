
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ObjectManager.h
 *  \brief Definition of class \c OR_ObjectManager
 *  \author Gabriel Peyré 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ObjectManager_h_
#define __OR_ObjectManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Object.h"
#include "../utils/OR_SmartManagerMap_Template.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Object
 *  \brief  A manager of OR_Object
 *  \author Backchiche 2001-08-04
 *  
 *	Define interesting function to search for an object given it's name.
 */ 
/*------------------------------------------------------------------------------*/
template<class T>
class ORION3D_API OR_Manager_Template_Object: public OR_SmartManagerMap_Template<T>
{

public:

	/** search for an element given its name */
	virtual T* GetElement( const char *name )
	{
		for(IT_ManagerMap_Template(T) it=begin(); it!=end(); ++it)
		{
			T* pObj = (*it).second;				
			if ( pObj->GetName().equals( name ) )
			{
				return pObj;
			}
		}
		return NULL;
	}


    //-------------------------------------------------------------------------
    /** \name activity management */
    //-------------------------------------------------------------------------
    //@{
	/** is the objet active */
	virtual OR_Bool GetActivity()
	{
		if (IsSelectedEmpty()) return false;
		return GetElementSelected()->IsActive();
	}
	/** disable the object for rendering
		\return previous activity */
	virtual OR_I32 Disable()			
	{
		if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
		return GetElementSelected()->Disable();
	}
	/** enable the object for rendering
		\return previous activity */
	virtual OR_I32 Enable()
	{
		if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
		return GetElementSelected()->Enable();
	}
	/** toggle on/off the object for rendering 
		\return previous activity */
	virtual OR_Bool Toggle()
	{
		if (IsSelectedEmpty()) return false;
		return GetElementSelected()->Toggle();
	}
	/** get the real type of the object */
	OR_Elements GetType()
	{
		if (IsSelectedEmpty()) return OR_UNDEFINED;
		return GetElementSelected()->GetType();
	}
    //@}


    //-------------------------------------------------------------------------
    /** \name position management */
    //-------------------------------------------------------------------------
    //@{
	/** translate the object in local axes given a direction */
	OR_RETURN_CODE Translate(OR_Coord_XYZW axe, OR_Float val)
	{
		if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
		GetElementSelected()->Translate(axe, val);
		return OR_OK;
	}
	/** translate the object in local axes */
	OR_RETURN_CODE Translate(OR_Vector3D vect)
	{
		if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
		GetElementSelected()->Translate(vect);
		return OR_OK;
	}
	/** positionnate the object in local axes */
	OR_RETURN_CODE Posit(OR_Vector3D pos)
	{
		if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
		GetElementSelected()->Posit(pos);
		return OR_OK;
	}
	/** virtual method : rotate the object on its axe */
	OR_RETURN_CODE Rotate(OR_Float val)
	{
		if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
		GetElementSelected()->Rotate(val);
		return OR_OK;
	}
    //@}

	//-------------------------------------------------------------------------
    /** \name Physic management */
    //-------------------------------------------------------------------------
    //@{
	/** Get the rigid body used to compute physics */
	OR_RigidBody* GetRigidBody()
	{
		if (IsSelectedEmpty()) return NULL;
		return GetElementSelected()->GetRigidBody();
	}
	/** Set the rigid body used to compute physics */
	OR_RETURN_CODE SetRigidBody(OR_RigidBody& RB)
	{
		if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
		GetElementSelected()->SetRigidBody(RB);
		return OR_OK;
	}
    //@}

	/**
		Usefull function : return a string for each element in the list.
		[used by the shell to automaticaly build a list of name for the sub-directories]
	*/
	OR_String GetUniqueString(IT_ManagerMap_Template(T) itIterator)
	{
		for( IT_ManagerMap_Template(T) it = this->begin(); it!=this->end(); ++it )
		{
			if( it==itIterator )
			{
				/* the element has been found */
				return (*it).second->GetName();
			}
		}
		/* oups, the object has not been found */
		OR_Globals::MessageHandler()->Warning("OR_Manager_Template_Object::GetUniqueString", "The object doesn't belong to the manager.");

		return OR_String("not_found");
	}

};

} // End namespace OR



#endif // __OR_ObjectManager_h_

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

