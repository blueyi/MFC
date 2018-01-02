// ButtonSubDlg.h : header file
//

#if !defined(AFX_BUTTONSUBDLG_H__262FC0A7_7925_41FA_B27F_3676317F23B0__INCLUDED_)
#define AFX_BUTTONSUBDLG_H__262FC0A7_7925_41FA_B27F_3676317F23B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////// ////////////////////////////////////////////////
// CButtonSubDlg dialog
#include "MyButton.h"
class CButtonSubDlg : public CDialog
{
// Construction
public:
	CButtonSubDlg(CWnd* pParent = NULL);	// standard constructor
	CMyButton *but;
	CRgn cRgn;
	int idcount;
	CClientDC *pdc;
	CPoint spoint,epoint;
// Dialog Data
	//{{AFX_DATA(CButtonSubDlg)
	enum { IDD = IDD_BUTTONSUB_DIALOG };
	CMyButton	m_bt;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonSubDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CButtonSubDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONSUBDLG_H__262FC0A7_7925_41FA_B27F_3676317F23B0__INCLUDED_)
