//-------------------------------------------------------------------------
/** \name GW file inclusion */
//-------------------------------------------------------------------------
//@{
#include "stdafx.h"
#include <GL/glut.h>
#include <il/il.h>
#include <il/ilut.h>
#include "../../gw_toolkit/GW_Toolkit.h"
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
	#pragma comment(lib, "gw_core_dbg.lib")
	#pragma comment(lib, "gw_toolkit_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit_dbg.lib")
	#pragma comment(lib, "gw_multiresolution_dbg.lib")
	#pragma comment(lib, "gw_geodesic_dbg.lib")
#else
	#pragma comment(lib, "gw_core.lib")
	#pragma comment(lib, "gw_toolkit.lib")
	#pragma comment(lib, "gw_multiresolution_toolkit.lib")
	#pragma comment(lib, "gw_multiresolution.lib")
	#pragma comment(lib, "gw_geodesic.lib")
#endif // GW_DEBUG
//@}


/** for the interface */
GLfloat nLineWidth = 1;

GW_Toolkit Toolkit;
GW_Toolkit ToolkitFlattened;
GW_Bool bDisplayMesh = GW_True;
GW_Bool bDisplayFlattenedMesh = GW_False;

/** wire frame/filled mode */
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

/** The color of each voronoi vertex */
std::map<GW_U32, GW_Vector3D> VertexColorMap;
/** an image to texture the model */
GW_TopographicFunction Texture;
GLuint TextureID = 0;	// OpenGL Id for the texture.
#define TEXTURE_FILE_NAME "../ressources/images/chess.bmp"


GW_Float rCurvatureWeight = 0;

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
		if( ToolkitFlattened.LoadFile( (*SelectedFile).c_str() )<0 )
			exit(-1);
	}
	Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
	Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kStoppingVertex );
}

GW_Float CurvatureWeightCallback(GW_GeodesicVertex& Vert)
{
//	GW_ASSERT( Vert.GetMaxAbsCurv()>=0 && Vert.GetMaxAbsCurv()<10000 );
	if( Vert.GetMaxAbsCurv()>=0 && Vert.GetMaxAbsCurv()<100 )
		return 0.5+rCurvatureWeight*Vert.GetMaxAbsCurv();
	else
		return 1;
}

GW_Float BasicWeightCallback(GW_GeodesicVertex& Vert)
{
	return 1;
}

void ComputeColorCallback( GW_Vertex& Vert, float* color )
{
	char str[50];
	sprintf( str, "Processing vertex number %d.", Vert.GetID());
	GW_OutputComment( str );

	GW_GeodesicVertex& GeodesicVert = (GW_GeodesicVertex&) Vert;

	/* interpolate the data */
	T_FloatMap Weights;
	Toolkit.GetVoronoiMesh().GetNaturalNeighborWeights( Weights, Toolkit.GetGeodesicMesh(), GeodesicVert );
	GW_Vector3D ColorVect;
	for( IT_FloatMap it=Weights.begin(); it!=Weights.end(); ++it )
	{
		GW_U32 nID = it->first;
		GW_Float rWeight = it->second;
		GW_ASSERT( VertexColorMap.find(nID)!=VertexColorMap.end() );
		ColorVect += VertexColorMap[nID]*rWeight;
	}
	color[0] = ColorVect[0];
	color[1] = ColorVect[1];
	color[2] = ColorVect[2];
}

T_Vector2DMap FlattenMap;
GW_Bool bIsMeshFlattened = GW_False, bIsMeshInterpolated = GW_False;
void FlattenMesh()
{
	cout << "Flattening the basis points" << endl;
	Toolkit.GetVoronoiMesh().FlattenBasePoints( Toolkit.GetGeodesicMesh(), FlattenMap );
	cout << "done." << endl;

	bIsMeshFlattened = GW_True;	
}

