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
GW_GeodesicMesh& Mesh = Toolkit.GetGeodesicMesh();
GW_VoronoiMesh& VoronoiMesh = Toolkit.GetVoronoiMesh();
GW_Toolkit ToolkitFlattened;
GW_GeodesicMesh& FlattenedMesh = ToolkitFlattened.GetGeodesicMesh();
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


T_Vector2DMap FlattenMap;
GW_Bool bIsMeshFlattened = GW_False, bIsMeshInterpolated = GW_False;

void FlattenMesh_IsoMap()
{		
	char str[100];

	VoronoiMesh.BuildMesh( Mesh, GW_False );
	GW_U32 n = VoronoiMesh.GetNbrVertex();
	GW_U32 p = Mesh.GetNbrVertex();

	GW_MatrixNxP base_matrix(n,n,-1);		// only distance bewtween base points
	GW_MatrixNxP global_matrix(n,p,-1);		// distance bewteen all points


	/* compute the distance matrix */
	for( GW_U32 i=0; i<n; ++i )
	{
		GW_VoronoiVertex* pVoronoiVerti = (GW_VoronoiVertex*)VoronoiMesh.GetVertex(i);				GW_ASSERT( pVoronoiVerti!=NULL );
		GW_GeodesicVertex* pGeodesicVerti = (GW_GeodesicVertex*) pVoronoiVerti->GetBaseVertex();	GW_ASSERT( pGeodesicVerti!=NULL );

		sprintf( str, "Computing distance information for vertex %d.", i );
		GW_OutputComment( str );

		/* compute the distance map */
		Mesh.ResetGeodesicMesh();
		Mesh.PerformFastMarching( pGeodesicVerti );

		/* fill the base matrix */
		for( GW_U32 j=0; j<n; ++j )
		{
			GW_VoronoiVertex* pVoronoiVertj = (GW_VoronoiVertex*) VoronoiMesh.GetVertex(j);					GW_ASSERT( pVoronoiVerti!=NULL );
			GW_GeodesicVertex* pGeodesicVertj = (GW_GeodesicVertex*) pVoronoiVertj->GetBaseVertex();	GW_ASSERT( pGeodesicVerti!=NULL );
			GW_Float rDist = pGeodesicVertj->GetDistance();
			if( base_matrix[i][j]<0 )
				base_matrix[i][j] = rDist*rDist;
			else
				base_matrix[i][j] = (base_matrix[i][j]+rDist*rDist)*0.5;

			if( base_matrix[j][i]<0 )
				base_matrix[j][i] = rDist*rDist;
			else
				base_matrix[j][i] = (base_matrix[j][i]+rDist*rDist)*0.5;
		}
		/* fill the global matrix */
		for( GW_U32 j=0; j<p; ++j )
		{
			GW_GeodesicVertex* pGeodesicVertj = (GW_GeodesicVertex*) Mesh.GetVertex(j);		GW_ASSERT( pGeodesicVerti!=NULL );
			GW_Float rDist = pGeodesicVertj->GetDistance();
			global_matrix[i][j] = rDist*rDist;
		}
	}

	/* center the matrix */
	GW_OutputComment( "Performing the multidimensional scaling." );
	GW_MatrixNxP J(n,n,-1.0/n);
	for( GW_U32 i=0; i<n; ++i )
		J[i][i] += 1;
	/* center the matrix */
	GW_MatrixNxP dist_matrix;
	dist_matrix = J*base_matrix*J*(-0.5);

	/* perform eigen-decomposition */
	GW_MatrixNxP v(n,n);
	GW_VectorND RealEig(n);
	dist_matrix.Eigenvalue( v, NULL, &RealEig, NULL );

	GW_Float rScaleX = 0;
	GW_Float rScaleY = 0;
	GW_I32 nEigenvectorX = -1;
	GW_I32 nEigenvectorY = -1;
	/* find the two maximum eigenvalues */
	for( GW_U32 i=0; i<n; ++i )
	{
		if( RealEig[i]>=rScaleX )
		{
			rScaleY = rScaleX;
			nEigenvectorY = nEigenvectorX;
			rScaleX = RealEig[i];
			nEigenvectorX = i;
		}
		else if( RealEig[i]>=rScaleY )
		{
			rScaleY = RealEig[i]; 
			nEigenvectorY = i;
		}
	}
	rScaleX = sqrt(rScaleX);
	rScaleY = sqrt(rScaleY);
	GW_ASSERT( nEigenvectorX>=0 );
	GW_ASSERT( nEigenvectorY>=0 );

	/* compute the 2D position */
	T_Vector2DMap FlatteningMap;
	GW_MatrixNxP L(2,n);	// flattening positions
	FlatteningMap.clear();
	if( nEigenvectorX>=0 && nEigenvectorY>=0 )
		for( GW_U32 i=0; i<n; ++i )
		{
			GW_VoronoiVertex* pVoronoiVerti = (GW_VoronoiVertex*) VoronoiMesh.GetVertex(i);				GW_ASSERT( pVoronoiVerti!=NULL );
			GW_GeodesicVertex* pGeodesicVerti = (GW_GeodesicVertex*) pVoronoiVerti->GetBaseVertex();	GW_ASSERT( pGeodesicVerti!=NULL );

			GW_Vector2D pos;
			pos[0] = rScaleX*v[i][nEigenvectorX];
			pos[1] = rScaleY*v[i][nEigenvectorY];
			FlatteningMap[ pGeodesicVerti->GetID() ] = pos;
			L[0][i] = v[i][nEigenvectorX]/rScaleX;
			L[1][i] = v[i][nEigenvectorY]/rScaleY;
		}

	/* construct the mesh *****************************************************************************/
	GW_OutputComment( "Flattening the rest of the mesh." );
	GW_VectorND delta_n(n);
	for( GW_U32 k=0; k<n; ++k )
	{
		delta_n[k] = 0;	// compute the mean of the kth row
		for( GW_U32 kk=0; kk<n; ++kk )
			delta_n[k] += base_matrix[k][kk];
		delta_n[k] /= n;
	}
	GW_GeodesicMesh& MeshFlat = ToolkitFlattened.GetGeodesicMesh();
	for( GW_U32 i=0; i<MeshFlat.GetNbrVertex(); ++i )
	{
		GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) MeshFlat.GetVertex(i);
		GW_VectorND delta_x(n);		// distance from vertex to landmark
		for( GW_U32 k=0; k<n; ++k )
			delta_x[k] = global_matrix[k][i];
		delta_x = delta_n-delta_x;
		GW_VectorND pos(2);
		pos = 0.5*(L*delta_x);
		pVert->SetPosition( GW_Vector3D(pos[0], pos[1], 0) );
	}

	bIsMeshFlattened = GW_True;	
	ToolkitFlattened.GetGeodesicDisplayer().BuildVertexArray( ToolkitFlattened.GetGeodesicMesh() );
}


