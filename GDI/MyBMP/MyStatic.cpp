// MyStatic.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "MyStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatic

CMyStatic::CMyStatic()
{
	m_foreColor=RGB(0,0,0);
	m_backColor=RGB(255,255,255);
	m_bTrans=TRUE;
	m_pFont=NULL;
}

CMyStatic::~CMyStatic()
{
	if(m_pFont!=NULL)
		delete m_pFont;
}

BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	//{{AFX_MSG_MAP(CMyStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers
void CMyStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	CString str;
	GetWindowText(str);
	if(m_bTrans)
		dc.SetBkMode(TRANSPARENT);
	else
		dc.SetBkColor(m_backColor);
	dc.SetTextColor(m_foreColor);
	CFont * pOldFont=NULL;
	if(m_pFont!=NULL)
		pOldFont=dc.SelectObject(m_pFont);
	dc.DrawText(str,&rect,DT_LEFT | DT_VCENTER);
	if(m_pFont!=NULL)
		dc.SelectObject(pOldFont);
}
void CMyStatic::SetForeColor(COLORREF foreColor)
{
	m_foreColor=foreColor;
}
COLORREF CMyStatic::GetForeColor()
{
	return m_foreColor;
}
void CMyStatic::SetBackColor(COLORREF backColor)
{
	m_backColor=backColor;
}
COLORREF CMyStatic::GetBackColor()
{
	return m_backColor;
}
void CMyStatic::SetTransMode(BOOL bTrans)
{
	m_bTrans=bTrans;
}
BOOL CMyStatic::IsTrans()
{
	return m_bTrans;
}
void CMyStatic::SetStyle(COLORREF foreColor,COLORREF backColor,BOOL bTrans)
{
	SetForeColor(foreColor);
	SetBackColor(backColor);
	SetTransMode(bTrans);
}
void CMyStatic::SetFont(int nWeight,BOOL bItalic,BOOL bUnderlined,TCHAR * pFontName)
{
	if(m_pFont!=NULL)
		delete m_pFont;
	m_pFont = new CFont;
	m_pFont->CreateFont(0,0,0,0,nWeight,bItalic,bUnderlined,0,ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,pFontName);
}