#ifndef		__FTGlyph__
#define		__FTGlyph__

#include "FTGL.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H


class FTGL_EXPORT FTBBox
{
	public:
		FTBBox()
		:	x1(0),
			y1(0),
			z1(0),
			x2(0),
			y2(0),
			z2(0)
		{}
		
		FTBBox( FT_Glyph glyph)
		{
			FT_BBox bbox;
			FT_Glyph_Get_CBox( glyph, ft_glyph_bbox_subpixels, &bbox );
			
			x1 = bbox.xMin >> 6;
			y1 = bbox.yMin >> 6;;
			z1 = 0;
			x2 = bbox.xMax >> 6;;
			y2 = bbox.yMax >> 6;;
			z2 = 0;	
		}		
		
		FTBBox( int a, int b, int c, int d, int e, int f)
		:	x1(a),
			y1(b),
			z1(c),
			x2(d),
			y2(e),
			z2(f)
		{}

		~FTBBox()
		{}
	
		// Make these ftPoints
		int x1, y1, z1, x2, y2, z2;

	protected:
	
	
	private:
};


/**
 * FTGlyph is the base class for FTGL glyphs.
 *
 * It provides the interface between Freetype glyphs and their openGL
 * renderable counterparts. This is an abstract class and derived classes
 * must implement the <code>render</code> function. 
 * 
 * @see FTGlyphContainer
 *
 */
class FTGL_EXPORT FTGlyph
{
	public:
		/**
		 * Constructor
		 */
		FTGlyph();

		/**
		 * Destructor
		 */
		virtual ~FTGlyph();

		/**
		 * Renders this glyph at the current pen position.
		 *
		 * @param pen	The current pen position.
		 * @return		The advance distance for this glyph.
		 */
		virtual float Render( const FT_Vector& pen) = 0;
		
		/**
		 * Return the advance width for this glyph.
		 *
		 * @return	advance width.
		 */
		float Advance() const { return advance;}
		
		/**
		 * Return the bounding box for this glyph.
		 *
		 * @return	bounding box.
		 */
		FTBBox BBox() const { return bBox;}
		
		/**
		 * Queries for errors.
		 *
		 * @return	The current error code.
		 */
		FT_Error Error() const { return err;}
		
	protected:
		/**
		 * The advance distance for this glyph
		 */
		float advance;

		/**
		 * Vector from the pen position to the topleft corner of the glyph
		 */
		FT_Vector pos;

		
		/**
		 * A freetype bounding box
		 */
		FTBBox bBox;
		
		/**
		 * Current error code. Zero means no error.
		 */
		FT_Error err;
		
	private:

};


#endif	//	__FTGlyph__

