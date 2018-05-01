#include	"FTGLOutlineFont.h"
#include	"FTGlyphContainer.h"
#include	"FTGL.h"
#include	"FTOutlineGlyph.h"


FTGLOutlineFont::FTGLOutlineFont()
{}


FTGLOutlineFont::~FTGLOutlineFont()
{}


FTGlyph* FTGLOutlineFont::MakeGlyph( unsigned int g)
{
	FT_Glyph* ftGlyph = face.Glyph( g, FT_LOAD_DEFAULT);

	if( ftGlyph)
	{
		FTOutlineGlyph* tempGlyph = new FTOutlineGlyph( *ftGlyph);
		return tempGlyph;
	}

	err = face.Error();
	return NULL;
}


void FTGLOutlineFont::render( const char* string)
{	
	glPushAttrib( GL_ENABLE_BIT | GL_HINT_BIT | GL_LINE_BIT | GL_PIXEL_MODE_BIT);
	
	glEnable( GL_LINE_SMOOTH);
	glHint( GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);
 	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // GL_ONE

	FTFont::render( string);

	glPopAttrib();

}


void FTGLOutlineFont::render( const wchar_t* string)
{	
	glPushAttrib( GL_ENABLE_BIT | GL_HINT_BIT | GL_LINE_BIT | GL_PIXEL_MODE_BIT);
	
	glEnable( GL_LINE_SMOOTH);
	glHint( GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);
 	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // GL_ONE

	FTFont::render( string);

	glPopAttrib();

}

