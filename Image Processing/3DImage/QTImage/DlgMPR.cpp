// DlgMPR.cpp : implementation file
//

#include "stdafx.h"
#include "qtimage.h"
#include "DlgMPR.h"
#include "vtkImageReslice.h"
#include "vtkMatrix4x4.h"
#include "DrawSeries.h"
#include "QTImageDlg.h"
#include "ROIManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMPR dialog
extern CQTImageDlg* gpMainDlg;

int  round(double f);

CDlgMPR::CDlgMPR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMPR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMPR)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pImage=NULL;
	
	m_bLBDown=FALSE;

	m_pDlgSR=NULL;
	m_iViewMode=0;

	m_bEnableManualSeg=FALSE;
	m_bEnableCross=TRUE;
	m_pROI=NULL;

	m_bDrawing=NULL;

	m_pntCross1.x=0;
	m_pntCross1.y=0;
}

CDlgMPR::~CDlgMPR()
{
	
	if(m_pDlgSR)
	{
		if(m_pDlgSR->m_hWnd)
		{
			m_pDlgSR->DestroyWindow();
		}
		delete m_pDlgSR;
	}

	if(m_pDlgSeg)
	{
		if(m_pDlgSeg->m_hWnd)
		{
			m_pDlgSeg->DestroyWindow();
		}
		delete m_pDlgSeg;
	}
}

void CDlgMPR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMPR)
	DDX_Control(pDX, IDC_SLIDER_3, m_slider3);
	DDX_Control(pDX, IDC_SLIDER_2, m_slider2);
	DDX_Control(pDX, IDC_SLIDER_1, m_slider1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMPR, CDialog)
	//{{AFX_MSG_MAP(CDlgMPR)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_2, OnCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_3, OnCustomdrawSlider3)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMPR message handlers

BOOL CDlgMPR::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	m_pDlgSR=new CDlgSR(this);
	m_pDlgSR->Create(IDD_IMAGE_SR,this);
	m_pDlgSR->ShowWindow(TRUE);

	m_pDlgSeg=new CDlgSegment(this);
	m_pDlgSeg->Create(IDD_DIALOG_SEGMENT,this);
	m_pDlgSeg->ShowWindow(TRUE);
	m_pDlgSeg->m_pDlgMPR=this;
	m_pDlgSeg->m_pDlgSR=m_pDlgSR;

	CQTImageDlg* pMainDlg = gpMainDlg;
	int x=GetSystemMetrics(SM_CXSCREEN);
	int y=GetSystemMetrics(SM_CYSCREEN);
	CRect rc;
	pMainDlg->GetWindowRect(&rc);
	MoveWindow(0,0,rc.Width(),rc.Height());

	m_memDC1.EnableDrawBack(FALSE);
	m_memDC2.EnableDrawBack(FALSE);
	m_memDC3.EnableDrawBack(FALSE);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgMPR::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(25,40,128));
	
	
 	return TRUE;
}

