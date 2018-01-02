// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "RTDemo.h"
#include "RTDemoDoc.h"
#include "ChildFrm.h"
#include "RTDemoView.h"
#include "RTForm.h"
#include "RTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_COMMAND(ID_VIEW_RESTORETIMER, OnViewRestoretimer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESTORETIMER, OnUpdateViewRestoretimer)
	ON_COMMAND(ID_VIEW_KILLTIMER, OnViewKilltimer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_KILLTIMER, OnUpdateViewKilltimer)
	ON_COMMAND(ID_EDIT_INSERT, OnEditInsert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INSERT, OnUpdateEditInsert)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_EDIT_MODIFY, OnEditModify)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MODIFY, OnUpdateEditModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	BOOL bSuccess;
	CRect rect;
	GetClientRect(&rect);
	CSize size  = rect.Size();
	size.cy = size.cy * 2 / 3;

	if (!(bSuccess = m_wndSplitter.CreateStatic(this, 2, 1, WS_CHILD|WS_VISIBLE, AFX_IDW_PANE_FIRST)))
	{
		TRACE("Failed to CreateStaticSplitter\n");
		return FALSE;
	}
                    
    if (!(bSuccess &= m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CRTDemoView), size, pContext)))
	{
		TRACE("Failed to create base pane\n");
		return FALSE;
	}  

	if (!(bSuccess &= m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CRTForm), size, pContext)))
	{
		TRACE("Failed to create base pane\n");
		return FALSE;
	}  

   	m_wndSplitter.SetActivePane(1, 0);

	return TRUE;
}

void CChildFrame::OnViewRestoretimer() 
{
	((CRTDemoView*)m_wndSplitter.GetPane(0, 0))->RTRestoreTimer();
}

void CChildFrame::OnUpdateViewRestoretimer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(((CRTDemoView*)m_wndSplitter.GetPane(0, 0))->m_bTimerOn == FALSE);
}

void CChildFrame::OnViewKilltimer() 
{
	((CRTDemoView*)m_wndSplitter.GetPane(0, 0))->RTKillTimer();
}

void CChildFrame::OnUpdateViewKilltimer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(((CRTDemoView*)m_wndSplitter.GetPane(0, 0))->m_bTimerOn == TRUE);
}

void CChildFrame::OnEditInsert() 
{
	CInsert Insert(this);
	Insert.DoModal();
}

void CChildFrame::OnUpdateEditInsert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CChildFrame::OnEditDelete() 
{
	CRTDlg RtDlg(this);
	RtDlg.DoModal();
}

void CChildFrame::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	if (((CRTDemoView*)m_wndSplitter.GetPane(0, 0))->m_Graph.m_LineArray.GetSize() > 0)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

void CChildFrame::OnEditModify() 
{
	CModify MdDlg(this);
	MdDlg.DoModal();
}

void CChildFrame::OnUpdateEditModify(CCmdUI* pCmdUI) 
{
	if (((CRTDemoView*)m_wndSplitter.GetPane(0, 0))->m_Graph.m_LineArray.GetSize() > 0)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}
