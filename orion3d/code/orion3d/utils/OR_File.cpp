/*----------------------------------------------------------*/
/*                      OR_File.cpp                         */
/*----------------------------------------------------------*/
/* to handle a file                                         */
/*----------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_File.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_File.h"
#include "OR_String.h"
#include "../utils/OR_MessageHandler.h"
#include "../maths/OR_Maths.h"

using namespace OR;


#define IMPLEMENT_SERIALIZATION(T)								\
	OR_File& OR_File::operator << (const T &v)					\
	{ if (file==NULL) { OR_Globals::MessageHandler()->Warning(	\
		"OR_File::<<", "File is not opened."); return *this; }	\
	if (Mode!='w') { OR_Globals::MessageHandler()->Warning(		\
		"OR_File::<<", "File is not opened in write mode.");	\
	return *this; }												\
	fwrite(&v, sizeof(T), 1, file); return *this;				\
	return *this; }												\
	OR_File& OR_File::operator >> (T &v)						\
	{ if (file==NULL) { OR_Globals::MessageHandler()->Warning(	\
	"OR_File::<<", "File is not opened."); return *this; }		\
	if (Mode!='r') { 	OR_Globals::MessageHandler()->Warning(	\
	"OR_File::<<", "File is not opened in read mode.");			\
	return *this; }												\
	fread(&v, sizeof(T), 1, file); return *this;				\
	return *this; }												\

IMPLEMENT_SERIALIZATION(OR_Float)
IMPLEMENT_SERIALIZATION(OR_U8)
IMPLEMENT_SERIALIZATION(OR_U16)
IMPLEMENT_SERIALIZATION(OR_U32)
IMPLEMENT_SERIALIZATION(OR_U64)
IMPLEMENT_SERIALIZATION(OR_I8)
IMPLEMENT_SERIALIZATION(OR_I16)
IMPLEMENT_SERIALIZATION(OR_I32)
IMPLEMENT_SERIALIZATION(OR_I64)
IMPLEMENT_SERIALIZATION(OR_Bool)
IMPLEMENT_SERIALIZATION(OR_Elements)
IMPLEMENT_SERIALIZATION(OR_Culling_Mode)
IMPLEMENT_SERIALIZATION(OR_VIEWPORT_Type)
IMPLEMENT_SERIALIZATION(OR_LENSFLARE_Type)
IMPLEMENT_SERIALIZATION(OR_Drawing_Mode)
IMPLEMENT_SERIALIZATION(OR_Blending_Mode)
IMPLEMENT_SERIALIZATION(OR_ANIMATION_Evaluator_Type)
IMPLEMENT_SERIALIZATION(OR_ANIMATION_Track_Type)
IMPLEMENT_SERIALIZATION(OR_ANIMATION_Track_Behavior)
IMPLEMENT_SERIALIZATION(OR_ANIMATION_Player_Behavior)
IMPLEMENT_SERIALIZATION(OR_ANIMATION_Target)
IMPLEMENT_SERIALIZATION(OR_Types)
IMPLEMENT_SERIALIZATION(OR_ForceType)
IMPLEMENT_SERIALIZATION(OR_META_Type)
IMPLEMENT_SERIALIZATION(OR_Position)
IMPLEMENT_SERIALIZATION(OR_MetaNormalType)
IMPLEMENT_SERIALIZATION(OR_ScrMode)

#undef IMPLEMENT_SERIALIZATION

/* serialization for maths class */
#define IMPLEMENT_SERIALIZATION(T, size)						\
	OR_File& OR_File::operator << (const T &v)					\
	{ if (file==NULL) { OR_Globals::MessageHandler()->Warning(	\
	"OR_File::<<", "File is not opened."); return *this; }		\
	if (Mode!='w') { OR_Globals::MessageHandler()->Warning(		\
	"OR_File::<<", "File is not opened in write mode.");		\
	return *this; }												\
	fwrite(v.GetData(), sizeof(OR_Float)*size, 1, file);		\
	return *this; }												\
	OR_File& OR_File::operator >> (T &v)						\
	{ if (file==NULL) { OR_Globals::MessageHandler()->Warning(	\
	"OR_File::<<", "File is not opened."); return *this; }		\
	if (Mode!='r') { 	OR_Globals::MessageHandler()->Warning(	\
	"OR_File::<<", "File is not opened in read mode.");			\
	return *this; }												\
	fread(v.GetData(), sizeof(OR_Float)*size, 1, file); 		\
	return *this; }	

