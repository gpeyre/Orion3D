#include "stdafx.h"
#include "OR_3DS_Wrapper.h"


OR_3DSWrapper::OR_3DSWrapper(IUtil* _IUtility, Interface* _MAXInterface, OR_Toolkit* _Engine)
{
	this->IUtility		= _IUtility;
	this->MAXInterface	= _MAXInterface;
	this->Engine		= _Engine;
	this->Time			= 0;
	this->SamplingEnd	= 4800;
	this->SamplingStart = 0;
	this->SamplingForce = false;
	this->SamplingRate  = 4800/30;
	this->SamplingTreshold = OR_PI/18.;
}


OR_3DSWrapper::~OR_3DSWrapper()
{
	this->MaxToOrionMtlMap.clear();
}



void	OR_3DSWrapper::SetInterface(Interface* _MAXInterface)
{
	this->MAXInterface = _MAXInterface;
}


void	OR_3DSWrapper::SetIUtil(IUtil* _IUtility)
{
	this->IUtility = _IUtility;
}

void	OR_3DSWrapper::SetTime(TimeValue _Time)
{
	this->Time	= _Time;
}

void	OR_3DSWrapper::SetEngine(OR_Toolkit* _Engine)
{
	this->Engine = _Engine;
}


OR_3DS_Node*	OR_3DSWrapper::Update( int Flags, OR_3DS_Node* Root )
{
	if( !Engine || !MAXInterface || !IUtility || !Flags ) return Root;

	if( Engine->GetShaderManager().GetNbElements() == 0 ) Flags |= OR_Update_Materials;
	
	if( Flags & OR_Update_Materials )
	{
		if( Engine ) Engine->GetLogManager().AddLine( "\nUpdating shaders" );
		if( Engine ) Engine->GetLogManager().AddIndent();
		
		this->RetrieveSceneMaterials();

		if( Engine ) Engine->GetLogManager().SubIndent();
		if( Engine ) Engine->GetLogManager().AddLine( "\nFinish updating shaders" );
	}
	
	if( Flags & OR_Update_Hierarchy )
	{
		if( Engine ) Engine->GetLogManager().AddLine("\nUpdating objects...");
		if( Engine ) Engine->GetLogManager().AddIndent();

		//delete all objects
		INode*	 MAXNode = MAXInterface->GetRootNode();
		OR_Node* Father = NULL;
		OR_AnimationPlayer* AnimationRoot = NULL;
		if( Root )
		{
			//If the root has an animation, keep it to set it to the new root
			if( !Root->GetPlayerList().empty() )
			{
				AnimationRoot = Root->GetPlayerList().front();
				Root->GetPlayerList().pop_front();
				Root->RemoveAllPlayers();
			}
			//Save the MAX Node and the father
			MAXNode = Root->GetMAXNode();
			Father = Root->GetFather();
			//erase the tree
			Father->RemoveSon( *Root );
			OR_DELETE( Root );
			//Remove all objects that are not in the hiearchy tree anymore
			Engine->GetMeshManager().RemoveUnusedObjects();
			Engine->GetSkinManager().RemoveUnusedObjects();
			Engine->GetMeshDataManager().RemoveUnusedObjects();
			Engine->GetCameraManager().RemoveUnusedObjects();
			Engine->GetLightManager().RemoveUnusedObjects();
		}
		Root = this->RetrieveNode_Rec( MAXNode, Father );
		OR_ASSERT( Root->GetObject() );
		
		if( Father )
		{
			Father->AddSonLast(*Root);
		}
		//If the former Root had an animation, bind the animation to the new root
		if( AnimationRoot )
		{
			Root->AddPlayer(*AnimationRoot);
		}
		//Met à jour les skins
		for( IT_ManagerMap_Template( OR_Skin ) it = OR_Globals::SkinManager()->begin() ; it != OR_Globals::SkinManager()->end() ; ++it )
		{
			OR_Skin* TheSkin = (*it).second;
			for( OR_U32 b = 0; b < TheSkin->GetNbrBones() ; ++b )
			{
				INode* MAXBone =  (INode*)( TheSkin->GetBone( b ) );
				OR_3DS_Node* ORBone = OR_3DS_Utils::FindNode( Root, MAXBone );
				OR_ASSERT( ORBone!=NULL );
				ORBone->GetObject()->SetIsSkinningBone( true );
				TheSkin->SetBone( b, ORBone->GetObject() );
			}
		}
		
		if( Engine ) Engine->GetLogManager().SubIndent();
		if( Engine ) Engine->GetLogManager().AddLine( "\nFinish updating objects" );
	}
	//Le else est là pour éviter d'updater les matrices si les objets ont
	//été updatés (les matrices sont alors à jour)
	else
	{
		if( Flags & OR_Update_Matrices )
		{
			if( Engine ) Engine->GetLogManager().AddLine( "\nUpdating matrices" );
			if( Engine ) Engine->GetLogManager().AddIndent();
			
			this->UpdateMatrices_Rec( Root );

			if( Engine ) Engine->GetLogManager().SubIndent();
			if( Engine ) Engine->GetLogManager().AddLine( "\nFinish updating matrices" );
		}
	}

	if( Flags & OR_Update_Targets )
	{
		if( Engine ) Engine->GetLogManager().AddLine( "\nUpdating targets" );
		if( Engine ) Engine->GetLogManager().AddIndent();
		
		this->UpdateTargets( Root, Root );

		if( Engine ) Engine->GetLogManager().SubIndent();
		if( Engine ) Engine->GetLogManager().AddLine( "\nFinish updating targets" );
	}


	if( Flags & OR_Apply_Shaders )
	{
		if( Engine ) Engine->GetLogManager().AddLine( "\nApplying shaders" );
		if( Engine ) Engine->GetLogManager().AddIndent();

		this->ApplyShaders_Rec( Root );

		if( Engine ) Engine->GetLogManager().SubIndent();
		if( Engine ) Engine->GetLogManager().AddLine( "\nFinish applying shaders" );		
	}

	if( Flags & OR_Update_Animations )
	{
		if( Engine ) Engine->GetLogManager().AddLine( "\nUpdating animations" );
		if( Engine ) Engine->GetLogManager().AddIndent();
		
		Root->RemoveAllPlayers();
		OR_Animation* Anim = ((OR_3DS_MAXNode*)Root->GetMAXNode())->GetOR_Animation( SamplingRate, SamplingTreshold, SamplingForce, SamplingStart, SamplingEnd );
		if (Anim)
		{
			Engine->GetAnimationManager().AddElement( Anim );
			OR_AnimationPlayer* Player = new OR_AnimationPlayer( Anim );
			Player->SetBehaviour( OR_ANIMATION_Player_Loop );
			Player->Pause();
			Root->AddPlayer( *Player );
		}

		if( Engine ) Engine->GetLogManager().SubIndent();
		if( Engine ) Engine->GetLogManager().AddLine( "\nFinish updating animations" );
	}

	return Root;
}



