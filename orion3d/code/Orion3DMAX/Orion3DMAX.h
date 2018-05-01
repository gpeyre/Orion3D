	//============================================================================
/*! \par Project  Orion3DMAX
    \par Platform Windows 95/98/NT/Me/2K
    \author       Antoche (antoche@altern.org)
    \note         THERE IS NOT ANY WARRANTY
                  OF ANY KIND, USE THIS FILE AT YOUR OWN RISK.
*///==========================================================================

/** \file 
	Contains the main Dll classes
	\author Antoche
**/

/*!
	\mainpage	Orion3DMAX Documentation

	\section	userinfo End-User Information
	\subsection	o3dmax What is Orion3DMAX ?
				Orion3DMAX is an 3D Studio MAX 4 plug-in that lets you preview
				your scene with Orion3D while you still can modify it with 3DS, 
				and many more.
				              
    \subsection	orion3d What is Orion3D ?
				Orion3D is a portable 3D engine using OpenGL and advanced
				rendering techniques such as Portals, PVS, BSP, hierarchical
				animation, particules systems, etc... visit http://www.orion3d.fr.st
				for up-to-date information about Orion3D.

	\image		html screenshot.jpg "Orion3D screenshot"

	\subsection	user How do I use Orion3DMAX ?
	\subsection one
				First make sure the file Orion3DMAX.dle is in the plugins\ folder
				of 3DSMAX4. Now you can launch 3DSMAX4 and create or open a scene. When
				you want to see the scene through real-time Orion3D rendering, open the
				Utility panel and launch the Orion3DMAX Viewer utility plug-in (if it is
				not in the list, you can add it with the "Configure Button Sets" button
				or launch it via the "More..." button.
				
	\subsection two
				The interface of Orion3DMAX is composed of two parts. The first is
				the usual rollout panel in the 3DSMAX Interface. It looks like this :

	\image		html panel.jpg

				The second part is the viewer itself. It is a windows that renders the
				scene in real-time. At the beginning, it has the same size & position
				that the active viewport and is always on top. You can reduce or expand
				it with the buttons 2 & 3 in the Orion3DMAX rollout panel or by 
				double-clicking on the title bar of the window.

	\subsection three
				The viewer allows you to navigate freely in the scene using the mouse
				and the arrow keys : left click + drag or up/down to zoom in/out, and
				right click + drag to turn.

				You can also change some display preferences with the rollout panel : 
				change the display style with buttons 5(filled), 6(wireframe), 7(points),
				(de)activate the display of lights, cameras, gizmos and local axes with
				checkboxes (11). The section (12) informs you about the number of objects
				in the scene. 

				As Orion3DMAX retrieve the animations, you play/pause the animation with
				button (8) or set the time with the slider (9). The combo box (10) permits
				you to bind the camera of the viewer to a viewport or a camera of 3DSMAX.
				If you choose "None", the camera of the viewer will not be reset when
				you update the scene.

				Last but not least, use the "Update" button (1) when the MAX scene has 
				changed and you need to update the objects dipslayed in the viewer.

	\subsection four
				If you close the plug-in panel or switch to another panel, the plug-in
				will still be active (the viewer window is still here). Each time the
				panel is open, the scene is updated. To definitely close the plug-in,
				click on button (4). If you close 3DSMAX while Orion3DMAX is active, it
				will close itself.
				
	\subsection	download How do I get the lastest release of Orion3DMAX ?
				Go to the Orion3D web page (http://www.orion3d.fr.st) and follow the links in
				the download section

	\section	devinfo Developer information
	\subsection	coder How does it works ?
				A little explanation later :)

	\subsection	compile How do I compile ACT Exporter ?
				You need a compiler that can create .dll files, like Ms Visual C++ 6. You
				also need the 3DSMAX4 SDK which can be installed with 3DSMAX4, and the orion3d
				SDK. If you use VC++6, then open the Orion3DMAX workspace (Orion3DMAX.dsw)
				and launch build. If you installed 3DSMAX4 in an other folder than \3dsmax4, then
				you will have to change the paths in :
				 - Project>Settings>link>Category:General>Output file name,
				 - Project>Settings>link>Category:Input>Additional library path
				 - Project>Settings>C++>Category:Preprocessor>Additional include directories


	\subsection	download How do I get the lastest source code of Orion3DMAX ?
				You can download the up-to-date source code of Orion3DMAX on the Orion3D CVS.
				Simply log in on cvs.orion3d.sourceforge.net as an anonymous user and checkout
				the "Orion3DMAX" module. You will also need some of the orion3d source code
				to compile it, wich is located in the "orion3d" module.
				If you don't know what a CVS is you can find an explanation on the Orion3D web
				page.	

	\section	author How to join the author?
				You liked this program? You didn't? You have something to say
				about it ? You want more information ?
				e-mail me at antoche@altern.org or visit my webpage (http://www.antoche.fr.st)
				or the Orion3D page (http://www.orion3d.fr.st)
*/


