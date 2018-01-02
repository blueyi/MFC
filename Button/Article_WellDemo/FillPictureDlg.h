#if !defined(AFX_FILLPICTUREDLG_H__52EABC29_1EDD_444D_BE8C_F5EB914F14D8__INCLUDED_)
#define AFX_FILLPICTUREDLG_H__52EABC29_1EDD_444D_BE8C_F5EB914F14D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "fillgradientdlg.h"
// FillPictureDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFillPictureDlg dialog
class SVIZDLLEXPORT CFillPictureDlg : public CPropertyPage
{
// Construction
public:
	CFillPictureDlg(CWnd* pParent = NULL);   // standard constructor
	DECLARE_DYNAMIC(CFillPictureDlg);
	void		DrawSample		();
	void		SetValue		();

// Dialog Data
	//{{AFX_DATA(CFillPictureDlg)
	enum { IDD = IDD_SVIZ_FILL_PICTURE };
	CComboBox		m_typeCtrl;
	CSampleButton	m_sample;
	int				m_type;
	//}}AFX_DATA
	CString			m_fileName;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFillPictureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFillPictureDlg)
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////



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
