// ProgressAndTipDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "imagesexport.h"
#include "ProgressAndTipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressAndTipDlg dialog


CProgressAndTipDlg::CProgressAndTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressAndTipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressAndTipDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProgressAndTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressAndTipDlg)
	DDX_Control(pDX, IDC_PROGRESS_PRO, m_sProgressCtrl);
	DDX_Control(pDX, IDC_STATIC_TIP_FILE_NAME, m_sStatic_Ctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressAndTipDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressAndTipDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressAndTipDlg message handlers

BOOL CProgressAndTipDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CProgressAndTipDlg::PumpMessages()
{
    // Must call Create() before using the dialog
    ASSERT(m_hWnd!=NULL);

    MSG msg;
    // Handle dialog messages
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if(!IsDialogMessage(&msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);  
      }
    }
}
int  CProgressAndTipDlg::SetStep(int nStep)
{
	return m_sProgressCtrl.SetStep(nStep);
}
    
int  CProgressAndTipDlg::StepIt()
{
	PumpMessages();
    int iResult = m_sProgressCtrl.StepIt();
    
    return iResult;

}
