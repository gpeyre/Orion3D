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
#include "../../gw_geodesic/GW_GeometryAtlas.h"
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
#else
	#pragma comment(lib, "glut32.lib")
	#pragma comment(lib, "DevIL.lib")
	#pragma comment(lib, "ilu.lib")
	#pragma comment(lib, "ilut.lib")
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_toolkit.lib")
	#pragma comment(lib, "gw_geodesic.lib")
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

GW_Bool bEdgeRepulsive = GW_True;
GW_Float rCurvatureWeight = 0.1;

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

GW_GeometryAtlas GeometryAtlas;
GW_U32 nGeometryAtlasSampling = 15;

GW_GeodesicMesh* pSelectedMesh = &Mesh;
T_GeodesicMeshVector Meshes_ToDelete;
GW_Bool bDisplayBasePoints = GW_True;



void load_file()
{
	if( SelectedFile!=FileList.end() )
	{
		if( Toolkit.LoadFile( (*SelectedFile).c_str() )<0 )
			exit(-1);
	}
	Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
	Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kStoppingVertex );
	MeshToFlatten.push_back( &Mesh );
	MeshToFlatten_VoronoiMesh.push_back( &VoronoiMesh );
	MeshToFlatten_Displayer.push_back( &Toolkit.GetGeodesicDisplayer() );
}

