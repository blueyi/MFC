// FadeDialog.h : header file
//

#ifndef FADEDIALOG_H
#define FADEDIALOG_H

//=============================================================================
class CFadeDialog : public CDialog
//=============================================================================
{
// Construction
public:
	CFadeDialog(UINT nId, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CFadeDialog)
	//}}AFX_DATA
	int m_nTransparency;
	int m_nStep;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFadeDialog)
protected:
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFadeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //FADEDIALOG_H
