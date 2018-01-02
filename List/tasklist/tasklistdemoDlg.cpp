#include "stdafx.h"
#include "tasklistdemo.h"
#include "tasklistdemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CTasklistdemoDlg::CTasklistdemoDlg(CWnd* pParent)	: CDialog(CTasklistdemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTasklistdemoDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTasklistdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTasklistdemoDlg)
	DDX_Control(pDX, IDC_TODOLIST, m_ctrlTask);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTasklistdemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTasklistdemoDlg)
	ON_BN_CLICKED(IDC_ADDTOLIST, OnAddtolist)
	ON_NOTIFY(MCN_SELECT, IDC_MONTH, OnSelectMonth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CTasklistdemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Initialize dialog controls
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_LEVEL);
	ASSERT(pSlider);

	pSlider->SetTic(3);
	pSlider->SetRange(1, 3, TRUE);

	// initialize task list control with some default items

	CTaskList* pTasklist = (CTaskList*)GetDlgItem(IDC_TODOLIST);
	ASSERT(pTasklist);

	pTasklist->AddTask(1, "Very important task");
	pTasklist->AddTask(2, "Intermediate importance");
	pTasklist->AddTask(3, "Task to be completed when time is available.  Notice the adjustment of the drop down :) Thanx Chris");
	
	// Make first element default element
	pTasklist->SetCurSel(0);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTasklistdemoDlg::OnAddtolist() 
{
	CEdit* pControl = (CEdit*)GetDlgItem(IDC_EDIT);
	ASSERT(pControl);

	// Can't add empty items
	if(!pControl->GetWindowTextLength()) return;

	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_LEVEL);
	ASSERT(pSlider);

	int nPos = pSlider->GetPos();

	CTaskList* pTasklist = (CTaskList*)GetDlgItem(IDC_TODOLIST);
	ASSERT(pTasklist);

	CString buff;
	pControl->GetWindowText(buff);
	
	pTasklist->AddTask(nPos, buff);
}

void CTasklistdemoDlg::OnSelectMonth(NMHDR* pNMHDR, LRESULT* pResult) 
{
	AfxMessageBox("This function is not implemented in this DEMO version", MB_OK, NULL);
	
	*pResult = 0;
}
