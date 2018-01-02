// AlphaBlendingDlg.h : header file
//

#if !defined(AFX_ALPHABLENDINGDLG_H__3698D8ED_3DD7_41D2_8D6A_269EE2CB3BCF__INCLUDED_)
#define AFX_ALPHABLENDINGDLG_H__3698D8ED_3DD7_41D2_8D6A_269EE2CB3BCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAlphaBlendingDlg dialog
#include "Canvas.h"
class CAlphaBlendingDlg : public CDialog
{
// Construction
public:
	CAlphaBlendingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAlphaBlendingDlg)
	enum { IDD = IDD_ALPHABLENDING_DIALOG };
	CSliderCtrl	m_TransSlider;
	CCanvas	m_stCanvas;
	CString	m_editAlpha;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlphaBlendingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAlphaBlendingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonApply();
	afx_msg void OnAlpha();
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAnimate();
	afx_msg void OnStop();
	afx_msg void OnButtonMove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALPHABLENDINGDLG_H__3698D8ED_3DD7_41D2_8D6A_269EE2CB3BCF__INCLUDED_)
