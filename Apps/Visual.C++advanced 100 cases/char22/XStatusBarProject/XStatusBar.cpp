
#include "StdAfx.h"
#include "XStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

volatile static char jrrcid[] = "%J%";

#define IDC_JRLIB_STATUSBAR_TIMER	20000

XPaneInfo::XPaneInfo()
{
	progress	= NULL;
	hScrollPos	= 0;
	vScrollPos	= 0;

	SetDefault();
}

XPaneInfo::XPaneInfo(const XPaneInfo& paneInfo)
{
	for (int i = 0; i < 2; i++)
	{
		fgColor[i]	= paneInfo.fgColor[i];
		bkColor[i]	= paneInfo.bkColor[i];
		string[i]	= paneInfo.string[i];
	}

	font			= paneInfo.font;
	mode			= paneInfo.mode;
	progress		= NULL;
	hScrollPos		= paneInfo.hScrollPos;
	vScrollPos		= paneInfo.vScrollPos;
}

XPaneInfo::~XPaneInfo()
{
	if (progress)	delete progress;
	progress = NULL; 
}

XPaneInfo XPaneInfo::operator=(const XPaneInfo& paneInfo)
{
	for (int i = 0; i < 2; i++)
	{
		fgColor[i]	= paneInfo.fgColor[i];
		bkColor[i]	= paneInfo.bkColor[i];
		string[i]	= paneInfo.string[i];
	}

	font			= paneInfo.font;
	mode			= paneInfo.mode;
	hScrollPos		= paneInfo.hScrollPos;
	vScrollPos		= paneInfo.vScrollPos;

	if (progress)	delete progress;
	progress = NULL; 

	return *this;
}

void XPaneInfo::SetDefault()
{
	bkColor[1]	= COLORREF(GetSysColor(COLOR_MENU));
	bkColor[0]	= bkColor[1];

	fgColor[1]	= GetSysColor(COLOR_MENUTEXT);
	fgColor[0]	= RGB(GetRValue(bkColor[1])/2, GetGValue(bkColor[1])/2, GetBValue(bkColor[1])/2);

	mode		= XSB_TEXT | DT_LEFT;
	SetFont(CFont::FromHandle((HFONT) GetStockObject(ANSI_VAR_FONT)));

	if (progress)	delete progress;
	progress = NULL; 
}

void XPaneInfo::SetFont(LPCSTR name, int size)
{
	CFont pointFont;
	pointFont.CreatePointFont(size, name);
	pointFont.GetLogFont(&font);
}

void XPaneInfo::SetMode(int newMode)
{
	if ((mode = newMode) & XSB_PROGRESS)
	{
		if (!progress)
		{
			UINT style = WS_VISIBLE | WS_CHILD;
			if (mode & XSB_SMOOTH) style |= PBS_SMOOTH;

			progress = new CProgressCtrl();
			progress->Create(style, CRect(0,0,0,0), XStatusBar::aktBar, 1);
		}
	}
	else if (progress)
	{
		delete progress;
		progress = NULL; 
	}
}

void XPaneInfo::SetFgColor(COLORREF on, COLORREF off)
{
	fgColor[1] = on;

	if (off != -1)
		fgColor[0] = off;
	else
	{
		COLORREF bk = GetSysColor(COLOR_MENU);
		fgColor[0] = RGB(GetRValue(bk)/2, GetGValue(bk)/2, GetBValue(bk)/2);
	}
}

void XPaneInfo::SetBkColor(COLORREF on, COLORREF off)
{
	bkColor[1] = on;
	if (off != -1)	bkColor[0] = off;
	else			bkColor[0] = GetSysColor(COLOR_MENU);
}

void XPaneInfo::SetBitmap(LPCSTR newOnBitmap, LPCSTR newOffBitmap)
{
	string[1]	= newOnBitmap;
	string[0]	= newOffBitmap;
}

void XPaneInfo::SetText(LPCSTR newOnText, LPCSTR newOffText)
{
	string[1]	= newOnText;
	string[0]	= newOffText;
}

void XPaneInfo::SetNumber(int newOnNumber, int newOffNumber)
{
	string[1].Format("%d", newOnNumber);
	string[0].Format("%d", newOffNumber);
}

void XPaneInfo::HScroll(CRect& rect, int maxWidth, int nullValue)
{
	if (++hScrollPos > maxWidth)	hScrollPos = nullValue;
	rect.left -= hScrollPos;
}

void XPaneInfo::VScroll(CRect& rect, int maxHeight, int nullValue)
{
	if (++vScrollPos > maxHeight)	vScrollPos = nullValue;
	rect.top -= vScrollPos;
}

