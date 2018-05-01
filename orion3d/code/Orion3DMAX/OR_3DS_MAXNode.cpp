/*------------------------------------------------------------------------------
 *  \file  OR_3DS_MAXNode.cpp
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-11-05
 *------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_3DS_MAXNode.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "stdafx.h"
#include "OR_3DS_MAXNode.h"

#ifndef OR_USE_INLINE
#   include "OR_3DS_MAXNode.inl"
#endif

namespace OR_3DS {


/*------------------------------------------------------------------------------
 * Name : OR_3DS_MAXNode::GetVisibilityTrack
 *
 *  \param  &start EXPLANATION
 *  \param  &end EXPLANATION
 *  \param  Step EXPLANATION
 *  \param  Treshold_Angle EXPLANATION
 *  \param  Force EXPLANATION
 *  \param  ForceStart EXPLANATION
 *  \param  ForceEnd EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-06
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_AnimationTrack* OR_3DS_MAXNode::GetVisibilityTrack( float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float ForceStart, OR_Float ForceEnd )
{
	OR_AnimationTrack* TheTrack = NULL;
	OR_Globals::LogManager()->AddString("\nExporting visibility track from %s...",this->GetName() );
	OR_Globals::LogManager()->AddIndent();
	OR_Globals::LogManager()->AddLine("\nType : ");

//Retrieve the animation controller of the node and check if there is a track
	Control* VisiblityController = this->GetVisController();
	if ( !VisiblityController) return NULL;
	
	if( VisiblityController ) TheTrack = OR_3DS_Utils::GetFloatTrackFromController( VisiblityController );

	if( TheTrack )
	{
		start = TheTrack->GetKeyframeList().front()->GetTime();
		end = TheTrack->GetKeyframeList().back()->GetTime();

		TheTrack->SetTarget( OR_ANIMATION_Target_Display );
		OR_Globals::LogManager()->AddString("\nData : %d keys  from %.2fs to %.2fs", TheTrack->GetKeyframeList().size(), start, end);
	}
	
	OR_Globals::LogManager()->SubIndent();

	return TheTrack;

}


	
//Get the position track of a 3DS Node
OR_AnimationTrack* OR_3DS_MAXNode::GetPositionTrack( float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float Start, OR_Float End )
{
	OR_AnimationTrack* TheTrack = NULL;
	OR_Globals::LogManager()->AddString("\nExporting position track from %s...",this->GetName());
	OR_Globals::LogManager()->AddIndent();
	OR_Globals::LogManager()->AddLine("\nType : ");

//Retrieve the animation controller of the node and check if there is a track
	Control* Controller = this->GetTMController();
	if ( !Controller) return NULL;
	
	Control *PositionController = Controller->GetPositionController();
	if( PositionController ) TheTrack = OR_3DS_Utils::GetPositionTrackFromController( PositionController );
	if( !TheTrack ) TheTrack = this->SamplePositionTrack( Step, Treshold_Angle, Force, Start, End );

	if( TheTrack )
	{
		start = TheTrack->GetKeyframeList().front()->GetTime();
		end = TheTrack->GetKeyframeList().back()->GetTime();

		OR_Matrix4x4 BaseMatrix = this->GetRelativeOR_Matrix(0);
		//BaseMatrix.UnScale();
		OR_3DS_Utils::MakeVector3DTrackRelative( TheTrack, BaseMatrix );
		
		TheTrack->SetTarget(OR_ANIMATION_Target_Pos);
		OR_Globals::LogManager()->AddString("\nData : %d keys  from %.2fs to %.2fs", TheTrack->GetKeyframeList().size(), start, end);
	}
	
	OR_Globals::LogManager()->SubIndent();

	return TheTrack;
}




OR_AnimationTrack* OR_3DS_MAXNode::GetRotationTrack( float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float Start, OR_Float End )
{
	//For information about how it works, just look at GetPositionTrack()
	//it works the same way
	OR_AnimationTrack* TheTrack = NULL;
	OR_Globals::LogManager()->AddString("\nExporting rotation track from %s...",this->GetName());
	OR_Globals::LogManager()->AddIndent();
	OR_Globals::LogManager()->AddLine("\nType : ");

	Control* Controller = this->GetTMController();
if( !Controller ) return NULL;

	Control *RotationController = Controller->GetRotationController();
	if( RotationController ) TheTrack = OR_3DS_Utils::GetRotationTrackFromController( RotationController );
	if( !TheTrack ) TheTrack = this->SampleRotationTrack( Step, Force, Start, End );
		
	if( TheTrack )
	{
		if( TheTrack->GetKeyframeList().size()>0 )
		{
			start = TheTrack->GetKeyframeList().front()->GetTime();
			end = TheTrack->GetKeyframeList().back()->GetTime();
			
			Matrix3 BaseMatrix = this->GetRelativeMatrix3(0);BaseMatrix.NoScale();
			Quat BaseQuat( BaseMatrix );
			OR_Quaternion BaseQuaternion( BaseQuat.w, BaseQuat.x, BaseQuat.y, BaseQuat.z );
			OR_3DS_Utils::MakeQuaternionTrackRelative( TheTrack, BaseQuaternion );

			TheTrack->SetTarget(OR_ANIMATION_Target_Rot);	
			OR_Globals::LogManager()->AddString("\nData : %d keys  from %.2fs to %.2fs", TheTrack->GetKeyframeList().size() , start, end);
		}
		else
			OR_DELETE( TheTrack );
	}
	OR_Globals::LogManager()->SubIndent();
	
	return TheTrack;
}




OR_AnimationTrack* OR_3DS_MAXNode::GetScaleTrack( float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float Start, OR_Float End )
{
	//For information about how it works, just look at GetPositionTrack()
	//it works the same way
	OR_AnimationTrack* TheTrack = NULL;

	OR_Globals::LogManager()->AddString("\nExporting scale track from %s...",this->GetName());
	OR_Globals::LogManager()->AddIndent();
	OR_Globals::LogManager()->AddLine("\nType : ");
				
	Control* Controller = this->GetTMController();
if( !Controller ) return NULL;

	Control *ScaleController = Controller->GetScaleController();
	if( ScaleController ) TheTrack = OR_3DS_Utils::GetScaleTrackFromController( ScaleController );
	if( !TheTrack ) TheTrack = this->SampleScaleTrack( Step, Force, Start, End );
			
	if (TheTrack)
	{
		start = TheTrack->GetKeyframeList().front()->GetTime();
		end = TheTrack->GetKeyframeList().back()->GetTime();
		
		Matrix3 BaseMatrix = this->GetRelativeMatrix3(0);
		Point3 BaseTrans; Quat BaseRot; Point3 BaseScale;
		DecomposeMatrix( BaseMatrix, BaseTrans, BaseRot, BaseScale );
		OR_Vector3D ORBaseScale( BaseScale.x-1, BaseScale.y-1, BaseScale.z-1 );
		OR_3DS_Utils::MakeVector3DTrackRelative( TheTrack, ORBaseScale );

		TheTrack->SetTarget(OR_ANIMATION_Target_Scale);
		
		OR_3DS_Utils::SetTrackBehavior( TheTrack, ScaleController );

		OR_Globals::LogManager()->AddString("\nData : %d keys  from %.2fs to %.2fs", TheTrack->GetKeyframeList().size(), start, end);
	}

	return TheTrack;
}




OR_AnimationNode*	OR_3DS_MAXNode::GetOR_AnimationNode( float &start, float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float Start, OR_Float End, OR_AnimationNode* Father )
{
	float	tmpstart , tmpend;
	int		cmpt;
	OR_AnimationTrack* TempTrack = NULL;
	OR_AnimationNode* TheNode = new OR_AnimationNode;
	
	start = FLT_MAX;end = -FLT_MAX;

	OR_Globals::LogManager()->AddString("\nExporting animation node from %s...",this->GetName());
	OR_Globals::LogManager()->AddIndent();

	for (cmpt=0 ; cmpt<4 ; cmpt++)
	{
		switch(cmpt)
		{
			case 0:
				TempTrack = this->GetPositionTrack( tmpstart, tmpend, Step, Treshold_Angle, Force, Start, End );
			break;
			case 1:
				TempTrack = this->GetRotationTrack( tmpstart , tmpend, Step, Treshold_Angle, Force, Start, End );
			break;
			case 2:
				TempTrack = this->GetScaleTrack( tmpstart , tmpend, Step, Treshold_Angle, Force, Start, End );
			break;
			case 3:
				TempTrack = this->GetVisibilityTrack( tmpstart , tmpend, Step, Treshold_Angle, Force, Start, End );
			break;
		}
		if (TempTrack)
		{			
			start = min(start , tmpstart); end = max(end , tmpend);
			TheNode->AddTrackFirst( *TempTrack );
		}
	}

	TheNode->SetFather(Father);

	OR_Globals::LogManager()->SubIndent();
	
	return TheNode;	
}


OR_AnimationNode*	OR_3DS_MAXNode::GetAnimationTree( OR_U32 &nbnodes, OR_Float &start, OR_Float &end, OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float Start, OR_Float End, OR_AnimationNode* Father )
{
	OR_AnimationNode* Noeud = NULL;
	OR_AnimationNode* TempNode;
	float tmpstart = start,tmpend = end;
	int i;

	Noeud	= this->GetOR_AnimationNode( tmpstart, tmpend, Step, Treshold_Angle, Force, Start, End, Father);

	OR_Globals::LogManager()->AddIndent();

	if (!Noeud) return NULL;

	start	= min(start, tmpstart);
	end		= max(end, tmpend);
	for(i=0 ; i<this->NumberOfChildren() ; i++)
	{
		TempNode = ((OR_3DS_MAXNode*)this->GetChildNode(i))->GetAnimationTree( nbnodes, start, end, Step, Treshold_Angle, Force, Start, End, Noeud );
		if (TempNode) Noeud->AddSonLast(*TempNode);
	}

	++nbnodes;

	OR_Globals::LogManager()->SubIndent();
	
	return Noeud;
}

OR_Animation*	OR_3DS_MAXNode::GetOR_Animation( OR_Float Step, OR_Float Treshold_Angle, OR_Bool Force, OR_Float Start, OR_Float End )
{
	OR_Globals::LogManager()->AddString( "\nExporting animation from %s...", this->GetName() );
	OR_Globals::LogManager()->AddIndent();

	float start=FLT_MAX,end=-FLT_MAX;
	OR_U32 nbnodes = 0;
	OR_Animation* Animation = NULL;
	OR_AnimationNode* RootNode = this->GetAnimationTree( nbnodes, start, end, Step, Treshold_Angle, Force, Start, End );
	if (RootNode)
	{
		if (start<end)
		{
			RootNode->RescaleTime(start,end);
			Animation = new OR_Animation();
			Animation->SetFatherNode(RootNode);
			Animation->SetDuration(end-start);
			Animation->SetName(this->GetName());
			Animation->SetNbObject(nbnodes);
		}
		else delete RootNode;
	}

	OR_Globals::LogManager()->SubIndent();

	return Animation;	
}




/*------------------------------------------------------------------------------
 * Name : OR_3DS_AnimUtils::OR_AnimationTrack
 *
 *  \param  &start EXPLANATION
 *  \param  &end EXPLANATION
 *  \param  *Controller EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-15
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_AnimationTrack* OR_3DS_MAXNode::SamplePositionTrack( OR_I32 Step, OR_Float Treshold_Angle, OR_Bool Force, OR_I32 Start, OR_I32 End )
{
	if( Start > End || Step<=0 ) return NULL;

	OR_Vector3D CurPos;
	OR_Float	Treshold = fabs( cos( Treshold_Angle ) );

	Control*	Controller = this->GetTMController();
	if ( Controller )
	{
		Interval TimeRange = Controller->GetTimeRange( TIMERANGE_CHILDNODES | TIMERANGE_CHILDANIMS | TIMERANGE_ALL );
		if( !TimeRange.Empty() && TimeRange.Duration() != 0 ) 
		{
			Start = TimeRange.Start();
			End =  TimeRange.End();
		}
		else if( !Force ) return NULL;
	}
	else if( !Force ) return NULL;

	OR_AnimationTrack* TheTrack = new OR_AnimationTrack_Linear_Vector;
	OR_KeyFrame_Linear<OR_Vector3D>* Key;
	OR_KeyFrame_Linear<OR_Vector3D>* LastKey;
	
	for( OR_I32 CurTime = Start ; CurTime<End+Step ; CurTime += Step )
	{
		CurPos = this->GetRelativeOR_Matrix( CurTime ).GetTranslation();

		if( TheTrack->GetKeyframeList().size() ) LastKey = (OR_KeyFrame_Linear<OR_Vector3D>*)TheTrack->GetKeyframeList().back();
		else
		{
			LastKey = new OR_KeyFrame_Linear<OR_Vector3D>( CurTime/4800., CurPos );
			TheTrack->AddKeyFrame(*LastKey);
		}

		for( OR_I32 i = LastKey->GetTime()*4800 + Step ; i < CurTime ; i += Step )
		{							
			OR_Vector3D Pos = this->GetRelativeOR_Matrix( i ).GetTranslation();
			OR_Vector3D Dir1 = (Pos-LastKey->Data);	Dir1.Normalize();
			OR_Vector3D Dir2 = (CurPos-Pos);		Dir2.Normalize();
			if( fabs( Dir1 * Dir2 ) <= Treshold )
			{
				Key = new OR_KeyFrame_Linear<OR_Vector3D>( i/4800., Pos );
				TheTrack->AddKeyFrame(*Key);
				break;
			}
		}
	}
	CurPos = this->GetRelativeOR_Matrix( End ).GetTranslation();
	Key = new OR_KeyFrame_Linear<OR_Vector3D>( End/4800., CurPos );
	TheTrack->AddKeyFrame(*Key);

	OR_3DS_Utils::SetTrackBehavior( TheTrack, Controller );

	return TheTrack;
}





/*------------------------------------------------------------------------------
 * Name : OR_3DS_AnimUtils::SampleRotationTrack
 *
 *  \param  start EXPLANATION
 *  \param  end EXPLANATION
 *  \param  Controller EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-15
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_AnimationTrack* OR_3DS_MAXNode::SampleRotationTrack( OR_I32 Step, OR_Bool Force, OR_I32 Start, OR_I32 End )
{
	if( Start > End || Step<=0 ) return NULL;

	Control* Controller = this->GetTMController();
	if ( Controller )
	{
		Interval TimeRange = Controller->GetTimeRange( TIMERANGE_CHILDNODES | TIMERANGE_CHILDANIMS | TIMERANGE_ALL );
		if( !TimeRange.Empty() && TimeRange.Duration() != 0 ) 
		{
			Start = TimeRange.Start();
			End =  TimeRange.End();
		}
		else if( !Force ) return NULL;
	}
	else if( !Force ) return NULL;
	
		
	OR_AnimationTrack* TheTrack = new OR_AnimationTrack_Linear_Quaternion;
	for( OR_I32 CurTime = Start ; CurTime<End ; CurTime += Step )
	{
		Matrix3 Matrix = this->GetRelativeMatrix3( CurTime );
		AffineParts Parts;
		//decomp_affine( Matrix, &Parts );		
		DecomposeMatrix( Matrix, Parts.t, Parts.q, Parts.k );
		OR_Quaternion Rotation(Parts.q.w ,Parts.q.x, Parts.q.y, Parts.q.z);
		/*
		if( TheTrack->GetKeyframeList().size() )
		{			
			OR_KeyFrame_Linear<OR_Quaternion>* LastKey = (OR_KeyFrame_Linear<OR_Quaternion>*)TheTrack->GetKeyframeList().back();
			if( ( Rotation * ~LastKey->Data ).GetW() > .1 ) 
			{
				OR_KeyFrame_Linear<OR_Quaternion>* Key = new OR_KeyFrame_Linear<OR_Quaternion>( CurTime , Rotation );
				TheTrack->AddKeyFrame( *Key );
			}
		}
		else*/
		{
			OR_KeyFrame_Linear<OR_Quaternion>* Key = new OR_KeyFrame_Linear<OR_Quaternion>( CurTime/4800. , Rotation );
			TheTrack->AddKeyFrame( *Key );
		}
	}

	OR_3DS_Utils::SetTrackBehavior( TheTrack, Controller );

	return TheTrack;
}




