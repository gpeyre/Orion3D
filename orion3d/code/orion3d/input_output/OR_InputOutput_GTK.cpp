/*----------------------------------------------------------------------------*/
/*                         OR_InputOutput_GTK.cpp                             */
/*----------------------------------------------------------------------------*/
/* functions implementation for GTK in/out                                    */
/*----------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_InputOutput_GTK.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_InputOutput.h"

	
#ifdef _USE_GTK_

namespace OR
{
/*----------------------------------------------------------------------------*/
/*                              class OR_InputOutput                          */
/*----------------------------------------------------------------------------*/
/* gestion des fonction d'input/output via                                    */
/* glut ou windows                                                            */
/*----------------------------------------------------------------------------*/

/* initialize static variables */
GtkWidget* OR_InputOutput::glarea=NULL;
GtkWidget* OR_InputOutput::window=NULL;
GtkWidget* OR_InputOutput::box_main=NULL;

/* GTK specific functions ***************************************************/
void OR_InputOutput::PostReDisplay()
{
	gtk_widget_draw(GTK_WIDGET(glarea), NULL);
}

void OR_InputOutput::Swap()
{
	gtk_gl_area_swapbuffers(GTK_GL_AREA(glarea));
}

void OR_InputOutput::Initialisation(OR_I32 *argc, char **argv, char* name,
									OR_I32 size_x, OR_I32 size_y,
									OR_I32 posx, OR_I32 posy)
{	
	/* initialize gtkgl */
	SetupPixelFormat(argc, argv);
	
	/* create the glarea */
	create_glarea(size_x, size_y);

	/* Main box */
	box_main = gtk_vbox_new(FALSE, 10);

	/* Main widget container */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* set windows style */
	gtk_window_set_title(GTK_WINDOW(window), name);

	/* destroy this window when exiting from gtk_main() */
	gtk_quit_add_destroy(1, GTK_OBJECT(window));
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	/* set callback function for the windows */
	gtk_signal_connect(GTK_OBJECT(window), "delete_event",
                      GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	gtk_signal_connect(GTK_OBJECT (window), "destroy",
                      GTK_SIGNAL_FUNC(gtk_main_quit), NULL);

	/* link the widget together */
	gtk_box_pack_start(GTK_BOX(box_main), glarea,      FALSE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), box_main);

	/* shows the widget */
	gtk_widget_show(glarea);
	gtk_widget_show(box_main);
	gtk_widget_show(window);
	
	/* initialize opengl and openil */
	MyOrion->InitGraphics();
}

void OR_InputOutput::MinimumInit(OR_I32 *argc, char **argv, OR_I32 largeur, OR_I32 hteur)
{
	/* initialize gtkgl */
	SetupPixelFormat(argc, argv);
	
	/* create the glarea */
	create_glarea(largeur, hteur);
}

void OR_InputOutput::SetupPixelFormat(OR_I32 *argc, char **argv)
{
	gtk_init(argc, &argv);
}

GtkWidget* OR_InputOutput::GetMainBox()
{
	return box_main;
}

GtkWidget* OR_InputOutput::GetGlArea()
{
	return glarea;
}

GtkWidget* OR_InputOutput::GetWindow()
{
	return window;
}

