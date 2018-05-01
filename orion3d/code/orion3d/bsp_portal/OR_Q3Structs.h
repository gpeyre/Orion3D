#ifndef _OR_Q3STRUCTS_H_
#define _OR_Q3STRUCTS_H_



namespace OR
{

	
//////////////////////////////
// .BSP File related structures :
//////////////////////////////


#pragma warning(disable : 4200)	   
///Quake 3 lump types
enum OR_Q3_LumpTypes
{
	LUMP_ENTITIES,
	LUMP_SHADERS,
	LUMP_PLANES,
	LUMP_NODES,
	LUMP_LEAVES,
	LUMP_LEAF_FACES,
	LUMP_LEAF_BRUSHES,
	LUMP_MODELS,
	LUMP_BRUSHES,
	LUMP_BRUSH_SIDES,
	LUMP_VERTICES,
	LUMP_ELEMENTS,
	LUMP_FOG,
	LUMP_FACES,
	LUMP_LIGHTMAPS,
	LUMP_LIGHTGRID,
	LUMP_PVS,
	LUMP_NLUMPS
};


///Quake 3 face types
enum OR_Q3_FaceTypes {
    FACETYPE_NORMAL	= 1,		///< Normal face (can be drawn with gl_triangle_fan)
	FACETYPE_PLANAR	= 1,		///< The same as above
    FACETYPE_PATCH	= 2,		///< Curved face (bezier)
    FACETYPE_MESH	= 3,		///< Mesh face (drawn with elements and gl_triangles)
    FACETYPE_FLARE	= 4
};

///Quake 3 .BSP lump header
struct OR_Q3_LumpHeader
{
	OR_I32 Offset;					///< Offset of the lump in the file
	OR_I32 Length;					///< Size of the lump in the file
};

/** warning C4200: nonstandard extension used : zero-sized array in struct/union */
#pragma warning( disable : 4200 )

///Quake 3 .BSP file header
struct OR_Q3_FileHeader
{
	char ID[4];					///< Must be equal to "IBSP"
	OR_I32 Version;				///< Must be equal to 46
//!!! WARNING : DO NOT REPLACE Lumps[] by *Lumps !!!!!! This will cause a crash !!
	OR_Q3_LumpHeader Lumps[];	///< Lumps headers
};

///Quake 3 Vertex
struct OR_Q3_Vertex
{
	OR_Vector3D	Position;		///< Position
	OR_Float		TexCoords[2];	///< Texcoords of the texture
	OR_Float		LightCoords[2];	///< Texcoords of the lightmap
	OR_Vector3D	Normal;			///< Normal (for vertex lighting)
	OR_I32			Color;			///< Color (for vertex lighting)
};

///Quake 3 Face
struct OR_Q3_Face
{
	OR_I32		Shader;				///< Index of the shader used in the shaders lump
	OR_I32		Unknown;			///< ?	
	OR_I32		FaceType;			///< Face type (see enum OR_Q3_Face_Type)
	OR_I32		FirstVert;			///< Index of the first vertex in the vertices lump
	OR_I32		NumVerts;			///< Number of consecutive vertices used in the vertices lump
	OR_I32		FirstElmt;			///< Index of the first element in the elements lump
	OR_I32		NumElmts;			///< Number of consecutive elements used in the elements lump
	OR_I32		NumLightmap;		///< Index of the lightmap used in the lightmaps lump
	OR_I32		LightmapOffsets[2];	///< Not sure
	OR_I32		LightmapSizes[2];	///< Not sure
	OR_Float	Origin[3];			///< Not sure
	OR_Float	BBox[6];			///< Bounding box of the face
	OR_Float	Normal[3];			///< Face normal
	OR_I32		Unknown2[2];		///< ?
};

///Quake 3 Shader
struct OR_Q3_Shader
{
	char	ShaderName[64];		///< Texture name
	OR_I32		Surface_Flags;		///< See below
	OR_I32		Content_Flags;		///< See below too
};

///Quake 3 BSP node
struct OR_Q3_BSP_Node 
{
	OR_I32		Plane;				///< Space partitioning plane
	OR_I32		Children[2];		///< Back and front child nodes
	OR_I32		BBox[6];			///< Bounding box of node
};

///Quake 3 BSP leaf
struct OR_Q3_BSP_Leaf 
{
	OR_I32		Cluster;			///< Visibility cluster number
	OR_I32		Area;				///< Volume of the leaf
	OR_I32		BBox[6];			///< Bounding box of leaf
	OR_I32		FirstFace;
	OR_I32		NumFaces;			///< Lookup for the face list (indexes are for faces)
	OR_I32		FirstBrush;
	OR_I32		NumBrushes;			///< Lookup for the brush list (indexes are for brushes)
};

///Quake 3 BSP Plane
struct OR_Q3_BSP_Plane 
{
	OR_Float	Normal[3];			///< Normal of the plane
	OR_Float	Distance;			///< Distance of the plane from origin
};

///Quake 3 PVS
struct OR_Q3_PVS 
{
	OR_I32 NumClusters;
	OR_I32 RowSize;
//WARNING : DO NOT REPLACE Data[] by *Data !!!!!! This will cause a crash !!
	unsigned char Data[];
};

#pragma warning(default : 4200)	   

/////////////////////////////////////
// Surface flags (merci Heidi Software)
/////////////////////////////////////

// Copyright (C) 1999-2000 Id Software, Inc.
//
// This file must be identical in the quake and utils directories

// contents flags are seperate bits
// a given brush can contribute multiple content bits

// these definitions also need to be in q_shared.h!

#define	CONTENTS_SOLID			1		// an eye is never valid in a solid
#define	CONTENTS_LAVA			8
#define	CONTENTS_SLIME			16
#define	CONTENTS_WATER			32
#define	CONTENTS_FOG			64

#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000
//bot specific contents types
#define	CONTENTS_TELEPORTER		0x40000
#define	CONTENTS_JUMPPAD		0x80000
#define CONTENTS_CLUSTERPORTAL	0x100000
#define CONTENTS_DONOTENTER		0x200000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_BODY			0x2000000	// should never be on a brush, only in game
#define	CONTENTS_CORPSE			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes not used for the bsp
#define	CONTENTS_STRUCTURAL		0x10000000	// brushes used for the bsp
#define	CONTENTS_TRANSLUCENT	0x20000000	// don't consume surface fragments inside
#define	CONTENTS_TRIGGER		0x40000000
#define	CONTENTS_NODROP			0x80000000	// don't leave bodies or items (death fog, lava)

#define	SURF_NODAMAGE			0x1		// never give falling damage
#define	SURF_SLICK				0x2		// effects game physics
#define	SURF_SKY				0x4		// lighting from environment map
#define	SURF_LADDER				0x8
#define	SURF_NOIMPACT			0x10	// don't make missile explosions
#define	SURF_NOMARKS			0x20	// don't leave missile marks
#define	SURF_FLESH				0x40	// make flesh sounds and effects
#define	SURF_NODRAW				0x80	// don't generate a drawsurface at all
#define	SURF_HINT				0x100	// make a primary bsp splitter
#define	SURF_SKIP				0x200	// completely ignore, allowing non-closed brushes
#define	SURF_NOLIGHTMAP			0x400	// surface doesn't need a lightmap
#define	SURF_POINTLIGHT			0x800	// generate lighting info at vertexes
#define	SURF_METALSTEPS			0x1000	// clanking footsteps
#define	SURF_NOSTEPS			0x2000	// no footstep sounds
#define	SURF_NONSOLID			0x4000	// don't collide against curves with this set
#define SURF_LIGHTFILTER		0x8000	// act as a light filter during q3map -light
#define	SURF_ALPHASHADOW		0x10000	// do per-pixel light shadow casting in q3map
#define	SURF_NODLIGHT			0x20000	// don't dlight even if solid (solid lava, skies)



} // namespace OR

#endif //_OR_Q3STRUCTS_H_