OR_3DS_Node*	OR_3DSWrapper::RetrieveNode_Rec( INode* RootNode, OR_Node* Father, OR_3DS_Node* Root )
{
	OR_3DS_Node *Noeud, *Son;
	int i;
	if( !Engine ) return NULL;
	if( !RootNode ) return NULL;


	Noeud = &((OR_3DS_MAXNode*)RootNode)->GetNode( Time, Father, Root );
	if( !Root ) Root = Noeud;
	
	Engine->GetLogManager().AddLine("\n---------------------------------------------------");
	Engine->GetLogManager().AddIndent();
	
	if( Noeud->GetObject() )
	{
		switch( GetGlobalType( Noeud->GetObject()->GetType() ) )
		{
			case OR_MESH:
				Engine->GetMeshManager().AddElement((OR_Mesh*) Noeud->GetObject());				
				break;
			case OR_SKIN:
				Engine->GetSkinManager().AddElement((OR_Skin*) Noeud->GetObject());				
				break;
			case OR_LIGHT:					
				Engine->GetLightManager().AddLight((OR_Light*)Noeud->GetObject());
				break;
			case OR_CAMERA:
				Engine->GetCameraManager().AddElement((OR_Camera*) Noeud->GetObject());
				break;
			case OR_GIZMO:
				Engine->GetGizmoManager().AddElement((OR_Gizmo*) Noeud->GetObject());
				break;
		}
		ApplyShader( Noeud );
	
		for( i=0 ; i<RootNode->NumberOfChildren() ; i++)
		{
			Son = this->RetrieveNode_Rec( RootNode->GetChildNode(i) , Noeud, Root );
			if (Son) Noeud->AddSonLast(*Son);			
		}
	}
	
	if( Engine ) Engine->GetLogManager().SubIndent();

	return Noeud;
}



