#if !defined(AFX_TIMERSPEED_H__44AB8243_FEA9_11D3_85DB_0008C777FFEE__INCLUDED_)
#define AFX_TIMERSPEED_H__44AB8243_FEA9_11D3_85DB_0008C777FFEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimerSpeed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimerSpeed dialog

class CTimerSpeed : public CDialog
{
// Construction
public:
	CTimerSpeed(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimerSpeed)
	enum { IDD = IDD_DTIMER };
	CStatic	m_SpeedMsg;
	CSliderCtrl	m_TimerSpeed;
	int		m_nTimerSpeed;
	//}}AFX_DATA

	CWnd* pWnd;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerSpeed)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimerSpeed)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERSPEED_H__44AB8243_FEA9_11D3_85DB_0008C777FFEE__INCLUDED_)
