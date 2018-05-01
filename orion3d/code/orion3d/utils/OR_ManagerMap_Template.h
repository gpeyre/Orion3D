
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ManagerMap_Template.h
 *  \brief definition of class OR_ManagerMap_Template.
 *  \author Gabriel Peyré 2001-07-19
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ManagerMap_Template_h_
#define __OR_ManagerMap_Template_h_

#include "../configuration/OR_Config.h"
#include "../utils/OR_ClassFactory.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ManagerMap_Template
 *  \brief  A manager of objects.
 *  \author Gabriel Peyré 2001-07-19
 *  
 *	Use a map to make a correspondance between objects and unic IDs.
 */ 
/*------------------------------------------------------------------------------*/


#define T_ManagerMap_Template(T)    map<OR_I32, T*>
#define IT_ManagerMap_Template(T)   T_ManagerMap_Template(T)::iterator
#define CIT_ManagerMap_Template(T)  T_ManagerMap_Template(T)::const_iterator
#define RIT_ManagerMap_Template(T)  T_ManagerMap_Template(T)::reverse_iterator
#define CRIT_ManagerMap_Template(T) T_ManagerMap_Template(T)::const_reverse_iterator

template<class T>
class ORION3D_API OR_ManagerMap_Template
{	

public:

	/** constructor */
	OR_ManagerMap_Template(OR_Bool bOwnedObjects=true)
	{
		bOwnedObjects_ = bOwnedObjects;
		nNextId_=0;
		SelectedElement_=MyMap_.begin();
	}
	/** destructor */
	~OR_ManagerMap_Template()
	{
		if( bOwnedObjects_ )
		{
			/* delete each element in the list */
			for(IT_ManagerMap_Template(T) it=begin(); it!=end(); ++it)
				OR_DELETE( (*it).second );
		}
		/* clear the map */
		MyMap_.clear();
	}
	