void InterpolateFlattenMesh_NaturalNeighbor()
{
	char str[50];
	GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
	GW_GeodesicMesh& MeshFlat = ToolkitFlattened.GetGeodesicMesh();
	T_FloatMap Weights;

	if( !bIsMeshFlattened )
		FlattenMesh();

	/* we must recompute the voronoi diagram of the basis points */
	Toolkit.GetVoronoiMesh().PerformFastMarching( Toolkit.GetGeodesicMesh() );

	cout << "Interpolation of the flattening using Natural Neighbors." << endl;
	for( GW_U32 i=0; i<MeshFlat.GetNbrVertex(); ++i  )
	{
#ifdef GW_DEBUG
		sprintf( str, "Processing vertex number %d.", i);
		GW_OutputComment( str );
#else
		if( (i%200) == 0 )
		{
			sprintf( str, "Processing vertex number %d.", i);
			GW_OutputComment( str );
		}
#endif
		GW_GeodesicVertex* pVertFlat = (GW_GeodesicVertex*) MeshFlat.GetVertex(i);	GW_ASSERT( pVertFlat!=NULL );
		GW_GeodesicVertex* pVert     = (GW_GeodesicVertex*) Mesh.GetVertex(i);		GW_ASSERT( pVert!=NULL );
		/* compute interpolation weights */
		Toolkit.GetVoronoiMesh().GetNaturalNeighborWeights( Weights, Toolkit.GetGeodesicMesh(), *pVert );
		GW_Vector3D Pos;
		for( IT_FloatMap it=Weights.begin(); it!=Weights.end(); ++it )
		{
			GW_U32 nID = it->first;
			GW_Float rWeight = it->second;
			GW_ASSERT( FlattenMap.find(nID)!=FlattenMap.end() );
			GW_Vector2D FlatPos = FlattenMap[nID];
			Pos += GW_Vector3D(FlatPos[0], FlatPos[1], 0)*rWeight;
		}
		pVertFlat->SetPosition( Pos );
	}
	cout << "done." << endl;

	ToolkitFlattened.GetGeodesicDisplayer().BuildVertexArray( ToolkitFlattened.GetGeodesicMesh() );

	bIsMeshInterpolated = GW_True;
}

void InterpolateFlattenMesh_ReciprocicalDistance()
{
	char str[50];
	GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
	GW_GeodesicMesh& MeshFlat = ToolkitFlattened.GetGeodesicMesh();
	T_FloatMap Weights;

	if( !bIsMeshFlattened )
		FlattenMesh();

	/* we must recompute the voronoi diagram of the basis points */
	Toolkit.GetVoronoiMesh().PerformFastMarching( Toolkit.GetGeodesicMesh() );

	cout << "Interpolation of the flattening using Reciprocical Distance." << endl;
	for( GW_U32 i=0; i<MeshFlat.GetNbrVertex(); ++i  )
	{
#ifdef GW_DEBUG
		sprintf( str, "Processing vertex number %d.", i);
		GW_OutputComment( str );
#else
		if( (i%200) == 0 )
		{
			sprintf( str, "Processing vertex number %d.", i);
			GW_OutputComment( str );
		}
#endif
		GW_GeodesicVertex* pVertFlat = (GW_GeodesicVertex*) MeshFlat.GetVertex(i);	GW_ASSERT( pVertFlat!=NULL );
		GW_GeodesicVertex* pVert     = (GW_GeodesicVertex*) Mesh.GetVertex(i);		GW_ASSERT( pVert!=NULL );
		/* compute interpolation weights */
		Toolkit.GetVoronoiMesh().GetReciprocicalDistanceWeights( Weights, Toolkit.GetGeodesicMesh(), *pVert );
		GW_Vector3D Pos;
		for( IT_FloatMap it=Weights.begin(); it!=Weights.end(); ++it )
		{
			GW_U32 nID = it->first;
			GW_Float rWeight = it->second;
			GW_ASSERT( FlattenMap.find(nID)!=FlattenMap.end() );
			GW_Vector2D FlatPos = FlattenMap[nID];
			Pos += GW_Vector3D(FlatPos[0], FlatPos[1], 0)*rWeight;
		}
		pVertFlat->SetPosition( Pos );
	}
	cout << "done." << endl;

	ToolkitFlattened.GetGeodesicDisplayer().BuildVertexArray( ToolkitFlattened.GetGeodesicMesh() );

	bIsMeshInterpolated = GW_True;
}


