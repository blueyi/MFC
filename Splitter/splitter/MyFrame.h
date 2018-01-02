#if !defined(AFX_MYFRAME_H__CF47D870_5027_11D5_AC0B_00104B2CD040__INCLUDED_)
#define AFX_MYFRAME_H__CF47D870_5027_11D5_AC0B_00104B2CD040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFrame frame

class CMyFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMyFrame)
protected:
	CMyFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyFrame();

	// Generated message map functions
	//{{AFX_MSG(CMyFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFRAME_H__CF47D870_5027_11D5_AC0B_00104B2CD040__INCLUDED_)
