#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "ColoredDlg.h"
#include "CustomSlider.h"
#include "CustomButton.h"

// COptionsDlg dialog

class COptionsDlg : public CColoredDlg
{
	DECLARE_DYNAMIC(COptionsDlg)

public:
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionsDlg();

// Dialog Data
	enum { IDD = IDD_OPTIONS_DLG };

protected:

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void DrawListFontSizeText();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedAboutBtn();
	afx_msg void OnBnClickedHidePeers();
	afx_msg void OnBnClickedHideSec();
	afx_msg void OnBnClickedSoundOn();
	afx_msg void OnPaint();

public:
	CComboBox m_adapters;
	CCustomSlider m_speed;
	CCustomButton m_hidepeers;
	CCustomButton m_hidesec;
	CCustomButton m_soundoff;
	CString m_strScanSpeed;

	CCustomSlider m_fontsize;
	CCustomButton m_btnAbout;
};
