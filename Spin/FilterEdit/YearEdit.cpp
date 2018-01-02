#include "StdAfx.h"
#include "YearEdit.h"

namespace FilterEdit
{
bool CYearEdit::m_bInitialised = false;
CRegEx CYearEdit::m_RegEx;

CYearEdit::CYearEdit () :
	CBaseEdit (&m_RegEx)
{
	if (!m_bInitialised)
	{
		CString strRegEx (_T("175[3-9]|17[6-9][0-9]|1[8-9][0-9]{2}|")
			_T("[2-9][0-9]{3}"));

		m_RegEx.assign (strRegEx);
		m_bInitialised = true;
	}
}

CYearEdit::~CYearEdit ()
{
}

int CYearEdit::GetValue () const
{
	CString strValue;

	GetWindowText(strValue);
	return atoi(strValue);
}

BEGIN_MESSAGE_MAP(CYearEdit, CBaseEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

void CYearEdit::OnKillFocus (CWnd *pNewWnd)
{
	if (GetWindowTextLength() < 4)
	{
		const int iYear = COleDateTime::GetCurrentTime().GetYear();
		CString strYear;

		strYear.Format("%d", iYear);
		SetWindowText(strYear);
	}

	CBaseEdit::OnKillFocus (pNewWnd);
}
}
