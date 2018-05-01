
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Collision.h
 *  \brief definition of class OR_Collision
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Collision_h_
#define __OR_Collision_h_

#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"

namespace OR {

class OR_RigidBody;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Collision
 *  \brief  A collision between two rigid body.
 *  \author Gabriel Peyré 2001-08-28
 *  
 *	This class is here to make the transition between \b OPCODE and \b Orion3D.
 *	All collision detected by \b OPCODE genreates an \c OR_Collision.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Collision
{

public:

    OR_Collision();
    virtual ~OR_Collision();

    //-------------------------------------------------------------------------
    /** \name Resolution of the collision */
    //-------------------------------------------------------------------------
    //@{
	void Resolve();
    //@}

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	OR_RigidBody* GetBodyA();
	OR_RigidBody* GetBodyB();
	void          SetBodyA(OR_RigidBody& BodyA);
	void          SetBodyB(OR_RigidBody& BodyB);


	OR_Vector3D& GetPosition();
	void         SetPosition(OR_Vector3D& Postion);
	OR_Vector3D& GetNormal();
	void         SetNormal(OR_Vector3D& Normal);
	OR_Vector3D& GetEdgeA();
	void		 SetEdgeA(OR_Vector3D& EdgeA);
	OR_Vector3D& GetEdgeB();
	void		 SetEdgeB(OR_Vector3D& EdgeA);
	OR_Bool		 IsVertexFace();
	void		 SetIsVertexFace(OR_Bool bIsvertexFace);
    //@}


private:

	/** first rigid body involved */
	OR_RigidBody* pBodyA_;
	/** second rigid body involved */
	OR_RigidBody* pBodyB_;

	/** position of the collision point, in world frame */
	OR_Vector3D	Position_;
	/** normal at collision, pointing from A to B.
		for edge/edge contact : Normal_ = Edge_A_^EdgeB_ */
	OR_Vector3D	Normal_;
	/** for edge/edge collision : edge of A colliding, in world frame */
	OR_Vector3D EdgeA_;
	/** for edge/edge collision : edge of B colliding, in world frame */
	OR_Vector3D EdgeB_;
	/** is the collision a vertex/face one ? if not, it is an edge/edge one. */
	OR_Bool bIsvertexFace_;

};

typedef list<OR_Collision*>        T_CollisionList;
typedef T_CollisionList::iterator IT_CollisionList;

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_Collision.inl"
#endif


#endif // __OR_Collision_h_

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

