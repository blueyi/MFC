#if !defined(AFX_TEXTDIALOG_H__128F630C_5EB9_4157_B649_67716CD3AD45__INCLUDED_)
#define AFX_TEXTDIALOG_H__128F630C_5EB9_4157_B649_67716CD3AD45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextDialog dialog
#define WM_TEXT_CHANGE WM_USER+10001
#include "Label.h"
//class CGisInterface;

class CTextDialog : public CDialog
{
// Construction
private:
	CLabel m_Text;
	LOGFONT m_lf;
	CString m_str;		//标注文字
	float m_blc;		//当前比例尺
	CWnd *m_pWnd;
public:
	void GetData();
	void Create(CWnd *pWnd,float blc,CLabel &label);
	CTextDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextDialog)
	enum { IDD = IDD_TEXT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextDialog)
	public:
	virtual int DoModal(CWnd *pWnd,float blc,CLabel &label);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextDialog)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeText();
	afx_msg void OnFont();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTDIALOG_H__128F630C_5EB9_4157_B649_67716CD3AD45__INCLUDED_)
