#if !defined(AFX_PGLREGIONPROPPAGE_H__0217D8D5_EFD3_4A9A_8029_9B4879DDACAD__INCLUDED_)
#define AFX_PGLREGIONPROPPAGE_H__0217D8D5_EFD3_4A9A_8029_9B4879DDACAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLRegionPropPage.h : header file
//
#include "pgl/PGLRegion.h"

/////////////////////////////////////////////////////////////////////////////
// CPGLRegionPropPage dialog
class CPGLRegionPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPGLRegionPropPage)

// Construction
public:
	CPGLRegionPropPage(CPGLRegion* pRegion = NULL);
	~CPGLRegionPropPage();

// Dialog Data
	//{{AFX_DATA(CPGLRegionPropPage)
	enum { IDD = IDD_PGL_PROPPAGE_REGION };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPGLRegionPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPGLRegion* m_pRegion;
	// Generated message map functions
	//{{AFX_MSG(CPGLRegionPropPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLREGIONPROPPAGE_H__0217D8D5_EFD3_4A9A_8029_9B4879DDACAD__INCLUDED_)
