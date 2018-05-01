/*------------------------------------------------------------------------------*/
/** 
 *  \file  main.cpp
 *  \brief Main file for string test program.
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) main.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

/* tell that we are using the Orion3D dll */
#define ORION3D_IMPORTS

//-------------------------------------------------------------------------
/** \name orion3d file inclusion */
//-------------------------------------------------------------------------
//@{
/* this will check wich library we will need to use */
#include "../../orion3d/configuration/OR_Config.h"
#include "../../orion3d/utils/OR_String.h"
#include "../../orion3d/utils/OR_File.h"
#include "../../orion3d/utils/OR_StringTokenizer.h"
/* we want to avoid putting OR:: before each Orion3D beautifull class names */
using namespace OR;
//@}



/*------------------------------------------------------------------------------*/
/** 
 * Name : main 
 *
 *  \param  argc ...
 *  \param  argv ..
 *  \author Gabriel Peyré 2001-10-17
 *
 *	entry point for the application
 */ 
/*------------------------------------------------------------------------------*/
int main( int argc, char *argv[ ], char *envp[ ] )
{
	OR_String s("youhou yaha/yoho/");

	OR_File f;
	f.Open("test.txt", "wb");
	f << OR_String("this is a test !");
	f << OR_String(" youhou ...");
	f.Close();

	OR_String test;
	f.Open("test.txt", "rb");

	f >> test;
	f >> test;
	test += "mama";
	test += "ce";
	test += "ae";

	s += 2;
	OR_Bool test2 = s == "toto";
	OR_StringTokenizer st(s, " ");
	int nbr_tok = st.countTokens();
	
	OR_String lhs;
	OR_String rhs;
	
	if( st.hasMoreTokens() )
	{
		lhs = st.nextToken();
		
		if(st.hasMoreTokens())
		{
			rhs = st.nextToken();
			OR_StringTokenizer path(rhs, "/");
			while (path.hasMoreTokens())
			{
				OR_String rep = path.nextToken();
				rep.dump();
			}
			
		}
	}
	
	return 0;
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