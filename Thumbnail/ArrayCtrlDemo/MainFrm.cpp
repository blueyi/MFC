/////////////////////////////////////////////////////////////////////////////
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ArrayCtrlDemo.h"

#include "ObjInfo.h"
#include "ArrayCtrl.h"
#include "SfxApi.h"
#include "MainFrm.h"
#include "Dialog.h"
#include "ShowWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	ID_AYCTRL1		10
#define	ID_AYCTRL2		20
#define	ID_AYCTRL4		30
#define	ID_AYCTRL3		80
#define	ID_TABCTRL		90

#define	ID_AYCTRL4UP	ID_AYCTRL4+TAB_ITEMS-1

#define	BORDER_WIDTH	4
#define	BORDER_HEIGHT	4

#define	W_FRAME			BORDER_WIDTH * 2
#define	H_FRAME			BORDER_HEIGHT * 2

#define	SPLASH_SIZE		32

#define	NAME_FORMAT		_T("%s\\%s")
#define	SEARCH_FORMAT	_T("%s\\*.*")

int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg, LPARAM lp, LPARAM pData);

int		nCbord	= 8;
HICON	hSmile, hFrown, hUnimpr;
TCHAR	szPath1[MAX_PATH], szPath2[MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_ENTERSIZEMOVE, OnEnterSizeMove)
	ON_MESSAGE(WM_EXITSIZEMOVE, OnExitSizeMove)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()

	ON_NOTIFY_RANGE(ACN_DRAWITEM,		ID_AYCTRL1, ID_AYCTRL2, OnNotifyDrawItem)
	ON_NOTIFY_RANGE(ACN_NEEDTIPTEXT,	ID_AYCTRL1, ID_AYCTRL2, OnNotifyGetText)
	ON_NOTIFY_RANGE(ACN_DELETEITEM,		ID_AYCTRL1, ID_AYCTRL2, OnNotifyDelete)

	ON_NOTIFY_RANGE(ACN_DRAWITEM,		ID_AYCTRL4, ID_AYCTRL4UP, OnNotifyDrawColor)
	ON_NOTIFY_RANGE(ACN_NEEDTIPTEXT,	ID_AYCTRL4, ID_AYCTRL4UP, OnNotifyGetInfo)
	ON_NOTIFY_RANGE(ACN_CLICK,			ID_AYCTRL1, ID_AYCTRL4UP, OnNotifyLButtonDown)
	ON_NOTIFY_RANGE(ACN_RCLICK,			ID_AYCTRL1, ID_AYCTRL4UP, OnNotifyRButtonDown)
	ON_NOTIFY_RANGE(ACN_DBCLICK,		ID_AYCTRL1, ID_AYCTRL4UP, OnNotifyLButtonDblClk)

	ON_NOTIFY(TCN_SELCHANGE,	ID_TABCTRL, OnTabSelItem)
	ON_NOTIFY(ACN_DRAWITEM,		ID_AYCTRL3, OnSplashDrawItem)

	ON_COMMAND(ID_ITEM_COPY,	OnItemCopy)
	ON_COMMAND(ID_ITEM_REMOVE,	OnItemRemove)
	ON_COMMAND(ID_ITEM_SPLASH,	OnItemSplash)
	ON_COMMAND(ID_MAIN_BKCOLOR, OnMainBkColor)
	ON_COMMAND(ID_CTRL_BKCOLOR, OnCtrlBkColor)
	ON_COMMAND(ID_CTRL_GLCOLOR, OnCtrlGlColor)
	ON_COMMAND(ID_CTRL_TOGGLE,	OnCtrlToggle)
	ON_COMMAND(ID_CTRL_DIR,		OnCtrlDir)
	ON_COMMAND(ID_CTRL_THUMBSIZE, OnChangeSize)
	ON_COMMAND(ID_CTRL_DELETE,	OnDeleteItems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame implementation

// Constructor
CMainFrame::CMainFrame()
{
	int			i;

	// TODO: add member initialization code here
	m_bAutoMenuEnable = FALSE;
	m_pNullImage = new CBitmap;
	m_pNullImage->LoadBitmap(_T("IDB_IMAGENULL"));

	szPath1[0] = NIL;
	szPath2[0] = NIL;
	m_pActCtrl = NULL;
	m_pSplashImage = NULL;
	for(i=0; i<TAB_ITEMS; i++) m_pACtrlVect[i] = NULL;
	m_nTabSel = 0;
}

// Destroyer
CMainFrame::~CMainFrame()
{
}

//-------------------------------------------------------------------------//
// Window creation                                                         //
//-------------------------------------------------------------------------//
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int			i, nW, nH;
	CRect		rClient, rControl;
	CSize		sItem;
	TCITEM		tci;
	TCHAR		szTCtext[MAX_PATH];

	m_fResizing = 0;

	if( CFrameWnd::OnCreate(lpCreateStruct) == -1 ) return -1;

	// Register the image show windows class
	m_pShowClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW, ::LoadCursor(NULL, IDC_ARROW), HBRUSH(NULL), NULL);

	// Load some stuff
	m_CtrlMenu.LoadMenu(IDM_CTRL);
	m_ItemMenu.LoadMenu(IDM_ITEM);
	m_HandCur = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR1));
	m_crBackGnd = ::GetSysColor(COLOR_3DFACE);
	m_pBrush = new CBrush(m_crBackGnd);
	m_pFont = SfxCreateFont(_T("Arial"), 8, 0, 0, 0);
	hSmile = (HICON)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SMILE), IMAGE_ICON, 16, 16, 0);
	hFrown = (HICON)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_FROWN), IMAGE_ICON, 16, 16, 0);
	hUnimpr = (HICON)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_UNIMPR), IMAGE_ICON, 16, 16, 0);

	GetClientRect(&rClient);
	nW = rClient.Width();
	nH = rClient.Height();

	// create first Array control (unmoveable)
	rControl.SetRect(0, 0, nW/2, nH/2);
	sItem = CSize(64,64);
	m_pACtrl1 = new CArrayCtrl;
	if( !m_pACtrl1->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ACS_GRIDLINES | ACS_BALLOONTIP | ACS_CLIENTEDGE | ACS_USERDATA, 
								rControl, (CWnd*)this, ID_AYCTRL1, sItem) ) return -1;
	m_pACtrl1->SetTipColor(RGB(0,255,0), RGB(0,0,0));
	m_pACtrl1->SetCursor(m_HandCur);
	m_pACtrl1->SetCtrlData((LPARAM)TPTR(szPath1));

	// create second Array control (follow parent window resizing to right)
	rControl.SetRect(nW/2, 0, nW, nH/2);
	sItem = CSize(128, 192);			// wallet size
	m_pACtrl2 = new CArrayCtrl;
	if( !m_pACtrl2->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ACS_GRIDLINES | ACS_BALLOONTIP | ACS_CLIENTEDGE | ACS_USERDATA, 
								rControl, (CWnd*)this, ID_AYCTRL2, sItem) ) return -1;
	m_pACtrl2->SetTipColor(RGB(255,255,0), RGB(0,0,0));
	m_pACtrl2->SetGridThickness(4);
	m_pACtrl2->SetCtrlData((LPARAM)TPTR(szPath2));

	// create third Array control (image viewer, follow parent window to bottom)
	rControl.SetRect(nCbord, nH/2 + nCbord, nW/2 - nCbord, nH - nCbord * 2);
	m_pACtrl3 = new CArrayCtrl;
	if( !m_pACtrl3->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ACS_CLIENTEDGE, 
								rControl, (CWnd*)this, ID_AYCTRL3) ) return -1;
	m_pACtrl3->SetItemSize(SPLASH_SIZE, SPLASH_SIZE);

	// create fourth Tab control (follow parent window resizing to right and bottom)
	rControl.SetRect(nW/2, nH/2 + nCbord, nW - nCbord, nH - nCbord);
	m_pTabCtrl = new CTabCtrl;
	m_pTabCtrl->Create(WS_CHILD | WS_VISIBLE, rControl, (CWnd*)this, ID_TABCTRL);
	m_pTabCtrl->SetFont(m_pFont);
	m_pTabCtrl->SetExtendedStyle(TCS_BUTTONS | TCS_FLATBUTTONS);
	tci.mask = TCIF_TEXT;
	tci.iImage = -1;
	for(i=0; i<TAB_ITEMS; i++)
	{
		wsprintf(szTCtext, "Bri %d%%", 100 - i*10);
		tci.pszText = TPTR(szTCtext);
		m_pTabCtrl->InsertItem(i, &tci); 
	}

	BuildControl(0);
	m_nTabSel = 0;

	return 0;
}