typedef void (*T_CallbackComputeWeight)(GW_SparseMatrix& M, GW_Vertex& vert, GW_U32 offset = 0, GW_U32 extra_space = 0 );

void ComputeWeight_Regular( GW_SparseMatrix& M, GW_Vertex& vert, GW_U32 offset = 0, GW_U32 extra_space = 0  )
{
	GW_U32 i = vert.GetID();
	GW_U32 nNum = vert.GetNumberNeighbor();
	M.SetRowSize( i, nNum+1 );
	M.SetData( i+offset, i+offset, 1);	// the other sum to 1.
	GW_Float rWeight = 1.0/nNum;
	for( GW_VertexIterator it = vert.BeginVertexIterator(); it!=vert.EndVertexIterator(); ++it )
	{
		GW_Vertex* pNeighbor = *it; GW_ASSERT( pNeighbor!=NULL );
		M.SetData( i+offset, pNeighbor->GetID()+offset, -rWeight );
	}
}

void ComputeWeight_Conformal( GW_SparseMatrix& M, GW_Vertex& vert, GW_U32 offset = 0, GW_U32 extra_space = 0 )
{
	GW_U32 i = vert.GetID();
	GW_U32 nNum = vert.GetNumberNeighbor();
	M.SetRowSize( i+offset, nNum+1+extra_space );

	GW_Vector3D Pos = vert.GetPosition();
	GW_Float rTotal = 0;
	for( GW_VertexIterator it = vert.BeginVertexIterator(); it!=vert.EndVertexIterator(); ++it )
	{
		GW_Vertex* pVertNeighbor = *it;		GW_ASSERT( pVertNeighbor!=NULL );
		GW_Vector3D& PosNeighbor = pVertNeighbor->GetPosition();
		GW_Vertex* pVertAdj[2] = { it.GetLeftVertex(), it.GetRightVertex() };
		GW_Float rWeight = 0;
		for( GW_U32 k=0; k<2; ++k )
		if( pVertAdj[k]!=NULL )
		{
			GW_Vector3D& PosAdj = pVertAdj[k]->GetPosition();
			GW_Vector3D e1 = PosNeighbor - PosAdj;
			GW_Vector3D e2 = Pos - PosAdj;
			e1.Normalize();
			e2.Normalize();
			GW_Float dot = e1*e2;
			// cotan(alpha) = cos(alpha)/sin(alpha) = dot/sqrt(1-dot^2)
			if( GW_ABS(dot)!=1 )
				rWeight += dot/sqrt(1-dot*dot);
		}
		M.SetData( i+offset,pVertNeighbor->GetID()+offset, rWeight );
		rTotal += rWeight;
	}
	M.SetData(i+offset,i+offset,-rTotal);
}

