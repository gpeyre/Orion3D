/*---------------------------------------------------------------------*/
/*                                  OR_Texture.h                       */
/*---------------------------------------------------------------------*/
/*              definition de la classe OR_Texture		               */            
/*---------------------------------------------------------------------*/

/** \file 
	Contains the definition of a 2D texture.
	\author Gabriel.
**/

#ifndef _OR_TEXTURE_H_
#define _OR_TEXTURE_H_

#include "../configuration/OR_Config.h"
#include "../utils/OR_SmartCounter.h"
#include "../misc/OR_Endian_Conv.h"
#include "../utils/OR_SmartManagerMap_Template.h"
#include "../utils/OR_Serializable.h"
#include "../utils/OR_Log.h"
#include "../utils/OR_File.h"
#include "../utils/OR_String.h"

#ifdef _USE_OPENIL_
	#include <il/il.h>
	#include <il/ilu.h>
	#include <il/ilut.h>
#endif // _USE_OPENIL_

namespace OR
{
	
/*-----------------------------------------------------------------------*/
/*                              classe OR_Texture                        */            
/*-----------------------------------------------------------------------*/
/* A 2D texture.                                                         */
/*-----------------------------------------------------------------------*/

/// A 2D texture.
/** 
	Load a image file into opengl memory using OpenIL.
	\author Antoche
*/
class ORION3D_API OR_Texture: public OR_Serializable, public OR_SmartCounter
{
private:

	/** opengl number of the texture */
	GLuint NumTex;
#ifdef _USE_OPENIL_
	/** OpenIL identifier for the texture */
	ILuint OpenIL_id;
#endif
	/** width of the image */
	GLsizei	Width;
	/** height of the image */
	GLsizei	Height;
	/** number of component of the image */
	GLint	Components;
	/** opengl format of the image */
	GLenum	Format;
	/** opengl type of the image */
	GLenum	Type;

	/** the data image : used only by BuildFromScreen*/
	unsigned char *Data;

	/** does the texture belong to a cube map ?? */
	OR_Bool IsCubeMap;
	/** if so, what is its number ?? */
	OR_I32 CubeMapNum;
	/** does the texture use mip mapping ?? */
	OR_Bool IsMipMap;
	/** adresse of the image file. The normal use of this variable is to store the
		adress of the texture relative to a .krd file. */
	OR_String Adresse;
	/** buffer utilised for feedback mode */
	OR_Float* FeedBuffer;

public:

	/** constructor */
	OR_Texture(OR_Bool iscubemap=false, OR_I32 num=0, OR_Bool ismipmap=false);
	/** destructor */
	virtual ~OR_Texture();
	
	/** load texture from a bmp file */
	OR_I32 LoadImage( const char * File );
	/** load texture from a bmp file */
	OR_I32 LoadImageFileFromMem( const void *File, OR_I32 size, ILenum type=IL_TYPE_UNKNOWN);
	/** free the memory both from OpenGL and from OpenIL */
	void Unload();
	/** free the memory from OpenIL */
	void UnloadData();
	/** set the texture as current opengl texture */
	void Bind();
	/** re-load the data already loaded from an image file to opengl */
	OR_RETURN_CODE ReLoadToGL();

	/* OPSOLETE ********************************************************/
	/** use feedback mode to build the texture */
	OR_I32 BuildFromScreen(OR_I32 ll_x, OR_I32 ll_y, OR_I32 width, OR_I32 height);

	/* to query the texture ********************************************/
	/** get the adress of the image file */
	const OR_String& GetImageAdress( ) const
	{ return Adresse; }
	/** set the image adress */
	void SetImageAdress(char* adr)
	{ Adresse=adr; }
	/** have an image file been loaded ? */
	OR_Bool IsImageLoaded()
	{ return Data!=NULL; }
	/** get the number of components (channels) of the image */
	OR_U32 GetComponents()
	{ return Components; }
	/** get the width of the image */
	OR_U32 GetWidth()
	{ return Width; }
	/** get the height of the image */
	OR_U32 GetHeight()
	{ return Height; }
	/** return true if the texture is using mimap */
	OR_Bool GetIsMipmap()
	{ return IsMipMap; }
	/** get the opengl format of the image */
	GLenum	GetFormat()
	{ return Format; }
	/** get the opengl type of the image */
	GLenum	GetType()
	{ return Type; }
	unsigned char* GetScreenData()
	{ return Data; }

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_Texture);
    //@}


	/* filters ********************************************************/
#ifdef _USE_OPENIL_
	/** get the data image */
	unsigned char * GetData()
	{
		return ilGetData();
	}

