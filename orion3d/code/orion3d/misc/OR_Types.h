/*----------------------------------------------------------------------------*/
/*                              OR_Types.h                                    */
/*----------------------------------------------------------------------------*/
/* definition of enumerate type used in Orion3D                               */
/*----------------------------------------------------------------------------*/

/** \file 
	Contains the definition of enumerate type used in Orion3D.
	\author Gabriel.
**/


#ifndef _OR_TYPES_H_
#define _OR_TYPES_H_

#include "../stdafx.h"

namespace OR
{
	
//-------------------------------------------------------------------------
/** \name Basic types */
//-------------------------------------------------------------------------
//@{
#ifdef __UNIX__
	typedef char                    OR_I8;
	typedef unsigned char           OR_U8;
	typedef short                   OR_I16;
	typedef unsigned short          OR_U16;
	typedef long                    OR_I32;
	typedef unsigned long           OR_U32;
	typedef long long int           OR_I64;
	typedef unsigned long long int  OR_U64;
	typedef float                   OR_Real32;
	typedef double                  OR_Real64;
	typedef bool                    OR_Bool;
	typedef OR_Real32               OR_Float;
#elif defined (WIN32)
	typedef char                OR_I8;
	typedef unsigned char       OR_U8;
	typedef short               OR_I16;
	typedef unsigned short      OR_U16;
	typedef long                OR_I32;
	typedef unsigned long       OR_U32;
	typedef __int64             OR_I64;
	typedef unsigned __int64    OR_U64;
	typedef float               OR_Real32;
	typedef double              OR_Real64;
	typedef bool                OR_Bool;
	typedef OR_Real32           OR_Float;
#elif defined (_PS2_)
	typedef char                OR_I8;
	typedef unsigned char       OR_U8;
	typedef short               OR_I16;
	typedef unsigned short      OR_U16;
	typedef int                 OR_I32;
	typedef unsigned int        OR_U32;
	typedef long long           OR_I64;
	typedef unsigned long long  OR_U64;
	typedef float               OR_Real32;
	typedef double              OR_Real64;
	typedef OR_I8               OR_Bool;
	typedef OR_Real32           OR_Float;
#else
	#error "Unknown architecture !"
#endif

