// ZDlg.h : header file
//

#if !defined(AFX_ZDLG_H__11E86686_263F_11DB_ACFE_0050BA012D9B__INCLUDED_)
#define AFX_ZDLG_H__11E86686_263F_11DB_ACFE_0050BA012D9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

#include "lib\ButtonMine.h"

class ZDlg : public CDialog
{
// Construction
public:
	ZDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(ZDlg)
	enum { IDD = IDD_STEP_DIALOG };
	CStatic	sta_Inf;
	ButtonMine	btn_Jpg;
	ButtonMine	btn_Gif;
	ButtonMine	btn_Bmp;
	ButtonMine	btn_Resize1;
	ButtonMine	btn_Resize0;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(ZDlg)
	virtual BOOL OnInitDialog();
	afx_msg void On_IDOK();
	afx_msg void On_Enable();
	afx_msg void On_BtnResSunken();
	afx_msg void On_BtnResRaised();
	afx_msg void On_BtnWeaker();
	afx_msg void On_BtnFocus();
	afx_msg void On_BtnBmp();
	afx_msg void On_BtnGif();
	afx_msg void On_BtnJpg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void P_DispInf(CString csBtn);
	int i_MessageCount;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDLG_H__11E86686_263F_11DB_ACFE_0050BA012D9B__INCLUDED_)
