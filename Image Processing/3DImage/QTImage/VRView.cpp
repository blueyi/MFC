// ImageView3D.cpp : implementation file
//

#include "stdafx.h"
#include "VRView.h"
#include "Commands.h"
#include "GlobalHeader.h"
#include "vtkAnnotatedCubeActor.h"
#include "vtkPropAssembly.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVRView dialog
extern CString gsFootPath;

CDlgVRView::CDlgVRView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVRView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVRView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pMFCWindow=NULL;
	
	m_colorTransferFunction=vtkColorTransferFunction::New();
	m_opacityTransferFunction=vtkPiecewiseFunction::New();;
	m_gradOpacityTransferFunction=vtkPiecewiseFunction::New();
	m_volumeMapper=vtkFixedPointVolumeRayCastMapper::New();
	m_textureMapper=vtkOpenGLVolumeTextureMapper3D::New();
	m_volumeProperty=vtkVolumeProperty::New();
	m_volume=vtkVolume::New();

	m_blendingColorTransferFunction=vtkColorTransferFunction::New();
	m_blendingOpacityTransferFunction=vtkPiecewiseFunction::New();
	m_blendingGradOpacityTransferFunction=vtkPiecewiseFunction::New();
	m_blendingVolumeMapper=vtkFixedPointVolumeRayCastMapper::New();
	m_blendingTextureMapper=vtkOpenGLVolumeTextureMapper3D::New();
	m_blendingVolumeProperty=vtkVolumeProperty::New();
	m_blendingVolume=vtkVolume::New();

	m_rayCastCompositeFunction=vtkVolumeRayCastCompositeFunction::New();
	m_rayCastMIPFunction=vtkVolumeRayCastMIPFunction::New();
	m_rayCastMapper=vtkVolumeRayCastMapper::New();
	m_blendingRayCastCompositeFunction=vtkVolumeRayCastCompositeFunction::New();
	m_blendingRayCastMIPFunction=vtkVolumeRayCastMIPFunction::New();
	m_blendingRayCastMapper=vtkVolumeRayCastMapper::New();

	m_pCorAnnotate=vtkCornerAnnotation::New();
	
	m_pImage=NULL;
	m_grayHistogram=NULL;

	
}


void CDlgVRView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVRView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVRView, CDialog)
	//{{AFX_MSG_MAP(CDlgVRView)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_MESSAGE(WM_CALL_COMMAND,OnCallCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVRView message handlers

