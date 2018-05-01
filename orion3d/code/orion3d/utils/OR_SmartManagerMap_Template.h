
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SmartManagerMap_Template.h
 *  \brief Definition of class \c OR_SmartManagerMap_Template
 *  \author Gabriel Peyré 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SmartManagerMap_Template_h_
#define __OR_SmartManagerMap_Template_h_

#include "../configuration/OR_Config.h"
#include "../utils/OR_ManagerMap_Template.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SmartManagerMap_Template
 *  \brief  A manager of object that can use smart memory management.
 *  \author Gabriel Peyré 2001-10-29
 *  
 *	The objects that this manager can use must inherit from \c OR_SmartCounter.
 */ 
/*------------------------------------------------------------------------------*/

template<class T>
class ORION3D_API OR_SmartManagerMap_Template: public OR_ManagerMap_Template<T>
{

public:

    //-------------------------------------------------------------------------
    /** \name overloaded methods that use smart memory management */
    //-------------------------------------------------------------------------
    //@{
	/** destructor : delete the object only if it is no longer in used */
	~OR_SmartManagerMap_Template()
	{
		/* delete each element in the list */
		for( IT_ManagerMap_Template(T) it=begin(); it!=end(); ++it )
		{
			T* pObj = (*it).second;
			pObj->ReleaseIt();
			
			if( pObj->NoLongerUsed() )
			{
				OR_DELETE( pObj );
			}
			/*else
			{
				OR_Globals::MessageHandler()->Warning("OR_SmartManagerMap_Template::~OR_SmartManagerMap_Template",
					"Can't delete object because still used elsewhere.");
			}*/
			
		}
		
		/* clear the map */
		MyMap_.clear();
	}

	
	/** overload the \c AddElement method from class \c OR_ManagerMap_Template */
	virtual OR_I32 AddElement(T* pNewElement)
	{
		/* declare that we use this object */
		pNewElement->UseIt();
		
		return OR_ManagerMap_Template<T>::AddElement( pNewElement );
	}

	/** remove the objects that are no longer used */
	void RemoveUnusedObjects()
	{
		IT_ManagerMap_Template(T) it=begin(); 
		while( it!=end() ) 
		{
			T* pObj = (*it).second;
			
			/* delete it only if we no more use it */
			if( pObj->GetReferenceCounter()==1 )
			{
				pObj->ReleaseIt();
				if(it==SelectedElement_)
					SelectedElement_=begin();
				
				it = MyMap_.erase(it);
				
				OR_DELETE( pObj );
			}
			else
			{
				++it;
			}
		}
	}

	/** delete an element 
		\return OR_OK if the element was removed, OR_ERROR otherwise */
	OR_RETURN_CODE DeleteElement(OR_I32 numero)
	{
		IT_ManagerMap_Template(T) it = MyMap_.find(numero);
		if( it!=end() )
		{
			T* pObj = MyMap_[numero];
			pObj->ReleaseIt();
			if( pObj->NoLongerUsed() )
			{
				OR_DELETE( pObj );
			}
			/*else
			{
				OR_Globals::MessageHandler()->Warning("OR_SmartManagerMap_Template::DeleteElement",
					"Can't delete object because still used elsewhere.");
			}*/

			if( SelectedElement_==it ) 
				SelectedElement_=begin();
			MyMap_.erase(it);
			
			return OR_OK;
		}
		return OR_ERROR;
	}

	/** delete the selected element.
		the the selected element become the first one
		\return OR_OK if the element was removed, OR_ERROR otherwise */
	OR_RETURN_CODE DeleteElement()
	{
		if( SelectedElement_==end() )
			return OR_ERROR;

		T* pObj = (*SelectedElement_).second;
		pObj->ReleaseIt();
		if( pObj->NoLongerUsed() )
		{
			OR_DELETE( pObj );
		}
		/*else
		{
			OR_Globals::MessageHandler()->Warning("OR_SmartManagerMap_Template::DeleteElement",
				"Can't delete object because still used elsewhere.");
		}*/

		IT_ManagerMap_Template(T) it = MyMap_.erase(SelectedElement_);
		SelectedElement_=begin();

		if( it!=end() ) 
			return OR_OK;
		else 
			return OR_ERROR;
	}
	
	/** remove and DELETE all elements from the manager */
	void DeleteAll()
	{
		for(IT_ManagerMap_Template(T) it=begin(); it!=end(); ++it)
		{
			T* pObj = (*it).second;
			pObj->ReleaseIt();
			if( pObj->NoLongerUsed() )
			{
				OR_DELETE( pObj );
			}
			/*
			else
			{
				OR_Globals::MessageHandler()->Warning("OR_SmartManagerMap_Template::DeleteAll",
					"Can't delete object because still used elsewhere.");
			}*/
		}
		
		SelectedElement_=begin();
		MyMap_.clear();
	}

	


	/** Remove an element in the manager.
		If the element is no longer used, then delete it.
		If the element to remove was the seleced element, then selected element is set to first element.

		\return OR_OK if the element was successfuly removed, OR_ERROR otherwise */
	OR_RETURN_CODE RemoveElement(T* pObj)
	{
		for(IT_ManagerMap_Template(T) it=begin(); it!=end(); ++it)
		{
			if( (*it).second==pObj )
			{
				if(it==SelectedElement_)
					SelectedElement_=begin();
				
				pObj->ReleaseIt();
				if( pObj->NoLongerUsed() )
				{
					OR_DELETE( pObj );
				}
				/*else
				{
					OR_Globals::MessageHandler()->Warning("OR_SmartManagerMap_Template::RemoveElement",
						"Can't delete object because still used elsewhere.");
				}*/

				MyMap_.erase(it);
				return OR_OK;
			}
		}
		return OR_ERROR;
	}

    //@}

};

} // End namespace OR


#endif // __OR_SmartManagerMap_Template_h_

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

