#if !defined(AFX_MYFADE_H__0544A91C_CD25_4C1E_AD5D_13D4652522E7__INCLUDED_)
#define AFX_MYFADE_H__0544A91C_CD25_4C1E_AD5D_13D4652522E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFade.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFade window

class CMyFade : public CWnd
{
// Construction
public:
	CMyFade(CWnd*		pParentWnd);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFade)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	HBITMAP CopyScreenToBitmap(LPRECT lpRect);
	CWnd*		m_pWndLock;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hNewBitmap;
	static void FadeScreen(CWnd *pParent);
	virtual ~CMyFade();

	// Generated message map functions
protected:
	void OnDraw(CDC* pDC);
	//{{AFX_MSG(CMyFade)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
public:
	HBITMAP FadeBitmap(HBITMAP hBmp, double dfTrans=100);
	 BOOL Create(CWnd* pParent, CRect rc);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFadeWnd)
public:
	//}}AFX_VIRTUAL
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFADE_H__0544A91C_CD25_4C1E_AD5D_13D4652522E7__INCLUDED_)


