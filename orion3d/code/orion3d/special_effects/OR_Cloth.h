//*****************************************************************************
/// \author Gabriel Peyré
//*****************************************************************************

#ifndef __OR_Cloth_h_
#define __OR_Cloth_h_

#include "../configuration/OR_Config.h"
#include "../physic/OR_Particule.h"
#include "../physic/OR_DampedSpringConstraint.h"
#include "../physic/OR_ParticuleManager.h"
#include "../physic/OR_ConstraintManager.h"
#include "../physic/OR_MaximumDistanceConstraint.h"
#include "../objects/OR_Object.h"
#include "../objects/OR_Gizmo.h"
#include "../objects/OR_CubeGizmo.h"
#include "../special_effects/OR_SpecialEffect.h"

#define CHECK_INSIDE_CLOTH(x, y)  ((x>=0) && (y>=0) && (x<aNbrParticules_[0]) && (y<aNbrParticules_[1]) )
#define ACCESS_PARTICULE_ARRAY(x, y)  (x + (y)*aNbrParticules_[0])

namespace OR {

//=============================================================================
/**
*   @class  OR_Cloth
*   @brief  A cloth, composed of particule linked by constaints
*
*	\code
* 
*   .    .
*	.    .
*   6----8.....
*   |    |    .
*   |    |    .
*   3----5----7....
*   |    |    |
*   |    |    |
*   1----2----4....
*   .    .    .
*   .    .    .
*
*	\endcode
*	The particule 1 manage the spring betwee :
*		- 1->2 and 1->4 [side springs]
*		- 1->5 and 2->4 [diagonal springs]
*		- 1->7 and 1->3 [structural springs]
*
*	\example cloth_test/main.cpp
*/
/// \author Gabriel Peyré
//=============================================================================
class ORION3D_API OR_Cloth: public OR_SpecialEffect, public OR_ParticuleManager
{

public:

    OR_Cloth(OR_I32 nNbrParticulesX=10, OR_I32 nNbrParticulesY=10, OR_CubeGizmo* pGizmo=NULL);
    virtual ~OR_Cloth();

	//-------------------------------------------------------------------------
    /** @name accessor */
    //-------------------------------------------------------------------------
    //@{
	void SetNbrParticules(OR_I32 nNbrParticulesX, OR_I32 nNbrParticulesY);
	OR_I32* GetNbrParticules();
	void SetGizmo(OR_CubeGizmo& pGizmo);
	OR_CubeGizmo* GetGizmo();
	OR_Particule* GetParticule(OR_I32 nX, OR_I32 nY);

	OR_Float GetSideStiffness();
	OR_Float GetDiagonalStiffness();
	OR_Float GetStructuralStiffness();
	void  SetSideStiffness(OR_Float rSideStiffness);
	void  SetDiagonalStiffness(OR_Float rDiagonalStiffness);
	void  SetStructuralStiffness(OR_Float rStructuralStiffness);
	OR_Float GetMaxRelativeElongation();
	void  SetMaxRelativeElongation(OR_Float rMaxRelativeElongation);

	OR_Float GetSideDampling();
	OR_Float GetDiagonalDampling();
	OR_Float GetStructuralDampling();
	void  SetSideDampling(OR_Float rSideDampling);
	void  SetDiagonalDampling(OR_Float rDiagonalDampling);
	void  SetStructuralDampling(OR_Float rStructuralDampling);

	OR_Float GetParticuleInvMass();
	void  SetParticuleInvMass(OR_Float rInvMass);
    //@}

	void Build();


	void UseRelaxableConstraints(OR_Bool bUse);

    //-------------------------------------------------------------------------
    /** @name overload from special effect */
    //-------------------------------------------------------------------------
    //@{
	void Draw();
	void Update();
    //@}

	//-------------------------------------------------------------------------
    /** \name helpers */
    //-------------------------------------------------------------------------
    //@{
	void AutoSetDampling();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildFromFile( OR_File& file );
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_Cloth);
    //@}

private:

    //-------------------------------------------------------------------------
    /** \name private methods */
    //-------------------------------------------------------------------------
    //@{
	void Reset();
	void PositionateParticules();
	void SetUpConstraints();
    //@}

	/** number of particules on X and Y axis */
	OR_I32 aNbrParticules_[2];
	/** a gizmo to specify size and position of the cloth */
	OR_CubeGizmo* pGizmo_;

    //-------------------------------------------------------------------------
    /** @name arrays */
    //-------------------------------------------------------------------------
    //@{
	/** an array to store paritcules */
	OR_Particule* pParticuleArray_;
	/** side springs */
	OR_DampedSpringConstraint* pSideSpringArray_;
	/** diagonal springs */
	OR_DampedSpringConstraint* pDiagonalSpringArray_;
	/** structural springs */
	OR_DampedSpringConstraint* pStructuralSpringArray_;
	/** maximum distance constraints array */
	OR_MaximumDistanceConstraint* pConstraintArray_;	
    //@}

	/** does the cloth needs to be re-built ? */
	OR_Bool bNeedsRebuild_;
	/** the manager that store all constraints in the cloth */
	OR_ConstraintManager ConstraintManager;

    //-------------------------------------------------------------------------
    /** @name spring constraints */
    //-------------------------------------------------------------------------
    //@{
	/** stiffness of the side springs */
	OR_Float rSideStiffness_;
	/** stiffness of the diagonal springs */
	OR_Float rDiagonalStiffness_;
	/** stiffness of the structural springs */
	OR_Float rStructuralStiffness_;
	/** dampling of the side springs */
	OR_Float rSideDampling_;
	/** dampling of the diagonal springs */
	OR_Float rDiagonalDampling_;
	/** dampling of the structural springs */
	OR_Float rStructuralDampling_;


	/** maximum elongation of the springs */
	OR_Float rMaxRelativeElongation_;
    //@}

    //-------------------------------------------------------------------------
    /** \name NAME HERE particules constants */
    //-------------------------------------------------------------------------
    //@{
	OR_Float rParticuleInvMass_;
    //@}


	OR_Bool bUseRelaxableConstraints_;
};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_Cloth.inl"
#endif


#endif // __OR_Cloth_h_

