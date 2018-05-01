//*****************************************************************************
// Created: Gabriel Peyré 2001-06-29
//*****************************************************************************

#ifndef __OR_Shadable_h_
#define __OR_Shadable_h_

#include "../configuration/OR_Config.h"


namespace OR {
	
class OR_Shader;

//=============================================================================
/**
*   @class  OR_Shadable
*   @brief  base class for each class which want to be rendered by a shader
*	
*	Each object (for instance a mesh) which want to use a shader has to  inherit 
*	from this class.
*	This class act like a state machine : 
*		- the caller that want to render the objet (can be the object himself, the alpha pipeline ...)
*		  initialize the state (ie. 'render all' or 'render only an array') before calling the 
*		  shader function \c ProcessShader.
*		- the shader process the vertex, either globaly (using \c ProcessAllFaces)
*		  or on a per face basis (using \c ProcessOneFace). It can also access the internal of the
*		  shadable (to make per-vertex computations) using \c AccessArrays.
*/
// Created: Gabriel Peyré 2001-06-29
//=============================================================================
class ORION3D_API OR_Shadable
{

public:

	enum T_ShadableMode
	{
		kProcessArray,
		kProcessAll
	};

    OR_Shadable();
	OR_Shadable( const OR_Shadable& Dup );
    virtual ~OR_Shadable();
	OR_Shadable& operator=( const OR_Shadable& Dup );

    //-------------------------------------------------------------------------
    /** @name initialize the state of the shadable object [called by the object] */
    //-------------------------------------------------------------------------
    //@{
	void SetFaceToProcess(OR_U32* aFace, OR_U32 nNbr);
	void SetFaceToProcess_All();

	/** initialize modelview matrix before rendering the object to screen */
	virtual void SetUpModelView() {}
    //@}

    //-------------------------------------------------------------------------
    /** @name processing function [called by the shader] */
    //-------------------------------------------------------------------------
    //@{
	virtual void ProcessAllFaces()=0;
	virtual void ProcessOneFace(OR_U32 nNumFace)=0;
    //@}  

    //-------------------------------------------------------------------------
    /** \name access to shadable internals */
    //-------------------------------------------------------------------------
    //@{
	virtual void AccessArrays( OR_Float* &aVertArray, OR_Float* &aNormArray, OR_Float* &aTexCorrdArray, OR_U32* &aFaceArray, 
							   OR_U32& nNbrVert, OR_U32& nNbrFace );
    //@}

    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	void       SetShader(OR_Shader* pShader);
	OR_Shader* GetShader();
	OR_Shadable::T_ShadableMode GetShadableMode();

	OR_U32* GetFaceArrayToProcess();
	OR_U32  GetNbrFaceToProcess();
    //@}


protected:

	/** a list of vertex to process */
	OR_U32 *pFaceArray_;
	/** the number of vertex to process */
	OR_U32 nNbrFace_;

	/** the current shader */
	OR_Shader* pShader_;
	/** the way we want to process the shader
		(using an array of vertex, or processing all faces) */
	OR_Shadable::T_ShadableMode ShadableMode_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_Shadable.inl"
#endif


#endif // __OR_Shadable_h_

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

