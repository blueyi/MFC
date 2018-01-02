// QTImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QTImage.h"
#include "QTImageDlg.h"
#include "Viewer2D.h"
#include "DlgMPR.h"
#include "Points2Mesh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQTImageDlg dialog
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CString g_sProgramPath;
CQTImageDlg* gpMainDlg;

void gUpdateProgress(void *info, float progress, const char *msg)
{

	CQTImageDlg* pMainDlg = gpMainDlg;
	CString sTmp;
	if(progress>0.0 && progress<=0.99)
	{
		sTmp.Format("%s %.0f",msg,progress*100);
	}else
	{
		sTmp.Format("%s",msg);
	}
	
	pMainDlg->SendMessage(WM_SETMESSAGESTRING,WPARAM(&sTmp),NULL);
}

CQTImageDlg::CQTImageDlg(CWnd* pParent /*=NULL*/)
	: CDialogSampleDlgBase(CQTImageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQTImageDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		
	
	CString m_strStylesPath = szStylesPath;
	int nIndex  = m_strStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		m_strStylesPath = m_strStylesPath.Left(nIndex);
	}
	else {
		m_strStylesPath.Empty();
	}
	m_strStylesPath += _T("\\");

	g_sProgramPath.Format("%s",m_strStylesPath);
	
	XTPSkinManager()->LoadSkin(m_strStylesPath + _T("neXpro.msstyles"));


	m_rcBorders.SetRectEmpty();
	m_bInRepositionControls = FALSE;
	m_bInitDone = FALSE;

	m_pVRDlg=NULL;
	m_pDlgContour=NULL;
	m_pDlgPixelEdit=NULL;
	m_pDlgMPR=NULL;

	m_2DBKColor=RGB(0,0,0);
	
}

CQTImageDlg::~CQTImageDlg()
{
	if(m_pVRDlg)
	{
		if(m_pVRDlg->m_hWnd)
		{
			m_pVRDlg->DestroyWindow();
		}
		delete m_pVRDlg;
	}

	if(m_pDlgContour)
	{
		if(m_pDlgContour->m_hWnd)
		{
			m_pDlgContour->DestroyWindow();
		}
		delete m_pDlgContour;
	}
	
	if(m_pDlgPixelEdit)
	{
		if(m_pDlgPixelEdit->m_hWnd)
		{
			m_pDlgPixelEdit->DestroyWindow();
		}
		delete m_pDlgPixelEdit;
	}

	if(m_pDlgMPR)
	{
		if(m_pDlgMPR->m_hWnd)
		{
			m_pDlgMPR->DestroyWindow();
		}
		delete m_pDlgMPR;
	}
			
}

void CQTImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSampleDlgBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQTImageDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQTImageDlg, CDialogSampleDlgBase)
	//{{AFX_MSG_MAP(CQTImageDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMsgString)
	ON_MESSAGE(WM_SHOW_SERIES,OnShowSeries)
	ON_COMMAND(IDM_FILE_IMPORT_SERIES, OnFileImportSeries)
	ON_COMMAND(IDM_FILE_EXIT, OnFileExit)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW3D_VOL_RENDER, OnView3dVolRender)
	ON_COMMAND(ID_VIEW3D_GROUND_COLOR, OnView3dGroundColor)
	ON_COMMAND(ID_VIEW2D_GROUND_COLOR, OnView2dGroundColor)
	ON_COMMAND(IDM_FILE_SAVE_SERIES, OnFileSaveSeries)
	ON_COMMAND(ID_VIEW2D_RESET_WINDOWLEVEL, OnView2dResetWindowlevel)
	ON_COMMAND(ID_VIEW2D_CONTOURLINE, OnView2dContourline)
	ON_COMMAND(ID_EDIT_PIXELEDIT, OnEditPixel)
	ON_COMMAND(ID_VIEW2D_MPR, OnView2dMpr)
	ON_COMMAND(ID_ROI_SEGMENT, OnRoiSegment)
	ON_COMMAND(ID_VIEW3D_DELAUNAY, OnView3dDelaunay)
	ON_COMMAND(ID_VIEW3D_POWERCRUST, OnView3dPowercrust)
	ON_COMMAND(ID_VIEW3D_SOLID_SURFACE, OnView3dSolidSurface)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQTImageDlg message handlers

LRESULT CQTImageDlg::OnShowSeries(WPARAM wParam, LPARAM lParam)
{
	vtkImageData *pImage=(vtkImageData *)wParam;
	
	m_view2DManager.ShowSeries(pImage);

	return 0;
}


