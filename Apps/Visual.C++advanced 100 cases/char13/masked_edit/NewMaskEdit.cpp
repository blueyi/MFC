// NewMaskEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NewMaskEdit.h"

#include <ctype.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

NewMaskEdit::NewMaskEdit()
{
	m_bLastKeyWasDelete = false;
	m_bLastKeyWasBackspace = false;

	m_cPlaceHolder = '_';
}

NewMaskEdit::~NewMaskEdit()
{
}

void NewMaskEdit::setMask(LPCTSTR pszMask, char cPlaceHolder)
{
	m_strMaskText = pszMask;

	m_strSaveText.Empty();

	int nIndex = 0;
	while (nIndex < m_strMaskText.GetLength())
	{
		if (isMaskChar(nIndex))
			m_strSaveText += m_strMaskText[nIndex];
		else
			m_strSaveText += m_cPlaceHolder;

		nIndex++;
	}

	CWnd::SetWindowText(m_strSaveText);
}

void NewMaskEdit::SetWindowText(LPCTSTR pszText)
{
	setText(pszText);
}

void NewMaskEdit::setText(LPCTSTR pszText)
{
	CString strText(pszText);

	m_strSaveText.Empty();

	int nMaskIndex = 0;
	int nTextIndex = 0;

	while (nMaskIndex < m_strMaskText.GetLength())
	{
		if (!isMaskChar(nMaskIndex))
		{
			if (nTextIndex < strText.GetLength())
				m_strSaveText += strText[nTextIndex++];
			else
				m_strSaveText += m_cPlaceHolder;
		}
		else
			m_strSaveText += m_strMaskText[nMaskIndex];

		nMaskIndex++;
	}

	CWnd::SetWindowText(m_strSaveText);
}

CString NewMaskEdit::getText()
{
	CString strText;

	int nMaskIndex = 0;
	while (nMaskIndex < m_strMaskText.GetLength())
	{
		if (!isMaskChar(nMaskIndex))
			strText += m_strSaveText[nMaskIndex];

		nMaskIndex++;
	}
	return strText;
}


BEGIN_MESSAGE_MAP(NewMaskEdit, CEdit)
	//{{AFX_MSG_MAP(NewMaskEdit)
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewMaskEdit message handlers

bool NewMaskEdit::isMaskChar(int nPos)
{
	ASSERT(nPos < m_strMaskText.GetLength());

	return (m_strMaskText[nPos] != '#' &&
			m_strMaskText[nPos] != '?'); // Add new masks as needed
}

bool NewMaskEdit::getReplacementChar(int nPos, char cWant, char& cGet)
{
	if (nPos >= m_strMaskText.GetLength())
		return false;

	switch (m_strMaskText[nPos])
	{
	case '#':
		if (0 == isdigit(cWant))
			return false;

		cGet = cWant;
		break;

	case '?':
		if (0 == isalpha(cWant))
			return false;

		cGet = cWant;
		break;

	// Add new masks as needed

	default:
		cGet = m_strMaskText[nPos];
		break;
	}
	return true;
}

int NewMaskEdit::gotoNextEntryChar(int nPos)
{
	if (m_bLastKeyWasBackspace)
	{
		nPos--;

		while (nPos >= 0 && isMaskChar(nPos))
			nPos--;

		nPos++;
	}
	else
	{
		while (nPos < m_strMaskText.GetLength() && isMaskChar(nPos))
			nPos++;
	}
	return nPos;
}

void NewMaskEdit::OnUpdate() 
{
	int nStart, nEnd;
	GetSel(nStart, nEnd);

	CString strEditText;
	GetWindowText(strEditText);

	if (strEditText == m_strSaveText)
		return;

	if (m_bLastKeyWasBackspace)
	{
		m_strSaveText.SetAt(nStart, isMaskChar(nStart) ? m_strMaskText[nStart] : m_cPlaceHolder);

		CWnd::SetWindowText(m_strSaveText);
		int nNext = gotoNextEntryChar(nStart);
		SetSel(nNext, nNext);
	}
	else if (m_bLastKeyWasDelete)
	{
		m_strSaveText.SetAt(nStart, isMaskChar(nStart) ? m_strMaskText[nStart] : m_cPlaceHolder);

		CWnd::SetWindowText(m_strSaveText);
		int nNext = gotoNextEntryChar(nStart + 1);
		SetSel(nNext, nNext);
	}
	else
	{
		if (nStart - 1 < 0)
			return;

		char cWanted = strEditText[nStart - 1];

		char cReplace = 0;

		if (getReplacementChar(nStart - 1, cWanted, cReplace))
		{
			if (m_strSaveText.GetLength() < nStart)
				m_strSaveText.GetBufferSetLength(nStart);

			m_strSaveText.SetAt(nStart - 1, cReplace);
			m_strSaveText.ReleaseBuffer();
		}

		CWnd::SetWindowText(m_strSaveText);
		int nNext = gotoNextEntryChar(nStart);
		SetSel(nNext, nNext);
	}
}

void NewMaskEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_bLastKeyWasDelete = (VK_DELETE == nChar);
	m_bLastKeyWasBackspace = (VK_BACK == nChar);
	
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
