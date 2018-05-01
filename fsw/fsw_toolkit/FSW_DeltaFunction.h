
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_DeltaFunction.h
 *  \brief  Definition of class \c FSW_DeltaFunction
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_DELTAFUNCTION_H_
#define _FSW_DELTAFUNCTION_H_

#include "../fsw_core/FSW_Config.h"
#include "../fsw_core/FSW_Maths.h"
#include "../fsw_core/FSW_QuadTree.h"
#include "../fsw_core/FSW_TreeFunction_ABC.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_DeltaFunction
 *  \brief  Set only one coefficient to 1, all others set to 0.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 *
 *  Usefull to represent the wavelet functions. Just compute a backward
 *	transform on the tree.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_DeltaFunction: public FSW_TreeFunction_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_DeltaFunction( FSW_U32 nDepth, FSW_U32 nCoefNum, FSW_U32 nVertNum=0, FSW_Float rSPike=1 );
    virtual ~FSW_DeltaFunction();
    //@}

	void PostBuildTree( FSW_QuadTree& Tree );

	void SetDepth( FSW_U32 nDepth );
	void SetCoefNum( FSW_U32 nCoefNum );
	void SetVertNum( FSW_U32 nVertNum );
	void SetSpikeValue( FSW_Float rSPike );

private:

	FSW_U32 nDepth_;
	FSW_U32 nCoefNum_;
	FSW_U32 nVertNum_;
	FSW_Float rSPike_;
};

FSW_END_NAMESPACE


#endif // _FSW_DELTAFUNCTION_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
 