// DlgSR.cpp : implementation file
//

#include "stdafx.h"
#include "qtimage.h"
#include "DlgSR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSR dialog


CDlgSR::CDlgSR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSR)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pSRCtrl=NULL;
}

CDlgSR::~CDlgSR()
{
	if(m_pSRCtrl)
	{
		if(m_pSRCtrl->m_hWnd)
		{
			m_pSRCtrl->DestroyWindow();
		}
		delete m_pSRCtrl;
	}

	if(m_pSRView)
	{
		if(m_pSRView->m_hWnd)
		{
			m_pSRView->DestroyWindow();
		}
		delete m_pSRView;
	}
}

void CDlgSR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSR)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSR, CDialog)
	//{{AFX_MSG_MAP(CDlgSR)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSR message handlers

BOOL CDlgSR::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	m_pSRView=new CDlgSRView(this);
	m_pSRView->Create(IDD_IMAGE_SRVIEW,this);
	m_pSRView->ShowWindow(SW_SHOW);

	m_pSRCtrl=new CDlgSRCtrl(this);
	m_pSRCtrl->Create(IDD_IMAGE_SRCTRL,this);
	m_pSRCtrl->m_pSRView=m_pSRView;
	m_pSRCtrl->ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSR::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_pSRCtrl)
	{
		return;
	}

	m_pSRView->MoveWindow(0,0,cx,cy);
}

void CDlgSR::SetSeries(vtkImageData *pImage)
{
	m_pSRView->SetSeries(pImage);
}

void CDlgSR::UpdateMesh()
{
	m_pSRView->UpdateMesh();
}

BOOL CDlgSR::PreTranslateMessage(MSG* pMsg) 
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

void CDlgSR::AddMesh(vtkImageData *pImage, MESH_OPTIONS option)
{
	m_pSRView->AddMesh(pImage,option);
}

void CDlgSR::ClearMesh()
{
	m_pSRView->ClearMesh();
}

void CDlgSR::AddActor(vtkActor *pActor)
{
	m_pSRView->AddActor(pActor);
}

void CDlgSR::SetGroundColor(COLORREF color)
{
	m_pSRView->SetGroundColor(color);
}
