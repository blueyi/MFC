// PpPersistence.cpp : implementation file
//

#include "stdafx.h"
#include "demoflb.h"
#include "PpPersistence.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpPersistence property page

IMPLEMENT_DYNCREATE(CPpPersistence, CPropertyPage)

CPpPersistence::CPpPersistence() : CPropertyPage(CPpPersistence::IDD),
m_listFont(FNTLB_HAS_TOOLTIPS | FNTLB_TOOLTIPTEXT_FONT | FNTLB_TRACKING_TOOLTIP | FNTLB_MRUCUSTOMLIST, _T("MruPersist"))
{
	//{{AFX_DATA_INIT(CPpPersistence)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpPersistence::~CPpPersistence()
{
}

void CPpPersistence::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpPersistence)
	DDX_Control(pDX, IDC_BTN_CLEARSEL, m_btnClearSel);
	DDX_Control(pDX, IDC_BTN_MRUSAVE, m_btnMruSave);
	DDX_Control(pDX, IDC_BTN_MRUREMOVE, m_btnMruRemove);
	DDX_Control(pDX, IDC_BTN_MRUPERSISTENCE, m_btnMruPersist);
	DDX_Control(pDX, IDC_BTN_MRULOAD, m_btnMruLoad);
	DDX_Control(pDX, IDC_BTN_MRUCLEAR, m_btnMruClear);
	DDX_Control(pDX, IDC_BTN_MRUADD, m_btnMruAdd);
	DDX_Control(pDX, IDC_LIST, m_listFont);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpPersistence, CPropertyPage)
	//{{AFX_MSG_MAP(CPpPersistence)
	ON_BN_CLICKED(IDC_BTN_MRUADD, OnBtnMruAdd)
	ON_BN_CLICKED(IDC_BTN_MRUCLEAR, OnBtnMruClear)
	ON_BN_CLICKED(IDC_BTN_MRUPERSISTENCE, OnBtnMruPersistence)
	ON_BN_CLICKED(IDC_BTN_MRUREMOVE, OnBtnMruRemove)
	ON_BN_CLICKED(IDC_BTN_MRUSAVE, OnBtnMruSave)
	ON_BN_CLICKED(IDC_BTN_CLEARSEL, OnBtnClearSel)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelChangeList)
	ON_BN_CLICKED(IDC_BTN_MRULOAD, OnBtnMruLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpPersistence message handlers

BOOL CPpPersistence::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listFont.Initialize();
	
	AdaptButtonsState();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPpPersistence::AdaptButtonsState()
{
	CString strCaption = _T("Set MRU list persistence = ");
	if (m_listFont.IsMruListPersistent())
	{
		m_btnMruSave.EnableWindow(TRUE); 
		m_btnMruLoad.EnableWindow(TRUE); 
		strCaption += _T("False");
	}
	else
	{
		m_btnMruSave.EnableWindow(FALSE); 
		m_btnMruLoad.EnableWindow(FALSE); 
		strCaption += _T("True");
	}
	m_btnMruPersist.SetWindowText(strCaption);

	if (m_listFont.GetSelectedCount()>0)
		m_btnMruAdd.EnableWindow(TRUE);
	else
		m_btnMruAdd.EnableWindow(FALSE);

	if (m_listFont.GetMruFontCount()>0)
		m_btnMruClear.EnableWindow(TRUE);
	else
		m_btnMruClear.EnableWindow(FALSE);

	if (m_listFont.GetSelectedCount()>0 && m_listFont.GetMruFontCount()>0)
		m_btnMruRemove.EnableWindow(TRUE);
	else
		m_btnMruRemove.EnableWindow(FALSE);

	if (m_listFont.GetSelectedCount()>0)
		m_btnClearSel.EnableWindow(TRUE);
	else
		m_btnClearSel.EnableWindow(FALSE);
}

void CPpPersistence::OnBtnMruAdd() 
{
	m_listFont.AddSelectedFontsToMruList();
	m_listFont.SetTopIndex(0);
	AdaptButtonsState();	
}

void CPpPersistence::OnBtnMruClear() 
{
	m_listFont.ClearMruList();
	AdaptButtonsState();	
}

void CPpPersistence::OnBtnMruPersistence() 
{
	m_listFont.EnableMruListPersistence(! m_listFont.IsMruListPersistent());
	AdaptButtonsState();	
}

void CPpPersistence::OnBtnMruRemove() 
{
	m_listFont.RemoveSelectedFontsFromMruList();	
	AdaptButtonsState();	
}

void CPpPersistence::OnBtnMruSave() 
{
	m_listFont.SaveMruListSettings();
	AdaptButtonsState();	
}

void CPpPersistence::OnBtnClearSel() 
{
	m_listFont.ClearSelection();
	AdaptButtonsState();	
}

void CPpPersistence::OnSelChangeList() 
{
	AdaptButtonsState();	
}

void CPpPersistence::OnBtnMruLoad() 
{
	m_listFont.ReloadMruListSettings();
	m_listFont.SetTopIndex(0);
	AdaptButtonsState();	
}
