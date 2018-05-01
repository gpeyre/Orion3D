#include "../stdafx.h"
#include "Interface.h"

BOOL CALLBACK 	AddParamDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch( uMsg ) { // Respond to the message ...
		case WM_INITDIALOG: // Initialize the Controls here.
			SendMessage(GetDlgItem(hwndDlg, IDC_PARAMNAME), EM_SETLIMITTEXT , 255 , 0);
			SendMessage(GetDlgItem(hwndDlg , IDC_PARAMTYPE ) , CB_INSERTSTRING, 0, (LPARAM) "Unsigned integer");
			SendMessage(GetDlgItem(hwndDlg , IDC_PARAMTYPE ) , CB_INSERTSTRING, 1, (LPARAM) "String");
			SendMessage(GetDlgItem(hwndDlg , IDC_PARAMTYPE ) , CB_SELECTSTRING, 0, (LPARAM) "Unsigned integer");			
		return TRUE;

		case WM_DESTROY:
		return FALSE;

		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDOK:
				{
					OR_3DS_UserParam*	Param = NULL;
					char				Name[256];

					SendMessage(GetDlgItem(hwndDlg, IDC_PARAMNAME) , WM_GETTEXT , (WPARAM)256 , (LPARAM)Name );
					if( !strlen( Name ) )
					{
						MessageBox( hwndDlg, "You must enter a name", "Error", MB_OK | MB_ICONERROR );
						return TRUE;
					}
					switch( ComboBox_GetCurSel( GetDlgItem( hwndDlg, IDC_PARAMTYPE ) ) )
					{
						case 0:
						{
							BOOL Success = FALSE;
							int Val = GetDlgItemInt( hwndDlg, IDC_PARAMDATA , &Success , FALSE );
							if( Success==FALSE ) 
							{
								MessageBox( hwndDlg, "Invalid default value", "Error", MB_OK | MB_ICONERROR );
								return TRUE;
							}
							Param = new_UserParamU32(Name , Val);
						}
						break;
						
						case 1:
						{
							int Size = SendMessage( GetDlgItem( hwndDlg, IDC_PARAMDATA ), WM_GETTEXTLENGTH , 0 , 0 ) + 1;
							char * Content = new char[Size];Content[Size-1]=0;
							SendMessage( GetDlgItem( hwndDlg, IDC_PARAMDATA ), WM_GETTEXT , (WPARAM)Size , (LPARAM)Content );
							Param = new_UserParamString( Name , Size , Content );
							OR_DELETEARRAY( Content );
						}
						break;

						default:
							MessageBox( hwndDlg, "You must choose a type", "Error", MB_OK | MB_ICONERROR );
						return TRUE;						
					}
					if( Param )
					{
						AddProperty_Rec( RootNode, Param );
						TVITEM item;
						item.hItem = TreeView_GetSelection( GetDlgItem( hwndDlg, IDC_TREE ) );
						if( item.hItem )
						{
							item.mask = TVIF_HANDLE | TVIF_PARAM;
							TreeView_GetItem( GetDlgItem( hwndDlg, IDC_TREE ), &item );
							RefreshProperties( (OR_3DS_Node*)item.lParam );
						}

						DestroyWindow( hwndDlg );
					}
				}
				break;

				case IDCANCEL:
					DestroyWindow( hwndDlg );
				break;

			}
		break;

		default:
		break;
	}
	return FALSE;
}

