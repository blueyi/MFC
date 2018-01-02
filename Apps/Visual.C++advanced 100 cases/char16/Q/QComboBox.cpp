/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 9/16/98 2:20:27 PM
  Comments: QComboBox.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "QComboBox.h"
#include <math.h>
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQComboBox

#define NotifyWindow(pWnd,message,wParam,lParam) if (pWnd) pWnd->SendMessage(message, (WPARAM)wParam, (LPARAM)lParam)

CBrush CQComboBox::m_brBkGnd(defaultRGBBkGnd);
CFont CQComboBox::m_font;
CMap<CQComboBox*,CQComboBox*, BOOL, BOOL> CQComboBox::m_mapUnloadedQCombos;

static const LOGFONT logFontPages =
{
/*LONG lfHeight*/8,
/*LONG lfWidth*/0,
/*LONG lfEscapement*/0,
/*LONG lfOrientation*/0,
/*LONG lfWeight*/FW_NORMAL,
/*BYTE lfItalic*/FALSE,
/*BYTE lfUnderline*/FALSE,
/*BYTE lfStrikeOut*/FALSE,
/*BYTE lfCharSet*/ANSI_CHARSET,
/*BYTE lfOutPrecision*/0,
/*BYTE lfClipPrecision*/0,
/*BYTE lfQuality*/DEFAULT_QUALITY,
/*BYTE lfPitchAndFamily*/DEFAULT_PITCH,
/*CHAR lfFaceName[LF_FACESIZE]*/_T("MS Sans Serif")
};

// Function name	: CQComboBox::CQComboBox
// Description	    : default constuctor
// Return type		: 
CQComboBox::CQComboBox(TLine fctLine, TLinePartial fctLinePartial, LPARAM lParam)
{
	m_lParam = lParam;
	m_QuickLoader.SetParent(this);
	RegClassQComboBox();
	m_pListBox = NULL;
	m_pEdit = NULL;
	m_bCaptured = FALSE;
	m_fctLine = fctLine;
	m_fctLinePartial = fctLinePartial;
	m_nCountVisible = 0;
	SetRateWidth(0.0);
	SetMultipleHeight();
	m_fctLoadFunction = LoadPartialListBox;
	m_mapUnloadedQCombos[this] = !IsAlreadyLoad();

	//When you callthe contructor, you need to attach two function.
	//The first, for giving line number nIndex
	//The second, for fiving numer of line which start with a given string.
	// If you don't write that functions, especialy m_fctLine, you will have some suprises
	ASSERT(m_fctLine);
}

// Function name	: CQComboBox::~CQComboBox
// Description	    : virtual destructor
// Return type		: 
CQComboBox::~CQComboBox()
{
	m_mapUnloadedQCombos.RemoveKey(this);
}

BEGIN_MESSAGE_MAP(CQComboBox, CWnd)
	//{{AFX_MSG_MAP(CQComboBox)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQComboBox message handlers
UINT CQComboBox::m_nSelChange = NULL;
UINT CQComboBox::m_nLoading = NULL;
UINT CQComboBox::m_nLoaded = NULL;

// Function name	: CQComboBox::RegClassQComboBox
// Description	    : Register this window class
// Return type		: BOOL 
BOOL CQComboBox::RegClassQComboBox()
{
	WNDCLASS wndClass;
		wndClass.style = CS_DBLCLKS;
		wndClass.lpfnWndProc = ::DefWindowProc;
		wndClass.cbClsExtra = NULL;
		wndClass.cbWndExtra = NULL;
		wndClass.hInstance = AfxGetInstanceHandle();
		wndClass.hIcon = NULL;
		wndClass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)m_brBkGnd;
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = wndClassName;
	BOOL bResult = AfxRegisterClass(&wndClass);
	if (bResult)
	{
		if (!m_nSelChange)
			m_nSelChange = RegisterWindowMessage(defaultSelChange);
		if (!m_nLoading)
			m_nLoading = RegisterWindowMessage(defaultLoading);
		if (!m_nLoaded)
			m_nLoaded = RegisterWindowMessage(defaultLoaded);
		if (!m_font.GetSafeHandle())
		{
			//At the first call set the new font
			m_font.CreateFontIndirect(&logFontPages);
		}
	}
	return bResult;
}

CQComboBox* CQComboBox::m_pActiveMCBox = NULL;
CQComboBox::CWindowProcs CQComboBox::m_wndProcs;
// Function name	: CQComboBox::ListBoxWindowProc
// Description	    : ListControl window procedure
// Return type		: LRESULT CALLBACK 
// Argument         : HWND hWnd
// Argument         : UINT nMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CALLBACK CQComboBox::ListBoxWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	if (CQComboBox* pOwner = CQComboBox::m_pActiveMCBox)
		if (!pOwner->ForwardMessage(nMsg, wParam, lParam))
			return NULL;
	return CallWindowProc( CQComboBox::m_wndProcs.GetOldListBoxProcedure(hWnd), hWnd, nMsg, wParam, lParam );
}

