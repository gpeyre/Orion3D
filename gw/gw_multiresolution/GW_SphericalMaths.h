
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_SphericalMaths.h
 *  \brief  Definition of class \c GW_SphericalMaths
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_SPHERICALMATHS_H_
#define _GW_SPHERICALMATHS_H_

#include "../gw_core/GW_Config.h"
#include "../gw_maths/GW_Maths.h"

GW_BEGIN_NAMESPACE

class GW_QuadTreeNode;
class GW_QuadTree;
class GW_TreeFunction_ABC;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_SphericalMaths
 *  \brief  Basic Maths functions.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 *
 *  A bunch of useful functions to work on a sphere. Warning : All 
 *  vectors are assumed to live un the sphere of radius 1 : the must 
 *  be normalized.
 */ 
/*------------------------------------------------------------------------------*/
class GW_SphericalMaths
{

public:

    //-------------------------------------------------------------------------
    /** \name Spherical geometry helpers. */
    //-------------------------------------------------------------------------
    //@{
    static GW_Float SphericalTriangleArea(const GW_Vector3D& v1, const GW_Vector3D& v2, const GW_Vector3D& v3);
	static GW_Float FlatTriangleArea(const GW_Vector3D& v1, const GW_Vector3D& v2, const GW_Vector3D& v3);
	static void FlatTriangleNormal(GW_Vector3D& Normal, const GW_Vector3D& v1, const GW_Vector3D& v2, const GW_Vector3D& v3);
    //@}

    //-------------------------------------------------------------------------
    /** \name Wrapper functions to make computations directly on quadtree node. */
    //-------------------------------------------------------------------------
    //@{
	static GW_Float SphericalTriangleArea(const GW_QuadTreeNode& Node);
	static GW_Float FlatTriangleArea(const GW_QuadTreeNode& Node);
	static void FlatTriangleNormal(GW_Vector3D& Normal, const GW_QuadTreeNode& Node);
    //@}

	typedef GW_Float (*T_RecurseIntegralComputation_Function)(GW_QuadTreeNode& CurNode, void* pChunk);

	static GW_Float RecurseIntegralComputation(GW_QuadTree& Tree, T_RecurseIntegralComputation_Function pFunc, void* pChunk=NULL);
	static GW_Float RecurseIntegralComputation_Rec(GW_QuadTreeNode& CurNode, T_RecurseIntegralComputation_Function pFunc, void* pChunk);

	static GW_Float ComputeIntegral(GW_QuadTree& Tree);
	static GW_Float ComputeL1Distance(GW_QuadTree& Tree, GW_TreeFunction_ABC& Func);
	static GW_Float ComputeL2Distance(GW_QuadTree& Tree, GW_TreeFunction_ABC& Func);


	static void ConvertCartesianToSpherical(const GW_Vector3D& Pos, GW_Float& rLong, GW_Float& rLat);

private:

	static GW_Float Helper_ComputeIntegral(GW_QuadTreeNode& CurNode, void* pChunk);
	static GW_Float Helper_ComputeL1Distance(GW_QuadTreeNode& CurNode, void* pChunk);
	static GW_Float Helper_ComputeL2Distance(GW_QuadTreeNode& CurNode, void* pChunk);

};

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_SphericalMaths.inl"
#endif


#endif // _GW_SPHERICALMATHS_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
