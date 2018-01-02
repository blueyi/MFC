// PpMruSync.cpp : implementation file
//

#include "stdafx.h"
#include "demoflb.h"
#include "PpMruSync.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpMruSync property page

IMPLEMENT_DYNCREATE(CPpMruSync, CPropertyPage)

CPpMruSync::CPpMruSync() : CPropertyPage(CPpMruSync::IDD),
m_listFont1(FNTLB_HAS_TOOLTIPS | FNTLB_TOOLTIPTEXT_FONT | FNTLB_TRACKING_TOOLTIP | FNTLB_MRUCUSTOMLIST, _T("MruSyncTest")),
m_listFont2(FNTLB_HAS_TOOLTIPS | FNTLB_TOOLTIPTEXT_FONT | FNTLB_TRACKING_TOOLTIP | FNTLB_MRUCUSTOMLIST, _T("MruSyncTest"))
{
	//{{AFX_DATA_INIT(CPpMruSync)
	//}}AFX_DATA_INIT
}

CPpMruSync::~CPpMruSync()
{
}

void CPpMruSync::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpMruSync)
	DDX_Control(pDX, IDC_BTN_MRUCLEAR2, m_btnClear2);
	DDX_Control(pDX, IDC_BTN_MRUCLEAR1, m_btnClear1);
	DDX_Control(pDX, IDC_LIST2, m_listFont2);
	DDX_Control(pDX, IDC_BTN_MRUREMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_BTN_MRUADD, m_btnAdd);
	DDX_Control(pDX, IDC_LIST1, m_listFont1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpMruSync, CPropertyPage)
	//{{AFX_MSG_MAP(CPpMruSync)
	ON_BN_CLICKED(IDC_BTN_MRUADD, OnBtnMruAdd)
	ON_BN_CLICKED(IDC_BTN_MRUREMOVE, OnBtnMruRemove)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelChangeList1)
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelChangeList2)
	ON_BN_CLICKED(IDC_BTN_MRUCLEAR1, OnBtnMruClear1)
	ON_BN_CLICKED(IDC_BTN_MRUCLEAR2, OnBtnMruClear2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpMruSync message handlers

void CPpMruSync::OnBtnMruAdd() 
{
	m_listFont1.AddSelectedFontsToMruList();
	m_listFont1.ClearSelection();
	m_listFont1.SetTopIndex(0);
//	m_listFont2.SetTopIndex(0);
	// differs the SetTopIndex (due to messages posted by CFontListManager)
	m_listFont2.PostMessage(LB_SETTOPINDEX, 0, NULL);
	if (m_listFont1.GetMruFontCount() > 0)
	{
		m_btnClear1.EnableWindow(TRUE);
		m_btnClear2.EnableWindow(TRUE);
	}
	else
	{
		m_btnClear1.EnableWindow(FALSE);
		m_btnClear2.EnableWindow(FALSE);
	}

}

void CPpMruSync::OnBtnMruRemove() 
{
	m_listFont2.RemoveSelectedFontsFromMruList();
	m_listFont2.ClearSelection();
//	m_listFont1.SetTopIndex(0);
	// differs the SetTopIndex (due to messages posted by CFontListManager)
	m_listFont1.PostMessage(LB_SETTOPINDEX, 0, NULL);
	m_listFont2.SetTopIndex(0);
	if (m_listFont1.GetMruFontCount() > 0)
	{
		m_btnClear1.EnableWindow(TRUE);
		m_btnClear2.EnableWindow(TRUE);
	}
	else
	{
		m_btnClear1.EnableWindow(FALSE);
		m_btnClear2.EnableWindow(FALSE);
	}
}

void CPpMruSync::OnSelChangeList1() 
{
	if(m_listFont1.GetSelCount() > 0)
		m_btnAdd.EnableWindow(TRUE);
	else
		m_btnAdd.EnableWindow(FALSE);
	
}

void CPpMruSync::OnSelChangeList2() 
{
	if(m_listFont2.GetSelCount() > 0)
		m_btnRemove.EnableWindow(TRUE);
	else
		m_btnRemove.EnableWindow(FALSE);
}

BOOL CPpMruSync::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listFont1.Initialize();
	m_listFont2.Initialize();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPpMruSync::OnBtnMruClear1() 
{
	m_listFont1.ClearMruList();
	m_btnClear1.EnableWindow(FALSE);
	m_btnClear2.EnableWindow(FALSE);
	OnSelChangeList1();
	OnSelChangeList2();
}

void CPpMruSync::OnBtnMruClear2() 
{
	m_listFont2.ClearMruList();
	m_btnClear1.EnableWindow(FALSE);
	m_btnClear2.EnableWindow(FALSE);
	OnSelChangeList1();
	OnSelChangeList2();
}

