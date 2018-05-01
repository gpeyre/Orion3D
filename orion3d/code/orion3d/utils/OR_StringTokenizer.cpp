/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_StringTokenizer.cpp
 *  \brief Definition of class \c OR_StringTokenizer
 *  \author Gabriel Peyré 2001-11-21
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_StringTokenizer.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_StringTokenizer.h"


#ifndef OR_USE_INLINE
	#include "OR_StringTokenizer.inl"
#endif


#include <stdlib.h> // for exit() // Needed for MS Windows compilers
#include <ctype.h> // for isspace()
#include <string.h> // for strlen()


using namespace OR;


// Creates a new string tokenizer based on the specified
// string to be tokenized.
// calls base class cstr with string param
OR_StringTokenizer::OR_StringTokenizer(OR_String str)
	:OR_String(str.val())  // calls base class cstr
{
	// OR_String(str.val()) -- do not call here in body but call
	// in initialization stage which will avoid extra call on
	// default base-class constructor and will be faster
	// and very efficient
	debug_("in OR_StringTokenizer cstr(OR_String str)", "ok");
	CurrentPosition = TotalTokens = RemainingTokens = 0;
	DlFlag = false;
	OrigStr = strdup(str.val());
	WorkStr = strdup(str.val());
	vPrepWorkStr();
}

// Creates a new string tokenizer based on the specified
// string to be tokenized and a set of delimiters.
// The default delimiters are the space, tab, newline, and
// carriage-return characters.
// calls base class cstr with string param
OR_StringTokenizer::OR_StringTokenizer(OR_String str, OR_String delimiters)
	:OR_String(str.val())  // calls base class cstr
{
	// OR_String(str.val()) -- do not call here in body but call
	// in initialization stage which will avoid extra call on
	// default base-class constructor and will be faster
	// and very efficient
	debug_("in OR_StringTokenizer cstr(OR_String str)", "ok");
	CurrentPosition = TotalTokens = RemainingTokens = 0;
	DlFlag = false;
	OrigStr = strdup(str.val());
	WorkStr = strdup(str.val());
	vPrepWorkStr(delimiters.val());
}

// Creates a new string tokenizer based on the specified
// string to be tokenized and a set of delimiters and a
// flag (DlFlag) that indicates whether delimiters should be returned as tokens.
// calls base class cstr with string param
OR_StringTokenizer::OR_StringTokenizer(OR_String str, OR_String delimiters, OR_Bool dflag)
	:OR_String(str.val())  // calls base class cstr
{
	// OR_String(str.val()) -- do not call here in body but call
	// in initialization stage which will avoid extra call on
	// default base-class constructor and will be faster
	// and very efficient
	debug_("in OR_StringTokenizer cstr(OR_String str)", "ok");
	CurrentPosition = TotalTokens = RemainingTokens = 0;
	DlFlag = dflag;
	OrigStr = strdup(str.val());
	WorkStr = strdup(str.val());
	vPrepWorkStr(delimiters.val());
}

OR_StringTokenizer::~OR_StringTokenizer()
{
	free(OrigStr); 
	OrigStr = NULL;
	free(WorkStr); 
	WorkStr = NULL;
	free(ListOfDl); 
	ListOfDl = NULL;
}

// returns the number of remaining tokens
int OR_StringTokenizer::countTokens()
{
	return RemainingTokens;
}

OR_Bool OR_StringTokenizer::hasMoreElements()
{
	if (RemainingTokens) // RemainingTokens != 0
		return true;
	else
		return false;
}

// retunrs true if there are more tokens in the string
// being tokenized. It is identical to hasMoreElements
OR_Bool OR_StringTokenizer::hasMoreTokens()
{
	if (RemainingTokens) // RemainingTokens != 0
		return true;
	else
		return false;
}

// returns the next element in the string. It is identical
// to nextToken
OR_String OR_StringTokenizer::nextElement() // in java returns type 'Object'
{
	return nextToken();
}

// returns the next token in the string. It is identical 
// to nextElement
OR_String OR_StringTokenizer::nextToken()
{
	OR_String tmpstr;
	tmpstr = &WorkStr[CurrentPosition];
	debug_("WorkStr[CurrentPosition]", &WorkStr[CurrentPosition]);
	CurrentPosition = CurrentPosition + strlen(&WorkStr[CurrentPosition])+ 1;

	// The DlFlag indicates whether delimiters should be returned as tokens.
	if (DlFlag) // DlFlag == true
	{
		char ee[2];
		ee[0] = ListOfDl[TotalTokens - RemainingTokens];
		ee[1] = 0;
		tmpstr += ee;
	}

	RemainingTokens--;
	debug_("RemainingTokens", RemainingTokens);
	if (ListOfDl) // if ListOfDl != NULL
		debug_("ListOfDl[ii]", ListOfDl[TotalTokens - RemainingTokens] );
	return tmpstr;
}

// changes the set of delimiters to the specified string
// and then returns the next token in the string.
OR_String OR_StringTokenizer::nextToken(OR_String delimiters)
{
	strcpy(WorkStr, &OrigStr[CurrentPosition]);
	debug_("OrigStr", OrigStr);
	vPrepWorkStr(delimiters.val());
	return nextToken();
}





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