GtkWidget* OR_InputOutput::create_glarea(OR_I32 size_x, OR_I32 size_y)
{  
	/* the pixel format */
	OR_I32 attrlist[]= 
	{
		GDK_GL_RGBA,
		GDK_GL_RED_SIZE,1,
		GDK_GL_GREEN_SIZE,1,
		GDK_GL_BLUE_SIZE,1,
		GDK_GL_DOUBLEBUFFER,
		GDK_GL_NONE
	};

	/*check if opengl is supported */
	if(gdk_gl_query() == FALSE) 
	{
		OR_Globals::MessageHandler()->Debug("OR_InputOutput::create_glarea", "OpenGL not supported.");
		exit(-1);
	}

	/* create the main glarea */
	if ((glarea = gtk_gl_area_new(attrlist)) == NULL) 
	{
		OR_Globals::MessageHandler()->Debug("OR_InputOutput::create_glarea", "Error creating GtkGLArea.");
		return NULL;
	}

	/*
	typedef enum
	{
	  GDK_EXPOSURE_MASK		= 1 << 1,
	  GDK_POINTER_MOTION_MASK	= 1 << 2,
	  GDK_POINTER_MOTION_HINT_MASK	= 1 << 3,
	  GDK_BUTTON_MOTION_MASK	= 1 << 4,
	  GDK_BUTTON1_MOTION_MASK	= 1 << 5,
	  GDK_BUTTON2_MOTION_MASK	= 1 << 6,
	  GDK_BUTTON3_MOTION_MASK	= 1 << 7,
	  GDK_BUTTON_PRESS_MASK		= 1 << 8,
	  GDK_BUTTON_RELEASE_MASK	= 1 << 9,
	  GDK_KEY_PRESS_MASK		= 1 << 10,
	  GDK_KEY_RELEASE_MASK		= 1 << 11,
	  GDK_ENTER_NOTIFY_MASK		= 1 << 12,
	  GDK_LEAVE_NOTIFY_MASK		= 1 << 13,
	  GDK_FOCUS_CHANGE_MASK		= 1 << 14,
	  GDK_STRUCTURE_MASK		= 1 << 15,
	  GDK_PROPERTY_CHANGE_MASK	= 1 << 16,
	  GDK_VISIBILITY_NOTIFY_MASK	= 1 << 17,
	  GDK_PROXIMITY_IN_MASK		= 1 << 18,
	  GDK_PROXIMITY_OUT_MASK	= 1 << 19,
	  GDK_SUBSTRUCTURE_MASK		= 1 << 20,
	  GDK_SCROLL_MASK               = 1 << 21,
	  GDK_ALL_EVENTS_MASK		= 0x3FFFFE
	} GdkEventMask;
	*/
	/* tell to gtkgl wich events we want to handle */
	gtk_widget_set_events(
						GTK_WIDGET(glarea),
						GDK_EXPOSURE_MASK|
						GDK_KEY_PRESS_MASK|
						GDK_KEY_RELEASE_MASK|
						GDK_POINTER_MOTION_MASK|
						GDK_POINTER_MOTION_HINT_MASK|
						GDK_BUTTON_MOTION_MASK|
						GDK_BUTTON1_MOTION_MASK|
						GDK_BUTTON2_MOTION_MASK|
						GDK_BUTTON3_MOTION_MASK|
						GDK_BUTTON_PRESS_MASK|
						GDK_BUTTON_RELEASE_MASK
						);

	/* set up call back */
	gtk_signal_connect(GTK_OBJECT(glarea), "button_release_event",
					GTK_SIGNAL_FUNC(glarea_button_release), NULL);
	gtk_signal_connect(GTK_OBJECT(glarea), "button_press_event",
					GTK_SIGNAL_FUNC(glarea_button_press), NULL);
	gtk_signal_connect(GTK_OBJECT(glarea), "motion_notify_event",
					GTK_SIGNAL_FUNC(glarea_motion_notify), NULL);
	gtk_signal_connect(GTK_OBJECT(glarea), "expose_event",
                    GTK_SIGNAL_FUNC(glarea_draw), NULL);
	gtk_signal_connect (GTK_OBJECT(glarea), "configure_event",
					GTK_SIGNAL_FUNC(glarea_reshape), NULL);
	gtk_signal_connect (GTK_OBJECT(glarea), "realize",
					GTK_SIGNAL_FUNC(glarea_init), NULL);
	gtk_signal_connect(GTK_OBJECT(glarea), "key_press_event",
					GTK_SIGNAL_FUNC(glarea_key_pressed), NULL);
	gtk_signal_connect(GTK_OBJECT(glarea), "key_release_event",
					GTK_SIGNAL_FUNC(glarea_key_released), NULL);
	gtk_idle_add((GtkFunction)glarea_idle, glarea);
	gtk_signal_connect(GTK_OBJECT(glarea), "destroy",
					GTK_SIGNAL_FUNC (glarea_destroy), NULL);

	/* set the size of the area */
	gtk_widget_set_usize(GTK_WIDGET(glarea), size_x, size_y);

	return glarea;
}

gint OR_InputOutput::glarea_button_release(GtkWidget* widget, GdkEventButton* event)
{
	Mouseclic(event->button, 0, event->x, event->y);

	return TRUE;
}

gint OR_InputOutput::glarea_button_press(GtkWidget* widget, GdkEventButton* event)
{
	Mouseclic(event->button, 1, event->x, event->y);

	return TRUE;
}

gint OR_InputOutput::glarea_motion_notify(GtkWidget* widget, GdkEventMotion* event) 
{
	Mouse(event->x, event->y);

	return TRUE;
}

gint OR_InputOutput::glarea_draw(GtkWidget* widget, GdkEventExpose* event) 
{
	/* Draw only on the last expose event. */
	if (event->count > 0) return(TRUE);
	/* gtk_gl_area_make_current MUST be called before rendering */
	/* into the GtkGLArea.                                      */
	if (gtk_gl_area_make_current(GTK_GL_AREA(widget))) 
	{
		Display();
	}
	
	return TRUE;	
}

gint OR_InputOutput::glarea_reshape(GtkWidget* widget, GdkEventConfigure* event) 
{
	/* gtk_gl_area_make_current MUST be called before rendering */
	/* into the GtkGLArea.                                      */
	if (gtk_gl_area_make_current (GTK_GL_AREA(widget))) 
	{
		Reshape(widget->allocation.width, widget->allocation.height);
	}
  
	return (TRUE);
}

gint OR_InputOutput::glarea_init(GtkWidget* widget) 
{
	if (gtk_gl_area_make_current (GTK_GL_AREA(widget))) 
	{
		/* initializing opengl is made by InitGL, not here */
	}

	return TRUE;
}

gint OR_InputOutput::glarea_destroy(GtkWidget* widget) 
{
	Destroy();

	return TRUE;
}

gint OR_InputOutput::glarea_key_released(GtkWidget *widget, GdkEventKey *event)
{
	KeyReleased(event->keyval, 0, 0);
 
	/* prevent the default handler from being run */
	gtk_signal_emit_stop_by_name(GTK_OBJECT(widget),"key_press_event");
	return TRUE;
}

gint OR_InputOutput::glarea_key_pressed(GtkWidget *widget, GdkEventKey *event)
{
	KeyPressed(event->keyval, 0, 0);
 
	/* prevent the default handler from being run */
	gtk_signal_emit_stop_by_name(GTK_OBJECT(widget),"key_press_event");
	return TRUE;
}

gint OR_InputOutput::glarea_idle(GtkWidget *glarea)
{
	Idle();
	return TRUE;
}

void OR_InputOutput::MainLoop()
{
	/* start an inifinite loop */
	gtk_main();
}


} // namespace OR

#endif /* #ifdef _USE_GTK_ */


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_license.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////