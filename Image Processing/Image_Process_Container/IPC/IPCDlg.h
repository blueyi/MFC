// IPCDlg.h : header file
//

#if !defined(AFX_IPCDLG_H__13C2E56D_7CFE_43F8_B565_F8B13CC8A124__INCLUDED_)
#define AFX_IPCDLG_H__13C2E56D_7CFE_43F8_B565_F8B13CC8A124__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ximage.h"
#include "DlgTools.h"
#include "DlgImageContainer.h"

/////////////////////////////////////////////////////////////////////////////
// CIPCDlg dialog

class CIPCDlg : public CDialog
{
// Construction
public:
	CIPCDlg(CWnd* pParent = NULL);	// standard constructor
	~CIPCDlg();

// Dialog Data
	//{{AFX_DATA(CIPCDlg)
	enum { IDD = IDD_IPC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int					FindType(const CString &ext);
	CString				FindExtension(const CString &name);

	//dlgs:
	CDlgTools			m_dlgTools;
	CDlgImageContainer	m_dlgImageContainer;

	HICON				m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnSelectRoi();
	afx_msg void OnShowRoi();
	afx_msg void OnDetectEdge();
	afx_msg void OnOperationNull();
	afx_msg void OnOperationBrush();
	afx_msg void OnOperationErase();
	afx_msg void OnOperationDraw();
	afx_msg void OnOperationCut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCDLG_H__13C2E56D_7CFE_43F8_B565_F8B13CC8A124__INCLUDED_)
