#if !defined(AFX_SLIDERITEM_H__DF857764_B505_47F4_A6D1_661119D549EB__INCLUDED_)
#define AFX_SLIDERITEM_H__DF857764_B505_47F4_A6D1_661119D549EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SliderItem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSliderItem window

class CSliderItem : public CSliderCtrl
{
// Construction
public:
	CSliderItem(int nItem, int nSubItem);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliderItem)
	public:
	virtual void OnFinalRelease();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSliderItem();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSliderItem)
	afx_msg void OnNcDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	int m_nSubItem;
	int m_nItem;
	BOOL m_bVK_ESCAPE;
	//{{AFX_MSG(CComboItem)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSliderItem)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDERITEM_H__DF857764_B505_47F4_A6D1_661119D549EB__INCLUDED_)
