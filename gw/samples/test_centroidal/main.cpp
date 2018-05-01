//-------------------------------------------------------------------------
/** \name GW file inclusion */
//-------------------------------------------------------------------------
//@{
#include <il/il.h>
#include <il/ilut.h>
#include "stdafx.h"
#include <GL/glut.h>
#include "../../gw_toolkit/GW_Toolkit.h"
#include "../../gw_toolkit/GW_InputOutput.h"
#include "../../gw_toolkit/GW_VRMLLoader.h"
#include "../../gw_geodesic/GW_Parameterization.h"
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
	#pragma comment(lib, "DevIL-d.lib")
	#pragma comment(lib, "ilu-d.lib")
	#pragma comment(lib, "ilut-d.lib")
	#pragma comment(lib, "gw_core_dbg.lib")
	#pragma comment(lib, "gw_toolkit_dbg.lib")
	#pragma comment(lib, "gw_geodesic_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit_dbg.lib")
	#pragma comment(lib, "gw_compression_dbg.lib")
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "DevIL.lib")
	#pragma comment(lib, "ilu.lib")
	#pragma comment(lib, "ilut.lib")
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_toolkit.lib")
	#pragma comment(lib, "gw_geodesic.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit.lib")
	#pragma comment(lib, "gw_compression.lib")
#endif // GW_DEBUG
//@}

GW_Toolkit Toolkit;
GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
GW_VoronoiMesh& VoronoiMesh = Toolkit.GetVoronoiMesh();
T_GeodesicVertexList& VertexList = VoronoiMesh.GetBaseVertexList();
GW_Bool bDisplayMesh = GW_True;
GW_Bool bDisplayVoronoiMesh = GW_False;

/** wire frame/filled mode */
GLfloat nLineWidth = 1;
GW_Bool bWireFrameModeOn = GW_False;
GW_Bool bFilledModeOn = GW_True;
#define WIREFRAME_COLOR 0
#define BACKGROUND_COLOR 1
#define WINDOW_SIZE 600

GW_Parameterization Parameterization_;


#ifdef GW_DEBUG
	#define FILE_LIST "files_debug.txt"
#else
	#define FILE_LIST "files.txt"
#endif
T_StringList FileList;
IT_StringList SelectedFile = FileList.end();

typedef std::vector<T_GeodesicVertexList*> T_VertexListVector;
typedef T_VertexListVector::iterator IT_VertexListVector;
typedef std::vector<GW_GeodesicDisplayer*> T_DisplayerVector;
typedef T_DisplayerVector::iterator IT_DisplayerVector;
typedef std::vector<GW_VoronoiMesh*> T_VoronoiMeshVector;
typedef T_VoronoiMeshVector::iterator IT_VoronoiMeshVector;

/** list of available meshes */
/** 0=main mesh, 1=models to flatten, 2=models flatened */
GW_U32 DisplayedMesh;
GW_U32 DisplayedMesh_Nbr = 3;
T_GeodesicMeshVector MeshToFlatten;
T_VoronoiMeshVector MeshToFlatten_VoronoiMesh;
T_DisplayerVector MeshToFlatten_Displayer;
T_GeodesicMeshVector MeshFlattenned;
T_DisplayerVector MeshFlattenned_Displayer;
GW_U32 MeshToFlatten_Selected = 0;
GW_U32 MeshFlattenned_Selected = 0;

GW_GeodesicMesh* pSelectedMesh = &Mesh;
T_GeodesicMeshVector Meshes_ToDelete;
GW_Bool bDisplayBasePoints = GW_True;
GW_Bool bEnableTexture = GW_False;


GW_TopographicFunction TextureMapping;
#define TEXTURE_FILE_NAME	"../ressources/images/big-dots.jpg"


GW_U32 nNbrTexture = 0;
GW_U32 nTextureSeleted = 1;
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