GW_U32 VertexForced1 = 0;
GW_U32 VertexForced2 = 1;
void solve_system( GW_SparseMatrix& M, GW_VectorND& x, GW_VectorND& b )
{
	GW_U32 nStepIter = 1;
//	GW_Float err = M.IterativeSolve(x, b, GW_SparseMatrix::IterativeSolver_BiCG, GW_SparseMatrix::Preconditioner_SSOR, 
//			1e-10, nMaxIter, 1.2, GW_True );

	LSP_Vector xv;
	LSP_Vector bv;
	size_t Dim = M.GetDim();
	GW_Float Omega = 1.2;

	/* temportary data */
	V_Constr( &xv, "xv", Dim, Normal, True );
	GW_SparseMatrix::Copy( xv, x );
	V_Constr( &bv, "bv", Dim, Normal, True );
	GW_SparseMatrix::Copy( bv, b );

	GW_Float eps = 1e-8;
	SetRTCAccuracy( eps );
	V_SetAllCmp( &xv, 0 );	// initial guess

	GW_SparseMatrix::Copy( x, xv );
	GW_Float err = (b-M*x).Norm2();
	cout << "Nbr Iter=0, Error in resolution : " << err << endl;

	GW_U32 nNbrIter = 0;
	GW_U32 nMaxIter = 10000; // Dim*50
	while( nNbrIter<=nMaxIter && err>eps )
	{
		BiCGIter( &M.M_, &xv, &bv, nStepIter, SSORPrecond, Omega );
		// test for stop
		nNbrIter += nStepIter;
		if( LASResult()!=LASOK )
		{
			cout << "Error ";
			WriteLASErrDescr(stdout);
		}
		/* r = b - A * x */
		GW_SparseMatrix::Copy( x, xv );
		err = (b-M*x).Norm2();
		if( nNbrIter%1==0 )
		{
			cout << "Nbr Iter=" << nNbrIter << ", Error in resolution : " << err << endl;
		}
	}

	
//	std::ofstream str("log.log");
//	str << M << b << x;
//	str.close();

	GW_SparseMatrix::Copy( x, xv );


	/* destroy data */
	V_Destr(&xv);
	V_Destr(&bv);

}

T_CallbackComputeWeight CallbackComputeWeight = ComputeWeight_Conformal;
void InterpolateFlattenMesh_Floater()
{
	cout << "Interpolation of the flattening using Floater Scheme." << endl;
	GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
	GW_GeodesicMesh& MeshFlat = ToolkitFlattened.GetGeodesicMesh();

	if( !bIsMeshFlattened )
		FlattenMesh();

	GW_U32 n = Mesh.GetNbrVertex();
	GW_SparseMatrix M( n );		// weight matrix
	/* build the M matrix */
	for( GW_U32 i=0; i<n; ++i )
	{
		GW_Vertex* pVert = Mesh.GetVertex(i);	GW_ASSERT( pVert!=NULL );
		if( FlattenMap.find(i)==FlattenMap.end() )
			CallbackComputeWeight( M, *pVert );
		else
		{
			M.SetRowSize(i,1);
			M.SetData( i, i, 1 );	// fixed point
		}
	}

	/* compute each coords */
	for( GW_U32 i=0; i<2; ++i )
	{
		GW_VectorND x(n), b(n);		// solution and rhs
		x.SetZero();
		b.SetZero();
		for( IT_Vector2DMap it=FlattenMap.begin(); it!=FlattenMap.end(); ++it )
		{
			GW_U32 nId = it->first;
			GW_Vector2D& pos = it->second;
			b[nId] = pos[i];
		}
		/* solve the system */
		solve_system( M, x, b );
		/* set the position */
		for( GW_U32 j=0; j<n; ++j )
		{
			GW_Vertex* pVert = MeshFlat.GetVertex(j);	GW_ASSERT( pVert!=NULL );
			GW_Float rPos = x[j];
			pVert->GetPosition()[i] = x[j];
			pVert->GetPosition()[2] = 0;		// assure that Z position is 0.
		}
	}

	ToolkitFlattened.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kGeodesicDistance );
	ToolkitFlattened.GetGeodesicDisplayer().BuildVertexArray( ToolkitFlattened.GetGeodesicMesh() );

	bIsMeshInterpolated = GW_True;
	cout << "done." << endl;
}


