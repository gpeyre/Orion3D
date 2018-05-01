
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_DeltaFunction.h
 *  \brief  Definition of class \c GW_DeltaFunction
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_DELTAFUNCTION_H_
#define _GW_DELTAFUNCTION_H_

#include "../gw_core/GW_Config.h"
#include "../gw_multiresolution/GW_SphericalMaths.h"
#include "../gw_multiresolution/GW_QuadTree.h"
#include "../gw_multiresolution/GW_TreeFunction_ABC.h"
	
GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_DeltaFunction
 *  \brief  Set only one coefficient to 1, all others set to 0.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 *
 *  Usefull to represent the wavelet functions. Just compute a backward
 *	transform on the tree.
 */ 
/*------------------------------------------------------------------------------*/

class GW_DeltaFunction: public GW_TreeFunction_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_DeltaFunction( GW_U32 nDepth, GW_U32 nCoefNum, GW_U32 nVertNum=0, GW_Float rSPike=1 );
    virtual ~GW_DeltaFunction();
    //@}

	void PostBuildTree( GW_QuadTree& Tree );

	void SetDepth( GW_U32 nDepth );
	void SetCoefNum( GW_U32 nCoefNum );
	void SetVertNum( GW_U32 nVertNum );
	void SetSpikeValue( GW_Float rSPike );

private:

	GW_U32 nDepth_;
	GW_U32 nCoefNum_;
	GW_U32 nVertNum_;
	GW_Float rSPike_;
};

GW_END_NAMESPACE


#endif // _GW_DELTAFUNCTION_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
 