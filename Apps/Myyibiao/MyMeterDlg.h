// MyMeterDlg.h : header file
//

#if !defined(AFX_MYMETERDLG_H__508E3492_A72E_4816_823C_A3FF870251AD__INCLUDED_)
#define AFX_MYMETERDLG_H__508E3492_A72E_4816_823C_A3FF870251AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Meter.h"
#include "HyperLink.h"
/////////////////////////////////////////////////////////////////////////////
// CMyMeterDlg dialog

class CMyMeterDlg : public CDialog
{
// Construction
public:
	CMyMeterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyMeterDlg)
	enum { IDD = IDD_MYMETER_DIALOG };
	CMeter	m_myMeter;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMeterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyMeterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMETERDLG_H__508E3492_A72E_4816_823C_A3FF870251AD__INCLUDED_)
