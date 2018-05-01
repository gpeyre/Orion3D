/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ParticuleSystem.h
 *  \brief Definition of OR_ParticuleSystem.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ParticuleSystem_h_
#define __OR_ParticuleSystem_h_

#include "../configuration/OR_Config.h"
#include "OR_Emitter_ABC.h"
#include "OR_SpecialEffect.h"
#include "OR_DisplayableParticule.h"
#include "../physic/OR_ParticuleManager.h"
#include "../objects/OR_Mesh.h"
#include "../shaders/OR_ShaderManager.h"


namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ParticuleSystem
 *  \brief  A particule system.
 *  \author Gabriel Peyré 2001-07-18
 *	A particule system is a particule manager with some extra features :
 *		- an emmitter to initialize particule.
 *		- a garbage collector to recycle dead particules.
 *
 *	\example particles_test/main.cpp
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_ParticuleSystem: public OR_ParticuleManager, public OR_SpecialEffect
{

public:

    OR_ParticuleSystem();
    virtual ~OR_ParticuleSystem();

    //-------------------------------------------------------------------------
    /** \name Overload of methods from \c OR_SpecialEffect */
    //-------------------------------------------------------------------------
    //@{
	void Update();
	void Draw();
    //@}

    //-------------------------------------------------------------------------
    /** \name source management */
    //-------------------------------------------------------------------------
    //@{
	void  SetDebit(OR_Float rDebit);
	void  ModifiyDebit(OR_Float mod);
	void  SetInitialSpeed(OR_Float rVal);
	void  SetEmissionVariance(OR_Float rVariance);
	void  SetSpeedVariance(OR_Float rVariance);
	void  SetEnergyStart(OR_Float rEnergystart);
	void  SetEnergyStartVariance(OR_Float rEnergystartvariance);
	void  SetEnergyLost(OR_Float rEnergylost);
	void  SetEnergyLostVariance(OR_Float rEnergylostvariance);
	void  SetParticuleInvMass(OR_Float rVal);
	void  SetParticuleInvMassVariance(OR_Float val);
	OR_Float GetDebit();
	OR_Float GetInitialSpeed();
	OR_Float GetEmissionVariance();
	OR_Float GetSpeedVariance();
	OR_Float GetEnergyStart();
	OR_Float GetEnergyStartVariance();
	OR_Float GetEnergyLost();
	OR_Float GetEnergyLostVariance();
	OR_Float GetParticuleInvMass();
	OR_Float GetParticuleInvMassVariance();
	void  ModifyDebit(OR_Float val);
	void  SetMaxRadius(OR_Float rMaxradius);
	void  SetNbMaxParticules(OR_I32 val);
	void  ClearGarbageCollector();
	void  ClearSystem();
	OR_Emitter_ABC* GetEmmitter();
	void            SetEmmitter(OR_Emitter_ABC& Emitter);
    //@}

    //-------------------------------------------------------------------------
    /** \name Manage the way the particules are displayed */
    //-------------------------------------------------------------------------
    //@{
	void     SetShape(OR_Mesh& shape);
	void     SetStartColor(OR_Float r, OR_Float g, OR_Float b, OR_Float a);
	void     SetEndColor(OR_Float r, OR_Float g, OR_Float b, OR_Float a);
	void     SetParticuleBounce(OR_Float val);
	OR_Mesh* GetShape();
	OR_Float*   GetStartColor();
	OR_Float*   GetEndColor();
	OR_Float    GetParticuleBounce();
	OR_RETURN_CODE   EnableBilboarding();
	void             SetBlendingMode(OR_Blending_Mode mode);
	OR_Blending_Mode GetBlendingMode();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name Query the system */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool IsSourceActive();
	OR_Bool IsSystemActive();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void BuildFromFile( OR_File& file );
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_ParticuleSystem);
    //@}

private:

    //-------------------------------------------------------------------------
    /** \name Dead particules */
    //-------------------------------------------------------------------------
    //@{
	/** the list of dead particules to recycle */
	T_ParticuleList GarbageCollector_;
	/** the radius maximum that a particule can reach (killed if it goes over), <0 means infinite */
	OR_Float rMaxRadius_;
    //@}


    //-------------------------------------------------------------------------
    /** \name debit control */
    //-------------------------------------------------------------------------
    //@{
	/** number of particules emitted each frame : if <=0, no emission */
	OR_Float rDebit_;
	/** the fractionar part */
	OR_Float rRestToEmit_;
	/** total alive particules */
	OR_I32 nNbrParticules_;
	/** maximum number of particules */
	OR_I32 nNbrMaxParticules_;
	/** time of the last update, in milli seconds */
	OR_I64 nLastFrame_;
    //@}

    //-------------------------------------------------------------------------
    /** \name Source control */
    //-------------------------------------------------------------------------
    //@{
	/** the emitter of particules */
	OR_Emitter_ABC* pEmmitter_;
	/** the medium energy of each particule at the emission */
	OR_Float rEnergyStart_;
	/** the medium amout of energy lost each frame by the particule */
	OR_Float rEnergyLost_;
	/** the 'random' part of the energy at the begining [each particule doesn't have exactly the same value] */
	OR_Float rEnergyStartVariance_;
	/** the 'random' part of the energy lost  [each particule doesn't have exactly the same value] */
	OR_Float rEnergyLostVariance_;
	/** variance to the initial speed, in degree (you can reprsent that value as the angle of the cone of emission). */
	OR_Float rEmissionVariance_;
	/** variance to the lengh of the initial speed */
	OR_Float rSpeedVariance_;
	/** medium mass of a particule */
	OR_Float rParticuleInvMass_;
	/** the 'random' part of the particule mass  [each particule doesn't have exactly the same value] */
	OR_Float rParticuleInvMassVariance_;
	/** medium length of the initial speed */
	OR_Float rInitialSpeed_;
    //@}

    //-------------------------------------------------------------------------
    /** \name Particule display proprieties */
    //-------------------------------------------------------------------------
    //@{
	/** the shape of the particule */
	OR_Mesh* pShape_;
	/** color of the particules at the begining */
	OR_Float aStartColor_[4];
	/** color of the particules at the end */
	OR_Float aEndColor_[4];
	/** bounce of a particule */
	OR_Float rParticuleBounce_;
	/** the way blending is computed */
	OR_Blending_Mode BlendingMode_;
    //@}

    //-------------------------------------------------------------------------
    /** \name Private methods */
    //-------------------------------------------------------------------------
    //@{
	void SetColor(OR_Float energy);
	void InitParticule(OR_Particule& particule);
    //@}

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ParticuleSystem.inl"
#endif


#endif // __OR_ParticuleSystem_h_

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

