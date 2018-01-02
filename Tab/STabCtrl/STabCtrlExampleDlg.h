#include "STabCtrl.h"
// STabCtrlExampleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSTabCtrlExampleDlg dialog

class CSTabCtrlExampleDlg : public CDialog
{
// Construction
public:
	CSTabCtrlExampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSTabCtrlExampleDlg)
	enum { IDD = IDD_STABCTRLEXAMPLE_DIALOG };
	CStatic	m_Static3;
	CStatic	m_Static2;
	CStatic	m_Static1;
	CSTabCtrl	m_TabCtrl;
	CButton m_EnableRadioCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSTabCtrlExampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSTabCtrlExampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDisable();
	afx_msg void OnEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
