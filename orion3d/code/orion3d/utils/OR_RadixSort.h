/**
 *	This class is a copy from Pierre Terdiman code source.
 */

#ifndef __ICERADIXSORT_H__
#define __ICERADIXSORT_H__

#include "../configuration/OR_Config.h"


namespace OR {
	
#define RADIX_LOCAL_RAM

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_RadixSort
 *  \brief  Perform a radix sort.
 *  \author Pierre Terdiman
 */ 
/*------------------------------------------------------------------------------*/


class OR_RadixSort
{

public:

	// Constructor/Destructor
	OR_RadixSort();
	~OR_RadixSort();

	// Sorting methods
	OR_RadixSort& Sort(const OR_U32* input, OR_U32 nb, OR_Bool signedvalues=true);
	OR_RadixSort& Sort(const OR_Float* input, OR_U32 nb);

	//! Access to results. mIndices is a list of indices in sorted order, i.e. in the order you may further process your data
	OR_U32* GetIndices() const;
	//! mIndices2 gets trashed on calling the sort routine, but otherwise you can recycle it the way you want.
	OR_U32* GetRecyclable() const;

	// Stats
	OR_U32 GetUsedRam() const;
	OR_U32 GetNbTotalCalls() const;
	//! Returns the number of premature exits due to temporal coherence.
	OR_U32 GetNbHits() const;

private:

#ifndef RADIX_LOCAL_RAM
	OR_U32*			mHistogram;					//!< Counters for each byte
	OR_U32*			mOffset;					//!< Offsets (nearly a cumulative distribution function)
#endif

	OR_U32			mCurrentSize;				//!< Current size of the indices list
	OR_U32			mPreviousSize;				//!< Size involved in previous call
	OR_U32*			mIndices;					//!< Two lists, swapped each pass
	OR_U32*			mIndices2;
	// Stats
	OR_U32			mTotalCalls;
	OR_U32			mNbHits;
	// Internal methods
	OR_Bool			Resize(OR_U32 nb);
	void			ResetIndices();
};


} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_RadixSort.inl"
#endif

#endif // __ICERADIXSORT_H__


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
