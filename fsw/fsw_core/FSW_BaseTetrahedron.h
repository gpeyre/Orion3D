
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BaseTetrahedron.h
 *  \brief  Definition of class \c FSW_BaseTetrahedron
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_BASETETRAHEDRON_H_
#define _FSW_BASETETRAHEDRON_H_

#include "FSW_Config.h"
#include "FSW_BaseMesh_ABC.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_BaseTetrahedron
 *  \brief  A base mesh consisting of an octahedron, that subdivides into a sphere.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 *
 *  The octahedron is composed of 8 faces (2 pyramid), and gives an 
 *  easy way to tesslate a sphere with a consistant naming scheme.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_BaseTetrahedron:	public FSW_BaseMesh_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_BaseTetrahedron();
    virtual ~FSW_BaseTetrahedron();
    //@}

	
	/*------------------------------------------------------------------------------*/
    /** \name Overloaded. */
    /*------------------------------------------------------------------------------*/
    //@{
    virtual void BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector );
	virtual FSW_QuadTreeNode* GetRelativeSon(FSW_QuadTreeNode& Son, FSW_QuadTreeVertex& Direction);

	virtual void Positionate( FSW_QuadTreeNode& CurNode );
	virtual void ConvertToLocalFrame( const FSW_Vector3D& Pos, FSW_Float& rU, FSW_Float& rV );

	virtual FSW_U32 GetNbrVertex( FSW_U32 nDepth );
	virtual FSW_U32 GetNbrFace( FSW_U32 nDepth );
	virtual FSW_U32 GetNbrEdge( FSW_U32 nDepth );
    //@}

	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the base mesh in the compressed files. */
	virtual const char* GetBaseMeshName()
	{ return "FSW_BaseTetrahedron"; }
    //@}

private:
	
	/** a very useful lookup table that encode 
	    proximity relations between the 8 quadrant of the octaedre */
	static FSW_U32 aSubTreeNeighbor_[4][3];

};

FSW_END_NAMESPACE


#endif // _FSW_BASETETRAHEDRON_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
