//-------------------------------------------------------------------------
/** \name GW file inclusion */
//-------------------------------------------------------------------------
//@{
#include <il/il.h>
#include <il/ilut.h>
#include "stdafx.h"
#include <GL/glut.h>
#include "../../gw_toolkit/GW_Toolkit.h"
#include "../../gw_geodesic/GW_Parameterization.h"
#include "../../gw_toolkit/GW_InputOutput.h"
#include "../../gw_multiresolution_toolkit/GW_TopographicFunction.h"
#undef exit
using namespace GW;
//@}

//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef GW_DEBUG
	#pragma comment(lib, "glut32.lib")
	#include <il/il.h>
	#include <il/ilut.h>
	#pragma comment(lib, "gw_core_dbg.lib")
	#pragma comment(lib, "gw_toolkit_dbg.lib")
	#pragma comment(lib, "gw_geodesic_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit_dbg.lib")
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "DevIL.lib")
	#pragma comment(lib, "ilu.lib")
	#pragma comment(lib, "ilut.lib")
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_toolkit.lib")
	#pragma comment(lib, "gw_geodesic.lib")
	#pragma comment(lib, "gw_multiresolution.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit.lib")
#endif // GW_DEBUG
//@}


GW_Toolkit Toolkit;
GW_Parameterization Parameterization;
GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
GW_VoronoiMesh& VoronoiMesh = Toolkit.GetVoronoiMesh();
GW_GeodesicDisplayer& Displayer = Toolkit.GetGeodesicDisplayer();
T_GeodesicVertexList& VertList = Toolkit.GetVoronoiMesh().GetBaseVertexList();
GW_Bool bDisplayMesh = GW_True;
GW_Bool bDisplayVoronoiMesh = GW_False;

/** wire frame/filled mode */
GLfloat nLineWidth = 1;
GW_Bool bWireFrameModeOn = GW_False;
GW_Bool bFilledModeOn = GW_True;
#define WIREFRAME_COLOR 0
#define BACKGROUND_COLOR 1
#define WINDOW_SIZE 600

/** interpolation data */
GW_Float rXInterp = 0.33;
GW_Float rYInterp = 0.33;
GW_Float rXInterpStep = 0.02;
GW_Float rYInterpStep = 0.02;
GW_Vector3D InterpPos;

/* texture for the visage */
GW_TopographicFunction TextureMapping;
GW_TopographicFunction TextureMapping_Grad;
#define TEXTURE_FILE_NAME		"../ressources/wrl/headus/eric-head/head.jpg"
#define TEXTURE_FILE_NAME_GRAD	"../ressources/wrl/headus/eric-head/head_grad.jpg"

// #define TEXTURE_FILE_NAME	"../ressources/wrl/headus/lyndon/head.jpg"
// #define TEXTURE_FILE_NAME_GRAD	"../ressources/wrl/headus/lyndon/head_grad.jpg"
// #define TEXTURE_FILE_NAME		"../ressources/images/crackymud.jpg"
// #define TEXTURE_FILE_NAME_GRAD	"../ressources/images/crackymud_grad.jpg"


GW_U32 nNbrTexture = 0;
GW_U32 nTextureSeleted = 2;
/** texture loading */
void load_texture(const char* file)
{
	if( ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
		iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION ||
		ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION ) 
	{
		cout << "DevIL version is different...exiting!";
		exit(1);
	} 
	ilInit();

	nNbrTexture++;
	ILuint Image;
	ilGenImages( 1, &Image );
	ilBindImage( Image );
	ilEnable(IL_ORIGIN_SET);
	ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);
	ILboolean Ok = ilLoadImage( ILstring(file) );
	if( !Ok  )
	{
		cout << "Error while loading textre " << file << endl;
		exit(1);
	}
	GW_U32 Width = ilGetInteger(IL_IMAGE_WIDTH);
	GW_U32 Height = ilGetInteger(IL_IMAGE_HEIGHT); 
	char str[150];
	sprintf(str, "Loading image %s, size %ux%u", file, Width, Height);
	cout << str << endl;

	/* binding with opengl */
	ilutRenderer( ILUT_OPENGL );
	GLuint Texture = ilutGLBindTexImage();

	ilDeleteImages( 1, &Image );
}