void CDlgMPR::SetSeries(vtkImageData* pData)
{
	m_pImage=pData;
	if(!m_pImage)
		return;

	int *pDim=m_pImage->GetDimensions();
	m_Dim1[0]=pDim[0];
	m_Dim1[1]=pDim[1];
	m_Dim1[2]=pDim[2];

	m_mSlice1.SetDimension(4,4);
	m_mSlice2.SetDimension(4,4);
	m_mSlice3.SetDimension(4,4);
	m_mSlice1.Identity();
	double *space=m_pImage->GetSpacing();
	m_mSlice1.value[0][0]*=space[0];
	m_mSlice1.value[1][0]*=space[0];
	m_mSlice1.value[2][0]*=space[0];
	m_mSlice1.value[0][1]*=space[1];
	m_mSlice1.value[1][1]*=space[1];
	m_mSlice1.value[2][1]*=space[1];
	m_mSlice1.value[0][2]*=space[2];
	m_mSlice1.value[1][2]*=space[2];
	m_mSlice1.value[2][2]*=space[2];

	Matrix mOld(4,4);
	mOld.Identity();

	
	double dsSagMatrix[16]={0 , 0 , 1 , 0,
		                   1 , 0 , 0  , 0,
						   0 , 1 , 0  , 0,
						   0 , 0 , 0  , 1};
	double dCorMatrix[16]={1 , 0 , 0 , 0,
		                    0 , 0 , -1 , 0,
						    0 , 1 , 0  , 0,
						    0 , 0 , 0  , 1};
		
	vtkMatrix4x4 *resliceAxes = vtkMatrix4x4::New();
	vtkImageReslice *reslice = vtkImageReslice::New();
	vtkImageData *pNewImage;
	Matrix mOri(4,4);

	resliceAxes->DeepCopy(dCorMatrix);
	mOri.value[0][0]=dCorMatrix[0];
	mOri.value[0][1]=dCorMatrix[1];
	mOri.value[0][2]=dCorMatrix[2];
	mOri.value[0][3]=dCorMatrix[3];
	mOri.value[1][0]=dCorMatrix[4];
	mOri.value[1][1]=dCorMatrix[5];
	mOri.value[1][2]=dCorMatrix[6];
	mOri.value[1][3]=dCorMatrix[7];
	mOri.value[2][0]=dCorMatrix[8];
	mOri.value[2][1]=dCorMatrix[9];
	mOri.value[2][2]=dCorMatrix[10];
	mOri.value[2][3]=dCorMatrix[11];
	mOri.value[3][0]=dCorMatrix[12];
	mOri.value[3][1]=dCorMatrix[13];
	mOri.value[3][2]=dCorMatrix[14];
	mOri.value[3][3]=dCorMatrix[15];
		
	reslice->SetInput(m_pImage);
	reslice->SetOutputDimensionality(3);
	reslice->SetResliceAxes(resliceAxes);
	reslice->SetInterpolationModeToCubic();

	pNewImage=reslice->GetOutput();
	reslice->Update();
	pNewImage->UpdateInformation();
	pDim=pNewImage->GetDimensions();
	m_Dim2[0]=pDim[0];
	m_Dim2[1]=pDim[1];
	m_Dim2[2]=pDim[2];
	space=pNewImage->GetSpacing();
	double *origin=pNewImage->GetOrigin();
	CalcMatrix(mOld,mOri,space,origin,m_mSlice2);

	
	resliceAxes->DeepCopy(dsSagMatrix);
	mOri.value[0][0]=dsSagMatrix[0];
	mOri.value[0][1]=dsSagMatrix[1];
	mOri.value[0][2]=dsSagMatrix[2];
	mOri.value[0][3]=dsSagMatrix[3];
	mOri.value[1][0]=dsSagMatrix[4];
	mOri.value[1][1]=dsSagMatrix[5];
	mOri.value[1][2]=dsSagMatrix[6];
	mOri.value[1][3]=dsSagMatrix[7];
	mOri.value[2][0]=dsSagMatrix[8];
	mOri.value[2][1]=dsSagMatrix[9];
	mOri.value[2][2]=dsSagMatrix[10];
	mOri.value[2][3]=dsSagMatrix[11];
	mOri.value[3][0]=dsSagMatrix[12];
	mOri.value[3][1]=dsSagMatrix[13];
	mOri.value[3][2]=dsSagMatrix[14];
	mOri.value[3][3]=dsSagMatrix[15];
		
	reslice->SetResliceAxes(resliceAxes);

	pNewImage=reslice->GetOutput();
	reslice->Update();
	pNewImage->UpdateInformation();
	pDim=pNewImage->GetDimensions();
	m_Dim3[0]=pDim[0];
	m_Dim3[1]=pDim[1];
	m_Dim3[2]=pDim[2];
	space=pNewImage->GetSpacing();
	origin=pNewImage->GetOrigin();
	CalcMatrix(mOld,mOri,space,origin,m_mSlice3);

	
	reslice->Delete();
	resliceAxes->Delete();

	

	
	m_slider1.SetRange(0,m_Dim1[2]-1);
	m_slider1.SetPageSize(1);
	m_iCurSlice1=m_Dim1[2]/2;
	m_slider1.SetPos(m_iCurSlice1);
	

	
	m_slider2.SetRange(0,m_Dim2[2]-1);
	m_slider2.SetPageSize(1);
	m_iCurSlice2=m_Dim2[2]/2;
	m_slider2.SetPos(m_iCurSlice2);

	
	m_slider3.SetRange(0,m_Dim3[2]-1);
	m_slider3.SetPageSize(1);
	m_iCurSlice3=m_Dim3[2]/2;
	m_slider3.SetPos(m_iCurSlice3);
	
	CQTImageDlg* pMainDlg = gpMainDlg;
	CString sName=pMainDlg->m_seriesManager.GetName(m_pImage);
	SetWindowText(sName);

	pMainDlg->m_seriesManager.SetBase(m_pImage,m_mSlice1,m_mSlice2,m_mSlice3);

	m_bkColor=pMainDlg->m_2DBKColor;

	m_pDlgSeg->SetSeries(pData);
	m_pDlgSR->SetSeries(pData);

	DrawROI();

	m_pntCross1.x=0;
	m_pntCross1.y=0;

}

void CDlgMPR::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if(!m_pImage)
		return;
		
	m_memDC1.DrawBack(&dc);
	m_memDC2.DrawBack(&dc);
	m_memDC3.DrawBack(&dc);
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgMPR::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLBDown=TRUE;
	DefineCrossLine(point);
	if(m_bEnableManualSeg)
	{
		int index=-1;
		if(m_rcRealDraw1.PtInRect(point))
		{
			index=1;
		}else if(m_rcRealDraw2.PtInRect(point))
		{
			index=2;
		}else if(m_rcRealDraw3.PtInRect(point))
		{
			index=3;
		}
		
		
		if(index>0 )
		{
			if(m_TempROILine.pntNum==0)
			{
				m_pROI=m_pDlgSeg->GetCurROI();
				m_TempROILine.iImageType=index;
				m_TempROILine.color=m_pROI->GetColor();
			}else
			{
				if(m_TempROILine.iImageType!=index)
				{
					if(m_TempROILine.pntNum>0)
					{
						delete m_TempROILine.pnts;
					}
					m_TempROILine.pntNum=0;
					m_TempROILine.pnts=NULL;
					DrawROI(m_TempROILine.iImageType);
					m_TempROILine.iImageType=index;
				}
			}
		}
		
		
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgMPR::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLBDown=FALSE;
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgMPR::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
	if(!m_bLBDown)
		return;

	if(m_bEnableCross)
	{
		DefineCrossLine(point);
	}

	if(m_bEnableManualSeg)
	{
		int index=-1;
		if(m_rcRealDraw1.PtInRect(point))
		{
			index=1;
		}else if(m_rcRealDraw2.PtInRect(point))
		{
			index=2;
		}else if(m_rcRealDraw3.PtInRect(point))
		{
			index=3;
		}
		if(index!=m_TempROILine.iImageType)
			return;

		ROI_POINT *pnts=new ROI_POINT[m_TempROILine.pntNum+1];
		if(m_TempROILine.pntNum>0)
		{
			memcpy(pnts,m_TempROILine.pnts,sizeof(ROI_POINT)*m_TempROILine.pntNum);
		}
		pnts[m_TempROILine.pntNum].x=point.x;
		pnts[m_TempROILine.pntNum].y=point.y;
		
		delete m_TempROILine.pnts;
		
		m_TempROILine.pntNum++;
		m_TempROILine.pnts=pnts;

		
		if(index==1)
		{
			DrawROI(1);
		}else if(index==2)
		{
			DrawROI(2);
		}else if(index==3)
		{
			DrawROI(3);
		}
			
	}
	
}

