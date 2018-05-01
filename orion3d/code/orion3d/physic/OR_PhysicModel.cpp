/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PhysicModel.cpp
 *  \brief Definition of class \c OR_PhysicModel
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_PhysicModel.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"

#include "OR_PhysicModel.h"

#ifndef OR_USE_INLINE
	    #include "OR_PhysicModel.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicModel constructor
 *
 *  \param  Mesh the \b Orion3D mesh used to get vertex and faces.
 *  \author Gabriel Peyré 2001-09-13
 *
 *	Creates an \b Opcode model and intialize it's options.
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicModel::OR_PhysicModel(OR_Mesh& Mesh)
:	pMesh_	( &Mesh )
{
	// 1-1) Build a quantized no-leaf tree
	OPCODECREATE OPCC;
	OPCC.NbTris		= (udword)  pMesh_->GetNbFaces();
	OPCC.NbVerts	= (udword)  pMesh_->GetNbVertex();
	OPCC.Tris		= (udword*) pMesh_->GetFaceList();
	OPCC.Verts		= (Point*)  pMesh_->GetVertsArray();
	//	OPCC.Rules		= SPLIT_COMPLETE | SPLIT_LARGESTAXIS;
	OPCC.Rules		= SPLIT_COMPLETE | SPLIT_SPLATTERPOINTS;
	OPCC.NoLeaf		= true;
	OPCC.Quantized	= true;
	OpcodeModel_.Build(OPCC);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicModel destructor
 *
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicModel::~OR_PhysicModel()
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicModel::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_PhysicModel::BuildSonList(T_ShellObjectList& ShellSonList)
{
	ShellSonList.clear();

	if( pMesh_!=NULL )
		OR_ADD_SHELL_SON(ShellSonList, *pMesh_, OR_String("mesh_") + pMesh_->GetName() );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicModel::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_PhysicModel::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	/* NOTHING */
}



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

