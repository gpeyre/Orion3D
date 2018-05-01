/*----------------------------------------------------------*/
/*                      OR_File                             */
/*----------------------------------------------------------*/
/* to handle a file                                         */
/*----------------------------------------------------------*/

/** \file
	to handle a file.
	\author Gabriel
*/


#ifndef _OR_FILE_H_
#define _OR_FILE_H_

#include "../configuration/OR_Config.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_String.h"
#include "../orion3d_maths/OML_Matrix4x4.h"
#include "../orion3d_maths/OML_Vector3D.h"
#include "../configuration/OR_Config.h"
#include "../orion3d_maths/OML_Maths.h"
#include "../orion3d_maths/OML_Matrix4x4.h"
#include "../orion3d_maths/OML_Matrix3x3.h"
#include "../orion3d_maths/OML_MatrixNxP.h"
#include "../orion3d_maths/OML_Vector2D.h"
#include "../orion3d_maths/OML_Vector3D.h"
#include "../orion3d_maths/OML_Vector4D.h"
#include "../orion3d_maths/OML_VectorND.h"
#include "../orion3d_maths/OML_SparseMatrix.h"
#include "../orion3d_maths/OML_Quaternion.h"

namespace OR
{

typedef ORION3D_API class OML::OML_Matrix4x4	OR_Matrix4x4;
typedef ORION3D_API class OML::OML_Matrix3x3	OR_Matrix3x3;
typedef ORION3D_API class OML::OML_MatrixNxP	OR_MatrixNxP;
typedef ORION3D_API class OML::OML_SparseMatrix			OR_SparseMatrix;
typedef ORION3D_API class OML::OML_SparseMatrixBlock	OR_SparseMatrixBlock;
typedef ORION3D_API class OML::OML_Vector4D	OR_Vector4D;
typedef ORION3D_API class OML::OML_Vector3D	OR_Vector3D;
typedef ORION3D_API class OML::OML_Vector2D	OR_Vector2D;
typedef ORION3D_API class OML::OML_VectorND	OR_VectorND;
typedef ORION3D_API class OML::OML_Quaternion	OR_Quaternion;

/*----------------------------------------------------------*/
/*                    class OR_File                         */
/*----------------------------------------------------------*/
/* to handle a file                                         */
/*----------------------------------------------------------*/

/// a class to handle a file.
/**
	Define << and >> operators to output on a stream.
	Be carefull : destroying the file doesn't close it ! You have to do it
	manualy ! (this is because OR_File are not manipulated as pointers, so 
	there are often destroyed, whereas we want the FILE* not to be closed).
	\author Gabriel
*/

class ORION3D_API OR_File
{
private:
	/** the file */
	FILE* file;
	/** the way the file was opened */
	char Mode;
public:
	/** base constructor */
	OR_File()
	{ file=NULL; Mode='x'; }
	/** constructor : open the file */
	OR_File(const char* name, const char* mode="rb")
	{ file=fopen(name, mode); Mode=mode[0]; }
	/** destructor */
	~OR_File()
	{ file=NULL; }

	/** open the file 
		\return is the file open ? */
	OR_Bool Open(const char* name, const char* mode="rb")
	{ 
		if (file!=NULL) fclose(file);
		file=fopen(name, mode);
		Mode=mode[0];
		return (file!=NULL);
	}
	/** close the file */
	void Close()
	{ fclose(file); }
	/** get the FILE* */
	FILE* GetFile()
	{ return file; }
	/** is the file open ? */
	OR_Bool IsOpen()
	{ return (file!=NULL); }
	/** Are we at the end of the file ? */
	OR_Bool Eof()
	{ return feof( file ); }

	OR_String GetLine();

	//-------------------------------------------------------------------------
    /** \name i/o methods */
    //-------------------------------------------------------------------------
    //@{
	OR_RETURN_CODE Write(void* data, size_t size, OR_U32 nb);
	OR_RETURN_CODE Read(void* data, size_t size, OR_U32 nb);
    //@}

    //-------------------------------------------------------------------------
    /** \name operators on base types */
    //-------------------------------------------------------------------------
    //@{
	#define DEFINE_SERIALIZATION(T)			\
	OR_File& operator << (const T &v);		\
	OR_File& operator >> (T &v)				\

	DEFINE_SERIALIZATION(OR_Float);
	DEFINE_SERIALIZATION(OR_U8);
	DEFINE_SERIALIZATION(OR_U16);
	DEFINE_SERIALIZATION(OR_U32);
	DEFINE_SERIALIZATION(OR_U64);
	DEFINE_SERIALIZATION(OR_I8);
	DEFINE_SERIALIZATION(OR_I16);
	DEFINE_SERIALIZATION(OR_I32);
	DEFINE_SERIALIZATION(OR_I64);
	DEFINE_SERIALIZATION(OR_Bool);
	DEFINE_SERIALIZATION(OR_Elements);
	DEFINE_SERIALIZATION(OR_Culling_Mode);
	DEFINE_SERIALIZATION(OR_VIEWPORT_Type);
	DEFINE_SERIALIZATION(OR_LENSFLARE_Type);
	DEFINE_SERIALIZATION(OR_Drawing_Mode);
	DEFINE_SERIALIZATION(OR_Blending_Mode);
	DEFINE_SERIALIZATION(OR_ANIMATION_Evaluator_Type);
	DEFINE_SERIALIZATION(OR_ANIMATION_Track_Type);
	DEFINE_SERIALIZATION(OR_ANIMATION_Track_Behavior);
	DEFINE_SERIALIZATION(OR_ANIMATION_Player_Behavior);
	DEFINE_SERIALIZATION(OR_ANIMATION_Target);
	DEFINE_SERIALIZATION(OR_Types);
	DEFINE_SERIALIZATION(OR_ForceType);
	DEFINE_SERIALIZATION(OR_META_Type);
	DEFINE_SERIALIZATION(OR_Position);
	DEFINE_SERIALIZATION(OR_MetaNormalType);
	DEFINE_SERIALIZATION(OR_ScrMode);

	DEFINE_SERIALIZATION(OR_Matrix4x4);
	DEFINE_SERIALIZATION(OR_Matrix3x3);
	DEFINE_SERIALIZATION(OR_MatrixNxP);
	DEFINE_SERIALIZATION(OR_SparseMatrix);
	DEFINE_SERIALIZATION(OR_SparseMatrixBlock);
	DEFINE_SERIALIZATION(OR_Vector4D);
	DEFINE_SERIALIZATION(OR_Vector3D);
	DEFINE_SERIALIZATION(OR_Vector2D);
	DEFINE_SERIALIZATION(OR_VectorND);
	DEFINE_SERIALIZATION(OR_Quaternion);

	#undef DEFINE_SERIALIZATION
    //@}

	//-------------------------------------------------------------------------
    /** \name operators on OR_Serializable */
    //-------------------------------------------------------------------------
    //@{
	OR_File& operator << (OR_Serializable* v);
	OR_File& operator >> (OR_Serializable* v);
	OR_File& operator << (OR_Serializable& v);
	OR_File& operator >> (OR_Serializable& v);
    //@}

	
};

} // namespace OR

#endif _OR_FILE_H_


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