GW_Float rCurvatureWeight = 0.1;
GW_Bool bDisplayGradient = GW_True;
GW_Bool bAvoidEdge = GW_False;
GW_Float rAvoid = 10;
GW_Float rStopAtEdge = 10;			// 80

GW_Float CurvatureWeightCallback(GW_GeodesicVertex& Vert)
{

	/* curvature computation */
	GW_Float rCurv_Val = Vert.GetMaxCurv()*Vert.GetMaxCurv() + Vert.GetMinCurv()*Vert.GetMinCurv();
	GW_CLAMP( rCurv_Val, 0, 50 );
	//	GW_ASSERT( Vert.GetMaxAbsCurv()>=0 && Vert.GetMaxAbsCurv()<10000 );


	/* gradient computation */
	GW_Float rGrad_Val = TextureMapping_Grad.GetValue( Vert.GetTexCoordU(), 1-Vert.GetTexCoordV() );

#if 0
	if( Vert.GetMaxAbsCurv()>=0 && Vert.GetMaxAbsCurv()<100 )
		return 0.5+rCurvatureWeight*Vert.GetMaxAbsCurv();
	else
		return 1;
#else
	if( bAvoidEdge )
		return 1/(0.5+rAvoid*rGrad_Val);
	else
		return 0.5+rStopAtEdge*rGrad_Val;
#endif

}
GW_Float BasicWeightCallback(GW_GeodesicVertex& Vert)
{
	return 1;
}

// GW_GeodesicMesh::T_WeightCallbackFunction WeightCallback = BasicWeightCallback; // HalfHalfWeightCallback;
GW_GeodesicMesh::T_WeightCallbackFunction WeightCallback = CurvatureWeightCallback;


void FlattenMesh()
{
	for( GW_U32 i=0; i<Mesh.GetNbrVertex(); ++i )
	{
		GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) Mesh.GetVertex(i);
		pVert->SetPosition( GW_Vector3D( 4*pVert->GetTexCoordU()-2, 4*pVert->GetTexCoordV()-2, 0 ) );
	}
	return;
	for( GW_U32 i=0; i<Mesh.GetNbrVertex(); ++i )
	{
		GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) Mesh.GetVertex(i);
		GW_Vector3D pos = pVert->GetPosition();
		pos.Normalize();
		GW_Float rLong, rLat;
		GW_SphericalMaths::ConvertCartesianToSpherical( pos, rLong, rLat );
		rLat = (rLat+GW_HALFPI)/GW_PI;
		rLong = rLong/GW_TWOPI;
		GW_ASSERT( rLat<=1 && rLat>=0 );
		GW_ASSERT( rLong<=1 && rLong>=0 );
		pVert->SetPosition( GW_Vector3D( 4*rLong-2, 4*rLat-2, 0 ) );
	}
}

/** compute the color using the image */
void ComputeColorCallback( GW_Vertex& Vert, float* color )
{
	if( bDisplayGradient )
	{
#if 0
		GW_Float gu=0, gv=0;
		TextureMapping.GetGradient( Vert.GetTexCoordU(), Vert.GetTexCoordV(), gu, gv );
		GW_Float rVal = sqrt(gu*gu + gv*gv)/6.0;
#endif
		GW_Float rVal = TextureMapping_Grad.GetValue( Vert.GetTexCoordU(), Vert.GetTexCoordV() );
		color[0] = (float) rVal;
		color[1] = (float) rVal;
		color[2] = (float) rVal;
	}
	else
	{
		GW_Float rVal = TextureMapping.GetValue( Vert.GetTexCoordU(), Vert.GetTexCoordV() );
		color[0] = (float) rVal;
		color[1] = (float) rVal;
		color[2] = (float) rVal;
	}
}


#ifdef GW_DEBUG
	#define FILE_LIST "files_debug.txt"
#else
	#define FILE_LIST "files.txt"
