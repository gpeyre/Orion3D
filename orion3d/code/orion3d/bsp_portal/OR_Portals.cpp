/*---------------------------------------------------------------------*/
/*                               OR_Portal                             */
/*---------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Portal.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Portals.h"

namespace OR
{
	
OR_Area::OR_Area()
{
	NumFaces=0;
	NumPortals=0;
}

void	OR_Area::Init(OR_BSP_Node* B, OR_U32 numPortals, OR_Portal* portals, OR_U32 NumF, OR_Single_Face* F)
{
	BSP = B;
	NumPortals = numPortals;
	Portals = portals;
	NumFaces = NumF;
	FaceList = F;
}


///////////////////////////////////////////////////////////////

OR_Portal_Renderer::OR_Portal_Renderer()
{
	NumAreas=0;NumVerts=0;NumPortals=0;NumTexs=0;
	VertsArray	= NULL;
	TVertsArray	= NULL;
	NormsArray	= NULL;
	Areas		= NULL;
	Portals		= NULL;
	Textures	= NULL;
	Buffers		= NULL;
}


OR_Portal_Renderer::~OR_Portal_Renderer()
{
	Unload();
}


void	OR_Portal_Renderer::Unload()
{
	OR_DELETEARRAY(VertsArray);
	OR_DELETEARRAY(TVertsArray);
	OR_DELETEARRAY(NormsArray);
	OR_DELETEARRAY(Areas);
	OR_DELETEARRAY(Portals);
	OR_DELETEARRAY(Textures);
	OR_DELETEARRAY(Buffers);
	NumAreas=0;NumVerts=0;NumPortals=0;NumTexs=0;
}

OR_I32		OR_Portal_Renderer::LoadKSP(char* name)
{

	FILE* Fichier = fopen(name,"rb");
	OR_U32 Version, j;
	char Buffer[3];
	const OR_I32 MAXLEN = 100;
	char *basepath, *tmp_basep;

	/* check if file exists */
	if (!Fichier) {
		fprintf(stderr, "error opening file '%s'\n", name);
		return 0;
	}
	
	/* 
	 * get the base of the filename 
	 */
	basepath = (char *)malloc(sizeof(char)*(strlen(name) + 1));
	memset(basepath,0,strlen(name) + 1);
	
	/* find the last slash in the path */	
	tmp_basep = strrchr(name,OR_SLASH[0]);
	/* and get the basename */
	memcpy(basepath,name,(unsigned long)(tmp_basep-name)+1);
			
	/* make sure the file is a KSP file */
	xfread(Buffer,1,3,Fichier);
	if (strncmp("KSP",Buffer,3)!=0) return 0;

	/* get the version number */
	xfread(&Version,sizeof(OR_U32), 1, Fichier);
	/* 
	 * Note: the following method contains INV* and inv* calls.  The purpose
	 * of these calls is to invert the datatypes read in from the KSP file
	 * from big-endian (Intel PC style) to little-endian (Mac/Unix style)
	 * encoding.
	 */
	 
	/***************************************************************************
	 *WARNING: This is based on the assumption that KSP files are only created *
	 * on PCs!!!! (this should change soon w/ addition of magic numbers to the *
	 * header of the file)													   *
	 ***************************************************************************/
	 
	if (Version==300)
	{
		Unload();
		xfread(&NumTexs,sizeof(OR_U32),1,Fichier);
		
		Textures = new OR_Shader*[NumTexs];
		Buffers = new OR_Face_Buffer[NumTexs];
		
		for (j=0; j<NumTexs; j++)
		{
			OR_Float	Ambient[4], Diffuse[4], Specular[4], Shine;
			char	Name[MAXLEN];
			char	TexPath[MAXLEN];
			OR_I32		Id;

			xfread(&Id     ,  sizeof(OR_I32),      1, Fichier);
			xfread(TexPath ,	 	    1, MAXLEN, Fichier);
			xfread(Ambient ,sizeof(OR_Float),      4, Fichier);
			xfread(Diffuse ,sizeof(OR_Float),      4, Fichier);
			xfread(Specular,sizeof(OR_Float),      4, Fichier);
			xfread(&Shine  ,sizeof(OR_Float),      1, Fichier);
			xfread(Name    ,            1, MAXLEN, Fichier);

			OR_Shader* shader;

			if (TexPath && *TexPath) {
				convpath(TexPath,basepath);
				shader = new OR_SingleTextureMapShader(TexPath);
			}
			else
				shader = new OR_FlatShader();

			shader->SetAmbient(Ambient);
			shader->SetDiffuse(Diffuse);
			shader->SetSpecular(Specular);
			//shader->SetEmission(Emission);
			shader->SetShine(Shine*100);
			shader->SetCullingMode(OR_Culling_Front);

			Textures[Id] = shader;
			Buffers[j].Init(Textures[Id],Id,&CurTex);
		}

		xfread(&NumVerts,sizeof(OR_U32),1,Fichier);

		VertsArray	= new OR_Float[NumVerts*3];
		TVertsArray	= new OR_Float[NumVerts*3];
		NormsArray	= new OR_Float[NumVerts*3];

		xfread(VertsArray,	sizeof(OR_Float),	(unsigned long)NumVerts*3,	Fichier);
		xfread(TVertsArray,	sizeof(OR_Float),	(unsigned long)NumVerts*3,	Fichier);
		xfread(NormsArray,	sizeof(OR_Float),	(unsigned long)NumVerts*3,	Fichier);

		OR_U32	NumFaces;
		OR_Single_Face*	Faces;
		
		xfread(&NumFaces,sizeof(OR_U32),1,Fichier);
		
		/**************************************************************
		 * DANGER: this breaks if OR_Single_Face is ever changed      *
		 **************************************************************/
		Faces = new OR_Single_Face[NumFaces];
		xfread(Faces,sizeof(OR_U32),(unsigned long)NumFaces*4,Fichier);
		
		xfread(&NumAreas,sizeof(OR_U32),1,Fichier);

		OR_U32* AreasOffsets	= new OR_U32[NumAreas];
		OR_U32* AreasSizes	= new OR_U32[NumAreas];

		xfread(AreasOffsets,sizeof(OR_U32),(unsigned long)NumAreas,Fichier);
		xfread(AreasSizes  ,sizeof(OR_U32),(unsigned long)NumAreas,Fichier);

		OR_U32* PortalsOffsets	= new OR_U32[NumAreas];
		OR_U32* PortalsSizes		= new OR_U32[NumAreas];
		
		xfread(PortalsOffsets,sizeof(OR_U32),(unsigned long)NumAreas,Fichier);
		xfread(PortalsSizes  ,sizeof(OR_U32),(unsigned long)NumAreas,Fichier);
		xfread(&NumPortals   ,sizeof(OR_U32),       1,Fichier);
		
		Portals = new OR_Portal[NumPortals];
		for (OR_U32 p=0;p<NumPortals;p++)
		{
			xfread(&Portals[p].Target,sizeof(OR_U32),1,Fichier);
			xfread(&Portals[p].NumPoints,sizeof(OR_U32),1,Fichier);

			Portals[p].Points=new OR_Vector3D[Portals[p].NumPoints];
			for (OR_U32 j=0;j<Portals[p].NumPoints;j++)
			{
				OR_U32 N;
				xfread(&N,sizeof(OR_U32),1,Fichier);
				
				Portals[p].Points[j] = OR_Vector3D(&VertsArray[N*3]);
			}

		}


		OR_BSP_Node** BSPArray = new OR_BSP_Node*[NumAreas];
		for (OR_U32 a=0;a<NumAreas;a++)
		{
			BSPArray[a] = new OR_BSP_Node;
			BSPArray[a]->Load(Fichier);
		}
			
		
		fclose(Fichier);


		Areas = new OR_Area[NumAreas];

		for(OR_U32 i=0; i<NumAreas; i++) 
			Areas[i].Init( 	 BSPArray[i], 
							 PortalsSizes[i],
							&Portals[PortalsOffsets[i]],
							 AreasSizes[i],
							&Faces[AreasOffsets[i]]
						 );

		BuildLinks();


		glEnable(GL_VERTEX_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3,GL_FLOAT,0,VertsArray);
		glTexCoordPointer(3,GL_FLOAT,0,TVertsArray);
		glNormalPointer(GL_FLOAT,0,NormsArray);
	}

	else if (Version==310)
	{
		Unload();
		fread(&NumTexs,1,sizeof(OR_U32),Fichier);
		Textures = new OR_Shader*[NumTexs];
		Buffers = new OR_Face_Buffer[NumTexs];
		for (OR_U32 t=0;t<NumTexs;t++)
		{
			OR_Float	Ambient[4], Diffuse[4], Specular[4], Shine;
			char	Name[100];
			char	TexPath[100];
			OR_I32		Id;

			fread(&Id,sizeof(OR_I32),1,Fichier);
			fread(TexPath,100,1,Fichier);
			fread(Ambient,1,sizeof(OR_Float)*4,Fichier);
			fread(Diffuse,1,sizeof(OR_Float)*4,Fichier);
			fread(Specular,1,sizeof(OR_Float)*4,Fichier);
			fread(&Shine,1,sizeof(OR_Float),Fichier);
			fread(Name,100,1,Fichier);

			OR_Shader* shader;

			if (TexPath && *TexPath) {
				shader = new OR_SingleTextureMapShader(TexPath);
			}
			else
				shader = new OR_FlatShader();

			shader->SetAmbient(Ambient);
			shader->SetDiffuse(Diffuse);
			shader->SetSpecular(Specular);
			//shader->SetEmission(Emission);
			shader->SetShine(Shine*100);

			Textures[Id] = shader;
			Buffers[t].Init(Textures[Id],Id,&CurTex);
		}

		

		fread(&NumVerts,1,sizeof(OR_U32),Fichier);

		VertsArray	= new OR_Float[NumVerts*3];
		TVertsArray	= new OR_Float[NumVerts*3];
		NormsArray	= new OR_Float[NumVerts*3];

		fread(VertsArray,	1,	NumVerts*3*sizeof(OR_Float),	Fichier);
		fread(TVertsArray,	1,	NumVerts*3*sizeof(OR_Float),	Fichier);
		fread(NormsArray,	1,	NumVerts*3*sizeof(OR_Float),	Fichier);




		OR_U32	NumFaces;
		OR_Single_Face*	Faces;
		
		fread(&NumFaces,1,sizeof(OR_U32),Fichier);
		Faces = new OR_Single_Face[NumFaces];
		fread(Faces,1,NumFaces*4*sizeof(OR_U32),Fichier);

		fread(&NumPortals,1,sizeof(OR_U32),Fichier);
		Portals = new OR_Portal[NumPortals];
		for (OR_U32 p=0;p<NumPortals;p++)
		{
			fread(&Portals[p].Target,1,sizeof(OR_U32),Fichier);
			fread(&Portals[p].NumPoints,1,sizeof(OR_U32),Fichier);
			Portals[p].Points=new OR_Vector3D[Portals[p].NumPoints];
			for (OR_U32 j=0;j<Portals[p].NumPoints;j++)
			{
				OR_Vector3D V;
				fread(&V,1,sizeof(OR_Vector3D),Fichier);
				Portals[p].Points[j] = V;
			}

		}

		fread(&NumAreas,1,sizeof(OR_U32),Fichier);
		Areas = new OR_Area[NumAreas];
		for (OR_U32 i=0;i<NumAreas;i++)
		{
			OR_U32	FacesOffset;
			OR_U32	NumFaces;
			OR_U32	PortalsOffset;
			OR_U32	NumPortals;
			OR_BSP_Node*	BSP = new OR_BSP_Node;

			fread(&FacesOffset,1,sizeof(OR_U32),Fichier);
			fread(&NumFaces,1,sizeof(OR_U32),Fichier);
			fread(&PortalsOffset,1,sizeof(OR_U32),Fichier);
			fread(&NumPortals,1,sizeof(OR_U32),Fichier);
			BSP->Load(Fichier);

			Areas[i].Init(BSP,NumPortals,&Portals[PortalsOffset],NumFaces,&Faces[FacesOffset]);
		}

		
		fclose(Fichier);



		BuildLinks();


		glEnable(GL_VERTEX_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3,GL_FLOAT,0,VertsArray);
		glTexCoordPointer(3,GL_FLOAT,0,TVertsArray);
		glNormalPointer(GL_FLOAT,0,NormsArray);
	}
	else
	{
		/* the gizmo is not a cube one */
		OR_Globals::MessageHandler()->Debug("OR_Portal_Renderer::LoadKSP", 
						"KSP Version non supportee");
		return OR_Error_Opening_File;
	}



	return 1;

}

