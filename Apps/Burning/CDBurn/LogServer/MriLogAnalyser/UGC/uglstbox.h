class CUGLstBox : public CListBox
{
// Construction
public:
	CUGLstBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGLstBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUGLstBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUGLstBox)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	//pointer to the main class
	CUGCtrl *	m_ctrl;
	int			m_HasFocus;
	int		*	m_col;
	long	*   m_row;
	BOOL		m_selected;

	int			m_cellTypeId;

private:
	void Select();

};

/////////////////////////////////////////////////////////////////////////////
