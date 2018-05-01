/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_TopographicFunction.cpp
 *  \brief  Definition of class \c FSW_TopographicFunction
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_TopographicFunction.cpp (c) Gabriel Peyré & Antoine Bouthors 2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_TopographicFunction.h"

#ifndef FSW_USE_INLINE
    #include "FSW_TopographicFunction.inl"
#endif

using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction:: LoadFromFile
/**
 *  \param  aFileAdress [char*] the adress of the file.
 *	\param	aMode The mode in wich the file should be opened (e.g. 'rb' for binary or 'rt' for ASCII).
 *	\param	aType The type of the data. Should be : 
 *		- U16 : 16 bit unsignet int.
 *		- I16 : 16 bit signed int.
 *		- U32 : 32 bit unsignet int.
 *		- I32 : 32 bit signed int.
 *		- Float : 32 bit float.
 *		- Double : 64 bit float.
 *  \return [FSW_Bool] Was the loading successful ?
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 * 
 *  Load the data from a file to the array.
 */
/*------------------------------------------------------------------------------*/
FSW_RETURN_CODE FSW_TopographicFunction::LoadFromFile(const char* aFileAdress, 
                                               FSW_U32 uLongPrec,
											   FSW_U32 uLatPrec,
											   const char* aMode, const char* aType)
{
	FSW_U32 uNbrRead = -1;
	FSW_U32 uNbrToRead = uLongPrec*uLatPrec;
	FILE* pHandle = fopen(aFileAdress, aMode);
	if( pHandle==NULL )
		return FSW_Error_Opening_File;
	void* pTmpArray = NULL;

	/* check for the type of the data */
	#define LOAD_DATA(type)	if( strcmp(aType, #type )==0 )							\
	{	pTmpArray = new FSW_##type[uNbrToRead];										\
		uNbrRead = (FSW_U32) fread( pTmpArray, sizeof( FSW_##type ), uNbrToRead, pHandle ); }	
	LOAD_DATA( U16 )
	LOAD_DATA( U32 )
	LOAD_DATA( I16 )
	LOAD_DATA( I32 )
	LOAD_DATA( Float )
	#undef LOAD_DATA

	/* check everything was read */
	if( uNbrRead!=uNbrToRead )
		FSW_DELETEARRAY(pTmpArray);
	if( pTmpArray==NULL )
		return FSW_Error_Opening_File;

    if( aData_!=NULL )
		FSW_DELETEARRAY(aData_);
	/* convert the data to float */
	aData_ = new FSW_Float[uNbrRead];
	aSize_[X] = uLongPrec;
	aSize_[Y] = uLatPrec;

	rMin_ = 1e10;
	rMax_ = -1e10;


	if( strcmp(aType, "I16")==0 )						
	{	
		FSW_I16* pArray = (FSW_I16*) pTmpArray;
		for( FSW_U32 i=0; i<uNbrRead; ++i )	
		{	
			aData_[i] = (FSW_Float) pArray[i];
			if(aData_[i]>rMax_) rMax_=aData_[i];										
			if(aData_[i]<rMin_) rMin_=aData_[i]; 
		} 
	}
	if( strcmp(aType, "U16")==0 )
	{	
		FSW_U16* pArray = (FSW_U16*) pTmpArray;
		for( FSW_U32 i=0; i<uNbrRead; ++i )	
		{	
			aData_[i] = (FSW_Float) pArray[i];
			if(aData_[i]>rMax_) rMax_=aData_[i];										
			if(aData_[i]<rMin_) rMin_=aData_[i]; 
		} 
	}

	/* copy in final destination */
	#define COPY_DATA(type) if( strcmp(aType, #type)==0 )							\
	{	for( FSW_U32 i=0; i<uNbrRead; ++i )	{										\
		aData_[i] = (FSW_Float) ((FSW_##type*) pTmpArray)[i];						\
		if(aData_[i]>rMax_) rMax_=aData_[i];										\
		if(aData_[i]<rMin_) rMin_=aData_[i]; } }
//	COPY_DATA( U16 )
	COPY_DATA( U32 )
//	COPY_DATA( I16 )
	COPY_DATA( I32 )
	COPY_DATA( Float )
	#undef COPY_DATA

	FSW_DELETEARRAY(pTmpArray);

	return FSW_True;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction::ScaleTo
/**
 *  \param  rMin [FSW_Float] New minimum of the function.
 *  \param  rMax [FSW_Float] New maximum of the function.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Scale the data so that it fit in the given range.
 */
/*------------------------------------------------------------------------------*/
void FSW_TopographicFunction::ScaleTo(FSW_Float rMin, FSW_Float rMax)
{
	if( aData_==NULL )
		return;
	for( FSW_U32 i=0; i<aSize_[X]; ++i )
	for( FSW_U32 j=0; j<aSize_[Y]; ++j )
	{
		FSW_Float rVal = this->AccessData( i,j );
		rVal = rMin + (rVal-rMin_)*(rMax-rMin)/(rMax_-rMin_);
		this->SetData(rVal, i,j);
	}

	rMin_ = rMin;
	rMax_ = rMax;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_TopographicFunction::LoadFromImage
/**
 *  \param   File [char*] The adress of the image file.
 *  \return [FSW_RETURN_CODE] Was the loading succesfull ?
 *  \author Gabriel Peyré
 *  \date   10-29-2002
 * 
 *  Load the data from an image, using DevIl lib.
 */
/*------------------------------------------------------------------------------*/
FSW_RETURN_CODE FSW_TopographicFunction::LoadFromImage( const char * File )
{
	ILuint Error;
	ILuint nImageNum;

	/* this should be done only once ... but it's convenient to put it here. */
	ilInit();

	ilGenImages(1, &nImageNum);
	ilBindImage(nImageNum);

	/* check for error */
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
		return FSW_ERROR;
	ilLoadImage(File);
	/* check for error */
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
		return FSW_ERROR;

	ILubyte* pData = ilGetData();
	FSW_ASSERT( pData!=NULL );
	ILint Components	= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL); ;
	ILint Type			= ilGetInteger(IL_IMAGE_TYPE);
	ILint Format		= ilGetInteger(IL_IMAGE_FORMAT);	
	ILint Width			= ilGetInteger(IL_IMAGE_WIDTH);
	ILint Height		= ilGetInteger(IL_IMAGE_HEIGHT);	

	FSW_DELETEARRAY(aData_);
	/* convert the data to float */
	aData_ = new FSW_Float[Width*Height];
	aSize_[X] = Width;
	aSize_[Y] = Height;

	FSW_U32 DataSize;
	switch(Type) 
	{
	case GL_UNSIGNED_BYTE:
		DataSize = sizeof(GLubyte);
		break;
	case GL_BYTE:
		DataSize = sizeof(GLbyte);
		break;
	case GL_UNSIGNED_SHORT:
		DataSize = sizeof(GLushort);
		break;
	case GL_SHORT:
		DataSize = sizeof(GLshort);
		break;
	case GL_UNSIGNED_INT:
		DataSize = sizeof(GLuint);
		break;
	case GL_INT:
		DataSize = sizeof(GLint);
		break;
	case GL_FLOAT:
		DataSize = sizeof(GLfloat);
		break;
	default:
		ilDeleteImages(1, &nImageNum);
		return FSW_ERROR;
	}

	/* copy the image (1st component) in the array */
	FSW_U32 nPos = 0;
	for( FSW_I32 i=0; i<Height*Width; ++i )
	{
		FSW_Float rVal = pData[nPos];
		aData_[i] = rVal;
		if(rVal>rMax_) rMax_ = rVal;										
		if(rVal<rMin_) rMin_ = rVal; 
		nPos += DataSize*Components;
	}
	
	ilDeleteImages(1, &nImageNum);
	return FSW_OK;
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2002 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
