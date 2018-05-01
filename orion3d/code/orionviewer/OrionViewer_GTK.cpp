/*---------------------------------------------------------------------------*/
/*                         OrionViewer_GTK.cpp                               */
/*---------------------------------------------------------------------------*/
/* defines some cool windows for Orionviewer when using GTK+ for output.     */
/*---------------------------------------------------------------------------*/

#include "stdafx.h"
#include "OrionViewer_GTK.h" 

/** \file
	defines some cool windows for Orionviewer when using GTK+ for output.
	\author Gabriel
*/

#ifdef _USE_GTK_

/* prototypes of callback functions *******************************************/
void PrintFPSReport();
void PrintHelp();
void quit();
void SoundSystemInfo();
void About();
int LoadKRD();
int LoadKSP();
int LoadBSP();
void ToggleSurfaceShader();
void ToggleMetaShader();
void ToggleMathsSurface();
void ToggleMetaObjects();
void ToggleParticules();
void ToggleDrawGizmo();
void ToggleDrawLight();
void ToggleDrawCamera();
void ToggleDrawLocalAxe();
void DrawNothing();
void ToggleCameraType();

/* Create an Arrow widget with the specified parameters
 * and pack it into a button */
GtkWidget *create_arrow_button( GtkArrowType  arrow_type,
				GtkShadowType shadow_type )
{
  GtkWidget *button;
  GtkWidget *arrow;

  button = gtk_button_new();
  arrow = gtk_arrow_new (arrow_type, shadow_type);

  gtk_container_add (GTK_CONTAINER (button), arrow);
  
  gtk_widget_show(button);
  gtk_widget_show(arrow);

  return(button);
}

/* Create a Button Box with the specified parameters */
GtkWidget *create_menu_h1( gint  horizontal,
                        char *title,
                        gint  spacing,
                        gint  child_w,
                        gint  child_h,
                        gint  layout)
{
  GtkWidget *frame;
  GtkWidget *bbox;
  GtkWidget *button;

  frame = gtk_frame_new (title);

  if (horizontal)
    bbox = gtk_hbutton_box_new ();
  else
    bbox = gtk_vbutton_box_new ();

  gtk_container_set_border_width (GTK_CONTAINER (bbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), bbox);

  /* Set the appearance of the Button Box */
  gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), (GtkButtonBoxStyle) layout);
  gtk_button_box_set_spacing (GTK_BUTTON_BOX (bbox), spacing);
  gtk_button_box_set_child_size (GTK_BUTTON_BOX (bbox), child_w, child_h);

  button = gtk_button_new_with_label ("Sound system infos");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(SoundSystemInfo), NULL);

    button = gtk_button_new_with_label ("FPS Report");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(PrintFPSReport), NULL);

  button = gtk_button_new_with_label ("Help !");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(PrintHelp), NULL);

  button = gtk_button_new_with_label ("Quit");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(quit), NULL);

  button = gtk_button_new_with_label ("About");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(About), NULL);

  return(frame);
}

/* Create a Button Box with the specified parameters */
GtkWidget *create_menu_v1(gint  horizontal,
                        char *title,
                        gint  spacing,
                        gint  child_w,
                        gint  child_h,
                        gint  layout)
{
  GtkWidget *frame;
  GtkWidget *bbox;
  GtkWidget *button;

  frame = gtk_frame_new (title);

  if (horizontal)
    bbox = gtk_hbutton_box_new ();
  else
    bbox = gtk_vbutton_box_new ();

  gtk_container_set_border_width (GTK_CONTAINER (bbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), bbox);

  /* Set the appearance of the Button Box */
  gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), (GtkButtonBoxStyle) layout);
  gtk_button_box_set_spacing (GTK_BUTTON_BOX (bbox), spacing);
  gtk_button_box_set_child_size (GTK_BUTTON_BOX (bbox), child_w, child_h);

  button = gtk_button_new_with_label ("Load KRD");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(LoadKRD), NULL);

  button = gtk_button_new_with_label ("Load KSP");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(LoadKSP), NULL);

   button = gtk_button_new_with_label ("Load BSP");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(LoadBSP), NULL);

  return(frame);
}
	