	/** add an element, return the number. select the element just added. */
	virtual OR_I32 AddElement(T* pNewElement)
	{
		OR_ASSERT( pNewElement!=NULL );
		MyMap_[nNextId_] = pNewElement;
		OR_I32 nSvg = nNextId_;
		nNextId_++;
		/* select the new element */
		IT_ManagerMap_Template(T) it=MyMap_.find(nSvg);
		if( it!=MyMap_.end() ) 
			SelectedElement_=it;
		return nSvg;
	}
	/** delete an element 
		\return OR_OK if the element was removed, OR_ERROR otherwise */
	OR_RETURN_CODE DeleteElement(OR_I32 numero)
	{
		IT_ManagerMap_Template(T) it = MyMap_.find(numero);
		if( it!=end() )
		{
			OR_DELETE(MyMap_[numero]);
			
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
		OR_DELETE((*SelectedElement_).second);
		IT_ManagerMap_Template(T) it=MyMap_.erase(SelectedElement_);
		SelectedElement_=begin();
		if(it!=end()) return OR_OK;
		else return OR_ERROR;
	}
	/** remove and DELETE all elements from the manager */
	void DeleteAll()
	{
		for(IT_ManagerMap_Template(T) it=begin(); it!=end(); ++it)
			OR_DELETE((*it).second);
		MyMap_.clear();
	}
	/** remove (not delete !!) an element in the manager.
		if the element to remove was the seleced element, then selected element is set to first element
		\return OR_OK if the element was successfuly removed, OR_ERROR otherwise */
	OR_RETURN_CODE RemoveElement(T* element)
	{
		for(IT_ManagerMap_Template(T) it=begin(); it!=end(); ++it)
		{
			if( (*it).second==element )
			{
				if(it==SelectedElement_)
					SelectedElement_=begin();
				MyMap_.erase(it);
				return OR_OK;
			}
		}
		return OR_ERROR;
	}
	/** search for an element given it's number */
	T* SearchElement(OR_I32 numero)
	{
		return MyMap_[numero];
	}
	/** does the manager contains the given element */
	OR_Bool ContainsElement(T* element)
	{
		for(IT_ManagerMap_Template(T) it=begin(); it!=end(); ++it)
		{
			if( (*it).second==element )
				return true;
		}
		return false;
	}
	/** select an element given its number.
		\return the number of the new selected element */
	OR_I32 Select(OR_I32 numero)
	{
		IT_ManagerMap_Template(T) it=MyMap_.find(numero);
		if( it!=MyMap_.end() ) 
			SelectedElement_=it;
		return (*SelectedElement_).first;
	}
	/** select next object and return its number */
	OR_RETURN_CODE SelectNext()
	{
		if( SelectedElement_==end() ) 
			SelectedElement_=MyMap_.begin();
		else
			SelectedElement_++;

		if( SelectedElement_!=end() ) 
			return (*SelectedElement_).first;
		else 
			return OR_ERROR;
	}
	/** select the root */
	void SelectFirstElement()
	{
		SelectedElement_=MyMap_.begin();
	}
	/** return the number of elements */
	OR_U32 GetNbElements()
	{
		return MyMap_.size();
	}
	/** return the element selected 
		\return NULL if no element was selected */
	T* GetElementSelected()
	{
		if(SelectedElement_==end()) return NULL;
		return (*SelectedElement_).second;
	}
	/** get the number of the selected element 
		\return OR_ERROR if no element was selected */
	OR_I32 GetNumElementSelected()
	{
		if(SelectedElement_==end()) return OR_ERROR;
		return (*SelectedElement_).first;
	}

	/** return true if  EltSelected->Element==NULL */
	OR_Bool IsSelectedEmpty()
	{
		if( SelectedElement_==MyMap_.end() ) return true;
		return ( (*SelectedElement_).second ==NULL);
	}

	/** get a begin iterator */
	IT_ManagerMap_Template(T) begin()
	{ 
		return MyMap_.begin(); 
	}
	/** get a end iterator */
	IT_ManagerMap_Template(T) end()
	{ 
		return MyMap_.end(); 
	}
	/** get a begin iterator */ 
	CIT_ManagerMap_Template( T ) begin( ) const 
	{ 
		return MyMap_.begin( ); 
	} 
	/** get a end iterator */ 
	CIT_ManagerMap_Template( T ) end( ) const 
	{ 
		return MyMap_.end( ); 
	} 

	/** get a reverse begin iterator */
	RIT_ManagerMap_Template(T) rbegin()
	{ 
		return MyMap_.rbegin(); 
	}
	/** get a reverse end iterator */
	RIT_ManagerMap_Template(T) rend()
	{ 
		return MyMap_.rend(); 
	}
	/** get a reverse begin iterator */ 
	CRIT_ManagerMap_Template( T ) rbegin( ) const 
	{ 
		return MyMap_.rbegin( ); 
	} 
	/** get a reverse end iterator */ 
	CRIT_ManagerMap_Template( T ) rend( ) const 
	{ 
		return MyMap_.rend( ); 
	} 

	/**
		Usefull function : return a string for each element in the list.
		[used by the shell to automaticaly build a list of name for the sub-directories]
	*/
	OR_String GetUniqueString(IT_ManagerMap_Template(T) itIterator)
	{
		OR_U32 nCounter = 0;
		for( IT_ManagerMap_Template(T) it = this->begin(); it!=this->end(); ++it )
		{
			if( it==itIterator )
			{
				/* the element has been found */
				return OR_String( nCounter );
			}
		}
		/* oups, the object has not been found */
		OR_Globals::MessageHandler()->Warning("OR_ManagerMap_Template::GetUniqueString", "The object doesn't belong to the manager.");

		return OR_String("not_found");
	}
	
	/*------------------------------------------------------------------------------*/
	// Name : OR_ManagerMap_Template::SerializeToFile
	/** 
	*  \param  file the file we want to export the manager to.
	*  \author Gabriel Peyré 2001-08-05
	*
	*	Export each element of the manager to a file. This element can be re-loade using 
	*	SerializeToFile.
	*/ 
	/*------------------------------------------------------------------------------*/
	void SerializeToFile(OR_File& file)
	{
		OR_I32 nNumElt = GetNbElements();
		file << nNumElt;
		for( IT_ManagerMap_Template(T) it=begin(); it!=end(); ++it )
			OR_ClassFactory::BuildToFile(  file, (OR_Serializable &) *(*it).second  );
	}

	/*------------------------------------------------------------------------------*/
	// Name : OR_ManagerMap_Template::SerializeFromFile
	/** 
	*  \param  file the file we want to import the manager from.
	*  \author Gabriel Peyré 2001-08-05
	*
	*	import each element of the manager from a file. This supposed the manager had been exported
	*	using SerializeToFile.
	*/ 
	/*------------------------------------------------------------------------------*/
	void SerializeFromFile(OR_File& file)
	{
		OR_I32 nNumElt;
		file >> nNumElt;
		for( OR_I32 i=0; i<nNumElt; ++i )
			this->AddElement( (T*) &OR_ClassFactory::BuildFromFile(file)  );
	}

protected:
	
	/** this is the STL map that serve of base for the OR_Manager */
	T_ManagerMap_Template(T) MyMap_;
	/** this is to give each time a new ID */
	OR_I32 nNextId_;
	/** this is the selected element */
	IT_ManagerMap_Template(T) SelectedElement_;
	
	/** are the element owned by the manager */
	OR_Bool bOwnedObjects_;

};

} // End namespace OR




#endif // __OR_ManagerMap_Template_h_

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