void	OR_Portal_Renderer::Render(OR_Camera* Cam,OR_U32 StartArea)
{
    OR_U32 a, b;
	OR_U32 i=StartArea;//Area dans laquelle se trouve la cam»ra
	if (i>=NumAreas) return;
#ifdef _DEBUG
	printf("%d:",i);
#endif //_DEBUG
	OR_Float FOV = Cam->GetFovy()*OR_PI/360;//Récupère Fovy/2. en radians
	OR_Float Aspect = Cam->GetAspect();
	
	for (a=0;a<NumAreas;a++) Areas[a].Drawn=false;
	for (b=0;b<NumPortals;b++) Portals[b].Drawn=false;
	
	OR_Vector3D Pos	=	Cam->GetAbsolutePosition();
	OR_Vector3D Dir	=	-Cam->GetCamAxe(Z); //! Camera direction = -Z
	OR_Vector3D Up	=	Cam->GetCamAxe(Y);
	OR_Vector3D Right=	Cam->GetCamAxe(X);

	OR_Clipper Clipper;
	OR_Vector3D Norm = Up*cos(FOV) + Dir*sin(FOV);
	OR_Float D = Pos*Norm;
	Clipper.Planes[0].N=Norm;
	Clipper.Planes[0].d=D;

	Norm= -Up*cos(FOV) + Dir*sin(FOV);D = Pos*Norm;
	Clipper.Planes[1].N=Norm;Clipper.Planes[1].d=D;
	
	Norm= Right*cos(FOV)/Aspect + Dir*sin(FOV);D = Pos*Norm;
	Clipper.Planes[2].N=Norm;Clipper.Planes[2].d=D;
	
	Norm= -Right*cos(FOV)/Aspect + Dir*sin(FOV);D = Pos*Norm;
	Clipper.Planes[3].N=Norm;Clipper.Planes[3].d=D;

	Clipper.NumPlanes=4;
	this->CurTex=-1;
	Draw(i,Pos,Clipper);
#ifdef _DEBUG
	OR_Globals::Context()->SetColor(1,0,0);
	OR_Globals::Context()->SimpleDrawMode();
	glBegin(GL_LINES);
	for (i=0;i<NumVerts;i++)
	{
		glVertex3fv(&VertsArray[3*i]);
		glVertex3f(VertsArray[3*i] + NormsArray[3*i], VertsArray[3*i+1] + NormsArray[3*i+1], VertsArray[3*i+2] + NormsArray[3*i+2]);
	}
	glEnd();
	OR_Globals::Context()->NormalDrawMode();
	OR_Globals::Context()->SetColor(1,1,1);
#endif //_DEBUG
	Flush();
	for (a=0;a<NumAreas;a++) Areas[a].Drawn=false;

#ifdef _DEBUG
	printf("\n");
#endif //_DEBUG
}


