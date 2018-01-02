// Points2Mesh.cpp: implementation of the CPoints2Mesh class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "qtimage.h"
#include "Points2Mesh.h"
#include "vtkPowerCrustSurfaceReconstruction.h"
#include "vtkTextureMapToSphere.h"
#include "vtkBMPReader.h"
#include "vtkTexture.h"
#include "vtkTransformTextureCoords.h"
#include "vtkReverseSense.h"
#include "vtkSurfaceReconstructionFilter.h"
#include "vtkProgrammableSource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPoints2Mesh::CPoints2Mesh()
{
	m_pPnts=NULL;
	m_iCount=0;
	m_meshType=DELAUNAY;
	m_sTextureFile="";
}

CPoints2Mesh::~CPoints2Mesh()
{

}

vtkActor* CPoints2Mesh::GetActor()
{
	if(m_iCount<3 || m_pPnts==NULL)
		return NULL;

	short   error = 0;
	int	i;
	
	vtkPoints *points = vtkPoints::New();
	
	for(i = 0; i < m_iCount; i++)
	{
		points->InsertPoint( i, m_pPnts[i].x, m_pPnts[i].y, m_pPnts[i].z);
	}
	
	vtkPolyData *profile = vtkPolyData::New();
    profile->SetPoints( points);
	points->Delete();

	vtkDelaunay3D *delaunayTriangulator = NULL;
	vtkPolyDataNormals *polyDataNormals = NULL;
	vtkDataSet*	output = NULL;
	vtkReverseSense *reverse=NULL;
	

	if(m_meshType==DELAUNAY)
	{
		delaunayTriangulator = vtkDelaunay3D::New();
		delaunayTriangulator->SetInput(profile);
		
		delaunayTriangulator->SetTolerance( 0.001);
		delaunayTriangulator->SetAlpha( 20);
		delaunayTriangulator->BoundingTriangulationOff();
		
		output = (vtkDataSet*) delaunayTriangulator->GetOutput();
	}
	else if(m_meshType==POWERSUFR)	
	{	
		
		vtkPowerCrustSurfaceReconstruction *power = vtkPowerCrustSurfaceReconstruction::New();
		power->SetInput( profile);
		power->Update();

		polyDataNormals = vtkPolyDataNormals::New();
		polyDataNormals->ConsistencyOn();
		polyDataNormals->AutoOrientNormalsOn();
		polyDataNormals->SetInput(power->GetOutput());
		power->Delete();		

		output = (vtkDataSet*) polyDataNormals -> GetOutput();
	}else
	{
		vtkSurfaceReconstructionFilter *surf=vtkSurfaceReconstructionFilter::New();
		surf->SetInput(profile);

		vtkContourFilter *cf=vtkContourFilter::New();
		cf->SetInput(surf->GetOutput());
		cf->SetValue(0,0.0);
		surf->Delete();

		//# Sometimes the contouring algorithm can create a volume whose gradient
		//# vector and ordering of polygon (using the right hand rule) are 
		//# inconsistent. vtkReverseSense cures this problem.
		reverse=vtkReverseSense::New();
		reverse->SetInput(cf->GetOutput());
		reverse->ReverseCellsOn();
		reverse->ReverseNormalsOn();
		cf->Delete();

		output= (vtkDataSet*)reverse -> GetOutput();
	}
	
	// ****************** Mapper
	vtkTextureMapToSphere *tmapper = vtkTextureMapToSphere::New();
	tmapper->SetInput(output);
	tmapper->PreventSeamOn();
	
	if( polyDataNormals) polyDataNormals->Delete();
	if( delaunayTriangulator) delaunayTriangulator->Delete();
	if( reverse) reverse->Delete();

	vtkTransformTextureCoords *xform = vtkTransformTextureCoords::New();
	xform->SetInput(tmapper->GetOutput());
	xform->SetScale(4,4,4);
	tmapper->Delete();
			
	vtkDataSetMapper  *map = vtkDataSetMapper ::New();
	map->SetInput(xform->GetOutput());
	map->ScalarVisibilityOff();
	xform->Delete();

	
	
	map->Update();

	vtkActor *roiVolumeActor=roiVolumeActor = vtkActor::New();
	//roiVolumeActor->GetProperty()->FrontfaceCullingOn();
	//roiVolumeActor->GetProperty()->BackfaceCullingOn();
	
	roiVolumeActor->SetMapper(map);
	map->Delete();
	
	// *****************Texture
	CString sTextureFile=m_sTextureFile;
	
	vtkBMPReader *bmpread = vtkBMPReader::New();
	bmpread->SetFileName(sTextureFile);

	vtkTexture *texture=NULL;
	if (!texture) {
		texture = vtkTexture::New();
		texture->InterpolateOn();
	}
	texture->SetInput( bmpread->GetOutput());
	bmpread->Delete();

	roiVolumeActor->SetTexture( texture);
	texture->Delete();

	
	profile->Delete();

	//roiVolumeActor->GetProperty()->FrontfaceCullingOn();
	//roiVolumeActor->GetProperty()->BackfaceCullingOn();
	
	
	return roiVolumeActor;
}