	typedef void*				OR_UserData;

/** value returned by function to indicates error or OR_OK */
typedef OR_I32 OR_RETURN_CODE;
//@}

//-------------------------------------------------------------------------
/** \name STL conteners types */
//-------------------------------------------------------------------------
//@{
using namespace std;


/* vectors ********************************************************************/
/** vector of OR_Object* */
typedef vector<class OR_Object*> T_ObjectVector;
/** iterator for vector of OR_Object* */
typedef T_ObjectVector::iterator IT_ObjectVector;
/** List of OR_Object* */
typedef list<class OR_Object*> T_ObjectList;
/** iterator for List of OR_Object* */
typedef T_ObjectList::iterator IT_ObjectList;

/** vector of OR_U32 */
typedef vector<OR_U32> T_U32Vector;
/** iterator for vector of OR_U32 */
typedef T_U32Vector::iterator IT_U32Vector;

/** vector of OR_I32 */
typedef vector<OR_I32> T_I32Vector;
/** iterator for vector of OR_I32 */
typedef T_I32Vector::iterator IT_I32Vector;

/** vector of OR_Float */
typedef vector<OR_Float> T_FloatVector;
/** iterator for vector of OR_Float */
typedef T_FloatVector::iterator IT_FloatVector;

/* Lists ********************************************************************/
/** List of OR_U32 */
typedef list<OR_U32>			T_U32List;
/** iterator for List of OR_U32 */
typedef T_U32List::iterator		IT_U32List;

/** List of OR_I32 */
typedef list<OR_I32>			T_I32List;
/** iterator for List of OR_I32 */
typedef T_I32List::iterator		IT_I32List;

/** List of OR_Float */
typedef list<OR_Float>			T_FloatList;
/** iterator for List of OR_Float */
typedef T_FloatList::iterator	IT_FloatList;

/** list of string */
class OR_String;
typedef list<OR_String*>		T_StringList;
/** iterator for a list of string */
typedef T_StringList::iterator	IT_StringList;

class OR_AnimationPlayer;
/** a list of animation players */
typedef list<OR_AnimationPlayer*> T_AnimationPlayerList;
/** an iterator on a list of animation players */
typedef T_AnimationPlayerList::iterator IT_AnimationPlayerList;
//@}


//-------------------------------------------------------------------------
/** \name enumerates constants */
//-------------------------------------------------------------------------
//@{

/** space coords */
enum OR_Coord_XYZW { X, Y, Z, W };
/** color coords */
enum OR_Coord_RVBA { R, V, B, A };
// #define G 1

/** list of different viewport types */
enum OR_VIEWPORT_Type
{
	OR_VIEWPORT_Screen, OR_VIEWPORT_FeedBack,
	OR_VIEWPORT_Undefined
};

/** list of every lens flare type */
enum OR_LENSFLARE_Type
{
	OR_LENSFLARE_Infinite,
	OR_LENSFLARE_Local,
	OR_LENSFLARE_Undefined
};

/** different culling modes */
enum OR_Culling_Mode
{
	OR_Culling_Front,		/* cull front facing polys */
	OR_Culling_Back,		/* cull back facing polys */
	OR_Culling_None,		/* don't cull any polys */
	OR_Culling_Undefined	/* tralala */
};

/** different drawing modes */
enum OR_Drawing_Mode
{
	OR_Drawing_Filled,
	OR_Drawing_Wireframe,
	OR_Drawing_Point
};

/** different blending modes : in the form OR_Culling_xxx_yyy where :
		- xxx Specifies how the red, green, blue, and alpha source-blending factors are computed. 
		- yyy Specifies how the red, green, blue, and alpha destination-blending factors are computed. 
	these value are expressed using the syntax :
		- 1 = constant equals to 1.
		- 0 = constant equals to 0.
		- SrcA = source alpha value.
		- DstA = destination alpha value.
		- Minus = minus operation between two values. */
enum OR_Blending_Mode
{
	OR_Blending_SrcA_1MinusSrcA,
	OR_Blending_SrcA_1,
	OR_Blending_SrcA_0,
	OR_Blending_1_1,
	OR_Blending_None,
	OR_Blending_Undefined
};

/* animation constants *************************************************************/
/** list of different animation evaluators */
enum OR_ANIMATION_Evaluator_Type
{
	OR_ANIMATION_Evaluator_Linear,
	OR_ANIMATION_Evaluator_Bezier,
	OR_ANIMATION_Evaluator_Constant,
	OR_ANIMATION_Evaluator_TCB,
	OR_ANIMATION_Evaluator_Smooth, 
	OR_ANIMATION_Evaluator_Undefined
};

/** list of different track type */
enum OR_ANIMATION_Track_Type
{
	OR_ANIMATION_Track_Float,
	OR_ANIMATION_Track_Vector,
	OR_ANIMATION_Track_Quaternion,
	OR_ANIMATION_Track_Bool,
	OR_ANIMATION_Track_Undefined
};

/** list of different track behaviors */
enum OR_ANIMATION_Track_Behavior
{
	OR_ANIMATION_Behavior_Constant,		//Constant value equal to first or last key
	OR_ANIMATION_Behavior_Loop,			//Restart when at last keyframe
	OR_ANIMATION_Behavior_PingPong,		//Go backwards when at last keyframe
	OR_ANIMATION_Behavior_RelativeLoop,	//Restart where the last keyframe stopped
	OR_ANIMATION_Behavior_Undefined
};

/** list of different animation player behaviors */
enum OR_ANIMATION_Player_Behavior
{
	OR_ANIMATION_Player_Pause,
	OR_ANIMATION_Player_Stop,			
	OR_ANIMATION_Player_Loop,			
	OR_ANIMATION_Player_PingPong,		
	OR_ANIMATION_Player_RelativeLoop,	
	OR_ANIMATION_Player_Undefined
};

/** list of different targets */
enum OR_ANIMATION_Target
{
	OR_ANIMATION_Target_Pos,			/* 3D vector */
	OR_ANIMATION_Target_PosX,			/* OR_Float */
	OR_ANIMATION_Target_PosY,			/* OR_Float */
	OR_ANIMATION_Target_PosZ,			/* OR_Float */
	OR_ANIMATION_Target_Rot,			/* quaternion */
	OR_ANIMATION_Target_Scale,			/* 3D vector */
	OR_ANIMATION_Target_ScaleX,			/* OR_Float */
	OR_ANIMATION_Target_ScaleY,			/* OR_Float */
	OR_ANIMATION_Target_ScaleZ,			/* OR_Float */
	OR_ANIMATION_Target_Ambient,		/* 3D vector */
	OR_ANIMATION_Target_AmbientR,		/* OR_Float */
	OR_ANIMATION_Target_AmbientV,		/* OR_Float */
	OR_ANIMATION_Target_AmbientB,		/* OR_Float */
	OR_ANIMATION_Target_Diffuse,		/* 3D vector */
	OR_ANIMATION_Target_DiffuseR,		/* OR_Float */
	OR_ANIMATION_Target_DiffuseV,		/* OR_Float */
	OR_ANIMATION_Target_DiffuseB,		/* OR_Float */
	OR_ANIMATION_Target_Specular,		/* 3D vector */
	OR_ANIMATION_Target_SpecularR,		/* OR_Float */
	OR_ANIMATION_Target_SpecularV,		/* OR_Float */
	OR_ANIMATION_Target_SpecularB,		/* OR_Float */
	OR_ANIMATION_Target_Shine,			/* OR_Float */
	OR_ANIMATION_Target_Display,		/* OR_Float / OR_Bool */
	OR_ANIMATION_Target_Undefined
};

/** differents arguments for Set[f|fv|i|iv]() */
enum OR_Types 
{ 
	OR_Shadows, OR_Reflections,
	/* fog values ***********************************/
	OR_FOG_Color, OR_FOG_Density, OR_FOG_OnOff,
	/* camera types ********************************/
	OR_CAMERA_Pos, OR_CAMERA_DistanceMin,
	OR_CAMERA_Near, OR_CAMERA_Far, OR_CAMERA_Fovy,
	OR_CAMERA_Aspect,
	OR_CAMERA_GetType, OR_CAMERA_Roll,
	/* light values *********************************/
	OR_LIGHT_Ambient, OR_LIGHT_Diffuse, OR_LIGHT_Specular,
	OR_LIGHT_Atenuation, OR_LIGHT_Cutoff, OR_LIGHT_Exponent,
	OR_LIGHT_Pos, OR_LIGHT_Direction, OR_LIGHT_GlobalAmbient,
	/* nurbs values *********************************/
	OR_NURBS_Pos, OR_NURBS_Axe, OR_NURBS_Selected_CtrlPt,
	OR_NURBS_Fill,
	/* mesh values **********************************/
	OR_MESH_Pos, 
	/* particules values ****************************/
	OR_PARTICULES_Debit, OR_PARTICULES_EnergyStart, 
	OR_PARTICULES_EnergyStartVariance, OR_PARTICULES_EnergyLost, 
	OR_PARTICULES_EnergyLostVariance, OR_PARTICULES_Mass,
	OR_PARTICULES_MassVariance, OR_PARTICULES_SourcePos, 
	OR_PARTICULES_InitialSpeed,	 
	OR_PARTICULES_MaxRadius, 
	OR_PARTICULES_NbMaxParticules,
	OR_PARTICULES_EmissionVariance,
	OR_PARTICULES_StartColor, OR_PARTICULES_EndColor,
	OR_PARTICULES_IsSourceActive, OR_PARTICULES_IsSystemActive,
	OR_PARTICULES_Bounce,
	/* meta-env values *******************************/
	OR_META_ENV_Precision, OR_META_ENV_IsoLevel,
	/* shader values *********************************/
	OR_SHADER_Ambient, OR_SHADER_Diffuse, 
	OR_SHADER_Emission, OR_SHADER_Specular, 
	OR_SHADER_Shine, OR_SHADER_Alpha,
	OR_SHADER_BorderWidth,
	OR_SHADER_GetType,
	/* force values **********************************************/
	OR_FORCE_Type, OR_FORCE_Pos, OR_FORCE_Equation,
	OR_FORCE_DistMax,
	/* gizmos values************ *********************************/
	OR_GIZMO_Dim, OR_GIZMO_Bounce,
	OR_GIZMO_Intensity, OR_GIZMO_InfluenceRadius, 
	/* viewport values *******************************************/
	OR_VIEWPORT_Priority, OR_VIEWPORT_UsePerCent,
	OR_VIEWPORT_Color,
	/* number of elements ****************************************/
	OR_Nb_CAMERA,OR_Nb_MESH, OR_Nb_NURBS, OR_Nb_PLAN, OR_Nb_LIGHT,
	OR_Nb_PARTICULES_SYSTEM,
	OR_Nb_MATHS_SURFACE,
	OR_Nb_META_ENV, OR_Nb_METABALL,
	OR_Nb_SHADER,
	OR_Nb_FORCE, OR_Nb_PARTICULES_FORCE,
	OR_Nb_GIZMO, OR_Nb_PARTICULES_GIZMO,
	OR_Nb_VIEWPORT,
	OR_Nb_TEXTURE,
	/* selected element *******************************************/
	OR_Selected_CAMERA, OR_Selected_LIGHT, OR_Selected_PLAN,
	OR_Selected_NURBS, OR_Selected_MESH,
	OR_Selected_PARTICULES_SYSTEM,
	OR_Selected_MATHS_SURFACE,
	OR_Selected_META_ENV, OR_Selected_METABALL,
	OR_Selected_SHADER,
	OR_Selected_FORCE, OR_Selected_PARTICULES_FORCE,
	OR_Selected_GIZMO, OR_Selected_PARTICULES_GIZMO,
	OR_Selected_VIEWPORT,
	OR_Selected_TEXTURE,
	/* draw types **************************************************/
	OR_MATH_SURFACE_OnOff, OR_LIGHT_OnOff,
	OR_MESH_OnOff, OR_GIZMO_OnOff,
	OR_CAMERA_OnOff, OR_META_ENV_OnOff
};

/** different elements of Orion3D */
enum OR_Elements 
{ 
	OR_MESH, 
	OR_LIGHT,
		OR_LIGHT_Target_Spot, 
		OR_LIGHT_Free_Spot,
		OR_LIGHT_Target_Direct, 
		OR_LIGHT_Free_Direct,
	OR_NURBS,
	OR_PARTICULES_SYSTEM,
	OR_LIGHT_Solid, OR_NURBS_CtrlPt, 
	OR_CAMERA, 
		OR_CAMERA_Free, 
		OR_CAMERA_Target,
	OR_FOG, 
	OR_MATH_SURFACE,
	OR_META_ENV, OR_METABALL,
	OR_SURFACE_TESLATOR,
	OR_SHADER,
		OR_SHADER_Flat,
		OR_SHADER_SingleTextureMap, 
		OR_SHADER_Reflexive,
		OR_SHADER_Cartoon, 
		OR_SHADER_Billboard,
		OR_SHADER_Bump_Emboss, 
		OR_Shader_Multi,
	OR_GIZMO, 
		OR_GIZMO_Sphere, 
		OR_GIZMO_Cube, 
		OR_GIZMO_Cylinder,
		OR_GIZMO_Square, 
		OR_GIZMO_Vector, 
		OR_GIZMO_Point,	
	OR_BONE,
	OR_PARTICULES_GIZMO,
	OR_FORCE, OR_PARTICULES_FORCE,
	OR_VIEWPORT,
	OR_EMPTY,
	OR_LENSFLARE,
	OR_UNDEFINED,
	OR_LOCAL_AXES,
	OR_TRAJECTORIES,
	OR_SKINNING_BONE,
	OR_SKIN
};

/** the different type of force : used to speed up calculations */
enum OR_ForceType 
{  
	OR_CsteCentral,		/* a central force with Equation[1]=Equation[2]=0 */
	OR_QuadCentral,		/* a central force with Equation[1]=0 */
	OR_CsteOrthoPlanar,     /* an ortho-planar force with Equation[1]=Equation[2]=0 */
	OR_QuadOrthoPlanar,	/* an ortho-planar force with Equation[1]=0 */
	OR_ForceGeneral		/* general case */
};

/** different type of meta-elements */
enum OR_META_Type  
{ 
	OR_META_Blobby, OR_META_Quadratic, OR_META_Undefined 
};

/** differents behaviour of meta-elements */
enum OR_MetaBehaviour 
{ 
	OR_MetaStatic, OR_MetaRotate, OR_MetaBehaviour_Undefined
};

/** different way to compute normals of meta-elements */
enum OR_MetaNormalType
{ 
	OR_FlatNormal, OR_GradientNormal, OR_MetaNormalType_Undefined 
};

/*--------------------------------------------------------------------*/
/* different screenmode for screen savers.                            */
/*--------------------------------------------------------------------*/

/** different screenmode for screen savers */
enum OR_ScrMode 
{ 
	OR_Scr_None, OR_Scr_Config, 
	OR_Scr_Password, OR_Scr_Preview, 
	OR_Scr_Saver, OR_Scr_Undefined
};

/*--------------------------------------------------------------------*/
/* used to classify OR_Plane                                          */
/*--------------------------------------------------------------------*/
/** used to classify OR_Plane */
enum OR_Position 
{ 
	OR_POS_FRONT , 
	OR_POS_BACK , 
	OR_POS_LIE , 
	OR_POS_CROSS 
};

/** different type of buttons */
enum OR_BUTTON
{
   OR_BUTTON_LEFT,
   OR_BUTTON_MIDDLE,
   OR_BUTTON_RIGHT,
   OR_WHEEL
};

/** different state of buttons */
enum OR_BUTTON_STATE
{
   OR_BUTTON_UP,
   OR_BUTTON_DOWN
};

/** used to classify OR_SOUND_Types */
enum OR_SOUND_Types{
	OR_SOUND_2D,
	OR_SOUND_3D
};

//@}



/*--------------------------------------------------------------------*/
/*                       Orion3D callback functions                   */
/*--------------------------------------------------------------------*/

/** when the scene needs to be drawn */
typedef void (*OR_Display_Func)(void);
/** when a windows resizing occurs */
typedef void (*OR_Reshape_Func)(OR_I32 w, OR_I32 h);
/** when a mouse clic occurs */
typedef void (*OR_Mouseclic_Func)(OR_I32 button, OR_I32 state, OR_I32 x, OR_I32 y);
/** when a mouse move accurs together with a button click */
typedef void (*OR_Mouse_Func)(OR_I32 x, OR_I32 y);
/** when a mouse move occurs without a button click */
typedef void (*OR_Passmotion_Func)(OR_I32 x, OR_I32 y);
/** when nothing occurs */
typedef void (*OR_Idle_Func)(void);
/** when a keyboard key is pressed */
typedef void (*OR_KeyPressed_Func)(OR_U32 button, OR_I32 x, OR_I32 y);
/** when a keyboard key is released */
typedef void (*OR_KeyReleased_Func)(OR_U32 button, OR_I32 x, OR_I32 y);
/** when a keyboard special key is pressed */
typedef void (*OR_Special_Func)(OR_I32 key, OR_I32 x, OR_I32 y);
/** to initialize the graphics */
typedef void (*OR_Init_Func)();
/** when the windows is destroyed */
typedef void (*OR_Destroy_Func)();

/** during the loading of a bsp */
typedef void (*OR_Bsp_Loading)(OR_I32 current, OR_I32 end, char msg[]);

/*---------------------------------------------------------------------*/
/* misc functions types                                                */
/*---------------------------------------------------------------------*/

/** a string printer funtion */
typedef void (*OR_FUNCTION_MessagePrinter)
	(char* func, char* message, va_list argptr);
/** a message handler function */
typedef void (*OR_FUNCTION_MessageHandler)
	(char* func, char* message, va_list argptr);

} // namespace OR

#endif /* #ifndef _OR_TYPES_H_ */

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////