/*------------------------------------------------------------------------------
 * Name : OR_3DS_MAXNode::SampleScaleTrack
 *
 *  \param  Step EXPLANATION
 *  \param  Force EXPLANATION
 *  \param  ForceStart EXPLANATION
 *  \param  ForceEnd EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-06
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_AnimationTrack* OR_3DS_MAXNode::SampleScaleTrack( OR_I32 Step, OR_Bool Force, OR_I32 ForceStart, OR_I32 ForceEnd )
{
	if( ForceStart > ForceEnd || Step<=0 ) return NULL;

	OR_Vector3D CurScale;
	//OR_Float	Treshold = fabs( cos( Treshold_Angle ) );

	Control*	Controller = this->GetTMController();
	if ( Controller )
	{
		Interval TimeRange = Controller->GetTimeRange( TIMERANGE_CHILDNODES | TIMERANGE_CHILDANIMS | TIMERANGE_ALL );
		if( !TimeRange.Empty() && TimeRange.Duration() != 0 ) 
		{
			ForceStart = TimeRange.Start();
			ForceEnd =  TimeRange.End();
		}
		else if( !Force ) return NULL;
	}
	else if( !Force ) return NULL;

	OR_AnimationTrack* TheTrack = new OR_AnimationTrack_Linear_Vector;
	OR_KeyFrame_Linear<OR_Vector3D>* Key;
	
	for( OR_I32 CurTime = ForceStart ; CurTime<ForceEnd+Step ; CurTime += Step )
	{
		Matrix3 Matrix = this->GetRelativeMatrix3( CurTime );
		AffineParts Parts;
		//decomp_affine( Matrix, &Parts );		
		DecomposeMatrix( Matrix, Parts.t, Parts.q, Parts.k );
		CurScale.SetCoord( Parts.k.x, Parts.k.y, Parts.k.z );

		Key = new OR_KeyFrame_Linear<OR_Vector3D>( CurTime/4800., CurScale );
		TheTrack->AddKeyFrame(*Key);
	}

	OR_3DS_Utils::SetTrackBehavior( TheTrack, Controller );

	return TheTrack;
}



OR_Mesh*	OR_3DS_MAXNode::GetOR_Mesh( TimeValue Time, T_U32Vector &LookUpTable )
{
	OR_Globals::LogManager()->AddString("\nExporting mesh from %s...",this->GetName());

	Object* LObjet = this->EvalWorldState(Time).obj;
	if (!LObjet) return NULL;

	Matrix3 OffsetMatrix = GetOffsetMatrix3( Time );
	Matrix3 NormalOffsetMatrix = OffsetMatrix;
	NormalOffsetMatrix.NoTrans();

	if( LObjet->CanConvertToType( Class_ID( TRIOBJ_CLASS_ID, 0 ) ) )
	{
		OR_U32 f,v;
		TriObject* Tri = (TriObject *) LObjet->ConvertToType( Time, Class_ID( TRIOBJ_CLASS_ID, 0 ) );
		if( !Tri ) return NULL;
		Mesh LeMesh = Tri->GetMesh();
		Mesh LAutreMesh = LeMesh;//Comme on récupère une référence, on la duplique dans une autre variable
		Mesh* mesh= &LAutreMesh;
		
		LookUpTable.clear();
	
		//construit les normales	
		mesh->checkNormals(TRUE);
		mesh->buildRenderNormals();

		OR_U32 NbrVerts = mesh->getNumVerts();
		OR_U32 NbrFaces = mesh->getNumFaces();
		
		DWORD*	SmGroups=  new DWORD[ NbrFaces ];
		MtlID*  MtlIds = new MtlID[ NbrVerts ];
		OR_SingleFace*	IndicesArray = new OR_SingleFace[ NbrFaces ];
		T_FloatVector	VertsArray;VertsArray.reserve( NbrVerts*3 );
		T_FloatVector	NormArray;NormArray.reserve( NbrVerts*3 );
		T_FloatVector	TVertsArray;TVertsArray.reserve( NbrVerts*2 );

		OR_Globals::LogManager()->AddIndent();
		OR_Globals::LogManager()->AddString( "\nOriginal 3DSMAX mesh : %d faces, %d vertices", NbrFaces, NbrVerts );


		for( f=0 ; f<NbrFaces ; ++f )
		{
			IndicesArray[f]=OR_SingleFace( mesh->faces[f].v, mesh->faces[f].getMatID() );
			SmGroups[f]=mesh->faces[f].getSmGroup();
		}

		for( v=0 ; v<NbrVerts ; ++v )
		{
			Point3 Pos = OffsetMatrix*mesh->verts[v];
			Point3 Norm ;
			if( (mesh->getRVertPtr(v)->rFlags & NORCT_MASK) > 1 )
				Norm = NormalOffsetMatrix*mesh->getRVertPtr(v)->ern[0].getNormal();
			else
				Norm = NormalOffsetMatrix*mesh->getNormal(v);
			VertsArray.push_back( Pos.x );VertsArray.push_back( Pos.y );VertsArray.push_back( Pos.z );
			NormArray.push_back( Norm.x );NormArray.push_back( Norm.y );NormArray.push_back( Norm.z );
			TVertsArray.push_back( -FLT_MAX );TVertsArray.push_back( -FLT_MAX );
			MtlIds[v] = -1;
		}


		//éclatement des vertex à plusieurs normales :
		//Pour chaque vertex...
		for( v=0 ; v<NbrVerts ; v++ )
		{
			RVertex* V = mesh->getRVertPtr(v);
			//...Si le vertex concerné a plusieurs normales...
			if( (V->rFlags & NORCT_MASK)>1 )
			{
				//...pour chaque normale :
				for( DWORD n=1 ; n<(V->rFlags & NORCT_MASK) ; n++ )
				{
					//Récupère le smoothing group associé à la normale
					DWORD SmGroup = V->ern[n].getSmGroup();
					//Récupère la normale
					Point3 Normale = NormalOffsetMatrix*V->ern[n].getNormal();
					//Change les faces de même smoothing group faisant référence à ce vertex
					OR_U32 NewIndice = VertsArray.size()/3;
					for( OR_U32 f=0 ; f<NbrFaces ; f++ )
					{
						if( (SmGroups[f] & SmGroup) && mesh->faces[f].v[0] == v ) IndicesArray[f][0] = NewIndice;
						if( (SmGroups[f] & SmGroup) && mesh->faces[f].v[1] == v ) IndicesArray[f][1] = NewIndice;
						if( (SmGroups[f] & SmGroup) && mesh->faces[f].v[2] == v ) IndicesArray[f][2] = NewIndice;
					}
					//Rajoute un nouveau vertex ayant la normale correspondant au smoothing group
					VertsArray.push_back( VertsArray[v*3] );	VertsArray.push_back( VertsArray[v*3+1] );	VertsArray.push_back( VertsArray[v*3+2] );
					NormArray.push_back( Normale.x );			NormArray.push_back( Normale.y );			NormArray.push_back( Normale.z );
					TVertsArray.push_back( TVertsArray[v*2] );	TVertsArray.push_back( TVertsArray[v*2+1] );
					LookUpTable.push_back( v );
				}
			}
		}
		delete[] SmGroups;

		//éclatement des vertex à plusieurs texcoords :
		//Pour chaque face...
		for( f=0 ; f<NbrFaces ; ++f )
		{
			//...Pour les 3 vertex de la face...
			for( v=0 ; v<3 ; ++v )
			{
				OR_U32 Indice = IndicesArray[f][v];
				//...Si le vertex est mappé...
				//!!!Dans la version 4 le flag HAS_TVERTS n'a pas l'air d'être bien mis
				//if( (mesh->faces[f].flags & HAS_TVERTS) && mesh->tVerts && mesh->tvFace )
				if( mesh->tvFace && mesh->tVerts )
				{
					Point3 UVMap = mesh->tVerts[ mesh->tvFace[f].getTVert(v) ];
					//Si aucun mapping n'a été appliqué au vertex, l'applique
					if( TVertsArray[ Indice*2 ] == -FLT_MAX && TVertsArray[ Indice*2+1 ] == -FLT_MAX ) 
					{
						TVertsArray[ Indice*2 ] = UVMap.x;
						TVertsArray[ Indice*2+1 ] = UVMap.y;
					}
					//Sinon (un mapping a déjà été appliqué au vertex)...
					//...Si le mapping est différent de celui de la face, le vertex
					//est utilisé par une face avec un mapping différent
					else if( fabs( TVertsArray[ Indice*2 ] - UVMap.x ) > OR_EPSILON || fabs( TVertsArray[ Indice*2+1 ] - UVMap.y ) > OR_EPSILON )
					{
						//=>Duplique le vertex et applique le mapping de notre face
						IndicesArray[f][v] = VertsArray.size()/3;
						VertsArray.push_back( VertsArray[ Indice*3 ] );	VertsArray.push_back( VertsArray[ Indice*3+1 ] );	VertsArray.push_back( VertsArray[ Indice*3+2 ] );
						NormArray.push_back( NormArray[ Indice*3 ] );	NormArray.push_back( NormArray[ Indice*3+1 ] );		NormArray.push_back( NormArray[ Indice*3+2 ] );
						TVertsArray.push_back( UVMap.x );				TVertsArray.push_back( UVMap.y );
						LookUpTable.push_back( Indice );
					}
				}
				else
				{
					TVertsArray[ Indice*2 ] = 0;
					TVertsArray[ Indice*2+1 ] = 0;
				}
			}
		}


		//Et wizz on inverse les faces si la matrice a la mauvaise idée de les foutre à l'envers
		if ( this->GetObjectTM( Time ).Parity() )
			for (f=0 ; f<NbrFaces ; f++)
			{
				OR_U32 Temp = IndicesArray[f][2];
				IndicesArray[f][2] = IndicesArray[f][0];
				IndicesArray[f][0] = Temp;
			}

		//merge all Indices in a single array
		OR_U32* Indices = new OR_U32[ 3*NbrFaces ];

		for( f=0 ; f<NbrFaces ; f++ )
		{
			Indices[ f*3+2 ] = IndicesArray[f][2];
			Indices[ f*3+1 ] = IndicesArray[f][1];
			Indices[ f*3+0 ] = IndicesArray[f][0];
		}

		NbrVerts = VertsArray.size()/3;
		OR_Mesh* TheMesh = new OR_Mesh( &VertsArray.front(), &NormArray.front(), &TVertsArray.front() , Indices , NbrVerts, NbrFaces );
		TheMesh->SetShader( NULL );

		OR_DELETEARRAY( IndicesArray );
		OR_DELETEARRAY( Indices );
		OR_DELETEARRAY( MtlIds );
		VertsArray.clear();
		NormArray.clear();
		TVertsArray.clear();

		OR_Globals::LogManager()->AddString( "\nFinal Orion3D mesh : %d faces, %d vertices", NbrFaces, NbrVerts );
		OR_Globals::LogManager()->SubIndent();

		return TheMesh;
	}
	OR_Globals::LogManager()->AddString( "\nFailed : couldn't convert %s to TriObject", this->GetName() );
	return NULL;
}

OR_Light*	OR_3DS_MAXNode::GetOR_Light( TimeValue Time )
{
	OR_Globals::LogManager()->AddString( "\nExporting light from %s...", this->GetName() );
	
	Object* LObjet = this->EvalWorldState(Time).obj;
	if (!LObjet) return NULL;

	GenLight* Spot = (GenLight *) LObjet;
	if (!Spot) return NULL;
	LightState	State;
	if (Spot->EvalLightState(Time,Interval(0,0),&State)!=REF_SUCCEED) return NULL;

	OR_Globals::LogManager()->AddIndent();
	OR_Globals::LogManager()->AddLine("\nType : ");
	
	OR_Light* TheLight = NULL;
	switch(Spot->Type())
	{
		case OMNI_LIGHT:
		case FSPOT_LIGHT:	TheLight = new OR_Light_FreeSpot();
							OR_Globals::LogManager()->AddLine("Free spot/omni");break;
		case TSPOT_LIGHT:	TheLight = new OR_Light_TargetSpot();
							OR_Globals::LogManager()->AddLine("Target spot");break;
		case DIR_LIGHT:		TheLight = new OR_Light_FreeDirect();
							OR_Globals::LogManager()->AddLine("Free directionnal");break;
		case TDIR_LIGHT:	TheLight = new OR_Light_TargetDirect();
							OR_Globals::LogManager()->AddLine("Target directionnal");break;
		default: return NULL;
	}

	OR_Globals::LogManager()->AddLine("\nParameters : ");
	OR_Globals::LogManager()->AddIndent();
	
	float Multiplieur = State.intens;
	if (!Multiplieur) Multiplieur=.001f;

	if (Spot->IsSpot()==TRUE && State.overshoot==FALSE)
	{
		((OR_Light_Spot*)TheLight)->SetCutOff(State.fallsize/2.f);
		((OR_Light_Spot*)TheLight)->SetExponent((1-(State.hotsize/State.fallsize))*128.f);
		OR_Globals::LogManager()->AddString("\nCutOff : %.3f",State.fallsize/2.f);
		OR_Globals::LogManager()->AddString("\nExponent : %.3f",(1-(State.hotsize/State.fallsize))*128.f);
	}
	else
	{
		((OR_Light_Spot*)TheLight)->SetCutOff(180);
		((OR_Light_Spot*)TheLight)->SetExponent(0);
		OR_Globals::LogManager()->AddLine("\nCutOff : 180");
		OR_Globals::LogManager()->AddLine("\nExponent : 0");
	}

	if (State.on==TRUE) TheLight->Enable();
	else TheLight->Disable();

	OR_Globals::LogManager()->AddString("\nColor : R:%.3f G:%.3f B:%.3f", State.color.r, State.color.g, State.color.b);
	
	if (State.ambientOnly==TRUE)
	{
		TheLight->SetAmbient(R , State.color.r);
		TheLight->SetAmbient(V , State.color.g);
		TheLight->SetAmbient(B , State.color.b);
		TheLight->SetAmbient(A , 1.f);
	}
	else
	{
		TheLight->SetAmbient(R,0.f);
		TheLight->SetAmbient(V,0.f);
		TheLight->SetAmbient(B,0.f);
		TheLight->SetAmbient(A,0.f);
	}

	if (State.affectDiffuse==TRUE && State.ambientOnly==FALSE)
	{
		TheLight->SetDiffuse(R , State.color.r);
		TheLight->SetDiffuse(V , State.color.g);
		TheLight->SetDiffuse(B , State.color.b);
		TheLight->SetDiffuse(A , 1.f);
	}
	else
	{
		TheLight->SetDiffuse(R , 0.f);
		TheLight->SetDiffuse(V , 0.f);
		TheLight->SetDiffuse(B , 0.f);
		TheLight->SetDiffuse(A , 1.f);
	}

	if (State.affectSpecular==TRUE && State.ambientOnly==FALSE)
	{
		TheLight->SetSpecular(R , State.color.r);
		TheLight->SetSpecular(V , State.color.g);
		TheLight->SetSpecular(B , State.color.b);
		TheLight->SetSpecular(A , 1.f);
	}
	else
	{
		TheLight->SetSpecular(R , 0.f);
		TheLight->SetSpecular(V , 0.f);
		TheLight->SetSpecular(B , 0.f);
		TheLight->SetSpecular(A , 1.f);
	}

	if (State.useAtten)
	{
		float atten[3] = {1.f/Multiplieur , 3/State.attenEnd/Multiplieur , 0.f};
		OR_Globals::LogManager()->AddString("\nAttenuation : 1/(ax² + bx + c) with a=%.3f b=%.3f c=%.3f", atten[2], atten[1], atten[0]);
		((OR_Light_Spot*)TheLight)->SetAtenuation(atten);
	}
	else
	{
		float atten[3] = {1.f/Multiplieur , 0.f , 0.f};
		OR_Globals::LogManager()->AddString("\nAttenuation : 1/(ax² + bx + c) with a=%.3f b=%.3f c=%.3f", atten[2], atten[1], atten[0]);
		((OR_Light_Spot*)TheLight)->SetAtenuation(atten);
	}

	OR_Globals::LogManager()->SubIndent();
	OR_Globals::LogManager()->SubIndent();

	return TheLight;
}

OR_Gizmo*	OR_3DS_MAXNode::GetOR_Gizmo(TimeValue Time)
{
	OR_Globals::LogManager()->AddString("\nExporting gizmo from %s...",this->GetName());
	
	Object* LObjet = this->EvalWorldState(Time).obj;
	if (!LObjet) return NULL;

	OR_Gizmo* TheGizmo = NULL;

	OR_Globals::LogManager()->AddIndent();
	OR_Globals::LogManager()->AddLine("\nType : ");
	if (LObjet->ClassID()==Class_ID(POINTHELP_CLASS_ID,0))
	{
		TheGizmo = new OR_PointGizmo;
		TheGizmo->SetDim(OR_Vector3D(0,0,0));
		OR_Globals::LogManager()->AddLine("Point");
	}
	else if (LObjet->ClassID()==BOXGIZMO_CLASSID)
	{
		TheGizmo = new OR_CubeGizmo;
		float l,w,h;
		((BoxGizmoObject*)LObjet)->pblock->GetValue(PB_BOXGIZMO_LENGTH , Time , l , FOREVER );
		((BoxGizmoObject*)LObjet)->pblock->GetValue(PB_BOXGIZMO_WIDTH , Time , w , FOREVER );
		((BoxGizmoObject*)LObjet)->pblock->GetValue(PB_BOXGIZMO_HEIGHT , Time , h , FOREVER );
		TheGizmo->SetDim(OR_Vector3D( w/2. , l/2. , h/2. ));
		OR_Globals::LogManager()->AddLine("Box");
	}
	else if (LObjet->ClassID()==SPHEREGIZMO_CLASSID)
	{
		TheGizmo = new OR_SphereGizmo;
		float r;
		((SphereGizmoObject*)LObjet)->pblock->GetValue(PB_GIZMO_RADIUS , Time , r , FOREVER );
		TheGizmo->SetDim(OR_Vector3D( r , r , r ));
		OR_Globals::LogManager()->AddLine("Sphere");
	}
	else if (LObjet->ClassID()==CYLGIZMO_CLASSID)
	{
		TheGizmo = new OR_CylinderGizmo;
		float r,h;
		((CylGizmoObject*)LObjet)->pblock->GetValue(PB_CYLGIZMO_RADIUS , Time , r , FOREVER );
		((CylGizmoObject*)LObjet)->pblock->GetValue(PB_CYLGIZMO_HEIGHT , Time , h , FOREVER );
		TheGizmo->SetDim(OR_Vector3D( r , r , h/2));
		OR_Globals::LogManager()->AddLine("Cylinder");
	}
	else
	{
		TheGizmo = new OR_PointGizmo;
		TheGizmo->SetDim(OR_Vector3D(0,0,0));
		OR_Globals::LogManager()->AddLine("Unkown, considered as point");
	}
	OR_Globals::LogManager()->SubIndent();
	
	return TheGizmo;
}

OR_Camera*		OR_3DS_MAXNode::GetOR_Camera(TimeValue Time)
{
	OR_Globals::LogManager()->AddString("\nExporting camera from %s...",this->GetName());
	
	Object* LObjet = this->EvalWorldState(Time).obj;
	if (!LObjet) return NULL;

	if (LObjet->SuperClassID()!=CAMERA_CLASS_ID) return NULL;
	CameraObject* Cam = (CameraObject *) LObjet;
	if (!Cam) return NULL;
	CameraState CamState;
	Cam->EvalCameraState(Time,FOREVER/*Interval(0,0)*/,&CamState);

	OR_Globals::LogManager()->AddIndent();

	OR_Globals::LogManager()->AddLine("\nType : ");
	OR_Camera* TheCam = NULL;
	if (this->GetTarget())
	{
		TheCam = new OR_Camera_Target;
		OR_Globals::LogManager()->AddLine("target cam");
	}
	else
	{
		TheCam = new OR_Camera_Free;
		OR_Globals::LogManager()->AddLine("free cam");
	}
		

	if (!CamState.manualClip) TheCam->SetFar(10000.);
	else TheCam->SetFar(CamState.yon);
	if (CamState.hither>1e-3 || CamState.isOrtho) TheCam->SetNear(CamState.hither);
	else TheCam->SetNear(.5f);

	OR_Globals::LogManager()->AddLine("\nProjection : ");

	if (CamState.isOrtho)
	{
		OR_Globals::LogManager()->AddLine("ortho");
		TheCam->SetFovy(CamState.fov*CamState.tdist); //fov = largeur
		if (!CamState.manualClip) TheCam->SetNear(-TheCam->GetFar());
		TheCam->SetOrtho(true);
	}
	else
	{
		OR_Globals::LogManager()->AddLine("perspective");
		TheCam->SetFovy(CamState.fov * 180. / OR_PI / 1.3f);
		TheCam->SetOrtho(false);
	}

	TheCam->SetAspect(1.3f);

	return TheCam;
}

