#if !defined(AFX_TREEHELPER_H__25106690_3812_11D2_8F84_0060B0ECF89C__INCLUDED_)
#define AFX_TREEHELPER_H__25106690_3812_11D2_8F84_0060B0ECF89C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TreeHelper.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeHelper window

class CTreeHelper : public CTreeCtrl
{
// Construction
public:
	CTreeHelper(UINT nBitmapID= 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeHelper)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeHelper();

	void	ShowTree( CString* i_psPfad, LPCTSTR i_psSeparator, CWnd* pParent , CPoint* i_pPoint  );

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeHelper)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CWnd* m_pFocusWnd;
	CImageList*	m_pimagelist;
	UINT	m_nBitmapID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEHELPER_H__25106690_3812_11D2_8F84_0060B0ECF89C__INCLUDED_)
