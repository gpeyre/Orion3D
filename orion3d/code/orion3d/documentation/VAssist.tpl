readme:
AutoText and Code Template entries used by Visual Assist. 

You can obtain information on the purpose and format of this
file by clicking "Help..." on the Auto Completion tab of the
options dialog. The button will open "readtmpl.txt" in the
Misc subdirectory of the Visual Assist installation directory.
If you are currently in VC++, you can also right-click on the 
string "readtmpl.txt" to display a menu with an Open Document 
item that can open the file for you.

caretPosChar:
§


readme:
AutoText follows. None of the entry names contain a space.


#d:
#define 
#de:
#define 
#u:
#undef 
#un:
#undef 
#p:
#pragma 
#pr:
#pragma 
#in:
#include "§"
#ins:
#include <§>
#im:
#import "§"
#if:
#ifdef §
#endif
#ifn:
#ifndef §
#endif
#el:
#else
#eli:
#elif 
#en:
#endif

A:
ASSERT(§)
r:
return
T:
TRUE
t:
true
F:
FALSE
f:
false
I:
INT
U:
UINT
B:
BOOL
V:
VOID
H:
HWND
L:
LONG
N:
NULL
class:
class §
{
public:
protected:
private:
};
struct:
struct § {
};
catch:
catch (§) {
}
ifel:
if (§) {
} else {
}
if:
if (§) {
}
al:
alert(§);
<div:
<DIV §></DIV>
<span:
<SPAN §></SPAN>
<i:
<INPUT TYPE=§ >
<t:
<TABLE §>
	<TR>
		<TD>
		</TD>
	</TR>
</TABLE>
fun:
function §() {
	
}
<h:
<HTML>
	<HEAD>
		§
	</HEAD>
	<BODY>
		
	</BODY>
</HTML>
<b:
<BODY>
§
</BODY>
<a:
<A HREF="§"></A>
<i:
<IMG SRC="§">
<m:
<META NAME="§" CONTENT="">
<ti:
<TITLE> § </TITLE>
<s:
<SCRIPT language="JavaScript">

§

</SCRIPT>
while:
while (§) {
}
do:
do {
	§
} while();
switch:
switch(§) {
case :
	break;
case :
	break;
default:
}
//:
// § [%MONTH%/%DAY%/%YEAR%]
///:
//////////////////////////////////////////////////////////////////////////

/*:
/* § */
/**:
/** § */
//@:
//-------------------------------------------------------------------------
/** \name AddCommentHere */
//-------------------------------------------------------------------------
//@{
§
//@}


readme:
Code Templates follow. All entry names contain a space.


.H file definition using selection:
/*------------------------------------------------------------------------------*/
/** 
 *  \file  %0.h
 *  \brief Definition of class \c %0
 *  \author Gabriel Peyré %DATE%
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __%0_h_
#define __%0_h_


#include "../configuration/OR_Config.h"


namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  %0
 *  \brief  AddCommentHere
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	AddCommentHere
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API %0
{
public:

    //-------------------------------------------------------------------------
    /** \name Constructor and destructor */
    //-------------------------------------------------------------------------
    //@{
	%0();
	~%0();
	//@}

private:

	§

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "%0.inl"
#endif

#endif // __%0_h_

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


.CPP file definition using selection:
/*------------------------------------------------------------------------------*/
/** 
 *  \file  %0.cpp
 *  \brief Implementation of class \c %0
 *  \author Gabriel Peyré %DATE%
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) %0.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "%0.h"

#ifndef OR_USE_INLINE
	#include "%0.inl"
#endif

using namespace OR;

§


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


.INL file definition using selection:
/*------------------------------------------------------------------------------*/
/** 
 *  \file  %0.inl
 *  \brief Inlined methods for \c %0
 *  \author Gabriel Peyré %DATE%
 */ 
/*------------------------------------------------------------------------------*/

#include "%0.h"

namespace OR {

§

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


Method comment using selection:

/*------------------------------------------------------------------------------*/
/** 
 * Name : %0
 *
 *  \author Gabriel Peyré %DATE%
 *
 *	AddCommentHere
 */ 
/*------------------------------------------------------------------------------*/
%0
{
	§
}

Class definition using selection:

/*------------------------------------------------------------------------------*/
/** 
 *  \class  %0
 *  \brief  CommentHere
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	CommentHere
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API %0
{
public:

    //-------------------------------------------------------------------------
    /** \name Constructor and destructor */
    //-------------------------------------------------------------------------
    //@{
	%0();
	~%0();
	//@}

private:

	§

};

#ifndef using selection:
#ifdef %1
	%0
#endif

Group block using selection:
//-------------------------------------------------------------------------
/** \name § */
//-------------------------------------------------------------------------
//@{
%0
//@}
