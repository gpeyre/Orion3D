/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_String.h
 *  \brief Definition of class \c OR_String
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/

#include "../stdafx.h"

#include <stdio.h> // for FILE and sprintf()
#include <string.h> // for strcpy()
#include <ctype.h> // for isspace()
#include <stdlib.h> // for exit() // Needed for MS Windows compilers

#include "OR_String.h"


#ifndef OR_USE_INLINE
	#include "OR_String.inl"
#endif

using namespace OR;


OR_String::OR_String()
{
	sval = (char *) my_malloc(sizeof(char)* INITIAL_SIZE);
	Common2AllCstrs();
}

OR_String::OR_String(const char *bb)
{
	OR_U32 tmpii = strlen(bb);
	sval = (char *) my_malloc(sizeof(char)* tmpii);
	strncpy(sval, bb, tmpii);
	sval[tmpii] = '\0';

	//debug_("In cstr(char *bb) bb", bb);
	debug_("In cstr(char *bb) sval", sval);
	#ifdef DEBUG_STR
		//fprintf(stderr, "\nAddress of sval=%x\n", & sval);
		//fprintf(stderr, "\nAddress of this-pointer=%x\n", this);
	#endif // DEBUG_STR

	Common2AllCstrs();
}

OR_String::OR_String(const char *bb, OR_I32 start, OR_I32 slength)
{
	OR_U32 tmpii = strlen(bb);
	if (start > (OR_I32) tmpii || start < 0)
	{
		cerr << "\n\nString(char *, OR_I32, OR_I32) - start is  out of bounds!!\n\n" << endl;
		exit(1);
	}
	sval = (char *) my_malloc(sizeof(char)* slength);
	strncpy(sval, & bb[start], slength);
	sval[slength] = '\0';

	//debug_("In cstr(char *bb) bb", bb);
	debug_("In cstr(char *bb) sval", sval);
	#ifdef DEBUG_STR
		//fprintf(stderr, "\nAddress of sval=%x\n", & sval);
		//fprintf(stderr, "\nAddress of this-pointer=%x\n", this);
	#endif // DEBUG_STR

	Common2AllCstrs();
}

OR_String::OR_String(OR_I32 bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // integers nnn digits max
	sprintf(sval, "%d", bb);
	debug_("In cstr(OR_I32 bb) sval", sval);

	Common2AllCstrs();
}

OR_String::OR_String(OR_U32 bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_I32 nnn digits max
	sprintf(sval, "%lu", bb);
	debug_("In cstr(OR_U32 bb) sval", sval);

	Common2AllCstrs();
}

OR_String::OR_String(OR_Float bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Float nnn digits max
	sprintf(sval, "%f", bb);
	debug_("In cstr(OR_Float bb) sval", sval);

	Common2AllCstrs();
}

OR_String::OR_String(OR_Real64 bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Real64 nnn digits max
	sprintf(sval, "%f", bb);
	debug_("In cstr(OR_Real64 bb) sval", sval);

	Common2AllCstrs();
}

OR_String::OR_String(OR_Bool bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Float nnn digits max
	if( bb )
		sprintf(sval, "true");
	else
		sprintf(sval, "false");

	Common2AllCstrs();
}

OR_String::OR_String(const OR_Vector2D& bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Float nnn digits max
	
	sprintf(sval, "{X=%.2f, Y=%.2f}", bb.GetCoord()[X], bb.GetCoord()[Y]);

	Common2AllCstrs();
}

OR_String::OR_String(const OR_Vector3D& bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Float nnn digits max
	
	sprintf(sval, "{X=%.2f, Y=%.2f, Z=%.2f}", bb.GetCoord()[X], bb.GetCoord()[Y], bb.GetCoord()[Z]);

	Common2AllCstrs();
}

OR_String::OR_String(const OR_Vector4D& bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Float nnn digits max
	
	sprintf(sval, "{X=%.2f, Y=%.2f, Z=%.2f, W=%.2f}", bb.GetCoord()[X], bb.GetCoord()[Y], bb.GetCoord()[Z], bb.GetCoord()[W]);

	Common2AllCstrs();
}

OR_String::OR_String(const OR_Matrix4x4& bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Float nnn digits max
	
	sprintf(sval, "[%.2f, %.2f, %.2f, %.2f]\n[%.2f, %.2f, %.2f, %.2f]\n[%.2f, %.2f, %.2f, %.2f]\n[%.2f, %.2f, %.2f, %.2f]", 
			bb.GetData(0,0), bb.GetData(0,1), bb.GetData(0,2), bb.GetData(0,3),
			bb.GetData(1,0), bb.GetData(1,1), bb.GetData(1,2), bb.GetData(1,3),
			bb.GetData(2,0), bb.GetData(2,1), bb.GetData(2,2), bb.GetData(2,3),
			bb.GetData(3,0), bb.GetData(3,1), bb.GetData(3,2), bb.GetData(3,3) );

	Common2AllCstrs();
}

OR_String::OR_String(const OR_Matrix3x3& bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Float nnn digits max
	
	sprintf(sval, "[%.2f, %.2f, %.2f]\n[%.2f, %.2f, %.2f]\n[%.2f, %.2f, %.2f]", 
			bb.GetData(0,0), bb.GetData(0,1), bb.GetData(0,2),
			bb.GetData(1,0), bb.GetData(1,1), bb.GetData(1,2),
			bb.GetData(2,0), bb.GetData(2,1), bb.GetData(2,2));

	Common2AllCstrs();
}

OR_String::OR_String(const OR_Quaternion& bb)
{
	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Float nnn digits max
	
	sprintf(sval, "{W=%.2f, X=%.2f, Y=%.2f, Z=%.2f}", bb.GetW(), bb.GetX(), bb.GetY(), bb.GetZ());

	Common2AllCstrs();
}

// Copy Constructor needed by operator +
OR_String::OR_String(const OR_String & rhs)
{
	// Do a deep-copy instead of compiler's default shallow copy copy-cstr
	debug_("In copy-cstr()", "ok");
	OR_U32 tmpii = strlen(rhs.sval);
	sval = (char *) my_malloc(sizeof(char)* tmpii);
	strncpy(sval, rhs.sval, tmpii);
	sval[tmpii] = '\0';

	Common2AllCstrs();
}

// This function is for providing Java code compatibility
/*
OR_String::OR_String(StringBuffer sb)
{
	debug_("In OR_String(StringBuffer)", "ok");
	OR_U32 tmpii = strlen(sb.sval);
	sval = (char *) malloc(sizeof(char)* tmpii);
	strncpy(sval, sb.sval, tmpii);
	sval[tmpii] = '\0';

	Common2AllCstrs();
}
*/

// For use by StringBuffer class. Put a dummy
// variable for different signature.
// StringBuffer class imitates Java's StringBuffer object
OR_String::OR_String(OR_I32 size, OR_Bool dummy)
{
	sval = (char *) my_malloc(sizeof(char)* size);
	debug_("In cstr(OR_I32 size, OR_Bool dummy) sval", sval);
	#ifdef DEBUG_STR
		//fprintf(stderr, "\nAddress of sval=%x\n", & sval);
		//fprintf(stderr, "\nAddress of this-pointer=%x\n", this);
	#endif // DEBUG_STR

	Common2AllCstrs();
}

OR_String::~OR_String()  // destructor
{
	debug_("In dstr sval", sval);
	#ifdef DEBUG_STR
		//fprintf(stderr, "\nAddress of sval=%x\n", & sval);
		//fprintf(stderr, "\nAddress of this-pointer=%x\n", this);
	#endif // DEBUG_STR
	my_free(sval);
	//delete [] sval;
	sval = NULL;

	delete _pString; _pString = NULL;
	delete _pNumber2String; _pNumber2String = NULL;
}

OR_U32 OR_String::length() const
{ 
	return strlen(sval); 
}

// Imitating Java's charAt string function...
char OR_String::charAt(OR_I32 where) const
{
	verifyIndex(where);
	return (sval[where]);
}

// Imitate Java's getChars function...
// The sourceStart specifies the index of the beginning of the substring
// and sourceEnd specifies an index that is one past the end of desired
// substring. Thus the substring contains characters from sourceStart 
// through (sourceEnd - 1). The array that will receive the characters
// is specified by target. The index within target at which the substring
// will be copied is passed in targetStart. Care must be taken to assure
// that the target array is large enough to hold the number of characters
// in the specified substring.
// For e.g.  getChars(3, 6, aa, 0) on "ABCDEFGHIJK" gives aa ="DEF"
void OR_String::getChars(OR_I32 sourceStart, OR_I32 sourceEnd, char target[], OR_I32 targetStart)
{
	verifyIndex(sourceStart);
	verifyIndex(sourceEnd);

	if (sourceEnd >= sourceStart)
	{
		strncpy(& target[targetStart], & sval[sourceStart], sourceEnd - sourceStart);
		target[targetStart + (sourceEnd - sourceStart)] = 0;
	}
	else
	{
		cerr << "\n\ngetChars() - SourceEnd is greater than SourceStart!!\n\n" << endl;
		exit(1);
	}
}

// Imitate Java's getChars string function...
// Returns array of characters for the entire string
char* OR_String::toCharArray()
{
	return (sval);
}

// Imitate Java's getBytes string function...
// Returns array of characters for the entire string
char* OR_String::getBytes()
{
	return (sval);
}

// Imitate Java's equals string function...
OR_Bool OR_String::equals( const OR_String& str2 ) const  // See also == operator
{
	return ( _equalto(str2.sval));
}

// Imitate Java's equals string function...
OR_Bool OR_String::equals( const char *str2 ) const  // See also == operator
{
	return ( _equalto(str2));
}

