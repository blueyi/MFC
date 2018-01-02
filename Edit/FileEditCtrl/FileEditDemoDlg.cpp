// FileEditDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileEditDemo.h"
#include "FileEditDemoDlg.h"
#include "pja_icon.h"

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
    CPJA_Icon   m_pja;
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
    DDX_Control(pDX, IDC_PJA, m_pja);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileEditDemoDlg dialog

CFileEditDemoDlg::CFileEditDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CFileEditDemoDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CFileEditDemoDlg)
    m_styles = 0;
    m_flags = 0;
	m_nicon = 0;
	//}}AFX_DATA_INIT
    pBuffer = NULL;
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFileEditDemoDlg::~CFileEditDemoDlg()
{
    if (pBuffer) delete[] pBuffer;
}

void CFileEditDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFileEditDemoDlg)
//	DDX_Control(pDX, IDC_CHECK1, m_disablebutton);
	DDX_Control(pDX, IDC_GRAY, m_gray);
	DDX_Control(pDX, IDC_FLAT, m_flat);
	DDX_Control(pDX, IDC_SPIN1, m_spin);
	DDX_Control(pDX, IDC_SETBUTTONWIDTH, m_setwidth);
	DDX_Control(pDX, IDC_EDIT3, m_butwidth);
	DDX_Control(pDX, IDC_TRANSPARENT, m_transparent);
	DDX_Control(pDX, IDC_STRETCH, m_stretch);
	DDX_Control(pDX, IDC_MY_ICON, m_icon);
	DDX_Control(pDX, IDC_IMAGE, m_image);
	DDX_Control(pDX, IDC_BITMAP, m_bitmap);
    DDX_Control(pDX, IDC_NODEREF, m_noderef);
    DDX_Control(pDX, IDC_WILD, m_wild);
    DDX_Control(pDX, IDC_VALIDATE, m_validate);
    DDX_Control(pDX, IDC_LEFT, m_left);
    DDX_Control(pDX, IDC_CHECKSETDIR, m_SetDir);
    DDX_Control(pDX, ID_DUMP, m_dump);
    DDX_Control(pDX, IDC_MULTI, m_multi);
    DDX_Control(pDX, IDC_FOLD, m_fold);
    DDX_Control(pDX, IDC_DISABLE, m_disable);
    DDX_Control(pDX, IDC_STATIC1, m_stattext);
    DDX_Control(pDX, IDC_FILE, m_file);
    DDX_Control(pDX, IDC_EDIT2, m_editclitip);
    DDX_Control(pDX, IDC_DRAG, m_drag);
    DDX_Control(pDX, IDC_CLITIP, m_clitip);
    DDX_Control(pDX, IDC_BUTTIP, m_buttip);
    DDX_Control(pDX, IDC_BROWSE, m_browse);
    DDX_Control(pDX, IDC_ADD, m_Add);
    DDX_Radio(pDX, IDC_NORMAL, m_styles);
    DDX_Radio(pDX, IDC_FILE, m_flags);
	DDX_Radio(pDX, IDC_MY_ICON, m_nicon);
	//}}AFX_DATA_MAP
    DDX_FileEditCtrl(pDX, IDC_EDIT1, m_fileeditctrl, FEC_FILEOPEN);
    if (m_validate.GetCheck())
        DDV_FileEditCtrl(pDX, IDC_EDIT1);
}

