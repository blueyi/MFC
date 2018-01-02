// sampleDlg.h : header file
//

#if !defined(AFX_SAMPLEDLG_H__1A4206C7_9598_11D5_8AFA_C4F458764E3E__INCLUDED_)
#define AFX_SAMPLEDLG_H__1A4206C7_9598_11D5_8AFA_C4F458764E3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EditList.h"

/////////////////////////////////////////////////////////////////////////////

// CSampleDlg dialog
class CSampleDlg : public CDialog
{
// Construction
public:
	CSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSampleDlg)
	enum { IDD = IDD_SAMPLE_DIALOG };
	CEditList	m_cList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	enum 
	{ 
		eProduct = 0,
		eID, 
		ePrice, 
		eAmount,
		eSlider,
		eLast
	};
protected:
	void InsertEmpty( );
	void BuildList();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEDLG_H__1A4206C7_9598_11D5_8AFA_C4F458764E3E__INCLUDED_)
