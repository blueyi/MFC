// ccc.cpp : implementation file
//

#include "stdafx.h"
#include "TextInStatus.h"
#include "ccc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ccc

ccc::ccc()
{
}

ccc::~ccc()
{
}


BEGIN_MESSAGE_MAP(ccc, CStatusBar)
	//{{AFX_MSG_MAP(ccc)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ccc message handlers

void ccc::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_strscrolltext.IsEmpty())
	{
		KillTimer(1);
		SetPaneText(CommandToIndex(IDS_SCROLL_PANE), "");
		return;
	}
	static UINT str_idx = 0;        //offset into string
	
	//if end of string, return to top
	if (str_idx >= (UINT) (m_strscrolltext.GetLength() / 2) - 1)
	{
		str_idx = 0;
	}
	
	//display string
	SetPaneText(CommandToIndex(IDS_SCROLL_PANE), ((LPCSTR) 
		m_strscrolltext)+str_idx); 
	
	//scroll one character
	str_idx = str_idx + 1;
	
	CStatusBar::OnTimer(nIDEvent);
}

void ccc::OnDestroy() 
{
	CStatusBar::OnDestroy();
	
	KillTimer(1);
	
}

void ccc::startdisplay(void) 
{
	//set text for scrolling
	m_strscrolltext = "   hello! world.   ";
		
	//to make it circular scroll
	m_strscrolltext += m_strscrolltext;
	
	KillTimer(1);
	VERIFY(SetTimer(1, 200, NULL) != 0);    //timer
}