void CDlgMPR::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_slider1.GetSafeHwnd())
		return;

	Layout();
}

void CDlgMPR::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i=m_slider1.GetPos();
	if(m_iCurSlice1!=i)
	{
		m_iCurSlice1=i;
		DrawROI(1);
	}

	*pResult = 0;
}

void CDlgMPR::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i=m_slider2.GetPos();
	if(m_iCurSlice2!=i)
	{
		m_iCurSlice2=i;
		DrawROI(2);
	}
	*pResult = 0;
}

void CDlgMPR::OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i=m_slider3.GetPos();
	if(m_iCurSlice3!=i)
	{
		m_iCurSlice3=i;
		DrawROI(3);
		//InvalidateRect(&m_rcSlice3,FALSE);
		//UpdateWindow();
	}
	*pResult = 0;
}

void CDlgMPR::CreateDraw1()
{
	if(!m_pImage)
		return;

	if(!m_memDC1.IsInitialized())
	{
		CClientDC dc(this);
		m_memDC1.LoadDC(&dc,m_rcSlice1);
	}

	CDrawSeries draw;
	draw.SetBKColor(m_bkColor);
	draw.EnableAutoWindowLevel();
	CRect rc;
	rc.left=rc.top=0;
	rc.right=m_rcSlice1.Width();
	rc.bottom=m_rcSlice1.Height();
	draw.Draw(&m_memDC1,rc,m_pImage,m_iCurSlice1,1);
	draw.GetRealDrawRect(m_rcRealDraw1);
	m_rcRealDraw1.OffsetRect(m_rcSlice1.left,m_rcSlice1.top);

	CRect rcTmp(m_rcRealDraw1.left-m_rcSlice1.left,m_rcRealDraw1.top-m_rcSlice1.top,
			m_rcRealDraw1.left-m_rcSlice1.left+m_rcRealDraw1.Width(),
			m_rcRealDraw1.top-m_rcSlice1.top+m_rcRealDraw1.Height());
	draw.Draw(&m_memDC1,rcTmp,m_pImage,m_pDlgSeg->m_pSegmentedImage,m_iCurSlice1,1,0.5,RGB(0,0,0));
	draw.Draw(&m_memDC1,rcTmp,m_pImage,m_pDlgSeg->m_pSegmentingImage,m_iCurSlice1,1,0.5,RGB(0,0,255));

	int x=m_pnt1.x-m_rcSlice1.left;
	int y=m_pnt1.y-m_rcSlice1.top;

	
	m_pntCross1.x=m_Dim1[0]*(m_pnt1.x-m_rcRealDraw1.left)/m_rcRealDraw1.Width();
	m_pntCross1.y=m_Dim1[1]*(m_pnt1.y-m_rcRealDraw1.top)/m_rcRealDraw1.Height();

	CPen penRed(PS_SOLID, 1, RGB(255,0,0));
	CPen* pOldPen = m_memDC1.SelectObject(&penRed);
	
	m_memDC1.MoveTo(0,y);
	m_memDC1.LineTo(m_rcSlice1.Width(),y);
	m_memDC1.MoveTo(x,0);
	m_memDC1.LineTo(x,m_rcSlice1.Height());

	m_memDC1.SelectObject(pOldPen);

	if(m_bEnableManualSeg && m_TempROILine.iImageType==1 && m_TempROILine.pntNum>1)
	{
		CPen penTmp(PS_SOLID, 2, m_TempROILine.color);
		pOldPen = m_memDC1.SelectObject(&penTmp);

		POINT pnt;
		pnt.x=m_TempROILine.pnts[0].x-m_rcSlice1.left;
		pnt.y=m_TempROILine.pnts[0].y-m_rcSlice1.top;
		m_memDC1.MoveTo(pnt);
		for(int i=1;i<m_TempROILine.pntNum;i++)
		{
			pnt.x=m_TempROILine.pnts[i].x-m_rcSlice1.left;
			pnt.y=m_TempROILine.pnts[i].y-m_rcSlice1.top;
			m_memDC1.LineTo(pnt);
		}
		m_memDC1.SelectObject(pOldPen);
	}

	
}

