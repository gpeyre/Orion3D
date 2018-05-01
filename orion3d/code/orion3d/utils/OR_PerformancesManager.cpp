/*-------------------------------------------------------------------*/
/*                        OR_PerformancesManager.cpp                 */
/*-------------------------------------------------------------------*/
/* Created : 10 Apr 2001   14h43                                     */
/*-------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_PerformancesManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_PerformancesManager.h"

namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                   class OR_PerformancesManager                    */
/*-------------------------------------------------------------------*/
/* A class to manage performances.                                   */
/*-------------------------------------------------------------------*/

OR_PerformancesManager::OR_PerformancesManager()
{
	IntervalNum=0;
	FrameNum=0;
	FPSActive=true;
}

void OR_PerformancesManager::UpdateFPS()
{
	if (FrameNum==0 && IntervalNum==0)
	{
		/* initialize FPS computation */
		StartTime=OR_GetTime();
	}
	FrameNum++;
	if (FrameNum==OR_FPS_INTERVAL_SIZE)
	{
		OR_I64 time=OR_GetTime();
		FPS_Times[IntervalNum]=1000.0f*((OR_Float )OR_FPS_INTERVAL_SIZE)/((OR_Float) time-StartTime);
		StartTime=time;
		IntervalNum++;
		FrameNum=0;
		if (IntervalNum==OR_FPS_NB_MAX_INTERVAL)
		{
			IntervalNum=0;
		}
	}
}

void OR_PerformancesManager::FPSReport()
{
#ifdef _WIN32_
	OR_Float sum=0;
	OR_Float moy=0;
	OR_Float equart=0;
	OR_U32 i;
	
	char message[10000]="Parameters : Interval size=";
	char nb[20];
	strcat(message, _itoa(OR_FPS_INTERVAL_SIZE, nb, 10) );
	strcat(message, "\n\n");

	for (i=0; i<IntervalNum; i++)
	{
		strcat(message, "Interval ");
		strcat(message, _itoa(i, nb, 10));
		strcat(message, " : FPS=");
		
		strcat(message, OR_FloatToString(FPS_Times[i]) );
		strcat(message, "\n");
		sum+=FPS_Times[i];
	}
	
	if (IntervalNum!=0) moy=sum/IntervalNum;
	for (i=0; i<IntervalNum; i++)
	{
		equart+=(FPS_Times[i]-moy)*(FPS_Times[i]-moy);
	}
	if (IntervalNum!=0) equart=sqrt(equart/IntervalNum);

	strcat(message, "\n- Esperance=");
	strcat(message, OR_FloatToString(moy) );
	strcat(message, "\n- Equart type=");
	strcat(message, OR_FloatToString(equart) );
	
	MessageBox(0, message,"FPS Report",MB_OK | MB_ICONINFORMATION);
#else
	OR_Float sum=0;
	OR_Float moy=0;
	OR_Float equart=0;
	OR_U32 i;
	fprintf(stderr, "\n\n############### FPS REPORT ###############\n");
	fprintf(stderr, "Parameters : Interval size=%iFPS\n\n", OR_FPS_INTERVAL_SIZE);
	for (i=0; i<IntervalNum; i++)
	{
		fprintf(stderr, "Interval %i : FPS=%f\n", i, FPS_Times[i]);
		sum+=FPS_Times[i];
	}
	if (IntervalNum!=0) moy=sum/IntervalNum;
	for (i=0; i<IntervalNum; i++)
	{
		equart+=(FPS_Times[i]-moy)*(FPS_Times[i]-moy);
	}
	if (IntervalNum!=0) equart=sqrt(equart/IntervalNum);
	fprintf(stderr, "\nEsperance=%f  Equart type=%f [don't know how to say that in $English$ ...]\n",
		moy, equart);
	fprintf(stderr, "\n\n##########################################\n");
#endif
}

void OR_PerformancesManager::FPSLog(char *name)
{
	FILE* file=fopen(name, "wt");
	for (OR_U32 i=0; i<IntervalNum; i++)
	{
		fprintf(file, "%i %f\n", i, FPS_Times[i]);
	}
	fclose(file);
}

OR_Float OR_PerformancesManager::GetFPS()
{
	if (IntervalNum==0) return OR_ERROR;
	return FPS_Times[IntervalNum-1];
}


} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                           END  OF FILE	                                 //
///////////////////////////////////////////////////////////////////////////////