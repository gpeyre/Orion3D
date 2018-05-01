#include "../stdafx.h"
#include "Interface_Orion3D.h"

OR_Bool		CtrlPressed = false;
bool		BoutG=false;
bool		BoutD=false;

DWORD	Go(void * MaxInterface)
{

	InitializeCriticalSection( &Critic );

	CLAIM_ENGINE

	if (Engine) Engine->GetLogManager().AddLine("\nStarting Orion3D...");
	
 	if( !InitEngine((Interface*)MaxInterface) )
	{
		MessageBox(NULL , "Failed to initialise Orion3D" , "Orion3DMAX Viewer : Error" , MB_OK | MB_ICONERROR);
		LeaveCriticalSection( &Critic );
		return 0;
	}
	HANDLE Event = OpenEvent( EVENT_ALL_ACCESS, FALSE, ORION3D_EVENT_START );
	SetEvent(Event);
	CloseHandle(Event);

	UNCLAIM_ENGINE

	Lock = true;
	Engine->MainLoop();
	Lock = false;
	return 0;
}

int InitEngine(Interface* MaxInterface)
{
	Engine = new OR_Toolkit;
	int argc[] = {1};
	char* argv[] = {"Orion3DMAX.dle"};
	float Default_Light_Ambient[] = { .0f , .0f , .0f , 1.f };
	float Default_Light_Diffuse[] = { .8f , .8f , .8f , 1.f };
	float Default_Light_Specular[] = { .8f , .8f , .8f , 1.f };
	float Global_Ambient[4]={ 0,0,0,1.f };
	float CamFreePos[3] = { 0,0,5 };
	float Default_Shader_Ambient[4] = { .58f , .58f , .58f , 1.f };
	float Default_Shader_Diffuse[4] = { .58f , .58f , .58f , 1.f };
	float Default_Shader_Specular[4] = { .31f , .31f , .31f , 1.f };
	float Default_Shader_Shine = 32;


	Rect rect;
	ViewExp* Viewport = MaxInterface->GetActiveViewport();
	GetWindowRect( Viewport->GetHWnd(), &rect );
	MaxInterface->ReleaseViewport( Viewport );	

	if (!Engine) return 0;
	pInputOutput = new OR_InputOutput_Win32( *Engine );
	if( !pInputOutput )
	{
		delete Engine;
		return 0;
	}
	/* register the wrapper used for input.output */
	Engine->SetInputOutput(*pInputOutput);
	OrionHWND = pInputOutput->Initialisation_Win32( hInstance, NULL, WS_VISIBLE  | WS_BORDER | WS_THICKFRAME| WS_CAPTION, ORION3D_WINDOW_TITLE , rect.w()+8 , rect.h()+27 , rect.x()-5 , rect.y()-25 );
	if( OrionHWND == NULL ) 
	{
		delete Engine;
		delete pInputOutput;
		return 0;
	}
	MaxInterface->RegisterDlgWnd( OrionHWND );

	pInputOutput->SetIdleFunc( Idlefunc );
	pInputOutput->SetDisplayFunc( Drawfunc );
	pInputOutput->SetMotionFunc( Mousefunc );
	pInputOutput->SetKeyPressedFunc( Keyboard );
	pInputOutput->SetKeyReleasedFunc( Keyboardreleased );
	pInputOutput->SetMouseClicFunc( Mouseclick );

	Engine->InitGraphics();

	/* create a free camera ***************************************/
	Engine->Select( OR_CAMERA, Engine->AddFreeCamera() );
	Engine->Setfv( OR_CAMERA_Pos, CamFreePos );
	Engine->GetCameraManager().GetElementSelected()->SetName( ORION3D_FLYING_CAM );
	Engine->AddScreenViewPort( 1 );
	Engine->SetViewPortDimensions( 0,0,1,1 );
	Engine->SetViewportCamera();
	
	Engine->Setfv( OR_LIGHT_GlobalAmbient, Global_Ambient );

	// create a default lighting
	OR_Light_FreeDirect* Omni = new OR_Light_FreeDirect();
	Omni->SetName( ORION3D_DEFAULT_LIGHT );
	OR_3DS_Node* OmniNode = new OR_3DS_Node;
	OmniNode->SetObject(*Omni);
	OR_Node* CamNode = Engine->GetHierarchyTree().GetNodeByName( ORION3D_FLYING_CAM );							
	OmniNode->SetFather( CamNode );
	CamNode->AddSonLast( *OmniNode );
	Omni->Posit(OR_Vector3D(0,0,10));
	Omni->SetAmbient( Default_Light_Ambient );
	Omni->SetDiffuse( Default_Light_Diffuse);
	Omni->SetSpecular( Default_Light_Specular );
	Omni->SetName( ORION3D_DEFAULT_LIGHT );
	Engine->GetLightManager().AddLight( Omni );

	RootNode=new OR_3DS_Node;
	OR_PointGizmo* MAXSceneRoot = new OR_PointGizmo();
	MAXSceneRoot->SetName( OR_String( MaxInterface->GetRootNode()->GetName() ).replace( ' ', '_' ) );
	RootNode->SetObject( *MAXSceneRoot );
	RootNode->SetMAXNode( MaxInterface->GetRootNode() );
	Engine->GetGizmoManager().AddElement( MAXSceneRoot );
	Engine->GetHierarchyTree().GetRootNode()->AddSonLast( *RootNode );
	int test = 3;

	Engine->GetContext().SetLocalViewer( true );
	Engine->GetContext().SetPerspectiveCorrection( true );

	Engine->GetShellKernel().SetQuitFunc( Orion3D_quit );

	return 1;
}