OR_Bone*		OR_3DS_MAXNode::GetOR_Bone(TimeValue Time)
{
	OR_Globals::LogManager()->AddString("\nExporting bone from %s...",this->GetName());

	float length = 1;
	if (this->NumberOfChildren()) 
	{
		OR_Matrix4x4 M = ((OR_3DS_MAXNode*)this->GetChildNode(0))->GetRelativeOR_Matrix(Time);
		M.UnScale();
		length = ~(M.GetTranslation());
	}
	
	OR_Bone* TheBone = new OR_Bone(length);
	return TheBone;
}



OR_Skin*	OR_3DS_MAXNode::GetOR_Skin( TimeValue Time, T_U32Vector &LookupTable )
{
	OR_Skin* Result = NULL;

	//Try with Skin modifier
	Modifier* SkinMod = this->FindSkinModifier();
	if( SkinMod )  
	{
		Result = GetOR_SkinFromISkin( Time, LookupTable, SkinMod );
	}
	if( Result ) return Result;

#ifdef I_PHYEXPORT
	//Try with Physique
	Modifier* PhysiqueMod = this->FindPhysiqueModifier();
	if( PhysiqueMod )
	{
		Result = GetOR_SkinFromPhysique( Time, LookupTable, PhysiqueMod );
	}
#endif
	
	return Result;

}

