// WizFontExampleStatic.cpp : implementation file
//

#include "stdafx.h"
#include "fontsTest.h"
#include "WizFontExampleStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizFontExampleStatic

CWizFontExampleStatic::CWizFontExampleStatic()
{
}

CWizFontExampleStatic::~CWizFontExampleStatic()
{
}


BEGIN_MESSAGE_MAP(CWizFontExampleStatic, CStatic)
	//{{AFX_MSG_MAP(CWizFontExampleStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizFontExampleStatic message handlers
void CWizFontExampleStatic::SetFont (LPCTSTR fontname, int pp_size, BOOL bItal, BOOL bBold, BOOL bUnder)
{
	memset (&m_lf, 0, sizeof(m_lf));
	m_lf.lfCharSet	= DEFAULT_CHARSET;
	strcpy(m_lf.lfFaceName, fontname);
	m_lf.lfHeight = pp_size*10;
	m_lf.lfItalic = bItal;
	m_lf.lfUnderline = bUnder;
	m_lf.lfWeight = (bBold) ? FW_BOLD : FW_REGULAR;
	// BLOCK
		{
		CClientDC dc (this);
		if (m_Font.GetSafeHandle())
			m_Font.DeleteObject();

		if (!m_Font.CreatePointFontIndirect(&m_lf, &dc))
			{ ASSERT(0); return; }
		}

	CString text;
	TCHAR bold_ch = (bBold) ?  'B' : ' ';
	TCHAR ital_ch = (bItal) ?  'I' : ' ';
	TCHAR Under_ch = (bUnder) ?  'U' : ' ';
	text.Format (_T("%s size % d %c %c %c"), fontname, pp_size, bold_ch, ital_ch, Under_ch);
	//SetWindowText(text);
	m_strSample = text;
	//CEdit::SetFont(&theFont, TRUE);
	CWnd* parent = GetParent();
	if (parent)
		{
		CRect r;
		GetWindowRect(r);
		parent->ScreenToClient(&r);
		parent->InvalidateRect(r);
		parent->UpdateWindow();
		}
	Invalidate(TRUE);
}


void CWizFontExampleStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rcText;
	CFont *oldFont;
	CSize TextExtent;
	COLORREF crText;
	TEXTMETRIC tm;
	int bkMode, len, x, y;
	CString strSample = _T("AaBbYyZz ");

	//strSample.LoadString(AFX_IDS_SAMPLETEXT);
	strSample += m_strSample;

	// If there is no sample font abort
	if (!m_Font.GetSafeHandle())
		return;

	// Get the bounding box
	GetClientRect( &rcText );

	// Select the new font and colors into the dc
	oldFont = dc.SelectObject( &m_Font );
	crText = dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
	bkMode = dc.SetBkMode(TRANSPARENT);

	// Calculate the position of the text
	dc.GetTextMetrics( &tm );

	len = strSample.GetLength();
	TextExtent = dc.GetTextExtent(strSample, len);
	TextExtent.cy = tm.tmAscent - tm.tmInternalLeading;

	if ((TextExtent.cx >= (rcText.right - rcText.left)) ||
			(TextExtent.cx <= 0))
		x = rcText.left;
	else
		x = rcText.left + ((rcText.right - rcText.left) - TextExtent.cx) / 2;

	y = min(rcText.bottom,
		rcText.bottom - ((rcText.bottom - rcText.top) - TextExtent.cy) / 2);

	// Draw it
	dc.ExtTextOut(x, y - (tm.tmAscent), ETO_CLIPPED, &rcText,
		strSample, len, NULL);

	// Put the DC back the way it was
	dc.SetBkMode(bkMode);
	dc.SetTextColor(crText);

	if (oldFont)
		dc.SelectObject(oldFont);
}
