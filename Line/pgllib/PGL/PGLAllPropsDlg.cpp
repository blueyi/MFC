// PGLAllPropsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/pgl.h"
#include "PGL/PGLAllPropsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLAllPropsDlg dialog


CPGLAllPropsDlg::CPGLAllPropsDlg(CWnd* pParent /*=NULL*/, CPGLGraph* _pGraph)
	: CDialog(CPGLAllPropsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPGLAllPropsDlg)
	//}}AFX_DATA_INIT
	PGL_TRACE("CPGLAllPropsDlg - construtor\n");

	m_pGraph=_pGraph;
	m_pSheet=NULL;
	m_lSelID=0;
}


void CPGLAllPropsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLAllPropsDlg)
	DDX_Control(pDX, IDC_PGL_OBJECTTREE, m_tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLAllPropsDlg, CDialog)
	//{{AFX_MSG_MAP(CPGLAllPropsDlg)
	ON_WM_DESTROY()
	ON_NOTIFY(TVN_SELCHANGED, IDC_PGL_OBJECTTREE, OnSelchangedPglObjecttree)
	ON_BN_CLICKED(IDC_PGL_BUTTON_CLOSE, OnPglButtonClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLAllPropsDlg message handlers


void CPGLAllPropsDlg::FillTree()
{
	CString str;
	ASSERT_VALID(m_pGraph);

	// creating image list
	VERIFY(m_imgList.Create( 12, 12, ILC_COLOR4, 7, 5));
	COLORREF crMask=0;

	// loading bitmaps
	// saving old ressource.
	HINSTANCE hOldInst=AfxGetResourceHandle();
	// setting dll ressource
	AfxSetResourceHandle(AfxGetInstanceHandle());
	// load bitmap
	m_bmpSelect.LoadBitmap(IDB_PGL_SELECT_BITMAP);
	// restoring old ressource.
	AfxSetResourceHandle(hOldInst);

	m_imgList.Add(&m_bmpSelect,crMask);
	// adding image to imagelist
	m_tree.SetImageList(&m_imgList, TVSIL_NORMAL);

	// filling tree...
	m_pGraph->AddPropTree(&m_tree,TVI_ROOT);	
}


BOOL CPGLAllPropsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//filling tree
	FillTree();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPGLAllPropsDlg::OnDestroy() 
{
	// removing images
	while (m_imgList.GetImageCount()>0)
	{
		m_imgList.Remove(0);
	}
	m_imgList.DeleteImageList();

	// removing property sheet if it exists
	if (m_pSheet)
	{
		// kill active all current page
		CPropertyPage* pPage=m_pSheet->GetActivePage();
		ASSERT_VALID(pPage);
		pPage->OnKillActive();
		// removing prop sheet from tab
		for (int i=0;i<m_pSheet->GetPageCount();i++)
		{
			CPropertyPage* pPage=m_pSheet->GetPage(i);
			if (pPage)
				delete pPage;
		}
		// deleting sheet
		delete m_pSheet;
		m_pSheet=NULL;
	}

	// Cleaning up tree
	m_tree.DeleteAllItems();

	CDialog::OnDestroy();
}

void CPGLAllPropsDlg::OnSelchangedPglObjecttree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	ASSERT_VALID(m_pGraph);

	// removing prop sheet from tab
	if (m_pSheet)
	{
		// kill active all current page
		CPropertyPage* pPage=m_pSheet->GetActivePage();
		ASSERT_VALID(pPage);
		pPage->OnKillActive();
	
		for (int i=0;i<m_pSheet->GetPageCount();i++)
		{
			pPage=m_pSheet->GetPage(i);
			if (pPage)
				delete pPage;
		}
		delete m_pSheet;
		m_pSheet=NULL;
	}

	// getting new item
	CPGLObject* pObj;
	TVITEM pItemOld=pNMTreeView->itemOld;
	TVITEM pItemNew=pNMTreeView->itemNew;

	// setting item to bold
	if (pItemOld.hItem)
	{
		// reseting bold
		VERIFY(m_tree.SetItemState( pItemOld.hItem, !TVIS_BOLD  , TVIS_BOLD) );
		// reseting text (if it has changed
		pObj=m_pGraph->FindObject(pItemOld.lParam);
		if (pObj)
		{
			m_tree.SetItemText( pItemOld.hItem,pObj->GetName()); 
		}
	}
	VERIFY(m_tree.SetItemState( pItemNew.hItem, TVIS_BOLD  ,TVIS_BOLD) );

	// getting object.
	// check if it is the object manager
	if (pItemNew.lParam==-1)
	{
		*pResult = 0;
		return;
	}

	// check to find object
	pObj=m_pGraph->FindObject(pItemNew.lParam);
	// if none found stop
	if (pObj==NULL)
	{
		// not found
		*pResult = 0;
		return;
	}

	// adding property sheet of object
	ASSERT_VALID(pObj);
	m_pSheet=new CPropertySheet;
	pObj->AddPropertyPage(m_pSheet);
	m_pSheet->Create(this, WS_CHILD | WS_VISIBLE, 0);
	m_pSheet->ModifyStyleEx(0,WS_EX_CONTROLPARENT);
	m_pSheet->ModifyStyle(0,WS_TABSTOP);
	CRect rect;
	GetDlgItem(IDC_PGL_STATIC_PROPSHEET)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_pSheet->SetWindowPos(NULL,rect.left,rect.top,
		rect.right-rect.left,rect.top-rect.bottom,
		SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);

	*pResult = 0;
}


void CPGLAllPropsDlg::OnPglButtonClose() 
{
	CDialog::OnOK();
}
