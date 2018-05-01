/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Particule.h
 *  \brief description of a point particule
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Particule_h_
#define __OR_Particule_h_

#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Particule
 *  \brief  A point particule
 *  \author Gabriel Peyré 2001-07-18
 *
 *  A point particule, that can be updated using a Verlet scheme integration
 *	of motion laws
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Particule: public OR_Serializable
{

public:

    //-------------------------------------------------------------------------
    /** \name constructor & destructor */
    //-------------------------------------------------------------------------
    //@{
	OR_Particule();
    virtual ~OR_Particule();
    //@}

	//-------------------------------------------------------------------------
    /** \name update method */
    //-------------------------------------------------------------------------
    //@{
	void ReSet();
	void UpdatePhysics_Verlet();
	void UpdatePhysics_RK4(OR_U32 nNbStep);
	void UpdatePhysics_Euler();
    //@}

    //-------------------------------------------------------------------------
    /** \name forces & constraint management */
    //-------------------------------------------------------------------------
    //@{
	void AddForce(OR_Vector3D& force);
	void AddImpulse(OR_Vector3D& impulse);
	void ResetAccumulators();
	void AddConstaint();
	void RemoveConstraint();
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OR_Vector3D& GetPosition();
	void         SetPosition(OR_Vector3D& position);
	OR_Vector3D& GetOldPosition();
	void         SetOldPosition(OR_Vector3D& position);
	void		 ReSetPosition(OR_Vector3D& position);

	OR_Float     GetInvMass();
	void         SetInvMass(OR_Float rInvMass);
	OR_Vector3D& GetSpeed();
	void         SetSpeed(OR_Vector3D&   Speed);
	OR_Float     GetBounce();
	void         SetBounce(OR_Float rBounce);
    //@}

    //-------------------------------------------------------------------------
    /** @name helpers */
    //-------------------------------------------------------------------------
    //@{
	void  Translate(OR_Vector3D& direction);
	void  ComputeSpeed();
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_Particule);
    //@}

protected:

	/** current position of the particule */
	OR_Vector3D Pos_;
	/** last position of the particule */
	OR_Vector3D PosOld_;
	/** the speed of the particule, computed using Pos_ and OldPos_*/
	OR_Vector3D Speed_;
	/** force acting on the particule */
	OR_Vector3D ForceAccumulator_;
	/** impulse acting on the particule */
	OR_Vector3D ImpulseAccumulator_;
	/** inverse of the mass of the particule */
	OR_Float rInvMass_;
	/** how many constaints are acting on the particule */
	OR_I32 nNbrConstaints_;
	/** bounce resitution coef */
	OR_Float rBounce_;

    //-------------------------------------------------------------------------
    /** @name RK4 specific datas */
    //-------------------------------------------------------------------------
    //@{
	/** RK4 accumulator for position integration */
	OR_Vector3D RK4SpeedAccumulator_;
	/** RK4 accumulator for speed integration */
	OR_Vector3D RK4PosAccumulator_;
	/** position at current time */
	OR_Vector3D CurPos_;
	/** speed at current time */
	OR_Vector3D CurSpeed_;
    //@}

	/** was the function 'SetSpeed' called ? (used for Verlet integration scheme) */
	OR_Bool bIsSpeedSpecified_;
};


/** a list of particules */
typedef list<OR_Particule*> T_ParticuleList;
/** an iterator on a list of particules */
typedef T_ParticuleList::iterator IT_ParticuleList;

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_Particule.inl"
#endif


#endif // __OR_Particule_h_

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

