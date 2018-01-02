#if !defined(AFX_PPMRUSYNC_H__126EAA53_2F1B_4747_9DAD_F0391FAB44C8__INCLUDED_)
#define AFX_PPMRUSYNC_H__126EAA53_2F1B_4747_9DAD_F0391FAB44C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpMruSync.h : header file
//

#include "FontListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CPpMruSync dialog

class CPpMruSync : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpMruSync)

// Construction
public:
	CPpMruSync();
	~CPpMruSync();

// Dialog Data
	//{{AFX_DATA(CPpMruSync)
	enum { IDD = IDD_PP_MRUSYNC };
	CButton	m_btnClear2;
	CButton	m_btnClear1;
	CFontListBox	m_listFont2;
	CButton	m_btnRemove;
	CButton	m_btnAdd;
	CFontListBox	m_listFont1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpMruSync)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpMruSync)
	afx_msg void OnBtnMruAdd();
	afx_msg void OnBtnMruRemove();
	afx_msg void OnSelChangeList1();
	afx_msg void OnSelChangeList2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMruClear1();
	afx_msg void OnBtnMruClear2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPMRUSYNC_H__126EAA53_2F1B_4747_9DAD_F0391FAB44C8__INCLUDED_)
