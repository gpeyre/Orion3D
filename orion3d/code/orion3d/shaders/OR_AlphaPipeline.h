/*------------------------------------------------------------------------*/
/*                         OR_AlphaPilpeline.h                            */
/*------------------------------------------------------------------------*/
/* definition of an alpha pipeline, ie. a buffer to handle blended faces. */
/*------------------------------------------------------------------------*/

/** \file 
	definition of an alpha pipeline, ie. a buffer to handle blended faces.
	\author Gabriel.
**/

#ifndef _OR_ALPHAPELINE_H_
#define _OR_ALPHAPELINE_H_

#include "../configuration/OR_Config.h"
#include "OR_Shadable.h"
#include "OR_Shader.h"
#include "../utils/OR_RadixSort.h"

namespace OR
{

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_AlphaBuffer_Token
 *  \brief  the objects that are stored in the alpha pipeline.
 *  \author Gabriel Peyré 2001-11-14
 *
 *	It is composed of :
 *		- a pointer to the object it belongs to (must inherit from OR_Shadable).
 *		- the index of the 3 vertice that compose the face, relative to the vertex array of the object.
 *
 *	\example alphapipeline_test/main.cpp
 */ 
/*------------------------------------------------------------------------------*/
class OR_AlphaBuffer_Token
{
public:

	/** contstructor */
	OR_AlphaBuffer_Token(OR_Shadable* object=NULL, OR_U32 num1=-1, OR_U32 num2=-1, OR_U32 num3=-1)
	{
		pObject_         = object;
		aVertexIndex_[0] = num1;
		aVertexIndex_[1] = num2;
		aVertexIndex_[2] = num3;
	}

	/** set up the params */
	void Set(OR_Shadable* object=NULL, OR_U32 num1=-1, OR_U32 num2=-1, OR_U32 num3=-1)
	{
		pObject_         = object;
		aVertexIndex_[0] = num1;
		aVertexIndex_[1] = num2;
		aVertexIndex_[2] = num3;
	}

	/** get a vertex indice in a face */
	OR_U32 GetVertexIndice( OR_U32 i )
	{
		OR_ASSERT( i<3 );
		return aVertexIndex_[i];
	}
	/** the object this face belongs to  */
	OR_Shadable* GetShadable()
	{
		OR_ASSERT( pObject_!=NULL );
		return pObject_;
	}

private:

	/** a pointer to the object it belongs to */
	OR_Shadable* pObject_;
	/* the number of the vertices face, relative to the vertex array of the face. */
	OR_U32 aVertexIndex_[3];
};


/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_AlphaPipeline
 *  \brief  Treat transparent objects.
 *  \author Gabriel Peyré 2001-11-14
 *
 *	An alpha pileline is simply a list used to store the faces with alpha<1.
 *	At the end of the rendering process, the list is sorted by Z using a radix sort
 *	in an array, then this array is flushed to screen, passing packed lists of vertex 
 *	to the proprietary objects.
 *
 *	\example alphapipeline_test/main.cpp
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_AlphaPipeline
{
public:

	/** constructor */
	OR_AlphaPipeline();
	/** destructor */
	~OR_AlphaPipeline();

	/** reset to zero the size of the list */
	void Reset();

	/* check and set the arrays sizes ****************************************************/
	/** check if the packed array is too small, if so, realocate it */
	void SetPakedArraySize(OR_U32 size)
	{
		if (size>PackedListSize)
		{
			/* the array is too small : reallocate it */
			OR_DELETEARRAY(PackedList);
			PackedList=new OR_U32[size];
			PackedListSize=size;
		}
	}
	/** check if the input arrays are too small, if so, realocate them */
	void SetInputSize(OR_U32 size);

	/* adding faces **********************************************************************/
	/** add a face to the list (given by 3 OR_U32), creating a new entry if we are at the end of the list 
		Heavily used, to inlined ! */
	void AddFace( OR_Shadable* object, OR_U32 numface1, OR_U32 numface2, 
				  OR_U32 numface3, OR_Float z )
	{
		if (NbFaces<OR_MAX_APHA_BUFFER_SIZE)
		{
			NbFaces++;
			this->SetInputSize(NbFaces);
			InputList[NbFaces-1].Set( object, numface1, numface2, numface3 );
			InputZ[NbFaces-1]=z;
		}
		else
		{
			OR_Globals::MessageHandler()->Warning("OR_AlphaPileline::AddFace", 
							"The alpha buffer is full [size=%i].", OR_MAX_APHA_BUFFER_SIZE);
		}
	}
	/** add a face to the list (given by OR_U32*), creating new entries if we are at the end of the list
		Heavily used, to inlined ! */
	void AddFace(OR_Shadable* object, OR_U32* numface, OR_Float z)
	{
		this->AddFace(object, numface[0], numface[1], numface[2], z);
	}

	/* sorting and flushing **************************************************************/
	/** sort the faces in an array */
	OR_RETURN_CODE PerformSort();
	/** flush the faces to screen, packing them by list of same objects */
	OR_RETURN_CODE Flush();

	/* get performances ******************************************************************/
	/** Returns the total number of calls to the radix sorter. */
	OR_U32 GetNbTotalCalls() const
	{ 
		return RadixSort_.GetNbTotalCalls();
	}
	/** Returns the number of premature exits due to temporal coherence. */
	OR_U32 GetNbHits() const
	{ 
		return RadixSort_.GetNbHits();
	}

private:

	/* input datas *********************************************************************/
	/** the number of faces in the list [must be < OR_MAX_APHA_BUFFER_SIZE] */
	OR_U32 NbFaces;
	/** the size of the input list */
	OR_U32 InputSize;
	/** the list of input token (one token per face) */
	OR_AlphaBuffer_Token *InputList;
	/** the list of Z values (one value per face) <-- input */
	OR_Float *InputZ;

	/* to handle packed output *********************************************************/
	/** list of packed vertices faces numbers [3 vertices per face] */
	OR_U32* PackedList;
	/** size of the packed list */
	OR_U32 PackedListSize;

	/* sorter datas *******************************************************************/
	/** the sorting algorithm */
	OR_RadixSort RadixSort_;

};


} // namespace OR

#endif /* #ifndef _OR_ALPHAPELINE_H_ */


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_license.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////