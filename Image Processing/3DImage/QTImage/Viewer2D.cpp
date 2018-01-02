// Viewer2D.cpp : implementation file
//

#include "stdafx.h"
#include "QTImage.h"
#include "Viewer2D.h"
#include "Commands.h"
#include "DlgContourLine.h"
#include "QTImageDlg.h"
#include "vtkPolyDataConnectivityFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C2DViewer dialog
extern CQTImageDlg* gpMainDlg;

C2DViewer::C2DViewer(CWnd* pParent /*=NULL*/)
	: CImageViewer(C2DViewer::IDD, pParent)
{
	//{{AFX_DATA_INIT(C2DViewer)
	//}}AFX_DATA_INIT
	m_Type=0;
	m_pViewer=NULL;
	m_pImage=NULL;
	m_iCurSlice=-1;
	m_pManager=NULL;
	m_bSelected=FALSE;
	m_pCorAnnotate = vtkCornerAnnotation::New();
}


void C2DViewer::DoDataExchange(CDataExchange* pDX)
{
	CImageViewer::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DViewer)
	DDX_Control(pDX, IDC_SLIDER_SLICE, m_pSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DViewer, CImageViewer)
	//{{AFX_MSG_MAP(C2DViewer)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_CALL_COMMAND,OnCallCommand)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SLICE, OnCustomdrawSliderSlice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DViewer message handlers

void C2DViewer::OnSize(UINT nType, int cx, int cy) 
{
	CImageViewer::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_pSlider.GetSafeHwnd())
	{
		if(m_bEnableSlider)
		{
			m_pSlider.MoveWindow(0,0,cx,25);
		}else
		{
			m_pSlider.MoveWindow(0,0,1,1);
		}
	}
}


LRESULT C2DViewer::OnCallCommand(WPARAM wParam, LPARAM lParam)
{
	CString sPara="";
	int nCmdID = (int)wParam;
	if(lParam)
	{
		sPara=*((CString *)lParam);
	}
	
	switch(nCmdID)
	{
	case CMD_CLEARCONTOUR:
		ClearContour();
		break;
	case CMD_UPDATECONTOURIMAGE:
		UpdateImageContour();
		break;
	default:
		break;
	
	}

	return 0;
}