void CDlgMPR::CreateDraw2()
{
	

	if(!m_memDC2.IsInitialized())
	{
		CClientDC dc(this);
		m_memDC2.LoadDC(&dc,m_rcSlice2);
	}

	CDrawSeries draw;
	draw.SetBKColor(m_bkColor);
	draw.EnableAutoWindowLevel();
	CRect rc;
	rc.left=rc.top=0;
	rc.right=m_rcSlice2.Width();
	rc.bottom=m_rcSlice2.Height();
	draw.Draw(&m_memDC2,rc,m_pImage,m_iCurSlice2,2);
	draw.GetRealDrawRect(m_rcRealDraw2);
	m_rcRealDraw2.OffsetRect(m_rcSlice2.left,m_rcSlice2.top);

	CRect rcTmp(m_rcRealDraw2.left-m_rcSlice2.left,m_rcRealDraw2.top-m_rcSlice2.top,
			m_rcRealDraw2.left-m_rcSlice2.left+m_rcRealDraw2.Width(),
			m_rcRealDraw2.top-m_rcSlice2.top+m_rcRealDraw2.Height());
	draw.Draw(&m_memDC2,rcTmp,m_pImage,m_pDlgSeg->m_pSegmentedImage,m_iCurSlice2,2,0.5,RGB(0,0,0));
	draw.Draw(&m_memDC2,rcTmp,m_pImage,m_pDlgSeg->m_pSegmentingImage,m_iCurSlice2,2,0.5,RGB(0,0,255));

	int x=m_pnt2.x-m_rcSlice2.left;
	int y=m_pnt2.y-m_rcSlice2.top;

	CPen penRed(PS_SOLID, 1, RGB(255,0,0));
	CPen* pOldPen = m_memDC2.SelectObject(&penRed);
	
	m_memDC2.MoveTo(0,y);
	m_memDC2.LineTo(m_rcSlice2.Width(),y);
	m_memDC2.MoveTo(x,0);
	m_memDC2.LineTo(x,m_rcSlice2.Height());

	m_memDC2.SelectObject(pOldPen);

	if(m_bEnableManualSeg &&  m_TempROILine.iImageType==2 && m_TempROILine.pntNum>1)
	{
		CPen penTmp(PS_SOLID, 2, m_TempROILine.color);
		pOldPen = m_memDC2.SelectObject(&penTmp);

		POINT pnt;
		pnt.x=m_TempROILine.pnts[0].x-m_rcSlice2.left;
		pnt.y=m_TempROILine.pnts[0].y-m_rcSlice2.top;
		m_memDC2.MoveTo(pnt);
		for(int i=1;i<m_TempROILine.pntNum;i++)
		{
			pnt.x=m_TempROILine.pnts[i].x-m_rcSlice2.left;
			pnt.y=m_TempROILine.pnts[i].y-m_rcSlice2.top;
			m_memDC2.LineTo(pnt);
		}
		m_memDC2.SelectObject(pOldPen);
	}
}


void CDlgMPR::CreateDraw3()
{
	

	if(!m_memDC3.IsInitialized())
	{
		CClientDC dc(this);
		m_memDC3.LoadDC(&dc,m_rcSlice3);
	}

	CDrawSeries draw;
	draw.SetBKColor(m_bkColor);
	draw.EnableAutoWindowLevel();
	CRect rc;
	rc.left=rc.top=0;
	rc.right=m_rcSlice3.Width();
	rc.bottom=m_rcSlice3.Height();
	draw.Draw(&m_memDC3,rc,m_pImage,m_iCurSlice3,3);
	draw.GetRealDrawRect(m_rcRealDraw3);
	m_rcRealDraw3.OffsetRect(m_rcSlice3.left,m_rcSlice3.top);

	CRect rcTmp(m_rcRealDraw3.left-m_rcSlice3.left,m_rcRealDraw3.top-m_rcSlice3.top,
			m_rcRealDraw3.left-m_rcSlice3.left+m_rcRealDraw3.Width(),
			m_rcRealDraw3.top-m_rcSlice3.top+m_rcRealDraw3.Height());
	draw.Draw(&m_memDC3,rcTmp,m_pImage,m_pDlgSeg->m_pSegmentedImage,m_iCurSlice3,3,0.5,RGB(0,0,0));
	draw.Draw(&m_memDC3,rcTmp,m_pImage,m_pDlgSeg->m_pSegmentingImage,m_iCurSlice3,3,0.5,RGB(0,0,255));

	int x=m_pnt3.x-m_rcSlice3.left;
	int y=m_pnt3.y-m_rcSlice3.top;

	CPen penRed(PS_SOLID, 1, RGB(255,0,0));
	CPen* pOldPen = m_memDC3.SelectObject(&penRed);
	
	m_memDC3.MoveTo(0,y);
	m_memDC3.LineTo(m_rcSlice3.Width(),y);
	m_memDC3.MoveTo(x,0);
	m_memDC3.LineTo(x,m_rcSlice3.Height());

	m_memDC3.SelectObject(pOldPen);

	if(m_bEnableManualSeg &&  m_TempROILine.iImageType==3 && m_TempROILine.pntNum>1)
	{
		CPen penTmp(PS_SOLID, 2, m_TempROILine.color);
		pOldPen = m_memDC3.SelectObject(&penTmp);

		POINT pnt;
		pnt.x=m_TempROILine.pnts[0].x-m_rcSlice3.left;
		pnt.y=m_TempROILine.pnts[0].y-m_rcSlice3.top;
		m_memDC3.MoveTo(pnt);
		for(int i=1;i<m_TempROILine.pntNum;i++)
		{
			pnt.x=m_TempROILine.pnts[i].x-m_rcSlice3.left;
			pnt.y=m_TempROILine.pnts[i].y-m_rcSlice3.top;
			m_memDC3.LineTo(pnt);
		}
		m_memDC3.SelectObject(pOldPen);
	}
}