GW_Float CurvatureWeightCallback(GW_GeodesicVertex& Vert)
{
	GW_Float rTotalCurv = Vert.GetMaxCurv()*Vert.GetMaxCurv() + Vert.GetMinCurv()*Vert.GetMinCurv();
	GW_CLAMP( rTotalCurv, 0, 10 );
	if( !bEdgeRepulsive )
		return 0.5+rTotalCurv*rCurvatureWeight;
	else
		return 1/(0.5+rTotalCurv*rCurvatureWeight);
	return 1;
}
GW_Float BasicWeightCallback(GW_GeodesicVertex& Vert)
{
	return 1;
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
		}
		Toolkit.GetGeodesicDisplayer().DisplayMesh( Mesh );
		if( bWireFrame )
		{
			Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	if( DisplayedMesh==3 )							// displaying geometry atlas
	{
		GW_Float rColor = 0.8f;
		GW_Vector3D Color(rColor, rColor, rColor);;
		glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
		glEnable( GL_COLOR_MATERIAL );
		/* render mesh */
		if( bWireFrame )
		{
			// glEnable( GL_CULL_FACE );
			// glDisable(GL_LIGHTING);
			glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth( nLineWidth );
			rColor = WIREFRAME_COLOR;
			Color = GW_Vector3D(rColor, rColor, rColor);
		}
		else
			glColor( Color );
		T_GeometryCellVector& CellGroup = GeometryAtlas.GetCellGroupVector().front();
#if 1
		GW_Toolkit::Display(GeometryAtlas, 2, 5, GW_Vector3D(0,0,0), GW_Vector3D(1,0,0), Color );
#else
		for( IT_GeometryCellVector it = CellGroup.begin(); it!=CellGroup.end(); ++it )
			GW_Toolkit::Display(*(*it));
#endif
		if( bWireFrame )
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
					if( !bWireFrame )
						glColor3f( 0, 0, 0.5 );
					pSelectedDisplayer->DisplayMesh( *pMesh );
					glEnable( GL_LIGHTING );
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



typedef std::vector<T_TrissectorInfoMap> T_TrissectorMapVector;
typedef T_TrissectorMapVector::iterator IT_TrissectorMapVector;

GW_U32 nNumLocalFrontSeleted = 0;
T_TrissectorInfoMap GlobalTrissectorInfoMap;
T_TrissectorMapVector TrissectorMapVector;
T_U32Vector Global2LocalID;		// to perform conversion from global ID to each sub-mesh ID
std::vector<T_TrissectorInfoVector> CyclicPositionVector;	// the 2D position of each trissector


void set_up_cellsgeometry(GW_Bool bSmooth)
{
	GeometryAtlas.InitSampling( CyclicPositionVector, nGeometryAtlasSampling );
	T_MeshVector ParamMeshVector, RealMeshVector;
	for( IT_GeodesicMeshVector it = MeshFlattenned.begin(); it!=MeshFlattenned.end(); ++it )
		ParamMeshVector.push_back(*it);
	for( IT_GeodesicMeshVector it = MeshToFlatten.begin(); it!=MeshToFlatten.end(); ++it )
		RealMeshVector.push_back(*it);

	if( bSmooth )
	{
		cout << "Smoothing the sampling ... ";
		GeometryAtlas.SmoothSampling(50);
		cout << "done." << endl;
	}

	cout << "Positionate the vertices ... ";
	GeometryAtlas.PositionateVertex( ParamMeshVector, RealMeshVector );
	cout << "done." << endl;
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
			else if( DisplayedMesh==1 && MeshFlattenned.size()==0 || DisplayedMesh==3 )
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
			else if( DisplayedMesh==2 )
			{
				Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kBoundaries );
				cout << "Now displaying geometry atlas." << endl;
				DisplayedMesh = 3;
				pSelectedMesh = &Mesh;
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
	case 'e':
		{
			cout << "Saving current selected mesh, enter name : " << endl;
			string s;
			std::getline(std::cin, s);
			string path = string("../ressources/off/") + s + string(".off");
			GW_GeodesicMesh* pMeshToSave = MeshToFlatten[MeshToFlatten_Selected];
			if( pMeshToSave!=NULL )
				GW_OFFLoader::Save( *pMeshToSave, path.c_str() );
			string pathf = string("../ressources/off/") + s + string("_flattened.off");
			pMeshToSave = MeshFlattenned[MeshToFlatten_Selected];
			if( pMeshToSave!=NULL )
				GW_OFFLoader::Save( *pMeshToSave, pathf.c_str() );
		}
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
	case 'U':
		nGeometryAtlasSampling += 3;
		set_up_cellsgeometry(GW_False);
		break;
	case 'u':
		nGeometryAtlasSampling -= 3;
		if( nGeometryAtlasSampling<2 )
			nGeometryAtlasSampling = 2;
		set_up_cellsgeometry(GW_False);
		break;
	case 'b':
		if( bDisplayBasePoints )
			cout << "Not displaying base points." << endl;
		else
			cout << "Displaying base points." << endl;
		bDisplayBasePoints = !bDisplayBasePoints;
		break;
	default:
		cout << "GW is SO COOL !" << endl;
	}
}


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
		bEdgeRepulsive = GW_True;
		pSelectedMesh->RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add one furthest point ";
		GW_VoronoiMesh::AddFurthestPointsIterate( *pSelectedVertexList, *pSelectedMesh, 1, bUseRandomStartPoint );
		pSelectedDisplayer->SetUpDraw( *pSelectedMesh );
		break;
	case GLUT_KEY_F2:
		rCurvatureWeight = rRepulsiveWeight;
		bEdgeRepulsive = GW_True;
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 10 furthest points  ";
		GW_VoronoiMesh::AddFurthestPointsIterate( *pSelectedVertexList, *pSelectedMesh, 10, bUseRandomStartPoint);
		pSelectedDisplayer->SetUpDraw( *pSelectedMesh );
		break;
	case GLUT_KEY_F11:
		rCurvatureWeight = rRepulsiveWeight;
		bEdgeRepulsive = GW_True;
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 100 furthest points ";
		GW_VoronoiMesh::AddFurthestPointsIterate( *pSelectedVertexList, *pSelectedMesh, 100, bUseRandomStartPoint );
		pSelectedDisplayer->SetUpDraw( *pSelectedMesh );
		break;
	case GLUT_KEY_F3:
		rCurvatureWeight = rAtractiveWeight;
		bEdgeRepulsive = GW_False;
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
		cout << "Performing 1 Lloyd iteration algorithm ... " << endl;
		Parameterization_.PerformPseudoLloydIteration( Mesh, VertexList );
		cout << "done." << endl;
		break;
	case GLUT_KEY_F5:
		{
			/* segmenting regions ****************************************************************/
			rCurvatureWeight = rAtractiveWeight;
			bEdgeRepulsive = GW_False;
			Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
			cout << "Segmenting all regions  ... " << endl;
			Parameterization_.SegmentAllRegions( Mesh, VertexList, &GlobalTrissectorInfoMap );
			cout << "done." << endl;
			Toolkit.GetGeodesicDisplayer().BuildVertexArray( Mesh );
			Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kBoundaries );
			/* extracting the meshes **************************************************************/
			cout << "Extracting sub-meshes ... ";
			T_GeodesicMeshVector NewMeshes;
			GW_Parameterization::ExtractSubMeshes( *pSelectedMesh, *pSelectedVertexList, NewMeshes, &Global2LocalID );
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
			/* set up the trissector info *************************************************************/
			GW_U32 nNbrRegion = (GW_U32) VertexList.size();
			TrissectorMapVector.resize( nNbrRegion );
			for( IT_TrissectorInfoMap it = GlobalTrissectorInfoMap.begin(); it!=GlobalTrissectorInfoMap.end(); ++it )
			{
				GW_TrissectorInfo& tr = it->second;
				GW_U32 region_num = tr.GetInterior();
				GW_ASSERT( region_num<nNbrRegion );
				T_TrissectorInfoMap& tr_map = TrissectorMapVector[region_num];
                GW_U32 nGlobalID = it->first;
				GW_ASSERT( nGlobalID < Global2LocalID.size() );
				GW_U32 nLocalID = Global2LocalID[nGlobalID];
				tr_map[nLocalID] = tr;
			}
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
			Mesh.RegisterWeightCallbackFunction( BasicWeightCallback );
			cout << "Flattening each possible mesh ... " << endl;

			CyclicPositionVector.resize( MeshToFlatten.size() );
			/* flatten each base mesh */
			IT_VoronoiMeshVector it_voronoi = MeshToFlatten_VoronoiMesh.begin();
			std::vector<T_TrissectorInfoVector>::iterator it_cyclicpos = CyclicPositionVector.begin();
			IT_TrissectorMapVector it_trissectorinfomap = TrissectorMapVector.begin();
			int num = 0;
			for( IT_GeodesicMeshVector it=MeshToFlatten.begin(); it!=MeshToFlatten.end(); ++it, ++num )
			{
				GW_GeodesicMesh* pMesh = *it;
				GW_VoronoiMesh* pVoronoiMesh = *it_voronoi;
				T_GeodesicVertexList* pVertList = &pVoronoiMesh->GetBaseVertexList();
				T_TrissectorInfoVector& CyclicPosition = *it_cyclicpos;
				T_TrissectorInfoMap& TrissectorInfoMap = *it_trissectorinfomap;

				/* the newly flattenened mesh */
				GW_GeodesicMesh& NewMesh = *(new GW_GeodesicMesh);
				NewMesh = *pMesh;

				/* add the mesh to the list */
				MeshFlattenned.push_back(&NewMesh);
				Meshes_ToDelete.push_back(&NewMesh);

				/** flatten the mesh */
				if( num==MeshToFlatten_Selected )	// only selected
				{
					GW_U32 n = pMesh->GetNbrVertex();
					GW_SparseMatrix K(n);
					GW_OutputComment("Building the conformal matrix.");
					GW_Parameterization::BuildConformalMatrix(*pMesh, K);
					GW_MatrixNxP L(2,n,0.0);
					GW_OutputComment("Solving the boundary free problem.");
					GW_Parameterization::ResolutionBoundaryFixed( *pMesh, K, L, NULL, &TrissectorInfoMap, &CyclicPosition );
					for( GW_U32 i=0; i<n; ++i )
					{
						GW_Vertex* pVert = NewMesh.GetVertex(i);
						pVert->SetPosition( GW_Vector3D( L.GetData(0,i), L.GetData(1,i), 0 ) );
					}
				}				

				/* create new displayer and stuff */
				//	NewMesh.BuildRawNormal();
				GW_GeodesicDisplayer* pNewDisplayer = new GW_GeodesicDisplayer;
				MeshFlattenned_Displayer.push_back(pNewDisplayer);
				pNewDisplayer->BuildVertexArray( NewMesh );
				pNewDisplayer->EnableDraw( GW_BasicDisplayer::kGeodesicDistance );
				pNewDisplayer->EnableDraw( GW_BasicDisplayer::kLighting );
				pNewDisplayer->SetUpDraw( NewMesh );
	
				it_voronoi++;
				it_cyclicpos++;
				it_trissectorinfomap++;

			}
			cout << "done." << endl;
			/** build geometry atlas */
			set_up_cellsgeometry(GW_False);
		}
		break;
	case GLUT_KEY_F8:
		set_up_cellsgeometry(GW_True);
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