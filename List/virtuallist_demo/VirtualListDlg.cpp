// VirtualListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualList.h"
#include "VirtualListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVirtualListDlg dialog

CVirtualListDlg::CVirtualListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVirtualListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVirtualListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVirtualListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVirtualListDlg)
	DDX_Control(pDX, IDC_COMBO_STYLE, m_style);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVirtualListDlg, CDialog)
	//{{AFX_MSG_MAP(CVirtualListDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADDTEN, OnButtonAddten)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, OnGetdispinfoList)
	ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST, OnOdfinditemList)
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST, OnOdcachehintList)
	ON_CBN_SELCHANGE(IDC_COMBO_STYLE, OnSelchangeComboStyle)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST, OnKeydownList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtualListDlg message handlers

BOOL CVirtualListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ListView_SetExtendedListViewStyle(m_list.m_hWnd, LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES );

	//Create image list
	m_imagelist.Create(IDB_BITMAP, 16, ILC_COLOR4, RGB(255, 255, 255));
	m_imagelistLarge.Create(IDB_BITMAP_LARGE, 32, ILC_COLOR4, RGB(255, 255, 255));
		
	m_list.SetImageList(&m_imagelist, LVSIL_SMALL);
	m_list.SetImageList(&m_imagelistLarge, LVSIL_NORMAL);
	


	m_list.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 130);
	m_list.InsertColumn(1, _T("Slogan"), LVCFMT_LEFT, 200);

	m_style.SetCurSel(3);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVirtualListDlg::OnPaint() 
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
HCURSOR CVirtualListDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVirtualListDlg::OnButtonAddten() 
{
	//Add 10 elements to the database
	for(int i=0; i<10; i++)
		m_database.push_back( CSampleData() );

	//Resize the list to add the elements to the list
	m_list.SetItemCount( m_database.size() );

	UpdateCount();
}

void CVirtualListDlg::OnButtonClear() 
{
	//Clear database and list.
	m_database.clear();

	m_list.SetItemCount(0);

	UpdateCount();
}

void CVirtualListDlg::UpdateCount()
{
	CString temp;
	temp.Format(_T("%d items."), m_database.size());

	GetDlgItem(IDC_STATIC_COUNT)->SetWindowText(temp);
}


void CVirtualListDlg::OnSelchangeComboStyle() 
{
	//Change list view style
	DWORD style = 0;

	switch( m_style.GetCurSel() )
	{
		case 0:
			style = LVS_ICON;
			break;
    
		case 1:
			style = LVS_SMALLICON;
			break;

		case 2:
			style = LVS_LIST;
			break;

		default:
			style = LVS_REPORT;
			break;
	}

	//Remove old style, and add new
	m_list.ModifyStyle(LVS_TYPEMASK, style);
	
	//Turn on/off check box
	if(style == LVS_ICON || style == LVS_SMALLICON)
		//Off
		ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_CHECKBOXES, 0);
	else
		//On
		ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES);
}

//This function is called when the list needs data. This is the most
//critical function when working with virtual lists.
void CVirtualListDlg::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	//Create a pointer to the item
	LV_ITEM* pItem= &(pDispInfo)->item;

	//Which item number?
	int itemid = pItem->iItem;

	//Do the list need text information?
	if (pItem->mask & LVIF_TEXT)
	{
		CString text;

		//Which column?
		if(pItem->iSubItem == 0)
		{
			//Text is name
			text = m_database[itemid].m_name;
		}
		else if (pItem->iSubItem == 1)
		{
			//Text is slogan
			text = m_database[itemid].m_slogan;
		}

		//Copy the text to the LV_ITEM structure
		//Maximum number of characters is in pItem->cchTextMax
		lstrcpyn(pItem->pszText, text, pItem->cchTextMax);
	}

	//Do the list need image information?
	if( pItem->mask & LVIF_IMAGE) 
	{
		//Set which image to use
		pItem->iImage=m_database[itemid].m_image;
		
		//Show check box?
		if(IsCheckBoxesVisible())
		{
			//To enable check box, we have to enable state mask...
			pItem->mask |= LVIF_STATE;
			pItem->stateMask = LVIS_STATEIMAGEMASK;

			if(m_database[itemid].m_checked)
			{
				//Turn check box on..
				pItem->state = INDEXTOSTATEIMAGEMASK(2);
			}
			else
			{
				//Turn check box off
				pItem->state = INDEXTOSTATEIMAGEMASK(1);
			}
		}
	}

	*pResult = 0;
}

