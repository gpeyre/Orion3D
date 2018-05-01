//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifndef __OR_Force_ABC_h_
#define __OR_Force_ABC_h_

#include "../configuration/OR_Config.h"
#include "OR_RigidBody.h"
#include "OR_Particule.h"
#include "../utils/OR_Serializable.h"
#include "../shell/OR_ShellObject_ABC.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_Force_ABC
*   @brief  Base class for all force.
*
*	A force just have to be able to compute the vector to apply to
*		- a particule : ProcessParticule
*		- a physic handler (ie. a rigid body) : ProcessObject
*
*	\todo Add a "Range of action", for example, "always", "once", "timestamp",
*	to specify for how long the force is active.
*/
/// \author Gabriel Peyré 2001-08-31
//=============================================================================
class ORION3D_API OR_Force_ABC: public OR_Serializable, public OR_ShellObject_ABC
{

public:
	
	OR_Force_ABC();
	virtual ~OR_Force_ABC();

    virtual void ProcessParticule(OR_Particule& particule)=0;
	virtual void ProcessObject(OR_RigidBody& handler)=0;

    //-------------------------------------------------------------------------
    /** @name activity management */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool IsActive();
	OR_Bool Disable();
	OR_Bool Enable();
	OR_Bool Toggle();

	OR_Bool GetActivity()
	{ return this->IsActive(); }
	void SetActivity(OR_Bool bActivity)
	{ bIsActive_ = bActivity; }
    //@}

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	
	OR_DECL_SHELL_ACCESSOR_FUNC(Activity, OR_Force_ABC, Bool);
    //@}

private:

	OR_Bool bIsActive_;
};

} // End namespace OR


#ifdef OR_USE_INLINE
#   include "OR_Force_ABC.inl"
#endif


#endif // __OR_Force_ABC_h_