#ifdef _DEBUG
	void XPaneInfo::Dump(CDumpContext& dc) const
	{
		dc	<< "FgColor / BkColor / Value:\t" 
			<< fgColor[1] << " - " << fgColor[0] << " / "
			<< bkColor[1] << " - " << bkColor[0] << " / "
			<< string[1]  << " - " << string[0]  << "\n"
			<< "Mode:\t"  << mode  << "\n";
	}

	void XPaneInfo::AssertValid() const
	{
		ASSERT((progress == NULL) || _CrtIsValidHeapPointer(progress));
	}

	CDumpContext& AFXAPI operator<<(CDumpContext& dc, XPaneInfo& paneInfo)
	{
		paneInfo.Dump(dc);
		return dc;
	}
#endif // _DEBUG

XStatusBar *XStatusBar::aktBar = NULL;

XStatusBar::XStatusBar()
{
	aktBar		= this;
	timerID		= 0;
}

XStatusBar::~XStatusBar()
{
}

BEGIN_MESSAGE_MAP(XStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(XStatusBar)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

bool XStatusBar::CreateStatusBar(CWnd *pWnd, const UINT* lpIDArray, int nIDCount, UINT pane0Style)
{
	bool ret = (Create(pParent = pWnd) &&
				SetIndicators(lpIDArray, nIDCount));

	if (ret)	SetStyle(0, pane0Style);
	else		AfxMessageBox("Unable to create Statusbar.");

	return ret;
}

BOOL XStatusBar::SetIndicators(const UINT* lpIDArray, int nIDCount)
{
	BOOL ret = CStatusBar::SetIndicators(lpIDArray, nIDCount);

	XPaneInfo defaultInfo;
	paneInfo.SetSize(nIDCount);
	
	for (int i = 0; i < nIDCount; i++)
		paneInfo[i] = defaultInfo;

	return ret;
}

void XStatusBar::OnPaint()
{
	CPaintDC	dc(this);
	CRect		client;		GetClientRect(client);
	CDC			memDC;		memDC.CreateCompatibleDC(&dc);
	CBitmap		bitmap;		bitmap.CreateCompatibleBitmap(&dc, client.Width(), client.Height());
	CBitmap		*oldBitmap	= (CBitmap *) memDC.SelectObject(&bitmap);
	COLORREF	hell		= GetSysColor(COLOR_3DHILIGHT);
	COLORREF	dunkel		= GetSysColor(COLOR_3DSHADOW);

	memDC.FillSolidRect(client, GetSysColor(COLOR_3DFACE));

	//========================================================================
	// Zeichne alle Pane-Rechtecke mit ihrem Inhalt
	//========================================================================
	bool scroll = false;
	for (int i = 0, n = paneInfo.GetSize(); i < n; i++)
	{
		XPaneInfo &aktPane = paneInfo[i];

		CRect	rect;
		GetItemRect(i, rect);
		UINT style = GetPaneStyle(i);

		if (style & SBPS_POPOUT)			memDC.Draw3dRect(rect, hell, dunkel);
		else if (!(style & SBPS_NOBORDERS))	memDC.Draw3dRect(rect, dunkel, hell);

		on = (GetPaneStyle(i) & SBPS_DISABLED) == 0;

		rect.DeflateRect(1, 1);
		memDC.FillSolidRect(rect, aktPane.GetBkColor(on));

		CRgn clip;
		clip.CreateRectRgnIndirect(&rect);
		memDC.SelectClipRgn(&clip);

		switch (aktPane.GetMode() & XSB_MODE)
		{
		case XSB_TEXT:
		case XSB_NUMBER:	DrawTextPane(	 &memDC, i, rect, aktPane);	break;
		case XSB_BITMAP:	DrawBitmapPane(	 &memDC, i, rect, aktPane);	break;
		case XSB_PROGRESS:	DrawProgressPane(&memDC, i, rect, aktPane);	break;
		default:														break;
		}

		if (aktPane.GetMode() & XSB_SCROLL)	scroll = true;

		memDC.SelectClipRgn(NULL);
	}

		 if (scroll  && (timerID == 0))		timerID = SetTimer(IDC_JRLIB_STATUSBAR_TIMER, 100, NULL);
	else if (!scroll && (timerID != 0))		{ KillTimer(timerID); timerID = 0; }

	if (!GetParent()->IsZoomed()) DrawSizing(&memDC);

	dc.BitBlt(0, 0, client.Width(), client.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldBitmap);
}

void XStatusBar::DrawSizing(CDC *pDC)
{
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);

	CPen hellPen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
	CPen dunkelPen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
	CPen *oldPen = pDC->SelectObject(&dunkelPen);
	for (int i = 1; i < 18; i++)
	{
		switch (i % 4)
		{
		case 0:		pDC->SelectObject(&dunkelPen);	break;
		case 1:		pDC->SelectObject(&hellPen);	break;
		case 2:		continue;
		case 3:		pDC->SelectObject(&dunkelPen);	break;
		}
		pDC->MoveTo(rect.right - i, rect.bottom);
		pDC->LineTo(rect.right,		rect.bottom - i);
	}

	pDC->SelectObject(oldPen);
}

