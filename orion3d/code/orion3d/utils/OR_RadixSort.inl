/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_IDStack.inl
 *  \brief Inlined methods for \c OR_IDStack
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_RadixSort.h"

namespace OR {

/** Access to results. mIndices is a list of indices in sorted order, i.e. in the order you may further process your data */
	OR_INLINE OR_U32* OR_RadixSort::GetIndices() const
{ 
	return mIndices;		
}

/** mIndices2 gets trashed on calling the sort routine, but otherwise you can recycle it the way you want. */
OR_INLINE OR_U32* OR_RadixSort::GetRecyclable() const
{ 
	return mIndices2;		
}

/** Returns the total number of calls to the radix sorter. */
OR_INLINE OR_U32 OR_RadixSort::GetNbTotalCalls() const
{ 
	return mTotalCalls;	
}

/** Returns the number of premature exits due to temporal coherence. */
OR_INLINE OR_U32 OR_RadixSort::GetNbHits() const	
{ 
	return mNbHits;		
}


} // End namespace OR

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