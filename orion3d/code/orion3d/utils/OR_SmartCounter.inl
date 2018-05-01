/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SmartCounter.inl
 *  \brief Inlined methods for \c OR_SmartCounter
 *  \author Gabriel Peyré 2001-09-12
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_SmartCounter.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SmartCounter constructor
 *
 *  \author Gabriel Peyré 2001-09-12
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SmartCounter::OR_SmartCounter()
:	nReferenceCounter_	( 0 )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------
 * Name : OR_SmartCounter constructor
 *
 *  \param  Dup EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-24
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_SmartCounter::OR_SmartCounter( const OR_SmartCounter& Dup )
:	nReferenceCounter_(0)
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------
 * Name : OR_SmartCounter::operator
 *
 *  \param  Dup EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-24
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_SmartCounter& OR_SmartCounter::operator=( const OR_SmartCounter& Dup )
{
	nReferenceCounter_ = 0;
	return (*this);
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SmartCounter destructor
 *
 *  \author Gabriel Peyré 2001-09-12
 *
 *	Check that nobody is still using the object.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SmartCounter::~OR_SmartCounter()
{
	OR_ASSERT( nReferenceCounter_==0 );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SmartCounter::UseIt
 *
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Declare that we use this object. We must call \c ReleaseIt when we no longer use this object.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_SmartCounter::UseIt()
{
	nReferenceCounter_++;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SmartCounter::ReleaseIt
 *
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Declare that we no longer use this object.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_SmartCounter::ReleaseIt()
{
	nReferenceCounter_--;
	OR_ASSERT( nReferenceCounter_>=0 );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SmartCounter::NoLongerUsed
 *
 *  \return true if no one use this object anymore.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	We can delete the object only if \c NoLongerUsed return true.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
bool OR_SmartCounter::NoLongerUsed()
{
	OR_ASSERT( nReferenceCounter_>=0 );
	return nReferenceCounter_==0;
}



/*------------------------------------------------------------------------------
 * Name : OR_SmartCounter::GetReferenceCounter
 *
 *  \return the value of the reference counter
 *  \author Antoine Bouthors 2001-11-30
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_I32 OR_SmartCounter::GetReferenceCounter()
{
	return nReferenceCounter_;
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