//-------------------------------------------------------------------------//
// Before window creation                                                  //
//-------------------------------------------------------------------------//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) ) return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style |= WS_CLIPCHILDREN;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//-------------------------------------------------------------------------//
// frame window has focus                                                  //
//-------------------------------------------------------------------------//
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the active control window
	if( m_pActCtrl ) m_pActCtrl->SetFocus();
}

//-------------------------------------------------------------------------//
// begin resize action                                                     //
//-------------------------------------------------------------------------//
LRESULT CMainFrame::OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
	m_fResizing = 1;
	return 0;
}

//-------------------------------------------------------------------------//
// end resize action                                                       //
//-------------------------------------------------------------------------//
LRESULT CMainFrame::OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
	m_fResizing = 0;
	ResizeChildren();
	return 0;
}

//-------------------------------------------------------------------------//
// window has changed her size                                             //
//-------------------------------------------------------------------------//
void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	if( m_fResizing ) return;
	if( nType == SIZE_MINIMIZED ) return;
	ResizeChildren();
}


//-------------------------------------------------------------------------//
// resize all children control window                                      //
//-------------------------------------------------------------------------//
void CMainFrame::ResizeChildren()
{
	int				nNewW, nW1, nW3;
	int				nH1, nH2;
	CRect			rcClient, rcCtrl1, rcCtrl2, rcCtrl3;

	GetClientRect(&rcClient);
	m_pACtrl1->GetWindowRect(&rcCtrl1);
	nW1 = rcCtrl1.Width();
	nH1 = rcCtrl1.Height();
	m_pACtrl2->GetWindowRect(&rcCtrl2);
	nH2 = rcCtrl2.Height();
	m_pACtrl3->GetWindowRect(&rcCtrl3);
	nW3 = rcCtrl3.Width();
	nNewW = rcClient.Width() - nW1;
	if( nNewW <= 0 ) return;
	m_pACtrl2->MoveWindow(nW1, 0, nNewW, nH2, TRUE);
	m_pACtrl3->MoveWindow(nCbord, nH1 + nCbord, nW3, rcClient.Height() - nH1 - nCbord * 2, TRUE);

	m_pTabCtrl->MoveWindow(nW3 + nCbord * 2, nH2 + nCbord, nNewW - nCbord, rcClient.Height() - nH2 - nCbord * 2, TRUE);
	m_pTabCtrl->GetClientRect(&rcCtrl3);
	m_pTabCtrl->AdjustRect(FALSE, &rcCtrl3);
	ReflectChange(&rcCtrl3);
}

//-------------------------------------------------------------------------//
// various commands management                                             //
//-------------------------------------------------------------------------//
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the controls have first crack at the command
	if( m_pACtrl1->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) ) return TRUE;
	if( m_pACtrl2->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) ) return TRUE;
	if( m_pACtrl3->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) ) return TRUE;
	if( m_pACtrlVect[m_nTabSel]->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) ) return TRUE;
	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//-------------------------------------------------------------------------//
