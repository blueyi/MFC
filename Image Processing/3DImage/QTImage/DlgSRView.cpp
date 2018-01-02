// DlgSRView.cpp : implementation file
//

#include "stdafx.h"
#include "qtimage.h"
#include "DlgSRView.h"
#include "QTImageDlg.h"
#include "ROIManager.h"
#include "vtkImageGaussianSmooth.h"
#include "vtkImageThreshold.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkStripper.h"
#include "vtkImageMarchingCubes.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataNormals.h"
#include "vtkDecimatePro.h"
#include "vtkPolyDataConnectivityFilter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSRView dialog
extern CQTImageDlg* gpMainDlg;

CDlgSRView::CDlgSRView(CWnd* pParent /*=NULL*/)
	: CImageViewer(CDlgSRView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSRView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Type=1;

	m_pOMW=vtkOrientationMarkerWidget::New();
}


void CDlgSRView::DoDataExchange(CDataExchange* pDX)
{
	CImageViewer::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSRView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSRView, CImageViewer)
	//{{AFX_MSG_MAP(CDlgSRView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSRView message handlers

BOOL CDlgSRView::OnInitDialog() 
{
	CImageViewer::OnInitDialog();
	
	// TODO: Add extra initialization here
	vtkInteractorStyleTrackballCamera* pStyle = vtkInteractorStyleTrackballCamera::New();
	m_pInteractor->SetInteractorStyle(pStyle);
	pStyle->Delete();

	vtkAxesActor *pAxes = vtkAxesActor::New();
	pAxes->SetShaftTypeToCylinder();
	pAxes->SetXAxisLabelText("x");
	pAxes->SetYAxisLabelText("y");
	pAxes->SetZAxisLabelText("z");
	pAxes->SetTotalLength(50, 50, 50);
	pAxes->SetAxisLabels(1);

	m_pOMW->SetOrientationMarker(pAxes);
	m_pOMW->SetInteractor(m_pInteractor);
	m_pOMW->EnabledOn();
	m_pOMW->InteractiveOff();
	pAxes->Delete();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSRView::SetSeries(vtkImageData *pImage)
{
	m_pImage=pImage;
}

void CDlgSRView::OnDestroy() 
{
	m_pOMW->Delete();

	CImageViewer::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CDlgSRView::UpdateMesh()
{
	CQTImageDlg* pMainDlg = gpMainDlg;
	CROIManager *pROIManager=&pMainDlg->m_roiManager;
	m_pSegmentedImage=pMainDlg->m_seriesManager.GetSegmentedImage(m_pImage);
	int iROICount=pROIManager->GetROICount(m_pImage);
	if(iROICount<=0)
		return;

	m_pRenderer->RemoveAllViewProps();
	CROI *pROI;
	for(int i=0;i<iROICount;i++)
	{
		pROI=pROIManager->GetROIAt(m_pImage,i);
		UpdateMesh(pROI);
	}

	/*//test
	vtkMarchingCubes *pMarchFilter=vtkMarchingCubes::New();
	pMarchFilter->SetInput(m_pImage); //SegmentedImage);
	pMarchFilter->SetNumberOfContours(3);
	pMarchFilter->SetValue(0,400);
	pMarchFilter->SetValue(1,1500);
	pMarchFilter->SetValue(2,2500);
	for(i=0;i<5;i++)
	{
		//pROI=pROIManager->GetROIAt(m_pImage,i);
		//pMarchFilter->SetValue(i,i*100); //pROI->GetLabel());
	}
	
	vtkColorTransferFunction *color=vtkColorTransferFunction::New();
	color->AddRGBPoint(380,255,0,255);
	color->AddRGBPoint(410,255,255,255);
	color->AddRGBPoint(1500,255,255,0);
	color->AddRGBPoint(2600,0,0,255);
	
	vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
	skinMapper->SetInput(pMarchFilter->GetOutput());
	skinMapper->ScalarVisibilityOn();
	skinMapper->SetScalarRange(pMarchFilter->GetOutput()->GetScalarRange());
	//skinMapper->SetLookupTable(color);

	vtkActor *pActor=vtkActor::New();
	pActor->SetMapper(skinMapper);
	//pActor->GetProperty()->SetDiffuseColor(1, .49, .25);
	//pActor->GetProperty()->SetSpecular(.3);
	//pActor->GetProperty()->SetSpecularPower(20);
	
	m_pRenderer->AddActor(pActor);
	
	pMarchFilter->Delete();
	skinMapper->Delete();
	pActor->Delete();
	color->Delete();
	//test*/

	m_pRenderer->Render();
	m_pRenderer->ResetCamera();
	Invalidate(FALSE);
}

void CDlgSRView::UpdateMesh(CROI *pROI)
{
	
	short label=pROI->GetLabel();

	vtkImageThreshold *imageThreshold=vtkImageThreshold::New();
	imageThreshold->SetInput(m_pSegmentedImage);
	imageThreshold->ThresholdBetween(label,label);
	imageThreshold->SetReplaceIn(1);
	imageThreshold->SetReplaceOut(1);
	imageThreshold->SetOutValue(0);
	imageThreshold->SetInValue(label);
	
	
	try
	{
		m_meshOptions.color=pROI->GetColor();
		m_meshOptions.opacity=pROI->GetOpacity()/255.0;
		m_meshOptions.label=pROI->GetLabel();
		UpdateMesh(imageThreshold->GetOutput());
	}catch(...)
	{
		//
	}
	
	imageThreshold->Delete();
}

void CDlgSRView::UpdateMesh2(CROI *pROI)
{
	
	short label=pROI->GetLabel();
	int *Dim=m_pSegmentedImage->GetDimensions();
	unsigned short *pData=(unsigned short *)m_pSegmentedImage->GetScalarPointer(0,0,0);

	ROI *ppROI;

	//计算BOUNDS
	short bound[3][2];
	bound[0][0]=bound[1][0]=bound[2][0]=9999;
	bound[0][1]=bound[1][1]=bound[2][1]=-9999;

	int iROICount=pROI->GetCount();
	for(int j=0;j<iROICount;j++)
	{
		ppROI=pROI->GetAt(j);
		if(bound[0][0]>ppROI->bounds[0])
		{
			bound[0][0]=ppROI->bounds[0];
		}
		if(bound[0][1]<ppROI->bounds[1])
		{
			bound[0][1]=ppROI->bounds[1];
		}

		if(bound[1][0]>ppROI->bounds[2])
		{
			bound[1][0]=ppROI->bounds[2];
		}
		if(bound[1][1]<ppROI->bounds[3])
		{
			bound[1][1]=ppROI->bounds[3];
		}

		if(bound[2][0]>ppROI->bounds[4])
		{
			bound[2][0]=ppROI->bounds[4];
		}
		if(bound[2][1]<ppROI->bounds[5])
		{
			bound[2][1]=ppROI->bounds[5];
		}
	}

	
	int Dim0Dim1=Dim[0]*Dim[1];

	for(int x=0;x<Dim[0];x++)
	{
		for(int y=0;y<Dim[1];y++)
		{
			for(int z=0;z<Dim[2];z++)
			{
				if(pData[z*Dim0Dim1+y*Dim[0]+x]==label)
				{
				if(bound[0][0]>x)
				{
					bound[0][0]=x;
				}
				if(bound[0][1]<x)
				{
					bound[0][1]=x;
				}

				if(bound[1][0]>y)
				{
					bound[1][0]=y;
				}
				if(bound[1][1]<y)
				{
					bound[1][1]=y;
				}

				if(bound[2][0]>z)
				{
					bound[2][0]=z;
				}
				if(bound[2][1]<z)
				{
					bound[2][1]=z;
				}
				}
			}
		}
	}
	//计算bounds end


	
	vtkImageData *pNewImage=vtkImageData::New();
	int newDim[3];
	newDim[0]=bound[0][1]-bound[0][0]+1;
	newDim[1]=bound[1][1]-bound[1][0]+1;
	newDim[2]=bound[2][1]-bound[2][0]+1;
	double *dSpaceing=m_pSegmentedImage->GetSpacing();

	short *pNewData = new short[newDim[0]*newDim[1]*newDim[2]];	
	
	
	for(int y=0;y<newDim[1];y++)
	{
		for(int z=0;z<newDim[2];z++)
		{
			short *pNewData2=pNewData+z*newDim[0]*newDim[1]+y*newDim[0];
			unsigned short *pData2=pData+(bound[2][0]+z)*Dim[0]*Dim[1]+(bound[1][0]+y)*Dim[0]+bound[0][0];
			memcpy((char*)pNewData2,(char*)pData2,sizeof(short)*newDim[0]);
		}
	}
	
	Dim0Dim1=newDim[0]*newDim[1];

	for(j=0;j<iROICount;j++)
	{
		ppROI=pROI->GetAt(j);
		for(int x=ppROI->bounds[0];x<=ppROI->bounds[1];x++)
		{
			for(int y=ppROI->bounds[2];y<=ppROI->bounds[3];y++)
			{
				for(int z=ppROI->bounds[4];z<=ppROI->bounds[5];z++)
				{
					if(pROI->PtInRegion(x,y,z,ppROI))
					{
						pNewData[(z-bound[2][0])*Dim0Dim1+(y-bound[1][0])*newDim[0]+(x-bound[0][0])]=pROI->GetLabel();
					}
				}
			}
		}
	}

	vtkShortArray *array =  vtkShortArray::New();
	array ->SetArray(pNewData, newDim[0]*newDim[1]*newDim[2],0) ;
	pNewImage->GetPointData()->SetScalars(array);
	pNewImage->SetDimensions(newDim[0],newDim[1],newDim[2]);
	pNewImage->SetScalarType(VTK_SHORT);
	pNewImage->SetSpacing(dSpaceing[0], dSpaceing[1], dSpaceing[2]);
	pNewImage->SetOrigin(bound[0][0], bound[1][0], bound[2][0]);
	array->Delete();
			
	
	try
	{
		m_meshOptions.color=pROI->GetColor();
		m_meshOptions.opacity=pROI->GetOpacity()/255.0;
		m_meshOptions.label=pROI->GetLabel();
		UpdateMesh(pNewImage);
	}catch(...)
	{
		//
	}
	
	pNewImage->Delete();
}

void CDlgSRView::UpdateMesh(vtkImageData *pImage)
{
	float fContour=m_meshOptions.label-0.5;
	COLORREF color=m_meshOptions.color;
	float fOpacity=m_meshOptions.opacity;
	
	int select=0;
	if(select==0)
	{
		vtkContourFilter *pMarchFilter=vtkContourFilter::New();
		pMarchFilter->SetInput(pImage);
		pMarchFilter->ReleaseDataFlagOn();
		pMarchFilter->ComputeNormalsOff();
		pMarchFilter->ComputeScalarsOff();
		pMarchFilter->ComputeGradientsOff();
		pMarchFilter->UseScalarTreeOn();
		pMarchFilter->SetNumberOfContours(1);
		pMarchFilter->SetValue(0,fContour);
		
		vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
		skinMapper->SetInputConnection(pMarchFilter->GetOutputPort());
		skinMapper->ScalarVisibilityOff();
		
		vtkActor *pActor=vtkActor::New();
		pActor->SetMapper(skinMapper);
		pActor->GetProperty()->SetDiffuseColor(1, .49, .25);
		pActor->GetProperty()->SetSpecular(.3);
		pActor->GetProperty()->SetSpecularPower(20);
		pActor->GetProperty()->SetOpacity(fOpacity);
		pActor->GetProperty()->SetShading(1);
		pActor->GetProperty()->SetColor(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
		
		m_pRenderer->AddActor(pActor);
		
		pMarchFilter->Delete();
		skinMapper->Delete();
		pActor->Delete();
		return;
	}

	// VTK Gaussian (because we care about the speed and not so much about
	// precision)
	vtkImageGaussianSmooth *m_VTKGaussianFilter;
	
	// The polygon smoothing filter
	vtkSmoothPolyDataFilter *m_PolygonSmoothingFilter;
	
	// Triangle stripper
	vtkStripper *m_StripperFilter;  
	
	// Marching cubes filter
	vtkImageMarchingCubes *     m_MarchingCubesFilter;
	
	vtkContourFilter *m_ContourFilter;
	// A filter that computes normals
	vtkPolyDataNormals *        m_NormalsFilter;
	
	// The triangle decimation driver
	vtkDecimatePro *            m_DecimateProFilter;

	// Initialize the Gaussian filter
	m_VTKGaussianFilter = vtkImageGaussianSmooth::New();
	m_VTKGaussianFilter->ReleaseDataFlagOn();
  
	// Create and configure a filter for polygon smoothing
	m_PolygonSmoothingFilter = vtkSmoothPolyDataFilter::New();
	m_PolygonSmoothingFilter->ReleaseDataFlagOn();

	// Create and configure a filter for triangle strip generation
	m_StripperFilter = vtkStripper::New();
	m_StripperFilter->ReleaseDataFlagOn();

	// Create and configure the marching cubes filter
	m_MarchingCubesFilter = vtkImageMarchingCubes::New();
	m_MarchingCubesFilter->ReleaseDataFlagOn();
	m_MarchingCubesFilter->ComputeScalarsOff();
	m_MarchingCubesFilter->ComputeGradientsOff();
	m_MarchingCubesFilter->SetNumberOfContours(1);
	m_MarchingCubesFilter->SetValue(0,fContour);

	// Create and configure a filter for triangle decimation
	

	// Create and configure the contour filter
	m_ContourFilter = vtkContourFilter::New();
	m_ContourFilter->ReleaseDataFlagOn();
	m_ContourFilter->ComputeNormalsOff();
	m_ContourFilter->ComputeScalarsOff();
	m_ContourFilter->ComputeGradientsOff();
	m_ContourFilter->UseScalarTreeOn();
	m_ContourFilter->SetNumberOfContours(1);
	m_ContourFilter->SetValue(0,fContour);
	
	// Create and configure the normal computer
	m_NormalsFilter = vtkPolyDataNormals::New();
	m_NormalsFilter->SplittingOff();
	m_NormalsFilter->ConsistencyOff();
	m_NormalsFilter->ReleaseDataFlagOn();

	// Create and configure a filter for triangle decimation
	m_DecimateProFilter = vtkDecimatePro::New();
	m_DecimateProFilter->ReleaseDataFlagOn();

	//配置三角化参数
	// Define the current pipeline end-point
	vtkImageData *pipeImageTail = pImage;
	vtkPolyData *pipePolyTail = NULL;

	// Route the pipeline according to the settings
	// 1. Check if Gaussian smoothing will be used

	if(m_meshOptions.bUseGaussianSmoothing)
    {    
		// The Gaussian filter is enabled
		m_VTKGaussianFilter->SetInput(pipeImageTail);
		pipeImageTail = m_VTKGaussianFilter->GetOutput();

		// Apply parameters to the Gaussian filter
		float sigma = m_meshOptions.fGaussianStandardDeviation;

		// Sigma is in millimeters
		const double *spacing = pImage->GetSpacing();
		m_VTKGaussianFilter->SetStandardDeviation(
			sigma / spacing[0], sigma / spacing[1], sigma / spacing[2]);
		m_VTKGaussianFilter->SetRadiusFactors(
			3 * sigma / spacing[0], 3 * sigma / spacing[1], 3 * sigma / spacing[2]);
    }

	if(m_meshOptions.bUsePatented)
	{
		m_MarchingCubesFilter->SetInput(pipeImageTail);
		pipePolyTail = m_MarchingCubesFilter->GetOutput();
	}else
	{
		m_ContourFilter->SetInput(pipeImageTail);
		pipePolyTail = m_ContourFilter->GetOutput();
	}

	
	// 3. Check if decimation is required
	if(m_meshOptions.bUseDecimation)
    {
		
		
		// Decimate Pro filter gets the pipe tail
		m_DecimateProFilter->SetInput(pipePolyTail);
		pipePolyTail = m_DecimateProFilter->GetOutput();
		
		// Apply parameters to the decimation filter
		m_DecimateProFilter->SetTargetReduction(
			m_meshOptions.fDecimateTargetReduction);
		
		m_DecimateProFilter->SetPreserveTopology(
			m_meshOptions.bDecimatePreserveTopology);
		
		
	}
	if(!m_meshOptions.bUsePatented)
	{
		// 4. Compute the normals (non-patented only)
		m_NormalsFilter->SetInput(pipePolyTail);
		pipePolyTail = m_NormalsFilter->GetOutput();
	}
	

	// 5. Include/exclude mesh smoothing filter
	if(m_meshOptions.bUseMeshSmoothing)
    {
		// Pipe smoothed output into the pipeline
		m_PolygonSmoothingFilter->SetInput(pipePolyTail);
		pipePolyTail = m_PolygonSmoothingFilter->GetOutput();

		// Apply parameters to the mesh smoothing filter
		m_PolygonSmoothingFilter->SetNumberOfIterations(
			m_meshOptions.iMeshSmoothingIterations);

		m_PolygonSmoothingFilter->SetRelaxationFactor(
			m_meshOptions.fMeshSmoothingRelaxationFactor);

		m_PolygonSmoothingFilter->SetFeatureAngle(
			m_meshOptions.fMeshSmoothingFeatureAngle);

		m_PolygonSmoothingFilter->SetFeatureEdgeSmoothing(
			m_meshOptions.bMeshSmoothingFeatureEdgeSmoothing);

		m_PolygonSmoothingFilter->SetBoundarySmoothing(
			m_meshOptions.bMeshSmoothingBoundarySmoothing);

		m_PolygonSmoothingFilter->SetConvergence(
			m_meshOptions.fMeshSmoothingConvergence);
    }

	// 6. Pipe in the final output into the stripper
	m_StripperFilter->SetInput(pipePolyTail);

	vtkPolyDataMapper *isoMapper=vtkPolyDataMapper::New();
	isoMapper->SetInput(m_StripperFilter->GetOutput());
	isoMapper->ScalarVisibilityOff();

	vtkActor *isoActor=vtkActor::New();
	isoActor->SetMapper(isoMapper);

	isoActor->GetProperty()->SetDiffuseColor(1, .49, .25);
	isoActor->GetProperty()->SetSpecular(.3);
	isoActor->GetProperty()->SetSpecularPower(20);
	isoActor->GetProperty()->SetOpacity(fOpacity);
	isoActor->GetProperty()->SetColor(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
	isoActor->GetProperty()->SetShading(1);
	
	m_pRenderer->AddActor(isoActor);

	m_ContourFilter->Delete();	
	isoActor->Delete();
	isoMapper->Delete();
	m_VTKGaussianFilter->Delete();
	m_PolygonSmoothingFilter->Delete();
	m_StripperFilter->Delete();
	m_MarchingCubesFilter->Delete();
	m_NormalsFilter->Delete();
	m_DecimateProFilter->Delete();
	
}

BOOL CDlgSRView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN){   
		switch(pMsg->wParam){   
		case   VK_ESCAPE:   
			 return   TRUE;   
			 break;
		case VK_RETURN:
			return TRUE;
			break;
		}   
	}   
	return CImageViewer::PreTranslateMessage(pMsg);
}

void CDlgSRView::AddMesh(vtkImageData *pImage, MESH_OPTIONS option)
{
	memcpy(&m_meshOptions,&option,sizeof(MESH_OPTIONS));
	UpdateMesh(pImage);
	m_pRenderer->Render();
	m_pRenderer->ResetCamera();
	Invalidate(FALSE);
}

void CDlgSRView::ClearMesh()
{
	m_pRenderer->RemoveAllViewProps();
}

void CDlgSRView::AddActor(vtkActor *pActor)
{
	m_pRenderer->RemoveAllViewProps();

	m_pRenderer->AddActor(pActor);
	m_pRenderer->Render();
	m_pRenderer->ResetCamera();
	Invalidate(FALSE);
}

void CDlgSRView::SetGroundColor(COLORREF color)
{
	m_pRenderer->SetBackground(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
}
