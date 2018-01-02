// cstm2dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PropSheet Wizard.h"
#include "cstm2dlg.h"
#include "PropSheet Wizardaw.h"
#include "PageDlg.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef TBSTYLE_TRANSPARENT
#define TBSTYLE_TRANSPARENT 0x0800
#endif	//TBSTYLE_TRANSPARENT

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog


CCustom2Dlg::CCustom2Dlg()
	: CAppWizStepDlg(CCustom2Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom2Dlg)
	m_pageSize = 1;
	m_title = _T("");
	//}}AFX_DATA_INIT
}


void CCustom2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom2Dlg)
	DDX_Control(pDX, IDC_FRAME_TOOLBAR, m_frame);
	DDX_Control(pDX, IDC_LIST_PAGES, m_pages);
	DDX_Radio(pDX, IDC_RADIO_SMALLPAGES, m_pageSize);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_title);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom2Dlg::OnDismiss()
{
	if (!UpdateData ())
		return (FALSE);

	if (m_title.IsEmpty ())
		return (FALSE);

	DefineStringMacro (_T ("SHEET_TITLE"), m_title);

	for (int i = 0;i < m_pages.GetItemCount ();i++)
	{
		CString file;
		DefineStringMacro (_T ("PAGE_CAPTION"), i, m_pages.GetItemText (i, 0));
		DefineStringMacro (_T ("PAGE_CLASS"), i, file = m_pages.GetItemText (i, 1));
		if (file[0] == TCHAR ('C'))
			file = file.Mid (1);
		DefineStringMacro (_T ("PAGE_FILE"), i, file);
		file.SetAt (0, tolower (file[0]));
		DefineStringMacro (_T ("PAGE_VAR"), i, _T ("m_") + file);
		file.MakeUpper ();
		DefineStringMacro (_T ("PAGE_ID"), i, _T ("IDD_") + file);
		DefineStringMacro (_T ("PAGE_BMP"), i, _T ("IDB_") + file);
		if (!i)
			DefineStringMacro (_T ("PAGE_FIRST_BMP"), _T ("IDB_") + file);
		DefineIntMacro (_T ("PAGE_VAL"), i, 1000 + i);
		DefineIntMacro (_T ("PAGE_ITERATOR"), i, i + 1);
	}

	int nPages = m_pages.GetItemCount (), nClasses = nPages + 2, nIndex = nPages;
	DefineIntMacro (_T ("NUM_PAGES"), nPages);
	CString sAbout;
	if (PropSheetWizardaw.m_Dictionary.Lookup (_T ("ABOUT_BOX"), sAbout))
	{
		DefineIntMacro (_T ("ABOUT_NUM"), ++nIndex);
		nClasses++;
	}
	DefineIntMacro (_T ("NUM_CLASSES"), nClasses);
	DefineIntMacro (_T ("NUM_RESOURCES"), nClasses - 1 - !PropSheetWizardaw.m_Dictionary.Lookup (_T ("SEND_TO_TASKBAR"), sAbout));
	DefineIntMacro (_T ("MAINSHEET_NUM"), ++nIndex);
	DefineIntMacro (_T ("APP_NUM"), ++nIndex);

	DefineBoolMacro (_T ("SMALL_PAGE"), m_pageSize == 0);
	DefineBoolMacro (_T ("MEDIUM_PAGE"), m_pageSize == 1);
	DefineBoolMacro (_T ("LARGE_PAGE"), m_pageSize == 2);

	return (TRUE);	// return FALSE if the dialog shouldn't be dismissed
}

BOOL CCustom2Dlg::PreTranslateMessage (MSG* pMsg)
{
	// Let the ToolTip process this message.
	m_ctrlTooltip.RelayEvent (pMsg);

	return CAppWizStepDlg::PreTranslateMessage (pMsg);
}

