// ComboToolBar.cpp: implementation of the CComboToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Xx.h"
#include "ComboToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define dxAdditional 64
#define dxSeparator 8

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CComboToolBar, CToolBar)
	//{{AFX_MSG_MAP(CComboToolBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CComboToolBar::CComboToolBar(UINT nIDButton)
{
	m_nIDButton = nIDButton;
}

CComboToolBar::~CComboToolBar()
{

}

int CComboToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_combo.Create(_T("MultiColumnComboBox"), _T(""), WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, NULL);

	return 0;
}

void CComboToolBar::InitCombo()
{
	// Call this function after LoadToolBar
	int nIndex  = CommandToIndex(m_nIDButton);
	if (nIndex >= 0)
	{
		CRect rect; 
		 GetItemRect(nIndex, &rect);
		m_combo.MoveWindow(rect.right + dxSeparator, rect.top, rect.Width() + dxAdditional, rect.Height());
	}
}

void CComboToolBar::OnSize(UINT nType, int cx, int cy) 
{
	CToolBar::OnSize(nType, cx, cy);
	
	InitCombo();
	
}
 
CSize CComboToolBar::CalcDynamicLayout( int nLength, DWORD dwMode )
{
	CSize rSize = CToolBar::CalcDynamicLayout(nLength, dwMode );
	rSize.cx += dxAdditional + 4 * dxSeparator;
	return rSize;
}
