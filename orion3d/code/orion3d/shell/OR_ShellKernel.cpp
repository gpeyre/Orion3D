/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellKernel.cpp
 *  \brief Definition of class \c OR_ShellKernel
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ShellKernel.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"

#include "OR_ShellKernel.h"
#include "OR_ShellConsole_ABC.h"
#include "OR_ShellKernelManager.h"
#include "OR_ShellObject_ABC.h"

#ifndef OR_USE_INLINE
	#include "OR_ShellKernel.inl"
#endif



using namespace OR;

OR_ShellKernel* OR_ShellKernel::pStaticThis_ = NULL;




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel constructor
 *
 *  \param  RootObject_ the root of the hierarchy.
 *  \author Gabriel Peyré 2001-11-15
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellKernel::OR_ShellKernel(OR_ShellObject_ABC& RootObject_, OR_String& RootName)
:	pCurrentConsole_( NULL ),
	fQuitFunc_		( Default_Quit_Func )

{
	Pwd_.push_back( &RootObject_ );
	RootObject_.SetShellName(RootName);

	/* construct the datas for the next current object */
	this->GetCurrentObject().BuildSonList(SonList_);
	this->RegisterFuncDecl();

	/* declare the top level functions */
	this->BuildFuncDeclList( TopFuncDeclList_ );
	for( IT_ShellFuncDeclList it = TopFuncDeclList_.begin(); it!=TopFuncDeclList_.end(); ++it )
	{
		OR_ShellFuncDecl* pDecl = *it;
		WrapperLUA_.RegisterFunc( pDecl->GetFunc(), pDecl->GetFuncName().const_val() );
	}
	
	/* compute the new pwd string */
	this->ComputePwdString();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel constructor
 *
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellKernel::OR_ShellKernel()
:	pCurrentConsole_( NULL )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel destructor
 *
 *  \author Gabriel Peyré 2001-11-15
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellKernel::~OR_ShellKernel()
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ExecuteCmdCd
 *
 *  \param  name the name of the directory to go to.
 *  \return was the command successful.
 *  \author Gabriel Peyré 2001-11-15
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellKernel::ExecuteCmdCd(const OR_String& name)
{
	OR_ASSERT( !Pwd_.empty() );

	OR_StringTokenizer path(name, OR_String("//") );

	while( path.hasMoreTokens() )
	{		
		/* next directory in the path */
		OR_String rep = path.nextToken();
		if( !(rep==OR_String("")) )
		{
			/* try to make a cd in this directory */
			OR_Bool bIsSucces = this->ExecuteCmdCdSingle( rep );
			if( !bIsSucces )
			{
				pCurrentConsole_->Display( OR_String("error : cd : object " + rep + OR_String(" doesn't exist.\n") ) );
				return false;
			}
		}
	}
	return true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ExecuteCmdCdSingle
 *
 *  \param  name name of the directory.
 *  \return was the cd successfull ?
 *  \author Gabriel Peyré 2001-11-22
 *
 *	make a cd command into a \e single directory.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellKernel::ExecuteCmdCdSingle(const OR_String& name)
{
	OR_ASSERT( !Pwd_.empty() );
	
	/* the current directory */
	OR_ShellObject_ABC& CurObj = this->GetCurrentObject();
	
	/* treat the '.' directory */
	if( name == "." )
		return true;

	/* treat the '..' directory first */
	if( name == ".." )
	{
		/* check that we are not on the root */
		if( this->GetPwdLength()==1 )
			return false;
		
		/* free datas for the current object name and function */
		CurObj.ResetName();
		this->ResetShellObjectName(SonList_);
		this->UnRegisterFuncDecl();
		
		/* make a 'cd ..' in the path */
		Pwd_.pop_back();
		
		/* construct the datas for the next current object */
		SonList_.clear();
		this->GetCurrentObject().BuildSonList(SonList_);
		this->RegisterFuncDecl();
		
		/* compute the new pwd string */
		this->ComputePwdString();
		
		return true;
	}


	/* get the list of the son's of the object */
	SonList_.clear();
	CurObj.BuildSonList(SonList_);
	
	for( IT_ShellObjectList it=SonList_.begin(); it!=SonList_.end(); ++it )
	{
		OR_ShellObject_ABC* pObj = *it;
		if( pObj->GetShellObjectName() == name )
		{
			
			/* we have found the directory we want to go to */			
			Pwd_.push_back( pObj );
			
			/* reset the name of each object EXCEPT the one that are in the path */
			this->ResetShellObjectName(SonList_);
			/* free the datas for the previous current object */
			this->UnRegisterFuncDecl();
			
			/* construct the datas for the new current object */
			SonList_.clear();
			this->GetCurrentObject().BuildSonList(SonList_);
			this->RegisterFuncDecl();
			
			/* compute the new pwd string */
			this->ComputePwdString();
			
			return true;
		}
	}
	
	return false;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::void	
 *
 *  \param  name the name of the command to display help about (pass "" for complete help).
 *  \return A string giving explanations about the commands.
 *  \author Gabriel Peyré 2001-11-22
 */ 
/*------------------------------------------------------------------------------*/
OR_String OR_ShellKernel::ExecuteCmdHelp(const OR_String& name)
{
	OR_String HelpString;
	OR_U32 nMaxFuncNameLength = this->ComputeMaxFuncNameLength();
	
	if( name=="" )
	{
		IT_ShellFuncDeclList it;
		/* print a complete help first for top level functions */
		for( it = TopFuncDeclList_.begin(); it!=TopFuncDeclList_.end(); ++it )
		{
			if( it!=TopFuncDeclList_.begin() )
				HelpString += "\n";

			OR_ShellFuncDecl* pDecl = *it;
			HelpString += pDecl->GetFuncName();
			/* fill with blanks */
			OR_U32 nDeltaLength = nMaxFuncNameLength-pDecl->GetFuncName().length()+1;
			OR_ASSERT( nDeltaLength>0 );
			for( OR_U32 i=0; i<nDeltaLength; ++i )
				HelpString += " ";
			HelpString += ": " + pDecl->GetFuncDesc();
		}
		/* then for additional functions */
		for( it = FuncDeclList_.begin(); it!=FuncDeclList_.end(); ++it )
		{
			if( !(it==FuncDeclList_.begin() && TopFuncDeclList_.empty()) )
				HelpString += "\n";
			
			OR_ShellFuncDecl* pDecl = *it;
			HelpString += pDecl->GetFuncName();
			/* fill with blanks */
			OR_U32 nDeltaLength = nMaxFuncNameLength-pDecl->GetFuncName().length()+1;
			OR_ASSERT( nDeltaLength>0 );
			for( OR_U32 i=0; i<nDeltaLength; ++i )
				HelpString += " ";
			HelpString += ": " + pDecl->GetFuncDesc();
		}
	}
	else
	{
		/* print a help for each function asked */
		OR_StringTokenizer st(name, " ");
		while( st.hasMoreElements() )
		{
			OR_String FuncName = st.nextToken();
			OR_ShellFuncDecl* pDecl = this->GetFuncByName( FuncName );
			if( pDecl==NULL )
			{
				/* the function is not declared */
				HelpString += "Function " + FuncName + " doesn't exist.";
			}
			else
			{
				HelpString += pDecl->GetFuncName();
				/* fill with blanks */
				OR_U32 nDeltaLength = nMaxFuncNameLength-pDecl->GetFuncName().length()+1;
				for( OR_U32 i=0; i<nDeltaLength; ++i )
					HelpString += " ";
				HelpString += ": " + pDecl->GetFuncDesc();
			}

			if( st.hasMoreElements() )
				HelpString += "\n";
		}
	}
	
	return HelpString;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::GetFuncByName
 *
 *  \param  name the name of the function.
 *  \return the function, NULL if it does not exist.
 *  \author Gabriel Peyré 2001-11-22
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellFuncDecl* OR_ShellKernel::GetFuncByName(const OR_String& name)
{
	IT_ShellFuncDeclList it;

	for( it = FuncDeclList_.begin(); it!=FuncDeclList_.end(); ++it )
	{
		OR_ShellFuncDecl* pDecl = *it;
		if( pDecl->GetFuncName()==name )
			return pDecl;
	}
	for( it = TopFuncDeclList_.begin(); it!=TopFuncDeclList_.end(); ++it )
	{
		OR_ShellFuncDecl* pDecl = *it;
		if( pDecl->GetFuncName()==name )
			return pDecl;
	}

	return NULL;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ComputeMaxFuncNameLength
 *
 *  \return the maximum length of the names of the functions.
 *  \author Gabriel Peyré 2001-11-22
 */ 
/*------------------------------------------------------------------------------*/
OR_U32 OR_ShellKernel::ComputeMaxFuncNameLength()
{
	OR_U32 nLength = 0;
	IT_ShellFuncDeclList it;

	for( it = FuncDeclList_.begin(); it!=FuncDeclList_.end(); ++it )
	{
		OR_ShellFuncDecl* pDecl = *it;
		nLength = OR_MAX( nLength, pDecl->GetFuncName().length() );
	}
	for( it = TopFuncDeclList_.begin(); it!=TopFuncDeclList_.end(); ++it )
	{
		OR_ShellFuncDecl* pDecl = *it;
		nLength = OR_MAX( nLength, pDecl->GetFuncName().length() );
	}
	
	return nLength;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ResetShellObjectName
 *
 *	\param SonList the object to remove
 *  \author Gabriel Peyré 2001-11-15
 *
 * reset the name of each object EXCEPT the object that are in the path.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::ResetShellObjectName(T_ShellObjectList& SonList)
{
	for( IT_ShellObjectList it = SonList.begin(); it!=SonList.end(); ++it )
	{
		OR_ShellObject_ABC* pObj = *it;
		/* don't reset the name of the next directory, since we book keep it's name for the pwd */
		if( !(this->IsInPwd(*pObj)) )
			pObj->ResetName();
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ExecuteCmdPwd
 *
 *  \return a string representing the pwd.
 *
 *  \author Gabriel Peyré 2001-11-15
 */ 
/*------------------------------------------------------------------------------*/
OR_String& OR_ShellKernel::ExecuteCmdPwd()
{
	return PwdString_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ExecuteCmdAbout
 *
 *  \return create an about string.
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
OR_String OR_ShellKernel::ExecuteCmdAbout()
{
	OR_String AboutString = "Orion3D shell [v" + OR_String( (OR_U32) OR_SHELL_MAJOR_VERSION) + "." + OR_String( (OR_U32) OR_SHELL_MINOR_VERSION) + "]\n";
	AboutString += "www.orion3d.fr.st\n";
	AboutString += "'help' : print the list of available functions.\n";
	AboutString += "----";

	return AboutString;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ComputePwdString
 *
 *  \author Gabriel Peyré 2001-11-15
 *
 *	Compute the string representing the pwd.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::ComputePwdString()
{
	PwdString_.clear();
	
	for( IT_ShellObjectList it=Pwd_.begin(); it!=Pwd_.end(); ++it   )
	{
		OR_ShellObject_ABC* pObj = *it;
		PwdString_ += pObj->GetShellObjectName();
		PwdString_ += OR_String("/");
	}
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ExecuteCmdLs
 *
 *  \param  name the name of the directory where we want to perform the ls ("" if current directory).
 *  \author Gabriel Peyré 2001-11-17
 *
 *	First search for the object where we want to make the ls, and then compute
 *	the ls string.
 */ 
/*------------------------------------------------------------------------------*/
OR_String& OR_ShellKernel::ExecuteCmdLs(const OR_String& name)
{
	OR_ShellObject_ABC* pTargetObj = &this->GetCurrentObject();
	LsString_.clear();

	/* add current directory to path */
	LsString_ += OR_String( "./  " );
	/* add father directory to path */
	if( this->GetPwdLength()>1 )
		LsString_ += "../  ";
	
	if( !(name==OR_String("")) )
	{
		/* determine the node on wich the LS take place */
		pTargetObj = this->DirectAccessObject( OR_String(name) );
		if( pTargetObj==NULL )
		{
			LsString_ = OR_String("Error, can't find '") + OR_String(name) + OR_String("'.");
			return LsString_;
		}
	}
	
	/* get the list of the son's of the object */
	T_ShellObjectList TargetSonList;
	TargetSonList.clear();
	pTargetObj->BuildSonList(TargetSonList);
	
	/* build the ls string */
	for( IT_ShellObjectList it=TargetSonList.begin(); it!=TargetSonList.end(); it++ )
	{
		OR_ShellObject_ABC* pObj = *it;
		LsString_ += pObj->GetShellObjectName();
		LsString_ += "/  ";
	}
	
	/* reset the name of each object EXCEPT those in the pwd */
	this->ResetShellObjectName( TargetSonList );
	
	/* remove the data used by the son list */
	TargetSonList.clear();
	
	return LsString_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::IsInPwd	
 *
 *  \param  Obj the object to test.
 *  \return is the object in the pwd ?
 *  \author Gabriel Peyré 2001-11-15
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool	OR_ShellKernel::IsInPwd(OR_ShellObject_ABC& Obj)
{
	for( IT_ShellObjectList it=Pwd_.begin(); it!=Pwd_.end(); ++it )
	{
		if( &Obj==(*it) )
			return true;
	}

	return false;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellObject_ABC::ResetSonList
 *
 *  \author Gabriel Peyré 2001-11-14
 *
 *	Free the space occuped by the object son's list.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::ResetSonList()
{
	SonList_.clear();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellObject_ABC::ResetFuncDeclList
 *
 *  \author Gabriel Peyré 2001-11-17
 *
 *	Free the space used by the list of functions proposed by the object.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::ResetFuncDeclList()
{
	/* delete each function declaration */
	for(IT_ShellFuncDeclList it = FuncDeclList_.begin(); it!=FuncDeclList_.end(); ++it)
	{
		OR_ShellFuncDecl* pDecl = *it;
		OR_ASSERT( pDecl!=NULL );
		OR_DELETE( pDecl )
	}

	FuncDeclList_.clear();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::DoString
 *
 *  \param  cmd the command line.
 *  \param  console the console to output the result.
 *  \author Gabriel Peyré 2001-11-17
 *
 *	Interpret the line, and then either :
 *		- make a 'cd','ls','pwd' or 'help'
 *		- call the \b LUA interpreter to execute an object defined function.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::DoString(OR_String& cmd, OR_ShellConsole_ABC& console)
{
	
	/* equivalent to str = st.getNextToken(); but skipping empty token */
	#define GET_NEXT_TOKEN_AND_SKIP_BLANK( st, str )	\
	while( st.hasMoreTokens() && str=="" )				\
		str = st.nextToken();							\
	if( str=="" ) return

	pCurrentConsole_ = &console;
	
	OR_StringTokenizer st(cmd, OR_String(" "));
	OR_String First = "";

	GET_NEXT_TOKEN_AND_SKIP_BLANK(st, First);

	/* first thing to do : tell we are the current manager, for top level fucntion */
	this->SetStaticThis();

	/* check if a cd/ls/pwd command is called */
	if( First=="ls" )
	{
		OR_String Res;

		if( st.countTokens()>0 )
		{
			OR_String target;
			GET_NEXT_TOKEN_AND_SKIP_BLANK(st, target);
			Res = this->ExecuteCmdLs( target );
		}
		else
		{
			Res = this->ExecuteCmdLs( OR_String("") );
		}
		console.Display( Res );
	}
	else if( First=="cd" )
	{
		if( st.countTokens()>0 )
		{
			OR_String target;
			GET_NEXT_TOKEN_AND_SKIP_BLANK(st, target);
			if( target=="" )
				console.Display(OR_String("error : cd : no enough arguments.\n"));
			else
				this->ExecuteCmdCd( target );
		}
		else
		{
			/* no enough arguments */
			console.Display(OR_String("error : cd : no enough arguments.\n"));
		}
	}
	else if( First=="pwd" )
	{
		if( st.countTokens()>0 )
		{
			/* to much arguments */
			console.Display(OR_String("error : pwd : too much arguments."));
		}
		else
		{
			OR_String Res = this->ExecuteCmdPwd();
			console.Display( Res );
		}
	}
	else if( First=="help" )
	{
		OR_String Res;
		
		if( st.countTokens()>0 )
		{
			OR_String target;
			while( st.hasMoreTokens() )
				target += st.nextToken();
			Res = this->ExecuteCmdHelp( target );
		}
		else
		{
			Res = this->ExecuteCmdHelp( OR_String("") );
		}
		console.Display( Res );
	}
	else if( First=="about" )
	{
		if( st.countTokens()>0 )
		{
			/* to much arguments */
			console.Display(OR_String("error : about : too much arguments."));
		}
		else
		{
			OR_String Res = this->ExecuteCmdAbout();
			console.Display( Res );
		}
	}
	else if( First=="quit" )
	{
		if( fQuitFunc_() != 0 )
			console.Display( OR_String("You can't exit now.") );
	}
	else
	{
		WrapperLUA_.DoString( cmd.const_val() );
	}

	if( !(First=="cd") )
		console.Display( OR_String("\n") );

	pCurrentConsole_ = NULL;

	#undef GET_NEXT_TOKEN_AND_SKIP_BLANK
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::TryCompletion
 *
 *  \param  orignal the string to complete.
 *  \param  completed the string that has been completed.
 *  \param  suggestion a suggestion if the completion was not possible.
 *  \return was the completion a success ?
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellKernel::TryCompletion(OR_String& orignal, OR_String& completed, OR_String& suggestion)
{
	/* equivalent to str = st.getNextToken(); but skipping empty token */
	#define GET_NEXT_TOKEN_AND_SKIP_BLANK( st, str )	\
	while( st.hasMoreTokens() && str=="" )				\
		str = st.nextToken();							\
	if( str=="" ) return false;

	/* count the number of non empty token */
	OR_StringTokenizer st1( orignal, OR_String(" ") );
	OR_U32 nNbrToken = 0;
	while( st1.hasMoreTokens() )
	{
		if( !(st1.nextToken()==OR_String("")) )
			nNbrToken++;
	}

	OR_StringTokenizer st( orignal, OR_String(" ") );

	#define NOT_MATCHING completed  = orignal; suggestion = OR_String(""); return false

	if( nNbrToken==0 )
	{
		/* the string is empty */
		NOT_MATCHING;
	}
	else if( nNbrToken==1 )
	{
		OR_String FuncName;
		GET_NEXT_TOKEN_AND_SKIP_BLANK( st, FuncName );
		/* try to find the name of the function */
		OR_Bool bRes =  this->TryCompletionFunction(FuncName, completed, suggestion);
		/* check if we have make an improvement, if so, don't make suggestion ! */
		if( !(completed == orignal) )
			suggestion = OR_String("");
		return bRes;
	}
	else if( nNbrToken==2 )
	{
		/* try to complete the function arguments */
		OR_String FuncName;
		OR_String FuncArg;
		GET_NEXT_TOKEN_AND_SKIP_BLANK( st, FuncName );
		GET_NEXT_TOKEN_AND_SKIP_BLANK( st, FuncArg );

		/* check if a cd/ls/pwd command is called */
		if( FuncName=="ls" || FuncName=="cd" )
		{
			/* try to find the target directory */
			OR_StringTokenizer StArg( FuncArg, "/" );
			if( StArg.countTokens()==0 )
			{
				/* no directoty specified. should not happend */
				OR_ASSERT( false );
				NOT_MATCHING;
			}
			else if( StArg.countTokens()==1 )
			{
				OR_String BeginObjName = StArg.nextToken();
				/* try to complete the name of the directory */
				OR_Bool bSuccess = this->TryCompletionObject( BeginObjName, completed, suggestion );
				if( bSuccess && !(completed == BeginObjName) )
				{
					/* we have make an improvement, so don't make suggestion ! */
					suggestion = OR_String("");
					/* a completion was made for the target dir, rebuild the whole string */
					completed = FuncName + " " + completed;
				}
				return bSuccess;
			}
			else
			{
				/* for the moment, we are only able to complete one directory ... */
				NOT_MATCHING;
			}			
		}
		else if( FuncName=="help" )
		{
			OR_String FuncName;
			GET_NEXT_TOKEN_AND_SKIP_BLANK( st, FuncName );
			/* try to find the name of the function */
			return this->TryCompletionFunction( FuncName, completed, suggestion );
		}
		else
		{	
			/* pwd, about and other have no completion */
			NOT_MATCHING;
		}
	}
	else
	{
		/* too much arguments */
		NOT_MATCHING;
	}

	#undef NOT_MATCHING
	#undef GET_NEXT_TOKEN_AND_SKIP_BLANK
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ListFuncBeginingWith
 *
 *  \param  FuncList output the list of function whose names begins with given string
 *	\param	name begining of the name.
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::ListFuncBeginingWith(T_StringList& FuncList, OR_String& name)
{
	IT_ShellFuncDeclList it;

	for( it = FuncDeclList_.begin(); it!=FuncDeclList_.end(); ++it )
	{
		OR_ShellFuncDecl* pDecl = *it;
		if( pDecl->GetFuncName().startsWith(name) )
			FuncList.push_back( &pDecl->GetFuncName() );
	}
	for( it = TopFuncDeclList_.begin(); it!=TopFuncDeclList_.end(); ++it )
	{
		OR_ShellFuncDecl* pDecl = *it;
		if( pDecl->GetFuncName().startsWith(name) )
			FuncList.push_back( &pDecl->GetFuncName() );
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ListObjBeginingWith
 *
 *  \param  ObjList the list of object matching the begining of the name
 *  \param  name the begining of the name of the object.
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::ListObjBeginingWith(T_StringList& ObjList, OR_String& name)
{
	SonList_.clear();
	this->GetCurrentObject().BuildSonList( SonList_ );

	for( IT_ShellObjectList it = SonList_.begin(); it!=SonList_.end(); ++it )
	{
		OR_ShellObject_ABC* pObj = *it;
		if( pObj->GetShellObjectName().startsWith(name) )
			ObjList.push_back( &pObj->GetShellObjectName() );
	}
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::FindCommonBegining
 *
 *  \param  NameList a list of name.
 *  \param  CommonBegining returned value : a common begining for all string.
 *  \author Gabriel Peyré 2001-12-01
 *
 *	Find the common begining for a list of names.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::FindCommonBegining(T_StringList& NameList, OR_String& CommonBegining)
{
	CommonBegining = OR_String("");

	OR_U32 i =0;
	OR_Bool bIsOk = true;

	while( bIsOk )
	{
		char c;
		if( NameList.front()->length() <= i )
			break;
		
		c = NameList.front()->charAt( i );
		
		for( IT_StringList it = NameList.begin(); it!=NameList.end(); ++it )
		{
			OR_String* pStr = *it;
			
			if( (pStr->length() <= i) ||
				(pStr->charAt(i) != c) )
			{
				bIsOk = false;
				break;
			}
		}
		
		if( bIsOk )
			CommonBegining += OR_String(&c, 0, 1);
		i++;
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::TryCompletionFunction
 *
 *  \param  FuncName the begining of the name of a function
 *  \param  completed the complete name of the function (if possibe).
 *  \param  suggestion a sugssion list.
 *  \return was the completion a success ?
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellKernel::TryCompletionFunction(OR_String& FuncName, OR_String& completed, OR_String& suggestion)
{
	T_StringList PossibleFunc;
	/* try to complete the function name */
	this->ListFuncBeginingWith( PossibleFunc, FuncName );
	
	if( PossibleFunc.size()==0 )
	{
		/* no matching found */
		completed  = FuncName; 
		suggestion = OR_String(""); 
		return false;
	}
	else if( PossibleFunc.size()==1 )
	{
		/* one matching found : ok, make a completion ! */
		completed  = *PossibleFunc.front();
		suggestion = OR_String("");
		return true;
	}
	else
	{
		suggestion.clear();
		
		/* more than one func match : try to find a common begining for all string */
		this->FindCommonBegining( PossibleFunc, completed );
		
		/* make a suggestion list, in the case the common begining does not add anything */
		for( IT_StringList it = PossibleFunc.begin(); it!=PossibleFunc.end(); ++it )
		{
			if( it!=PossibleFunc.begin() )
				suggestion += "  ";
			suggestion += *(*it);
		}
		
		return true;
		suggestion.clear();
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::TryCompletionObject
 *
 *  \param  ObjName begining of the name of the son object.
 *  \param  completed the complete name (if possible).
 *  \param  suggestion a suggestion list.
 *  \return was the completion a success ?
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellKernel::TryCompletionObject(OR_String& ObjName, OR_String& completed, OR_String& suggestion)
{
	T_StringList PossibleObj;
				
	this->ListObjBeginingWith( PossibleObj, ObjName );
	/* make the */
	if( PossibleObj.size()==0 )
	{
		/* no matching found */
		
		completed  = ObjName; 
		suggestion = OR_String(""); 
		return false;;
	}
	else if( PossibleObj.size()==1 )
	{
		/* one matching found : ok, make a completion ! */
		completed  = *PossibleObj.front();
		suggestion = OR_String("");
		return true;
	}
	else
	{
		suggestion.clear();

		/* more than one func match : try to find a common begining for all string */
		this->FindCommonBegining( PossibleObj, completed );

		/* more than one func match : make a suggestion list */
		for( IT_StringList it = PossibleObj.begin(); it!=PossibleObj.end(); ++it )
		{
			if( it!=PossibleObj.begin() )
				suggestion += "  ";
			suggestion += *(*it);
		}
		return true;
	}
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::RegisterFuncDecl
 *
 *  \author Gabriel Peyré 2001-11-17
 *
 *	First get from the object all function that it defined.
 *	register to the \b LUA wrapper each function of the object.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::RegisterFuncDecl()
{
	/* get the functions */
	this->GetCurrentObject().BuildFuncDeclList( FuncDeclList_ );
	/* set up the static this for callbacks */
	this->GetCurrentObject().SetStaticThis();

	for( IT_ShellFuncDeclList it = FuncDeclList_.begin(); it!=FuncDeclList_.end(); ++it )
	{
		OR_ShellFuncDecl* pDecl = *it;
		WrapperLUA_.RegisterFunc( pDecl->GetFunc(), pDecl->GetFuncName().const_val() );
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::UnRegisterFuncDecl
 *
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	Register to the \b LUA wrapper each function of the object, then
 *	remove all function that the object defined.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::UnRegisterFuncDecl()
{
	for( IT_ShellFuncDeclList it = FuncDeclList_.begin(); it!=FuncDeclList_.end(); ++it )
	{
		OR_ShellFuncDecl* pDecl = *it;
		WrapperLUA_.UnRegisterFunc( pDecl->GetFuncName().const_val() );
	}

	/* remove the functions of the object */
	FuncDeclList_.clear();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::SetRootObject
 *
 *	\param	root the new root.
 *  \author Gabriel Peyré 2001-11-19
 *
 *	Set the root of the pwd. Reset all datas.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::SetRootObject(OR_ShellObject_ABC& root, OR_String& RootName)
{
	/* set the name of the root */
	root.SetShellName(RootName);
	/* reset all datas */
	Pwd_.clear();

	/* reset the name of each object EXCEPT the one that are in the path */
	this->ResetShellObjectName(SonList_);
	/* free the datas for the previous current object */
	this->ResetSonList();
	this->UnRegisterFuncDecl();

	Pwd_.push_back( &root );

	/* construct the datas for the next current object */
	SonList_.clear();
	this->GetCurrentObject().BuildSonList(SonList_);
	this->RegisterFuncDecl();	

	/* compute the new pwd string */
	this->ComputePwdString();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::GetNbrSubDir
 *
 *  \return the number of sub-directories of the current directory.
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
OR_U32 OR_ShellKernel::GetNbrSubDir()
{		
	return SonList_.size();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::GetSubDir	
 *
 *	\param	nNumSubDir the number of the sub-directory.
 *  \return the name of a given directory.
 *  \author Gabriel Peyré 2001-11-25
 */ 
/*------------------------------------------------------------------------------*/
OR_String OR_ShellKernel::GetSubDir(OR_U32 nNumSubDir)
{
	if( nNumSubDir>this->GetNbrSubDir() )
		return OR_String("");

	SonList_.clear();
	this->GetCurrentObject().BuildSonList( SonList_ );

	IT_ShellObjectList it = SonList_.begin();
	for( OR_U32 i=0; i<nNumSubDir; ++i )
	{
		OR_ASSERT(it!=SonList_.end());
		++it;
	}

	if( it!=SonList_.end() )
		return (*it)->GetShellObjectName();
	else
		return OR_String("");
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	OR_ADD_SHELL_FUNC(FuncDeclList, about, "Print an 'about' message.");
	OR_ADD_SHELL_FUNC(FuncDeclList, pwd, "Return te current pwd.");
	OR_ADD_SHELL_FUNC(FuncDeclList, cd, "Change of current directory.");
	OR_ADD_SHELL_FUNC(FuncDeclList, ls, "Return the sub-directories.");
	OR_ADD_SHELL_FUNC(FuncDeclList, help, "Print help message about additional functions.");
	OR_ADD_SHELL_FUNC(FuncDeclList, GetNbrSubDir, "Get the number of sub-directiries.");
	OR_ADD_SHELL_FUNC(FuncDeclList, GetSubDir, "Get the name of  given sub-directory.");
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::about
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::about(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( about, 0 );

	OR_SHELL_FUNC_PRINT(  OR_ShellKernel::GetStaticThis().ExecuteCmdAbout() );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::cd
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::cd(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( cd, 1 );
	
	OR_SHELL_ACCESS_AND_USE( cd, 1, String, TargetDir, OR_ShellKernel::GetStaticThis().ExecuteCmdCd(TargetDir); )
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::ls
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::ls(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( ls, 0 );
	
	OR_SHELL_FUNC_PRINT( OR_ShellKernel::GetStaticThis().ExecuteCmdLs( OR_String("") ) );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::pwd
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::pwd(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( pwd, 0 );
	
	OR_SHELL_FUNC_PRINT( OR_ShellKernel::GetStaticThis().ExecuteCmdPwd() );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::help
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::help(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( help, 1 );
	
	OR_SHELL_ACCESS_AND_USE( help, 1, String, TargetFunc,
		OR_SHELL_FUNC_PRINT( OR_ShellKernel::GetStaticThis().ExecuteCmdHelp(TargetFunc) );
	);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::GetNbrSubDir
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::GetNbrSubDir(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( GetNbrSubDir, 0 );
	
	stack.ReturnValueU32( OR_ShellKernel::GetStaticThis().GetNbrSubDir() );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::GetSubDir
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellKernel::GetSubDir(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( GetSubDir, 1 );
	
	OR_SHELL_ACCESS_AND_USE( GetSubDir, 1, Float, NumSubDir, 
		stack.ReturnValueString( OR_ShellKernel::GetStaticThis().GetSubDir(NumSubDir) ); )	
}



/*------------------------------------------------------------------------------
/** Name : OR_ShellConsole_ABC::Default_Quit_Func
 *
 *  \return Was the quit successful
 *  \author Antoine Bouthors 2001-12-03
 *------------------------------------------------------------------------------*/
OR_U32 OR_ShellKernel::Default_Quit_Func()
{
	exit(0);
	return OR_OK;
}


void OR_ShellKernel::BuildFromFile( OR_File& file )
{
	/** \todo fille the export functions */
}

void OR_ShellKernel::BuildToFile( OR_File& file )
{
	/** \todo fille the export functions */
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

