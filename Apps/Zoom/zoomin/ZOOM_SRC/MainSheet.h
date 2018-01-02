// MainSheet.h : header file
//

class CPropertyDlg;

class CMainSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMainSheet)
	CPropertyDlg* m_propDlg;
	CPropertyPage* m_aboutDlg;

public:
	CMainSheet(CWnd* pParentWnd);
	virtual ~CMainSheet();

	//{{AFX_VIRTUAL(CMainSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CMainSheet)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
