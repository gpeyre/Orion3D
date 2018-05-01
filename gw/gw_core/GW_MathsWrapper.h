/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_MathsWrapper.h
 *  \brief  Definition of class \c GW_MathsWrapper
 *  \author Gabriel Peyré
 *  \date   6-8-2003
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_MATHSWRAPPER_H_
#define _GW_MATHSWRAPPER_H_

#include "GW_Config.h"
#include "GW_Serializable.h"
#include "../gw_maths/GW_Maths.h"
#include "../gw_maths/GW_Vector2D.h"
#include "../gw_maths/GW_Vector3D.h"
#include "../gw_maths/GW_VectorND.h"
#include "../gw_maths/GW_Matrix3x3.h"
#include "../gw_maths/GW_MatrixNxP.h"
#include "../gw_maths/GW_SparseMatrix.h"

namespace GW {

/* GW_Vector3D ***********************************************/
inline
GW_Ofstream& operator<<(GW_Ofstream& file, GW_Vector3D &v)
{
	file << v[0] << v[1] << v[2];
	return file;
}
inline
GW_Ifstream& operator>>(GW_Ifstream& file, GW_Vector3D &v)
{
	file >> v[0] >> v[1] >> v[2];
	return file;
}

/* GW_Vector2D ***********************************************/
inline
GW_Ofstream& operator<<(GW_Ofstream& file, GW_Vector2D &v)
{
	file << v[0] << v[1];
	return file;
}
inline
GW_Ifstream& operator>>(GW_Ifstream& file, GW_Vector2D &v)
{
	file >> v[0] >> v[1];
	return file;
}


/* GW_VectorND ***********************************************/
inline
GW_Ofstream& operator<<(GW_Ofstream& file, GW_VectorND &v)
{
	GW_ASSERT( GW_False );
	return file;
}
inline
GW_Ifstream& operator>>(GW_Ifstream& file, GW_VectorND &v)
{
	GW_ASSERT( GW_False );
	return file;
}



/*------------------------------------------------------------------------------*/
/** \name a list of GW_Vector2D */
/*------------------------------------------------------------------------------*/
//@{
typedef std::list<GW_Vector2D> T_Vector2DList;
typedef T_Vector2DList::iterator IT_Vector2DList;
typedef T_Vector2DList::reverse_iterator RIT_Vector2DList;
typedef T_Vector2DList::const_iterator CIT_Vector2DList;
typedef T_Vector2DList::const_reverse_iterator CRIT_Vector2DList;
//@}

/*------------------------------------------------------------------------------*/
/** \name a vector of GW_Vector2D */
/*------------------------------------------------------------------------------*/
//@{
typedef std::vector<GW_Vector2D> T_Vector2DVector;
typedef T_Vector2DVector::iterator IT_Vector2DVector;
typedef T_Vector2DVector::reverse_iterator RIT_Vector2DVector;
typedef T_Vector2DVector::const_iterator CIT_Vector2DVector;
typedef T_Vector2DVector::const_reverse_iterator CRIT_Vector2DVector;
//@}

/*------------------------------------------------------------------------------*/
/** \name a map of GW_Vector2D */
/*------------------------------------------------------------------------------*/
//@{
typedef std::map<GW_U32, GW_Vector2D> T_Vector2DMap;
typedef T_Vector2DMap::iterator IT_Vector2DMap;
typedef T_Vector2DMap::reverse_iterator RIT_Vector2DMap;
typedef T_Vector2DMap::const_iterator CIT_Vector2DMap;
typedef T_Vector2DMap::const_reverse_iterator CRIT_Vector2DMap;
//@}



} // End namespace GW




#endif // _GW_MATHSWRAPPER_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
