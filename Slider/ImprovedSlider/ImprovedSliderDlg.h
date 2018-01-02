// ImprovedSliderDlg.h : header file
//

#if !defined(IMPROVED_SLIDER_DLG_H)
#define IMPROVED_SLIDER_DLG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NiceSlider.h"

/////////////////////////////////////////////////////////////////////////////
// CImprovedSliderDlg dialog

class CImprovedSliderDlg : public CDialog
{
// Construction
public:
	CImprovedSliderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImprovedSliderDlg)
	enum { IDD = IDD_IMPROVEDSLIDER_DIALOG };
	CSliderCtrl	m_slider;
	CNiceSliderCtrl	m_sliderImproved;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImprovedSliderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImprovedSliderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(IMPROVED_SLIDER_DLG_H)
