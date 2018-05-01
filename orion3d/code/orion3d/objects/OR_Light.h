/*----------------------------------------------------------------------*/
/*                                OR_Light.h                            */
/*----------------------------------------------------------------------*/
/* definitions of light class                                           */            
/*----------------------------------------------------------------------*/

#ifndef _OR_LIGHT_H_
#define _OR_LIGHT_H_

/** \file 
	Contains the definition of a light class, with 2 main types  :

		- spot : a local light.
		- direct : an infinite light.

	Each type contains 2 sub-types :
		- free : the light can be directed using a target.
		- directionnal : the light can be directed using a vector [the direction].
	At each frame, the engine emmit new paticules, bringing up to life dead
	particules, if it's possible [to avoid to re-allocate memory].
	\author Gabriel.
**/

#include "../configuration/OR_Config.h"
#include "OR_Object.h"
#include "OR_Gizmo.h"

namespace OR
{
	
/*----------------------------------------------------------------------*/
/*                                classe OR_Light                       */
/*----------------------------------------------------------------------*/
/* super class for all Light class                                      */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Object                                         */
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief class OR_Light in group group_object
 */

/// super class for all Light class.
/** 
	The OR_Light class implement paramters common to all light class, ie.
	the base colors.
	\author Gabriel
*/
class ORION3D_API OR_Light:	public OR_Object
{

public:

    //-------------------------------------------------------------------------
    /** \name constructor & destructor */
    //-------------------------------------------------------------------------
    //@{
    OR_Light();
	OR_Light( const OR_Light& Dup );
	virtual ~OR_Light();
    //@}

    //-------------------------------------------------------------------------
    /** \name colors management */
    //-------------------------------------------------------------------------
    //@{
	/** set the ambient component of the light */
	void SetAmbient(OR_Float val[4]);
	/** set the specular component of the light */
	void SetSpecular(OR_Float val[4]);
	/** set the diffuse component of the light */
	void SetDiffuse(OR_Float val[4]);
	/** set the ambient component of the light */
	void SetAmbient(OR_Coord_RVBA c, OR_Float val);
	/** set the specular component of the light */
	void SetSpecular(OR_Coord_RVBA c, OR_Float val);
	/** set the diffuse component of the light */
	void SetDiffuse(OR_Coord_RVBA c, OR_Float val);

	void SetDiffuse(OR_Vector4D color);
	void SetSpecular(OR_Vector4D color);
	void SetAmbient(OR_Vector4D color);
    //@}

    //-------------------------------------------------------------------------
    /** \name light ID management */
    //-------------------------------------------------------------------------
    //@{
	OR_U32 GetLightID();
	OR_U32 AssignLightID();
    //@}


	/** set the proprieties of the light */
	virtual void SetProperties();

    //-------------------------------------------------------------------------
    /** \name overload functions of OR_Object */
    //-------------------------------------------------------------------------
    //@{
	/** get the type of the object */
	OR_Elements GetType()		{ return OR_LIGHT; }
	/** overload function from OR_Object */
	virtual void Put()						{ }
	/** overload function from OR_Object */
	virtual void Draw()						{ }

	/** overload Enable() OR_Object method */
    OR_Bool Enable();
	/** overload Disable() OR_Object method */
    OR_Bool Disable();
	/** overload Togle() OR_Object method */
    OR_Bool Toggle();
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
    //@}

protected:
	
	/** OpenGL target for the light */
    OR_U32 nLightID_;;
	
	/** ambient color */
    OR_Vector4D Ambient;
	/** diffuse color */
	OR_Vector4D Diffuse;
	/** specular color */
	OR_Vector4D Specular;
	/** assign the color to OpenGL */
	void SetColors();

};

/*----------------------------------------------------------------------*/
/*                    classe OR_Light_Spot                              */
/*----------------------------------------------------------------------*/
/* super class for all spot class [ie. a cone of light]                 */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light                                          */
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief super class for all spot class [ie. a cone of light]
 */

/// super class for all Light class.
/** 
	inherit from class OR_Light
	\author Gabriel
*/

class ORION3D_API OR_Light_Spot: public OR_Light
{
protected:
	/** cutoff value */
	OR_Float CutOff;
	/** exponent value */
	OR_Float Exponent;
	/** constant|linear|quadratic atenuation */
	OR_Vector3D Atenuation;
public:
	/** constructor */
	OR_Light_Spot();	
	virtual ~OR_Light_Spot() {}
	/** set the cutoff value */
	void SetCutOff(OR_Float val);
	/** set the exponent value */
	void SetExponent(OR_Float val);
	/** set the atenuation value */
	void SetAtenuation(OR_Float val[3]);
	/** set the proprieties of the light */ 
	virtual void SetProperties( ); 

	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
};

/*----------------------------------------------------------------------*/
/*                    classe OR_Light_FreeSpot                          */
/*----------------------------------------------------------------------*/
/* a spot [ie. a cone of light] given by its position and a vector      */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light_Spot                                     */
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief a spot [ie. a cone of light] given by its position and a vector      
 */

/// super class for all Light class.
/** 
	inherit from class OR_Light_Spot
	\author Gabriel
*/

class ORION3D_API OR_Light_FreeSpot: public OR_Light_Spot
{
public:
	/** constructor */
	OR_Light_FreeSpot();
	virtual ~OR_Light_FreeSpot();
	/** set the direction of the light, ie. Z axis */
	void SetDirection(OR_Vector3D v);
	
