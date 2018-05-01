/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_TopographicFunction.cpp
 *  \brief  Definition of class \c GW_TopographicFunction
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_TopographicFunction.cpp (c) Gabriel Peyré & Antoine Bouthors 2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_TopographicFunction.h"

#ifndef GW_USE_INLINE
    #include "GW_TopographicFunction.inl"
#endif

using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction:: LoadFromFile
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
 *  \return [GW_Bool] Was the loading successful ?
 *  \author Gabriel Peyré
 *  \date   10-26-2002
 * 
 *  Load the data from a file to the array.
 */
/*------------------------------------------------------------------------------*/
GW_RETURN_CODE GW_TopographicFunction::LoadFromFile(const char* aFileAdress, 
                                               GW_U32 uLongPrec,
											   GW_U32 uLatPrec,
											   const char* aMode, const char* aType)
{
	GW_U32 uNbrRead = -1;
	GW_U32 uNbrToRead = uLongPrec*uLatPrec;
	FILE* pHandle = fopen(aFileAdress, aMode);
	if( pHandle==NULL )
		return GW_Error_Opening_File;
	void* pTmpArray = NULL;

	/* check for the type of the data */
	#define LOAD_DATA(type)	if( strcmp(aType, #type )==0 )							\
	{	pTmpArray = new GW_##type[uNbrToRead];										\
		uNbrRead = (GW_U32) fread( pTmpArray, sizeof( GW_##type ), uNbrToRead, pHandle ); }	
	LOAD_DATA( U16 )
	LOAD_DATA( U32 )
	LOAD_DATA( I16 )
	LOAD_DATA( I32 )
	LOAD_DATA( Float )
	#undef LOAD_DATA

	/* check everything was read */
	if( uNbrRead!=uNbrToRead )
		GW_DELETEARRAY(pTmpArray);
	if( pTmpArray==NULL )
		return GW_Error_Opening_File;

    if( aData_!=NULL )
		GW_DELETEARRAY(aData_);
	/* convert the data to float */
	aData_ = new GW_Float[uNbrRead];
	aSize_[X] = uLongPrec;
	aSize_[Y] = uLatPrec;

	rMin_ = 1e10;
	rMax_ = -1e10;


	if( strcmp(aType, "I16")==0 )						
	{	
		GW_I16* pArray = (GW_I16*) pTmpArray;
		for( GW_U32 i=0; i<uNbrRead; ++i )	
		{	
			aData_[i] = (GW_Float) pArray[i];
			if(aData_[i]>rMax_) rMax_=aData_[i];										
			if(aData_[i]<rMin_) rMin_=aData_[i]; 
		} 
	}
	if( strcmp(aType, "U16")==0 )
	{	
		GW_U16* pArray = (GW_U16*) pTmpArray;
		for( GW_U32 i=0; i<uNbrRead; ++i )	
		{	
			aData_[i] = (GW_Float) pArray[i];
			if(aData_[i]>rMax_) rMax_=aData_[i];										
			if(aData_[i]<rMin_) rMin_=aData_[i]; 
		} 
	}

	/* copy in final destination */
	#define COPY_DATA(type) if( strcmp(aType, #type)==0 )							\
	{	for( GW_U32 i=0; i<uNbrRead; ++i )	{										\
		aData_[i] = (GW_Float) ((GW_##type*) pTmpArray)[i];						\
		if(aData_[i]>rMax_) rMax_=aData_[i];										\
		if(aData_[i]<rMin_) rMin_=aData_[i]; } }
//	COPY_DATA( U16 )
	COPY_DATA( U32 )
//	COPY_DATA( I16 )
	COPY_DATA( I32 )
	COPY_DATA( Float )
	#undef COPY_DATA

	GW_DELETEARRAY(pTmpArray);

	return GW_True;
}

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::ScaleTo
/**
 *  \param  rMin [GW_Float] New minimum of the function.
 *  \param  rMax [GW_Float] New maximum of the function.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Scale the data so that it fit in the given range.
 */
/*------------------------------------------------------------------------------*/
void GW_TopographicFunction::ScaleTo(GW_Float rMin, GW_Float rMax)
{
	if( aData_==NULL )
		return;
	for( GW_U32 i=0; i<aSize_[X]; ++i )
	for( GW_U32 j=0; j<aSize_[Y]; ++j )
	{
		GW_Float rVal = this->AccessData( i,j );
		rVal = rMin + (rVal-rMin_)*(rMax-rMin)/(rMax_-rMin_);
		this->SetData(rVal, i,j);
	}

	rMin_ = rMin;
	rMax_ = rMax;
}

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::LoadFromImage
/**
 *  \param   File [char*] The adress of the image file.
 *  \return [GW_RETURN_CODE] Was the loading succesfull ?
 *  \author Gabriel Peyré
 *  \date   10-29-2002
 * 
 *  Load the data from an image, using DevIl lib.
 */
/*------------------------------------------------------------------------------*/
GW_RETURN_CODE GW_TopographicFunction::LoadFromImage( const char * File )
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
		return GW_ERROR;
	ilLoadImage( ILstring(File) );
	/* check for error */
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
		return GW_ERROR;

	ILubyte* pData = ilGetData();
	GW_ASSERT( pData!=NULL );
	ILint Components	= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL); ;
	ILint Type			= ilGetInteger(IL_IMAGE_TYPE);
	ILint Format		= ilGetInteger(IL_IMAGE_FORMAT);	
	ILint Width			= ilGetInteger(IL_IMAGE_WIDTH);
	ILint Height		= ilGetInteger(IL_IMAGE_HEIGHT);	

	GW_DELETEARRAY(aData_);
	/* convert the data to float */
	aData_ = new GW_Float[Width*Height];
	aSize_[X] = Width;
	aSize_[Y] = Height;

	GW_U32 DataSize;
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
		return GW_ERROR;
	}

	/* copy the image (1st component) in the array */
	GW_U32 nPos = 0;
	for( GW_I32 i=0; i<Height*Width; ++i )
	{
		GW_Float rVal = pData[nPos];
		aData_[i] = rVal;
		if(rVal>rMax_) rMax_ = rVal;										
		if(rVal<rMin_) rMin_ = rVal; 
		nPos += DataSize*Components;
	}
	
	ilDeleteImages(1, &nImageNum);
	return GW_OK;
}

/*------------------------------------------------------------------------------*/
// Name : GW_TopographicFunction::GetGradient
/**
 *  \param  rU [GW_Float] u coord
 *  \param  rV [GW_Float] v coord
 *  \param  gU [GW_Float&] gradient on u
 *  \param  gV [GW_Float&] gradient on v
 *  \author Gabriel Peyré
 *  \date   5-20-2003
 * 
 *  Compute the gradient at a given point.
 */
/*------------------------------------------------------------------------------*/
void GW_TopographicFunction::GetGradient( GW_Float rU, GW_Float rV, GW_Float& gU, GW_Float& gV ) const
{
#define EPS 0.01
	GW_Float t1 = rU - EPS;
	GW_Float t2 = rU + EPS;
	if( t1<0 ) t1=0;
	if( t1>1 ) t1=1;
	if( t2<0 ) t2=0;
	if( t2>1 ) t2=1;
	GW_Float delta = t2-t1;
	GW_ASSERT( delta>0 );
	gU = ( this->GetValue( t1, rV ) - this->GetValue( t2, rV ) )/delta;

	t1 = rV - EPS;
	t2 = rV + EPS;
	if( t1<0 ) t1=0;
	if( t1>1 ) t1=1;
	if( t2<0 ) t2=0;
	if( t2>1 ) t2=1;
	delta = t2-t1;
	GW_ASSERT( delta>0 );
	gV = ( this->GetValue( rU, t1 ) - this->GetValue( rU, t2 ) )/delta;
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
