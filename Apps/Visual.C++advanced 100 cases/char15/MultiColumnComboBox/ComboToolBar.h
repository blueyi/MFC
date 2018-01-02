// ComboToolBar.h: interface for the CComboToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMBOTOOLBAR_H__3B54149A_61A8_11D2_86B6_0040055C08D9__INCLUDED_)
#define AFX_COMBOTOOLBAR_H__3B54149A_61A8_11D2_86B6_0040055C08D9__INCLUDED_

#include "MultiColumnComboBox.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CComboToolBar : public CToolBar  
{
public:
	UINT m_nIDButton;
	virtual void InitCombo();
	CMultiColumnComboBox m_combo;
	CComboToolBar(UINT nIDButton);
	virtual ~CComboToolBar();
	virtual CSize CalcDynamicLayout( int nLength, DWORD dwMode );
	//{{AFX_VIRTUAL(CComboToolBar)
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CComboToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_COMBOTOOLBAR_H__3B54149A_61A8_11D2_86B6_0040055C08D9__INCLUDED_)