BOOL CALLBACK 	TreeViewDlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	HIMAGELIST himl;  // handle to image list 
	HIMAGELIST Images;  // handle to image list 
	HBITMAP hbmp;     // handle to bitmap 
	const int CX_BITMAP=16,CY_BITMAP=16,NUM_BITMAPS=6;
	int idx;
	TreeViewHandle = hwndDlg;
	static HMENU Menu;
	static WORD MouseX,MouseY;
	LVCOLUMN Col1;
	
	switch( uMsg ) { // Respond to the message ...
		case WM_INITDIALOG: // Initialize the Controls here.
		{
			SendMessage( GetDlgItem( hwndDlg, IDC_TREE ), TVM_SETBKCOLOR , 0 , RGB(0xFF,0xFF,0xFF) );
			SendMessage( GetDlgItem( hwndDlg, IDC_PROPERTIES ), TVM_SETBKCOLOR , 0 , RGB(0xFF,0xFF,0xFF) );

			// Create the image list. 
		    if( (himl = ImageList_Create( CX_BITMAP, CY_BITMAP, 
		        FALSE, NUM_BITMAPS, 0) ) == NULL) 
		        return FALSE; 

		    // Add the open file, closed file, and document bitmaps. 
		    hbmp = (HBITMAP)LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_GIZMO ) ); 
		    idx = ImageList_Add( himl, hbmp, (HBITMAP) NULL ); 
		    DeleteObject( hbmp ); 
		    hbmp = (HBITMAP)LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_CAMERA ) ); 
		    idx = ImageList_Add( himl, hbmp, (HBITMAP) NULL ); 
		    DeleteObject( hbmp ); 
		    hbmp = (HBITMAP)LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_MESH ) ); 
		    idx = ImageList_Add( himl, hbmp, (HBITMAP) NULL ); 
		    DeleteObject( hbmp ); 
		    hbmp = (HBITMAP)LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_LIGHT ) ); 
			idx = ImageList_Add( himl, hbmp, (HBITMAP) NULL ); 
		    DeleteObject( hbmp ); 
		    hbmp = (HBITMAP)LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_UNKNOWN ) ); 
		    idx = ImageList_Add( himl, hbmp, (HBITMAP) NULL ); 
		    DeleteObject( hbmp ); 
		    hbmp = (HBITMAP)LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_SELECTED ) ); 
		    idx = ImageList_Add( himl, hbmp, (HBITMAP) NULL ); 
		    DeleteObject( hbmp ); 

		    // Fail if not all of the images were added. 
		    if( ImageList_GetImageCount( himl ) < NUM_BITMAPS) 
		        return FALSE; 
			//ImageList_SetOverlayImage(himl, idx, idx-1);

		    // Associate the image list with the tree view control. 
		    TreeView_SetImageList( GetDlgItem( hwndDlg, IDC_TREE ), himl, TVSIL_NORMAL ); 

			Images = ImageList_Create( 16, 16, FALSE, 1, 0 );
			hbmp = (HBITMAP)LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_USERDATA ) ); 
		    idx = ImageList_Add( Images, hbmp, (HBITMAP)NULL ); 
		    DeleteObject( hbmp ); 

			ListView_SetImageList( GetDlgItem( hwndDlg, IDC_PROPERTIES ), Images, LVSIL_SMALL );

			Col1.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			Col1.fmt = LVCFMT_LEFT;
			Col1.cx = 50;
			Col1.pszText = "Value";
			Col1.cchTextMax = strlen( Col1.pszText );
			Col1.iSubItem = 1;
			SendMessage( GetDlgItem( hwndDlg, IDC_PROPERTIES ), LVM_INSERTCOLUMN, 0, (LPARAM)&Col1 );
			Col1.iImage = 1;
			Col1.cx = 99;
			Col1.pszText = "Name";
			Col1.cchTextMax = strlen( Col1.pszText );			
			Col1.iSubItem = 0;
			SendMessage( GetDlgItem( hwndDlg, IDC_PROPERTIES ), LVM_INSERTCOLUMN, 0, (LPARAM)&Col1 );
			
			LoadOptions();
			UpdateOptions();
		}
		return TRUE;

		case WM_DESTROY:
		case WM_NCDESTROY:
			TreeViewHandle = NULL;
		return FALSE;

		case WM_COMMAND:
			switch( LOWORD( wParam ) )
			{
				case IDC_DELPARAM:
				{
					int i = ListView_GetNextItem( GetDlgItem( hwndDlg, IDC_PROPERTIES ), -1, LVNI_SELECTED );
					char Text[256] = "\0";
					ListView_GetItemText( GetDlgItem( hwndDlg, IDC_PROPERTIES ), i, 0, Text, 256 );
					DeleteProperty_Rec( RootNode, Text );
					TVITEM item;
					item.hItem = TreeView_GetSelection( GetDlgItem( hwndDlg, IDC_TREE ) );
					if( item.hItem)
					{
						item.mask = TVIF_HANDLE | TVIF_PARAM;
						TreeView_GetItem( GetDlgItem( hwndDlg, IDC_TREE ), &item );					
						RefreshProperties( (OR_3DS_Node*)item.lParam );
					}
				}
				return TRUE;
				
				case IDC_ADDPARAM:
					MAXInterface->RegisterDlgWnd( CreateDialog( hInstance, MAKEINTRESOURCE( IDD_ADDPARAM ), MAXInterface->GetMAXHWnd(), AddParamDlgProc ) );
				return TRUE;

				case IDC_EXPORTGEOM:
				{
					char name[256]="";
					OPENFILENAME ofn = 
					{
						sizeof(OPENFILENAME),0,0,
						"Orion3D KRD\0*.KRD\0",
						NULL,0,0,
						name,256,
						NULL,0,
						".\\",
						NULL,
						OFN_ENABLESIZING | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT,
						0,0,
						"KRD",
						NULL,NULL,NULL
					};
					
					if( GetSaveFileName( &ofn ) )
					{
						CLAIM_ENGINE

						TVITEM item;
						item.hItem = TreeView_GetSelection( GetDlgItem( hwndDlg, IDC_TREE ) );
						if( item.hItem )
						{
							item.mask = TVIF_HANDLE | TVIF_PARAM;
							SendMessage( GetDlgItem( hwndDlg, IDC_TREE ), TVM_GETITEM, 0, (LPARAM)&item );
							if( item.lParam )
							{
								/* export the hierarchy into a krd file */
								Engine->PrepareHierarchyExport();
								Engine->GetSerializer().SetExportAnimation( false );
								Engine->GetSerializer().SetExportShader( true );
								Engine->GetSerializer().SetExportHierarchy( true );
								Engine->GetSerializer().SetHierarchyStartNode(* (OR_Node*)item.lParam );
								Engine->SaveFile( name );
								/* copy textures */
								char* TargetDir = strdup( name );
								char* FileStart = strrchr( TargetDir, '\\' );
								FileStart[0] = 0;
								Wrapper.CopyTextures( TargetDir );
							}
						}
						else
						{
							Engine->Warning( "SaveKRD", "No item is selected in the hierarchy view" );
						}
						
						UNCLAIM_ENGINE
					}
				}
				break;

				case IDC_EXPORTANIM:
				{
					char name[256]="";
					OPENFILENAME ofn = 
					{
						sizeof(OPENFILENAME),0,0,
						"Orion3D ACT\0*.ACT\0",
						NULL,0,0,
						name,256,
						NULL,0,
						".\\",
						NULL,
						OFN_ENABLESIZING | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT,
						0,0,
						"ACT",
						NULL,NULL,NULL
					};
					
					if( GetSaveFileName( &ofn ) )
					{
						CLAIM_ENGINE
						TVITEM item;
						item.hItem = TreeView_GetSelection( GetDlgItem( hwndDlg, IDC_TREE ) );
						if( item.hItem )
						{
							item.mask = TVIF_HANDLE | TVIF_PARAM;
							SendMessage( GetDlgItem( hwndDlg, IDC_TREE ), TVM_GETITEM, 0, (LPARAM)&item );
							if( item.lParam )
							{
								/* export the animation into a krd file : 
									set OR_HierarchyRoot to the pseudo-root */
								Engine->PrepareHierarchyExport();
								Engine->GetSerializer().SetExportAnimation( true );
								Engine->GetSerializer().SetExportShader( false );
								Engine->GetSerializer().SetExportHierarchy( false );
								Engine->GetSerializer().SetAnimationStartNode(* (OR_Node*)item.lParam );
								Engine->GetSerializer().SetAnimationHierarchyRoot(* (OR_Node*) RootNode );

								Engine->SaveFile( name );
							}
						}
						else
						{
							Engine->Warning( "SaveKRD", "No item is selected in the hierarchy view" );
						}
						UNCLAIM_ENGINE
					}
				}
				break;
			}
		break;

		//case WM_MOUSELEAVE:
		case WM_NOTIFY:
		//case WM_LBUTTONUP:
		//case WM_KEYUP:
			switch( ((LPNMHDR)lParam)->code )
			{
				case TVN_SELCHANGED:
				{
					TVITEM item;
					item.hItem = TreeView_GetSelection( GetDlgItem( hwndDlg, IDC_TREE ) );
					if( item.hItem )
					{
						item.mask = TVIF_HANDLE | TVIF_PARAM;
						TreeView_GetItem(GetDlgItem(hwndDlg,IDC_TREE),&item);					
						RefreshProperties( (OR_3DS_Node*)item.lParam );
					}
				}
				break;
				case TVN_SETDISPINFO:
					MessageBox(NULL,"TVN_SETDISPINFO","hop",MB_OK);
				break;
/*
				case NM_DBLCLK:
				{
					if( ((LPNMHDR)lParam)->idFrom==IDC_PROPERTIES)
					{
						MAXInterface->RegisterDlgWnd(CreateDialog(hInstance , MAKEINTRESOURCE(IDD_ADDPARAM) , MAXInterface->GetMAXHWnd() , AddParamDlgProc));
						TVITEM item;
						item.hItem = TreeView_GetSelection(GetDlgItem(hwndDlg,IDC_TREE));
						if( item.hItem)
						{
							item.mask = TVIF_HANDLE | TVIF_PARAM;
							TreeView_GetItem(GetDlgItem(hwndDlg,IDC_TREE),&item);					
							RefreshProperties((Node*)item.lParam);
						}
					}
				}
*/
			}
		break;	

		default:
		break;
	}
	return FALSE;
}

void		DeleteProperty_Rec( OR_3DS_Node* CurNode, char* Property)
{
	((OR_3DS_MAXNode*)CurNode->GetMAXNode())->RemoveUserParam(Property);
	T_NodeList &List = CurNode->GetSonList();
	for( IT_NodeList it = List.begin() ; it!=List.end() ; ++it )
		DeleteProperty_Rec( (OR_3DS_Node*)*it, Property );
}

void		AddProperty_Rec( OR_3DS_Node* CurNode, OR_3DS_UserParam* Property )
{
	((OR_3DS_MAXNode*)CurNode->GetMAXNode())->SetUserParam(Property);
	T_NodeList &List = CurNode->GetSonList();
	for( IT_NodeList it = List.begin() ; it!=List.end() ; ++it)
		AddProperty_Rec( (OR_3DS_Node*)*it, Property );
}

