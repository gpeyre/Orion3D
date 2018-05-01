//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifndef __OR_GravityForce_h_
#define __OR_GravityForce_h_

#include "../configuration/OR_Config.h"
#include "OR_Force_ABC.h"
#include "../maths/OR_Maths.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_GravityForce
*   @brief  A gravity force.
*/
/// \author Gabriel Peyré 2001-08-31
//=============================================================================
class ORION3D_API OR_GravityForce: public OR_Force_ABC
{

public:

    OR_GravityForce(OR_Vector3D& g = OR_Vector3D(0,0,-9.8f));
    virtual ~OR_GravityForce();

    //-------------------------------------------------------------------------
    /** @name OR_Force_ABC overload */
    //-------------------------------------------------------------------------
    //@{
    void ProcessParticule(OR_Particule& particule);
	void ProcessObject(OR_RigidBody& handler);
    //@}

    //-------------------------------------------------------------------------
    /** @name accessors */
    //-------------------------------------------------------------------------
    //@{
	void SetGravity(OR_Vector3D& g);
	OR_Vector3D& GetGravity();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	void BuildFromFile( OR_File& file );
	void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_GravityForce);
    //@}
private:

	/** gravity vector. ( F  = m*g )*/
	OR_Vector3D g_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_GravityForce.inl"
#endif


#endif // __OR_GravityForce_h_
