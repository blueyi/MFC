// testpgl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "testpgl.h"

#include "MainFrm.h"
#include "testpglDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestpglApp

BEGIN_MESSAGE_MAP(CTestpglApp, CWinApp)
	//{{AFX_MSG_MAP(CTestpglApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestpglApp construction

CTestpglApp::CTestpglApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pIdleView = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestpglApp object

CTestpglApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestpglApp initialization

BOOL CTestpglApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	AfxEnableControlContainer();
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTestpglDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPGLGraphView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// initialize gdi+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_ulGdiplusToken, &gdiplusStartupInput, NULL);

	return TRUE;
}


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
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	// TODO
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CTestpglApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTestpglApp message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	  
	return 0;
}

int CTestpglApp::ExitInstance() 
{
	// shutdown GDI+
	Gdiplus::GdiplusShutdown(m_ulGdiplusToken);
	
	return CWinApp::ExitInstance();
}

CPGLGraph* CTestpglApp::GenerateGraph()
{
	int i,j;
	int nPoints=200;
	int nx=10;
	int ny=10;
	double dx=0.5;
	double dy=0.1;
	double x,y,norm;

	double *x1=new double[nPoints];
	double *x2=new double[nPoints];
	double *x3=new double[nPoints];
	double *y1=new double[nPoints];
	double *y2=new double[nPoints];
	double *y3=new double[nPoints];

	double *z=new double[nx*ny];
	double *vx=new double[nx*ny];
	double *vy=new double[nx*ny];

	for (i=0;i<nPoints;i++)
	{
		x2[i]=(double)i/(double)nPoints*10;
		x1[i]=(double)i/(double)nPoints*4+2;
		x3[i]=x1[i];
		y1[i]=sin(x1[i]/2.0);
		y2[i]=(cos(2*x2[i])+sin(x2[i]))/2.0;
		y3[i]=y1[i];
	}
	for (i=0;i<ny;i++)
	{
		for (j=0;j<nx;j++)
		{
			x=j*nx*2.5;
			y=(i-ny/2)*nx;
			z[i*nx+j]=x+y;

			norm=sqrt(x*x+y*y+0.01);
			vx[i*nx+j]=x/norm;
			vy[i*nx+j]=y/norm;
		}
	}

	CPGLGraph* pGraph=new CPGLGraph();

	pGraph->Divide(1,2);

	CPGLRegion* pRegion = pGraph->GetChild(0);
	CPGLAxe2D* pAxe=pRegion->GetAxe();
	//setting labels...
	pAxe->SetBottomLabel(_T("Bottom label"));
	pAxe->GetBottomLabel()->Show();
	pAxe->SetLeftLabel(_T("Left label"));
	pAxe->SetTopLabel(_T("The title"));
	pAxe->SetRightLabel(_T("Right label"));
	pAxe->GetRightLabel()->Show();

	CPGLLine2D* pLine=new CPGLLine2D();
	CPGLLine2D* pLine2=new CPGLLine2D();
	CPGLMapZ* pMapZ=new CPGLMapZ();
	CPGLMapVector* pMapV=new CPGLMapVector();

	// adding first line
	pLine->SetDatas(nPoints,x1,y1);
	pLine->SetColor(1.0f,0.0f,0.0f,1.0f);
	pLine->SetName(_T("Funny"));
	pLine->ShowStartArrow();
	pLine->ShowEndArrow();
	pRegion->AddObject(pLine);

	// adding second line
	pLine2->SetDatas(nPoints,x2,y2);
	pLine2->SetColor(0.0f,0.0f,1.0f,1.0f);
	pLine2->SetName(_T("Even more funny"));
	pLine2->SetLineType(PGL_LINE_NONE);
	pLine2->SetPointType(PGL_POINT_SQUARE);
	pLine2->SetPointWidth(8.0);
	pRegion->AddObject(pLine2);

	m_uLineID = pLine2->GetID();

	// Adding third line with LOD
	CPGLLine2DLOD* pLineLOD=new CPGLLine2DLOD();
	pLineLOD->SetFilled(TRUE);
	pLineLOD->SetDatas(nPoints,x3,y3);
	pLineLOD->SetTol(0.01);
	pLineLOD->SetColor(0.7f,0.3f,0.3f,1.0f);
	pLineLOD->SetName(_T("Another 2D with LOD"));
	pRegion->AddObject(pLineLOD);

	CPGLLineVer* pLineVer = new CPGLLineVer;
	pLineVer->SetName("A vertical line");
	pLineVer->SetCaption("A vertical line");
	pLineVer->SetLineWidth(4);
	pLineVer->SetX(8);
	pLineVer->SetColor(0.0f,0.2f,0.2f);
	pRegion->AddObject(pLineVer);

	CPGLLineHor* pLineHor = new CPGLLineHor;
	pLineHor->SetName("A horizontal line");
	pLineHor->SetCaption("A horizontal line");
	pLineHor->SetLineWidth(2);
	pLineHor->SetY(0);
	pLineHor->SetColor(0.7f,0.2f,0.2f);
	pRegion->AddObject(pLineHor);

	pRegion = pGraph->GetChild(1);
	pAxe=pRegion->GetAxe();
	pAxe->SetTimeLabel(TRUE);
	pAxe->SetTimeLabelFormat(CTime::GetCurrentTime(),CTimeSpan(0,12,0,0),"%d:%H");

	//setting labels...
	pAxe->SetBottomLabel(_T("Time label (New)"));
	pAxe->GetLeftLabel()->Hide();
	pAxe->GetLeftNumber()->Hide();
	pAxe->SetRightLabel(_T("y label"));
	pAxe->GetRightLabel()->Show();
	pAxe->GetRightNumber()->Show();

	// adding map
	pMapZ->SetGrid(0,nx,0,dx);
	pMapZ->SetGrid(1,ny,-1,dy);
	pMapZ->SetDatas(z);
	pMapZ->SetName(_T("Height map"));
	pRegion->AddObject(pMapZ);

	// adding map
	pMapV->SetGrid(0,nx,0,dx);
	pMapV->SetGrid(1,ny,-1+ny*dy,dy);
	pMapV->SetColor(0,0,0);
	pMapV->SetDatas(vx,vy);
	pMapV->SetName(_T("Vector map"));
	pRegion->AddObject(pMapV);
	
/*	// adding text
	pText->SetString("Ceci est un exemple de texte.");
	float position[3]={5.0f ,0.5f ,0.0};
	pText->SetPosition(position);
	pText->SetColor(0.0f,0.0f,0.0f,1.0f);
	pRegion->AddObject(pText);
*/
	pGraph->ZoomAll(TRUE);

	return pGraph;
}

void CTestpglApp::AnimateLine()
{
	if (!m_pAnimatedLine)
		return;

	clock_t tNow = clock();
	double duration = (double)(tNow - m_tStart) / CLOCKS_PER_SEC;
	double x;

	// calcul
	for (UINT i=0;i<m_pAnimatedLine->GetNPoints();i++)
	{
		x=(double)i/(double)m_pAnimatedLine->GetNPoints()*10;
		m_pAnimatedLine->SetXi(i,  x);
		m_pAnimatedLine->SetYi(i, (cos(duration*2+x)+sin(duration-x))/2.0);
	}
}

BOOL CTestpglApp::OnIdle(LONG lCount) 
{
	if (m_pIdleView)
	{
		if (m_pAnimatedLine)
			AnimateLine();

		m_pIdleView->InvalidateRect(NULL,FALSE);
		return TRUE;
	}

	return CWinApp::OnIdle(lCount);
}
