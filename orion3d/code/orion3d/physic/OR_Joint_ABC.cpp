/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Joint_ABC.cpp
 *  \brief Definition of class \c OR_Joint_ABC
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Joint_ABC.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Joint_ABC.h"

#ifndef OR_USE_INLINE
	    #include "OR_Joint_ABC.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC constructor
 *
 *  \param  RB1 first rigid body
 *  \param  RB2 second rigid body
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Joint_ABC::OR_Joint_ABC(OR_RigidBody& RB1, OR_RigidBody& RB2)
:	OR_SmartCounter(),
	pJacobian_	( NULL ),
	pBody1_		( &RB1 ),
	pBody2_		( &RB2 )
{
	Block1_.SetMatrix( Matrix1_ );
	Block2_.SetMatrix( Matrix2_ );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC constructor
 *
 *  \author Gabriel Peyré 2001-10-30
 *
 *	Sould only be used by automatic serialization process.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Joint_ABC::OR_Joint_ABC()
:	OR_SmartCounter(),
	pJacobian_	( NULL ),
	pBody1_		( NULL ),
	pBody2_		( NULL )
{
	Block1_.SetMatrix( Matrix1_ );
	Block2_.SetMatrix( Matrix2_ );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Joint_ABC destructor
 *
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
OR_Joint_ABC::~OR_Joint_ABC()
{
	/** remove the blocks from the jacobian matrix */
	pJacobian_->RemoveBlock( Block1_ );
	pJacobian_->RemoveBlock( Block2_ );
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

