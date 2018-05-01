/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_String.h
 *  \brief Definition of class \c OR_ShellConsole_ABC
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __STRING_H_ALDEV_
#define __STRING_H_ALDEV_

#include <iostream> 
using std::cerr;
using std::endl;

#include "../configuration/OR_Config.h"
#include "../misc/OR_Globals.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_File.h"
#include <stdio.h> // for FILE and sprintf()


using namespace OR;

namespace OR
{

const short INITIAL_SIZE = 	50;
const short NUMBER_LENGTH = 300;
const OR_I32 MAX_ISTREAM_SIZE = 2048;


/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_String
 *  \brief  a string
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	A Java like string, using the implementation of Marc Spoorendonk
 *
 *	\example string_test/main.cpp
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_String: public OR_Serializable
{

public:

    //-------------------------------------------------------------------------
    /** \name constructors & destructor */
    //-------------------------------------------------------------------------
    //@{
	OR_String();
	OR_String(const char bb[]);  // needed by operator+
	OR_String(const char bb[], OR_I32 start, OR_I32 slength); // subset of chars
	OR_String(OR_I32 bb);		// needed by operator+
	OR_String(OR_U32 bb);		// needed by operator+
	OR_String(OR_Float bb);		// needed by operator+
	OR_String(OR_Bool bb);		// needed by operator+
	OR_String(OR_Real64 bb);	// needed by operator+
	OR_String(const OR_Vector2D& bb);	// needed by operator+
	OR_String(const OR_Vector3D& bb);	// needed by operator+
	OR_String(const OR_Vector4D& bb);	// needed by operator+
	OR_String(const OR_Matrix4x4& bb);	// needed by operator+
	OR_String(const OR_Matrix3x3& bb);	// needed by operator+
	OR_String(const OR_Quaternion& bb);	// needed by operator+
	OR_String(const OR_String & rhs);	// Copy Constructor needed by operator+
	OR_String(OR_I32 bb, OR_Bool dummy);  // for StringBuffer class
	virtual ~OR_String();
    //@}


	char *val() {return sval;} // It is not safe to make sval public
	const char *const_val() const { return sval; }

	// Functions below imitate Java language's OR_String object 
	OR_U32 length() const;
	char charAt(OR_I32 where) const;
	void getChars(OR_I32 sourceStart, OR_I32 sourceEnd, 
			char target[], OR_I32 targetStart);
	char* toCharArray();
	char* getBytes();

	OR_Bool equals( const OR_String& str2) const; // See also == operator
	OR_Bool equals( const char *str2 ) const; // See also == operator
	OR_Bool equalsIgnoreCase( const OR_String& str2 ) const;

	OR_Bool regionMatches(OR_I32 startIndex, OR_String str2, 
			OR_I32 str2StartIndex, OR_I32 numChars);
	OR_Bool regionMatches(OR_Bool ignoreCase, OR_I32 startIndex, 
			OR_String str2, OR_I32 str2StartIndex, OR_I32 numChars);

	OR_String toUpperCase() const;
	OR_String toLowerCase() const;

	OR_Bool startsWith(OR_String str2);
	OR_Bool startsWith(char *str2);

	OR_Bool endsWith(OR_String str2);
	OR_Bool endsWith(char *str2);

	OR_I32 compareTo(OR_String str2) const;
	OR_I32 compareTo(char *str2) const;
	OR_I32 compareToIgnoreCase(OR_String str2) const;
	OR_I32 compareToIgnoreCase(char *str2) const;

	OR_I32 indexOf(char ch, OR_I32 startIndex = 0);
	OR_I32 indexOf(char *str2, OR_I32 startIndex = 0);
	OR_I32 indexOf(OR_String str2, OR_I32 startIndex = 0);

	OR_I32 lastIndexOf(char ch, OR_I32 startIndex = 0);
	OR_I32 lastIndexOf(char *str2, OR_I32 startIndex = 0);
	OR_I32 lastIndexOf(OR_String str2, OR_I32 startIndex = 0);

	OR_String substring(OR_I32 startIndex, OR_I32 endIndex = 0);
	OR_String replace(char original, char replacement);
	OR_String replace(char *original, char *replacement);

	void truncate(OR_U32 nPos);

	OR_String trim(); // See also overloaded trim()

	OR_String concat(OR_String str2);  // See also operator +
	OR_String concat(char *str2); // See also operator +
	OR_String concat(OR_I32 bb);
	OR_String concat(OR_U32 bb);
	OR_String concat(char c);
	OR_String concat(OR_Float bb);
	OR_String concat(OR_Real64 bb);

	OR_String reverse(); // See also overloaded reverse()
	OR_String deleteCharAt(OR_I32 loc);
	OR_String deleteStr(OR_I32 startIndex, OR_I32 endIndex); // Java's "delete()"

	OR_String valueOf(char ch)
		{char aa[2]; aa[0]=ch; aa[1]=0; return OR_String(aa);}
	OR_String valueOf(char chars[]){ return OR_String(chars);}
	OR_String valueOf(char chars[], OR_I32 startIndex, OR_I32 numChars);
	OR_String valueOf(OR_Bool tf)
		{if (tf) return OR_String("true"); else return OR_String("false");}
	OR_String valueOf(OR_I32 num){ return OR_String(num);}
	OR_String valueOf(OR_U32 num){ return OR_String(num);}
	OR_String valueOf(OR_Float num) {return OR_String(num);}
	OR_String valueOf(OR_Real64 num) {return OR_String(num);}

	// ---- End of Java like OR_String object functions -----

	//////////////////////////////////////////////////////
	// 		List of additonal functions not in java
	//////////////////////////////////////////////////////
	OR_String ltrim();
	void ltrim(OR_Bool dummy); // Directly changes object. dummy to get different signature
	OR_String rtrim();
	void rtrim(OR_Bool dummy); // Directly changes object. See also chopall(). 
			// dummy to get different signature

	void chopall(char ch='\n'); // removes trailing character 'ch'. See also rtrim()
	void chop(); // removes one trailing character

	void roundf(OR_Float input_val, short precision);
	void decompose_float(OR_I32 *integral, OR_I32 *fraction); 

	void roundd(OR_Real64 input_val, short precision);
	void decompose_double(OR_I32 *integral, OR_I32 *fraction); 

	void explode(char *separator); // see also token() and overloaded explode()
	OR_String *explode(OR_I32 & strcount, char separator = ' '); // see also token()
	void implode(char *glue);
	void join(char *glue);
	OR_String repeat(char *input, OR_U32 multiplier);
	OR_String tr(char *from, char *to); // translate characters
	OR_String center(OR_I32 padlength, char padchar = ' ');
	OR_String space(OR_I32 number = 0, char padchar = ' ');
	OR_String xrange(char start, char end);
	OR_String compress(char *list = " ");
	OR_String left(OR_I32 slength = 0, char padchar = ' ');
	OR_String right(OR_I32 slength = 0, char padchar = ' ');
	OR_String overlay(char *newstr, OR_I32 start = 0, OR_I32 slength = 0, char padchar = ' ');

	OR_String at(char *regx); // matches first match of regx
	OR_String before(char *regx); // returns string before regx
	OR_String after(char *regx); // returns string after regx
	OR_String mid(OR_I32 startIndex = 0, OR_I32 length = 0);

	OR_Bool isNull();  
	OR_Bool isInteger();
	OR_Bool isInteger(OR_I32 pos);
	OR_Bool isNumeric();
	OR_Bool isNumeric(OR_I32 pos);
	OR_Bool isEmpty();  // same as length() == 0
	OR_Bool isUpperCase();
	OR_Bool isUpperCase(OR_I32 pos);
	OR_Bool isLowerCase();
	OR_Bool isLowerCase(OR_I32 pos);
	OR_Bool isWhiteSpace();
	OR_Bool isWhiteSpace(OR_I32 pos);
	OR_Bool isBlackSpace();
	OR_Bool isBlackSpace(OR_I32 pos);
	OR_Bool isAlpha();
	OR_Bool isAlpha(OR_I32 pos);
	OR_Bool isAlphaNumeric();
	OR_Bool isAlphaNumeric(OR_I32 pos);
	OR_Bool isPunct();
	OR_Bool isPunct(OR_I32 pos);
	OR_Bool isPrintable();
	OR_Bool isPrintable(OR_I32 pos);
	OR_Bool isHexDigit();
	OR_Bool isHexDigit(OR_I32 pos);
	OR_Bool isCntrl();
	OR_Bool isCntrl(OR_I32 pos);
	OR_Bool isGraph();
	OR_Bool isGraph(OR_I32 pos);

	void clear();
	OR_I32 toInteger();
	OR_I32 parseLong();

	OR_Real64 toDouble();
	OR_String token(char separator = ' '); // see also StringTokenizer, explode()
	OR_String crypt(char *original, char *salt);
	OR_String getline(FILE *infp = stdin); // see also putline()
	//OR_String getline(fstream *infp = stdin); // see also putline()

	void putline(FILE *outfp = stdout); // see also getline()
	//void putline(fstream *outfp = stdout); // see also getline()

	void swap(OR_String aa, OR_String bb); // swap aa to bb
	OR_String *sort(OR_String aa[]);  // sorts array of strings
	OR_String sort(OR_I32 startIndex = 0, OR_I32 length = 0);  // sorts characters inside a string
	OR_I32 freq(char ch); // returns the number of distinct, nonoverlapping matches
	void Format(const char *fmt, ...);
	OR_String replace(OR_I32 startIndex, OR_I32 endIndex, OR_String str);

	void substring(OR_I32 startIndex, OR_I32 endIndex, OR_Bool dummy); // Directly changes object
	void reverse(OR_Bool dummy); // Directly changes object. dummy to get different signature
	OR_String deleteCharAt(OR_I32 loc, OR_Bool dummy); // Directly changes object
	OR_String deleteStr(OR_I32 startIndex, OR_I32 endIndex, OR_Bool dummy);
	void trim(OR_Bool dummy); // Directly changes object. dummy to get different signature
	OR_String insert(OR_I32 index, OR_String str2);
	OR_String insert(OR_I32 index, OR_String str2, OR_Bool dummy); // Directly changes object
	OR_String insert(OR_I32 index, char ch);
	OR_String insert(OR_I32 index, char ch, OR_Bool dummy); // Directly changes object
	OR_String insert(char *newstr, OR_I32 start = 0, OR_I32 length = 0, char padchar = ' ');

	OR_String dump(); // Dump the string like 'od -c' (octal dump) does

	// required by java's StringBuffer
	void ensureCapacity(OR_I32 capacity);
	void setLength(OR_I32 len);
	void setCharAt(OR_I32 where, char ch); // see also charAt(), getCharAt()

	// required by java's Integer class, Long, Double classes
	OR_I32 parseInt(OR_String ss) {return ss.toInteger();}
	OR_I32 parseInt(char *ss)
		{OR_String tmpstr(ss); return tmpstr.toInteger();}
	OR_I32 parseLong(OR_String ss) {return ss.parseLong();}
	OR_I32 parseLong(char *ss)
		{OR_String tmpstr(ss); return tmpstr.parseLong();}
	OR_Float floatValue() {return (OR_Float) toDouble(); }
	OR_Real64 doubleValue() {return toDouble(); }
	char * number2string(OR_I32 bb);  // see also OR_String(OR_I32)
	char * number2string(OR_U32 bb);  // see also OR_String(OR_I32)
	char * number2string(OR_Real64 bb);  // see also OR_String(OR_Real64)

	/* OR_String path tools ***************************************/
	void	SetRelativeToPath( const OR_String& Base );
	void	StripDots(); 
	OR_Bool	MkDir(); 
	OR_String	GetPath(); 

	///////////////////////////////////////////////
	// 		List of duplicate function names
	///////////////////////////////////////////////
	// char * c_str() // use val()
	// OR_Bool find();  // Use regionMatches()
	// OR_Bool search();  // Use regionMatches()
	// OR_Bool matches(); // Use regionMatches()
	// OR_I32 rindex(OR_String str2, OR_I32 startIndex = 0); Use lastIndexOf()
	// OR_String blanks(OR_I32 slength);  // Use repeat()
	// OR_String append(OR_String str2); // Use concat() or + operator
	// OR_String prepend(OR_String str2);  // Use + operator. See also append()
	// OR_String split(char separator = ' ');  // Use token(), explode() or StringTokenizer class
	OR_Bool contains(char *str2, OR_I32 startIndex = 0); // use indexOf()
	// void empty(); Use is_empty()
	// void vacuum(); Use clear()
	// void erase(); Use clear()
	// void zero(); Use clear()
	// OR_Bool is_float(); Use is_numeric();
	// OR_Bool is_decimal(); Use is_numeric();
	// OR_Bool is_Digit(); Use is_numeric();
	// OR_Float float_value(); Use toDouble();
	// OR_Float tofloat(); Use toDouble();
	// OR_Real64 double_value(); Use toDouble();
	// OR_Real64 numeric_value(); Use toDouble();
	// OR_I32 int_value(); Use toInteger()
	// OR_I32 tonumber(); Use toInteger()
	// OR_String get(); Use substring() or val() but prefer java's substring
	// OR_String getFrom(); Use substring() or val() but prefer java's substring
	// OR_String head(OR_I32 len); Use substring(0, len)
	// OR_String tail(OR_I32 len); Use substring(length()-len, length())
	// OR_String cut(); Use deleteCharAt() or deleteStr()
	// OR_String cutFrom(); Use deleteCharAt() or deleteStr()
	// OR_String paste(); Use insert()
	// OR_String fill(); Use replace()
	// char firstChar(); // Use substring(0, 1);
	// char lastChar(); // Use substring(length()-1, length());
	// OR_String findNext(); Use token(), explode() or StringTokenizer class

	// begin();  iterator. Use operator [ii]
	// end();  iterator. Use operator [ii]
	// copy();  Use assignment =  operator, OR_String aa = bb;
	// clone();  Use assignment =  operator, OR_String aa = bb;
	// void putCharAt(OR_I32 where, char ch); Use setCharAt()
	// void replaceCharAt(OR_I32 where, char ch); Use setCharAt()
	// char getCharAt(OR_I32 where); Use CharAt()
	// void parseArgs(OR_I32 where, char ch); Use StringTokensizer class, token() or explode()
	// void truncate(); Use trim(), rtrim(), chop() or chopall()
	// convert number to string notostring(), int2str, long2str Use number2string()

	// All Operators ...
	OR_String operator+ (const OR_String & rhs);
	friend OR_String operator+ (const OR_String & lhs, const OR_String & rhs)
	{ OR_String tmp(lhs); tmp._str_cat( rhs.const_val() ); return(tmp); }

	OR_String& operator+= (const OR_String & rhs); // using reference will be faster
	OR_String& operator+= (char c);
	OR_String& operator= (const OR_String & rhs); // using reference will be faster
	OR_Bool operator== (const OR_String & rhs); // using reference will be faster
	OR_Bool operator== (const char *rhs);
	friend OR_Bool operator==(const OR_String& lhs, const OR_String& rhs)
	{ return lhs._equalto(rhs);	}
	OR_Bool operator!= (const OR_String & rhs);
	OR_Bool operator!= (const char *rhs); 
	char operator [] (OR_U32 Index) const;
	char& operator [] (OR_U32 Index);
	friend std::ostream &  operator<< (std::ostream & Out, const OR_String & str2);
	friend std::istream &  operator>> (std::istream & In, OR_String & str2);

	OR_Bool OR_String::operator< (const char *rhs) const; // handy methods for map & vector:
	OR_Bool OR_String::operator< (const OR_String & rhs) const; // handy methods for map & vector:
	
	void _str_cat(const char bb[]);

	//-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_String);
    //@}

protected:

	char *sval; // Not safe to make sval public
	void verifyIndex(OR_U32 index) const; // not "inline" because MS Win32 complains
	void verifyIndex(OR_U32 index, char *aa) const;// not "inline" - MS Win32 complains

	void _str_cat(OR_I32 bb);
	void _str_cat(OR_U32 bb);
	void _str_cat(OR_Float bb);

	void _str_cpy(char bb[]);
	void _str_cpy(OR_I32 bb); // itoa
	void _str_cpy(OR_U32 bb);
	void _str_cpy(OR_Float bb); // itof


private:

	// Note: All the private variables and functions begin
	// with _ (underscore)

	//static OR_String *_global_String; // for use in add operator
	//inline void _free_glob(OR_String **aa);

	OR_Bool _equalto(const OR_String & rhs, OR_Bool type = false) const;
	OR_Bool _equalto(const char *rhs, OR_Bool type = false) const;
	mutable OR_String *_pString;  // temporary pointer for internal use..
	mutable char *_pNumber2String;  // temporary pointer for internal use..
	inline void _allocpString() const;
	inline void _allocpNumber2String() const;
	inline void Common2AllCstrs();
	inline void _reverse();
	inline void _deleteCharAt(OR_I32 loc);
	inline void _deleteStr(OR_I32 startIndex, OR_I32 endIndex);
	inline void _trim();
	inline void _ltrim();
	inline void _rtrim();
	inline void _substring(OR_I32 startIndex, OR_I32 endIndex);
	void _roundno(OR_Real64 input_dbl, OR_Float input_flt, short precision, OR_Bool type);

};


const short SAFE_MEM = 3;

const short DATE_MAX_SIZE = 200;

const short MALLOC = 1;  // memory type
const short REALLOC	= 2;  // memory type

const short VOID_TYPE =		1;
const short CHAR_TYPE =		2;
const short SHORT_TYPE =	3;
const short INT_TYPE =		4;
const short LONG_TYPE =		5;
const short FLOAT_TYPE =	6;
const short DOUBLE_TYPE =	7;
/** clean reallocation*/
inline
void local_my_free(void *aa, char fname[], OR_I32 lineno)
{
	if (aa == NULL)
		return;
	free(aa);
	aa = NULL;
}
// size_t is type-defed OR_U32
inline
void *local_my_malloc(size_t size, char fname[], OR_I32 lineno) 
{
	size_t  tmpii = size + SAFE_MEM;
	void *aa = NULL;
	aa = (void *) malloc(tmpii);
	
	OR_ASSERT( aa!=NULL );
	
	memset(aa, 0, tmpii);
	return aa;
}
// size_t is type-defed OR_U32
inline
char *local_my_realloc(char *aa, size_t size, char fname[], OR_I32 lineno)
{
	OR_U32 tmpjj = 0;
	if (aa) // aa !=  NULL
		tmpjj = strlen(aa);
	OR_U32 tmpqq = size + SAFE_MEM;
	size_t  tmpii = sizeof (char) * (tmpqq);
	aa = (char *) realloc(aa, tmpii);
	
	OR_ASSERT( aa!=NULL );

	// do not memset!! memset(aa, 0, tmpii);
	aa[tmpqq-1] = 0;
	OR_U32 kk = tmpjj;
	if (tmpjj > tmpqq)
		kk = tmpqq;
	for ( ; kk < tmpqq; kk++)
		aa[kk] = 0;
	return aa;
}
// size_t is type-defed OR_U32
inline
short *local_my_realloc(short *aa, size_t size, char fname[], OR_I32 lineno)
{
	OR_U32 tmpqq = size + SAFE_MEM;
	size_t  tmpii = sizeof (short) * (tmpqq);
	aa = (short *) realloc(aa, tmpii);
	
	OR_ASSERT( aa!=NULL );

	// do not memset!! memset(aa, 0, tmpii);
	// Not for numbers!! aa[tmpqq-1] = 0;
	return aa;
}
// size_t is type-defed OR_U32
inline
OR_I32 *local_my_realloc(OR_I32 *aa, size_t size, char fname[], OR_I32 lineno)
{
	OR_U32 tmpqq = size + SAFE_MEM;
	size_t  tmpii = sizeof (OR_I32) * (tmpqq);
	aa = (OR_I32 *) realloc(aa, tmpii);

	OR_ASSERT( aa!=NULL );

	// do not memset!! memset(aa, 0, tmpii);
	// Not for numbers!! aa[tmpqq-1] = 0;
	return aa;
}
// size_t is type-defed OR_U32
inline
OR_U32 *local_my_realloc(OR_U32 *aa, size_t size, char fname[], OR_I32 lineno)
{
	OR_U32 tmpqq = size + SAFE_MEM;
	size_t  tmpii = sizeof (OR_U32) * (tmpqq);
	aa = (OR_U32 *) realloc(aa, tmpii);
	
	OR_ASSERT( aa!=NULL );

	// do not memset!! memset(aa, 0, tmpii);
	// Not for numbers!! aa[tmpqq-1] = 0;
	return aa;
}
// size_t is type-defed OR_U32
inline
OR_Float *local_my_realloc(OR_Float *aa, size_t size, char fname[], OR_I32 lineno)
{
	OR_U32 tmpqq = size + SAFE_MEM;
	size_t  tmpii = sizeof (OR_Float) * (tmpqq);
	aa = (OR_Float *) realloc(aa, tmpii);
	
	OR_ASSERT( aa!=NULL );

	// do not memset!! memset(aa, 0, tmpii);
	// Not for numbers!! aa[tmpqq-1] = 0;
	return aa;
}

// size_t is type-defed OR_U32
inline
OR_Real64 *local_my_realloc(OR_Real64 *aa, size_t size, char fname[], OR_I32 lineno)
{
	OR_U32 tmpqq = size + SAFE_MEM;
	size_t  tmpii = sizeof (OR_Real64) * (tmpqq);
	aa = (OR_Real64 *) realloc(aa, tmpii);
	
	OR_ASSERT( aa!=NULL );

	// do not memset!! memset(aa, 0, tmpii);
	// Not for numbers!! aa[tmpqq-1] = 0;
	return aa;
}

#define my_realloc(NM, SZ) (local_my_realloc(NM, SZ, __FILE__, __LINE__))
#define my_malloc(SZ) (local_my_malloc(SZ, __FILE__, __LINE__))
#define my_free(NM) (void) (local_my_free(NM, __FILE__, __LINE__))

/* don't print debug info */
#define debug_(x,y)
/* clean free */


}	// namespace OR



#ifdef OR_USE_INLINE
	#include "OR_String.inl"
#endif

#endif // __STRING_H_ALDEV_



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
