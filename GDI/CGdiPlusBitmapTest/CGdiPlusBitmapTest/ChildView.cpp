#include "stdafx.h"
#include "CGdiPlusBitmapTest.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_LOADJPG, OnLoadJpg)
	ON_COMMAND(ID_LOADPNG, OnLoadPng)
	ON_COMMAND(ID_LOADBMP, OnLoadBmp)
END_MESSAGE_MAP()

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);

	Gdiplus::Graphics graphics(dc);
	graphics.DrawImage(m_bitmap, 0, 0);
}

void CChildView::OnLoadJpg()
{
	m_bitmap.Load(IDB_SUNSET);
	Invalidate();
}

void CChildView::OnLoadPng()
{
	CGdiPlusBitmapResource* pBitmap = new CGdiPlusBitmapResource;
	if (pBitmap->Load(_T("IDB_BAY"), _T("PNG")))
	{
		CClientDC dc(this);
		Gdiplus::Graphics graphics(dc);
		graphics.DrawImage(*pBitmap, 0, 0);
	}
	else
	{
		AfxMessageBox("Failure loading image");
	}
	delete pBitmap;
}

void CChildView::OnLoadBmp()
{
	CGdiPlusBitmapResource* pBitmap = new CGdiPlusBitmapResource;
	if (pBitmap->Load(IDB_DOTS))
	{
		CClientDC dc(this);
		Gdiplus::Graphics graphics(dc);
		graphics.DrawImage(*pBitmap, 0, 0);
	}
	else
	{
		AfxMessageBox("Failure loading image");
	}
	delete pBitmap;
}