// request to erase background                                             //
//-------------------------------------------------------------------------//
BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
	int			ww, hw;
	CBrush		*pOrigBrush;
	CRect		rcFrame, rcCtrl;

	GetClientRect(&rcFrame);
	ww = rcFrame.Width();
	hw = rcFrame.Height();
	pOrigBrush = pDC->SelectObject(m_pBrush);
	pDC->PatBlt(0, 0, ww, hw, PATCOPY);
	pDC->SelectObject(pOrigBrush);
	return 1;
}

//-------------------------------------------------------------------------//
//  User has clicked left button over an Array control                     //
//-------------------------------------------------------------------------//
void CMainFrame::OnNotifyLButtonDown(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* pResult)
{
	LPACITEMACTIVATE	lpacia;

	*pResult = 0;
	lpacia = (LPACITEMACTIVATE)pNotifyStruct;
	SetActiveCtrl(lpacia->pControl);
}

//-------------------------------------------------------------------------//
//  User has clicked right button over an Array control                    //
//-------------------------------------------------------------------------//
void CMainFrame::OnNotifyRButtonDown(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* pResult)
{
	CMenu*				pSubMenu;
	LPACITEMACTIVATE	lpacia;
	int					nStatus;
	CPoint				point;

	*pResult = 0;
	lpacia = (LPACITEMACTIVATE)pNotifyStruct;
	point = lpacia->ptAction;
	SetActiveCtrl(lpacia->pControl);

	// select appropriate menu to be displayed
	if( lpacia->nItem < 0 )
	{
		pSubMenu = m_CtrlMenu.GetSubMenu(0);
		nStatus = MF_ENABLED;
		if( (nCtrlId >= ID_AYCTRL4) && (nCtrlId <= ID_AYCTRL4UP) ) nStatus = MF_GRAYED;
		m_CtrlMenu.EnableMenuItem(ID_CTRL_DIR, nStatus);
		m_CtrlMenu.EnableMenuItem(ID_CTRL_DELETE, nStatus);
	}
	else
	{
		if( (nCtrlId >= ID_AYCTRL4) && (nCtrlId <= ID_AYCTRL4UP) ) return;
		pSubMenu = m_ItemMenu.GetSubMenu(0);
		m_ItemMenu.GetSubMenu(0);
	}
	m_pActCtrl->ClientToScreen(&point);
	pSubMenu->TrackPopupMenu(TPM_CENTERALIGN, point.x, point.y, this, NULL);
}

//-------------------------------------------------------------------------//
//  User has double clicked left button over an Array control              //
//-------------------------------------------------------------------------//
void CMainFrame::OnNotifyLButtonDblClk(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* pResult)
{
	CObjInfo*			pObjInfo;
	CClrInfo*			pClrInfo;
	LPACITEMACTIVATE	lpacia;
	LPCTSTR				lpszPath;
	CString				sFileName;

	*pResult = 0;
	lpacia = (LPACITEMACTIVATE)pNotifyStruct;
	if( (nCtrlId >= ID_AYCTRL4) && (nCtrlId <= ID_AYCTRL4UP) )
	{
		pClrInfo = (CClrInfo*)(lpacia->dwParam);
		ViewColor(pClrInfo);
		return;
	}

	SetActiveCtrl(lpacia->pControl);
	pObjInfo = (CObjInfo*)(lpacia->dwParam);
	if( lpacia->nItem < 0 ) return;
	lpszPath = (LPCTSTR)(m_pActCtrl->GetCtrlData());
	sFileName.Format(NAME_FORMAT, (LPCTSTR)lpszPath, (LPCTSTR)pObjInfo->GetName());
	switch( pObjInfo->GetFormat() & OBJECT_FORMAT_MASK )
	{
	case OBJECT_FORMAT_ICO:
		// You must register your own associated application to this file format.
		// I have register a modified IconPro (© Microsoft) application in order to accepting file name
		// from command line
		ShellExecute(m_hWnd, _T("open"), sFileName, NULL, NULL, SW_SHOWNORMAL);
		break; 
	case OBJECT_FORMAT_TXT:
		// Normally, it is Notepad.
		::SfxRunProc(_T("notepad.exe"), (LPCTSTR)sFileName);
		break; 
	case OBJECT_FORMAT_IMG:
		ViewImage(sFileName);
		break;
	}
}

//-------------------------------------------------------------------------//
// Tooltip notification message for obtaining text (ACN_NEEDTIPTEXT)       //
//-------------------------------------------------------------------------//
void CMainFrame::OnNotifyGetText(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* pResult)
{
	CObjInfo*		pObjInfo;
	LPACTOOLTIPINFO	lpactti;

	*pResult = 0;
	lpactti = (LPACTOOLTIPINFO)pNotifyStruct;
	pObjInfo = (CObjInfo*)(lpactti->dwParam);
	lstrcpy(lpactti->lpszTipText, pObjInfo->GetName());
}

//-------------------------------------------------------------------------//
//  Control is deleting an item, so it notify this to parent               //
//-------------------------------------------------------------------------//
void CMainFrame::OnNotifyDelete(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* pResult)
{
	CObjInfo*		pObjInfo;
	LPACITEMINFO	lpacii;

	*pResult = 0;
	lpacii = (LPACITEMINFO)pNotifyStruct;
	pObjInfo = (CObjInfo*)(lpacii->dwParam);
	if( pObjInfo ) delete pObjInfo;
}

