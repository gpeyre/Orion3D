/*------------------------------------------------------------------------------*/
/** 
 *  \file  main.cpp
 *  \brief main file for \b GLUT wrapper test.
 *  \author Gabriel Peyré 2001-10-17
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) main.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

/* first thing to do : tell to Orion3D we are using the GLUT wrapper */
#define _USE_GTK_
/* tell that we are using the Orion3D dll */
#define ORION3D_IMPORTS


//-------------------------------------------------------------------------
/** \name orion3d file inclusion */
//-------------------------------------------------------------------------
//@{
/* this will check wich library we will need to use */
#include "../../orion3d/configuration/OR_Config.h"
#include "../../orion3d/toolkit/OR_Toolkit.h"
#include "../../orion3d/wrapper_gtk/OR_InputOutput_Gtk.h"
/* we want to avoid putting OR:: before each Orion3D beautifull class names */
using namespace OR;
//@}



//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef OR_DEBUG
	#pragma comment(lib, "orion3d_wrapper_gtk_dbg.lib")
	#pragma comment(lib, "orion3d_toolkit_dbg.lib")
#else
	#pragma comment(lib, "orion3d_wrapper_gtk.lib")
	#pragma comment(lib, "orion3d_toolkit.lib")
#endif // OR_DEBUG
//@}


//-------------------------------------------------------------------------
/** @name 3D engine */
//-------------------------------------------------------------------------
//@{
/** the main helper, create all Orion3D stuff */
OR_Toolkit *pToolkit = new OR_Toolkit;
/** the wrapper used for input/output */
OR_InputOutput_GTK* pInputOutput = new OR_InputOutput_GTK(*pToolkit);
//@}


/*------------------------------------------------------------------------------*/
/** 
 * Name : LoadMyWorld
 *
 *  \author Gabriel Peyré 2001-10-17
 *
 *	Just load a tiny gizmo and a camera : add your own stuff !
 */ 
/*------------------------------------------------------------------------------*/
void LoadMyWorld()
{	
	/* create and add a sphere **********************************/
	OR_SphereGizmo* pSphere = new OR_SphereGizmo();
	pToolkit->AddObject(pSphere);

	/* create a target camera ***********************************/
	pToolkit->AddTargetCamera();
	OR_Camera_Target* pCamera = (OR_Camera_Target*) pToolkit->GetCameraManager().GetElementSelected();
	pCamera->Posit(OR_Vector3D(0,-10,5) );
	pCamera->SetTarget( pSphere );

	/* create a viewport for this camera ************************/
	pToolkit->AddScreenViewPort(1);
	pToolkit->SetViewPortDimensions(0,0,1, 1);
}



/** to handle mouse movements */
void mouse(OR_I32 x, OR_I32 y)
{
	OR_Bool BoutG=pToolkit->GetLeftButtonState();
	OR_Bool BoutD=pToolkit->GetRightButtonState();
	OR_I32 xmouse=pToolkit->GetMousePosX();
	OR_I32 ymouse=pToolkit->GetMousePosY();

	if( BoutD && !BoutG )
	{
		pToolkit->RotateCamera(Y, (xmouse-x)*0.01);
		pToolkit->RotateCamera(X, (ymouse-y)*0.01);
	}
	else if( BoutG )
	{
		pToolkit->TranslateCamera(Z, (-ymouse+y)*0.05);
	}
	
    pToolkit->SetMousePosX(x);
    pToolkit->SetMousePosY(y);
}

/** to handle keyboard */
void keyboard(OR_U32 button, OR_I32 x, OR_I32 y)
{
	switch((char) button)
	{
	case 27:
		::exit(0);
		break;
	default:
		printf("Orion3D is SO COOL !\n");
	}
}

/** to handle arrow keys */
void keyboardspec(OR_I32  key, OR_I32 x, OR_I32 y)
{
	switch (key) 
	{
	case GDK_Up:
		pToolkit->TranslateCamera(Z, -1);
		break;
	case GDK_Down:
		pToolkit->TranslateCamera(Z, 1);
		break;
	case GDK_Left:
		pToolkit->RotateCamera(Z, -0.1f);
		break;
	case GDK_Right:
		pToolkit->RotateCamera(Z, 0.1f);
		break;
	case 27:
		::exit(0);
		break;
	}
}

