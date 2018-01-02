// EditTestDlg.h : header file
//

#if !defined(AFX_EDITTESTDLG_H__A853BFA2_FB1D_4036_B964_3783C6F0C744__INCLUDED_)
#define AFX_EDITTESTDLG_H__A853BFA2_FB1D_4036_B964_3783C6F0C744__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "CurrencyEdit.h"
#include "DateTimeEdit.h"
#include "FloatEdit.h"
#include "Spin.h"
#include "UIntRangeEdit.h"
#include "YearEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CEditTestDlg dialog

class CEditTestDlg : public CDialog
{
// Construction
public:
	CEditTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEditTestDlg)
	enum { IDD = IDD_EDITTEST_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEditTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnRadioDate();
	afx_msg void OnRadioTime();
	afx_msg void OnRadioDateTime();
	afx_msg void OnCheckAllowNull();
	afx_msg void OnCalendar ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	FilterEdit::CDateTimeEdit m_EditDate;
	FilterEdit::CSpin m_SpinDate;
	FilterEdit::CUIntRangeEdit m_EditUInt;
	FilterEdit::CSpin m_SpinUInt;
	FilterEdit::CYearEdit m_EditYear;
	FilterEdit::CFloatEdit m_EditPrice;
	FilterEdit::CBaseEdit m_EditEmail;
public:
	afx_msg void OnMove(int x, int y);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTESTDLG_H__A853BFA2_FB1D_4036_B964_3783C6F0C744__INCLUDED_)
