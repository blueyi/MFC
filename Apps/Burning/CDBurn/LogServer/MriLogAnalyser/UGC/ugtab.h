#define UTABSCROLLID 100

#define UTMAXTABS	64


class CUGTab : public CWnd
{
// Construction
public:
	CUGTab();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGTab)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUGTab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUGTab)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	CString		m_tabStrings[UTMAXTABS];
	int			m_tabWidths[UTMAXTABS];
	int			m_tabIDs[UTMAXTABS];
	COLORREF	m_tabTextColors[UTMAXTABS];
	COLORREF	m_tabBackColors[UTMAXTABS];

	int		m_tabCount;
	int		m_tabOffset;
	int		m_maxTabOffset;

	int		m_currentTab;

	int		m_scrollWidth;

	CScrollBar m_scroll;	

	CFont	m_defFont;
	CFont	*m_font;

	int		m_resizeReady;
	int		m_resizeInProgress;

	friend CUGCtrl;
	CUGCtrl* m_ctrl;
	CUGGridInfo *	m_GI;			//pointer to the grid information

	int		m_bestWidth;

	int GetTabItemWidth(LPCTSTR string);

public:

	int AddTab(LPCTSTR string,long ID);
	int InsertTab(int pos,LPCTSTR string,long ID);
	int DeleteTab(long ID);

	int SetCurrentTab(long ID);
	int GetCurrentTab();

	int GetTabCount();

	int AdjustScrollBars();

	int SetTabBackColor(long ID,COLORREF color);
	int SetTabTextColor(long ID,COLORREF color);
	int SetTabFont(CFont *font);

public:

	void OnTabLClicked(long ID);
	void OnTabRClicked(long ID);
	void OnTabDClicked(long ID);
	void OnTabSizing(int width);

	void Update();
};

/////////////////////////////////////////////////////////////////////////////
