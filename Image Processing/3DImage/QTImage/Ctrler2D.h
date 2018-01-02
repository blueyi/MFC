#if !defined(AFX_CTRLER2D_H__1F4A0FAC_74A1_4052_B602_21DC1516223F__INCLUDED_)
#define AFX_CTRLER2D_H__1F4A0FAC_74A1_4052_B602_21DC1516223F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ctrler2D.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DCtrler dialog

class C2DCtrler : public CDialog
{
// Construction
public:
	C2DCtrler(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C2DCtrler)
	enum { IDD = IDD_IMAGE_CTRL2D };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DCtrler)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C2DCtrler)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRLER2D_H__1F4A0FAC_74A1_4052_B602_21DC1516223F__INCLUDED_)
