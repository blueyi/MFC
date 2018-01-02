#if !defined(AFX_BMPBKGNDDLG_H__F18D507B_20D5_4AF1_935C_5016CE6B2399__INCLUDED_)
#define AFX_BMPBKGNDDLG_H__F18D507B_20D5_4AF1_935C_5016CE6B2399__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpBkgndDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBmpBkgndDlg dialog

class CBmpBkgndDlg : public CDialog
{
// Construction
public:
	CBmpBkgndDlg(CWnd* pParent = NULL);   // standard constructor
	~CBmpBkgndDlg();
// Dialog Data
	//{{AFX_DATA(CBmpBkgndDlg)
	enum { IDD = IDD_BMP_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpBkgndDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_HollowBrush;
	CBitmap m_BkGndBmp;

	// Generated message map functions
	//{{AFX_MSG(CBmpBkgndDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPBKGNDDLG_H__F18D507B_20D5_4AF1_935C_5016CE6B2399__INCLUDED_)
