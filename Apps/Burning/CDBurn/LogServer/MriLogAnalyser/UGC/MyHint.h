#pragma once
//alignment defines
#define UG_ALIGNLEFT		1
#define UG_ALIGNRIGHT		2
#define UG_ALIGNCENTER		4
#define UG_ALIGNTOP			8
#define UG_ALIGNBOTTOM		16
#define UG_ALIGNVCENTER		32

//common return codes  - error and warning codes are positive values
#define UG_SUCCESS			0
#define UG_ERROR			1
#define UG_NA				-1

////////////////////////////////////////
class CMyHint : public CWnd
{
// Construction
public:
	CMyHint();

// Attributes
public:

// Operations
public:

	BOOL Create(CWnd* pParentWnd, HBRUSH hbrBackground=NULL);
	// --- In  :	pParentWnd		-	pointer to parent window
	//				hbrBackground	-	brush to be used to fill background
	// --- Out : 
	// --- Returns:	TRUE if item tip window was successfully created, or FALSE 
	//				otherwise
	// --- Effect : creates item tip window

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyHint)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyHint();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyHint)
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	CString GetMaxLenString(LPCTSTR string);
	void SetLineNum(int nNum);

//	CMap1 *			m_ctrl;		//pointer to the main class
	CString			m_text;
	COLORREF		m_textColor;
	COLORREF		m_backColor;
	int				m_windowAlign;
	int				m_textAlign;
	CFont *			m_hFont;
	int				m_fontHeight, m_nFixedFontHeight;


	int	SetWindowAlign(int align);
	int SetTextAlign(int align);
	int SetTextColor(COLORREF color);
	int SetBackColor(COLORREF color);
	int SetFont(CFont *font);

	int SetText(LPCTSTR string,int update);
	int MoveHintWindow(int x,int y,int width);

	int Hide();
	int Show();

	int m_nPrevX, m_nPrevY, m_nX, m_nY;

};

/////////////////////////////////////////////////////////////////////////////