/** a callbak function to register the neighborhood information */
GW_U32 nNumNeighbor = 0;
GW_U32 nNumStartVertex = 0;
const GW_U32 K = 5;
GW_MatrixNxP neighbor_matrix( 1,1,-1 );	
T_FloatMap* pAllDistanceMap = NULL;
void LLE_BuildNeighbor_Callback( GW_GeodesicVertex& Vert )
{
	GW_VoronoiVertex* pVoronoiVert = VoronoiMesh.GetVoronoiFromGeodesic( Vert );
	if( pVoronoiVert!=NULL && nNumNeighbor<K )
	{
		if( nNumStartVertex!=pVoronoiVert->GetID() )	// avoid self neighbor ...
		{
			neighbor_matrix.SetData( nNumStartVertex,nNumNeighbor,pVoronoiVert->GetID() );
			nNumNeighbor++;
		}
	}
	/* set the distance of the geodesic vertex */
	GW_U32 nID = Vert.GetID();
	T_FloatMap& CurMap = pAllDistanceMap[nID];
	CurMap[nNumStartVertex] = Vert.GetDistance();
}
GW_Bool LLE_BuildNeighbor_StopCallback( GW_GeodesicVertex& Vert )
{
	return nNumNeighbor>=K;
}

T_FloatMap* pComputeDistance_CurMap = NULL;
void LLE_ComputeDistance_Callback( GW_GeodesicVertex& Vert )
{
	GW_VoronoiVertex* pVoronoiVert = VoronoiMesh.GetVoronoiFromGeodesic( Vert );
	if( pVoronoiVert!=NULL )
	{
		GW_U32 nID = pVoronoiVert->GetID();
		if( pComputeDistance_CurMap->find( nID )!=pComputeDistance_CurMap->end() )
		{
			GW_ASSERT( nNumStartVertex!=nID );
			/* we must compute the distance to this one */
			GW_ASSERT( (*pComputeDistance_CurMap)[nID]<0 );
			(*pComputeDistance_CurMap)[nID] = Vert.GetDistance();
			nNumNeighbor++;
		}
	}
}
GW_Bool LLE_ComputeDistance_StopCallback( GW_GeodesicVertex& Vert )
{
	GW_ASSERT(pComputeDistance_CurMap!=NULL);
	return nNumNeighbor>=pComputeDistance_CurMap->size();
}

