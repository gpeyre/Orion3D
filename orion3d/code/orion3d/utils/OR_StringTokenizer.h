/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_StringTokenizer.h
 *  \brief Definition of class \c OR_StringTokenizer
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __STRINGTOKENIZER_H_ALDEV_
#define __STRINGTOKENIZER_H_ALDEV_

#include "../configuration/OR_Config.h"
#include "OR_String.h"

namespace OR
{


/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_StringTokenizer
 *  \brief  a string
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	A Java like string tokenizer, using the implementation of Marc Spoorendonk
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_StringTokenizer: public OR_String
{

public:

	OR_StringTokenizer(OR_String str);
	OR_StringTokenizer(OR_String str, OR_String delimiters);
	OR_StringTokenizer(OR_String str, OR_String delimiters, OR_Bool delimAsToken);
	~OR_StringTokenizer();

	int 	countTokens();
	OR_Bool 	hasMoreElements();
	OR_Bool 	hasMoreTokens();
	OR_String 	nextElement(); // in java returns type 'Object'
	OR_String 	nextToken();
	OR_String 	nextToken(OR_String delimiters);

private:

	int		CurrentPosition; // current index on string
	int		TotalTokens;
	int		RemainingTokens;
	char *	ListOfDl; // list of delimiters
	char * 	WorkStr; // temp work string
	char * 	OrigStr; // original string passed
	OR_Bool  	DlFlag;  // delimiter flag
	inline 	void vPrepWorkStr(char *delimiters = NULL);

};

}	// namespace OR



#ifdef OR_USE_INLINE
	#include "OR_StringTokenizer.inl"
#endif


#endif // __STRINGTOKENIZER_H_ALDEV_



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