#ifndef _MAX_VIEWER_H_
#define _MAX_VIEWER_H_

#include "stdafx.h"
#include "./Interface.h"
#include "./Globals.h"

/** \file
 *	This is the main file of the Orion3DMAX Viewer plug-in. It contains the member functions,
 *	the plug-in class and the class descriptor of this plug-in
 *	\author Antoche - antoche@altern.org
**/

///Orion3DMAX Viewer ClassID
const Class_ID ViewerClassID = Class_ID(0xbb371d7, 0x5f344ff5);
///Orion3DMAX Viewer Super ClassID
const SClass_ID ViewerSuperClassID = UTILITY_CLASS_ID;

/** \class UtilityObj
  	\brief 3DSMAX utility plug-in

  	It's a 3DSMAX class, see the MAX SDK documentation for more information about it
	\todo Replace this fucking GetRsrcString() by something less dirty
**/

/*--------------------------------------------------------------
Code de la Classe :
---------------------------------------------------------------*/
/// Main class of the Orion3DMAX Viewer plug-in
class ViewerPlugin : /*public TimeChangeCallback, */public UtilityObj 
{
private:
	///Former mem handler (function called when there is not enough memory anymore)
	_PNH		OldLowMemHandler;
	///Our mem handler : display a warning message when there is not enough memory
	static int		LowMemHandler(size_t size);

	class CTimeCallback:public TimeChangeCallback 
	{
		public:
		void TimeChanged(TimeValue t) {SetTime(t);}		
	} MyTimeCallback;

public:

	/// Constructor
	ViewerPlugin();
	/// Destructor
	~ViewerPlugin();
	///Called by 3DSMAX when the user starts the plug-in clicking on its button.
	///This is the main entrey point of the plug-in. This function launch Orion3D and the
	///viewer window, and creates the rollout panels
	///\param ip 3DSMAX Interface (we use it to access anything we want from 3DSMAX)
	///\param ui a class that holds only one function : CloseUtility, that allows the plug-in to close itself (we use it when the user clicks on the cross button of the rollout panel)
	virtual void	BeginEditParams(Interface *ip,IUtil *iu);
	///Called by 3DSMAX when the user close the plug-in panel. Here we destroy the panels
	///but the plug-in is not stopped and the Orion3D window is still active, since
	///it is useful to have it when we modify objects
	///\param ip 3DSMAX Interface (we use it to access anything we want from 3DSMAX)
	///\param ui a class that holds only one function : CloseUtility, that allows the plug-in to close itself (we use it when the user clicks on the cross button of the rollout panel)
	virtual void	EndEditParams(Interface *ip,IUtil *iu);
	///Called by 3DSMAX when the user adds/removes objects to/from the selection set. We don't care about it
	///\param ip 3DSMAX Interface (we use it to access anything we want from 3DSMAX)
	///\param ui a class that holds only one function : CloseUtility, that allows the plug-in to close itself (we use it when the user clicks on the cross button of the rollout panel)
	virtual void	SelectionSetChanged(Interface *ip,IUtil *iu);
	///This method is called after BeginEditParams() when the user starts the utility from the command line with the option -U and passes an argument to the utility. We don't care about it neither.
	///\param param the command line string
	virtual void	SetStartupParam(TSTR param);
	///Called by 3DSMAX when it needs to delete the plug-in from the memory
	virtual void	DeleteThis();
	///Called by 3DSMAX when it closes
	static void		Exit(void *param, NotifyInfo *info);
	///Called by 3DSMAX when 3DSMAX time change
	virtual void	TimeChanged(TimeValue t);
};


/*
class CNotifier:public ReferenceTarget
{
public:
	ViewerPlugin* Plugin;
	virtual RefResult NotifyRefChanged(Interval changeInt, RefTargetHandle hTarget,PartID& partID,RefMessage message)
	{
		if (!Plugin) return REF_SUCCEED;
		switch (message) {
		case REFMSG_MOUSE_CYCLE_COMPLETED:
		case REFMSG_TM_CHANGE:
			//Plugin->UpdateMatrices();
			//PlaySound("C:\\WINNT\\Media\\Utopia - Arrêt critique.WAV" , NULL , SND_FILENAME | SND_ASYNC );
		break;
		case REFMSG_NODE_LINK:
		case REFMSG_NOTIFY_PASTE:
		case REFMSG_SEL_NODES_DELETED:
		case REFMSG_TEXMAP_REMOVED:
		case REFMSG_OBJECT_REPLACED:
		case REFMSG_NODE_MATERIAL_CHANGED:
			//Plugin->Update();
			//PlaySound("C:\\WINNT\\Media\\Utopia - Niveau inférieur.WAV" , NULL , SND_FILENAME | SND_ASYNC );
		break;
			
		}
		return REF_SUCCEED;
	}
};
*/
/*--------------------------------------------------------------
Code du descripteur de classe :
---------------------------------------------------------------*/
/** \class ClassDesc
  	\brief 3DSMAX class descriptor

  	It's a 3DSMAX class, see the MAX SDK documentation for more information about it
	\todo Replace this fucking GetRsrcString() by something less dirty
**/
/// Orion3DMAX Viewer Class descriptor
/// This class is to describe the Viewer plug-in. We send it to 3DSMAX when it calls the
//	global function LibClassDesc() at startup.
class ViewerClassDesc : public ClassDesc {
	public:
/** @return Whether the plug-in is public or not*/
	int 			IsPublic()					{ return TRUE;								}
/** @return A new instance of the plug-in class*/
	void * 			Create(BOOL loading=FALSE)	{ return new ViewerPlugin();					}
/** @return The name of the plug-in*/
	const TCHAR * 	ClassName()					{ return _T("Orion3DMAX Viewer");				}
/** @return The super class ID of the plug-in (it's an export plug-in, so we return SCENE_EXPORT_CLASS_ID)*/
	SClass_ID 		SuperClassID()				{ return  ViewerSuperClassID;				}
/** @return The unique class ID of the plug-in, generated with the Gencid.exe tool of the SDK). 
 *	For your information it is Class_ID(0xbb371d7, 0x5f344ff5), but you may not care about it :o)
**/
	Class_ID 		ClassID()					{ return ViewerClassID;	}
/** @return The category in which the plug-in must appear (nothing, since it is an export plug-in)*/
	const TCHAR* 	Category()					{ return _T("Orion3D");					}
/** Deletes this class*/
	void DeleteThis()							{ delete this;								}
};


#endif //_MAX_VIEWER_H_