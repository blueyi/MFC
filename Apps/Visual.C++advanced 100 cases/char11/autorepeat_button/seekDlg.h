// seekDlg.h : header file
//

#if !defined(AFX_SEEKDLG_H__E5CF1A07_0910_11D2_A171_000000000000__INCLUDED_)
#define AFX_SEEKDLG_H__E5CF1A07_0910_11D2_A171_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SeekButton.h"
#include "MyEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CSeekDlg dialog

class CSeekDlg : public CDialog
{
// Construction
public:
	CSeekDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSeekDlg)
	enum { IDD = IDD_SEEK_DIALOG };
	int		m_value;
	int		m_value2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeekDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	CSeekButton forwardBut, backwardBut;
	CMyEdit myEdit;
	CMyEdit myEdit2;
	// Generated message map functions
	//{{AFX_MSG(CSeekDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEEKDLG_H__E5CF1A07_0910_11D2_A171_000000000000__INCLUDED_)