// Function name	: CQComboBox::ParentWindowProc
// Description	    : Parent window procedure.
// Return type		: LRESULT CALLBACK 
// Argument         : HWND hWnd
// Argument         : UINT nMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CALLBACK CQComboBox::ParentWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CQComboBox* pOwner = CQComboBox::m_pActiveMCBox;
	CQComboBox* pFirst = GetFirstQComboBox();

	{
		switch (nMsg)
		{
			case WM_KICKIDLE:
			{
				//Start to load items, after 3 seconds.
				if (pFirst)
					pFirst->SetTimer(QIDTIMERSTARTLOADITEMS, QTIMESTARTLOADITEMS, NULL);
				break;
			}
			case WM_COMMAND:
			case WM_SYSCOMMAND:
			case WM_LBUTTONDOWN:
			case WM_NCLBUTTONDOWN:
			{
				if (pFirst)
				{
					pFirst->KillTimer(QIDTIMERSTARTLOADITEMS);
					pFirst->KillTimer(QIDTIMERLOADITEMS);
				};

				if (pOwner)
				{
					BOOL bDropped = pOwner->IsDropedDown();
					pOwner->DropDown(FALSE);
					if (nMsg == WM_COMMAND)
						if (LOWORD(wParam) == IDOK)
						{
							pOwner->SelectCurrentItem();
							return FALSE;
						}
						else
							if (LOWORD(wParam) == IDCANCEL)
								if (bDropped)
									return FALSE;
					break;
				}
			}
		}
	};
	WNDPROC wndProc = CQComboBox::m_wndProcs.GetOldParentProcedure(hWnd);
	ASSERT (wndProc);
	return CallWindowProc( wndProc, hWnd, nMsg, wParam, lParam );
}

// Function name	: CQComboBox::EditWindowProc
// Description	    : Edit window procedure
// Return type		: LRESULT CALLBACK 
// Argument         : HWND hWnd
// Argument         : UINT nMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CALLBACK CQComboBox::EditWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CQComboBox* pOwner = CQComboBox::m_pActiveMCBox;
	switch (nMsg)
	{
		case WM_SETFOCUS:
			{
				CQComboBox::m_pActiveMCBox = (CQComboBox*)CWnd::FromHandle(::GetParent(hWnd));
				break;
			}
		case WM_KILLFOCUS:
			{
				if (pOwner)
				{
					pOwner->DropDown(FALSE);
					CQComboBox::m_pActiveMCBox = NULL;
				}
				break;
			}
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			{
				int nStep = 0;
				if (pOwner)
					switch ((int) wParam)
					{
						case VK_NEXT:
							{
								if (nStep == 0)
									nStep = +pOwner->GetVisibleCount();
							}
						case VK_PRIOR:
							{
								if (nStep == 0)
									nStep = -pOwner->GetVisibleCount();
							}
						case VK_UP:
							{
								if (nStep == 0)
									nStep = -1;
							}
						case VK_DOWN:
							{
								if (nStep == 0)
									nStep = +1;
								if (abs(nStep) > 1 || ((abs(nStep) == 1) && GetAsyncKeyState(VK_MENU) >= 0))
								{
									pOwner->LoadPartial(pOwner->m_QuickLoader.GetItemLine(pOwner->GetCurrentItem()) + nStep, nStep/abs(nStep) * pOwner->GetVisibleCount());
									pOwner->SetCurrentItem(pOwner->GetCurrentItem() + nStep);
									pOwner->SelectCurrentItem();
									break;
								}
							}
						case defaultDropDownKey:
							{
								pOwner->DropDown(!pOwner->IsDropedDown());
								break;
							}
					}
				break;
			}
	}
	return CallWindowProc( CQComboBox::m_wndProcs.GetOldEditProcedure(hWnd), hWnd, nMsg, wParam, lParam );
}