BEGIN_MESSAGE_MAP(CFileEditDemoDlg, CDialog)
    ON_NOTIFY(FEC_NM_PREBROWSE, IDC_EDIT1, OnPreBrowse)
    ON_NOTIFY(FEC_NM_POSTBROWSE, IDC_EDIT1, OnPostBrowse)
    ON_NOTIFY(FEC_NM_DROP, IDC_EDIT1, OnDrop)
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
    //{{AFX_MSG_MAP(CFileEditDemoDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_ADD, OnAdd)
    ON_BN_CLICKED(IDC_BUTTIP, OnButtip)
    ON_BN_CLICKED(IDC_CLITIP, OnClitip)
    ON_BN_CLICKED(IDC_DISABLE, OnDisable)
    ON_BN_CLICKED(IDC_DRAG, OnDrag)
    ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
    ON_BN_CLICKED(IDC_FILE, OnFile)
    ON_BN_CLICKED(IDC_FOLD, OnFold)
    ON_BN_CLICKED(IDC_NORMAL, OnNormal)
    ON_BN_CLICKED(IDC_READ, OnRead)
    ON_BN_CLICKED(IDC_MULTI, OnMulti)
    ON_BN_CLICKED(ID_DUMP, OnDump)
    ON_BN_CLICKED(IDC_LEFT, OnLeft)
    ON_BN_CLICKED(IDC_VALIDATE, OnValidate)
    ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
    ON_BN_CLICKED(IDC_WILD, OnWild)
    ON_BN_CLICKED(IDC_NODEREF, OnNoderef)
	ON_BN_CLICKED(IDC_IMAGE, OnImage)
	ON_BN_CLICKED(IDC_BITMAP, OnBitmap)
	ON_BN_CLICKED(IDC_MY_ICON, OnMyIcon)
	ON_BN_CLICKED(IDC_STRETCH, OnStretch)
	ON_BN_CLICKED(IDC_TRANSPARENT, OnTransparent)
	ON_BN_CLICKED(IDC_SETBUTTONWIDTH, OnSetbuttonwidth)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_BN_CLICKED(IDC_FLAT, OnFlat)
	ON_BN_CLICKED(IDC_GRAY, OnGray)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileEditDemoDlg message handlers

BOOL CFileEditDemoDlg::OnInitDialog()
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
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // TODO: Add extra initialization here
    CString Caption;
    Caption.LoadString(AFX_IDS_APP_TITLE);
    SetWindowText(Caption);
    EnableToolTips();
    m_browse.SetCheck(TRUE);
    m_SetDir.SetCheck(TRUE);
    m_validate.SetCheck(TRUE);
    m_editclitip.SetWindowText(_T("Client Tooltip Text"));
    m_spin.SetRange(0, 235);
    m_butwidth.SetWindowText(_T("21"));

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileEditDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileEditDemoDlg::OnPaint() 
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
HCURSOR CFileEditDemoDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CFileEditDemoDlg::OnAdd() 
{   // add a trailing slash to the folder string
    if (m_Add.GetCheck())
        m_fileeditctrl.ModifyFlags(0, FEC_TRAILINGSLASH);
    else
        m_fileeditctrl.ModifyFlags(FEC_TRAILINGSLASH, 0);
}

void CFileEditDemoDlg::OnBitmap() 
{   // image is a bitmap
    m_transparent.EnableWindow();
    HANDLE handle = ::LoadImage(AfxGetInstanceHandle(),
                                MAKEINTRESOURCE(IDB_BITMAP1),
                                IMAGE_BITMAP,
                                0,
                                0,
                                LR_DEFAULTCOLOR);
    m_fileeditctrl.SetButtonImage(handle,  PJAI_BITMAP | PJAI_AUTODELETE | (m_stretch.GetCheck() ? PJAI_STRETCHED : 0) | (m_transparent.GetCheck() ? PJAI_TRANSPARENT : 0));
}

void CFileEditDemoDlg::OnBrowse() 
{
    if (m_browse.GetCheck())
        m_SetDir.EnableWindow(TRUE);
    else
        m_SetDir.EnableWindow(FALSE);
}

void CFileEditDemoDlg::OnButtip() 
{   // enable the button tooltip
    if (m_buttip.GetCheck())
        m_fileeditctrl.ModifyFlags(0, FEC_BUTTONTIP);
    else
        m_fileeditctrl.ModifyFlags(FEC_BUTTONTIP, 0);
}

void CFileEditDemoDlg::OnChangeEdit2() 
{   // client area tooltip text has changed
    CString text;
    m_editclitip.GetWindowText(text);
    m_fileeditctrl.SetClientTipText(text);
}

void CFileEditDemoDlg::OnClitip() 
{   // enable client area tooltip
    if (m_clitip.GetCheck())
        m_fileeditctrl.ModifyFlags(0, FEC_CLIENTTIP);
    else
        m_fileeditctrl.ModifyFlags(FEC_CLIENTTIP, 0);
}

