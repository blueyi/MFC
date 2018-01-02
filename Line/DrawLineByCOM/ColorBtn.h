#if !defined(AFX_COLORBUTTIN_H__1E43DD81_D920_11D1_A1F0_0000E8D50680__INCLUDED_)
#define AFX_COLORBUTTIN_H__1E43DD81_D920_11D1_A1F0_0000E8D50680__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ColorBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{
// Construction
public:
	CColorButton();

// Attributes
public:
	COLORREF	color;
	void SetColor(COLORREF clr)	{ color = clr; Invalidate(); } 
	COLORREF GetColor()			{ return color; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorButton)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBUTTIN_H__1E43DD81_D920_11D1_A1F0_0000E8D50680__INCLUDED_)