BOOL C2DViewer::OnInitDialog() 
{
	CImageViewer::OnInitDialog();
	
	// TODO: Add extra initialization here
	vtkInteractorStyleImage *pImageStyle = vtkInteractorStyleImage::New();
	m_pInteractor->SetInteractorStyle(pImageStyle);
	m_pInteractor->GetInteractorStyle()->On();
	pImageStyle->Delete();

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
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C2DViewer::MouseDownCallBack(vtkObject *obj, unsigned long event, void *clientdata, void *calldata)
{
	C2DViewer* m_pView = reinterpret_cast<C2DViewer*>( clientdata );
		
	if (m_pView->m_pViewer)
	{
		POSITION pos=m_pView->m_pList->GetHeadPosition();
		C2DViewer *pView;
		while(pos)
		{
			pView=m_pView->m_pList->GetNext(pos);
			if(pView==m_pView)
			{
				pView->UpdateSelectedStatus(TRUE);
			}else
			{
				pView->UpdateSelectedStatus(FALSE);
			}
		}
	}
}

void C2DViewer::MoveMouseCallBack(vtkObject *obj, unsigned long event, void *clientdata, void *calldata)
{
	C2DViewer* m_pView = reinterpret_cast<C2DViewer*>( clientdata );
	if (m_pView->m_pViewer)
	{
		CString sWindowLevel;
		sWindowLevel.Format("WL:%.0f WW:%.0f",m_pView->m_pViewer->GetColorLevel(),m_pView->m_pViewer->GetColorWindow());
		m_pView->m_pCorAnnotate->SetText(0,sWindowLevel);
		m_pView->Invalidate(FALSE);
	}
	
}

void C2DViewer::SetupImageViewer()
{
	m_pRenderer->RemoveAllViewProps();

	if (!m_pViewer==NULL)
	{
		m_pViewer->Delete();
		m_pViewer = vtkImageViewer2::New();
	}
	else
	{
		m_pViewer = vtkImageViewer2::New();
	}
	
	m_pViewer->SetInput(m_pImage);

	
	m_pCorAnnotate->SetImageActor(m_pViewer->GetImageActor());
	m_pCorAnnotate->ShowSliceAndImageOn();
	vtkTextProperty *tprop = m_pCorAnnotate->GetTextProperty();
	tprop->SetColor(1,1,1);
	tprop->SetFontSize(6);
	tprop->SetFontFamilyToArial();
	m_pRenderer->AddActor2D(m_pCorAnnotate);
	
	m_pViewer->SetRenderWindow(m_pMFCWindow->GetRenderWindow());
	m_pViewer->SetRenderer(m_pRenderer);
	m_pViewer->SetupInteractor(m_pInteractor); 
	
	m_pInteractor->Initialize();
	
	int nMin,nMax;
	m_pViewer->GetSliceRange(nMin,nMax);
	m_iCurSlice=nMax/2;
	m_pSlider.SetPos(m_iCurSlice);
	SetCurImage(m_iCurSlice);

	short min=9999;
	short max=-9999;
	double *pp=m_pImage->GetScalarRange();
	min=pp[0];
	max=pp[1];

	m_pViewer->SetColorWindow(max-min);
	m_pViewer->SetColorLevel(min+(max-min)/2);

	CString sTmp;
	sTmp.Format("WL:%i WW:%i",min+(max-min)/2,max-min);
	m_pCorAnnotate->SetText(0,sTmp);

	m_pRenderer->ResetCamera();

	try
	{
		m_pViewer->Render();
	}catch(...)
	{
		//
	}

		
}

void C2DViewer::SetSeries(vtkImageData *pData)
{
	m_pImage=pData;

	if(m_pImage==NULL || !m_pSlider.GetSafeHwnd())
		return;

	int *pDim=m_pImage->GetDimensions();
	m_pSlider.SetRange(0,pDim[2]-1);
	m_pSlider.SetPageSize(1);
	

	SetupImageViewer();
	
	
}

void C2DViewer::OnDestroy() 
{
	m_pCorAnnotate->Delete();

	if(m_pViewer) m_pViewer->Delete();

	CImageViewer::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void C2DViewer::OnCustomdrawSliderSlice(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i=m_pSlider.GetPos();
	if(m_iCurSlice!=i)
	{
		SetCurImage(i);
	}

	*pResult = 0;
}

void C2DViewer::SetCurImage(int index)
{
	if(m_pViewer==NULL)
		return;

	int nMin,nMax;
	m_pViewer->GetSliceRange(nMin,nMax);
	if(index<nMin)
	{
		index=0;
	}
	if(index>nMax)
	{
		index=nMax;
	}
	if (index>=nMin && index<=nMax)
	{
		m_pViewer->SetSlice(index);
		m_iCurSlice=index;
	}

	CString sTmp=m_pManager->GetName(m_pImage);
	CString sName;
	sName.Format("%s (%i/%i)",sTmp,m_iCurSlice,nMax);
	SetWindowText(sName);

}


void C2DViewer::DisableSlider()
{
	m_bEnableSlider=FALSE;
}

void C2DViewer::ResetWindowLevel()
{
	if(!m_pImage||!m_pViewer)
		return;

	short min=9999;
	short max=-9999;
	double *pp=m_pImage->GetScalarRange();
	min=pp[0];
	max=pp[1];

	m_pViewer->SetColorWindow(max-min);
	m_pViewer->SetColorLevel(min+(max-min)/2);

	CString sTmp;
	sTmp.Format("WL:%i WW:%i",min+(max-min)/2,max-min);
	m_pCorAnnotate->SetText(0,sTmp);
	m_pViewer->Render();
}

void C2DViewer::UpdateSelectedStatus(BOOL bSelected)
{
	if(bSelected!=m_bSelected)
	{
		m_bSelected=bSelected;
		COLORREF color;
		if(m_bSelected)
		{
			color=RGB(26,51,102);
		}else
		{
			color=m_groundColor;
		}

		float r,g,b;
		r=(float)GetRValue(color);
		g=(float)GetGValue(color);
		b=(float)GetBValue(color);
		m_pRenderer->SetBackground(r/255.0, g/255.0, b/255.0);

		CQTImageDlg* pMainDlg = gpMainDlg;
		CDlgContourLine *pDlgContour=pMainDlg->m_pDlgContour;
		CDlgPixelEdit *pDlgPixelEdit=pMainDlg->m_pDlgPixelEdit;
		if(m_bSelected)
		{
			pDlgContour->m_pView=this;
			pDlgPixelEdit->m_pView=this;
			pDlgPixelEdit->UpdateImage();
		}else
		{
			ClearContour();
		}
		Invalidate(FALSE);
	}
}

void C2DViewer::SetGroundColor(COLORREF color)
{
	m_groundColor=color;
	if(!m_bSelected)
	{
		float r,g,b;
		r=(float)GetRValue(color);
		g=(float)GetGValue(color);
		b=(float)GetBValue(color);
		m_pRenderer->SetBackground(r/255.0, g/255.0, b/255.0);
		Invalidate(FALSE);
	}
}

vtkImageData* C2DViewer::GetSeries()
{
	return m_pImage;
}

void C2DViewer::UpdateImageContour()
{
	if(!m_pImage)
		return;

	vtkActor* pActor;
	POSITION pos=m_pContourActorList.GetHeadPosition();
	while(pos)
	{
		pActor=m_pContourActorList.GetNext(pos);
		m_pRenderer->RemoveActor(pActor);
	}
	m_pContourActorList.RemoveAll();

	CList<IA_PIXEL_ITEM,IA_PIXEL_ITEM&> *pList;
	IA_PIXEL_ITEM item;
	CQTImageDlg* pMainDlg = gpMainDlg;
	CDlgContourLine *pDlgContour=pMainDlg->m_pDlgContour;
	pList=&pDlgContour->m_contourList;
	int iCount=pList->GetCount();
	if(iCount<=2)  //等值线数据中两边两个端点无意义
	{
		Invalidate(FALSE);
		return;
	}

	BOOL bLargest=pDlgContour->m_bLargest;
	//准备图像数据
	vtkImageData *pContourImage=vtkImageData::New();
	int *pDim=m_pImage->GetDimensions();
	double *dSpaceing=m_pImage->GetSpacing();
	int iCurIndex=m_pViewer->GetSlice();
	float zValue=iCurIndex*dSpaceing[2]+0.5;
	
	short * m_data = new short [pDim[0]*pDim[1]];	
	short *pData=(short *)m_pImage->GetScalarPointer(0,0,0);
	pData=pData+pDim[0]*pDim[1]*iCurIndex;

	memcpy((char*)m_data,(char*)pData,sizeof(short)*pDim[0]*pDim[1]);
	
	vtkShortArray *array =  vtkShortArray::New();
	array ->SetArray(m_data, pDim[0]*pDim[1],0) ;
	pContourImage->GetPointData()->SetScalars(array);
	pContourImage->SetDimensions(pDim[0],pDim[1],1);
	pContourImage->SetScalarType(VTK_SHORT);
	pContourImage->SetSpacing(dSpaceing[0], dSpaceing[1], dSpaceing[2]);
	pContourImage->SetOrigin(0.0, 0.0, 0.0);
	array->Delete();

	//生成等值线
	for(int i=1;i<iCount-1;i++)
	{
		pos=pList->FindIndex(i);
		if(!pos)
			continue;
		item=pList->GetAt(pos);
		
		vtkContourFilter *pContour=vtkContourFilter::New();
		pContour->SetInput(pContourImage);
		pContour->SetNumberOfContours(1);
		pContour->SetValue(0,item.pixel);


		vtkPolyDataConnectivityFilter *filter1=vtkPolyDataConnectivityFilter::New();
		filter1->SetInput(pContour->GetOutput());
		filter1->SetExtractionModeToLargestRegion();
		

		vtkPolyDataMapper *isoMapper=vtkPolyDataMapper::New();
		if(bLargest)
		{
			isoMapper->SetInput(filter1->GetOutput());
			isoMapper->ScalarVisibilityOff();
			isoMapper->SetScalarRange(filter1->GetOutput()->GetScalarRange());
		}else
		{
			isoMapper->SetInput(pContour->GetOutput());
			isoMapper->ScalarVisibilityOff();
			isoMapper->SetScalarRange(pContour->GetOutput()->GetScalarRange());
		}

		vtkActor *isoActor=vtkActor::New();
		isoActor->SetMapper(isoMapper);
		isoActor->GetProperty()->SetColor(GetRValue(item.color)/255.0,GetGValue(item.color)/255.0,GetBValue(item.color)/255.0);
		isoActor->SetPosition(0,0,zValue);

		m_pRenderer->AddActor(isoActor);
		m_pContourActorList.AddTail(isoActor);
	
		pContour->Delete();
		isoActor->Delete();
		isoMapper->Delete();
		filter1->Delete();
	}
	

	pContourImage->Delete();

	m_pRenderer->Render();	
	Invalidate(FALSE);
}

void C2DViewer::ClearContour()
{
	vtkActor* pActor;
	POSITION pos=m_pContourActorList.GetHeadPosition();
	while(pos)
	{
		pActor=m_pContourActorList.GetNext(pos);
		m_pRenderer->RemoveActor(pActor);
	}
	m_pContourActorList.RemoveAll();

	m_pRenderer->Render();	
	Invalidate(FALSE);
}

int C2DViewer::GetCurIndex()
{
	return m_iCurSlice;
}
