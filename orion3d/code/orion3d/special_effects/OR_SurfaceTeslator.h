/*------------------------------------------------------------*/
/*                    OR_SurfaceTeslator.h                    */
/*------------------------------------------------------------*/
/* definition of class OR_SurfaceTesslator and OR_SurfNode    */
/*------------------------------------------------------------*/

/** \file 
	Contains the definition of a general mathemaic surface teslator.

	A surface teslator used an equation, which is defined by something that must
	inherit from class OR_SurfaceEquation, to teslate it and render it at a given
	level of detail, using a quadtree to store the data.
	\author Gabriel.
**/

#ifndef _OR_SURFACE_TESLATOR_H_
#define _OR_SURFACE_TESLATOR_H_

#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"
#include "../objects/OR_Object.h"

namespace OR
{
	
/*------------------------------------------------------------*/
/* class OR_SurfVertex                                        */
/*------------------------------------------------------------*/

/** a vertex of a surface, with its normal, and its courbure 
	\author Gabriel */
class OR_SurfVertex
{
public:
	OR_Vector3D* Vertex;
	OR_Vector3D* Normal;
	OR_Float Courbure;
	
	/** constructor : create the vertex and the normal */
	OR_SurfVertex();
	/** destructor : delete vertex & normal */
	virtual ~OR_SurfVertex();
};

/*------------------------------------------------------------*/
/* class OR_SurfaceEquation                                   */
/*------------------------------------------------------------*/

/** a class that is able to compute the values of a surface 
	\author Gabriel */
class ORION3D_API OR_SurfaceEquation
{
public:
	/** compute the value at a given u and v
		can use the corner value [if != NULL], for exemple to do central differencing */
	virtual void ComputeValue(OR_SurfVertex* vert,
				 			  OR_Float u, OR_Float v,
							  OR_SurfVertex* no, OR_SurfVertex* ne, 
							  OR_SurfVertex* se, OR_SurfVertex* so)
	{  }

	/** get the minimum value of u 
		\return minimum value of u */
	virtual OR_Float GetUMin() { return 0; }
	/** get the maximum value of u 
		\return maximum value of u */
	virtual OR_Float GetUMax()	{ return 1; }
	/** get the minimum value of u */
	virtual OR_Float GetVMin()	{ return 0; }
	/** get the minimum value of u */
	virtual OR_Float GetVMax()	{ return 1; }
};

/*------------------------------------------------------------*/
/*      class OR_SurfNode                                     */
/*------------------------------------------------------------*/

/** a node of the quad tree used by the teslator to compute the ground
	\author Gabriel */
class ORION3D_API OR_SurfNode
{

private:

	OR_Bool IsLeafNode;

public:

	OR_SurfVertex* Vert_NO;
	OR_SurfVertex* Vert_NE;
	OR_SurfVertex* Vert_SO;
	OR_SurfVertex* Vert_SE;

	OR_SurfNode* Node_NO;
	OR_SurfNode* Node_NE;
	OR_SurfNode* Node_SE;
	OR_SurfNode* Node_SO;

	/** constructor, initialize the sons */
	OR_SurfNode();
	/** destructor : delete each sub-tree */
	virtual ~OR_SurfNode();
	/** set the node as a leaf one */
	void SetAsLeaf();
	/** set the node as a non leaf one */
	void SetAsNonLeaf();
	/** is the node a leaf one ? */
	OR_Bool IsLeaf();

};

/*---------------------------------------------------------------*/
/*              class OR_SurfaceTeslator                         */
/*---------------------------------------------------------------*/

/** compute a quad tree representing the surface
	and render it using dynamic LOD. */
class ORION3D_API OR_SurfaceTeslator: OR_Object
{
private:
	/** the objetc which is able to compute the values of the surface */
	OR_SurfaceEquation* MyEquation;
	/** the root of the quad tree which represent the surface */
	OR_SurfNode* Root;
	/** maximum of recursion in the tree */
	OR_I32 MaxDepth;
	/** does the tree needs to be re-build ? */
	OR_Bool NeedsRebuild;
	/** when to stop the recursion for a given build */
	OR_I32 DepthStop;
	/** rotation axe */
	OR_Vector3D Axe;
	/** rotation value on its axe */
	OR_Float Rot;
	/** recursive function for building the tree */
	void BuildTreeRec(OR_I32 depth, OR_SurfNode* cur_node,
					  OR_Float UMin, OR_Float Umax, OR_Float VMin, OR_Float VMax);
	/** recursive function for updating the tree */
	void UpdateRec(OR_SurfNode* cur_node);
	/** recursive function for drawing the tree */
	void DrawRec(OR_SurfNode* cur_node);
public:
	/** constructor
		\param myequation the object which is able to compute values of the surface */
	OR_SurfaceTeslator(OR_SurfaceEquation* myequation);
	/** destructor : delete the quadtree */
	virtual ~OR_SurfaceTeslator();
	/** build the tree to a given depth	
		\param depth depth of recursion in the quadtree */
	void BuildTree(OR_I32 depth);
	/** build the tree to a maximum depth */
	void BuildTree();
	/** update the tree : 
			- recurse first to construct necessary vertex
			- recurse a second time to ajust and fix cracks in the surface */
	void Update();
	/* overload virtual function from OR_Object */
	/** return the type of the OR_Object */
	virtual OR_Elements GetType();
	/** rotate the surface 
		\param val value of the rotation */
	virtual void Rotate(OR_Float val);
	/** set the rotation angle of the surface
		\param val new value of the rotation angle */
	void SetAngle(OR_Float val);
	/** set the rotation axe of the surface 
		\param axe new rotation axe of the surface */
	void SetAxe(OR_Vector3D axe);
	/** draw the surface */
	virtual void Draw();
};


} // namespace OR

#endif	/* #ifndef _OR_SURFACE_TESLATOR_H_ */


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////