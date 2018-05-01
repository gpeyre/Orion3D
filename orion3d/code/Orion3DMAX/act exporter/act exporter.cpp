/** \file 
	Contains the code of the main Dll classes
	\author Antoche
**/

#include "act exporter.h"

/****************************************************************
Code de la Classe MyPlugin :
*****************************************************************/

//////////////////////////////////////////////////////////////////
// Number of extensions supported 
int				ACTPlugin::ExtCount() 
{
	return 1;
}

//////////////////////////////////////////////////////////////////
// Extension #n (i.e. "KSP")
const TCHAR *	ACTPlugin::Ext(int n) 
{
	switch(n) {
	case 0:
		return _T("act");
		break;
	default:
		return _T("");
		break;
	}
}

//////////////////////////////////////////////////////////////////
// Long description
const TCHAR *	ACTPlugin::LongDesc() 
{
	return _T("Orion3D ACT Export");
}

//////////////////////////////////////////////////////////////////
// Short description
const TCHAR *	ACTPlugin::ShortDesc() 
{
	return _T("Orion3D act");
}

//////////////////////////////////////////////////////////////////
// Author name
const TCHAR *	ACTPlugin::AuthorName() 
{
	return _T("Antoche");
}

//////////////////////////////////////////////////////////////////
// Copyright message 
const TCHAR *	ACTPlugin::CopyrightMessage() 
{
	return _T("Copyright (c) 2000 Antoche");
}

//////////////////////////////////////////////////////////////////
// Other message #1
const TCHAR *	ACTPlugin::OtherMessage1() 
{
	return _T("");
}

//////////////////////////////////////////////////////////////////
// Other message #2
const TCHAR *	ACTPlugin::OtherMessage2() 
{
	return _T("");
}

//////////////////////////////////////////////////////////////////
// Version number * 100 (e.g. v3.01 = 301) 
unsigned int	ACTPlugin::Version() 
{
	return 100;
}

//////////////////////////////////////////////////////////////////
// Show DLL's "About..." box
void	ACTPlugin::ShowAbout(HWND hWnd) 
{
	MessageBox(hWnd,"Orion3D act exporter v.1 beta 1\nby Antoche - antoche@altern.org\nhttp://www.antoche.fr.st - http://www.orion3d.fr.st\nCopyright (c) 2000","About ACT Exporter",MB_OK | MB_ICONINFORMATION);
}

//////////////////////////////////////////////////////////////////
//Renvoie les options supportées par le plug-in
BOOL	ACTPlugin::SupportsOptions(int ext, DWORD options) 
{
	return FALSE;
}


//////////////////////////////////////////////////////////////////
// Export file
int		ACTPlugin::DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options) 
{
	//Header of the first animation (how could there be more than one ?)
	CAnimHeader* AnimHeaders = NULL;
	//Root animation node
	CAnimationNode** AnimRootNodes = NULL;
	//Root object node
	INode* RootNode;
	//Animations count (how could there be more than one ?)
	int NbAnims = 0;
	//Version file
	int	Version = 100;
	//Version ID (ACT)
	char	*ID = "ACT";
	//couner
	int n;


	//Retrieve animations from the selected node (or the root node if no object is selected)
	if (i->GetSelNodeCount()>0)
	{
		AnimHeaders = new CAnimHeader[i->GetSelNodeCount()];
		AnimRootNodes = new CAnimationNode*[i->GetSelNodeCount()];
		for (n=0 ; n<i->GetSelNodeCount() ; n++)
		{
			RootNode=i->GetSelNode(n);
			AnimRootNodes[n] = this->ExportAnimRec(&AnimHeaders[n],RootNode);
			if (AnimRootNodes[n]!=NULL) 
			{
				AnimRootNodes[n]->RelativiseRec();
				AnimRootNodes[n]->RelativiseTimeRec(AnimHeaders[n].Start , AnimHeaders[n].Duration);
				strncpy(AnimHeaders[n].Name , RootNode->GetName() , OR_TAILLE_NOM);
				NbAnims++;
			}
		}
	}
	else
	{
		AnimHeaders = new CAnimHeader[i->GetRootNode()->NumberOfChildren()];
		AnimRootNodes = new CAnimationNode*[i->GetRootNode()->NumberOfChildren()];
		for (n=0 ; n<i->GetRootNode()->NumberOfChildren() ; n++)
		{
			RootNode=i->GetRootNode()->GetChildNode(n);
			AnimRootNodes[n] = this->ExportAnimRec(&AnimHeaders[n],RootNode);
			if (AnimRootNodes[n]!=NULL) 
			{
				AnimRootNodes[n]->RelativiseRec();
				AnimRootNodes[n]->RelativiseTimeRec(AnimHeaders[n].Start , AnimHeaders[n].Duration);
				strncpy(AnimHeaders[n].Name , RootNode->GetName() , OR_TAILLE_NOM);
				NbAnims++;
			}
		}
	}

	if (!NbAnims)
	{
		MessageBox(NULL , "No animation to export." , "ACT Exporter::Finish" , MB_OK | MB_ICONINFORMATION);
		return 1;
	}
	
	FILE* File = fopen(name , "wb");
	if (!File)
	{
		MessageBox(NULL , "The file could not be opened for writing. Export failed." , "ACT Exporter::Error" , MB_OK | MB_ICONERROR);
		return 1;
	}

	//write the file header (id, version, animation count)
	fwrite(ID		, sizeof(char)	  , 3 , File);
	fwrite(&Version , sizeof(Version) , 1 , File);
	fwrite(&NbAnims , sizeof(NbAnims) , 1 , File);

	for (n=0 ; n<NbAnims ; n++)
	{
		//write the animation header
		fwrite(&AnimHeaders[n] , sizeof(OR_ExportHeader_Animation) , 1 , File);
		//write recursively the animation in the file
		this->WriteAnimRec(AnimRootNodes[n] , File);
	}
	fclose(File);

	//Make a resume
	int NbNodesTotal=0, NbTracksTotal=0, NbKeysTotal=0;
	for (n=0 ; n<NbAnims ; n++) 
	{
		NbNodesTotal+=AnimHeaders[n].NbObjects;
		NbTracksTotal+=AnimHeaders[n].NbTracks;
		NbKeysTotal+=AnimHeaders[n].NbKeys;
	}
	char Coool[1000];
	sprintf(Coool , "Export successfull !\nResume :\n - %d animations,\n - %d nodes,\n - %d tracks,\n - %d keyframes." , NbAnims , NbNodesTotal , NbTracksTotal , NbKeysTotal);
	MessageBox(NULL , Coool , "ACT Exporter::Finish" , MB_OK | MB_ICONINFORMATION);


	for (n=0 ; n<NbAnims ; n++) if (AnimRootNodes[n]) delete AnimRootNodes[n];
	delete AnimRootNodes;
	delete AnimHeaders;

	return 1;
}

