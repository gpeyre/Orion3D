#ifndef _ACT_EXPORTER_H_
#define _ACT_EXPORTER_H_

//#include "Includes.h"
#include "../OR_3DS_AnimUtils.h"


/** \file
 *	This is the main file of the plug-in. It contains the member functions,
 *	the KSP export plug-in class and the class descriptor of this plug-in
 *	\author Antoche - antoche@altern.org
**/

/*--------------------------------------------------------------
Code de la Classe :
---------------------------------------------------------------*/
/// Main class of the plug-in
/** C'est la classe qui fait le lien entre 3DSMAX et le reste du plug-in. 
 *  Elle est héritée la classe SceneExport de 3DSMAX et toutes les fonctions
 *	publiques sont des fonctions virtuelles de SceneExport. Ces fonctions sont
 *	réclamées et appelées par 3DSMAX uniquement
**/

class ACTPlugin : public SceneExport
{
public:
/** Constructor
**/
	ACTPlugin() {};	
/** Destructor
**/
	~ACTPlugin() {};				
/** @return the number of extensions supported
**/
	int				ExtCount();
/** @return the #n extension supported
 *	@param n number of the supported extension
**/
	const TCHAR *	Ext(int n);
	/** @return a detailed description of the Plug-in	*/
	const TCHAR *	LongDesc();
	/** @return a short description of the Plug-in	*/
	const TCHAR *	ShortDesc();
	/** @return the author's name (hey ! it's me !)	*/
	const TCHAR *	AuthorName();
	/** @return a copyright (&copy;) message	*/
	const TCHAR *	CopyrightMessage();
	/** @return an additionnal message	*/
	const TCHAR *	OtherMessage1();
	/** @return another additionnal message	*/
	const TCHAR *	OtherMessage2();
	/** @return the version of the plug-in	*/
	unsigned int	Version();
	/** Show the About Box of the plug-in	*/
	/** @param hWnd Handle of the parent window	*/
	void			ShowAbout(HWND hWnd);
	/// It's the main plug-in function. It is called when the user launches the export
	/**	
		@return 1 if successed, 0 if failed
		@param name the FileName to be exported to
		@param ei the Export Interface (not used)
		@param i the Main Interface. We can access to everything with it
		@param SuppressPrompts if true, tell the plug-in not to display any query (for exemple for batch exports)
		@param options Option for export. For now the only option avaliable is whether the plug-in must export only selected objects or not

	*/
	int				DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);
	/** @return TRUE if the option asked for is supported
		@param option which options are being queried
		@param ext indicates which extension the options are being queried for
		As said before, the only option supported for now is SCENE_EXPORT_SELECTED
	*/
	BOOL			SupportsOptions(int ext, DWORD options);
	/** Called to delete the plug-in.*/
	void			DeleteThis();

	/** Retrieve the animation of a node and its subtree. Recursive function : it calls
		itself for each RootNode son. This function uses CNode functions to get the tracks
		of RootNode
		@param AnimHeader the animation header, in which the function fills the number
				of keys, nodes and tracks.
		@param RootNode the 3DSMAX node that contains the animation
		@return the animation corresponding to RootNode
	**/
	OR_AnimationNode* ExportAnimRec(OR_Animation* AnimHeader, INode* RootNode);
	/** Write the animation tree (i.e. nodes, tracks and keyframes) in the file File starting 
		from Node. Recursive function :	it calls itself for each Node son.
		@param Node the node to write in the file.
		@param File the file where to write the node
	**/
	void			WriteAnimRec(OR_AnimationNode* Node , FILE* File);

};


/*--------------------------------------------------------------
Code du descripteur de classe :
---------------------------------------------------------------*/

/// Class descriptor
/** C'est une classe héritée de la classe ClassDesc de 3DSMAX. Elle sert à décrire un 
 *	plug-in et est réclamée par MAX (et envoyée par la fonction globale \a LibClassDesc()
 *	à l'initialisation.
**/
class ACTClassDesc : public ClassDesc {
/** @return Whether the plug-in is public or not*/
	public:
	int 			IsPublic()					{ return TRUE;								}
/** @return A new instance of the plug-in class*/
	void * 			Create(BOOL loading=FALSE)	{ return new ACTPlugin();					}
/** @return The name of the plug-in*/
	const TCHAR * 	ClassName()					{ return _T("ACT Exporter");				}
/** @return The super class ID of the plug-in (it's an export plug-in, so we return SCENE_EXPORT_CLASS_ID)*/
	SClass_ID 		SuperClassID()				{ return SCENE_EXPORT_CLASS_ID;				}
/** @return The unique class ID of the plug-in, generated with the Gencid.exe tool of the SDK). 
 *	For your information it is Class_ID(0x749e4602, 0x3c2d19d9), but you may not care about it :o)
**/
	Class_ID 		ClassID()					{ return Class_ID(0x3e651160, 0x617c0f32);	}
/** @return The category in which the plug-in must appear (nothing, since it is an export plug-in)*/
	const TCHAR* 	Category()					{ return _T("");					}
/** Deletes this class*/
	void DeleteThis()							{ delete this;								}
};

#endif //_ACT_EXPORTER_H_