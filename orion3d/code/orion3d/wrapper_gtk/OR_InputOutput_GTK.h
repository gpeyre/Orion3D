//*****************************************************************************
/// \author Gabriel Peyré
//*****************************************************************************

#ifndef __OR_InputOutput_GTK_h_
#define __OR_InputOutput_GTK_h_

#ifdef __GNUG__
    #pragma interface
#endif

#include "../configuration/OR_Config.h"
#include "../input_output/OR_InputOutput_ABC.h"

#ifdef _USE_GTK_

namespace OR {

//=============================================================================
/**
*   @class  OR_InputOutput_GTK
*   @brief  A wrapper that use GLUT API for input/output.
*
*	GTK homepage <a href="http://www.gtk.org">www.gtk.org</a>
*/
/// \author Gabriel Peyré
//=============================================================================
class OR_InputOutput_GTK: public OR_InputOutput_ABC
{

friend OR_InputOutput_ABC;

public:

    OR_InputOutput_GTK(OR_Renderer_ABC& Renderer);
    virtual ~OR_InputOutput_GTK();

	//-------------------------------------------------------------------------
    /** @name overload of OR_InputOutput_ABC methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void Initialisation(int *argc, char **argv, char* name,
		OR_I32 largeur=640, OR_I32 hteur=480,
		OR_I32 posx=0, OR_I32 posy=0);
	virtual void SetupPixelFormat(int *argc, char **argv);
	virtual void PostReDisplay();
	virtual void Swap();
	virtual void MainLoop();
    //@}

	//-------------------------------------------------------------------------
    /** @name API-specific default callbacks */
    //-------------------------------------------------------------------------
    //@{
	static void Default_Destroy();
	static void Default_KeyPressed(OR_U32 button, OR_I32 x, OR_I32 y);
	static void Default_Mouseclic(OR_I32 button, OR_I32 state, OR_I32 x, OR_I32 y);
    //@}

    //-------------------------------------------------------------------------
    /** @name GTK specific datas */
    //-------------------------------------------------------------------------
    //@{
	/** to create the main glarea */
	static GtkWidget* create_glarea(OR_I32 size_x, OR_I32 size_y);
	/** glarea callback function */
	static gint glarea_button_release(GtkWidget*, GdkEventButton*);
	/** glarea callback function */
	static gint glarea_button_press(GtkWidget*, GdkEventButton*);
	/** glarea callback function */
	static gint glarea_motion_notify(GtkWidget*, GdkEventMotion*);
	/** glarea callback function */
	static gint glarea_draw(GtkWidget*, GdkEventExpose*);
	/** glarea callback function */
	static gint glarea_reshape(GtkWidget*, GdkEventConfigure*);
	/** glarea callback function */
	static gint glarea_init(GtkWidget*);
	/** glarea callback function */
	static gint glarea_destroy(GtkWidget*);
	/** glarea callback function */
	static gint glarea_key_released(GtkWidget *widget, GdkEventKey *event);
	/** glarea callback function */
	static gint glarea_key_pressed(GtkWidget *widget, GdkEventKey *event);
	/** glarea callback function */
	static gint glarea_idle(GtkWidget *glarea);

	/**
	\code

	                     window                     <-- a container
	                        |
	                     box_main                   <-- a box
	                    /        \
	a glarea -->   gllarea     mybutton             <-- a button
	\endcode
	*/
	/** the opengl widget */
	static GtkWidget* glarea;
	/** the main containers */
	static GtkWidget* window;
	/* the main box */
	static GtkWidget* box_main;
    //@}

    //-------------------------------------------------------------------------
    /** @name GTK specific methods */
    //-------------------------------------------------------------------------
    //@{
	/** initialize GTK (only the glarea) */
	void MinimumInit(int *argc, char **argv, OR_I32 largeur, OR_I32 hteur);
	/** to get the main box */
	GtkWidget* GetMainBox();
	/** to get the main glarea */
	GtkWidget* GetGlArea();
	/** get the main window */
	GtkWidget* GetWindow();
    //@}



};

} // End namespace OR

#endif // _USE_GTK_


#endif // __OR_InputOutput_GTK_h_