void NaturalFlattening()
{
	cout << "Flattening using natural boundary condition Floater's Scheme." << endl;
	GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
	GW_GeodesicMesh& MeshFlat = ToolkitFlattened.GetGeodesicMesh();

	GW_U32 n = Mesh.GetNbrVertex();
	GW_SparseMatrix M( 2*(n) );		// weight matrix
	GW_VectorND x(2*(n), GW_Float(0));	// solution
	GW_VectorND b(2*(n), GW_Float(0));	// rhs
  
	/* build the M matrix */
	for( GW_U32 i=0; i<n; ++i )
	{
		GW_Vertex* pVert = Mesh.GetVertex(i);	GW_ASSERT( pVert!=NULL );
	
		/* test if the mesh is a boundary one */
		if( !pVert->IsBoundaryVertex() )
		{
			ComputeWeight_Conformal( M, *pVert, 0 );	// X coords
			ComputeWeight_Conformal( M, *pVert, n );	// Y coords
		}
		else
		{
			/* we need 2 more space */
			ComputeWeight_Conformal( M, *pVert, 0, 2 );	// X coords
			ComputeWeight_Conformal( M, *pVert, n, 2 );	// Y coords
			/* we must adjust the corresponding row */
			GW_Vertex* pVert1 = NULL;
			GW_Vertex* pVert2 = NULL;
			/* special case for boundary vertices : must turn IN CLOUNTERCLOCKWISE sense */
			GW_Face* pFace = pVert->GetFace();	GW_ASSERT( pFace!=NULL );
			// first find FIRST boundary vertex
			GW_Face* pStartFace = pFace;
			GW_Vertex* pDirVertex = pFace->GetNextVertex(*pVert);	GW_ASSERT( pDirVertex!=NULL );
			pDirVertex = pFace->GetNextVertex(*pDirVertex);			GW_ASSERT( pDirVertex!=NULL );
			while( pFace->GetFaceNeighbor(*pDirVertex)!=NULL )
			{
				GW_Face* pPrevFace = pFace;
				pFace = pFace->GetFaceNeighbor(*pDirVertex);
				pDirVertex = pPrevFace->GetVertex(*pVert,*pDirVertex);	GW_ASSERT(pDirVertex!=NULL);
			}
		//	GW_ASSERT( pFace!=pStartFace || pStartFace->GetFaceNeighbor(*pDirVertex)!=NULL );
			pVert1 = pFace->GetVertex(*pVert,*pDirVertex);	GW_ASSERT(pVert1!=NULL);
			// then find LAST vertex
			pDirVertex = pVert1;
			while( pFace->GetFaceNeighbor(*pDirVertex)!=NULL ) 
			{
				GW_Face* pPrevFace = pFace;
				pFace = pFace->GetFaceNeighbor(*pDirVertex);
				pDirVertex = pPrevFace->GetVertex(*pVert,*pDirVertex);	GW_ASSERT(pDirVertex!=NULL);
			}
		//	GW_ASSERT( pFace!=pStartFace || pStartFace->GetFaceNeighbor(*pDirVertex)!=NULL );
			pVert2 = pFace->GetVertex(*pVert,*pDirVertex);	GW_ASSERT(pVert2!=NULL);
			GW_ASSERT( pVert1!=NULL && pVert2!=NULL );
			GW_Float epsilon = 1;
			/* X coords **********************************/
			M.SetData( i,pVert1->GetID()+n, +epsilon );		// add a constraint on -Y coordinate
			M.SetData( i,pVert2->GetID()+n, -epsilon );
			/* Y coords **********************************/
			M.SetData( i+n,pVert1->GetID(), -epsilon );		// add a constraint on X coordinate
			M.SetData( i+n,pVert2->GetID(), +epsilon );
		}
	}



	/* add two more constraints : choose them as far as possible from one another */
	GW_Vertex* pVert[2];
	Toolkit.AddFurthestPoint(2);
	T_GeodesicVertexList& VertList = Toolkit.GetVoronoiMesh().GetBaseVertexList();
	GW_ASSERT( VertList.size()>=2 );
	IT_GeodesicVertexList it = VertList.begin();
	pVert[0] = *it;		GW_ASSERT( pVert[0]!=NULL );	it++;
	pVert[1] = *it;		GW_ASSERT( pVert[1]!=NULL && pVert[0]!=pVert[1] );

	GW_Vector2D arbitrary_pos[2] = { GW_Vector2D(-2.5,0), GW_Vector2D(2.5,0) };
	for( GW_U32 i=0; i<2; ++i )
	{
		GW_U32 nID = pVert[i]->GetID();
		/* Add a position constraint */
		M.SetRowSize( nID, 1);
		M.SetRowSize( nID+n, 1);
		M.SetData( nID,   nID,	 1 );		// X constraint
		M.SetData( nID+n, nID+n, 1 );		// Y constraint
		b[nID]	 = arbitrary_pos[i][0];
		b[nID+n] = arbitrary_pos[i][1];
	}

	solve_system(M,x,b);

	
	std::ofstream str("log.log");
	str << x;
	str.close();

	/* set the position */
	for( GW_U32 j=0; j<n; ++j )
	{
		GW_Vertex* pVert = MeshFlat.GetVertex(j);	GW_ASSERT( pVert!=NULL );
		pVert->SetPosition( GW_Vector3D( x[j], x[j+n], 0) );
	}

	ToolkitFlattened.GetGeodesicDisplayer().BuildVertexArray( ToolkitFlattened.GetGeodesicMesh() );

	bIsMeshInterpolated = GW_True;
	cout << "done." << endl;
}

