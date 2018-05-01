
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_QuadTreeVertex.h
 *  \brief  Definition of class \c GW_QuadTreeVertex
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_QUADTREEVERTEX_H_
#define _GW_QUADTREEVERTEX_H_

#include "../gw_core/GW_Config.h"
#include "../gw_multiresolution/GW_SphericalMaths.h"
#include "GW_TreeFunction_ABC.h"

GW_BEGIN_NAMESPACE

class GW_DataChunk_ABC;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_QuadTreeVertex
 *  \brief  A vertex of the teslated sphere.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 *
 *  These vertex are refered to by the various node of the quadtree defining the sphere.
 *	In case of vertex base computations (e.g. for interpolating wavelets), the vertex
 *	cary the information, i.e. a single \c GW_Float slot that can hold : 
 *		- The data of the function (before a forward wavelet transform is made, or
 *		  after a backward transform).
 *		- A detail wavelet coefficient (once the forward transform is made), or
 *		  a tempory coarse level coefficient (during the transform).
 *
 *  On construction of the teslated sphere, the coordinates of the vertex
 *	is assigned.
 */ 
/*------------------------------------------------------------------------------*/

class GW_QuadTreeVertex
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_QuadTreeVertex();
    virtual ~GW_QuadTreeVertex();
    //@}

	//-------------------------------------------------------------------------
    /** \name Accessors */
    //-------------------------------------------------------------------------
    //@{
	void SetPosition(const GW_Vector3D& Pos);
	GW_Vector3D& GetPosition();
	const GW_Vector3D& GetPositionConst() const;
	void SetValue(GW_Float rVal);
	GW_Float GetValue() const;
#ifdef GW_DEBUG
	GW_I32 GetQuantifiedValue() const;
	void SetQuantifiedValue(GW_I32 nQuantifiedValue);
#endif
    //@}

    //-------------------------------------------------------------------------
    /** \name Data chunk management. */
    //-------------------------------------------------------------------------
    //@{
	GW_DataChunk_ABC* GetDataChunk();
	void SetDataChunk(GW_DataChunk_ABC& DataChunk);
    //@}

private:

	/** position of the vertex */
	GW_Vector3D Pos_;
	/** Value hold by the vertex. For vertex base transform *ONLY* */
	GW_Float rVal_;
#ifdef GW_DEBUG
	GW_I32 nQuantifiedValue_;
#endif

	/** for vertex based wavelet transform ONLY : 
		the data chunk the transform use to store some precomputed values. */
	GW_DataChunk_ABC* pDataChunk_;

};

/*------------------------------------------------------------------------------*/
/** \name a list of GW_QuadTreeVertex */
/*------------------------------------------------------------------------------*/
//@{
typedef std::list<GW_QuadTreeVertex*> T_QuadTreeVertexList;
typedef T_QuadTreeVertexList::iterator IT_QuadTreeVertexList;
typedef T_QuadTreeVertexList::reverse_iterator RIT_QuadTreeVertexList;
typedef T_QuadTreeVertexList::const_iterator CIT_QuadTreeVertexList;
typedef T_QuadTreeVertexList::const_reverse_iterator CRIT_QuadTreeVertexList;
//@}

/*------------------------------------------------------------------------------*/
/** \name a vector of GW_QuadTreeVertex */
/*------------------------------------------------------------------------------*/
//@{
typedef std::vector<GW_QuadTreeVertex*> T_QuadTreeVertexVector;
typedef T_QuadTreeVertexVector::iterator IT_QuadTreeVertexVector;
typedef T_QuadTreeVertexVector::reverse_iterator RIT_QuadTreeVertexVector;
typedef T_QuadTreeVertexVector::const_iterator CIT_QuadTreeVertexVector;
typedef T_QuadTreeVertexVector::const_reverse_iterator CRIT_QuadTreeVertexVector;
//@}

/*------------------------------------------------------------------------------*/
/** \name a map of GW_QuadTreeVertex */
/*------------------------------------------------------------------------------*/
//@{
typedef std::map<GW_U32, GW_QuadTreeVertex*> T_QuadTreeVertexMap;
typedef T_QuadTreeVertexMap::iterator IT_QuadTreeVertexMap;
typedef T_QuadTreeVertexMap::reverse_iterator RIT_QuadTreeVertexMap;
typedef T_QuadTreeVertexMap::const_iterator CIT_QuadTreeVertexMap;
typedef T_QuadTreeVertexMap::const_reverse_iterator CRIT_QuadTreeVertexMap;
//@}

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_QuadTreeVertex.inl"
#endif


#endif // _GW_QUADTREEVERTEX_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
