#if !defined(AFX_PAGEWND_H__6E349275_0119_11D2_87D0_00C0DFA97DA3__INCLUDED_)
#define AFX_PAGEWND_H__6E349275_0119_11D2_87D0_00C0DFA97DA3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PageWnd.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
//utility struct to map invalid area in page row, col coords

typedef struct  {
 int startrow;
 int startcol;
 int endrow;
 int endcol;
 int startwidth;
 int endwidth;
 int startheight;
 int endheight;
}BOUND;


/////////////////////////////////////////////////////////////////////////////
//
#define CELL_CHARSIZE 64

class CCell  {
  public:
    CCell()  {
      m_pcontents =  0;       

      m_fclr   = ::GetSysColor(COLOR_WINDOWTEXT);
      m_falign = TA_RIGHT;

      m_bClrIdx = 0;
      m_fontIdx = 0;
    }

    virtual ~CCell() {  if(m_pcontents) delete []m_pcontents; };

    short       m_falign;    //horz align
    char*       m_pcontents;
    COLORREF    m_fclr;      //text clr
    int         m_bClrIdx;   //bkgnd brush index in TPage m_pBrushList
    int         m_fontIdx;   //index of font in TPage  m_pFontList
};


/////////////////////////////////////////////////////////////////////////////
//

class CScrollData
{
  public:
    CScrollData() {XPos = 0; YPos = 0; XRange = 0; YRange = 0; XUnit = 0; YUnit = 0;}
    virtual ~CScrollData(){};

  public:
    int XPos, YPos;
    int XPage, YPage;
    int XRange, YRange;
    int XUnit, YUnit;
};



class CPageEdit;
/////////////////////////////////////////////////////////////////////////////
// CPageWnd window

class CPageWnd : public CWnd
{
// Construction
public:
	CPageWnd(int nrows = 10, int ncols = 10);

// Attributes
public:


protected:
  COLORREF        BkgndColor;
  int             m_ncols, m_nrows, m_ncells;
  int             m_stdwidth, m_stdheight;
  SIZE            m_PageSize;
  CScrollData*    m_pScrollData;
  CCell**         m_pCells;
  int*            m_height;
  int*            m_width;
  bool            m_bCapture;
  bool            m_bGrid;
  bool            m_bReadOnly;
  CRect           m_EditRect;
  
  int             m_rowEdit, m_colEdit, m_rowEditEx, m_colEditEx;
  int             m_idx, m_ex_x;
  int             m_left_limit, m_right_limit;

  char            m_charClip;

  CFont*          m_pDefFont;
  CFont*          m_pDefFontBold;
  CPen*           m_pGridPen;
  
  CPageEdit*      m_pEditCtrl;
  HCURSOR         m_CurSize, m_CurArrow;

  //font and cell bkgnd list
  CArray<CFont*, CFont*>    *m_pFontList;
  CArray<CBrush*, CBrush*>  *m_pBrushList;

  virtual int      IsSplitLine(int x, int y);
  
  virtual int      HeightInPixels(int h);
  virtual void     Init();

  virtual void     GetCellPosition(int idx, int& row, int& col);
  virtual int      GetCellIndex(int row, int col);
  virtual CCell*   GetCell(int cellIdx);
  virtual CCell*   GetCell(int row, int col);

  virtual void     Paint(CDC& dc, BOOL erase, CRect& rect);
  virtual void     Draw_ZeroZero(CDC& dc, CRect& rect);
  virtual void     Draw_ZeroRow(CDC& dc, BOUND& bound);
  virtual void     Draw_ZeroCol(CDC& dc, BOUND& bound);
  virtual void     Draw_Contents(CDC& dc, BOUND& bound);
  virtual void     Draw_Grid(CDC& dc, BOUND& bound);
  virtual void     CellEntry(CDC& dc, int row, int col, CRect cellRect);
  
  virtual void     AdjustScrollBars();
  virtual void     MarkActiveCell(bool fprev, bool fnext);
  virtual void     MarkHeader(bool mark);

// Operations
public:
  virtual void     EditAccept(bool accept);
  virtual COLORREF GetCellColor(int row, int col);
  virtual int      SetCellColor(int row, int col, COLORREF clr);
  virtual CBrush*  GetCellBrush(int row, int col);
  
  virtual bool     SetCellText(int row, int col, char* szText);
  virtual int      GetCellText(int row, int col, char* szText, int cb);
  virtual char*    GetCellTextPtr(int row, int col);

  virtual int      GetRowCount() {return m_nrows; }
  virtual int      GetColCount() {return m_ncols;}

  virtual HFONT    GetCellFontHandle(int row, int col);
  virtual CFont*   GetCellFont(int row, int col);
  virtual int      SetCellFont(int row, int col, HFONT hfont);
  virtual int      SetCellFont(int row, int col, int index);
  virtual int      SetCellFont(int row, int col, LOGFONT* plf);

  virtual void     SetCellAlign(int row, int col, short fAlign);
  virtual short    GetCellAlign(int row, int col);

  virtual COLORREF GetCellTextColor(int row, int col);
  virtual void     SetCellTextColor(int row, int col, COLORREF clr);

  virtual CFont*   GetDefaultFont() {return m_pDefFont;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPageWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPageWnd)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPageEdit window

class CPageEdit : public CEdit
{
// Construction
public:
	CPageEdit();

// Attributes
protected:
  CRect     m_rcClient;
  CPageWnd* m_pPage;
  int       m_charWidth;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPageEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPageEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEWND_H__6E349275_0119_11D2_87D0_00C0DFA97DA3__INCLUDED_)
