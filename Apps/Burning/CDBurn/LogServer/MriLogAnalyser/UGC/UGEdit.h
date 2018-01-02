class CUGEdit : public CEdit
{
// Construction
public:
	CUGEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGEdit)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUGEdit();


	// Generated message map functions
protected:
	//{{AFX_MSG(CUGEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnUpdate();
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


	BOOL m_cancel;
	BOOL m_continueFlag;
	int  m_continueCol;
	int  m_continueRow;

	UINT m_lastKey;

	BOOL m_autoSize;

	int m_origHeight;
	int m_currentHeight;

	void CalcEditRect();

public:

	CUGCtrl * m_ctrl;

	BOOL SetAutoSize(BOOL state);
	
	UINT  GetLastKey();
};

/////////////////////////////////////////////////////////////////////////////
