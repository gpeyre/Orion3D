/*---------------------------------------------------------------------*/
/*                         OR_List_Template.h                           */
/*---------------------------------------------------------------------*/
/* standard data structures used by Orion3D (list, tree ...)           */            
/*---------------------------------------------------------------------*/

/** \file 
	Contains the definition of standard templates class [chained list, manager ...].
	\author Gabriel.
**/

#ifndef _OR_LIST_TEMPLATE_H_
#define _OR_LIST_TEMPLATE_H_

#include "../configuration/OR_Config.h"

using namespace std;

namespace OR
{

/*---------------------------------------------------------------------*/
/*                        class OR_ListElt_Template                    */
/*---------------------------------------------------------------------*/
/*		a template of a list element								   */            
/*---------------------------------------------------------------------*/

/*! \ingroup group_template
 *  \brief class OR_ListElt_Template in group group_template
 */

/// A single element of a chained list.
/** A classic chained list element, used every where ...
	\author Gabriel
*/
template<class T>
class OR_ListElt_Template
{
public:
	/** constructor */
	OR_ListElt_Template(T* element, OR_ListElt_Template* son)
	{
		Element=element;
		Son=son;
	}
	OR_ListElt_Template(T* element)
	{
		Element=element;
		Son=NULL;
	}
	OR_ListElt_Template(void)
	{
		Element=NULL;
		Son=NULL;
	}

	/** destructor */
	virtual ~OR_ListElt_Template()
	{
		OR_DELETE(Element);
		OR_DELETE(Son);
	}

	/** return the number of element in the list (including itself) */
	OR_I32 GetNbElement()
	{
		OR_I32 i=0;
		OR_ListElt_Template<T> *e=this;
	
		while (e!=NULL)
		{
			i++;
			e=e->Son;
		}
		return i;
	}

	/** get the last element of the list */
	OR_ListElt_Template<T>* GetLastElement()
	{
		OR_ListElt_Template<T> *e=this;
		while (e->Son!=NULL) e=e->Son;
		return e;
	}
	/** get the before last element of the list */
	OR_ListElt_Template<T>* GetBeforeLastElement()
	{
		if (this->Son==NULL) return NULL;
		OR_ListElt_Template<T> *e=this;
		while (e->Son->Son!=NULL) e=e->Son;
		return e;
	}

	T* Element;
	/** the son of the node */
	OR_ListElt_Template* Son;
};


} // namespace OR

#endif // _OR_LIST_TEMPLATE_H_


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