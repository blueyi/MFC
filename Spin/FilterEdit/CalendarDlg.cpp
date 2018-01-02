// CalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CalendarDlg.h"
#include "DateTimeEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace FilterEdit
{
/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog
CCalendarDlg::CCalendarDlg(CDateTimeEdit *pEdit, CWnd* pParent /*=NULL*/) :
	CDialog (),
	m_pEdit (pEdit)
{
	// Dynamically create dialog
	std::vector<char> memory;
	DLGTEMPLATE *pDlgTemplate = 0;
	std::size_t size = sizeof(DLGTEMPLATE);
	CFont *pFont = pParent->GetFont();
	LOGFONT lf;

	m_pParentWnd = pParent;
	pFont->GetLogFont(&lf);
	memory.resize (size);
	pDlgTemplate = reinterpret_cast<DLGTEMPLATE *>(&memory.front());
	pDlgTemplate->style = DS_SETFONT | DS_SETFOREGROUND | DS_3DLOOK |
		WS_POPUP | WS_BORDER | WS_VISIBLE;
	pDlgTemplate->dwExtendedStyle = 0;
	pDlgTemplate->cdit = 0;
	pDlgTemplate->x = 0;
	pDlgTemplate->y = 0;
	pDlgTemplate->cx = 90;
	pDlgTemplate->cy = 80;
	memory.resize(size + sizeof(WORD));
	// No Menu
	*(reinterpret_cast<WORD *>(&memory[size])) = 0;
	size = memory.size();
	memory.resize(size + sizeof(WORD));
	// Default Windows Class
	*(reinterpret_cast<WORD *>(&memory[size])) = 0;
	size = memory.size();
	memory.resize(size + sizeof(TCHAR));
	// Caption
	*(reinterpret_cast<TCHAR *>(&memory[size])) = 0;
	size = memory.size();
	memory.resize(size + sizeof(WORD));
	// Font Size
	*(reinterpret_cast<WORD *>(&memory[size])) = 8;
	size = memory.size();

	const std::size_t iFontLen = _tcslen (lf.lfFaceName);

	memory.resize (size + sizeof(TCHAR) * (iFontLen + 1));
	// Font Name
	::memcpy (reinterpret_cast<TCHAR *>(&memory[size]),
		lf.lfFaceName, sizeof(TCHAR) * (iFontLen + 1));

	// Modeless dialog
	CreateIndirect (reinterpret_cast<DLGTEMPLATE *>(&memory.front()),
		m_pParentWnd);
	// Modal dialog
	//InitModalIndirect (reinterpret_cast<DLGTEMPLATE *>(&memory.front()),
	//	m_pParentWnd);
}

void CCalendarDlg::SetDate (const int iDay, const int iMonth, const int iYear)
{
	if (iDay > 0 && iMonth > 0 && iYear >= 0)
	{
		SYSTEMTIME st;

		::memset (&st, 0, sizeof(st));
		st.wDay = static_cast<WORD>(iDay);
		st.wMonth = static_cast<WORD>(iMonth);
		st.wYear = static_cast<WORD>(iYear);
		m_Calendar.SetCurSel (&st);
	}
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CCalendarDlg::PostNcDestroy ()
{
	const int iLen = m_pEdit->GetWindowTextLength ();

	m_pEdit->m_pCalendarDlg = 0;
	m_pEdit->SetFocus ();
	m_pEdit->SetSel (iLen, iLen);
	delete this;
}

BEGIN_MESSAGE_MAP(CCalendarDlg, CDialog)
	//{{AFX_MSG_MAP(CCalendarDlg)
	ON_WM_KILLFOCUS()
	ON_NOTIFY(MCN_SELECT, 123, OnSelectDaypicker)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg message handlers
BOOL CCalendarDlg::OnInitDialog()
{
	CRect rect;
	CRect EditRect;

	CDialog::OnInitDialog();
	GetWindowRect (&rect);
	m_pParentWnd->GetWindowRect (&EditRect);
	MoveWindow (EditRect.left, EditRect.bottom, rect.right - rect.left,
		rect.bottom - rect.top);
	m_Calendar.Create (WS_TABSTOP | WS_VISIBLE, CRect(0, 0,
		rect.right - rect.left, rect.bottom - rect.top), this, 123);
	m_Calendar.SetFont(m_pParentWnd->GetFont());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCalendarDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);
	DestroyWindow ();
}

void CCalendarDlg::OnSelectDaypicker (NMHDR *pNotifyStruct, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE> (pNotifyStruct);
	const bool bProcessChars = m_pEdit->GetProcessChars ();
	bool bValid = true;

	m_pEdit->SetProcessChars (false);
	bValid = m_pEdit->SetDate (pSelChange->stSelStart.wYear,
		pSelChange->stSelStart.wMonth, pSelChange->stSelStart.wDay);
	m_pEdit->SetProcessChars (bProcessChars);
	m_pEdit->IsInputValid();
	*pResult = 0;
	DestroyWindow ();
}
}