BEGIN_MESSAGE_MAP(CCustom2Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom2Dlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PAGES, OnItemchangedListPages)
	ON_COMMAND(IDC_PAGE_NEW, OnPageNew)
	ON_COMMAND(IDC_PAGE_MODIFY, OnPageModify)
	ON_COMMAND(IDC_PAGE_DELETE, OnPageDelete)
	ON_COMMAND(IDC_PAGE_MOVEUP, OnPageMoveUp)
	ON_COMMAND(IDC_PAGE_MOVEDOWN, OnPageMoveDown)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_LARGEPAGES, OnChangeSize)
	ON_BN_CLICKED(IDC_RADIO_MEDIUMPAGES, OnChangeSize)
	ON_BN_CLICKED(IDC_RADIO_SMALLPAGES, OnChangeSize)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PAGES, OnDblclkListPages)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0x0000, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0x0000, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg message handlers

BOOL CCustom2Dlg::OnInitDialog() 
{
	PropSheetWizardaw.m_Dictionary.Lookup (_T ("Root"), m_title);
	CAppWizStepDlg::OnInitDialog();

	// Create the ToolTip control.
	m_ctrlTooltip.Create (this);
	m_ctrlTooltip.Activate (TRUE);

	// TODO: Use one of the following forms to add controls:
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_EDIT_TITLE), IDS_CUSTOM2_EDIT_TITLE_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_RADIO_SMALLPAGES), IDS_CUSTOM2_RADIO_SMALLPAGES_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_RADIO_MEDIUMPAGES), IDS_CUSTOM2_RADIO_MEDIUMPAGES_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_RADIO_LARGEPAGES), IDS_CUSTOM2_RADIO_LARGEPAGES_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_LIST_PAGES), IDS_CUSTOM2_LIST_PAGES_TIP);
	m_ctrlTooltip.AddTool (&m_toolBar, LPSTR_TEXTCALLBACK);

	m_toolBar.SetToolTips (&m_ctrlTooltip);
	CRect r;
	m_frame.GetWindowRect (r);
	CWnd *pParent = this;
	pParent->ScreenToClient (r);
	r.InflateRect (0, 2);
	m_toolBar.Create (WS_CHILD|WS_VISIBLE|CCS_NOPARENTALIGN|CCS_NODIVIDER|CCS_NORESIZE|TBSTYLE_TRANSPARENT|TBSTYLE_TOOLTIPS, r, pParent, IDR_TOOLBAR);
	m_toolBar.SetButtonSize (CSize (21, 18));
	m_toolBar.SetBitmapSize (CSize (14, 12));
	VERIFY (m_toolBar.AddBitmap (5, IDR_TOOLBAR) != -1);
	for (int i = 0;i < 5;i++)
	{
		TBBUTTON tb;
		tb.iString = 0;
		tb.fsState = TBSTATE_ENABLED;
		tb.fsStyle = TBSTYLE_BUTTON;
		tb.dwData = 0;
		tb.iBitmap = i;
		tb.idCommand = IDC_PAGE_NEW + i;
		VERIFY (m_toolBar.AddButtons (1, &tb));
	}
	m_toolBar.AutoSize ();
	m_toolBar.SetWindowPos (NULL, r.left, r.top, r.Width (), r.Height (), SWP_NOZORDER);

	m_pages.ModifyStyle (0, LVS_SHOWSELALWAYS);
	m_pages.GetClientRect (r);
	m_pages.InsertColumn (0, _T ("Page Caption"), LVCFMT_LEFT, r.Width () / 2);
	m_pages.InsertColumn (1, _T ("Page Class"), LVCFMT_LEFT, r.Width () / 2);

	m_pages.DeleteAllItems ();
	CString root, page;
	PropSheetWizardaw.m_Dictionary.Lookup (_T ("Root"), root);
	m_pages.InsertItem (0, root + _T (" Page"));
	PropSheetWizardaw.m_Dictionary.Lookup (_T ("Safe_root"), root);
	root.SetAt (0, toupper (root[0]));
	page = _T ("C") + root + _T ("Page");
	root.SetAt (0, tolower (root[0]));
	m_pages.SetItemText (0, 1, page);

	UpdateControls ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustom2Dlg::OnItemchangedListPages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView->uChanged & LVIF_STATE)
		UpdateControls ();
	
	*pResult = 0;
}