GW_Vector2D ComputeGradient( GW_MatrixNxP& P, GW_VectorND& D, GW_Vector2D& x )
{
	GW_Vector2D g;
//	GW_ASSERT( P.GetNbrCols()==2 );
	GW_U32 r = P.GetNbrRows();
//	GW_ASSERT( D.GetDim()==r );
	for( GW_U32 i=0; i<r; ++i )
	{
		GW_Vector2D p( P[i][0], P[i][1] );
		g[0] += (p[0]-x[0])*( D[i]-(p-x).SquareNorm() );
		g[1] += (p[1]-x[1])*( D[i]-(p-x).SquareNorm() );
	}
	return g*4.0;
}
GW_Float ComputeEnergy( GW_MatrixNxP& P, GW_VectorND& D, GW_Vector2D& x )
{
	GW_Float E = 0;
	GW_ASSERT( P.GetNbrCols()==2 );
	GW_U32 r = P.GetNbrRows();
	GW_ASSERT( D.GetDim()==r );
	for( GW_U32 i=0; i<r; ++i )
	{
		GW_Vector2D p( P[i][0], P[i][1] );
		E += ( D[i]-(p-x).SquareNorm() )*( D[i]-(p-x).SquareNorm() );
	}
	return E;
}
GW_Vector2D PerformGradientDescent( GW_MatrixNxP& P, GW_VectorND& D, 
									GW_Float rStep = 0.03f, GW_U32 nNbrStepMax = 2000, GW_Float rEps = 1e-5 )
{
	GW_Vector2D x;	
	GW_ASSERT( P.GetNbrCols()==2 );
	GW_U32 r = P.GetNbrRows();
	GW_ASSERT( D.GetDim()==r );
	/* initialize with barycenter */
	for( GW_U32 i=0; i<r; ++i )
		x += GW_Vector2D( P[i][0], P[i][1] );
	x /= r;
	/* now run gradient descent */
	GW_U32 nNbrStep = 0;
	GW_Float rEnergy = ComputeEnergy( P,D,x );
	GW_Float rDeltaEnergy = GW_INFINITE;
	while( nNbrStep<=nNbrStepMax && rDeltaEnergy>rEps )
	{
		x = x - ComputeGradient(P,D,x)*rStep;
		GW_Float rNewEnergy = ComputeEnergy( P,D,x );
		rDeltaEnergy = GW_ABS( rNewEnergy-rEnergy );
		rEnergy = rNewEnergy;
		nNbrStep++;
	}

	return x;
}


