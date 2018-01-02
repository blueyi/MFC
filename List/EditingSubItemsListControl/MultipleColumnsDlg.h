// MultipleColumnsDlg.h : header file
//

#if !defined(AFX_MULTIPLECOLUMNSDLG_H__D99A84DB_38F7_477D_9A86_145A9474E25A__INCLUDED_)
#define AFX_MULTIPLECOLUMNSDLG_H__D99A84DB_38F7_477D_9A86_145A9474E25A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMultipleColumnsDlg dialog

class CMultipleColumnsDlg : public CDialog
{
// Construction
public:
	CMultipleColumnsDlg(CWnd* pParent = NULL);	// standard constructor
	void InsertItems();
	void SetCell(HWND hWnd1, CString value, int nRow, int nCol);
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;

	int nItem, nSubItem;


// Dialog Data
	//{{AFX_DATA(CMultipleColumnsDlg)
	enum { IDD = IDD_MULTIPLECOLUMNS_DIALOG };
	CListCtrl	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultipleColumnsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMultipleColumnsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OK();
	afx_msg void OnOK();
	afx_msg void OnExit();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIPLECOLUMNSDLG_H__D99A84DB_38F7_477D_9A86_145A9474E25A__INCLUDED_)
