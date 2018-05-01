/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaMesh.h
 *  \brief Definition of class \c OR_MetaMesh
 *  \author Gabriel Peyré 2002/04/15
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_MetaMesh_h_
#define __OR_MetaMesh_h_


#include "../configuration/OR_Config.h"
#include "../objects/OR_Mesh.h"
#include "OR_MetaObject_ABC.h"


namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MetaMesh
 *  \brief  AddCommentHere
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	Use a mesh to produce an isosurface that fit the mesh.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_MetaMesh: public OR_MetaObject_ABC
{
public:

    //-------------------------------------------------------------------------
    /** \name Constructor and destructor */
    //-------------------------------------------------------------------------
    //@{
	OR_MetaMesh( OR_Mesh* pMesh );
	~OR_MetaMesh();
	//@}

	//-------------------------------------------------------------------------
	/** \name overload from \c OR_MetaObject_ABC */
	//-------------------------------------------------------------------------
	//@{
	virtual void AddMetaValue(OR_MetaGrid& grid);
	//@}

	
	void		SetInfluenceRadius(OR_Float radius);
	OR_Float	GetInfluenceRadius();
	void		SetMesh( OR_Mesh& mesh );
	OR_Mesh*	GetMesh();

private:

	/** the mesh used to compute the shape*/
	OR_Mesh* pMesh_;
	/** the system we need to solve to compute the coef */
	OR_MatrixNxP CoefSystem_;
	/** the coeeficient of the radial functions */
	OR_VectorND Coef_;
	/** the right hand side of the system */
	OR_VectorND Rhs_;
	/** the radius of influence of each function */
	OR_Float rInfluenceRadius_;
	/** does the system needs to be re-computed */
	OR_Bool bSystemNeedsUpdate_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_MetaMesh.inl"
#endif

#endif // __OR_MetaMesh_h_

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

