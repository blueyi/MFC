#if !defined(AFX_RTDLG_H__607B1DE5_F605_11D3_85D4_0008C777FFEE__INCLUDED_)
#define AFX_RTDLG_H__607B1DE5_F605_11D3_85D4_0008C777FFEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RTDlg.h : header file
//

#include "OwnList.h"

/////////////////////////////////////////////////////////////////////////////
// CRTDlg dialog

class CRTDlg : public CDialog
{
// Construction
public:
	CRTDlg(CWnd* pParent = NULL);   // standard constructor
	CWnd* m_pParent;

// Dialog Data
	//{{AFX_DATA(CRTDlg)
	enum { IDD = IDD_DDELETE };
	COwnerDrawListBox	m_LDeleteName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ResetColorList();

	// Generated message map functions
	//{{AFX_MSG(CRTDlg)
	afx_msg void OnBdelete();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkLdeletename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CModify dialog
#include "ColorBtn.h"
class CModify : public CDialog
{
// Construction
public:
	CModify(CWnd* pParent = NULL);   // standard constructor
	CWnd* m_pParent;

// Dialog Data
	//{{AFX_DATA(CModify)
	enum { IDD = IDD_DMODIFY };
	CButton	m_BApply;
	CSpinButtonCtrl	m_SMWidth;
	CComboBox	m_CMStyle;
	CComboBox	m_CMName;
	CColorButton	m_BMColor;
	CString	m_EMDesc;
	double	m_EMMax;
	double	m_EMMin;
	double	m_EMScaleMin;
	CString	m_EMUnit;
	int		m_EMWidth;
	double	m_EMScaleMax;
	CString	m_EMName;
	//}}AFX_DATA

	COLORREF m_nColor;
	int		 m_nIndex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Reset(int i);
	void SaveLine(int i);

	// Generated message map functions
	//{{AFX_MSG(CModify)
	afx_msg void OnBmcolor();
	afx_msg void OnSelchangeCmname();
	afx_msg void OnSelchangeCmstyle();
	virtual BOOL OnInitDialog();
	afx_msg void OnBapply();
	afx_msg void OnChangeEmname();
	afx_msg void OnChangeEmdesc();
	afx_msg void OnChangeEmunit();
	afx_msg void OnChangeEmwidth();
	afx_msg void OnChangeEmmin();
	afx_msg void OnChangeEmmax();
	afx_msg void OnChangeEmscalemin();
	afx_msg void OnChangeEmscalemax();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CInsert dialog

class CInsert : public CDialog
{
// Construction
public:
	CInsert(CWnd* pParent = NULL);   // standard constructor
	CWnd* m_pParent;

// Dialog Data
	//{{AFX_DATA(CInsert)
	enum { IDD = IDD_DINSERT };
	CButton	m_BIApply;
	CSpinButtonCtrl	m_SIWidth;
	CSpinButtonCtrl	m_SIIndex;
	CComboBox	m_CIStyle;
	CColorButton	m_BIColor;
	CString	m_EIDesc;
	int		m_EIIndex;
	double	m_EIMax;
	double	m_EIMin;
	CString	m_EIName;
	double	m_EIScaledMax;
	double	m_EIScaledMin;
	CString	m_EIUnit;
	int		m_EIWidth;
	//}}AFX_DATA

	COLORREF m_nColor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsert)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InsertALine();

	// Generated message map functions
	//{{AFX_MSG(CInsert)
	afx_msg void OnBicolor();
	afx_msg void OnSelchangeCistyle();
	virtual BOOL OnInitDialog();
	afx_msg void OnBiapply();
	virtual void OnCancel();
	afx_msg void OnChangeEiwidth();
	afx_msg void OnChangeEiunit();
	afx_msg void OnChangeEiscaledmin();
	afx_msg void OnChangeEiscaledmax();
	afx_msg void OnChangeEIName();
	afx_msg void OnChangeEimin();
	afx_msg void OnChangeEimax();
	afx_msg void OnChangeEiindex();
	afx_msg void OnChangeEidescription();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTDLG_H__607B1DE5_F605_11D3_85D4_0008C777FFEE__INCLUDED_)
