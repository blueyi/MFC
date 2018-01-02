// ListSubclassDlg.h : header file
//

#if !defined(AFX_LISTSUBCLASSDLG_H__FCAFAD48_796F_11D5_AD86_B1D3CD2E4211__INCLUDED_)
#define AFX_LISTSUBCLASSDLG_H__FCAFAD48_796F_11D5_AD86_B1D3CD2E4211__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ListBoxEx.h"
/////////////////////////////////////////////////////////////////////////////
// CListSubclassDlg dialog

class CListSubclassDlg : public CDialog
{
// Construction
public:
	BOOL DrawScrolls (CDC *pDC);
COLORREF BkColor,TextColor, HTextClr, HColor;
	CListSubclassDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListSubclassDlg)
	enum { IDD = IDD_LISTSUBCLASS_DIALOG };
	CListBox	m_TextColor;
	CListBox	m_BkColor;
	CListBoxEx	m_names;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListSubclassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	CPalette* SetPalette(CPalette* pPalette);
	CPalette* m_pPalette;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListSubclassDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnInsert();
	afx_msg void OnDblclkTextColor();
	afx_msg void OnDblclkBkColor();
	afx_msg void OnDelete();
	afx_msg void OnDisabled();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTSUBCLASSDLG_H__FCAFAD48_796F_11D5_AD86_B1D3CD2E4211__INCLUDED_)
