// PGLPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/pgl.h"
#include "PGL/PGLPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLPropertySheet

IMPLEMENT_DYNAMIC(CPGLPropertySheet, CPropertySheet)

CPGLPropertySheet::CPGLPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPGLPropertySheet::CPGLPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CPGLPropertySheet::~CPGLPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CPGLPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CPGLPropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLPropertySheet message handlers

BOOL CPGLPropertySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	ASSERT_VALID(m_pGraph);

	// creating tree
	RECT rc;
	GetWindowRect (&rc);
	// Increase the height of the CPropertySheet by 30
	rc.right += 200;
	// Resize the CPropertySheet
	MoveWindow (rc.left+200, rc.top, rc.right, rc.bottom-rc.top);
	// Convert to client coordinates
	ScreenToClient (&rc);

	
	// filling tree
	FillTree();

	return bResult;
}

void CPGLPropertySheet::FillTree()
{
	ASSERT_VALID(m_pGraph);
	CString str;
	//////////////////////////////////
	// filling tree...
	// getting axis
	CPGLAxe2D* pAxe=m_pGraph->GetAxe();
	ASSERT_VALID(pAxe);
	// adding to tree
	HTREEITEM pAxeItem;
	pAxeItem=m_tree.InsertItem(TVIF_TEXT | TVIF_PARAM | TVIF_STATE  /* nMask*/, 
				"Axis" /* lpszItem*/, 
				0 /* nImage */, 
				0 /* nSelectedImage */, 
				TVIS_BOLD  /* nState */, 
				TVIS_OVERLAYMASK | TVIS_STATEIMAGEMASK /* nStateMask */, 
				pAxe->GetID() /*  lParam */, 
				TVI_ROOT /* hParent */, 
				TVI_LAST /* hInsertAfter */);
	ASSERT(pAxeItem!=NULL);

	// Adding objects
	// getting objects
	CPGLObjectManager* pObjMg=m_pGraph->GetObjectManager();
	ASSERT_VALID(pObjMg);
	CPGLObject* pObj;
	POSITION pos;

	// inserting object root
	HTREEITEM pObjMgItem;
	str.Format("Objects (%i)",pObjMg->GetCount());
	pObjMgItem=m_tree.InsertItem(TVIF_TEXT | TVIF_PARAM | TVIF_STATE  /* nMask*/, 
				str /* lpszItem*/, 
				0 /* nImage */, 
				0 /* nSelectedImage */, 
				TVIS_BOLD  /* nState */, 
				TVIS_OVERLAYMASK | TVIS_STATEIMAGEMASK /* nStateMask */, 
				-1 /*  lParam */, 
				TVI_ROOT /* hParent */, 
				TVI_LAST /* hInsertAfter */);
	ASSERT(pObjMgItem!=NULL);

	// filling up insert structure
	pos=pObjMg->GetHeadPosition();
	while (pos!=NULL)
	{
		pObj=pObjMg->GetNext(pos);
		ASSERT_VALID(pObj);

		// inserting info
		m_tree.InsertItem(TVIF_TEXT | TVIF_PARAM /* nMask*/, 
				pObj->GetName() /* lpszItem*/, 
				0 /* nImage */, 
				0 /* nSelectedImage */, 
				0 /* nState */, 
				0 /* nStateMask */, 
				(long)pObj->GetID() /*  lParam */, 
				pObjMgItem /* hParent */, 
				TVI_LAST /* hInsertAfter */);
	}
}