#endif
T_StringList FileList;
IT_StringList SelectedFile = FileList.end();

void load_file()
{
	if( SelectedFile!=FileList.end() )
	{
		if( Toolkit.LoadFile( (*SelectedFile).c_str() )<0 )
			exit(-1);
	}
	Displayer.DisableDraw( GW_BasicDisplayer::kVertexParametrization );
	Displayer.DisableDraw( GW_BasicDisplayer::kStoppingVertex );
}

/*------------------------------------------------------------------------------*/
/** 
* Name : init
*
*  \author Gabriel Peyré 2001-10-17
*
*	Init various stuff.
*/ 
/*------------------------------------------------------------------------------*/
void init()
{	
	/* load into opengl */
	load_texture(TEXTURE_FILE_NAME);
	load_texture(TEXTURE_FILE_NAME_GRAD);
	glBindTexture( GL_TEXTURE_2D, nTextureSeleted );
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
		GL_NEAREST);

	/* loading data from an image **************************************/
	cout << "Loading image file " << TEXTURE_FILE_NAME << " ..." << endl;
	GW_RETURN_CODE bRes = TextureMapping.LoadFromImage(TEXTURE_FILE_NAME);
	if( bRes<0 )
	{
		cout << "Loading failed." << endl;
		::exit(1);
	}
	cout << "Loading successful." << endl;
	cout << "----" << endl;
	TextureMapping.ScaleTo( 0,1.0 );

	/* loading data from an image **************************************/
	cout << "Loading image file " << TEXTURE_FILE_NAME_GRAD << " ..." << endl;
	bRes = TextureMapping_Grad.LoadFromImage(TEXTURE_FILE_NAME_GRAD);
	if( bRes<0 )
	{
		cout << "Loading failed." << endl;
		::exit(1);
	}
	cout << "Loading successful." << endl;
	cout << "----" << endl;
	TextureMapping_Grad.ScaleTo( 0,1.0 );

//	Displayer.RegisterComputeColorCallback( ComputeColorCallback );

	/* redirect GW messages */
	GW_OutputStream = stdout;

	if( GW_Toolkit::LoadFileList( FILE_LIST, FileList )<0 )
	{
		cerr << "Can't open files listing " << FILE_LIST << "." << endl;
		exit(-1);
	}
	SelectedFile = FileList.begin();

	/* load the current file */
	load_file();
}

void draw_scene()
{
	if( bDisplayMesh )
	{
		/* render path */
		Displayer.DisplayPath( Toolkit.GetGeodesicPath(), GW_Vector3D(1,1,1) );
		/* display the list of vertex */
		Displayer.DisplayVoronoiPoints( VoronoiMesh, GW_Vector3D(1,1,1) );
		/* render mesh */
		Displayer.DisplayMesh( Mesh );
	}
	if( bDisplayVoronoiMesh )
	{
		glDisable(GL_TEXTURE_2D);
		glDisable( GL_CULL_FACE );
		Toolkit.GetCoarseDisplayer().DisplayMesh( VoronoiMesh );
		glEnable( GL_CULL_FACE );
		glEnable(GL_TEXTURE_2D);
	}
}

void display_startpoint( GW_Vertex* pVert, GW_Float r, GW_Float v, GW_Float b )
{
	if( pVert!=NULL )
	{
		glPointSize( 6 );
		glColor3f( r,v,b );
		glDisable( GL_LIGHTING );
		glBegin( GL_POINTS );
			glVertex( *pVert );
		glEnd();
		glEnable( GL_LIGHTING );
	}
}

void display()
{
	GW_InputOutput::PrepareDisplay();
	
	glDisable( GL_CULL_FACE );

	glPushMatrix();

	if( bWireFrameModeOn )
	{
		Displayer.EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		Toolkit.GetCoarseDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		glDisable( GL_LIGHTING );
		glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth( nLineWidth );
		draw_scene();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_LIGHTING );
		Displayer.DisableDraw( GW_BasicDisplayer::kForceMonoColor );
		Toolkit.GetCoarseDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
	}
	if( bFilledModeOn )
		draw_scene();

	/* draw a dot at position of the interpolation */
	glDisable( GL_LIGHTING );
	glLineWidth( 8.0 );
	glColor3f( 1,1,0 );
	glBegin( GL_POINTS );