void	Idlefunc()
{
	HANDLE EventWait = OpenEvent(EVENT_ALL_ACCESS , FALSE ,ORION3D_EVENT_NEED_MAJ);
	if (EventWait)
	{
		Engine->GetLogManager().AddLine("\nUpdating scene...");
		Engine->GetLogManager().AddIndent();

		UpdateNode = Wrapper.Update( UpdateFlags, UpdateNode );
		if (Engine->GetLightManager().GetNbElements()>1)
			Engine->GetLightManager().GetElement(ORION3D_DEFAULT_LIGHT)->Disable();
		else
			Engine->GetLightManager().GetElement(ORION3D_DEFAULT_LIGHT)->Enable();

		HANDLE EventDone = OpenEvent(EVENT_ALL_ACCESS , FALSE , ORION3D_EVENT_MAJ_DONE);

		Engine->GetLogManager().SubIndent();
		Engine->GetLogManager().AddLine("\nDone");
		SetEvent(EventWait);
		CloseHandle(EventWait);
		WaitForSingleObject(EventDone , INFINITE);
		CloseHandle(EventDone);
		//The materials are to be retrieved by the thread dealing with opengl
		//or the textures wouldn't be loaded
		//ReloadTextures();
	}

	CLAIM_ENGINE
	Engine->Update();
	if ( SelectedView>1 && SelectedCam )
	{
		OR_Camera* pCam = Engine->GetCameraManager().GetElement( ORION3D_FLYING_CAM );
		if(pCam != NULL)
			pCam->SetAbsoluteMatrix( SelectedCam->GetAbsoluteMatrix() );
	}
	Engine->PostReDisplay();
	UNCLAIM_ENGINE
	Sleep( 30 );
}

void	Drawfunc()
{
	CLAIM_ENGINE
	Engine->GetContext().ForceDrawingMode( Engine->GetContext().GetDrawingMode() );
	Engine->RenderAllViewport();
	Engine->GetInputOutput()->Swap();
	UNCLAIM_ENGINE	
}

void	Mouseclick(OR_I32 button, OR_I32 state, OR_I32 x, OR_I32 y)
{

	if( button==OR_BUTTON_LEFT )
	{
		if( state == OR_BUTTON_DOWN ) BoutG = true;
		else BoutG = false;
	}
	if( button==OR_BUTTON_RIGHT )
	{
		if( state == OR_BUTTON_DOWN ) BoutD = true;
		else BoutD = false;
	}

}

void Mousefunc(OR_I32 x, OR_I32 y)
{
	if( SelectedCam ) return;
	CLAIM_ENGINE
	OR_Camera_Free* Cam = (OR_Camera_Free*)Engine->GetCameraManager().GetElement( ORION3D_FLYING_CAM );
	OR_I32 xmouse=pInputOutput->GetMousePosX();
	OR_I32 ymouse=pInputOutput->GetMousePosY();

	if( BoutD )
	{
		Cam->Rotate( Y, (-xmouse+x)*0.004 );
		Cam->Rotate( X, (+ymouse-y)*0.004 );
	}
	if( BoutG )
	{
		if( CtrlPressed )
		{
			Cam->Translate( X, (xmouse-x)*Cam->GetFar()/30000.f );
			Cam->Translate( Y, (-ymouse+y)*Cam->GetFar()/30000.f );
		}
		else
			Cam->Translate( Z, (-ymouse+y)*Cam->GetFar()/30000.f );
	}

	UNCLAIM_ENGINE
}



void Keyboard(OR_U32 key, OR_I32 b1, OR_I32 b2)
{
	CLAIM_ENGINE

	OR_Camera* Cam = Engine->GetCameraManager().GetElement( ORION3D_FLYING_CAM );
	switch (key) 
	{
	case VK_UP:
		Cam->Translate(Z, -Cam->GetFar()/300.);
		break;
	case VK_DOWN:
		Cam->Translate(Z, Cam->GetFar()/300.);
		break;
	case VK_LEFT:
		Cam->Translate(X, -Cam->GetFar()/500.);
		break;
	case VK_RIGHT:
		Cam->Translate(X, Cam->GetFar()/500.);
		break;
	case VK_CONTROL:
		CtrlPressed = true;
		break;
	}
	UNCLAIM_ENGINE
}

void Keyboardreleased(OR_U32 key, OR_I32 b1, OR_I32 b2)
{
	switch (key) 
	{
	case VK_CONTROL:
		CtrlPressed = false;
		break;
	}

}



OR_U32		Orion3D_quit()
{
	((OR_ShellConsoleText&)Engine->GetShellConsole()).CloseConsole();
	return 0;
}