/** \todo Finish Physique export */
OR_Skin*	OR_3DS_MAXNode::GetOR_SkinFromPhysique( TimeValue Time, T_U32Vector &LookupTable, Modifier *PhysiqueMod )
{
//#ifdef I_PHYEXPORT

	IPhysiqueExport *phyExport = (IPhysiqueExport *)PhysiqueMod->GetInterface(I_PHYINTERFACE);	
	if( !phyExport ) return NULL;
//	if( phyExport->Version() != CURRENT_VERSION*10 ) return NULL;
	
//#if( CURRENT_VERSION == 3 )
	
	IPhyContextExport *contextExport = (IPhyContextExport *)phyExport->GetContextInterface( this );
	if( !contextExport ) return NULL;

	contextExport->AllowBlending( TRUE );
	contextExport->ConvertToRigid();
	
	OR_U32 NbrVerts = contextExport->GetNumberVertices();
	OR_U32 i,j;
	T_INodeMap BonesMap;
	IT_INodeMap it;

	for( i=0 ; i<NbrVerts ; ++i )
	{
		int Type = contextExport->GetVertexInterface(i)->GetVertexType();
		if( Type == RIGID_BLENDED_TYPE )
		{	
			IPhyBlendedRigidVertex *vtxExport = (IPhyBlendedRigidVertex *)contextExport->GetVertexInterface(i);
			for( j=0 ; j < (OR_U32)vtxExport->GetNumberNodes() ; ++j )
			{
				INode* Bone = vtxExport->GetNode(j);
				if( BonesMap.find(Bone) == BonesMap.end() )
					BonesMap[Bone] = 0;
			}
		}
		else if( Type == RIGID_NON_BLENDED_TYPE )
		{
			IPhyRigidVertex *vtxExport = (IPhyRigidVertex *)contextExport->GetVertexInterface(i);
			INode* Bone = vtxExport->GetNode();
			if( BonesMap.find(Bone) == BonesMap.end() )
				BonesMap[Bone] = 0;
		}
		else
		{
			return NULL;
		}
	}

	PhysiqueMod->DisableMod();
	phyExport->SetInitialPose( true );
	OR_Mesh* OrionMesh = GetOR_Mesh( Time, LookupTable );
	OR_Skin* OrionSkin = new OR_Skin( *OrionMesh );
	delete OrionMesh;

	OrionSkin->SetNbrBones( BonesMap.size() );
	Matrix3 MeshRefMatrix;
	phyExport->GetInitNodeTM( this, MeshRefMatrix );
	OrionSkin->SetMeshRefMatrix( OR_3DS_Utils::ToOR_Matrix(MeshRefMatrix) );
	
	for( i=0, it = BonesMap.begin() ; it != BonesMap.end() ; ++it, ++i )
	{
		(*it).second = i;
		OrionSkin->SetBone( i, (OR_Object*)((*it).first) );

		Matrix3 BoneRefMatrix;
		phyExport->GetInitNodeTM( (*it).first, BoneRefMatrix );
		OrionSkin->SetRefMatrix( i, OR_3DS_Utils::ToOR_Matrix(BoneRefMatrix) );
	}

	for( i=0 ; i<NbrVerts ; ++i )
	{
		int Type = contextExport->GetVertexInterface(i)->GetVertexType();
		if( Type == RIGID_BLENDED_TYPE )
		{
			//float Sum=0;
			IPhyBlendedRigidVertex *vtxExport = (IPhyBlendedRigidVertex *)contextExport->GetVertexInterface(i);
			for( j=0 ; j < (OR_U32)vtxExport->GetNumberNodes() ; ++j )
			{
				OR_U32 CurBone = BonesMap[ vtxExport->GetNode(j) ];
				OR_Float Weight = vtxExport->GetWeight(j);
				//Sum += Weight;
				OrionSkin->SetWeight( CurBone, i, Weight+OrionSkin->GetWeight( CurBone, i ) );
			}
			/*OR_ASSERT( Sum > OR_EPSILON );
			for( j=0 ; j<vtxExport->GetNumberNodes() ; ++j )
			{
				OR_U32 CurBone = BonesMap[ vtxExport->GetNode(j) ];
				OrionSkin->SetWeight( CurBone, i, OrionSkin->GetWeight( CurBone, i )/Sum );
			}
			*/
		}
		else if( Type == RIGID_NON_BLENDED_TYPE )
		{
			IPhyRigidVertex *vtxExport = (IPhyRigidVertex *)contextExport->GetVertexInterface(i);
			OR_U32 CurBone = BonesMap[ vtxExport->GetNode() ];
			OrionSkin->SetWeight( CurBone, i, 1 );
		}
	}
	for( i=0 ; i<LookupTable.size() ; ++i )
	{
		for( j=0 ; j<BonesMap.size() ; ++j )
		{
			OrionSkin->SetWeight( j, i+NbrVerts , OrionSkin->GetWeight( j, LookupTable[i] ) );
		}
	}


	OrionSkin->Initialize();

	phyExport->SetInitialPose( false );
	PhysiqueMod->EnableMod();
	phyExport->ReleaseContextInterface( contextExport );

	return OrionSkin;

//#endif // CURRENT_VERSION == 3

//#else // !defined I_PHYEXPORT
//	return NULL;
//#endif // I_PHYEXPORT
}



