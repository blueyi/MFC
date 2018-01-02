/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// ShowWnd.h : interface of the CShowWnd class                             //
//                              CColorWnd class                            //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWWND_H__A26C391A_7022_4B68_BA6D_06B87A943DCA__INCLUDED_)
#define AFX_SHOWWND_H__A26C391A_7022_4B68_BA6D_06B87A943DCA__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShowWnd window

class CShowWnd : public CWnd
{
// Construction
public:
	CShowWnd();

// Attributes
public:
	CBitmap*	m_pImage;

// Operations
public:
	// none

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShowWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CShowWnd)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// CShowWnd window
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CColorWnd window

class CColorWnd : public CWnd
{
// Construction
public:
	CColorWnd();

// Attributes
public:
	CFont*		m_pFont;
	COLORREF	m_dwRGB;
	COLORREF	m_dwHSB;
	COLORREF	m_dwContrast1;
	COLORREF	m_dwContrast2;
	HICON		m_hIcon1;
	HICON		m_hIcon2;

// Operations
public:
	// none

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CShowWnd)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// CColorWnd window
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWWND_H__A26C391A_7022_4B68_BA6D_06B87A943DCA__INCLUDED_)
