#if !defined(AFX_PPPERSISTENCE_H__C21C4DB8_FAD3_424B_8CE6_AA06DC174310__INCLUDED_)
#define AFX_PPPERSISTENCE_H__C21C4DB8_FAD3_424B_8CE6_AA06DC174310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpPersistence.h : header file
//

#include "FontListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CPpPersistence dialog

class CPpPersistence : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpPersistence)

// Construction
public:
	CPpPersistence();
	~CPpPersistence();

	void AdaptButtonsState();
// Dialog Data
	//{{AFX_DATA(CPpPersistence)
	enum { IDD = IDD_PP_PERSISTENCE };
	CButton	m_btnClearSel;
	CButton	m_btnMruSave;
	CButton	m_btnMruRemove;
	CButton	m_btnMruPersist;
	CButton	m_btnMruLoad;
	CButton	m_btnMruClear;
	CButton	m_btnMruAdd;
	CFontListBox	m_listFont;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpPersistence)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpPersistence)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMruAdd();
	afx_msg void OnBtnMruClear();
	afx_msg void OnBtnMruPersistence();
	afx_msg void OnBtnMruRemove();
	afx_msg void OnBtnMruSave();
	afx_msg void OnBtnClearSel();
	afx_msg void OnSelChangeList();
	afx_msg void OnBtnMruLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPPERSISTENCE_H__C21C4DB8_FAD3_424B_8CE6_AA06DC174310__INCLUDED_)
