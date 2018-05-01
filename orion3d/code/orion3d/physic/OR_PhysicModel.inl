/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PhysicModel.inl
 *  \brief Inlined methods for \c OR_PhysicModel
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_PhysicModel.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicModel::GetOpcodeModel
 *
 *  \return The \b Opcode model that is used for collision detection.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OPCODE_Model& OR_PhysicModel::GetOpcodeModel()
{
	return OpcodeModel_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicModel::GetMesh
 *
 *  \return The \b Orion3D model used as base for the \b Opcode model.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Mesh& OR_PhysicModel::GetMesh()
{
	OR_ASSERT( pMesh_!=NULL );
	return *pMesh_;
}


} // End namespace OR

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

