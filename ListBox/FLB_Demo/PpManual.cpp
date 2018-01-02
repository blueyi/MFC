// PpManual.cpp : implementation file
//

#include "stdafx.h"
#include "DemoFLB.h"
#include "PpManual.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpManual property page

IMPLEMENT_DYNCREATE(CPpManual, CPropertyPage)

CPpManual::CPpManual() : CPropertyPage(CPpManual::IDD),
m_listFont1(FNTLB_HAS_TOOLTIPS | FNTLB_TOOLTIPTEXT_FONT | FNTLB_TRACKING_TOOLTIP | FNTLB_TOOLTIPSELECTED | FNTLB_MRUCUSTOMLIST, _T("MruTest2"))
{
	//{{AFX_DATA_INIT(CPpManual)
	//}}AFX_DATA_INIT
	m_psp.dwFlags &= ~PSP_HASHELP;  // Lose the Help button
}

CPpManual::~CPpManual()
{
	
}

void CPpManual::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpManual)
	DDX_Control(pDX, IDC_BUTTON1, m_btnFontChange);
	DDX_Control(pDX, IDC_BTN_MRUREMOVE, m_btnMruRemove);
	DDX_Control(pDX, IDC_BTN_MRUCLEAR, m_btnMruClear);
	DDX_Control(pDX, IDC_BTN_MRUADD, m_btnMruAdd);
	DDX_Control(pDX, IDC_BTNCLEARSEL, m_btnClearSel);
	DDX_Control(pDX, IDC_BTNCLEARLIST, m_btnClearList);
	DDX_Control(pDX, IDC_BTN_REMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_LIST1, m_listFont1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpManual, CPropertyPage)
	//{{AFX_MSG_MAP(CPpManual)
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelChangeList1)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_REMOVE, OnBtnRemove)
	ON_BN_CLICKED(IDC_BTNCLEARLIST, OnBtnClearList)
	ON_BN_CLICKED(IDC_BTNCLEARSEL, OnBtnClearSel)
	ON_BN_CLICKED(IDC_BTN_MRUADD, OnBtnMruAdd)
	ON_BN_CLICKED(IDC_BTN_MRUREMOVE, OnBtnMruRemove)
	ON_BN_CLICKED(IDC_BTN_MRUCLEAR, OnBtnMruClear)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelChangeList2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpManual message handlers

BOOL CPpManual::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// Dynamically create a CFontListBox
	CRect rcList1;
	m_listFont1.GetWindowRect(&rcList1);
	ScreenToClient(&rcList1);
	CRect rcClient;
	GetClientRect(&rcClient);
	CRect rcList2;
	rcList2.CopyRect(&rcList1);
	rcList2.right = rcClient.Width() - rcList1.left;
	rcList2.left = rcList2.right - rcList1.Width();
	rcList2.InflateRect(CSize(::GetSystemMetrics(SM_CXBORDER),::GetSystemMetrics(SM_CYBORDER)));
	m_plistFont2 = new CFontListBox;
	m_plistFont2->SetFlags(m_listFont1.GetFlags() | FNTLB_MANUAL);
	m_plistFont2->SetMruFontListName(m_listFont1.GetMruFontListName());
	m_plistFont2->Create(m_listFont1.GetStyle(), rcList2, this, IDC_LIST2, m_listFont1.GetExStyle());

	m_listFont1.Initialize();
	m_plistFont2->Initialize();

	if (!AfxFontChangeSupported())
		m_btnFontChange.EnableWindow(FALSE);
	AdaptButtonsState();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPpManual::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	if (m_plistFont2)
		delete m_plistFont2;
}

void CPpManual::OnSelChangeList1() 
{
	AdaptButtonsState();
}

void CPpManual::OnSelChangeList2() 
{
	AdaptButtonsState();
}

void CPpManual::OnBtnAdd() 
{
	CStringArray	arFontNames;
	CString	str;
	for (int i=0; i<(m_listFont1.GetCount()-1); i++)
	{
		if (m_listFont1.GetSel(i))
		{
			m_listFont1.GetText(i, str);
			arFontNames.Add(str);
		}
	}
	m_plistFont2->AddFontsToList(&arFontNames);
	AdaptButtonsState();
}

void CPpManual::OnBtnRemove() 
{
	m_plistFont2->RemoveSelectedFontsFromList();
	AdaptButtonsState();
}

void CPpManual::OnBtnClearList() 
{
	m_plistFont2->ClearList();
	AdaptButtonsState();
}

void CPpManual::OnBtnClearSel() 
{
	m_listFont1.ClearSelection();
	AdaptButtonsState();
}

void CPpManual::AdaptButtonsState()
{
	if (m_listFont1.GetDisplayedMruFontCount()>0)
		m_btnMruClear.EnableWindow(TRUE);
	else
		m_btnMruClear.EnableWindow(FALSE);

	if (m_listFont1.GetSelectedCount()>0)
	{
		m_btnMruAdd.EnableWindow(TRUE);
		m_btnMruRemove.EnableWindow(TRUE);
		m_btnAdd.EnableWindow(TRUE);
		m_btnClearSel.EnableWindow(TRUE);
	}
	else
	{
		m_btnMruAdd.EnableWindow(FALSE);
		m_btnMruRemove.EnableWindow(FALSE);
		m_btnAdd.EnableWindow(FALSE);
		m_btnClearSel.EnableWindow(FALSE);
	}

	if (m_plistFont2->GetSelectedCount()>0)
		m_btnRemove.EnableWindow(TRUE);
	else
		m_btnRemove.EnableWindow(FALSE);
	if (m_plistFont2->GetCount() > 0)
		m_btnClearList.EnableWindow(TRUE);
	else
		m_btnClearList.EnableWindow(FALSE);

}



void CPpManual::OnBtnMruAdd() 
{
	m_listFont1.AddSelectedFontsToMruList();
	AdaptButtonsState();
}

void CPpManual::OnBtnMruRemove() 
{
	m_listFont1.RemoveSelectedFontsFromMruList();
	AdaptButtonsState();
}

void CPpManual::OnBtnMruClear() 
{
	m_listFont1.ClearMruList();
	AdaptButtonsState();
}

void CPpManual::OnButton1() 
{
	::PostMessage(HWND_BROADCAST, WM_FONTCHANGE, NULL, NULL);
}