void CDlgMPR::CalcMatrix(Matrix mOld, Matrix mOri, double *space, double *origin,Matrix &mNewImage)
{
		
	Matrix mOldImage(4,4);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			mOldImage.value[i][j]=mOld.value[i][j];
			mNewImage.value[i][j]=mOri.value[i][j];
		}
	}
	mNewImage.value[0][3]=0;
	mNewImage.value[1][3]=0;
	mNewImage.value[2][3]=0;

	mOldImage=mOldImage*mNewImage;
	
	mNewImage.value[0][0]=1;
	mNewImage.value[0][1]=0;
	mNewImage.value[0][2]=0;
	mNewImage.value[0][3]=origin[0];
	mNewImage.value[1][0]=0;
	mNewImage.value[1][1]=1;
	mNewImage.value[1][2]=0;
	mNewImage.value[1][3]=origin[1];
	mNewImage.value[2][0]=0;
	mNewImage.value[2][1]=0;
	mNewImage.value[2][2]=1;
	mNewImage.value[2][3]=origin[2];
	mNewImage.value[3][0]=0;
	mNewImage.value[3][1]=0;
	mNewImage.value[3][2]=0;
	mNewImage.value[3][3]=1;

	mNewImage=mOldImage*mNewImage;
	
	Vector vNorm;
	vNorm.value[0]=mNewImage.value[0][0];
	vNorm.value[1]=mNewImage.value[1][0];
	vNorm.value[2]=mNewImage.value[2][0];
	vNorm=vNorm.Normalize();
	mNewImage.value[0][0]=vNorm.value[0]*space[0];
	mNewImage.value[1][0]=vNorm.value[1]*space[0];
	mNewImage.value[2][0]=vNorm.value[2]*space[0];
	vNorm.value[0]=mNewImage.value[0][1];
	vNorm.value[1]=mNewImage.value[1][1];
	vNorm.value[2]=mNewImage.value[2][1];
	vNorm=vNorm.Normalize();
	mNewImage.value[0][1]=vNorm.value[0]*space[1];
	mNewImage.value[1][1]=vNorm.value[1]*space[1];
	mNewImage.value[2][1]=vNorm.value[2]*space[1];
	vNorm.value[0]=mNewImage.value[0][2];
	vNorm.value[1]=mNewImage.value[1][2];
	vNorm.value[2]=mNewImage.value[2][2];
	vNorm=vNorm.Normalize();
	mNewImage.value[0][2]=vNorm.value[0]*space[2];
	mNewImage.value[1][2]=vNorm.value[1]*space[2];
	mNewImage.value[2][2]=vNorm.value[2]*space[2];

}

