// MultipleColumnsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultipleColumns.h"
#include "MultipleColumnsDlg.h"

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
// CMultipleColumnsDlg dialog

CMultipleColumnsDlg::CMultipleColumnsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultipleColumnsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultipleColumnsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultipleColumnsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultipleColumnsDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMultipleColumnsDlg, CDialog)
	//{{AFX_MSG_MAP(CMultipleColumnsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OK)
	ON_BN_CLICKED(IDC_BUTTON2, OnExit)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultipleColumnsDlg message handlers

BOOL CMultipleColumnsDlg::OnInitDialog()
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
	
	//Set the style to listControl
	ListView_SetExtendedListViewStyle(::GetDlgItem(m_hWnd,IDC_LIST1),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); 
	InsertItems();
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_HIDE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMultipleColumnsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMultipleColumnsDlg::OnPaint() 
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
HCURSOR CMultipleColumnsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// This function handles the ENTER key 
void CMultipleColumnsDlg::OnOK() 
{	
    CWnd* pwndCtrl = GetFocus();
    // get the control ID which is presently having the focus
	int ctrl_ID = pwndCtrl->GetDlgCtrlID();
	CString str;
    switch (ctrl_ID)
	{	//if the control is the EditBox	
        case IDC_EDIT1:
			//get the text from the EditBox
			GetDlgItemText(IDC_EDIT1,str);
			//set the value in the listContorl with the specified Item & SubItem values
			SetCell(::GetDlgItem (m_hWnd,IDC_LIST1),str,nItem,nSubItem);
			::SendDlgItemMessage(m_hWnd,IDC_EDIT1,WM_KILLFOCUS,0,0);
			::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_HIDE);
            break;     
        default:
            break;
    }
}
void CMultipleColumnsDlg::OK() 
{
	CDialog::EndDialog (0);	
}

void CMultipleColumnsDlg::OnExit() 
{
	CDialog::EndDialog (0);	

}

// This function inserts the default values into the listControl
void CMultipleColumnsDlg::InsertItems()
{
	HWND hWnd = ::GetDlgItem(m_hWnd, IDC_LIST1);

	// Set the LVCOLUMN structure with the required column information
	LVCOLUMN list;
	list.mask =  LVCF_TEXT |LVCF_WIDTH| LVCF_FMT |LVCF_SUBITEM;
	list.fmt = LVCFMT_LEFT;
	list.cx = 50;
	list.pszText   = "S.No";
	list.iSubItem = 0;
	//Inserts the column
	::SendMessage(hWnd,LVM_INSERTCOLUMN, (WPARAM)0,(WPARAM)&list);
	
	list.cx = 100;
	list.pszText   = "Name";
	list.iSubItem = 1;
	::SendMessage(hWnd  ,LVM_INSERTCOLUMN, (WPARAM)1,(WPARAM)&list);

	list.cx = 100;
	list.pszText   = "Address";
	list.iSubItem = 2;
	::SendMessage(hWnd  ,LVM_INSERTCOLUMN, (WPARAM)1,(WPARAM)&list);

	list.cx = 100;
	list.pszText   = "Country";
	list.iSubItem = 3;
	::SendMessage(hWnd  ,LVM_INSERTCOLUMN, (WPARAM)1,(WPARAM)&list);

	// Inserts first Row with four column .
	SetCell(hWnd,"1",0,0);
	SetCell(hWnd,"Prabhakar",0,1);
	SetCell(hWnd,"Hyderabad",0,2);
	SetCell(hWnd,"India",0,3);

	// Inserts second Row with four columns .
	SetCell(hWnd,"2",1,0);
	SetCell(hWnd,"Uday",1,1); 
	SetCell(hWnd,"Chennai",1,2);
	SetCell(hWnd,"India",1,3);

	// Inserts third Row with four column .
	SetCell(hWnd,"3",2,0);
	SetCell(hWnd,"Saradhi",2,1); 
	SetCell(hWnd,"Bangolore",2,2);
	SetCell(hWnd,"India",2,3);

	// Inserts fourth Row with four column .
	SetCell(hWnd,"4",3,0);
	SetCell(hWnd,"Surya",3,1); 
	SetCell(hWnd,"Calcutta",3,2);
	SetCell(hWnd,"India",3,3);


}
// This function set the text in the specified SubItem depending on the Row and Column values
void CMultipleColumnsDlg::SetCell(HWND hWnd1, CString value, int nRow, int nCol)
{
	TCHAR     szString [256];
	wsprintf(szString,value ,0);

	//Fill the LVITEM structure with the values given as parameters.
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nRow;
	lvItem.pszText = szString;
	lvItem.iSubItem = nCol;
	if(nCol >0)
	//set the value of listItem
	::SendMessage(hWnd1,LVM_SETITEM, (WPARAM)0,(WPARAM)&lvItem);
	else
	//Insert the value into List
	ListView_InsertItem(hWnd1,&lvItem);

}



void CMultipleColumnsDlg::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{

	Invalidate();
	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
	RECT rect;
	//get the row number
	nItem = temp->iItem;
	//get the column number
	nSubItem = temp->iSubItem;
	if(nSubItem == 0 || nSubItem == -1 || nItem == -1)
		return ;
	//Retrieve the text of the selected subItem from the list
	CString str = GetItemText(hWnd1,nItem ,nSubItem);

	RECT rect1,rect2;
	// this macro is used to retrieve the Rectanle of the selected SubItem
	ListView_GetSubItemRect(hWnd1,temp->iItem,temp->iSubItem,LVIR_BOUNDS,&rect);
	//Get the Rectange of the listControl
	::GetWindowRect(temp->hdr.hwndFrom,&rect1);
	//Get the Rectange of the Dialog
	::GetWindowRect(m_hWnd,&rect2);

	int x=rect1.left-rect2.left;
	int y=rect1.top-rect2.top;
	
	if(nItem != -1)	
	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT1),HWND_TOP,rect.left+x,rect.top +y,rect.right-rect.left - 3,rect.bottom-rect.top -1,NULL);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_SHOW);
	::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT1));
	//Draw a Rectangle around the SubItem
	::Rectangle(::GetDC(temp->hdr.hwndFrom),rect.left,rect.top-1,rect.right,rect.bottom);
	//Set the listItem text in the EditBox
	::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),str);
	*pResult = 0;
}

//this function will returns the item text depending on the item and SubItem Index
CString CMultipleColumnsDlg::GetItemText(HWND hWnd, int nItem, int nSubItem) const
{
	LVITEM lvi;
	memset(&lvi, 0, sizeof(LVITEM));
	lvi.iSubItem = nSubItem;
	CString str;
	int nLen = 128;
	int nRes;
	do
	{
		nLen *= 2;
		lvi.cchTextMax = nLen;
		lvi.pszText = str.GetBufferSetLength(nLen);
		nRes  = (int)::SendMessage(hWnd, LVM_GETITEMTEXT, (WPARAM)nItem,
			(LPARAM)&lvi);
	} while (nRes == nLen-1);
	str.ReleaseBuffer();
	return str;
}
