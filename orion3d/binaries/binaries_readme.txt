###########################################################################################################################
                                                binaries_readme.txt
###########################################################################################################################

These foders contains :
	- Extenal libraries .lib files ['external_lib/'] :		** FOR DEVELOPPERS **
		- fmod files.
		- ZLib files.
		- OpenIL files.
		- GTK+ files.
		----> these files should be put in the lib/ folder of your compiler.
	- Extenal libraries .dll files ['external_dll/'] :		** FOR EVERYBODY **
		- fmod files.
		- ZLib files.
		- OpenIL files.
		- GTK+ files.
		----> these should be put in your 'system/' folder.
	- Orion3D .lib files :						** FOR DEVELOPPERS **
		orion3d_glut.lib : using the GLUT wrapper for input/output.
		orion3d_gtk.lib : using the GTK+ wrapper for input/output.
		orion3d_win32.lib : using the Win32 wrapper for input/output.
		orion3d_none.lib : not using any wrapper for input/output (you'll have to write your own functions !).
		----> these files should be put in the lib/ folder of your compiler.
		      a better solution would be to add a path in your project to this directory, because you'll probably
		      have to re-build these files.
	- Orion3D .dll files :						** FOR EVERYBODY **
		orion3d_glut.dll : using the GLUT wrapper for input/output.
		orion3d_gtk.dll : using the GTK+ wrapper for input/output.
		orion3d_win32.dll : using the Win32 wrapper for input/output.
		orion3d_none.dll : not using any wrapper for input/output (you'll have to write your own functions !).
		----> these should be put in your 'system/' folder.
	
###########################################################################################################################