BOOL CALLBACK 	ViewerDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DlgHandle=hwndDlg;

	switch( uMsg ) { // Respond to the message ...
		case WM_INITDIALOG: // Initialize the Controls here.
		{
			if( Engine ) Engine->GetLogManager().AddLine("\nCreating viewer rollout panel");
			HICON icone;
			icone = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FILLED));	SendMessage(GetDlgItem(DlgHandle , IDC_FILLED) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)icone);		DestroyIcon(icone);
			icone = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIRE));		SendMessage(GetDlgItem(DlgHandle , IDC_WIRE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)icone);		DestroyIcon(icone);
			icone = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POINT));	SendMessage(GetDlgItem(DlgHandle , IDC_POINT) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)icone);		DestroyIcon(icone);
			icone = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIMIZE));	SendMessage(GetDlgItem(DlgHandle , IDC_MINIMIZE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)icone);	DestroyIcon(icone);
			icone = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAXIMIZE));	SendMessage(GetDlgItem(DlgHandle , IDC_MAXIMIZE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)icone);	DestroyIcon(icone);
			icone = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLOSE));	SendMessage(GetDlgItem(DlgHandle , IDC_CLOSE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)icone);		DestroyIcon(icone);
			icone = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAY));		SendMessage(GetDlgItem(DlgHandle , IDC_PLAYPAUSE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)icone);	DestroyIcon(icone);
			icone = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CONSOLE));	SendMessage(GetDlgItem(DlgHandle , IDC_CONSOLE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)icone);	DestroyIcon(icone);
			
			if( RootNode && !RootNode->GetPlayerList().empty() )
			{
				OR_AnimationPlayer *Player = RootNode->GetPlayerList().front();
				if( Player->IsPlaying() && !TimeEvent )
				{
					TimeEvent = timeSetEvent(100,100,(LPTIMECALLBACK)UpdateTime,0,TIME_PERIODIC);
					SendMessage(GetDlgItem(DlgHandle , IDC_PLAYPAUSE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAUSE)));
				}
			}
		}
		return TRUE;

		case WM_DESTROY: // Release the Controls here.
		case WM_NCDESTROY:
			if( Engine) Engine->GetLogManager().AddLine("\nDestroying viewer rollout panel");
			if( TimeEvent) timeKillEvent(TimeEvent);TimeEvent=0;
			DlgHandle = NULL;
		return FALSE;
		
		case WM_COMMAND: // Various messages come in this way.
			switch(LOWORD(wParam)){
				case IDC_PUSH:
				{
					if( Engine ) Engine->GetLogManager().AddLine("\nUser pressed Update button");

					//Disable the button
					LONG UpdateBtnState = GetWindowLong( GetDlgItem( hwndDlg, IDC_PUSH ), GWL_STYLE ) | WS_DISABLED;
					SetWindowLong( GetDlgItem( hwndDlg, IDC_PUSH ), GWL_STYLE, UpdateBtnState );
					SetWindowPos( hwndDlg, 0, 0 ,0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED ); 
					UpdateWindow( hwndDlg );
					HCURSOR PrevCursor = SetCursor( LoadCursor( NULL, IDC_WAIT ) );

					OR_U32 Flags = 0;
					if( IsDlgButtonChecked( hwndDlg, IDC_UPDATE_ANIMS ) ) Flags |= OR_Update_Animations;
					if( IsDlgButtonChecked( hwndDlg, IDC_UPDATE_OBJECTS ) ) Flags |= OR_Update_Objects;
					if( IsDlgButtonChecked( hwndDlg, IDC_UPDATE_MATERIALS ) ) Flags |= OR_Update_Shaders;
					if( IsDlgButtonChecked( hwndDlg, IDC_UPDATE_MATRICES ) ) Flags |= OR_Update_Matrices;
					
					RootNode = Update( Flags , RootNode);
					UpdateOptions();
					if( !RootNode->GetPlayerList().empty() )
					{
						OR_AnimationPlayer *Player = RootNode->GetPlayerList().front();
						SendMessage(GetDlgItem(DlgHandle , IDC_TIMESLIDER) , TBM_SETPOS , TRUE, Player->GetTime()*ORION3D_FRAMES_PER_SEC*Player->GetAnimation()->GetDuration());
						if( Player->IsPlaying())
						{
							SendMessage(GetDlgItem(DlgHandle , IDC_PLAYPAUSE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAUSE)) );
							TimeEvent = timeSetEvent(100,100,(LPTIMECALLBACK)UpdateTime,0,TIME_PERIODIC);
						}
						else
							SendMessage(GetDlgItem(DlgHandle , IDC_PLAYPAUSE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAY)) );
					}

					//Enable the button
					UpdateBtnState &= ~WS_DISABLED;
					SetWindowLong( GetDlgItem( hwndDlg, IDC_PUSH ), GWL_STYLE, UpdateBtnState );
					SetWindowPos( hwndDlg, 0, 0 ,0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED ); 
					UpdateWindow( hwndDlg );

					SetCursor( PrevCursor );
				}
				return TRUE;

				case IDC_SAMPLING_FORCE:
					Wrapper.SetSamplingForce( IsDlgButtonChecked( hwndDlg, IDC_SAMPLING_FORCE ) );
				break;

				case IDC_SAMPLING_TRESHOLD:
					if( HIWORD(wParam) == EN_SETFOCUS ) if (AcceleratorsEnabled()) DisableAccelerators();
					if( HIWORD(wParam) == EN_KILLFOCUS ) EnableAccelerators();
					if( HIWORD(wParam) == EN_CHANGE )
						Wrapper.SetSamplingTreshold( GetDlgItemFloat( hwndDlg, IDC_SAMPLING_TRESHOLD )*OR_PI/180. );
				break;

				case IDC_SAMPLING_RATE:
					if( HIWORD(wParam) == EN_SETFOCUS ) if (AcceleratorsEnabled()) DisableAccelerators();
					if( HIWORD(wParam) == EN_KILLFOCUS ) EnableAccelerators();
					if( HIWORD(wParam) == EN_CHANGE )
						Wrapper.SetSamplingRate( 4800. / GetDlgItemFloat( hwndDlg, IDC_SAMPLING_RATE ) );
				break;

				case IDC_SAMPLING_START:
					if( HIWORD(wParam) == EN_SETFOCUS ) if (AcceleratorsEnabled()) DisableAccelerators();
					if( HIWORD(wParam) == EN_KILLFOCUS ) EnableAccelerators();
					if( HIWORD(wParam) == EN_CHANGE )
						Wrapper.SetSamplingStart( 4800*GetDlgItemFloat( hwndDlg, IDC_SAMPLING_START ) );
				break;

				case IDC_SAMPLING_END:
					if( HIWORD(wParam) == EN_SETFOCUS ) if (AcceleratorsEnabled()) DisableAccelerators();
					if( HIWORD(wParam) == EN_KILLFOCUS ) EnableAccelerators();
					if( HIWORD(wParam) == EN_CHANGE )
						Wrapper.SetSamplingEnd( 4800*GetDlgItemFloat( hwndDlg, IDC_SAMPLING_END ) );
				break;

				case IDC_CONSOLE:
				{
					OR_ShellConsoleText& Console = (OR_ShellConsoleText&)Engine->GetShellConsole();
					if( !Console.IsOpen() )
						Console.OpenConsole();
					else
						Console.CloseConsole();
				}
				return TRUE;

				case IDC_DISPGIZMOS:
					Engine->ToggleDraw(OR_GIZMO);
				return TRUE;

				case IDC_DISPLIGHTS:
					Engine->ToggleDraw(OR_LIGHT);
				return TRUE;

				case IDC_DISPCAMERAS:
					Engine->ToggleDraw(OR_CAMERA);
				return TRUE;

				case IDC_DISPAXES:
					Engine->ToggleDraw(OR_LOCAL_AXES);
				return TRUE;

				case IDC_DISPTRAJ:
					Engine->ToggleDraw(OR_TRAJECTORIES);
				return TRUE;

				case IDC_DISPBONES:
					Engine->ToggleDraw(OR_BONE);
				return TRUE;

				case IDC_SELECTVIEW:
				if( HIWORD(wParam)==CBN_SELENDOK ) {
					char CamName[OR_NAME_LENGTH];
					SelectedView = SendMessage( (HWND)lParam, CB_GETCURSEL, 0, 0);
					SendMessage( GetDlgItem( DlgHandle, IDC_SELECTVIEW ), CB_GETLBTEXT, SelectedView, (LPARAM)CamName );
					SetView( SelectedView );
				}
				return TRUE;

				case IDC_UPDATEVIEW:
					SetView( SelectedView );
				return TRUE;

				case IDC_FILLED:
					Engine->GetContext().SetDrawingMode(OR_Drawing_Filled );
				return TRUE;

				case IDC_WIRE:
					Engine->GetContext().SetDrawingMode( OR_Drawing_Wireframe );
				return TRUE;

				case IDC_POINT:
					Engine->GetContext().SetDrawingMode( OR_Drawing_Point );
				return TRUE;

				case IDC_CLOSE:
					if( Engine ) Engine->GetLogManager().AddLine( "\nUser terminate the plug-in" );
					IUtility->CloseUtility();
					ShutDown();
				return TRUE;

				case IDC_MINIMIZE:
					if( IsIconic( OrionHWND ) )
					{
						ShowWindow(OrionHWND , SW_RESTORE);
						SendMessage( GetDlgItem( DlgHandle, IDC_MINIMIZE), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(HANDLE)LoadIcon( hInstance, MAKEINTRESOURCE(IDI_MINIMIZE) ) );
					}
					else
					{
						ShowWindow(OrionHWND , SW_MINIMIZE);
						SendMessage( GetDlgItem( DlgHandle, IDC_MINIMIZE), BM_SETIMAGE, (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RESTORE) ) );
					}
				return TRUE;

				case IDC_MAXIMIZE:
					ShowWindow(OrionHWND , SW_SHOWMAXIMIZED);
				return TRUE;

				case IDC_ABOUT:
					MAXInterface->RegisterDlgWnd(CreateDialog(hInstance , MAKEINTRESOURCE(IDD_ABOUT) , MAXInterface->GetMAXHWnd(), AboutDlgProc));
				return TRUE;
				
				case IDC_PLAYPAUSE:
					if( !RootNode->GetPlayerList().empty() )
					{
						OR_AnimationPlayer *Player = RootNode->GetPlayerList().front();
						if( Engine ) Engine->GetLogManager().AddLine("\nUser toggled play/pause");
						if( Player->TogglePlayPause() )
						{
							TimeEvent = timeSetEvent(100,100,(LPTIMECALLBACK)UpdateTime,0,TIME_PERIODIC);
							SendMessage(GetDlgItem(DlgHandle , IDC_PLAYPAUSE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAUSE)));
						}
						else
						{
							if( TimeEvent ) timeKillEvent(TimeEvent);TimeEvent=0;
							SendMessage(GetDlgItem(DlgHandle , IDC_PLAYPAUSE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAY)));
						}
						if( Player->GetTime()>1.f ) Player->Restart();
					}
				return TRUE;

				case IDC_TOPMOST:
					if( IsDlgButtonChecked( hwndDlg, IDC_TOPMOST ) )
						SetWindowPos( OrionHWND , HWND_TOPMOST , 0 , 0 , 0 , 0 , SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED );
					else
						SetWindowPos( OrionHWND , HWND_NOTOPMOST , 0 , 0 , 0 , 0 , SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED );
					break;
				return TRUE;

				case IDC_BINDTIME:
					if( IsDlgButtonChecked(DlgHandle , IDC_BINDTIME) )
					{
						LONG Style;
						if( !RootNode->GetPlayerList().empty() && RootNode->GetPlayerList().front()->IsPlaying() )
							SendMessage( hwndDlg, WM_COMMAND, (WPARAM)IDC_PLAYPAUSE, (LPARAM)0 );
						Style = GetWindowLong(GetDlgItem(hwndDlg,IDC_PLAYPAUSE),GWL_STYLE) | WS_DISABLED;
						SetWindowLong( GetDlgItem( hwndDlg, IDC_PLAYPAUSE ), GWL_STYLE, Style );
						Style = GetWindowLong( GetDlgItem( hwndDlg, IDC_TIMESLIDER ), GWL_STYLE ) | WS_DISABLED;
						SetWindowLong( GetDlgItem( hwndDlg, IDC_TIMESLIDER ), GWL_STYLE, Style );
						SetTime( MAXInterface->GetTime() );
					}
					else
					{
						LONG Style;
						Style = GetWindowLong( GetDlgItem( hwndDlg, IDC_PLAYPAUSE ), GWL_STYLE ) & ~WS_DISABLED;
						SetWindowLong( GetDlgItem( hwndDlg, IDC_PLAYPAUSE ), GWL_STYLE, Style);
						Style = GetWindowLong( GetDlgItem( hwndDlg, IDC_TIMESLIDER ), GWL_STYLE )& ~WS_DISABLED;
						SetWindowLong( GetDlgItem( hwndDlg, IDC_TIMESLIDER ), GWL_STYLE, Style );
					}
				return TRUE;

				default:
				break;
			}
		break;

		case WM_HSCROLL: // Others this way...
			if( (HWND)lParam == GetDlgItem( hwndDlg, IDC_TIMESLIDER ) )
			{
				//case IDC_TIMESLIDER: if( ((LPNMHDR)lParam)->code==NM_RELEASEDCAPTURE)
					if(  !RootNode->GetPlayerList().empty() ) 
					{
						OR_AnimationPlayer* Player = RootNode->GetPlayerList().front();
						if( TimeEvent) timeKillEvent(TimeEvent);TimeEvent=0;
						Player->Pause();
						SendMessage(GetDlgItem(DlgHandle , IDC_PLAYPAUSE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAY)));
						Player->SetTime( SendMessage( GetDlgItem(DlgHandle , IDC_TIMESLIDER ), TBM_GETPOS, 0, 0)/float(ORION3D_FRAMES_PER_SEC)/Player->GetAnimation()->GetDuration() );
					}
				return TRUE;

				//default:
				//break;
			}
		break;

		// Other cases...
		default:
		break;
	}

	return FALSE;
}