//-------------------------------------------------------------------------//
// Copy bitmap to clipboard                                                //
//-------------------------------------------------------------------------//
void CMainFrame::OnItemCopy()
{
	CObjInfo*	pObjInfo;
	int			nItem;
	CBitmap*	pImage;
	LPCTSTR		lpszPath;
	CString		sFileName;

	nItem = m_pActCtrl->GetSelectedItem();
	if( nItem < 0 ) return;
	pObjInfo = (CObjInfo*)(m_pActCtrl->GetItemData(nItem));

	// Only image will be copied into clipboard
	switch( pObjInfo->GetFormat() & OBJECT_FORMAT_MASK)
	{
	case OBJECT_FORMAT_ICO:
	case OBJECT_FORMAT_TXT:
		break;
	case OBJECT_FORMAT_IMG:
		lpszPath = (LPCTSTR)(m_pActCtrl->GetCtrlData());
		sFileName.Format(NAME_FORMAT, (LPCTSTR)lpszPath, (LPCTSTR)pObjInfo->GetName());
		pImage = ::SfxLoadImage((LPCTSTR)sFileName);
		if( pImage == NULL ) break;
		OpenClipboard();
		EmptyClipboard();
		SetClipboardData(CF_BITMAP, pImage->GetSafeHandle()); 
		CloseClipboard();
		break;
	}
}

//-------------------------------------------------------------------------//
// Splash the item to control 3                                            //
//-------------------------------------------------------------------------//
void CMainFrame::OnItemSplash()
{
	CObjInfo*	pObjInfo;
	int			nItem;
	LPCTSTR		lpszPath;
	CString		sFileName;

	nItem = m_pActCtrl->GetSelectedItem();
	if( nItem < 0 ) return;
	pObjInfo = (CObjInfo*)(m_pActCtrl->GetItemData(nItem));
	lpszPath = (LPCTSTR)(m_pActCtrl->GetCtrlData());
	sFileName.Format(NAME_FORMAT, (LPCTSTR)lpszPath, (LPCTSTR)pObjInfo->GetName());
	switch( pObjInfo->GetFormat() & OBJECT_FORMAT_MASK )
	{
	case OBJECT_FORMAT_IMG:
		SplashToControl(sFileName);	
		break;
	}
}

//-------------------------------------------------------------------------//
// Remove the item from the control                                        //
//-------------------------------------------------------------------------//
void CMainFrame::OnItemRemove()
{
	int			nItem;

	nItem = m_pActCtrl->GetSelectedItem();
	if( nItem < 0 ) return;
	m_pActCtrl->RemoveItem(nItem);
}

//-------------------------------------------------------------------------//
// Change the background color of the main frame window                    //
//-------------------------------------------------------------------------//
void CMainFrame::OnMainBkColor() 
{
	CDC				*pDC;
	CColorDialog	dlg;

	dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	dlg.m_cc.rgbResult = m_crBackGnd;
	if( dlg.DoModal() != IDOK ) return;

	m_crBackGnd = dlg.GetColor();
	if( m_pBrush ) delete m_pBrush;
	m_pBrush = new CBrush(m_crBackGnd);

	pDC = GetDC();
	OnEraseBkgnd(pDC);
	ReleaseDC(pDC);
}

//-------------------------------------------------------------------------//
// Change the control background color                                     //
//-------------------------------------------------------------------------//
void CMainFrame::OnCtrlBkColor() 
{
	CColorDialog	dlg;

	dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	dlg.m_cc.rgbResult = m_pActCtrl->GetBkColor();
	if( dlg.DoModal() != IDOK ) return;
	ReflectChange(0, dlg.GetColor());
}

//-------------------------------------------------------------------------//
// Change the gridline color                                               //
//-------------------------------------------------------------------------//
void CMainFrame::OnCtrlGlColor() 
{
	CColorDialog	dlg;

	dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	dlg.m_cc.rgbResult = m_pActCtrl->GetGridColor();
	if( dlg.DoModal() != IDOK ) return;
	ReflectChange(1, dlg.GetColor());
}

//-------------------------------------------------------------------------//
// Activate/Deactivate gridline                                            //
//-------------------------------------------------------------------------//
void CMainFrame::OnCtrlToggle() 
{
	m_pActCtrl->SetGridLines((m_pActCtrl->GetGridLines() == TRUE? FALSE: TRUE));
}

//-------------------------------------------------------------------------//
// Delete all items                                                        //
//-------------------------------------------------------------------------//
void CMainFrame::OnDeleteItems() 
{
	m_pActCtrl->RemoveAllItems();
}

//-------------------------------------------------------------------------//
// Notification message from an CArrayCtrl for drawing item (ACN_DRAWITEM) //
//-------------------------------------------------------------------------//
void CMainFrame::OnNotifyDrawItem(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result)
{
	LPACITEMINFO	lpacii;
	CDC*			pDC;
	CBrush*			pOrigBrush;
	CPen*			pOrigPen;
	CPen			Border;
	CObjInfo*		pObjInfo;
	int				nWidth, nHeight;
	COLORREF		crDraw;

	*result = 0;
	lpacii = (LPACITEMINFO)pNotifyStruct;
	pDC = lpacii->pDC;
	nWidth = lpacii->nWidth;
	nHeight = lpacii->nHeight;
	pObjInfo = (CObjInfo*)(lpacii->dwParam);

	switch( pObjInfo->GetFormat() & OBJECT_FORMAT_MASK )
	{
	case OBJECT_FORMAT_ICO:
		RenderIcon(pDC, pObjInfo->GetIcon(), nWidth, nHeight);
		break;
	case OBJECT_FORMAT_TXT:
		RenderText(pDC, pObjInfo->GetText(), nWidth, nHeight);
		break;
	case OBJECT_FORMAT_IMG:
		RenderImage(pDC, pObjInfo->GetBitmap(), nWidth, nHeight);
		break;
	default:
		RenderInvalid(pDC);
		return;
	}
	if( lpacii->dwState & ACIS_SELECTED )
	{
		crDraw = SfxContrastColor(lpacii->pControl->GetBkColor());
		Border.CreatePen(PS_SOLID, 3, crDraw);
		pOrigBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		pOrigPen = pDC->SelectObject(&Border);
		pDC->Rectangle(0, 0, nWidth, nHeight);
		pDC->SelectObject(pOrigBrush);
		pDC->SelectObject(pOrigPen);
	}
	return;
}