// Function name	: CQComboBox::OnInit
// Description	    : Init the control
// Return type		: BOOL 
BOOL CQComboBox::OnInit()
{
	// You must already attach a function who give me a line.
	ASSERT (m_fctLine != NULL);
	ASSERT (m_font.GetSafeHandle());
	SetFont(&m_font);
	ModifyStyle(WS_OVERLAPPED , WS_TABSTOP);
	m_pEdit		= new CEdit();
	m_pListBox = new CListBox();
	if (m_pEdit->Create(WS_CHILD | WS_VISIBLE | defaultEditStyle, CRect(0,0,0,0), this, IDEDIT ))
	{
		ModifyStyleEx(0, WS_EX_STATICEDGE);
		m_pEdit->SetFont(&m_font);
		if (m_pListBox->Create(WS_BORDER | WS_CHILD | defaultListBoxStyle , CRect(0,0,0,0), GetDesktopWindow(), IDListBox))
		{
			m_pListBox->SetFont(&m_font);
			//Set the refernce to this object in user data dword
			::SetWindowLong(m_pListBox->m_hWnd, GWL_USERDATA, (long)this);
			::SetWindowLong(m_pListBox->m_hWnd, GWL_STYLE, GetWindowLong(m_pListBox->m_hWnd, GWL_STYLE) | WS_CLIPSIBLINGS | WS_OVERLAPPED);
			m_pListBox->ModifyStyleEx(0, WS_EX_TOOLWINDOW);
			m_pListBox->SetWindowPos(&CWnd::wndTopMost,0,0,0,0, SWP_NOSIZE | SWP_NOMOVE);
			ListView_SetExtendedListViewStyle(m_pListBox->m_hWnd, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			Resize();
			m_wndProcs.AddEdit(GetEdit(), EditWindowProc);
			m_wndProcs.AddListBox(GetListBox(), ListBoxWindowProc);
			m_wndProcs.AddParent(GetParent(), ParentWindowProc);
			m_nCountVisible = GetVisibleCount();
			return TRUE;
		}
	}
	return FALSE;
}

// Function name	: CQComboBox::PreSubclassWindow
// Description	    : Call to subclass window
// Return type		: void 
void CQComboBox::PreSubclassWindow() 
{
	CWnd::PreSubclassWindow();

	OnInit();
}

// Function name	: CQComboBox::OnDestroy
// Description	    : Remove all dependent datas.
// Return type		: void 
void CQComboBox::OnDestroy() 
{
	CWnd::OnDestroy();

	m_wndProcs.RemoveEdit(GetEdit());
	m_wndProcs.RemoveListBox(GetListBox());
	m_wndProcs.RemoveParent(GetParent());
	
	if (CListBox* pList = GetListBox())
		delete pList;

	if (CEdit* pEdit = GetEdit())
		delete pEdit;

	m_pListBox = NULL;
	m_pEdit = NULL;

}

// Function name	: CQComboBox::GetListBox
// Description	    : return the list control for 
// Return type		: CListBox* 
CListBox* CQComboBox::GetListBox()
{
	return m_pListBox;
}

// Function name	: CQComboBox::GetEdit
// Description	    : retirn  pointer to edit control inside of thsi control
// Return type		: CEdit* 
CEdit* CQComboBox::GetEdit()
{
	return m_pEdit;
}

// Function name	: CQComboBox::DrawButton
// Description	    : Draw down button
// Return type		: void 
// Argument         : CDC * pDC
// Argument         : CRect r
// Argument         : BOOL bDown
void CQComboBox::DrawButton(CDC * pDC, CRect r, BOOL bDown)
{
	CPen penWhite(PS_SOLID,1,RGB(255,255,255));
	CPen penBlack(PS_SOLID,1,RGB(0,0,0));
	pDC->FrameRect(r,&CBrush(RGB(128,128,128)));
	if (!bDown)
	{
		pDC->SelectObject(&penWhite);
		 pDC->MoveTo(r.left, r.bottom - 2);
		 pDC->LineTo(r.left, r.top);
		 pDC->LineTo(r.right - 1, r.top);
	}
	CBitmap bitmapOEM;
	if (bitmapOEM.LoadOEMBitmap(OBM_COMBO))
	{
		CDC dcMem;
		if (dcMem.CreateCompatibleDC(pDC))
		{
			BITMAP b; bitmapOEM.GetBitmap(&b);
			int leftC = max((r.Width() - b.bmWidth) / 2,1);
			int topC = max((r.Height() - b.bmHeight) / 2,1);
			if (bDown)
			{
				leftC++;
				topC++;
			}
			CBitmap* pOldBitmap = dcMem.SelectObject(&bitmapOEM);
			pDC->BitBlt(r.left + leftC, r.top + topC, r.Width() - (leftC + 1), r.Height() - (topC), &dcMem, 0,0, SRCCOPY);
			pOldBitmap = dcMem.SelectObject(pOldBitmap);
		}
	}
}

// Function name	: CQComboBox::OnPaint
// Description	    : On Draw function
// Return type		: void 
void CQComboBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect r; GetClientRect(r);
	r.right--;

	dc.MoveTo(r.left, r.bottom);
	 dc.LineTo(r.left, r.top);
	 dc.LineTo(r.right, r.top);
	 dc.LineTo(r.right, r.bottom);

	r.left = r.right - defaultSizeDX;
	r.InflateRect(0,-2);r.bottom++;r.right--;r.left++;
	m_rectBtn = r;

	DrawButton(&dc, m_rectBtn);
}

