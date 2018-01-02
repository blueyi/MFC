// TTreeCtrlDemoDlg.h : header file
//

#if !defined(AFX_TTREECTRLDEMODLG_H__6FA6B899_3CE1_4237_82B9_AD2908D797D9__INCLUDED_)
#define AFX_TTREECTRLDEMODLG_H__6FA6B899_3CE1_4237_82B9_AD2908D797D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeCtrlCh.h"


/////////////////////////////////////////////////////////////////////////////
// CTTreeCtrlDemoDlg dialog
class TTipItemData:public ItemDataABSTRACT
{
public:

	TTipItemData();
	CString strTool;
	POSITION pos;
	CString GetToolTipString();
};



class CTTreeCtrlDemoDlg : public CDialog
{
// Construction
public:
	CTTreeCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTTreeCtrlDemoDlg)
	enum { IDD = IDD_TTREECTRLDEMO_DIALOG };
	CTreeCtrlCh	m_Tree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTreeCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTTreeCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTREECTRLDEMODLG_H__6FA6B899_3CE1_4237_82B9_AD2908D797D9__INCLUDED_)