//-------------------------------------------------------------------------//
// Rendering invalid object market-place into item DC                      //
//-------------------------------------------------------------------------//
void CMainFrame::RenderInvalid(CDC* pDC)
{
	::SfxDrawImage(pDC, BORDER_WIDTH, BORDER_HEIGHT, 0, 0, m_pNullImage, 0);
	return;
}

//-------------------------------------------------------------------------//
// Rendering icon into item DC                                             //
//-------------------------------------------------------------------------//
void CMainFrame::RenderIcon(CDC* pDC, HICON hIcon, int nWidth, int nHeight)
{
	int				nBmpW, nBmpH, nStartX, nStartY, nInnerW, nInnerH;
	BITMAP			bminfo;
	ICONINFO		iconinfo;

	nBmpW = ::GetSystemMetrics(SM_CXICON);
	nBmpH = ::GetSystemMetrics(SM_CYICON);
	if( ::GetIconInfo(hIcon,&iconinfo) )
	{
		::GetObject(iconinfo.hbmColor, sizeof(bminfo), (LPVOID)&bminfo);
		nBmpW = bminfo.bmWidth;
		nBmpH = bminfo.bmHeight;
		::DeleteObject(iconinfo.hbmMask);
		::DeleteObject(iconinfo.hbmColor);
	}
	nInnerW = nWidth - W_FRAME;
	nInnerH = nHeight - H_FRAME;
	nStartX = BORDER_WIDTH + (nInnerW - nBmpW)/2;
	nStartY = BORDER_HEIGHT + (nInnerH - nBmpH)/2;
	::DrawIconEx(pDC->GetSafeHdc(), nStartX, nStartY, hIcon, 0, 0, 0, NULL, DI_NORMAL);
	return;
}

//-------------------------------------------------------------------------//
// Rendering text into item DC                                             //
//-------------------------------------------------------------------------//
void CMainFrame::RenderText(CDC* pDC, LPCTSTR lpszText, int nWidth, int nHeight)
{
	CFont*			pOrigFont;
	CRect			rcBounds;

	rcBounds.SetRect(BORDER_WIDTH, BORDER_HEIGHT, nWidth - W_FRAME, nHeight - H_FRAME);
	pOrigFont = pDC->SelectObject(m_pFont); 
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(lpszText, lstrlen(lpszText), &rcBounds, DT_WORDBREAK);
	pDC->SelectObject(pOrigFont); 
	return;
}

//-------------------------------------------------------------------------//
// Rendering image into item DC                                            //
//-------------------------------------------------------------------------//
void CMainFrame::RenderImage(CDC* pDC, CBitmap* pBitmap, int nWidth, int nHeight)
{
	int				nBmpW, nBmpH, nStartX, nStartY, nInnerW, nInnerH;
	BITMAP			bminfo;

	pBitmap->GetObject(sizeof(bminfo), (LPVOID)&bminfo);
	nBmpW = bminfo.bmWidth;
	nBmpH = bminfo.bmHeight;
	nInnerW = nWidth - W_FRAME;
	nInnerH = nHeight - H_FRAME;
	nStartX = BORDER_WIDTH + (nInnerW - nBmpW)/2;
	nStartY = BORDER_HEIGHT + (nInnerH - nBmpH)/2;
	SfxDrawImage(pDC, nStartX, nStartY, 0, 0, pBitmap, 0);
	return;
}

//-------------------------------------------------------------------------//
// Notification message from an CArrayCtrl for drawing item (ACN_DRAWITEM) //
//-------------------------------------------------------------------------//
void CMainFrame::OnSplashDrawItem(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	LPACITEMINFO	lpacii;
	CDC*			pDC;
	int				ncol, nrow;

	*pResult = 0;
	lpacii = (LPACITEMINFO)pNotifyStruct;
	pDC = lpacii->pDC;

	ncol = lpacii->nColumn;
	nrow = lpacii->nRow;

	SfxCopyImage(pDC, 0, 0, SPLASH_SIZE, SPLASH_SIZE, m_pSplashImage, ncol*SPLASH_SIZE, nrow*SPLASH_SIZE);
	return;
}

//-------------------------------------------------------------------------//
// Notification message from an CTabCtrl for item selection (TCN_SELCHANGE)//
//-------------------------------------------------------------------------//
void CMainFrame::OnTabSelItem(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	int				nTabItem;

	*pResult = 0;
	nTabItem = m_pTabCtrl->GetCurSel();
	m_pACtrlVect[m_nTabSel]->Activate(FALSE);

	m_nTabSel = nTabItem;
	if( m_pACtrlVect[m_nTabSel] == NULL ) BuildControl(nTabItem);
	else m_pACtrlVect[m_nTabSel]->Activate(TRUE);
	return;
}

//-------------------------------------------------------------------------//
// Notification message from an CArrayCtrl for drawing item (ACN_DRAWITEM) //
//-------------------------------------------------------------------------//
void CMainFrame::OnNotifyDrawColor(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result)
{
	LPACITEMINFO	lpacii;
	CDC*			pDC;
	CClrInfo*		pClrInfo;
	int				nW, nH;
	CRect			rcRect;
	CBrush			Brush;

	*result = 0;
	lpacii = (LPACITEMINFO)pNotifyStruct;
	pDC = lpacii->pDC;
	nW = lpacii->nWidth;
	nH = lpacii->nHeight;
	rcRect.SetRect(0, 0, nW, nH);
	pClrInfo = (CClrInfo*)(lpacii->dwParam);
	Brush.CreateSolidBrush(pClrInfo->GetRGBColor());
	pDC->FillRect(&rcRect, &Brush);
	
	if( lpacii->dwState & ACIS_SELECTED ) 
		::DrawIconEx(pDC->GetSafeHdc(), (nW-16)/2, (nH-16)/2, hSmile, 0, 0, 0, NULL, DI_NORMAL);

	return;
}