OR_Skin*	OR_3DS_MAXNode::GetOR_SkinFromISkin( TimeValue Time, T_U32Vector &LookupTable, Modifier *SkinMod )
{
	OR_U32 i,j;
	OR_U32 NBones; //Number of bones

	ISkin *Skin = (ISkin*)SkinMod->GetInterface(I_SKIN);
	if( !Skin ) return NULL;
	ISkinContextData *ContextData = Skin->GetContextInterface(this);
	if( !ContextData ) return NULL;
	NBones = Skin->GetNumBones();
	
	//Initialize the skin
	SkinMod->DisableMod();
	OR_Mesh* OrionMesh = GetOR_Mesh( Time, LookupTable );
	OR_Skin* OrionSkin = new OR_Skin( *OrionMesh );
	delete OrionMesh;
	SkinMod->EnableMod();
	OrionSkin->SetNbrBones( NBones );

	//Get the mesh reference matrix
	Matrix3 MeshRefMatrice;
	OR_Matrix4x4 ORMeshRefMatrice;
	OR_ASSERT( Skin->GetSkinInitTM( this, MeshRefMatrice, true ) == SKIN_OK );
	
	/*	trick : ISkin::GetSkinInitTM ALWAYS return the object TM even if we ask
		for the node TM. So we take the object TM and pre-multiply by the inverse
		of the offset TM to get the right Reference Node TM of the skin */
	Matrix3 OffsetMatrix = GetOffsetMatrix3( Time );
	MeshRefMatrice = Inverse(OffsetMatrix)*MeshRefMatrice;

	ORMeshRefMatrice = OR_3DS_Utils::ToOR_Matrix( MeshRefMatrice );
	OrionSkin->SetMeshRefMatrix( ORMeshRefMatrice );

	//Set the bones reference matrices
	for( i=0 ; i < NBones ; i++ )
	{
		INode* Bone = Skin->GetBone(i);
		OrionSkin->SetBone( i, (OR_Object*)Bone );

		OR_Matrix4x4 ORBoneRefMatrices;
		Matrix3 BoneRefMatrice;
		OR_ASSERT( Skin->GetBoneInitTM( Bone, BoneRefMatrice, false ) == SKIN_OK );
		//BoneRefMatrice = Inverse( BoneRefMatrice );
		ORBoneRefMatrices = OR_3DS_Utils::ToOR_Matrix( BoneRefMatrice );
		//Initialise skin with references matrices
		OrionSkin->SetRefMatrix( i, ORBoneRefMatrices );
	}

	//Initialise skin with weights
	OR_U32 NbISkinPoints = ContextData->GetNumPoints();
	OR_U32 NbPoints = OrionSkin->GetNbVertex() - LookupTable.size();
	OR_U32 Offset = NbPoints;
	
	if( NbISkinPoints > NbPoints )
		OR_Globals::MessageHandler()->Warning( "OR_3DS_MAXNode::GetOR_SkinFromISkin", 
		"The Skin modifier has more points than the mesh.\nIf you are skinning a patch, add a \"Turn to Mesh\" modifier before the Skin modifier." );
	if( NbISkinPoints < NbPoints ) NbPoints = NbISkinPoints;
	
	if( NBones )
	{		
		for( i=0 ; i < NbPoints ; ++i )
		{
			for( j=0 ; j < (OR_U32)ContextData->GetNumAssignedBones(i) ; ++j )
			{
				if( ContextData->GetBoneWeight(i,j) > 0 )
				{
					OrionSkin->SetWeight( ContextData->GetAssignedBone(i,j) , i, ContextData->GetBoneWeight(i,j) );
				}
			}
		}
		for( i=0 ; i < (OR_U32)LookupTable.size() ; ++i )
		{
			for( j=0 ; j < NBones ; ++j )
			{
				OrionSkin->SetWeight( j, i+Offset , OrionSkin->GetWeight( j, LookupTable[i] ) );
			}
		}
	}
		
	OrionSkin->Initialize();

	// Log some infos about the skin
	const OR_Skin::T_SkinEltList& SkinEltList = OrionSkin->GetSkinElts();
	OR_Globals::LogManager()->AddString("\nExporting skin for %s : %d skin links for %d faces and %d bones",
				  OrionSkin->GetName(), SkinEltList.size(), OrionSkin->GetNbFaces(), OrionSkin->GetNbrBones() );
	OR_Globals::LogManager()->AddIndent();

	i = 0;
	for( OR_Skin::CIT_SkinEltList it = SkinEltList.begin() ; it != SkinEltList.end() ; ++it )
	{
		OR_Globals::LogManager()->AddString("\nSkin #%d : %d faces for %d bones", 
					  i, (*it).m_NbrFaces , (*it).m_Bones.size() );
		++i;
	}
	OR_Globals::LogManager()->SubIndent();
	OR_Globals::LogManager()->AddString("\n----\n");

	return OrionSkin;
}