// Function name	: CQComboBox::Resize
// Description	    : Call to remove the edit and list controls
// Return type		: void 
void CQComboBox::Resize()
{
	ASSERT (GetListBox());
	CRect r;
	GetWindowRect(r);
	SetWindowPos(0, 0, 0, r.Width(), defaultSizeDY, SWP_NOMOVE | SWP_NOZORDER | SWP_NOMOVE);
	// Set the height and width of edit control
	GetClientRect(r);
	r.InflateRect(-1,-2); r.bottom++;
	r.right -= defaultSizeDX;
	GetEdit()->MoveWindow(r.left, r.top, r.Width(), r.Height());
	// Set the height and width of list control
	GetWindowRect(r);
	int dy = r.Height();
	r.top = r.bottom;
	r.left++;r.right--;
	r.bottom += m_nMultipleHeight * dy;
	r.right += int(m_dWidthList * r.Width());
	GetListBox()->MoveWindow(r.left, r.top, r.Width(), r.Height());
}

// Function name	: CQComboBox::DropDown
// Description	    : DropDown
// Return type		: void 
// Argument         : BOOL bDown
void CQComboBox::DropDown(BOOL bDown)
{
	if (IsWindowVisible())
		if (IsDropedDown() != bDown)
		{
			Resize();
			LoadPartial(0, +GetVisibleCount());
			GetListBox()->ShowWindow(bDown ? SW_SHOW : SW_HIDE);
			if (bDown)
				GetEdit()->SetFocus();
		}
}

// Function name	: CQComboBox::IsDropedDown
// Description	    : If the list control is dropped downd, return TRUE
// Return type		: BOOL 
BOOL CQComboBox::IsDropedDown()
{
	return GetListBox()->IsWindowVisible();
}

// Function name	: CQComboBox::OnWindowPosChanged
// Description	    : 
// Return type		: void 
// Argument         : WINDOWPOS FAR* lpwndpos
void CQComboBox::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CWnd::OnWindowPosChanged(lpwndpos);
	Resize();
}

// Function name	: CQComboBox::OnLButtonDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CQComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_rectBtn.PtInRect(point))
	{
		SetButton();
		DropDown(!IsDropedDown());
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

// Function name	: CQComboBox::OnLButtonUp
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CQComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseButton();

	CWnd::OnLButtonUp(nFlags, point);
}

// Function name	: CQComboBox::OnMouseMove
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CQComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bCaptured)
	{
		CPoint p; ::GetCursorPos(&p);
		ScreenToClient(&p);
		if (!m_rectBtn.PtInRect(p))
			ReleaseButton();
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

// Function name	: CQComboBox::ReleaseButton
// Description	    : Call to release the capture and image of button. After SetButton()
// Return type		: void 
void CQComboBox::ReleaseButton()
{
	if (m_bCaptured)
	{
		ReleaseCapture();
		CDC* pDC = GetDC();
			DrawButton(pDC, m_rectBtn);
		ReleaseDC(pDC);
		m_bCaptured = FALSE;
	}
}

// Function name	: CQComboBox::SetButton
// Description	    : 
// Return type		: void 
void CQComboBox::SetButton()
{
	if (!m_bCaptured)
	{
		SetCapture();
		CDC* pDC = GetDC();
			DrawButton(pDC, m_rectBtn, TRUE);
		ReleaseDC(pDC);
		m_bCaptured = TRUE;
	}
}

// Function name	: CQComboBox::ForwardMessage
// Description	    : This function is called by ListBoxWindowProc
// Return type		: void 
// Argument         : UINT nMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
BOOL CQComboBox::ForwardMessage(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT (GetListBox());
	switch (nMsg)
	{
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		{
			BOOL bOutside = TRUE;
			int nIndex = GetListBox()->ItemFromPoint(CPoint(LOWORD(wParam), HIWORD(lParam)), bOutside);
			if (GetCurrentItem() != nIndex)
				SetCurrentItem(nIndex);
			if (nMsg == WM_LBUTTONDOWN)
			{
				DropDown(FALSE);
				SelectCurrentItem();
			}
			break;
		}
		case WM_VSCROLL:
		{
			CListBox* pListBox = GetListBox();
			UINT nScrollCode =  (int) LOWORD(wParam);
			int nHM = NULL, nStep = NULL;
			switch ( nScrollCode )
			{
				case SB_LINEDOWN:
				case SB_PAGEDOWN:
					{
						nHM = GetVisibleCount();
						nStep = (nScrollCode == SB_LINEDOWN ? 1 : nHM);
					}
				case SB_PAGEUP:
				case SB_LINEUP:
				{
					if (!nHM)
					{
						nHM = -GetVisibleCount();
						nStep = (nScrollCode == SB_LINEUP ? -1 : nHM);
					}
					int nPos = pListBox->GetTopIndex();
					LoadPartial( nPos, nHM);
					pListBox->SetTopIndex(nPos + nStep);
					pListBox->SetScrollPos(SB_VERT,  pListBox->GetTopIndex());
					break;
				}
				case SB_THUMBPOSITION:
				{
					int nPos = LoadPartial(HIWORD(wParam), GetVisibleCount());
					pListBox->SetScrollPos(SB_VERT,  HIWORD(wParam));
					pListBox->SetTopIndex(nPos);
					break;
				}
			}
			return FALSE;
			break;
		}
	}
	return TRUE;
}

// Function name	: CQComboBox::OnSetFocus
// Description	    : When control have focus then edit will take the focus
// Return type		: void 
// Argument         : CWnd* pOldWnd
void CQComboBox::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	GetEdit()->SetFocus();

}