BOOL CALLBACK 	AboutDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch( uMsg ) {
		case WM_INITDIALOG:
		return TRUE;
		
		case WM_DESTROY:			
		return FALSE;
		
		case WM_COMMAND:
			DestroyWindow(hwndDlg);
		return TRUE;

		default:
		break;
	}
	return FALSE;
	
}



OR_3DS_Node*	Update(int Flags, OR_3DS_Node* Noeud)
{
	bool IsPlaying=false;
	OR_Float Time=0.f;

	CLAIM_ENGINE
		
	if( RootNode && !RootNode->GetPlayerList().empty() )
	{
		OR_AnimationPlayer* Player = RootNode->GetPlayerList().front();
		Player->Pause();
		Time = Player->GetTime();
		if( TimeEvent) timeKillEvent(TimeEvent);TimeEvent=0;
	}
	
	if( Engine) Engine->GetLogManager().AddString("\nUpdating with flags %d");
	if( Engine) Engine->GetLogManager().AddIndent();

	UNCLAIM_ENGINE

	UpdateNode = Noeud;
	UpdateFlags = Flags;

	HANDLE EventWait = CreateEvent(NULL , FALSE , FALSE , ORION3D_EVENT_NEED_MAJ);
	HANDLE EventDone = CreateEvent(NULL , FALSE , FALSE , ORION3D_EVENT_MAJ_DONE);

	Engine->GetLogManager().AddIndent();
	Engine->GetLogManager().AddLine("\nWaiting for shaders update");
	Engine->GetLogManager().AddIndent();

	WaitForSingleObject(EventWait , INFINITE);
	CloseHandle(EventWait);

	Engine->GetLogManager().SubIndent();
	Engine->GetLogManager().AddLine("\nOK");
	
	Noeud = UpdateNode;

	CLAIM_ENGINE
		
	if( Noeud && !Noeud->GetPlayerList().empty() )
	{
		OR_AnimationPlayer* Player = Noeud->GetPlayerList().front();
		Player->SetTime(Time);
		if( IsPlaying) Player->Play();		
	}

	UNCLAIM_ENGINE

	if( Engine) Engine->GetLogManager().SubIndent();

	SendMessage(GetDlgItem(DlgHandle , IDC_PLAYPAUSE) , BM_SETIMAGE , (WPARAM)IMAGE_ICON , (LPARAM)(HANDLE)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAY)));
	SetEvent(EventDone);
	CloseHandle(EventDone);	

	if( Engine) Engine->GetLogManager().SubIndent();
	if( Engine) Engine->GetLogManager().AddLine("\nUpdate done");

	return Noeud;
}



