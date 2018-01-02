#include "stdafx.h"
#include "Work.h"

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CWorkFrm, CFrameWnd)

BEGIN_MESSAGE_MAP(CWorkFrm, CFrameWnd)
	//{{AFX_MSG_MAP(CWorkFrm)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////

CWorkFrm::CWorkFrm()
{
}

CWorkFrm::~CWorkFrm()
{
}

int CWorkFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!mView.Create(NULL,NULL,AFX_WS_DEFAULT_VIEW,CRect(0,0,0,0),this,AFX_IDW_PANE_FIRST,NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	if (!mToolBar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC)||
		!mToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      
	}

	if (!mStatusBar.Create(this) ||!mStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      
	}

	return 0;
}

BOOL CWorkFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.hMenu=NULL;
	cs.style&=~WS_MAXIMIZEBOX;
	cs.style&=~WS_THICKFRAME;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	cs.cx=1180;
	cs.cy=840;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

void CWorkFrm::OnSetFocus(CWnd* pOldWnd)
{
	mView.SetFocus();
}

BOOL CWorkFrm::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (mView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