//-------------------------------------------------------------------------//
// Tooltip notification message for obtaining text (ACN_NEEDTIPTEXT)       //
//-------------------------------------------------------------------------//
void CMainFrame::OnNotifyGetInfo(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result)
{
	CClrInfo*		pClrInfo;
	LPACTOOLTIPINFO	lpactti;
	DWORD			dwRGB, dwHSB;
	TCHAR			szBuffer[MAX_PATH];

	*result = 0;
	lpactti = (LPACTOOLTIPINFO)pNotifyStruct;
	pClrInfo = (CClrInfo*)(lpactti->dwParam);
	dwRGB = pClrInfo->GetRGBColor();
	dwHSB = pClrInfo->GetHSBColor();
	::SfxGetColorInfo(dwRGB, dwHSB, TPTR(szBuffer), _T("  "));
	lstrcpy(lpactti->lpszTipText, (LPCTSTR)szBuffer);
}

//-------------------------------------------------------------------------//
// Destroy window message                                                  //
//-------------------------------------------------------------------------//
void CMainFrame::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	if( m_pNullImage ) delete m_pNullImage;
	if( m_pBrush ) delete m_pBrush;
	delete m_pFont;
	m_CtrlMenu.DestroyMenu();
	m_ItemMenu.DestroyMenu();
}

//-------------------------------------------------------------------------//
// Change the control's objects values                                     //
//-------------------------------------------------------------------------//
void CMainFrame::OnChangeSize() 
{
	CSizeDlg	dlg;
	int			witem, hitem, nChanged, nCtrlId;

	if( dlg.DoModal() != IDOK ) return;

	nChanged = 0;							// no changes
	witem = m_pActCtrl->GetItemWidth();		// current item size
	hitem = m_pActCtrl->GetItemHeight();	// ...
	if( witem != dlg.m_witem )
	{
		witem = dlg.m_witem;
		nChanged = 1;
	}
	if( hitem != dlg.m_hitem )
	{
		hitem = dlg.m_hitem;
		nChanged = 1;
	}

	nCtrlId = m_pActCtrl->GetCtrlId();
	if( (nCtrlId == ID_AYCTRL1) || (nCtrlId == ID_AYCTRL2) )
	{
		if( nChanged )
		{
			// width or height or both are changed
			BeginWaitCursor();
			RebuildThumb(witem, hitem);
			EndWaitCursor();
			m_pActCtrl->SetItemSize(witem, hitem);
		}
		nChanged = 0;
		if( dlg.m_dimcheck ) nChanged = (dlg.m_dimcheck==IDC_RADIO1? ACDT_COLUMNS: ACDT_ROWS); 
		if( nChanged == 0 ) m_pActCtrl->SetDimension(dlg.m_fixval);
		else m_pActCtrl->SetDimension(dlg.m_fixval, nChanged);
		return; 
	}
	if( (nCtrlId >= ID_AYCTRL4) || (nCtrlId <= ID_AYCTRL4UP) )
	{
		if( nChanged ) ReflectChange(witem, hitem);
		return; 
	}

}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame service methods

//-------------------------------------------------------------------------//
// View the image in a separate window                                     //
//-------------------------------------------------------------------------//
void CMainFrame::ViewImage(LPCTSTR lpszImageName)
{
	CShowWnd	*pWndShow;
	CBitmap*	pImage;
	BITMAP		bm;
	CRect		rc;

	pImage = ::SfxLoadImage(lpszImageName);
	if( pImage == NULL ) return;
	pImage->GetObject(sizeof(bm), (LPVOID)&bm);

	::SfxRandAdjustWindow(&rc, bm.bmWidth, bm.bmHeight, WS_CAPTION | WS_BORDER, FALSE);
	pWndShow = new CShowWnd;
	pWndShow->CreateEx(0, m_pShowClass, lpszImageName, 
						WS_POPUP | WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX | WS_SYSMENU, 
						(const RECT&)rc, this, 0, (LPVOID)pImage);
	pWndShow->ShowWindow(SW_SHOW);
	pWndShow->UpdateWindow();
}

//-------------------------------------------------------------------------//
// View the color in a separate window                                     //
//-------------------------------------------------------------------------//
void CMainFrame::ViewColor(CClrInfo* pClrInfo)
{
	CColorWnd	*pWndClr;
	CRect		rc;

	::SfxRandAdjustWindow(&rc, 320, 180, WS_CAPTION | WS_BORDER, FALSE);

	pWndClr = new CColorWnd;
	pWndClr->CreateEx(0, m_pShowClass, _T("Test on contrasting color"), 
						WS_POPUP | WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX | WS_SYSMENU, 
						(const RECT&)rc, this, 0, (LPVOID)pClrInfo);
	pWndClr->ShowWindow(SW_SHOW);
	pWndClr->UpdateWindow();
	SetFocus();
}

//-------------------------------------------------------------------------//
// Method to run the folder selection dialog                               //
//-------------------------------------------------------------------------//
void CMainFrame::OnCtrlDir()
{
	IMalloc			*pMalloc = NULL;
	HRESULT			hr;
	LPITEMIDLIST	pidlroot, pidlsel;
	BROWSEINFO		bi;
	LPTSTR			lpszPath;
	TCHAR			szFolder[MAX_PATH], szDir[MAX_PATH];

    ::SHGetMalloc(&pMalloc);
	pidlroot = NULL;
	hr = ::SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidlroot);
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pidlRoot = pidlroot;
	bi.pszDisplayName = TPTR(szFolder);
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lParam = (LPARAM)NULL;
	bi.lpszTitle = _T("Choose a folder. Then click OK button.");
	bi.lpfn = (BFFCALLBACK)&BrowseCallbackProc;
	pidlsel = ::SHBrowseForFolder(&bi);
	if( pidlroot )
	{
		pMalloc->Free(pidlroot);
		pMalloc->Release();
	}
	if( pidlsel == NULL ) return;
	::SHGetPathFromIDList((LPITEMIDLIST)pidlsel, TPTR(szDir));
	lpszPath = (LPTSTR)(m_pActCtrl->GetCtrlData());
	lstrcpy(lpszPath, CTPTR(szDir));
	BeginWaitCursor();
	BuildFileList(lpszPath);
	EndWaitCursor();
}

