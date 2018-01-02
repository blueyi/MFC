#pragma once

#include "afxcmn.h"

#include "ColoredDlg.h"
#include "ListCtrlEx.h"

// CWifiDevicesDlg dialog

class CScannerDlg : public CColoredDlg
{
	DECLARE_DYNAMIC(CScannerDlg)

public:
	CScannerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScannerDlg();
	void UpdateList();
	void SetListFont(int iFontSize);

// Dialog Data
	enum { IDD = IDD_SCANNER_DLG };

protected:
	void UpdateItem(DisplayInfo nfo);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnPopupGolarge();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

	bool GetRow(DWORD ID, DisplayInfo &di);
	void ApplyListFont();
	bool m_bListFontApplied;

	DisplayInfo m_diTmp;
	int m_iListFontSize;
	bool m_bLarge;
	int m_iLargeID;

	CListCtrlEx m_list;
	CFont m_listfont;
	CString m_numactive;
	CString m_rb_static;
};
