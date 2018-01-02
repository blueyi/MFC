// ProSliderDlg.h : header file
//
//	See disclaimer.txt or ProSliderCtrl.h for copyright & usage issues
//  © Copyright 2004 Cem KARACA.

#pragma once
#include "afxcmn.h"
#include "prosliderctrl.h"
#include "afxwin.h"
#include <math.h>

// CProSliderDlg dialog
class CProSliderDlg : public CDialog
{
// Construction
public:
	CProSliderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROSLIDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Slider bar to control ProSlider slider position
	CSliderCtrl m_sl1;
	// Slider bar to control Proslider progress bar
	CSliderCtrl m_sl2;
	// Pro Slider handle
	CProSliderCtrl m_ProSlider;
	// Vertical ProSlider Bar
	CProSliderCtrl m_VerProSlider;
	// Debug screen 1
	CStatic m_Static1;
	// Debug text for progress bar
	CStatic m_Static2;
	// Start Button
	CButton m_btnStart;
	CButton m_btnStop;
	// Slider Position for animation
	int m_SliderPos;
	// Progress Bar position
	int m_ProgressPos;
	// Timer Value
	int m_TimerValue;
	// Timer Value
	int m_TimerValue1;
	afx_msg void OnBnStart();
	afx_msg void OnBnStop();
	afx_msg void OnTimer(UINT nIDEvent);
	// Returns negative exponential of mean, i.e. Poisson random numbers
	double nexp(double mean);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnEnChangeEdit();
	// Progress Bar
	CProgressCtrl m_Progress;
	// Timer for Slider ctrl animation
	CEdit m_EditTimer;
	// Timer for Progress bar animation
	CEdit m_EditTimer1;
	CButton m_btnStart1;
	CButton m_btnStop1;
	afx_msg void OnBnStart1();
	afx_msg void OnBnStop1();
	afx_msg void OnEnChangeEdit2();
	CButton m_bnBorders;
	afx_msg void OnBnBorders();
	afx_msg void OnBnStepIt();
	afx_msg void OnBnRandom();
	afx_msg void OnBnFreeze();
	CButton m_bnFreeze;
};