/* Create a Button Box with the specified parameters */
GtkWidget *create_menu_v2(gint  horizontal,
                        char *title,
                        gint  spacing,
                        gint  child_w,
                        gint  child_h,
                        gint  layout)
{
  GtkWidget *frame;
  GtkWidget *bbox;
  GtkWidget *button;

  frame = gtk_frame_new (title);

  if (horizontal)
    bbox = gtk_hbutton_box_new ();
  else
    bbox = gtk_vbutton_box_new ();

  gtk_container_set_border_width (GTK_CONTAINER (bbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), bbox);

  /* Set the appearance of the Button Box */
  gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), (GtkButtonBoxStyle) layout);
  gtk_button_box_set_spacing (GTK_BUTTON_BOX (bbox), spacing);
  gtk_button_box_set_child_size (GTK_BUTTON_BOX (bbox), child_w, child_h);

  button = gtk_button_new_with_label ("Toggle surface shader");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleSurfaceShader), NULL);

  button = gtk_button_new_with_label ("Toggle meta-object shader");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleMetaShader), NULL);

  button = gtk_button_new_with_label ("Toggle maths-surf on/off");
  gtk_container_add (GTK_CONTAINER (bbox), button);
   gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleMathsSurface), NULL);

  button = gtk_button_new_with_label ("Toggle meta-object on/off");
  gtk_container_add (GTK_CONTAINER (bbox), button);
    gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleMetaObjects), NULL);

    button = gtk_button_new_with_label ("Toggle particules on/off");
  gtk_container_add (GTK_CONTAINER (bbox), button);
    gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleParticules), NULL);

  return(frame);
}

/* Create a Button Box with the specified parameters */
GtkWidget *create_menu_v3(gint  horizontal,
                        char *title,
                        gint  spacing,
                        gint  child_w,
                        gint  child_h,
                        gint  layout)
{
  GtkWidget *frame;
  GtkWidget *bbox;
  GtkWidget *button;

  frame = gtk_frame_new (title);

  if (horizontal)
    bbox = gtk_hbutton_box_new ();
  else
    bbox = gtk_vbutton_box_new ();

  gtk_container_set_border_width (GTK_CONTAINER (bbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), bbox);

  /* Set the appearance of the Button Box */
  gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), (GtkButtonBoxStyle) layout);
  gtk_button_box_set_spacing (GTK_BUTTON_BOX (bbox), spacing);
  gtk_button_box_set_child_size (GTK_BUTTON_BOX (bbox), child_w, child_h);

  button = gtk_button_new_with_label ("Draw lights on/off");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleDrawLight), NULL);

  button = gtk_button_new_with_label ("Draw cameras on/off");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleDrawCamera), NULL);

  button = gtk_button_new_with_label ("Draw gizmos on/off");
  gtk_container_add (GTK_CONTAINER (bbox), button);
   gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleDrawGizmo), NULL);

  button = gtk_button_new_with_label ("Draw local axes on/off");
  gtk_container_add (GTK_CONTAINER (bbox), button);
    gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleDrawLocalAxe), NULL);

	button = gtk_button_new_with_label ("Draw nothing");
  gtk_container_add (GTK_CONTAINER (bbox), button);
    gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(DrawNothing), NULL);

    button = gtk_button_new_with_label ("Camera satellite/marche");
  gtk_container_add (GTK_CONTAINER (bbox), button);
    gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(ToggleCameraType), NULL);

  return(frame);
}