LRESULT CQTImageDlg::OnSetMsgString(WPARAM wParam, LPARAM lParam)
{
	CString strMessage=*((CString *)wParam);
	
	m_wndStatusBar.SetWindowText(strMessage);
	return 0;
}

BOOL CQTImageDlg::OnInitDialog()
{
	SetFlag(xtResizeNoSizeIcon);

	CDialogSampleDlgBase::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	gpMainDlg=this;
	// TODO: Add extra initialization here
	
	int x=GetSystemMetrics(SM_CXSCREEN);
	int y=GetSystemMetrics(SM_CYSCREEN);
	MoveWindow((x-800)/2,(y-600)/2,800,600);
	this->ShowWindow(SW_MAXIMIZE);
	SetWindowText("QT Image");

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(0, ID_SEPARATOR, SBPS_STRETCH, 100);

	InitCommandBars();

	CXTPCommandBars* pCommandBars = GetCommandBars();
	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAIN_MENU);
	

	m_bInitDone = TRUE;
	RepositionControls();

	
	m_view2DManager.SetParent(this);
	m_view2DManager.Init();
	m_view2DManager.SetSeriesManager(&m_seriesManager);

	vtkObject* pObj = vtkObject::New();
	pObj->GlobalWarningDisplayOff();
	pObj->Delete();

	m_pVRDlg=new CDlgVR();
	m_pVRDlg->Create(IDD_IMAGE_VR,NULL);
	m_pVRDlg->ShowWindow(SW_HIDE);

	m_pDlgContour=new CDlgContourLine();
	m_pDlgContour->Create(IDD_CONTOUR_CONFIG,NULL);
	m_pDlgContour->ShowWindow(SW_HIDE);
	m_pDlgContour->MoveWindow((x-500)/2,(y-300)/2,500,300);

	m_pDlgPixelEdit=new CDlgPixelEdit();
	m_pDlgPixelEdit->Create(IDD_PIXELEDIT,NULL);
	m_pDlgPixelEdit->ShowWindow(SW_HIDE);
	
	m_pDlgMPR=new CDlgMPR();
	m_pDlgMPR->Create(IDD_DIALOG_MPR,NULL);
	m_pDlgMPR->ShowWindow(SW_HIDE);

	
	m_srDlg.Create(IDD_IMAGE_SR_FRAME,NULL);
	m_srDlg.ShowWindow(FALSE);
	int width=700;
	int height=500;
	m_srDlg.MoveWindow((x-width)/2,(y-height)/2,width,height);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQTImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogSampleDlgBase::OnSysCommand(nID, lParam);
	}
}

BOOL CQTImageDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	pDC->FillSolidRect(&rect,RGB(0,0,0));

	
 	return FALSE;
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQTImageDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CQTImageDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialogSampleDlgBase::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RepositionControls();

	if(cx<300)
		return;
	
	CRect rect(0,m_rcBorders.top,cx,cy-m_rcBorders.bottom);
	m_clientRect=rect;

	m_view2DManager.SetWndRect(m_clientRect);
	
}

void CQTImageDlg::RepositionControls()
{
	if (m_bInRepositionControls || !m_bInitDone)
		return;

	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);

	if ((GetStyle() & WS_MINIMIZE) || (rcClientStart.IsRectEmpty()))
		return;

	m_bInRepositionControls = TRUE;

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNow);

	CRect rcBorders(rcClientNow.left - rcClientStart.left, rcClientNow.top - rcClientStart.top,  rcClientStart.right - rcClientNow.right, 
		rcClientStart.bottom - rcClientNow.bottom);

	if (rcBorders != m_rcBorders)
	{
		
		CPoint ptOffset(rcBorders.left - m_rcBorders.left, rcBorders.top - m_rcBorders.top);
		CSize szOffset(rcBorders.left + rcBorders.right - m_rcBorders.left - m_rcBorders.right,
			rcBorders.top + rcBorders.bottom - m_rcBorders.top - m_rcBorders.bottom);

		CRect rcWindow;
		GetWindowRect(rcWindow);
		rcWindow.BottomRight() += szOffset;

		Offset(ptOffset);
		m_szWindow += szOffset;
		m_szMin += szOffset;
	
		MoveWindow(rcWindow, TRUE);
	}

	m_rcBorders = rcBorders;

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	m_bInRepositionControls = FALSE;
}

