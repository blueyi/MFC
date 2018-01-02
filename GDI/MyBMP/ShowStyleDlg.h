#if !defined(AFX_BMPSTYLEDLG_H__13AF3722_4A0C_11D4_9F8F_0080C88D88FF__INCLUDED_)
#define AFX_BMPSTYLEDLG_H__13AF3722_4A0C_11D4_9F8F_0080C88D88FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpStyleDlg.h : header file
// Download by http://www.codefans.net

/////////////////////////////////////////////////////////////////////////////
// CBmpStyleDlg dialog
//只需要引入头文件，并把基类改成CMyDialog就行了，不需要任何其他操作
#include "MyDialog.h"
#include "MyStatic.h"
class CShowStyleDlg : public CMyDialog
{
// Construction
public:
	CShowStyleDlg(CWnd* pParent = NULL);   // standard constructor
	CMyStatic m_useStatic;
// Dialog Data
	//{{AFX_DATA(CBmpStyleDlg)
	enum { IDD = IDD_SHOW_STYLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpStyleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBmpStyleDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPSTYLEDLG_H__13AF3722_4A0C_11D4_9F8F_0080C88D88FF__INCLUDED_)