BOOL CDlgVRView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_pMFCWindow = new vtkMFCWindow(this);
	this->m_pRenderer = vtkRenderer::New();
	this->m_pMFCWindow->GetRenderWindow()->AddRenderer(this->m_pRenderer);
	
	
	m_pInteractor = this->m_pMFCWindow->GetInteractor();
	vtkInteractorStyleTrackballCamera* pStyle = vtkInteractorStyleTrackballCamera::New();
	m_pInteractor->SetInteractorStyle(pStyle);
	pStyle->Delete();
	
	
	m_groundColor=RGB(0,0,0);
	m_pRenderer->SetBackground(0, 0, 0);
    m_pRenderer->ResetCamera(); 
	m_pRenderer->SetRenderWindow(m_pMFCWindow->GetRenderWindow());
	
	vtkObject* pObj = vtkObject::New();
	pObj->GlobalWarningDisplayOff();
	pObj->Delete();

		

	vtkCallbackCommand* callback1 = vtkCallbackCommand::New();
	callback1->SetCallback(MoveMouseCallBack);
	callback1->SetClientData(this);
	m_pInteractor->AddObserver(vtkCommand::MouseMoveEvent,callback1);
	callback1->Delete();

	vtkCallbackCommand* callback2 = vtkCallbackCommand::New();
	callback2->SetCallback(MouseDownCallBack);
	callback2->SetClientData(this);
	m_pInteractor->AddObserver(vtkCommand::LeftButtonPressEvent,callback2);
	callback2->Delete();

	vtkCallbackCommand* callback3 = vtkCallbackCommand::New();
	callback3->SetCallback(KeyPressCallBack);
	callback3->SetClientData(this);
	m_pInteractor->AddObserver(vtkCommand::KeyPressEvent, callback3);
	callback3->Delete();

	vtkCallbackCommand* callback4 = vtkCallbackCommand::New();
	callback4->SetCallback(RenderAbortCheckCallBack);
	callback4->SetClientData(this);
	m_pMFCWindow->GetRenderWindow()->AddObserver(vtkCommand::AbortCheckEvent, callback4);
	callback4->Delete();

	m_pRenderer->AddActor2D(m_pCorAnnotate);
	m_pCorAnnotate->SetText(0,"hello");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgVRView::OnDestroy() 
{
	if(m_grayHistogram) delete []m_grayHistogram;

	m_pCorAnnotate->Delete();

	m_rayCastCompositeFunction->Delete();
	m_rayCastMIPFunction->Delete();
	m_rayCastMapper->Delete();
	m_blendingRayCastCompositeFunction->Delete();
	m_blendingRayCastMIPFunction->Delete();
	m_blendingRayCastMapper->Delete();

	m_colorTransferFunction->Delete();
	m_opacityTransferFunction->Delete();
	m_gradOpacityTransferFunction->Delete();
	m_volumeMapper->Delete();
	m_textureMapper->Delete();
	m_volumeProperty->Delete();
	m_volume->Delete();

	m_blendingColorTransferFunction->Delete();
	m_blendingOpacityTransferFunction->Delete();
	m_blendingGradOpacityTransferFunction->Delete();
	m_blendingVolumeMapper->Delete();
	m_blendingTextureMapper->Delete();
	m_blendingVolumeProperty->Delete();
	m_blendingVolume->Delete();
	

	if (m_pRenderer)
	{
		
		m_pRenderer->RemoveAllObservers();
		m_pRenderer->RemoveAllViewProps();
		m_pRenderer->Delete();
	}
	
	if (m_pMFCWindow)
	{
		m_pMFCWindow->GetRenderWindow()->Finalize();
		delete m_pMFCWindow;
	}

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CDlgVRView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN){   
		switch(pMsg->wParam){   
		case   VK_ESCAPE:   
		case VK_RETURN:
			 return   TRUE;   
			 break;
		}   
	}   

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgVRView::SetVRImage(vtkImageData *pImage)
{
	if(!pImage)
	{
		m_pRenderer->RemoveVolume(m_volume);

		return TRUE;
	}

	m_pImage=pImage;
	UpdateHistogram();

		
	m_volConfig.sampleDistance=1;
	m_volConfig.LOD=1.0;
	m_volConfig.method=VOLRENDER_HARDWARE;
	m_volConfig.renderMode=VOLRENDER_VOLUME;
	m_volConfig.bGradient=FALSE;
	m_volConfig.bShade=FALSE;

	double *pp=m_pImage->GetScalarRange();
	m_volConfig.WindowWidth=pp[1]-pp[0];
	m_volConfig.WindowLevel=pp[0]+m_volConfig.WindowWidth/2;

	/*设置默认颜色和透明度*/
	double dData[2];
	dData[0]=0;
	dData[1]=VRCTRL_PIXELMAXRANGE;
	
	IA_PIXEL_ITEM item;
	m_volConfig.pixelOpacityColorList.RemoveAll();

	item.pixel=dData[0];
	item.opacity=0;
	item.color=RGB(0.3*255,0.3*255,1.0*255);
	m_volConfig.pixelOpacityColorList.AddTail(item);

	item.pixel=dData[0] + (dData[1]-dData[0])*0.25;
	item.opacity=0;
	item.color=RGB(0.3*255,0.3*255,1.0*255);
	m_volConfig.pixelOpacityColorList.AddTail(item);

	item.pixel=dData[0] + (dData[1]-dData[0])*0.5;
	item.opacity=0.2;
	item.color=RGB(0.3*255,1.0*255,0.3*255);
	m_volConfig.pixelOpacityColorList.AddTail(item);

	item.pixel=dData[0] + (dData[1]-dData[0])*0.75;
	item.opacity=0.2;
	item.color=RGB(1.0*255,1.0*255,0.3*255);
	m_volConfig.pixelOpacityColorList.AddTail(item);

	item.pixel=dData[1];
	item.opacity=0.2;
	item.color=RGB(1.0*255,0.3*255,0.3*255);
	m_volConfig.pixelOpacityColorList.AddTail(item);

	m_volConfig.gradOpacityList.RemoveAll();
	item.pixel=0;
	item.opacity=0;
	m_volConfig.gradOpacityList.AddTail(item);
	item.pixel=VRCTRL_GRADIENTRANGE;
	item.opacity=1;
	m_volConfig.gradOpacityList.AddTail(item);

	m_pRenderer->AddVolume(m_volume);
		

	UpdateView();

	m_pRenderer->ResetCamera();
	return TRUE;
}

