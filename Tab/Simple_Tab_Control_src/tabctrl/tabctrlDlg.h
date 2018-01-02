// tabctrlDlg.h : header file
//

#pragma once
#include "ibtabctrl.h"
#include "ppone.h"
#include "pptwo.h"
#include "ppthree.h"

// CtabctrlDlg dialog
class CtabctrlDlg : public CDialog
{
// Construction
public:
	CtabctrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TABCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CPPOne m_oPPOne;
	CPPTwo m_oPPTwo;
	CPPThree m_oPPThree;
	CIbTabCtrl m_ctrlTabV;
	afx_msg void OnBnClickedButtonRp1();
	afx_msg void OnBnClickedButtonRp2();
	afx_msg void OnBnClickedButtonRp3();
};
