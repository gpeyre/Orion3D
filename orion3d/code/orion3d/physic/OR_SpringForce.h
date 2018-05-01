
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SpringForce.h
 *  \brief Definition of class \c OR_SpringForce
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SpringForce_h_
#define __OR_SpringForce_h_

#include "../configuration/OR_Config.h"
#include "OR_Force_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SpringForce
 *  \brief  spring between a fixed point in space and the object.
 *  \author Gabriel Peyré 2001-09-10
 *  
 *	If you want to create a spring between two objects, use a constraint.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_SpringForce: public OR_Force_ABC
{

public:

    OR_SpringForce(OR_Vector3D& Anchor=OR_Vector3D(0,0,0), OR_Float rStiffness = 0.005f, OR_Float rLength = 1, OR_Float rDampling=0);
    virtual ~OR_SpringForce();

	//-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OR_Float GetDampling();
	void	 SetDampling(OR_Float rDampling);
	void	 SetStiffness(OR_Float rStiffness);
	OR_Float GetStiffness();
	void	 SetRestLength(OR_Float rRestLength);
	OR_Float GetRestLength();
	void	     SetAnchor(OR_Vector3D& Anchor);
	OR_Vector3D& GetAnchor();
    //@}

	//-------------------------------------------------------------------------
    /** @name OR_Force_ABC overload */
    //-------------------------------------------------------------------------
    //@{
    void ProcessParticule(OR_Particule& particule);
	void ProcessObject(OR_RigidBody& obj);
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	void BuildFromFile( OR_File& file );
	void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_SpringForce);
    //@}

private:

	/** the dampling coefficient */
	OR_Float rDampling_;
	/** the stength of the spring */
	OR_Float rStiffness_;
	/** size of the spring when it is at rest */
	OR_Float rRestLength_;
	/** position of the anchor the object is linked to */
	OR_Vector3D Anchor_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_SpringForce.inl"
#endif


#endif // __OR_SpringForce_h_

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