// Function name	: CQComboBox::OnCommand
// Description	    : When something is happen in edit control, notify the list control
// Return type		: BOOL 
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
BOOL CQComboBox::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (LOWORD(wParam) == IDEDIT)
		if (HIWORD(wParam) == EN_CHANGE)
		{
			ASSERT( GetEdit() && GetEdit()->GetDlgCtrlID() == IDEDIT);
			CString text,t ;
			GetEdit()->GetWindowText(t);
			Search(t);
		}
	
	return CWnd::OnCommand(wParam, lParam);
}

// Function name	: CQComboBox::Search
// Description	    : Look for the lpszFindItem
// Return type		: void 
// Argument         : LPCTSTR lpszFindItem
void CQComboBox::Search(LPCTSTR lpszFindItem)
{
	if (CListBox* pListBox = GetListBox())
	{
		LoadPartial(0, GetVisibleCount());
		int nItem = pListBox->FindString(-1, lpszFindItem);
		if (nItem < 0)
		{
			int tLine = LinePartial(lpszFindItem);
			LoadPartial(tLine - GetVisibleCount(), 2 * GetVisibleCount());
			nItem = pListBox->FindString(-1, lpszFindItem);
		}
		SetCurrentItem(nItem);
	}
}

// Function name	: CQComboBox::SelectCurrentItem
// Description	    : Select the current item of list. Called if user click the mouse, oor press ENTER
// Return type		: void 
void CQComboBox::SelectCurrentItem()
{
	int nIndex = GetCurrentItem();
	if (nIndex != LB_ERR)
	{
		CString sItem; GetListBox()->GetText(nIndex, sItem);
		GetListBox()->SetScrollPos(SB_VERT, GetListBox()->GetTopIndex());
		GetEdit()->SetWindowText(sItem);
		//Notify the parent that one item was changed
		if (nIndex >= 0)
			if (CWnd* pParent = GetParent())
				pParent->SendMessage(m_nSelChange, (WPARAM)GetDlgCtrlID(), (LPARAM)m_hWnd);
	}
}

// Function name	: CQComboBox::GetCurrentItem
// Description	    : Get current item from list control
// Return type		: int 
int CQComboBox::GetCurrentItem()
{
	return GetListBox()->GetCurSel();
}

// Function name	: CQComboBox::SetCurrentItem
// Description	    : Set current item from list control to nIndex
// Return type		: void 
// Argument         : int nIndex
void CQComboBox::SetCurrentItem(int nIndex)
{
	GetListBox()->SetCurSel(nIndex);
}

// Function name	: CQComboBox::OnCreate
// Description	    : Call OnInit if control is created dynamically
// Return type		: int 
// Argument         : LPCREATESTRUCT lpCreateStruct
int CQComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	OnInit();
	
	return 0;
}

// Function name	: CQComboBox::SetRateWidth
// Description	    : This function will changes the width of inside listcontrol
// Return type		: double 
// Argument         : double dWidthList
double CQComboBox::SetRateWidth(double dWidthList)
{
	double dResult = m_dWidthList;
	m_dWidthList = fabs(dWidthList);
	return dResult;
}

// Function name	: CQComboBox::SetMultipleHeight
// Description	    : 
// Return type		: int 
// Argument         : int nMHeight
int CQComboBox::SetMultipleHeight(int nMHeight)
{
	int nResult = m_nMultipleHeight;
	m_nMultipleHeight = abs(nMHeight);
	if (::IsWindow(m_hWnd))
	{
		Resize();
		m_nCountVisible = GetVisibleCount();
	}
	return nResult;
}

// Function name	: CQComboBox::GetCountItem
// Description	    : 
// Return type		: int 
int CQComboBox::GetCountItem()
{
	return m_nCountItems;
}

