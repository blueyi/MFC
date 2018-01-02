// TransparentControlDlg.h : header file
//

#pragma once

#include "StaticEx.h"
#include "ButtonEx.h"
#include "ButtonEx1.h"
#include "SliderCtrlEx.h"
// CTransparentControlDlg dialog
class CTransparentControlDlg : public CDialog
{
// Construction
public:
	CTransparentControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TRANSPARENTCONTROL_DIALOG };

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
	void BuildBkDC();

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedButton2();
	LRESULT OnTransaprentBk( WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton4();

	CStaticEx m_static1;
	CButtonEx m_Button1;
	CButtonEx1 m_ButtonEx1;
	CSliderCtrlEx m_sliderctrl;
	int m_nBkResID;
	CDC* m_pMemDC;
	CBitmap* m_pOldBitmap;
	CBitmap* m_pBitmapMem;

};
