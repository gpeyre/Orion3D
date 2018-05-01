
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Maths.h
 *  \brief Definition of class \c OR_Maths
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Maths_h_
#define __OR_Maths_h_

#include "../configuration/OR_Config.h"
#include "../orion3d_maths/OML_Maths.h"
#include "../orion3d_maths/OML_Matrix4x4.h"
#include "../orion3d_maths/OML_Matrix3x3.h"
#include "../orion3d_maths/OML_MatrixNxP.h"
#include "../orion3d_maths/OML_Vector2D.h"
#include "../orion3d_maths/OML_Vector3D.h"
#include "../orion3d_maths/OML_Vector4D.h"
#include "../orion3d_maths/OML_VectorND.h"
#include "../orion3d_maths/OML_SparseMatrix.h"
#include "../orion3d_maths/OML_Quaternion.h"

namespace OR {


typedef ORION3D_API OML::OML_Matrix4x4	OR_Matrix4x4;
typedef ORION3D_API OML::OML_Matrix3x3	OR_Matrix3x3;
typedef ORION3D_API OML::OML_MatrixNxP	OR_MatrixNxP;
typedef ORION3D_API OML::OML_SparseMatrix		OR_SparseMatrix;
typedef ORION3D_API OML::OML_SparseMatrixBlock	OR_SparseMatrixBlock;
typedef ORION3D_API OML::OML_Vector4D	OR_Vector4D;
typedef ORION3D_API OML::OML_Vector3D	OR_Vector3D;
typedef ORION3D_API OML::OML_Vector2D	OR_Vector2D;
typedef ORION3D_API OML::OML_VectorND	OR_VectorND;
typedef ORION3D_API OML::OML_Quaternion	OR_Quaternion;

/** vector of matrices */
typedef vector<OR_Matrix4x4> T_MatrixVector;
/** iterator for vector of matrices */
typedef T_MatrixVector::iterator IT_MatrixVector;

class OR_Plane;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Maths
 *  \brief  Basic maths functions that fits nowhere else.
 *  \author Gabriel Peyré 2001-11-05
 *
 *	\example maths_test/main.cpp
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Maths:	public OML::OML_Maths
{
	
public:
	
    //-------------------------------------------------------------------------
    /** \name \b OpenGL operations */
    //-------------------------------------------------------------------------
    //@{
	static void GetCurrentModelView(OR_Matrix4x4& mat);
	static void SetCurrentModelView(OR_Matrix4x4& mat);
	static void MultiplyCurrentModelView(OR_Matrix4x4& mat);
	
	static void GetCurrentProjection(OR_Matrix4x4& mat);
	static void SetCurrentProjection(OR_Matrix4x4& mat);
	static void MultiplyCurrentProjection(OR_Matrix4x4& mat);
    //@}

	//-------------------------------------------------------------------------
    /** \name plane classify */
    //-------------------------------------------------------------------------
    //@{
	static OR_Position Classify(OR_Vector3D vect, OR_Plane* P);
	static OR_Position Classify(OR_Vector3D vect, OR_Plane* P, OR_Float Decal);
    //@}


};

} // End namespace OR

#ifdef OR_USE_INLINE
	#include "OR_Maths.inl"
#endif

#endif // __OR_Maths_h_

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