void CDlgMPR::DefineCrossLine(CPoint point)
{
	if(!m_bEnableCross)
	{
		return;
	}

	int pDim1[3]={m_Dim1[0],m_Dim1[1],m_Dim1[2]};
	int pDim2[3]={m_Dim2[0],m_Dim2[1],m_Dim2[2]};
	int pDim3[3]={m_Dim3[0],m_Dim3[1],m_Dim3[2]};

	if(m_rcRealDraw1.PtInRect(point))
	{
		m_pnt1.x=point.x;
		m_pnt1.y=point.y;
		

		Vector v(4),vNew(4);
		v.value[0]=pDim1[0] * (point.x-m_rcRealDraw1.left)/m_rcRealDraw1.Width();
		v.value[1]=pDim1[1] * (point.y-m_rcRealDraw1.top)/m_rcRealDraw1.Height();
		v.value[2]=m_iCurSlice1;
		v.value[3]=1;

		v=m_mSlice1 * v;

		Matrix m=m_mSlice2.Inverse();
		vNew=m * v;

		m_pnt2.x=m_rcRealDraw2.Width() * vNew.value[0]/pDim2[0]+m_rcRealDraw2.left;
		m_pnt2.y=m_rcRealDraw2.Height() * vNew.value[1]/pDim2[1]+m_rcRealDraw2.top;
		m_iCurSlice2= vNew.value[2];
		m_slider2.SetPos(m_iCurSlice2);
		

		m=m_mSlice3.Inverse();
		vNew=m * v;

		m_pnt3.x=m_rcRealDraw3.Width() * vNew.value[0]/pDim3[0]+m_rcRealDraw3.left;
		m_pnt3.y=m_rcRealDraw3.Height() * vNew.value[1]/pDim3[1]+m_rcRealDraw3.top;
		m_iCurSlice3= vNew.value[2];
		m_slider3.SetPos(m_iCurSlice3);
		DrawROI();
	}else if(m_rcRealDraw2.PtInRect(point))
	{
		m_pnt2.x=point.x;
		m_pnt2.y=point.y;
		

		Vector v(4),vNew(4);
		v.value[0]=pDim2[0] * (point.x-m_rcRealDraw2.left)/m_rcRealDraw2.Width();
		v.value[1]=pDim2[1] * (point.y-m_rcRealDraw2.top)/m_rcRealDraw2.Height();
		v.value[2]=m_iCurSlice2;
		v.value[3]=1;

		v=m_mSlice2 * v;

		Matrix m=m_mSlice1.Inverse();
		vNew=m * v;

		m_pnt1.x=m_rcRealDraw1.Width() * vNew.value[0]/pDim1[0]+m_rcRealDraw1.left;
		m_pnt1.y=m_rcRealDraw1.Height() * vNew.value[1]/pDim1[1]+m_rcRealDraw1.top;
		m_iCurSlice1= vNew.value[2];
		m_slider1.SetPos(m_iCurSlice1);
		

		m=m_mSlice3.Inverse();
		vNew=m * v;

		m_pnt3.x=m_rcRealDraw3.Width() * vNew.value[0]/pDim3[0]+m_rcRealDraw3.left;
		m_pnt3.y=m_rcRealDraw3.Height() * vNew.value[1]/pDim3[1]+m_rcRealDraw3.top;
		m_iCurSlice3= vNew.value[2];
		m_slider3.SetPos(m_iCurSlice3);
		DrawROI();
	}else if(m_rcRealDraw3.PtInRect(point))
	{
		m_pnt3.x=point.x;
		m_pnt3.y=point.y;
		

		Vector v(4),vNew(4);
		v.value[0]=pDim3[0] * (point.x-m_rcRealDraw3.left)/m_rcRealDraw3.Width();
		v.value[1]=pDim3[1] * (point.y-m_rcRealDraw3.top)/m_rcRealDraw3.Height();
		v.value[2]=m_iCurSlice3;
		v.value[3]=1;

		v=m_mSlice3 * v;

		Matrix m=m_mSlice1.Inverse();
		vNew=m * v;

		m_pnt1.x=m_rcRealDraw1.Width() * vNew.value[0]/pDim1[0]+m_rcRealDraw1.left;
		m_pnt1.y=m_rcRealDraw1.Height() * vNew.value[1]/pDim1[1]+m_rcRealDraw1.top;
		m_iCurSlice1= vNew.value[2];
		m_slider1.SetPos(m_iCurSlice1);
		

		m=m_mSlice2.Inverse();
		vNew=m * v;

		m_pnt2.x=m_rcRealDraw2.Width() * vNew.value[0]/pDim2[0]+m_rcRealDraw2.left;
		m_pnt2.y=m_rcRealDraw2.Height() * vNew.value[1]/pDim2[1]+m_rcRealDraw2.top;
		m_iCurSlice2= vNew.value[2];
		m_slider2.SetPos(m_iCurSlice2);
		DrawROI();
	}
}

void CDlgMPR::Layout()
{
	CRect rc;
	GetClientRect(&rc);
	int iWidth;
	int iHeight;
	if(m_iViewMode==0)
	{
		iWidth=rc.Width()/3;
		CRect rcDraw(iWidth-28,0,iWidth-2,rc.Height());
		m_slider1.MoveWindow(rcDraw);

		rcDraw.left+=iWidth;
		rcDraw.right+=iWidth;
		m_slider2.MoveWindow(rcDraw);

		rcDraw.left+=iWidth;
		rcDraw.right+=iWidth;
		m_slider3.MoveWindow(rcDraw);

		rcDraw.left=0;
		rcDraw.top=0;
		rcDraw.right=iWidth-30;
		rcDraw.bottom=rc.Height();
		m_rcSlice1=rcDraw;

		rcDraw.left+=iWidth;
		rcDraw.right+=iWidth;
		m_rcSlice2=rcDraw;

		rcDraw.left+=iWidth;
		rcDraw.right+=iWidth;
		m_rcSlice3=rcDraw;

		m_pDlgSR->MoveWindow(0,0,1,1);
		m_pDlgSeg->MoveWindow(0,0,1,1);
		
	}else
	{
		int iLeft=300;
		rc.left=iLeft;
		iWidth=rc.Width()/2;
		iHeight=rc.Height()/2-2;
		CRect rcDraw(iLeft+iWidth-28,0,iLeft+iWidth-3,iHeight);
		m_slider1.MoveWindow(rcDraw);

		rcDraw.left+=iWidth;
		rcDraw.right+=iWidth;
		m_slider2.MoveWindow(rcDraw);

		rcDraw.top+=iHeight+2;
		rcDraw.bottom+=iHeight+2;
		m_slider3.MoveWindow(rcDraw);

		rcDraw.left=iLeft;
		rcDraw.top=0;
		rcDraw.right=iLeft+iWidth-30;
		rcDraw.bottom=iHeight;
		m_rcSlice1=rcDraw;

		rcDraw.left+=iWidth;
		rcDraw.right+=iWidth;
		m_rcSlice2=rcDraw;

		rcDraw.top+=iHeight+2;
		rcDraw.bottom+=iHeight+2;
		m_rcSlice3=rcDraw;

		rcDraw.left-=iWidth;
		rcDraw.right=rcDraw.right-iWidth+28;
		m_pDlgSR->MoveWindow(rcDraw);

		m_pDlgSeg->MoveWindow(0,0,iLeft,rc.Height());
		
	}

	m_memDC1.ClearDC();
	m_memDC2.ClearDC();
	m_memDC3.ClearDC();
	DrawROI();
}