//This functions is called when the user "writes" in the list box to find an item.
void CVirtualListDlg::OnOdfinditemList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// pNMHDR has information about the item we should find
	// In pResult we should save which item that should be selected
	NMLVFINDITEM* pFindInfo = (NMLVFINDITEM*)pNMHDR;

	/* pFindInfo->iStart is from which item we should search.
	   We search to bottom, and then restart at top and will stop
	   at pFindInfo->iStart, unless we find an item that match
	 */

	// Set the default return value to -1
	// That means we didn't find any match.
	*pResult = -1;

	//Is search NOT based on string?
	if( (pFindInfo->lvfi.flags & LVFI_STRING) == 0 )
	{
		//This will probably never happend...
		return;
	}

	/*
		Let's look on a sample list;
		
		  Name
		  Anders
		* Anna
		  Annika
		  Bob
		  Emma
		  Emmanuel

		Anna is selected. 
		If "A" is written, Annika should be selected.
		If "AND" is written, Anders should be selected. 
		If "ANNK" is written, the selection should stay on Anna.
		If "E" is written, Emma should be selected.

    */

	//This is the string we search for
	CString searchstr = pFindInfo->lvfi.psz;

//	TRACE(_T("Find: %s\n"), searchstr);
	
	int startPos = pFindInfo->iStart;
	//Is startPos outside the list (happens if last item is selected)
	if(startPos >= m_list.GetItemCount())
		startPos = 0;

	int currentPos=startPos;
	
	//Let's search...
	do
	{		
		//Do this word begins with all characters in searchstr?
		if( _tcsnicmp(m_database[currentPos].m_name, searchstr, searchstr.GetLength()) == 0)
		{
			//Select this item and stop search.
			*pResult = currentPos;
			break;
		}

		//Go to next item
		currentPos++;

		//Need to restart at top?
		if(currentPos >= m_list.GetItemCount())
			currentPos = 0;

	//Stop if back to start
	}while(currentPos != startPos);		
}

//This is called to give you a chance to catch data. Useless in most cases :-)
void CVirtualListDlg::OnOdcachehintList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVCACHEHINT* pCacheHint = (NMLVCACHEHINT*)pNMHDR;

/*	TRACE(	_T("Chache item %d to item %d\n"),
			pCacheHint->iFrom,
			pCacheHint->iTo );*/

	//... cache the data pCacheHint->iFrom to pCacheHint->iTo ...

	*pResult = 0;
}


void CVirtualListDlg::ToggleCheckBox(int item)
{
	//Change check box
	m_database[item].m_checked = !m_database[item].m_checked;

	//And redraw
	m_list.RedrawItems(item, item);
}

//This is called when user clicks on the list. 
//If you had check box you have to write code to make them possible to toggle.
void CVirtualListDlg::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	LVHITTESTINFO hitinfo;
	//Copy click point
	hitinfo.pt = pNMListView->ptAction;

	//Make the hit test...
	int item = m_list.HitTest(&hitinfo); 

	if(item != -1)
	{
		//We hit one item... did we hit state image (check box)?
		//This test only works if we are in list or report mode.
		if( (hitinfo.flags & LVHT_ONITEMSTATEICON) != 0)
		{
			ToggleCheckBox(item);
		}
	}

	
	*pResult = 0;
}

//This is called when a key i pressed down
void CVirtualListDlg::OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;

	//If user press space, toggle flag on selected item
	if( pLVKeyDown->wVKey == VK_SPACE )
	{
		//Check if check boxes are visible
		if( IsCheckBoxesVisible() )
		{
			//Toggle if some item is selected
			if(m_list.GetSelectionMark() != -1)
				ToggleCheckBox( m_list.GetSelectionMark() );
		}
	}

	*pResult = 0;
}

BOOL CVirtualListDlg::IsCheckBoxesVisible()
{
	DWORD style = m_list.GetStyle();

	if( ((style & LVS_TYPEMASK) == LVS_LIST) ||
		((style & LVS_TYPEMASK) == LVS_REPORT) )
			return TRUE;

	return FALSE;
}
