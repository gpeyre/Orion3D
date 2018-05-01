
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SphericalJoint.h
 *  \brief Definition of class \c OR_SphericalJoint
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SphericalJoint_h_
#define __OR_SphericalJoint_h_

#include "../configuration/OR_Config.h"
#include "OR_Joint_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SphericalJoint
 *  \brief  a spherical joint.
 *  \author Gabriel Peyré 2001-10-31
 *  
 *	This joint only allow rotation around a point. It removes 3 DOF.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_SphericalJoint: public OR_Joint_ABC
{

public:

	OR_SphericalJoint(); 
	OR_SphericalJoint(OR_RigidBody& RB1, OR_RigidBody& RB2);
    virtual ~OR_SphericalJoint();

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	void SetAnchorPoint(OR_Vector3D& v);
	void SetAnchorPointRelative1(OR_Vector3D& v);
	void SetAnchorPointRelative2(OR_Vector3D& v);
	OR_Vector3D& GetAnchorPointRelative1();
	OR_Vector3D& GetAnchorPointRelative2();
    //@}

	//-------------------------------------------------------------------------
    /** \name methods to overload */
    //-------------------------------------------------------------------------
    //@{
	/** the numer of degree of freedom that this constraint removes from the system */
	virtual OR_U32 GetDimension();
	/** compute and place the block in the jacobian matrix */
	virtual void Update(OR_SparseMatrix& Jacobian, OR_VectorND& Constr, OR_VectorND& ConstrDeriv,
						OR_U32 nOffset);
    //@}

		//-------------------------------------------------------------------------
    /** @name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file )	
	{ /* \todo fill this */ }
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file )
	{ /* \todo fill this */ }
	/** macro to define class-specific function */
	OR_DEFINE_SERIALIZATION(OR_SphericalJoint);
    //@}


private:

	/** anchor position in coordinates relative to rigid body 1 */
	OR_Vector3D P1_;
	/** anchor position in coordinates relative to rigid body 2 */
	OR_Vector3D P2_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_SphericalJoint.inl"
#endif


#endif // __OR_SphericalJoint_h_

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

