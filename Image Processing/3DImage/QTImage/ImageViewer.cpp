// ImageViewer.cpp : implementation file
//

#include "stdafx.h"
#include "QTImage.h"
#include "ImageViewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageViewer dialog


CImageViewer::CImageViewer(UINT IDD,CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageViewer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Type=0;
	m_pMFCWindow=NULL;
	m_bEnableSlider=TRUE;
	m_bSelected=FALSE;
}

CImageViewer::~CImageViewer()
{
	//
}


void CImageViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageViewer)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageViewer, CDialog)
	//{{AFX_MSG_MAP(CImageViewer)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageViewer message handlers

void CImageViewer::OnDestroy() 
{
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

BOOL CImageViewer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_pMFCWindow = new vtkMFCWindow(this);
	this->m_pRenderer = vtkRenderer::New();
	this->m_pMFCWindow->GetRenderWindow()->AddRenderer(this->m_pRenderer);
	

	m_pInteractor = this->m_pMFCWindow->GetInteractor();
			
	m_pRenderer->SetBackground(0, 0, 0);
	m_groundColor=RGB(0,0,0);
    m_pRenderer->ResetCamera(); 
	m_pRenderer->SetRenderWindow(m_pMFCWindow->GetRenderWindow());
	

	vtkObject* pObj = vtkObject::New();
	pObj->GlobalWarningDisplayOff();
	pObj->Delete();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImageViewer::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_pMFCWindow)
	{
		if(m_Type==0 && m_bEnableSlider)
		{
			m_pMFCWindow->MoveWindow(2, 27, cx-4, cy-29);	
		}else
		{
			m_pMFCWindow->MoveWindow(2, 2, cx-4, cy-4);	
		}
	}
}


BOOL CImageViewer::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(0,0,0));
	
	
 	return TRUE;
}

BOOL CImageViewer::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN){   
		switch(pMsg->wParam){   
		case   VK_ESCAPE:   
			 return   TRUE;   
			 break;
		}   
	}   

	if((pMsg->message   ==   WM_KEYDOWN)   &&   (pMsg->wParam   ==   VK_RETURN))   
	{   
		
		return TRUE;
		
	}   
	return CDialog::PreTranslateMessage(pMsg);
}