GW_Bool bIsTextureCoordsComputed = GW_False;
void TextureMesh()
{
	bIsTextureCoordsComputed = GW_True;
	GW_GeodesicMesh& Mesh  = Toolkit.GetGeodesicMesh();
	GW_GeodesicMesh& MeshF = ToolkitFlattened.GetGeodesicMesh();
	GW_Vector3D min, max;
	MeshF.GetBoundingBox( min, max );
	for( GW_U32 i=0; i<Mesh.GetNbrVertex(); ++i )
	{
		GW_Vertex* pVert  = Mesh.GetVertex( i );		GW_ASSERT( pVert!=NULL );
		GW_Vertex* pVertF = MeshF.GetVertex( i );		GW_ASSERT( pVertF!=NULL );
		GW_Vector3D& pos = pVertF->GetPosition(); 
		GW_Float u = GW_SCALE_01( pos[0], min[0], max[0] );
		GW_Float v = GW_SCALE_01( pos[1], min[1], max[1] );
		pVert->SetTexCoords( u,v );
		pVertF->SetTexCoords( u,v );
	}
	Toolkit.GetGeodesicDisplayer().BuildVertexArray( Mesh );
	ToolkitFlattened.GetGeodesicDisplayer().BuildVertexArray( MeshF );
}

#define    checkImageWidth 64
#define    checkImageHeight 64
GLubyte checkImage[checkImageWidth][checkImageHeight][3];
void makeCheckImage()
{
    int i, j, c;

	for (i = 0; i < checkImageWidth; i++)
	for (j = 0; j < checkImageHeight; j++) 
	{
		c = ((((i&0x8)==0)^((j&0x8))==0))*255;
		checkImage[i][j][0] = (GLubyte) c;
		checkImage[i][j][1] = (GLubyte) c;
		checkImage[i][j][2] = (GLubyte) c;
	}

	glGenTextures( 1, &TextureID );
	glBindTexture( GL_TEXTURE_2D, TextureID );
    
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth, 
        checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 
        &checkImage[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
        GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
        GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}


void load_texture()
{
#if 0
	cout << "Loading image file " << TEXTURE_FILE_NAME << " ..." << endl;
	ILuint Error;
	ILuint nImageNum;

	/* this should be done only once ... but it's convenient to put it here. */
	ilInit();

	ilGenImages(1, &nImageNum);
	ilBindImage(nImageNum);

	/* check for error */
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
	{
		cout << "Loading failed." << endl;
		::exit(1);
	}
	ilLoadImage(TEXTURE_FILE_NAME);
	/* check for error */
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
	{
		cout << "Loading failed." << endl;
		::exit(1);
	}

	ILubyte* pData = ilGetData();
	GW_ASSERT( pData!=NULL );
	ILint Components	= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL); ;
	ILint Type			= ilGetInteger(IL_IMAGE_TYPE);
	ILint Format		= ilGetInteger(IL_IMAGE_FORMAT);	
	ILint Width			= ilGetInteger(IL_IMAGE_WIDTH);
	ILint Height		= ilGetInteger(IL_IMAGE_HEIGHT);	


	/** give the texture to opengl */
	glGenTextures( 1, &TextureID );
	glBindTexture( GL_TEXTURE_2D, TextureID );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );	// GL_LINEAR
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexImage2D
	(
		GL_TEXTURE_2D, 		//target
		0,					//mipmap level
		GL_RGBA,			//nb couleurs
		Width,				//largeur
		Height,				//hauteur
		0,					//border size
		GL_RGB,				//type des couleurs
		Type,				//codage de chaque composante
		pData				//Image
	);
