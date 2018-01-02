// SampleStatic.h : header file
//

#ifndef SAMPLESTATIC_H
#define SAMPLESTATIC_H

/////////////////////////////////////////////////////////////////////////////
// CSampleStatic window

class CSampleStatic : public CStatic
{
// Construction
public:
	CSampleStatic();
	virtual ~CSampleStatic();

// Attributes
public:
	void SetBackgroundColor(COLORREF rgb, BOOL bRedraw = TRUE);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleStatic)
	//}}AFX_VIRTUAL

// Implementation
protected:
	COLORREF	m_rgbBackground;
	CBrush *	m_pBrush;

	// Generated message map functions
protected:
	//{{AFX_MSG(CSampleStatic)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //SAMPLESTATIC_H
