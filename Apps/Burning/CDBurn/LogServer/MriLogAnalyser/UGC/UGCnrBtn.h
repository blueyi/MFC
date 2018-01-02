class CUGCnrBtn : public CWnd
{
// Construction
public:
	CUGCnrBtn();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGCnrBtn)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUGCnrBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUGCnrBtn)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:


	// internal information
	friend CUGCtrl;
	CUGCtrl		*	m_ctrl;		//pointer to the main class
	CUGGridInfo *	m_GI;		//pointer to the grid information

	int				m_isSizing;		//sizing flag
	int				m_canSize;		//sizing flag
	int				m_sizingHeight;	//sizing flag
	int				m_sizingWidth;	//sizing flag
	
	//internal functions
	void Update();
	void Moved();
};

/////////////////////////////////////////////////////////////////////////////