#endif

	makeCheckImage();

	cout << "Loading successful." << endl;
	cout << "----" << endl;
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

	/* load the texture */
	load_texture();
}

void draw_scene()
{
	glEnable( GL_LIGHTING );
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	if( bDisplayMesh )
	{
		/* render path */
		Toolkit.GetGeodesicDisplayer().DisplayPath( Toolkit.GetGeodesicPath(), GW_Vector3D(1,1,1) );
		/* display the list of vertex */
		Toolkit.GetGeodesicDisplayer().DisplayVoronoiPoints( Toolkit.GetVoronoiMesh() );
		Toolkit.GetGeodesicDisplayer().DisplayGeodesicBoundaries( Toolkit.GetVoronoiMesh() );
		/* render mesh */
		Toolkit.GetGeodesicDisplayer().DisplayMesh( Toolkit.GetGeodesicMesh() );
	}
	if( bDisplayFlattenedMesh )
	{
		if( bIsMeshInterpolated )
			ToolkitFlattened.GetGeodesicDisplayer().DisplayMesh( ToolkitFlattened.GetGeodesicMesh() );
		/* display the flattened points */
		glDisable( GL_LIGHTING );
		glColor3f( 0.5,0,0 );
		glPointSize( 6 );
		glBegin( GL_POINTS );
		for( IT_Vector2DMap it=FlattenMap.begin(); it!=FlattenMap.end(); ++it )
		{
			GW_Vector3D pos = GW_Vector3D( it->second[0], it->second[1], 0 );
			glVertex(pos);
		}
		glEnd();
		glEnable( GL_LIGHTING );
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

	glPushMatrix();

	if( bWireFrameModeOn )
	{
		Toolkit.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		ToolkitFlattened.GetGeodesicDisplayer().EnableDraw( GW_BasicDisplayer::kForceMonoColor );
		glDisable( GL_LIGHTING );
		glColor3f( WIREFRAME_COLOR, WIREFRAME_COLOR, WIREFRAME_COLOR );
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth( nLineWidth );
		draw_scene();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable( GL_LIGHTING );
		Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
		ToolkitFlattened.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kForceMonoColor );
	}
	if( bFilledModeOn )
	{
		if( bIsTextureCoordsComputed )
		{
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, TextureID );
		}
		draw_scene();
		if( bIsTextureCoordsComputed )
			glDisable( GL_TEXTURE_2D );
	}

	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
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
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kGeodesicDistance) )
			Toolkit.GetGeodesicDisplayer().IncreaseContrast( GW_BasicDisplayer::kGeodesicDistance );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case '-':
		cout << "Decreasing constrast." << endl;
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kGeodesicDistance) )
			Toolkit.GetGeodesicDisplayer().DecreaseContrast( GW_BasicDisplayer::kGeodesicDistance );
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case 'r':
		Toolkit.GetGeodesicMesh().ResetGeodesicMesh();
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Toolkit.GetGeodesicMesh() );
		break;
	case '\t':
		if( SelectedFile != FileList.end() )
			SelectedFile++;
		if( SelectedFile == FileList.end() )
			SelectedFile = FileList.begin();
		load_file();
		break;
	case '\n':case '\r':
		glutFullScreen();
		break;
	case 'm':
		bDisplayMesh = !bDisplayMesh;
		if( bDisplayMesh )
			cout << "Displaying original mesh." << endl;
		else
			cout << "Not displaying original mesh." << endl;
		break;
	case 'M':
		bDisplayFlattenedMesh = !bDisplayFlattenedMesh;
		if( bDisplayFlattenedMesh )
			cout << "Displaying flattened mesh." << endl;
		else
			cout << "Not displaying flattened mesh." << endl;
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
	GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
	switch(key)
	{
	case GLUT_KEY_F1:
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add one furthest point  ... " << endl;
		Toolkit.AddFurthestPoint(1);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F2:
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 10 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(10);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F11:
		Mesh.RegisterWeightCallbackFunction( CurvatureWeightCallback );
		cout << "Add 100 furthest points  ... " << endl;
		Toolkit.AddFurthestPoint(100);
		cout << "done." << endl;
		break;
	case GLUT_KEY_F3:
		FlattenMesh();
		break;
	case GLUT_KEY_F4:
		InterpolateFlattenMesh_NaturalNeighbor();
		break;
	case GLUT_KEY_F5:
		InterpolateFlattenMesh_ReciprocicalDistance();
		break;
	case GLUT_KEY_F6:
		TextureMesh();
		break;
	case GLUT_KEY_F7:
		InterpolateFlattenMesh_Floater();
		break;
	case GLUT_KEY_F10:
		NaturalFlattening();
		break;
	case GLUT_KEY_F9:
		{
			cout << "Interpolating color value using Natural Neighbors ... " << endl;
			/* randomize the color */
			VertexColorMap.clear();
			T_GeodesicVertexList& VertList = Toolkit.GetVoronoiMesh().GetBaseVertexList();
			GW_U32 n = 0;
			for( IT_GeodesicVertexList it=VertList.begin(); it!=VertList.end(); ++it )
			{
				GW_GeodesicVertex* pGeodesicVert = *it;
				GW_ASSERT( pGeodesicVert!=NULL );
				VertexColorMap[pGeodesicVert->GetID()] = GW_Vector3D(n%2, n%2, n%2);
				n++;
			}

			/* recompute the color using interpolation */
			Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kVertexParametrization );
			Toolkit.GetGeodesicDisplayer().DisableDraw( GW_BasicDisplayer::kGeodesicDistance );
			Toolkit.GetGeodesicDisplayer().RegisterComputeColorCallback( ComputeColorCallback );
			Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );
			Toolkit.GetGeodesicDisplayer().RegisterComputeColorCallback( NULL );
			cout << "done." << endl;
		}
		break;
	case GLUT_KEY_F8:
		Toolkit.GetGeodesicDisplayer().ToggleDraw( GW_BasicDisplayer::kLighting );
		cout << "Turning Lighting ";
		if( Toolkit.GetGeodesicDisplayer().GetPropriety(GW_BasicDisplayer::kLighting ) )
			cout << "ON." << endl;
		else 
			cout << "OFF." << endl;
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
	/* just a hack to check memory leak under win32 */
#ifdef GW_DEBUG	
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); // Get current flag
	flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	_CrtSetDbgFlag(flag); // Set flag to the new value
#endif

	GW_InputOutput::Init(argc, argv, WINDOW_SIZE, "GW -- Test of interpolation schemes");

	srand( (unsigned)time( NULL ) );

	cout << endl << "    GW -- Test of interpolation schemes." << endl << endl;
	cout << "---" << endl;
	cout << "Use 'Left Click + Mouse' to spin the sphere." << endl;
	cout << "Use 'Right Click' to pop-up menu." << endl;
	cout << "Use 'Right+Left Click + mouse up/down' to zoom in/out." << endl;
	cout << "---" << endl;
	cout << "F1:  Add 1 furthest point to coarse mesh." << endl;
	cout << "F2:  Add 10 furthest points to coarse mesh." << endl;
	cout << "F3:  Flatten the basis point." << endl;
	cout << "F4:  Interpolate flattening." << endl;
	cout << "F8:  Turn Lighting ON/OFF." << endl;
	cout << "---" << endl;
	cout << "w: Toggle wireframe ON/OFF." << endl;
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