void CCustom2Dlg::OnPageMoveUp() 
{
	int nSelect = m_pages.GetNextItem (-1, LVNI_SELECTED|LVNI_FOCUSED);
	if (nSelect > 0)
	{
		CString s1 = m_pages.GetItemText (nSelect, 0), s2 = m_pages.GetItemText (nSelect, 1);
		m_pages.DeleteItem (nSelect);
		nSelect = m_pages.InsertItem (nSelect - 1, s1);
		m_pages.SetItemText (nSelect, 1, s2);
		m_pages.SetItemState (nSelect, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	}
	UpdateControls ();
}

void CCustom2Dlg::OnPageMoveDown() 
{
	int nSelect = m_pages.GetNextItem (-1, LVNI_SELECTED|LVNI_FOCUSED);
	if (nSelect < m_pages.GetItemCount () - 1)
	{
		CString s1 = m_pages.GetItemText (nSelect, 0), s2 = m_pages.GetItemText (nSelect, 1);
		m_pages.DeleteItem (nSelect);
		nSelect = m_pages.InsertItem (nSelect + 1, s1);
		m_pages.SetItemText (nSelect, 1, s2);
		m_pages.SetItemState (nSelect, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	}
	UpdateControls ();
}

void CCustom2Dlg::OnPageNew() 
{
	CPageDlg dlg;
	if (dlg.DoModal () == IDOK)
	{
		for (int i = m_pages.GetItemCount ();--i >= 0;)
		{
			CString f1 = m_pages.GetItemText (i, 1),
					f2 = dlg.m_class;
			if (f1 == f2)
			{
				CString msg;
				AfxFormatString1 (msg, IDS_CLASS_EXIST, dlg.m_class);
				AfxMessageBox (msg, MB_OK|MB_ICONHAND);
				return;
			}
			CString szClassOld = f1;
			if (f1[0] == 'C')
				f1 = f1.Mid (1);
			if (f2[0] == 'C')
				f2 = f2.Mid (1);
			if (f1 == f2)
			{
				CString msg;
				AfxFormatString2 (msg, IDS_FILE_EXIST, f1, szClassOld);
				AfxMessageBox (msg, MB_OK|MB_ICONHAND);
				return;
			}
		}
		int nSelect = m_pages.GetNextItem (-1, LVNI_SELECTED|LVNI_FOCUSED);
		nSelect = m_pages.InsertItem (nSelect + 1, dlg.m_caption);
		m_pages.SetItemText (nSelect, 1, dlg.m_class);
		m_pages.SetItemState (nSelect, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		UpdateControls ();
	}
}

void CCustom2Dlg::OnPageModify() 
{
	int nSelect = m_pages.GetNextItem (-1, LVNI_SELECTED|LVNI_FOCUSED);
	if (nSelect < 0)
		return;
	CPageDlg dlg;
	dlg.m_caption = m_pages.GetItemText (nSelect, 0);
	dlg.m_class = m_pages.GetItemText (nSelect, 1);
	if (dlg.DoModal () == IDOK)
	{
		for (int i = m_pages.GetItemCount ();--i >= 0;)
		{
			if (i == nSelect)
				continue;
			CString f1 = m_pages.GetItemText (i, 1),
					f2 = dlg.m_class;
			if (f1 == f2)
			{
				CString msg;
				AfxFormatString1 (msg, IDS_CLASS_EXIST, dlg.m_class);
				AfxMessageBox (msg, MB_OK|MB_ICONHAND);
				return;
			}
			CString szClassOld = f1;
			if (f1[0] == 'C')
				f1 = f1.Mid (1);
			if (f2[0] == 'C')
				f2 = f2.Mid (1);
			if (f1 == f2)
			{
				CString msg;
				AfxFormatString2 (msg, IDS_FILE_EXIST, f1, szClassOld);
				AfxMessageBox (msg, MB_OK|MB_ICONHAND);
				return;
			}
		}
		m_pages.SetItemText (nSelect, 0, dlg.m_caption);
		m_pages.SetItemText (nSelect, 1, dlg.m_class);
		m_pages.SetItemState (nSelect, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		UpdateControls ();
	}
}

void CCustom2Dlg::OnPageDelete() 
{
	int nSelect = m_pages.GetNextItem (-1, LVNI_SELECTED|LVNI_FOCUSED);
	if (nSelect >= 0)
	{
		m_pages.DeleteItem (nSelect);
		m_pages.SetItemState (nSelect, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		if (nSelect >= m_pages.GetItemCount ())
			nSelect = m_pages.GetItemCount () - 1;
		if (nSelect >= 0)
			m_pages.SetItemState (nSelect, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		UpdateControls ();
	}
}

void CCustom2Dlg::UpdateControls ()
{
	int nSelect = m_pages.GetNextItem (-1, LVNI_SELECTED);
	m_toolBar.EnableButton (IDC_PAGE_MODIFY, nSelect >= 0);
	m_toolBar.EnableButton (IDC_PAGE_DELETE, nSelect >= 0 && m_pages.GetItemCount () > 1);
	m_toolBar.EnableButton (IDC_PAGE_MOVEUP, nSelect > 0);
	m_toolBar.EnableButton (IDC_PAGE_MOVEDOWN, nSelect >= 0 && nSelect < m_pages.GetItemCount () - 1);
}

#define STEP2_LEFT				8
#define STEP2_TOP				72
#define STEP2_WIDTH				179
#define STEP2_HEIGHT			180

// Coordinates for yellow rectangle in dialog-box units
#define RIGHT_YELLOW_DLGU	124
#define BOTTOM_YELLOW_DLGU	197

void CCustom2Dlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CDC mdc;
	mdc.CreateCompatibleDC (&dc);
	
	CRect rect (0, 0, RIGHT_YELLOW_DLGU+1, BOTTOM_YELLOW_DLGU+1);
	MapDialogRect (&rect);
	dc.DPtoLP (&rect);
	CBitmap bmp, *ob;
	bmp.CreateCompatibleBitmap (&dc, rect.right, rect.bottom);
	ob = mdc.SelectObject (&bmp);
	PaintBackground (mdc, this);
	UINT nBmpID;
	switch (m_pageSize)
	{
	case 0:
		nBmpID = IDB_STEP2SMALL;
		break;
	case 2:
		nBmpID = IDB_STEP2LARGE;
		break;
	default:
		nBmpID = IDB_STEP2MEDIUM;
		break;
	}
	PaintBitmap (nBmpID, STEP2_LEFT, STEP2_TOP, STEP2_WIDTH, STEP2_HEIGHT, mdc);
	dc.BitBlt (rect.left, rect.top, rect.Width (), rect.Height (), &mdc, rect.left, rect.top, SRCCOPY);
	mdc.SelectObject (ob);
}

void CCustom2Dlg::OnChangeSize() 
{
	if (UpdateData ())
	{
		// Invalidate the portion of this dialog on which we draw the picture
		CRect rect (STEP2_LEFT, STEP2_TOP, STEP2_LEFT + STEP2_WIDTH, STEP2_TOP + STEP2_HEIGHT);
		InvalidateRect (rect, FALSE);
		RedrawWindow (rect, NULL, RDW_UPDATENOW);
		UpdateControls ();
	}
}

void CCustom2Dlg::OnDblclkListPages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int index = m_pages.GetNextItem (-1, LVNI_SELECTED);
	if (index >= 0 && index < m_pages.GetItemCount ())
		OnPageModify ();
	
	*pResult = 0;
}

BOOL CCustom2Dlg::OnToolTipText(UINT nId, NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	TOOLTIPTEXTA *pTTTA = (TOOLTIPTEXTA *)pNMHDR;
	TOOLTIPTEXTW *pTTTW = (TOOLTIPTEXTW *)pNMHDR;

	UINT nID = pNMHDR->idFrom - IDC_PAGE_NEW + IDS_CUSTOM2_PAGE_NEW_TIP;
	if (pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW)
	{
		CString strTipText;
		strTipText.LoadString (nID);
		static CHAR szBuffer[1000];
		static WCHAR wszBuffer[1000];
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			lstrcpy (szBuffer, strTipText);
			pTTTA->lpszText = szBuffer;
		}
		else
		{
			_mbstowcsz (wszBuffer, strTipText, strTipText.GetLength () + 1);
			pTTTW->lpszText = wszBuffer;
		}	
	}
	return (FALSE);
}