/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_TreeFunction_ABC.h
 *  \brief  Definition of class \c FSW_TreeFunction_ABC
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/
#ifndef _FSW_TREEFUNCTION_H_
#define _FSW_TREEFUNCTION_H_

#include "FSW_Config.h"
#include "FSW_Maths.h"

FSW_BEGIN_NAMESPACE

class FSW_QuadTreeNode;
class FSW_QuadTreeVertex;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_TreeFunction_ABC
 *  \brief  The base class for all spherical functions.
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 *
 *  Describe the methods that functions defined on the manifold must 
 *  implement. One for vertex based and one for face based.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_TreeFunction_ABC
{

public:

    //-------------------------------------------------------------------------
    /** \name The default implementation set coefficient to zero. */
    //-------------------------------------------------------------------------
    //@{
	virtual FSW_Float GetValue( FSW_Float rU, FSW_Float rV ) const;
    //@}

    //-------------------------------------------------------------------------
    /** \name Helpers. */
    //-------------------------------------------------------------------------
    //@{
	void ComputeSphericalNormal(FSW_Vector3D& Normal, FSW_Float theta, FSW_Float phi) const;
	void ComputePlanarNormal(FSW_Vector3D& Normal, FSW_Float theta, FSW_Float phi) const;
    //@}

};

FSW_END_NAMESPACE


#endif // _FSW_TREEFUNCTION_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2002 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
