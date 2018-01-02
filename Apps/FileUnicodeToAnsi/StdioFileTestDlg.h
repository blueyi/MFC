// StdioFileTestDlg.h : header file
//

#if !defined(AFX_STDIOFILETESTDLG_H__FBBF946E_9B9A_48CD_B0B8_8635E2267E43__INCLUDED_)
#define AFX_STDIOFILETESTDLG_H__FBBF946E_9B9A_48CD_B0B8_8635E2267E43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStdioFileTestDlg dialog

class CStdioFileTestDlg : public CDialog
{
// Construction
public:
	CStdioFileTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStdioFileTestDlg)
	enum { IDD = IDD_STDIOFILETEST_DIALOG };
	CButton	m_buttonCopyAsUnicode;
	CButton	m_buttonCopyAsAnsi;
	CEdit	m_editText;
	CStatic	m_staticSizeChars;
	CStatic	m_staticIsUnicode;
	CEdit	m_editFilePath;
	CString	m_sFilePath;
	CString	m_sIsUnicode;
	CString	m_sSizeInChars;
	CComboBox	m_comboFileCodePage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStdioFileTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStdioFileTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonBrowse();
	afx_msg void OnChangeEditFile();
	afx_msg void OnButtonCopyAsAnsi();
	afx_msg void OnButtonCopyAsUnicode();
	afx_msg void OnSelChangeComboFileCharset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int		GetUserFileSelection(CString& sSelectedFile);
	void		MakeCopy(IN const bool bAsUnicode);
	void		ReadSelectedFile(IN const UINT nCodePage);

	void		AddCodePage(IN const CString& sDesc, IN const UINT nCodePage, IN const UINT nCurrentCP);
	UINT		GetSelectedCodePage();

	CMapStringToPtr	m_mapCodePageDescsToCodePages;
	CString				m_sCurrentCPDesc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDIOFILETESTDLG_H__FBBF946E_9B9A_48CD_B0B8_8635E2267E43__INCLUDED_)