void CDlgVRView::UpdateHistogram()
{
	if(!m_pImage)
		return;

	int *pDim=m_pImage->GetDimensions();
	unsigned short *pData=(unsigned short *)m_pImage->GetScalarPointer(0,0,0);
	m_pixelMin=9999;
	m_pixelMax=0;
	for(int i=0;i<pDim[0]*pDim[1]*pDim[2];i++)
	{
		unsigned short sData=*(pData+i);
		if(sData<m_pixelMin)
		{
			m_pixelMin=sData;
		}
		if(sData>m_pixelMax)
		{
			m_pixelMax=sData;
		}
	}

	pData=(unsigned short *)m_pImage->GetScalarPointer(0,0,0);
	
	unsigned short dataRange[2];
	dataRange[0]=(unsigned short)m_pixelMin;
	dataRange[1]=(unsigned short)m_pixelMax;

	if(m_grayHistogram) delete []m_grayHistogram;
	m_grayHistogram=new IA_PIXEL_ITEM[dataRange[1]-dataRange[0]+1];
	memset((char*)m_grayHistogram,0,sizeof(IA_PIXEL_ITEM)*(dataRange[1]-dataRange[0]+1));

	for(i=0;i<pDim[0]*pDim[1]*pDim[2];i++)
	{
		unsigned short sData=*(pData+i);
		if(sData<dataRange[0])
		{
			m_grayHistogram[0].pixel=dataRange[0];
			m_grayHistogram[0].count++;
		}else if(sData>dataRange[1])
		{
			m_grayHistogram[dataRange[1]-dataRange[0]].pixel=dataRange[1];
			m_grayHistogram[dataRange[1]-dataRange[0]].count++;
		}else
		{
			m_grayHistogram[sData-dataRange[0]].pixel=sData;
			m_grayHistogram[sData-dataRange[0]].count++;
		}
	}

}

void CDlgVRView::InitialVRActor()
{
	/*设置初始VR参数*/
	m_volConfig.bGradient=FALSE;
	m_volConfig.bShade=FALSE;
	m_volConfig.method=VOLRENDER_HARDWARE;
	m_volConfig.renderMode=VOLRENDER_VOLUME;

	m_colorTransferFunction->AddRGBPoint(     0, 0,0,0);
	m_colorTransferFunction->AddRGBPoint(   255, 1,1,1);
	m_opacityTransferFunction->AddPoint(   0, 0 );
	m_opacityTransferFunction->AddPoint( 255, 1 );
	m_gradOpacityTransferFunction->AddPoint(   0, 0 );
	m_gradOpacityTransferFunction->AddPoint( VRCTRL_GRADIENTRANGE, 1 );

	IA_PIXEL_ITEM item;

	item.pixel=0;
	item.color=RGB(0,0,0);
	item.opacity=0;
	m_volConfig.pixelOpacityColorList.AddTail(item);
	item.pixel=255;
	item.color=RGB(255,255,255);
	item.opacity=1;
	m_volConfig.pixelOpacityColorList.AddTail(item);

	

	item.pixel=0;
	item.opacity=0;
	m_volConfig.gradOpacityList.AddTail(item);
	item.pixel=VRCTRL_GRADIENTRANGE;
	item.opacity=1;
	m_volConfig.gradOpacityList.AddTail(item);
	
	m_volumeProperty->SetColor(m_colorTransferFunction);
	m_volumeProperty->SetScalarOpacity(m_opacityTransferFunction);
	
	m_volumeProperty->SetDiffuse(1.0);
	m_volumeProperty->SetAmbient(.20);
    m_volumeProperty->SetSpecular(0);
    m_volumeProperty->SetSpecularPower(1);
	

	m_volume->SetProperty(m_volumeProperty);

	m_pRenderer->AddVolume(m_volume);

	UpdateView();
}






LRESULT CDlgVRView::OnCallCommand(WPARAM wParam, LPARAM lParam)
{
	CString sPara="";
	int nCmdID = (int)wParam;
	if(lParam)
	{
		sPara=*((CString *)lParam);
	}
	
	switch(nCmdID)
	{
	case CMD_REFRESH_VOLUMERENDING:
		UpdateView();
		break;
	default:
		break;
	
	}

	return 0;
}