void		LoadOptions()
{
	HKEY	KeyHandle;
	ULONG	ValSize = sizeof(DWORD);
	DWORD	ValType = REG_DWORD;
	DWORD	DispGizmos, DispLights, DispCameras, DispAxes,
			DispTraj, DispBones, DrawMode, TopMost, BindTime,
			UpdateAnims, UpdateObjects, UpdateMatrices, UpdateMaterials;
	
	CLAIM_ENGINE
	
	if( RegOpenKey(HKEY_LOCAL_MACHINE , "Software\\Orion3D\\Orion3DMAX\\Viewer" , &KeyHandle)!=ERROR_SUCCESS)
	{
		DispGizmos = 1;
		DispLights = 1;
		DispCameras = 1;
		DispAxes = 1;
		DrawMode = 0;
		SelectedView = 0;
		TopMost = 1;
		BindTime = 0;
		DispTraj = 1;
		DispBones = 1;
	}
	else
	{
		if( RegQueryValueEx(KeyHandle , "DispGizmos",	NULL , &ValType , (BYTE*)&DispGizmos,	&ValSize)	!=ERROR_SUCCESS) DispGizmos = 1;
		if( RegQueryValueEx(KeyHandle , "DispLights",	NULL , &ValType , (BYTE*)&DispLights,	&ValSize)	!=ERROR_SUCCESS) DispLights = 1;
		if( RegQueryValueEx(KeyHandle , "DispCameras",	NULL , &ValType , (BYTE*)&DispCameras,	&ValSize)	!=ERROR_SUCCESS) DispCameras = 1;
		if( RegQueryValueEx(KeyHandle , "DispAxes",		NULL , &ValType , (BYTE*)&DispAxes,		&ValSize)	!=ERROR_SUCCESS) DispAxes = 1;
		if( RegQueryValueEx(KeyHandle , "DispTraj",		NULL , &ValType , (BYTE*)&DispTraj,		&ValSize)	!=ERROR_SUCCESS) DispTraj = 1;
		if( RegQueryValueEx(KeyHandle , "DispBones",	NULL , &ValType , (BYTE*)&DispBones,	&ValSize)	!=ERROR_SUCCESS) DispBones = 1;
		if( RegQueryValueEx(KeyHandle , "SelectedView",	NULL , &ValType , (BYTE*)&SelectedView,	&ValSize)	!=ERROR_SUCCESS) SelectedView = 0;
		if( RegQueryValueEx(KeyHandle , "DrawMode",		NULL , &ValType , (BYTE*)&DrawMode,		&ValSize)	!=ERROR_SUCCESS) DrawMode = 0;
		if( RegQueryValueEx(KeyHandle , "TopMost",		NULL , &ValType , (BYTE*)&TopMost,		&ValSize)	!=ERROR_SUCCESS) TopMost = 1;
		if( RegQueryValueEx(KeyHandle , "BindTime",		NULL , &ValType , (BYTE*)&BindTime,		&ValSize)	!=ERROR_SUCCESS) BindTime = 0;
		if( RegQueryValueEx(KeyHandle , "UpdateAnims",		NULL , &ValType , (BYTE*)&UpdateAnims,		&ValSize)	!=ERROR_SUCCESS) UpdateAnims = 0;
		if( RegQueryValueEx(KeyHandle , "UpdateObjects",	NULL , &ValType , (BYTE*)&UpdateObjects,	&ValSize)	!=ERROR_SUCCESS) UpdateObjects = 0;
		if( RegQueryValueEx(KeyHandle , "UpdateMatrices",	NULL , &ValType , (BYTE*)&UpdateMatrices,	&ValSize)	!=ERROR_SUCCESS) UpdateMatrices = 0;
		if( RegQueryValueEx(KeyHandle , "UpdateMaterials",	NULL , &ValType , (BYTE*)&UpdateMaterials,	&ValSize)	!=ERROR_SUCCESS) UpdateMaterials = 0;

		RegCloseKey(KeyHandle);
	}
	CheckDlgButton(DlgHandle , IDC_DISPGIZMOS,	DispGizmos);
	CheckDlgButton(DlgHandle , IDC_DISPLIGHTS,	DispLights);
	CheckDlgButton(DlgHandle , IDC_DISPCAMERAS, DispCameras);
	CheckDlgButton(DlgHandle , IDC_DISPAXES,	DispAxes);
	CheckDlgButton(DlgHandle , IDC_DISPTRAJ,	DispTraj);
	CheckDlgButton(DlgHandle , IDC_DISPBONES,	DispBones);
	CheckDlgButton(DlgHandle , IDC_TOPMOST,		TopMost);	
	CheckDlgButton(DlgHandle , IDC_BINDTIME,	BindTime);	
	CheckDlgButton(DlgHandle , IDC_UPDATE_ANIMS,	UpdateAnims);	
	CheckDlgButton(DlgHandle , IDC_UPDATE_OBJECTS,	UpdateObjects);	
	CheckDlgButton(DlgHandle , IDC_UPDATE_MATRICES,	UpdateMatrices);	
	CheckDlgButton(DlgHandle , IDC_UPDATE_MATERIALS,UpdateMaterials);	
	switch(DrawMode)
	{
		case 2:
			CheckDlgButton(DlgHandle , IDC_POINT,	1);
			Engine->GetContext().SetDrawingMode(OR_Drawing_Point);
		break;
		
		case 1:
			CheckDlgButton(DlgHandle , IDC_WIRE,	1);
			Engine->GetContext().SetDrawingMode(OR_Drawing_Wireframe);
		break;
		
		case 0:
		default:
			CheckDlgButton(DlgHandle , IDC_FILLED,	1);
			Engine->GetContext().SetDrawingMode(OR_Drawing_Filled);
		break;
	}


	SendMessage(GetDlgItem(DlgHandle , IDC_SELECTVIEW ) , CB_RESETCONTENT, 0, 0);
	OR_CameraManager& CameraManager = Engine->GetCameraManager();
	for( IT_ManagerMap_Template(OR_Camera) itCam = CameraManager.begin() ; itCam != CameraManager.end() ; ++itCam )
	{
		if( !(*itCam).second->GetName().equals( ORION3D_FLYING_CAM ) )
			SendMessage( GetDlgItem( DlgHandle , IDC_SELECTVIEW ) , CB_ADDSTRING, 0, (LPARAM) (*itCam).second->GetName().const_val() );
	}
	
	SendMessage(GetDlgItem(DlgHandle , IDC_SELECTVIEW ) , CB_INSERTSTRING, 0, (LPARAM) "None");
	SendMessage(GetDlgItem(DlgHandle , IDC_SELECTVIEW ) , CB_INSERTSTRING, 1, (LPARAM) "Current Viewport");
	SetView(SelectedView);
	SendMessage(GetDlgItem(DlgHandle , IDC_SELECTVIEW), CB_SETCURSEL, (WPARAM)SelectedView, 0);

	if( DispGizmos)		Engine->EnableDraw(OR_GIZMO);		else Engine->DisableDraw(OR_GIZMO);
	if( DispLights)		Engine->EnableDraw(OR_LIGHT);		else Engine->DisableDraw(OR_LIGHT);
	if( DispCameras)	Engine->EnableDraw(OR_CAMERA);		else Engine->DisableDraw(OR_CAMERA);
	if( DispAxes)		Engine->EnableDraw(OR_LOCAL_AXES);	else Engine->DisableDraw(OR_LOCAL_AXES);
	if( DispTraj)		Engine->EnableDraw(OR_TRAJECTORIES);else Engine->DisableDraw(OR_TRAJECTORIES);
	if( DispBones)		Engine->EnableDraw(OR_BONE);		else Engine->DisableDraw(OR_BONE);
	if( BindTime && RootNode && !RootNode->GetPlayerList().empty())
	{
		OR_AnimationPlayer* Player = RootNode->GetPlayerList().front();
		Player->SetTime(MAXInterface->GetTime()/4800./Player->GetAnimation()->GetDuration());
	}
	if( BindTime)
	{
		LONG Style;
		Style = GetWindowLong(GetDlgItem(DlgHandle,IDC_PLAYPAUSE),GWL_STYLE) | WS_DISABLED;
		SetWindowLong(GetDlgItem(DlgHandle,IDC_PLAYPAUSE),GWL_STYLE,Style);
		Style = GetWindowLong(GetDlgItem(DlgHandle,IDC_TIMESLIDER),GWL_STYLE)| WS_DISABLED;
		SetWindowLong(GetDlgItem(DlgHandle,IDC_TIMESLIDER),GWL_STYLE,Style);
		SetTime( MAXInterface->GetTime() );
	}	

	SetDlgItemFloat( DlgHandle, IDC_SAMPLING_TRESHOLD, 180./OR_PI*Wrapper.GetSamplingTreshold() );
	SetDlgItemFloat( DlgHandle, IDC_SAMPLING_RATE, 4800./Wrapper.GetSamplingRate() );
	CheckDlgButton( DlgHandle, IDC_SAMPLING_FORCE, Wrapper.GetSamplingForce() );
	SetDlgItemFloat( DlgHandle, IDC_SAMPLING_END, Wrapper.GetSamplingEnd()/4800. );
	SetDlgItemFloat( DlgHandle, IDC_SAMPLING_START, Wrapper.GetSamplingStart()/4800. );
	
	UNCLAIM_ENGINE
		
	if( OrionHWND && TopMost ) SetWindowPos( OrionHWND , HWND_TOPMOST , 0 , 0 , 0 , 0 , SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED );

}