void CFileEditDemoDlg::OnDisable() 
{   // disable control
    if (m_disable.GetCheck())
    {
        m_fileeditctrl.EnableWindow(FALSE);
        m_drag.EnableWindow(FALSE);
        m_browse.EnableWindow(FALSE);
        m_SetDir.EnableWindow(FALSE);
        m_file.EnableWindow(FALSE);
        m_multi.EnableWindow(FALSE);
        m_wild.EnableWindow(FALSE);
        m_noderef.EnableWindow(FALSE);
        m_fold.EnableWindow(FALSE);
        m_Add.EnableWindow(FALSE);
        m_buttip.EnableWindow(FALSE);
        m_clitip.EnableWindow(FALSE);
    }
    else
    {
        m_fileeditctrl.EnableWindow(TRUE);
        m_drag.EnableWindow(TRUE);
        m_browse.EnableWindow(TRUE);
        if (m_browse.GetCheck())
            m_SetDir.EnableWindow(TRUE);
        m_file.EnableWindow(TRUE);
        if (m_file.GetCheck())
        {
            m_multi.EnableWindow(TRUE);
            m_wild.EnableWindow(TRUE);
            m_noderef.EnableWindow(TRUE);
        }
        m_fold.EnableWindow(TRUE);
        if (m_fold.GetCheck())
            m_Add.EnableWindow(TRUE);
        m_buttip.EnableWindow(TRUE);
        m_clitip.EnableWindow(TRUE);
    }
}

void CFileEditDemoDlg::OnDrag() 
{   // accept drag and drop files
    if (m_drag.GetCheck())
        m_fileeditctrl.ModifyStyleEx(0, WS_EX_ACCEPTFILES);
    else
        m_fileeditctrl.ModifyStyleEx(WS_EX_ACCEPTFILES, 0);
}

void CFileEditDemoDlg::OnDump() 
{   // display files or folder entered in control
    if (UpdateData(TRUE))   // validate entries
    {
        CDumpDialog dump(this);
        dump.DoModal();
    }
}

void CFileEditDemoDlg::OnFile() 
{   // set control to accept files
    m_fileeditctrl.ModifyFlags(FEC_FOLDER, FEC_FILEOPEN);
    m_multi.EnableWindow(TRUE);
    m_wild.EnableWindow(TRUE);
    m_noderef.EnableWindow(TRUE);
    m_Add.EnableWindow(FALSE);
    OnMulti();
}

void CFileEditDemoDlg::OnFold() 
{   // set control to accept a folder
    m_fileeditctrl.ModifyFlags(FEC_FILEOPEN, FEC_FOLDER);
    m_Add.EnableWindow(TRUE);
    m_multi.EnableWindow(FALSE);
    m_wild.EnableWindow(FALSE);
    m_noderef.EnableWindow(FALSE);
    m_dump.SetWindowText(_T("Display Folder"));
    m_validate.SetWindowText(_T("Folder must e&xist"));
}

void CFileEditDemoDlg::OnImage() 
{   // use an image on the button instead of the ellipses
	if (m_image.GetCheck())
    {
        m_bitmap.EnableWindow();
        m_icon.EnableWindow();
        m_stretch.EnableWindow();
        if (m_bitmap.GetCheck())
            OnBitmap();
        else
            OnMyIcon();
    }
    else
    {
        m_bitmap.EnableWindow(FALSE);
        m_icon.EnableWindow(FALSE);
        m_transparent.EnableWindow(FALSE);
        m_stretch.EnableWindow(FALSE);
        m_fileeditctrl.SetButtonImage(NULL, 0);
    }
}

void CFileEditDemoDlg::OnLeft() 
{   // place the button on the left side of the control
    if (m_left.GetCheck())
        m_fileeditctrl.ModifyFlags(0, FEC_BUTTONLEFT);
    else
        m_fileeditctrl.ModifyFlags(FEC_BUTTONLEFT, 0);
}

void CFileEditDemoDlg::OnMulti() 
{   // set control to accept multiple files
//  OPENFILENAME *pOFN = m_fileeditctrl.GetOpenFileName();
    if (m_multi.GetCheck())
    {
        // Both these methods do the same thing and either one can be used
        m_fileeditctrl.ModifyFlags(0, FEC_MULTIPLE);
//      pOFN->Flags |= OFN_ALLOWMULTISELECT;

        m_file.SetWindowText(_T("Browse for &Files"));
        m_dump.SetWindowText(_T("Display Files"));
        m_validate.SetWindowText(_T("Files must e&xist"));
    }
    else
    {
        m_fileeditctrl.ModifyFlags(FEC_MULTIPLE, 0);
//      pOFN->Flags &= ~OFN_ALLOWMULTISELECT;

        m_file.SetWindowText(_T("Browse for &File"));
        m_dump.SetWindowText(_T("Display File"));
        m_validate.SetWindowText(_T("File must e&xist"));
    }

    // force a call to CFileEditCtrl::FillBuffers() by modifying the window text
    CString text;
    m_fileeditctrl.GetWindowText(text);
    m_fileeditctrl.SetWindowText(text);
}

