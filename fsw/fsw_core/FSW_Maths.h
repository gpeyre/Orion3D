
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_Maths.h
 *  \brief  Definition of class \c FSW_Maths
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_MATHS_H_
#define _FSW_MATHS_H_

#include "FSW_Config.h"
#include "FSW_Vector3D.h"

FSW_BEGIN_NAMESPACE

class FSW_QuadTreeNode;
class FSW_QuadTree;
class FSW_TreeFunction_ABC;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_Maths
 *  \brief  Basic Maths functions.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 *
 *  A bunch of useful functions to work on a sphere. Warning : All 
 *  vectors are assumed to live un the sphere of radius 1 : the must 
 *  be normalized.
 */ 
/*------------------------------------------------------------------------------*/
class FSW_Maths
{

public:

    //-------------------------------------------------------------------------
    /** \name Spherical geometry helpers. */
    //-------------------------------------------------------------------------
    //@{
    static FSW_Float SphericalTriangleArea(const FSW_Vector3D& v1, const FSW_Vector3D& v2, const FSW_Vector3D& v3);
	static FSW_Float FlatTriangleArea(const FSW_Vector3D& v1, const FSW_Vector3D& v2, const FSW_Vector3D& v3);
	static void FlatTriangleNormal(FSW_Vector3D& Normal, const FSW_Vector3D& v1, const FSW_Vector3D& v2, const FSW_Vector3D& v3);
    //@}

    //-------------------------------------------------------------------------
    /** \name Wrapper functions to make computations directly on quadtree node. */
    //-------------------------------------------------------------------------
    //@{
	static FSW_Float SphericalTriangleArea(const FSW_QuadTreeNode& Node);
	static FSW_Float FlatTriangleArea(const FSW_QuadTreeNode& Node);
	static void FlatTriangleNormal(FSW_Vector3D& Normal, const FSW_QuadTreeNode& Node);
    //@}

	typedef FSW_Float (*T_RecurseIntegralComputation_Function)(FSW_QuadTreeNode& CurNode, void* pChunk);

	static FSW_Float RecurseIntegralComputation(FSW_QuadTree& Tree, T_RecurseIntegralComputation_Function pFunc, void* pChunk=NULL);
	static FSW_Float RecurseIntegralComputation_Rec(FSW_QuadTreeNode& CurNode, T_RecurseIntegralComputation_Function pFunc, void* pChunk);

	static FSW_Float ComputeIntegral(FSW_QuadTree& Tree);
	static FSW_Float ComputeL1Distance(FSW_QuadTree& Tree, FSW_TreeFunction_ABC& Func);
	static FSW_Float ComputeL2Distance(FSW_QuadTree& Tree, FSW_TreeFunction_ABC& Func);


	static void ConvertCartesianToSpherical(const FSW_Vector3D& Pos, FSW_Float& rLong, FSW_Float& rLat);

private:

	static FSW_Float Helper_ComputeIntegral(FSW_QuadTreeNode& CurNode, void* pChunk);
	static FSW_Float Helper_ComputeL1Distance(FSW_QuadTreeNode& CurNode, void* pChunk);
	static FSW_Float Helper_ComputeL2Distance(FSW_QuadTreeNode& CurNode, void* pChunk);

};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_Maths.inl"
#endif


#endif // _FSW_MATHS_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