void load_check_texture()
{
	nNbrTexture++;
#define checkImageWidth	 64
#define checkImageHeight 64
	GLubyte checkImage[checkImageWidth][checkImageHeight][3];
	int i, j, c;
	for (i = 0; i < checkImageWidth; i++) 
	for (j = 0; j < checkImageHeight; j++)
	{
		c = ((((i&0x8)==0)^((j&0x8))==0))*255;
		checkImage[i][j][0] = (GLubyte) c;
		checkImage[i][j][1] = (GLubyte) c;
		checkImage[i][j][2] = (GLubyte) c;
	}

	GLuint texture;
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth, 
		checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 
		&checkImage[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
		GL_NEAREST);
	// GL_DECAL, GL_MODULATE, or GL_BLEND,
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void texture_mesh( GW_GeodesicMesh& Mesh, GW_GeodesicMesh& MeshCood )
{
	GW_ASSERT( Mesh.GetNbrVertex()==MeshCood.GetNbrVertex() );
	GW_Vector3D min, max;
	MeshCood.GetBoundingBox( min, max );
	for( GW_U32 i=0; i<Mesh.GetNbrVertex(); ++i )
	{
		GW_GeodesicVertex& Vert = (GW_GeodesicVertex&) *Mesh.GetVertex(i);
		GW_Vector3D& coord = MeshCood.GetVertex(i)->GetPosition();
		GW_Float u = GW_SCALE_01( coord[0], min[0], max[0] );
		GW_Float v = GW_SCALE_01( coord[1], min[1], max[1] );
		Vert.SetTexCoords( u, v );
	}
}

void load_file()
{
	if( SelectedFile!=FileList.end() )
	{
		if( Toolkit.LoadFile( (*SelectedFile).c_str() )<0 )
			exit(-1);
	}
	/* TODO : remove this */
	GW_Float r = Mesh.GetBoundingRadius();
	for( GW_U32 i=0; i<Mesh.GetNbrVertex(); ++i )
	{
		GW_Vector3D pos = Mesh.GetVertex(i)->GetPosition()/r;
		Mesh.GetVertex(i)->SetTexCoords( 0.5 + pos[0]/(2.0*r), 0.5 + pos[1]/(2.0*r) );
	}

	Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
	Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kStoppingVertex );
	MeshToFlatten.push_back( &Mesh );
	MeshToFlatten_VoronoiMesh.push_back( &VoronoiMesh );
	MeshToFlatten_Displayer.push_back( &Toolkit.GetGeodesicDisplayer() );
}

GW_Float rCurvatureWeight = 0.1;
GW_Float rAvoid = 10;
GW_Float rStopAtEdge = 0;			// 80
GW_Bool bAvoidEdge = GW_False;
GW_Float CurvatureWeightCallback(GW_GeodesicVertex& Vert)
{
	return 1;

	/* curvature computation */
	GW_Float rCurv_Val = Vert.GetMaxCurv()*Vert.GetMaxCurv() + Vert.GetMinCurv()*Vert.GetMinCurv();
	GW_CLAMP( rCurv_Val, 0, 50 );
	//	GW_ASSERT( Vert.GetMaxAbsCurv()>=0 && Vert.GetMaxAbsCurv()<10000 );
	/* gradient computation */
	GW_Float rGrad_Val = TextureMapping.GetValue( Vert.GetTexCoordU(), 1-Vert.GetTexCoordV() );

#if 1
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
GW_GeodesicMesh::T_WeightCallbackFunction WeightCallback = BasicWeightCallback;

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
	/* redirect GW messages */
	GW_OutputStream = stdout;

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

	/* build texture */
	load_check_texture();
	load_texture("../ressources/images/scottish.jpg");
	load_texture("../ressources/images/scottish2.jpg");
	load_texture("../ressources/images/brick1.jpg");
	load_texture("../ressources/images/brick2.jpg");
	load_texture("../ressources/images/circle.jpg");
	load_texture("../ressources/images/artmodern.jpg");
	glBindTexture( GL_TEXTURE_2D, nTextureSeleted );
	glDisable(GL_TEXTURE_2D);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
		GL_NEAREST);

	if( GW_Toolkit::LoadFileList( FILE_LIST, FileList )<0 )
	{
		cerr << "Can't open files listing " << FILE_LIST << "." << endl;
		exit(-1);
	}
	SelectedFile = FileList.begin();

	/* load the current file */
	load_file();

	GW_Bool bInitRandomStartPoints = GW_False;

	if( bInitRandomStartPoints )
	{
		/* select some point at random */
		GW_U32 nNbrStartVertex = 45;
		GW_U32 StartList[10] = {5880, 18592, 5592, 5782, 7111, 19560, 19357, 14775, 7251, 15734};
#if 1
		GW_Float rMaxRadius = 5;
		GW_U32 nInitialChoice = (GW_U32) GW_RAND_RANGE(0, Mesh.GetNbrVertex()) ; // 7000
		GW_Vector3D Pos = Mesh.GetVertex( nInitialChoice )->GetPosition();

		for( GW_U32 i=0; i<nNbrStartVertex; ++i )
		{
			GW_GeodesicVertex* pStartVertex = NULL;
			GW_Float rCurMinDist = GW_INFINITE;
			GW_U32 nTry = 0;
			while( rCurMinDist>rMaxRadius && nTry<100 )
			{
				nTry++;
				GW_GeodesicVertex* pVert =  (GW_GeodesicVertex*) Mesh.GetRandomVertex();
				// GW_GeodesicVertex* pVert =  (GW_GeodesicVertex*) Mesh.GetVertex( StartList[i] );
				if( ~(Pos-pVert->GetPosition()) < rCurMinDist )
				{
					rCurMinDist = ~(Pos-pVert->GetPosition());
					pStartVertex = pVert;
				}
			}
			cout << pStartVertex->GetID() << "  ";
			VertexList.push_back( pStartVertex );
		}
		return;
#endif

		for( GW_U32 i=0; i<nNbrStartVertex; ++i )
		{
			GW_GeodesicVertex* pStartVertex;
			pStartVertex = (GW_GeodesicVertex*) Mesh.GetRandomVertex();
			GW_ASSERT( pStartVertex!=NULL );
			VertexList.push_back( pStartVertex );
		}
		cout << "Initialize the Voronoi diagram ... ";
//		GW_Parameterization::PerformFastMarching(  Mesh, VertexList );
		cout << "done.";
		Toolkit.GetGeodesicDisplayer().ResetFrontColor();
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );
	}
}