////////////////////////////////////////////////////////////////////

void	ACTPlugin::WriteAnimRec(CAnimationNode* Node , FILE* File)
{
	int i,j;
	fwrite(Node , sizeof(OR_ExportHeader_AnimationNode) , 1 , File);

	for (i=0 ; i<Node->NbTrack ; i++)
	{
		fwrite(Node->Tracks[i] , sizeof(OR_ExportHeader_AnimationTrack) , 1 , File);
		for (j=0 ; j<Node->Tracks[i]->NbKeyFrame ; j++)
		{
			fwrite(Node->Tracks[i]->Keys[j] , Node->Tracks[i]->KeySize , 1 , File);
		}
	}

	for (i=0 ; i<Node->NbSon ; i++)
	{
		this->WriteAnimRec(Node->Sons[i] , File);
	}
}

//////////////////////////////////////////////////////////////////


CAnimationNode* ACTPlugin::ExportAnimRec(CAnimHeader* AnimHeader, INode* RootNode)
{
	int i=0;
	int NbAnimatedNodes = 0;
	CAnimationNode* ANode = new CAnimationNode;

	CAnimationTrack *TrackPosition;
	CAnimationTrack *TrackRotation;
	CAnimationTrack *TrackScale;
	
	TrackPosition	= ((CNode*)RootNode)->GetPositionTrack();	if (TrackPosition)	ANode->NbTrack++;
	TrackRotation	= ((CNode*)RootNode)->GetRotationTrack();	if (TrackRotation)	ANode->NbTrack++;
	TrackScale		= ((CNode*)RootNode)->GetScaleTrack();		if (TrackScale)		ANode->NbTrack++;

	ANode->Tracks = new CAnimationTrack*[ANode->NbTrack];
	if (TrackPosition)	
	{
		ANode->Tracks[i++] = TrackPosition;
		ANode->Length = max(ANode->Length,TrackPosition->Ending - TrackPosition->Beginning);
		ANode->Start = min(ANode->Start,TrackPosition->Beginning);
	}
	if (TrackRotation)	
	{
		ANode->Tracks[i++] = TrackRotation;
		ANode->Length = max(ANode->Length,TrackRotation->Ending - TrackRotation->Beginning);
		ANode->Start = min(ANode->Start,TrackRotation->Beginning);
	}
	if (TrackScale)		
	{
		ANode->Tracks[i++] = TrackScale;	
		ANode->Length = max(ANode->Length,TrackScale->Ending - TrackScale->Beginning);
		ANode->Start = min(ANode->Start,TrackScale->Beginning);
	}

	ANode->NbSon = RootNode->NumberOfChildren();
	if (ANode->NbSon)
	{
		ANode->Sons = new CAnimationNode*[ANode->NbSon];
		for (i=0 ; i<ANode->NbSon ; i++)
		{
			ANode->Sons[i] = this->ExportAnimRec(AnimHeader , (CNode*)RootNode->GetChildNode(i));
			if (!ANode->Sons[i])
			{
				ANode->Sons[i] = new CAnimationNode(); //void node
			}
			else
			{
				ANode->Length	= max(ANode->Length , ANode->Sons[i]->Length);
				ANode->Start	= min(ANode->Start , ANode->Sons[i]->Start);
				NbAnimatedNodes++;
			}
		}
	}

	if (!NbAnimatedNodes && !ANode->NbTrack)
	{
		delete ANode;
		ANode = NULL;
	}
	else
	{
		AnimHeader->NbObjects++;
		AnimHeader->NbTracks += ANode->NbTrack;
		for (i=0 ; i<ANode->NbTrack ; i++)	AnimHeader->NbKeys+= ANode->Tracks[i]->NbKeyFrame; 
		AnimHeader->Duration = max(ANode->Length , AnimHeader->Duration);
		AnimHeader->Start = min(ANode->Start , AnimHeader->Start);
	}
	
	return ANode;
}


//You know what ? it is the END OF FILE !