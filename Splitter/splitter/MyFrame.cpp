// MyFrame.cpp : implementation file
//

#include "stdafx.h"
#include "splitter.h"
#include "MyFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFrame

IMPLEMENT_DYNCREATE(CMyFrame, CMDIChildWnd)

CMyFrame::CMyFrame()
{
}

CMyFrame::~CMyFrame()
{
}


BEGIN_MESSAGE_MAP(CMyFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMyFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFrame message handlers