// Imitate Java's equalsIgnoreCase string function...
OR_Bool OR_String::equalsIgnoreCase( const OR_String& str2) const
{
	OR_String  aa, bb;
	aa = this->toLowerCase();
	bb = str2.toLowerCase();
	return ( aa._equalto(bb.sval) );
}

// Imitate Java's regionMatches string function...
// The startIndex specifies the index at which the region begins within
// the invoking OR_String object. The string being compared is str2. The
// index at which comparison will start within str2 is specified by
// str2Index. The length of the substring being compared is numChars.
OR_Bool OR_String::regionMatches(OR_I32 startIndex, OR_String str2, OR_I32 str2StartIndex, OR_I32 numChars)
{
	verifyIndex(startIndex);
	str2.verifyIndex(str2StartIndex);
	if (strncmp(& this->sval[startIndex], & str2.sval[str2StartIndex], numChars) == 0)
		return true;
	else
		return false;
}

// Imitate Java's regionMatches string function...
// This is overloaded function of regionMatches
// If ignoreCase is true, the case of the characters is ignored, otherwise
// case is significant (i.e. if ignoreCase is true then ignore the 
// case and compare)
// The startIndex specifies the index at which the region begins within
// the invoking OR_String object. The string being compared is str2. The
// index at which comparison will start within str2 is specified by
// str2Index. The length of the substring being compared is numChars.
OR_Bool OR_String::regionMatches(OR_Bool ignoreCase, OR_I32 startIndex, OR_String str2, OR_I32 str2StartIndex, OR_I32 numChars)
{
	if (ignoreCase)  // if (ignoreCase == true)
	{
		verifyIndex(startIndex);
		str2.verifyIndex(str2StartIndex);
		OR_String string1, string2;
		string1 = this->toLowerCase();
		string2 = str2.toLowerCase();
		if (strncmp(& string1.sval[startIndex], & string2.sval[str2StartIndex], numChars) == 0)
			return true;
		else
			return false;
	}
	else
	{
		return regionMatches(startIndex, str2, str2StartIndex, numChars);
	}
}

// Imitate Java's toLowerCase string function...
//       OR_String  ss("sometest");
//       OR_String  egg = ss.toLowerCase();
OR_String OR_String::toLowerCase() const
{
	_allocpString();

	for (OR_I32 tmpii = strlen(_pString->sval); tmpii >= 0; tmpii--)
	{
		_pString->sval[tmpii] = tolower(_pString->sval[tmpii]);
	}
	return *_pString;  // return the object now
}

// Imitate Java's toUpperCase string function...
//       OR_String  ss("sometest");
//       OR_String  egg = ss.toUpperCase();
OR_String OR_String::toUpperCase() const
{
	_allocpString();

	for (OR_I32 tmpii = strlen(_pString->sval); tmpii >= 0; tmpii--)
	{
		_pString->sval[tmpii] = toupper(_pString->sval[tmpii]);
	}
	return *_pString;  // return the object now
}

// Imitate Java's startsWith string function...
OR_Bool OR_String::startsWith(OR_String str2)
{
	if (!strncmp(this->sval, str2.sval, strlen(str2.sval) )) // if (strncmp() == 0)
		return true;
	else
		return false;
}

// Imitate Java's startsWith string function...
// overloaded function
OR_Bool OR_String::startsWith(char *str2)
{
	OR_I32 lenstr2 = strlen(str2);
	if (!strncmp(this->sval, str2, lenstr2)) // if (strncmp() == 0)
		return true;
	else
		return false;
}

// Imitate Java's endsWith string function...
OR_Bool OR_String::endsWith(OR_String str2)
{
	// string length of str2 should be less than current string
	if (strlen(str2.sval) > strlen(sval))
		return false;

	if (!strncmp(& this->sval[strlen(sval) - strlen(str2.sval)], str2.sval, strlen(str2.sval) )) // if (strncmp() == 0)
		return true;
	else
		return false;
}

// Imitate Java's endsWith string function...
OR_Bool OR_String::endsWith(char *str2)
{
	// string length of str2 should be less than current string
	if (strlen(str2) > strlen(sval))
		return false;

	if (!strncmp(& this->sval[strlen(sval) - strlen(str2)], str2, strlen(str2) ) ) // if (strncmp() == 0)
		return true;
	else
		return false;
}

// Imitate Java's compareTo string function...
// For sorting applications, you need to know which is less than, equal to
// or greater than the next. 
// A string is less than another if it comes before the other in dictionary
// order. A string is greater than another if it comes after the other in
// dictionary order.
//  Less than zero  --> The invoking string is less than str2
//  Greater than zero  --> The invoking string is greater than str2
//  Zero  --> The two strings are equal.
OR_I32 OR_String::compareTo(OR_String str2) const
{
	OR_I32  flag = 0;
	// Compare letters in string to each letter in str2
	for (OR_I32 tmpii = 0, tmpjj = strlen(sval), tmpkk = strlen(str2.sval); tmpii < tmpjj; tmpii++)
	{
		if (tmpii > tmpkk)
			break;
		if (sval[tmpii] == str2.sval[tmpii])
			flag = 0;
		else
		if (sval[tmpii] > str2.sval[tmpii])
		{
			flag = 1;
			break;
		}
		else // if (sval[tmpii] < str2.sval[tmpii])
		{
			flag = -1;
			break;
		}
	}
	return flag;
}

// Imitate Java's compareTo string function...
// Overloaded function of compareTo
OR_I32 OR_String::compareTo(char *str2) const
{
	OR_I32  flag = 0;
	// Compare letters in string to each letter in str2
	for (OR_I32 tmpii = 0, tmpjj = strlen(sval), tmpkk = strlen(str2); tmpii < tmpjj; tmpii++)
	{
		if (tmpii > tmpkk)
			break;
		if (sval[tmpii] == str2[tmpii])
			flag = 0;
		else
		if (sval[tmpii] > str2[tmpii])
		{
			flag = 1;
			break;
		}
		else // if (sval[tmpii] < str2[tmpii])
		{
			flag = -1;
			break;
		}
	}
	return flag;
}

// Imitate Java's compareToIgnoreCase string function...
OR_I32 OR_String::compareToIgnoreCase(OR_String str2) const
{
	OR_String tmpaa = this->toLowerCase(),
	tmpbb = str2.toLowerCase();

	return tmpaa.compareTo(tmpbb);
}

// Imitate Java's compareToIgnoreCase string function...
// Overloaded function
OR_I32 OR_String::compareToIgnoreCase(char *str2) const
{
	OR_String tmpaa = this->toLowerCase(),
	tmpcc(str2), tmpbb = tmpcc.toLowerCase();

	return tmpaa.compareTo(tmpbb);
}

// Imitate Java's indexOf string function...
// Searches for the first occurence of a character or string
// Return the index at which the character or substring was
// found, or -1 on failure.
OR_I32 OR_String::indexOf(char ch, OR_I32 startIndex)
{
	verifyIndex(startIndex);
	OR_I32 ii = startIndex;
	for (; ii < (OR_I32) strlen(sval); ii++)
	{
		if (sval[ii] == ch)
			break;
	}
	if (ii == (OR_I32) strlen(sval))
		return -1;
	return ii;
}

// Imitate Java's indexOf string function...
// Overloaded function
OR_I32 OR_String::indexOf(char *str2, OR_I32 startIndex)
{
	verifyIndex(startIndex);
	char * tok;
	OR_I32 res = -1;

	if ( !isNull() )
	{
		tok = strstr(sval + startIndex, str2);
		if (tok == NULL)
			res = -1;
		else
			res = (OR_I32) (tok - sval);
	}
	return res;
}

// Imitate Java's indexOf string function...
// Overloaded function
OR_I32 OR_String::indexOf(OR_String str2, OR_I32 startIndex)
{
	verifyIndex(startIndex);
	char * tok;
	OR_I32 res = -1;

	if ( !isNull() )
	{
		tok = strstr(sval + startIndex, str2.sval);
		if (tok == NULL)
			res = -1;
		else
			res = (OR_I32) (tok - sval);
	}
	return res;
}

// Imitate Java's lastIndexOf string function...
// Searches for the last occurence of a character or string
// Return the index at which the character or substring was
// found, or -1 on failure.
OR_I32 OR_String::lastIndexOf(char ch, OR_I32 startIndex)
{
	verifyIndex(startIndex);
	OR_I32 ii;

	// Begin search from the last character of string
	if (!startIndex) // if (startIndex == 0)
		ii = strlen(sval);
	else
		ii = startIndex;
	for (; ii > -1; ii--)
	{
		if (sval[ii] == ch)
			break;
	}
	if (!ii && sval[ii] != ch) // if (ii == 0)
		return -1;
	return ii;
}

// Imitate Java's lastIndexOf string function...
// Overloaded function
OR_I32 OR_String::lastIndexOf(char *str2, OR_I32 startIndex)
{
	verifyIndex(startIndex);
    char *tok = NULL;
    OR_I32 res = -1;
 
    //register char *tmpaa = strdup(sval); do not use register
    char *tmpaa = strdup(sval);  // malloc here
    if (!tmpaa) // tmpaa == NULL
    {
        cerr << "\n\nMemory alloc failed in strdup in lastIndexOf()\n\n" << endl;
        exit(-1);
    }
 
    if (!startIndex) // if (startIndex == 0)
        startIndex = strlen(sval);
    else
        tmpaa[startIndex+1] = 0;
 
    for (OR_I32 ii = 0; ii <= startIndex; ii++)
    {
        tok = strstr(& tmpaa[ii], str2);
        if (tok == NULL)
            break;
        else
        {
            res = (OR_I32) (tok - tmpaa);
			debug_("res", res);
            ii = res; // jump to where it matched (+1 in for loop)
        }
    }
    free(tmpaa);
	debug_("res", res);
	debug_("indexOf", & sval[res]);

	return res;
}

