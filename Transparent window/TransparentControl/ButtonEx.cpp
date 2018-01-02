// ButtonEx.cpp : implementation file
//

#include "stdafx.h"
#include "TransparentControl.h"
#include "ButtonEx.h"
#include ".\buttonex.h"


// CButtonEx

IMPLEMENT_DYNAMIC(CButtonEx, CButton)
CButtonEx::CButtonEx()
{
	m_bTracking = FALSE;
}

CButtonEx::~CButtonEx()
{
}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()



// CButtonEx message handlers


void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  Add your code to draw the specified item
    m_objTransparent.TransparentBk( lpDrawItemStruct->hDC, GetSafeHwnd());

	CDC dc;
	dc.Attach( lpDrawItemStruct->hDC);

	TRACE(_T("CButtonEx::DrawItem %x\r\n"), lpDrawItemStruct->itemState);

	BITMAP bmpInfo;
	m_bitmapNor.GetBitmap( &bmpInfo);

	if ( m_bTracking )
	{
		CDC memdc;
		memdc.CreateCompatibleDC( &dc);
		memdc.SelectObject(m_bitmapOver);
		BLENDFUNCTION bf = {0};
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = 80;

		dc.AlphaBlend( 0,0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &memdc, 0,0, bmpInfo.bmWidth, bmpInfo.bmHeight, bf);
		//dc.TransparentBlt( 0,0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &memdc, 0,0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255,0,255));
	}

	if ( lpDrawItemStruct->itemState & ODS_SELECTED  )
	{
		CDC memdc;
		memdc.CreateCompatibleDC( &dc);
		memdc.SelectObject(m_bitmapDown);
		dc.TransparentBlt( 0,0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &memdc, 0,0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255,0,255));
	}

	CString strText;
	GetWindowText( strText);
	CRect rtText;
	GetClientRect( &rtText);
	dc.SetBkMode( TRANSPARENT);
	dc.DrawText( strText, &rtText, DT_CENTER|DT_SINGLELINE |DT_VCENTER);
}

void CButtonEx::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CButton::PreSubclassWindow();

	m_objTransparent.Install( GetSafeHwnd());
	m_bitmapNor.LoadBitmap( IDB_BITMAP_BTN_NORMAL);
	m_bitmapOver.LoadBitmap( IDB_BITMAP_BTN_OVER);
	m_bitmapDown.LoadBitmap( IDB_BITMAP_BTN_DOWN);
}

BOOL CButtonEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
    return TRUE;
	//return CButton::OnEraseBkgnd(pDC);
}

void CButtonEx::OnMouseMove(UINT nFlags, CPoint point)
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

LRESULT CButtonEx::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bTracking = FALSE;
	Invalidate(FALSE);
	return TRUE;
}



