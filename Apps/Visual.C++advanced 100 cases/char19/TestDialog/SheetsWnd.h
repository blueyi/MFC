/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/19/98 11:33:04 AM
  Comments: SheetsWnd.h : header file
 ************************************/

#if !defined(AFX_SHEETSWND_H__67869EBF_1ED0_11D2_999A_00400561FB65__INCLUDED_)
#define AFX_SHEETSWND_H__67869EBF_1ED0_11D2_999A_00400561FB65__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// 
//

/////////////////////////////////////////////////////////////////////////////
// CSheetsWnd window

#define IDTHIS  0x01000
#define IDBTNS  0

class CSheetsWnd : public CWnd
{
// Construction
public:
	CSheetsWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheetsWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual CWnd* GetViewFromPoint(CPoint point);
	virtual void Draw(CDC* pDC);
	virtual CWnd* GetActiveView();
	virtual CString GetViewTitle(CWnd* pView);
	virtual CWnd* GetNextView();
	virtual CWnd* GetFirstView();
	static CSheetsWnd* GetWndSheet(HWND hWndParent);
	static void Resize(HWND hWndParent);
	static void RestoreWndProc(HWND hWndParent);
	WNDPROC m_wndProcParent;
	virtual BOOL Attach(CWnd * pWndParent, COLORREF rgbBackground = GetSysColor(COLOR_3DFACE));
	virtual ~CSheetsWnd();

	// Generated message map functions
protected:
	virtual CRect GetRect(CWnd* pWndParent);
	CRect CSheetsWnd::GetRect(HWND hWndParent);
	//{{AFX_MSG(CSheetsWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nHorzScroll, m_nMaxHorzScroll;
	CFont m_font;
	CWnd* m_pViewFind;
	CScrollBar m_btns;
	CBrush m_brBackground;
	CRect m_DrawRect;
	static int m_nLastID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEETSWND_H__67869EBF_1ED0_11D2_999A_00400561FB65__INCLUDED_)
