#ifndef		__FTVectoriser__
#define		__FTVectoriser__

#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "FTGL.h"

#include "FTGlyph.h"

using namespace std;

#ifndef CALLBACK
#define CALLBACK
#endif

/**
 * ftPoint class is a basic 3 dimensional point for holding outline font
 * point data.
 *
 * @see	FTOutlineGlyph
 * @see	FTPolyGlyph
 *
 */
class FTGL_EXPORT ftPoint
{
	public:
		/**
		 * Default constructor. Point is set to zero.
		 */
		ftPoint()
		: x(0), y(0), z(0)
		{}
		
		/**
		 * Constructor.
		 *
		 * @param X
		 * @param Y
		 * @param Z
		 */
		ftPoint( const double X, const double Y, const double Z)
		: x(X), y(Y), z(Z)
		{}
		
		/**
		 * Operator == Tests for eqaulity
		 *
		 * @param a
		 * @param b
		 * @return
		 */
		friend bool operator == ( const ftPoint &a, const ftPoint &b);

		/**
		 * Operator != Tests for non equality
		 *
		 * @param a
		 * @param b
		 * @return
		 */
		friend bool operator != ( const ftPoint &a, const ftPoint &b);
		
		/**
		 * The point data
		 */
		double x, y, z; // FIXME make private
		
	private:
};


/**
 * FTContour class is a container of points that describe an outline
 * point data.
 *
 * @see	FTOutlineGlyph
 * @see	FTPolyGlyph
 * @see	ftPoint
 *
 */
class FTGL_EXPORT FTContour
{
	public:
		/**
		 * Default constructor
		 */
		FTContour()
		:	kMAXPOINTS( 1000)
		{	
			pointList.reserve( kMAXPOINTS);
		}

		/**
		 *	Destructor
		 */
		~FTContour()
		{
			pointList.clear();
		}

		/**
		 * Add a point to the end of this contour.
		 *
		 * Doesn't add the point if it's already on the end or the start
		 * of the contour. The Z component is always 0
		 *
		 * @param x	The X component of the point
		 * @param y The Y component of the point
		 */
		void AddPoint( const double x, const double y)
		{
			ftPoint point( x, y, 0.0); 
			
			// Eliminate duplicate points.
			if( pointList.empty() || ( pointList[pointList.size() - 1] != point && pointList[0] != point))
			{
				pointList.push_back( point);
			}
		}

		/**
		 * How many points define this contour
		 *
		 * @return the number of points in this contour
		 */
		int size() const { return pointList.size();}

		/**
		 *	The list of points in this contour
		 */
		vector< ftPoint> pointList;
		
	private:
		/**
		* A 'max' number of points that this contour holds. Note however it
		* can hold more than this number. It is just used to reserve space
		* in the <vector>
		*/
		const unsigned int kMAXPOINTS;
};


class FTGL_EXPORT FTTesselation
{
	public:
		FTTesselation()
		{
			pointList.reserve( 128);
		}

		~FTTesselation()
		{
			pointList.clear();
		}

		
		void AddPoint( const double x, const double y, const double z)
		{	
			pointList.push_back( ftPoint( x, y, z));
		}


		int size() const { return pointList.size();}

		GLenum meshType;
		vector<ftPoint> pointList;
	private:
		
};


class FTGL_EXPORT FTMesh
{
	public:
		FTMesh();
		~FTMesh();
		
		void AddPoint( const double x, const double y, const double z);
		void Begin( GLenum m);
		void End();
		
		double* Point();
		int size() const;
		
		void Error( GLenum e) { err = e;}
		GLenum Error() const { return err;}

		vector< ftPoint> tempPool;
		vector< FTTesselation*> tess;
	protected:
	
	private:
		/**
		 *	The list of points in this mesh
		 */
		FTTesselation* tempTess;
		GLenum err;

};


/**
 * FTVectoriser class is a helper class that converts font outlines into
 * point data. It includes a bezier curve evaluator
 *
 * @see	FTOutlineGlyph
 * @see	FTPolyGlyph
 * @see	FTContour
 * @see	ftPoint
 *
 */
class FTGL_EXPORT FTVectoriser
{
	public:
		/**
		 * Constructor
		 *
		 * @param glyph The freetype glyph to be processed
		 */
		FTVectoriser( FT_Glyph glyph);

		/**
		 *	Destructor
		 */
		virtual ~FTVectoriser();

		/**
		 * Process the freetype outline data into contours of points
		 *
		 * @return <code>true</code> on success
		 */
		bool Process();

		/**
		 * Copy the outline data into a block of <code>doubles</code>
		 *
		 * @param d	a pointer to the memory to copy the data into.
		 */
		void GetOutline( double* d);

		/**
		 * Build a mesh from the outline and copy the vertex data into a
		 * block of <code>doubles</code>
		 *
		 * @param zNormal	The direction of the z axis of the normal
		 * for this mesh
		 */
		void MakeMesh( int zNormal = 1.0);
		
		/**
		 * Copy the tesselation data into a block of <code>doubles</code>
		 *
		 * @param d	a pointer to the memory to copy the data into.
		 */
		void GetMesh( double* d);
		
		/** Get the number of points in the tesselation
		 *
		 * @return the number of points.
		 */
		int MeshPoints() const { return mesh->size();}
		
		/**
		 * Get the total count of points in this outline
		 *
		 * @return the number of points
		 */
		int points();

		/**
		 * Get the count of contours in this outline
		 *
		 * @return the number of contours
		 */
		int contours() const { return contourList.size();}

		/**
		 * Get the nuber of points in a contour in this outline
		 *
		 * @param c		The contour index
		 * @return		the number of points in contour[c]
		 */
		int contourSize( int c) const { return contourList[c]->size();}

		/**
		 * Get the flag for the tesselation rule for this outline
		 *
		 * @return The contour flag
		 */
		int ContourFlag() const { return contourFlag;}
		
	private:
		/**
		 * Process a conic ( second order bezier curve)
		 *
		 * @param index	The index of the current point in the point list.
		 * @param first	The index into the pointlist of the first point in
		 *				the contour that the current point is part of.
		 * @param last	The index into the pointlist of the last point in
		 *				the contour that the current point is part of.
		 * @return 		the number of control points processed
		 */
		int Conic( const int index, const int first, const int last);

		/**
		 * Process a cubic ( third order) bezier curve
		 *
		 * @param index	The index of the current point in the point list.
		 * @param first	The index into the pointlist of the first point in
		 *				the contour that the current point is part of.
		 * @param last	The index into the pointlist of the last point in
		 *				the contour that the current point is part of.
		 * @return 		the number of control points processed
		 */
		int Cubic( const int index, const int first, const int last);

		/**
		 * @param a
		 * @param b
		 */
		void deCasteljau( const float t, const int n);

		/**
		 * @param a
		 */
		void evaluateCurve( const int n);

		/**
		 * The list of contours in this outline
		 */
		vector< const FTContour*> contourList;
			
		/**
		 * A Mesh for tesselations
		 */
		FTContour* contour;
			
		/**
		 * A Mesh for tesselations
		 */
		FTMesh* mesh;

		/**
		* A flag indicating the tesselation rule for this outline
		 */
		int contourFlag;

		/**
		 * A Freetype outline
		 */
		FT_Outline ftOutline;
		
		/**
		 */
		 // Magic numbers -- #define MAX_DEG 4
		float bValues[4][4][2];	//3D array storing values of de Casteljau algorithm.
		float ctrlPtArray[4][2]; // Magic numbers
		
		/**
		 */
		const float kBSTEPSIZE;

};


#endif	//	__FTVectoriser__
