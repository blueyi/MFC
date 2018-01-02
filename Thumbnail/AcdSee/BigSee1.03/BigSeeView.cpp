// BigSeeView.cpp : implementation of the CBigSeeView class
//

#include "stdafx.h"
#include "BigSee.h"

#include "BigSeeDoc.h"
#include "BigSeeView.h"
#include "FileStatusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBigSeeView

IMPLEMENT_DYNCREATE(CBigSeeView, CListView)

BEGIN_MESSAGE_MAP(CBigSeeView, CListView)
	//{{AFX_MSG_MAP(CBigSeeView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBigSeeView construction/destruction

CBigSeeView::CBigSeeView():m_strFilePath(_T("")), m_strFileName(_T(""))
                           ,IsHaveImage(FALSE),m_strFileExt(_T(""))
{                         
	// TODO: add construction code here

}

CBigSeeView::~CBigSeeView()
{
}

BOOL CBigSeeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    cs.style&=~LVS_TYPEMASK;
	cs.style|=LVS_ICON;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBigSeeView drawing

void CBigSeeView::OnDraw(CDC* pDC)
{
	CBigSeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CBigSeeView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

    m_ilFile.Create(IDB_FILEDOC,48,1,RGB(255,0,255));
    m_ilFolder.Create(IDB_FOLDERDOC,48,1,RGB(255,0,255));
	GetListCtrl().SetImageList(&m_ilFile,LVSIL_NORMAL );
    //GetListCtrl().SetImageList(&m_ilFolder,LVSIL_NORMAL );
	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CBigSeeView printing

BOOL CBigSeeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBigSeeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBigSeeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBigSeeView diagnostics

#ifdef _DEBUG
void CBigSeeView::AssertValid() const
{
	CListView::AssertValid();
}

void CBigSeeView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CBigSeeDoc* CBigSeeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBigSeeDoc)));
	return (CBigSeeDoc*)m_pDocument;
}
#endif //_DEBUG
//////////////////////////
void CBigSeeView:: EnumFiles()
{
	if(IsHaveImage)
	{
		GetListCtrl().DeleteAllItems();
	}
	//Get the current folder
	LPTSTR pCurFolder=m_strFilePath.GetBufferSetLength(m_strFilePath.GetLength()-m_strFileName.GetLength()-1);
	//CString CurrentFolderPath(pCurFolder);
	LVITEM lvi;
	WIN32_FIND_DATA fd;
	int nindex=0;
	::SetCurrentDirectory(pCurFolder);
	/*
	CString temp("*.");
	strcat(temp.GetBuffer(0),m_strFileExt);//error method
	HANDLE hFind=::FindFirstFile(temp,&fd);
	*/
	HANDLE hFind=::FindFirstFile(_T("*.*"),&fd);
	if(hFind!=INVALID_HANDLE_VALUE)
	{
		do{ 
			CString temp=fd.cFileName;
			
			if((!(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))&&(temp.Right(m_strFileExt.GetLength())==m_strFileExt))
			{
		        lvi.mask=LVIF_TEXT|LVIF_IMAGE;
				lvi.iItem=nindex;
				lvi.iSubItem=0;
				lvi.iImage=0;
				lvi.pszText=fd.cFileName;
                if(GetListCtrl().InsertItem(&lvi)==-1)
                       return;
			}
			/*else //if(fd.dwFileAttributes&FILE_ATTRIBUTE_ARCHIVE)
			{
				GetListCtrl().SetImageList(&m_ilFile,LVSIL_NORMAL );
				lvi.mask=LVIF_TEXT|LVIF_IMAGE;
				lvi.iItem=nindex;
				lvi.iSubItem=0;
				lvi.iImage=0;
				lvi.pszText=fd.cFileName;
                if(GetListCtrl().InsertItem(&lvi)==-1)
                       return;
				
			}*/

		}while(::FindNextFile(hFind,&fd));
		::FindClose(hFind);
	}

}

/////////////////////////////////////////////////////////////////////////////
// CBigSeeView message handlers

/*
void CBigSeeView::OnItemdblclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	LPTSTR ItemInfo=(phdn->pitem)->pszText;
	GetDocument()->UpdateAllViews(this,0x5A,(CObject*)ItemInfo);
	*pResult = 0;
}
*/

void CBigSeeView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString ItemInfo=GetListCtrl().GetItemText(pNMListView->iItem,0);
	GetDocument()->UpdateAllViews(this,0x5A,(CObject*)(LPCTSTR)ItemInfo);
	*pResult = 0;
}


void CBigSeeView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{   
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString FileInfo=GetListCtrl().GetItemText(pNMListView->iItem,0);
	CFile file;
	CFileStatus filestatus;
	file.Open(FileInfo,CFile::modeRead);
	file.GetStatus(FileInfo,filestatus);

	int nItem, nFlags;
    //char szTest[80];
    nFlags = LVNI_SELECTED;
    nItem = GetListCtrl().GetNextItem(-1, nFlags );
    if ( nItem != -1 )
    {
        //sprintf( szTest, "Selected Item %d", nItem);
        //AfxMessageBox(szTest);
		CFileStatusDlg dlg;
		dlg.m_strfilepath=m_strFilePath;//filestatus.m_szFullName;
		dlg.m_strfilesize.Format("%d",filestatus.m_size/1024);
        strcat(dlg.m_strfilesize.GetBuffer(0),"KB");
		dlg.DoModal();
    }

	*pResult = 0;
}


BOOL CBigSeeView::OnEraseBkgnd(CDC* pDC) 
{
   COLORREF backcolor=(COLORREF) GetSysColor(COLOR_BTNFACE+1); 
	CBrush backBrush(backcolor); 
    
    // Save old brush 
    CBrush* pOldBrush = pDC->SelectObject(&backBrush); 
    CRect rect; 
    pDC->GetClipBox(&rect); 
    
    // Erase the area needed 
    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY); 
    pDC->SelectObject(pOldBrush); 
    
    return TRUE; 
	
//	return CListView::OnEraseBkgnd(pDC);
}

DROPEFFECT CBigSeeView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CListView::OnDragEnter(pDataObject, dwKeyState, point);
}

BOOL CBigSeeView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CListView::OnDrop(pDataObject, dropEffect, point);
}

void CBigSeeView::OnDragLeave() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListView::OnDragLeave();
}

DROPEFFECT CBigSeeView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CListView::OnDragOver(pDataObject, dwKeyState, point);
}