void CDlgMPR::EnableCross(BOOL bEnable)
{
	m_bEnableCross=bEnable;
	if(m_TempROILine.pntNum>0)
	{
		delete m_TempROILine.pnts;
	}
	m_TempROILine.pntNum=0;
	m_TempROILine.pnts=NULL;
}

void CDlgMPR::EnableManualSeg(BOOL bEnable)
{
	m_bEnableManualSeg=bEnable;

	if(m_TempROILine.pntNum>0)
	{
		delete m_TempROILine.pnts;
	}
	m_TempROILine.pntNum=0;
	m_TempROILine.pnts=NULL;
}

void CDlgMPR::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bEnableManualSeg)
	{
		int index=-1;
		if(m_rcRealDraw1.PtInRect(point))
		{
			index=1;
		}else if(m_rcRealDraw2.PtInRect(point))
		{
			index=2;
		}else if(m_rcRealDraw3.PtInRect(point))
		{
			index=3;
		}
		if(index!=m_TempROILine.iImageType)
			return;

		if(m_TempROILine.pntNum>0)
		{
			delete m_TempROILine.pnts;
		}
		m_TempROILine.pntNum=0;
		m_TempROILine.pnts=NULL;

		
		DrawROI(index);
	}

	CDialog::OnRButtonUp(nFlags, point);
}



