// LogoToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "BigSee.h"
#include "LogoToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogoToolBar

CLogoToolBar::CLogoToolBar()
{
}

CLogoToolBar::~CLogoToolBar()
{
}


BEGIN_MESSAGE_MAP(CLogoToolBar, CToolBar)//CToolBarCtrl
	//{{AFX_MSG_MAP(CLogoToolBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogoToolBar message handlers

int CLogoToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_Logo.CreateLogo(this,IDB_LOGO_BITMAP,-1);
	return 0;
}

void CLogoToolBar::OnSize(UINT nType, int cx, int cy) 
{
	CToolBar::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_Logo.MoveLogo(cx,cy);
}