void		SaveOptions()
{
	HKEY	KeyHandle;
	LONG	ValSize = sizeof(DWORD);
	DWORD	DispGizmos, DispLights, DispCameras, DispAxes,
			DispTraj, DispBones, DrawMode, TopMost, BindTime,
			UpdateAnims, UpdateObjects, UpdateMatrices, UpdateMaterials;
	
	RegCreateKey(HKEY_LOCAL_MACHINE , "Software\\Orion3D\\Orion3DMAX\\Viewer" , &KeyHandle);

	DispGizmos	= IsDlgButtonChecked(DlgHandle , IDC_DISPGIZMOS);
	DispLights	= IsDlgButtonChecked(DlgHandle , IDC_DISPLIGHTS);
	DispCameras	= IsDlgButtonChecked(DlgHandle , IDC_DISPCAMERAS);
	DispAxes	= IsDlgButtonChecked(DlgHandle , IDC_DISPAXES);
	DispTraj	= IsDlgButtonChecked(DlgHandle , IDC_DISPTRAJ);
	DispBones	= IsDlgButtonChecked(DlgHandle , IDC_DISPBONES);
	TopMost		= IsDlgButtonChecked(DlgHandle , IDC_TOPMOST);
	BindTime	= IsDlgButtonChecked(DlgHandle , IDC_BINDTIME);
	UpdateAnims		= IsDlgButtonChecked(DlgHandle , IDC_UPDATE_ANIMS );
	UpdateObjects	= IsDlgButtonChecked(DlgHandle , IDC_UPDATE_OBJECTS );
	UpdateMatrices	= IsDlgButtonChecked(DlgHandle , IDC_UPDATE_MATRICES );
	UpdateMaterials	= IsDlgButtonChecked(DlgHandle , IDC_UPDATE_MATERIALS );
	
	if( IsDlgButtonChecked(DlgHandle,IDC_POINT)==BST_CHECKED) DrawMode=2;
	else if( IsDlgButtonChecked(DlgHandle,IDC_WIRE)==BST_CHECKED) DrawMode=1;
	else DrawMode=0;

	RegSetValueEx(KeyHandle , "DispGizmos" ,	0 , REG_DWORD , (UBYTE*)&DispGizmos,	ValSize );
	RegSetValueEx(KeyHandle , "DispLights" ,	0 , REG_DWORD , (UBYTE*)&DispLights,	ValSize );
	RegSetValueEx(KeyHandle , "DispCameras",	0 , REG_DWORD , (UBYTE*)&DispCameras,	ValSize );
	RegSetValueEx(KeyHandle , "DispAxes",		0 , REG_DWORD , (UBYTE*)&DispAxes,		ValSize );
	RegSetValueEx(KeyHandle , "DispTraj",		0 , REG_DWORD , (UBYTE*)&DispTraj,		ValSize );
	RegSetValueEx(KeyHandle , "DispBones",		0 , REG_DWORD , (UBYTE*)&DispBones,		ValSize );
	RegSetValueEx(KeyHandle , "SelectedView",	0 , REG_DWORD , (UBYTE*)&SelectedView,	ValSize );
	RegSetValueEx(KeyHandle , "DrawMode",		0 , REG_DWORD , (UBYTE*)&DrawMode,		ValSize );
	RegSetValueEx(KeyHandle , "TopMost",		0 , REG_DWORD , (UBYTE*)&TopMost,		ValSize );
	RegSetValueEx(KeyHandle , "BindTime",		0 , REG_DWORD , (UBYTE*)&BindTime,		ValSize );
	RegSetValueEx(KeyHandle , "UpdateAnims",	0 , REG_DWORD , (UBYTE*)&UpdateAnims,	ValSize );
	RegSetValueEx(KeyHandle , "UpdateObjects",	0 , REG_DWORD , (UBYTE*)&UpdateObjects,	ValSize );
	RegSetValueEx(KeyHandle , "UpdateMatrices",	0 , REG_DWORD , (UBYTE*)&UpdateMatrices,ValSize );
	RegSetValueEx(KeyHandle , "UpdateMaterials",0 , REG_DWORD , (UBYTE*)&UpdateMaterials,ValSize );

	RegCloseKey(KeyHandle);
}


