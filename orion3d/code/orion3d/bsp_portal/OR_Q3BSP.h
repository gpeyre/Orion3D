#ifndef _OR_Q3BSP_H_
#define _OR_Q3BSP_H_

/** \file 
	Contains the definition of Q3 BSP handling methods.
	\author Antoche.
**/

#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"
#include "../maths/OR_Plane.h"
#include "OR_Portals.h"
#include "OR_Q3Structs.h"
#include "OR_Portals.h"
#include "../utils/OR_Archive.h"



namespace OR
{


// taken from aftershock:
// PVS test macro:  PVS table is a packed single bit array, rowsize
// bytes times numclusters rows
#define BSP_TESTVIS(from,to) (*(PVS->Data + (from)*PVS->RowSize + ((to)>>3)) & (1 << ((to) & 7)))

///Node of a Leafy BSP Tree
struct OR_LeafyBSP_Node
{
	OR_BSP_Node_Type	Type;
	OR_LeafyBSP_Node*	Father;
//For nodes
	OR_Plane			Plan;
	OR_LeafyBSP_Node*	Front;
	OR_LeafyBSP_Node*	Back;
//For leaves
	OR_I32 Cluster;
	OR_U32 Area;
	OR_U32 *Faces;
	OR_U32 NFaces;
	OR_Float	BBox[6];
};

///Multiple vertices face
struct OR_Stripped_Face
{
	OR_I32		NVerts;
	OR_I32		TexId;
	OR_I32		FirstVert;
	OR_U32*	Indices;
	GLenum	Mode;
};

///Pipeline buffer using multiple vertices face
class OR_Stripped_Face_Buffer
{
	///Pointeur sur la texture
	OR_Shader*			Shader;
	///Id correspondant a la texture
	OR_I32					TexId;
	///Nombre de faces dans la liste
	OR_I32					NumFaces;
	///Liste des points
	OR_Stripped_Face*	Faces[OR_FACE_BUFFER_SIZE+4];
	///Pointeur sur le portal renderer (pour savoir quelle est la texture courante)
	OR_I32*				CurTex;

public:
	///Procedure d'initialisation : permet d'assigner une texture et un id au face buffer
	///et de definir le renderer associe
	void	Init(OR_Shader* T,OR_I32 id, OR_I32* Tex);
	
	///operateur << : permet d'ajouter une face au face buffer. Le pointeur passe doit pointer
	///sur 3 OR_U32 (les trois points)
	void	operator<<(OR_Stripped_Face* F);
	
	///Envoie la liste des points a OpenGL puis la vide
	void	Draw();
};

///Manages and renders an map using a BSP and a PVS
class ORION3D_API OR_BSP_Renderer
{
private:
	OR_LeafyBSP_Node* BSPTree;
	///Vertex arrays contenant tous les vertex de la scene ;
	///Coordonnees
	OR_Float*			VertsArray;
	///Texcoords
	OR_Float*			TVertsArray;
	///Normales
	OR_Float*			NormsArray;
	///Nombre de vertex (le meme pour chaque array)
	OR_U32			NumVerts;
	///Nombre de textures utilisees dans la scene
	OR_U32			NumTexs;
	///Liste des textures
	OR_Shader**		Textures;
	///Face buffers (autant que de textures)
	OR_Stripped_Face_Buffer*	Buffers;
	///Current used shader
	OR_I32				CurTex;
	///Faces
	OR_Stripped_Face*	Faces;
	///Faces number
	OR_U32			NumFaces;
	///Current camera position
	OR_Vector3D		CamPos;
	///Current viewing direction
	OR_Vector3D		CamDir;
	///Possible visible set
	OR_Q3_PVS*		PVS;
	///Current Node (where the camera is)
	OR_LeafyBSP_Node*	CurNode;
	///Current clipper (view frustum)
	OR_Clipper			Clipper;
	///File content
	char*			Data;

	/// la callback qui pour le chargement des bsp
	static OR_Bsp_Loading		callback_loading;

	/// la callback de base
	static void default_loading(OR_I32 current, OR_I32 end, char msg[]);

	void					DrawBBox(OR_LeafyBSP_Node* Node);
	OR_I32						TestBBox(OR_Float *BBox);
	OR_LeafyBSP_Node*		FindNode(OR_LeafyBSP_Node* Start, OR_Vector3D P);
	OR_LeafyBSP_Node*		LoadBSPTree(OR_Q3_BSP_Node* Nodes, OR_Q3_BSP_Leaf* Leaves, OR_Q3_BSP_Plane* Planes, OR_I32* Faces, OR_I32 I, OR_LeafyBSP_Node* Father=NULL);
public:
	///Constructeur. Initialise tout a 0
	OR_BSP_Renderer();
	///Destructeur. Vide la memoire utilisee
	~OR_BSP_Renderer();

	void	Render(OR_Camera* Cam);
	///Load a .bsp file from a .pk3 file
	///@param pk3name path of the .pk3 archive
	///@param bspname path of the .bsp file into the pk3 archive
	OR_Bool	LoadQ3BSPFile(char *pk3name, char* bspname);
	void	SetLoadingCallback(OR_Bsp_Loading call_func);
	void	Unload();
	void	RenderNode(OR_LeafyBSP_Node* Node, OR_Bool DoTest);
};


} // namespace OR

#endif //_OR_Q3BSP_H_