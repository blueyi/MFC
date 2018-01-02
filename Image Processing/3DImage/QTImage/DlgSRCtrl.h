#if !defined(AFX_DLGSRCTRL_H__B8E1D193_24ED_41CB_A464_0099BB6D6398__INCLUDED_)
#define AFX_DLGSRCTRL_H__B8E1D193_24ED_41CB_A464_0099BB6D6398__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSRCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSRCtrl dialog
#include "DlgSRView.h"

class CDlgSRCtrl : public CDialog
{
// Construction
public:
	CDlgSRCtrl(CWnd* pParent = NULL);   // standard constructor

	CDlgSRView *m_pSRView;

// Dialog Data
	//{{AFX_DATA(CDlgSRCtrl)
	enum { IDD = IDD_IMAGE_SRCTRL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSRCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSRCtrl)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSRCTRL_H__B8E1D193_24ED_41CB_A464_0099BB6D6398__INCLUDED_)
