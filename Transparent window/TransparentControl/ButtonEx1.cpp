// ButtonEx1.cpp : implementation file
//

#include "stdafx.h"
#include "TransparentControl.h"
#include "ButtonEx1.h"


// CButtonEx1

IMPLEMENT_DYNAMIC(CButtonEx1, CButton)
CButtonEx1::CButtonEx1()
{
	m_bTracking = FALSE;
}

CButtonEx1::~CButtonEx1()
{
}


BEGIN_MESSAGE_MAP(CButtonEx1, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()



// CButtonEx1 message handlers


void CButtonEx1::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  Add your code to draw the specified item
	

	CDC dc;
	dc.Attach( lpDrawItemStruct->hDC);
	CRect rtBtn( lpDrawItemStruct->rcItem);

	BITMAP bmpInfo;
	m_bitmapNor.GetBitmap( &bmpInfo);

	CDC memdc;
	memdc.CreateCompatibleDC( &dc);
	CBitmap membmp;
	membmp.CreateCompatibleBitmap( &dc, rtBtn.Width(), rtBtn.Height());
	CBitmap* bmpOld = ( CBitmap*) memdc.SelectObject( &membmp);

	m_objTransparent.TransparentBk( memdc.GetSafeHdc(), GetSafeHwnd());
	CFont* pOldFont = ( CFont*)memdc.SelectObject( GetFont());

	if ( m_bTracking )
	{
		CDC dctemp;
		dctemp.CreateCompatibleDC( &dc);
		dctemp.SelectObject(m_bitmapOver);
		
		memdc.TransparentBlt( 0,0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &dctemp, 0,0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255,0,255));
	}

	if (  lpDrawItemStruct->itemState & ODS_SELECTED  )
	{
		CDC dctemp;
		dctemp.CreateCompatibleDC( &dc);
		dctemp.SelectObject(m_bitmapDown);
		memdc.TransparentBlt( 0,0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &dctemp, 0,0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255,0,255));
	}
	else if ( !m_bTracking)
	{
		CDC dctemp;
		dctemp.CreateCompatibleDC( &dc);
		dctemp.SelectObject(m_bitmapNor);
		memdc.TransparentBlt( 0,0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &dctemp, 0,0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255,0,255));

	}

	CString strText;
	GetWindowText( strText);
	CRect rtText;
	GetClientRect( &rtText);
	memdc.SetBkMode( TRANSPARENT);
	memdc.DrawText( strText, &rtText, DT_CENTER|DT_SINGLELINE |DT_VCENTER);

	dc.BitBlt( 0,0, rtBtn.Width(), rtBtn.Height(), &memdc, 0,0, SRCCOPY);
	memdc.SelectObject( bmpOld);
	memdc.SelectObject( pOldFont);
}

void CButtonEx1::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CButton::PreSubclassWindow();

	m_objTransparent.Install( GetSafeHwnd());
	m_bitmapNor.LoadBitmap( IDB_BITMAP4);
	m_bitmapOver.LoadBitmap( IDB_BITMAP5);
	m_bitmapDown.LoadBitmap( IDB_BITMAP3);
}

BOOL CButtonEx1::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CButton::OnEraseBkgnd(pDC);
}

void CButtonEx1::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CButton::OnMouseMove(nFlags, point);

	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof (tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
		Invalidate(FALSE);
	}

}

LRESULT CButtonEx1::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bTracking = FALSE;
	Invalidate(FALSE);
	return TRUE;
}