//	glVertex( InterpPos );
	glEnd();
	glEnable( GL_LIGHTING );

	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}



void TakeScreenShot( const char* base_name = "image", const char* extension = "jpg")
{
	// perform a screenshot
	ILuint ImageName;
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	ilutGLScreen();	

	string num_str, file_name;
	for( GW_U32 num=0; num<999; num++ ) 
	{
		num_str = "";
		if( num<10 )
			num_str = num_str + "0";
		if( num<100 )
			num_str = num_str + "0";
		char tmp[256];
		sprintf(tmp, "%u", num );
		num_str = num_str + tmp;

		file_name = string(base_name) + num_str + string(".") + extension;
		FILE* pF = fopen(file_name.c_str(), "rb");
		if( !pF )
			break;
		fclose(pF);
	}
	ilEnable(IL_FILE_OVERWRITE);
	ilSaveImage( (char*) file_name.c_str() );
}

string base_name = "face_adaptive/image";

/*------------------------------------------------------------------------------*/
// Name : keyboard
/**
*  \param  button [GW::GW_U32] key pressed.
*  \param  x [GW::GW_I32] x position of the mouse.
*  \param  y [GW::GW_I32] y position of the mouse.
*  \author Gabriel Peyré
*  \date   11-24-2002
* 
*  To handle the keyboard.
*/
/*------------------------------------------------------------------------------*/
void keyboard(unsigned char button, int x, int y)
{

	switch((char) button)
	{
	case 27:
		::exit(0);
		break;
	case 'w':
		bWireFrameModeOn = !bWireFrameModeOn;
		if( bWireFrameModeOn )
			cout << "Wireframe mode ON." << endl;
		else
			cout << "Wireframe mode OFF." << endl;
		break;
	case 'x':
		bFilledModeOn = !bFilledModeOn;
		if( bFilledModeOn )
			cout << "Filled mode ON." << endl;
		else
			cout << "Filled mode OFF." << endl;
		break;
	case '+':
		cout << "Increasing constrast." << endl;
		if( Displayer.GetPropriety(GW_BasicDisplayer::kGeodesicDistance) )
			Displayer.IncreaseContrast( GW_BasicDisplayer::kGeodesicDistance );
		Displayer.BuildColorArray( Mesh );
		break;
	case '-':
		cout << "Decreasing constrast." << endl;
		if( Displayer.GetPropriety(GW_BasicDisplayer::kGeodesicDistance) )
			Displayer.DecreaseContrast( GW_BasicDisplayer::kGeodesicDistance );
		Displayer.BuildColorArray( Mesh );
		break;
	case 'r':
		Mesh.ResetGeodesicMesh();
		Displayer.BuildColorArray( Mesh );
		break;
	case '\t':
		nTextureSeleted++;
		if( nTextureSeleted>nNbrTexture )
			nTextureSeleted=1;
		glBindTexture( GL_TEXTURE_2D, nTextureSeleted );
		break;
	case 'f':
		Displayer.ToggleDraw(GW_BasicDisplayer::kUseFlatLighting);
		// Toolkit.GetCoarseDisplayer().ToggleDraw(GW_BasicDisplayer::kUseFlatLighting);
		if( Displayer.GetPropriety(GW_BasicDisplayer::kUseFlatLighting) )
			cout << "Using flat lighting." << endl;
		else
			cout << "Not using flat lighting." << endl;
		break;
	case 's':
		cout << "Saving saved camera settings ... done.";
		GW_InputOutput::SaveCameraSettings();
		break;
	case 'l':
		cout << "Loading saved camera settings ... done.";
		GW_InputOutput::LoadCameraSettings();
		break;
	case '\n':case '\r':
		glutFullScreen();
		break;
	case 'm':
		bDisplayMesh = !bDisplayMesh;
		break;
	case 'M':
		bDisplayVoronoiMesh = !bDisplayVoronoiMesh;
		break;
	case 'b':
		Displayer.ToggleDraw( GW_BasicDisplayer::kBoundaries );
		break;
	case 'u':
		{
			cout << "Updating distance info ... ";
			VoronoiMesh.PerformFastMarching( Mesh, VertList );
			Displayer.BuildColorArray( Mesh );
			cout << "done." << endl;
		}
		break;
	case 'a':
		TakeScreenShot(base_name.c_str());
		break;
	case '&':
		{
			float a[3] = {0,1,0};
			GW_InputOutput::RotateView(-0.01, a);
		}
		break;
	case 'é':
		{
			float a[3] = {0,1,0};
			GW_InputOutput::RotateView(0.01, a);
		}
		break;
	case '"':
		{
			float a[3] = {0,1,0};
			GW_InputOutput::RotateView(-0.01, a);
			TakeScreenShot(base_name.c_str());
		}
		break;
	case '\'':
		{
			float a[3] = {0,1,0};
			GW_InputOutput::RotateView(0.01, a);
			TakeScreenShot(base_name.c_str());
		}
		break;
	case 'p':
		VoronoiMesh.Reset();
		break;
	case 'o':
		rStopAtEdge /= 1.1;
		cout << "New stopping weight" << rStopAtEdge << endl;
		break;
	case 'O':
		rStopAtEdge *= 1.1;
		cout << "New stopping weight" << rStopAtEdge << endl;
		break;
	default:
		cout << "GW is SO COOL !" << endl;
	}
}

