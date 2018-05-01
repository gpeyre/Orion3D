/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Constraint_ABC.h
 *  \brief defintion of OR_Constraint_ABC
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Constraint_ABC_h_
#define __OR_Constraint_ABC_h_

#include "OR_Particule.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Constraint_ABC
 *  \brief  Base class for every constraint.
 *  \author Gabriel Peyré 2001-07-18
 *  
 *	Constraints can be of two kinds :
 *		- relaxable :
 *		- non relaxable :
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Constraint_ABC: public OR_Serializable
{

public:

    //-------------------------------------------------------------------------
    /** \name constructor & destructor */
    //-------------------------------------------------------------------------
    //@{
    OR_Constraint_ABC(OR_Particule* pTarget1=NULL, OR_Particule* pTarget2=NULL);
    virtual ~OR_Constraint_ABC();
    //@}

    //-------------------------------------------------------------------------
    /** \name abstract methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void	Update()=0;
	virtual OR_Bool IsRelaxable()=0;
    //@}

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	void          SetTarget1(OR_Particule* pTarget);
	void          SetTarget2(OR_Particule* pTarget);
	OR_Particule* GetTarget1();
	OR_Particule* GetTarget2();
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file )=0;
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file )=0;
    //@}

protected:

	OR_Particule* pTarget1_;
	OR_Particule* pTarget2_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_Constraint_ABC.inl"
#endif


#endif // __OR_Constraint_ABC_h_

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

