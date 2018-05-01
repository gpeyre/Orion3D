
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Renderer_ABC.h
 *  \brief definition of class OR_Renderer_ABC
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Renderer_ABC_h_
#define __OR_Renderer_ABC_h_

#include "../configuration/OR_Config.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Renderer_ABC
 *  \brief  Base interface for all Orion3D renderer/
 *  \author Gabriel Peyré 2001-08-31
 * 
 *	A renderer is the object that drive the rendering process. So all it has
 *	to do is overload the method \c Draw().
 *
 *	An basic implementation is proposed in the class OR_Toolkit.
 */ 
/*------------------------------------------------------------------------------*/

class OR_Renderer_ABC
{

public:

	/** Draw all Orion3D stuff in a viewport */
	virtual void RenderToViewport(class OR_Viewport& Wiewport)=0;
	/** Global rendering stage. Should render all the viewports. */
	virtual void RenderAllViewport()=0;	
	/** reshape the window */
	virtual void Reshape(OR_I32 w,OR_I32 h)=0;
	/** update the 3D engine */
	virtual void Update()=0;
	/** initialisation of the renderer */
	virtual void InitGraphics()=0;

};

} // End namespace OR



#endif // __OR_Renderer_ABC_h_

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