	/** OpenIL filter : Images with people in them turn out the best with this filter, and no,
		it doesn't just change the image all green. ;-) It's a very interesting effect, 
		imo, and I discovered it! =P */
	OR_Bool FilterAlienify()
	{
		ilBindImage(OpenIL_id);
		return iluAlienify();
	}
	/** OpenIL filter : blur an image, using simple blurring convolution filters.
		All values in the convolution matrix are 1, so all pixels around a pixel get averaged
		in as much as the pixel being tested.
		\param iterations the number of iterations of blurring to perform on the image.
		If you want to blur an image more, increase the number of iterations, but beware, as it will be slow.  */
	OR_Bool FilterBlurAvg(OR_I32 iterations)
	{
		ilBindImage(OpenIL_id); 
		return iluBlurAvg(iterations);
	}
	/** OpenIL filter : blur an image, using simple blurring convolution filters.
		A Gaussian blur looks more natural, as diagonal pixels count as the least, side pixels count in
		the middle and the center pixel counts the most. 
		\param iterations the number of iterations of blurring to perform on the image.
		If you want to blur an image more, increase the number of iterations, but beware, as it will be slow.  */
	OR_Bool FilterBlurGaussian(OR_I32 iterations)
	{
		ilBindImage(OpenIL_id); 
		return iluBlurGaussian(iterations);
	}
	/** OpenIL filter : These two functions apply convolution filters to determine the edges in an image.
		A horizontal pass and a vertical pass on the image are combined to generate the appropriate edges.
		The algorithms are slightly different but generally give similar results.
		Experiment with them to see which one yields the best results for your application. */
	OR_Bool FilterEdgeDetectP()
	{
		ilBindImage(OpenIL_id); 
		return iluEdgeDetectP();
	}
	/** OpenIL filter : These two functions apply convolution filters to determine the edges in an image.
		A horizontal pass and a vertical pass on the image are combined to generate the appropriate edges.
		The algorithms are slightly different but generally give similar results.
		Experiment with them to see which one yields the best results for your application. */
	OR_Bool FilterEdgeDetectS()
	{
		ilBindImage(OpenIL_id); 
		return iluEdgeDetectS();
	}
	/** OpenIL filter : This function embosses an image, which makes it mostly grey with raised edges.
		This is a different form of edge detection. */
	OR_Bool FilterEmboss()
	{
		ilBindImage(OpenIL_id); 
		return iluEmboss();
	} 
	/** OpenIL filter : creates a negative of the image, effectively inverting all colours 
		(black becomes white, etc.). */
	OR_Bool FilterNegative()
	{
		ilBindImage(OpenIL_id); 
		return iluNegative();
	} 
	/** OpenIL filter : adds mono noise to an image to give it a noisy or even "dirty" look. 
		\param tolerance determines the variance factor -- 
		how far from the original pixel's value the new value should be allowed to variate. */
	OR_Bool FilterNoise(OR_Float tolerance)
	{
		ilBindImage(OpenIL_id); 
		return iluNoisify(tolerance);
	}
	/** OpenIL filter : This function pixellizes an image, making it appear blocky. 
		This function can be used for some neat effects, such as an interesting screen clearing effect. 
		\param pixsize size of the pixel */
	OR_Bool FilterPixelize(OR_U32 pixsize)
	{
		ilBindImage(OpenIL_id); 
		return iluPixelize(pixsize);
	} 
	/** OpenIL filter : iluSharpen "sharpens" the current image, making the edges more noticeable and
		the whole image "less blurry". 
		\param factor strength of the effect. 
		\param iter Number of iterations. */
	OR_Bool FilterSharpen(OR_Float factor, OR_U32 iter)
	{
		ilBindImage(OpenIL_id); 
		return iluSharpen(factor, iter);
	} 
#endif /* #ifdef _USE_OPENIL_ */
};

/*-------------------------------------------------------------------------*/
/*                          class OR_TextureManager                        */
/*-------------------------------------------------------------------------*/
/* a manager of textures                                                   */
/*-------------------------------------------------------------------------*/

/*! \ingroup group_manager 
 *  \brief class OR_TextureManager in group group_manager
 */

/// a manager of textures .
/** 
	Contains a copy of every texture in the scene.
	This alow to have an easy acces to each texture.
	\author Gabriel
*/
/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
#pragma warning( disable : 4660 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_SmartManagerMap_Template<OR_Texture>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_Texture>;

class ORION3D_API OR_TextureManager: public OR_SmartManagerMap_Template<OR_Texture>
{
public:
	/** add a new texture */
	OR_I32 AddTexture( const char* file, OR_Bool iscubemap=false, OR_I32 num=0, OR_Bool ismipmap=false );
	/** load a bitmap from a file */
	OR_I32  LoadImage( const char *File );
	/** Find a texture already loaded with Path */
	OR_Texture* FindTexture( const char* Path );
};

} // namespace OR

#endif		/* #ifndef _OR_TEXTURE_H_ */ 


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
