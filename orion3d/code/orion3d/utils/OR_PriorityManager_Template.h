
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PriorityManager_Template.h
 *  \brief definition of OR_PriorityManager_Template
 *  \author Gabriel Peyré 2001-07-19
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_PriorityManager_Template_h_
#define __OR_PriorityManager_Template_h_

#include "../configuration/OR_Config.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_PiorityManagerElt_Template
 *  \brief  an element of a OR_PriorityManager_Template
 *  \author Gabriel Peyré 2001-07-19
 *  
 */ 
/*------------------------------------------------------------------------------*/

template<class T>
class OR_PiorityManagerElt_Template
{
public:
	/** constructor */
	OR_PiorityManagerElt_Template(T* element, OR_PiorityManagerElt_Template<T>* son, OR_I32 prio, OR_I32 number)
	{
		Son=son;
		Priority=prio;
		Element=element;
		Number=number;
	}
	OR_PiorityManagerElt_Template(T* element)
	{
		Son=NULL;
		Priority=0;
		Element=element;
		Number=0;
	}
	OR_PiorityManagerElt_Template(void)
	{
		Son=NULL;
		Priority=0;
		Element=NULL;
		Number=0;
	}
	/** destructor */
	virtual ~OR_PiorityManagerElt_Template()
	{
		OR_DELETE(Son);
		OR_DELETE(Element);
	}
	
	/** the element */
	T* Element;
	/** the next element in the list */
	OR_PiorityManagerElt_Template* Son;
	/** the priority of the element */
	OR_I32 Priority;
	/** the number of the element */
	OR_I32 Number;
};


/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_PriorityManager_Template
 *  \brief  chained list using priority to store the element 
 *  \author Gabriel Peyré 2001-07-19
 *  
 */ 
/*------------------------------------------------------------------------------*/

template<class T>
class OR_PiorityManager_Template
{
private:
	typedef void (*OR_Iterator_Func)(T*);
	/** used to give a unique number to each element of the manager */
	OR_I32 UniqueId;
public:
	/** Root of the tree */
	OR_PiorityManagerElt_Template<T> *Root;
	/** selected node of the tree */
	OR_PiorityManagerElt_Template<T> *EltSelected;
	
	/** number of elements */
	OR_I32 NbElements;
	
	/** constructor */
	OR_PiorityManager_Template()
	{
		UniqueId=0;
		NbElements=0;
		Root=NULL;
		EltSelected=NULL;
	}
	/** destructor */
	virtual ~OR_PiorityManager_Template()
	{
		OR_DELETE(Root);
		EltSelected=NULL;
	}
	