void XStatusBar::DrawTextPane(CDC *pDC, int ix, CRect& rect, XPaneInfo& aktPane)
{
	CString		text		= aktPane.GetText(on);
	if (text.IsEmpty())		text = GetPaneText(ix);
	if (text.IsEmpty())		return;

	CFont		font;		font.CreateFontIndirect(&aktPane.GetFont());
	COLORREF	textColor	= aktPane.GetFgColor(on);
	CFont		*oldFont	= pDC->SelectObject(&font);
	int			oldBkMode	= pDC->SetBkMode(TRANSPARENT);
	COLORREF	oldFgColor	= pDC->SetTextColor(textColor);
	const int	mode		= aktPane.GetMode();
	const int	repeat		= mode & XSB_REPEAT;
	const int	hScroll		= mode & XSB_HSCROLL;
	const int	vScroll		= mode & XSB_VSCROLL;
	int			textAlign	= mode & XSB_ALIGN;
	if (hScroll)textAlign	&= ~(DT_CENTER | DT_RIGHT);

	if (repeat)
	{
		text += "  ";
		CSize s = pDC->GetTextExtent(text);
		if (hScroll)	aktPane.HScroll(rect, s.cx, 1);
		if (vScroll)	aktPane.VScroll(rect, s.cy, 1);

		int y = rect.top;
		if (hScroll && vScroll)
			for ( ; rect.left <= rect.right; rect.left += s.cx)
				for (rect.top = y ; rect.top <= rect.bottom; rect.top += s.cy)
					pDC->DrawText(text, rect, textAlign);
		else if (hScroll)
			for ( ; rect.left <= rect.right; rect.left += s.cx)
				pDC->DrawText(text, rect, textAlign);
		else if (vScroll)
			for ( ; rect.top <= rect.bottom; rect.top += s.cy)
				pDC->DrawText(text, rect, textAlign);
		else
			pDC->DrawText(text, rect, textAlign);
	}
	else
	{
		CSize s = pDC->GetTextExtent(text);
		if (hScroll)	aktPane.HScroll(rect, s.cx, -rect.Width());
		if (vScroll)	aktPane.VScroll(rect, s.cy, -rect.Height());

		pDC->DrawText(text, rect, textAlign);
	}

	pDC->SelectObject(oldFont);
	pDC->SetTextColor(oldFgColor);
	pDC->SetBkMode(oldBkMode);
}

void XStatusBar::DrawBitmapPane(CDC *pDC, int ix, CRect& rect, XPaneInfo& aktPane)
{
	CString		bmString	= aktPane.GetBitmap(on);
	if (bmString.IsEmpty())	return;
	CDC			memDC;		memDC.CreateCompatibleDC(pDC);
	CBitmap		bitmap;		bitmap.LoadBitmap(bmString);
	BITMAP		bm;			bitmap.GetBitmap(&bm);
	CBitmap		*oldBitmap	= memDC.SelectObject(&bitmap);
	const int	mode		= aktPane.GetMode();
	const int	hScroll		= mode & XSB_HSCROLL;
	const int	vScroll		= mode & XSB_VSCROLL;
	const int	repeat		= mode & XSB_REPEAT;
	const int	stretch		= mode & XSB_STRETCH;

	if (repeat)
	{
		if (hScroll)	aktPane.HScroll(rect, bm.bmWidth, 1);
		if (vScroll)	aktPane.VScroll(rect, bm.bmHeight, 1);

		if (hScroll && !vScroll)
			for (int x = rect.left; x < rect.right; x += bm.bmWidth)
				pDC->BitBlt(x, rect.top, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
		else if (vScroll && !hScroll)
			for (int y = rect.top; y < rect.bottom; y += bm.bmHeight)
				pDC->BitBlt(rect.left, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
		else
			for (int x = rect.left; x < rect.right; x += bm.bmWidth)
				for (int y = rect.top; y < rect.bottom; y += bm.bmHeight)
					pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);

	}
	else
	{
		if (hScroll)	aktPane.HScroll(rect, bm.bmWidth, -rect.Width());
		if (vScroll)	aktPane.VScroll(rect, bm.bmHeight, -rect.Height());

		if (hScroll || vScroll)
			pDC->BitBlt(rect.left, rect.top, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
		else if (stretch)
			pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		else
		{
			if (mode & DT_RIGHT)	rect.left	= rect.right - bm.bmWidth;
			if (mode & DT_CENTER)	rect.left	= (rect.left + rect.right - bm.bmWidth) / 2;
			if (mode & DT_BOTTOM)	rect.top	= rect.bottom - bm.bmHeight;
			if (mode & DT_VCENTER)	rect.top	= (rect.top + rect.bottom - bm.bmHeight) / 2;
			pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		}
	}

	memDC.SelectObject(oldBitmap);
}

void XStatusBar::DrawProgressPane(CDC *pDC, int ix, CRect& rect, XPaneInfo& aktPane)
{
	rect.InflateRect(1, 1);
	GetProgressCtrl(ix)->MoveWindow(rect, FALSE);
}

XPaneInfo& XStatusBar::GetXPaneInfo(int ix)
{
	ASSERT(ix < GetCount());
	return paneInfo[ix];
}

void XStatusBar::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == timerID)	Invalidate(FALSE);
}

