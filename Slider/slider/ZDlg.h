// ZDlg.h : header file
//

#if !defined(AFX_ZDLG_H__11E86686_263F_11DB_ACFE_0050BA012D9B__INCLUDED_)
#define AFX_ZDLG_H__11E86686_263F_11DB_ACFE_0050BA012D9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ZDlg dialog

#include "lib\SliderBoth.h"

class ZDlg : public CDialog
{
// Construction
public:
	ZDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(ZDlg)
	enum { IDD = IDD_STEP_DIALOG };
	CStatic	sta_Info;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(ZDlg)
	virtual BOOL OnInitDialog();
	afx_msg void On_IDOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	SliderBoth slider_Left,slider_Top,slider_Right,slider_Bottom;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDLG_H__11E86686_263F_11DB_ACFE_0050BA012D9B__INCLUDED_)
