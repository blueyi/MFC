// SplitterWndEx.cpp : implementation file   
//   

#include "stdafx.h"   
#include "CurveDrawing.h"   
#include "SplitterWndEx.h"   

#ifdef _DEBUG   
#define new DEBUG_NEW   
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;   
#endif   

/////////////////////////////////////////////////////////////////////////////   
// CSplitterWndEx   

CSplitterWndEx::CSplitterWndEx()   
{   
	m_cxSplitterGap = m_cySplitterGap = 1;//设置分割框不可见，宽度最小   
	m_cxSplitter=m_cySplitter=1;   
	//m_cxBorder = m_cyBorder = 0;   
}   

CSplitterWndEx::~CSplitterWndEx()   
{   
}   


BEGIN_MESSAGE_MAP(CSplitterWndEx, CSplitterWnd)   
	//{{AFX_MSG_MAP(CSplitterWndEx)   
	ON_WM_LBUTTONDOWN()   
	//}}AFX_MSG_MAP   
END_MESSAGE_MAP()   


/////////////////////////////////////////////////////////////////////////////   
// CSplitterWndEx message handlers   

void CSplitterWndEx::OnLButtonDown(UINT nFlags, CPoint point)    
{   
	// TODO: Add your message handler code here and/or call default   
	//将其中CSplitterWndEx::OnLButtonDown(nFlags, point);改为CWnd::OnLButtonDown(nFlags, point);这样就不会响应对分割框的移动了。   
	CWnd::OnLButtonDown(nFlags, point);   
}   