//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifndef __OR_ConstantForce_h_
#define __OR_ConstantForce_h_

#ifdef __GNUG__
    #pragma interface
#endif

#include "../configuration/OR_Config.h"
#include "OR_Force_ABC.h"
#include "../maths/OR_Maths.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_ConstantForce
*   @brief  A simple constant force
*/
/// \author Gabriel Peyré 2001-08-31
//=============================================================================
class ORION3D_API OR_ConstantForce: public OR_Force_ABC
{

public:

    OR_ConstantForce(OR_Vector3D& Force_ = OR_Vector3D(0,0,-9.8f));
    virtual ~OR_ConstantForce();

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
	void SetForce(OR_Vector3D& g);
	OR_Vector3D& GetForce();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	void BuildFromFile( OR_File& file );
	void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_ConstantForce);
    //@}

private:

	/** Force vector. ( F  = m*g )*/
	OR_Vector3D Force_;
};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_ConstantForce.inl"
#endif


#endif // __OR_ConstantForce_h_
