#if !defined(AFX_ELAWYER_H__B8EEE87B_9DA7_11D3_91D6_0050BABF4197__INCLUDED_)
#define AFX_ELAWYER_H__B8EEE87B_9DA7_11D3_91D6_0050BABF4197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ELawyer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CELawyer form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CELawyer : public CFormView
{
protected:
	CELawyer();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CELawyer)

// Form Data
public:
	//{{AFX_DATA(CELawyer)
	enum { IDD = IDD_EMPLOY_LAWYER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CELawyer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CELawyer();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CELawyer)
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELAWYER_H__B8EEE87B_9DA7_11D3_91D6_0050BABF4197__INCLUDED_)
