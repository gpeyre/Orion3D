/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_String.inl
 *  \brief Inlined methods for \c OR_String
 *  \author Gabriel Peyré 2001-11-21
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_String.h"


namespace OR {

	
OR_INLINE 
void OR_String::_substring(OR_I32 startIndex, OR_I32 endIndex)
{
	verifyIndex(startIndex); // startIndex can be from 0 to length()
	if (!endIndex) // endIndex == 0
		strcpy(sval, & sval[startIndex] ) ;
	else
	{
		verifyIndex(endIndex);
		if (endIndex >= startIndex)
		{
			strcpy(sval, & sval[startIndex] ) ;
			sval[endIndex -startIndex] = 0;
		}
		else
		{
			cerr << "\n\n_substring() - startIndex is greater than endIndex!!\n\n" 
				<< endl;
			exit(-1);
		}
	}
}


OR_INLINE 
void OR_String::_deleteStr(OR_I32 startIndex, OR_I32 endIndex)
{
	verifyIndex(startIndex);
	verifyIndex(endIndex);
	// For example -
	// 	deleteStr(3,3) on val = 'pokemon' returns 'poon'
	char *tmpaa = strdup(sval); // malloc here
	strcpy(& tmpaa[startIndex], & tmpaa[endIndex]);
	*this = tmpaa;
	free(tmpaa);
}



OR_INLINE 
void OR_String::_deleteCharAt(OR_I32 loc)
{
	char *tmpaa = strdup(sval); // malloc here
	strcpy(& tmpaa[loc], & tmpaa[loc+1]);
	*this = tmpaa;
	free(tmpaa);
}

OR_INLINE 
void OR_String::_reverse()
{
	// For example -
	// 		reverse() on "12345" returns "54321"
	char aa;
	OR_U32 tot_len = strlen(sval);
	OR_U32 midpoint = tot_len / 2;
	for (OR_U32 tmpjj = 0; tmpjj < midpoint; tmpjj++)
	{
		aa = sval[tmpjj];  // temporary storage var
		sval[tmpjj] = sval[tot_len - tmpjj - 1];  // swap the values
		sval[tot_len - tmpjj - 1] = aa; // swap the values
	}
}

OR_INLINE 
void OR_String::_trim()
{
	this->rtrim(true);
	this->ltrim(true);
	debug_("this->sval", this->sval);
}


OR_INLINE 
void OR_String::_ltrim()
{
	// May cause problems in my_realloc since 
	// location of bb will be destroyed !!
	char *bb = sval;

	if (bb == NULL)
		return;

	while (isspace(*bb))
		bb++;
	debug_("bb", bb);

	if (bb != NULL && bb != sval)
	{
		debug_("doing string copy", "done");
		_str_cpy(bb); // causes problems in my_realloc and bb is getting destroyed!!
	}
	else
		debug_("Not doing string copy", "done");
}

OR_INLINE 
void OR_String::_rtrim()
{
	for (OR_I32 tmpii = strlen(sval) - 1 ; tmpii >= 0; tmpii--)
	{
		if ( isspace(sval[tmpii]) )
			sval[tmpii] = '\0';
		else
			break;
	}
}


//////////////////////////////////////////////////////////
// Private functions start from here .........
//////////////////////////////////////////////////////////

OR_INLINE 
void OR_String::Common2AllCstrs() // common to all constructors
{
	// Put all the code which will be common to all constructors
	// this is for ease of maintainence.
	_pString = NULL;
	_pNumber2String = NULL;
}

OR_INLINE 
void OR_String::_allocpNumber2String() const
{
	// _pNumber2String will be deleted in destructor
	if (!_pNumber2String)  // if (_pNumber2String == NULL)
		_pNumber2String = (char *) my_malloc(NUMBER_LENGTH); // OR_Real64 nnn digits max
	else
		memset(_pNumber2String, 0, NUMBER_LENGTH);
}

OR_INLINE 
void OR_String::_allocpString() const
{
	// _pString will be deleted in destructor
	if (!_pString)  // if (_pString == NULL)
		_pString = new OR_String(this->sval); 
	else
		*_pString = this->sval;
}

// MUST use pointer-to-pointer **aa, otherwise the argument
// is NOT freed !!
/*
OR_INLINE 
void OR_String::_free_glob(OR_String **aa)
{
	debug_("called _free_glob()", "ok" );
	if (*aa != NULL)  // (*aa != NULL)
	{
		debug_("*aa is not null", "ok");
		delete *aa;
		*aa = NULL;
	}
	//else
		debug_("*aa is null", "ok");

	//if (*aa == NULL)
	debug_("*aa set to null", "ok");
}
*/


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

