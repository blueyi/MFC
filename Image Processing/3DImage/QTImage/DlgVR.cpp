// DlgVR.cpp : implementation file
//

#include "stdafx.h"
#include "QTImage.h"
#include "DlgVR.h"
#include "QTImageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVR dialog
extern CQTImageDlg* gpMainDlg;

CDlgVR::CDlgVR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVR)
	//}}AFX_DATA_INIT
	m_pView3D=NULL;
	m_pVRCtrl=NULL;

	
}

CDlgVR::~CDlgVR()
{
	if(m_pVRCtrl)
	{
		if(m_pVRCtrl->m_hWnd)
		{
			m_pVRCtrl->DestroyWindow();
		}
		delete m_pVRCtrl;
	}

	if(m_pView3D)
	{
		if(m_pView3D->m_hWnd)
		{
			m_pView3D->DestroyWindow();
		}
		delete m_pView3D;
	}
}

void CDlgVR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVR)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVR, CDialog)
	//{{AFX_MSG_MAP(CDlgVR)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVR message handlers

BOOL CDlgVR::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	m_pView3D=new CDlgVRView(this);
	m_pView3D->Create(IDD_IMAGE_VRVIEW,this);
	m_pView3D->ShowWindow(SW_SHOW);

	m_pVRCtrl=new CDlgVRCtrl(this);
	m_pVRCtrl->Create(IDD_IMAGE_VRCTRL,this);
	m_pVRCtrl->m_pVRView=m_pView3D;

	m_pVRCtrl->ShowWindow(SW_SHOW);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVR::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_pView3D)
		return;

	
	if(m_pView3D && m_pView3D->m_hWnd)
	{
		int iWidth=cx;
		if(cx>cy)
		{
			iWidth=cy;
		}
		m_pView3D->MoveWindow((cx-iWidth)/2, VR_CTRL_HEIGHT, iWidth, cy-VR_CTRL_HEIGHT);
	}

	if(m_pVRCtrl && m_pVRCtrl->m_hWnd)
	{
		m_pVRCtrl->MoveWindow(0, 0, cx, VR_CTRL_HEIGHT);
	}
	
}

void CDlgVR::SetSeries(vtkImageData *pImage)
{
	m_pView3D->SetVRImage(pImage);
	m_pVRCtrl->Update();

	CQTImageDlg* pMainDlg = gpMainDlg;
	CString sTmp;
	sTmp=pMainDlg->m_seriesManager.GetName(pImage);
	SetWindowText(sTmp);
}



void CDlgVR::SetGroundColor(COLORREF color)
{
	m_pView3D->SetGroundColor(color);
}


void CDlgVR::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_pView3D->SetVRImage(NULL);
	CDialog::OnClose();
}








