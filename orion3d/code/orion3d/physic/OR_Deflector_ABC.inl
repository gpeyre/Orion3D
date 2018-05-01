//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_Deflector_ABC.h"

namespace OR {


//-----------------------------------------------------------------------------
// Name: OR_Deflector_ABC constructor
/**
*   @param  rBounce the bounce of the surface
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Deflector_ABC::OR_Deflector_ABC(OR_Float rBounce)
{
	rBounce_=rBounce;
}


//-----------------------------------------------------------------------------
// Name: OR_Deflector_ABC destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Deflector_ABC::~OR_Deflector_ABC()
{
}


//-----------------------------------------------------------------------------
// Name: OR_Deflector_ABC::GetDeflectingBounce
/**
*   @return the bounce of the surface
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_Deflector_ABC::GetDeflectingBounce()
{
	return rBounce_;
}


//-----------------------------------------------------------------------------
// Name: OR_Deflector_ABC::SetDeflectingBounce
/**
*   @return the new bounce of the surface
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Deflector_ABC::SetDeflectingBounce(OR_Float rBounce)
{
	rBounce_=rBounce;
}



} // End namespace OR
