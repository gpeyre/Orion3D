//*****************************************************************************
/// \author Gabriel Peyré
//*****************************************************************************

#ifndef __OR_ManagerList_Template_h_
#define __OR_ManagerList_Template_h_


#include "../configuration/OR_config.h"
#include "../utils/OR_ClassFactory.h"


namespace OR {

//=============================================================================
/**
*   @class  OR_ManagerList_Template
*   @brief  A manager using a list.
*
*	Generaly, manager uses Map [see OR_ManagerList_Template], but some time,
*	we don't need to provide to the used easy access via key, so we simply use
*	STL list.
*/
/// \author Gabriel Peyré
//=============================================================================

#define T_ManagerList_Template(T)    list<T*>
#define IT_ManagerList_Template(T)   T_ManagerList_Template(T)::iterator
#define RIT_ManagerList_Template(T)  T_ManagerList_Template(T)::reverse_iterator

template<class T>
class OR_ManagerList_Template
{

public:

	/*------------------------------------------------------------------------------*/
	// Name : OR_ManagerList_Template constructor
	/** 
	 *  \param  bOwnedObjects does the manager owned the elements ?
	 *  \author Gabriel Peyré 2001-08-06
	 *
	 *	If the manager owned the elements, it means they will be destroyed by the manager
	 *	when its destructor will be called.
	 */ 
	/*------------------------------------------------------------------------------*/
	OR_ManagerList_Template(OR_Bool bOwnedObjects=true)
	{ 
		bOwnedObjects_=bOwnedObjects; 
	}

	/*------------------------------------------------------------------------------*/
	// Name : OR_ManagerList_Template destructor
	/** 
	 *  \author Gabriel Peyré 2001-08-06
	 */ 
	/*------------------------------------------------------------------------------*/
	~OR_ManagerList_Template()
	{
		if( bOwnedObjects_ )
		{
			/* delete each element in the list */
			for(IT_ManagerList_Template(T) it=begin(); it!=end(); ++it)
				OR_DELETE( (*it) );
		}
		/* clear the map */
		List_.clear();
	}

	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::AddFirst
	/**
	*   @param  pElement the element to add at the beginning of the list.
	*
	*	Add an element at the begining of the list.
	*  \author Gabriel Peyré 2001-07-20
	*/
	//-----------------------------------------------------------------------------
	void AddFirst(T& element)
	{ 
		List_.push_front(&element); 
	}

	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::AddLast
	/**
	*   @param  element the element to add at the end of the list.
	*
	*	Add an element at the end of the list.
	*  \author Gabriel Peyré 2001-07-20
	*/
	//-----------------------------------------------------------------------------
	void AddLast(T& element)
	{ 
		List_.push_back(&element); 
	}

	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::AddFirst
	/**
	*   @param  pElement the element to add at the beginning of the list.
	*
	*	Add an element at the begining of the list.
	*  \author Gabriel Peyré 2001-07-20
	*/
	//-----------------------------------------------------------------------------
	void AddFirst(T* element)
	{ 
		List_.push_front(element); 
	}

	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::AddLast
	/**
	*   @param  element the element to add at the end of the list.
	*
	*	Add an element at the end of the list.
	*  \author Gabriel Peyré 2001-07-20
	*/
	//-----------------------------------------------------------------------------
	void AddLast(T* element)
	{ 
		List_.push_back(element); 
	}

	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::PopFront
	/**
	*   @return NULL if the list is empty, the first element that have been removed otherwise
	*  \author Gabriel Peyré 2001-07-20
	*/
	//-----------------------------------------------------------------------------
	T* PopFront()
	{ 
		if( List_.empty() ) return NULL;
		T* Result = Front();
		List_.pop_front();
		return Result;
	}
	
	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::PopBack
	/**
	*   @return NULL if the list is empty, the last element that have been removed otherwise
	*  \author Gabriel Peyré 2001-07-20
	*/
	//-----------------------------------------------------------------------------
	T* PopBack()
	{
		if( List_.empty() ) return NULL;
		T* Result = Back();
		List_.pop_back();
		return Result;
	}
	
	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::Remove
	/**
	*   @param  element The element to remove from the list.
	*  \author Gabriel Peyré 2001-07-20
	*/
	//-----------------------------------------------------------------------------
	void Remove(T& element)
	{
		List_.remove(&element);
	}

	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::Back
	/**
	*   @return NULL if the list is empty, the last element otherwise
	*  \author Gabriel Peyré 2001-07-20
	*/
	//-----------------------------------------------------------------------------
	T* Back()
	{
		if(List_.empty())
			return NULL;
		return List_.back();
	}

	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::Front
	/**
	*   @return NULL if the list is empty, the first element otherwise
	*  \author Gabriel Peyré 2001-07-20
	*/
	//-----------------------------------------------------------------------------
	T* Front()
	{
		if(List_.empty())
			return NULL;
		return List_.front();
	}

	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::IsEmpty
	/**
	*   @return is the list empty ?	
	*  \author Gabriel Peyré 2001-07-20
	*/
	/// \author Gabriel Peyré
	//-----------------------------------------------------------------------------
	OR_Bool IsEmpty()
	{
		return List_.empty();
	}

	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::NbrElement
	/**
	*   @return the number of elements in the manager 
	*
	*  \author Gabriel Peyré 2001-07-20
	*/
	/// \author Gabriel Peyré
	//-----------------------------------------------------------------------------
	OR_U32 NbrElements()
	{
		return List_.size();
	}

	/*------------------------------------------------------------------------------*/
	/** 
	 * Name : OR_ManagerList_Template::IT_ManagerList_Template
	 *
	 *  \return iterator on the first element
	 *  \author Gabriel Peyré 2001-07-20
	 */ 
	/*------------------------------------------------------------------------------*/
	IT_ManagerList_Template(T) begin()
	{
		return List_.begin();
	}

	/*------------------------------------------------------------------------------*/
	/** 
	 * Name : OR_ManagerList_Template::IT_ManagerList_Template
	 *
	 *  \return itrator on the last element 
	 *  \author Gabriel Peyré 2001-07-20
	 */ 
	/*------------------------------------------------------------------------------*/
	IT_ManagerList_Template(T) end()
	{
		return List_.end();
	}


	//-----------------------------------------------------------------------------
	// Name: OR_ManagerList_Template::Clear
	/**
	*
	*	Clear the list [this doesn't delete the elements].
	*/
	///	\author Gabriel Peyré 2001-08-30
	//-----------------------------------------------------------------------------
	void clear()
	{
		List_.clear();
	}

	/*------------------------------------------------------------------------------*/
	// Name : OR_ManagerList_Template::SerializeToFile
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
		OR_I32 nNumElt = NbrElements();
		file << nNumElt;
		for( IT_ManagerList_Template(T) it=begin(); it!=end(); ++it )
			OR_ClassFactory::BuildToFile(  file, *(*it)  );
	}

	/*------------------------------------------------------------------------------*/
	// Name : OR_ManagerList_Template::SerializeFromFile
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
			this->AddLast( (T*) &OR_ClassFactory::BuildFromFile(file)  );
	}


protected:

	/** the list of elements */
	T_ManagerList_Template(T) List_;
	/** are the elements owned by the manager */
	OR_Bool bOwnedObjects_;

};

} // End namespace OR



#endif // __OR_ManagerList_Template_h_
