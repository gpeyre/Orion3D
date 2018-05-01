
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Q3BSP.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Q3BSP.h"



namespace OR
{
	


OR_Bsp_Loading	OR_BSP_Renderer::callback_loading=NULL;

OR_BSP_Renderer::OR_BSP_Renderer()
{
	BSPTree		= NULL;
	Buffers		= NULL;
	NormsArray	= NULL;
	NumTexs		= 0;
	NumVerts	= 0;
	Textures	= NULL;
	TVertsArray	= NULL;
	VertsArray	= NULL;
	Faces		= NULL;
	PVS			= NULL;
	CurNode		= NULL;
	Data		= NULL;
	callback_loading=default_loading;
}


OR_BSP_Renderer::~OR_BSP_Renderer()
{
	Unload();
}

void	OR_BSP_Renderer::Unload()
{
	OR_DELETE(this->BSPTree);
	OR_DELETEARRAY(this->Buffers);
	OR_DELETEARRAY(this->NormsArray);
	OR_DELETEARRAY(this->TVertsArray);
	OR_DELETEARRAY(this->VertsArray);
	OR_DELETEARRAY(this->Data);
	if (this->Faces)
	{
		for (OR_U32 i=0 ; i<NumFaces ; i++) OR_DELETE(Faces[i].Indices);
		OR_DELETEARRAY(this->Faces);
	}
	if (this->Textures)		
	{
		for (OR_U32 i=0 ; i<NumTexs ; i++) OR_DELETE(this->Textures[i]);
		OR_DELETEARRAY(this->Textures);
	}
	this->NumTexs	= 0;
	this->NumVerts	= 0;
	this->CurNode	= NULL;
}

void OR_BSP_Renderer::default_loading(OR_I32 current, OR_I32 end, char msg[])
{
	printf("%d %% loading texture %s\n",current*100/end,msg);
}

OR_Bool OR_BSP_Renderer::LoadQ3BSPFile(char *pk3name, char* bspname)
{
	OR_U32 i;
	OR_U32 size; //file size in bytes
	OR_Q3_FileHeader* Header;//file header

	OR_Archive Archive(pk3name);

	Unload();

	Data = Archive.Read(bspname , (size_t*) &size);

	if (!Data || !size) return false;

	Header = (OR_Q3_FileHeader*)Data;

	if (strncmp(Header->ID,"IBSP",4) || Header->Version != 46) return false;

	
//Load Textures
	OR_Q3_Shader* Q3Shaders = (OR_Q3_Shader*)(Data + Header->Lumps[LUMP_SHADERS].Offset);
	this->NumTexs =  Header->Lumps[LUMP_SHADERS].Length / sizeof (OR_Q3_Shader);
	Textures = new OR_Shader*[NumTexs];
	Buffers	= new OR_Stripped_Face_Buffer[NumTexs];
	OR_Float color[4]={.8f,.8f,.8f,1.0f };
	for (i=0 ; i<NumTexs ; i++)
	{
		if (strcmp("noshader",Q3Shaders[i].ShaderName))
		{
			void* Handle;
			OR_I32 n=0;
			do
			{
				Handle = Archive.GetFile(n);
				n++;
			} while (Handle && !strstr(Archive.GetFileName(Handle),Q3Shaders[i].ShaderName));
			if (Handle)
			{
				callback_loading(i,NumTexs,Q3Shaders[i].ShaderName);
				scanf("%d",&n);
	//			callback_loading(i,NumTexs,Archive.GetFileName(Handle));
			//	printf("loading texture %s\n",Archive.GetFileName(Handle));
				OR_Globals::LogManager()->AddString("   Loading texture : %s\n", Archive.GetFileName(Handle));
				OR_U32 size;
				char* lump = Archive.Read(Archive.GetFileName(Handle),(size_t*) &size);
				Textures[i] = new OR_SingleTextureMapShader(NULL, true);
				((OR_SingleTextureMapShader*)Textures[i])->LoadTextureFromMem(lump, size);
				delete[] lump;
			}
			else
				Textures[i] = new OR_FlatShader();			
		}
		else 
			Textures[i] = new OR_FlatShader();

		Textures[i]->SetAmbient(color);
		Textures[i]->SetDiffuse(color);
		Textures[i]->SetSpecular(color);
		Textures[i]->SetCullingMode(OR_Culling_Front);
		Buffers[i].Init(Textures[i],i,&CurTex);
	}


//Load Vertices
	OR_Q3_Vertex* Q3Vertices = (OR_Q3_Vertex*)(Data + Header->Lumps[LUMP_VERTICES].Offset);
	this->NumVerts = Header->Lumps[LUMP_VERTICES].Length / sizeof (OR_Q3_Vertex);
	VertsArray = new OR_Float[NumVerts*3];memset(VertsArray,0,NumVerts*3*sizeof(OR_Float));
	NormsArray = new OR_Float[NumVerts*3];memset(NormsArray,0,NumVerts*3*sizeof(OR_Float));
	TVertsArray = new OR_Float[NumVerts*3];memset(TVertsArray,0,NumVerts*3*sizeof(OR_Float));

	for (i=0 ; i<NumVerts ; i++)
	{
		memcpy(VertsArray+i*3,&Q3Vertices[i].Position,3*sizeof(OR_Float));
		memcpy(TVertsArray+i*3,&Q3Vertices[i].TexCoords,2*sizeof(OR_Float));
		memcpy(NormsArray+i*3,&Q3Vertices[i].Normal,3*sizeof(OR_Float));
	}
//Load Elements
	OR_I32* Elements = (OR_I32*)(Data + Header->Lumps[LUMP_ELEMENTS].Offset);

//Load Faces
	OR_Q3_Face* Q3Faces = (OR_Q3_Face*)(Data + Header->Lumps[LUMP_FACES].Offset);
	this->NumFaces = Header->Lumps[LUMP_FACES].Length / sizeof (OR_Q3_Face);
	Faces = new OR_Stripped_Face[NumFaces];memset(Faces,0,NumFaces*sizeof(OR_Stripped_Face));
	OR_U32 n=0;

	for (i=0 ; i<NumFaces ; i++)
		switch(Q3Faces[i].FaceType)
		{
			case FACETYPE_NORMAL:
			{
				Faces[n].NVerts = Q3Faces[i].NumVerts;// Q3Faces[i].NumElmts;
				Faces[n].FirstVert = Q3Faces[i].FirstVert;
				Faces[n].TexId = Q3Faces[i].Shader;
				Faces[n].Mode = GL_TRIANGLE_FAN;
				Faces[n].Indices = NULL;
				n++;
			}
			break;
			case FACETYPE_MESH:
			{
				Faces[n].NVerts = Q3Faces[i].NumElmts;
				Faces[n].FirstVert = Q3Faces[i].FirstVert;
				Faces[n].Indices = new OR_U32[Faces[n].NVerts];
				Faces[n].TexId = Q3Faces[i].Shader;
				Faces[n].Mode = GL_TRIANGLES;

				for (OR_I32 j=0 ; j<Faces[n].NVerts ; j++)
				{
					Faces[n].Indices[j] = Q3Faces[i].FirstVert + *(Elements + Q3Faces[i].FirstElmt + j);
					OR_ASSERT(Faces[n].Indices[j]<NumVerts);
				}
				n++;
			}
			break;
			case FACETYPE_PATCH:
			{
				//TODO: Utiliser le SurfaceTeslator de Gab
				Faces[n].NVerts = Q3Faces[i].NumVerts;
				Faces[n].FirstVert = Q3Faces[i].FirstVert;
				Faces[n].TexId = Q3Faces[i].Shader;
				Faces[n].Mode = GL_LINE_STRIP;
				Faces[n].Indices = NULL;
				n++;
				
			}
			break;
			default:
			break;
	}
		
	NumFaces = n;
//Load BSP
	OR_Q3_BSP_Node*		Q3BSPNodes	= (OR_Q3_BSP_Node*)(Data + Header->Lumps[LUMP_NODES].Offset);
	OR_Q3_BSP_Leaf*		Q3BSPLeaves = (OR_Q3_BSP_Leaf*)(Data + Header->Lumps[LUMP_LEAVES].Offset);
	OR_Q3_BSP_Plane*	Q3BSPPlanes = (OR_Q3_BSP_Plane*)(Data + Header->Lumps[LUMP_PLANES].Offset);
	OR_I32*				Q3IFaces	= (OR_I32*)(Data + Header->Lumps[LUMP_LEAF_FACES].Offset);
	OR_U32				NQ3Nodes	= Header->Lumps[LUMP_NODES].Length / sizeof(OR_Q3_BSP_Node);
	OR_U32				NQ3Leaves	= Header->Lumps[LUMP_LEAVES].Length / sizeof(OR_Q3_BSP_Leaf);

	BSPTree = LoadBSPTree(Q3BSPNodes,Q3BSPLeaves,Q3BSPPlanes,Q3IFaces,0);

//Load PVS
	PVS = (OR_Q3_PVS*)(Data + Header->Lumps[LUMP_PVS].Offset);

	return true;	
}

void OR_BSP_Renderer::SetLoadingCallback(OR_Bsp_Loading call_func)
{
	callback_loading=call_func;
}


OR_LeafyBSP_Node*	OR_BSP_Renderer::LoadBSPTree(OR_Q3_BSP_Node* Nodes, OR_Q3_BSP_Leaf* Leaves, OR_Q3_BSP_Plane* Planes, OR_I32* Faces, OR_I32 I, OR_LeafyBSP_Node* Father)
{
	OR_LeafyBSP_Node* NewNode	= new OR_LeafyBSP_Node;
	NewNode->Father = Father;
	
	if (I>=0)
	{
		OR_Q3_BSP_Node* TheNode		= (Nodes + I);
		NewNode->Type	= OR_BSP_Type_Node;
		NewNode->Plan.N	= OR_Vector3D(Planes[TheNode->Plane].Normal[0],Planes[TheNode->Plane].Normal[1],Planes[TheNode->Plane].Normal[2]);
		NewNode->Plan.d = Planes[TheNode->Plane].Distance;
		for (OR_I32 i=0 ; i<6 ; i++) NewNode->BBox[i] = TheNode->BBox[i];
		NewNode->Front	= LoadBSPTree(Nodes,Leaves,Planes,Faces,TheNode->Children[0]);
		NewNode->Back	= LoadBSPTree(Nodes,Leaves,Planes,Faces,TheNode->Children[1]);
	}
	else
	{
		OR_Q3_BSP_Leaf* TheLeaf		= (Leaves + (-1 - I));
		NewNode->Type	= OR_BSP_Type_Leaf;
		NewNode->NFaces = TheLeaf->NumFaces;
		NewNode->Faces	= new OR_U32[NewNode->NFaces];
		NewNode->Cluster= TheLeaf->Cluster;
		for (OR_U32 i=0 ; i<6 ; i++) NewNode->BBox[i] = TheLeaf->BBox[i];
		for (i=0 ; i<NewNode->NFaces ; i++)
			NewNode->Faces[i] = Faces[TheLeaf->FirstFace + i];		
	}

	return NewNode;
	
}

void	OR_BSP_Renderer::Render(OR_Camera* Cam)
{
	OR_U32 i;
	CurTex = -1;
	if (NumVerts && VertsArray)
	{
		glEnable(GL_VERTEX_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3,GL_FLOAT,0,VertsArray);
		glTexCoordPointer(3,GL_FLOAT,0,TVertsArray);
		glNormalPointer(GL_FLOAT,0,NormsArray);
		
		//for (i=0 ; i<NumFaces ; i++)
		//	Buffers[Faces[i].TexId] << (Faces+i);
		CamPos = Cam->GetAbsolutePosition();
		CamDir = -Cam->GetCamAxe(Z);
		CurNode = FindNode(BSPTree,CamPos);

		OR_Vector3D Pos	=	Cam->GetAbsolutePosition();
		OR_Vector3D Dir	=	-Cam->GetCamAxe(Z); //! Camera direction = -Z
		OR_Vector3D Up	=	Cam->GetCamAxe(Y);
		OR_Vector3D Right=	Cam->GetCamAxe(X);
		OR_Float FOV = Cam->GetFovy()*OR_PI/360;//Récupère Fovy/2. en radians
		OR_Float Aspect = Cam->GetAspect();

		
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
		OR_Globals::Context()->SetColor(.8f,.8f,.0f);DrawBBox(BSPTree);
		RenderNode(BSPTree,1);
		for (i=0 ; i<NumTexs ; i++)
			Buffers[i].Draw();
		
	}
}

OR_I32					OR_BSP_Renderer::TestBBox(OR_Float *BBox)
{
	OR_Vector3D Points[8];
	Points[0] = OR_Vector3D(BBox);
	Points[1] = OR_Vector3D(BBox+3);
	Points[2] = OR_Vector3D(BBox[0],BBox[4],BBox[2]);
	Points[3] = OR_Vector3D(BBox[0],BBox[4],BBox[5]);
	Points[4] = OR_Vector3D(BBox[0],BBox[1],BBox[5]);
	Points[5] = OR_Vector3D(BBox[3],BBox[4],BBox[2]);
	Points[6] = OR_Vector3D(BBox[3],BBox[1],BBox[2]);
	Points[7] = OR_Vector3D(BBox[3],BBox[1],BBox[5]);

	OR_I32 P[4]={0,0,0,0};
	for (OR_I32 i=0 ; i<8 ; i++)
		for (OR_I32 j=0 ; j<4 ; j++)
			if( OR_Maths::Classify(Points[i], Clipper.Planes+j)==OR_POS_FRONT ) P[j]++;

	OR_I32 r = P[0]*P[1]*P[2]*P[3];
	if (!r) return 0;//en dehors
	if (r==4096) return 1;//en dedans
	return 2;			//a cheval

}

OR_LeafyBSP_Node*	OR_BSP_Renderer::FindNode(OR_LeafyBSP_Node* Start, OR_Vector3D P)
{
	if (Start->Type == OR_BSP_Type_Node)
	{
		if( OR_Maths::Classify(P, &Start->Plan)!=OR_POS_BACK )
			return FindNode(Start->Front,P);		
		else
			return FindNode(Start->Back,P);
	}
	else
		return Start;
}

void	OR_BSP_Renderer::DrawBBox(OR_LeafyBSP_Node* Node)
{
	OR_Globals::Context()->SimpleDrawMode();
	glBegin(GL_LINES);
	glVertex3i(Node->BBox[0],Node->BBox[1],Node->BBox[2]);
	glVertex3i(Node->BBox[0],Node->BBox[1],Node->BBox[5]);
	glVertex3i(Node->BBox[0],Node->BBox[4],Node->BBox[2]);
	glVertex3i(Node->BBox[0],Node->BBox[4],Node->BBox[5]);
	glVertex3i(Node->BBox[3],Node->BBox[4],Node->BBox[2]);
	glVertex3i(Node->BBox[3],Node->BBox[4],Node->BBox[5]);
	glVertex3i(Node->BBox[3],Node->BBox[1],Node->BBox[2]);
	glVertex3i(Node->BBox[3],Node->BBox[1],Node->BBox[5]);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3i(Node->BBox[0],Node->BBox[1],Node->BBox[2]);
	glVertex3i(Node->BBox[0],Node->BBox[4],Node->BBox[2]);
	glVertex3i(Node->BBox[3],Node->BBox[4],Node->BBox[2]);
	glVertex3i(Node->BBox[3],Node->BBox[1],Node->BBox[2]);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3i(Node->BBox[0],Node->BBox[1],Node->BBox[5]);
	glVertex3i(Node->BBox[0],Node->BBox[4],Node->BBox[5]);
	glVertex3i(Node->BBox[3],Node->BBox[4],Node->BBox[5]);
	glVertex3i(Node->BBox[3],Node->BBox[1],Node->BBox[5]);
	glEnd();
	OR_Globals::Context()->NormalDrawMode();
}

void	OR_BSP_Renderer::RenderNode(OR_LeafyBSP_Node* Node, OR_Bool DoTest)
{
	OR_I32 test;
	if (CurNode->Cluster<0) return;

	
	/*if (!test) OR_Globals::Context()->SetColor(.8,0,0);else OR_Globals::Context()->SetColor(0,0,0.8);
	if (!DoTest) OR_Globals::Context()->SetColor(0,0.8,0);
	DrawBBox(Node);
	if (!test) return;*/
		
	if (Node->Type == OR_BSP_Type_Node)
	{
		if (DoTest)
		{
			test = TestBBox(Node->BBox);
			if (!test) return;
			if (test==1) DoTest=false;
		}
		/*if (CamPos.Classify(&Node->Plan)!=OR_POS_BACK)
		{*/
			RenderNode(Node->Back, DoTest);
			RenderNode(Node->Front, DoTest);
		/*}
		else
		{
			RenderNode(Node->Front);
			RenderNode(Node->Back);
		}*/		
	}
	else
	{
		if (Node->Cluster<0) return;
		if (!(BSP_TESTVIS(CurNode->Cluster,Node->Cluster))) return;

		for (OR_U32 i=0 ; i<Node->NFaces ; i++)
		{
			Buffers[Faces[Node->Faces[i]].TexId] << (Faces + Node->Faces[i]);			
		}
	}
	
}
///////////////////////////////////////////////////////////////

void	OR_Stripped_Face_Buffer::operator <<(OR_Stripped_Face* F)
{
	Faces[NumFaces]=F;
	NumFaces++;
	if (NumFaces>OR_FACE_BUFFER_SIZE) Draw();
}


void	OR_Stripped_Face_Buffer::Draw()
{
	/** \todo : Toche, turn the portal into an OR_Shadable */
#if 0
	OR_I32 i;
	if (!NumFaces) return;
	do
	{
		Shader->InializeRenderingContext();
		for (i=0 ; i<NumFaces ; i++) 
			if (Faces[i]->Indices)
				glDrawElements(Faces[i]->Mode,Faces[i]->NVerts,GL_UNSIGNED_INT,Faces[i]->Indices);
			else
				glDrawArrays(Faces[i]->Mode,Faces[i]->FirstVert,Faces[i]->NVerts);
		Shader->ResetRenderingContext();
	}
	while (Shader->NeedsAnotherPass());
	NumFaces=0;	
#endif
}


void	OR_Stripped_Face_Buffer::Init(OR_Shader* T,OR_I32 id,OR_I32* Tex)
{
	Shader=T;
	TexId=id;
	CurTex=Tex;
	NumFaces=0;
}


} // namespace OR

///////////////////////////////////////////////////////////////
