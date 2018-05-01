#include	"FTOutlineGlyph.h"
#include	"FTVectoriser.h"
#include	"FTGL.h"



FTOutlineGlyph::FTOutlineGlyph( FT_Glyph glyph)
:	FTGlyph(),
	vectoriser(0),
	numPoints(0),
	numContours(0),
	contourLength(0),
	data(0),
	glList(0)
{
	if( ft_glyph_format_outline != glyph->format)
	{
		return;
	}

	vectoriser = new FTVectoriser( glyph);
	
	vectoriser->Process();
	
	numPoints = vectoriser->points();
	numContours = vectoriser->contours();
	
	if ( ( numContours < 1) || ( numPoints < 3))
	{
		delete vectoriser;
		return;
	}
	
	contourLength = new int[ numContours];
	for( int cn = 0; cn < numContours; ++cn)
	{
		contourLength[cn] = vectoriser->contourSize( cn);
	}
	
	data = new double[ numPoints * 3];
	vectoriser->GetOutline( data);
	
	delete vectoriser;
	
	int d = 0;
	glList = glGenLists(1);
	glNewList( glList, GL_COMPILE);
		for( int c = 0; c < numContours; ++c)
		{
			glBegin( GL_LINE_LOOP);
			for( int p = 0; p < contourLength[c]; ++p)
			{
				glVertex2dv( data + d);
				d += 3;
			}
			glEnd();
		}
	glEndList();

	delete [] data; // FIXME
	delete [] contourLength; // FIXME

	bBox = FTBBox( glyph);
	advance = glyph->advance.x >> 16;

	// discard glyph image (bitmap or not)
	FT_Done_Glyph( glyph); // Why does this have to be HERE
}


FTOutlineGlyph::~FTOutlineGlyph()
{
//	delete [] data;
//	delete [] contourLength;
}


float FTOutlineGlyph::Render( const FT_Vector& pen)
{
	if( glList)
	{
		glTranslatef( pen.x, pen.y, 0);
			glCallList( glList);
		glTranslatef( -pen.x, -pen.y, 0);
	}
	
	return advance;
}

