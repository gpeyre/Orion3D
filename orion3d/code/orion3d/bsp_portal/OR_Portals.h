/*----------------------------------------------------------------------*/
/*                                  OR_Portals.h						*/
/*----------------------------------------------------------------------*/
/*        ecrite par Antoche											*/
/*----------------------------------------------------------------------*/
/* UTILISATION :														*/
/*	Tout ce qu'il faut savoir c'est savoir utiliser la classe			*/
/*	OR_Portal_Renderer, qui articule toutes les pieces du puzzle. Pour	*/
/*	bien commencer il faut donc appeler la fonction LoadKSP(), histoire	*/
/*	d'avoir une scene sur laquelle bosser. Il serait aussi bon d'appeler*/
/*	au moins une fois Reshape() pour avoir un clipper adequat. Enfin,	*/
/*	maintenant que c'est fait vous pouvez appeler Render() et			*/
/*	FindIntersection() qui, je pense, se passent de commentaires supple-*/
/*	mentaires. Enfin si, tout de meme un : StartArea. En effet, c'est a	*/
/*	vous de savoir dans quelle cellule se trouve votre camera ou votre	*/
/*	point de depart. Si vous ne le savez pas, eh ben y'a toujours		*/
/*	FindArea().															*/
/*----------------------------------------------------------------------*/
/*! \file OR_Portals.h
    \brief Les classes necessaires a la gestion des objets statiques.
    
	Tout ce qu'il faut savoir c'est savoir utiliser la classe OR_Portal_Renderer, qui articule toutes les pieces du puzzle.
	Pour bien commencer il faut donc appeler la fonction LoadKSP(), histoire d'avoir une scene sur laquelle bosser.
	Il serait aussi bon d'appeler au moins une fois Reshape() pour avoir un clipper adequat. 
	Enfin, maintenant que c'est fait vous pouvez appeler Render() et FindIntersection() qui, je pense, se passent de commentaires supplementaires.
	
	Enfin si, tout de meme un : StartArea. 
	En effet, c'est a vous de savoir dans quelle cellule se trouve votre camera ou votre point de depart.
	Si vous ne le savez pas, eh ben y'a toujours FindArea().
*/


#ifndef _OR_PORTALS_H_
#define _OR_PORTALS_H_

#include "../configuration/OR_Config.h"
#include "OR_BSP.h"
#include "../maths/OR_Maths.h"
#include "../maths/OR_Plane.h"
#include "../objects/OR_Camera.h"
#include "../misc/OR_Endian_Conv.h"
#include "../shaders/OR_Shader.h"
#include "../shaders/OR_SingleTextureMapShader.h"
#include "../shaders/OR_FlatShader.h"

