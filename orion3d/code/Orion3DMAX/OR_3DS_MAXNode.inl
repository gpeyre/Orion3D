/*------------------------------------------------------------------------------
 *  \file  OR_3DS_MAXNode.inl
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-11-05
 *------------------------------------------------------------------------------*/
#include "OR_3DS_MAXNode.h"

namespace OR_3DS {


int			OR_3DS_MAXNode::GetNbParam()
{
	int i=0;
	while (this->GetAppDataChunk(MyClassID, MySuperClassID , i)) 
		i++;
	return i;
}

void		OR_3DS_MAXNode::SetUserParam(OR_3DS_UserParam* Param)
{
	OR_3DS_UserParam* P;
	OR_3DS_UserParam* Copy = (OR_3DS_UserParam*)malloc(Param->Size);
	memcpy(Copy, Param, Param->Size);
	int i=0;
	while(P=this->GetUserParam(i))
	{
		if (strcmp(P->Name, Param->Name)==0) 
		{
			this->RemoveAppDataChunk(MyClassID, MySuperClassID, i);
			break;
		}
		i++;
	}
	this->AddAppDataChunk(MyClassID, MySuperClassID , i, Copy->Size , Copy);
}

OR_3DS_UserParam*	OR_3DS_MAXNode::GetUserParam(int i)
{
	AppDataChunk* DataChunk = this->GetAppDataChunk(MyClassID, MySuperClassID , i);
	if (DataChunk && DataChunk->length>=sizeof(OR_3DS_UserParam)) return ((OR_3DS_UserParam*)(DataChunk->data));
	return NULL;
}

OR_3DS_UserParam*	OR_3DS_MAXNode::GetUserParam(char* Name)
{
	OR_3DS_UserParam* Param;
	int i=0;
	do
	{
		Param = this->GetUserParam(i);
		if (Param && strcmp(Param->Name,Name)==0) return Param;
		i++;
	}while(Param);
	return NULL;
}

bool		OR_3DS_MAXNode::RemoveUserParam(char* Name)
{
	OR_3DS_UserParam* Param;
	int i=0;
	do
	{
		Param = this->GetUserParam(i);
		if (Param && strcmp(Param->Name,Name)==0) 
		{
			return (this->RemoveAppDataChunk(MyClassID, MySuperClassID , i)==TRUE);
		}
		i++;
	}while(Param);
	return false;
	
}
bool		OR_3DS_MAXNode::RemoveUserParam(int i)
{
	return (this->RemoveAppDataChunk(MyClassID, MySuperClassID , i)==TRUE);
}

OR_Object&	OR_3DS_MAXNode::GetOR_Object(TimeValue Time, T_U32Vector &LookupTable, OR_3DS_Node* Root )
{
	OR_Object* Result = NULL;

	Object* ObjRef = this->EvalWorldState(0).obj;
	if( !ObjRef ) Result = new OR_PointGizmo;

	//Search for an identic Orion3D object
	if( !Result && Root )
	{
		OR_3DS_Node* DupNode = OR_3DS_Utils::FindNodeForObject( Root, ObjRef );
		if( DupNode ) 
		{
			OR_Object* DupObj = DupNode->GetObject();
			if( DupObj ) Result = (OR_Object*)DupObj->Clone();
		}
	}

	//Couldn't find any similar Orion3D object
	if( !Result )
	{
		switch ( ObjRef->SuperClassID() )
		{
			case GEOMOBJECT_CLASS_ID:
			{
				/*if (this->GetBoneNodeOnOff())
					Result = this->GetOR_Bone(Time);
				else*/
				Result = this->GetOR_Skin( Time, LookupTable );
				if( !Result )
					Result = this->GetOR_Mesh( Time, LookupTable );
				
				if ( Result ) break;
				//!!! le break est dans le if(Result) comme ca si le if
				//est faux l'objet est pris comme un gizmo (eg : target des lights/cams)
			}
			case HELPER_CLASS_ID:
			{
				Result = this->GetOR_Gizmo(Time);
				break;
			}
			case LIGHT_CLASS_ID:
			{
				Result = this->GetOR_Light(Time);
				break;
			}
			case CAMERA_CLASS_ID:
			{
				Result = this->GetOR_Camera(Time);
				break;
			}
			default:
				Result = new OR_PointGizmo;
				break;		
		}
	}

	//Couldn't convert the 3DS object to an Orion3D one
	if (!Result) Result = new OR_PointGizmo;
	
	Result->SetName( OR_String( this->GetName() ).replace( ' ', '_' ) );
	Result->SetAbsoluteMatrix( this->GetOR_Matrix(Time) );
	Result->SetRelativeMatrix( this->GetRelativeOR_Matrix(Time) );
	Result->SetVisible( !this->IsHidden() );

	return *Result;
}




OR_3DS_Node&	OR_3DS_MAXNode::GetNode( TimeValue Time , OR_Node* Father, OR_3DS_Node* Root )
{
	OR_Globals::LogManager()->AddString("\nExporting node from %s...",this->GetName());
	OR_Globals::LogManager()->AddIndent();

	OR_3DS_Node* NewNode = new OR_3DS_Node();
	NewNode->SetMAXNode(this);
	NewNode->SetMAXTarget(this->GetTarget());
	NewNode->SetObject( this->GetOR_Object( Time, NewNode->LookupTable, Root ) );
	NewNode->SetFather(Father);

	OR_Globals::LogManager()->SubIndent();

	return *NewNode;
}


OR_Matrix4x4 OR_3DS_MAXNode::GetRelativeOR_Matrix(TimeValue Time)
{
	return OR_3DS_Utils::ToOR_Matrix(this->GetRelativeMatrix3(Time));
}


OR_Matrix4x4	OR_3DS_MAXNode::GetOR_Matrix(TimeValue Time)
{
	return OR_3DS_Utils::ToOR_Matrix(this->GetMatrix3(Time));	
}

Matrix3 OR_3DS_MAXNode::GetMatrix3(TimeValue Time)
{
	return this->GetNodeTM( Time );
}

Matrix3 OR_3DS_MAXNode::GetRelativeMatrix3(TimeValue Time)
{
	Matrix3 Mat = this->GetMatrix3(Time);
	if (this->GetParentNode())
	{
		Matrix3 FatherMatrix = ((OR_3DS_MAXNode*)this->GetParentNode())->GetMatrix3(Time);
		FatherMatrix.Invert();
		Mat = Mat * FatherMatrix;
	}
	return Mat;
}


/*------------------------------------------------------------------------------
 * Name : OR_3DS_MAXNode::GetOffsetMatrix3				
 *
 *  \param  Time EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-10
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
Matrix3	OR_3DS_MAXNode::GetOffsetMatrix3(TimeValue Time)
{
	Matrix3 NodeMatrix = this->GetNodeTM( Time );
	Matrix3 ObjMatrix = this->GetObjectTM( Time );
	return ObjMatrix*Inverse(NodeMatrix);
}


/*------------------------------------------------------------------------------
 * Name : OR_3DS_MAXNode::GetOffsetOR_Matrix		
 *
 *  \param  Time EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-10-10
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_Matrix4x4 OR_3DS_MAXNode::GetOffsetOR_Matrix(TimeValue Time)
{
	return OR_3DS_Utils::ToOR_Matrix( GetOffsetMatrix3( Time ) );
}




OR_3DS_UserParam* new_UserParamU32(char* Name, OR_U32 Val)
{
	OR_3DS_UserParam* P = (OR_3DS_UserParam*)malloc(4+256+4+4);
//	OR_3DS_UserParam* P = (OR_3DS_UserParam*)(new char[4+256+4+4]);
	P->Size = 4+256+4+4;
	strncpy(P->Name, Name, 256);
	P->Type = OR_3DS_UserParam::UserParam_U32;
	(*((OR_U32*)P->Data)) = Val;
	return P;
}


OR_3DS_UserParam* new_UserParamString(char* Name, unsigned int length, char* Val)
{
	OR_3DS_UserParam* P = (OR_3DS_UserParam*)malloc(4+256+4+length);
//	OR_3DS_UserParam* P = (OR_3DS_UserParam*)(new char[4+256+4+length]);
	P->Size = 4+256+4+length;
	strncpy(P->Name, Name, 256);
	P->Type = OR_3DS_UserParam::UserParam_String;
	if (Val) strncpy(P->Data, Val, length);
	return P;
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

