/*---------------------------------------------------------------------*/
/*                           OR_Fog.cpp                                */
/*---------------------------------------------------------------------*/
/*            implementation de la classe OR_Fog                       */            
/*---------------------------------------------------------------------*/
/* Gabriel Peyre - nikopol0@club-internet.fr                           */
/*---------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Fog.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Fog.h"

namespace OR
{
	
/*----------------------------------------------------------------------*/
/*                                 classe OR_Fog                        */
/*----------------------------------------------------------------------*/
/*       permet de creer et de gerer un brouillard                      */       
/*----------------------------------------------------------------------*/

void OR_Fog::Creat(OR_Float start,OR_Float end,OR_Float density,OR_Float color[4])
{
    Type=GL_LINEAR;
    Start=start;
    End=end;
    Density=density;
    for(OR_I32 i=0; i<=3; i++)
        Color[i]=color[i];
    glFogi (GL_FOG_MODE, (long)Type);
    glFogfv (GL_FOG_COLOR, Color);
    glFogf (GL_FOG_DENSITY, Density);
    glHint (GL_FOG_HINT, GL_DONT_CARE);
    glFogf (GL_FOG_START, Start);
    glFogf (GL_FOG_END, End);
}

void OR_Fog::Enable()
{
    glEnable(GL_FOG);
    glClearColor(Color[0], Color[1], Color[2], Color[3]);
}

void OR_Fog::Disable()
{
    glDisable(GL_FOG);
	 // retablir la couleur de fond = noir
    glClearColor(0, 0, 0, 1); 
}

void OR_Fog::ToggleType()
{
    switch (Type) {
        case GL_LINEAR :
            Type = GL_EXP;
            break;
        case GL_EXP :
            Type = GL_EXP2;
            break;
        case GL_EXP2 :
            Type = GL_LINEAR;
            break;
        }
    glFogi (GL_FOG_MODE, (long)Type);
}

OR_Bool OR_Fog::Toggle()
{
    if ( glIsEnabled(GL_FOG)==GL_TRUE )
        Disable();
    else
        Enable();
	return ( glIsEnabled(GL_FOG)==GL_TRUE );
}

void OR_Fog::ModDensity(OR_Float val)
{
    Density = val;
}

void OR_Fog::ModColor(OR_Coord_RVBA component, OR_Float val)
{
    Color[component] = val;
    glFogfv(GL_FOG_COLOR, Color);
    if ( glIsEnabled(GL_FOG)==GL_TRUE )   // remise › jour
        glClearColor(Color[0], Color[1], Color[2], Color[3]);
}

void OR_Fog::ModColor(OR_Float vect[3])
{
	for (OR_I32 i=0; i<=2; i++)
		Color[i] = vect[i];
    glFogfv(GL_FOG_COLOR, Color);
    if ( glIsEnabled(GL_FOG)==GL_TRUE )   // remise › jour
        glClearColor(Color[0], Color[1], Color[2], Color[3]);
}

/*------------------------------------------------------------------------------*/
// Name : OR_Fog::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Fog::BuildFromFile( OR_File& file )
{
}



/*------------------------------------------------------------------------------*/
// Name : OR_Fog::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Fog::BuildToFile( OR_File& file )
{
}

} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////