class CUGSideHdg : public CWnd
{
// Construction
public:
	CUGSideHdg();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGSideHdg)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUGSideHdg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUGSideHdg)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


protected:
	
	friend CUGCtrl;
	CUGCtrl *		m_ctrl;
	CUGGridInfo *	m_GI;			//pointer to the grid information

	CUGCell			m_cell;			//general purpose cell class

	CUGDrawHint		m_drawHint;		//cell drawing hints

	long			m_bottomRow;	//the row drawn at the bottom

	int				m_isSizing;			//sizing flag
	int				m_canSize;			//sizing flag
	int				m_colOrRowSizing;	// 0 - col 1- row
	long			m_sizingColRow;		// column or row number being sized
	int				m_sizingStartSize;	// original col/row width/height
	int				m_sizingStartPos;	// original starting mouse position
	int				m_sizingStartWidth;//original side heading total width
	int				m_sizingNumRowsDown; //number of rows from top when size started

	RECT			m_focusRect;		//focus rect for column sizing option

	int GetCellRect(int *col,long *row,RECT *rect);
	int GetCellRect(int col,long row,RECT *rect);
	int GetCellFromPoint(CPoint *point,int *col,long *row,RECT *rect);

	void DrawCellsIntern(CDC *dc);

public:

	int GetSHColWidth(int col);

	//internal functions
	void Update();
	void Moved();
};

/////////////////////////////////////////////////////////////////////////////