void	OR_Portal_Renderer::Draw(OR_U32 AIndex,OR_Vector3D Pos, OR_Clipper Clipper)
{
	OR_U32 i;
	OR_Area* A=&Areas[AIndex];
	OR_Bool Drawn=A->Drawn;
	A->Drawn=true;

#ifdef _DEBUG
	printf("(");
#endif //_DEBUG

	for (i=0;i<A->NumPortals;i++) if (!A->Portals[i].Drawn)
	{
		OR_Bool Visible=false;
		
		Visible=true;
		OR_U32* Values=new OR_U32[Clipper.NumPlanes];memset(Values,0,(unsigned long)Clipper.NumPlanes*4);
		for (OR_U32 j=0;j<A->Portals[i].NumPoints;j++)
		{
			for (OR_U32 k=0;k<Clipper.NumPlanes;k++)
				if( OR_Maths::Classify(A->Portals[i].Points[j], &Clipper.Planes[k])==OR_POS_BACK ) Values[k]++;
		}
		for (OR_U32 k=0;k<Clipper.NumPlanes;k++) if (Values[k]==A->Portals[i].NumPoints) {Visible=false;}



		if (Visible)
		{
			A->Portals[i].Drawn=true;
			A->Portals[i].Twin->Drawn=true;
			OR_Clipper C;
			C.NumPlanes=A->Portals[i].NumPoints;
			for (OR_U32 p=0;p<A->Portals[i].NumPoints;p++)
			{
				OR_Vector3D Normale=!((A->Portals[i].Points[p]-Pos)^(A->Portals[i].Points[(p+1)%A->Portals[i].NumPoints]-Pos));
				OR_Float D=Pos*Normale;
				C.Planes[p].d=D;
				C.Planes[p].N=Normale;
#ifdef _DEBUG
				OR_Vector3D Bary=(A->Portals[i].Points[p] + A->Portals[i].Points[(p+1)%A->Portals[i].NumPoints])/2;
				OR_Globals::Context()->SetColor(1,1,1);
				OR_Globals::Context()->SimpleDrawMode();
				glBegin(GL_LINES);
				glVertex3fv((OR_Float*)&Bary);
				Bary+=Normale;
				glVertex3fv((OR_Float*)&Bary);
				glEnd();
				OR_Globals::Context()->SetDefaultColor();
				OR_Globals::Context()->NormalDrawMode();
#endif //_DEBUG

			}

#ifdef _DEBUG
			OR_Globals::Context()->SetColor(1,1,1);
			A->Portals[i].Draw();
			printf("%d:",A->Portals[i].Target);
#endif //_DEBUG
			Draw(A->Portals[i].Target,Pos,C);
		}
	}

	if (Drawn) 
	{
#ifdef _DEBUG
		printf("x)");
#endif //_DEBUG
		return;
	}

	for (i=0;i<A->NumFaces;i++) 
		Buffers[A->FaceList[i].TexId]<<A->FaceList[i].Indices;

#ifdef _DEBUG
	printf(")");
#endif //_DEBUG

}