// Callback function for folder browse
int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg, LPARAM lp, LPARAM pData)
{
	CMainFrame*	pMain = (CMainFrame*)AfxGetMainWnd();
	TCHAR		szDir[MAX_PATH];

	switch( uMsg)
	{
	case BFFM_INITIALIZED:
		lstrcpy(TPTR(szDir), (LPCTSTR)(pMain->m_pActCtrl->GetCtrlData()));
		if( szDir[0] == 0 ) break;
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)szDir);
		break;
	case BFFM_SELCHANGED:
		if( ::SHGetPathFromIDList((LPITEMIDLIST)lp , TPTR(szDir)) )
				::SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)szDir);
		break;
	default:
		break;
	}
	return 0;
}

//-------------------------------------------------------------------------//
// Build the objects file list                                             //
//-------------------------------------------------------------------------//
void CMainFrame::BuildFileList(LPCTSTR lpszPath)
{
	HANDLE			hSearch; 
	CObjInfo*		pObjInfo;
	int				nFinished;
	DWORD			format;
	LPCTSTR			lpszFile;
	WIN32_FIND_DATA	wfd;
	CString			sSearch;


	m_pActCtrl->SetRedraw(FALSE);
	if( m_pActCtrl->GetItemCount() ) m_pActCtrl->RemoveAllItems();
	sSearch.Format(SEARCH_FORMAT, (LPCSTR)lpszPath);
	hSearch = ::FindFirstFile((LPCTSTR)sSearch, &wfd); 
	if( hSearch == INVALID_HANDLE_VALUE )
	{
		m_pActCtrl->SetRedraw(TRUE);
		return;
	}
	nFinished = 0;
	while( !nFinished )
	{
		if( wfd.cFileName[0] != '.' )
		{
			lpszFile = CTPTR(wfd.cFileName);
			if( (format = SfxGetFormat(lpszFile)) != OBJECT_FORMAT_UNKNOWN )
			{
				pObjInfo = BuildThumb(lpszPath, lpszFile, format);
				m_pActCtrl->AddItem((LPARAM)pObjInfo);
			}
		}
		if( !::FindNextFile(hSearch, &wfd) ) 
		{
			if( ::GetLastError() == ERROR_NO_MORE_FILES ) nFinished = 1; 
        } 
    }
	::FindClose(hSearch);
	m_pActCtrl->SetRedraw(TRUE);
	return;
}

