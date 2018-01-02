// ctstdlg.h : header file
//

#if !defined(AFX_CTSTDLG_H__4431C3B6_BA35_41AA_9BF4_CEDED4690ADC__INCLUDED_)
#define AFX_CTSTDLG_H__4431C3B6_BA35_41AA_9BF4_CEDED4690ADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MChMemBm.h"

/////////////////////////////////////////////////////////////////////////////
// CTstDlg dialog

class CTstDlg : public CDialog
{
// Construction
public:
	CTstDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTstDlg)
	enum { IDD = IDD_MEMBMTST2_DIALOG };
	CComboBox	m_cbxBmpResSelector;
	int		m_iBmpUsage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTstDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void PopulateBmpResourceSelector();

private:
	MChMemBm m_Bitmap;
	void UpdateBitmap();
	static CStringList m_slstBmpResNames;
	static BOOL CALLBACK EnumBmpResNames( HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LPARAM lParam );

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTstDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeResbmpselector();
	afx_msg void OnBmpusage();
	//}}AFX_MSG
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTSTDLG_H__4431C3B6_BA35_41AA_9BF4_CEDED4690ADC__INCLUDED_)
