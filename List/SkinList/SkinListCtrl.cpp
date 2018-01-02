// SkinListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SkinListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*****************************************************************
** credits for the custom highlight color bar
** using custom draw technique goes to Michael Dunn
**
** Neat Stuff to do in List Controls Using Custom Draw
** By Michael Dunn 
** http://www.codeproject.com/listctrl/lvcustomdraw.asp?print=true
******************************************************************/

/////////////////////////////////////////////////////////////////////////////
// CSkinListCtrl

CSkinListCtrl::CSkinListCtrl()
{
	g_MyClrBgHi = RGB(115,123,165);
	g_MyClrFgHi = RGB(229,229,229);
}

CSkinListCtrl::~CSkinListCtrl()
{
}


BEGIN_MESSAGE_MAP(CSkinListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSkinListCtrl)
	ON_WM_NCCALCSIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT ( NM_CUSTOMDRAW, OnCustomDrawList )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinListCtrl message handlers

void CSkinListCtrl::PreSubclassWindow() 
{
	//use our custom CHeaderCtrl
	m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->m_hWnd);

	CListCtrl::PreSubclassWindow();
}


void CSkinListCtrl::OnCustomDrawList ( NMHDR* pNMHDR, LRESULT* pResult )
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	static bool bHighlighted = false;
	

    // Take the default processing unless we set this to something else below.
    *pResult = CDRF_DODEFAULT;
	
    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.
	
    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        *pResult = CDRF_NOTIFYITEMDRAW;
	}
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        int iRow = (int)pLVCD->nmcd.dwItemSpec;
		
		bHighlighted = IsRowHighlighted(m_hWnd, iRow);
		if (bHighlighted)
		{
			pLVCD->clrText   = g_MyClrFgHi; // Use my foreground hilite color
			pLVCD->clrTextBk = g_MyClrBgHi; // Use my background hilite color
			
			// Turn off listview highlight otherwise it uses the system colors!
			EnableHighlighting(m_hWnd, iRow, false);
		}
		
		// We want item post-paint notifications, so...
		*pResult = CDRF_DODEFAULT | CDRF_NOTIFYPOSTPAINT;
		
	}
	else if(CDDS_ITEMPOSTPAINT == pLVCD->nmcd.dwDrawStage)
	{
	if (bHighlighted)
      {
        int  iRow = (int)pLVCD->nmcd.dwItemSpec;

        // Turn listview control's highlighting back on now that we have
        // drawn the row in the colors we want.
        EnableHighlighting(m_hWnd, iRow, true);
      }

      *pResult = CDRF_DODEFAULT;

	}
}

void CSkinListCtrl::EnableHighlighting(HWND hWnd, int row, bool bHighlight)
{
  ListView_SetItemState(hWnd, row, bHighlight? 0xff: 0, LVIS_SELECTED);
}

bool CSkinListCtrl::IsRowSelected(HWND hWnd, int row)
{
  return ListView_GetItemState(hWnd, row, LVIS_SELECTED) != 0;
}

bool CSkinListCtrl::IsRowHighlighted(HWND hWnd, int row)
{
  // We check if row is selected.
  // We also check if window has focus. This was because the original listview
  //  control I created did not have style LVS_SHOWSELALWAYS. So if the listview
  //  does not have focus, then there is no highlighting.

  return IsRowSelected(hWnd, row) /*&& (::GetFocus() == hWnd)*/;
}

void CSkinListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	/*****************************************************************
	** credits for this method of removing horz and vert
	** scrollbars goes to Filbert Fox. He posted this solution
	** on the www.codeguru.com discussion boards
	******************************************************************/

	//ensure the scrollbars are hidden
	//ModifyStyle( WS_HSCROLL | WS_VSCROLL, 0 ); 
	UpdateWindow();
	CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}

BOOL CSkinListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();

	return CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}


void CSkinListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();

	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSkinListCtrl::Init()
{
	//another way to hide scrollbars
	InitializeFlatSB(this->m_hWnd);
	FlatSB_EnableScrollBar(this->m_hWnd, SB_BOTH, ESB_DISABLE_BOTH);

	//GetSystemMetrics to find out height difference of the
	//titlebar so we can position scrollbars properly without
	//having to worry about windows appearances affecting it

	CWnd* pParent = GetParent();

	CRect windowRect;
	GetWindowRect(&windowRect);

	int nTitleBarHeight = 0;

	if(pParent->GetStyle() & WS_CAPTION)
		nTitleBarHeight = GetSystemMetrics(SM_CYSIZE);
	

	int nDialogFrameHeight = 0;
	int nDialogFrameWidth = 0;
	if((pParent->GetStyle() & WS_BORDER))
	{
		nDialogFrameHeight = GetSystemMetrics(SM_CYDLGFRAME);
		nDialogFrameWidth = GetSystemMetrics(SM_CYDLGFRAME);
	}

	if(pParent->GetStyle() & WS_THICKFRAME)
	{
		nDialogFrameHeight+=1;
		nDialogFrameWidth+=1;
	}


	//Create scrollbars at runtime
	m_SkinVerticleScrollbar.Create(NULL, WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE|WS_GROUP,CRect(windowRect.right-nDialogFrameWidth,windowRect.top-nTitleBarHeight-nDialogFrameHeight-1,windowRect.right+12-nDialogFrameWidth,windowRect.bottom+11-nTitleBarHeight-nDialogFrameHeight), pParent);
	m_SkinHorizontalScrollbar.Create(NULL, WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE|WS_GROUP,CRect(windowRect.left-nDialogFrameWidth,windowRect.bottom-nTitleBarHeight-nDialogFrameHeight-1,windowRect.right+1-nDialogFrameWidth,windowRect.bottom+11-nTitleBarHeight-nDialogFrameHeight), pParent);
	m_SkinVerticleScrollbar.pList = this;
	m_SkinHorizontalScrollbar.pList = this;
}

void CSkinListCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();

	CListCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CSkinListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();
	return FALSE;
	//return CListCtrl::OnEraseBkgnd(pDC);
}


void CSkinListCtrl::OnPaint() 
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CMemDC memDC(&dc, rect);
	
	CRect headerRect;
	GetDlgItem(0)->GetWindowRect(&headerRect);
	ScreenToClient(&headerRect);
	dc.ExcludeClipRect(&headerRect);
	   
	   
	CRect clip;
	memDC.GetClipBox(&clip);
	memDC.FillSolidRect(clip, RGB(76,85,118));
	   
	SetTextBkColor(RGB(76,85,118));
	   
	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();
	   
	   
	DefWindowProc(WM_PAINT, (WPARAM)memDC->m_hDC, (LPARAM)0);
}