void display_base_points( GW_GeodesicMesh& CurMesh, T_GeodesicVertexList& VertList, GW_Vector3D& color )
{
	if( bDisplayBasePoints )
	{
		GW_Float rPointSize = 6.0f;
		glPointSize( (GLfloat) rPointSize );
		glColor( color );
		glDisable( GL_LIGHTING );
		glBegin( GL_POINTS );
		for( IT_GeodesicVertexList it = VertList.begin(); it!=VertList.end(); ++it )
		{
			GW_GeodesicVertex* pVert = *it;
			GW_U32 nID = pVert->GetID();
			GW_GeodesicVertex* pRealVert = (GW_GeodesicVertex*) CurMesh.GetVertex(nID);
			glVertex( pRealVert->GetPosition() );
		}
		glEnd();
		glEnable( GL_LIGHTING );
	}
}

void draw_scene( GW_Bool bWireFrame )
{
	glDisable( GL_CULL_FACE );

	if( DisplayedMesh==0 )		// displaying main mesh
	{
//		Toolkit.GetGeodesicDisplayer().BuildVertexArray( Mesh );
		display_base_points(Mesh, VertexList, GW_Vector3D(0,0,0));
		/* render mesh */
		if( bWireFrame )
		{
			Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
			glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth( nLineWidth );
			glDisable( GL_LIGHTING );
		}
		Toolkit.GetGeodesicDisplayer().DisplayMesh( Mesh );
		if( bWireFrame )
		{
			Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable( GL_LIGHTING );
		}
	}

	if( DisplayedMesh==1 || DisplayedMesh==2 )		// displaying mesh to flatten
	{
		T_GeodesicMeshVector* pSelectedList = &MeshToFlatten;
		if( DisplayedMesh==2 )
			pSelectedList = &MeshFlattenned;
		GW_U32 num = 0;
		for( IT_GeodesicMeshVector it = pSelectedList->begin(); it!=pSelectedList->end(); ++it )
		{
			GW_GeodesicMesh* pMesh = *it;
			if( pMesh!=NULL )
			{
				GW_GeodesicDisplayer* pSelectedDisplayer = NULL;
				if( DisplayedMesh==1 )
				{
					display_base_points(*pMesh, MeshToFlatten_VoronoiMesh[num]->GetBaseVertexList(), GW_Vector3D(0,0,0));
					pSelectedDisplayer = MeshToFlatten_Displayer[num];
				}
				else
				{
					if( MeshToFlatten_VoronoiMesh[num]!=NULL )
						display_base_points(*pMesh, MeshToFlatten_VoronoiMesh[num]->GetBaseVertexList(), GW_Vector3D(0,0,0));
					pSelectedDisplayer = MeshFlattenned_Displayer[num];
				}

				if( bWireFrame )
				{
					pSelectedDisplayer->EnableDraw( GW_BasicDisplayer::kForceMonoColor );
					glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glLineWidth( nLineWidth );
				}

				if( DisplayedMesh==2 && pMesh==pSelectedMesh )
					pSelectedDisplayer->DisplayMesh( *pMesh );

				if( DisplayedMesh==1 && pMesh!=pSelectedMesh )
				{
					pSelectedDisplayer->DisplayMesh( *pMesh );
				}
				else if( DisplayedMesh==1 )
				{
					/* display selected in a special fashion */
					pSelectedDisplayer->EnableDraw( GW_BasicDisplayer::kForceMonoColor );
					glDisable( GL_LIGHTING );
					glDisable(GL_TEXTURE_2D);
					if( !bWireFrame )
						glColor3f( 0, 0, 0.5 );
					pSelectedDisplayer->DisplayMesh( *pMesh );
					glEnable( GL_LIGHTING );
					if( bEnableTexture )
						glEnable(GL_TEXTURE_2D);
					pSelectedDisplayer->DisableDraw( GW_BasicDisplayer::kForceMonoColor );
				}

				if( bWireFrame )
				{
					pSelectedDisplayer->DisableDraw( GW_BasicDisplayer::kForceMonoColor );
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glEnable( GL_LIGHTING );
				}
			}
			num++;
		}
	}
}

