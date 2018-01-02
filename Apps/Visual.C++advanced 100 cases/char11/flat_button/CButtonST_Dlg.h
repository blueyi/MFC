// CButtonST_Dlg.h : header file
//

#if !defined(AFX_CBUTTONST_DLG_H__E0078DA7_0782_11D2_8E55_9E80D52A2535__INCLUDED_)
#define AFX_CBUTTONST_DLG_H__E0078DA7_0782_11D2_8E55_9E80D52A2535__INCLUDED_

#include "BtnST.h"	// Added by ClassView
#include "AboutDlg.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CButtonST_Dlg dialog

class CButtonST_Dlg : public CDialog
{
// Construction
public:
	CButtonST_Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CButtonST_Dlg)
	enum { IDD = IDD_CBUTTONST_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonST_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CButtonST_Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CButtonST m_btnAbout16;
	CButtonST m_btnExit16;
	CButtonST m_btnScrew16;
	CButtonST m_btnRight16;
	CButtonST m_btnLeft16;
	CButtonST m_btnQuestion16;
	CButtonST m_btnText16;
	CButtonST m_btnView16;
	CButtonST m_btnExplore16;
	CButtonST m_btnCancelBor16;
	CButtonST m_btnOkBor16;
	CButtonST m_btnCDGold256;
	CButtonST m_btnCancel256;
	CButtonST m_btnOk256;
	CButtonST m_btnLamp256;
	CButtonST m_btnHand256;
	CButtonST m_btnOk16;
	CButtonST m_btnCancel16;
	CButtonST m_btnZip256;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBUTTONST_DLG_H__E0078DA7_0782_11D2_8E55_9E80D52A2535__INCLUDED_)
