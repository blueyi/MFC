#if !defined(AFX_WNDEX_H__374CA169_DF66_4A52_982A_1D71E78D2FD7__INCLUDED_)
#define AFX_WNDEX_H__374CA169_DF66_4A52_982A_1D71E78D2FD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWndEx window

class CWndEx : public CWnd
{
// Construction
public:
	BOOL CreateEx(DWORD dwExStyle,CString strWindowName,DWORD dwStyle,CRect rect,CWnd* pwndParent);
	BOOL Create(CString strWindowName,DWORD dwStyle,CRect rect,CWnd* pwndParent);

	BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

public:
	CWndEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWndEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDEX_H__374CA169_DF66_4A52_982A_1D71E78D2FD7__INCLUDED_)
