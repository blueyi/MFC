#if !defined(AFX_SVIZ_FILLGRADIENTDLG_H__1012)
#define AFX_SVIZ_FILLGRADIENTDLG_H__1012

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
#include "colourpicker.h"

/////////////////////////////////////////////////////////////////////////////
// CFillGradientDlg dialog
class SVIZDLLEXPORT CSampleButton : public CButton
{
// Construction
public:
    CSampleButton();
    DECLARE_DYNCREATE(CSampleButton);
private:

	void DrawItemPattern(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawItemLinear(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawItemPicture(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	// Overrides
	// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSampleButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation

};

class SVIZDLLEXPORT CFillGradientDlg : public CPropertyPage
{
// Construction
public:
	CFillGradientDlg(CWnd* pParent = NULL);   // standard constructor
	DECLARE_DYNAMIC(CFillGradientDlg);
	void			SetValue	();
	void			DrawSample	();

// Dialog Data
	//{{AFX_DATA(CFillGradientDlg)
	enum { IDD = IDD_SVIZ_FILL_GRADIENT };
	CSampleButton	m_sample;
	CScrollBar		m_darkCtrl;
	CColourPicker	m_color2btn;
	CColourPicker	m_color1btn;
	CScrollBar		m_endTr;
	CScrollBar		m_startTr;
	int				m_startTransparency;
	int				m_endTransparency;
	int				m_dark;
	int				m_nStyle;
	//}}AFX_DATA

	BOOL    m_bInitilized;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFillGradientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFillGradientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
	DECLARE_MESSAGE_MAP()
};



#endif 
///////////////////////////////////////////////////////////////////////
// This file is a part of the SViz MFC Extention Class.
// 2001-2002 SVizSoft Software, All Rights Reserved.
//
// SVIZSOFT GRANTS TO YOU THE LIMITED RIGHT TO USE THIS SOFTWARE ON 
// A SINGLE COMPUTER. 
// THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE THE PROPERTY
// OF SVIZSOFT AND ARE NOT TO BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER
// WITHOUT THE EXPRESSED WRITTEN CONSENT OF SVIZ SOFTWARE.
// 
// You can contact us.
// admin@svizsoft.com
///////////////////////////////////////////////////////////////////////
