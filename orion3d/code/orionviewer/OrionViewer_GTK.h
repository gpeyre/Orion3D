/*---------------------------------------------------------------------------*/
/*                         OrionViewer_GTK.h                                 */
/*---------------------------------------------------------------------------*/
/* defines some cool windows for Orionviewer when using GTK+ for output.     */
/*---------------------------------------------------------------------------*/

/** \file
	defines some cool windows for Orionviewer when using GTK+ for output.
	\author Gabriel
*/

#pragma once
#ifndef _ORIONVIEWER_GTK_H_
#define _ORIONVIEWER_GTK_H_
#ifdef _USE_GTK_

#include "../Orion3D/OR_Config.h"

/* Create an Arrow widget with the specified parameters
 * and pack it into a button */
GtkWidget *create_arrow_button( GtkArrowType  arrow_type,
				GtkShadowType shadow_type );
/* Create a Button Box with the specified parameters */
GtkWidget *create_menu_h1( gint  horizontal,
                        char *title,
                        gint  spacing,
                        gint  child_w,
                        gint  child_h,
                        gint  layout);
/* Create a Button Box with the specified parameters */
GtkWidget *create_menu_v1(gint  horizontal,
                        char *title,
                        gint  spacing,
                        gint  child_w,
                        gint  child_h,
                        gint  layout);	
/* Create a Button Box with the specified parameters */
GtkWidget *create_menu_v2(gint  horizontal,
                        char *title,
                        gint  spacing,
                        gint  child_w,
                        gint  child_h,
                        gint  layout);
/** Create a list of verical buttons */
GtkWidget *create_menu_v3(gint  horizontal,
                        char *title,
                        gint  spacing,
                        gint  child_w,
                        gint  child_h,
                        gint  layout);

void CreateGTKWindows();


#endif /* #ifdef _USE_GTK_ */
#endif /* # ifndef _ORIONVIEWER_GTK_H_ */
 

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                           END  OF FILE	                                 //
///////////////////////////////////////////////////////////////////////////////