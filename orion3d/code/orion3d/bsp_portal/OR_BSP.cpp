/*------------------------------------------------------------------------------*/
/*                     OR_BSP.cpp                                               */
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_BSP.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_BSP.h"

namespace OR
{
	
OR_BSP_Node::OR_BSP_Node()
{
	Front	= NULL;
	Back	= NULL;
}


OR_BSP_Node::~OR_BSP_Node()
{
	OR_DELETE( Front );
	OR_DELETE( Back );
}

OR_BSP_Node*	OR_BSP_Node::FindLeaf( OR_Vector3D P )
{
	if( Type == OR_BSP_Type_Node )
	{
		if( OR_Maths::Classify( P, &Plan ) == OR_POS_FRONT ) 
			return Front->FindLeaf( P );
		else 
			return Back->FindLeaf( P );
	}
	else 
		return this;
}


OR_Bool	OR_BSP_Node::IsInWall( OR_Vector3D P )
{
	if( Type == OR_BSP_Type_Node )
	{
		if( OR_Maths::Classify( P, &Plan ) != OR_POS_BACK ) 
			return Front->IsInWall( P );
		else return Back->IsInWall( P );
	}
	else return IsSolid;
}


OR_Bool	OR_BSP_Node::IsInWall( OR_Vector3D P, OR_Float Rayon )
{
	if( Type == OR_BSP_Type_Node )
	{
		if( OR_Maths::Classify( P, &Plan, Rayon ) != OR_POS_BACK ) 
			return Front->IsInWall( P, Rayon );
		else return Back->IsInWall( P, Rayon );
	}
	else return IsSolid;
}



OR_Bool found=false;

OR_Bool	OR_BSP_Node::FindIntersection( OR_Vector3D P1, OR_Vector3D P2, OR_Vector3D &Result, OR_Plane* &P, OR_BSP_Node* &Leaf )
{
	/*On a atteint un feuille :*/
	if( Type == OR_BSP_Type_Leaf )
	{
		if( IsSolid )
		{
			Result=P1;
			Leaf=this;
			return true;
		}
		else
		{
			Result=P2;
			return false;
		}
	}

	/*On a atteint une branche :*/
	OR_Position C1 = OR_Maths::Classify( P1, &Plan );
	OR_Position C2 = OR_Maths::Classify( P2, &Plan );

	/*Les deux OR_Vector3Ds sont du meme cote :*/	
	if( C1 == OR_POS_FRONT && C2 == OR_POS_FRONT ) return Front->FindIntersection( P1, P2, Result, P, Leaf );
	if( C1 == OR_POS_BACK && C2 == OR_POS_BACK ) return Back->FindIntersection( P1, P2, Result, P, Leaf );

	/*P1 devant et P2 derriere :*/
	if( C1 == OR_POS_FRONT && C2 == OR_POS_BACK )
	{
		OR_Vector3D P3 = Plan.FindIntersection( P1, P2 );
		if( Front->FindIntersection( P1, P3, Result, P, Leaf ) ) return true;
		if( Back->FindIntersection( P3, P2, Result, P, Leaf) ) 
		{
			if( P == NULL ) P = &Plan;
			return true;
		}
		return false;
	}

	/*P2 devant et P1 derriere :*/
	if( C2 == OR_POS_FRONT && C1 == OR_POS_BACK )
	{
		OR_Vector3D P3 = Plan.FindIntersection( P1, P2 );
		if( Back->FindIntersection( P1, P3, Result, P, Leaf ) ) return true;
		if( Front->FindIntersection( P3, P2, Result, P, Leaf ) ) 
		{
			if( P == NULL) P = &Plan;
			return true;
		}
		return false;
	}

	/*P1 sur le plan :*/
	if( C1 == OR_POS_LIE )
	{
		if( C2 == OR_POS_FRONT ) 
		{
			if( Front->FindIntersection( P1, P2, Result, P, Leaf ) )
			{
				if( P == NULL ) P = &Plan;
				return true;
			}
			return false;
		}
		else
		{
			if( Back->FindIntersection( P1, P2, Result, P, Leaf ) )
			{
				if( P == NULL ) P = &Plan;
				return true;
			}
			return false;
		}
	}

	/*P2 sur le plan :*/
	if( C1 == OR_POS_FRONT ) 
		return Front->FindIntersection( P1, P2, Result, P, Leaf );
	else
		return Back->FindIntersection( P1, P2, Result, P, Leaf );
}



OR_Bool	OR_BSP_Node::FindIntersection(OR_Vector3D P1,OR_Vector3D P2,OR_Vector3D &Result,OR_Plane* &P,OR_Float Rayon)
{
	/*On a atteint un feuille :*/
	if (Type==OR_BSP_Type_Leaf) {
		if (IsSolid) {Result=P1;return true;}
		else		 {Result=P2;return false;}
	}

	/*On a atteint une branche :*/
	OR_Position C1=OR_Maths::Classify(P1, &Plan, Rayon),C2=OR_Maths::Classify(P2, &Plan, Rayon);

	/*Les deux OR_Vector3Ds sont du meme cote :*/	
	if (C1==OR_POS_FRONT && C2==OR_POS_FRONT) return Front->FindIntersection(P1,P2,Result,P,Rayon);
	if (C1==OR_POS_BACK && C2==OR_POS_BACK) return Back->FindIntersection(P1,P2,Result,P,Rayon);

	/*P1 devant et P2 derriere :*/
	if (C1==OR_POS_FRONT && C2==OR_POS_BACK)
	{
		OR_Vector3D P3=Plan.FindIntersection(P1,P2,Rayon);
		if (Front->FindIntersection(P1,P3,Result,P,Rayon)) return true;
		if (Back->FindIntersection(P3,P2,Result,P,Rayon)) {if (P==NULL) P=&Plan;return true;}
		return false;
	}

	/*P2 devant et P1 derriere :*/
	if (C2==OR_POS_FRONT && C1==OR_POS_BACK)
	{
		OR_Vector3D P3=Plan.FindIntersection(P1,P2,Rayon);
		if (Back->FindIntersection(P1,P3,Result,P,Rayon)) return true;
		if (Front->FindIntersection(P3,P2,Result,P,Rayon)) {if (P==NULL) P=&Plan;return true;}
		return false;
	}

	/*P1 sur le plan :*/
	if (C1==OR_POS_LIE)
	{
		if (C2==OR_POS_FRONT) 
		{
			if (Front->FindIntersection(P1,P2,Result,P,Rayon)) {if (P==NULL) P=&Plan;return true;}
			return false;
		}
		else
		{
			if (Back->FindIntersection(P1,P2,Result,P,Rayon)) {if (P==NULL) P=&Plan;return true;}
			return false;
		}
	}

	/*P2 sur le plan :*/
	if (C1==OR_POS_FRONT) 
		return Front->FindIntersection(P1,P2,Result,P,Rayon);
		else
		return Back->FindIntersection(P1,P2,Result,P,Rayon);
}





/*
OR_BSP_Node::OR_BSP_Node(TypNode T, OR_Bool Solid, OR_I32 NF, Face* IF, OR_I32 NB, Face* IB, OR_BSP_Node* Fa=NULL, OR_BSP_Node* F=NULL, OR_BSP_Node* B=NULL)
{
	Type		=	T;
	Father		=	Fa;
	Front		=	F;
	Back		=	B;
	NumFrontFaces	=	NF;
	NumBackFaces	=	NB;
	FrontFaces		=   IF;
	BackFaces		=   IB;
	IsSolid		=	Solid;
};
*/


void	OR_BSP_Node::Load(FILE* Fichier)
{

	ImportType(&Type, Fichier);
			
	if (Type==OR_BSP_Type_Leaf)
	{
		xfread(&IsSolid   ,sizeof(OR_Bool),1,Fichier);
		xfread(&HasPortals,sizeof(OR_Bool),1,Fichier);
		
		if (HasPortals)
		{
			xfread(&NTargets,sizeof(OR_U32),1,Fichier);
			
			Targets=new OR_U32[NTargets];
			xfread(Targets,sizeof(OR_U32),(unsigned long)NTargets,Fichier);
		}
	}
	else
	{
		/******************************************************************
		 * DANGER: this breaks if OR_Plane or OR_Vector3D are ever changed *
		 ******************************************************************/
		xfread(&Plan,sizeof(OR_Float),4,Fichier);
		
		Back = new OR_BSP_Node;
		Front = new OR_BSP_Node;
		Back->Load(Fichier);
		Front->Load(Fichier);
	}
}

OR_Float	FindInter(OR_Vector3D P1,OR_Vector3D P2,OR_Plane P)
{
	return  ( ( (P.N*P.d) - P1 ) * P.N ) / ( (P2 - P1) * P.N );
}

OR_Float	FindInter(OR_Vector3D P1,OR_Vector3D P2,OR_Plane P,OR_Float Rayon)
{
	return  ( ( (P.N*(P.d+Rayon)) - P1 ) * P.N ) / ( (P2 - P1) * P.N );
}


} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////