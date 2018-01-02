// NumericEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NumericEdit.h"


// CNumericEdit

IMPLEMENT_DYNAMIC(CNumericEdit, CEdit)

///
/// <summary></summary>
///
CNumericEdit::CNumericEdit()
{
	// determine the decimal delimiter buffer size
	const int nBuffLen = ::GetLocaleInfo( LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, NULL, 0 );
	_ASSERT( nBuffLen > 0 );

	// get the decimal number delimiter
	const int nResult = ::GetLocaleInfo( LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, 
		m_strDelim.GetBuffer(nBuffLen), nBuffLen );
	_ASSERT(nResult != 0);
	m_strDelim.ReleaseBuffer();
}

///
/// <summary></summary>
///
CNumericEdit::~CNumericEdit()
{
}


BEGIN_MESSAGE_MAP(CNumericEdit, CEdit)	
	ON_WM_CHAR()	
END_MESSAGE_MAP()



// CNumericEdit message handlers

///
/// <summary></summary>
///
void CNumericEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if( nChar == m_strDelim )
	{
		CString strText;
		GetWindowText( strText );

		if( strText.IsEmpty() )
		{
			SetWindowText( (_T("0") + m_strDelim) );
			SetSel( 2, 2, FALSE );
			return;
		}
		else
		{
			// if the decimal point already entered, not allow enter more points
			if( strText.Find( m_strDelim ) >= 0 )
				return;
		}
	}

	// 8 - back space
	// 46 - .
	// 48 - 1
	// 57 - 0
	if( (nChar == m_strDelim) || (nChar >= '0' && nChar <= '9') || (nChar == 8) )
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}