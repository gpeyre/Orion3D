//*****************************************************************************
///	\author Gabriel Peyré 2001-08-30
//*****************************************************************************

#ifndef __OR_ForceManager_h_
#define __OR_ForceManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Force_ABC.h"
#include "../utils/OR_ManagerMap_Template.h"
#include "../utils/OR_Serializable.h"
#include "../shell/OR_ShellObject_ABC.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_ForceManager
*   @brief  A manager for the forces.
*
*	Provide function to process all force acting on a particule or on an object.
*/
///	\author Gabriel Peyré 2001-08-30
//=============================================================================

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Force_ABC>;

class ORION3D_API OR_ForceManager: public OR_ManagerMap_Template<OR_Force_ABC>, public OR_Serializable, public OR_ShellObject_ABC
{

public:

	void ProcessParticule(OR_Particule& particule);
	void ProcessObject(OR_RigidBody& handler);
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	void BuildFromFile( OR_File& file );
	void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_ForceManager);
    //@}

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
    //@}
};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_ForceManager.inl"
#endif


#endif // __OR_ForceManager_h_