void CFileEditDemoDlg::OnMyIcon() 
{   // image is an icon
    m_transparent.EnableWindow(FALSE);
    HANDLE handle = ::LoadImage(AfxGetInstanceHandle(),
                                MAKEINTRESOURCE(IDI_ICON2),
                                IMAGE_ICON,
                                0,
                                0,
                                LR_DEFAULTCOLOR);
    m_fileeditctrl.SetButtonImage(handle, PJAI_ICON | PJAI_AUTODELETE | (m_stretch.GetCheck() ? PJAI_STRETCHED : 0));
}

void CFileEditDemoDlg::OnNoderef() 
{
    // set control to dereference shortcut (*.lnk) files
    if (m_noderef.GetCheck())
        m_fileeditctrl.ModifyFlags (0, FEC_NODEREFERENCELINKS);
        // could also set the OFN_NODEREFERENCELINKS flag directly via GetOpenFileName()
    else
        m_fileeditctrl.ModifyFlags (FEC_NODEREFERENCELINKS, 0);
}

void CFileEditDemoDlg::OnNormal() 
{   // enable control, clear readonly status
    OnDisable();
    m_fileeditctrl.SetReadOnly(FALSE);
}

void CFileEditDemoDlg::OnPreBrowse(NMHDR *pNMHDR, LRESULT *pResult)
{   // called before the control launches the browse dialog
    if (m_browse.GetCheck())
    {
        // setting *pResult to zero allows the browse dialog to launch
        *pResult = 0;
        FEC_NOTIFY *pnotify = (FEC_NOTIFY *)pNMHDR;
        OPENFILENAME *pOFN = pnotify->pFEC->GetOpenFileName();
        BROWSEINFO *pBInfo = pnotify->pFEC->GetBrowseInfo();

        if (m_SetDir.GetCheck())
        {   // Set folder
            if (pOFN)
                // setting lpstrInitialDir to NULL causes CFileEditCtrl::FECOpenFile
                // to set it to the directory specified in the control
                pOFN->lpstrInitialDir = NULL;

            if (pBInfo)
            {
                // set lpfn to our callback function FECFolderProc(), and set lParam
                // to a pointer to the CFileEditCtrl control, and FECFolderProc will
                // set the initial directory in the SHBrowseForFolder dialog to the
                // directory specified in the control
                pBInfo->lpfn = FECFolderProc;
                pBInfo->lParam = (LPARAM)pnotify->pFEC;
            }
        }

        else  // !m_SetDir.GetCheck()
        {   // do not set folder
            if (pOFN)
            {
                // setting lpstrInitialDir to an empty string causes CFileDialog
                // to set the directory to the current working directory
                pOFN->lpstrInitialDir = _T("");
                *(pOFN->lpstrFile) = 0;
            }

            if (pBInfo)
                // setting lpfn to NULL causes SHBrowseForFolder to start at the
                // root directory
                pBInfo->lpfn = NULL;
        }
    }

    else  // !m_browse.GetCheck()
        // setting *pResult to non-zero does not allow the browse dialog to launch
        *pResult = 1;
}

void CFileEditDemoDlg::OnRead() 
{   // set control to readonly
    OnDisable();
    m_fileeditctrl.SetReadOnly(TRUE);
}

void CFileEditDemoDlg::OnStretch() 
{   // image is resized to fit the button
    if (m_bitmap.GetCheck())
        OnBitmap();
    else
        OnMyIcon();
}

BOOL CFileEditDemoDlg::OnToolTipText(UINT, NMHDR *pNMHDR, LRESULT *)
{   // Set tooltip font to the same font used by the dialog
    CToolTipCtrl *pToolTipCtrl = AfxGetThreadState()->m_pToolTip;
    if (pToolTipCtrl)
        pToolTipCtrl->SetFont(GetFont(), FALSE);

    // get text for demo dialog's tooltips
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT nID = pNMHDR->idFrom;
    if (pTTT->uFlags & TTF_IDISHWND)
        // idFrom is actually the HWND of the tool
        nID = ::GetDlgCtrlID((HWND)nID);
    if(nID)
    {
        pTTT->lpszText = MAKEINTRESOURCE(nID);
        pTTT->hinst = AfxGetResourceHandle();
        return(TRUE);
    }
    return(FALSE);
}

