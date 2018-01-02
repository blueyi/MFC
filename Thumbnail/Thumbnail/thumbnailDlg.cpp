// thumbnailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "thumbnail.h"
#include "thumbnailDlg.h"
#include "PathDialog.h"

#include <gdiplus.h>
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	75

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
// CThumbnailDlg dialog

CThumbnailDlg::CThumbnailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThumbnailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CThumbnailDlg)
	m_strImageDir = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThumbnailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThumbnailDlg)
	DDX_Control(pDX, IDC_LIST_THUMB, m_ListThumbnail);
	DDX_Control(pDX, IDC_IMAGE_RECT, m_ImageRect);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strImageDir);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CThumbnailDlg, CDialog)
	//{{AFX_MSG_MAP(CThumbnailDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_LOAD, OnBtnLoad)
	ON_NOTIFY(NM_CLICK, IDC_LIST_THUMB, OnClickListThumb)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_THUMB, OnKeydownListThumb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThumbnailDlg message handlers

BOOL CThumbnailDlg::OnInitDialog()
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
	m_ImageListThumb.Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, 0, 1);
	m_ListThumbnail.SetImageList(&m_ImageListThumb, LVSIL_NORMAL);
	m_nSelectedItem = 0;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThumbnailDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CThumbnailDlg::OnPaint() 
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
		CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CThumbnailDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CThumbnailDlg::OnBtnBrowse() 
{
	// TODO: Add your control notification handler code here
	CPathDialog  dlg( TEXT("Folder Selection"), 
					  TEXT("Select Image Directory to Browse"),
					  m_strImageDir, 
					  this );

	// show path dialog
	if ( dlg.DoModal() == IDOK )
	{
		CString strPath = dlg.GetPathName();
		if (strPath != m_strImageDir)
		{
			m_strImageDir = strPath;
			UpdateData(FALSE);
		}
	}
}

void CThumbnailDlg::OnBtnLoad() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	// validate image directory
	if (m_strImageDir.IsEmpty())
	{
		MessageBox(CString((LPCSTR)IDS_DIR_ERROR), CString((LPCSTR)IDS_TITLE), MB_OK|MB_ICONSTOP);
		GetDlgItem(IDC_EDIT_PATH)->SetFocus();
		return;
	}

	// show hour glass cursor
	BeginWaitCursor();

	// get the names of bitmap files
	if ( !GetImageFileNames() )
	{
		EndWaitCursor();
		return;
	}

	// draw thumbnail images in list control
	DrawThumbnails();

	// draw the selected image in its full size
	DrawSelectedImage();

	// set focus and select the first thumbnail in the list control
	m_ListThumbnail.SetFocus();
	m_ListThumbnail.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);	
	EndWaitCursor();

}

void CThumbnailDlg::OnClickListThumb(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	// retrieve message info.
	LPNMITEMACTIVATE pItemAct = (LPNMITEMACTIVATE)pNMHDR;

	// determine which item receives the click
	LVHITTESTINFO  hitTest;
	ZeroMemory(&hitTest, sizeof(LVHITTESTINFO));
	hitTest.pt = pItemAct->ptAction;
	m_ListThumbnail.SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)&hitTest);

	// draw the selected image
	if (hitTest.iItem != m_nSelectedItem && hitTest.iItem >= 0)
	{
		m_nSelectedItem = hitTest.iItem;
		DrawSelectedImage();
	}

	// select the item clicked
	*pResult = 0;
}

void CThumbnailDlg::OnKeydownListThumb(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	if (pLVKeyDow->wVKey == VK_LEFT || pLVKeyDow->wVKey == VK_RIGHT)
	{	
		// get total number of items in the list
		int nTotal = m_ListThumbnail.GetItemCount();

		// rule out the situation of an empty list
		if (nTotal == 0)
		{
			*pResult = 1; // current record stays selected
			return;
		}
    
		// reset selected item index
		int  nNewItem = -1;

		// set the selection
		if (pLVKeyDow->wVKey == VK_LEFT)	// left arrow
		{
			if (m_nSelectedItem > 0)
				nNewItem = m_nSelectedItem - 1;
		}
		else	// right arrow
		{
			if (m_nSelectedItem < nTotal-1)
				nNewItem = m_nSelectedItem + 1;
		}

		// update the selection
		if (nNewItem != -1)
		{
			// update the selected item index
			m_nSelectedItem = nNewItem;

			// draw the selected image
			DrawSelectedImage();
		}	 
	}
	
	// high-light the selected item
	*pResult = 0;
}

void CThumbnailDlg::OnOK() 
{
	// disable return key to close the dialog	
	//CDialog::OnOK();
}