	/** overload of OR_Object functions */
	virtual OR_Elements GetType()	
	{ return OR_LIGHT_Free_Spot; }
	/** overload of OR_Object functions */
	virtual void Put();
	/** overload of OR_Object functions */
	virtual void Draw();

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	OR_DEFINE_SERIALIZATION(OR_Light_FreeSpot);
    //@}
};

/*----------------------------------------------------------------------*/
/*                    classe OR_Light_TargetSpot                        */
/*----------------------------------------------------------------------*/
/* a spot [ie. a cone of light] given by its position and a target      */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light_Spot                                     */
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief a spot [ie. a cone of light] given by its position and a target     
 */

/// super class for all Light class.
/** 
	inherit from class OR_Light_Spot
	\author Gabriel
*/

class ORION3D_API OR_Light_TargetSpot: public OR_Light_Spot
{
public:
	/** constructor */
	OR_Light_TargetSpot();
	/* overload of OR_Object functions */
	virtual OR_Elements GetType()	
	{ return OR_LIGHT_Target_Spot; }
	virtual void Put();
	virtual void Draw();
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	OR_DEFINE_SERIALIZATION(OR_Light_TargetSpot);
    //@}
};

/*----------------------------------------------------------------------*/
/*                    classe OR_Light_Direct                            */
/*----------------------------------------------------------------------*/
/* super class for all direct class [ie. an infinite light]             */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light                                          */
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief super class for all direct class [ie. an infinite light]     
 */

/// super class for all Light class.
/** 
	inherit from class OR_Light 
	\author Gabriel
*/


class ORION3D_API OR_Light_Direct: public OR_Light
{
public:

	OR_Light_Direct();
};

/*----------------------------------------------------------------------*/
/*                    classe OR_Light_FreeDirect                        */
/*----------------------------------------------------------------------*/
/* a direct [ie. an infinite light] given by its position and a vector  */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light_Direct                                   */
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief a direct [ie. an infinite light] given by its position and a vector    
 */

/// super class for all Light class.
/** 
	inherit from class OR_Light_Direct 
	\author Gabriel
*/


class ORION3D_API OR_Light_FreeDirect: public OR_Light_Direct
{
public:
	/** constructor */
	OR_Light_FreeDirect();
	virtual ~OR_Light_FreeDirect() {}

	/** set the direction of the light, ie. Z axis */
	void SetDirection(OR_Vector3D v);
	/* overload of OR_Object functions */
	virtual OR_Elements GetType()
	{ return OR_LIGHT_Free_Direct; }
	virtual void Put();
	virtual void Draw();
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	OR_DEFINE_SERIALIZATION(OR_Light_FreeDirect);
    //@}
};

/*----------------------------------------------------------------------*/
/*                    classe OR_Light_TargetDirect                      */
/*----------------------------------------------------------------------*/
/* a direct [ie. an infinite light] given by its position and a target  */
/*----------------------------------------------------------------------*/
/* inherit from class OR_Light_Direct                                   */
/*----------------------------------------------------------------------*/

/*! \ingroup group_object
 *  \brief a direct [ie. an infinite light] given by its position and a target    
 */

/// super class for all Light class.
/** 
	inherit from class OR_Light_Direct  
	\author Gabriel
*/

class ORION3D_API OR_Light_TargetDirect: public OR_Light_Direct
{
public:
	/** constructor */
	OR_Light_TargetDirect();

	/* overload of OR_Object functions */
	virtual OR_Elements GetType()	
	{ return OR_LIGHT_Target_Direct; }
	virtual void Put();
	virtual void Draw();
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	OR_DEFINE_SERIALIZATION(OR_Light_TargetDirect);
    //@}
};


} // namespace OR



#ifdef OR_USE_INLINE
#   include "OR_Light.inl"
#endif

#endif     /* #ifndef _OR_LIGHT_H_ */


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
