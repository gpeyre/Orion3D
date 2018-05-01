/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_StringTokenizer.inl
 *  \brief Inlined methods for \c OR_StringTokenizer
 *  \author Gabriel Peyré 2001-11-21
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_StringTokenizer.h"

namespace OR {

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_StringTokenizer::vPrepWorkStr
 *
 *  \param  *delimiters 
 *  \author Gabriel Peyré 2001-11-21
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_StringTokenizer::vPrepWorkStr(char *delimiters)
{
	if (!WorkStr) // WorkStr == NULL
	{
		cerr << "OR_StringTokenizer:vPrepWorkStr: strdup failed " << endl;
		exit(1);
	}
	
	CurrentPosition = TotalTokens = RemainingTokens = 0;
	
	// Now, tokenize the temporary work string variable...
	// Put 0's to tokenize.. replacing the delimiter character
	if (!delimiters) // delimiter == NULL
	{
		for (int ii = 0, jj = strlen(WorkStr); ii < jj; ii++)
		{
			if (isspace(WorkStr[ii]))  // is a white space then...
			{
				WorkStr[ii] = 0;
				TotalTokens++;
			}
		}
		ListOfDl = NULL;
	}
	else
	{
		ListOfDl = (char *) my_malloc(strlen(WorkStr));
		
		for (int ii = 0, jj = strlen(WorkStr); ii < jj; ii++)
		{
			for (int mm = 0, nn = strlen(delimiters); mm < nn; mm++)
			{
				if (WorkStr[ii] == delimiters[mm])
				{
					WorkStr[ii] = 0;
					ListOfDl[TotalTokens] = delimiters[mm];
					TotalTokens++;
				}
			}
		}
	}
	
	//if (!TotalTokens && strlen(WorkStr) > 0) // TotalTokens == 0
	//	TotalTokens = 1;
	TotalTokens++;
	
	debug_("TotalTokens", TotalTokens);
	RemainingTokens = TotalTokens;
}

} // End namespace OR


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