UINT OpenSeriesFromFolder(LPVOID pParam )
{
	CQTImageDlg *pMainDlg=(CQTImageDlg *)pParam;

	vtkImageData *pData=pMainDlg->m_seriesManager.OpenSeries(pMainDlg->m_sNewOpenSeriesPath);
	if(!pData)
	{
		AfxMessageBox("Failed to open series.");
		AfxEndThread(0,TRUE);
		return 0;
	}

	pMainDlg->PostMessage(WM_SHOW_SERIES,WPARAM(pData),NULL);

	AfxEndThread(0,TRUE);
	return 0;
}

void CQTImageDlg::OnFileImportSeries() 
{
	// TODO: Add your command handler code here
	CString szFilter = "Img Files (*.img)|*.img|Dicom Files (*.dcm)|*.dcm|Vti Files (*.vti)|*.vti|Png Files (*.png)|*.png|Bmp Files (*.bmp)|*.bmp|Jpg Files (*.jpg)|*.jpg|All Files (*.*)|*.*||";
	CString sFolderName="";
	CFileDialog dlgFile(TRUE,
		NULL,NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL);
	if(dlgFile.DoModal())
	{
		sFolderName=dlgFile.GetPathName();
	}
	

	if(sFolderName=="")
	{
		return;
	}else
	{
	
		m_sNewOpenSeriesPath=sFolderName;

		AfxBeginThread(OpenSeriesFromFolder,(LPVOID)this,THREAD_PRIORITY_LOWEST,0,0,NULL);
		/*vtkImageData *pData=m_seriesManager.OpenSeries(m_sNewOpenSeriesPath);
		if(pData)
		{
			m_view2DManager.ShowSeries(pData);
		}*/

		
	}
	
}

void CQTImageDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
	PostMessage(WM_CLOSE);
}

