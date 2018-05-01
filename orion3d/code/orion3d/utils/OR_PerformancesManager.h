/*-------------------------------------------------------------------*/
/*                            OR_PerformancesManager.h               */
/*-------------------------------------------------------------------*/
/* Created : 10 Apr 2001   14h43                                     */
/*-------------------------------------------------------------------*/

/** \file
	Defines function to handle performances [FPS, memory ...].
	\author Gabriel
*/

#ifndef _OR_PERFORMANCES_MANAGER_
#define _OR_PERFORMANCES_MANAGER_

#include "../configuration/OR_Config.h"

namespace OR
{
	
/** size of a interval to compute FPS (1=instant computation) */
#define OR_FPS_INTERVAL_SIZE 20
/** maximum number of intervals to put in a FPS report */
#define OR_FPS_NB_MAX_INTERVAL 50

/*-------------------------------------------------------------------*/
/*                   class OR_PerformancesManager                    */
/*-------------------------------------------------------------------*/
/* A class to manage performances.                                   */
/*-------------------------------------------------------------------*/

/// A class to manage performances.
/**	Can be used to have FPS reports, etc ...
	\author Gabriel
*/

class ORION3D_API OR_PerformancesManager
{
private:
	/** the FPS that have been computed */
	OR_Float FPS_Times[OR_FPS_NB_MAX_INTERVAL];
	/** the number of the current interval */
	OR_U32 IntervalNum;
	/** the number of frame since the last FPS computation */
	OR_U32 FrameNum;
	/** the time of the last FPS computation */
	OR_I64 StartTime;
	/** is FPS computation active ?? */
	OR_Bool FPSActive;
public:
	/** constructor */
	OR_PerformancesManager();

	/* FPS management ********************************************/
	/** update the FPS computations */
	void UpdateFPS();
	/** make a report af the last FPSs */
	void FPSReport();
	/** make a log file of the last FPSs */
	void FPSLog(char *name="FPS_report.log");
	/** get current FPS */
	OR_Float GetFPS();
};


} // namespace OR

#endif /* #ifndef _OR_PERFORMANCES_MANAGER_ */

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