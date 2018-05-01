/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PushSpringConstraint.inl
 *  \brief Inlined methods of class OR_PushSpringConstraint
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#include "OR_PushSpringConstraint.h"

namespace OR {


//-----------------------------------------------------------------------------
// Name: OR_PushSpringConstraint constructor
/**
*   @param  rStiffness_ the strenght of the spring 
*   @param  rLength size of the spring at rest
*   @param  pTarget1 fisrt target of the constraint
*   @param  pTarget2 second target of the constraint
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_PushSpringConstraint::OR_PushSpringConstraint(OR_Float rStiffness_, OR_Float rLength,
												   OR_Particule* pTarget1,
												   OR_Particule* pTarget2)
:OR_SpringConstraint(rStiffness_, rLength, pTarget1, pTarget2)
{
}


//-----------------------------------------------------------------------------
// Name: OR_PushSpringConstraint destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_PushSpringConstraint::~OR_PushSpringConstraint()
{
}






} // End namespace OR