// Imitate Java's lastIndexOf string function...
// Overloaded function
OR_I32 OR_String::lastIndexOf(OR_String str2, OR_I32 startIndex)
{
	verifyIndex(startIndex);
    char *tok = NULL;
    OR_I32 res = -1;
 
    //register char *tmpaa = strdup(sval); do not use register
    char *tmpaa = strdup(sval);  // malloc here
    if (!tmpaa) // tmpaa == NULL
    {
        cerr << "\n\nMemory alloc failed in strdup in lastIndexOf()\n\n" << endl;
        exit(-1);
    }
 
    if (!startIndex) // if (startIndex == 0)
        startIndex = strlen(sval);
    else
        tmpaa[startIndex+1] = 0;
 
    for (OR_I32 ii = 0; ii <= startIndex; ii++)
    {
        tok = strstr(& tmpaa[ii], str2.sval);
        if (tok == NULL)
            break;
        else
        {
            res = (OR_I32) (tok - tmpaa);
			debug_("res", res);
            ii = res; // jump to where it matched (+1 in for loop)
        }
    }
    free(tmpaa);
	debug_("res", res);
	debug_("indexOf", & sval[res]);

	return res;
}

// Imitate Java's substring string function...
// The startIndex specifies the beginning index, and endIndex specifies
// the stopping point. The string returned contains all the characters
// from the beginning index, up to, but not including, the ending index.
OR_String OR_String::substring(OR_I32 startIndex, OR_I32 endIndex)
{
	OR_String tmpstr = OR_String(sval);
	tmpstr._substring(startIndex, endIndex);
	return tmpstr;
}

// Imitate Java's concat string function...
OR_String OR_String::concat(OR_String str2)
{
	//return (*this + str2);
	this->_str_cat(str2.sval);
	return *this;
}

