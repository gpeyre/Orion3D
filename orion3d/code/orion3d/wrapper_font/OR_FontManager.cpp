/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_FontManager.cpp
 *  \brief Definition of class \c OR_FontManager
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_FontManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_FontManager.h"

#ifndef OR_USE_INLINE
	#include "OR_FontManager.inl"
#endif

using namespace OR;

OR_FontManager::OR_FontManager()
{
	nNextId_=0;
	SelectedElement_=MyMap_.begin();
}
OR_FontManager::~OR_FontManager()
{
	/* delete each element in the list */
	for( IT_FontMap it=MyMap_.begin(); it!=MyMap_.end(); ++it )
	{
		OR_Font_ABC* pObj = (*it).second;
		pObj->ReleaseIt();

		if( pObj->NoLongerUsed() )
		{
			OR_DELETE( pObj );
		}
	}
	
	/* clear the map */
	MyMap_.clear();
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_FontManager::Draw
 *
 *  \author Gabriel Peyré 2001-11-13
 *
 *	Draw each font for wich a font has been specified.
 */ 
/*------------------------------------------------------------------------------*/
void OR_FontManager::Draw()
{
	for(IT_FontMap it=MyMap_.begin(); it!=MyMap_.end(); ++it)
		(*it).second->Draw();
}

/** add an element, return the number. select the element just added. */
OR_I32 OR_FontManager::AddElement(OR_Font_ABC* pNewElement)
{
	/* declare that we use this object */
	pNewElement->UseIt();

	OR_ASSERT( pNewElement!=NULL );
	MyMap_[nNextId_] = pNewElement;
	OR_I32 nSvg = nNextId_;
	nNextId_++;
	/* select the new element */
	IT_FontMap it=MyMap_.find(nSvg);
	if( it!=MyMap_.end() ) 
		SelectedElement_=it;
	return nSvg;
}


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