BOOL  CThumbnailDlg::GetImageFileNames()
{			
	CString	strExt;
	CString	strName;
	CString	strPattern;
	BOOL	bRC = TRUE;
	
	HANDLE					hFind = NULL;
	WIN32_FIND_DATA			FindFileData;
	std::vector<CString>	VectorImageNames;

	if ( m_strImageDir[m_strImageDir.GetLength() - 1] == TCHAR('\\') )	
		strPattern.Format( TEXT("%s*.*"), m_strImageDir );
	else
		strPattern.Format( TEXT("%s\\*.*"), m_strImageDir );

	hFind = ::FindFirstFile(strPattern, &FindFileData);	// strat search	
	if (hFind == INVALID_HANDLE_VALUE)
	{
		LPVOID  msg;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
					    NULL, 
						GetLastError(), 
					    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR)&msg, 
						0, 
						NULL);
		MessageBox((LPTSTR)msg, CString((LPCSTR)IDS_TITLE), MB_OK|MB_ICONSTOP);
		::LocalFree(msg);
		return FALSE;
	}

	// filter off the system files and directories
	if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
	    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
	    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
	    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
	{  	  
		// test file extension
		strName = FindFileData.cFileName;
		strExt = strName.Right(3);

		if ( (strExt.CompareNoCase( TEXT("bmp") ) == 0) ||
			 (strExt.CompareNoCase( TEXT("jpg") ) == 0) ||
			 (strExt.CompareNoCase( TEXT("gif") ) == 0) ||
			 (strExt.CompareNoCase( TEXT("tif") ) == 0) ||
			 (strExt.CompareNoCase( TEXT("png") ) == 0) )
		{
			// save the image file name
			VectorImageNames.push_back(strName);
		}
	}  

	// loop through to add all of them to our vector	
	while (bRC)
	{
		bRC = ::FindNextFile(hFind, &FindFileData);
		if (bRC)
		{
			// filter off the system files and directories
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
			    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
			    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
			    !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
			{
				// test file extension
				strName = FindFileData.cFileName;
				strExt = strName.Right(3);

				if ( (strExt.CompareNoCase( TEXT("bmp") ) == 0) ||
					 (strExt.CompareNoCase( TEXT("jpg") ) == 0) ||
					 (strExt.CompareNoCase( TEXT("gif") ) == 0) ||
					 (strExt.CompareNoCase( TEXT("tif") ) == 0) ||
					 (strExt.CompareNoCase( TEXT("png") ) == 0) )
				{
					// save the image file name
					VectorImageNames.push_back(strName);
				}
			}
		}  
		else
		{
			DWORD err = ::GetLastError();
			if (err !=  ERROR_NO_MORE_FILES)
			{
				LPVOID msg;
				::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
								NULL, err, 
								MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
								(LPTSTR)&msg, 0, NULL);
				MessageBox((LPTSTR)msg, CString((LPCSTR)IDS_TITLE), MB_OK|MB_ICONSTOP);
				::LocalFree(msg);
				::FindClose(hFind);
				return FALSE;
			}
		}
	} // end of while loop

	// close the search handle
	::FindClose(hFind);

	// update the names, if any
	if ( !VectorImageNames.empty() )
	{
		// reset the image name vector
		m_VectorImageNames.clear();
		m_VectorImageNames = VectorImageNames;
		return TRUE;
	}

	return FALSE;
}

void  CThumbnailDlg::DrawThumbnails()
{
	CBitmap*    pImage = NULL;
	HBITMAP		hBmp = NULL;
	POINT		pt;
	CString		strPath;
	int			i;

	// no images
	if (m_VectorImageNames.empty())
		return;

	// set the length of the space between thumbnails
	// you can also calculate and set it based on the length of your list control
	int nGap = 6;

	// hold the window update to avoid flicking
	m_ListThumbnail.SetRedraw(FALSE);

	// reset our image list
	for (i = 0; i<m_ImageListThumb.GetImageCount(); i++)
		m_ImageListThumb.Remove(i);	

	// remove all items from list view
	if (m_ListThumbnail.GetItemCount() != 0)
		m_ListThumbnail.DeleteAllItems();

	// set the size of the image list
	m_ImageListThumb.SetImageCount(m_VectorImageNames.size());
	i = 0;

	// draw the thumbnails
	std::vector<CString>::iterator	iter;
	for (iter = m_VectorImageNames.begin(); iter != m_VectorImageNames.end(); iter++)
	{		
		// load the bitmap
		strPath.Format( TEXT("%s\\%s"), m_strImageDir, *iter );

		USES_CONVERSION;
		Bitmap img( A2W(strPath) );
		Bitmap* pThumbnail = static_cast<Bitmap*>(img.GetThumbnailImage(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, NULL, NULL));
		
		// attach the thumbnail bitmap handle to an CBitmap object
		pThumbnail->GetHBITMAP(NULL, &hBmp);
		pImage = new CBitmap();		 
		pImage->Attach(hBmp);

		// add bitmap to our image list
		m_ImageListThumb.Replace(i, pImage, NULL);

		// put item to display
		// set the image file name as item text
		m_ListThumbnail.InsertItem(i, m_VectorImageNames[i], i);

		// get current item position	 
		m_ListThumbnail.GetItemPosition(i, &pt);	 
	  
		// shift the thumbnail to desired position
		pt.x = nGap + i*(THUMBNAIL_WIDTH + nGap);
		m_ListThumbnail.SetItemPosition(i, pt);
		i++;
			
		delete pImage;
		delete pThumbnail;
	}

	// let's show the new thumbnails
	m_ListThumbnail.SetRedraw(); 
}

void  CThumbnailDlg::DrawSelectedImage()
{
	CString		strPath;
	Rect		DesRect;
	RECT		clRect;

	// read the image file
	if (m_strImageDir.Right(1) == TEXT("\\") )
		strPath.Format( TEXT("%s%s"), m_strImageDir, m_VectorImageNames[m_nSelectedItem] );
	else
		strPath.Format( TEXT("%s\\%s"), m_strImageDir, m_VectorImageNames[m_nSelectedItem] );

	USES_CONVERSION;
	Image img( A2W(strPath) );

	// get destination rectangle
	m_ImageRect.GetClientRect(&clRect);
	DesRect.X = clRect.left;
	DesRect.Y = clRect.top;
	DesRect.Width = clRect.right - clRect.left;
	DesRect.Height = clRect.bottom - clRect.top;

	// draw the image
	Graphics gc( m_ImageRect.GetDC()->GetSafeHdc() );
	gc.DrawImage(&img, DesRect);
}


