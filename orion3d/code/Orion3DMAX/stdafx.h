#ifndef _StdAfx_Orion3DMAX_h_
#define _StdAfx_Orion3DMAX_h_

#pragma warning( disable : 4786 )

#define _WIN32_WINNT 0x0500


#include <windows.h>
#include <commctrl.h>
#include <new.h>
#include <winbase.h>

#include <direct.h>

#include <map>

#include <Max.h>
#include <imtl.h>
#include <texutil.h>
#include <stdmat.h>
#include <MESHDLIB.H>
#include <memory.h>
#include <iparamb2.h>
#include <gizmo.h>
#include <gizmoimp.h>
#include <utilapi.h>
#include <ISkin.h>
#include <modstack.h>
#include <notify.h>
#include <phyexp.h>
#include <decomp.h>


#include "configuration/OR_Config.h"

#include "misc/OR_PrintBuildLog.h"
#include "maths/OR_Maths.h"
#include "maths/OR_Plane.h"
#include "toolkit/OR_Toolkit.h"
#include "objects/OR_Mesh.h"
#include "objects/OR_Bone.h"
#include "objects/OR_Gizmo.h"
#include "objects/OR_Light.h"
#include "objects/OR_Object.h"
#include "objects/OR_Camera.h"
#include "objects/OR_Skin.h"
#include "hierarchy/OR_Node.h"
#include "hierarchy/OR_HierarchyTree.h"
#include "shaders/OR_SingleTextureMapShader.h"
#include "shaders/OR_MultiShader.h"
#include "shaders/OR_FlatShader.h"
#include "animation/OR_Animation.h"
#include "animation/OR_Evaluator.h"
#include "animation/OR_AnimationTrack.h"
#include "animation/OR_AnimationPlayer.h"
#include "input_output/OR_Viewport.h"
#include "wrapper_win32/OR_InputOutput_win32.h"

#include "O3DMAXViewer/resource.h"


#define CLAIM_ENGINE			EnterCriticalSection( &Critic );
#define UNCLAIM_ENGINE			LeaveCriticalSection( &Critic ); 
#define ORION3D_EVENT_START		"Orion3D is ready"
#define ORION3D_EVENT_NEED_MAJ	"Orion3D Ready for update"
#define ORION3D_EVENT_MAJ_DONE	"Orion3D Update done"
#define ORION3D_WINDOW_TITLE	"Orion3DMAX Viewer"
#define ORION3D_FLYING_CAM		"\1flying_sausage" // après la soucoupe volante... la saucisse volante !
#define ORION3D_DEFAULT_SHADER	"\1default_shader"
#define ORION3D_DEFAULT_LIGHT	"\1default_lighting"
#define ORION3D_FRAMES_PER_SEC	60

#endif //_StdAfx_Orion3DMAX_h_