#ifndef _ORION3DMAX_H_
#define _ORION3DMAX_H_
#ifndef _USE_WIN32_
#define _USE_WIN32_
#endif

#include "stdafx.h"
#include "O3DMAXViewer/O3DMAXViewer.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "geom.lib")
#pragma comment(lib, "maxutil.lib")
#pragma comment(lib, "core.lib")
#pragma comment(lib, "mesh.lib")

//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef OR_DEBUG
#pragma comment(lib, "orion3d_wrapper_win32_dbg.lib")
#pragma comment(lib, "orion3d_toolkit_dbg.lib")
#else
#pragma comment(lib, "orion3d_wrapper_win32.lib")
#pragma comment(lib, "orion3d_toolkit.lib")
#endif // ORION3D_DEBUG
//@}




/** \file
 *	This is the main file of the plug-in. It contains the member functions,
 *	the KSP export plug-in class and the class descriptor of this plug-in
 *	\author Antoche - antoche@altern.org
**/
/// state variable indicating whether the common & custom controls have been initialized
int controlsInit = FALSE;
/// An instance of the ACTClassDesc class
//static ACTClassDesc ACTCD;
/// An instance of the ViewerClassDesc class
static ViewerClassDesc ViewerCD;


/// This macro says the function will be exported as public in the library (doxy can't stand parenthesis in types)
#define ExportedFunction __declspec(dllexport) 
#define BOOLWINAPI BOOL WINAPI 

/** @return the class descriptor of the chosen plug-in
 *	@param i the number of the plug-in chosen
**/
ExportedFunction ClassDesc *LibClassDesc(int i);
/** @return a description of the library
**/
ExportedFunction const TCHAR *LibDescription();
/** @return the version of the library
**/
ExportedFunction ULONG LibVersion();

/** @return how many plug-ins there are in this library. Here there is only one (the KSP Exporter)
**/
ExportedFunction int LibNumberClasses(void);


/*
Uncomment the following block if you experience an "unresovled external : ClassDesc::GetRsrcString"-like
error ( the clean solution remains to install tjhe platform SDK available at 
http://www.microsoft.com/msdownload/platformsdk/sdkupdate/ or 
ftp://ftp.microsoft.com/developr/platformsdk )
*/

/*
#if	MAX_RELEASE >= 4000 //Uniquement pour la version 4.xx
#pragma warning(disable:4273)
TCHAR* ClassDesc::GetRsrcString(INT_PTR id) {return _T("");}
#pragma warning(default:4273)
#endif
*/


/** \class MtlBase
  	\brief 3DSMAX base material
	
  	It's a 3DSMAX class, see the MAX SDK documentation for more information about it
**/
/** \class ExitMAXCallback
  	\brief 3DSMAX exit callback class
	
  	It's a 3DSMAX class, see the MAX SDK documentation for more information about it
**/
/** \class SceneExport
  	\brief 3DSMAX base scene exporter
	
  	It's a 3DSMAX class, see the MAX SDK documentation for more information about it
**/
/** \class INode
  	\brief 3DSMAX hierarchy node
 
  	It's a 3DSMAX class, see the MAX SDK documentation for more information about it
**/



#endif //_ORION3DMAX_H_