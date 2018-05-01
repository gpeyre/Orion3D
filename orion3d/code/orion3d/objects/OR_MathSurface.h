
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MathSurface.h
 *  \brief Definition of class \c OR_MathSurface
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_MathSurface_h_
#define __OR_MathSurface_h_

#include "../configuration/OR_Config.h"
#include "OR_Object.h"
#include "OR_Mesh.h"
#include "../shaders/OR_Shader.h"
#include "../shaders/OR_ShaderManager.h"
#include "../shaders/OR_Shadable.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MathSurface
 *  \brief  a mathematic surface.
 *  \author Gabriel Peyré 2001-11-12
 *  The math surface use a callback function to compute the value of the surace for
 *	a given set (u,v) of parameters.
 */ 
/*------------------------------------------------------------------------------*/

typedef void (*T_MathSurf_Callback) (OR_Vector3D& val, OR_Float u, OR_Float v, void* pUserParam);

class ORION3D_API OR_MathSurface: public OR_Object, public OR_Shadable
{

public:

    OR_MathSurface();
    virtual ~OR_MathSurface();

    //-------------------------------------------------------------------------
    /** \name overloaded methods from OR_Object */
    //-------------------------------------------------------------------------
    //@{
	/** the type of the object */
	virtual OR_Elements GetType();
	/** draw the mesh */
	virtual void Draw();
    //@}

	
    //-------------------------------------------------------------------------
    /** @name overloaded functions from OR_Shadable */
    //-------------------------------------------------------------------------
    //@{
	virtual void ProcessAllFaces();
	virtual void ProcessOneFace(OR_U32 nNumFace);
	virtual void AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCorrdArray, OR_U32* &aFaceArray, 
							   OR_U32& nNbrVert, OR_U32& nNbrFace );
    //@}  

    //-------------------------------------------------------------------------
    /** \name callback function management */
    //-------------------------------------------------------------------------
    //@{
	void SetCallback(T_MathSurf_Callback pFunc);
	T_MathSurf_Callback GetCallback();
    //@}

	
	//-------------------------------------------------------------------------
    /** \name user param management */
    //-------------------------------------------------------------------------
    //@{
	void  SetUserParam(void* pUserParam);
	void* GetUserParam();
    //@}

    //-------------------------------------------------------------------------
    /** \name range management */
    //-------------------------------------------------------------------------
    //@{
	void SetURange(OR_Float rUMin, OR_Float rUMax);
	void SetVRange(OR_Float rVMin, OR_Float rVMax);
	void SetRange(OR_Float rUMin, OR_Float rUMax, OR_Float rVMin, OR_Float rVMax);
	void SetUMin(OR_Float rUMin);
	void SetUMax(OR_Float rUMax);
	void SetVMin(OR_Float rVMin);
	void SetVMax(OR_Float rVMax);
	OR_Float GetUMin();
	OR_Float GetUMax();
	OR_Float GetVMin();
	OR_Float GetVMax();

	void SetPrecision(OR_U32 nUPrecision, OR_U32 nVPrecision);
	void SetUPrecision(OR_U32 nUPrecision);
	void SetVPrecision(OR_U32 nVPrecision);
	OR_Float GetUPrecision();
	OR_Float GetVPrecision();
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile(OR_File& file);
	/** export the data from the object to an opened file */
	virtual void BuildToFile(OR_File& file);

	OR_DEFINE_SERIALIZATION( OR_MathSurface );
    //@}

private:

	//-------------------------------------------------------------------------
    /** \name helpers methods */
    //-------------------------------------------------------------------------
    //@{
	void ComputeNormal(OR_Vector3D& norm, OR_Float u, OR_Float v);
	void ComputeValue(OR_Vector3D& val, OR_Float u, OR_Float v);
	void ResizeTempArrays();
    //@}


	/** the function used to compute the surface */
	T_MathSurf_Callback pCallbackFunc_;

	/** a parameter passed to the callback function */
	void* pUserParam_;

	/** precision on U */
	OR_U32 nUPrecision_;
	/** precision on V */
	OR_U32 nVPrecision_;

	/** minimal param value on U */
	OR_Float rUMin_;
	/** minimal param value on V */
	OR_Float rVMin_;
	/** maximal param value on U */
	OR_Float rUMax_;
	/** maximal param value on V */
	OR_Float rVMax_;

	/** does the surface needs to be re-computed ? */
	OR_Bool bNeedsUpdate_;

	/** to keep the normal & vertex already computed */
	OR_Vector3D *norm1, *norm2, *vert1, *vert2;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_MathSurface.inl"
#endif


#endif // __OR_MathSurface_h_

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