void	OR_3DSWrapper::UpdateMatrices_Rec( OR_3DS_Node* curnode )
{
	if (curnode)
	{
		curnode->GetObject()->SetAbsoluteMatrix( ((OR_3DS_MAXNode*)curnode->GetMAXNode())->GetOR_Matrix(Time) );
		curnode->GetObject()->SetRelativeMatrix( ((OR_3DS_MAXNode*)curnode->GetMAXNode())->GetRelativeOR_Matrix(Time) );

		T_NodeList &Sons = curnode->GetSonList();
		for( IT_NodeList it = Sons.begin() ; it!=Sons.end() ; ++it )
			UpdateMatrices_Rec( (OR_3DS_Node*)*it );
	}
}

OR_Shader*	OR_3DSWrapper::RetrieveMaterial( MtlBase* MaxMtl )
{
	OR_ShaderManager& ShaderManager = Engine->GetShaderManager();
	OR_String MAXPath( MAXInterface->GetCurFilePath() );
	MAXPath.truncate( MAXPath.length() - strlen( MAXInterface->GetCurFileName() ) );

	OR_Shader* Result = ((OR_3DS_MAXMaterial*)MaxMtl)->GetOR_Shader(Time);
	if( Result )
	{
		if( Result->GetType()==OR_SHADER_SingleTextureMap )
		{
			OR_SingleTextureMapShader* SingleTextureShader = (OR_SingleTextureMapShader*)Result;
			OR_String Path( SingleTextureShader->GetTexture()->GetImageAdress() );
			OR_I32 SlashPos = Path.lastIndexOf( '\\' ) + 1;
			if( SlashPos > 0 )
			{
				OR_String File( Path.substring( SlashPos ) );
				Path.truncate( SlashPos );
				Path.SetRelativeToPath( MAXPath );
				Path += File;
			}
			SingleTextureShader->GetTexture()->SetImageAdress( Path.getBytes() );
		}
		ShaderManager.AddElement( Result );
		MaxToOrionMtlMap[MaxMtl] = Result;
	}

	return Result;
}


