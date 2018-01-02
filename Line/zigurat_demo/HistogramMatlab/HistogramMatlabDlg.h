// HistogramMatlabDlg.h : header file
//

#if !defined(AFX_HISTOGRAMMATLABDLG_H__74076A9A_C758_452E_B048_999BD0A491DE__INCLUDED_)
#define AFX_HISTOGRAMMATLABDLG_H__74076A9A_C758_452E_B048_999BD0A491DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHistogramMatlabDlg dialog

#include "MatlabEngine.h"

class CHistogramMatlabDlg : public CDialog
{
// Construction
public:
	CHistogramMatlabDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHistogramMatlabDlg)
	enum { IDD = IDD_HISTOGRAMMATLAB_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramMatlabDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static enum ERandType
	{
		ENormal = 1,
		EExponential = 2
	} ;

	void ShowHistogram(ERandType eType, UINT nSteps = 100);

protected:
	HICON m_hIcon;
	CMatlabEngine matlab;

	// Generated message map functions
	//{{AFX_MSG(CHistogramMatlabDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMMATLABDLG_H__74076A9A_C758_452E_B048_999BD0A491DE__INCLUDED_)
