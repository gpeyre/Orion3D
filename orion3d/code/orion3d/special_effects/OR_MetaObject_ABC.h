/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaObject_ABC.h
 *  \brief Definition of class \c OR_MetaObject_ABC
 *  \author Gabriel Peyré 2002/04/14
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_MetaObject_ABC_h_
#define __OR_MetaObject_ABC_h_


#include "../configuration/OR_Config.h"

namespace OR {

class OR_MetaGrid;

typedef OR_Float (*T_MetaFunction)(OR_Float dist);

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MetaObject_ABC
 *  \brief  AddCommentHere
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	A meta-object must be able to add it's value to the meta-grid.
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_MetaObject_ABC
{
public:

	OR_MetaObject_ABC();

    //-------------------------------------------------------------------------
    /** \name Grid management */
    //-------------------------------------------------------------------------
    //@{
	virtual void AddMetaValue(OR_MetaGrid& grid) = 0;
	//@}

	void SetMetaFunction( T_MetaFunction pMetaFunc );

	/** blobby function : should be 1 when dist=0, and 0 when dist>1 */
	static OR_Float	Default_MetaFunction(OR_Float dist)
	{
		if( dist<1 )
			return (dist - 1)*(dist - 1);
		else 
			return 0;
	}

protected:

	/** the function used to compute the meta-values */
	T_MetaFunction pMetaFunc_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
	#include "OR_MetaObject_ABC.inl"
#endif

#endif // __OR_MetaObject_ABC_h_

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

