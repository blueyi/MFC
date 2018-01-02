// mybar.cpp : implementation file
//

#include "stdafx.h"
#include "mybar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBar

CMyBar::CMyBar()
{
}

CMyBar::~CMyBar()
{
}


BEGIN_MESSAGE_MAP(CMyBar, CSizingControlBar)
    //{{AFX_MSG_MAP(CMyBar)
    ON_WM_CREATE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyBar message handlers


int CMyBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndButton.Create("Paste", WS_CHILD | WS_VISIBLE, CRect(0,0,0,0),
        this, ID_EDIT_PASTE))
        return -1;

    // older versions of Windows* (NT 3.51 for instance)
    // fail with DEFAULT_GUI_FONT
    if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
        if (!m_font.CreatePointFont(80, "MS Sans Serif"))
            return -1;

    m_wndButton.SetFont(&m_font);

    return 0;
}

void CMyBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

void CMyBar::OnSize(UINT nType, int cx, int cy) 
{
    CSizingControlBar::OnSize(nType, cx, cy);
    
    // TODO: Add your message handler code here
    CRect rc;
    GetClientRect(rc);

    rc.DeflateRect(4, 4);

    m_wndButton.MoveWindow(rc);
}
