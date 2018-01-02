#if !defined(AFX_CANVAS_H__402979D8_8268_47A4_8E23_32ACD6EC878E__INCLUDED_)
#define AFX_CANVAS_H__402979D8_8268_47A4_8E23_32ACD6EC878E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Canvas.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCanvas window
class CPlayColor;
class CMemDC;

class CCanvas : public CStatic
{
// Construction
public:
	CCanvas();
	static UINT WINAPI threadFunction(LPVOID pParam);
// Attributes
public:
	int mAlpha;
	int mFade;
// Operations
public:
	CMemDC* mpMemDC;
	void applyChange();
	void fadeEffect(int aStart = 1);
	void onAnimation();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCanvas)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCanvas();

	// Generated message map functions
protected:
	CPlayColor* mpCPlayColor;
	//{{AFX_MSG(CCanvas)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CANVAS_H__402979D8_8268_47A4_8E23_32ACD6EC878E__INCLUDED_)
