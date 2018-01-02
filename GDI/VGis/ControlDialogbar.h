#if !defined(AFX_CONTROLDIALOGBAR_H__6670652C_527F_41CE_9DBF_BBEB3C655F82__INCLUDED_)
#define AFX_CONTROLDIALOGBAR_H__6670652C_527F_41CE_9DBF_BBEB3C655F82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlDialogbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CControlDialogbar dialog

class CControlDialogbar : public CDialogBar
{
// Construction
public:
	CControlDialogbar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CControlDialogbar)
	enum { IDD = IDD_CONTROL_DIALOGBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlDialogbar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler){};

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CControlDialogbar)
	afx_msg void OnMove();
	afx_msg void OnBig();
	afx_msg void OnAll();
	afx_msg void OnRectbig();
	afx_msg void OnSmall();
	//}}AFX_MSG
	afx_msg LRESULT InitDialog(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLDIALOGBAR_H__6670652C_527F_41CE_9DBF_BBEB3C655F82__INCLUDED_)
