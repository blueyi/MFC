#if !defined(AFX_MRUPARAMSDLG_H__C7E22A20_47E0_11D2_9505_A0C64BC100C2__INCLUDED_)
#define AFX_MRUPARAMSDLG_H__C7E22A20_47E0_11D2_9505_A0C64BC100C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MRUParamsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMRUParamsDlg dialog

class CMRUParamsDlg : public CDialog
{
// Construction
public:
	CMRUParamsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMRUParamsDlg)
	enum { IDD = IDD_SET_MRU_PARAMS };
	CSpinButtonCtrl	m_spinner;
	int		m_nMRUSize;
	CString	m_cstrRegKey;
	CString	m_cstrRegValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRUParamsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMRUParamsDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRUPARAMSDLG_H__C7E22A20_47E0_11D2_9505_A0C64BC100C2__INCLUDED_)