#define GET_PANE_INFO(ix)	ASSERT(ix < GetCount()); \
							UINT id, style; int width; \
							GetPaneInfo(ix, id, style, width)

UINT XStatusBar::SetStyle(int ix, UINT newStyle)	{ GET_PANE_INFO(ix); SetPaneInfo(ix, id, newStyle, width); return style; }
int  XStatusBar::SetWidth(int ix, int newWidth)		{ GET_PANE_INFO(ix); SetPaneInfo(ix, id, style, newWidth); return width; }
UINT XStatusBar::GetStyle(int ix)					{ GET_PANE_INFO(ix); return style;	}
int  XStatusBar::GetWidth(int ix)					{ GET_PANE_INFO(ix); return width;	}
UINT XStatusBar::GetID(int ix)						{ GET_PANE_INFO(ix); return id;	}

#undef GET_PANE_INFO

void XStatusBar::OnDestroy() 
{
	if (timerID)	KillTimer(timerID);
	timerID = 0;

	CStatusBar::OnDestroy();
}

void XStatusBar::SavePane(int ix)
{
	ASSERT(ix < GetCount());

	XPaneInfo	value;
	if (!buffer.Lookup(ix, value))
		buffer[ix] = paneInfo[ix];
}

void XStatusBar::RestorePane(int ix)
{
	ASSERT(ix < GetCount());
	
	XPaneInfo	value;
	if (buffer.Lookup(ix, value))
	{
		paneInfo[ix] = value;
		buffer.RemoveKey(ix);
	}

	Invalidate(FALSE);
}

int XStatusBar::GetPaneAtPosition(CPoint& point)
{
	if (pParent->IsKindOf(RUNTIME_CLASS(CDialog)))
	{
		pParent->ClientToScreen(&point);
		ScreenToClient(&point);
	}

	CRect rect;
	for (int i = 0, n = GetCount(); i < n; i++)
	{
		GetItemRect(i, rect);
		if (rect.PtInRect(point))	return i;
	}

	return -1;
}

#define TO_PARENT(fkt, event)	\
	void XStatusBar::fkt(UINT nFlags, CPoint point) \
	{ \
		pParent->SendMessage(event, (WPARAM) nFlags, MAKELPARAM(point.x, point.y)); \
		CStatusBar::fkt(nFlags, point); \
	}

TO_PARENT(OnLButtonUp,		WM_LBUTTONUP);
TO_PARENT(OnMButtonUp,		WM_MBUTTONUP);
TO_PARENT(OnRButtonUp,		WM_RBUTTONUP);
TO_PARENT(OnLButtonDown,	WM_LBUTTONDOWN);
TO_PARENT(OnMButtonDown,	WM_MBUTTONDOWN);
TO_PARENT(OnRButtonDown,	WM_RBUTTONDOWN);
TO_PARENT(OnLButtonDblClk,	WM_LBUTTONDBLCLK);
TO_PARENT(OnMButtonDblClk,	WM_MBUTTONDBLCLK);
TO_PARENT(OnRButtonDblClk,	WM_RBUTTONDBLCLK);
TO_PARENT(OnMouseMove,		WM_MOUSEMOVE);

#undef TO_PARENT