void		UpdateOptions()
{
	char NbMeshes[10] , NbGizmos[10] , NbCameras[10] , NbLights[10];

	CLAIM_ENGINE

	sprintf(NbMeshes,	"%d" , Engine->GetMeshManager().GetNbElements());
	sprintf(NbGizmos,	"%d" , Engine->GetGizmoManager().GetNbElements()-2);
	sprintf(NbCameras,	"%d" , Engine->GetCameraManager().GetNbElements()-1);
	sprintf(NbLights,	"%d" , Engine->GetLightManager().GetNbElements()-1);
	
	SendDlgItemMessage(DlgHandle , IDC_NBMESHES,	WM_SETTEXT , 0 , (LPARAM)(LPCTSTR)NbMeshes);
	SendDlgItemMessage(DlgHandle , IDC_NBGIZMOS,	WM_SETTEXT , 0 , (LPARAM)(LPCTSTR)NbGizmos);
	SendDlgItemMessage(DlgHandle , IDC_NBCAMERAS,	WM_SETTEXT , 0 , (LPARAM)(LPCTSTR)NbCameras);
	SendDlgItemMessage(DlgHandle , IDC_NBLIGHTS,	WM_SETTEXT , 0 , (LPARAM)(LPCTSTR)NbLights);

	if( SelectedView==CB_ERR) SelectedView=0;

	SendMessage(GetDlgItem(DlgHandle , IDC_SELECTVIEW ) , CB_RESETCONTENT, 0, 0);
	OR_CameraManager &CameraManager = Engine->GetCameraManager();
	for( IT_ManagerMap_Template(OR_Camera) itCam = CameraManager.begin() ; itCam != CameraManager.end() ; ++itCam )
	{
		if( !(*itCam).second->GetName().equals( ORION3D_FLYING_CAM ) )
			SendMessage(GetDlgItem(DlgHandle , IDC_SELECTVIEW ) , CB_ADDSTRING, 0, (LPARAM) (*itCam).second->GetName().const_val() );
	}
	
	SendMessage(GetDlgItem(DlgHandle , IDC_SELECTVIEW ) , CB_INSERTSTRING, 0, (LPARAM) "None");
	SendMessage(GetDlgItem(DlgHandle , IDC_SELECTVIEW ) , CB_INSERTSTRING, 1, (LPARAM) "Current Viewport");
	SetView(SelectedView);
	SendMessage(GetDlgItem(DlgHandle , IDC_SELECTVIEW), CB_SETCURSEL, (WPARAM)SelectedView, 0);
	if( RootNode->GetPlayerList().empty())
		SendMessage(GetDlgItem(DlgHandle , IDC_TIMESLIDER), TBM_SETRANGE, TRUE, 0);
	else
		SendMessage(GetDlgItem(DlgHandle , IDC_TIMESLIDER), TBM_SETRANGE, TRUE, MAKELONG(0 , RootNode->GetPlayerList().front()->GetAnimation()->GetDuration()*ORION3D_FRAMES_PER_SEC));

	RefreshTree();

	UNCLAIM_ENGINE
}


void	SetView(DWORD &n)
{
	CLAIM_ENGINE
	//Sometimes n=0xFFFFFFF (vive les bugs de windows)
	if( n>1 && n>Engine->GetCameraManager().GetNbElements()) 
		n=Engine->GetCameraManager().GetNbElements()-1;

	OR_Camera* FlyingCam = Engine->GetCameraManager().GetElement( ORION3D_FLYING_CAM );
	switch( n)	{
		//Current viewport
		case 1:
		{
			ViewExp* Viewport;
			Matrix3 coordSysTM,aTM;
			Rect rect;
			float Aspect;
			
			Viewport = MAXInterface->GetActiveViewport();
			Viewport->GetAffineTM(aTM);
			coordSysTM = Inverse(aTM);
			
			FlyingCam->SetRelativeMatrix( OR_3DS_Utils::ToOR_Matrix( coordSysTM ) );
			GetClientRectP( Viewport->GetHWnd(), &rect );
			Aspect = float( rect.w() )/float( rect.h() );
			FlyingCam->SetAspect( Aspect );
			if( Viewport->IsPerspView()==TRUE )
			{
				FlyingCam->SetFovy( Viewport->GetFOV()*180./OR_PI/Aspect );
				FlyingCam->SetOrtho( false );
				float test = Viewport->GetScreenScaleFactor( Viewport->MapScreenToView( IPoint2(0.,0.), Viewport->GetFocalDist() ) );
				FlyingCam->SetFar( test*Viewport->GetFocalDist() );
				FlyingCam->SetNear( Viewport->GetFocalDist()/test );
			}
			else
			{
				Point3 P1 = Viewport->MapScreenToView(IPoint2(1.,1.),1);
				FlyingCam->SetFovy(2.*fabs(P1.x) );
				FlyingCam->SetOrtho( true );
				FlyingCam->SetFar( 3000. );
				FlyingCam->SetNear( -3000. );
				FlyingCam->GetRelativeMatrix().SetTranslation( OR_Vector3D(0,0,0) );
			}
			
			MAXInterface->ReleaseViewport( Viewport );
			SelectedCam = NULL;
		break;
		}

		//Free or error
		case CB_ERR:
		case 0:
			if( SelectedCam )
			{
				FlyingCam->SetRelativeMatrix( SelectedCam->GetAbsoluteMatrix() );
				FlyingCam->SetOrtho(SelectedCam->GetOrtho());
				FlyingCam->SetFovy(SelectedCam->GetFovy());
				FlyingCam->SetAspect(SelectedCam->GetAspect());
				FlyingCam->SetNear(SelectedCam->GetNear());
				FlyingCam->SetFar(SelectedCam->GetFar());
			}
			SelectedCam = NULL;
		break;

		//other
		default:
		{
			char CamName[ OR_NAME_LENGTH ];
			SendMessage( GetDlgItem( DlgHandle, IDC_SELECTVIEW ), CB_GETLBTEXT, n, (LPARAM)CamName );						
			SelectedCam = Engine->GetCameraManager().GetElement(CamName);
			FlyingCam->SetRelativeMatrix( SelectedCam->GetAbsoluteMatrix() );
			FlyingCam->SetOrtho(SelectedCam->GetOrtho());
			FlyingCam->SetFovy(SelectedCam->GetFovy());
			FlyingCam->SetAspect(SelectedCam->GetAspect());
			FlyingCam->SetNear(SelectedCam->GetNear());
			FlyingCam->SetFar(SelectedCam->GetFar());
		}
		break;
	}

	UNCLAIM_ENGINE
}


