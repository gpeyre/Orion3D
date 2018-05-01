
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_QuadTreeVertex.h
 *  \brief  Definition of class \c FSW_QuadTreeVertex
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_QUADTREEVERTEX_H_
#define _FSW_QUADTREEVERTEX_H_

#include "FSW_Config.h"
#include "FSW_Maths.h"
#include "FSW_TreeFunction_ABC.h"

FSW_BEGIN_NAMESPACE

class FSW_DataChunk_ABC;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_QuadTreeVertex
 *  \brief  A vertex of the teslated sphere.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 *
 *  These vertex are refered to by the various node of the quadtree defining the sphere.
 *	In case of vertex base computations (e.g. for interpolating wavelets), the vertex
 *	cary the information, i.e. a single \c FSW_Float slot that can hold : 
 *		- The data of the function (before a forward wavelet transform is made, or
 *		  after a backward transform).
 *		- A detail wavelet coefficient (once the forward transform is made), or
 *		  a tempory coarse level coefficient (during the transform).
 *
 *  On construction of the teslated sphere, the coordinates of the vertex
 *	is assigned.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_QuadTreeVertex
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_QuadTreeVertex();
    virtual ~FSW_QuadTreeVertex();
    //@}

	//-------------------------------------------------------------------------
    /** \name Accessors */
    //-------------------------------------------------------------------------
    //@{
	void SetPosition(const FSW_Vector3D& Pos);
	FSW_Vector3D& GetPosition();
	const FSW_Vector3D& GetPositionConst() const;
	void SetValue(FSW_Float rVal);
	FSW_Float GetValue() const;
#ifdef FSW_DEBUG
	FSW_I32 GetQuantifiedValue() const;
	void SetQuantifiedValue(FSW_I32 nQuantifiedValue);
#endif
    //@}

    //-------------------------------------------------------------------------
    /** \name Data chunk management. */
    //-------------------------------------------------------------------------
    //@{
	FSW_DataChunk_ABC* GetDataChunk();
	void SetDataChunk(FSW_DataChunk_ABC& DataChunk);
    //@}

private:

	/** position of the vertex */
	FSW_Vector3D Pos_;
	/** Value hold by the vertex. For vertex base transform *ONLY* */
	FSW_Float rVal_;
#ifdef FSW_DEBUG
	FSW_I32 nQuantifiedValue_;
#endif

	/** for vertex based wavelet transform ONLY : 
		the data chunk the transform use to store some precomputed values. */
	FSW_DataChunk_ABC* pDataChunk_;

};

/*------------------------------------------------------------------------------*/
/** \name a list of FSW_QuadTreeVertex */
/*------------------------------------------------------------------------------*/
//@{
typedef list<FSW_QuadTreeVertex*> T_QuadTreeVertexList;
typedef T_QuadTreeVertexList::iterator IT_QuadTreeVertexList;
typedef T_QuadTreeVertexList::reverse_iterator RIT_QuadTreeVertexList;
typedef T_QuadTreeVertexList::const_iterator CIT_QuadTreeVertexList;
typedef T_QuadTreeVertexList::const_reverse_iterator CRIT_QuadTreeVertexList;
//@}

/*------------------------------------------------------------------------------*/
/** \name a vector of FSW_QuadTreeVertex */
/*------------------------------------------------------------------------------*/
//@{
typedef vector<FSW_QuadTreeVertex*> T_QuadTreeVertexVector;
typedef T_QuadTreeVertexVector::iterator IT_QuadTreeVertexVector;
typedef T_QuadTreeVertexVector::reverse_iterator RIT_QuadTreeVertexVector;
typedef T_QuadTreeVertexVector::const_iterator CIT_QuadTreeVertexVector;
typedef T_QuadTreeVertexVector::const_reverse_iterator CRIT_QuadTreeVertexVector;
//@}

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_QuadTreeVertex.inl"
#endif


#endif // _FSW_QUADTREEVERTEX_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
