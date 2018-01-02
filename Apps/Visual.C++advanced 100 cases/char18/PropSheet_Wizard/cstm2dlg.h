// cstm2dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog

class CCustom2Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom2Dlg();
	virtual BOOL OnDismiss();

	virtual BOOL PreTranslateMessage (MSG* pMsg);

// Dialog Data
	//{{AFX_DATA(CCustom2Dlg)
	enum { IDD = IDD_CUSTOM2 };
	CStatic	m_frame;
	CListCtrl	m_pages;
	int		m_pageSize;
	CString	m_title;
	//}}AFX_DATA

	CToolBarCtrl m_toolBar;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedListPages(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPageNew();
	afx_msg void OnPageModify();
	afx_msg void OnPageDelete();
	afx_msg void OnPageMoveUp();
	afx_msg void OnPageMoveDown();
	afx_msg void OnPaint();
	afx_msg void OnChangeSize();
	afx_msg void OnDblclkListPages(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	BOOL OnToolTipText(UINT nId, NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
protected:
	CToolTipCtrl m_ctrlTooltip;
private:
	void UpdateControls ();
};
