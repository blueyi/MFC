// DynViewsDlg.h : header file
//

#if !defined(AFX_DYNVIEWSDLG_H__F04B773D_4B7E_40EF_BB5F_4FD7E04FFC8C__INCLUDED_)
#define AFX_DYNVIEWSDLG_H__F04B773D_4B7E_40EF_BB5F_4FD7E04FFC8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDynViewsDlg dialog


enum VIEW_TYPE { VIEW_2D, VIEW_OPENGL };

class CDynViewsDlg : public CDialog
{
// Construction
public:
	CDynViewsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDynViewsDlg)
	enum { IDD = IDD_DYNVIEWS_DIALOG };
	CTabCtrl	m_tabCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynViewsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void AddView(VIEW_TYPE viewType);
	void SelectTab(int nTab);
	HICON m_hIcon;

	// This member allows to reference any
	// dynamically created view
	CObList		m_listViews;

	// Generated message map functions
	//{{AFX_MSG(CDynViewsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTabctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddview();
	afx_msg void OnAddopenglview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNVIEWSDLG_H__F04B773D_4B7E_40EF_BB5F_4FD7E04FFC8C__INCLUDED_)