//-------------------------------------------------------------------------//
// Build the images thumbnail                                              //
//-------------------------------------------------------------------------//
CObjInfo* CMainFrame::BuildThumb(LPCTSTR lpszPath, LPCTSTR lpszFile, DWORD dwFormat)
{
	CDC			*pDC;
	CObjInfo*	pObjInfo;
	CBitmap*	pThumb;
	CBitmap*	pImage;
	HICON		hIcon;
	DWORD		dwSize;
	int			nWidth, nHeight;
	CString		sName;
	TCHAR		szBuffer[TXT_SIZE];

	sName.Format(NAME_FORMAT, lpszPath, lpszFile);
	nWidth = m_pActCtrl->GetItemWidth();
	nHeight = m_pActCtrl->GetItemHeight();
	pDC = GetDC();

	switch( dwFormat & OBJECT_FORMAT_MASK )
	{
	case OBJECT_FORMAT_TXT:
		dwSize = SfxGetTextFile((LPCTSTR)sName, TPTR(szBuffer), TXT_SIZE-1);
		szBuffer[dwSize] = NIL;
		if( !dwSize ) dwFormat = OBJECT_FORMAT_UNKNOWN;
		pObjInfo = new CObjInfo(lpszFile, dwFormat, CTPTR(szBuffer));
		break;
	case OBJECT_FORMAT_ICO:
		hIcon = (HICON)::LoadImage(NULL, (LPCTSTR)sName, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
		if( !hIcon ) dwFormat = OBJECT_FORMAT_UNKNOWN;
		pObjInfo = new CObjInfo(lpszFile, dwFormat, hIcon);
		break;
	case OBJECT_FORMAT_IMG:
		pImage = ::SfxLoadImage((LPCTSTR)sName);
		pThumb = NULL;
		if( pImage )
		{
			pThumb = SfxCreateThumb(pDC, pImage, nWidth - W_FRAME, nHeight - H_FRAME);
			::DeleteObject(pImage->Detach());
			delete pImage;
		}
		else dwFormat = OBJECT_FORMAT_UNKNOWN;
		pObjInfo = new CObjInfo(lpszFile, dwFormat, pThumb);
		break;
	}
	ReleaseDC(pDC);
	return pObjInfo;
}

//-------------------------------------------------------------------------//
// Rebuild the images thumbnail due to resize item                         //
//-------------------------------------------------------------------------//
void CMainFrame::RebuildThumb(int nWidth, int nHeight)
{
	CDC			*pDC;
	CObjInfo*	pObjInfo;
	CBitmap*	pThumb;
	CBitmap*	pImage;
	int			i, nItems;
	LPCTSTR		lpszPath;
	CString		sName;

	m_pActCtrl->SetRedraw(FALSE);
	nItems = m_pActCtrl->GetItemCount();
	pDC = GetDC();

	for(i=0; i<nItems; i++)
	{
		pObjInfo = (CObjInfo*)(m_pActCtrl->GetItemData(i));
		switch( pObjInfo->GetFormat() )
		{
		case OBJECT_FORMAT_TXT:
		case OBJECT_FORMAT_ICO:
			break;
		default:
			lpszPath = (LPCTSTR)(m_pActCtrl->GetCtrlData());
			sName.Format(NAME_FORMAT, (LPCTSTR)lpszPath, (LPCTSTR)pObjInfo->GetName());
			pImage = ::SfxLoadImage((LPCTSTR)sName);
			pThumb = NULL;
			if( pImage )
			{
				pThumb = SfxCreateThumb(pDC, pImage, nWidth - W_FRAME, nHeight - H_FRAME);
				delete pImage;
			}
			pObjInfo->SetBitmap(pThumb);
			break;
		}
	}
	ReleaseDC(pDC);
	m_pActCtrl->SetRedraw(TRUE);
}

//-------------------------------------------------------------------------//
// Splash image to array control 3                                          //
//-------------------------------------------------------------------------//
void CMainFrame::SplashToControl(LPCTSTR lpszImageName)
{
	int			bw, bh, nitems, ncol, nrow;
	BITMAP		bm;

	// delete previous splashed image, if any
	if( m_pSplashImage )
	{
		::DeleteObject(m_pSplashImage->Detach());
		delete m_pSplashImage;
	}

	// load new one
	m_pSplashImage = ::SfxLoadImage(lpszImageName);
	if( m_pSplashImage == NULL ) return;
	// compute items, columns and rows
	m_pSplashImage->GetObject(sizeof(bm), (LPVOID)&bm);
	bw = bm.bmWidth;
	bh = bm.bmHeight;
	ncol = bw/SPLASH_SIZE + (bw%SPLASH_SIZE? 1: 0);
	nrow = bh/SPLASH_SIZE + (bh%SPLASH_SIZE? 1: 0);
	nitems = ncol * nrow;

	m_pACtrl3->SetRedraw(FALSE);
	m_pACtrl3->SetItemCount(nitems);
	m_pACtrl3->SetColumns(ncol);
	m_pACtrl3->SetRedraw(TRUE);
}

//-------------------------------------------------------------------------//
// Build an Array control for Tab Control Item                             //
//-------------------------------------------------------------------------//
void CMainFrame::BuildControl(int nId)
{
	CArrayCtrl*		pACtrl;
	CClrInfo*		pClrObj;
	CRect			rClient;
	CSize			sItem;
	COLORREF		crHSB, crRGB, crBack, crGrid;
	int				nHue, nSat, nBri;

	m_pTabCtrl->GetClientRect(&rClient);
	m_pTabCtrl->AdjustRect(FALSE, &rClient);
	if( nId == 0 )
	{
		// if this is first control, set the defaults
		sItem = CSize(24,24);
		crBack = crGrid = RGB(255,255,255);
	}
	else
	{
		// otherwise get the settings from first control created 
		m_pACtrlVect[0]->GetItemSize(&sItem);
		crBack = m_pACtrlVect[0]->GetBkColor();
		crGrid = m_pACtrlVect[0]->GetGridColor();
	}
	pACtrl = new CArrayCtrl;
	if( !pACtrl->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ACS_GRIDLINES | ACS_BALLOONTIP | ACS_CLIENTEDGE | ACS_USERDATA, 
								rClient, m_pTabCtrl, ID_AYCTRL4+nId, sItem) ) return;

	pACtrl->SetTipColor(RGB(192,192,192), RGB(0,0,0));
	pACtrl->SetBkColor(crBack);
	pACtrl->SetGridColor(crGrid);
	pACtrl->SetColumns(10);
	m_pACtrlVect[nId] = pACtrl;

	pACtrl->SetRedraw(FALSE);
	nBri = (100 - nId*10);
	for(nHue=0; nHue<240; nHue += 10)
	{
		for(nSat=100; nSat>0; nSat -=10)
		{
			crHSB = HSB(nHue,nSat,nBri);
			crRGB = ::SfxColorHSBtoRGB(crHSB);
			pClrObj = new CClrInfo(crRGB, crHSB);
			pACtrl->AddItem((LPARAM)pClrObj);
		}
	}
	pACtrl->SetRedraw(TRUE);

}

//-------------------------------------------------------------------------//
// Reflect to all controls the parent window resizing                      //
//-------------------------------------------------------------------------//
void CMainFrame::ReflectChange(CRect* pRect)
{
	CArrayCtrl*		pACtrl;
	int				i;

	for(i=0; i<TAB_ITEMS; i++)
	{
		pACtrl = m_pACtrlVect[i];
		if( pACtrl ) pACtrl->MoveWindow(pRect, (m_nTabSel == i? TRUE: FALSE));
	}
}

//-------------------------------------------------------------------------//
// Reflect to all controls the change of background color                  //
//-------------------------------------------------------------------------//
void CMainFrame::ReflectChange(int nOper, COLORREF crColor)
{
	CArrayCtrl*		pACtrl;
	int				i;

	for(i=0; i<TAB_ITEMS; i++)
	{
		pACtrl = m_pACtrlVect[i];
		if( pACtrl == NULL ) continue;
		if( nOper == 0 ) pACtrl->SetBkColor(crColor);
		else pACtrl->SetGridColor(crColor);
	}
}

//-------------------------------------------------------------------------//
// Reflect to all controls the change of item size                         //
//-------------------------------------------------------------------------//
void CMainFrame::ReflectChange(int nW, int nH)
{
	CArrayCtrl*		pACtrl;
	int				i;

	for(i=0; i<TAB_ITEMS; i++)
	{
		pACtrl = m_pACtrlVect[i];
		if( pACtrl ) pACtrl->SetItemSize(nW,nH);
	}
}
