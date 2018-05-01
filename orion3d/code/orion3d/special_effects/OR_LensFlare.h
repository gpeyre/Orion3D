/*-------------------------------------------------------------------*/
/*                           OR_LensFlare.h                          */
/*-------------------------------------------------------------------*/
/* Created : 14 Apr 2001   18h09                                     */
/*-------------------------------------------------------------------*/

/** \file
	To perform lens flare effect.
	\author Gabriel
*/

#ifndef _OR_LENS_FLARE_
#define _OR_LENS_FLARE_

#include "../configuration/OR_Config.h"
#include "OR_SpecialEffect.h"
#include "../objects/OR_Camera.h"
#include "../shaders/OR_AlphaPipeline.h"
#include "../shaders/OR_Shader.h"
#include "../shaders/OR_BillboardShader.h"
#include "../shaders/OR_Shadable.h"

namespace OR
{
	

/*-------------------------------------------------------------------*/
/*                   class OR_LensFlare                              */
/*-------------------------------------------------------------------*/
/* super class for all lens flare.                                   */
/*-------------------------------------------------------------------*/

/// super class for all lens flare.
/**
	A lens flare can be of two kind :
		- infinite (coming from the sun, for example).
		- local (coming from a light).
	\author Gabriel
*/

class ORION3D_API OR_LensFlare: public OR_SpecialEffect, public OR_Shadable
{
protected:
	/** the shader used to render the lensflare */
	OR_Shader* MyShader;
	/** the size (half of the dimension on X and Y) of the square used to render the lensflare */
	OR_Float Size[2];
	/** the distance to perform the effect, can be :
		- for a local effect : 1=on the source, 0=on the camera. 
		- for an infinite effect : Distance=distance from the camera. */
	OR_Float Distance;

	/** the position of the lensflare */
	OR_Vector3D	Pos;
public:
	/** constructor */
	OR_LensFlare();
	
	/** display the effect to screen. 
		\param v Vector giving the direction of the effect. Is given in absolute coords.
			Can be :
			- for a local effect : this is the vector Camera->Target
			- for an infinite effect : a constant vector (ie. the direction of the light).
		\param d Distance from the camera to the orthgonal plane were the effect is drawn */
	void Display(OR_Vector3D v, OR_Float d);

	/** get the type of the lensflare */
	virtual OR_LENSFLARE_Type GetLensFlareType()
	{ return OR_LENSFLARE_Undefined; }

	/** to turn the shader into a bilboard one
		\return OR_OK : the operation is ok, OR_ERROR : shader is NULL */
	OR_RETURN_CODE EnableBilboarding();

	/** set the shader used to render the effect */
	void SetShader(OR_Shader* s)
	{ MyShader=s; }
	/** get the shader used to render the effect */
	OR_Shader* GetShader()
	{ return MyShader; }
	/** set the size of the effect on both directions */
	void SetSize(OR_Float s[2])
	{ Size[X]=s[X]; Size[Y]=s[Y]; }
	/** set the size of the effect on one directions */
	void SetSize(OR_Coord_XYZW c, OR_Float s)
	{ Size[c]=s; }
	/** get the size */
	OR_Float* GetSize()
	{ return Size; }
	/** set the distance */
	void SetDistance(OR_Float d)
	{ Distance=d; }
	/** get the distance */
	OR_Float GetDistance()
	{ return Distance; }

    //-------------------------------------------------------------------------
    /** @name overloaded functions from OR_Shadable */
    //-------------------------------------------------------------------------
    //@{
	virtual void ProcessAllFaces();
	virtual void ProcessOneFace(OR_U32 nNumFace);
	virtual void AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCorrdArray, OR_U32* &aFaceArray, 
							   OR_U32& nNbrVert, OR_U32& nNbrFace );
    //@}   
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildFromFile( OR_File& file );
	virtual void BuildToFile( OR_File& file );
    //@}
};



/*-------------------------------------------------------------------*/
/*                   class OR_LensFlare_Infinite                     */
/*-------------------------------------------------------------------*/
/* an infinite lens flare.                                           */
/*-------------------------------------------------------------------*/

/// an infinite lens flare.
/**
	An infinite lensflare is given by a constant vector, wich is the direction of the light.
	\author Gabriel
*/

class ORION3D_API OR_LensFlare_Infinite: public OR_LensFlare
{
private:

	/** direction of the light */
	OR_Vector3D Direction;

public:

	/** constructor */
	OR_LensFlare_Infinite();

	/** set the direction */
	void SetDirection(OR_Vector3D d)
	{ Direction=d; }
	/** get the direction */
	OR_Vector3D GetDirection()
	{ return Direction; }

	/** get the type of the lensflare */
	virtual OR_LENSFLARE_Type GetLensFlareType()
	{ return OR_LENSFLARE_Infinite; }

	/* special effect virtual functions ***************************************/
	/** update  the lensflare */
	virtual void Update();
	/** draw the lensflare */
	virtual void Draw();

	//-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildFromFile( OR_File& file );
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_LensFlare_Infinite);
    //@}
};


/*-------------------------------------------------------------------*/
/*                   class OR_LensFlare_Local                        */
/*-------------------------------------------------------------------*/
/* a local lens flare.                                               */
/*-------------------------------------------------------------------*/

/// a local lens flare.
/**
	An infinite lensflare is given by a constant vector, wich is the direction of the light.
	\author Gabriel
*/

class ORION3D_API OR_LensFlare_Local: public OR_LensFlare
{
private:
	/** the target (for example a light) of the effect. */
	OR_Object* Target;
public:
	/** constructor */
	OR_LensFlare_Local();

	/** get the type of the lensflare */
	virtual OR_LENSFLARE_Type GetLensFlareType()
	{ return OR_LENSFLARE_Local; }

	/** set the direction */
	void SetTarget(OR_Object* t)
	{ Target=t; }
	/** get the direction */
	OR_Object* GetTarget()
	{ return Target; }

	/* special effect virtual functions ***************************************/
	/** update  the lensflare */
	virtual void Update();
	/** draw the lensflare */
	virtual void Draw();
	
	//-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildFromFile( OR_File& file );
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_LensFlare_Local);
    //@}
};

} // namespace OR

#endif /* #ifndef _OR_LENS_FLARE_ */


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