IMPLEMENT_SERIALIZATION(OR_Matrix4x4, 16);
IMPLEMENT_SERIALIZATION(OR_Matrix3x3, 9);
IMPLEMENT_SERIALIZATION(OR_Vector4D, 4);
IMPLEMENT_SERIALIZATION(OR_Vector3D, 3);
IMPLEMENT_SERIALIZATION(OR_Vector2D, 2);

#undef IMPLEMENT_SERIALIZATION

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::<<
 *
 *  \param  file source file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator << (const OR_MatrixNxP &v)	
{
	(*this) << v.GetNbrCols() 
		<< v.GetNbrRows();
	
	if( v.GetNbrCols()>0 && v.GetNbrRows()>0 )
		fwrite( v.GetData(), sizeof(OR_Float), v.GetNbrCols()*v.GetNbrRows(), this->GetFile() );

	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::>>
 *
 *  \param  file dest file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator >> (OR_MatrixNxP &v)
{
	OR_U32 nNbrCols, nNbrRows;
	(*this)	>> nNbrCols 
			>> nNbrRows;
	
	v.Reset( nNbrRows, nNbrCols );
	fread( v.GetData(), sizeof(OR_Float), v.GetNbrCols()*v.GetNbrRows(), this->GetFile() );

	return *this;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::<<
 *
 *  \param  file source file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator << (const OR_Quaternion &v)	
{
	(*this) << v.GetX() << v.GetY() << v.GetZ() << v.GetW();
	
	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::>>
 *
 *  \param  file dest file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator >> (OR_Quaternion &v)
{
	OR_Float x,y,z,w;
	(*this) >> x >> y >> z >> w;
	v= OR_Quaternion(w,x,y,z);
	
	return *this;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::<<
 *
 *  \param  file source file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator << (const OR_VectorND &v)	
{	
	(*this) << v.GetDim();
	if( v.GetDim()>0 )
		fwrite( v.GetData(), sizeof(OR_Float), v.GetDim(), this->GetFile() );

	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::>>
 *
 *  \param  file dest file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator >> (OR_VectorND &v)
{
	OR_U32 nDim;
	(*this) >> nDim;
	v.Reset( nDim );
	if( nDim>0 )
		fread( v.GetData(), sizeof(OR_Float), v.GetDim(), this->GetFile() );
	
	return *this;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::<<
 *
 *  \param  file source file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator << (const OR_SparseMatrixBlock &v)	
{
	(*this) << v.GetRowOffset()
			<< v.GetColOffset()
			<< v.GetMatrix();

	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::>>
 *
 *  \param  file dest file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator >> (OR_SparseMatrixBlock &v)
{
	OR_MatrixNxP* pMatrix = new OR_MatrixNxP;
	v.SetMatrix( *pMatrix );

	OR_U32 nRowOffset, nColOffset;
	(*this) >> nRowOffset
			>> nColOffset
			>> (*pMatrix);

	v.SetOffset(nRowOffset, nColOffset);

	return *this;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::<<
 *
 *  \param  file source file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator << (const OR_SparseMatrix &v)	
{
	(*this) << v.GetNbrRows()
			<< v.GetNbrCols();
	
	OR_U32 nNbrBlock = v.GetNbrBlock();
	(*this) << nNbrBlock;
	
	OML::T_SparseMatrixBlockList BlockList = v.GetBlockList();

	for( OML::IT_SparseMatrixBlockList it=BlockList.begin(); it!=BlockList.end(); ++it )
		(*this) << (*it);

	return *this;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_File::>>
 *
 *  \param  file dest file
 *  \author Gabriel Peyré 2001-09-19
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator >> (OR_SparseMatrix &v)
{	
	OR_U32 nNbrCols, nNbrRows;

	(*this) >> nNbrRows
			>> nNbrCols;

	v.SetDim(nNbrRows, nNbrCols);
	
	OR_U32 nNbrBlock = 0;
	(*this) >> nNbrBlock;
	
	for( OR_U32 i=0; i<nNbrBlock; ++i )
	{
		OR_SparseMatrixBlock* pBlock = new OR_SparseMatrixBlock;
		(*this) >> (*pBlock);
		v.AddBlock( *pBlock );
	}

	return *this;
}







/*------------------------------------------------------------------------------*/
// Name : OR_File::operator <<
/** 
 *  \param  v The objet to export to file.
 *  \return The file.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the OR_Serializable object to a file.
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator <<(OR_Serializable* v)
{ 
	if (file==NULL)
	{
		OR_Globals::MessageHandler()->Warning("OR_File::<<",
			"File is not opened.");
		return *this;
	}
	if (Mode!='w')
	{
		OR_Globals::MessageHandler()->Warning("OR_File::<<",
			"File is not opened in write mode.");
		return *this;
	}
	if (v==NULL)
		OR_Globals::MessageHandler()->Warning("OR_File::<<",
		"Passing a NULL OR_Serializable*.");
	else
		v->BuildToFile(*this); 
	return *this; 
}
/*------------------------------------------------------------------------------*/
// Name : OR_File::operator >>
/** 
 *  \param  v The objet to import from file.
 *  \return The file.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Import the OR_Serializable object to a file.
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator >> (OR_Serializable* v)                        
{ 
	if (file==NULL)
	{
		OR_Globals::MessageHandler()->Warning("OR_File::<<",
			"File is not opened.");
		return *this;
	}
	if (Mode!='r')
	{
		OR_Globals::MessageHandler()->Warning("OR_File::<<",
			"File is not opened in read mode.");
		return *this;
	}
	if (v==NULL)
		OR_Globals::MessageHandler()->Warning("OR_File::>>",
		"Passing a NULL OR_Serializable*.");
	else
		v->BuildFromFile(*this); 
	return *this; 
}


/*------------------------------------------------------------------------------*/
// Name : OR_File::operator <<
/** 
 *  \param  v The objet to export to file.
 *  \return The file.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the OR_Serializable object to a file.
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator <<(OR_Serializable& v)
{ 
	if (file==NULL)
	{
		OR_Globals::MessageHandler()->Warning("OR_File::<<",
			"File is not opened.");
		return *this;
	}
	if (Mode!='w')
	{
		OR_Globals::MessageHandler()->Warning("OR_File::<<",
			"File is not opened in write mode.");
		return *this;
	}
	
	v.BuildToFile(*this); 
	return *this; 
}


/*------------------------------------------------------------------------------*/
// Name : OR_File::operator >>
/** 
 *  \param  v The objet to import from file.
 *  \return The file.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Import the OR_Serializable object to a file.
 */ 
/*------------------------------------------------------------------------------*/
OR_File& OR_File::operator >> (OR_Serializable& v)                        
{ 
	if (file==NULL)
	{
		OR_Globals::MessageHandler()->Warning("OR_File::<<",
			"File is not opened.");
		return *this;
	}
	if (Mode!='r')
	{
		OR_Globals::MessageHandler()->Warning("OR_File::<<",
			"File is not opened in read mode.");
		return *this;
	}
	v.BuildFromFile(*this); 
	return *this; 
}

/*------------------------------------------------------------------------------*/
// Name : OR_File::Write
/** 
 *  \param  data data to write to the file.
 *  \param  size size of the data type.
 *  \param  nb number of datas.
 *  \return Was it successful ?
 *  \author Gabriel Peyré 2001-08-05
 *
 *	write data in the file
 */ 
/*------------------------------------------------------------------------------*/
OR_RETURN_CODE OR_File::Write(void* data, size_t size, OR_U32 nb)
{ 
	OR_ASSERT(data!=NULL);
	if (file==NULL) 
	{ OR_Globals::MessageHandler()->Warning("OR_File::Write", "File is not opened."); return OR_ERROR; }
	if (Mode!='w') 
	{ OR_Globals::MessageHandler()->Warning("OR_File::Write", "File is not opened in write mode."); return OR_ERROR; }
	fwrite(data, size, nb, file); 
	return OR_OK;
}

/*------------------------------------------------------------------------------*/
// Name : OR_File::Read
/** 
 *  \param  data data to read from the file.
 *  \param  size size of the data type.
 *  \param  nb number of datas.
 *  \return Was it successful ?
 *  \author Gabriel Peyré 2001-08-05
 *
 *  read data from the file
 */ 
/*------------------------------------------------------------------------------*/
OR_RETURN_CODE OR_File::Read(void* data, size_t size, OR_U32 nb)
{ 
	OR_ASSERT(data!=NULL);
	if (file==NULL) 
	{ OR_Globals::MessageHandler()->Warning("OR_File::Read", "File is not opened."); return OR_ERROR; }
	if (Mode!='r') 
	{ OR_Globals::MessageHandler()->Warning("OR_File::Read", "File is not opened in read mode."); return OR_ERROR; }
	fread(data, size, nb, file); 
	return OR_OK;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_String OR_File::GetLine()
 *
 *  \return A string containing the contents of the file from the current position
 *  to the first cr character, including it.
 *  \author Antoine Bouthors 2002-04-15
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_String OR_File::GetLine()
{
	OR_String Result;
	char Character;
	if( file == NULL || feof( file ) ) return Result;

	do 
	{
		if( fread( &Character, 1, 1, file ) == 1 )
			Result += Character;
	} while( Character != '\n' && !feof( file ) );

	return Result;
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////