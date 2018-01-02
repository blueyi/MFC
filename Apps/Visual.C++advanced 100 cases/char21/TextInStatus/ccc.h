#if !defined(AFX_CCC_H__9E913167_E950_11D4_AFB3_0050BABF4197__INCLUDED_)
#define AFX_CCC_H__9E913167_E950_11D4_AFB3_0050BABF4197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ccc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ccc window

class ccc : public CStatusBar
{
// Construction
public:
	ccc();

// Attributes
public:

	CString m_strscrolltext; 
	void startdisplay(void);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ccc)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ccc();

	// Generated message map functions
protected:
	//{{AFX_MSG(ccc)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCC_H__9E913167_E950_11D4_AFB3_0050BABF4197__INCLUDED_)