void CQTImageDlg::OnDestroy() 
{
	m_view2DManager.RemoveAll();

	CDialogSampleDlgBase::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CQTImageDlg::OnView3dVolRender() 
{
	// TODO: Add your command handler code here
	if(!m_view2DManager.GetSeriesInCurWnd())
	{
		CString sTmp="Please open series firstly.";
		this->SendMessage(WM_SETMESSAGESTRING,WPARAM(&sTmp),NULL);
		return;
	}

	vtkImageData *pImage=m_view2DManager.GetSeriesInCurWnd();
	int *pDim=pImage->GetDimensions();
	if(pDim[2]<2)
	{
		MessageBox("It must be more than two images in this series for volume rending.");
		return;
	}

	
	m_pVRDlg->SetSeries(pImage);
		
	CRect rc=m_clientRect;
	POINT point;
	point.x=0;
	point.y=0;
	ClientToScreen(&point);
	rc.OffsetRect(point);
	m_pVRDlg->MoveWindow(rc);
	m_pVRDlg->ShowWindow(SW_SHOW);
}

void CQTImageDlg::OnView3dGroundColor() 
{
	// TODO: Add your command handler code here
	COLORREF color=RGB(0,0,0);
	CColorDialog dlg(color, CC_FULLOPEN);
	if(dlg.DoModal()==IDOK)
	{
		color=dlg.GetColor();
	
		m_pVRDlg->SetGroundColor(color);
		m_srDlg.SetGroundColor(color);
	}
}

void CQTImageDlg::OnView2dGroundColor() 
{
	// TODO: Add your command handler code here
	COLORREF color=RGB(0,0,0);
	CColorDialog dlg(color, CC_FULLOPEN);
	if(dlg.DoModal()==IDOK)
	{
		color=dlg.GetColor();
		m_2DBKColor=color;
		m_view2DManager.SetGroundColor(color);
	}
}

void CQTImageDlg::OnFileSaveSeries() 
{
	// TODO: Add your command handler code here
	CString szFilter = "Vti Files (*.vti)|*.vti|Png Files (*.png)|*.png|Raw Files (*.raw)|*.raw|All Files (*.*)|*.*||";
	CString sFolderName="";
	CFileDialog dlgFile(FALSE,
		"*.vti",NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL);
	if(dlgFile.DoModal())
	{
		sFolderName=dlgFile.GetPathName();
	}
	

	if(sFolderName=="")
	{
		return;
	}

	if(!m_view2DManager.GetSeriesInCurWnd())
	{
		CString sTmp="Please select series firstly.";
		this->SendMessage(WM_SETMESSAGESTRING,WPARAM(&sTmp),NULL);
		return;
	}

	vtkImageData *pImage=m_view2DManager.GetSeriesInCurWnd();

	if(m_seriesManager.SaveSeries(pImage,sFolderName))
	{
		MessageBox("Series is saved successfully.");
	}else
	{
		MessageBox("Failed to save series.");
	}
}

void CQTImageDlg::OnView2dResetWindowlevel() 
{
	// TODO: Add your command handler code here
	C2DViewer *pView=m_view2DManager.GetCurView();
	if(pView)
	{
		pView->ResetWindowLevel();
	}
}

void CQTImageDlg::OnView2dContourline() 
{
	// TODO: Add your command handler code here
	m_pDlgContour->m_pView=m_view2DManager.GetCurView();
	m_pDlgContour->ShowWindow(SW_SHOW);
}

void CQTImageDlg::OnEditPixel() 
{
	// TODO: Add your command handler code here
	m_pDlgPixelEdit->m_pView=m_view2DManager.GetCurView();
	
	m_pDlgPixelEdit->ShowWindow(SW_SHOW);
	m_pDlgPixelEdit->UpdateImage();
	
}

void CQTImageDlg::OnView2dMpr() 
{
	// TODO: Add your command handler code here
	
	C2DViewer *pView=m_view2DManager.GetCurView();
	if(pView)
	{
		m_pDlgMPR->SetSeries(pView->GetSeries());
		m_pDlgMPR->m_iViewMode=0;
		m_pDlgMPR->Layout();
		m_pDlgMPR->ShowWindow(TRUE);
	}
	
}

void CQTImageDlg::OnRoiSegment() 
{
	// TODO: Add your command handler code here
	C2DViewer *pView=m_view2DManager.GetCurView();
	if(pView)
	{
		m_pDlgMPR->SetSeries(pView->GetSeries());
		m_pDlgMPR->m_iViewMode=1;
		m_pDlgMPR->Layout();
		m_pDlgMPR->ShowWindow(TRUE);
	}
}


void CQTImageDlg::OnView3dDelaunay() 
{
	// TODO: Add your command handler code here
	CString szFilter = "Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CString sFolderName="";
	CFileDialog dlgFile(TRUE,
		NULL,NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL);
	if(dlgFile.DoModal())
	{
		sFolderName=dlgFile.GetPathName();
	}
	

	if(sFolderName=="")
	{
		return;
	}

	CStdioFile file;
	if(!file.Open(sFolderName,CFile::modeRead))
	{
		MessageBox("Can't open file.");
		return;
	}
	CString sTmp;
	if(!file.ReadString(sTmp))
	{
		file.Close();
		MessageBox("It is not a correct file we can read.");
		return;
	}
	if(sTmp!="***3DImage***")
	{
		file.Close();
		MessageBox("It is not a correct file we can read.");
		return;
	}

	if(!file.ReadString(sTmp))
	{
		file.Close();
		MessageBox("It is not a correct file we can read.");
		return;
	}

	int iCount=atoi(sTmp);
	if(iCount<=3)
	{
		file.Close();
		MessageBox("Too few points in this file");
		return;
	}

	PNT3D *pnts=new PNT3D[iCount];
	int i=0;
	int iFind;
	while(i<iCount)
	{
		if(!file.ReadString(sTmp))
		{
			break;
		}
		sTmp.TrimLeft();
		sTmp.TrimRight();
		iFind=sTmp.Find(" ",0);
		if(iFind<=0)
			continue;
		pnts[i].x=atof(sTmp.Left(iFind));
		sTmp=sTmp.Right(sTmp.GetLength()-iFind-1);

		iFind=sTmp.Find(" ",0);
		if(iFind<=0)
			continue;
		pnts[i].y=atof(sTmp.Left(iFind));
		sTmp=sTmp.Right(sTmp.GetLength()-iFind-1);
		pnts[i].z=atof(sTmp);

		i++;

	}

	file.Close();
	if(i<3)
	{
		MessageBox("Too few points in this file");
		return;
	}

	CPoints2Mesh mesh;
	mesh.m_meshType=DELAUNAY;
	mesh.m_iCount=i;
	mesh.m_pPnts=pnts;
	mesh.m_sTextureFile=g_sProgramPath+"..\\Data\\Texture\\masonry.bmp";

	vtkActor *actor=mesh.GetActor();

	m_srDlg.AddActor(actor);
	actor->Delete();
	delete []pnts;

	m_srDlg.ShowWindow(TRUE);
}

void CQTImageDlg::OnView3dPowercrust() 
{
	// TODO: Add your command handler code here
	CString szFilter = "Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CString sFolderName="";
	CFileDialog dlgFile(TRUE,
		NULL,NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL);
	if(dlgFile.DoModal())
	{
		sFolderName=dlgFile.GetPathName();
	}
	

	if(sFolderName=="")
	{
		return;
	}

	CStdioFile file;
	if(!file.Open(sFolderName,CFile::modeRead))
	{
		MessageBox("Can't open file.");
		return;
	}
	CString sTmp;
	if(!file.ReadString(sTmp))
	{
		file.Close();
		MessageBox("It is not a correct file we can read.");
		return;
	}
	if(sTmp!="***3DImage***")
	{
		file.Close();
		MessageBox("It is not a correct file we can read.");
		return;
	}

	if(!file.ReadString(sTmp))
	{
		file.Close();
		MessageBox("It is not a correct file we can read.");
		return;
	}

	int iCount=atoi(sTmp);
	if(iCount<=3)
	{
		file.Close();
		MessageBox("Too few points in this file");
		return;
	}

	PNT3D *pnts=new PNT3D[iCount];
	int i=0;
	int iFind;
	while(i<iCount)
	{
		if(!file.ReadString(sTmp))
		{
			break;
		}
		sTmp.TrimLeft();
		sTmp.TrimRight();
		iFind=sTmp.Find(" ",0);
		if(iFind<=0)
			continue;
		pnts[i].x=atof(sTmp.Left(iFind));
		sTmp=sTmp.Right(sTmp.GetLength()-iFind-1);

		iFind=sTmp.Find(" ",0);
		if(iFind<=0)
			continue;
		pnts[i].y=atof(sTmp.Left(iFind));
		sTmp=sTmp.Right(sTmp.GetLength()-iFind-1);
		pnts[i].z=atof(sTmp);

		i++;

	}

	file.Close();
	if(i<3)
	{
		MessageBox("Too few points in this file");
		return;
	}

	CPoints2Mesh mesh;
	mesh.m_meshType=POWERSUFR;
	mesh.m_iCount=i;
	mesh.m_pPnts=pnts;
	mesh.m_sTextureFile=g_sProgramPath+"..\\Data\\Texture\\masonry.bmp";

	vtkActor *actor=mesh.GetActor();

	m_srDlg.AddActor(actor);
	actor->Delete();
	delete []pnts;

	m_srDlg.ShowWindow(TRUE);
}

void CQTImageDlg::OnView3dSolidSurface() 
{
	// TODO: Add your command handler code here
	CString szFilter = "Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CString sFolderName="";
	CFileDialog dlgFile(TRUE,
		NULL,NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,
		NULL);
	if(dlgFile.DoModal())
	{
		sFolderName=dlgFile.GetPathName();
	}
	

	if(sFolderName=="")
	{
		return;
	}

	CStdioFile file;
	if(!file.Open(sFolderName,CFile::modeRead))
	{
		MessageBox("Can't open file.");
		return;
	}
	CString sTmp;
	if(!file.ReadString(sTmp))
	{
		file.Close();
		MessageBox("It is not a correct file we can read.");
		return;
	}
	if(sTmp!="***3DImage***")
	{
		file.Close();
		MessageBox("It is not a correct file we can read.");
		return;
	}

	if(!file.ReadString(sTmp))
	{
		file.Close();
		MessageBox("It is not a correct file we can read.");
		return;
	}

	int iCount=atoi(sTmp);
	if(iCount<=3)
	{
		file.Close();
		MessageBox("Too few points in this file");
		return;
	}

	PNT3D *pnts=new PNT3D[iCount];
	int i=0;
	int iFind;
	while(i<iCount)
	{
		if(!file.ReadString(sTmp))
		{
			break;
		}
		sTmp.TrimLeft();
		sTmp.TrimRight();
		iFind=sTmp.Find(" ",0);
		if(iFind<=0)
			continue;
		pnts[i].x=atof(sTmp.Left(iFind));
		sTmp=sTmp.Right(sTmp.GetLength()-iFind-1);

		iFind=sTmp.Find(" ",0);
		if(iFind<=0)
			continue;
		pnts[i].y=atof(sTmp.Left(iFind));
		sTmp=sTmp.Right(sTmp.GetLength()-iFind-1);
		pnts[i].z=atof(sTmp);

		i++;

	}

	file.Close();
	if(i<3)
	{
		MessageBox("Too few points in this file");
		return;
	}

	CPoints2Mesh mesh;
	mesh.m_meshType=VTKSURFACE;
	mesh.m_iCount=i;
	mesh.m_pPnts=pnts;
	mesh.m_sTextureFile=g_sProgramPath+"..\\Data\\Texture\\masonry.bmp";

	vtkActor *actor=mesh.GetActor();

	m_srDlg.AddActor(actor);
	actor->Delete();
	delete []pnts;

	m_srDlg.ShowWindow(TRUE);
}