Modifier* OR_3DS_MAXNode::FindSkinModifier()
{
	// Get object from node. Abort if no object.
	Object* pObj = this->GetObjectRef();
	
	if (!pObj) return NULL;

	// Is derived object ?
	while (pObj->SuperClassID() == GEN_DERIVOB_CLASS_ID)
	{
		// Yes -> Cast.
		IDerivedObject* pDerObj = static_cast<IDerivedObject*>(pObj);

		// Iterate over all entries of the modifier stack.
		int ModStackIndex = 0;
		while (ModStackIndex < pDerObj->NumModifiers())
		{
			// Get current modifier.
			Modifier* mod = pDerObj->GetModifier(ModStackIndex);

			// Is this Skin ?
			if (mod->ClassID() == SKIN_CLASSID )
			{
				// Yes -> Exit.
				return mod;
			}

			// Next modifier stack entry.
			ModStackIndex++;
		}
		pObj = pDerObj->GetObjRef();
	}

	// Not found.
	return NULL;
}

// From Character Studio's SDK
Modifier* OR_3DS_MAXNode::FindPhysiqueModifier()
{
	// Get object from node. Abort if no object.
	Object* ObjectPtr = this->GetObjectRef();
	if( !ObjectPtr ) return NULL;
	
	while (ObjectPtr->SuperClassID() == GEN_DERIVOB_CLASS_ID && ObjectPtr)
	{
		// Yes -> Cast.
		IDerivedObject* DerivedObjectPtr = (IDerivedObject *)(ObjectPtr);				
			
		// Iterate over all entries of the modifier stack.
		int ModStackIndex = 0;

		while (ModStackIndex < DerivedObjectPtr->NumModifiers())
		{
			// Get current modifier.
			Modifier* ModifierPtr = DerivedObjectPtr->GetModifier(ModStackIndex);

			// Is this Physique ?
			if (ModifierPtr->ClassID() == Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B))
			{
				return ModifierPtr;
			}

			ModStackIndex++;
		}

		ObjectPtr = DerivedObjectPtr->GetObjRef();
	}

	// Not found.
	return NULL;
}

} // End namespace OR_3DS


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