	/** add an element, return the number */
	OR_I32 AddElement(T* NouvElt, OR_I32 prio)
	{
		if (Root!=NULL)
		{
			/* select the place of the element given the priority */
			OR_PiorityManagerElt_Template<T> *e=Root;
			OR_PiorityManagerElt_Template<T> *e_father=Root;
			while (e!=NULL && e->Priority>prio) 
			{
				e_father=e;
				e=e->Son;
			}
			if (e!=Root)
			{
				OR_PiorityManagerElt_Template<T> *new_elt=new OR_PiorityManagerElt_Template<T>(NouvElt, e, prio, UniqueId);
				e_father->Son=new_elt;
			}
			else
			{
				Root=new OR_PiorityManagerElt_Template<T>(NouvElt, Root, prio, UniqueId);
			}
			UniqueId++;
			NbElements++;
			return UniqueId-1;
		}
		else
		{
			Root=new OR_PiorityManagerElt_Template<T>(NouvElt, NULL, prio, UniqueId);
			UniqueId++;
			NbElements++;
			return Root->Number;
		}
	}
	/** delete an element */
	OR_I32 DeleteElement(OR_I32 numero)
	{
		OR_PiorityManagerElt_Template<T> *e=Root;
		OR_PiorityManagerElt_Template<T> *e_father=Root;
		while (e!=NULL && e->Number!=numero) 
		{
			e_father=e;
			e=e->Son;
		}
		
		if (e!=NULL && e->Number==numero)
		{
			OR_DELETE(e->Element);
			/* re-affect the childs */
			if (e_father!=e)
				e_father->Son=e->Son;
			else
				Root=e->Son;
			/* delete the element */
			e->Son=NULL;
			OR_DELETE(e);
			NbElements--;
		}
		return numero;
	}
	/** delete the first element */
	OR_I32 DeleteElement()
	{
		OR_PiorityManagerElt_Template<T> *e=Root;
		OR_PiorityManagerElt_Template<T> *e_father=Root;
		while (e!=NULL && e!=EltSelected) 
		{
			e_father=e;
			e=e->Son;
		}
		
		if (e!=NULL && e==EltSelected)
		{
			OR_DELETE(e->Element);
			/* re-affect the childs */
			if (e_father!=e)
				e_father->Son=e->Son;
			else
				Root=e->Son;
			/* delete the element */
			e->Son=NULL;
			OR_DELETE(e);
			NbElements--;
		}
		/* TODO : modifier l'element selectionné */
		return EltSelected->Number;
	}
	/* search for an element given its number **/
	T* SearchElement(OR_I32 numero)
	{
		OR_PiorityManagerElt_Template<T> *e=Root;
		while (e!=NULL && e->Number!=numero) e=e->Son;
		if (e->Number==numero) return e->Element;
		else return NULL;
	}
	/** select an element given its number */
	OR_I32 Select(OR_I32 numero)
	{
		OR_PiorityManagerElt_Template<T> *e=Root;
		while (e!=NULL && e->Number!=numero) e=e->Son;
		if (e->Number==numero) EltSelected=e;
		return EltSelected->Number;
	}
	/** select next object and return its number */
	OR_I32 SelectNext()
	{
		if (EltSelected==NULL)
		{
			EltSelected=Root;
			if (Root==NULL) return -1;
		}
		EltSelected=EltSelected->Son;
		if (EltSelected==NULL) EltSelected=Root;
		return EltSelected->Number;
	}
	/** select the root */
	OR_I32 SelectRoot()
	{
		EltSelected=Root;
		return EltSelected->Number;
	}
	/** return the number of elements */
	OR_I32 GetNbElements()
	{
		return NbElements;
	}
	/** return the number of the elt selected */
	OR_I32 GetNumElementSelected()
	{
		if (EltSelected==NULL) return -1;
		return EltSelected->Number;
	}
	/** return the element selected */
	T* GetElementSelected()
	{
		return EltSelected->Element;
	}
	/** change the priority of selected element */
	OR_I32 ChangePriority(OR_I32 prio)
	{
		OR_PiorityManagerElt_Template<T> *e=Root;
		OR_PiorityManagerElt_Template<T> *f=Root;
		while (e!=NULL && e!=EltSelected) 
		{
			f=e;
			e=e->Son;
		}
		
		if (e!=NULL && e==EltSelected)
		{
			e->Priority=prio;
			/* re-affect the childs */
			if (f!=e)
				f->Son=e->Son;
			else
				Root=e->Son;
			/* re-place the element */
			f=Root;		
			while (f!=NULL && f->Priority>prio) f=f->Son;
			e->Son=f->Son;
			f->Son=e;
		}
		return EltSelected->Number;
	}
	/** apply a function on each non empty node */
	void Iterator(OR_Iterator_Func f)
	{
		OR_PiorityManagerElt_Template<T> *e=Root;
		while (e!=NULL)
		{
			f(e->Element);
			e=e->Son;
		}
	}
	/** return true if  EltSelected->Element==NULL */
	OR_Bool IsSelectedEmpty()
	{
		return (EltSelected==NULL);
	}
};

} // End namespace OR

#endif // __OR_PriorityManager_Template_h_

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