void	OR_3DSWrapper::RetrieveSceneMaterials()
{
	if( !Engine ) return;
	
	OR_U32 i;
	OR_Shader* Shad;
	OR_ShaderManager& ShaderManager = Engine->GetShaderManager();
	OR_TextureManager& TextureManager = Engine->GetTextureManager();
	OR_MeshManager& MeshManager = Engine->GetMeshManager();
	OR_SkinManager& SkinManager = Engine->GetSkinManager();
	IT_ManagerMap_Template( OR_Mesh ) itMesh;
	IT_ManagerMap_Template( OR_Skin ) itSkin;
	vector<MultiMtl*> MultiMaterials;
	vector<MultiMtl*>::iterator itMaxMtl;

	//Dereference all shaders so that they can be destroyed
	for( itMesh = MeshManager.begin() ; itMesh != MeshManager.end() ; ++ itMesh )
		(*itMesh).second->SetShader( NULL );
	for( itSkin = SkinManager.begin() ; itSkin != SkinManager.end() ; ++ itSkin )
		(*itSkin).second->SetShader( NULL );

	// delete all shaders & all textures
	ShaderManager.DeleteAll();
	TextureManager.DeleteAll();
	MaxToOrionMtlMap.clear();

	// create a default shader
	float Default_Shader_Ambient[4] = { .58f , .58f , .58f , 1.f };
	float Default_Shader_Diffuse[4] = { .58f , .58f , .58f , 1.f };
	float Default_Shader_Specular[4] = { .31f , .31f , .31f , 1.f };
	float Default_Shader_Shine = 32;
	Shad = new OR_FlatShader();
	Shad->SetAmbient( Default_Shader_Ambient );
	Shad->SetDiffuse( Default_Shader_Diffuse );
	Shad->SetSpecular( Default_Shader_Specular );
	Shad->SetShine( Default_Shader_Shine );
	Shad->SetName( ORION3D_DEFAULT_SHADER );
	ShaderManager.AddElement( Shad );

	//Retrieve the scene materials
	MtlBaseLib* MtlLib = MAXInterface->GetSceneMtls();
	for( i=0 ; i<MtlLib->Count() ; i++ )
	{
		MtlBase* MaxMtl = (*MtlLib)[i];
		Shad = RetrieveMaterial( MaxMtl );		
		if( Shad && Shad->GetType() == OR_Shader_Multi ) MultiMaterials.push_back( (MultiMtl*)MaxMtl );
	}

	for( itMaxMtl = MultiMaterials.begin() ; itMaxMtl != MultiMaterials.end() ; ++itMaxMtl )
	{
		MultiMtl* Multi = (*itMaxMtl);
		IT_MaxToOrionMtlMap itOrionMtl = MaxToOrionMtlMap.find( Multi );
		OR_ASSERT( itOrionMtl != MaxToOrionMtlMap.end() );

		OR_MultiShader* ORMulti = (OR_MultiShader*)(*itOrionMtl).second;
		OR_U32 NbrSubMaterials = Multi->NumSubMtls();
		for( i=0 ; i<NbrSubMaterials ; ++i )
		{
			OR_Shader* ORSubMtl;
			MtlBase* MaxSubMtl = Multi->GetSubMtl( i );
			IT_MaxToOrionMtlMap itOrionSubMtl = MaxToOrionMtlMap.find( MaxSubMtl );
			if( itOrionSubMtl == MaxToOrionMtlMap.end() )
			{
				ORSubMtl = RetrieveMaterial( MaxSubMtl );
				if( ORSubMtl->GetType() == OR_Shader_Multi ) MultiMaterials.push_back( (MultiMtl*)MaxSubMtl );
			}
			else
			{
				 ORSubMtl = (*itOrionSubMtl).second;
			}
			ORMulti->AddShader( ORSubMtl, NULL, 0 );
		}

	}
}