void CDlgMPR::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bEnableManualSeg)
	{
		int pDim1[3]={m_Dim1[0],m_Dim1[1],m_Dim1[2]};
		int pDim2[3]={m_Dim2[0],m_Dim2[1],m_Dim2[2]};
		int pDim3[3]={m_Dim3[0],m_Dim3[1],m_Dim3[2]};

		int index=-1;
		CRect rcRealDraw;
		int dim[2];
		if(m_rcRealDraw1.PtInRect(point))
		{
			index=1;
			rcRealDraw.left=m_rcRealDraw1.left;
			rcRealDraw.top=m_rcRealDraw1.top;
			rcRealDraw.right=m_rcRealDraw1.right;
			rcRealDraw.bottom=m_rcRealDraw1.bottom;
			dim[0]=pDim1[0];
			dim[1]=pDim1[1];
		}else if(m_rcRealDraw2.PtInRect(point))
		{
			index=2;
			rcRealDraw.left=m_rcRealDraw2.left;
			rcRealDraw.top=m_rcRealDraw2.top;
			rcRealDraw.right=m_rcRealDraw2.right;
			rcRealDraw.bottom=m_rcRealDraw2.bottom;
			dim[0]=pDim2[0];
			dim[1]=pDim2[1];
		}else if(m_rcRealDraw3.PtInRect(point))
		{
			index=3;
			rcRealDraw.left=m_rcRealDraw3.left;
			rcRealDraw.top=m_rcRealDraw3.top;
			rcRealDraw.right=m_rcRealDraw3.right;
			rcRealDraw.bottom=m_rcRealDraw3.bottom;
			dim[0]=pDim3[0];
			dim[1]=pDim3[1];
		}
		
		
		if(index>0 && m_TempROILine.pntNum>3 && 
			m_TempROILine.iImageType==index)
		{
			m_pROI=m_pDlgSeg->GetCurROI();
			ROI *pROI=m_pROI->AddROI();
			pROI->pntNum=m_TempROILine.pntNum;
			pROI->pnts=new ROI_POINT[pROI->pntNum];
			pROI->bounds[0]=pROI->bounds[2]=pROI->bounds[4]=5000;
			pROI->bounds[1]=pROI->bounds[3]=pROI->bounds[5]=-5000;

			for(int i=0;i<pROI->pntNum;i++)
			{
				pROI->pnts[i].x=dim[0] * (m_TempROILine.pnts[i].x-rcRealDraw.left)/rcRealDraw.Width();
				pROI->pnts[i].y=dim[1] * (m_TempROILine.pnts[i].y-rcRealDraw.top)/rcRealDraw.Height();
				if(pROI->bounds[0]>pROI->pnts[i].x)
				{
					pROI->bounds[0]=pROI->pnts[i].x;
				}
				if(pROI->bounds[1]<pROI->pnts[i].x)
				{
					pROI->bounds[1]=pROI->pnts[i].x;
				}
				if(pROI->bounds[2]>pROI->pnts[i].y)
				{
					pROI->bounds[2]=pROI->pnts[i].y;
				}
				if(pROI->bounds[3]<pROI->pnts[i].y)
				{
					pROI->bounds[3]=pROI->pnts[i].y;
				}
			}
			pROI->color=m_pROI->GetColor();
			pROI->alpha=m_pROI->GetOpacity()/255.0;
			Matrix m=m_mSlice1.Inverse();
			if(index==1)
			{
				pROI->iImageIndex=m_iCurSlice1;
				
				pROI->bounds[4]=m_iCurSlice1;
				pROI->bounds[5]=m_iCurSlice1;
			}else if(index==2)
			{
				pROI->iImageIndex=m_iCurSlice2;

				Vector v(4);
				v.value[0]=pROI->bounds[0];
				v.value[1]=pROI->bounds[2];
				v.value[2]=pROI->iImageIndex;
				v.value[3]=1;
				v=m * m_mSlice2 * v;
				pROI->bounds[0]=round(v.value[0]);
				pROI->bounds[2]=round(v.value[1]);
				pROI->bounds[4]=round(v.value[2]);

				v.value[0]=pROI->bounds[1];
				v.value[1]=pROI->bounds[3];
				v.value[2]=pROI->iImageIndex;
				v.value[3]=1;
				v=m * m_mSlice2 * v;
				pROI->bounds[1]=round(v.value[0]);
				pROI->bounds[3]=round(v.value[1]);
				pROI->bounds[5]=round(v.value[2]);
			}else
			{
				pROI->iImageIndex=m_iCurSlice3;

				Vector v(4);
				v.value[0]=pROI->bounds[0];
				v.value[1]=pROI->bounds[2];
				v.value[2]=pROI->iImageIndex;
				v.value[3]=1;
				v=m * m_mSlice3 * v;
				pROI->bounds[0]=round(v.value[0]);
				pROI->bounds[2]=round(v.value[1]);
				pROI->bounds[4]=round(v.value[2]);

				v.value[0]=pROI->bounds[1];
				v.value[1]=pROI->bounds[3];
				v.value[2]=pROI->iImageIndex;
				v.value[3]=1;
				v=m * m_mSlice3 * v;
				pROI->bounds[1]=round(v.value[0]);
				pROI->bounds[3]=round(v.value[1]);
				pROI->bounds[5]=round(v.value[2]);
			}
			pROI->iImageType=index;		
			
			unsigned short *pData=(unsigned short *)m_pDlgSeg->m_pSegmentedImage->GetScalarPointer(0,0,0);
					
			for(int x=pROI->bounds[0];x<=pROI->bounds[1];x++)
			{
				for(int y=pROI->bounds[2];y<=pROI->bounds[3];y++)
				{
					for(int z=pROI->bounds[4];z<=pROI->bounds[5];z++)
					{
						if(m_pROI->PtInRegion(x,y,z,pROI))
						{
							pData[z*pDim1[0]*pDim1[1]+y*pDim1[0]+x]=m_pROI->GetLabel();
						}
					}
				}
			}
			
		}

		if(index>0 && m_TempROILine.iImageType==index)
		{
			if(m_TempROILine.pntNum>0)
			{
				delete m_TempROILine.pnts;
			}
			m_TempROILine.pntNum=0;
			m_TempROILine.pnts=NULL;

			DrawROI(index);
		}
		
		
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CDlgMPR::DrawROI(int imageType/*=0*/)
{
	if(m_bDrawing || !m_pImage)
		return;

	m_bDrawing=TRUE;

	CROI *pROI;
	if(imageType==1 || imageType==0)
	{
		CreateDraw1();
		CRect rc(m_rcRealDraw1.left-m_rcSlice1.left,m_rcRealDraw1.top-m_rcSlice1.top,
			m_rcRealDraw1.left-m_rcSlice1.left+m_rcRealDraw1.Width(),
			m_rcRealDraw1.top-m_rcSlice1.top+m_rcRealDraw1.Height());
		for(int i=0;i<m_pDlgSeg->GetROICount();i++)
		{
			pROI=m_pDlgSeg->GetROIAt(i);
			//pROI->DrawROI(&m_memDC1,rc,1,m_iCurSlice1);
		}
		InvalidateRect(&m_rcSlice1,FALSE);
	}
	if(imageType==2 || imageType==0)
	{
		CreateDraw2();
		CRect rc(m_rcRealDraw2.left-m_rcSlice2.left,m_rcRealDraw2.top-m_rcSlice2.top,
			m_rcRealDraw2.left-m_rcSlice2.left+m_rcRealDraw2.Width(),
			m_rcRealDraw2.top-m_rcSlice2.top+m_rcRealDraw2.Height());
		for(int i=0;i<m_pDlgSeg->GetROICount();i++)
		{
			pROI=m_pDlgSeg->GetROIAt(i);
			//pROI->DrawROI(&m_memDC2,rc,2,m_iCurSlice2);
		}
		InvalidateRect(&m_rcSlice2,FALSE);
	}
	if(imageType==3 || imageType==0)
	{
		CreateDraw3();
		CRect rc(m_rcRealDraw3.left-m_rcSlice3.left,m_rcRealDraw3.top-m_rcSlice3.top,
			m_rcRealDraw3.left-m_rcSlice3.left+m_rcRealDraw3.Width(),
			m_rcRealDraw3.top-m_rcSlice3.top+m_rcRealDraw3.Height());
		for(int i=0;i<m_pDlgSeg->GetROICount();i++)
		{
			pROI=m_pDlgSeg->GetROIAt(i);
			//pROI->DrawROI(&m_memDC3,rc,3,m_iCurSlice3);
		}
		InvalidateRect(&m_rcSlice3,FALSE);
	}
	UpdateWindow();

	m_bDrawing=FALSE;
}

BOOL CDlgMPR::PreTranslateMessage(MSG* pMsg) 
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
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgMPR::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->m_pDlgSeg->Clear();
	CDialog::OnClose();
}