// Function name	: CQComboBox::SetCountItems
// Description	    : Set the count of items list box.
// Return type		: void 
// Argument         : int nCount
void CQComboBox::SetCountItems(int nCount)
{
	// Already, you must call GetVisibleCount()
	ASSERT (m_nCountVisible != 0);
	m_nCountItems = nCount;
	// If this need vertical scroll bar, I will put WS_VSCROLL style
	if ( m_nCountItems >= m_nCountVisible)
	{
		CWnd* pWnd = GetListBox();
		// Already you must call OnInit, in fact, you must call SubclassDlgItem , or Create function
		ASSERT (pWnd != NULL);
		pWnd->ModifyStyle(0, WS_VSCROLL);
		SCROLLINFO sInfo;
		 sInfo.cbSize = sizeof(sInfo);
		 sInfo.fMask = SIF_ALL;
		 sInfo.nMin = 0;
		 sInfo.nMax = m_nCountItems - 1;
		 sInfo.nPage = m_nCountVisible - 1;
		 sInfo.nPos = 0;
		 sInfo.nTrackPos = 0;
		pWnd->SetScrollInfo(SB_VERT, &sInfo);
	}
}

// Function name	: CQComboBox::GetVisibleCount
// Description	    : Get count of visible items.
// Return type		: int 
int CQComboBox::GetVisibleCount()
{
	CListBox* pListBox = GetListBox();
	ASSERT( pListBox );
	CRect r;
	if (pListBox->GetItemRect(0, r) == LB_ERR)
	{
		int nItem = pListBox->AddString(_T(""));
		pListBox->GetItemRect(0, r);
		pListBox->DeleteString(nItem);
	}
	CRect rClient; pListBox->GetClientRect(rClient);
	return rClient.Height() / r.Height() + 1;
}

// Function name	: CQComboBox::AlreadyLoadPartialListBox
// Description	    : 
// Return type		: void 
// Argument         : int nLineFrom
// Argument         : int nHowMany
int CQComboBox::AlreadyLoadPartialListBox(int nLineFrom, int nHowMany)
{
	//Already the load was made
	return nLineFrom;
}

// Function name	: CQComboBox::GetFirstQComboBox
// Description	    : Statical function. Return first element as QComboBox
// Return type		: CQComboBox* 
CQComboBox* CQComboBox::GetFirstQComboBox()
{
	if (POSITION position = m_mapUnloadedQCombos.GetStartPosition())
	{
		CQComboBox* pCombo = NULL;
		BOOL bLoaded = TRUE;
		m_mapUnloadedQCombos.GetNextAssoc(position, pCombo, bLoaded);
		return pCombo;
	}
	return NULL;
}

// Function name	: CQComboBox::OnTimer
// Description	    : 
// Return type		: void 
// Argument         : UINT nIDEvent
void CQComboBox::OnTimer(UINT nIDEvent) 
{
	switch (nIDEvent)
	{
		case QIDTIMERSTARTLOADITEMS:
		{
			KillTimer(QIDTIMERSTARTLOADITEMS);
			SetTimer(QIDTIMERLOADITEMS, QTIMELOADITEMS, NULL);
		}
		case QIDTIMERLOADITEMS:
		{
			POSITION position = m_mapUnloadedQCombos.GetStartPosition();
			while (position)
			{
				CQComboBox* pCombo = NULL;
				BOOL bLoaded = TRUE;
				m_mapUnloadedQCombos.GetNextAssoc(position, pCombo, bLoaded);
				if (pCombo->IsAlreadyLoad())
					m_mapUnloadedQCombos.RemoveKey(pCombo);
				else
				{
					pCombo->LoadPartial(0, GetVisibleCount());
				}
			}
			break;
		}
	}
	
	CWnd::OnTimer(nIDEvent);
}

// Function name	: CQComboBox::IsAlreadyLoad
// Description	    : Return TRUE if listvox is already loaded.
// Return type		: BOOL 
BOOL CQComboBox::IsAlreadyLoad()
{
	return m_fctLoadFunction == AlreadyLoadPartialListBox;
}

// Function name	: CQComboBox::LoadPartial
// Description	    : 
// Return type		: void 
// Argument         : int nLineFrom
// Argument         : int nHowMany
int CQComboBox::LoadPartial(int nLineFrom, int nHowMany)
{
	return (this->*m_fctLoadFunction)(nLineFrom, nHowMany);
}


// Function name	: CQComboBox::LoadPartialListBox
// Description	    : 
// Return type		: void 
int CQComboBox::LoadPartialListBox(int nLineFrom, int nHowMany)
{
	return m_QuickLoader.Load(nLineFrom, nHowMany);
}