void	OR_Portal_Renderer::Flush()
{
	for (OR_U32 i=0;i<NumTexs;i++) 
		if (Buffers[i].NumIndices) Buffers[i].Draw();
}


OR_U32	OR_Portal_Renderer::FindArea(OR_Vector3D Pos)
{
	for (OR_U32 i=0;i<NumAreas;i++) if (!Areas[i].BSP->IsInWall(Pos)) return i;
	return -1;
}


OR_Bool	OR_Portal_Renderer::FindIntersection(OR_U32 StartArea, OR_Vector3D P1,OR_Vector3D P2,OR_Vector3D &Result,OR_Plane* &P)
{
	OR_BSP_Node* Leaf;
	if (StartArea==-1) return false;
	if (Areas[StartArea].BSP->FindIntersection(P1,P2,Result,P,Leaf) && P)
	{
	  //OR_Plane* CurPlane=P;
		Areas[StartArea].Drawn=true;
		if (Leaf->HasPortals)
			for (OR_U32 i=0;i<Leaf->NTargets;i++) 
			{
				if (!Areas[Leaf->Targets[i]].Drawn)
				{
					OR_ASSERT(Leaf->Targets[i]<NumAreas);
					OR_Plane* TempPlane=NULL;
					OR_Vector3D PS=Result;
					if (FindIntersection(Leaf->Targets[i],PS,P2,Result,TempPlane))
					{
						if (TempPlane) P=TempPlane;
					}
				}
			}

		return true;
	}
	return false;
}



