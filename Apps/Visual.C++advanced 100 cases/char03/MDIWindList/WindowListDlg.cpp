// WindowListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDIWindList.h"
#include "WindowListDlg.h"

#include "ViewManager.h"
#include <stdlib.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWindowListDlg dialog


CWindowListDlg::CWindowListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWindowListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWindowListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWindowListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWindowListDlg)
	DDX_Control(pDX, IDC_WINDOWLIST, wndList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWindowListDlg, CDialog)
	//{{AFX_MSG_MAP(CWindowListDlg)
	ON_BN_CLICKED(IDC_ACTIVATE, OnActivate)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_LBN_SELCHANGE(IDC_WINDOWLIST, OnSelchangeWindowlist)
	ON_LBN_DBLCLK(IDC_WINDOWLIST, OnDblclkWindowlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowListDlg message handlers

BOOL CWindowListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CPtrArray		arViews;
	CStringArray	arViewTitles;

	CView * pActiveView = ((CFrameWnd *)AfxGetMainWnd())->GetActiveView();

	int t, iSel = -1;
	for (t = 0; t < theViewManager.arViewTitles.GetSize(); t++)
	{
		int idx = wndList.AddString(theViewManager.arViewTitles.GetAt(t));
		wndList.SetItemData(idx, t);
		if (pActiveView == (CView *) (theViewManager.arViews.GetAt(t))) iSel == t;
	}
	wndList.SetCurSel(iSel);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWindowListDlg::OnActivate() 
{
	int idx = wndList.GetCurSel();
	if (idx >= 0)
	{
		CDialog::OnOK();
		int item = wndList.GetItemData(idx);
		CView * pView = ((CView *) theViewManager.arViews.GetAt(item));
		((CMDIFrameWnd *)AfxGetMainWnd())->MDIActivate(pView->GetParent());
	}
}

int SortInt(const void *arg1, const void *arg2 )
{
	if (*((INT *)arg1)>*((INT *)arg2)) return 1;
	if (*((INT *)arg1)<*((INT *)arg2)) return -1;
	return 0;
}


void CWindowListDlg::OnClose() 
{
	int iCount = wndList.GetSelCount();
	if (iCount > 0)
	{
		INT * pi = new INT[iCount];
		ASSERT(pi);

		VERIFY(wndList.GetSelItems(iCount, pi) == iCount);

		qsort((void *) pi, (size_t) iCount, sizeof(int), SortInt);

		for (int t = 0; t < iCount; t++)
		{
			int item = wndList.GetItemData(pi[t]);
			((CView *) theViewManager.arViews.GetAt(item))->GetParent()->SendMessage(WM_CLOSE);
		}
		delete [] pi;

		CView * pActiveView = ((CFrameWnd *)AfxGetMainWnd())->GetActiveView();

		wndList.ResetContent();
		int iSel = -1;
		for (t = 0; t < theViewManager.arViewTitles.GetSize(); t++)
		{
			int idx = wndList.AddString(theViewManager.arViewTitles.GetAt(t));
			wndList.SetItemData(idx, t);
			if (pActiveView == (CView *) (theViewManager.arViews.GetAt(t))) iSel == t;
		}
		wndList.SetCurSel(iSel);

//		CDialog::OnOK();
	}
}

void CWindowListDlg::OnSelchangeWindowlist() 
{
	int iCount = wndList.GetSelCount();
	if (iCount <= 0)
	{
		GetDlgItem(IDC_CLOSE)->EnableWindow(false);
		GetDlgItem(IDC_ACTIVATE)->EnableWindow(false);
	}
	else if (iCount == 1)
	{
		GetDlgItem(IDC_CLOSE)->EnableWindow(true);
		GetDlgItem(IDC_ACTIVATE)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_CLOSE)->EnableWindow(true);
		GetDlgItem(IDC_ACTIVATE)->EnableWindow(false);
	}
}

void CWindowListDlg::OnDblclkWindowlist() 
{
	OnActivate();
}