/** when nothing occurs */
void idle(void)
{
	/* update the 3D engine */
	pToolkit->Update();
	
	/* re-draw everything */
	pToolkit->PostReDisplay();

	/* here you can add code to handle things each frame */
}






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




void PrintFPSReport()
{
	
	pToolkit->PrintFPSReport();
	pToolkit->MakeFPSLog();
}

void ToggleDrawGizmo()
{
	pToolkit->ToggleDraw(OR_GIZMO);
}
void ToggleDrawLight()
{
	pToolkit->ToggleDraw(OR_LIGHT);
}

void ToggleDrawCamera()
{
	pToolkit->ToggleDraw(OR_CAMERA);
}

void ToggleDrawLocalAxe()
{
	pToolkit->ToggleDraw(OR_LOCAL_AXES);
}

void DrawNothing()
{
	pToolkit->DisableDraw(OR_GIZMO);
	pToolkit->DisableDraw(OR_LIGHT);
	pToolkit->DisableDraw(OR_CAMERA);
	pToolkit->DisableDraw(OR_LOCAL_AXES);
}

void About()
{
#ifdef _WIN32_		
	MessageBox(NULL,"OrionViewer : a simple Orion3D program\n\nOrion3D (c) 2000 Gabriel & Antoche",
		"About OrionViewer.",
		MB_OK | MB_ICONINFORMATION);
#else
	printf("\n\nOrionViewer : a simple Orion3D program\n\nOrion3D (c) 2000 Gabriel & Antoche\n\nPress h for help.");
#endif
}

/** print the help message */
void PrintHelp()
{
	printf("\n");
	printf("----------------------------------------------------------------\n");
	printf("                -==[ gtk_test - HELP ]==-\n");
	printf("----------------------------------------------------------------\n");
	printf("This is just a sample program after all ...\n");
	printf("----------------------------------------------------------------\n");
}

void quit()
{
	::exit(0);
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

  button = gtk_button_new_with_label ("Nada");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(About), NULL);

  button = gtk_button_new_with_label ("Nada");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(About), NULL);

   button = gtk_button_new_with_label ("Nada");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(About), NULL);

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

  button = gtk_button_new_with_label ("Nada");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(About), NULL);

  button = gtk_button_new_with_label ("Nada");
  gtk_container_add (GTK_CONTAINER (bbox), button);
  gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(About), NULL);

  button = gtk_button_new_with_label ("Nada");
  gtk_container_add (GTK_CONTAINER (bbox), button);
   gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(About), NULL);

  button = gtk_button_new_with_label ("Nada");
  gtk_container_add (GTK_CONTAINER (bbox), button);
    gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(About), NULL);

    button = gtk_button_new_with_label ("Nada");
  gtk_container_add (GTK_CONTAINER (bbox), button);
    gtk_signal_connect (GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(About), NULL);

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

  return(frame);
}


void CreateGTKWindows()
{
	
#ifdef _USE_GTK_
	GtkWidget* box_main = pInputOutput->GetMainBox();
	GtkWidget* glarea   = pInputOutput->GetGlArea();
	GtkWidget* window   = pInputOutput->GetWindow();

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










/*------------------------------------------------------------------------------*/
/** 
 * Name : main 
 *
 *  \param  argc ...
 *  \param  argv ..
 *  \author Gabriel Peyré 2001-10-17
 *
 *	entry point for the application
 */ 
/*------------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
	/* check if we use an up-to-date version of Orion3D */
	if( OR_Toolkit::GetVersion() < OR_ORION3D_Version )
		pToolkit->Warning("Orionviewer main", "The version of Orion3D.dll is not supported.");
	
	/* register the wrapper used for input.output */
	pToolkit->SetInputOutput(*pInputOutput);
	pInputOutput->Initialisation(&argc, argv, "-==[GTK Test]==-",1024,768);
	
	printf("\n\n   -==[ Test for GTK wrapper ]==-\n");
	fflush(stdout);

	/* just load a tiny gizmo and a camera */
	LoadMyWorld();
	
	/* set up callback functions */
	pToolkit->SetMotionFunc(mouse);
	pToolkit->SetKeyPressedFunc(keyboard);
	pToolkit->SetSpecialFunc(keyboardspec);
	pToolkit->SetIdleFunc(idle);
	
	pToolkit->LogAddLine("\n--- Lauching GTK wrapper test ---\n");

	CreateGTKWindows();
	

	/* run an infinite loop */
	pToolkit->MainLoop();
	
	return 0;
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