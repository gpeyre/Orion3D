/*------------------------------------------------------------------------*/
/*                         OR_AlphaPilpeline.cpp                          */
/*------------------------------------------------------------------------*/
/* definition of an alpha pipeline, ie. a buffer to handle blended faces. */
/*------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_AlphaPilpeline.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_AlphaPipeline.h"

// #define OR_DEBUG_AlphaPipeline_CheckSort

namespace OR
{
	
OR_AlphaPipeline::OR_AlphaPipeline()
:	NbFaces			( 0 ),
	InputSize		( 0 ),
	InputZ			( NULL ),
	InputList		( NULL ),
	PackedListSize	( 0 ),
	PackedList		( NULL )
{
	/* NOTHING */
}

OR_AlphaPipeline::~OR_AlphaPipeline()
{
	OR_DELETEARRAY(PackedList);
}

void OR_AlphaPipeline::Reset()
{
	/* delete the list */
	NbFaces=0;
	PackedListSize=0;
	InputSize=0;
	OR_DELETEARRAY(PackedList);

	OR_DELETEARRAY(InputZ);
	OR_DELETEARRAY(InputList);
}

void OR_AlphaPipeline::SetInputSize(OR_U32 size)
{
	if (size>InputSize)
	{
		/* compute the new size of the arrays */
		OR_U32 new_size;
		if (size < InputSize+OR_ALPHA_BUFFER_INCREASE_SIZE) 
			new_size = InputSize+OR_ALPHA_BUFFER_INCREASE_SIZE;
		else 
			new_size = size;

		/* the arrays are too small : reallocate them */
		OR_AlphaBuffer_Token* InputList_tmp = new OR_AlphaBuffer_Token[new_size];;
		OR_Float *InputZ_tmp = new OR_Float[new_size];

		if (InputList!=NULL)
		{
			/* copy the existing datas */
			memcpy(InputList_tmp, InputList, InputSize*sizeof(OR_AlphaBuffer_Token));
			memcpy(InputZ_tmp, InputZ, InputSize*sizeof(OR_Float));
			OR_DELETEARRAY(InputList);
			OR_DELETEARRAY(InputZ);
		}
		InputList=InputList_tmp;
		InputZ=InputZ_tmp;
		InputSize=new_size;
	}
}

OR_RETURN_CODE OR_AlphaPipeline::Flush()
{
	OR_U32 nIndex = 0;
	OR_I32 PackedCount = 0;

	/* the kind of object we are packing */
	OR_Shadable* pRefObject = NULL;

	/* the number of this start object */
	OR_I32 nStartIndex=0;

	/** to avoid confusing with NbFaces-1 */
	if( NbFaces==0 )
		return OR_OK;

	/* get the ordered list of faces */
	OR_U32* mIndices = RadixSort_.GetIndices();

	#ifdef OR_DEBUG_AlphaPipeline_CheckSort
		/* check if the values are well sorted */
		OR_I32 nb_error=0;
		for( OR_U32 cpt2=0; cpt2<NbFaces-1; cpt2++ )
		{
			if( InputZ[mIndices[cpt2]]>InputZ[mIndices[cpt2+1]] ) 
				nb_error++;
		}
		if( nb_error>0 ) 
			fprintf(stderr, "Number of error in sort : %i\n", nb_error);
	#endif	

	while( nIndex<NbFaces )
	{
		/* take the first element as reference */
		pRefObject  = InputList[mIndices[nIndex]].GetShadable();
		nStartIndex = nIndex;
		PackedCount = 1;

		/* count the number of faces that can be packed together */
		while( (nIndex<NbFaces-1) && (InputList[mIndices[nIndex+1]].GetShadable()==pRefObject) )
		{
			/* e->Son->Element can be packed */
			PackedCount++;
			nIndex++;
		}

		/* check if the array is too small */
		this->SetPakedArraySize(3*PackedCount);

		/* add PackedCount group of 3 vertices to the list */
		for (OR_I32 i=0; i<PackedCount; i++)
		{
			PackedList[3*i]   = InputList[mIndices[nStartIndex+i]].GetVertexIndice( 0 );
			PackedList[3*i+1] = InputList[mIndices[nStartIndex+i]].GetVertexIndice( 1 );
			PackedList[3*i+2] = InputList[mIndices[nStartIndex+i]].GetVertexIndice( 2 );
		}

		/* flush the faces */
		OR_Shader*pShader = pRefObject->GetShader();
		if( pShader!=NULL )
		{
			glPushMatrix();
				pRefObject->SetFaceToProcess( PackedList, PackedCount );
				pRefObject->SetUpModelView();
				pShader->ProcessShader( *pRefObject );
			glPopMatrix();
		}

		/* re-start with a new object */
		nIndex++;
	}

	/* restart to fill the input arrays */
	NbFaces=0;

	return OR_OK;
}


OR_RETURN_CODE OR_AlphaPipeline::PerformSort()
{
	RadixSort_.Sort(InputZ, NbFaces);

	return OR_OK;
}


} // namespace OR

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