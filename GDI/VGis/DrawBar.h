#if !defined(AFX_DRAWBAR_H__1743C9CB_C2F4_4918_B0C1_FE0C65DC0931__INCLUDED_)
#define AFX_DRAWBAR_H__1743C9CB_C2F4_4918_B0C1_FE0C65DC0931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawBar dialog


class CDrawBar : public CDialogBar
{
// Construction
public:
	CDrawBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDrawBar)
	enum { IDD = IDD_DRAW_DIALOGBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler){};

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDrawBar)
	afx_msg void OnLine();
	afx_msg void OnCircle();
	afx_msg void OnArc();
	afx_msg void OnRgn();
	afx_msg void OnMline();
	//}}AFX_MSG
	afx_msg LRESULT InitDialog(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWBAR_H__1743C9CB_C2F4_4918_B0C1_FE0C65DC0931__INCLUDED_)
