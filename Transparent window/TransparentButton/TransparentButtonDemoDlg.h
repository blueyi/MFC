// TransparentButtonDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "HoverButton.h"


// CTransparentButtonDemoDlg dialog
class CTransparentButtonDemoDlg : public CDialog
{
// Construction
public:
	CTransparentButtonDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TRANSPARENTBUTTONDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	const int m_nWidth;
	const int m_nHeight;
	CRgn  m_WinRgn;

	CBitmap	m_Bitmap;
	CPalette m_Palette;

	int m_nBkGrndBitmapID;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CHoverButtonEx m_OpenButton;
	CHoverButtonEx m_SaveButton;
	CHoverButtonEx m_Btn1;
	CHoverButtonEx m_Btn2;
	CHoverButtonEx m_Btn3;
	CHoverButtonEx m_Btn4;
	CHoverButtonEx m_ExitBtn;
	afx_msg void OnBnClickedNextBg();
};