// Function name	: CQComboBox::Line
// Description	    : Return line nLine, by calling own statical function
// Return type		: LPCTSTR 
// Argument         : int nLine
// Argument         : LPARAM & lParam
LPCTSTR CQComboBox::Line(int nLine, LPARAM& lParamItem)
{
	return m_fctLine(nLine, lParamItem, m_lParam);
}

// Function name	: CQComboBox::LinePartial
// Description	    : return the index of real line, which has string equal with lpszItemPartial
// Return type		: int 
// Argument         : LPCTSTR lpszItemPartial
int CQComboBox::LinePartial(LPCTSTR lpszItemPartial)
{
	if (m_fctLinePartial)
		return m_fctLinePartial(lpszItemPartial, m_lParam);
	return 0;
}

//QSnapLoader implementation
int CQComboBox::QSnapLoader::SNodeItemsInfo::m_nCountRef = 0;
// Function name	: CQComboBox::QSnapLoader::~QSnapLoader
// Description	    : virtual destructor
// Return type		: 
CQComboBox::QSnapLoader::~QSnapLoader()
{
	SNodeItemsInfo* pNodeNext = m_pFirstNode;
	while (pNodeNext)
	{
		SNodeItemsInfo* pNodeDelete = pNodeNext;
		pNodeNext = pNodeNext->m_pNextNode;
		delete pNodeDelete;
	};
}

// Function name	: CQComboBox::QSnapLoader::QSnapLoader
// Description	    : default constructor
// Return type		: 
CQComboBox::QSnapLoader::QSnapLoader()
{
	m_pFirstNode = new SNodeItemsInfo(0,0,0);
}

// Function name	: CQComboBox::QSnapLoader::SetParent
// Description	    : Set the parent of this structure
// Return type		: void 
// Argument         : CQComboBox * pParent
void CQComboBox::QSnapLoader::SetParent(CQComboBox * pParent)
{
	m_pParent = pParent;
}

// Function name	: CQComboBox::QSnapLoader::GetListNodes
// Description	    : 
// Return type		: CString 
CString CQComboBox::QSnapLoader::GetListNodes()
{
	CString text;
	SNodeItemsInfo* pIncreaseNode = m_pFirstNode;
	int s = 0;
	while (pIncreaseNode)
	{
		CString t;
		t.Format(_T("(%i,%i,%i, [%i,%i])\r\n"), pIncreaseNode->m_nItemLine, pIncreaseNode->m_nCount, pIncreaseNode->m_nItemLB, pIncreaseNode->GetLastLine(), pIncreaseNode->GetLastItem());
		text += t;
		s += pIncreaseNode->m_nCount;
		pIncreaseNode = pIncreaseNode->m_pNextNode;
	}
	CString t;
	t.Format(_T("Count loaded: %i, Count items. listbox() %i"), s, m_pParent->GetListBox()->GetCount());
	text += t;
	return text;
}