void display()
{
	GW_InputOutput::PrepareDisplay();

	glPushMatrix();

	if( bWireFrameModeOn )
	{
		glDisable( GL_LIGHTING );
		glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth( nLineWidth );
		draw_scene( GW_True );
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_LIGHTING );
	}
	if( bFilledModeOn )
		draw_scene( GW_False );

	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void reset_geodesic_data()
{
	/* reset everything */
	Mesh.ResetGeodesicMesh();
	Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );

	for( GW_U32 i=0; i<MeshToFlatten_Displayer.size(); ++i )
	{
		GW_GeodesicDisplayer* pDisplayer = MeshToFlatten_Displayer[i];
		GW_GeodesicMesh* pMesh = MeshToFlatten[i];
		if( pMesh!=NULL && pDisplayer!=NULL )
		{
			pMesh->ResetGeodesicMesh();
			pDisplayer->BuildColorArray( *pMesh );
		}
	}

	for( GW_U32 i=0; i<MeshFlattenned_Displayer.size(); ++i )
	{
		GW_GeodesicDisplayer* pDisplayer = MeshFlattenned_Displayer[i];
		GW_GeodesicMesh* pMesh = MeshFlattenned[i];
		if( pMesh!=NULL && pDisplayer!=NULL )
		{
			pMesh->ResetGeodesicMesh();
			pDisplayer->BuildColorArray( *pMesh );
		}
	}
}

void toggle_light()
{
	/* reset everything */
	Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kLighting );

	for( GW_U32 i=0; i<MeshToFlatten_Displayer.size(); ++i )
	{
		GW_GeodesicDisplayer* pDisplayer = MeshToFlatten_Displayer[i];
		if( pDisplayer!=NULL )
			pDisplayer->ToggleDraw( GW_BasicDisplayer::kLighting );
	}

	for( GW_U32 i=0; i<MeshFlattenned_Displayer.size(); ++i )
	{
		GW_GeodesicDisplayer* pDisplayer = MeshFlattenned_Displayer[i];
		if( pDisplayer!=NULL )
			pDisplayer->ToggleDraw( GW_BasicDisplayer::kLighting );
	}
}

