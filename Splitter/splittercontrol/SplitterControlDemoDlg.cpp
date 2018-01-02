// SplitterControlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SplitterControlDemo.h"
#include "SplitterControlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterControlDemoDlg dialog

CSplitterControlDemoDlg::CSplitterControlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSplitterControlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSplitterControlDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSplitterControlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplitterControlDemoDlg)
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_EDIT_HELP, m_edHelp);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_stTitle);
	DDX_Control(pDX, IDC_EDIT, m_txtContent);
	DDX_Control(pDX, IDC_LIST, m_lstItem);
	DDX_Control(pDX, IDC_TREE, m_wndType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSplitterControlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSplitterControlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
    ON_WM_SIZE()
    ON_NOTIFY(SPN_MAXMINPOS, IDC_SPLITTER2, OnMaxMinInfo)
    ON_NOTIFY(SPN_MAXMINPOS, IDC_SPLITTER1, OnMaxMinInfo)
    ON_NOTIFY(SPN_DELTA,     IDC_SPLITTER1, OnSplitter1Delta)
    ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
    ON_WM_NCHITTEST()
    ON_WM_LBUTTONDOWN()
    ON_WM_SIZING()
    ON_WM_SETCURSOR()
    ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterControlDemoDlg message handlers

BOOL CSplitterControlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CRect rc;
	CWnd* pWnd;

	pWnd = GetDlgItem(IDC_SPLITTER1);
	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);
	BOOL bRet = m_wndSplitter1.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_SPLITTER1, SPS_VERTICAL|SPS_DELTA_NOTIFY);//, RGB(255, 0, 0));
    if (FALSE == bRet)
    {
        AfxMessageBox("m_wndSplitter1 create failed");
    }

	pWnd = GetDlgItem(IDC_SPLITTER2);
	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);
	bRet = m_wndSplitter2.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_SPLITTER2, SPS_HORIZONTAL, RGB(0, 0, 255));
    if (FALSE == bRet)
    {
        AfxMessageBox("m_wndSplitter2 create failed");
    }

	InitSampleData();

    this->m_wndSplitter1.RegisterLinkedWindow(SPLS_LINKED_LEFT,     GetDlgItem(IDC_TREE));
    this->m_wndSplitter1.RegisterLinkedWindow(SPLS_LINKED_RIGHT,    GetDlgItem(IDC_LIST));
    this->m_wndSplitter1.RegisterLinkedWindow(SPLS_LINKED_RIGHT,    GetDlgItem(IDC_EDIT));
    this->m_wndSplitter1.RegisterLinkedWindow(SPLS_LINKED_RIGHT,    &m_wndSplitter2);

    this->m_wndSplitter2.RegisterLinkedWindow(SPLS_LINKED_UP,       GetDlgItem(IDC_LIST));
    this->m_wndSplitter2.RegisterLinkedWindow(SPLS_LINKED_DOWN,     GetDlgItem(IDC_EDIT));

    //  relayout the splotter to make them good look
    this->m_wndSplitter1.Relayout();
    this->m_wndSplitter2.Relayout();

    this->Resize();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSplitterControlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CSplitterControlDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSplitterControlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CSplitterControlDemoDlg::InitSampleData()
{
	m_wndType.ModifyStyle(0, TVS_LINESATROOT | TVS_HASBUTTONS
		| TVS_SHOWSELALWAYS | TVS_HASLINES );
	HTREEITEM hRoot = m_wndType.InsertItem("Local folder");
	HTREEITEM h1 = m_wndType.InsertItem("Inbox", hRoot);
	HTREEITEM h2 = m_wndType.InsertItem("Outbox", hRoot);
	HTREEITEM h3 = m_wndType.InsertItem("Send Items", hRoot);
	m_wndType.SetItemData(hRoot, 0);
	m_wndType.SetItemData(h1, 1);
	m_wndType.SetItemData(h2, 2);
	m_wndType.SetItemData(h3, 3);

	m_lstItem.ModifyStyle(0, LVS_REPORT);
	m_lstItem.InsertColumn(0, "From", LVCFMT_LEFT, 100);
	m_lstItem.InsertColumn(1, "Subject", LVCFMT_LEFT, 100);

    m_edHelp.SetWindowText("Yes, I'm the help edit.");
}

void CSplitterControlDemoDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	HTREEITEM h = m_wndType.GetSelectedItem();
	DWORD nID = m_wndType.GetItemData(h);

	m_lstItem.DeleteAllItems();
	m_lstItem.DeleteColumn(1);
	m_lstItem.DeleteColumn(0);
	
	switch(nID)
	{
		case 0:break;
		case 1:
			m_lstItem.InsertColumn(0, "From", LVCFMT_LEFT, 100);
			m_lstItem.InsertColumn(1, "Subject", LVCFMT_LEFT, 200);
			m_lstItem.InsertItem(0, "Dad");
			m_lstItem.SetItemText(0, 1, "Dad's letter");
			m_lstItem.SetItemData(0, 0);

			m_lstItem.InsertItem(1, "AnhPhong");
			m_lstItem.SetItemText(1, 1, "Hi, how are you ?");
			m_lstItem.SetItemData(1, 1);

			m_lstItem.InsertItem(2, "TrungHau");
			m_lstItem.SetItemText(2, 1, "Reply to Hi");
			m_lstItem.SetItemData(2, 2);
			break;
		case 2:
			m_lstItem.InsertColumn(0, "Subject", LVCFMT_LEFT, 200);
			m_lstItem.InsertColumn(1, "Recipcent", LVCFMT_LEFT, 100);
			m_lstItem.InsertItem(0, "Reply to Dad's letter");
			m_lstItem.SetItemData(0, 100);

			m_lstItem.SetItemText(0, 1, "Dad");
			m_lstItem.InsertItem(1, "I'm fine, and you !");
			m_lstItem.SetItemText(1, 1, "AnhPhong");
			m_lstItem.SetItemData(1, 101);
			break;
		case 3:
			m_lstItem.InsertColumn(0, "From", LVCFMT_LEFT, 100);
			m_lstItem.InsertColumn(1, "Subject", LVCFMT_LEFT, 200);
			m_lstItem.InsertItem(0, "TrungHau");
			m_lstItem.SetItemText(0, 1, "Hi");
			m_lstItem.SetItemData(0, 200);
			break;
	}
}

void CSplitterControlDemoDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	
	CString strContent = "";
	POSITION pos = m_lstItem.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_lstItem.GetNextSelectedItem(pos);
		int n = m_lstItem.GetItemData(nCurSel);
		switch(n)
		{
			case 0: strContent =	"content of Dad's letter";
				break;
			case 1: strContent = "content of Hi, how are you ?";
				break;
			case 2: strContent = "content of Reply to Hi ";
				break;
			
			case 100 : strContent = "content of Reply to Dad's letter";
				break;
			case 101: strContent = "content of I'm fine, and you !";
				break;

			case 200: strContent = "content of Hi";
				break;

		}
	}
	m_txtContent.SetWindowText(strContent);
}

void CSplitterControlDemoDlg::OnSize(UINT nType, int cx, int cy)
{
    this->Resize();
}

void CSplitterControlDemoDlg::MoveDlgItem(int nID, const CRect& rcPos, BOOL bRepaint)
{
    CWnd* pWnd = this->GetDlgItem(nID);
    if (NULL == pWnd)
    {
        return;
    }

    pWnd->MoveWindow(rcPos, bRepaint);

    CRect rcsp;
    m_wndSplitter2.GetWindowRect(rcsp);
    this->ScreenToClient(rcsp);
}

