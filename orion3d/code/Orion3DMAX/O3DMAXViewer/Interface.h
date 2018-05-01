#ifndef _OR_3DS_INTERFACE_H_
#define _OR_3DS_INTERFACE_H_

#include "stdafx.h"
#include "./Interface_Orion3D.h"
#include "./Globals.h"

using namespace OR;
using namespace OR_3DS;

BOOL	CALLBACK	AddParamDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK	TreeViewDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK	ViewerDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK	AboutDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


///Load the options of the viewer from the register
void		LoadOptions();
///Save the options of the viewer from the rollout panel
void		SaveOptions();
///Update the informations displayed by the rollout panel (nb mehes, views, etc...)
void		UpdateOptions();
///Make the tree up to date
void		RefreshTree();
HTREEITEM	RefreshTree_Rec( OR_3DS_Node* curnode, HTREEITEM Father );
void		DeleteProperty_Rec( OR_3DS_Node* CurNode, char* Property );
void		AddProperty_Rec( OR_3DS_Node* CurNode, OR_3DS_UserParam* Property );
///Set the parameters of the flying camera to thoses of the n-th element in the view cmobo box. n is modified if the index is out of range
void		SetView(DWORD &n);
///Move the time slider to current time position
void		CALLBACK	UpdateTime(UINT wTimerID,UINT wMsg,DWORD dwUser,DWORD dw1,DWORD dw2);
///Uses CriticalSection and the wrapper to update the Engine
OR_3DS_Node*		Update(int Flags, OR_3DS_Node* Noeud=NULL);
///Display the object's properties in the panel
void		RefreshProperties(OR_3DS_Node* node);
BOOL		TreeViewSetCheckState( HWND hwndTreeView, HTREEITEM hItem, BOOL fCheck );
BOOL		TreeViewGetCheckState( HWND hwndTreeView, HTREEITEM hItem );
HTREEITEM	TreeViewAddItem( HWND HWNDTree, HTREEITEM Father, HTREEITEM Position, const char* Text, int image , bool checked, LPARAM custom = 0 );
///Close orion3d and the rollout panel
int			ShutDown();
///Close orion3d when exiting 3DSMAX
void		CloseAtExit();
///Set the time of the first animplayer
void		SetTime(TimeValue Time);

#endif //_OR_3DS_INTERFACE_H_