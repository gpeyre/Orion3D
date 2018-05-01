/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_FontManager.h
 *  \brief Definition of class \c OR_FontManager
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_FontManager_h_
#define __OR_FontManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Font_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_FontManager
 *  \brief  Manager of fonts.
 *  \author Gabriel Peyré 2001-11-13 
 */ 
/*------------------------------------------------------------------------------*/

class OR_FontManager
{

public:

	OR_FontManager();
	virtual ~OR_FontManager();

	OR_I32 AddElement(OR_Font_ABC* font);

	void Draw();

	OR_Font_ABC* GetElementSelected()
	{
		if( SelectedElement_==MyMap_.end() )
			return NULL;
		return (*SelectedElement_).second;
	}
	T_FontMap& GetFontMap()
	{ return MyMap_; }

private:

	/** the next Id to assign */
	OR_I32 nNextId_;
	/** the map of fonts */
	T_FontMap MyMap_;
	/** the selected element */
	IT_FontMap SelectedElement_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_FontManager.inl"
#endif


#endif // __OR_FontManager_h_

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

