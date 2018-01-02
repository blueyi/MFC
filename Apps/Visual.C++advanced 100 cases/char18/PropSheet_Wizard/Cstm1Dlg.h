// cstm1dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog

class CCustom1Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom1Dlg();
	virtual BOOL OnDismiss();

	virtual BOOL PreTranslateMessage (MSG* pMsg);

// Dialog Data
	//{{AFX_DATA(CCustom1Dlg)
	enum { IDD = IDD_CUSTOM1 };
	CButton	m_ctrlStandardButtons;
	CButton	m_ctrlStartOnTaskBar;
	CButton	m_ctrlSendToTaskBar;
	CButton	m_ctrlMinimizeBox;
	BOOL	m_aboutBox;
	BOOL	m_bitmapPages;
	BOOL	m_minimizeBox;
	BOOL	m_sendToTaskBar;
	BOOL	m_startOnTaskBar;
	int		m_modal;
	int		m_mfcDLL;
	BOOL	m_tooltips;
	BOOL	m_standardButtons;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateNeeded();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CToolTipCtrl m_ctrlTooltip;
private:
	void UpdateControls ();
};
