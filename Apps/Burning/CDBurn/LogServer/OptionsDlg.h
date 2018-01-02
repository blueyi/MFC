#if !defined(AFX_OPTIONSDLG_H__8FED9AC3_3A0B_46E7_B7C2_8E235C421693__INCLUDED_)
#define AFX_OPTIONSDLG_H__8FED9AC3_3A0B_46E7_B7C2_8E235C421693__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

class COptionsDlg : public CDialog
{
// Construction
public:
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_DLG_OPTIONS };
	CString	m_sWorkDirectory;
	BOOL	m_bScanParams;
	BOOL	m_bMagnetTemp;
	BOOL	m_bRfAmp;
	BOOL	m_bGradientAmp;
	BOOL	m_bGradientPower;
	BOOL	m_bShimAmp;
	BOOL	m_bSpectrometer;
	BOOL	m_bSIU;
	BOOL	m_bGating;
	BOOL	m_bPatientTable;
	BOOL	m_bInformation;
	UINT	m_iPermittedLogFileNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	afx_msg void OnBtnWorkDirectory();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetOptionsToDlgItems();
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__8FED9AC3_3A0B_46E7_B7C2_8E235C421693__INCLUDED_)
