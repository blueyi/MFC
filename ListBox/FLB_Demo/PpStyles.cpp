// PpStyles.cpp : implementation file
//

#include "stdafx.h"
#include "DemoFLB.h"
#include "PpStyles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
            

// CFontDialog callback function
int CFFontCount = 0;

UINT_PTR CALLBACK CFHookProc(
  HWND hdlg,      // handle to dialog box
  UINT uiMsg,     // message identifier
  WPARAM wParam,  // message parameter
  LPARAM lParam   // message parameter
)
{
	CWnd* pFntDlg = CWnd::FromHandle(hdlg);
	CWnd* pCmbBx = pFntDlg->GetDlgItem(0x470);
	if (pCmbBx)
	{
		CListBox* pLstBox = (CListBox*)(pCmbBx->GetDlgItem(0x3E8));
		if (pLstBox)
		{
			if (pLstBox->GetCount() > 0)
				CFFontCount = pLstBox->GetCount();
		}
	}
	// default processing
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CPpStyles property page

IMPLEMENT_DYNCREATE(CPpStyles, CPropertyPage)

CPpStyles::CPpStyles() : CPropertyPage(CPpStyles::IDD) ,
m_listFont(FNTLB_HAS_TOOLTIPS | FNTLB_TOOLTIPTEXT_FONT | FNTLB_TRACKING_TOOLTIP | FNTLB_MRUCUSTOMLIST, _T("MruTest"))
{
	//{{AFX_DATA_INIT(CPpStyles)
	m_TTWhat = -1;
	m_strSample = _T("");
	m_TTTracking = FALSE;
	m_hasTT = FALSE;
	m_displayGraphic = FALSE;
	m_MruType = -1;
	m_MruList = FALSE;
	m_ExpandedHeight = FALSE;
	m_MruName = _T("");
	m_listStyle = -1;
	m_officeBitmap = FALSE;
	m_TTShowSel = FALSE;
	m_TtMaxItems = _T("");
	//}}AFX_DATA_INIT
	m_psp.dwFlags &= ~PSP_HASHELP;  // Lose the Help button
}

CPpStyles::~CPpStyles()
{
}

void CPpStyles::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpStyles)
	DDX_Control(pDX, IDC_BTN_CLEARSEL, m_ClearSel);
	DDX_Control(pDX, IDC_BTN_CLEARMRU, m_btnClearMru);
	DDX_Control(pDX, IDC_LIST2, m_listFont);
	DDX_Control(pDX, IDC_CMB_LISTSTYLE, m_listStyleCtl);
	DDX_Control(pDX, IDC_CHECK_MRU, m_MruListCtl);
	DDX_Control(pDX, IDC_BTN_MRUADD, m_MruAdd);
	DDX_Control(pDX, IDC_RADIO_MRU0, m_MruTypeCtl0);
	DDX_Control(pDX, IDC_RADIO_MRU1, m_MruTypeCtl1);
	DDX_Control(pDX, IDC_RADIO_MRU2, m_MruTypeCtl2);
	DDX_Control(pDX, IDC_APPLY, m_btnApply);
	DDX_Radio(pDX, IDC_RADIO1, m_TTWhat);
	DDX_Text(pDX, IDC_EDIT1, m_strSample);
	DDX_Check(pDX, IDC_CHECK_TRACKING, m_TTTracking);
	DDX_Check(pDX, IDC_CHECK_HASTOOLTIP, m_hasTT);
	DDX_Check(pDX, IDC_CHECK_GRAPHIC, m_displayGraphic);
	DDX_Radio(pDX, IDC_RADIO_MRU0, m_MruType);
	DDX_Check(pDX, IDC_CHECK_MRU, m_MruList);
	DDX_Check(pDX, IDC_CHECK_HEIGHT, m_ExpandedHeight);
	DDX_Text(pDX, IDC_EDT_MRUNAME, m_MruName);
	DDX_CBIndex(pDX, IDC_CMB_LISTSTYLE, m_listStyle);
	DDX_Check(pDX, IDC_CHECK_BMP, m_officeBitmap);
	DDX_Check(pDX, IDC_CHK_SELECTED, m_TTShowSel);
	DDX_Text(pDX, IDC_TT_MAXITEMS, m_TtMaxItems);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpStyles, CPropertyPage)
	//{{AFX_MSG_MAP(CPpStyles)
	ON_BN_CLICKED(IDC_APPLY, OnApplyStyleChanges)
	ON_BN_CLICKED(IDC_CHECK_GRAPHIC, OnModifyData)
	ON_BN_CLICKED(IDC_BTN_MRUADD, OnBtnMruadd)
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelchangeListFont)
	ON_BN_CLICKED(IDC_BTN_SHOWFNTDLG, OnShowFontDialog)
	ON_BN_CLICKED(IDC_BTN_CLEARSEL, OnBtnClearSel)
	ON_LBN_SELCANCEL(IDC_LIST2, OnSelCancelListFont)
	ON_BN_CLICKED(IDC_BTN_CLEARMRU, OnBtnClearMru)
	ON_BN_CLICKED(IDC_CHECK_HASTOOLTIP, OnModifyData)
	ON_BN_CLICKED(IDC_CHECK_TRACKING, OnModifyData)
	ON_EN_CHANGE(IDC_EDIT1, OnModifyData)
	ON_BN_CLICKED(IDC_RADIO1, OnModifyData)
	ON_BN_CLICKED(IDC_RADIO2, OnModifyData)
	ON_BN_CLICKED(IDC_CHECK_MRU, OnModifyData)
	ON_BN_CLICKED(IDC_RADIO_MRU0, OnModifyData)
	ON_BN_CLICKED(IDC_RADIO_MRU1, OnModifyData)
	ON_BN_CLICKED(IDC_CHECK_HEIGHT, OnModifyData)
	ON_BN_CLICKED(IDC_RADIO_MRU2, OnModifyData)
	ON_EN_CHANGE(IDC_EDT_MRUNAME, OnModifyData)
	ON_CBN_SELCHANGE(IDC_CMB_LISTSTYLE, OnModifyData)
	ON_BN_CLICKED(IDC_CHECK_BMP, OnModifyData)
	ON_BN_CLICKED(IDC_CHK_SELECTED, OnModifyData)
	ON_EN_CHANGE(IDC_TT_MAXITEMS, OnChangeTtMaxItems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpStyles message handlers

BOOL CPpStyles::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_TTWhat = (m_listFont.GetFlags() & FNTLB_TOOLTIPTEXT_FONT) ? 0 : 1;
	m_strSample = m_listFont.GetSampleText();
	m_TTTracking = (m_listFont.GetFlags() & FNTLB_TRACKING_TOOLTIP) ? TRUE:FALSE;
	m_hasTT = (m_listFont.GetFlags() & FNTLB_HAS_TOOLTIPS) ? TRUE: FALSE;
	m_displayGraphic = (m_listFont.GetFlags() & FNTLB_GRAPHIC) ? TRUE:FALSE;
	m_TTShowSel = (m_listFont.GetFlags() & FNTLB_TOOLTIPSELECTED) ? TRUE: FALSE;
	m_btnApply.EnableWindow(FALSE);
	m_MruList = (m_listFont.GetFlags() & FNTLB_MRULIST) ? TRUE:FALSE;
	if ((m_listFont.GetFlags() & FNTLB_MRUGLOBALLIST) == FNTLB_MRUGLOBALLIST)
		m_MruType = 2;
	else if((m_listFont.GetFlags() & FNTLB_MRUCUSTOMLIST) == FNTLB_MRUCUSTOMLIST)
		m_MruType = 1;
	else
		m_MruType = 0;
	m_MruName = m_listFont.GetCustomMruListName();
	m_MruTypeCtl0.EnableWindow((BOOL)m_MruType);
	m_MruTypeCtl1.EnableWindow((BOOL)m_MruType);
	m_MruTypeCtl2.EnableWindow((BOOL)m_MruType);
	m_ExpandedHeight = (m_listFont.GetFlags() & FNTLB_ITEMHEIGHTEXPANDED) ? TRUE:FALSE;
	if (! m_MruList)
		m_MruAdd.EnableWindow(FALSE);
	else
	{
		if (m_listFont.GetCurSel() >= 0)
			m_MruAdd.EnableWindow(TRUE);
		else
			m_MruAdd.EnableWindow(FALSE);
	}

	DWORD dwStyle = m_listFont.GetStyle();
	if (dwStyle & LBS_NOSEL)
		m_listStyle = 3;
	else if (dwStyle & LBS_MULTIPLESEL)
		m_listStyle = 1;
	else if (dwStyle & LBS_EXTENDEDSEL)
		m_listStyle = 2;
	else
		m_listStyle = 0;

	CString str;
	str.Format("%d", m_listFont.GetTooltipMaxItems());
	m_TtMaxItems = str;

	UpdateData(FALSE);
	 
	m_listFont.Initialize();

	str.Format("%d fonts loaded", m_listFont.GetFontCount());
	SetDlgItemText(IDC_NB_FONTS, str);
	str.Format("%d fonts in MRU", m_listFont.GetMruFontCount());
	SetDlgItemText(IDC_NB_FONTSMRU, str);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPpStyles::OnApplyStyleChanges() 
{
	UpdateData(TRUE);

	m_listFont.SetTooltipMaxItems(atoi(m_TtMaxItems));

	if (m_listStyle == 3)
		m_listFont.ModifyStyle(LBS_MULTIPLESEL | LBS_EXTENDEDSEL, LBS_NOSEL);
	else if (m_listStyle == 1)
		m_listFont.ModifyStyle(LBS_NOSEL | LBS_EXTENDEDSEL, LBS_MULTIPLESEL);
	else if (m_listStyle == 2)
		m_listFont.ModifyStyle(LBS_NOSEL | LBS_MULTIPLESEL, LBS_EXTENDEDSEL);
	else 
		m_listFont.ModifyStyle(LBS_NOSEL | LBS_MULTIPLESEL | LBS_EXTENDEDSEL, NULL);

	// if a first time, don't modify the Mru properties
	DWORD dwNewFlags = m_listFont.GetFlags() & FNTLB_MRUSTYLE_MASK;
	dwNewFlags |= (m_TTWhat ? NULL : FNTLB_TOOLTIPTEXT_FONT);
	dwNewFlags |= (m_TTTracking ? FNTLB_TRACKING_TOOLTIP : NULL);
	dwNewFlags |= (m_TTShowSel ? FNTLB_TOOLTIPSELECTED : NULL);
	dwNewFlags |= (m_hasTT ? FNTLB_HAS_TOOLTIPS : NULL);
	dwNewFlags |= (m_displayGraphic ? FNTLB_GRAPHIC : NULL);
	dwNewFlags |= (m_ExpandedHeight ? FNTLB_ITEMHEIGHTEXPANDED : NULL);
	m_listFont.SetRedraw(FALSE); // redrawing is made by other modification (flags)
	if (m_officeBitmap)
		m_listFont.LoadImages(IDB_BMP_OFF11);
	else
		m_listFont.SetStdImages();
	m_listFont.SetRedraw(TRUE);
	m_listFont.SetSampleText(m_strSample);
	m_listFont.SetFlags(dwNewFlags);
	// now, modify the mru list, if needed
	if (m_MruList)
	{
		
		if (m_MruType == 0)
			m_listFont.AttachToMruFontList(NULL);
		else if (m_MruType == 1)
			m_listFont.AttachToMruFontList(m_MruName);
		else if (m_MruType == 2)
			m_listFont.AttachToMruFontList(GLOBAL_MRULIST);
	}
	else
	{
		m_listFont.DetachFromMruFontList();
	}
	m_btnApply.EnableWindow(FALSE);
	CString str;
	str.Format("%d fonts in MRU", m_listFont.GetMruFontCount());
	SetDlgItemText(IDC_NB_FONTSMRU, str);
	AdaptBtnState();
}

void CPpStyles::OnModifyData() 
{
//	UpdateData(TRUE);
	if (m_MruListCtl.GetCheck())
	{
		m_MruTypeCtl0.EnableWindow(TRUE);
		m_MruTypeCtl1.EnableWindow(TRUE);
		m_MruTypeCtl2.EnableWindow(TRUE);
	}
	else
	{
		m_MruTypeCtl0.EnableWindow(FALSE);
		m_MruTypeCtl1.EnableWindow(FALSE);
		m_MruTypeCtl2.EnableWindow(FALSE);
	}
	m_btnApply.EnableWindow(TRUE);
}

void CPpStyles::OnBtnMruadd() 
{
	m_listFont.AddSelectedFontsToMruList();
	m_listFont.SetTopIndex(0);					// so you can see that's really added !
	CString str;
	str.Format("%d fonts in MRU", m_listFont.GetMruFontCount());
	SetDlgItemText(IDC_NB_FONTSMRU, str);
	AdaptBtnState();
}

void CPpStyles::OnSelchangeListFont() 
{
	AdaptBtnState();
}

void CPpStyles::OnShowFontDialog() 
{
	CFontDialog dlgF;
	dlgF.m_cf.lpfnHook = CFHookProc;
	dlgF.DoModal();	
	if (CFFontCount)
	{
		CString str;
		str.Format("%d fonts in MS FontDialog", CFFontCount);
		SetDlgItemText(IDC_NB_FONTS_FNTDLG, str);
	}
	else
	{
		SetDlgItemText(IDC_NB_FONTS_FNTDLG, _T(""));
	}

}

void CPpStyles::OnBtnClearSel() 
{
	m_listFont.ClearSelection();
	AdaptBtnState();
}

void CPpStyles::OnSelCancelListFont() 
{
//	OnSelchangeListFont();
}

void CPpStyles::OnBtnClearMru() 
{
	m_listFont.ClearMruList();
	AdaptBtnState();	
}

void CPpStyles::AdaptBtnState()
{
	if (m_listFont.GetSelectedCount()>0 && m_listFont.HasMruList())
		m_MruAdd.EnableWindow(TRUE);
	else
		m_MruAdd.EnableWindow(FALSE);
	if (m_listFont.GetMruFontCount()>0 && m_listFont.HasMruList())
		m_btnClearMru.EnableWindow(TRUE);
	else
		m_btnClearMru.EnableWindow(FALSE);
	if (m_listFont.GetSelectedCount() > 0)
		m_ClearSel.EnableWindow(TRUE);
	else
		m_ClearSel.EnableWindow(FALSE);
}

void CPpStyles::OnChangeTtMaxItems() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (::IsWindow(m_btnApply.m_hWnd))
		m_btnApply.EnableWindow(TRUE);
}
