#include "../stdafx.h"
#include "O3DMAXViewer.h"

ViewerPlugin::ViewerPlugin():UtilityObj()
{
	OldLowMemHandler = _set_new_handler(LowMemHandler);
	RegisterNotification(this->Exit , NULL, NOTIFY_SYSTEM_SHUTDOWN);
}


ViewerPlugin::~ViewerPlugin()
{
	if (MAXInterface) MAXInterface->UnRegisterTimeChangeCallback(&MyTimeCallback);
	UnRegisterNotification(this->Exit , NULL, NOTIFY_SYSTEM_SHUTDOWN);
	_set_new_handler(OldLowMemHandler);
}

void ViewerPlugin::BeginEditParams( Interface *ip, IUtil *iu )
{
	MAXInterface = ip;
	IUtility = iu;
	
	if( !Engine )
	{
		DlgHandle = NULL;
		HANDLE Event = CreateEvent(NULL , FALSE , FALSE , ORION3D_EVENT_START);
		EngineThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Go, (LPVOID)ip , 0, &EngineThreadId);
		DWORD Waitresult = WaitForSingleObject( Event, 5000 );
		CloseHandle(Event);
		if( Waitresult==WAIT_FAILED || Waitresult==WAIT_TIMEOUT )
		{
			iu->CloseUtility();
			return;
		}
		Wrapper.SetEngine(Engine);
		ip->RegisterTimeChangeCallback(&MyTimeCallback);
	}
	Wrapper.SetInterface(ip);
	Wrapper.SetIUtil(iu);
	DlgHandle = ip->AddRollupPage(hInstance, MAKEINTRESOURCE(IDD_DIALOG_VIEWER), ViewerDlgProc , _T("Orion3DMAX"));	
	TreeViewHandle = ip->AddRollupPage(hInstance, MAKEINTRESOURCE(IDD_TREEVIEW), TreeViewDlgProc , _T("Hierarchy View"));	
/*
	int* test = (int*)malloc(4);
	*test = 4;
	MAXInterface->GetRootNode()->AddAppDataChunk(Class_ID(VIEWER_CLASS_ID,0), ViewerSuperClassID, 1, 4, test);
	int hop = *(int*)MAXInterface->GetRootNode()->GetAppDataChunk(Class_ID(VIEWER_CLASS_ID,0), ViewerSuperClassID, 1)->data;
	MAXInterface->GetRootNode()->RemoveAppDataChunk(Class_ID(VIEWER_CLASS_ID,0), ViewerSuperClassID, 1);
*/
}

void ViewerPlugin::EndEditParams(Interface *ip,IUtil *iu)
{	
	EnableAccelerators();
	if (TimeEvent) timeKillEvent(TimeEvent);TimeEvent=0;
	SaveOptions();
	ip->DeleteRollupPage(DlgHandle);
	ip->DeleteRollupPage(TreeViewHandle);
}


void ViewerPlugin::SelectionSetChanged(Interface *ip,IUtil *iu)
{
//	MessageBox(NULL,"SelectionSetChanged","O3DMAXViewer",MB_OK);
}


void ViewerPlugin::SetStartupParam(TSTR param)
{
	MessageBox(NULL,"SetStartupParam","O3DMAXViewer",MB_OK);
}

void ViewerPlugin::DeleteThis()
{
	delete this;
}



///Display a warning message when there is not enough memory
int	ViewerPlugin::LowMemHandler(size_t size)
{
	if( Engine ) Engine->GetMessageHandler().Warning("(Allowing memory)","Memory low. Orion3D will not be able to create all the objects. Try closing some other apps\n%d bytes could not be allocated",size);
	return 0;
}

void ViewerPlugin::Exit(void *param, NotifyInfo *info)
{
	CloseAtExit();
}

void ViewerPlugin::TimeChanged(TimeValue t)
{
	SetTime(t);
}