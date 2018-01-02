////////////////////////////////////////////////////////////////
// CCoolBar 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// CCoolBar implements coolbars for MFC.
//
#include "StdAfx.h"
#include "CoolBar.h"
#include "CJToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCoolBar, CControlBar)

BEGIN_MESSAGE_MAP(CCoolBar, CControlBar)
	//{{AFX_MSG_MAP(CCoolBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(RBN_HEIGHTCHANGE, OnHeigtChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCoolBar::CCoolBar()
{
}

CCoolBar::~CCoolBar()
{
}

//////////////////
// Create coolbar
//
BOOL CCoolBar::Create(CWnd* pParentWnd, DWORD dwStyle,
	DWORD dwAfxBarStyle, UINT nID)
{
	ASSERT_VALID(pParentWnd);   // must have a parent

	// dynamic coolbar not supported
	dwStyle &= ~CBRS_SIZE_DYNAMIC;

	// save the style (this code copied from MFC--probably unecessary)
	m_dwStyle = dwAfxBarStyle;
	if (nID == AFX_IDW_TOOLBAR)
		m_dwStyle |= CBRS_HIDE_INPLACE;

	// MFC requires these:
	dwStyle |= CCS_NODIVIDER|CCS_NOPARENTALIGN;

	// Initialize cool common controls
	static BOOL bInit = FALSE;
	if (!bInit) {
		INITCOMMONCONTROLSEX sex;
		sex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		sex.dwICC = ICC_COOL_CLASSES;
		InitCommonControlsEx(&sex);
		bInit = TRUE;
	}

	// Create the cool bar using style and parent.
	CRect rc;
	rc.SetRectEmpty();
	return CWnd::CreateEx(WS_EX_TOOLWINDOW, REBARCLASSNAME, NULL,
		dwStyle, rc, pParentWnd, nID);
}

//////////////////
// Handle WM_CREATE. Call virtual fn so derived class can create bands.
//
int CCoolBar::OnCreate(LPCREATESTRUCT lpcs)
{
	return CControlBar::OnCreate(lpcs) == -1 ? -1
		: OnCreateBands();	// call pure virtual fn to create bands
}

//////////////////
// Standard UI handler updates any controls in the coolbar.
//
void CCoolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

/////////////////
// These two functions are called by MFC to calculate the layout of
// the main frame. Since CCoolBar is not designed to be dynamic, the
// size is always fixed, and the same as the window size. 
//
CSize CCoolBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZ);
}

CSize CCoolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CRect rc;
	GetWindowRect(&rc);
	CSize sz(bHorz && bStretch ? 0x7FFF : rc.Width(),
		!bHorz && bStretch ? 0x7FFF : rc.Height());
	return sz;
}

//////////////////
// Low-level height-changed handler just passes to virtual fn w/nicer args.
//
void CCoolBar::OnHeigtChange(NMHDR* pNMHDR, LRESULT* pRes)
{
	CRect rc;
	GetWindowRect(&rc);
	OnHeightChange(rc);
	*pRes = 0; // why not?
}

//////////////////
// Height changed:
// Notify the parent frame by posting a WM_SIZE message. This will cause the
// frame to do RecalcLayout. The message must be posted, not sent, because
// the coolbar could send RBN_HEIGHTCHANGE while the user is sizing, which
// would be in the middle of a CFrame::RecalcLayout, and RecalcLayout doesn't
// let you re-enter it. Posting gurantees that CFrameWnd can finish any recalc
// it may be in the middle of before handling my posted WM_SIZE. Very confusing.
//
void CCoolBar::OnHeightChange(const CRect& rcNew)
{
	CWnd* pParent = GetParent();
	CRect rc;
	pParent->GetWindowRect(&rc);
	pParent->PostMessage(WM_SIZE, 0, MAKELONG(rc.Width(),rc.Height()));
}

void CCoolBar::OnPaint()
{
	Default();	// bypass CControlBar
}

BOOL CCoolBar::OnEraseBkgnd(CDC* pDC)
{
	return (BOOL)Default();  // bypass CControlBar
}