GW_U32 nNumLocalFrontSeleted = 0;
/*------------------------------------------------------------------------------*/
// Name : keyboard_spec
/**
*  \param  button [GW::GW_U32] key pressed.
*  \param  x [GW::GW_I32] x position of the mouse.
*  \param  y [GW::GW_I32] y position of the mouse.
*  \author Gabriel Peyré
*  \date   11-24-2002
* 
*  To handle the keyboard.
*/
/*------------------------------------------------------------------------------*/
void keyboard_spec(int key, int x, int y)
{
	GW_Bool bUseRandomStartPoint = GW_True;
	GW_Bool bAssignColor = GW_False;
	GW_Bool bFillHole = GW_False;
	switch(key)
	{
	case GLUT_KEY_F1:
		bAvoidEdge = GW_True;
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add one furthest point  ... " << endl;
		Toolkit.AddFurthestPoint(1, bUseRandomStartPoint, bAssignColor);
		cout << "done." << endl;
		Displayer.ResetFrontColor();
		Displayer.BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case GLUT_KEY_F2:
		bAvoidEdge = GW_True;
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add 10 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(10, bUseRandomStartPoint, bAssignColor);
		cout << "done." << endl;
		Displayer.BuildColorArray( Mesh );
		break;
	case GLUT_KEY_F10:
		bAvoidEdge = GW_False;
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add 100 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(100, bUseRandomStartPoint, bAssignColor);
		Displayer.ResetFrontColor();
		Displayer.BuildColorArray( Mesh );
		cout << "done." << endl;
		break;
	case GLUT_KEY_F11:
		bAvoidEdge = GW_False;
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Add 1000 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(1000, bUseRandomStartPoint, bAssignColor);
		Displayer.ResetFrontColor();
		Displayer.BuildColorArray( Mesh );
		cout << "done." << endl;
		break;
		/*
	case GLUT_KEY_F3:	// positionate one point on centroïdal position.
		bAvoidEdge = GW_False;
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Performing Loyd iteration to center the vertex ... " << endl;
		Parameterization.PerformLloydIteration( Mesh, VertList );
		Displayer.BuildColorArray( Mesh );
		cout << "done." << endl;
		VoronoiMesh.PerformFastMarching( Mesh, VertList );
		break; */
/*	case GLUT_KEY_F4:	// make an iteration of Loyd, i.e. positionate all centroïdal.
		bAvoidEdge = GW_False;
		cout << "Performing Loyd algorithm to center the vertex ... " << endl;
		Parameterization.PerformLloydAlgorithm( Mesh, VertList );
		cout << "done." << endl;
		break; 
	case GLUT_KEY_F4:
		bAvoidEdge = GW_False;
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		cout << "Performing segmentation of all regions along Voronoi edges ... " << endl;
		Parameterization.SegmentAllRegions( Mesh, VertList );
		cout << "done." << endl;
		Displayer.DisableDraw( GW_BasicDisplayer::kMarchingState );
		Displayer.EnableDraw( GW_BasicDisplayer::kBoundaries );
		Displayer.BuildVertexArray( Mesh );
		break;
	 case GLUT_KEY_F7:
		cout << "Explode the different regions ... ";
		Parameterization.ExplodeAllRegions( VertList, 0.5 );
		Displayer.BuildVertexArray( Mesh );
		cout << "done." << endl;
		break;
	case GLUT_KEY_F5:
		cout << "Flattening the mesh ... ";
		FlattenMesh();
		Displayer.BuildVertexArray( Mesh );
		cout << "done." << endl;
		break; */
	case GLUT_KEY_F6:
		Mesh.RegisterWeightCallbackFunction( WeightCallback );
		Displayer.DisableDraw( GW_BasicDisplayer::kVertexParametrization );
		cout << "Building coarse mesh ... " << endl;
		VoronoiMesh.BuildMesh( Mesh, bFillHole );
		GW_OutputComment("Building normals.");
		VoronoiMesh.BuildRawNormal();
		GW_OutputComment("Reorienting the mesh.");
		VoronoiMesh.ReOrientMesh( *VoronoiMesh.GetFace(0) );
		VoronoiMesh.ReOrientNormals();
		cout << "done." << endl;
		Displayer.BuildColorArray( Mesh );
		Toolkit.GetCoarseDisplayer().BuildVertexArray( VoronoiMesh );
		Toolkit.GetCoarseDisplayer().EnableDraw(GW_BasicDisplayer::kUseFlatLighting);
		break;
	default:
		cout << "GW is SO COOL !" << endl;
	}
}

