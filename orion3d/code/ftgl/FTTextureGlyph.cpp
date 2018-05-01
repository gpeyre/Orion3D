#include	"FTTextureGlyph.h"
#include	"FTGL.h"

//#include "mmgr.h"


FTTextureGlyph::FTTextureGlyph( FT_Glyph glyph, int id, int xOffset, int yOffset, GLsizei width, GLsizei height)
:	FTGlyph(),
	data(0),
	destWidth(0),
	destHeight(0),
	numGreys(0),
	glTextureID(id),
	activeTextureID(0)
{
	// FIXME This function will always fail if the glyph's format isn't scalable????
	err = FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1);
	if( err || glyph->format != ft_glyph_format_bitmap)
	{
		return;
	}

	FT_BitmapGlyph  bitmap = ( FT_BitmapGlyph)glyph;
	FT_Bitmap*      source = &bitmap->bitmap;

	// FIXME check the pixel mode
	//ft_pixel_mode_grays
	    
	int srcWidth = source->width;
	int srcHeight = source->rows;
	int srcPitch = source->pitch;
    
    destWidth = srcWidth;
    destHeight = srcHeight;
    
    data = new unsigned char[destWidth * destHeight];

    for(int y = 0; y < srcHeight; ++y)
    {
    	for(int x = 0; x < srcWidth; ++x)
    	{
			*( data + ( y * destWidth  + x)) = *( source->buffer + ( y * srcPitch) + x);
    	}    	
    }

	glBindTexture( GL_TEXTURE_2D, glTextureID);
	glTexSubImage2D( GL_TEXTURE_2D, 0, xOffset, yOffset, destWidth, destHeight, GL_ALPHA, GL_UNSIGNED_BYTE, data);


//		0    
//		+----+
//		|    |
//		|    |
//		|    |
//		+----+
//		     1
	
	// FIXME ????
	uv[0].x = static_cast<float>(xOffset) / static_cast<float>(width);
	uv[0].y = static_cast<float>(yOffset) / static_cast<float>(height);
	uv[1].x = static_cast<float>( xOffset + destWidth) / static_cast<float>(width);
	uv[1].y = static_cast<float>( yOffset + destHeight) / static_cast<float>(height);
	
	numGreys = source->num_grays;
	advance = glyph->advance.x >> 16;
	bBox = FTBBox( glyph);

 	pos.x = bitmap->left;
	pos.y = bitmap->top;
	
	delete [] data;
	
// discard glyph image (bitmap or not)
	// Is this the right place to do this?
	FT_Done_Glyph( glyph);
}


FTTextureGlyph::~FTTextureGlyph()
{}


float FTTextureGlyph::Render( const FT_Vector& pen)
{
	glGetIntegerv( GL_TEXTURE_2D_BINDING_EXT, &activeTextureID);
	if( activeTextureID != glTextureID)
	{
		glBindTexture( GL_TEXTURE_2D, (GLuint)glTextureID);
	}
	
	glBegin( GL_QUADS);
		glTexCoord2f( uv[0].x, uv[0].y);
		glVertex2f( pen.x + pos.x,				pen.y + pos.y);

		glTexCoord2f( uv[0].x, uv[1].y);
		glVertex2f( pen.x + pos.x,				pen.y + pos.y - destHeight);

		glTexCoord2f( uv[1].x, uv[1].y);
		glVertex2f( pen.x + destWidth + pos.x,	pen.y + pos.y - destHeight);
		
		glTexCoord2f( uv[1].x, uv[0].y);
		glVertex2f( pen.x + destWidth + pos.x,	pen.y + pos.y);
	glEnd();

	return advance;

}