void CDlgVRView::RenderAbortCheckCallBack(vtkObject *obj, unsigned long event, void *clientdata, void *calldata)
{
	CDlgVRView* m_pView = reinterpret_cast<CDlgVRView*>( clientdata );
	vtkRenderWindowInteractor* iren = m_pView->m_pInteractor;
	if(m_pView->m_pRenderer->GetRenderWindow()->GetEventPending()!= 0)
	{
        m_pView->m_pRenderer->GetRenderWindow()->SetAbortRender(1);
	}
	
}


void CDlgVRView::KeyPressCallBack(vtkObject *obj, unsigned long event, void *clientdata, void *calldata)
{
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
	CDlgVRView* m_pView = reinterpret_cast<CDlgVRView*>( clientdata );
	char code = iren->GetKeyCode();
	char* cKeysys = iren->GetKeySym();
	
	
	
}


void CDlgVRView::MouseDownCallBack(vtkObject *obj, unsigned long event, void *clientdata, void *calldata)
{
	CDlgVRView* m_pView = reinterpret_cast<CDlgVRView*>( clientdata );
	
}
		
void CDlgVRView::MoveMouseCallBack(vtkObject *obj, unsigned long event, void *clientdata, void *calldata)
{
	CDlgVRView* m_pView = reinterpret_cast<CDlgVRView*>( clientdata );
	
}

void CDlgVRView::UpdateColorOpacity()
{
	short start=m_volConfig.WindowLevel-m_volConfig.WindowWidth/2;
	short end=m_volConfig.WindowLevel+m_volConfig.WindowWidth/2;
	if(start<1)
		start=1;
	if(end>4096)
		end=4096;

	IA_PIXEL_ITEM item;
	short pixel;

	m_colorTransferFunction->RemoveAllPoints();
	m_colorTransferFunction->AddRGBPoint(start-1,GetRValue(m_groundColor)/255.0,
			GetGValue(m_groundColor)/255.0,GetBValue(m_groundColor)/255.0);
	m_colorTransferFunction->AddRGBPoint(end+1,GetRValue(m_groundColor)/255.0,
			GetGValue(m_groundColor)/255.0,GetBValue(m_groundColor)/255.0);

	m_opacityTransferFunction->RemoveAllPoints();
	m_opacityTransferFunction->AddPoint(start-1,0);
	m_opacityTransferFunction->AddPoint(end+1,0);

	POSITION pos=m_volConfig.pixelOpacityColorList.GetHeadPosition();
	while(pos)
	{
		item=m_volConfig.pixelOpacityColorList.GetNext(pos);
		pixel=((end-start)*item.pixel/VRCTRL_PIXELMAXRANGE)+start;
		m_colorTransferFunction->AddRGBPoint(pixel,GetRValue(item.color)/255.0,
			GetGValue(item.color)/255.0,GetBValue(item.color)/255.0);
		m_opacityTransferFunction->AddPoint(pixel,item.opacity);
	}
	
}

BOOL CDlgVRView::OnEraseBkgnd(CDC* pDC)
{

 	return TRUE;
}

void CDlgVRView::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_pMFCWindow)
	{
		m_pMFCWindow->MoveWindow(2, 2, cx-4, cy-4);	
				
	}
}



void CDlgVRView::UpdateGradMethod()
{
	m_gradOpacityTransferFunction->RemoveAllPoints();

	IA_PIXEL_ITEM item;

	
	POSITION pos=m_volConfig.gradOpacityList.GetHeadPosition();
	while(pos)
	{
		item=m_volConfig.gradOpacityList.GetNext(pos);
		m_gradOpacityTransferFunction->AddPoint(item.pixel,item.opacity);
	}

	
}


void CDlgVRView::SetGroundColor(COLORREF color)
{
	m_groundColor=color;

	float r,g,b;
	r=(float)GetRValue(color);
	g=(float)GetGValue(color);
	b=(float)GetBValue(color);
	m_pRenderer->SetBackground(r/255.0, g/255.0, b/255.0);
	Invalidate(FALSE);
}