void FlattenMesh_LLE()
{		
	char str[100];

	VoronoiMesh.BuildMesh( Mesh, GW_False );
	GW_U32 n = VoronoiMesh.GetNbrVertex();
	GW_U32 p = Mesh.GetNbrVertex();

	GW_MatrixNxP weight_matrix( n,K,-1 );	
	neighbor_matrix.Reset(n,K); 
	neighbor_matrix.SetValue(-1);

	pAllDistanceMap =  new T_FloatMap[p];	// keep distance information from one vertex to some base vertices
	T_FloatMap* pBaseDistanceMap = new T_FloatMap[n];	// keep distance information from one base vertex to some base vertices

	/* compute the neighborhood information */
	for( GW_U32 i=0; i<n; ++i )
	{
		GW_VoronoiVertex* pVoronoiVerti = (GW_VoronoiVertex*)VoronoiMesh.GetVertex(i);				GW_ASSERT( pVoronoiVerti!=NULL );
		GW_GeodesicVertex* pGeodesicVerti = (GW_GeodesicVertex*) pVoronoiVerti->GetBaseVertex();	GW_ASSERT( pGeodesicVerti!=NULL );

		sprintf( str, "Computing neighborhood information for vertex %d.", i );
		GW_OutputComment( str );

		/* compute the distance map */
		Mesh.ResetGeodesicMesh();
		/* init the callback data */
		nNumNeighbor = 0;
		nNumStartVertex = i;
		Mesh.RegisterNewDeadVertexCallbackFunction( LLE_BuildNeighbor_Callback );
		Mesh.RegisterForceStopCallbackFunction( LLE_BuildNeighbor_StopCallback );
		Mesh.PerformFastMarching( pGeodesicVerti );
		Mesh.RegisterNewDeadVertexCallbackFunction( NULL );
		Mesh.RegisterForceStopCallbackFunction( NULL );
	}

	/* compute needed distances */
	for( GW_U32 i=0; i<n; ++i )
	{
		T_FloatMap& CurMap1 = pBaseDistanceMap[i];
		for( GW_U32 s=0; s<K; ++s )
		{
			GW_U32 s_num = neighbor_matrix.GetData( i,s );
			CurMap1[s_num] = -1;
			T_FloatMap& CurMap2 = pBaseDistanceMap[s_num];
			for( GW_U32 t=0; t<K; ++t )
			{
				GW_U32 t_num = neighbor_matrix.GetData( i,t );
				if( s!=t )
				{
					GW_ASSERT( s_num!=t_num );
					CurMap2[t_num] = -1;		// we need to compute distance from s to t
					T_FloatMap& CurMap3 = pBaseDistanceMap[t_num];
					CurMap3[s_num] = -1;		// we need to compute distance from t to s
				}
			}
		}
	}
	for( GW_U32 i=0; i<n; ++i )
	{
		T_FloatMap& CurMap = pBaseDistanceMap[i];
		for( IT_FloatMap it=CurMap.begin(); it!=CurMap.end(); ++it )
			GW_ASSERT( it->first != i );
	}
	for( GW_U32 i=0; i<n; ++i )
	{
		GW_VoronoiVertex* pVoronoiVerti = (GW_VoronoiVertex*)VoronoiMesh.GetVertex(i);				GW_ASSERT( pVoronoiVerti!=NULL );
		GW_GeodesicVertex* pGeodesicVerti = (GW_GeodesicVertex*) pVoronoiVerti->GetBaseVertex();	GW_ASSERT( pGeodesicVerti!=NULL );
		sprintf( str, "Computing distance information for vertex %d.", i );
		GW_OutputComment( str );
		/* compute the distance map */
		Mesh.ResetGeodesicMesh();
		/* init the callback data */
		pComputeDistance_CurMap = & pBaseDistanceMap[i];
		nNumNeighbor = 0;
		nNumStartVertex = i;
		Mesh.RegisterNewDeadVertexCallbackFunction( LLE_ComputeDistance_Callback );
		Mesh.RegisterForceStopCallbackFunction( LLE_ComputeDistance_StopCallback );
		Mesh.PerformFastMarching( pGeodesicVerti );
		GW_ASSERT( nNumNeighbor==pComputeDistance_CurMap->size() );
		Mesh.RegisterNewDeadVertexCallbackFunction( NULL );
		Mesh.RegisterForceStopCallbackFunction( NULL );
	}
	for( GW_U32 i=0; i<n; ++i )
	{
		T_FloatMap& CurMap = pBaseDistanceMap[i];
		for( IT_FloatMap it=CurMap.begin(); it!=CurMap.end(); ++it )
			GW_ASSERT( it->first != i );
	}


	/* compute the weight */
	GW_MatrixNxP C(K,K);
	GW_MatrixNxP rho(K+1,K+1);
	GW_MatrixNxP J(K+1,K+1,-1.0/(K+1));
	for( GW_U32 i=0; i<K+1; ++i )
		J[i][i] += 1;
	for( GW_U32 i=0; i<n; ++i )
	{
		sprintf( str, "Computing weights for vertex %d.", i );
		GW_OutputComment( str );

		GW_VoronoiVertex* pVoronoiVerti = (GW_VoronoiVertex*)VoronoiMesh.GetVertex(i);				GW_ASSERT( pVoronoiVerti!=NULL );
		GW_GeodesicVertex* pGeodesicVerti = (GW_GeodesicVertex*) pVoronoiVerti->GetBaseVertex();	GW_ASSERT( pGeodesicVerti!=NULL );
		/* building the matrix of pairwise local distance */
		for( GW_U32 s=0; s<K+1; ++s )
		for( GW_U32 t=0; t<K+1; ++t )
		{
			if( s==t )
				rho.SetData( t,s, 0 );
			else
			{
				GW_U32 s_num, t_num;
				if( s==0 )
					s_num = i;
				else
					s_num = neighbor_matrix.GetData( i,s-1 );
				if( t==0 )
					t_num = i;
				else
					t_num = neighbor_matrix.GetData( i,t-1 );
				// We need the distance between point s_num and t_num
				GW_Float rDist = -1;
				T_FloatMap& CurMap1 = pBaseDistanceMap[s_num];
				if( CurMap1.find(t_num)!=CurMap1.end() )
				{
					GW_ASSERT(CurMap1[t_num]>=0);
					rDist = CurMap1[t_num];		
				}
				T_FloatMap& CurMap2 = pBaseDistanceMap[t_num];
				if( CurMap2.find(s_num)!=CurMap2.end() )
				{
					GW_ASSERT(CurMap2[s_num]>=0);
					if( rDist<0 )
						rDist = CurMap2[s_num];
					else
						rDist = 0.5*(rDist+CurMap2[s_num]);
				}
				GW_ASSERT( rDist>=0 );
				rho.SetData( t,s, rDist );
			}
		}
		/* turn it into a dot product matrix */
		rho = J*rho*J*(-0.5);
		/* build Cst = <x0-xs,x0-xt> matrix */
		for( GW_U32 s=1; s<K+1; ++s )
		for( GW_U32 t=1; t<K+1; ++t )
		{
			/* <x0-xs,x0-xt> = rho{00}+rho{st}-rho{0s}-rho{t0}*/
			// C[s-1][t-1] = 
			C.SetData( t-1,s-1, rho.GetData(0,0)+rho.GetData(s,t)-rho.GetData(0,s)-rho.GetData(t,0) );
		}
		/* little preconditionning */
		GW_Float delta = 0.1f;
		for( GW_U32 j=0; j<K; ++j )
			C[j][j] += delta/K;
		/* weights are renormalized solution to C*w=1 */
		GW_VectorND rhs(K,1);
		GW_VectorND w(K,0.0f);
		C.LUSolve( w,rhs );
       //  cout << "\nw = \n" << w;
		GW_Float sum = 0;
		for( GW_U32 j=0; j<K; ++j )
			sum += w[j];
		GW_ASSERT( sum!=0 );
		if( sum!=0 )
			w = w*(1.0/sum);
		for( GW_U32 j=0; j<K; ++j )
			weight_matrix.SetData( i,j,  1.0/K ); 
//			weight_matrix.SetData( i,j,  w[j] );
	}

	// cout << weight_matrix;
	/* center the matrix */
	GW_OutputComment( "Performing the flattening." );
	GW_MatrixNxP M(n,n,0.0);
	for( GW_U32 i_num=0; i_num<n; ++i_num )	// compute Id-W
	{
		M[i_num][i_num] = 1;
		for( GW_U32 j=0; j<K; ++j )
		{
			GW_U32 j_num = neighbor_matrix.GetData(i_num,j);
			M[i_num][j_num] -= weight_matrix.GetData(i_num,j);
		}
	}
	M = M.Transpose()*M;

	/* perform eigen-decomposition */
	GW_MatrixNxP v(n,n);
	GW_VectorND RealEig(n);
	M.Eigenvalue( v, NULL, &RealEig, NULL );

	GW_I32 nNumEigs[3] = {-1,-1,-1};
	GW_Float rValEigs[3] = { 1e9, 1e9, 1e9 };
	/* find the two minimum non-null eigenvalues */
	for( GW_U32 i=0; i<n; ++i )
	{
		if( RealEig[i]<=rValEigs[0] )
		{
			rValEigs[2] = rValEigs[1];
			rValEigs[1] = rValEigs[0];
			rValEigs[0] = RealEig[i];
			nNumEigs[2] = nNumEigs[1];
			nNumEigs[1] = nNumEigs[0];
			nNumEigs[0] = i;
		}
		else if( RealEig[i]<=rValEigs[1] )
		{
			rValEigs[2] = rValEigs[1];
			rValEigs[1] = RealEig[i];
			nNumEigs[2] = nNumEigs[1];
			nNumEigs[1] = i;
		}
		else if( RealEig[i]<=rValEigs[2] )
		{
			rValEigs[2] = RealEig[i];
			nNumEigs[2] = i;
		}
	}
	/* the choosen number */
	GW_U32 x_ind = nNumEigs[1];
	GW_U32 y_ind = nNumEigs[2];
	GW_U32 x_scale = 1; //sqrt( RealEig[x_ind] );
	GW_U32 y_scale = 1; //sqrt( RealEig[y_ind] );

	/* compute the 2D position */
	T_Vector2DMap FlatteningMap;
	GW_MatrixNxP L(2,n);	// flattening positions
	FlatteningMap.clear();

	for( GW_U32 i=0; i<n; ++i )
	{
		GW_VoronoiVertex* pVoronoiVerti = (GW_VoronoiVertex*) VoronoiMesh.GetVertex(i);				GW_ASSERT( pVoronoiVerti!=NULL );
		GW_GeodesicVertex* pGeodesicVerti = (GW_GeodesicVertex*) pVoronoiVerti->GetBaseVertex();	GW_ASSERT( pGeodesicVerti!=NULL );

		GW_Vector2D pos;
		pos[0] = v[i][x_ind]/x_scale;
		pos[1] = v[i][y_ind]/y_scale;
		FlatteningMap[ pGeodesicVerti->GetID() ] = pos;
		L[0][i] = v[i][x_ind]/x_scale;
		L[1][i] = v[i][y_ind]/y_scale;
	}

	/* construct the mesh *****************************************************************************/
	/* solve the energy minimisation E(x)=sum_{j=0}^{r-1}{ ( D[j]-|x-P[j]|^2 )^2 } */ 
	GW_OutputComment( "Flattening the rest of the mesh." );
	GW_GeodesicMesh& MeshFlat = ToolkitFlattened.GetGeodesicMesh();
	for( GW_U32 i=0; i<p; ++i )
	{
		/* compute some auxiliary variables */
		T_FloatMap& CurMap = pAllDistanceMap[i];
		GW_U32 r = (GW_U32) CurMap.size();	// number of landmark
		GW_MatrixNxP PosMatrix( r,2,0.0f );
		GW_VectorND DistVector( r, 0.0f );
		GW_U32 j = 0;
		for( IT_FloatMap it = CurMap.begin(); it!=CurMap.end(); ++it )
		{
			GW_U32 nLandMark = it->first;
			DistVector.SetData( j, it->second );
			PosMatrix.SetData( j,0, L.GetData( 0,nLandMark ) );
			PosMatrix.SetData( j,1, L.GetData( 1,nLandMark ) );
			j++;
		}
		/* perform a gradient descent */
		GW_Vector2D	pos = PerformGradientDescent( PosMatrix,DistVector );
		GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) MeshFlat.GetVertex(i);
		pVert->SetPosition( GW_Vector3D(pos[0], pos[1], 0) );

	}
