/*------------------------------------------------------------------------------
 *  \file  OR_3DS_MAXMaterial.cpp
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Antoine Bouthors 2001-11-05
 *------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_3DS_MAXMaterial.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "stdafx.h"
#include "OR_3DS_MAXMaterial.h"

#ifndef OR_USE_INLINE
#   include "OR_3DS_MAXMaterial.inl"
#endif

namespace OR_3DS {


	

OR_Shader* OR_3DS_MAXMaterial::GetOR_Shader(TimeValue Time)
{
	OR_Globals::LogManager()->AddString( "\nExporting shader from %s...", this->GetName() );
	OR_Globals::LogManager()->AddIndent();
	OR_Globals::LogManager()->AddLine( "\nType : " );

	OR_Shader* TheShader = NULL;

	if( this->ClassID() == Class_ID(  MULTI_CLASS_ID, 0 ) )
	{
		OR_Globals::LogManager()->AddLine( "Multi" );
		TheShader = new OR_MultiShader();
	}
	else if( this->ClassID() == Class_ID( DMTL_CLASS_ID, 0 ) )
	{
		StdMat* Std = (StdMat *)this;

		// Access the Diffuse map and see if it's a Bitmap texture
		Texmap *tmap = Std->GetSubTexmap(ID_DI);
		if (tmap && tmap->ClassID() == Class_ID( BMTEX_CLASS_ID, 0) && Std->SubTexmapOn(ID_DI) ) 
		{
			BitmapTex *bmt = (BitmapTex*) tmap;
			OR_Globals::LogManager()->AddString( "Single bitmap (%s)", bmt->GetMapName() );
			TheShader = new OR_SingleTextureMapShader( bmt->GetMapName() );			
		}
		else
		{
			TheShader = new OR_FlatShader;
			OR_Globals::LogManager()->AddLine( "Flat" );
		}
		
		if (TheShader->GetType() == OR_SHADER_SingleTextureMap)
		{
			TheShader->SetAmbient(R, 1.f);
			TheShader->SetAmbient(V, 1.f);
			TheShader->SetAmbient(B, 1.f);
		}
		else
		{
			TheShader->SetAmbient(R, Std->GetAmbient(Time).r);
			TheShader->SetAmbient(V, Std->GetAmbient(Time).g);
			TheShader->SetAmbient(B, Std->GetAmbient(Time).b);
		}

		if (TheShader->GetType() == OR_SHADER_SingleTextureMap)
		{
			TheShader->SetDiffuse(R, 1.f);
			TheShader->SetDiffuse(V, 1.f);
			TheShader->SetDiffuse(B, 1.f);
		}
		else
		{
			TheShader->SetDiffuse(R, Std->GetDiffuse(Time).r);
			TheShader->SetDiffuse(V, Std->GetDiffuse(Time).g);
			TheShader->SetDiffuse(B, Std->GetDiffuse(Time).b);
		}
				
		float ShineStr = Std->GetShinStr(Time);
		
		TheShader->SetSpecular(R, Std->GetSpecular(Time).r*ShineStr);
		TheShader->SetSpecular(V, Std->GetSpecular(Time).g*ShineStr);
		TheShader->SetSpecular(B, Std->GetSpecular(Time).b*ShineStr);
		
		if (Std->GetSelfIllumColorOn()==TRUE)
		{
			TheShader->SetEmission(R, Std->GetSelfIllumColor(Time).r);
			TheShader->SetEmission(V, Std->GetSelfIllumColor(Time).g);
			TheShader->SetEmission(B, Std->GetSelfIllumColor(Time).b);
		}
		else
		{
			TheShader->SetEmission(R, Std->GetSelfIllum(Time)*Std->GetDiffuse(Time).r);
			TheShader->SetEmission(V, Std->GetSelfIllum(Time)*Std->GetDiffuse(Time).g);
			TheShader->SetEmission(B, Std->GetSelfIllum(Time)*Std->GetDiffuse(Time).b);
		}
		if( Std->GetOpacity(Time) > 1.-OR_EPSILON )
		{
			TheShader->SetNeedsSorting( false );
			TheShader->SetBlendingMode( OR_Blending_None );
		}
		else
		{
			TheShader->SetNeedsSorting( true );
			TheShader->SetBlendingMode( OR_Blending_SrcA_1MinusSrcA );
		}		
		
		TheShader->SetAmbient(A, Std->GetOpacity(Time));
		TheShader->SetDiffuse(A, Std->GetOpacity(Time));
		TheShader->SetSpecular(A, 1);
		TheShader->SetEmission(A, 1);

		TheShader->SetShine(Std->GetShininess(Time)*128.);
		
		if(Std->GetTwoSided()==TRUE) TheShader->SetCullingMode(OR_Culling_None);
		else TheShader->SetCullingMode(OR_Culling_Back);

		OR_Globals::LogManager()->AddString("\nAmbient color  : R=%.3f G=%.3f B=%.3f", TheShader->GetAmbient()[0], TheShader->GetAmbient()[1], TheShader->GetAmbient()[2]);
		OR_Globals::LogManager()->AddString("\nDiffuse color  : R=%.3f G=%.3f B=%.3f", TheShader->GetDiffuse()[0], TheShader->GetDiffuse()[1], TheShader->GetDiffuse()[2]);
		OR_Globals::LogManager()->AddString("\nSpecular color : R=%.3f G=%.3f B=%.3f", TheShader->GetSpecular()[0], TheShader->GetSpecular()[1], TheShader->GetSpecular()[2]);
		OR_Globals::LogManager()->AddString("\nEmission color : R=%.3f G=%.3f B=%.3f", TheShader->GetEmission()[0], TheShader->GetEmission()[1], TheShader->GetEmission()[2]);
		OR_Globals::LogManager()->AddString("\nAlpha : %.3f", TheShader->GetAmbient()[3]);
		OR_Globals::LogManager()->AddString("\nShininess : %.3f", TheShader->GetShine());
		OR_Globals::LogManager()->AddString("\nShin. Strength : %.3f", ShineStr);

	}
	if( TheShader )
	{
		TheShader->SetName( OR_String( this->GetName().data() ).replace( ' ', '_' ) );
	}
	else
		OR_Globals::LogManager()->AddLine( "Unsupported" );
	
	OR_Globals::LogManager()->SubIndent();
	return TheShader;

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

