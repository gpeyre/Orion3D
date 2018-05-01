
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Exception_ABC.h
 *  \brief Definition of class OR_Exception_ABC
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Exception_ABC_h_
#define __OR_Exception_ABC_h_

#include "../configuration/OR_Config.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Exception_ABC
 *  \brief  base class for Orion3D exceptions.
 *  \author Gabriel Peyré 2001-08-04
 *  A excption has to overide the print message to print a message on a stream.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Exception_ABC
{

public:

	virtual void Print()=0;

};

} // End namespace OR


#endif // __OR_Exception_ABC_h_

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