//	cout << MeshFlat.GetBoundingRadius();
	MeshFlat.ScaleVertex( 3/MeshFlat.GetBoundingRadius() );

	bIsMeshFlattened = GW_True;	
	ToolkitFlattened.GetGeodesicDisplayer().BuildVertexArray( ToolkitFlattened.GetGeodesicMesh() );

	GW_DELETEARRAY( pAllDistanceMap  );
	GW_DELETEARRAY( pBaseDistanceMap );
}

GW_Bool bIsTextureCoordsComputed = GW_False;
void TextureMesh()
{
	bIsTextureCoordsComputed = GW_True;
	GW_GeodesicMesh& Mesh  = Toolkit.GetGeodesicMesh();
	GW_GeodesicMesh& MeshF = ToolkitFlattened.GetGeodesicMesh();
	GW_Vector3D min, max;
	MeshF.GetBoundingBox( min, max );
	min = GW_Vector3D(-3,-3,0);
	max = GW_Vector3D(3,3,0);
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

#define    checkImageWidth 128
#define    checkImageHeight 128
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
		ToolkitFlattened.GetGeodesicDisplayer().DisplayMesh( ToolkitFlattened.GetGeodesicMesh() );
		/* display the flattened points */
		glDisable( GL_LIGHTING );
		glColor( GW_Vector3D(0,0,1) );
		glPointSize( 8 );
		glBegin( GL_POINTS );
		for( GW_U32 i=0; i<VoronoiMesh.GetNbrBasePoints(); ++i )
		{
			GW_VoronoiVertex* pVVert = (GW_VoronoiVertex*) VoronoiMesh.GetVertex(i);
			GW_U32 nNum = pVVert->GetBaseVertex()->GetID();
			GW_GeodesicVertex* pVert = (GW_GeodesicVertex*) FlattenedMesh.GetVertex(nNum);
			glVertex( pVert->GetPosition() );
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
	case 'r':
		Mesh.ResetGeodesicMesh();
		FlattenedMesh.ResetGeodesicMesh();
		Toolkit.GetGeodesicDisplayer().BuildColorArray( Mesh );
		ToolkitFlattened.GetGeodesicDisplayer().BuildColorArray( FlattenedMesh );
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
	case 's':
		cout << "Saving saved camera settings ... done.";
		GW_InputOutput::SaveCameraSettings();
		break;
	case 'l':
		cout << "Loading saved camera settings ... done.";
		GW_InputOutput::LoadCameraSettings();
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
		cout << "Flattening mesh ... " << endl;
		FlattenMesh_LLE();
		cout << "done." << endl;
		break;
	case GLUT_KEY_F4:
		cout << "Texturing mesh ... " << endl;
		TextureMesh();
		cout << "done." << endl;
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

	GW_InputOutput::Init(argc, argv, WINDOW_SIZE, "GW -- Test of surface flattening");

	srand( (unsigned)time( NULL ) );

	cout << endl << "    GW -- Test of surface flattening." << endl << endl;
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