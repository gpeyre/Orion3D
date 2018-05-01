#error Removed.


#ifdef _USE_GTK_
	#pragma warning( disable : 4133 )
	/* MUST INCLUDE gtkgl.c UNTIL THE .LIB IS BUILD */
	#include "..\gtk+\gtkgl\gdkgl-win32.c"
	#include "..\gtk+\gtkgl\gtkglarea.c"
#endif