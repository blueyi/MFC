// VirtualListDlg.h : header file
//

#if !defined(AFX_VIRTUALLISTDLG_H__110C97A6_E572_11D8_B14D_002018574596__INCLUDED_)
#define AFX_VIRTUALLISTDLG_H__110C97A6_E572_11D8_B14D_002018574596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVirtualListDlg dialog

#include <vector>
using namespace std;

#include "randomtext.h"

const int IMAGECOUNT = 4;

class CSampleData
{
public:
	CSampleData()
	{
		m_name = RandomText::GetName();
		m_slogan = RandomText::GetSlogan();
		m_image = rand()%IMAGECOUNT;
		m_checked = (rand()%2!=0);
	}

	CString m_name;
	CString m_slogan;
	int m_image;
	bool m_checked;
};

class CVirtualListDlg : public CDialog
{
// Construction
public:
	BOOL IsCheckBoxesVisible();
	void ToggleCheckBox(int item);
	void UpdateCount();
	CVirtualListDlg(CWnd* pParent = NULL);	// standard constructor

	//This is the database we using
	vector<CSampleData> m_database;

	//Image list
	CImageList m_imagelist;
	CImageList m_imagelistLarge;

// Dialog Data
	//{{AFX_DATA(CVirtualListDlg)
	enum { IDD = IDD_VIRTUALLIST_DIALOG };
	CComboBox	m_style;
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVirtualListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVirtualListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAddten();
	afx_msg void OnButtonClear();
	afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdfinditemList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdcachehintList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboStyle();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIRTUALLISTDLG_H__110C97A6_E572_11D8_B14D_002018574596__INCLUDED_)