// Imitate Java's concat string function...
// overloaded function
OR_String OR_String::concat(char *str2)
{
	//return (*this + str2);
	this->_str_cat(str2);
	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_String::concat
 *
 *  \param  c char to add to the string
 *  \return the new string.
 *  \author Gabriel Peyré 2001-11-21
 */ 
/*------------------------------------------------------------------------------*/
OR_String OR_String::concat(char c)
{
	(*this) += OR_String(&c, 0, 1);
	return *this;
}


OR_String OR_String::concat(OR_I32 bb)
{
	this->_str_cat(number2string(bb));
	return *this;
}

OR_String OR_String::concat(OR_U32 bb)
{
	this->_str_cat(number2string(bb));
	return *this;
}

OR_String OR_String::concat(OR_Float bb)
{
	this->_str_cat(number2string((OR_Real64)bb));
	return *this;
}

OR_String OR_String::concat(OR_Real64 bb)
{
	this->_str_cat(number2string(bb));
	return *this;
}

// Imitate Java's replace string function...
// Replace all occurences of string 'original' with 
// 'replacement' in 'sval'
OR_String OR_String::replace(char original, char replacement)
{
	// For example -
	// 		replace('A', 'B') on sval = "some AAA and AAACC"
	// 		returns sval = "some BBB and BBBCC"
	//OR_String *tmpstr = new OR_String(sval); Use default copy cstr
	OR_String tmpstr(sval);
	for (OR_I32 ii = 0, len = strlen(sval); ii < len; ii++)
	{
		if (tmpstr.sval[ii] == original)
			tmpstr.sval[ii] = replacement;
	}
	return tmpstr; // this will use copy constructor to make a default copy
}

// Imitate Java's replace string function...
// overloaded function
// Replace all occurences of string 'original' with
// 'replacement' in 'sval'
OR_String OR_String::replace(char *original, char *replacement)
{
    char *tok = NULL, *buffer;
    char *haystack = strdup(sval);
    OR_I32 lenrepl = strlen(replacement);
    OR_I32 lenorig = strlen(original);     // ADDED

    // Allocate space for buffer
    { // local scope
        OR_I32 matches = 0;
        for (OR_I32 pos = 0; ;pos++) { // count the number of matches
            tok = strstr(& haystack[pos], original);
            if (tok == NULL)
                break;
            else {
                // pos = one position after previous match
                pos += (OR_I32) (tok -haystack);
                matches++;
            }
        }

		if (!matches) {// matches == 0, no match of 'original' found
			if (haystack != NULL)
				free(haystack);
			return (OR_String(sval)); // return original string
		}

        //matches = strlen(sval) + (matches * lenrepl) + 20; CHANGED
        matches = strlen(sval) + (matches * (lenrepl-lenorig)) + 1;
        debug_("sizeof new buffer", matches);
        buffer = (char *) malloc(matches);
        memset(buffer, 0, matches);
    }

    for (OR_I32 pos = -1; ;) {
        debug_("haystack", haystack);
        tok = strstr(haystack, original);
        if (tok == NULL) {
            strcat(buffer, haystack);
            break;
        }
        else {
            pos = (OR_I32) (tok - haystack);
            strncat(buffer, haystack, pos);
            strcat(buffer, replacement);
            //buffer[strlen(buffer)] = 0;
            debug_("pos", pos );
            debug_("buffer", buffer );
            //strcpy(haystack, &haystack[pos+lenrepl]); CHANGED
            strcpy(haystack, &haystack[pos+lenorig]);
        }
    }
    debug_("buffer", buffer );
    free(haystack);
    OR_String tmpstr(buffer);
    free(buffer);
    return tmpstr;
}

/*
another method of doing replace function but slow..
OR_String OR_String::replace(char *original, char *replacement)
{
	// For example -
	// 		replace("AAA", "BB") on sval = "some AAA and AAACC"
	// 		returns sval = "some BB and BBCC"
	OR_String bb(this->before(original).sval);
	if (strlen(bb.sval) == 0)
		return OR_String(sval); // return original string
	bb += replacement;

	OR_String tmpaa(this->sval), cc, dd;
	for (;;)
	{
		cc = tmpaa.after(original).sval;
		debug_("cc", cc.sval );
		if (!strlen(cc.sval)) // if (strlen(cc.sval) == 0)
			break;

		dd = cc.before(original).sval;
		if (strlen(dd.sval) == 0)
		{
			bb += cc;
			break;
		}
		else
		{
			bb += dd;
			bb += replacement;
		}
		tmpaa = cc;
	}
	debug_("bb.sval", bb.sval );
	return bb;
}
*/

// Imitate Java's replace function -  StringBuffer 
OR_String OR_String::replace (OR_I32 startIndex, OR_I32 endIndex, OR_String str)
{
	verifyIndex(startIndex);
	verifyIndex(endIndex);
	OR_I32 tmpjj = strlen(str.sval);
	if (tmpjj == 0)
		return *this;
	OR_I32 tmpii = endIndex-startIndex-1;
	if (tmpjj < tmpii) // length of str is less than specified indexes.
		tmpii = tmpjj;
	debug_("sval", sval);
	debug_("str.sval", str.sval);
	strncpy(& sval[startIndex], str.sval, tmpii);
	sval[startIndex+tmpii] = 0;
	debug_("sval", sval);
	return *this;
}

// Imitate Java's trim string function...
OR_String OR_String::trim()
{
	//OR_String *tmpstr = new OR_String(sval);
	OR_String tmpstr(sval);
	tmpstr._trim();
	debug_("tmpstr.sval", tmpstr.sval);
	return tmpstr; // this will use copy constructor to make a default copy
}

// Imitate Java's insert string function...
OR_String OR_String::insert(OR_I32 index, OR_String str2)
{
	OR_String tmpstr(this->insert(str2.sval, index).sval);
	debug_("tmpstr.sval", tmpstr.sval);
	return tmpstr;
}

// Imitate Java's insert string function...
OR_String OR_String::insert(OR_I32 index, char ch)
{
	char aa[2];
	aa[0] = ch;
	aa[1] = 0;
	OR_String tmpstr(this->insert(aa, index).sval);
	debug_("tmpstr.sval", tmpstr.sval);
	return tmpstr;
}

// Imitate Java's deleteCharAt string function...
OR_String OR_String::deleteCharAt(OR_I32 loc)
{
	OR_String tmpstr(sval);
	tmpstr._deleteCharAt(loc);
	return tmpstr;
}

// Imitate Java's delete string function...
// Note: -->Java name is "delete()", cannot use reserved name delete() in C++
// The startIndex specifies the index of the first character to remove,
// and endIndex specifies an index one past the last character to remove.
// Thus, the substring deleted runs from startIndex to (endIndex - 1)
OR_String OR_String::deleteStr(OR_I32 startIndex, OR_I32 endIndex)
{
	// For example -
	// 	deleteStr(3,3) on val = 'pokemon' returns 'poon'
	OR_String tmpstr(sval);
	tmpstr._deleteStr(startIndex, endIndex);
	return tmpstr;
}

// Imitate Java's reverse string function...
OR_String OR_String::reverse()
{
	// For example -
	// 		reverse() on "12345" returns "54321"
	OR_String tmpstr(sval);
	tmpstr._reverse();
	return tmpstr;
}

// Imitate Java's valueOf string function...
OR_String OR_String::valueOf(char chars[], OR_I32 startIndex, OR_I32 numChars)
{
	verifyIndex(startIndex);
	OR_I32 ii = strlen(chars);
	if (startIndex > ii)
	{
		cerr << "\n\nvalueOf() - startIndex greater than string length of"
			<< "string passed\n\n" << endl;
		exit(0);
	}
	if ( (numChars+startIndex) > ii)
	{
		cerr << "\n\nvalueOf() - numChars exceeds the string length of"
			<< "string passed\n\n" << endl;
		exit(0);
	}

	char *aa = strdup(chars);
	aa[startIndex + numChars] = 0;
	OR_String tmpstr(& aa[startIndex]);
	free(aa);
	return tmpstr;
}

// Imitate Java's ensureCapacity string function...
// For use by StringBuffer class. 
// Pre-allocate room for certain number of chars, useful
// if you know in advance that you will be appending a large
// number of small strings to StringBuffer
void OR_String::ensureCapacity(OR_I32 capacity)
{
	sval = (char *) my_realloc(sval, capacity);
	sval[0] = '\0';
	debug_("In ensureCapacity(OR_I32 capacity) sval", sval);
}

// Imitate Java's setLength string function...
// For use by StringBuffer class. 
void OR_String::setLength(OR_I32 len)
{
	sval = (char *) my_realloc(sval, len);
	sval[0] = '\0';
	debug_("In setLength(OR_I32 len) sval", sval);
}

// Imitate Java's setCharAt function -  StringBuffer 
void OR_String::setCharAt(OR_I32 where, char ch)
{
	verifyIndex(where);
	sval[where] = ch;
	debug_("in setCharAt()", "ok");
}

// ---- End of Java like OR_String object functions -----

// overloaded function - directly changes object
// Variable dummy will give different signature to function
void OR_String::substring(OR_I32 startIndex, OR_I32 endIndex, OR_Bool dummy)
{
	this->_substring(startIndex, endIndex);
}

// overloaded function - directly changes object
OR_String OR_String::deleteStr(OR_I32 startIndex, OR_I32 endIndex, OR_Bool dummy)
{
	this->_deleteStr(startIndex, endIndex);
	return *this;
}

// overloaded function - directly changes object
OR_String OR_String::deleteCharAt(OR_I32 loc, OR_Bool dummy)
{
	this->_deleteCharAt(loc);
	return *this;
}

// Returns string before regx. Matches first occurence of regx
OR_String OR_String::at(char *regx)
{
	char *tok = NULL;
	tok = strstr(sval, regx);
	if (tok == NULL)
		return(OR_String(""));
	else
	{
		OR_I32 res = (OR_I32) (tok - sval);
		char *lefttok = strdup(sval);
		memset(lefttok, 0, strlen(sval));
		strcpy(lefttok, & sval[res]);
		OR_String tmpstr(lefttok);
		free(lefttok);
		return(tmpstr);
	}
}

// Returns string before regx. Matches first occurence of regx
OR_String OR_String::before(char *regx)
{
	char *tok = NULL;
	tok = strstr(sval, regx);
	if (tok == NULL)
		return(OR_String(""));
	else
	{
		OR_I32 res = (OR_I32) (tok - sval);
		char *lefttok = strdup(sval);
		lefttok[res] = 0;
		OR_String tmpstr(lefttok);
		free(lefttok);
		return(tmpstr);
	}
}

// Returns string after regx. Matches first occurence of regx
OR_String OR_String::after(char *regx)
{
	char *tok = NULL;
	tok = strstr(sval, regx);
	if (tok == NULL)
		return(OR_String(""));
	else
	{
		OR_I32 res = (OR_I32) (tok - sval);
		char *lefttok = strdup(sval);
		memset(lefttok, 0, strlen(sval));
		strcpy(lefttok, & sval[res + strlen(regx)]);
		OR_String tmpstr(lefttok);
		free(lefttok);
		return(tmpstr);
	}
}

// Explodes the string and returns the list in 
// the list-head pointer explodeH
// See also token()
void OR_String::explode(char *separator)
{
	/*
	char *aa = NULL, *bb = NULL;
	aa = (char *) my_malloc(strlen(sval));
	for (bb = strtok(aa, separator); bb != NULL; bb = strtok(NULL, separator) )
	{
		OR_String *tmp = new OR_String(bb);
		OR_String::explodeH.insert(OR_String::explodeH.end(), *tmp);
	}
	my_free(aa);

	list<OR_String>::iterator iter1; // see file include/g++/stl_list.h
	debug_("Before checking explode..", "ok");
	if (OR_String::explodeH.empty() == true )
	{
		debug_("List is empty!!", "ok");
	}

	for (iter1 = OR_String::explodeH.begin(); iter1 != OR_String::explodeH.end(); iter1++)
	{
		if (iter1 == NULL)
		{
			debug_("Iterator iter1 is NULL!!", "ok" );
			break;
		}
		debug_("(*iter1).sval", (*iter1).sval);
	}
	*/
}

// Overloaded function of explode(). This will return an
// array of strings and total number in strcount reference 
// variable.
// See also token()
OR_String *OR_String::explode(OR_I32 & strcount, char separator)
{
	OR_String aa(sval);
	aa.trim(true);
	strcount = 0;
	for (OR_I32 ii = 0, jj = strlen(aa.sval); ii < jj; ii++)
	{
		if (aa.sval[ii] == separator)
			strcount++;
	}

	OR_String *tmpstr = new OR_String[strcount+1];
	if (!strcount) // strcount == 0
		tmpstr[0] = aa.sval;
	else
	{
		for (OR_I32 ii = 0; ii <= strcount; ii++)
			tmpstr[ii] = aa.token(separator);
	}
	return tmpstr;
}

// Implodes the strings in the list-head 
// pointer explodeH and returns the OR_String class 
void OR_String::implode(char *glue)
{
}

// Joins the strings in the list-head 
// pointer explodeH and returns the OR_String class 
void OR_String::join(char *glue)
{
	implode(glue);
}

// Repeat the input string n times
OR_String OR_String::repeat(char *input, OR_U32 multiplier)
{
	// For example -
	// repeat("k", 4) returns "kkkk"
	if (!input) // input == NULL
	{
		return (OR_String(""));
	}

	char *aa = (char *) my_malloc(strlen(input) * multiplier);
	for (OR_U32 tmpii = 0; tmpii < multiplier; tmpii++)
	{
		strcat(aa, input);
	}
	OR_String tmpstr(aa);
	my_free(aa);
	return tmpstr;
}

// Reverse the string
// Overloaded version of reverse(). This will directly change the object.
void OR_String::reverse(OR_Bool dummy)
{
	this->_reverse();
}

// Translate certain chars
// For e.g ("abcd", "ABC") translates all occurences of each 
// character in 'from' to corresponding character in 'to'
OR_String OR_String::tr(char *from, char *to)
{
	OR_I32 lenfrom = strlen(from), lento = strlen(to);
	if (lento > lenfrom)
		lento = lenfrom; // set it to least
	else
	if (lento < lenfrom)
		lenfrom = lento; // set it to least 
	debug_("lento", lento);

	//register char *aa = strdup(sval); do not use register
	char *aa = strdup(sval);
	for (OR_I32 ii = 0, jj = strlen(sval); ii < jj; ii++) // for every char in val
	{
		for (OR_I32 kk = 0; kk < lento; kk++) // for every char in "from" string
		{
			if (aa[ii] == from[kk])
				aa[ii] = to[kk];
		}
	}
	OR_String tmpstr(aa);
	free(aa);
	return tmpstr;
}

// Center the text
OR_String OR_String::center(OR_I32 padlength, char padchar)
{
	// For example -
	// 		center(10, '*') on sval="aa" returns "****aa****"
	// 		center(10) on sval="aa" returns "    aa    "
	// The result is a string of 'padlength' characters with sval centered in it.
	OR_I32 tmpii = sizeof(char) * (padlength + strlen(sval) + 10);
	char *aa = (char *) malloc(tmpii);
	memset(aa, 0, tmpii);

	OR_I32 jj, kk;

	for (jj = 0, kk = (OR_I32) padlength/2; jj < kk; jj++)
	{
		aa[jj] = padchar;
	}
	strcat(aa, sval);
	for (jj = strlen(aa), kk = jj + (OR_I32) padlength/2; jj < kk; jj++)
	{
		aa[jj] = padchar;
	}
	OR_String tmpstr(aa);
	free(aa);
	return tmpstr;
}

// Formats the original string by placing <number> of <padchar> characters
// between each set of blank-delimited words. Leading and Trailing blanks
// are always removed. If <number> is omitted or is 0, then all spaces are
// in the string are removed. The default number is 0 and 
// default padchar ' '
OR_String OR_String::space(OR_I32 number, char padchar)
{
	// For example -
	// 		space(3) on sval = "I do not know" 
	// 				will return "I   do   not   know"
	// 		space(1, '_') on sval = "A deep black space"  
	// 				will return "A_deep_black_space"
	// 		space() on sval = "I   know     this"
	// 				will return "Iknowthis"

	debug_("this->sval", this->sval );
	OR_String tmpstr = this->trim().sval;
	debug_("tmpstr.sval", tmpstr.sval );

	// count spaces
	OR_I32 spacecount = 0, ii, jj;
	for (ii = 0, jj = strlen(tmpstr.sval); ii < jj; ii++)
	{
		if (tmpstr.sval[ii] == ' ')
			spacecount++;
	}
	debug_("spacecount", spacecount);

	char ee[2];
	ee[0] = padchar;
	ee[1] = 0;
	OR_String bb = tmpstr.repeat(ee, spacecount);

	OR_I32 tmpii = sizeof(char) * (strlen(tmpstr.sval) + (number * spacecount) + 20);
	char *aa = (char *) malloc(tmpii);
	memset(aa, 0, tmpii);
	for (ii = 0, jj = strlen(tmpstr.sval); ii < jj; ii++)
	{
		if (tmpstr.sval[ii] == ' ')
			strcat(aa, bb.sval);
		else
		{
			ee[0] = sval[ii];
			strcat(aa, ee);
		}
	}
	tmpstr = aa;
	free(aa);
	return tmpstr;
}

// The result is string comprised of all characters between 
// and including <start> and <end>
OR_String OR_String::xrange(char start, char end)
{
	// For example -
	// 	xrange('a', 'j') returns val = "abcdefghij"
	// 	xrange(1, 8) returns val = "12345678"

	if (end < start)
	{
		cerr << "\nThe 'end' character is less than 'start' !!" << endl;
		return OR_String("");
	}

	// Note: The 'end' is greater than 'start'!! And add +1
	OR_I32 tmpii = sizeof(char) * (end - start + 11); 
	char *aa = (char *) malloc(tmpii);
	memset(aa, 0, tmpii);
	debug_("xrange tmpii", tmpii);
	for (OR_I32 ii = start, jj = 0; ii <= end; ii++, jj++)
	{
		aa[jj] = ii;
		debug_("xrange aa[jj]", aa[jj] );
	}
	OR_String tmpstr(aa);
	free(aa);
	return tmpstr;
}

// Removes any characters contained in <list>. The default character
// for <list> is a blank ' '
OR_String OR_String::compress(char *list_)
{
	// For example -
	// 	compress("$,%") on sval = "$1,934" returns "1934"
	// 	compress() on sval = "call me alavoor vasudevan" returns "callmealavoorvasudevan"
	OR_I32 lenlist = strlen(list_);
	//register char *aa = strdup(sval); do not use register
	char *aa = strdup(sval);
	for (OR_I32 ii = 0, jj = strlen(sval); ii < jj; ii++) // for every char in sval
	{
		for (OR_I32 kk = 0; kk < lenlist; kk++) // for every char in "from" string
		{
			if (aa[ii] == list_[kk])
			{
				strcpy(& aa[ii], & aa[ii+1]);
			}
		}
	}
	OR_String tmpstr(aa);
	free(aa);
	return tmpstr;
}

// The <newstr> is inserted into sval beginning at <start>. The <newstr> will
// be padded or truncated to <lengthstr> characters. The default <lengthstr> is 
// string length of newstr
OR_String OR_String::insert(char *newstr, OR_I32 start, OR_I32 lengthstr, char padchar)
{
	// For example -
	// 	insert("something new", 4, 20, '*') on sval = "old thing" 
	// 		returns "old something new*******thing"
	OR_I32 tmplen = sizeof(char) * ( start + strlen(newstr) + lengthstr + strlen(sval) + 10 );
	char *tmpaa = (char *) malloc (tmplen);
	memset(tmpaa, 0, tmplen);
	if (!start) // start == 0
	{
		strcpy(tmpaa, newstr);
		strcat(tmpaa, this->sval);
	}
	else
	{
		strncpy(tmpaa, this->sval, start);
		strcat(tmpaa, newstr);
		if (strlen(this->sval) > (OR_U32) start)
			strcat(tmpaa, & this->sval[start]);
	}

	OR_String tmpstr(tmpaa);
	free(tmpaa);
	return tmpstr;
}

// overloaded insert function... Directly changes the object
OR_String OR_String::insert(OR_I32 index, OR_String str2, OR_Bool dummy)
{
	//_allocpString();
	this->insert((char*) str2.sval, index);
	//*_pString =  this->insert(str2.sval, index).sval;
	//return *_pString;  // return the object now
	//*this =  this->insert(str2.sval, index).sval;
	//debug_("tmpstr.sval", tmpstr.sval);
	return *this;
}

// overloaded insert function... Directly changes the object
OR_String OR_String::insert(OR_I32 index, char ch, OR_Bool dummy)
{
	char aa[2];
	aa[0] = ch;
	aa[1] = 0;
	*this = this->insert(aa, index).sval;
	//debug_("tmpstr.sval", tmpstr.sval);
	return *this;
}

// The result is string of <length> chars madeup of leftmost chars in sval.
// Quick way to left justify a string.
OR_String OR_String::left(OR_I32 slength, char padchar)
{
	// For example -
	// 	left(15) on sval = "Wig"       returns "Wig            "
	// 	left(4) on  sval = "Wighat"    returns "Wigh"
	// 	left() on   sval = "   Wighat" returns "Wighat   "
	if (!slength) // slength == 0
		slength = strlen(sval);
	debug_("left() slength", slength);

	OR_I32 tmpii = slength + 20;
	char *aa = (char *) malloc(tmpii);
	memset(aa, 0, tmpii);
	debug_("this->ltrim().sval ", this->ltrim().sval);
	strcpy(aa, this->ltrim().sval);
	debug_("left() aa", aa );

	OR_I32 currlen = strlen(aa);
	if (currlen < slength)  
	{
		// pad the string now
		char ee[2];
		ee[0] = padchar;
		ee[1] = 0;
		strcat(aa, this->repeat(ee, (OR_U32) (slength-currlen) ).sval);
	}
	else
	{
		aa[slength] = 0;
	}

	debug_("left() aa", aa );
	OR_String tmpstr(aa);
	free(aa);
	return tmpstr;
}

// The result is string of <length> chars madeup of rightmost chars in sval.
// Quick way to right justify a string.
OR_String OR_String::right(OR_I32 slength, char padchar)
{
	// For example -
	// 	right(10) on sval = "never to saying   " returns " to saying"
	// 	right(4) on  sval = "Wighat"             returns "ghat"
	// 	right(8) on  sval = "4.50"               returns "    4.50"
	// 	right() on   sval = "  4.50     "        returns "       4.50"

	if (!slength) // slength == 0
		slength = strlen(sval);
	debug_("right() slength", slength);

	OR_I32 tmpii = slength + 20;
	char *aa = (char *) malloc(tmpii);
	memset(aa, 0, tmpii);

	OR_I32 currlen = strlen(this->rtrim().sval);
	debug_("right() currlen", currlen );
	if (currlen < slength)  
	{
		// pad the string now
		char ee[2];
		ee[0] = padchar;
		ee[1] = 0;
		strcpy(aa, this->repeat(ee, (OR_U32) (slength-currlen) ).sval);
		strcat(aa, this->rtrim().sval);
		debug_("right() aa", aa );
	}
	else
	{
		strcpy(aa, this->rtrim().sval);
		strcpy(aa, & aa[currlen-slength]);
		aa[slength] = 0;
	}

	debug_("right() aa", aa );
	OR_String tmpstr(aa);
	free(aa);
	return tmpstr;
}

// The <newstr> is overlayed into sval beginning at <start>. The <newstr> will
// be padded or truncated to <length> characters. The default <length> is 
// string length of newstr
OR_String OR_String::overlay(char *newstr, OR_I32 start, OR_I32 slength, char padchar)
{
	// For example -
	// 	overlay("12345678", 4, 10, '*') on sval = "oldthing is very bad"
	// 		returns "old12345678**ery bad"
	// 	overlay("12345678", 4, 5, '*') on sval = "oldthing is very bad"
	// 		returns "old12345ery bad"
	OR_I32 len_newstr = strlen(newstr);
	if (!slength) // slength == 0
		slength = len_newstr;
	char *aa = (char *) malloc(slength + len_newstr + 10);
	aa[0] = 0;
	char ee[2];
	ee[0] = padchar;
	ee[1] = 0;
	if (len_newstr < slength)
	{
		// pad it now
		strcpy(aa, newstr);
		strcat(aa, this->repeat(ee, (slength-len_newstr)).sval );
	}
	else
	{
		strcpy(aa, newstr);
		aa[slength] = 0;
	}

	// Now overlay the string.
	OR_String tmpstr(sval);

	debug_("tmpstr.sval", tmpstr.sval);
	for (OR_I32 ii=start, jj=strlen(tmpstr.sval), kk=start+slength, mm=0; 
				ii < jj; ii++, mm++)
	{
		if (ii == kk)
			break;
		if (mm == slength)
			break;
		tmpstr.sval[ii] = aa[mm];
	}
	free(aa);
	debug_("tmpstr.sval", tmpstr.sval);
	return tmpstr;
}

// If string is literally equal to .. or not equal to
// If type is false than it is ==
OR_Bool OR_String::_equalto(const OR_String & rhs, OR_Bool type) const
{
	if (type == false) // test for ==
	{
		if (strlen(rhs.sval) == strlen(sval))
		{
			if (!strncmp(rhs.sval, sval, strlen(sval))) //  == 0
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else // test for !=
	{
		if (strlen(rhs.sval) != strlen(sval))
		{
			if (!strncmp(rhs.sval, sval, strlen(sval))) //  == 0
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

// If string is literally equal to .. or not equal to
// If type is false than it is ==
OR_Bool OR_String::_equalto(const char *rhs, OR_Bool type) const
{
	if (type == false) // test for ==
	{
		if (strlen(rhs) == strlen(sval))
		{
			if (!strncmp(rhs, sval, strlen(sval))) //  == 0
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else // test for !=
	{
		if (strlen(rhs) != strlen(sval))
		{
			if (!strncmp(rhs, sval, strlen(sval))) //  == 0
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

// Synonym function is vacuum()
void OR_String::clear()
{
	sval = (char *) my_realloc(sval, 10);
	sval[0] = '\0';
}

// Remove trailing ALL given character 'ch' - see also chop()
// For example : 
// 	sval = "abcdef\n\n\n" then chopall() = "abcdef"
// 	sval = "abcdefffff" then chopall('f') = "abcde"
void OR_String::chopall(char ch)
{
	OR_U32 tmpii = strlen(sval) - 1 ;
	for (; tmpii >= 0; tmpii--)
	{
		if (sval[tmpii] == ch)
			sval[tmpii] = 0;
		else
			break;
	}
}

// Remove trailing character - see also chopall()
// chop() is often used to remove trailing newline character
void OR_String::chop()
{
	sval[strlen(sval)-1] = 0;
}

// Overloaded version of trim(). This will directly change the object.
void OR_String::trim(OR_Bool dummy)
{
	this->_trim();
}

// Overloaded version of ltrim(). This will directly change the object.
void OR_String::ltrim(OR_Bool dummy)
{
	this->_ltrim();
}


OR_String OR_String::ltrim()
{
	OR_String tmpstr(sval);
	tmpstr._ltrim();
	return tmpstr;
}

// Overloaded version of rtrim(). This will directly change the object.
void OR_String::rtrim(OR_Bool dummy)
{
	this->_rtrim();
}


OR_String OR_String::rtrim()
{
	OR_String tmpstr(sval);
	tmpstr._rtrim();
	return tmpstr;
}

// Use for rounding off fractions digits of floats
// Rounds-off floats with given precision and then
// stores the result into OR_String's sval field
// Also returns the result as a char *
void OR_String::roundf(OR_Float input_val, short precision)
{
	debug_("In roundf", "ok");

	// As per "C" compiler on 32-bit CPUs OR_Float is at least 6 
	// decimal digits of precision.
	// Double and, OR_I32 OR_Real64 is at least 10 decimal digits
	// On 64-bit machines accuracy will be much higher
	// 		fprintf(stderr, "\n ff:%.6f", ff);    	// f OR_Float
	// 		fprintf(stderr, "\n dd:%.26lf", dd);  	// lf OR_Real64
	// 		fprintf(stderr, "\n ldd:%.26Lf", ldd); 	// Lf OR_I32 OR_Real64
	_roundno(0.0, input_val, precision, false);

	/*
	OR_Float	integ_flt, deci_flt;
	OR_Real64	dbl_flt;

	// get the integral and decimal parts of the OR_Float value..
	// For MS Windows compatibility do not use modff()
	//deci_flt = modff(input_val, & integ_flt);
	deci_flt = (OR_Float) modf((OR_Real64 ) input_val, & dbl_flt); 
	integ_flt = (OR_Float) dbl_flt;

	deci_flt *= pow(10, precision);  // 10 raised to precision
	//for (OR_I32 tmpzz = 0; tmpzz < precision; tmpzz++)
	//{
	//	deci_flt *= 10;
	//}
	debug_("deci_flt", deci_flt);

	OR_U32 deci_int = (OR_U32) ( rint(deci_flt) );

	if (deci_int > 999) // (MAX_PREC) digits
		sprintf(sval, "%lu.%lu", (OR_U32) integ_flt, deci_int); 
	else
	if (deci_int > 99) // (MAX_PREC - 1) digits
		sprintf(sval, "%lu.0%lu", (OR_U32) integ_flt, deci_int); 
	else
	if (deci_int > 9) // (MAX_PREC - 2) digits
		sprintf(sval, "%lu.00%lu", (OR_U32) integ_flt, deci_int); 
	else
		sprintf(sval, "%lu.00000%lu", (OR_U32) integ_flt, deci_int); 
	*/
}

void OR_String::roundd(OR_Real64 input_val, short precision)
{
	// As per "C" compiler on 32-bit CPUs OR_Float is at least 6 
	// decimal digits of precision.
	// Double and, OR_I32 OR_Real64 is at least 10 decimal digits
	// On 64-bit machines accuracy will be much higher
	// 		fprintf(stderr, "\n ff:%.6f", ff);    	// f OR_Float
	// 		fprintf(stderr, "\n dd:%.26lf", dd);  	// lf OR_Real64
	// 		fprintf(stderr, "\n ldd:%.26Lf", ldd); 	// Lf OR_I32 OR_Real64
	debug_("In roundd", "ok");
	_roundno(input_val, 0.0, precision, false);

	/*
	OR_Real64	integ_flt, deci_flt;
	// get the integral and decimal parts of the OR_Real64 value..
	deci_flt = modf(input_val, & integ_flt);

	deci_flt *= pow(10, precision);  // 10 raised to precision
	//for (OR_I32 tmpzz = 0; tmpzz < precision; tmpzz++)
	//{
	//	debug_("deci_flt", deci_flt);
	//	deci_flt *= 10;
	//}
	debug_("deci_flt", deci_flt);

	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Real64 nnn digits max

	OR_U32 deci_int = (OR_U32) ( rint(deci_flt) );

	if (deci_int > 99999) // (MAX_PREC) digits
		sprintf(sval, "%lu.%lu", (OR_U32) integ_flt, deci_int); 
	else
	if (deci_int > 9999) // (MAX_PREC - 1) digits
		sprintf(sval, "%lu.0%lu", (OR_U32) integ_flt, deci_int); 
	else
	if (deci_int > 999) // (MAX_PREC - 2) digits
		sprintf(sval, "%lu.00%lu", (OR_U32) integ_flt, deci_int); 
	else
	if (deci_int > 99) // (MAX_PREC - 3) digits
		sprintf(sval, "%lu.000%lu", (OR_U32) integ_flt, deci_int); 
	else
	if (deci_int > 9) // (MAX_PREC - 4) digits
		sprintf(sval, "%lu.0000%lu", (OR_U32) integ_flt, deci_int); 
	else // (MAX_PREC - 5) digits
		sprintf(sval, "%lu.00000%lu", (OR_U32) integ_flt, deci_int); 
	*/
}

// Provided for documentation purpose only
// You must use the function indexOf()
OR_Bool OR_String::contains(char *str2, OR_I32 startIndex) 
{
	// For example -
	//		if (indexOf("ohboy") > -1 )
	//			cout << "\nString contains 'ohboy'" << endl;
	//		if (indexOf("ohboy") < 0 )
	//			cout << "\nString does NOT contain 'ohboy'" << endl;
	//		if (indexOf("ohboy", 4) > -1 )
	//			cout << "\nString contains 'ohboy'" << endl;
	//		if (indexOf("ohboy", 4) < 0 )
	//			cout << "\nString does NOT contain 'ohboy'" << endl;
	cerr << "\n\nYou must use indexOf() function instead of contains()\n\n" << endl;
	exit(-1);
}

// Synonym function is empty()
OR_Bool OR_String::isNull()
{
	if (sval[0] == '\0')
		return true;
	else
	{
		if (sval == NULL)
			return true;
		else
			return false;
	}
}

// Leading, trailing white-spaces of string are ignored
OR_Bool OR_String::isInteger()
{
	OR_String tmpstr(sval);
	tmpstr.trim(true);
	debug_("tmpstr.sval", tmpstr.sval );
	if ( strspn ( tmpstr.sval, "0123456789" ) != strlen(tmpstr.sval) )
		return ( false ) ;
	else
		return ( true ) ;
}

// overloaded func
OR_Bool OR_String::isInteger(OR_I32 pos) 
{
	verifyIndex(pos);
	if (isdigit(sval[pos])) // is not 0
		return true;
	else // is 0
		return false;
}

// Leading, trailing white-spaces of string are ignored
OR_Bool OR_String::isNumeric()
{
	OR_String tmpstr(sval);
	tmpstr.trim(true);
	debug_("tmpstr.sval", tmpstr.sval );
	if ( strspn ( tmpstr.sval, "0123456789.+-e" ) != strlen(tmpstr.sval) )
		return ( false ) ;
	else
		return ( true ) ;
}

// overloaded func
OR_Bool OR_String::isNumeric(OR_I32 pos) 
{
	verifyIndex(pos);
	if (isdigit(sval[pos])) // is not 0
		return true;
	else // is 0
		return false;
}

OR_Bool OR_String::isEmpty()
{
	if (strlen(sval) == 0)
		return true;
	else
		return false;
}

// See also explode()
//	Warning : The OR_String instance is modified by removing
//		      the returned token from the string. It is advised
//			  that you save the original string before calling
//			  this function like for example : 
//		OR_String savestr = origstr;
//		OR_String aa, bb, cc;
//		aa = origstr.token();
//		bb = origstr.token();
//		cc = origstr.token();
//
//  This routine returns the first non-'separator' (default 
//  white-space) token string from the OR_String instance
OR_String OR_String::token(char separator) 
{
	char ee[2];
	ee[0] = separator;
	ee[1] = 0;
	char *res = strtok(sval, ee);
	if (!res) // if res == NULL
	{
		debug_("token", res);
		debug_("sval", sval);
		return(OR_String(sval));
	}
	else
	{
		OR_String tmpstr(res);

		// Should take string length of sval and not res
		// because strtok() had put a NULL ('\0') at the location
		// and also strtok() ignores the leading blanks of sval
		strcpy(sval, & sval[strlen(sval)+1]);
		debug_("token", res);
		debug_("sval", sval);
		return tmpstr;
	}
}

OR_String OR_String::crypt(char *original, char *salt)
{
	return OR_String("");
}

OR_I32 OR_String::toInteger()
{
	if ( strlen(sval) == 0 ) {
		cerr << "OR_String::toInteger() - Cannot convert a zero length string "
		<< " to a numeric" << endl ;
		return 0; 
		//abort() ;
	}

	if ( ! isInteger() ) {
		cerr << "OR_String::toInteger() - Cannot convert string [" << sval
		<< "] to an integer numeric string" << endl ;
		return 0; 
		//abort() ;
	}

	return ( atoi ( sval ) ) ;
}

OR_I32 OR_String::parseLong()
{
	if ( strlen(sval) == 0 ) {
		cerr << "OR_String::parseLong() - Cannot convert a zero length string "
		<< " to a numeric" << endl ;
		return 0; 
		//abort() ;
	}

	if ( ! isInteger() ) {
		cerr << "OR_String::parseLong() - Cannot convert string [" << sval
		<< "] to an integer numeric string" << endl ;
		return 0; 
		//abort() ;
	}

	return ( atol ( sval ) ) ;
}

OR_Real64 OR_String::toDouble()
{
	if ( strlen(sval) == 0 ) {
		cerr << "OR_String::toDouble() - Cannot convert a zero length string "
		<< " to a numeric" << endl ;
		return 0; 
		//abort() ;
	}

	if ( ! isNumeric() ) {
		cerr << "OR_String::toDouble() - Cannot convert string [" << sval
		<< "] to a OR_Real64 numeric string" << endl ;
		return 0; 
		//abort() ;
	}

	OR_Real64 d = atof ( sval ) ;

	return ( d ) ;
}

OR_String OR_String::getline(FILE *infp)
{
	//register char ch, *aa = NULL; do not use register
	char ch = 0, *aa = NULL;

	//register const short SZ = 100; do not use register
	const short SZ = 100;
	// Initial value of ii > SZ so that aa is alloc'ed memory
	//register OR_I32 jj = 0; do not use register
	OR_I32 jj = 0;
	aa = (char *) realloc(aa, 15);  // initialize some little memory
	for (OR_I32 ii = SZ+1; (ch = fgetc(infp)) != EOF; ii++, jj++)  // use fgetc instead of getc
	{
		if (ii > SZ)  // allocate memory in steps of SZ for performance
		{
			aa = (char *) realloc(aa, jj + ii + 15);  // +15 is safe mem
			ii = 0;
		}

		if (ch == '\n')  // read until newline is encountered
		{
			if (jj == 0) // When jj is 0, then ch may have '\n' so...
			{
				jj--; // reset to nullify loop increment
				continue;
			}
			break;
		}
		aa[jj] = ch;
	}
	aa[jj] = 0;
	_str_cpy(aa);  // puts the value in string
	free(aa);
	return *this;
}

/*
void OR_String::Format(const char *fmt, ... )
{
	va_list iterator;
	va_start(iterator, fmt );
	va_end(iterator);
}
*/

/*
 * NAME:        dump()
 * DESCRIPTION: Dump the string like 'od -c' (octal dump) does.
 * AUTHOR of dump():      Marc Spoorendonk a.k.a. Grmbl <marc@spoorendonk.com>
 * DATE:        2001-01-06 01:34:09 CET
*/
OR_String OR_String::dump()
{
	OR_I32 i;
	char c;
	OR_String ret;

	for (i=0;; i++) 
	{
		c=sval[i];
		switch(c) 
		{
			case '\0': ret += " \\0"; return ret;
			case '\n': ret += " \\n"; break;
			case '\t': ret += " \\t"; break;
			case '\r': ret += " \\r"; break;
			case '\b': ret += " \\b"; break;
			case '\f': ret += " \\f"; break;
			case 127:  ret += "DEL"; break;
			case 3:    ret += " ^C"; break;
			default:
				if (c <' ' || c > '~') // print it in octal
				{
					char tmp[4];
					sprintf(tmp, "%-3o", c);
					debug_("Print as octal tmp", tmp);
					ret += tmp;
				}
				else // print it as a character
				{
					// cant add a char so adding a char[] instead
					char tmp[]="  x";
					tmp[2]=c;
					debug_("Print as char tmp", tmp);
					ret += tmp;
				}
		}
		ret += " ";
	}
	// not reached
}

// checks for the out of bounds values
void OR_String::verifyIndex(OR_U32 index) const
{
	// Index can be from 0 to length() of string
	// That is if string aa = "abcde" then 
	// valid values for index = 0 to index = 5
	// at index = 5 is the null value '\0' (i.e. aa[5] = '\0')
	if (index < 0 || index > strlen(sval) )
	{
		// throw "Index Out Of Bounds Exception";
		cerr << "\n\nIndex Out Of Bounds Exception at ["
				<< index << "] in:\n\n" << sval << endl;
		exit(1);
	}
}

// checks for the out of bounds values
void OR_String::verifyIndex(OR_U32 index, char *aa) const
{
	if (!aa) // aa == NULL
	{
		cerr << "\n\nverifyIndex(OR_I32, char *) str null value\n\n" << endl;
		exit(-1);
	}
	if (index < 0 || index >= strlen(aa) )
	{
		cerr << "\n\nIndex Out Of Bounds Exception at ["
				<< index << "] in:\n\n" << aa << endl;
		exit(1);
	}
}

char * OR_String::number2string(OR_I32 bb)
{
	_allocpNumber2String();
	sprintf(_pNumber2String, "%d", bb);
	return _pNumber2String;
}

char * OR_String::number2string(OR_U32 bb)
{
	_allocpNumber2String();
	sprintf(_pNumber2String, "%lu", bb);
	return _pNumber2String;
}

char * OR_String::number2string(OR_Real64 bb)
{
	_allocpNumber2String();
	sprintf(_pNumber2String, "%.16f", bb);
	return _pNumber2String;
}

//////////////////////////////////////////////////////////
// Private functions start from here .........
//////////////////////////////////////////////////////////

void OR_String::_str_cpy(char bb[])
{
	debug_("In _str_cpy bb", bb);
	if (bb == NULL)
	{
		sval[0] = '\0';
		return;
	}

	OR_U32 tmpii = strlen(bb);

	if (tmpii == 0)
	{
		sval[0] = '\0';
		return;
	}

	debug_("In _str_cpy tmpii", tmpii);
	debug_("In _str_cpy sval", sval);

	// What if sval and bb are the same string and pointing to the same 
	// memory location ? Then you cannot reallocate sval as it will 
	// completely destroy bb. Hence you should use memmove() or 
	// strdup() to preserve bb. 
	// This case happens in ltrim() and trim() functions.
	if (tmpii < strlen(sval))
	{
		memmove(sval, bb, tmpii);
		sval = (char *) my_realloc(sval, tmpii);
	} 
	else
	{
		sval = (char *) my_realloc(sval, tmpii);
		memmove(sval, bb, tmpii);
	}

	// sval = (char *) my_realloc(sval, tmpii);  // bug - realloc may destroy bb
	//sval = new char [tmpii + SAFE_MEM_2];
	
	debug_("In _str_cpy bb", bb);
	
	strncpy(sval, bb, tmpii);
	debug_("In _str_cpy sval", sval);
	sval[tmpii] = '\0';
	debug_("In _str_cpy sval", sval);
}

void OR_String::_str_cpy(OR_I32 bb)
{
	char tmpaa[NUMBER_LENGTH];
	sprintf(tmpaa, "%d", bb);
	_str_cpy(tmpaa);
}

void OR_String::_str_cpy(OR_U32 bb)
{
	char tmpaa[NUMBER_LENGTH];
	sprintf(tmpaa, "%ld", bb);
	_str_cpy(tmpaa);
}

void OR_String::_str_cpy(OR_Float bb)
{
	char tmpaa[NUMBER_LENGTH];
	sprintf(tmpaa, "%f", bb);
	_str_cpy(tmpaa);
}

void OR_String::_str_cat( const char bb[])
{
	OR_U32 tmpjj = strlen(bb), tmpii = strlen(sval);
	sval = (char *) my_realloc(sval, tmpii + tmpjj);
	debug_("sval in _str_cat() ", sval);
	strncat(sval, bb, tmpjj);
}

void OR_String::_str_cat(OR_I32 bb)
{
	char tmpaa[NUMBER_LENGTH];
	sprintf(tmpaa, "%d", bb);

	OR_U32 tmpjj = strlen(tmpaa), tmpii = strlen(sval);
	sval = (char *) my_realloc(sval, tmpii + tmpjj);
	strncat(sval, tmpaa, tmpjj);
}

void OR_String::_str_cat(OR_U32 bb)
{
	char tmpaa[NUMBER_LENGTH];
	sprintf(tmpaa, "%ld", bb);

	OR_U32 tmpjj = strlen(tmpaa), tmpii = strlen(sval);
	sval = (char *) my_realloc(sval, tmpii + tmpjj);
	strncat(sval, tmpaa, tmpjj);
}

void OR_String::_str_cat(OR_Float bb)
{
	char tmpaa[NUMBER_LENGTH];
	sprintf(tmpaa, "%f", bb);

	OR_U32 tmpjj = strlen(tmpaa), tmpii = strlen(sval);
	sval = (char *) my_realloc(sval, tmpii + tmpjj);
	strncat(sval, tmpaa, tmpjj);
}

void OR_String::_roundno(OR_Real64 input_dbl, OR_Float input_flt, short precision, OR_Bool type)
{
	short max_precision;
	if (type == true) // input val is OR_Real64
		max_precision = 10;
	else // input val is OR_Float
		max_precision = 6;  

	if (precision > max_precision) // this is the max reliable precision
		precision = max_precision;

	sval = (char *) my_malloc(NUMBER_LENGTH); // OR_Float nnn digits max

	if (type == true) // input val is OR_Real64
		sprintf(sval, "%.10f", input_dbl); 
	else // input val is OR_Float
		sprintf(sval, "%.6f", input_flt); 

	for (OR_I32 tmpval = 0; ; tmpval++) // find the loaction of decimal point
	{
		if (sval[tmpval] == '.')
		{
			sval[tmpval+precision] = 0;
			break;
		}
	}

	// Do later the round-off code
	// { ... rounding off code here... }
}

//////////////////////////////////////////////////////////
// All operator functions start from here .........
//////////////////////////////////////////////////////////
OR_String OR_String::operator+ (const OR_String & rhs)
{
	OR_String tmp(*this);
	tmp._str_cat(rhs.sval);
	debug_("rhs.sval in operator+", rhs.sval );
	debug_("tmp.sval in operator+", tmp.sval );
	return (tmp);
}

// Using reference will be faster in = operator
OR_String& OR_String:: operator= ( const OR_String& rhs )
{
	if (& rhs == this)
	{
		debug_("Fatal Error: In operator(=). rhs is == to 'this pointer'!!", "ok" );
		return *this;
	}

	this->_str_cpy(rhs.sval);
	debug_("rhs value", rhs.sval );

	// Free global vars memory
	//_free_glob(& OR_String::_global_String);
	//if (OR_String::_global_String == NULL)
		//fprintf(stderr, "\n_global_String is freed!\n");

	//return (OR_String(*this));
	return *this;
}

// Using reference will be faster in = operator
OR_String& OR_String::operator+= (const OR_String & rhs)
{
	/*******************************************************/
	// Note : For adding two char strings, first cast OR_String 
	// as in - 
	//aa += (OR_String) "cccc" + "dddd";
	/*******************************************************/

	if (& rhs == this)
	{
		debug_("Fatal error: In operator+= rhs is equals 'this' ptr", "ok");
		return *this;
	}
	this->_str_cat(rhs.sval);
	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_String::operator
 *
 *  \param  c the char to add at the end of the string.
 *  \return the string itself.
 *  \author Gabriel Peyré 2001-11-21
 */ 
/*------------------------------------------------------------------------------*/
OR_String& OR_String::operator+=(char c)
{
	this->_str_cat(&c);
	return *this;
}


OR_Bool OR_String::operator== (const OR_String & rhs)
{
	return(_equalto(rhs.sval));
}

OR_Bool OR_String::operator== (const char *rhs)
{
	return(_equalto(rhs));
}

OR_Bool OR_String::operator!= (const OR_String & rhs)
{
	return(_equalto(rhs.sval, true));
}

OR_Bool OR_String::operator!= (const char *rhs)
{
	return(_equalto(rhs, true));
}

char OR_String::operator[] (OR_U32 Index) const
{
	verifyIndex(Index);
	return sval[Index];
}

char & OR_String::operator[] (OR_U32 Index)
{
	verifyIndex(Index);
	return sval[Index];
}

std::istream & operator >> (std::istream & In, OR_String & str2)
{
	// allocate max size of 2048 characters
	static char aa[MAX_ISTREAM_SIZE]; 
	aa[0] = 0;

	// When you use the data input provided by cin you will have to trust
	// that the user of your program will be totally cooperative and that he
	// will not introduce his name when an interger value is requested.
	// The cin will cause lot of problems and program behaviour will be strange
	In >> aa;
	str2 = aa; // assign to reference OR_String
	return In; // return istream
}

std::ostream & operator << (std::ostream & Out, const OR_String & str2)
{
	Out << str2.const_val();
	return Out;
}

// handy methods for map & vector
OR_Bool OR_String::operator< (const char *rhs) const
{
	return strncmp(rhs, sval, strlen(sval)) > 0;
}

// handy methods for map & vector
OR_Bool OR_String::operator< (const OR_String & rhs) const
{
	return strncmp(rhs.sval, sval, strlen(sval)) > 0;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_String::void	
 *
 *  \param  Base the base of the path.
 *  \author Gabriel Peyré 2001-11-21
 *
 *	Make the path representing the path relative to the base path.
 */ 
/*------------------------------------------------------------------------------*/
void OR_String::SetRelativeToPath( const OR_String& Base )
{
	OR_String BaseDup( Base );
	// if one of the strings is void, exit
	if (	BaseDup.length()==0 ||	this->length()==0 ) 
		return;
	// if BaseDup or path is not an absolute path (ie starting with "\" or "x:", return
	if (	BaseDup.charAt(0)!='\\' 
		&&	!(	BaseDup.charAt(1)==':'
		&&	isalpha(BaseDup.charAt(0)) ) ) 
		return;
	if (	this->charAt(0)!='\\' 
		&&	!(	this->charAt(1)==':'
		&&	isalpha(this->charAt(0)) ) ) 
		return;
	// if both paths contain drive letters, letters must be the same
	if (	BaseDup.length()>1 
		&&	BaseDup.charAt(1)==':'
		&&	this->length()>1
		&&	this->charAt(1)==':'
		&&	tolower(BaseDup.charAt(0))!=tolower(this->charAt(0)) ) 
		return;
	
	// add a "\\" at the end if there isn't
	if( this->charAt(this->length()-1)!='\\' ) 
		this->concat('\\');
	if( BaseDup.charAt(BaseDup.length()-1)!='\\' ) 
		BaseDup.concat('\\');

	// init pointers
	OR_U32 p_BaseDup=0, p_this=0;
	if( BaseDup.length()>1 && BaseDup.charAt(1)==':' ) 
		p_BaseDup=2;
	if( this->length()>1 && this->charAt(1)==':' ) 
		p_this=2;
	OR_U32 slash_BaseDup=p_BaseDup, slash_this=p_this;
	
	// find the length of the common parts in path and BaseDup
	while(	p_BaseDup<BaseDup.length()
		&&	p_this<this->length()
		&& BaseDup[p_BaseDup]==this->charAt(p_this))
	{
		if (this->charAt(p_this)=='\\')
		{
			slash_BaseDup = p_BaseDup;
			slash_this = p_this;
		}
		p_BaseDup++;
		p_this++;
	}
	
	// delete the common part if paths
	(*this) = this->substring( slash_this+1 );
	p_BaseDup = slash_BaseDup+1;
	p_this = 0;
	
	// add as many "..\" as there are directories left is BaseDup
	while(p_BaseDup<BaseDup.length())
	{
		if (BaseDup.charAt(p_BaseDup)=='\\') (*this) = OR_String( "..\\" ) + (*this);
		p_BaseDup++;
	}
}

/*------------------------------------------------------------------------------ 
* Name : OR_String::StripDots 
* 
*  \author Antoine Bouthors 2002-01-05 
* 
* Transform a path with dots (.. , .) into a normal path 
*------------------------------------------------------------------------------*/ 
void OR_String::StripDots() 
{ 
	OR_U32 p=length()-1; 
	while( p>0 ) 
	{ 
		if( sval[p] == '.' ) 
		{ 
			if( p>1 && sval[p-1]=='.' && sval[p-2]=='\\' ) 
			{ 
				OR_U32 End = p+1; 
				OR_U32 Counter = 2; 
				p = p-2; 
				while( Counter > 0 ) 
				{ 
					   if( p<0 || sval[p]=='\\' ) Counter--; 
					   else if( sval[p]=='.' && p>0 && sval[p-1]=='.' ) Counter+=2; 
					   p--; 
				} 
				strcpy( sval+p+1, sval+End ); 
			} 
			else if( p>0 && sval[p-1] == '\\' ) 
			{ 
				strcpy( sval+p, sval+p+2 ); 
			} 
		} 
		p--; 
	} 
} 


/*------------------------------------------------------------------------------ 
* Name : OR_String::GetPath 
* 
*  \return The string up to the last \ (including it) 
*  \author Antoine Bouthors 2002-01-05 
* 
*------------------------------------------------------------------------------*/ 
OR_String OR_String::GetPath() 
{ 
	OR_I32 LastSlash = lastIndexOf( '\\' ); 
	if( LastSlash > 0 ) return substring( 0, LastSlash ); 
	else return OR_String( "" ); 
} 


/*------------------------------------------------------------------------------ 
* Name : OR_String::MkDir 
* 
*      \return true if the directory has been sucessfully created 
*  \author Antoine Bouthors 2002-01-05 
* 
* Create the directory designed by this 
*------------------------------------------------------------------------------*/ 
OR_Bool OR_String::MkDir() 
{ 
	if( length()==0 ) return false; 
	int Result = mkdir( sval ); 
	if( Result == EEXIST ) return true; 
	if( Result == 0 ) return true; 
	if( GetPath().MkDir() ) 
		return ( mkdir( sval ) == 0 ); 
	else 
		return false; 
} 



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_String::truncate
 *
 *  \param  nPos position of the first character to remove.
 *  \author Gabriel Peyré 2001-11-21
 */ 
/*------------------------------------------------------------------------------*/
void OR_String::truncate(OR_U32 nPos)
{
	(*this) = this->deleteStr(nPos, this->length());
}


/* serialization methods ***************************************/
void OR_String::BuildFromFile( OR_File& file )
{
	/* read the length of the string */
	OR_I32 nLength;
	file >> nLength;
	OR_ASSERT(nLength>=0);
	/* set the size */
	char* str = new char[nLength+1];
	str[nLength]=NULL;
	/* read the data */
	fread(str, sizeof(char), nLength, file.GetFile());
	this->clear();
	this->concat( OR_String(str, 0, nLength) );
	OR_DELETEARRAY(str);
}

void OR_String::BuildToFile( OR_File& file )
{
	/* write the length of the string */
	OR_I32 nSize = this->length();
	file << nSize;
	/* write the data */	
	fwrite(this->toCharArray(), sizeof(char), this->length(), file.GetFile());
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