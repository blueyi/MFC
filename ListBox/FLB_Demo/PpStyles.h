#if !defined(AFX_PPSTYLES_H__67CA9AFB_4B72_4774_B113_74694C2743CC__INCLUDED_)
#define AFX_PPSTYLES_H__67CA9AFB_4B72_4774_B113_74694C2743CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpStyles.h : header file
//

#include "FontListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CPpStyles dialog

class CPpStyles : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpStyles)

// Construction
public:
	CPpStyles();
	~CPpStyles();

	void AdaptBtnState();
// Dialog Data
	//{{AFX_DATA(CPpStyles)
	enum { IDD = IDD_PP_STYLES };
	CButton	m_ClearSel;
	CButton	m_btnClearMru;
	CFontListBox	m_listFont;
	CComboBox	m_listStyleCtl;
	CButton	m_MruListCtl;
	CButton	m_MruAdd;
	CButton	m_MruTypeCtl0;
	CButton	m_MruTypeCtl1;
	CButton	m_MruTypeCtl2;
	CButton	m_btnApply;
	int		m_TTWhat;
	CString	m_strSample;
	BOOL	m_TTTracking;
	BOOL	m_hasTT;
	BOOL	m_displayGraphic;
	int		m_MruType;
	BOOL	m_MruList;
	BOOL	m_ExpandedHeight;
	CString	m_MruName;
	int		m_listStyle;
	BOOL	m_officeBitmap;
	BOOL	m_TTShowSel;
	CString	m_TtMaxItems;
	//}}AFX_DATA
//	CFontListBox	m_listFont;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpStyles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpStyles)
	virtual BOOL OnInitDialog();
	afx_msg void OnApplyStyleChanges();
	afx_msg void OnModifyData();
	afx_msg void OnBtnMruadd();
	afx_msg void OnSelchangeListFont();
	afx_msg void OnShowFontDialog();
	afx_msg void OnBtnClearSel();
	afx_msg void OnSelCancelListFont();
	afx_msg void OnBtnClearMru();
	afx_msg void OnChangeTtMaxItems();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPSTYLES_H__67CA9AFB_4B72_4774_B113_74694C2743CC__INCLUDED_)
