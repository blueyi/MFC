// PageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageDlg dialog

class CPageDlg : public CDialog
{
// Construction
public:
	CString ToSafeName (LPCTSTR lpszName);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void UpdateOk ();
	CPageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageDlg)
	enum { IDD = IDD_DIALOG_PAGE };
	CEdit	m_ctrlClass;
	CButton	m_ok;
	CString	m_caption;
	CString	m_class;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bClassChanged;
	CToolTipCtrl m_tooltip;
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CPageDlg)
	afx_msg void OnChangeEditCaption();
	afx_msg void OnChangeEditClass();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