namespace OR
{
	
///Face buffers size
#define  OR_FACE_BUFFER_SIZE 512
///Maximum planes number for a clipper
#define  OR_CLIPPER_MAX_SIDES 20

class	OR_Portal_Renderer;
/*-----------------------------------------------------------------------*/
/*                              classe OR_Single_Face                    */
/*-----------------------------------------------------------------------*/
/*	Utilise par la classe OR_Face_Buffer pour definir une face par ses	 */
/*	vertex et sa texture												 */
/*-----------------------------------------------------------------------*/

/******************************************************************************
 * WARNING: Don't Modify this without consulting OR_Portal_Renderer::LoadKSP!!*
 * the endian conversion algorithms depend on this!							  *
 ******************************************************************************/
///Defines a triangle by its 3 points inidices and its texture id
typedef struct OR_Single_Face
{

	//Les 3 indices referencant les 3 vertex de la face
	OR_U32	Indices[3];
	//Id de la texture
	OR_I32		TexId;

}OR_Single_Face;


/*-----------------------------------------------------------------------*/
/*                              classe OR_Face_Buffer                    */
/*-----------------------------------------------------------------------*/
/*	Utilise pour le rendu. Permet de faire le rendu des faces par texture*/
/*	Chaque face buffer correspond a une texture unique et a une liste de */
/*	vertex utilisant cette texture										 */
/*-----------------------------------------------------------------------*/

/*! \ingroup group_static
 *  \brief class OR_Face_Buffer in group group static
 */

/// Utilise pour le rendu. Permet de faire le rendu des faces par texture.

/** 
	Chaque face buffer correspond a une texture unique et a une liste de vertex utilisant cette texture.
*/

typedef class OR_Face_Buffer
{
friend class OR_Portal_Renderer;
	//Pointeur sur la texture
	OR_Shader*	Shader;
	//Id correspondant a la texture
	OR_I32			TexId;
	//Nombre de vertex dans la liste
	OR_I32			NumIndices;
	//Liste des points
	OR_U32		Indices[OR_FACE_BUFFER_SIZE+4];
	//Pointeur sur le portal renderer (pour savoir quelle est la texture courante)
	OR_I32*		CurTex;

public:
	//Procedure d'initialisation : permet d'assigner une texture et un id au face buffer
	//et de definir le renderer associe
	void	Init(OR_Shader* T,OR_I32 id, OR_I32* Tex);
	
	//operateur << : permet d'ajouter une face au face buffer. Le pointeur passe doit pointer
	//sur 3 OR_U32 (les trois points)
	void	operator<<(OR_U32* F);
	
	//Envoie la liste des points a OpenGL puis la vide
	void	Draw();
}OR_Face_Buffer;


/*-----------------------------------------------------------------------*/
/*                              classe OR_Clipper                        */
/*-----------------------------------------------------------------------*/
/*	Un clipper definit une pyramide (a 3 faces ou +) de clipping. Utilise*/
/*	par le portal Renderer pour clipper les portals au moment du rendu	 */
/*-----------------------------------------------------------------------*/

/*! \ingroup group_static
 *  \brief class OR_Clipper in group group static
 */

/// Un clipper definit une pyramide (a 3 faces ou +) de clipping.
	
/** 
	Utilise par le portal Renderer pour clipper les portals au moment du rendu.
*/
typedef struct OR_Clipper
{

	//Nombre de plans de clipping
	OR_U32		NumPlanes;
	//Liste des faces du clipper
	OR_Plane	Planes[OR_CLIPPER_MAX_SIDES];

}OR_Clipper;


/*-----------------------------------------------------------------------*/
/*                              classe OR_Portal                         */
/*-----------------------------------------------------------------------*/
/*	Portail menant aux differentes cellules								 */
/*-----------------------------------------------------------------------*/

/*! \ingroup group_static
 *  \brief class OR_Portal in group group static
 */

/// Portail menant aux differentes cellules	
/** 
	Antoche, a toi de jouer ...
	Et oui, c'est dur la vie ;)	
*/
typedef class OR_Portal
{
friend class OR_Portal_Renderer;
	//Nombre de points du portal
	OR_U32		NumPoints;
	//Liste des points du portal
	OR_Vector3D*	Points;
	//Id de la cellule vue a travers le portal
	OR_U32		Target;
	//Booleen utilise pour le rendu ou l'intersection
	OR_Bool		Drawn;
	//Pointeur sur le portal jumeau (portal ayant les meme points mais inverse)
	OR_Portal*	Twin;

public:
	//Trace les contours du portal ; utilise uniquement dans le debug
	void	Draw();
	
	//Initialise les variables du portal
	void	Init(OR_U32 NumPoints,OR_Vector3D* Points,OR_U32 Target);
}OR_Portal;


/*-----------------------------------------------------------------------*/
/*                              classe OR_Area                           */
/*-----------------------------------------------------------------------*/
/*	Cellule contenant les objets a dessiner et les portals menant aux	 */
/*	autres cellules														 */
/*-----------------------------------------------------------------------*/

/*! \ingroup group_static
 *  \brief class OR_Area in group group static
 */

/// Cellule contenant les objets a dessiner et les portals menant aux autres cellules.
/** 
	Antoche, a toi de jouer ...
	Et oui, c'est dur la vie ;)	
*/
typedef class OR_Area
{

friend class OR_Portal_Renderer;

	//Pointeur sur le BSP associe a la cellule
	OR_BSP_Node*	BSP;
	//Nombre de faces dans la cellule
	OR_U32			NumFaces;
	//Liste des faces de la cellule
	OR_Single_Face*	FaceList;

	//Nombre de portals partant de la cellule
	OR_U32			NumPortals;
	//Liste des portals
	OR_Portal*		Portals;

	//booleen utilise pour le rendu et la detection de collision	
	OR_Bool			Drawn;

public:

	//Constructeur
	OR_Area();
	
	//Initialise les variables
	void			Init(OR_BSP_Node* BSP, OR_U32 NumPortals, OR_Portal* Portals, OR_U32 NumFaces, OR_Single_Face* FaceList);

}OR_Area;


/*-----------------------------------------------------------------------*/
/*                              classe OR_Portal_Renderer                */
/*-----------------------------------------------------------------------*/
/*	Classe principale : manager des areas et des portals				 */
/*-----------------------------------------------------------------------*/

/*! \ingroup group_static
 *  \brief class OR_Portal_Renderer in group group static
 */

/// Classe principale : manager des areas et des portals
/** 
	Antoche, a toi de jouer ...
	Et oui, c'est dur la vie ;)	
*/
typedef class ORION3D_API OR_Portal_Renderer
{
friend class OR_Area;
	//Vertex arrays contenant tous les vertex de la scene ;
	//Coordonnees
	OR_Float*			VertsArray;
	//Texcoords
	OR_Float*			TVertsArray;
	//Normales
	OR_Float*			NormsArray;
	//Nombre de vertex (le meme pour chaque array)
	OR_U32			NumVerts;
	//Nombre de cellules contenues dans la scene
	OR_U32			NumAreas;
	//Liste des cellules de la scene
	OR_Area*		Areas;
	//Nombre de portals contenues dans la scene
	OR_U32			NumPortals;
	//Liste des portals de la scene
	OR_Portal*		Portals;
	//Nombre de textures utilisees dans la scene
	OR_U32			NumTexs;
	//Liste des textures
	OR_Shader**		Textures;
	//Face buffers (autant que de textures)
	OR_Face_Buffer*	Buffers;
public:
	//Constructeur. Initialise tout a 0
	OR_Portal_Renderer();
	//Destructeur. Vide la memoire utilisee
	~OR_Portal_Renderer();
	
	//Charge un fichier KSP
	OR_I32				LoadKSP(char* name);
	
	//Effecture le rendu de la scene a partir de la camera et de la cellule specifiees
	void			Render(OR_Camera* Cam,OR_U32 StartArea);
		
	//Renvoie le point d'intersection le plus proche a partir de P1 vers P2
	/* Utilisation :
		P1 : point de depart du rayon (parametre d'entree)
		P2 : point d'arrivee du rayon (parametre d'entree)
		Result : point d'intersection (parametre de retour)
		P : pointeur sur le plan sur lequel vient buter le rayon (parametre mixte). DOIT ETRE NULL a l'entree.
			Si le rayon ne bute sur aucun mur, vaut NULL (cas oò P1 est deja dans un mur)
		Valeur de retour : true s'il y a eu intersection
	*/
	OR_Bool			FindIntersection(OR_U32 StartArea, OR_Vector3D P1,OR_Vector3D P2,OR_Vector3D &Result,OR_Plane* &P);
	//Renvoie l'id de l'area contenant le point Pos
	OR_U32			FindArea(OR_Vector3D Pos);
	//Vide la memoire utilisee
	void			Unload();
	//Texture courante (pour les face buffers)
	OR_I32				CurTex;
private:
	//Met a jour les infos sur les portal jumeaux
	void			BuildLinks();
	//Dessine une area et les ares visibles a partir de celle-ci (recursive)
	void			Draw(OR_U32 AIndex,OR_Vector3D Pos, OR_Clipper Clipper);
	//Force le rendu de tous les face buffers
	void			Flush();
}OR_Portal_Renderer;


} // namespace OR

#endif //_OR_PORTALS_H_
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