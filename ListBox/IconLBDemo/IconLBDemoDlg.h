// IconLBDemoDlg.h : header file
//

#if !defined(AFX_ICONLBDEMODLG_H__DA462427_5FCA_11D5_BBEE_0050BAD90EEA__INCLUDED_)
#define AFX_ICONLBDEMODLG_H__DA462427_5FCA_11D5_BBEE_0050BAD90EEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "IconListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CIconLBDemoDlg dialog

class CIconLBDemoDlg : public CDialog
{
// Construction
public:
	CIconLBDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIconLBDemoDlg)
	enum { IDD = IDD_ICONLBDEMO_DIALOG };
	CButton	m_ChangeIcon;
	CIconListBox m_ListBox;
	CString	m_Str;
	int		m_Img;
	BOOL	m_Check;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconLBDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CImageList m_imgNormal;
	void InitImageLists();

	// Generated message map functions
	//{{AFX_MSG(CIconLBDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnInsert();
	afx_msg void OnChangeicon();
	afx_msg void OnCheckImageList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONLBDEMODLG_H__DA462427_5FCA_11D5_BBEE_0050BAD90EEA__INCLUDED_)
