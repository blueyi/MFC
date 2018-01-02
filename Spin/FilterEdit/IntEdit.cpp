#include "StdAfx.h"
#include "IntEdit.h"

namespace FilterEdit
{
bool CIntEdit::m_bInitialised = false;
CRegEx CIntEdit::m_RegEx;

CIntEdit::CIntEdit () :
	CBaseEdit (&m_RegEx)
{
	if (!m_bInitialised)
	{
		CString strRegEx (_T("0|[-+]?[1-9][0-9]*"));

		m_RegEx.assign (strRegEx);
		m_bInitialised = true;
	}
}

CIntEdit::~CIntEdit ()
{
}

int CIntEdit::GetValue () const
{
	CString strInt;

	GetWindowText (strInt);
	return _tstoi (strInt);
}
}
