/*----------------------------------------------------------------------*/
/*                                  OR_BSP.h							*/
/*----------------------------------------------------------------------*/
/*        ecrite par Antoche											*/
/*----------------------------------------------------------------------*/
/* UTILISATION :														*/
/*	En fait tous les BSP sont geres par le portal renderer, donc t'as	*/
/*	meme pas a savoir comment utiliser les BSP, d'ailleurs t'as meme	*/
/*	pas besoin de savoir que les collisions sont gerees par des BSP, et	*/
/*	pi d'abord t'as meme pas a etre ici alors degage !					*/
/*----------------------------------------------------------------------*/

/** \file 
	Contains the definition of BSP handling methods.
	\author Antoche.
**/

#ifndef _OR_BSP_H_
#define _OR_BSP_H_

#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"
#include "../maths/OR_Plane.h"
#include "../misc/OR_Endian_Conv.h"

namespace OR
{

	

//Types possibles pour un noeud : Node ou Leaf
enum OR_BSP_Node_Type { OR_BSP_Type_Leaf , OR_BSP_Type_Node };




/*-----------------------------------------------------------------------*/
/*                              classe OR_BSP_Node						 */
/*-----------------------------------------------------------------------*/
/*	Noeud d'un BSP														 */
/*-----------------------------------------------------------------------*/

/*! \ingroup group_static
 *  \brief class OR_BSP_Node in group group static
 */

/// Noeud d'un BSP.
/** 
	Antoche, a toi de jouer ...
	Et oui, c'est dur la vie ;)	
*/
typedef class OR_BSP_Node
{
friend class OR_Portal_Renderer;
private:

	//Type du noeud (noeud/feuille)
	OR_BSP_Node_Type	Type;

	//Special feuille :
	//Feuille solide ou non
	OR_Bool		IsSolid;
	//Plan contenant des portals ou non
	OR_Bool		HasPortals;
	//Nombre d'areas vers lesquelles menent les portals
	OR_U32		NTargets;
	//Liste des areas vers lesquelles menent les portals
	OR_U32*		Targets;

	//Special noeud :
	//Plan de coupure du noeud
	OR_Plane	Plan;
	//Fils Avant
	OR_BSP_Node*	Front;
	//Fils Arriere
	OR_BSP_Node*	Back;

public:
	//Constructeur
	OR_BSP_Node();
	
	//Destructeur (recursif)
	~OR_BSP_Node();
	
	//Charge un BSP a partir d'un fichier KSP
	void			Load(FILE* Fichier);
	
	//Dit si un point se trouve dans une feuille solide (COLLISION DECTECTION)
	OR_Bool			IsInWall(OR_Vector3D P);
	
	//Dit si une bounding sphere se trouve dans une feuille solide par dynamic shtifting (COLLISION DECTECTION)
	OR_Bool			IsInWall(OR_Vector3D P,OR_Float Rayon);
	
	//Renvoie le point d'intersection le plus proche a partir de P1 vers P2
	/* Utilisation :
		P1 : point de depart du rayon (parametre d'entree)
		P2 : point d'arrivee du rayon (parametre d'entree)
		Result : point d'intersection (parametre de retour)
		P : pointeur sur le plan sur lequel vient buter le rayon (parametre mixte). DOIT ETRE NULL a l'entree.
			Si le rayon ne bute sur aucun mur, vaut NULL (cas oò P1 est deja dans un mur)
		Leaf : feuille correspondant au mur touche
		Valeur de retour : true s'il y a eu intersection
	*/
	OR_Bool			FindIntersection(OR_Vector3D P1,OR_Vector3D P2,OR_Vector3D &Result,OR_Plane* &P, OR_BSP_Node* &Leaf);

	//!!! PAS ENCORE TERMINE !!!
	//Renvoie le point d'intersection d'une bounding sphere le plus proche a partir de P1 vers P2 pra dynamic shifting
	/* Utilisation :
		P1 : point de depart du rayon (parametre d'entree)
		P2 : point d'arrivee du rayon (parametre d'entree)
		Result : point d'intersection (parametre de retour)
		P : pointeur sur le plan sur lequel vient buter le rayon (parametre mixte). DOIT ETRE NULL a l'entree.
			Si le rayon ne bute sur aucun mur, vaut NULL (cas oò P1 est deja dans un mur)
		Leaf : feuille correspondant au mur touche
		Valeur de retour : true s'il y a eu intersection
	*/
	OR_Bool			FindIntersection(OR_Vector3D P1,OR_Vector3D P2,OR_Vector3D &Result,OR_Plane* &P, OR_Float Rayon);
	
	//Renvoie la feuille dans laquelle se trouve le point (DEBUG)
	OR_BSP_Node*	FindLeaf(OR_Vector3D P);

}OR_BSP_Node;



} // namespace OR

#endif //_OR_BSP_H_


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