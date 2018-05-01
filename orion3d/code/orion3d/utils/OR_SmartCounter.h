
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SmartCounter.h
 *  \brief Definition of class \c OR_SmartCounter
 *  \author Gabriel Peyré 2001-09-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SmartCounter_h_
#define __OR_SmartCounter_h_

#include "../configuration/OR_Config.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SmartCounter
 *  \brief  A smart reference counter.
 *  \author Gabriel Peyré 2001-09-12
 *  
 *	Each object that want to use reference management must inherit from this class.
 *
 *	Each time an external object wants to use the object for some period, it should call :
 *	\code
 *	MyObject->UseIt();
 *	\endcode
 *	When the external object stop using this object, it must call :
 *	\code 
 *	MyObject->ReleaseIt();
 *	if( MyObject->NoLongerUsed() )
 *		OR_DELETE( MyObject );
 *	\endcode
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_SmartCounter
{

public:

    OR_SmartCounter();
    OR_SmartCounter( const OR_SmartCounter& Dup );
    OR_SmartCounter& operator=( const OR_SmartCounter& Dup );
    virtual ~OR_SmartCounter();

    //-------------------------------------------------------------------------
    /** \name memory management */
    //-------------------------------------------------------------------------
    //@{
	void UseIt();
	void ReleaseIt();
	bool NoLongerUsed();
	OR_I32 GetReferenceCounter();
    //@}

    //-------------------------------------------------------------------------
    /** \name helper */
    //-------------------------------------------------------------------------
    //@{
	static OR_Bool CheckAndDelete(OR_SmartCounter* pCounter);
    //@}
	
private:
	
	//-------------------------------------------------------------------------
    /** \name memory management */
    //-------------------------------------------------------------------------
    //@{
	OR_I32 nReferenceCounter_;
    //@}

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_SmartCounter.inl"
#endif


#endif // __OR_SmartCounter_h_

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