void modify_texture_coord( GW_Float rTextureScale )
{
	IT_DisplayerVector it_disp = MeshToFlatten_Displayer.begin();
	for( IT_GeodesicMeshVector it=MeshToFlatten.begin(); it!=MeshToFlatten.end(); ++it )
	{
		GW_GeodesicMesh* pMesh = *it;
		GW_GeodesicDisplayer* pDisp = *it_disp;
		for( GW_U32 i=0; i<pMesh->GetNbrVertex(); ++i )
		{
			GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) pMesh->GetVertex(i);
			pVert->SetTexCoordU( rTextureScale*pVert->GetTexCoordU() );
			pVert->SetTexCoordV( rTextureScale*pVert->GetTexCoordV() );
		}
		pDisp->BuildVertexArray( *pMesh );
		it_disp++;
	}
}

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
	GW_Float rTextureScale = 1.1;

	GW_GeodesicDisplayer* pSelectedDisplayer = &Toolkit.GetGeodesicDisplayer();
	if( DisplayedMesh==1 )
		pSelectedDisplayer = MeshToFlatten_Displayer[MeshToFlatten_Selected];
	if( DisplayedMesh==2 )
		pSelectedDisplayer = MeshFlattenned_Displayer[MeshFlattenned_Selected];
	if( pSelectedDisplayer==NULL )
		pSelectedDisplayer = &Toolkit.GetGeodesicDisplayer();

	switch((char) button)
	{
	case 27:
		/* delete newly created mesh */
		for( IT_GeodesicMeshVector it = Meshes_ToDelete.begin(); it!=Meshes_ToDelete.end(); ++it )
			GW_DELETE( *it );
		/* delete created list */
		for( IT_VoronoiMeshVector it = MeshToFlatten_VoronoiMesh.begin(); it!=MeshToFlatten_VoronoiMesh.end(); ++it )
		{
			if( *it!=&VoronoiMesh )
			GW_DELETE( *it );
		}
		for( IT_DisplayerVector it = MeshToFlatten_Displayer.begin(); it!=MeshToFlatten_Displayer.end(); ++it )
		{
			if( *it!=&Toolkit.GetGeodesicDisplayer() )
				GW_DELETE( *it );
		}
		for( IT_DisplayerVector it = MeshFlattenned_Displayer.begin(); it!=MeshFlattenned_Displayer.end(); ++it )
			GW_DELETE( *it );
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
	case 'r':
		reset_geodesic_data();
		break;
	case '\t':
		{
			if( DisplayedMesh==0 )	// displaying mesh to flatten
			{
				Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kBoundaries );
				cout << "Now displaying mesh to flatten." << endl;
				DisplayedMesh = 1;
				MeshToFlatten_Selected = 0;
				pSelectedMesh = MeshToFlatten[0];
			}
			else if( DisplayedMesh==1 && MeshFlattenned.size()==0 || DisplayedMesh==2 )
			{
				Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kBoundaries );
				cout << "Now displaying original mesh." << endl;
				DisplayedMesh = 0;
				pSelectedMesh = &Mesh;
			}
			else if( DisplayedMesh==1 && MeshFlattenned.size()!=0 )
			{
				Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kBoundaries );
				cout << "Now displaying flattened mesh." << endl;
				DisplayedMesh = 2;
				MeshFlattenned_Selected = 0;
				pSelectedMesh = MeshFlattenned[0];
			}
			
		}
		break;
	case '+':
		{
			if( DisplayedMesh==1 )	// displaying mesh to flatten
			{
				MeshToFlatten_Selected++;
				if( MeshToFlatten_Selected>=MeshToFlatten.size() )
					MeshToFlatten_Selected = 0;
				pSelectedMesh = MeshToFlatten[MeshToFlatten_Selected];
				/* print some information about the mesh */
				GW_Float rPerimeter, rArea;
				GW_U32 nNbrBoundaries;
				GW_Mesh& Mesh = *MeshToFlatten[MeshToFlatten_Selected];
				rArea = Mesh.GetArea();
				rPerimeter = Mesh.GetPerimeter( &nNbrBoundaries );
				GW_Float rRatio = 4*GW_PI*rArea/(rPerimeter*rPerimeter);
				cout << "For Information : Nbr.Boundaries=" << nNbrBoundaries << ",  Isoperimetric distorition=" << rRatio << "." << endl;
				if( nNbrBoundaries>1 )
					GW_OutputComment("More than 1 boundary : you should subdivide the mesh using 'q'.");
				if( rRatio>2 )
					GW_OutputComment("Hughe isoperimetric distortion : you should subdivide the mesh using 'q'.");
			}
			if( DisplayedMesh==2 )	// displaying mesh to flatten
			{
				MeshFlattenned_Selected++;
				if( MeshFlattenned_Selected>=MeshFlattenned.size() )
					MeshFlattenned_Selected = 0;
				pSelectedMesh = MeshFlattenned[MeshFlattenned_Selected];
			}
		}
		break;
	case '-':
		{
			if( DisplayedMesh==1 )	// displaying mesh to flatten
			{
				if( MeshToFlatten_Selected==0 )
					MeshToFlatten_Selected = ((GW_U32) MeshToFlatten.size())-1;
				else
					MeshToFlatten_Selected--;
				pSelectedMesh = MeshToFlatten[MeshToFlatten_Selected];
			}
			if( DisplayedMesh==2 )	// displaying mesh to flatten
			{
				if( MeshFlattenned_Selected==0 )
					MeshFlattenned_Selected = ((GW_U32) MeshFlattenned.size())-1;
				else
					MeshFlattenned_Selected--;
				pSelectedMesh = MeshFlattenned[MeshFlattenned_Selected];
			}
		}
		break;
	case 'f':
		Toolkit.GetGeodesicDisplayer().ToggleDraw(GW_BasicDisplayer::kUseFlatLighting);
		// Toolkit.GetCoarseDisplayer().ToggleDraw(GW_BasicDisplayer::kUseFlatLighting);
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kUseFlatLighting) )
			cout << "Using flat lighting." << endl;
		else
			cout << "Not using flat lighting." << endl;
		break;
	case 's':
		cout << "Saving saved camera settings ... done." << endl;
		GW_InputOutput::SaveCameraSettings();
		break;
	case 'l':
		cout << "Loading saved camera settings ... done." << endl;
		GW_InputOutput::LoadCameraSettings();
		break;
	case 'a':
		ilutGLScreenie();
		break;
	case 'e':
		{
			cout << "Saving current selected mesh, enter name : " << endl;
			string s;
			std::getline(std::cin, s);
			string path = string("../ressources/off/") + s + string(".off");
			GW_OFFLoader::Save( *pSelectedMesh, path.c_str() );
		}
		break;
	case 'y':
		nTextureSeleted++;
		if( nTextureSeleted>nNbrTexture  )
			nTextureSeleted=1;
		glBindTexture( GL_TEXTURE_2D, nTextureSeleted );
		cout << "Changing of texture." << endl;
		break;
	case 'T':
		modify_texture_coord(rTextureScale);
		break;
	case 't':
		modify_texture_coord(1/rTextureScale);
		break;
	case 'u':
		for( GW_U32 i=0; i<pSelectedMesh->GetNbrVertex(); ++i )
		{
			GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) pSelectedMesh->GetVertex(i);
			pVert->SetTexCoordU( rTextureScale*pVert->GetTexCoordU() );
			pVert->SetTexCoordV( rTextureScale*pVert->GetTexCoordV() );
		}
		pSelectedDisplayer->BuildVertexArray( *pSelectedMesh );
		break;
	case 'U':
		for( GW_U32 i=0; i<pSelectedMesh->GetNbrVertex(); ++i )
		{
			GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) pSelectedMesh->GetVertex(i);
			pVert->SetTexCoordU( 1/rTextureScale*pVert->GetTexCoordU() );
			pVert->SetTexCoordV( 1/rTextureScale*pVert->GetTexCoordV() );
		}
		pSelectedDisplayer->BuildVertexArray( *pSelectedMesh );
		break;
	case 'q':
		{
			cout << "Subdividing selected region ... " << endl;
			GW_GeodesicMesh* pMesh = MeshToFlatten[MeshToFlatten_Selected];
			GW_ASSERT( pMesh!=NULL );
			GW_Parameterization::SplitMesh( *pMesh );
			MeshToFlatten_Displayer[MeshToFlatten_Selected]->BuildVertexArray(*pMesh);
			cout << "done." << endl;
#if 0
			GW_GeodesicMesh* pNewMesh1 = NULL, *pNewMesh2 = NULL;
			/* add the new meshes */
			if( pNewMesh1!=NULL )
			{
				MeshToFlatten[MeshToFlatten_Selected] = pNewMesh1;
				MeshToFlatten_Displayer[MeshToFlatten_Selected]->BuildVertexArray( *pNewMesh1 );
				Meshes_ToDelete.push_back( pNewMesh1 );
			}
			if( pNewMesh2!=NULL )
			{
				MeshToFlatten.push_back( pNewMesh2 );
				MeshToFlatten_VoronoiMesh.push_back(new GW_VoronoiMesh);
				GW_GeodesicDisplayer* pNewDisplayer = new GW_GeodesicDisplayer;
				MeshToFlatten_Displayer.push_back(pNewDisplayer);
				pNewDisplayer->BuildVertexArray( *pNewMesh2 );
				pNewDisplayer->EnableDraw( GW_BasicDisplayer::kGeodesicDistance );
				pNewDisplayer->EnableDraw( GW_BasicDisplayer::kLighting );
				pNewDisplayer->EnableDraw( GW_BasicDisplayer::kBoundaries );
				Meshes_ToDelete.push_back( pNewMesh2 );
			}
			if( pSelectedMesh==pMesh && pNewMesh1!=NULL )
				pSelectedMesh=pNewMesh1;
#endif			
		}
	case 'b':
		if( bDisplayBasePoints )
			cout << "Not displaying base points." << endl;
		else
			cout << "Displaying base points." << endl;
		bDisplayBasePoints = !bDisplayBasePoints;
		break;
	case 'd':
		if( bEnableTexture )
		{
			cout << "Not using texture.";
			bEnableTexture = GW_False;
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			cout << "Using texture.";
			bEnableTexture = GW_True;
			glEnable(GL_TEXTURE_2D);
		}
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
	GW_Float rDeltaMove = 0.1;

	GW_Float rRepulsiveWeight = 0.0;
	GW_Float rAtractiveWeight = 0.0;
	if( DisplayedMesh==0 )
	{
		rRepulsiveWeight = 0*0.1;
		rAtractiveWeight = 0*2;
	}

	GW_Bool bUseRandomStartPoint = GW_False;
	GW_Bool bAssignColor = GW_False;
	GW_Bool bFillHole = GW_False;

	T_GeodesicVertexList* pSelectedVertexList = &VertexList;
	if( DisplayedMesh==1 )
		pSelectedVertexList = &MeshToFlatten_VoronoiMesh[MeshToFlatten_Selected]->GetBaseVertexList();
	GW_GeodesicDisplayer* pSelectedDisplayer = &Toolkit.GetGeodesicDisplayer();
	if( DisplayedMesh==1 )
		pSelectedDisplayer = MeshToFlatten_Displayer[MeshToFlatten_Selected];
	if( DisplayedMesh==2 )
		pSelectedDisplayer = MeshFlattenned_Displayer[MeshFlattenned_Selected];
	if( pSelectedDisplayer==NULL )
		pSelectedDisplayer = &Toolkit.GetGeodesicDisplayer();

	switch(key)
	{
	case GLUT_KEY_F1:
		rCurvatureWeight = rRepulsiveWeight;
		bAvoidEdge = GW_True;
		pSelectedMesh->RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add one furthest point ";
		GW_VoronoiMesh::AddFurthestPointsIterate( *pSelectedVertexList, *pSelectedMesh, 1, bUseRandomStartPoint );
		pSelectedDisplayer->SetUpDraw( *pSelectedMesh );
		break;
	case GLUT_KEY_F2:
		rCurvatureWeight = rRepulsiveWeight;
		bAvoidEdge = GW_True;
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 10 furthest points  ";
		GW_VoronoiMesh::AddFurthestPointsIterate( *pSelectedVertexList, *pSelectedMesh, 10, bUseRandomStartPoint);
		pSelectedDisplayer->SetUpDraw( *pSelectedMesh );
		break;
	case GLUT_KEY_F11:
		rCurvatureWeight = rRepulsiveWeight;
		bAvoidEdge = GW_True;
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 100 furthest points ";
		GW_VoronoiMesh::AddFurthestPointsIterate( *pSelectedVertexList, *pSelectedMesh, 100, bUseRandomStartPoint );
		pSelectedDisplayer->SetUpDraw( *pSelectedMesh );
		break;
	case GLUT_KEY_F3:
		rCurvatureWeight = rAtractiveWeight;
		bAvoidEdge = GW_False;
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
		cout << "Performing 1 Lloyd iteration algorithm ... " << endl;
		Parameterization_.PerformPseudoLloydIteration( Mesh, VertexList );
		cout << "done." << endl;
		break;
	case GLUT_KEY_F5:
		{
			rCurvatureWeight = rAtractiveWeight;
			bAvoidEdge = GW_False;
			Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
			cout << "Segmenting all regions  ... " << endl;
			Parameterization_.SegmentAllRegions( Mesh, VertexList );
			cout << "done." << endl;
			Toolkit.GetGeodesicDisplayer().BuildVertexArray( Mesh );
			Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kBoundaries );
			/* extracting the meshes */
			cout << "Extracting sub-meshes ... ";
			T_GeodesicMeshVector NewMeshes;
			GW_Parameterization::ExtractSubMeshes( *pSelectedMesh, *pSelectedVertexList, NewMeshes );
			MeshToFlatten.clear();
			MeshToFlatten_VoronoiMesh.clear();
			MeshToFlatten_Displayer.clear();
			for( IT_GeodesicMeshVector it=NewMeshes.begin(); it!=NewMeshes.end(); ++it )
			{
				GW_GeodesicMesh* pMesh = *it;
				MeshToFlatten.push_back(pMesh);
				MeshToFlatten_VoronoiMesh.push_back(new GW_VoronoiMesh);
				Meshes_ToDelete.push_back(pMesh);
				GW_GeodesicDisplayer* pNewDisplayer = new GW_GeodesicDisplayer;
				MeshToFlatten_Displayer.push_back(pNewDisplayer);
				pNewDisplayer->BuildVertexArray( *pMesh );
				pNewDisplayer->EnableDraw( GW_BasicDisplayer::kGeodesicDistance );
				pNewDisplayer->EnableDraw( GW_BasicDisplayer::kLighting );
				pNewDisplayer->EnableDraw( GW_BasicDisplayer::kBoundaries );
				pNewDisplayer->SetUpDraw( *pMesh );
				pMesh->CheckIntegrity();
			}
			cout << "done." << endl;
		}
		break;
	case GLUT_KEY_F6:
		{
			GW_U32 nNbrPoints = 30;
			cout << "Distributing points on each mesh ... " << endl;
			IT_VoronoiMeshVector it_voronoi = MeshToFlatten_VoronoiMesh.begin();
			for( IT_GeodesicMeshVector it=MeshToFlatten.begin(); it!=MeshToFlatten.end(); ++it )
			{
				GW_GeodesicMesh* pMesh = *it;
				GW_VoronoiMesh* pVoronoiMesh = *it_voronoi;
				pSelectedMesh->RegisterWeightCallbackFunction( BasicWeightCallback );
				cout << "Add furthest points ";
				GW_VoronoiMesh::AddFurthestPointsIterate( pVoronoiMesh->GetBaseVertexList(), *pMesh, nNbrPoints, bUseRandomStartPoint );
				it_voronoi++;
			}
			reset_geodesic_data();
			cout << "done." << endl;
		}
		break;
	case GLUT_KEY_F7:
		{
			Mesh.RegisterWeightCallbackFunction( WeightCallback );
			cout << "Flattening each possible mesh ... " << endl;
			/* flatten each base mesh */
			IT_VoronoiMeshVector it_voronoi = MeshToFlatten_VoronoiMesh.begin();
			for( IT_GeodesicMeshVector it=MeshToFlatten.begin(); it!=MeshToFlatten.end(); ++it )
			{
				GW_GeodesicMesh* pMesh = *it;
				GW_VoronoiMesh* pVoronoiMesh = *it_voronoi;
				T_GeodesicVertexList* pVertList = &pVoronoiMesh->GetBaseVertexList();
				if( pVertList->size()!=0 )
				{
					/* the newly flattenened mesh */
					GW_GeodesicMesh& NewMesh = *(new GW_GeodesicMesh);
					NewMesh = *pMesh;

#if 1
					/* add the mesh to the list */
					MeshFlattenned.push_back(&NewMesh);
					Meshes_ToDelete.push_back(&NewMesh);
					/* flattening */
					// GW_Parameterization::T_ParameterizationType ParamType = GW_Parameterization::kGeodesicConformal;
					GW_Parameterization::T_ParameterizationType ParamType = GW_Parameterization::kGeodesicIsomap;
					GW_Parameterization::T_ResolutionType ResolType = GW_Parameterization::kSpectral;
					if( ParamType!=GW_Parameterization::kGeodesicIsomap )
					{
						GW_OutputComment( "Computing the Voronoi Mesh." );
						pVoronoiMesh->BuildMesh( *pMesh, GW_False );
					}
					GW_OutputComment( "Flattening the mesh." );
					Parameterization_.ParameterizeMesh( *pMesh, *pVoronoiMesh, NewMesh, ParamType, ResolType );
					//	NewMesh.BuildRawNormal();
					GW_GeodesicDisplayer* pNewDisplayer = new GW_GeodesicDisplayer;
					MeshFlattenned_Displayer.push_back(pNewDisplayer);
					pNewDisplayer->BuildVertexArray( NewMesh );
					pNewDisplayer->EnableDraw( GW_BasicDisplayer::kGeodesicDistance );
					pNewDisplayer->EnableDraw( GW_BasicDisplayer::kLighting );
					pNewDisplayer->SetUpDraw( NewMesh );
#else
					/** flatten also the main mesh */
					GW_U32 n = pMesh->GetNbrVertex();
					GW_SparseMatrix K(n);
					GW_OutputComment("Building the conformal matrix.");
					GW_Parameterization::BuildConformalMatrix(*pMesh, K);
					GW_MatrixNxP L(2,n,0.0);
					GW_OutputComment("Solving the boundary free problem.");
					GW_Parameterization::ResolutionBoundaryFixed( *pMesh, K, L );
					for( GW_U32 i=0; i<n; ++i )
					{
						GW_Vertex* pVert = pMesh->GetVertex(i);
						pVert->SetPosition( GW_Vector3D( L.GetData(0,i), L.GetData(1,i), 0 ) );
					}
					MeshToFlatten_Displayer[MeshToFlatten_Selected]->BuildVertexArray( *pMesh );
#endif
				}
				else
				{
					MeshFlattenned.push_back(NULL);
					MeshFlattenned_Displayer.push_back(NULL);
				}
				it_voronoi++;
			}
			cout << "done." << endl;
		}
		break;
	case GLUT_KEY_F8:
		{
			cout << "Texturing each Mesh ... ";
			/* flatten each base mesh */
			for( GW_U32 i=0; i<GW_MIN(MeshToFlatten.size(), MeshFlattenned.size()); ++i )
			{
				GW_GeodesicMesh* pMeshToFlatten = MeshToFlatten[i];
				GW_GeodesicMesh* pMeshFlattened = MeshFlattenned[i];
				if( pMeshToFlatten!=NULL && pMeshFlattened!=NULL )
				{
					texture_mesh( *pMeshToFlatten, *pMeshFlattened );
					texture_mesh( *pMeshFlattened, *pMeshFlattened );
				}
				MeshToFlatten_Displayer[i]->BuildVertexArray(*pMeshToFlatten);
				MeshFlattenned_Displayer[i]->BuildVertexArray(*pMeshFlattened);
			}
			bEnableTexture = GW_True;
			glEnable(GL_TEXTURE_2D);
			cout << "done." << endl;
		}
		break;
	case GLUT_KEY_F9:
		toggle_light();
		cout << "Turning Lighting ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kLighting ) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
		break;
	case GLUT_KEY_LEFT:
		GW_InputOutput::MoveTarget( -rDeltaMove, 0 );
		break;
	case GLUT_KEY_RIGHT:
		GW_InputOutput::MoveTarget( rDeltaMove, 0 );
		break;
	case GLUT_KEY_DOWN:
		GW_InputOutput::MoveTarget( 0, -rDeltaMove );
		break;
	case GLUT_KEY_UP:
		GW_InputOutput::MoveTarget( 0, rDeltaMove );
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

	GW_InputOutput::Init(argc, argv, WINDOW_SIZE, "GW -- Test of mesh parameterization");

	srand( (unsigned)time( NULL ) );

	cout << endl << "    GW -- Test of mesh parameterization" << endl << endl;
	cout << "---" << endl;
	cout << "Use 'Left Click + Mouse' to spin the sphere." << endl;
	cout << "Use 'Right Click' to pop-up menu." << endl;
	cout << "Use 'Right+Left Click + mouse up/down' to zoom in/out." << endl;
	cout << "---" << endl;
	cout << "F1:  Add 1 furthest point to coarse mesh." << endl;
	cout << "F2:  Add 10 furthest points to coarse mesh." << endl;
	cout << "F3:  Build coarse mesh." << endl;
	cout << "F4:  Build geodesic boundaries." << endl;
	cout << "F5:  Compute parametrization." << endl;
	cout << "F6:  Perform a local fast marching." << endl;
	cout << "F8:  Turn Lighting ON/OFF." << endl;
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