/*------------------------------------------------------------------------------
 * Name : OR_3DS_Wrapper::void			
 *
 *  \param  BaseRep EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2002-01-05
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
void OR_3DSWrapper::CopyTextures( const OR_String BaseRep )
{
	CIT_ManagerMap_Template( OR_Texture ) it;
	const OR_TextureManager& TextureManager = Engine->GetTextureManager();

	OR_String MAXPath( MAXInterface->GetCurFilePath() );
	MAXPath.truncate( MAXPath.length() - strlen( MAXInterface->GetCurFileName() ) );
	
	for( it = TextureManager.begin() ; it != TextureManager.end() ; ++it )
	{
		const OR_Texture* Texture = (*it).second;
		
		OR_String Source( Texture->GetImageAdress() );
		if( Source[1] != ':' ) Source = MAXPath + Source;
		OR_String Cible( Texture->GetImageAdress() );
		if( Cible[1] != ':' ) 
		{
			if( BaseRep.charAt(BaseRep.length()-1)=='\\') Cible =  BaseRep + Cible;
			else Cible =  BaseRep + OR_String( "\\" ) + Cible;
		}
		Source.StripDots();
		Cible.StripDots();

		OR_Bool Path = Cible.GetPath().MkDir();

		CopyFile( Source.val(), Cible.val(), FALSE );
	}
			
			
}

void	OR_3DSWrapper::ApplyShaders_Rec( OR_3DS_Node* Root )
{
	ApplyShader( Root );
	
	T_NodeList &Sons = Root->GetSonList();
	for( IT_NodeList it = Sons.begin() ; it!=Sons.end() ; ++it )
		ApplyShaders_Rec( (OR_3DS_Node*)*it );	
}

void	OR_3DSWrapper::ApplyShader( OR_3DS_Node* Noeud )
{
	OR_ShaderManager& ShaderManager = Engine->GetShaderManager();
	OR_Object* TheObject = Noeud->GetObject();
	
	if( TheObject && ( TheObject->GetType()==OR_MESH || TheObject->GetType()==OR_SKIN ) )
	{
		OR_Mesh*	TheMesh = (OR_Mesh*)TheObject;
		Mtl*		MaxMtl = Noeud->GetMAXNode()->GetMtl();
		if( TheMesh->GetShader() == NULL )
		{
			//Find the shader for this mesh
			IT_MaxToOrionMtlMap it = MaxToOrionMtlMap.find( MaxMtl );
			if( it != MaxToOrionMtlMap.end() )
			{
				OR_Shader* TheShader = (*it).second;
				if( TheShader->GetType() == OR_Shader_Multi )
				{
					Mesh* MaxMesh = NULL;
					OR_MultiShader* NewMutlti = new OR_MultiShader( *(OR_MultiShader*)TheShader );
					ShaderManager.AddElement( NewMutlti );
					Object* MaxObjet = Noeud->GetMAXNode()->EvalWorldState(Time).obj;
					TriObject* Tri = (TriObject *) MaxObjet->ConvertToType( Time, Class_ID( TRIOBJ_CLASS_ID, 0 ) );
					if( Tri ) 
					{
						MaxMesh = &( Tri->GetMesh() );
						OR_3DS_Utils::InitMultiShaderFromMesh( NewMutlti, (MultiMtl*)MaxMtl, MaxMesh, MaxToOrionMtlMap );
					}
					NewMutlti->SetName( NewMutlti->GetName() + TheMesh->GetName() );

					TheShader = NewMutlti;
				}
				TheMesh->SetShader( TheShader );
			}
			//If we do not have found one, set the default shader
			else
			{
				Engine->GetShaderManager().SelectFirstElement();
				TheMesh->SetShader( Engine->GetShaderManager().GetElementSelected() );
			}
			if( Engine ) Engine->GetLogManager().AddString( "\nShader %s assigned to object %s", TheMesh->GetShader()->GetName(), TheMesh->GetName() );
		}
	}

}



void	OR_3DSWrapper::UpdateTargets( OR_3DS_Node* curnode, OR_3DS_Node* Root )
{
	if( curnode->GetMAXTarget()!=NULL )
	{
		OR_3DS_Node* Target = OR_3DS_Utils::FindNode( Root, curnode->GetMAXTarget() );
		if ( !Target && Engine ) 
			Engine->GetMessageHandler().Warning("OR_3DSWrapper::UpdateTargets",
									 "Coudln't find the target named %s for object %s",
									 curnode->GetMAXTarget()->GetName(),
									 curnode->GetObject()->GetName()
									);
		else
			curnode->GetObject()->SetTarget( Target->GetObject() );
	}
	
	T_NodeList &Sons = curnode->GetSonList();
	for( IT_NodeList it = Sons.begin() ; it!=Sons.end() ; ++it )
		UpdateTargets( (OR_3DS_Node*)*it, Root );
}