void	OR_Portal_Renderer::BuildLinks()
{
	for (OR_U32 i=0;i<NumAreas;i++)
	{
		for (OR_U32 j=0;j<Areas[i].NumPortals;j++)
		{
			for (OR_U32 k=0;k<Areas[Areas[i].Portals[j].Target].NumPortals;k++) 
				if (Areas[Areas[i].Portals[j].Target].Portals[k].Target==i && Areas[Areas[i].Portals[j].Target].Portals[k].NumPoints==Areas[i].Portals[j].NumPoints)
				{
					OR_Bool equal=true;
					for (OR_U32 l=0;l<Areas[i].Portals[j].NumPoints;l++)
						if(Areas[Areas[i].Portals[j].Target].Portals[k].Points[l]!=Areas[i].Portals[j].Points[Areas[i].Portals[j].NumPoints-1-l])  equal=false;
					if (equal) Areas[i].Portals[j].Twin=&(Areas[Areas[i].Portals[j].Target].Portals[k]);
				}				
		}
	}
}
///////////////////////////////////////////////////////////////

void	OR_Face_Buffer::operator <<(OR_U32* F)
{
	memcpy(&Indices[NumIndices],F,12);
	NumIndices+=3;
	if (NumIndices>OR_FACE_BUFFER_SIZE) Draw();
}


void	OR_Face_Buffer::Draw()
{
	/** \todo : Toche, turn the portal into an OR_Shadable */
#if 0
	if (!NumIndices) return;
	do
	{
		Shader->InializeRenderingContext();
		glDrawElements(GL_TRIANGLES,NumIndices,GL_UNSIGNED_INT,Indices);
		Shader->ResetRenderingContext();
	}
	while (Shader->NeedsAnotherPass());
	NumIndices=0;	
#endif
}


void	OR_Face_Buffer::Init(OR_Shader* T,OR_I32 id,OR_I32* Tex)
{
	Shader=T;
	TexId=id;
	CurTex=Tex;
	NumIndices=0;
}


///////////////////////////////////////////////////////////////

void	OR_Portal::Draw()
{
	OR_Globals::Context()->SimpleDrawMode();
	glBegin(GL_LINE_LOOP);
	for (OR_U32 i=0;i<NumPoints;i++)	glVertex3fv((OR_Float*)&Points[i]);
	glEnd();
	OR_Globals::Context()->NormalDrawMode();
}

void	OR_Portal::Init(OR_U32 N,OR_Vector3D* P,OR_U32 T)
{
	NumPoints=N;
	Points=P;
	Target=T;
}


} // namespace OR

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