/*------------------------------------------------------------------------------*/
/** 
* Name : main 
*
*  \param  argc ...
*  \param  argv ...
*  \author Gabriel Peyré 11-24-2002
*
*	Entry point for the application.
*/ 
/*------------------------------------------------------------------------------*/
int main( int argc, char *argv[] )
{	
    // GW_Maths::TestClass();

	/* just a hack to check memory leak under win32 */
#ifdef GW_DEBUG	
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); // Get current flag
	flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	_CrtSetDbgFlag(flag); // Set flag to the new value
#endif

	GW_InputOutput::Init(argc, argv, WINDOW_SIZE, "GW -- Test of image based remeshing");

	srand( (unsigned)time( NULL ) );

	cout << endl << "    GW -- Test of image based remeshing" << endl << endl;
	cout << "---" << endl;
	cout << "Use 'Left Click + Mouse' to spin the sphere." << endl;
	cout << "Use 'Right Click' to pop-up menu." << endl;
	cout << "Use 'Right+Left Click + mouse up/down' to zoom in/out." << endl;
	cout << "---" << endl;
	cout << "F1:  Add 1 furthest point to coarse mesh." << endl;
	cout << "F2:  Add 10 furthest points to coarse mesh." << endl;
	cout << "F3:  Perform Lloyd iteration." << endl;
	cout << "F4:  Perform segmentation." << endl;
	cout << "F6:  Build coarse mesh." << endl;
	cout << "---" << endl;
	cout << "w: Toggle wireframe ON/OFF." << endl;
	cout << "s/S: Add/Remove one front for marching." << endl;
	cout << "b/B: Add a level of base points for future coarse mesh." << endl;
	cout << "+/- : increase/decrease contrast of current proprieties." << endl;
	cout << "---" << endl;
	fflush(stdout);

	/* load a bunch of stuff */
	init();

	/* set up callback functions */
	glutKeyboardFunc( keyboard );
	glutSpecialFunc(keyboard_spec);
	glutDisplayFunc( display );

	/* run an infinite loop */
	glutMainLoop();

	return 0;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////