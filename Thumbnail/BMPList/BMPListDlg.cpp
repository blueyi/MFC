// BMPListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BMPList.h"
#include "BMPListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBMPListDlg dialog


CBMPListDlg::CBMPListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBMPListDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBMPListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_cList);
}

BEGIN_MESSAGE_MAP(CBMPListDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, GetDispInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CBMPListDlg message handlers

BOOL CBMPListDlg::OnInitDialog()
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
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Create 256 color image lists
	// Need to create image list with a phantom bitmap.
	// This image list is only used to hold the place.  The images are loaded
	// dynamically as the list control is scrolled.
	if(m_imageList.GetSafeHandle() == NULL) {
		m_imageList.Create(210, 160, ILC_COLOR24 | ILC_MASK, 8, 1);
		m_cList.SetImageList(&m_imageList, LVSIL_SMALL);
		m_cList.SetImageList(&m_imageList, LVSIL_NORMAL);
		m_imageList.SetImageCount(1);
	}

	// Set up list control
	// Nothing special here.  Just some columns for the report view.
	m_cList.InsertColumn(0, _T("Column 1"), LVCFMT_LEFT, 200);
	m_cList.InsertColumn(1, _T("Column 2"), LVCFMT_LEFT, 100);
	m_cList.InsertColumn(3, _T("Column 3"), LVCFMT_LEFT, 100);
	m_cList.InsertColumn(4, _T("Column 4"), LVCFMT_LEFT, 100);
	m_cList.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_INFOTIP | LVS_EX_FLATSB);

	// Add some data
	InsertItems();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBMPListDlg::GetDispInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

	//Create a pointer to the item
	LV_ITEM* pItem= &(pDispInfo)->item;

	//Which item number?
	int nItem = pItem->iItem;

	CMyDataInfo *pInfo = NULL;
	if(nItem > m_MyDataArray.GetSize()-1)
		return; // Just to be safe

	pInfo = (CMyDataInfo *)m_MyDataArray.GetAt(nItem);
	if(pInfo == NULL)
		return;
    
	//Do we need text information?
	if (pItem->mask & LVIF_TEXT) {
		CString csText;

		//Which column?
		if(pItem->iSubItem == 0)
			csText = pInfo->m_csColumn1;
		else if (pItem->iSubItem == 1) // Column 1
			csText = pInfo->m_csColumn2;
		else if (pItem->iSubItem == 2) // Column 2
			csText = pInfo->m_csColumn3;
		else if (pItem->iSubItem == 3) // Column 3
			csText = pInfo->m_csColumn4;

		//Copy the text to the LV_ITEM structure
		//Maximum number of characters is in pItem->cchTextMax
		lstrcpyn(pItem->pszText, csText, pItem->cchTextMax);
	}

	//Does the list need image information?
	if( pItem->mask & LVIF_IMAGE) {
		// Need to reset first item of image list to the correct bitmap
		HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),pInfo->m_csImage,
			IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		if(hBmp != NULL) {
			CBitmap *cBmp = CBitmap::FromHandle(hBmp);
			if(cBmp != NULL)
				m_imageList.Replace(0,cBmp,NULL);
		}
		// Note, there is no Navigator 0.bmp so that image will always display blank to 
		// illustrate what would happen when the file is not found.
		else {
			CBitmap *cBmp = new CBitmap();
			cBmp->LoadBitmap(IDB_BLANK);
			m_imageList.Replace(0,cBmp,NULL);
			delete cBmp;
		}
		pItem->iImage = 0; // Always use 0 since only one element
    }
	*pResult = 0;
}

void CBMPListDlg::InsertItems()
{
	m_MyDataArray.RemoveAll(); // Clear the array

	// Add some data (100000 records)
	// These items are stored in an array, not in the list control itself.
	// We're just putting in enough here to identify the row and column
	// This is the slowest operation in the prgram, but we need some data
	// to do the illustration.
	for(int i = 0; i < 100000; ++i) {
		CMyDataInfo *pInfo = new CMyDataInfo();
		if(pInfo) {
			CString cs;
			cs.Format(_T("R%dColumn1"),i);
			pInfo->m_csColumn1 = cs;
			cs.Format(_T("R%dColumn2"),i);
			pInfo->m_csColumn2 = cs;
			cs.Format(_T("R%dColumn3"),i);
			pInfo->m_csColumn3 = cs;
			cs.Format(_T("R%dColumn4"),i);
			pInfo->m_csColumn4 = cs;

			// This will count from Navigator 0.bmp to Navigator 4.bmp.  There is no
			// file Navigator 0.bmp so those rows will use the blank bitmap from the build in
			// resources.
			cs.Format(_T("Navigator %d.bmp"),(i % 5));
			pInfo->m_csImage = cs; // Just repeat images every 4 
			m_MyDataArray.Add(pInfo);
		}
	}

	m_cList.DeleteAllItems();

	// This sets the count in the list without adding any items.  This is very fast.
	m_cList.SetItemCountEx((int)m_MyDataArray.GetCount(), LVSICF_NOSCROLL|LVSICF_NOINVALIDATEALL);
}

void CBMPListDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBMPListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBMPListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