void CFileEditDemoDlg::OnTransparent() 
{   // bitmap is to be transparent
	OnBitmap();
}

void CFileEditDemoDlg::OnValidate() 
{   // verify that the files entered actually exist
    OPENFILENAME *pOFN = m_fileeditctrl.GetOpenFileName();
    if (pOFN)
        if (m_validate.GetCheck())
            pOFN->Flags |= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
        else
            pOFN->Flags &= ~(OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST);
}

void CFileEditDemoDlg::OnWild() 
{   // set control to accept wildcards in file name
    if (m_wild.GetCheck())
        m_fileeditctrl.ModifyFlags(0, FEC_WILDCARDS);
    else
        m_fileeditctrl.ModifyFlags(FEC_WILDCARDS, 0);
}

/////////////////////////////////////////////////////////////////////////////
// CDumpDialog dialog

CDumpDialog::CDumpDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CDumpDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDumpDialog)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CDumpDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDumpDialog)
	DDX_Control(pDX, IDC_STATIC1, m_static);
    DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDumpDialog, CDialog)
    //{{AFX_MSG_MAP(CDumpDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpDialog message handlers

BOOL CDumpDialog::OnInitDialog() 
{
    CDialog::OnInitDialog();

    CFileEditDemoDlg *pDemo = (CFileEditDemoDlg *)GetParent();
    int width = 0;
    CString str;
    CDC *pDC = m_List.GetDC();
    int saved = pDC->SaveDC();
    pDC->SelectObject(GetFont());

    UINT count = 0;

    // call GetStartPosition() to get the position of the first file in the control
    POSITION pos = pDemo->m_fileeditctrl.GetStartPosition();
    while (pos)
    {
        // add the file paths to the list
        str = pDemo->m_fileeditctrl.GetNextPathName(pos);
        m_List.AddString(str);
        CSize size(0, 0);
        size = pDC->GetTextExtent(str);
        width = width > size.cx ? width : size.cx;
        ++count;
    }
    pDC->RestoreDC(saved);
    ReleaseDC(pDC);
    m_List.SetHorizontalExtent(width + 5);

    str.Format(_T("%u"), count);
    m_static.SetWindowText(str);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileEditDemoDlg::OnSetbuttonwidth() 
{   // used the default button width or the user defined button width
	if (m_setwidth.GetCheck())
    {
        m_butwidth.EnableWindow();
        CString str;
        m_butwidth.GetWindowText(str);
        m_fileeditctrl.SetButtonWidth(atoi(str));
    }
    else
    {
        m_butwidth.EnableWindow(FALSE);
        m_fileeditctrl.SetButtonWidth();   // use default width
    }
}

void CFileEditDemoDlg::OnChangeEdit3() 
{   // change the width of the browse button
    if (IsWindow(m_butwidth) && m_setwidth.GetCheck())
    {
        CString str;
        m_butwidth.GetWindowText(str);
        int width = atoi(str);
        m_fileeditctrl.SetButtonWidth(width);
    }
}

void CFileEditDemoDlg::OnFlat() 
{	// change between a flat or normal control
    m_gray.EnableWindow(m_flat.GetCheck());
    if (m_flat.GetCheck())
    {
        m_fileeditctrl.ModifyFlags(0, FEC_FLAT);
        OnGray();
    }
    else
        m_fileeditctrl.ModifyFlags(FEC_FLAT | FEC_GRAYSCALE, 0);
}

void CFileEditDemoDlg::OnGray() 
{   // draw the flat button in grayscale
	if (m_gray.GetCheck())
        m_fileeditctrl.ModifyFlags(0, FEC_GRAYSCALE);
    else
        m_fileeditctrl.ModifyFlags(FEC_GRAYSCALE, 0);
    // force the control to be redrawn. if we don't do this, the change
    // won't show until the control redraws itself
    m_fileeditctrl.RedrawWindow(NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
}

void CFileEditDemoDlg::OnDrop(NMHDR *pNMHDR, LRESULT *pResult)
{   // handles the FEC_NM_DROP notification from fileeditctrl
    FEC_NOTIFY *fecn = (FEC_NOTIFY *)pNMHDR;
}

void  CFileEditDemoDlg::OnPostBrowse(NMHDR *pNMHDR, LRESULT *pResult)
{   // handles the FEC_NM_POSTBROWSE notification from fileeditctrl
    FEC_NOTIFY *fecn = (FEC_NOTIFY *)pNMHDR;
}