// Function name	: CQComboBox::QSnapLoader::Load
// Description	    : 
// Return type		: void 
// Argument         : int nItemFrom
// Argument         : int nHowMany
// This function will return the real position into listbox.
int CQComboBox::QSnapLoader::Load(int nItemFrom, int nHowMany)
{
	int nIF = abs(nItemFrom + (nHowMany < 0 ? nHowMany : 0));
	int nHM = abs(nHowMany), nResult = nItemFrom;
	CWnd* pWndParentWindowOfCombo = m_pParent->GetParent();
	if (nHM = min(nHM, max(0,m_pParent->GetCountItem() - nIF)))
	{
		//Something must load
		ASSERT (nHM != NULL);
		SNodeItemsInfo* pNodeNext = m_pFirstNode;
		SNodeItemsInfo* pNodePrev = NULL;
		// Already the constructor was called
		ASSERT (pNodeNext);
		//Find the nodes ie pPrevNext->m_nItemLine <= nIF < pPrevNext->m_nItemLine
		while (pNodeNext && (nIF >= pNodeNext->m_nItemLine))
		{
			pNodePrev = pNodeNext;
			pNodeNext = pNodeNext->m_pNextNode;
		}

		// If in the first block , number of items count is equal with total number of items,
		// then this function will not be called again. The next function that will
		//be called will be AlreadyLoadPartialListBox.
		if (m_pFirstNode->m_nCount == m_pParent->GetCountItem())
		{
			m_pParent->m_fctLoadFunction = m_pParent->AlreadyLoadPartialListBox;
			return nItemFrom;
		}

		LPCTSTR lpszItemLB = NULL;
		LPARAM lParam = NULL;
		int nFirst = pNodePrev->GetLastLine(), nItem = pNodePrev->GetLastItem();
		CListBox* pListBox = m_pParent->GetListBox();
		nResult = pNodePrev->GetLastItem();

		if (pNodeNext == NULL)
		{
			// After the prev node do not exist another node.
			BOOL bEnd = TRUE;
			if (nIF > nFirst)
			{
				SNodeItemsInfo* sThis = pNodePrev;
				pNodePrev = new SNodeItemsInfo(nIF,0, nResult );
				sThis->m_pNextNode = pNodePrev;
				pNodePrev->m_pPrevNode = sThis;
				nFirst = nIF;
				bEnd = FALSE;
			}
			else
			{
				nResult = pNodePrev->m_nItemLB + nIF - pNodePrev->m_nItemLine;
			}
			NotifyWindow(pWndParentWindowOfCombo, m_nLoading, m_pParent->m_hWnd, nFirst);
			int i = 0;
			for (i = 0; (lpszItemLB = m_pParent->Line(nFirst + i, lParam)) && (i < nHM); i++)
			{
				pListBox->SetItemData(nItem = pListBox->InsertString(nItem, lpszItemLB), lParam);
				pNodePrev->m_nCount++;
				nItem++;
			}
			NotifyWindow(pWndParentWindowOfCombo, m_nLoaded, m_pParent->m_hWnd, i);
		}
		else
		{
			SNodeItemsInfo* pIncreaseNode = pNodeNext->m_pNextNode;
			int nDiff = pNodeNext->m_nItemLine - nFirst;
			ASSERT ( nDiff >= 0 );
			nItem = nResult; // first item that will be inserted
			// {...+..} ___ {...+..}
			if (nDiff <= nHM)
			{
				// The real nHM will be the diference between nHowMany - nDiff
				nHM = nDiff;
				// Try to restrict these node in only one.
				pNodePrev->m_nCount += pNodeNext->m_nCount + nHM;
				pNodePrev->m_pNextNode = pNodeNext->m_pNextNode;
				delete pNodeNext;
				nResult = pNodePrev->m_nItemLB + nIF - pNodePrev->m_nItemLine;
			}
			else
			{
				//      nFirst
				//        /--- > nHM --\
				// {...+..} __+________{......}
				if (nIF < nFirst)
				{
					nResult = pNodePrev->m_nItemLB + nIF - pNodePrev->m_nItemLine;
					nFirst = pNodePrev->GetLastLine();
					pNodePrev->m_nCount += nHM;
					pIncreaseNode = pNodeNext;
				}
				// {......} ______+___ {...+...}
				else
					if (nIF + nHM >= pNodeNext->m_nItemLine)
					{
						nHM = pNodeNext->m_nItemLine - nIF;
						pNodeNext->m_nItemLine = nIF;
						pNodeNext->m_nCount += nHM;
						//pNodeNext->m_nItemLB remains constant
						nItem = pNodeNext->m_nItemLB;
						nFirst = nIF;
						nResult = pNodeNext->m_nItemLB;
					}
					// {......} __+____+___ {......}
					else
					{
						SNodeItemsInfo* sThis = new SNodeItemsInfo(nIF, nHM, nResult );
						sThis->m_pPrevNode = pNodePrev;
						sThis->m_pNextNode = pNodeNext;
						pNodePrev->m_pNextNode = sThis;
						pNodeNext->m_pPrevNode = sThis;
						nFirst = nIF;
						pIncreaseNode = pNodeNext;
					}
			}
			// if some items must insert, do it
			if (nHM > 0)
			{
				NotifyWindow(pWndParentWindowOfCombo, m_nLoading, m_pParent->m_hWnd, nFirst);
				for (int i = 0; i < nHM; i++)
				{
					lpszItemLB = m_pParent->Line(nFirst + i, lParam);
					// while pNodePrev and pNodeNext exist !
					ASSERT (lpszItemLB);
					pListBox->SetItemData(nItem = pListBox->InsertString(nItem, lpszItemLB), lParam);
					nItem++;
				}
				while (pIncreaseNode)
				{
					pIncreaseNode->m_nItemLB += nHM;
					pIncreaseNode = pIncreaseNode->m_pNextNode;
				}
				NotifyWindow(pWndParentWindowOfCombo, m_nLoaded, m_pParent->m_hWnd, nHM);
			}

		}
	}
	return nResult;
}

// Function name	: CQComboBox::QSnapLoader::GetItemLine
// Description	    : return the real line, converts from nItemLB
// Return type		: int 
// Argument         : int nItemLB
int CQComboBox::QSnapLoader::GetItemLine(int nItemLB)
{
	nItemLB = max(0,nItemLB);
	SNodeItemsInfo* pNodeNext = m_pFirstNode;
	while (pNodeNext && ( pNodeNext->m_nItemLB > nItemLB ))
		pNodeNext = pNodeNext->m_pNextNode;
	return pNodeNext->m_nItemLine  + nItemLB - pNodeNext->m_nItemLB;
}

