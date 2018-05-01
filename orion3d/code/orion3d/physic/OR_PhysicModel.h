
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PhysicModel.h
 *  \brief Definition of class \c OR_PhysicModel
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_PhysicModel_h_
#define __OR_PhysicModel_h_

#include "../configuration/OR_Config.h"
#include "../objects/OR_Mesh.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"



#undef PI	
#undef HALFPI	
#undef TWOPI
#undef INVPI
#include "../../opcode/Opcode.h"
using namespace Opcode;
#undef OR


namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_PhysicModel
 *  \brief  A model used for collision detection.
 *  \author Gabriel Peyré 2001-09-13
 *  
 *	This is a wrapper between the \b Orion3D mesh and the \b Opcode collision models.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_PhysicModel: public OR_ShellObject_ABC
{

public:

    OR_PhysicModel(OR_Mesh& Mesh);
    virtual ~OR_PhysicModel();

	OPCODE_Model& GetOpcodeModel();
	OR_Mesh&      GetMesh();

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);
	//@}

private:

	/** the \b Orion3D mesh used as a base for the Opcode model */
	OR_Mesh* pMesh_;
	/** the model used for collision detection */
	OPCODE_Model OpcodeModel_;

};

typedef list<OR_PhysicModel*>		T_PhysicModelList;
typedef T_PhysicModelList::iterator IT_PhysicModelList;

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_PhysicModel.inl"
#endif


#endif // __OR_PhysicModel_h_

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

