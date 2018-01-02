// ValidatingEditDemoDlg.h : header file
//

#if !defined(AFX_VALIDATINGEDITDEMODLG_H__47C40B3E_B2C8_11D5_938E_0002A50C1C28__INCLUDED_)
#define AFX_VALIDATINGEDITDEMODLG_H__47C40B3E_B2C8_11D5_938E_0002A50C1C28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "amsEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CValidatingEditDemoDlg dialog

class CValidatingEditDemoDlg : public CDialog
{
// Construction
public:
	CValidatingEditDemoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CValidatingEditDemoDlg)
	enum { IDD = IDD_VALIDATING_EDIT_DEMO };
	CAMSTimeEdit	m_ctlEditTimeDataEntry;
	CSpinButtonCtrl	m_ctlSpinNumericRightDigits;
	CSpinButtonCtrl	m_ctlSpinNumericLeftDigits;
	CSpinButtonCtrl	m_ctlSpinAlphanumericMaxCharacters;
	CAMSCurrencyEdit	m_ctlEditCurrencyDataEntry;
	CAMSNumericEdit	m_ctlEditNumericDataEntry;
	CAMSMaskedEdit	m_ctlEditMaskedDataEntry;
	CAMSDateEdit	m_ctlEditDateDataEntry;
	CAMSAlphanumericEdit	m_ctlEditAlphanumericDataEntry;
	BOOL	m_bCheckNumericCannotBeNegative;
	CString	m_strEditAlphanumericInvalidCharacters;
	double	m_dEditCurrencyAsDouble;
	CString	m_strEditMaskedMask;
	int		m_nEditNumericRightDigits;
	int		m_nEditNumericLeftDigits;
	double	m_dEditNumericAsDouble;
	int		m_nEditAlphanumericMaxCharacters;
	BOOL	m_bCheckTime24HourFormat;
	BOOL	m_bCheckTimeShowSeconds;
	//}}AFX_DATA

	CDateTimeCtrl m_dateMax;
	CDateTimeCtrl m_dateMin;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValidatingEditDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CValidatingEditDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEditAlphanumericInvalidCharacters();
	afx_msg void OnCheckNumericCannotBeNegative();
	afx_msg void OnChangeEditMaskedMask();
	afx_msg void OnChangeEditCurrencyDataEntry();
	afx_msg void OnChangeEditNumericDataEntry();
	afx_msg void OnChangeEditAlphanumericMaxCharacters();
	afx_msg void OnChangeEditNumericLeftDigits();
	afx_msg void OnChangeEditNumericRightDigits();
	afx_msg void OnCheckTime24HourFormat();
	afx_msg void OnCheckTimeShowSeconds();
	afx_msg void OnChangeDateRange(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALIDATINGEDITDEMODLG_H__47C40B3E_B2C8_11D5_938E_0002A50C1C28__INCLUDED_)
