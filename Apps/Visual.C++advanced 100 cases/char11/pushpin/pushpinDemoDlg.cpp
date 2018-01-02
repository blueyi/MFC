#include "stdafx.h"
#include "pushpindemo.h"
#include "pushpindemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPushpin2Dlg::CPushpin2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPushpin2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPushpin2Dlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPushpin2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPushpin2Dlg)
	DDX_Control(pDX, IDC_EDGE, m_ctrlCheck);
	DDX_Control(pDX, IDC_BUTTON1, m_ctrlPushPin);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPushpin2Dlg, CDialog)
	//{{AFX_MSG_MAP(CPushpin2Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOLORCHANGE()
	ON_BN_CLICKED(IDC_EDGE, OnEdge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPushpin2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	return TRUE;
}

void CPushpin2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CPushpin2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPushpin2Dlg::OnSysColorChange() 
{
	CDialog::OnSysColorChange();
	
  //Inform the push pin of the system color changes
	m_ctrlPushPin.ReloadBitmaps();
}

void CPushpin2Dlg::OnEdge() 
{
	m_ctrlPushPin.SetUseEdgeBitmap(m_ctrlCheck.GetCheck() == 1);
}