void CDlgVRView::UpdateView()
{
	UpdateColorOpacity();
	UpdateGradMethod();
	m_volumeProperty->SetColor(m_colorTransferFunction);
	m_volumeProperty->SetScalarOpacity(m_opacityTransferFunction);

	if(m_volConfig.bGradient)
	{
		m_volumeProperty->SetGradientOpacity(m_gradOpacityTransferFunction);
	}else
	{
		m_volumeProperty->SetGradientOpacity(NULL);
	}

	if(m_volConfig.bShade)
	{
		m_volumeProperty->ShadeOn();
	}else
	{
		m_volumeProperty->ShadeOff();
	}

	setEngine(m_volConfig.method);
	setRenderMode(m_volConfig.renderMode);
	
	m_volumeMapper->SetAutoAdjustSampleDistances( 1);
	m_volumeMapper->SetMinimumImageSampleDistance(m_volConfig.LOD);
	m_volumeMapper->SetSampleDistance(m_volConfig.LOD*m_volConfig.sampleDistance);
	m_volumeMapper->SetMaximumImageSampleDistance(m_volConfig.LOD*m_volConfig.lowResLODFactor);
	m_textureMapper->SetSampleDistance(m_volConfig.LOD*m_volConfig.sampleDistance);

	//m_volumeMapper->SetCropping(1);
	//m_volumeMapper->SetCroppingRegionFlagsToSubVolume();
	//m_volumeMapper->SetCroppingRegionPlanes(-100,100,-100,100,-100,100);

	m_rayCastMapper->SetAutoAdjustSampleDistances( 1);
	m_rayCastMapper->SetMinimumImageSampleDistance(m_volConfig.LOD);
	m_rayCastMapper->SetSampleDistance(m_volConfig.LOD*m_volConfig.sampleDistance);
	m_rayCastMapper->SetMaximumImageSampleDistance(m_volConfig.LOD*m_volConfig.lowResLODFactor);

	m_blendingVolumeMapper->SetAutoAdjustSampleDistances( 1);
	m_blendingVolumeMapper->SetMinimumImageSampleDistance(m_volConfig.LOD);
	m_blendingVolumeMapper->SetSampleDistance(m_volConfig.LOD*m_volConfig.sampleDistance);
	m_blendingVolumeMapper->SetMaximumImageSampleDistance(m_volConfig.LOD*m_volConfig.lowResLODFactor);
	m_blendingTextureMapper->SetSampleDistance(m_volConfig.LOD*m_volConfig.sampleDistance);
	
	
	m_volumeProperty->SetInterpolationTypeToLinear();
	m_volume->SetProperty(m_volumeProperty);

	m_pRenderer->AddVolume(m_volume);

	m_pRenderer->Render();
	Invalidate(FALSE);
	
}


void CDlgVRView::setEngine(short engineID)
{

	switch( engineID)
	{
	case 2:   //ray cast
		{
			m_rayCastMapper->SetInput(m_pImage);
			m_volume->SetMapper(m_rayCastMapper);

			m_blendingRayCastMapper->SetInput(m_pImage);
			m_blendingVolume->SetMapper(m_blendingRayCastMapper);
		}
		break;
	case 1:		// FIX POINT
		m_volumeMapper->SetInput(m_pImage);
		m_volume->SetMapper(m_volumeMapper);

		m_blendingVolumeMapper->SetInput(m_pImage);
		m_blendingVolume->SetMapper(m_blendingVolumeMapper);
		break;
			
	case 0:		// TEXTURE
		//if(m_volConfig.renderMode==1)
		{
			m_textureMapper->SetInput(m_pImage);
			m_volume->SetMapper(m_textureMapper);

			m_blendingTextureMapper->SetInput(m_pImage);
			m_blendingVolume->SetMapper(m_blendingTextureMapper);
		}/*else
		{
			m_volumeMapper->SetInput(m_pImage);
			m_volume->SetMapper(m_volumeMapper);

			m_blendingVolumeMapper->SetInput(m_pImage);
			m_blendingVolume->SetMapper(m_blendingVolumeMapper);
		}*/
		break;
	}
		
	
}

void CDlgVRView::setRenderMode(short modeID)
{
		
	switch( modeID)
	{
	case 1:
		m_volumeMapper->SetBlendModeToComposite();
		m_blendingVolumeMapper->SetBlendModeToComposite();
		m_textureMapper->SetBlendModeToComposite();

		m_rayCastCompositeFunction->SetCompositeMethodToInterpolateFirst();
		m_rayCastMapper->SetVolumeRayCastFunction(m_rayCastCompositeFunction);
		break;
		
	case 0:
		m_volumeMapper->SetBlendModeToMaximumIntensity();
		m_blendingVolumeMapper->SetBlendModeToMaximumIntensity();
		m_textureMapper->SetBlendModeToMaximumIntensity();

		m_rayCastMIPFunction->SetMaximizeMethodToOpacity();
		m_rayCastMapper->SetVolumeRayCastFunction(m_rayCastMIPFunction);
		break;
		
	
	}

}