void CreateGTKWindows()
{
	
#ifdef _USE_GTK_
	GtkWidget* box_main=MyInputOutput->GetMainBox();
	GtkWidget* glarea=MyInputOutput->GetGlArea();
	GtkWidget* window=MyInputOutput->GetWindow();

#if 0
	/* create a quit button */
	GtkWidget* button_quit = gtk_button_new_with_label ("Quit");
	gtk_signal_connect (GTK_OBJECT(button_quit), "clicked",
                      GTK_SIGNAL_FUNC(quit), NULL);
	gtk_box_pack_start (GTK_BOX(box_main), button_quit, FALSE, TRUE, 0);
	gtk_widget_show(button_quit);
	/* create a help button */
	GtkWidget* button_help = gtk_button_new_with_label ("Help !");
	gtk_signal_connect (GTK_OBJECT(button_help), "clicked",
                      GTK_SIGNAL_FUNC(PrintHelp), NULL);
	gtk_box_pack_start (GTK_BOX(box_main), button_help, FALSE, TRUE, 0);
	gtk_widget_show(button_help);
#endif

	
#if 0
	/* Create an aspect_frame and add it to our toplevel window */
    GtkWidget *aspect_frame = gtk_aspect_frame_new ("Test Frame", /* label */
                                         0.5, /* center x */
                                         0.5, /* center y */
                                         2, /* xsize/ysize = 2 */
                                         FALSE /* ignore child's aspect */);
    gtk_container_add (GTK_CONTAINER(box_main), aspect_frame);
    gtk_widget_show (aspect_frame);
    /* Now add a child widget to the aspect frame */
    GtkWidget *drawing_area = gtk_drawing_area_new ();
    /* Ask for a 200x200 window, but the AspectFrame will give us a 200x100
     * window since we are forcing a 2x1 aspect ratio */
    gtk_widget_set_usize (drawing_area, 200, 200);
	gtk_container_add (GTK_CONTAINER(aspect_frame), drawing_area);
    gtk_widget_show(drawing_area);
#endif


	/* vertial menus */
	GtkWidget *frame_vert = gtk_frame_new ("[Menu]");
	gtk_box_pack_start (GTK_BOX (box_main), frame_vert, TRUE, TRUE, 10);
	GtkWidget *hbox = gtk_hbox_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (hbox), 10);
	gtk_container_add (GTK_CONTAINER (frame_vert), hbox);
	gtk_box_pack_start (GTK_BOX (hbox),
			create_menu_v1 (FALSE, "[Load files]", 5, 85, 20, GTK_BUTTONBOX_SPREAD),
			TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX (hbox),
			create_menu_v2 (FALSE, "[Toggle]", 5, 85, 20, GTK_BUTTONBOX_EDGE),
			TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX (hbox),
			create_menu_v3 (FALSE, "[Draw]", 5, 85, 20, GTK_BUTTONBOX_EDGE),
			TRUE, TRUE, 5);

	/* horizontal menu */
	gtk_box_pack_start (GTK_BOX (box_main),
	   create_menu_h1(TRUE, "", 40, 85, 20, GTK_BUTTONBOX_SPREAD),
		      TRUE, TRUE, 0);

#if 0
	/* create 4 arrow buttons */
	GtkWidget* button = create_arrow_button(GTK_ARROW_UP, GTK_SHADOW_IN);
	gtk_box_pack_start(GTK_BOX (box_main), button, FALSE, FALSE, 3);
	button = create_arrow_button(GTK_ARROW_DOWN, GTK_SHADOW_OUT);
	gtk_box_pack_start(GTK_BOX (box_main), button, FALSE, FALSE, 3);  
	button = create_arrow_button(GTK_ARROW_LEFT, GTK_SHADOW_ETCHED_IN);
	gtk_box_pack_start(GTK_BOX (box_main), button, FALSE, FALSE, 3);
	button = create_arrow_button(GTK_ARROW_RIGHT, GTK_SHADOW_ETCHED_OUT);
	gtk_box_pack_start(GTK_BOX (box_main), button, FALSE, FALSE, 3);
#endif
	gtk_widget_show_all (window);
	
	/* set focus to glarea widget : obligatoire pour gerer le keyboard  */
	GTK_WIDGET_SET_FLAGS(glarea, GTK_CAN_FOCUS);
	gtk_widget_grab_focus(GTK_WIDGET(glarea));
#endif // _USE_GTK_
}


#endif /* #ifdef _USE_GTK_ */
 

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