void CSplitterControlDemoDlg::Resize()
{
    CRect rcDlg;
    this->GetClientRect(rcDlg);
    
    CRect rcTitle;
    rcTitle.left    = rcDlg.left    + STD_GAP;
    rcTitle.right   = rcDlg.right   - STD_GAP;
    rcTitle.top     = rcDlg.top     + STD_GAP;
    rcTitle.bottom  = rcTitle.top   + STD_BUTTON_HEIGHT;
    this->MoveDlgItem(IDC_STATIC_TITLE, rcTitle, TRUE);

    CRect rcOK;
    rcOK.right      = rcTitle.right;
    rcOK.bottom     = rcDlg.bottom  - STD_GAP;
    rcOK.top        = rcOK.bottom   - STD_BUTTON_HEIGHT;
    rcOK.left       = rcOK.right    - STD_BUTTON_WIDTH;
    this->MoveDlgItem(IDOK, rcOK, TRUE);

    CRect rcCancel;
    rcCancel.right  = rcOK.left     - STD_GAP;
    rcCancel.left   = rcCancel.right- STD_BUTTON_WIDTH;
    rcCancel.top    = rcOK.top;
    rcCancel.bottom = rcOK.bottom;
    this->MoveDlgItem(IDCANCEL, rcCancel, TRUE);

    
    if (FALSE == IsWindow(m_wndSplitter1.GetSafeHwnd()))
    {
        return;
    }

    CRect rcSplit1;
    m_wndSplitter1.GetWindowRect(rcSplit1);
    this->ScreenToClient(rcSplit1);
    rcSplit1.bottom = rcOK.top - STD_GAP;
    this->m_wndSplitter1.MoveWindow(rcSplit1, TRUE);
    
    CRect rcSplit2;
    m_wndSplitter2.GetWindowRect(rcSplit2);
    this->ScreenToClient(rcSplit2);
    rcSplit2.right = rcOK.right;
    this->m_wndSplitter2.MoveWindow(rcSplit2, TRUE);

    CRect rcTree;
    LONG lTreeWidth = rcTree.Width();
    rcTree.left     = rcTitle.left;
    rcTree.right    = rcSplit1.left;
    rcTree.top      = rcTitle.bottom + STD_GAP;
    rcTree.bottom   = rcOK.top - STD_GAP;
    this->MoveDlgItem(IDC_TREE, rcTree, TRUE);

    CRect rcList;
    rcList.top      = rcTree.top;
    rcList.bottom   = rcSplit2.top;
    rcList.left     = rcSplit1.right;
    rcList.right    = rcOK.right;
    this->MoveDlgItem(IDC_LIST, rcList, TRUE);

    CRect rcEdit;
    rcEdit.left     = rcList.left;
    rcEdit.right    = rcList.right;
    rcEdit.top      = rcSplit2.bottom;
    rcEdit.bottom   = rcOK.top - STD_GAP;
    this->MoveDlgItem(IDC_EDIT, rcEdit, TRUE);

    CRect rcHelp;
    rcHelp.left     = rcTree.left;
    rcHelp.right    = rcTree.right;
    rcHelp.top      = rcOK.top;
    rcHelp.bottom   = rcOK.bottom;       
    this->MoveDlgItem(IDC_EDIT_HELP, rcHelp, TRUE);
}

void CSplitterControlDemoDlg::OnMaxMinInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
    //  Get current pos of the child controls
    CRect rcTree;
    CRect rcList;
    CRect rcEdit;
    CRect rcCancel;
    m_wndType.GetWindowRect(rcTree);
    m_lstItem.GetWindowRect(rcList);
    m_txtContent.GetWindowRect(rcEdit);
    m_btnCancel.GetWindowRect(rcCancel);
    
    this->ScreenToClient(rcTree);
    this->ScreenToClient(rcList);
    this->ScreenToClient(rcEdit);
    this->ScreenToClient(rcCancel);
    
    //  return the pos limit
    SPC_NM_MAXMINPOS* pNewMaxMinPos = (SPC_NM_MAXMINPOS*)pNMHDR;
    if (IDC_SPLITTER1 == pNMHDR->idFrom)
    {
        pNewMaxMinPos->lMin = rcTree.left + 50;
        pNewMaxMinPos->lMax = rcCancel.left - STD_GAP;
    }
    else
    {
        pNewMaxMinPos->lMin = rcList.top + 50;
        pNewMaxMinPos->lMax = rcEdit.bottom - 50;
    }
}

void CSplitterControlDemoDlg::OnSplitter1Delta(NMHDR* pNMHDR, LRESULT* pResult)
{
    //  this function just want to show you how to use the delta event
    *pResult = 0;

    SPC_NM_DELTA* pDelta = (SPC_NM_DELTA*)pNMHDR;
    if (NULL == pDelta)
    {
        return;
    }

    m_wndSplitter1.ChangePos(&m_edHelp, SPLS_LINKED_LEFT, pDelta->lDelta);
}

LRESULT mMouseStates = 0;
LRESULT CSplitterControlDemoDlg::OnNcHitTest(CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CRect rect;
    GetWindowRect(&rect);
    if(point.x <= rect.left+3)
        return (mMouseStates=HTLEFT);
    else if(point.x >= rect.right-3)
        return (mMouseStates=HTRIGHT);
    else if(point.y <= rect.top+3)
        return (mMouseStates=HTTOP);
    else if(point.y >= rect.bottom-3)
        return (mMouseStates=HTBOTTOM);
    else if(point.x <= rect.left+10 && point.y <= rect.top+10)
        return (mMouseStates=HTTOPLEFT);
    else if(point.x >= rect.right-10 && point.y <= rect.top+10)
        return (mMouseStates=HTTOPRIGHT);
    else if(point.x <= rect.left+10 && point.y >= rect.bottom-10)
        return (mMouseStates=HTBOTTOMLEFT);
    else if(point.x >= rect.right-10 && point.y >= rect.bottom-10)
        return (mMouseStates=HTBOTTOMRIGHT);
    else
        return rect.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);  

    return CDialog::OnNcHitTest(point);
}

void CSplitterControlDemoDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    //switch(mMouseStates) 
    //{
    //case HTLEFT:
    //case HTRIGHT:
    //    ::SetCursor(LoadCursor(NULL, IDC_SIZEWE));
    //    break;
    //case HTTOP:
    //case HTBOTTOM:
    //    ::SetCursor(LoadCursor(NULL, IDC_SIZENS));
    //    break;
    //case HTTOPLEFT:
    //case HTBOTTOMRIGHT:
    //    ::SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
    //    break;
    //case HTTOPRIGHT:
    //case HTBOTTOMLEFT:
    //    ::SetCursor(LoadCursor(NULL, IDC_SIZENESW));
    //    break;
    //default:
    //    ::SetCursor(LoadCursor(NULL, IDC_ARROW));
    //    break;
    //}

    //if (mMouseStates == HTTOP)
    //    PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
    //else if (mMouseStates == HTBOTTOM)
    //    PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
    //else if (mMouseStates == HTLEFT)
    //    PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
    //else if (mMouseStates == HTRIGHT)
    //    PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
    //else if (mMouseStates == HTTOPLEFT)
    //    PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
    //else if (mMouseStates == HTBOTTOMRIGHT)
    //    PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
    //else if (mMouseStates == HTTOPRIGHT)
    //    PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
    //else if (mMouseStates == HTBOTTOMLEFT)
    //    PostMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
    //else
    //{
    //    CRect rect;
    //    GetClientRect(&rect);
    //    rect.bottom = 600/*FRAME_TOP_SIZE*/;
    //    if(rect.PtInRect(point))
    //        PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
    //}

    CDialog::OnLButtonDown(nFlags, point);
}

void CSplitterControlDemoDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
    CDialog::OnSizing(fwSide, pRect);

    // TODO: Add your message handler code here
    //int mSizeX = 2;
    //int mSizeY = 2;
    //switch(fwSide) 
    //{
    //case WMSZ_LEFT:
    //    pRect->left = min(pRect->left, pRect->right - mSizeX);
    //    break;
    //case WMSZ_RIGHT:
    //    pRect->right = max(pRect->right, pRect->left + mSizeX);
    //    break;
    //case WMSZ_TOP:
    //    pRect->top = min(pRect->top, pRect->bottom - mSizeY);
    //    break;
    //case WMSZ_BOTTOM:
    //    pRect->bottom = max(pRect->bottom, pRect->top + mSizeY);
    //    break;
    //case WMSZ_TOPLEFT:
    //    pRect->left = min(pRect->left, pRect->right - mSizeX);
    //    pRect->top = min(pRect->top, pRect->bottom - mSizeY);
    //    break;
    //case WMSZ_BOTTOMRIGHT:
    //    pRect->right = max(pRect->right, pRect->left + mSizeX);
    //    pRect->bottom = max(pRect->bottom, pRect->top + mSizeY);
    //    break;
    //case WMSZ_TOPRIGHT:
    //    pRect->right = max(pRect->right, pRect->left + mSizeX);
    //    pRect->top = min(pRect->top, pRect->bottom - mSizeY);
    //    break;
    //case WMSZ_BOTTOMLEFT:
    //    pRect->bottom = max(pRect->bottom, pRect->top + mSizeY);
    //    pRect->left = min(pRect->left, pRect->right - mSizeX);
    //    break;
    //default:
    //    break;
    //}    
}

BOOL CSplitterControlDemoDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    // TODO: Add your message handler code here and/or call default
    if(nHitTest == HTCAPTION || nHitTest == HTSYSMENU ||
        nHitTest == HTMENU || nHitTest == HTCLIENT)
    {
        SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
    }
    else if(nHitTest == HTTOP || nHitTest == HTBOTTOM)
    {
        SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
    }
    else if(nHitTest == HTLEFT || nHitTest == HTRIGHT)
    {
        SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
    }
    else if(nHitTest == HTTOPLEFT || nHitTest == HTBOTTOMRIGHT)
    {
        SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
    }
    else if(nHitTest == HTTOPRIGHT || nHitTest == HTBOTTOMLEFT)
    {
        SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
    }
    else
    {
        SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
    }

    return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CSplitterControlDemoDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if(nHitTest == HTTOP)
        SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
    else if(nHitTest == HTBOTTOM)
        SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
    else if(nHitTest == HTLEFT)
        SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
    else if(nHitTest == HTRIGHT)
        SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
    else if(nHitTest == HTTOPLEFT)
        SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
    else if(nHitTest == HTTOPRIGHT)
        SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
    else if(nHitTest == HTBOTTOMLEFT)
        SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
    else if(nHitTest == HTBOTTOMRIGHT)
        SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));

    CDialog::OnNcLButtonDown(nHitTest, point);
}

