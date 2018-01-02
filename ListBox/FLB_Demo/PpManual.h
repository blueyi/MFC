#if !defined(AFX_PPMANUAL_H__70D6A1E5_E4EE_40D7_88E0_BA7275275F28__INCLUDED_)
#define AFX_PPMANUAL_H__70D6A1E5_E4EE_40D7_88E0_BA7275275F28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpManual.h : header file
//

#include "FontListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CPpManual dialog

class CPpManual : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpManual)

// Construction
public:
	CPpManual();
	~CPpManual();

	void AdaptButtonsState();
// Dialog Data
	//{{AFX_DATA(CPpManual)
	enum { IDD = IDD_PP_MANUAL };
	CButton	m_btnFontChange;
	CButton	m_btnMruRemove;
	CButton	m_btnMruClear;
	CButton	m_btnMruAdd;
	CButton	m_btnClearSel;
	CButton	m_btnClearList;
	CButton	m_btnRemove;
	CButton	m_btnAdd;
	CFontListBox	m_listFont1;
	//}}AFX_DATA

	CFontListBox*	m_plistFont2;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpManual)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpManual)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelChangeList1();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnRemove();
	afx_msg void OnBtnClearList();
	afx_msg void OnBtnClearSel();
	afx_msg void OnBtnMruAdd();
	afx_msg void OnBtnMruRemove();
	afx_msg void OnBtnMruClear();
	afx_msg void OnButton1();
	//}}AFX_MSG
	afx_msg void OnSelChangeList2();
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPMANUAL_H__70D6A1E5_E4EE_40D7_88E0_BA7275275F28__INCLUDED_)
