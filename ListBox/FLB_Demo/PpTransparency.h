#if !defined(AFX_PPTRANSPARENCY_H__A650D877_D224_427A_A322_CDD404DE9100__INCLUDED_)
#define AFX_PPTRANSPARENCY_H__A650D877_D224_427A_A322_CDD404DE9100__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpTransparency.h : header file
//

#include "FLBTransparent.h"
#include "BkBitmap.h"

/////////////////////////////////////////////////////////////////////////////
// CPpTransparency dialog

class CPpTransparency : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpTransparency)

// Construction
public:
	CPpTransparency();
	~CPpTransparency();

	void AdaptButtonsState();

// Dialog Data
	//{{AFX_DATA(CPpTransparency)
	enum { IDD = IDD_PP_TRANSPARENT };
	CButton	m_btnFontChange;
	CButton	m_btnGraphic;
	CButton	m_btnClearSel;
	CBkBitmap	m_image;
	CFLBTransparent	m_listFont;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpTransparency)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpTransparency)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnChangeImage();
	afx_msg void OnBtnClearSel();
	afx_msg void OnSelChangeList();
	afx_msg void OnBtnGraphic();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPTRANSPARENCY_H__A650D877_D224_427A_A322_CDD404DE9100__INCLUDED_)
