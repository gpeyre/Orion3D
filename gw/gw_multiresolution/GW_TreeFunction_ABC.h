/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_TreeFunction_ABC.h
 *  \brief  Definition of class \c GW_TreeFunction_ABC
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/
#ifndef _GW_TREEFUNCTION_H_
#define _GW_TREEFUNCTION_H_

#include "../gw_core/GW_Config.h"
#include "../gw_multiresolution/GW_SphericalMaths.h"

GW_BEGIN_NAMESPACE

class GW_QuadTreeNode;
class GW_QuadTreeVertex;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_TreeFunction_ABC
 *  \brief  The base class for all spherical functions.
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 *
 *  Describe the methods that functions defined on the manifold must 
 *  implement. One for vertex based and one for face based.
 */ 
/*------------------------------------------------------------------------------*/

class GW_TreeFunction_ABC
{

public:

    //-------------------------------------------------------------------------
    /** \name The default implementation set coefficient to zero. */
    //-------------------------------------------------------------------------
    //@{
	virtual GW_Float GetValue( GW_Float rU, GW_Float rV ) const;
    //@}

    //-------------------------------------------------------------------------
    /** \name Helpers. */
    //-------------------------------------------------------------------------
    //@{
	void ComputeSphericalNormal(GW_Vector3D& Normal, GW_Float theta, GW_Float phi) const;
	void ComputePlanarNormal(GW_Vector3D& Normal, GW_Float theta, GW_Float phi) const;
    //@}

};

GW_END_NAMESPACE


#endif // _GW_TREEFUNCTION_H_


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
