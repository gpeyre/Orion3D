#include	"FTGLPixmapFont.h"
#include	"FTGlyphContainer.h"
#include	"FTPixmapGlyph.h"


FTGLPixmapFont::FTGLPixmapFont()
{}


FTGLPixmapFont::~FTGLPixmapFont()
{}


FTGlyph* FTGLPixmapFont::MakeGlyph( unsigned int g)
{
	FT_Glyph* ftGlyph = face.Glyph( g, FT_LOAD_DEFAULT);

	if( ftGlyph)
	{
		FTPixmapGlyph* tempGlyph = new FTPixmapGlyph( *ftGlyph);
		return tempGlyph;
	}

	err = face.Error();
	return NULL;
}


void FTGLPixmapFont::render( const char* string)
{	
	glPushAttrib( GL_ENABLE_BIT | GL_PIXEL_MODE_BIT);

	glEnable(GL_BLEND);
 	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	FTFont::render( string);

	glPopAttrib();

}


void FTGLPixmapFont::render( const wchar_t* string)
{	
	glPushAttrib( GL_ENABLE_BIT | GL_PIXEL_MODE_BIT);

	glEnable(GL_BLEND);
 	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	FTFont::render( string);

	glPopAttrib();

}