void CALLBACK	UpdateTime( UINT wTimerID, UINT wMsg, DWORD dwUser, DWORD dw1, DWORD dw2 )
{
	CLAIM_ENGINE
	TimeEvent = wTimerID;
	if( RootNode && !RootNode->GetPlayerList().empty() )
	{
		OR_AnimationPlayer* Player = RootNode->GetPlayerList().front();
		PostMessage( GetDlgItem( DlgHandle , IDC_TIMESLIDER ), TBM_SETPOS, TRUE, Player->GetTime()*ORION3D_FRAMES_PER_SEC*Player->GetAnimation()->GetDuration() );
	}
	else
	{		 
		PostMessage( GetDlgItem( DlgHandle , IDC_PLAYPAUSE ), BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(HANDLE)LoadIcon( hInstance, MAKEINTRESOURCE(IDI_PLAY) ) );
		TimeEvent = 0;
		timeKillEvent( wTimerID );
	}	
	UNCLAIM_ENGINE
}



void RefreshTree()
{
	TreeView_DeleteAllItems( GetDlgItem( TreeViewHandle, IDC_TREE ) );
	HTREEITEM root = RefreshTree_Rec( RootNode, TVI_ROOT );
	TreeView_EnsureVisible( GetDlgItem( TreeViewHandle, IDC_TREE ), root );
	TreeView_Select( GetDlgItem( TreeViewHandle, IDC_TREE ), root, TVGN_CARET | TVGN_DROPHILITE | TVGN_FIRSTVISIBLE);
	TreeView_Expand( GetDlgItem( TreeViewHandle, IDC_TREE ), root, TVE_EXPAND | TVE_EXPANDPARTIAL );
	RefreshProperties( RootNode );
}


HTREEITEM RefreshTree_Rec( OR_3DS_Node* curnode, HTREEITEM Father )
{
	int image=4;
	if( !curnode ) return NULL;
	if( curnode->GetObject() )
		switch( GetGlobalType( curnode->GetObject()->GetType() ) )
		{
			case OR_GIZMO:	image=0;break;
			case OR_CAMERA:	image=1;break;
			case OR_MESH:	image=2;break;
			case OR_LIGHT:	image=3;break;
		}

	HTREEITEM curitem = TreeViewAddItem( GetDlgItem( TreeViewHandle, IDC_TREE ), Father, TVI_LAST, curnode->GetObject()->GetName().const_val(), image , true, (LPARAM)curnode );

	T_NodeList &List = curnode->GetSonList();
	for( IT_NodeList it=List.begin() ; it!=List.end() ; ++it )
		RefreshTree_Rec( (OR_3DS_Node*)*it, curitem );
	
	return curitem;
}

HTREEITEM TreeViewAddItem(HWND HWNDTree, HTREEITEM Father, HTREEITEM Position, const char* Text, int image , bool checked, LPARAM custom)
{
	LPTVINSERTSTRUCT tvis = new TVINSERTSTRUCT;
	tvis->hParent = Father;
	tvis->hInsertAfter = Position;
	tvis->item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_STATE | TVIF_PARAM;
	tvis->item.stateMask = TVIS_STATEIMAGEMASK;
	tvis->item.state = TVIS_EXPANDED | INDEXTOSTATEIMAGEMASK(checked? 2:1);
	tvis->item.pszText = (char*)Text;
	tvis->item.cchTextMax = strlen(tvis->item.pszText);
	tvis->item.iImage = image;
	tvis->item.iSelectedImage = image;
	tvis->item.lParam = custom;
	HTREEITEM Result = (HTREEITEM)SendMessage( HWNDTree, TVM_INSERTITEM, 0, (LPARAM)tvis );
	delete tvis;
	return Result;
}





void	RefreshProperties( OR_3DS_Node* node )
{
	ListView_DeleteAllItems( GetDlgItem( TreeViewHandle, IDC_PROPERTIES ) );
	int i=0;
	if( !node) return;
	OR_3DS_UserParam* Param = ((OR_3DS_MAXNode*)node->GetMAXNode())->GetUserParam( i );
	while(Param)
	{
		LVITEM item;
		item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		item.iImage = 0;
		item.pszText = strdup( Param->Name );
		item.cchTextMax = strlen( item.pszText );
		item.state = 0;
		item.stateMask = 0;
		item.iSubItem = 0;
		int index = SendMessage( GetDlgItem( TreeViewHandle, IDC_PROPERTIES ), LVM_INSERTITEM, 0, (LPARAM)&item );
		item.mask = LVIF_TEXT | LVIF_STATE;
		if( Param->Type==OR_3DS_UserParam::UserParam_U32)
		{
			char* Name = new char[10];
			sprintf(Name,"%d",*Param->Data);
			item.pszText = Name;
		}
		else
			item.pszText = Param->Data;
		item.cchTextMax = strlen(item.pszText);
		item.iSubItem = 1;
		item.iItem = index;
		SendMessage( GetDlgItem( TreeViewHandle, IDC_PROPERTIES ), LVM_SETITEM, index , (LPARAM)&item );
		if( Param->Type==OR_3DS_UserParam::UserParam_U32 ) OR_DELETEARRAY( item.pszText );

		Param = ((OR_3DS_MAXNode*)node->GetMAXNode())->GetUserParam(++i);
	}
}


///Close orion3d and the rollout panel
int		ShutDown()
{
	if( TimeEvent ) timeKillEvent( TimeEvent );TimeEvent = 0;
	if( !Engine ) return 0;
	if( Engine ) Engine->GetLogManager().AddLine( "\nTerminating Orion3D..." );
	if( Engine ) Engine->GetLogManager().AddIndent();
	MAXInterface->UnRegisterDlgWnd( OrionHWND );

	SendMessage( OrionHWND, WM_CLOSE, 0, 0 );
	DWORD CallTime = timeGetTime();
	while( Lock == true )
	{
		Sleep( 30 );
		DWORD LastTime = timeGetTime() - CallTime;
		if( LastTime > 5000 )
		{
			//allons-y gaiement
			TerminateThread( EngineThreadHandle, 0 );
			Lock = false;
		}
	}
	EnterCriticalSection( &Critic );
	DeleteCriticalSection( &Critic );
	CloseHandle( EngineThreadHandle );
	OR_DELETE( Engine );
	OR_DELETE( pInputOutput );

	SceneAnim = NULL;
	RootNode = NULL;
	OrionHWND = NULL;
	MAXInterface = NULL;
	IUtility = NULL;
	Wrapper.SetEngine( NULL );
	Wrapper.SetInterface( NULL );
	Wrapper.SetIUtil( NULL );	
	return 0;
}


void		CloseAtExit()
{
	if( DlgHandle!=NULL)
		SendMessage( DlgHandle , WM_COMMAND , IDC_CLOSE , 0 );
	else if( Engine )
		ShutDown();	
}


void SetTime( TimeValue Time )
{
	if( !Engine ) return;
	if( !IsDlgButtonChecked( DlgHandle, IDC_BINDTIME ) ) return;
	CLAIM_ENGINE
	if( RootNode && !RootNode->GetPlayerList().empty() )
	{
		OR_AnimationPlayer* Player = RootNode->GetPlayerList().front();
		float t = Time/4800./Player->GetAnimation()->GetDuration();
		t = max(min(t,1),0);
		Player->SetTime(t);
		SendMessage( GetDlgItem( DlgHandle , IDC_TIMESLIDER ) , TBM_SETPOS , TRUE, t*ORION3D_FRAMES_PER_SEC*Player->GetAnimation()->GetDuration() );
	}
	UNCLAIM_ENGINE
}