// BmpStatic.cpp : implementation file
//

#include "stdafx.h"
#include "static_tst.h"
#include "BmpStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpStatic

CBmpStatic::CBmpStatic() :
	m_crTrans( 0L )	//assume transparent color is black
{
}

CBmpStatic::~CBmpStatic()
{
}


BEGIN_MESSAGE_MAP(CBmpStatic, CStatic)
	//{{AFX_MSG_MAP(CBmpStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBmpStatic message handlers

void CBmpStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rDummy;

	//check if image was loaded for the first time
	if( !m_bmImg )
	{
		//create the image from resource
		m_bmImg.Create( AfxGetInstanceHandle(), GetWindowLong( m_hWnd, GWL_ID) );
		//adjust control height to the image height
		GetClientRect( rDummy );
		SetWindowPos(NULL, 0, 0, rDummy.Width(), m_bmImg.GetHeight(), SWP_NOZORDER | SWP_NOMOVE );
	}

	//draw transparent image
	m_bmImg.DrawTrans( dc.GetSafeHdc(), 0, 0, m_bmImg.GetWidth(), m_bmImg.GetHeight(), m_crTrans );

	//draw control text
	GetClientRect( rDummy );
	rDummy.left += m_bmImg.GetWidth();

	CString strTxt;
	GetWindowText( strTxt );

	int iOldBkMode = dc.SetBkMode( TRANSPARENT );	//set transparent mode for text
	HANDLE hOldFont = SelectObject( dc.GetSafeHdc(),	GetStockObject(DEFAULT_GUI_FONT) );	//select default GUI font
	dc.DrawText( strTxt, rDummy, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS );
	SelectObject( dc.GetSafeHdc(),	hOldFont );//restore old font
	dc.SetBkMode( iOldBkMode );	//restore old bk mode

}


