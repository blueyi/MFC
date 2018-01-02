// CTreeCtrlXMLDlg.h : header file
//

#pragma once

#include "afxcmn.h"

// Use our new class CTreeCtrlXML
#include "TreeCtrlXML.h"

// CCTreeCtrlXMLDlg dialog
class CCTreeCtrlXMLDlg : public CDialog
{

// Construction
public:
	
	CCTreeCtrlXMLDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_CTREECTRLXML_DIALOG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();

	DECLARE_MESSAGE_MAP()

	CTreeCtrlXML m_demoTree;		// The tree control object
};
